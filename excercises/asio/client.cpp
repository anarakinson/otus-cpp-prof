
#include <boost/asio.hpp>

#include <iostream> 

namespace asio = boost::asio;

class Notifier {
public:
    Notifier(const std::string &address, int port, asio::io_context &io_context) : 
    m_socket{io_context} {
        
        m_ep = asio::ip::tcp::endpoint(
            asio::ip::address::from_string(
                address
            ),
            port
        );
        m_socket.connect(m_ep);

        std::cout << "Connection: " << address << ":" << port << std::endl;

    }

    void notify(const std::string message) {

        // std::cout << message << std::endl;
        asio::write(m_socket, asio::buffer(message));
        size_t len = m_socket.read_some(
            asio::buffer(m_buffer)
        );

    }

private:
    asio::ip::tcp::endpoint m_ep;
    asio::ip::tcp::socket m_socket;
    std::array<char, 4096> m_buffer;

};


int main(int argc, char **argv) {

    std::locale::global(std::locale(""));

    int port = 9999;
    std::string address = "127.0.0.1";

    try {
        if (argc != 3) throw std::exception{};
        address = std::string{argv[1]};
        port = std::atoi(argv[2]);
    } catch (std::exception ex) {        
        std::cout << "Usage: client <ADDRESS> <PORT>" << std::endl;
    }

    asio::io_context io_context;
    
    try{
        
        Notifier notifier{address, port, io_context};

        std::string line;
        while (std::getline(std::cin, line)) {
                notifier.notify(line);
        }

    } catch (std::exception ex) {
        std::cout << ex.what() << std::endl;
    }

}