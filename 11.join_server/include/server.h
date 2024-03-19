
#pragma once

#include <table.h>
#include <database.h>

#include <boost/asio.hpp>

#include <iostream>
#include <vector>
#include <memory>

// create or not database for testing?
#define CREATE_DUMMY_DATABASE /*false*/ true 

namespace asio = boost::asio;
using boost::asio::ip::tcp;



class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket) : m_socket{std::move(socket)} {}
    ~Session() = default;

    void start() {
        do_read();
    }

private:

    void do_read() {
        auto self(shared_from_this());

        m_socket.async_read_some(
            asio::buffer(m_data, max_length), 
            [this, self] (boost::system::error_code err, size_t length) {
                if (!err) {
                    std::cout << "receive: " << length << " >>> " << std::string(m_data, length) << std::endl;
                    std::string query = std::string(m_data, length) + '\n';
                    if (query == "exit\n" || query == "EXIT\n") { return; }

                    // GET TABLE DATA
                    std::string answer = m_db(query);

                    // write answer
                    write_data(answer);
                    
                    do_write(answer.size());
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


    void write_data(std::string &string) {
        for (size_t i = 0; i < string.size(); ++i) {
            m_data[i] = string[i];
        }
    }


    
    tcp::socket m_socket;
    enum { max_length = 2048 };
    char m_data[max_length];

#if CREATE_DUMMY_DATABASE
    DataBase m_db = create_dummy_database();
#else
    DataBase m_db;
#endif

};



class Server {
public:

    Server(asio::io_context &context, int port) : 
    m_acceptor{context, tcp::endpoint(tcp::v4(), port)} 
    {
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
