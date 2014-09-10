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

#ifndef IPC_H
#define IPC_H

#include <util/buffer.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <errno.h>

namespace isc {
namespace util {

/// @brief Exception thrown when BaseIPC::open() failed.
class IPCOpenError : public Exception {
public:
    IPCOpenError(const char* file, size_t line, const char* what) :
    isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when BaseIPC::recv() failed.
class IPCRecvError : public Exception {
public:
    IPCRecvError(const char* file, size_t line, const char* what) :
    isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when BaseIPC::send() failed.
class IPCSendError : public Exception {
public:
    IPCSendError(const char* file, size_t line, const char* what) :
    isc::Exception(file, line, what) { };
};

/// @brief An Inter Process Communication(IPC) tool based on UNIX domain socket.
///
/// It is used by 2 processes for data communication. It provides methods for
/// bi-directional binary data transfer.
///
/// There should be 2 instances (a sender and a receiver) using this tool
/// at the same time. The filename for the sockets must match (i.e. 
/// the remote filename of the sender = the local filename of the receiver).
///
/// It should be used as a base class and not directly used for future classes
/// implementing inter process communication.
class BaseIPC {
public:

    /// @brief Packet reception buffer size
    ///
    /// Receive buffer size of UNIX socket
    static const uint32_t RCVBUFSIZE = 4096;

    /// @brief BaseIPC constructor.
    ///
    /// Creates BaseIPC object for UNIX socket communication using the given
    /// filenames. It doesn't create the socket immediately.
    ///
    /// @param local_filename Filename for receiving socket
    /// @param remote_filename Filename for sending socket
    BaseIPC(const std::string& local_filename, const std::string& remote_filename) :
        socketfd_(-1),
        remote_addr_len_(0),
        local_filename_(local_filename),
        remote_filename_(remote_filename)
    {
    }

    /// @brief BaseIPC destructor.
    ///
    /// It closes the socket explicitly.
    virtual ~BaseIPC() { closeIPC(); }
    
    
    /// @brief Open UNIX socket
    ///
    /// Method will throw if socket creation fails.
    ///
    /// @return A int value of the socket descriptor.
    int open() {
        //create socket
        int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
        if (fd < 0) {
            isc_throw(IPCOpenError, "Failed to create a socket");
    	}
    	socketfd_ = fd;
    	
        bindSocket();
        setRemoteFilename();
    	
    	return socketfd_;
    }

    /// @brief Close opened socket.
    void closeIPC() {
        if(socketfd_ >= 0)
            close(socketfd_);
        socketfd_ = -1;
    }

    /// @brief Send data.
    /// 
    /// @param buf The data to be sent.
    ///
    /// Method will throw if open() has not been called or sendto() failed. 
    /// open() MUST be called before calling this function.
    ///
    /// @return The number of bytes sent.
    int send(const isc::util::OutputBuffer &buf) { 
        if (remote_addr_len_ == 0) {
            isc_throw(IPCSendError, "Remote address unset");
        }
        int count = sendto(socketfd_, buf.getData(), buf.getLength(), 0,
                           (struct sockaddr*)&remote_addr_, remote_addr_len_);
        if (count < 0) {
            isc_throw(IPCSendError, "BaseIPC failed on sendto: "
                                    << strerror(errno));
        }
        return count;
    }

    /// @brief Receive data.
    ///
    /// Method will throw if socket recvfrom() failed.
    /// open() MUST be called before calling this function.
    ///
    /// @return The number of bytes received.
    isc::util::InputBuffer recv() {
        uint8_t buf[RCVBUFSIZE];
        int len = recvfrom(socketfd_, buf, RCVBUFSIZE, 0, NULL, NULL);
        if (len < 0) {
            isc_throw(IPCRecvError, "BaseIPC failed on recvfrom: "
                                    << strerror(errno));
    	} 
        isc::util::InputBuffer ibuf(buf, len);
        return ibuf;
    }

    /// @brief Get socket fd.
    /// 
    /// @return The socket fd of the unix socket.
    int getSocket() { return socketfd_; }

protected:

    /// @brief Set remote filename
    ///
    /// The remote filename is used for sending data. The filename is given
    /// in the constructor.
    void setRemoteFilename() {
        memset(&remote_addr_, 0, sizeof(struct sockaddr_un));
        remote_addr_.sun_family = AF_UNIX;
        strcpy(&remote_addr_.sun_path[1], remote_filename_.c_str());
        remote_addr_len_ = sizeof(sa_family_t) + remote_filename_.size() + 1;
    }
    
    /// @brief Bind the UNIX socket to the given filename
    ///
    /// The filename is given in the constructor.
    ///
    /// Method will throw if socket binding fails.
    void bindSocket() {
        struct sockaddr_un local_addr_;
        int local_addr_len_;
            
        //init address
        memset(&local_addr_, 0, sizeof(struct sockaddr_un));
        local_addr_.sun_family = AF_UNIX;
        strcpy(&local_addr_.sun_path[1], local_filename_.c_str());
        local_addr_len_ = sizeof(sa_family_t) + local_filename_.size() + 1;

        //bind to local_address
        if (bind(socketfd_, (struct sockaddr *)&local_addr_, local_addr_len_) < 0) {
            isc_throw(IPCOpenError, "failed to bind to local address: " + local_filename_);
    	}
    }
    
    /// UNIX socket value.
    int socketfd_;
    
    /// Remote UNIX socket address 
    struct sockaddr_un remote_addr_;
    
    /// Length of remote_addr_
    int remote_addr_len_;

    /// Filename for receiving and sending socket
    std::string local_filename_, remote_filename_;

}; // BaseIPC class

} // namespace util
} // namespace isc
#endif  // IPC_H

