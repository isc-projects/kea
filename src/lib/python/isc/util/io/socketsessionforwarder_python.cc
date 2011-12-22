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
#include <netdb.h>

#include <string>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <util/io/sockaddr_util.h>
#include <util/io/socketsession.h>
#include <util/python/pycppwrapper_util.h>

#include "socketsession_python.h"
#include "socketsessionforwarder_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::util::io;
using namespace isc::util::io::internal;
using namespace isc::util::io::python;
using boost::lexical_cast;

// Trivial constructor.
s_SocketSessionForwarder::s_SocketSessionForwarder() : cppobj(NULL) {
}

// Import pydoc text
#include "socketsessionforwarder_inc.cc"

// See python/isc/log/log.cc for the use of namespace
namespace clang_unnamed_namespace_workaround {
// Internal exception class thrown when address parsing fails
class AddressParseError: public isc::Exception {
public:
    AddressParseError(const char *file, size_t line, const char *what):
        isc::Exception(file, line, what) {}
};
}
using namespace clang_unnamed_namespace_workaround;

namespace {

int
SocketSessionForwarder_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_SocketSessionForwarder* self =
        static_cast<s_SocketSessionForwarder*>(po_self);
    try {
        const char* unix_file;
        if (PyArg_ParseTuple(args, "s", &unix_file)) {
            self->cppobj = new SocketSessionForwarder(unix_file);
            return (0);
        }
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to construct SocketSessionForwarder object: " +
            string(ex.what());
        PyErr_SetString(po_SocketSessionError, ex_what.c_str());
        return (-1);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (-1);
    }

    return (-1);
}

void
SocketSessionForwarder_destroy(PyObject* po_self) {
    s_SocketSessionForwarder* self =
        static_cast<s_SocketSessionForwarder*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

// Convert a Python socket address object to an addrinfo structure by
// getaddrinfo.
void
parsePySocketAddress(PyObject* obj, int type, int protocol,
                     struct sockaddr_storage* ss)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = type;
    hints.ai_protocol = protocol;
    hints.ai_flags = AI_NUMERICHOST | AI_NUMERICSERV;

    const char* addr;
    int port, flowinfo, scopeid;
    struct addrinfo *res;
    if (PyArg_ParseTuple(obj, "si", &addr, &port)) {
        // Possibly an IPv4 address.
        hints.ai_family = AF_INET;
        const int error = getaddrinfo(addr,
                                      lexical_cast<string>(port).c_str(),
                                      &hints, &res);
        if (error == 0) {
            assert(res->ai_addrlen <= sizeof(*ss));
            memcpy(ss, res->ai_addr, res->ai_addrlen);
            return;
        }
        isc_throw(AddressParseError, "Invalid or unsupported socket address: "
                  << gai_strerror(error));
    }
    PyErr_Clear();
    if (PyArg_ParseTuple(obj, "siii", &addr, &port, &flowinfo, &scopeid)) {
        // Possibly an IPv6 address.  We ignore flowinfo.
        hints.ai_family = AF_INET6;
        const int error = getaddrinfo(addr,
                                      lexical_cast<string>(port).c_str(),
                                      &hints, &res);
        if (error == 0) {
            assert(res->ai_addrlen <= sizeof(*ss));
            memcpy(ss, res->ai_addr, res->ai_addrlen);
            void* p = ss;
            static_cast<struct sockaddr_in6*>(p)->sin6_scope_id = scopeid;
            return;
        }
        isc_throw(AddressParseError, "Invalid or unsupported socket address: "
                  << gai_strerror(error));
    }
    PyErr_Clear();
    isc_throw(AddressParseError, "Invalid or unsupported socket address, must "
              "be AF_INET or AF_INET6 socket address.");
}

PyObject*
SocketSessionForwarder_connectToReceiver(PyObject* po_self, PyObject*) {
    s_SocketSessionForwarder* const self =
        static_cast<s_SocketSessionForwarder*>(po_self);

    try {
        self->cppobj->connectToReceiver();
        Py_RETURN_NONE;
    } catch (const isc::BadValue& ex) {
        PyErr_SetString(PyExc_TypeError, ex.what());
        return (NULL);
    } catch (const SocketSessionError& ex) {
        PyErr_SetString(po_SocketSessionError, ex.what());
        return (NULL);
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure in connecting to receiver: " +
            string(ex.what());
        PyErr_SetString(PyExc_SystemError, ex_what.c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (NULL);
    }
}

PyObject*
SocketSessionForwarder_push(PyObject* po_self, PyObject* args) {
    s_SocketSessionForwarder* const self =
        static_cast<s_SocketSessionForwarder*>(po_self);

    try {
        int fd, family, type, protocol;
        PyObject* po_local_end;
        PyObject* po_remote_end;
        Py_buffer py_buf;

        if (!PyArg_ParseTuple(args, "iiiiOOy*", &fd, &family, &type, &protocol,
                              &po_local_end, &po_remote_end, &py_buf)) {
            return (NULL);
        }
        struct sockaddr_storage ss_local, ss_remote;
        parsePySocketAddress(po_local_end, type, protocol, &ss_local);
        parsePySocketAddress(po_remote_end, type, protocol, &ss_remote);
        self->cppobj->push(fd, family, type, protocol,
                           *convertSockAddr(&ss_local),
                           *convertSockAddr(&ss_remote),
                           py_buf.buf, py_buf.len);
        Py_RETURN_NONE;
    } catch (const AddressParseError& ex) {
        PyErr_SetString(PyExc_TypeError, ex.what());
        return (NULL);
    } catch (const isc::BadValue& ex) {
        PyErr_SetString(PyExc_TypeError, ex.what());
        return (NULL);
    } catch (const SocketSessionError& ex) {
        PyErr_SetString(po_SocketSessionError, ex.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (NULL);
    } 
}

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef SocketSessionForwarder_methods[] = {
    { "push", SocketSessionForwarder_push, METH_VARARGS,
      SocketSessionForwarder_push_doc },
    { "connect_to_receiver", SocketSessionForwarder_connectToReceiver,
      METH_NOARGS, SocketSessionForwarder_connectToReceiver_doc },
    { NULL, NULL, 0, NULL }
};
} // end of unnamed namespace

namespace isc {
namespace util {
namespace io {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_SocketSessionForwarder
// Most of the functions are not actually implemented and NULL here.
PyTypeObject socketsessionforwarder_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "isc.util.io.SocketSessionForwarder",
    sizeof(s_SocketSessionForwarder),                 // tp_basicsize
    0,                                  // tp_itemsize
    SocketSessionForwarder_destroy,                 // tp_dealloc
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
    NULL,                               // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    SocketSessionForwarder_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    SocketSessionForwarder_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    SocketSessionForwarder_init,        // tp_init
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
initModulePart_SocketSessionForwarder(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&socketsessionforwarder_type) < 0) {
        return (false);
    }
    void* p = &socketsessionforwarder_type;
    if (PyModule_AddObject(mod, "SocketSessionForwarder",
                           static_cast<PyObject*>(p)) < 0) {
        return (false);
    }
    Py_INCREF(&socketsessionforwarder_type);

    return (true);
}
} // namespace python
} // namespace io
} // namespace util
} // namespace isc
