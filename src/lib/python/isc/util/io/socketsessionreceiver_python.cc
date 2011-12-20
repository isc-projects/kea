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

#include <util/python/pycppwrapper_util.h>

#include <util/io/socketsession.h>

#include "socketsession_python.h"
#include "socketsessionreceiver_python.h"

using namespace std;
using namespace isc::util::python;
using namespace isc::util::io;
using namespace isc::util::io::python;
using boost::lexical_cast;

// Trivial constructor.
s_SocketSessionReceiver::s_SocketSessionReceiver() : cppobj(NULL) {
}

// Import pydoc text
#include "socketsessionreceiver_inc.cc"

namespace {
// This C structure corresponds to a Python callable object for
// socket.fromfd().
// See json_dumps_obj in dns_requestloader_python.cc for background rationale
// of this trick.
PyObject* socket_fromfd_obj = NULL;

int
SocketSessionReceiver_init(PyObject* po_self, PyObject* args, PyObject*) {
    s_SocketSessionReceiver* self =
        static_cast<s_SocketSessionReceiver*>(po_self);
    try {
        // The constructor expects a Python socket object.  We'll extract
        // the underlying file descriptor using the fileno method (in the
        // duck typing manner) and pass it to the C++ constructor.
        PyObject* po_sock;
        if (PyArg_ParseTuple(args, "O", &po_sock)) {
            PyObjectContainer fd_container(PyObject_CallMethod(
                                               po_sock,
                                               const_cast<char*>("fileno"),
                                               NULL));
            PyObjectContainer fdarg_container(
                Py_BuildValue("(O)", fd_container.get()));
            int fd;
            if (PyArg_ParseTuple(fdarg_container.get(), "i", &fd)) {
                self->cppobj = new SocketSessionReceiver(fd);
                return (0);
            }
            PyErr_SetString(PyExc_TypeError, "Given object's fileno() doesn't "
                            "return an integer, probably not a valid socket "
                            "object");
        }
    } catch (const PyCPPWrapperException& ex) {
        // This could happen due to memory allocation failure, but it's more
        // likely that the object doesn't have the "fileno()" method or it
        // returns an unexpected type of value.  So we adjust the error
        // message accordingly.
        PyErr_SetString(PyExc_TypeError, "Failed to parse parameter, "
                        "probably not a valid socket object");
    } catch (const exception& ex) {
        const string ex_what =
            "Failed to construct SocketSessionReceiver object: " +
            string(ex.what());
        PyErr_SetString(po_SocketSessionError, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
    }

    return (-1);
}

PyObject*
createPySocketAddress(const struct sockaddr& sa) {
    socklen_t salen;
    if (sa.sa_family == AF_INET) {
        salen = sizeof(struct sockaddr_in);
    } else if (sa.sa_family == AF_INET6) {
        salen = sizeof(struct sockaddr_in6);
    } else {
        isc_throw(SocketSessionError, "Unsupported socket address family: "
                  << static_cast<int>(sa.sa_family));
    }

    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    const int error = getnameinfo(&sa, salen, hbuf, sizeof(hbuf), sbuf,
                                  sizeof(sbuf),
                                  NI_NUMERICHOST | NI_NUMERICSERV);
    if (error != 0) {
        isc_throw(SocketSessionError, "Unrecognized socket address format: "
                  << gai_strerror(error));
    }
    if (sa.sa_family == AF_INET) {
        return (Py_BuildValue("(si)", hbuf, lexical_cast<int>(sbuf)));
    }
    // We know it's AF_INET6 at this point.  We need some special trick for
    // non-0 scope (zone) ID: getnameinfo() may convert the address to a
    // textual representation using the extension described in RFC 4007,
    // in which case it contains a delimiter character '%'.  We need to remove
    // it before constructing the tuple.  The scope (zone) ID is preserved
    // in the corresponding field of the tuple.
    const void* p = &sa;
    const struct sockaddr_in6* sin6 =
        static_cast<const struct sockaddr_in6*>(p);
    char* cp = strchr(hbuf, '%');
    if (cp != NULL) {
        *cp = '\0';
    }
    return (Py_BuildValue("(siii)", hbuf, lexical_cast<int>(sbuf), 0,
                          sin6->sin6_scope_id));
}

void
SocketSessionReceiver_destroy(PyObject* po_self) {
    s_SocketSessionReceiver* self =
        static_cast<s_SocketSessionReceiver*>(po_self);
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

// A helper struct to automatically close a socket in an RAII manner.
struct ScopedSocket : boost::noncopyable {
    ScopedSocket(int fd) : fd_(fd) {}
    ~ScopedSocket() {
        close(fd_);
    }
    const int fd_;
};

PyObject*
SocketSessionReceiver_pop(PyObject* po_self, PyObject*) {
    s_SocketSessionReceiver* const self =
        static_cast<s_SocketSessionReceiver*>(po_self);

    try {
        // retrieve the session, and the convert it to a corresponding
        // Python tuple.
        const SocketSession session = self->cppobj->pop();

        // We need to immediately store the socket file descriptor in a
        // ScopedSocket object.  socket.fromfd() will dup() the FD, so we need
        // to close our copy even if an exception is thrown.
        ScopedSocket sock(session.getSocket());

        // Build Python socket object
        PyObjectContainer c_args(Py_BuildValue("(iiii)", sock.fd_,
                                               session.getFamily(),
                                               session.getType(),
                                               session.getProtocol()));
        PyObjectContainer c_sock(PyObject_CallObject(socket_fromfd_obj,
                                                     c_args.get()));
        // Convert the local and remote sockaddr to Python socket address objs
        PyObjectContainer c_local(createPySocketAddress(
                                      session.getLocalEndpoint()));
        PyObjectContainer c_remote(createPySocketAddress(
                                       session.getRemoteEndpoint()));
        // Convert the session data to Python byte object.
        PyObjectContainer c_data(Py_BuildValue("y#", session.getData(),
                                               session.getDataLength()));

        // Build a tuple from them and return it.
        return (Py_BuildValue("(OOOO)", c_sock.get(), c_local.get(),
                              c_remote.get(), c_data.get()));
    } catch (const SocketSessionError& ex) {
        PyErr_SetString(po_SocketSessionError, ex.what());
        return (NULL);
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure in receiving a socket session: " +
            string(ex.what());
        PyErr_SetString(PyExc_SystemError, ex_what.c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected C++ exception");
        return (NULL);
    }
}

// These are the functions we export

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef SocketSessionReceiver_methods[] = {
    { "pop", SocketSessionReceiver_pop, METH_NOARGS,
      SocketSessionReceiver_pop_doc },
    { NULL, NULL, 0, NULL }
};
} // end of unnamed namespace

namespace isc {
namespace util {
namespace io {
namespace python {
// This defines the complete type for reflection in python and
// parsing of PyObject* to s_SocketSessionReceiver
// Most of the functions are not actually implemented and NULL here.
PyTypeObject socketsessionreceiver_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "isc.util.io.SocketSessionReceiver",
    sizeof(s_SocketSessionReceiver),                 // tp_basicsize
    0,                                  // tp_itemsize
    SocketSessionReceiver_destroy,                 // tp_dealloc
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
    SocketSessionReceiver_doc,
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    SocketSessionReceiver_methods,                   // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    SocketSessionReceiver_init,                    // tp_init
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
initModulePart_SocketSessionReceiver(PyObject* mod) {
    // We initialize the static description object with PyType_Ready(),
    // then add it to the module. This is not just a check! (leaving
    // this out results in segmentation faults)
    if (PyType_Ready(&socketsessionreceiver_type) < 0) {
        return (false);
    }
    void* p = &socketsessionreceiver_type;
    if (PyModule_AddObject(mod, "SocketSessionReceiver",
                           static_cast<PyObject*>(p)) < 0) {
        return (false);
    }

    PyObject* socket_module = PyImport_AddModule("socket");
    if (socket_module != NULL) {
        PyObject* socket_dict = PyModule_GetDict(socket_module);
        if (socket_dict != NULL) {
            socket_fromfd_obj = PyDict_GetItemString(socket_dict, "fromfd");
        }
    }
    if (socket_fromfd_obj != NULL) {
        Py_INCREF(socket_fromfd_obj);
    } else {
        PyErr_SetString(PyExc_RuntimeError,
                        "isc.util.io.SocketSessionReceiver needs "
                        "socket.fromfd(), but it's missing");
        return (false);
    }

    Py_INCREF(&socketsessionreceiver_type);

    return (true);
}

} // namespace python
} // namespace io
} // namespace util
} // namespace isc
