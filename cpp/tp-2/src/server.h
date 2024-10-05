#include <boost/asio.hpp>

using namespace boost;

namespace http {
	using asio::ip::tcp;

	class Server {
		private:
			asio::io_context& m_io;
			tcp::acceptor m_acceptor;

			constexpr static int PORT = 5555;

		public:
			explicit Server(asio::io_context& ioContext);
			void run();
	};
}
