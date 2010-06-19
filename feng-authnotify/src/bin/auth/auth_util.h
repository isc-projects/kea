#ifndef AUTH_SERVER_UTIL
#define AUTH_SERVER_UTIL


namespace isc{
    namespace dns{
        class Message;
        class Rcode;
        class OutputBuffer;
    }
}

namespace auth_util
{
    void makeErrorMessage(isc::dns::Message &message, const isc::dns::Rcode &rcode);
    void messageToWire(isc::dns::Message &messge, isc::dns::OutputBuffer &wireData);
}

#endif
