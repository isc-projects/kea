//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <config.h>

#include <iostream>

#ifdef HAVE_GENERIC_TLS_METHOD

#include <cstdlib>
#include <cstring>
#include <functional>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
using std::placeholders::_1;
using std::placeholders::_2;

inline std::string CA_(const std::string& filename) {
  return (std::string(TEST_CA_DIR) + "/" + filename);
}

enum { max_length = 1024 };

class client
{
public:
  client(boost::asio::io_service& io_context,
      boost::asio::ssl::context& context,
      const tcp::endpoint& endpoint)
    : socket_(io_context, context)
  {
    socket_.set_verify_mode(boost::asio::ssl::verify_peer |
                            boost::asio::ssl::verify_fail_if_no_peer_cert);
    socket_.set_verify_callback(
        std::bind(&client::verify_certificate, this, _1, _2));

    connect(endpoint);
  }

private:
  bool verify_certificate(bool preverified,
      boost::asio::ssl::verify_context& ctx)
  {
    // The verify callback can be used to check whether the certificate that is
    // being presented is valid for the peer. For example, RFC 2818 describes
    // the steps involved in doing this for HTTPS. Consult the OpenSSL
    // documentation for more details. Note that the callback is called once
    // for each certificate in the certificate chain, starting from the root
    // certificate authority.

    // In this example we will simply print the certificate's subject name.
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying " << subject_name << "\n";

    return preverified;
  }

  void connect(const tcp::endpoint& endpoint)
  {
    socket_.lowest_layer().async_connect(endpoint,
        [this](const boost::system::error_code& error)
        {
          if (!error)
          {
            handshake();
          }
          else
          {
            std::cout << "Connect failed: " << error.message() << "\n";
          }
        });
  }

  void handshake()
  {
    socket_.async_handshake(boost::asio::ssl::stream_base::client,
        [this](const boost::system::error_code& error)
        {
          if (!error)
          {
            send_request();
          }
          else
          {
            std::cout << "Handshake failed: " << error.message() << "\n";
          }
        });
  }

  void send_request()
  {
    std::cout << "Enter message: ";
    std::cin.getline(request_, max_length);
    size_t request_length = std::strlen(request_);

    boost::asio::async_write(socket_,
        boost::asio::buffer(request_, request_length),
        [this](const boost::system::error_code& error, std::size_t length)
        {
          if (!error)
          {
            receive_response(length);
          }
          else
          {
            std::cout << "Write failed: " << error.message() << "\n";
          }
        });
  }

  void receive_response(std::size_t length)
  {
    boost::asio::async_read(socket_,
        boost::asio::buffer(reply_, length),
        [this](const boost::system::error_code& error, std::size_t length)
        {
          if (!error)
          {
            std::cout << "Reply: ";
            std::cout.write(reply_, length);
            std::cout << "\n";
          }
          else
          {
            std::cout << "Read failed: " << error.message() << "\n";
          }
        });
  }

  boost::asio::ssl::stream<tcp::socket> socket_;
  char request_[max_length];
  char reply_[max_length];
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: client <addr> <port>\n";
      return 1;
    }

    boost::asio::io_service io_context;

    using namespace std; // For atoi.
    tcp::endpoint endpoint(
      boost::asio::ip::address::from_string(argv[1]), atoi(argv[2]));

    boost::asio::ssl::context ctx(boost::asio::ssl::context::method::tls);
    ctx.load_verify_file(CA_("kea-ca.crt"));
    ctx.use_certificate_chain_file(CA_("kea-client.crt"));
    ctx.use_private_key_file(CA_("kea-client.key"),
                             boost::asio::ssl::context::pem);

    client c(io_context, ctx, endpoint);

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
#else // !HAVE_GENERIC_TLS_METHOD

int main()
{
  std::cerr << "this tool requires recent boost version (>= 1.64)\n";
  return 0;
}
#endif
