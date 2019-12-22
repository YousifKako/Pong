#include <iostream>

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class Client
{
private:
    const uint16_t port = 8888;
    const std::string ip = "localhost";

public:
    Client()
    {
        try
        {
            io_service io_service;

            /* Socket Creation */
            tcp::socket Socket(io_service);

            /* Connection */
            Socket.connect(tcp::endpoint(ip::address::from_string(this->ip), this->port));

            std::string ret;
            ret.resize(6);
            boost::asio::read(Socket, boost::asio::buffer(&ret[0], 6));
            std::cout << ret << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    ~Client()
    {

    }

    void handleData()
    {

    }
};