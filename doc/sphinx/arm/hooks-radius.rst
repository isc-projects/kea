.. _hooks-radius:

radius: RADIUS Server Support
=============================

The RADIUS hooks library allows Kea to interact with two types of RADIUS
servers: access and accounting. Although the most common DHCP and RADIUS
integration is done on the DHCP relay-agent level (DHCP clients send
DHCP packets to DHCP relays; those relays contact the RADIUS server and
depending on the response either send the packet to the DHCP server or
drop it), it does require DHCP relay hardware to support RADIUS
communication. Also, even if the relay has the necessary support, it is
often not flexible enough to send and receive additional RADIUS
attributes. As such, the alternative looks more appealing: to extend the
DHCP server to talk to RADIUS directly. That is the goal this library
intends to fulfill.

.. note::

   This library may only be loaded by the ``kea-dhcp4`` or the
   ``kea-dhcp6`` process.

The major feature of this hooks library is the ability to use RADIUS
authorization. When a DHCP packet is received, the Kea server sends an
Access-Request to the RADIUS server and waits for a response. The server
then sends back either an Access-Accept with specific client attributes,
or an Access-Reject. There are two cases supported here: first, the
Access-Accept includes a Framed-IP-Address (for DHCPv4) or
Framed-IPv6-Address (for DHCPv6), which will be interpreted by Kea as an
instruction to assign that specified IPv4 or IPv6 address. This
effectively means RADIUS can act as an address-reservation database.

The second case supported is the ability to assign clients to specific
pools based on a RADIUS response. In this case, the RADIUS server sends
back an Access-Accept with a Framed-Pool (IPv4) or Framed-IPv6-Pool
(IPv6). In both cases, Kea interprets those attributes as client
classes. With the addition of the ability to limit access to pools to
specific classes (see :ref:`classification-pools`), RADIUS can be
used to force the client to be assigned a dynamic address from a
specific pool. Furthermore, the same mechanism can be used to control
what kind of options the client will get if there are DHCP options
specified for a particular class.

.. _hooks-radius-install:

Compilation and Installation of the RADIUS Hook
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following section describes how to compile and install the software
on CentOS 7.0. Other systems may differ slightly.

.. note::

   Starting with Kea 1.7.0, ISC now provides Kea software and hooks in convenient to use
   native DEB and RPM packages. This includes the RADIUS hook and the required patched version
   of the FreeRADIUS client library. The software compilation for RADIUS is complicated. unless
   you have specific reasons to compile it yourself, you should seriously consider using
   native packages.

STEP 1: Install dependencies

Several tools are needed to build the dependencies and Kea itself. The
following commands should install them:

.. code-block:: console

   $ sudo rpm -Uvh https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
   $ sudo yum install gcc-g++ openssl-devel log4cplus-devel wget git

STEP 2: Install FreeRADIUS

The Kea RADIUS hooks library uses the FreeRADIUS client library to
conduct RADIUS communication. Unfortunately, the standard 1.1.7 release
available from the project website https://freeradius.org/sub_projects/
has several serious deficiencies; ISC engineers observed a segmentation
fault during testing. Also, the base version of the library does not
offer asynchronous transmissions, which are essential for effective
accounting implementation. Both of these issues were addressed by ISC
engineers, and the changes have been reported to the FreeRADIUS client
project. Acceptance of those changes is outside of ISC's control, so
until those are processed, it is strongly recommended to use the
FreeRADIUS client with ISC's patches. To download and compile this
version, please use the following steps:

.. code-block:: console

   $ git clone https://github.com/fxdupont/freeradius-client.git
   $ cd freeradius-client/
   $ git checkout iscdev
   $ ./configure
   $ make
   $ sudo make install

Additional parameters may be passed to the configure script, if needed.
Once installed, the FreeRADIUS client will be installed in
/usr/local. This is the default path where Kea will be looking for it.
It can be installed in a different directory; if so,
make sure to add that path to the configure script when compiling Kea.

STEP 3: Install a recent BOOST version

Kea requires a reasonably recent Boost version. Unfortunately, the
version available in CentOS 7 is too old, so a newer Boost version is
necessary. Furthermore, CentOS 7 has an old version of the g++ compiler
that does not handle the latest Boost versions. Fortunately, Boost 1.65
meets both requirements; it is both recent enough for Kea and able to be
compiled using the g++ 4.8 version in CentOS.

