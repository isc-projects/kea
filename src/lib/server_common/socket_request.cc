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
#include <config.h>

#include "socket_request.h"
#include <server_common/logger.h>

#include <config/ccsession.h>
#include <cc/session.h>
#include <cc/data.h>
#include <util/io/fd.h>
#include <util/io/fd_share.h>

#include <sys/un.h>
#include <sys/socket.h>
#include <cerrno>
#include <csignal>
#include <cstddef>

namespace isc {
namespace server_common {

namespace {
SocketRequestor* requestor(NULL);

// Before the boss process calls send_fd, it first sends this
// string to indicate success, followed by the file descriptor
const std::string& CREATOR_SOCKET_OK() {
    static const std::string str("1\n");
    return (str);
}

// Before the boss process calls send_fd, it sends this
// string to indicate failure. It will not send a file descriptor.
const std::string& CREATOR_SOCKET_UNAVAILABLE() {
    static const std::string str("0\n");
    return (str);
}

// The name of the ccsession command to request a socket from boss
// (the actual format of command and response are hardcoded in their
// respective methods)
const std::string& REQUEST_SOCKET_COMMAND() {
    static const std::string str("get_socket");
    return (str);
}

// The name of the ccsession command to tell boss we no longer need
// a socket (the actual format of command and response are hardcoded
// in their respective methods)
const std::string& RELEASE_SOCKET_COMMAND() {
    static const std::string str("drop_socket");
    return (str);
}

// RCode constants for the get_token command
const size_t SOCKET_ERROR_CODE = 2;
const size_t SHARE_ERROR_CODE = 3;

// A helper converter from numeric protocol ID to the corresponding string.
// used both for generating a message for the boss process and for logging.
inline const char*
protocolString(SocketRequestor::Protocol protocol) {
    switch (protocol) {
    case SocketRequestor::TCP:
        return ("TCP");
    case SocketRequestor::UDP:
        return ("UDP");
    default:
        return ("unknown protocol");
    }
}

// Creates the cc session message to request a socket.
// The actual command format is hardcoded, and should match
// the format as read in bind10_src.py.in
isc::data::ConstElementPtr
createRequestSocketMessage(SocketRequestor::Protocol protocol,
                           const std::string& address, uint16_t port,
                           SocketRequestor::ShareMode share_mode,
                           const std::string& share_name)
{
    const isc::data::ElementPtr request = isc::data::Element::createMap();
    request->set("address", isc::data::Element::create(address));
    request->set("port", isc::data::Element::create(port));
    if (protocol != SocketRequestor::TCP && protocol != SocketRequestor::UDP) {
        isc_throw(InvalidParameter, "invalid protocol: " << protocol);
    }
    request->set("protocol",
                 isc::data::Element::create(protocolString(protocol)));
    switch (share_mode) {
    case SocketRequestor::DONT_SHARE:
        request->set("share_mode", isc::data::Element::create("NO"));
        break;
    case SocketRequestor::SHARE_SAME:
        request->set("share_mode", isc::data::Element::create("SAMEAPP"));
        break;
    case SocketRequestor::SHARE_ANY:
        request->set("share_mode", isc::data::Element::create("ANY"));
        break;
    default:
        isc_throw(InvalidParameter, "invalid share mode: " << share_mode);
    }
    request->set("share_name", isc::data::Element::create(share_name));

    return (isc::config::createCommand(REQUEST_SOCKET_COMMAND(), request));
}

isc::data::ConstElementPtr
createReleaseSocketMessage(const std::string& token) {
    const isc::data::ElementPtr release = isc::data::Element::createMap();
    release->set("token", isc::data::Element::create(token));

    return (isc::config::createCommand(RELEASE_SOCKET_COMMAND(), release));
}

// Checks and parses the response receive from Boss
// If successful, token and path will be set to the values found in the
// answer.
// If the response was an error response, or does not contain the
// expected elements, a CCSessionError is raised.
void
readRequestSocketAnswer(isc::data::ConstElementPtr recv_msg,
                        std::string& token, std::string& path)
{
    int rcode;
    isc::data::ConstElementPtr answer = isc::config::parseAnswer(rcode,
                                                                 recv_msg);
    // Translate known rcodes to the corresponding exceptions
    if (rcode == SOCKET_ERROR_CODE) {
        isc_throw(SocketRequestor::SocketAllocateError, answer->str());
    }
    if (rcode == SHARE_ERROR_CODE) {
        isc_throw(SocketRequestor::ShareError, answer->str());
    }
    // The unknown exceptions
    if (rcode != 0) {
        isc_throw(isc::config::CCSessionError,
                  "Error response when requesting socket: " << answer->str());
    }

    if (!answer || !answer->contains("token") || !answer->contains("path")) {
        isc_throw(isc::config::CCSessionError,
                  "Malformed answer when requesting socket");
    }
    token = answer->get("token")->stringValue();
    path = answer->get("path")->stringValue();
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
    // TODO: Current master has socketsession code and better way
    // of handling errors without potential leaks for this. It is
    // not public there at this moment, but when this is merged
    // we should make a ticket to move this functionality to the
    // SocketSessionReceiver and use that.
    const int sock_pass_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_pass_fd == -1) {
        isc_throw(SocketRequestor::SocketError,
                  "Unable to open domain socket " << path <<
                  ": " << strerror(errno));
    }
    struct sockaddr_un sock_pass_addr;
    sock_pass_addr.sun_family = AF_UNIX;
    if (path.size() >= sizeof(sock_pass_addr.sun_path)) {
        close(sock_pass_fd);
        isc_throw(SocketRequestor::SocketError,
                  "Unable to open domain socket " << path <<
                  ": path too long");
    }
#ifdef HAVE_SA_LEN
    sock_pass_addr.sun_len = path.size();
#endif
    strcpy(sock_pass_addr.sun_path, path.c_str());
    const socklen_t len = path.size() + offsetof(struct sockaddr_un, sun_path);
    // Yes, C-style cast bad. See previous comment about SocketSessionReceiver.
    if (connect(sock_pass_fd, (const struct sockaddr*)&sock_pass_addr,
                len) == -1) {
        close(sock_pass_fd);
        isc_throw(SocketRequestor::SocketError,
                  "Unable to open domain socket " << path <<
                  ": " << strerror(errno));
    }
    return (sock_pass_fd);
}

// Reads a socket fd over the given socket (using recv_fd()).
//
// \exception SocketError if the socket cannot be read
// \return the socket fd that has been read
int
getSocketFd(const std::string& token, int sock_pass_fd) {
    // Tell the boss the socket token.
    const std::string token_data = token + "\n";
    if (!isc::util::io::write_data(sock_pass_fd, token_data.c_str(),
                                   token_data.size())) {
        isc_throw(SocketRequestor::SocketError, "Error writing socket token");
    }

    // Boss first sends some data to signal that getting the socket
    // from its cache succeeded
    char status[3];        // We need a space for trailing \0, hence 3
    memset(status, 0, 3);
    if (isc::util::io::read_data(sock_pass_fd, status, 2) < 2) {
        isc_throw(SocketRequestor::SocketError,
                  "Error reading status code while requesting socket");
    }
    // Actual status value hardcoded by boss atm.
    if (CREATOR_SOCKET_UNAVAILABLE() == status) {
        isc_throw(SocketRequestor::SocketError,
                  "CREATOR_SOCKET_UNAVAILABLE returned");
    } else if (CREATOR_SOCKET_OK() != status) {
        isc_throw(SocketRequestor::SocketError,
                  "Unknown status code returned before recv_fd '" << status <<
                  "'");
    }

    const int passed_sock_fd = isc::util::io::recv_fd(sock_pass_fd);

    // check for error values of passed_sock_fd (see fd_share.h)
    if (passed_sock_fd < 0) {
        switch (passed_sock_fd) {
        case isc::util::io::FD_SYSTEM_ERROR:
            isc_throw(SocketRequestor::SocketError,
                      "FD_SYSTEM_ERROR while requesting socket");
            break;
        case isc::util::io::FD_OTHER_ERROR:
            isc_throw(SocketRequestor::SocketError,
                      "FD_OTHER_ERROR while requesting socket");
            break;
        default:
            isc_throw(SocketRequestor::SocketError,
                      "Unknown error while requesting socket");
        }
    }
    return (passed_sock_fd);
}

// This implementation class for SocketRequestor uses
// a CC session for communication with the boss process,
// and fd_share to read out the socket(s).
// Since we only use a reference to the session, it must never
// be closed during the lifetime of this class
class SocketRequestorCCSession : public SocketRequestor {
public:
    explicit SocketRequestorCCSession(cc::AbstractSession& session) :
        session_(session)
    {
        // We need to filter SIGPIPE to prevent it from happening in
        // getSocketFd() while writing to the UNIX domain socket after the
        // remote end closed it.  See lib/util/io/socketsession for more
        // background details.
        // Note: we should eventually unify this level of details into a single
        // module.  Setting a single filter here should be considered a short
        // term workaround.
        if (std::signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
            isc_throw(Unexpected, "Failed to filter SIGPIPE: " <<
                      strerror(errno));
        }
        LOG_DEBUG(logger, DBGLVL_TRACE_BASIC, SOCKETREQUESTOR_CREATED);
    }

