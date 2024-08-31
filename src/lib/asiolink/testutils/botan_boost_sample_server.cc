//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <config.h>

#include <cstdlib>
#include <functional>
#include <iostream>

#include <asiolink/asio_wrapper.h>
#include <asiolink/botan_boost_wrapper.h>
#include <botan/asio_stream.h>
#include <botan/certstor_flatfile.h>
#include <botan/pkcs8.h>
#include <botan/auto_rng.h>

inline std::string CA_(const std::string& filename) {
  return (std::string(TEST_CA_DIR) + "/" + filename);
}

using boost::asio::ip::tcp;

using Server_Certificate_Store = Botan::Flatfile_Certificate_Store;

class Server_Credentials_Manager : public Botan::Credentials_Manager
{
public:
  explicit Server_Credentials_Manager(Botan::RandomNumberGenerator& rng)
    : stores_(), certs_(),
      store_(new Server_Certificate_Store(CA_("kea-ca.crt"))),
      cert_(Botan::X509_Certificate(CA_("kea-server.crt"))),
      key_(Botan::PKCS8::load_key(CA_("kea-server.key"), rng))
  {
    stores_.push_back(store_.get());
    certs_.push_back(cert_);
  }

  virtual ~Server_Credentials_Manager()
  {
  }

  std::vector<Botan::Certificate_Store*>
  trusted_certificate_authorities(const std::string&,
                                  const std::string&) override
  {
    return stores_;
  }

  std::vector<Botan::X509_Certificate>
  cert_chain(const std::vector<std::string>&,
             const std::string&,
             const std::string&) override
  {
    return certs_;
  }

  Botan::Private_Key*
  private_key_for(const Botan::X509_Certificate&,
                  const std::string&,
                  const std::string&) override
  {
    return key_.get();
  }

  std::vector<Botan::Certificate_Store*> stores_;
  std::vector<Botan::X509_Certificate> certs_;
  std::shared_ptr<Botan::Certificate_Store> store_;
  Botan::X509_Certificate cert_;
  std::unique_ptr<Botan::Private_Key> key_;
};

using Server_Session_Manager = Botan::TLS::Session_Manager_Noop;

class Server_Policy : public Botan::TLS::Default_Policy {
public:
  virtual ~Server_Policy()
  {
  }

  std::vector<std::string> allowed_signature_methods() const override
  {
    return { "RSA", "ECDSA", "IMPLICIT" };
  }

  bool require_cert_revocation_info() const override
  {
    return false;
  }
};

class session : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket, Botan::TLS::Context& ctx)
    : socket_(std::move(socket), ctx)
  {
  }

  void start()
  {
    do_handshake();
  }

private:
  void do_handshake()
  {
    auto self(shared_from_this());
    socket_.async_handshake(Botan::TLS::Connection_Side::SERVER,
        [this, self](const boost::system::error_code& error)
        {
          if (!error)
          {
            do_read();
          }
          else
          {
            std::cerr << "handshake failed with " << error.message() << "\n";
          }
        });
  }

  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_),
        [this, self](const boost::system::error_code& ec, std::size_t length)
        {
          if (!ec)
          {
            do_write(length);
          }
        });
  }

  void do_write(std::size_t length)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](const boost::system::error_code& ec,
          std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });
  }

  Botan::TLS::Stream<tcp::socket> socket_;
  char data_[1024];
};

class server
{
public:
  server(boost::asio::io_service& io_context,
         unsigned short port,
         Botan::Credentials_Manager& creds_mgr,
         Botan::RandomNumberGenerator& rng,
         Botan::TLS::Session_Manager& sess_mgr,
         Botan::TLS::Policy& policy)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
      context_(creds_mgr, rng, sess_mgr, policy)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](const boost::system::error_code& error, tcp::socket socket)
        {
          if (!error)
          {
            std::make_shared<session>(std::move(socket), context_)->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  Botan::TLS::Context context_;
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

    Botan::AutoSeeded_RNG rng;
    Server_Credentials_Manager creds_mgr(rng);
    Server_Session_Manager sess_mgr;
    Server_Policy policy;
    server s(io_context, std::atoi(argv[1]), creds_mgr, rng, sess_mgr, policy);

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
