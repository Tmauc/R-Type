/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** server
*/

#ifndef RTYPE_SERVER_HPP_
#define RTYPE_SERVER_HPP_

#include "rtype.hpp"
#include "Player.hpp"
#include "Laser.hpp"
#include "Ennemy.hpp"

using boost::asio::ip::udp;

typedef boost::bimap<uint64_t, udp::endpoint> ClientList;
typedef ClientList::value_type Client;
typedef std::pair<std::string, uint64_t> ClientMessage;

namespace RType
{

    class Server {
	public:
		Server(uint16_t local_port);
		~Server();

		bool HasMessages();
		ClientMessage PopMessage();

		void SendToClient(const std::string& message, uint64_t clientID);
		void SendToAllExcept(const std::string& message, uint64_t clientID);
		void SendToAll(const std::string& message);
		void update(void);
		bool disconnect(const uint64_t clientId);

		void movePlayer(uint64_t id, std::string dir);
		void launchShot(uint64_t id);

		std::vector<Player> players;
		std::vector<Laser> lasers;
		std::vector<Ennemy> ennemies;

	private:
		// Network send/receive stuff
		std::mutex _serverMutex;
		boost::asio::io_service io_service;
		udp::socket socket;
		udp::endpoint server_endpoint;
		udp::endpoint remote_endpoint;
		std::array<char, BUFFER_SIZE> recv_buffer;
		boost::thread service_thread;

		void start_receive();
		void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
		void handle_send(std::string /*message*/, const boost::system::error_code& /*error*/, std::size_t /*bytes_transferred*/) {}
		void run_service();
		uint64_t get_client_id(udp::endpoint endpoint);

		void send(const std::string& message, udp::endpoint target);

		// Incoming messages queue
		RTypeQueue<ClientMessage> incomingMessages;

		std::string getMapString();
		std::vector<std::string> map;

		// Clients of the server
		ClientList clients;

		uint64_t nextClientID;

		Server(Server&); // block default copy constructor
	};

} // namespace RType

#endif /* !RTYPE_SERVER_HPP_ */