

#include <server.h> 

#include <boost/asio.hpp> 

#include <iostream> 
#include <string> 



int main() {

    try{

        hello();

        int port = 9999;

        boost::asio::io_context io_context;

        Server server{io_context, port};

        io_context.run();

    } catch(std::exception ex) {
        std::cout << "ERROR: " << ex.what() << std::endl;
    }

}

