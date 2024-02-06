
#include <utils.h>
#include <bulk.h>
#include <logger.h>

#include <iostream>
#include <filesystem>



int main(int argc, char **argv) {

    // create log directory
    std::filesystem::create_directory("./logs");

    // parse arguments
    size_t N = get_args(argc, argv);
    if (N == 0) return 1;

    // Create bulk
    Bulk bulk{N};

    // create loggers
    ConsoleLogger c_logger;
    FileLogger f_logger;

    // attach loggers to bulk to notify them
    bulk.attach(&c_logger);
    bulk.attach(&f_logger);

    // start program loop
    bulk.loop();

    return 0;

}
