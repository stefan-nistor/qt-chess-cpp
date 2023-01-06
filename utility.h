#ifndef QT_CHESS_CPP_UTILITY_H
#define QT_CHESS_CPP_UTILITY_H

#include <iostream>
#include <unistd.h>

using namespace std;

auto readInt (int socket) -> int {

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

auto readString (int socket) ->  string {

    auto length = readInt(socket);
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

auto writeInt (int value, int socket) -> void {

    auto writtenByteCount = write ( socket, & value, sizeof (int) );

    if ( writtenByteCount == -1 ) {
        throw runtime_error ("write to socket error");
    }
}

auto writeString (string const & value, int socket) -> void {

    auto length = value.length() + 1;

    writeInt(length, socket);

    auto writtenByteCount = write ( socket, value.c_str(), length );

    if ( writtenByteCount == -1 ) {
        throw runtime_error ("write to socket error");
    }
}


#endif //QT_CHESS_CPP_UTILITY_H
