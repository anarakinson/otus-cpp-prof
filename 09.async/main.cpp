
#include <async.h>
#include <utils.h>
#include <bulk.h>
#include <loggers.h>


#include <iostream>
#include <filesystem>
#include <thread>
#include <future>


int main(int argc, char **argv) {

    // create log directory
    std::filesystem::create_directory("./logs");

    // parse arguments
    size_t N = Utils::get_args(argc, argv);
    if (N <= 0) {
        return 1;
    }

    try {

        // library logic
        auto h = async::connect(N);
        auto h2 = async::connect(N);

        async::receive(h, "1", 1);
        async::receive(h2, "1\n", 2);
        async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
        async::receive(h, "b\nc\nd\n}\n89\n", 11);
        
        async::disconnect(h);
        async::disconnect(h2);


    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    
    return 0;

}