To download and compile Boost 1.65, please use the following commands:

.. code-block:: console

   $ wget -nd https://boostorg.jfrog.io/artifactory/main/release/1.65.1/source/boost_1_65_1.tar.gz
   $ tar -zxvf boost_1_65_1.tar.gz
   $ cd boost_1_65_1/
   $ ./bootstrap.sh
   $ ./b2 --without-python
   $ sudo ./b2 install

Note that the b2 script may optionally take extra parameters; one of
them specifies the destination path where the sources are to be
compiled.

Alternatively, some systems provide newer boost packages. For example, 
CentOS 7 provides ``boost169-devel``. If you install it with 
``yum install boost169-devel``, you will need to point Kea to it with:

.. code-block:: console

   $ ./configure --with-boost-include=/usr/include/boost169 --with-boost-lib-dir=/usr/lib64/boost169

STEP 4: Compile and install Kea

Obtain the Kea sources either by downloading them from the git
repository or extracting the tarball. Use one of those commands
to obtain the Kea sources.

Choice 1: get from github

.. code-block:: console

   $ git clone https://github.com/isc-projects/kea.git

Choice 2: get a tarball and extract it

.. parsed-literal::

   $ tar -zxvf kea-|release|.tar.gz

The next step is to extract the premium Kea package that contains the
RADIUS repository into the Kea sources. After the tarball is extracted,
the Kea sources should have a premium/ subdirectory.

.. parsed-literal::

     $ cd kea
     $ tar -zxvf ../kea-premium-radius-|release|.tar.gz

Once this is done, verify that the Kea sources look similar to this:

.. code-block:: console

   $ ls -l
   total 952
   -rw-r--r--   1 thomson  staff    6192 Apr 25 17:38 AUTHORS
   -rw-r--r--   1 thomson  staff   29227 Apr 25 17:38 COPYING
   -rw-r--r--   1 thomson  staff  360298 Apr 25 20:00 ChangeLog
   -rw-r--r--   1 thomson  staff     645 Apr 25 17:38 INSTALL
   -rw-r--r--   1 thomson  staff    5015 Apr 25 17:38 Makefile.am
   -rw-r--r--   1 thomson  staff     587 Apr 25 17:38 README
   -rw-r--r--   1 thomson  staff   62323 Apr 25 17:38 configure.ac
   drwxr-xr-x  12 thomson  staff     408 Apr 26 19:04 doc
   drwxr-xr-x   7 thomson  staff     238 Apr 25 17:38 examples
   drwxr-xr-x   5 thomson  staff     170 Apr 26 19:04 ext
   drwxr-xr-x   8 thomson  staff     272 Apr 26 19:04 m4macros
   drwxr-xr-x  20 thomson  staff     680 Apr 26 11:22 premium
   drwxr-xr-x  10 thomson  staff     340 Apr 26 19:04 src
   drwxr-xr-x  14 thomson  staff     476 Apr 26 19:04 tools

The makefiles must be regenerated using ``autoreconf``.

The next step is to configure Kea, and there are several essential steps
necessary here. Running ``autoreconf -if`` is necessary to compile the
premium package that contains RADIUS. Also, the --with-freeradius option
is necessary to tell Kea where the FreeRADIUS client sources can be
found. Also, since the non-standard Boost is used, the path to it must
be specified.

.. code-block:: console

   $ autoreconf -i
   $ ./configure --with-freeradius=/path/to/freeradius --with-boost-include=/path/to/boost --with-boost-lib-dir=/path/to/boost/state/lib

For example, assuming the FreeRADIUS client was installed in the default
directory (/usr/local) and the Boost 1.65 sources were compiled in
/home/thomson/devel/boost1_65_1, the configure path should look as
follows:

.. code-block:: console

   $ ./configure --with-freeradius=/usr/local \
         --with-boost-include=/home/thomson/devel/boost_1_65_1 \
         --with-boost-lib-dir=/home/thomson/devel/boost_1_65_1/stage/lib

After some checks, the configure script should print a report similar to
the following:

