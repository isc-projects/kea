// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

#include <util/buffer.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <errno.h>

namespace isc {
namespace util {

/// @brief Exception thrown when invalid file names have been specified for a
/// unix socket.
class UnixSocketInvalidName : public Exception {
public:
    UnixSocketInvalidName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when @c UnixSocket::open fails.
class UnixSocketOpenError : public Exception {
public:
    UnixSocketOpenError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when @c UnixSocket::recv fails.
class UnixSocketRecvError : public Exception {
public:
    UnixSocketRecvError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when @c UnixSocket::send fails.
class UnixSocketSendError : public Exception {
public:
    UnixSocketSendError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Unix socket.
///
/// This class provides low level functions to operate on a unix socket. Other
/// classes may use it or derive from it to provide specialized mechanisms for
/// the Inter Process Communication (IPC).
///
/// This class requires that the two file names are specified: first file
/// defines a local address that the socket is bound to, the second one
/// specifies a remote address to which the data is sent. If this class is used
/// for IPC, the remote address associated with this socket is a local address
/// of the socket used by the other process. Conversely, when the local addres
/// of this socket is a remote address for the socket used by the other process.
///
/// Constructor of this class doesn't open a socket for communication. The
/// socket is opened with the @c UnixSocket::open method. If the socket is
/// opened a second call to @c UnixSocket::open will trigger an exception.
///
/// @note This class doesn't use abstract sockets, i.e. sockets not associated
/// with the path on the disk, because abstract sockets are the Linux
/// extension and are not portable.
class UnixSocket {
public:

    /// @brief Size of the pre-allocated buffer used to receive the data.
    static const uint32_t RCVBUFSIZE = 4096;

    /// @brief Constructor
    ///
    /// Sets paths to the local and remote file names. The file names are
    /// sanity checked by the constructor:
    /// - they must not be empty
    /// - they must not be equal.
    ///
    /// @param local_filename file name that the socket is bound to.
    /// @param remote_filename file name identifying a remote socket.
    ///
    /// @throw UnixSocketInvalidName if any of the file names is empty or if
    /// file names are equal.
    UnixSocket(const std::string& local_filename,
               const std::string& remote_filename);

    /// @brief Destructor.
    ///
    /// Closes open socket and removes socket file.
    virtual ~UnixSocket();

    /// @brief Opens unix socket
    ///
    /// This method opens a unix socket and binds it to the local file.
    ///
    /// @throw UnixSocketOpenError if the socket creation, binding fails.
    /// @throw UnixSocketOpenError if socket is already open.
    void open();

    /// @brief Convenience function checking if the socket is open.
    ///
    /// @return true if the unix socket is already open, false otherwise.
    bool isOpen() const {
        return (socketfd_ >= 0);
    }

    /// @brief Close opened socket.
    void closeFd();

    /// @brief Sends data over the unix socket.
    ///
    /// @param buf Reference to a buffer holding data to be sent.
    ///
    /// @throw UnixSocketSendError if failed to send the data over the socket,
    /// e.g. socket hasn't been opened or other error occurred.
    ///
    /// @return The number of bytes sent.
    int send(const isc::util::OutputBuffer &buf);

    /// @brief Receive data over the socket.
    ///
    /// This method receives the data over the socket and stores it in the
    /// pre-allocated buffer. The pointer to this buffer may be obtained
    /// by calling @c UnixSocket::getReceiveBuffer.
    ///
    /// @return Length of the received data.
    int receive();

    /// @brief Returns a const pointer to the buffer holding received data.
    ///
    /// This method always returns a valid pointer. The pointer holds the data
    /// received during the last call to @c UnixSocket::receive.
    const uint8_t* getReceiveBuffer() const {
        return (&input_buffer_[0]);
    }

    /// @brief Get socket descriptor.
    ///
    /// @return The socket descriptor.
    int get() const {
        return (socketfd_);
    }

private:

    /// @brief Converts the file name to the @c sockaddr_un structure.
    ///
    /// @param filename Path to the socket file.
    /// @param [out] sockaddr Structure being initialized.
    /// @param [out] sockaddr_len Length of the initialized structure.
    void filenameToSockAddr(const std::string& filename,
                            struct sockaddr_un& sockaddr,
                            int& sockaddr_len);

    /// @brief Unix socket descriptor.
    int socketfd_;

    /// @brief Remote unix socket address to which this socket is connected.
    struct sockaddr_un remote_addr_;

    /// @brief Length of @c remote_addr_ structure.
    int remote_addr_len_;

    /// @brief File name for local socket.
    std::string local_filename_;

    /// @brief File name for the remote socket.
    std::string remote_filename_;

    /// @brief Buffer holding received data from the socket.
    std::vector<uint8_t> input_buffer_;

}; // UnixSocket class

} // namespace util
} // namespace isc

#endif  // UNIX_SOCKET_H

