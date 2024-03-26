#pragma once 


#include <dummy.h>

#include <boost/asio.hpp>

#include <memory>
#include <iostream>

#include <cstdlib>
#include <utility>


namespace asio = boost::asio;
using boost::asio::ip::tcp;




class Session : public std::enable_shared_from_this<Session> {
public: 
    Session(tcp::socket socket) : m_socket{std::move(socket)} {}

    void start() {
        // std::cout << "session start" << std::endl;
        m_dummy = Dummy{};
        do_read();
    }


private:

    void do_read() {
    
        auto self(shared_from_this());
        // auto self = shared_from_this();

        m_socket.async_read_some(
            asio::buffer(m_data, max_length), 
            [this, self] (boost::system::error_code err, size_t length) {
                if (!err) {
                    std::cout << "receive: " << length << " >>> " << std::string(m_data, length) << std::endl;
                    m_dummy.update_line(std::string(m_data, length));
                    do_write(length);
                }
            }
        );
    
    }

    void do_write(size_t length) {

        auto self(shared_from_this());
        asio::async_write(
            m_socket, 
            asio::buffer(m_data, length),
            [this, self] (boost::system::error_code err, size_t /*length*/) {
                if (!err) {
                    do_read();
                }
            }
        );

    }

    tcp::socket m_socket;
    enum { max_length = 1024 };
    char m_data[max_length];

    Dummy m_dummy;

};



class Server {
public:

    Server(asio::io_context &context, int port) : 
    m_acceptor{context, tcp::endpoint(tcp::v4(), port)} {
        do_accept();
    }


private:

    void do_accept() {
        m_acceptor.async_accept(
            [this] (boost::system::error_code err, tcp::socket socket) {
                if (!err) {
                    std::make_shared<Session> (std::move(socket))->start();
                }
                do_accept();
            }
        );
    }

    tcp::acceptor m_acceptor;

};



void hello() {
    std::cout << "hello\n";
}

