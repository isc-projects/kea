// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include "socket_request.h"

#include <config/ccsession.h>
#include <cc/data.h>
#include <util/io/fd.h>
#include <util/io/fd_share.h>

#include <sys/un.h>
#include <sys/socket.h>
#include <cerrno>

// XXX TODO remove
#include <iostream>

namespace isc {
namespace server_common {

namespace {
SocketRequestor* requestor(NULL);

// Before the boss process calls send_fd, it first sends this
// string to indicate success
static const std::string CREATOR_SOCKET_OK("1");

// Before the boss process calls send_fd, it first sends this
// string to indicate failure
static const std::string CREATOR_SOCKET_UNAVAILABLE("0");

// The name of the ccsession command to request a socket from boss
// (the actual format of command and response are hardcoded in their
// respective methods)
static const std::string REQUEST_SOCKET_COMMAND("get_socket");

// The name of the ccsession command to tell boss we no longer need
// a socket (the actual format of command and response are hardcoded
// in their respective methods)
static const std::string RELEASE_SOCKET_COMMAND("drop_socket");

// This implementation class for SocketRequestor uses
// a ModuleCCSession for communication with the boss process,
// and fd_share to read out the socket(s).
// Since we only use a reference to the session, it must never
// be closed during the lifetime of this class
class SocketRequestorCCSession : public SocketRequestor {
public:
    SocketRequestorCCSession(config::ModuleCCSession& session) :
        session_(session)
    {}

    ~SocketRequestorCCSession() {
        closeFdShareSockets();
    }

    virtual SocketID requestSocket(Protocol protocol,
                                   const std::string& address,
                                   uint16_t port, ShareMode share_mode,
                                   const std::string& share_name) {
        isc::data::ConstElementPtr request_msg =
            createRequestSocketMessage(protocol, address, port,
                                       share_mode, share_name);

        // Send it to boss
        int seq = session_.groupSendMsg(request_msg, "Boss");

        // Get the answer from the boss.
        // Just do a blocking read, we can't really do much anyway
        isc::data::ConstElementPtr env, recv_msg;
        if (!session_.groupRecvMsg(env, recv_msg, false, seq)) {
            isc_throw(isc::config::CCSessionError,
                      "Incomplete response when requesting socket");
        }

        // Read the socket file from the answer
        std::string token, path;
        readRequestSocketAnswer(recv_msg, token, path);
        // get the domain socket over which we will receive the
        // real socket
        int sock_pass_fd = getFdShareSocket(path);

        // and finally get the socket itself
        int passed_sock_fd = getSocketFd(sock_pass_fd);
        return (SocketID(passed_sock_fd, token));
    };

    virtual void releaseSocket(const std::string& token) {
        isc::data::ConstElementPtr release_msg =
            createReleaseSocketMessage(token);

        // Send it to boss
        int seq = session_.groupSendMsg(release_msg, "Boss");

        // Get the answer from the boss.
        // Just do a blocking read, we can't really do much anyway
        isc::data::ConstElementPtr env, recv_msg;
        if (!session_.groupRecvMsg(env, recv_msg, false, seq)) {
            isc_throw(isc::config::CCSessionError,
                      "Incomplete response when sending drop socket command");
        }

        // Answer should just be success
        int rcode;
        isc::data::ConstElementPtr error = isc::config::parseAnswer(rcode,
                                                                    recv_msg);
        if (rcode != 0) {
            isc_throw(SocketError,
                      "Error requesting release of socket: " << error->str());
        }
    };

private:
    // Creates the cc session message to request a socket.
    // The actual command format is hardcoded, and should match
    // the format as read in bind10_src.py.in
    isc::data::ConstElementPtr
    createRequestSocketMessage(Protocol protocol,
                               const std::string& address,
                               uint16_t port, ShareMode share_mode,
                               const std::string& share_name)
    {
        isc::data::ElementPtr request = isc::data::Element::createMap();
        request->set("address", isc::data::Element::create(address));
        request->set("port", isc::data::Element::create(port));
        switch (protocol) {
        case SocketRequestor::UDP:
            request->set("protocol", isc::data::Element::create("UDP"));
            break;
        case SocketRequestor::TCP:
            request->set("protocol", isc::data::Element::create("TCP"));
            break;
        }
        switch (share_mode) {
        case DONT_SHARE:
            request->set("share_mode",
                         isc::data::Element::create("NO"));
            break;
        case SHARE_SAME:
            request->set("share_mode",
                         isc::data::Element::create("SAMEAPP"));
            break;
        case SHARE_ANY:
            request->set("share_mode",
                         isc::data::Element::create("ANY"));
            break;
        }
        request->set("share_name", isc::data::Element::create(share_name));

        return (isc::config::createCommand(REQUEST_SOCKET_COMMAND, request));
    }

    isc::data::ConstElementPtr
    createReleaseSocketMessage(const std::string& token) {
        isc::data::ElementPtr release = isc::data::Element::createMap();
        release->set("token", isc::data::Element::create(token));

        return (isc::config::createCommand(RELEASE_SOCKET_COMMAND, release));
    }

