#ifndef DIAGNOSTICM_CLIENT_H
#define DIAGNOSTICM_CLIENT_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/io_service.hpp>

#include <boost/thread.hpp>

#include <memory>
#include <mutex>
#include <thread>

using namespace boost::asio;

class Client {
private:
    io_service service;
    bool areConnected;

    std::unique_ptr<ip::tcp::socket> socket;
    std::unique_ptr<ip::tcp::endpoint> ep;

    std::vector<int> intList;

    std::thread read_thread;
public:
    static std::mutex io_access;

    Client(const std::string &ip, size_t port);
    void Connect();
    void Read();
    void Start();
};


#endif //DIAGNOSTICM_CLIENT_H
