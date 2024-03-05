
#include <async.h>


// async::handle_t async::connect(std::size_t N) {    

//     // Create bulk
//     auto bulk = new Bulk{N};

//     // create loggers
//     ConsoleLogger *c_logger = new ConsoleLogger{};
//     FileLogger *f_logger = new FileLogger{};

//     // attach loggers to bulk to notify them
//     bulk->attach(c_logger);
//     bulk->attach(f_logger);

//     return bulk;

// }


// void async::receive(async::handle_t handle, const char *data, std::size_t size) {

//     char ch;
//     for (int i = 0; i < size; ++i) {
//         ch = data[i];
//         static_cast<Bulk*>(handle)->update_line(ch);

//     }

// }


// void async::disconnect(handle_t handle) {

//     static_cast<Bulk*>(handle)->finish_processing();

// }






class async::iHandler {
public:
    iHandler() = default;
    iHandler(size_t N) : m_n{N} {}
    virtual ~iHandler() = default;

    virtual void update(char) = 0;

    virtual void finish() = 0;

private:
    size_t m_n;

};



class async::BulkHandler : public async::iHandler {
public:
    BulkHandler(size_t N) {
        
        // Create bulk
        m_bulk = new Bulk{N};

        // create loggers
        static ConsoleLogger c_logger = ConsoleLogger{};
        static FileLogger f_logger1 = FileLogger{};
        static FileLogger f_logger2 = FileLogger{};

        // attach loggers to bulk to notify them
        m_bulk->attach(&c_logger);
        m_bulk->attach(&f_logger1);
        m_bulk->attach(&f_logger2);

    } 

    void update(char ch) {
        m_bulk->update_line(ch);
    }

    void finish() {
        m_bulk->finish_processing();
    }

private:
    Bulk *m_bulk;

};




async::handle_t async::connect(std::size_t N) {    

    auto handler = new BulkHandler{N};

    return handler;

}


void async::receive(async::handle_t handle, const char *data, std::size_t size) {

    char ch;
    for (int i = 0; i < size; ++i) {
        ch = data[i];
        static_cast<iHandler*>(handle)->update(ch);

    }

}


void async::disconnect(handle_t handle) {

    static_cast<iHandler*>(handle)->finish();

}