    // Checks and parses the response receive from Boss
    // If successful, token and path will be set to the values found in the
    // answer.
    // If the response was an error response, or does not contain the
    // expected elements, a CCSessionError is raised.
    void readRequestSocketAnswer(isc::data::ConstElementPtr recv_msg,
                                 std::string& token,
                                 std::string& path) {
        int rcode;
        isc::data::ConstElementPtr answer = isc::config::parseAnswer(rcode,
                                                                     recv_msg);
        if (rcode != 0) {
            isc_throw(isc::config::CCSessionError,
                      "Error response when requesting socket: " <<
                      answer->str());
        }

        if (!answer ||
            !answer->contains("token") ||
            !answer->contains("path")) {
            isc_throw(isc::config::CCSessionError,
                      "Malformed answer when requesting socket");
        }
        token = answer->get("token")->stringValue();
        path = answer->get("path")->stringValue();
    }

    // Returns the domain socket file descriptor
    // If we had not opened it yet, opens it now
    int
    getFdShareSocket(const std::string& path) {
        if (fd_share_sockets_.find(path) == fd_share_sockets_.end()) {
            int new_fd = createFdShareSocket(path);
            fd_share_sockets_[path] = new_fd;
            return (new_fd);
        } else {
            return (fd_share_sockets_[path]);
        }
    }

    // Connect to the domain socket that has been received from Boss.
    // (i.e. the one that is used to pass created sockets over).
    //
    // This should only be called if the socket had not been connected to
    // already. To get the socket and reuse existing ones, use
    // getFdShareSocket()
    //
    // \param path The domain socket to connect to
    // \exception SocketError if the socket cannot be connected to
    // \return the socket file descriptor
    int
    createFdShareSocket(const std::string& path) {
        int sock_pass_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sock_pass_fd == -1) {
            isc_throw(SocketError, "Unable to open domain socket " << path <<
                                   ": " << strerror(errno));
        }
        struct sockaddr_un sock_pass_addr;
        sock_pass_addr.sun_family = AF_UNIX;
        if (path.size() > sizeof(sock_pass_addr.sun_path)) {
            isc_throw(SocketError, "Unable to open domain socket " << path <<
                                   ": path too long");
        }

        strcpy(sock_pass_addr.sun_path, path.c_str());
        size_t len = strlen(sock_pass_addr.sun_path) +
                     sizeof(sock_pass_addr.sun_family);
        if (connect(sock_pass_fd,
                    (struct sockaddr *)&sock_pass_addr,
                    len) == -1) {
            isc_throw(SocketError, "Unable to open domain socket " << path <<
                                   ": " << strerror(errno));
        }
        return (sock_pass_fd);
    }

    // Reads a socket fd over the given socket (using recv_fd()).
    //
    // \exception SocketError if the socket cannot be read
    // \return the socket fd that has been read
    int getSocketFd(int sock_pass_fd) {
        // Boss first sends some data to signal that getting the socket
        // from its cache succeeded
        char status[2];
        memset(status, 0, 2);
        if (isc::util::io::read_data(sock_pass_fd, &status, 1) < 1) {
            isc_throw(SocketError,
                      "Error reading status code while requesting socket");
        }
        // Actual status value hardcoded by boss atm.
        if (CREATOR_SOCKET_UNAVAILABLE == status) {
            isc_throw(SocketError,
                      "CREATOR_SOCKET_UNAVAILABLE returned");
        } else if (CREATOR_SOCKET_OK != status) {
            isc_throw(SocketError,
                      "Unknown status code returned before recv_fd " << status);
        }

        int passed_sock_fd = isc::util::io::recv_fd(sock_pass_fd);

        // check for error values of passed_sock_fd (see fd_share.h)
        if (passed_sock_fd <= 0) {
            switch (passed_sock_fd) {
            case isc::util::io::FD_COMM_ERROR:
                isc_throw(SocketError,
                          "FD_COMM_ERROR while requesting socket");
                break;
            case isc::util::io::FD_OTHER_ERROR:
                isc_throw(SocketError,
                          "FD_OTHER_ERROR while requesting socket");
                break;
            default:
                isc_throw(SocketError,
                          "Unknown error while requesting socket");
            }
        }
        return (passed_sock_fd);
    }

    // Closes the sockets that has been used for fd_share
    void
    closeFdShareSockets() {
        std::map<std::string, int>::iterator it;
        for (it = fd_share_sockets_.begin(); it != fd_share_sockets_.end(); ++it ) {
            close((*it).second);
        }
    }

    config::ModuleCCSession& session_;
    std::map<std::string, int> fd_share_sockets_;
};

}

SocketRequestor&
socketRequestor() {
    if (requestor != NULL) {
        return (*requestor);
    } else {
        isc_throw(InvalidOperation, "The socket requestor is not initialized");
    }
}

void
SocketRequestor::initTest(SocketRequestor* new_requestor) {
    requestor = new_requestor;
}


void
SocketRequestor::init(config::ModuleCCSession& session) {
    if (requestor != NULL) {
        isc_throw(InvalidOperation, "The socket requestor was already initialized");
    } else {
        requestor = new SocketRequestorCCSession(session);
    }
}

void
SocketRequestor::cleanup() {
    if (requestor != NULL) {
        delete requestor;
        requestor = NULL;
    } else {
        isc_throw(InvalidOperation, "The socket requestor is not initialized");
    }
}

}
}
