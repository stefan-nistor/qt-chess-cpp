#ifndef QT_CHESS_CPP_SESSION_H
#define QT_CHESS_CPP_SESSION_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEV

#ifdef DEV
#define IP "192.168.100.47"
#else
#define IP "127.0.0.1"
#endif

using namespace std;

class Session{
private:
    int socket = -1;
public:

    Session(std::string group, std::string endpoint) {
        this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in a{};
        a.sin_family = AF_INET;
        a.sin_port = htons(35600);
        a.sin_addr.s_addr = inet_addr(IP);
        if(socket == -1)
            throw std::runtime_error("Failed to initialize socket");
        if (-1 == connect(socket, (sockaddr *) & a, sizeof(a)))
            throw std::runtime_error("Failed to connect to the server");

        writeString(group);
        writeString(endpoint);
    }

    ~Session(){
        close(socket);
    }

    auto readInt() const -> int {

        int value;
        auto readByteCount = read ( socket, & value, sizeof (int) );

        if ( readByteCount == -1 ) {
            throw runtime_error ("read from socket error");
        }

        if ( readByteCount == 0 ) {
            throw runtime_error ("read from socket - premature disconnect");
        }

        return value;
    }

    auto readString () ->  string {

        auto length = readInt();
        string value;
        value.resize (length);

        auto readByteCount = read ( socket, value.data(), length );

        if ( readByteCount == -1 ) {
            throw runtime_error ("read from socket error");
        }

        if ( readByteCount == 0 ) {
            throw runtime_error ("read from socket - premature disconnect");
        }

        return value;
    }

    auto writeInt (int value) const -> void {

        auto writtenByteCount = write ( socket, & value, sizeof (int) );

        if ( writtenByteCount == -1 ) {
            throw runtime_error ("write to socket error");
        }
    }

    auto writeString (string const & value) -> void {

        auto length = value.length();

        writeInt(length);

        auto writtenByteCount = write ( socket, value.c_str(), length );

        if ( writtenByteCount == -1 ) {
            throw runtime_error ("write to socket error");
        }
    }

};

#endif //QT_CHESS_CPP_SESSION_H
