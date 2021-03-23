.. _tls:

*****************
TLS/HTTPS support
*****************

Since version 1.9.6 Kea includes TLS support for a better security.
TLS is used on HTTP communication providing three increasing levels of
protection:

- no TLS i.e. the only option available in prior versions.

- encryption i.e. protection against passive attacks and eavesdropping,
  the server is still authenticated but the client is not.

- mutual authentication between the client and the server.

.. note::

   The mutual authentication is for the TLS entities. When TLS and
   a HTTP authentication scheme are used there is no binding between
   the two security mechanisms so no proof that the TLS client and server
   are the same as the HTTP authentication client and server allowing
   Man-in-the-Middle attacks.

.. _tls_config:

Kea Installation with TLS/HTTPS support
=======================================

TLS/HTTPS support is available with OpenSSL and Botan cryptographic backends
with some constraints including on the boost library:

- OpenSSL versions older than 1.0.2 are obsolete so should not be considered.
  The TLS support was not tested and is not supported on these versions.

- OpenSSL version 1.0.2 has extended support for OpenSSL premium customers
  so should not be considered at the exception of these premium customers.
  The TLS support was tested but is not supported on this version.

- OpenSSL versions >= 1.1.x were tested and are supported. Note enough
  recent versions include TLS 1.3 support.

- OpenSSL 3.x was not yet released and Kea does not build with it.

- Botan 1.x versions are obsolete so should not be considered.
  The TLS support was not tested and is not supported on these versions.

- Botan 2.x versions were tested and are supported. Note the TLS support
  requires the four asio header files which are included in Botan
  packages / installation only when Botan was configured with the
  ``--with-boost`` option. It is still possible to take these files
  from the corresponding Botan distribution and to install them manually
  in the Botan include directory but of course this should be a last
  resort procedure. Note that without these header files Kea can still
  build but the TLS support is disable: any attempt to use it will fail
  with a fatal error.

- very old boost versions provide a SSL support (based on OpenSSL) without
  choice of the TLS version: Kea can still used them but they are not
  recommended.

- boost versions older than 1.64 provide a SSL support with a not flexible
  choice of the TLS version: Kea enforces the use of TLS 1.2 with them.

- boost versions newer than 1.64 (included) provide a SSL support with
  a generic TLS version: the best (higher) version available on both peers
  is selected.


TLS/HTTPS configuration
=======================

The new TLS configuration parameters are:

- the ``trust-anchor`` string parameter specifies the name of a file
  or directory where the certification authority (CA) certificate of
  the other peer can be found. With OpenSSL the directory must include
  hash symbolic links. With Botan the directory is recursively
  searched for certificates.

- the ``cert-file`` string parameter specifies the name of the file
  containing the end-entity certificate.

- the ``key-file`` string parameter specifies the private key of the
  end-entity certificate. The file must not be encrypted.

The three string parameters must be either all not specified (TLS disabled)
or all specified (TLS enabled).

TLS is asymmetric: the authentication of the server by the client is
mandatory but the authentication of the client by the server is optional.
In TLS terms this means the server can require the client certificate or
not so there is a server specific TLS parameter.

- the ``cert-required`` boolean parameter allows a server to not
  require the client certificate. Its default value is true which
  means to require the client certificate and to authenticate the
  client. This flag has no meaning on the client side: the server
  always provides a certificate which is validated by the client.

Objects in files must be in the PEM format. Files can contain more
than one certificate but this was not tested and is not supported.

Botan requires CA certificates to have the standard CA certificate
attributes, verifies that end-entity certificates are version 3
certificates (as required by the TLS standard) and supports only PKCS 8
files for the private key.

.. note::

   Some cryptographic libraries (e.g. Botan and recent OpenSSL) enforces
   minimal strength (i.e. key length), e.g. at least 2048 for RSA.

A sample set of certificates and associated objects is available at
``src/lib/asiolink/testutils/ca`` in sources with a ``doc.txt`` file
explaining how they were generated using the openssl command.

TLS handshake, the phase where the cryptographic parameters are exchanged
and authentication is verified, can fail in a lot of ways. Error messages
often do not really help to find the source of the problem.
Both OpenSSL and Botan provide a command line tool with a verify command
which can be used to understand and fix it.
