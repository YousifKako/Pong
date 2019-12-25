#include <iostream>
#include <thread>
#include <memory>
#include <mutex>

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio/read.hpp>

#include <SDL.h>

using namespace boost::asio;
using namespace boost::asio::ip;

class Server
{
private:
public:
    const uint32_t port = 99899;
    const std::string ip = "localhost";

    Server()
    {
        try
        {
            io_service io_service;

            /* Initialize to Accept a TCP connection on PORT */
            tcp::acceptor AcceptConnection(io_service, tcp::endpoint(tcp::v6(), this->port));

            /* Socket Creation */
            tcp::socket Socket(io_service);
            std::shared_ptr<tcp::socket> s1 = std::make_shared<tcp::socket>(tcp::socket(io_service));
            std::shared_ptr<tcp::socket> s2 = std::make_shared<tcp::socket>(tcp::socket(io_service));

            std::cout << "Waiting for Player 1" << std::endl;
            AcceptConnection.accept(*s1);

            std::cout << "Waiting for Player 2" << std::endl;
            AcceptConnection.accept(*s2);

            std::thread(handleClient, s1, s2).detach();
            handleClient(s2, s1);
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    static void handleClient(std::shared_ptr<tcp::socket> sock,
        std::shared_ptr<tcp::socket> sock2
    )
    {
        try
        {
            //std::cout << "Connection Established: "
            //    << sock->remote_endpoint() << std::endl;

            char a[2];
            while (1)
            {
                SDL_Delay(5);
            
                boost::asio::read(*sock, boost::asio::buffer(a, 2));

                boost::asio::write(*sock2, boost::asio::buffer(a, 2));
            }
        }
        catch (std::exception & e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
};











#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class tcp_connection
    : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context)
    {
        return pointer(new tcp_connection(io_context));
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        boost::asio::async_write(socket_, boost::asio::buffer(message_),
            boost::bind(&tcp_connection::handle_write, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

private:
    tcp_connection(boost::asio::io_context& io_context)
        : socket_(io_context)
    {
    }

    void handle_write(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/)
    {
    }

    tcp::socket socket_;
    std::string message_;
};

class tcp_server
{
public:
    tcp_server(boost::asio::io_context& io_context)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), 99899))
    {
        start_accept();
    }

private:
    void start_accept()
    {
        tcp_connection::pointer new_connection =
            tcp_connection::create(acceptor_.get_executor().context());

        acceptor_.async_accept(new_connection->socket(),
            boost::bind(&tcp_server::handle_accept, this, new_connection,
                boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection,
        const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->start();
        }

        start_accept();
    }

    tcp::acceptor acceptor_;
};

//int main()
//{
//    try
//    {
//        boost::asio::io_context io_context;
//        tcp_server server(io_context);
//        io_context.run();
//    }
//    catch (std::exception & e)
//    {
//        std::cerr << e.what() << std::endl;
//    }
//
//    return 0;
//}






int main(int argc, char* argv[])
{
    Server* server = new Server();
    return EXIT_SUCCESS;
}