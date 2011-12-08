# Copyright (C) 2011  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

"""\
This module provides Python bindings for the C++ classes in the
isc::acl::dns namespace.  Specifically, it defines Python interfaces of
handling access control lists (ACLs) with DNS related contexts.
The actual binding is implemented in an effectively hidden module,
isc.acl._dns; this frontend module is in terms of implementation so that
the C++ binding code doesn't have to deal with complicated operations
that could be done in a more straightforward way in native Python.

For further details of the actual module, see the documentation of the
_dns module.
"""

import pydnspp

import isc.acl._dns
from isc.acl._dns import *

class RequestACL(isc.acl._dns.RequestACL):
    """A straightforward wrapper subclass of isc.acl._dns.RequestACL.

    See the base class documentation for more implementation.
    """
    pass

class RequestLoader(isc.acl._dns.RequestLoader):
    """A straightforward wrapper subclass of isc.acl._dns.RequestLoader.

    See the base class documentation for more implementation.
    """
    pass

class RequestContext(isc.acl._dns.RequestContext):
    """A straightforward wrapper subclass of isc.acl._dns.RequestContext.

    See the base class documentation for more implementation.
    """

    def __init__(self, remote_address, tsig=None):
        """Wrapper for the RequestContext constructor.

        Internal implementation details that the users don't have to
        worry about: To avoid dealing with pydnspp bindings in the C++ code,
        this wrapper converts the TSIG record in its wire format in the form
        of byte data, and has the binding re-construct the record from it.
        """
        tsig_wire = b''
        if tsig is not None:
            if not isinstance(tsig, pydnspp.TSIGRecord):
                raise TypeError("tsig must be a TSIGRecord, not %s" %
                                tsig.__class__.__name__)
            tsig_wire = tsig.to_wire(tsig_wire)
        isc.acl._dns.RequestContext.__init__(self, remote_address, tsig_wire)

    def __str__(self):
        """Wrap __str__() to convert the module name."""
        s = isc.acl._dns.RequestContext.__str__(self)
        return s.replace('<isc.acl._dns', '<isc.acl.dns')
