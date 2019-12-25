#include <iostream>

#include <SDL.h>

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;
using boost::asio::ip::tcp;

static class Client
{
private:
    const uint32_t port = 99899;
    const std::string ip = "169.254.192.43";

public:
    Client(uint16_t* player1_y, uint16_t* player2_y)
    {
        std::thread(init, player1_y, player2_y).detach();
    }

    ~Client()
    {

    }

    static void init(uint16_t* player1_y, uint16_t* player2_y)
    {
        try
        {
            io_service io_service;

            /* Socket Creation */
            tcp::socket Socket(io_service);

            /* Connection */
            Socket.connect(tcp::endpoint(ip::address::from_string("169.254.192.43"), 99899));

            std::thread(recvYCoords, &Socket, player2_y).detach();
            sendYCoords(&Socket, player1_y);
        }
        catch (std::exception & e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    static void sendYCoords(tcp::socket* Socket, uint16_t* y)
    {
        try
        {
            int temp = 0;
            char temp2[2];
            while (1)
            {
                SDL_Delay(5);
                temp = *y;
                memcpy(temp2, (char*)&temp, 2);
                
                boost::asio::write(*Socket, boost::asio::buffer(temp2, 2));
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    static void recvYCoords(tcp::socket* sock, uint16_t* y)
    {
        try
        {
            short k = 0;
            char a[2];
            while (1)
            {
                //SDL_Delay(2);
                boost::asio::read(*sock, boost::asio::buffer(a, 2));
                
                memcpy(&k, a, 2);

                *y = k;
            }
        }
        catch (std::exception & e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
};