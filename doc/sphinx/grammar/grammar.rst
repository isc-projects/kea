..
   Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.

.. _bnf-grammar:

Kea Configuration File Syntax (BNF)
===================================

Kea consists of several daemons, each with its own configuration syntax. The following sections
provide a complete syntax of all possible parameters, written as Backus-Naur Form (BNF).
See `wikipedia article on BNF <https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form>`_ for
background and explanation.

BNF Grammar for DHCPv4
----------------------

.. include:: grammar-dhcp4-parser.rst

BNF Grammar for DHCPv6
----------------------

.. include:: grammar-dhcp6-parser.rst

BNF Grammar for Control Agent
-----------------------------

.. include:: grammar-ca-parser.rst

BNF Grammar for DHCP-DDNS
-------------------------

.. include:: grammar-d2-parser.rst

BNF Grammar for Kea-netconf
---------------------------

.. include:: grammar-netconf-parser.rst
