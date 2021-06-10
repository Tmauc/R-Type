/*
** EPITECH PROJECT, 2019
** rtype client
** File description:
** cpp
*/

#include "rtype_client.hpp"

namespace RType
{
	Client::Client(std::string host, std::string server_port, uint16_t local_port) :
		socket(io_service, udp::endpoint(udp::v4(), local_port)),
		service_thread(std::bind(&Client::run_service, this))
	{
		udp::resolver resolver(io_service);
		udp::resolver::query query(udp::v4(), host, server_port);
		server_endpoint = *resolver.resolve(query);
		Send("NEW");
	}

	Client::~Client()
	{
		this->disconnect();
		io_service.stop();
		service_thread.join();
	}

	void Client::start_receive()
	{
		socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
			boost::bind(&Client::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}

	void Client::disconnect(void)
	{
		if (!io_service.stopped()) {
			this->Send("RES");
		}
	}

	void Client::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
	{
		if (!error) {
			std::string message(recv_buffer.data(), recv_buffer.data() + bytes_transferred);
			incomingMessages.push(message);
		} else {
			std::cerr << "Client::handle_receive: " << error.message() << std::endl;
		}
		start_receive();
	}

	void Client::Send(std::string message)
	{
		socket.send_to(boost::asio::buffer(message), server_endpoint);
	}

	void Client::run_service()
	{
		start_receive();
		while (!io_service.stopped()) {
			try {
				io_service.run();
			}
			catch (const std::exception& e) {
				std::cerr << "NetworkServer: Network exception: " << e.what() << std::endl;
			}
			catch (...) {
				std::cerr << "Unknown exception in client network thread" << std::endl;
			}
		}
	}
}; // namespace Rtype