    ~SocketRequestorCCSession() {
        closeFdShareSockets();
        LOG_DEBUG(logger, DBGLVL_TRACE_BASIC, SOCKETREQUESTOR_DESTROYED);
    }

    virtual SocketID requestSocket(Protocol protocol,
                                   const std::string& address,
                                   uint16_t port, ShareMode share_mode,
                                   const std::string& share_name)
    {
        const isc::data::ConstElementPtr request_msg =
            createRequestSocketMessage(protocol, address, port,
                                       share_mode, share_name);

        // Send it to boss
        const int seq = session_.group_sendmsg(request_msg, "Boss");

        // Get the answer from the boss.
        // Just do a blocking read, we can't really do much anyway
        isc::data::ConstElementPtr env, recv_msg;
        if (!session_.group_recvmsg(env, recv_msg, false, seq)) {
            isc_throw(isc::config::CCSessionError,
                      "Incomplete response when requesting socket");
        }

        // Read the socket file from the answer
        std::string token, path;
        readRequestSocketAnswer(recv_msg, token, path);
        // get the domain socket over which we will receive the
        // real socket
        const int sock_pass_fd = getFdShareSocket(path);

        // and finally get the socket itself
        const int passed_sock_fd = getSocketFd(token, sock_pass_fd);
        LOG_DEBUG(logger, DBGLVL_TRACE_DETAIL, SOCKETREQUESTOR_GETSOCKET).
            arg(protocolString(protocol)).arg(address).arg(port).
            arg(passed_sock_fd).arg(token).arg(path);
        return (SocketID(passed_sock_fd, token));
    }

