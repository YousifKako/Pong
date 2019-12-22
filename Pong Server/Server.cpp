#include <iostream>

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class Server
{
private:
    const uint16_t port = 8888;
    const std::string ip = "localhost";

    std::vector<tcp::socket*> SocketList;

public:
    Server()
    {
        try
        {
            for (uint16_t i = 0; i < 2; ++i)
            {
                io_service io_service;

                /* Initialize to Accept a TCP connection on PORT */
                tcp::acceptor AcceptConnection(io_service, tcp::endpoint(tcp::v6(), this->port));

                /* Socket Creation */
                tcp::socket Socket(io_service);

                std::cout << "Waiting for Player " << i+1 << std::endl;

                /* Listen for Connections */
                AcceptConnection.accept(Socket);

                std::cout << "Connection Established: "
                    << Socket.remote_endpoint() << std::endl;

                /* Add the Connection to SocketList */
                this->SocketList.push_back(&Socket);

                std::string ret = "Hello";
                boost::asio::write(*this->SocketList.at(i), boost::asio::buffer(ret.data(), 6));

            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    ~Server()
    {

    }

    void handleData()
    {

    }
};

int main(int argc, char* argv[])
{
    Server* server = new Server();
    return EXIT_SUCCESS;
}