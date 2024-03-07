
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
    if (N == 0) return 1;

    try {

        // create loggers
        static ConsoleLogger c_logger = ConsoleLogger{};
        static FileLogger f_logger1 = FileLogger{};
        static FileLogger f_logger2 = FileLogger{};

        std::vector<iLogger*> loggers = {&c_logger, &f_logger1, &f_logger2};

        static LockFreeQueue<Utils::pair_Lines_and_Name> file_queue{};
        static LockFreeQueue<Utils::pair_Lines_and_Name> console_queue{};

        std::vector<LockFreeQueue<Utils::pair_Lines_and_Name>*> queues = {&file_queue, &console_queue};

        // attach queues
        c_logger.attach_queue(&console_queue);
        f_logger1.attach_queue(&file_queue);
        f_logger2.attach_queue(&file_queue);


        std::thread c_thread = c_logger.activate();
        std::thread f_thread1 = f_logger1.activate();
        std::thread f_thread2 = f_logger2.activate();

        // library logic
        auto h = async::connect(N, loggers, queues);
        auto h2 = async::connect(N, loggers, queues);

        async::receive(h, "1", 1);
        async::receive(h2, "1\n", 2);
        async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
        async::receive(h, "b\nc\nd\n}\n89\n", 11);
        
        async::disconnect(h);
        async::disconnect(h2);

        // start threads
        c_thread.join();
        f_thread1.join();
        f_thread2.join();

    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    
    return 0;

}
