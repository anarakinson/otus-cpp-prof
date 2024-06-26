#pragma once 


#include <bulk.h>
#include <thread_manager.h>
#include <loggers.h>
#include <lockfree_queue.h>

#include <iostream>
#include <string>


using pair_Lines_and_Name = std::pair<std::vector<std::string>, std::string>;

namespace async {

    using handle_t = void *;

    handle_t connect(std::size_t N);
    void receive(handle_t, const char*, std::size_t);
    void disconnect(handle_t);

    // handlers
    class iHandler;
    class BulkHandler;

} // async
