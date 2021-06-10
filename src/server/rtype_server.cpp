/*
** EPITECH PROJECT, 2019
** rtype server
** File description:
** cpp
*/

#include "rtype_server.hpp"

namespace RType
{

	Server::Server(uint16_t local_port) :
		socket(io_service, udp::endpoint(udp::v4(), local_port)),
		nextClientID(0L),
		service_thread(std::bind(&Server::run_service, this))
	{
    	std::cout << "Starting server on port " << static_cast<short>(local_port) << std::endl;
		
		std::ifstream infile("../res/map/map2.txt");
		std::string str;
		while (infile >> str) {
			this->map.push_back(str);
		}
		float map_size = static_cast<int>(this->map[0].size() * ((BLOCK_SIZE - 1) * BLOCK_SCALE) - SCREEN_WIDTH);
		std::srand(std::time(0));
		for (float i = SCREEN_WIDTH; i < map_size; i++) {
			if (std::rand() % ENNEMY_CHANCE == 1) {
				ennemies.push_back(Ennemy(i));
				i += ENNEMY_SIZE * 2;
			}
		}
	};

	Server::~Server()
	{
		io_service.stop();
		service_thread.join();
	}

	void Server::start_receive()
	{
		socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
			boost::bind(&Server::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}

	void Server::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
	{
		if (!error) {
			try {
				auto message = ClientMessage(std::string(recv_buffer.data(), recv_buffer.data() + bytes_transferred), get_client_id(remote_endpoint));
				if (!message.first.empty())
					incomingMessages.push(message);
			}
			catch (std::exception ex) {
            	std::cout << "handle_receive: Error parsing incoming message: " << ex.what() << std::endl;
			}
			catch (...) {
            	std::cout << "handle_receive: Unknown error while parsing incoming message" << std::endl;
			}
		} else {
        	std::cout << "handle_receive: error: " << error.message() << std::endl;
		}

		start_receive();
	}

	void Server::send(const std::string& message, udp::endpoint target_endpoint)
	{
		socket.send_to(boost::asio::buffer(message), target_endpoint);
	}

	void Server::run_service()
	{
		start_receive();
		while (!io_service.stopped()){
			try {
				io_service.run();
			}
			catch (const std::exception& e) {
				std::cout << "Server: Network exception: " << e.what() << std::endl;
			}
			catch (...) {
				std::cout << "Server: Network exception: unknown" << std::endl;
			}
		}
		std::cout << "Server network thread stopped" << std::endl;
	};

	uint64_t Server::get_client_id(udp::endpoint endpoint)
	{
		auto cit = clients.right.find(endpoint);
		if (cit != clients.right.end())
			return (*cit).second;

		nextClientID++;
		clients.insert(Client(nextClientID, endpoint));
		players.push_back(Player(nextClientID));
		std::cout << "NEW CLIENT : " << static_cast<unsigned long long int>(nextClientID) << std::endl;
		this->SendToClient(std::string("MAP|") + this->getMapString(), nextClientID);
		return nextClientID;
	};

	bool Server::disconnect(const uint64_t clientId)
	{
		std::unique_lock<std::mutex> lock(_serverMutex);
		for (auto cit : clients) {
			if (cit.left == clientId) {
				for (int i = 0; i < players.size(); i++) {
					if (players[i]._clientId == clientId) {
						clients.erase(cit);
						players.erase(players.begin() + i);
						std::cout << "RES CLIENT : " << static_cast<unsigned long long int>(clientId) << std::endl;
						return true;
					}
				}
			}
		}
		return false;
	}

	void Server::SendToClient(const std::string& message, uint64_t clientID)
	{
		try {
			send(message, clients.left.at(clientID));
		}
		catch (std::out_of_range) {
			std::cout << "Unknown client ID " << static_cast<unsigned long long int>(clientID) << std::endl;
		}
	};

	void Server::SendToAllExcept(const std::string& message, uint64_t clientID)
	{
		for (auto client : clients) {
			if (client.left != clientID)
				send(message, client.right);
		}
	};

	void Server::SendToAll(const std::string& message)
	{
		for (auto client : clients) {
			send(message, client.right);
		}
	};

	ClientMessage Server::PopMessage()
	{
		return incomingMessages.pop();
	}

	bool Server::HasMessages()
	{
		return !incomingMessages.empty();
	};

	std::string Server::getMapString()
	{
		std::string str;
		for (size_t y = 0; y < this->map.size(); y++) {
			for (size_t x = 0; x < this->map[y].size(); x++) {
				str += std::to_string(x * 39) + "," + std::to_string(y * 39) + "," + this->map[y][x] + ";";
			}
		}
		str.pop_back();
		return (str);
	};

	void Server::movePlayer(uint64_t id, std::string dir)
	{
		std::unique_lock<std::mutex> lock(_serverMutex);
		for (auto &p : this->players) {
			if (p._clientId == id) {
				p.move(map, dir);
			}
		}
	}

	void Server::launchShot(uint64_t id)
	{
		std::unique_lock<std::mutex> lock(_serverMutex);
		for (auto &p : this->players) {
			if (p._clientId == id) {
				lasers.push_back(Laser(pos_t{p._pos.x + ((PLAYER_SIZE * PLAYER_SCALE) / 2), p._pos.y + ((PLAYER_SIZE * PLAYER_SCALE) / 2)}, id, 10));
			}
		}
	}

	void Server::update()
	{
		std::unique_lock<std::mutex> lock(_serverMutex);
		auto esize = ENNEMY_SIZE * ENNEMY_SCALE;
		auto lsizex = LASER_SIZEX * LASER_SCALE;
		auto lsizey = LASER_SIZEY * LASER_SCALE;
		for (Player &p : players) {
			p._realPos.x += MAP_SPEED;
			size_t block_posx = (p._realPos.x + (PLAYER_SIZE * PLAYER_SCALE)) / (BLOCK_SIZE * BLOCK_SCALE);
        	size_t block_posy_high = p._realPos.y / (BLOCK_SIZE * BLOCK_SCALE);
			size_t block_posy_low = (p._realPos.y + (PLAYER_SIZE * PLAYER_SCALE)) / (BLOCK_SIZE * BLOCK_SCALE);
			if (block_posy_low >= 0 && map[block_posy_high][block_posx] == 'x' || block_posy_high <= SCREEN_HEIGHT && map[block_posy_low][block_posx] == 'x') {
				p._pos.x -= MAP_SPEED;
				p._realPos.x -= MAP_SPEED;
			}
		}
		for (size_t i = 0; i < lasers.size(); i++) {
			lasers[i]._curPos.x += lasers[i]._speed;
			if (lasers[i].isLaserGone())
				lasers.erase(lasers.begin() + i);
		}
		for (Ennemy &e : ennemies) {
			for (size_t i = 0; i < players.size(); i++) {
				if (players[i].isInside(e._pos.x, e._pos.y) ||
					players[i].isInside(e._pos.x + (ENNEMY_SIZE * ENNEMY_SCALE), e._pos.y) ||
					players[i].isInside(e._pos.x, e._pos.y + (ENNEMY_SIZE * ENNEMY_SCALE)) ||
					players[i].isInside(e._pos.x + (ENNEMY_SIZE * ENNEMY_SCALE), e._pos.y + (ENNEMY_SIZE * ENNEMY_SCALE))) {
					players.erase(players.begin() + i);
				}
			}
			e._pos.x -= ENNEMY_SPEED;
			e._pos.y = static_cast<float>((ENNEMY_SIN * sin(e._pos.x / 100)) + (SCREEN_HEIGHT / 2));
			if (e._pos.x < -ENNEMY_SIZE) {
				ennemies.erase(ennemies.begin());
			}
		}
		for (unsigned i=0; i < ennemies.size(); i++) {
			auto &e = ennemies[i];
			for (unsigned j=0; j < lasers.size(); j++) {
				auto &l = lasers[i];
				if ((l._curPos.x > e._pos.x && l._curPos.x < e._pos.x + esize && l._curPos.y > e._pos.y && l._curPos.y < e._pos.y + esize) ||
				(l._curPos.x + lsizex > e._pos.x && l._curPos.x + lsizex < e._pos.x + esize && l._curPos.y > e._pos.y && l._curPos.y < e._pos.y + esize) ||
				(l._curPos.x > e._pos.x && l._curPos.x < e._pos.x + esize && l._curPos.y + lsizex > e._pos.y && l._curPos.y + lsizey < e._pos.y + esize) ||
				(l._curPos.x + lsizex > e._pos.x && l._curPos.x + lsizex < e._pos.x + esize && l._curPos.y + lsizey > e._pos.y && l._curPos.y + lsizey < e._pos.y + esize)) {
					ennemies.erase(ennemies.begin() + i);
					lasers.erase(lasers.begin() + j);
				}
			}
		}
	}
}