#include <iostream>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

#include "server.h"
#include "exception.h"
#include "request.h"
#include "response.h"
#include "router.h"
#include "routes/helloworld.h"
#include "routes/hiyou.h"
#include "routes/sum.h"
#include "routes/meme.h"

using namespace boost;

namespace http {

	Server::Server(asio::io_context& ioContext)
		: m_io{ioContext},
			m_acceptor{ioContext, tcp::endpoint{tcp::v4(), PORT}} {
	}

	void Server::run() {
		router::Router router;
		router.addRoute(std::make_unique<router::route::helloWorld::HelloWorld>());
		router.addRoute(std::make_unique<router::route::meme::Meme>());
		router.addRoute(std::make_unique<router::route::hiyou::Hiyou>());
		router.addRoute(std::make_unique<router::route::sum::Sum>());


		std::cout << "Router initiated with " << router.nbRoutes() << " routes" << std::endl;

		while (true) { // infinite loop, as long as clients connect or something crashes

			std::cout << "Server listening !" << std::endl;

			tcp::iostream stream;
			this->m_acceptor.accept(stream.socket());

			std::cout << "Client connected !" << std::endl;

			while (true) { // infinite loop, as long as the client is connected

				const response::Response* res;

				try {
					request::Request req;
					stream >> req;

					if (!req) break;

					std::cout << "Request parsed : " << std::endl;
					std::cout << req;

					res = &router.serveRequest(req);

				} catch(const exception::BadRequest& e) {
					res = new response::Response(400, e.what());
				} catch(const exception::NotFound& e) {
					res = new response::Response(404, e.what());
				} catch(const std::exception& e) {
					std::cerr << e.what() << '\n';
					res = new response::Response(500, e.what());
				}

				stream << *res;
				std::cout << "> " << res->getStatus() << std::endl;

				break;
			}

			stream.close();
			std::cout << "Le client est déconnecté" << std::endl;
		}
	}


}

int main() {
	asio::io_context ioContext;
	http::Server server{ioContext};

	server.run();
}
