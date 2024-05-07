
#include <async.h>



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
    
        // get thread manager
        ThreadManager &singletone = ThreadManager::get_instance();

        // Create bulk
        m_bulk = std::unique_ptr<Bulk>(new Bulk{N});

        // attach loggers and queues to bulk for notifying them
        for (auto queue : singletone.queues()) {
            m_bulk->attach_queue(queue);
        }
        for (auto logger : singletone.loggers()) {
            m_bulk->attach(logger);
        }
        
    } 

    ~BulkHandler() {}

    void update(char ch) {
        m_bulk->update_line(ch);
    }

    void finish() {
        m_bulk->finish_processing();
    }


private:
    std::unique_ptr<Bulk> m_bulk;
    
};



async::handle_t async::connect(std::size_t N) {    

    auto handler = new BulkHandler{N};

    return handler;

}


void async::receive(async::handle_t handle, const char *data, std::size_t size) {
    
    char ch;
    for (size_t i = 0; i < size; ++i) {
        ch = data[i];
        static_cast<iHandler*>(handle)->update(ch);
    }

}


void async::disconnect(handle_t handle) {

    static_cast<iHandler*>(handle)->finish();
    delete static_cast<iHandler*>(handle);

}

