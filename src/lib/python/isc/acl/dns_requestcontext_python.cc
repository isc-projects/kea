// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// Enable this if you use s# variants with PyArg_ParseTuple(), see
// http://docs.python.org/py3k/c-api/arg.html#strings-and-buffers
//#define PY_SSIZE_T_CLEAN

// Python.h needs to be placed at the head of the program file, see:
// http://docs.python.org/py3k/extending/extending.html#a-simple-example
#include <Python.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include <cassert>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <util/python/pycppwrapper_util.h>

#include <acl/dns.h>
#include <acl/ip_check.h>

#include "acl.h"
#include "dns_requestcontext_python.h"

using namespace std;
using boost::scoped_ptr;
using boost::lexical_cast;
using namespace isc;
using namespace isc::util::python;
using namespace isc::acl::dns;
using namespace isc::acl::python;
using namespace isc::acl::dns::python;

namespace isc {
namespace acl {
namespace dns {
namespace python {

struct s_RequestContext::Data {
    Data(const char* const remote_addr, const unsigned short remote_port) {
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;
        hints.ai_flags = AI_NUMERICHOST | AI_NUMERICSERV;
        const int error(getaddrinfo(remote_addr,
                                    lexical_cast<string>(remote_port).c_str(),
                                    &hints, &res));
        if (error != 0) {
            isc_throw(InvalidParameter, "Failed to convert [" << remote_addr
                      << "]:" << remote_port << ", " << gai_strerror(error));
        }
        assert(sizeof(remote_ss) > res->ai_addrlen);
        memcpy(&remote_ss, res->ai_addr, res->ai_addrlen);
        remote_salen = res->ai_addrlen;
        freeaddrinfo(res);

        remote_ipaddr.reset(new IPAddress(getRemoteSockaddr()));
    }

    const struct sockaddr& getRemoteSockaddr() const {
        const void* p = &remote_ss;
        return (*static_cast<const struct sockaddr*>(p));
    }

    scoped_ptr<IPAddress> remote_ipaddr;
    socklen_t remote_salen;

private:
    struct sockaddr_storage remote_ss;
};

} // namespace python
} // namespace dns
} // namespace acl
} // namespace isc


//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// RequestContext
//

// Trivial constructor.
s_RequestContext::s_RequestContext() : cppobj(NULL), data_(NULL) {
}

namespace {
// Shortcut type which would be convenient for adding class variables safely.
typedef CPPPyObjectContainer<s_RequestContext, RequestContext> RequestContextContainer;

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// These are the functions we export
// For a minimal support, we don't need them.

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef RequestContext_methods[] = {
    { NULL, NULL, 0, NULL }
};

int
RequestContext_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_RequestContext* const self = static_cast<s_RequestContext*>(po_self);

    try {
        // In this initial implementation, the constructor is simply: It
        // takes a single parameter, which should be a Python socket address
        // object.  For IPv4, it's ('address test', numeric_port); for IPv6,
        // it's ('address text', num_port, num_flowid, num_zoneid).
        // Below, we parse the argument in the most straightforward way.
        // As the constructor becomes more complicated, we should probably
        // make it more structural (for example, we should first retrieve
        // the socket address as a PyObject, and parse it recursively)

        const char* remote_addr;
        unsigned short remote_port;
        unsigned int remote_flowinfo; // IPv6 only, unused here
        unsigned int remote_zoneid; // IPv6 only, unused here

        if (PyArg_ParseTuple(args, "(sH)", &remote_addr, &remote_port) ||
            PyArg_ParseTuple(args, "(sHII)", &remote_addr, &remote_port,
                             &remote_flowinfo, &remote_zoneid))
        {
            // We need to clear the error in case the first call to PareTuple
            // fails.
            PyErr_Clear();

            auto_ptr<s_RequestContext::Data> dataptr(
                new s_RequestContext::Data(remote_addr, remote_port));
            self->cppobj = new RequestContext(*dataptr->remote_ipaddr);
            self->data_ = dataptr.release();
            return (0);
        }
    } catch (const exception& ex) {
        const string ex_what = "Failed to construct RequestContext object: " +
            string(ex.what());
        PyErr_SetString(po_ACLError, ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError,
                        "Unexpected exception in constructing RequestContext");
        return (-1);
    }

    PyErr_SetString(PyExc_TypeError,
                    "Invalid arguments to RequestContext constructor");

    return (-1);
}

void
RequestContext_destroy(PyObject* po_self) {
    s_RequestContext* const self = static_cast<s_RequestContext*>(po_self);

    delete self->cppobj;
    delete self->data_;
    Py_TYPE(self)->tp_free(self);
}

// A helper function for __str()__
string
sockaddrToText(const struct sockaddr& sa, socklen_t sa_len) {
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    if (getnameinfo(&sa, sa_len, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf),
                    NI_NUMERICHOST | NI_NUMERICSERV)) {
        // In this context this should never fail.
        isc_throw(Unexpected, "Unexpected failure in getnameinfo");
    }

    return ("[" + string(hbuf) + "]:" + string(sbuf));
}

// for the __str__() method.  This method is provided mainly for internal
// testing.
PyObject*
RequestContext_str(PyObject* po_self) {
    const s_RequestContext* const self =
        static_cast<s_RequestContext*>(po_self);

    try {
        stringstream objss;
        objss << "<" << requestcontext_type.tp_name << " object, "
              << "remote_addr="
              << sockaddrToText(self->data_->getRemoteSockaddr(),
                                self->data_->remote_salen) << ">";
        return (Py_BuildValue("s", objss.str().c_str()));
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to convert RequestContext object to text: " +
            string(ex.what());
        PyErr_SetString(PyExc_RuntimeError, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "converting RequestContext object to text");
    }
    return (NULL);
}
} // end of unnamed namespace

namespace isc {
namespace acl {
namespace dns {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_RequestContext
// Most of the functions are not actually implemented and NULL here.
PyTypeObject requestcontext_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "isc.acl.dns.RequestContext",
    sizeof(s_RequestContext),                 // tp_basicsize
    0,                                  // tp_itemsize
    RequestContext_destroy,             // tp_dealloc
    NULL,                               // tp_print
    NULL,                               // tp_getattr
    NULL,                               // tp_setattr
    NULL,                               // tp_reserved
    NULL,                               // tp_repr
    NULL,                               // tp_as_number
    NULL,                               // tp_as_sequence
    NULL,                               // tp_as_mapping
    NULL,                               // tp_hash 
    NULL,                               // tp_call
    RequestContext_str,                 // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The RequestContext class objects is...(COMPLETE THIS)",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL, // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    RequestContext_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    RequestContext_init,                // tp_init
    NULL,                               // tp_alloc
    PyType_GenericNew,                  // tp_new
    NULL,                               // tp_free
    NULL,                               // tp_is_gc
    NULL,                               // tp_bases
    NULL,                               // tp_mro
    NULL,                               // tp_cache
    NULL,                               // tp_subclasses
    NULL,                               // tp_weaklist
    NULL,                               // tp_del
    0                                   // tp_version_tag
};

// Module Initialization, all statics are initialized here
bool
initModulePart_RequestContext(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&requestcontext_type) < 0) {
        return (false);
    }
    void* p = &requestcontext_type;
    if (PyModule_AddObject(mod, "RequestContext",
                           static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&requestcontext_type);

    return (true);
}
} // namespace python
} // namespace dns
} // namespace acl
} // namespace isc
