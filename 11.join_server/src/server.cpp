
#include <server.hpp>

#include <iostream>



int main(int argc, char **argv) {

    std::cout << "hello" << std::endl;

    if (argc != 2) {
        std::cout << "Usage: join_server <port>" << std::endl;
        return 1;
    }

    try{

        // parse arguments
        int port = std::atoi(argv[1]);

        // ---------------------------------
        boost::asio::io_context io_context;

        // ThreadManager thread_manager{};
        Server server{io_context, port};

        // thread_manager.start_threads();
        io_context.run();

    } catch(std::exception ex) {
        std::cout << "ERROR: " << ex.what() << std::endl;
    }    

}