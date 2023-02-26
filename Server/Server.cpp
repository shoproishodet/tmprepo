#include <iostream>

#include "Server.h"


Server::Server() {
    acceptor = std::make_unique<ip::tcp::acceptor>(service, ip::tcp::endpoint(ip::tcp::v4(),8001));
    worked = true;
}

void Server::TakeNew() {
    while (worked) {
        ip::tcp::socket sock(service);
        acceptor->accept(sock);
        std::lock_guard<std::mutex> lockGuard(sockets_access);
        sockets.emplace_back(std::move(sock));
    }
}

void Server::Send() {
    srand(std::time(nullptr));

    bool canContinue = false;

    while (!canContinue) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        std::lock_guard<std::mutex> lockGuard(sockets_access);
        if (!sockets.empty())
            canContinue = true;
    }

    for (int j = 0; j < 10; ++j) {
        int count = std::rand() % 15 + 5;

        std::vector<int> vec(count);

        for (auto &i: vec) {
            i = std::rand() % 101;
            std::cout << i << " ";
        }

        std::cout << std::endl;

        std::lock_guard<std::mutex> lockGuard(sockets_access);
        for (auto &s: sockets) {
            s.write_some(buffer(vec));
        }

        boost::this_thread::sleep_for(boost::chrono::seconds(5));
    }

    worked = false;
}

void Server::Start() {
    threads.create_thread([this]{ this->TakeNew(); });
    threads.create_thread([this]{ this->Send(); });

    while (worked)
        boost::this_thread::sleep_for(boost::chrono::seconds(1));

    threads.join_all();
}
