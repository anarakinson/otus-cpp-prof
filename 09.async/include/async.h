#pragma once 


#include <bulk.h>
#include <loggers.h>

#include <iostream>
#include <string>


namespace async {

    using handle_t = void *;

    handle_t connect(std::size_t);
    void receive(handle_t, const char*, std::size_t);
    void disconnect(handle_t);

    // handlers
    class iHandler;
    class BulkHandler;

} // async
