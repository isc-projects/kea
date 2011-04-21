//
// ssl/context_base.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2005-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_SSL_CONTEXT_BASE_HPP
#define ASIO_SSL_CONTEXT_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <boost/detail/workaround.hpp>
#include "asio/ssl/detail/openssl_types.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace ssl {

/// The context_base class is used as a base for the basic_context class
/// template so that we have a common place to define various enums.
class context_base
{
public:
  /// Different methods supported by a context.
  enum method
  {
    /// Generic SSL version 2.
    sslv2,

    /// SSL version 2 client.
    sslv2_client,

    /// SSL version 2 server.
    sslv2_server,

    /// Generic SSL version 3.
    sslv3,

    /// SSL version 3 client.
    sslv3_client,

    /// SSL version 3 server.
    sslv3_server,

    /// Generic TLS version 1.
    tlsv1,

    /// TLS version 1 client.
    tlsv1_client,

    /// TLS version 1 server.
    tlsv1_server,

    /// Generic SSL/TLS.
    sslv23,

    /// SSL/TLS client.
    sslv23_client,

    /// SSL/TLS server.
    sslv23_server
  };

  /// Bitmask type for SSL options.
  typedef int options;

#if defined(GENERATING_DOCUMENTATION)
  /// Implement various bug workarounds.
  static const int default_workarounds = implementation_defined;

  /// Always create a new key when using tmp_dh parameters.
  static const int single_dh_use = implementation_defined;

  /// Disable SSL v2.
  static const int no_sslv2 = implementation_defined;

  /// Disable SSL v3.
  static const int no_sslv3 = implementation_defined;

  /// Disable TLS v1.
  static const int no_tlsv1 = implementation_defined;
#else
  BOOST_STATIC_CONSTANT(int, default_workarounds = SSL_OP_ALL);
  BOOST_STATIC_CONSTANT(int, single_dh_use = SSL_OP_SINGLE_DH_USE);
  BOOST_STATIC_CONSTANT(int, no_sslv2 = SSL_OP_NO_SSLv2);
  BOOST_STATIC_CONSTANT(int, no_sslv3 = SSL_OP_NO_SSLv3);
  BOOST_STATIC_CONSTANT(int, no_tlsv1 = SSL_OP_NO_TLSv1);
#endif

  /// File format types.
  enum file_format
  {
    /// ASN.1 file.
    asn1,

    /// PEM file.
    pem
  };

  /// Bitmask type for peer verification.
  typedef int verify_mode;

#if defined(GENERATING_DOCUMENTATION)
  /// No verification.
  static const int verify_none = implementation_defined;

  /// Verify the peer.
  static const int verify_peer = implementation_defined;

  /// Fail verification if the peer has no certificate. Ignored unless
  /// verify_peer is set.
  static const int verify_fail_if_no_peer_cert = implementation_defined;

  /// Do not request client certificate on renegotiation. Ignored unless
  /// verify_peer is set.
  static const int verify_client_once = implementation_defined;
#else
  BOOST_STATIC_CONSTANT(int, verify_none = SSL_VERIFY_NONE);
  BOOST_STATIC_CONSTANT(int, verify_peer = SSL_VERIFY_PEER);
  BOOST_STATIC_CONSTANT(int,
      verify_fail_if_no_peer_cert = SSL_VERIFY_FAIL_IF_NO_PEER_CERT);
  BOOST_STATIC_CONSTANT(int, verify_client_once = SSL_VERIFY_CLIENT_ONCE);
#endif

  /// Purpose of PEM password.
  enum password_purpose
  {
    /// The password is needed for reading/decryption.
    for_reading,

    /// The password is needed for writing/encryption.
    for_writing
  };

protected:
  /// Protected destructor to prevent deletion through this type.
  ~context_base()
  {
  }

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
private:
  // Workaround to enable the empty base optimisation with Borland C++.
  char dummy_;
#endif
};

} // namespace ssl
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_SSL_CONTEXT_BASE_HPP