    virtual void releaseSocket(const std::string& token) {
        const isc::data::ConstElementPtr release_msg =
            createReleaseSocketMessage(token);

        // Send it to boss
        const int seq = session_.group_sendmsg(release_msg, "Boss");
        LOG_DEBUG(logger, DBGLVL_TRACE_DETAIL, SOCKETREQUESTOR_RELEASESOCKET).
            arg(token);

        // Get the answer from the boss.
        // Just do a blocking read, we can't really do much anyway
        isc::data::ConstElementPtr env, recv_msg;
        if (!session_.group_recvmsg(env, recv_msg, false, seq)) {
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
    }

private:
    // Returns the domain socket file descriptor
    // If we had not opened it yet, opens it now
    int
    getFdShareSocket(const std::string& path) {
        if (fd_share_sockets_.find(path) == fd_share_sockets_.end()) {
            const int new_fd = createFdShareSocket(path);
            // Technically, the (creation and) assignment of the new map entry
            // could thrown an exception and lead to FD leak.  This should be
            // cleaned up later (see comment about SocketSessionReceiver above)
            fd_share_sockets_[path] = new_fd;
            return (new_fd);
        } else {
            return (fd_share_sockets_[path]);
        }
    }

    // Closes the sockets that has been used for fd_share
    void
    closeFdShareSockets() {
        for (std::map<std::string, int>::const_iterator it =
                fd_share_sockets_.begin();
             it != fd_share_sockets_.end();
             ++it) {
            close((*it).second);
        }
    }

    cc::AbstractSession& session_;
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
initSocketRequestor(cc::AbstractSession& session) {
    if (requestor != NULL) {
        isc_throw(InvalidOperation,
                  "The socket requestor was already initialized");
    } else {
        requestor = new SocketRequestorCCSession(session);
    }
}

void
initTestSocketRequestor(SocketRequestor* new_requestor) {
    requestor = new_requestor;
}

void
cleanupSocketRequestor() {
    if (requestor != NULL) {
        delete requestor;
        requestor = NULL;
    } else {
        isc_throw(InvalidOperation, "The socket requestor is not initialized");
    }
}

}
}
