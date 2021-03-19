//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Use the cpp03 version because the cpp11 version does not compile with
// some g++ e.g. on Fedora 33.

#include <config.h>

#include <iostream>

#ifdef HAVE_GENERIC_TLS_METHOD

#include <cstdlib>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

inline std::string CA_(const std::string& filename) {
  return (std::string(TEST_CA_DIR) + "/" + filename);
}

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

class session
{
public:
  session(boost::asio::io_service& io_context,
      boost::asio::ssl::context& context)
    : socket_(io_context, context)
  {
  }

  ssl_socket::lowest_layer_type& socket()
  {
    return socket_.lowest_layer();
  }

  void start()
  {
    socket_.async_handshake(boost::asio::ssl::stream_base::server,
        boost::bind(&session::handle_handshake, this,
          boost::asio::placeholders::error));
  }

  void handle_handshake(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      std::cerr << "handshake error '" << error.message() << "'\n";
      delete this;
    }
  }

  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
      boost::asio::async_write(socket_,
          boost::asio::buffer(data_, bytes_transferred),
          boost::bind(&session::handle_write, this,
            boost::asio::placeholders::error));
    }
    else
    {
      delete this;
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

private:
  ssl_socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

class server
{
public:
  server(boost::asio::io_service& io_context, unsigned short port)
    : io_context_(io_context),
      acceptor_(io_context,
          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      context_(boost::asio::ssl::context::method::tls)
  {
    //context_.set_options(
    //    boost::asio::ssl::context::default_workarounds
    //    | boost::asio::ssl::context::no_sslv2
    //    | boost::asio::ssl::context::single_dh_use);
    //context_.set_password_callback(boost::bind(&server::get_password, this));
    context_.set_verify_mode(boost::asio::ssl::verify_peer |
                             boost::asio::ssl::verify_fail_if_no_peer_cert);
    context_.load_verify_file(CA_("kea-ca.crt"));
    context_.use_certificate_chain_file(CA_("kea-server.crt"));
    context_.use_private_key_file(CA_("kea-server.key"),
                                  boost::asio::ssl::context::pem);
    //context_.use_tmp_dh_file("dh2048.pem");

    start_accept();
  }

  void start_accept()
  {
    session* new_session = new session(io_context_, context_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(session* new_session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->start();
    }
    else
    {
      delete new_session;
    }

    start_accept();
  }

private:
  boost::asio::io_service& io_context_;
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ssl::context context_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: server <port>\n";
      return 1;
    }

    boost::asio::io_service io_context;

    using namespace std; // For atoi.
    server s(io_context, atoi(argv[1]));

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

