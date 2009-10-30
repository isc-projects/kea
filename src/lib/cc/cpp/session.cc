
#include "data.h"
#include "session.h"

#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;
using namespace ISC::CC;
using namespace ISC::Data;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

Session::Session()
{
    sock = -1;
}

void
Session::disconnect()
{
    close(sock);
    sock = -1;
}

void
Session::establish()
{
    int ret;
    struct sockaddr_in sin;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < -1)
        throw SessionError("socket() failed");

    sin.sin_len = sizeof(struct sockaddr_in);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9912);
    sin.sin_addr.s_addr = INADDR_ANY;
    ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin));
    if (ret < 0)
        throw SessionError("connect() failed");

    //
    // send a request for our local name, and wait for a response
    //
    std::string get_lname_str = "{ \"type\": \"getlname\" }";
    std::stringstream get_lname_stream;
    get_lname_stream.str(get_lname_str);
    ElementPtr get_lname_msg = Element::create_from_string(get_lname_stream);
    sendmsg(get_lname_msg);

    ElementPtr msg;
    recvmsg(msg, false);

    lname = msg->get("lname")->string_value();
    cout << "My local name is:  " << lname << endl;
}

//
// Convert to wire format and send this on the TCP stream with its length prefix
//
void
Session::sendmsg(ElementPtr& msg)
{
    std::string wire = msg->to_wire();
    unsigned int length = wire.length();
    unsigned int length_net = htonl(length);
    unsigned int ret;

    ret = write(sock, &length_net, 4);
    if (ret != 4)
        throw SessionError("Short write");

    ret = write(sock, wire.c_str(), length);
    if (ret != length)
        throw SessionError("Short write");
}

bool
Session::recvmsg(ElementPtr& msg, bool nonblock)
{
    unsigned int length_net;
    unsigned int ret;

    ret = read(sock, &length_net, 4);
    if (ret != 4)
        throw SessionError("Short read");

    unsigned int length = ntohl(length_net);
    char *buffer = new char[length];
    ret = read(sock, buffer, length);
    if (ret != length)
        throw SessionError("Short read");

    std::string wire = std::string(buffer, length);
    delete [] buffer;

    std::stringstream wire_stream;
    wire_stream <<wire;

    msg = Element::from_wire(wire_stream, length);

    return (true);
    // XXXMLG handle non-block here, and return false for short reads
}

void
Session::subscribe(std::string group, std::string instance, std::string subtype)
{
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("subscribe"));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));
    env->set("subtype", Element::create(subtype));

    sendmsg(env);
}

void
Session::unsubscribe(std::string group, std::string instance)
{
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("unsubscribe"));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));

    sendmsg(env);
}

unsigned int
Session::group_sendmsg(ElementPtr& msg, std::string group, std::string instance, std::string to)
{
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("send"));
    env->set("from", Element::create(lname));
    env->set("to", Element::create(to));
    env->set("group", Element::create(group));
    env->set("instance", Element::create(instance));
    env->set("seq", Element::create(sequence));
    env->set("msg", Element::create(msg->to_wire()));

    sendmsg(env);

    return (sequence++);
}

bool
Session::group_recvmsg(ElementPtr& envelope, ElementPtr& msg, bool nonblock)
{
    bool got_message = recvmsg(envelope, nonblock);
    if (!got_message) {
        return false;
    }

    msg = Element::from_wire(envelope->get("msg")->string_value());
    envelope->remove("msg");

    return (true);
}

unsigned int
Session::reply(ElementPtr& envelope, ElementPtr& newmsg)
{
    ElementPtr env = Element::create(std::map<std::string, ElementPtr>());

    env->set("type", Element::create("send"));
    env->set("from", Element::create(lname));
    env->set("to", Element::create(envelope->get("from")->string_value()));
    env->set("group", Element::create(envelope->get("group")->string_value()));
    env->set("instance", Element::create(envelope->get("instance")->string_value()));
    env->set("seq", Element::create(sequence));
    env->set("msg", Element::create(newmsg->to_wire()));
    env->set("reply", Element::create(envelope->get("seq")->string_value()));

    sendmsg(env);

    return (sequence++);
}
