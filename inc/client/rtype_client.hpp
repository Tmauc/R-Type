/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** client
*/

#ifndef RTYPE_CLIENT_HPP_
#define RTYPE_CLIENT_HPP_

#include "rtype.hpp"
#include <cstring>

using boost::asio::ip::udp;

namespace RType
{
class Client {
	public:
		Client(std::string host, std::string server_port, uint16_t local_port = 0);
		~Client();

		void Send(std::string message);
		void disconnect(void);
		inline bool HasMessages() { return !incomingMessages.empty(); };
		inline std::string PopMessage() { if (incomingMessages.empty()) throw std::logic_error("No messages to pop"); return incomingMessages.pop(); };

	private:
		// Network send/receive stuff
		boost::asio::io_service io_service;
		udp::socket socket;
		udp::endpoint server_endpoint;
		udp::endpoint remote_endpoint;
		std::array<char, BUFFER_SIZE> recv_buffer;
		boost::thread service_thread;

		// Queues for messages
		RTypeQueue<std::string> incomingMessages;

		void start_receive();
		void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
		void run_service();

		Client(Client&); // block default copy constructor

		// Statistics
	};
} // namespace RType

#endif /* !RTYPE_CLIENT_HPP_ */