.. parsed-literal::

          Kea source configure results:
       -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

   Package:
     Name:              kea
     Version:           |release|
     Extended version:  |release| (tarball)
     OS Family:         Linux

     Hooks directory:   /usr/local/lib/kea/hooks
     Premium hooks:     yes
     Included Hooks:    forensic_log flex_id host_cmds subnet_cmds radius host_cache

   C++ Compiler:
     CXX:             g++ --std=c++11
     CXX_VERSION:     g++ (GCC) 4.8.5 20150623 (Red Hat 4.8.5-16)
     CXX_STANDARD:    201103
     DEFS:            -DHAVE_CONFIG_H
     CPPFLAGS:         -DOS_LINUX  -DBOOST_ASIO_HEADER_ONLY
     CXXFLAGS:        -g -O2
     LDFLAGS:          -lpthread
     KEA_CXXFLAGS:     -Wall -Wextra -Wnon-virtual-dtor -Wwrite-strings -Woverloaded-virtual -Wno-sign-compare -pthread -Wno-missing-field-initializers -fPIC

   Python:
     PYTHON_VERSION:  not needed (because kea-shell is disabled)

   Boost:
     BOOST_VERSION:   1.65.1
     BOOST_INCLUDES:  -I/home/thomson/devel/boost_1_65_1
     BOOST_LIBS:      -L/home/thomson/devel/boost_1_65_1/stage/lib  -lboost_system

   OpenSSL:
     CRYPTO_VERSION:  OpenSSL 1.0.2k  26 Jan 2017
     CRYPTO_CFLAGS:
     CRYPTO_INCLUDES:
     CRYPTO_LDFLAGS:
     CRYPTO_LIBS:     -lcrypto

   Botan: no

   Log4cplus:
     LOG4CPLUS_VERSION:  1.1.3
     LOG4CPLUS_INCLUDES: -I/usr/include
     LOG4CPLUS_LIBS:     -L/usr/lib -L/usr/lib64 -llog4cplus

   Flex/bison:
     FLEX:  flex
     BISON: bison -y

   MySQL:
     no

   PostgreSQL:
     no

   Cassandra CQL:
     no
   Google Test:
     no
   Google Benchmark:
     no

   FreeRADIUS client:
     FREERADIUS_INCLUDE:    -I/usr/local/include
     FREERADIUS_LIB:        -L/usr/local/lib -lfreeradius-client
     FREERADIUS_DICTIONARY: /usr/local/etc/radiusclient/dictionary

   Developer:
     Enable Debugging:       no
     Google Tests:           no
     Valgrind:               not found
     C++ Code Coverage:      no
     Logger checks:          no
     Generate Documentation: no
     Parser Generation:      no
     Kea-shell:              no
     Perfdhcp:               no

Please make sure that the compilation includes the following:

-  RADIUS listed in Included Hooks;
-  FreeRADIUS client directories printed and pointing to the right
   directories;
-  Boost version at least 1.65.1. The versions available in CentOS 7
   (1.48 and 1.53) are too old.

Once the configuration is complete, compile Kea using make. If the
system has more than one core, using the "-j N"
option is recommended to speed up the build.

.. code-block:: console

       $ make -j5
       $ sudo make install

.. _hooks-radius-config:

RADIUS Hook Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~

The RADIUS hook is a library that has to be loaded by either DHCPv4 or
DHCPv6 Kea servers. Unlike some other available hooks libraries, this one
takes many parameters. For example, this configuration could be used:

