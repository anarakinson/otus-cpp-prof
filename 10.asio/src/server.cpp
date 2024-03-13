#include <server.h>

#include <iostream>



int main(int argc, char** argv) {

    if (argc != 3) {
        std::cout << "Usage: bulk_server <bulk_size> <port>" << std::endl;
        return 1;
    }


    // create log directory
    std::filesystem::create_directory("./logs");

    try{

        // parse arguments
        int port = std::atoi(argv[2]);
        size_t N = atoi(argv[1]);

        // ---------------------------------
        boost::asio::io_context io_context;

        // ThreadManager thread_manager{};
        Server server{io_context, port, N};

        // thread_manager.start_threads();
        io_context.run();

    } catch(std::exception ex) {
        std::cout << "ERROR: " << ex.what() << std::endl;
    }

}