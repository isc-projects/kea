#include <boost/asio/ssl.hpp>

int main() {
    ::SSL* ssl = 0;
    ::X509* cert = SSL_get0_peer_certificate(ssl);
    const ::X509_NAME *name = ::X509_get_subject_name(cert);
    int loc = ::X509_NAME_get_index_by_NID(name, NID_commonName, -1);
    const ::X509_NAME_ENTRY* ne = ::X509_NAME_get_entry(name, loc);
    unsigned char* buf = 0;
    int len = ::ASN1_STRING_to_UTF8(&buf, ::X509_NAME_ENTRY_get_data(ne));
    return 0;
}
