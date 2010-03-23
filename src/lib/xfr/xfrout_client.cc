#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include "fd_share.h"
#include "xfrout_client.h"

using boost::asio::local::stream_protocol;

namespace isc {
namespace xfr {

void
XfroutClient::connect()
{
    socket_.connect(stream_protocol::endpoint(file_path_));
}

void
XfroutClient::disconnect()
{
    socket_.close();
}

void
XfroutClient::sendData(uint8_t *msg_data, uint16_t msg_len)
{
    int count = 0;
    while(count < msg_len) {
        int size = send(socket_.native(), msg_data + count, msg_len - count, 0);
        if (size == -1) 
            isc_throw(XfroutError, "auth failed to send data to xfrout module\n");
       
       count += size;
    }

    return;
}

int 
XfroutClient::sendXfroutRequestInfo(int tcp_sock, uint8_t *msg_data, uint16_t  msg_len)
{
    if (-1 == send_fd(socket_.native(), tcp_sock))
        isc_throw(XfroutError, "Fail to send socket descriptor to xfrout module\n");

    sendData((uint8_t *)&msg_len, 2);
    sendData(msg_data, msg_len);
    
    int databuf = 0;
    int status = recv(socket_.native(), &databuf, sizeof(int), 0);
    if (status != 0)
        isc_throw(XfroutError, "xfr query doesn't been processed properly by xfrout module\n");

    return 0;
}

} // End for xfr
} // End for isc