::

     "Dhcp4": {

     # Your regular DHCPv4 configuration parameters here.

     "hooks-libraries": [
     {
         # Note that RADIUS requires host-cache for proper operation,
         # so that library is loaded as well.
         "library": "/usr/local/lib/kea/hooks/libdhcp_host_cache.so"
     },
     {
         "library": "/usr/local/lib/kea/hooks/libdhc_radius.so",
         "parameters": {

             # Specify where FreeRADIUS dictionary could be located
             "dictionary": "/usr/local/etc/freeradius/dictionary",

             # Specify which address to use to communicate with RADIUS servers
             "bindaddr": "*",

             # more RADIUS parameters here
         }
     } ]

RADIUS is a complicated environment. As such, it is not feasible
to provide a default configuration that works for everyone.
However, we do have one example that showcases some of the more common
features. Please see doc/examples/kea4/hooks-radius.json in the Kea
sources.

The RADIUS hook library supports the following global configuration
flags, which correspond to FreeRADIUS client library options:

-  ``bindaddr`` (default "*") - specifies the address to be used by the
   hooks library in communication with RADIUS servers. The "*" special
   value tells the kernel to choose the address.

-  ``canonical-mac-address`` (default false) - specifies whether MAC
   addresses in attributes follow the canonical RADIUS format (lowercase
   pairs of hexadecimal digits separated by '-').

-  ``client-id-pop0`` (default false) - used with flex-id, removes the
   leading zero (or pair of zeroes in DHCPv6) type in client-id (aka
   duid in DHCPv6). Implied by client-id-printable.

-  ``client-id-printable`` (default false) - checks whether the
   client-id/duid content is printable and uses it as is instead of in
   hexadecimal. Implies client-id-pop0 and extract-duid as 0 and 255 are
   not printable.

-  ``deadtime`` (default 0) is a mechanism to try unresponsive servers
   after responsive servers. Its value specifies the number of seconds
   after which a server is considered not to have answered, so 0
   disables the mechanism. As the asynchronous communication does not
   use locks or atomics, it is recommended that you do not use this
   feature when running in this mode.

-  ``dictionary`` (default set by configure at build time) - is the
   attribute and value dictionary. Note that it is a critical parameter. You
   may find dictionary examples in the FreeRADIUS repository under the etc
   directory.

-  ``extract-duid`` (default true) - extracts the embedded duid from an
   RFC 4361-compliant DHCPv4 client-id. Implied by client-id-printable.

-  ``identifier-type4`` (default client-id) - specifies the identifier
   type to build the User-Name attribute. It should be the same as the
   host identifier, and when the flex-id hook library is used the
   replace-client-id must be set to true; client-id will be used with
   client-id-pop0.

-  ``identifier-type6`` (default duid) - specifies the identifier type to
   build the User-Name attribute. It should be the same as the host
   identifier, and when the flex-id hook library is used the
   replace-client-id must be set to true; duid will be used with
   client-id-pop0.

-  ``realm`` (default "") - is the default realm.

-  ``reselect-subnet-address`` (default false) - uses the Kea reserved
   address/RADIUS Framed-IP-Address or Framed-IPv6-Address to reselect
   subnets where the address is not in the subnet range.

-  ``reselect-subnet-pool`` (default false) - uses the Kea
   client-class/RADIUS Frame-Pool to reselect subnets where no available
   pool can be found.

-  ``retries`` (default 3) - is the number of retries before trying the
   next server. Note that it is not supported for asynchronous
   communication.

-  ``session-history`` (default "") - is the name of the file providing
   persistent storage for accounting session history.

-  ``timeout`` (default 10) - is the number of seconds during which a
   response is awaited.

When ``reselect-subnet-pool`` or ``reselect-subnet-address`` is set to
true at the reception of RADIUS Access-Accept, the selected subnet is
checked against the client-class name or the reserved address; if it
does not match, another subnet is selected among matching subnets.

Two services are supported:

-  ``access`` - the authentication service.

-  ``accounting`` - the accounting service.

Configuration of services is divided into two parts:

-  Servers that define RADIUS servers that the library is expected to
   contact. Each server may have the following items specified:

   -  ``name`` - specifies the IP address of the server (it is
      possible to use a name which will be resolved, but it is not
      recommended).

   -  ``port`` (default RADIUS authentication or accounting service) -
      specifies the UDP port of the server. Note that the
      FreeRADIUS client library by default uses ports 1812
      (authorization) and 1813 (accounting). Some server implementations
      use 1645 (authorization) and 1646 (accounting). The
      "port" parameter may be used to adjust as needed.

   -  ``secret`` - authenticates messages.

   There may be up to eight servers. Note that when no server is
   specified, the service is disabled.

-  Attributes which define additional information that the Kea server
   will send to a RADIUS server. The parameter must be identified either
   by a name or type. Its value can be specified in one of three
   possible ways: data (which defines a plain text value), raw (which
   defines the value in hex), or expr (which defines an expression,
   which will be evaluated for each incoming packet independently).

   -  ``name`` - the name of the attribute.

   -  ``type`` - the type of the attribute. Either the type or the name must be
      provided, and the attribute must be defined in the dictionary.

   -  ``data`` - the first of three ways to specify the attribute
      content. The data entry is parsed by the FreeRADIUS library, so
      values defined in the dictionary of the attribute may be used.

   -  ``raw`` - the second of three ways to specify the attribute
      content; it specifies the content in hexadecimal. Note that it
      does not work with integer-content attributes (date, integer, and
      IPv4 address); a string-content attribute (string, IPv6 address,
      and IPv6 prefix) is required.

   -  ``expr`` - the last way to specify the attribute content. It
      specifies an evaluation expression which must return a not-empty
      string when evaluated with the DHCP query packet. Currently this
      is restricted to the access service.

For example, to specify a single access server available on localhost
that uses "xyz123" as a secret, and tell Kea to send three additional
attributes (Password, Connect-Info, and Configuration-Token), the
following snippet could be used:

::

   "parameters": {

       # Other RADIUS parameters here

       "access": {

           # This starts the list of access servers
           "servers": [
           {
               # These are parameters for the first (and only) access server
               "name": "127.0.0.1",
               "port": 1812,
               "secret": "xyz123"
           }
           # Additional access servers could be specified here
           ],

           # This defines a list of additional attributes Kea will send to each
           # access server in Access-Request.
           "attributes": [
           {
               # This attribute is identified by name (must be present in the
               # dictionary) and has static value (i.e. the same value will be
               # sent to every server for every packet)
               "name": "Password",
               "data": "mysecretpassword"
           },
           {
               # It is also possible to specify an attribute using its type,
               # rather than a name. 77 is Connect-Info. The value is specified
               # using hex. Again, this is a static value. It will be sent the
               # same for every packet and to every server.
               "type": 77,
               "raw": "65666a6a71"
           },
           {
               # This example shows how an expression can be used to send dynamic
               # value. The expression (see Section 13) may take any value from
               # the incoming packet or even its metadata (e.g. the interface
               # it was received over from)
               "name": "Configuration-Token",
               "expr": "hexstring(pkt4.mac,':')"
           }
           ] # End of attributes
       }, # End of access

       # Accounting parameters.
       "accounting": {
           # This starts the list of accounting servers
           "servers": [
           {
               # These are parameters for the first (and only) accounting server
               "name": "127.0.0.1",
               "port": 1813,
               "secret": "sekret"
           }
           # Additional accounting servers could be specified here
           ]
       }

   }

Customization is sometimes required for certain attributes by devices belonging
to various vendors. This is a great way to leverage the expression evaluation
mechanism. For example, MAC addresses which you might use as a convenience
value for the User-Name attribute most likely will appear in colon-hexadecimal
notation ``de:ad:be:ef:ca:fe``, but it might need to be expressed in:

* hyphen-hexadecimal notation ``de-ad-be-ef-ca-fe``

.. code-block:: json

   {
      "parameters": {
         "access": {
            "attributes": [
               {
                  "name": "User-Name",
                  "expr": "hexstring(pkt4.mac, '-')"
               }
            ]
         }
      }
   }

* period-separated hexadecimal notation ``dead.beef.cafe``, preferred by Cisco devices

.. code-block:: json

   {
      "parameters": {
         "access": {
            "attributes": [
               {
                  "name": "User-Name",
                  "expr": "concat(concat(concat(substring(hexstring(pkt4.mac, ''), 0, 4), '.'), concat(substring(hexstring(pkt4.mac, ''), 4, 4), '.'), concat(substring(hexstring(pkt4.mac, ''), 8, 4), '.'))"
               }
            ]
         }
      }
   }


For the RADIUS hooks library to operate properly in DHCPv4,
the Host Cache hooks library must also be loaded. The reason for this
is somewhat complex. In a typical deployment, the DHCP clients send
their packets via DHCP relay which inserts certain Relay Agent
Information options, such as circuit-id or remote-id. The values of
those options are then used by the Kea DHCP server to formulate the
necessary attributes in the Access-Request message sent to the RADIUS
server. However, once the DHCP client gets its address, it then renews
by sending packets directly to the DHCP server. As a result, the relays
are not able to insert their RAI options, and the DHCP server cannot send
the Access-Request queries to the RADIUS server by using just the
information from incoming packets. Kea needs to keep the information
received during the initial Discover/Offer exchanges and use it again
later when sending accounting messages.

This mechanism is implemented based on user context in host
reservations. (See :ref:`user-context` and :ref:`user-context-hooks` for
details.) The host cache mechanism allows the information retrieved by
RADIUS to be stored and later used for sending accounting and access
queries to the RADIUS server. In other words, the host-cache mechanism
is mandatory, unless administrators do not want RADIUS communication for messages
other than Discover and the first Request from each client.
