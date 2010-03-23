#ifndef _XFROUT_CLIENT_H
#define _XFROUT_CLIENT_H

#include <boost/asio.hpp>
#include <exceptions/exceptions.h>

namespace isc {
namespace xfr {

class XfroutError: public Exception 
{
public: 
    XfroutError(const char *file, size_t line, const char *what):
        isc::Exception(file, line, what) {}
};

using boost::asio::local::stream_protocol;
class XfroutClient
{
public:
    XfroutClient(const std::string &file):
        socket_(io_service_), file_path_(file) {}

    void connect();
    void disconnect();
    int sendXfroutRequestInfo(int tcp_sock, uint8_t *msg_data, uint16_t msg_len);

private:
    void sendData(uint8_t *msg_data, uint16_t msg_len);

private:
    boost::asio::io_service io_service_;
    // The socket used to communicate with the xfrout server.
    stream_protocol::socket socket_;
    const std::string file_path_;
};

} // End for namespace xfr
} // End for namespace isc

#endif
