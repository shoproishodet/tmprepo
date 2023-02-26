#ifndef DIAGNOSTICM_SERVER_H
#define DIAGNOSTICM_SERVER_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>

#include <list>
#include <memory>

using namespace boost::asio;

class Server {
private:
    io_service service;
    std::unique_ptr<ip::tcp::acceptor> acceptor;
    std::vector<ip::tcp::socket> sockets;
    bool worked;
    boost::thread_group threads;
    std::mutex sockets_access;
public:
    Server();
    void Start();
    void TakeNew();
    void Send();
};


#endif //DIAGNOSTICM_SERVER_H
