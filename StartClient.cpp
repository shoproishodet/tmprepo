#include <boost/asio.hpp>
#include "Client/Client.h"


int main() {
    Client client("127.0.0.1", 2001);
    client.Start();
}