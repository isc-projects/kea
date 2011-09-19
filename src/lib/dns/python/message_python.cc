// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <exceptions/exceptions.h>
#include <dns/message.h>
#include <dns/rcode.h>
#include <dns/tsig.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>

#include "name_python.h"
#include "question_python.h"
#include "edns_python.h"
#include "rcode_python.h"
#include "opcode_python.h"
#include "rrset_python.h"
#include "message_python.h"
#include "messagerenderer_python.h"
#include "tsig_python.h"
#include "tsigrecord_python.h"
#include "pydnspp_common.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::python;
using namespace isc::util;

namespace {
class s_Message : public PyObject {
public:
    isc::dns::Message* cppobj;
};

int Message_init(s_Message* self, PyObject* args);
void Message_destroy(s_Message* self);

PyObject* Message_getHeaderFlag(s_Message* self, PyObject* args);
PyObject* Message_setHeaderFlag(s_Message* self, PyObject* args);
PyObject* Message_getQid(s_Message* self);
PyObject* Message_setQid(s_Message* self, PyObject* args);
PyObject* Message_getRcode(s_Message* self);
PyObject* Message_setRcode(s_Message* self, PyObject* args);
PyObject* Message_getOpcode(s_Message* self);
PyObject* Message_setOpcode(s_Message* self, PyObject* args);
PyObject* Message_getEDNS(s_Message* self);
PyObject* Message_setEDNS(s_Message* self, PyObject* args);
PyObject* Message_getTSIGRecord(s_Message* self);
PyObject* Message_getRRCount(s_Message* self, PyObject* args);
// use direct iterators for these? (or simply lists for now?)
PyObject* Message_getQuestion(s_Message* self);
PyObject* Message_getSection(s_Message* self, PyObject* args);
//static PyObject* Message_beginQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_endQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_beginSection(s_Message* self, PyObject* args);
//static PyObject* Message_endSection(s_Message* self, PyObject* args);

PyObject* Message_addQuestion(s_Message* self, PyObject* args);
PyObject* Message_addRRset(s_Message* self, PyObject* args);
PyObject* Message_clear(s_Message* self, PyObject* args);
PyObject* Message_makeResponse(s_Message* self);
PyObject* Message_toText(s_Message* self);
PyObject* Message_str(PyObject* self);
PyObject* Message_toWire(s_Message* self, PyObject* args);
PyObject* Message_fromWire(s_Message* self, PyObject* args);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
PyMethodDef Message_methods[] = {
    { "get_header_flag", reinterpret_cast<PyCFunction>(Message_getHeaderFlag),
      METH_VARARGS,
      "Return whether the specified header flag bit is set in the "
      "header section. Takes a MessageFlag object as the only argument." },
    { "set_header_flag",
      reinterpret_cast<PyCFunction>(Message_setHeaderFlag), METH_VARARGS,
      "Sets the specified header flag bit to 1. The message must be in "
      "RENDER mode. If not, an InvalidMessageOperation is raised. "
      "Takes a MessageFlag object as the only argument." },
    { "get_qid", reinterpret_cast<PyCFunction>(Message_getQid), METH_NOARGS,
      "Returns the query id" },
    { "set_qid", reinterpret_cast<PyCFunction>(Message_setQid), METH_VARARGS,
      "Sets the query id. If the message is not in RENDER mode, an "
      "InvalidMessageOperation is raised.\n"
      "The argument must be an integer" },
    { "get_rcode", reinterpret_cast<PyCFunction>(Message_getRcode), METH_NOARGS,
      "Returns the message Response code (an Rcode object)" },
    { "set_rcode", reinterpret_cast<PyCFunction>(Message_setRcode), METH_VARARGS,
      "Sets the message Response code (an Rcode object).\n"
      "If the message is not in RENDER mode, an "
      "InvalidMessageOperation is raised."},
    { "get_opcode", reinterpret_cast<PyCFunction>(Message_getOpcode), METH_NOARGS,
      "Returns the message opcode (an Opcode object)" },
    { "set_opcode", reinterpret_cast<PyCFunction>(Message_setOpcode), METH_VARARGS,
      "Sets the message opcode (an Opcode object).\n"
      "If the message is not in RENDER mode, an "
      "InvalidMessageOperation is raised."},
    { "get_edns", reinterpret_cast<PyCFunction>(Message_getEDNS), METH_NOARGS,
      "Return, if any, the EDNS associated with the message."
    },
    { "set_edns", reinterpret_cast<PyCFunction>(Message_setEDNS), METH_VARARGS,
      "Set EDNS for the message."
    },
    { "get_tsig_record",
      reinterpret_cast<PyCFunction>(Message_getTSIGRecord), METH_NOARGS,
      "Return, if any, the TSIG record contained in the received message. "
      "If no TSIG RR is set in the message, None will be returned."
    },
    { "get_rr_count", reinterpret_cast<PyCFunction>(Message_getRRCount), METH_VARARGS,
      "Returns the number of RRs contained in the given section." },
    { "get_question", reinterpret_cast<PyCFunction>(Message_getQuestion), METH_NOARGS,
      "Returns a list of all Question objects in the message "
      "(should be either 0 or 1)" },
    { "get_section", reinterpret_cast<PyCFunction>(Message_getSection), METH_VARARGS,
      "Returns a list of all RRset objects in the given section of the message\n"
      "The argument must be of type Section" },
    { "add_question", reinterpret_cast<PyCFunction>(Message_addQuestion), METH_VARARGS,
      "Add a Question to the message."
      "If the message is not in RENDER mode, an "
      "InvalidMessageOperation is raised."},
    { "add_rrset", reinterpret_cast<PyCFunction>(Message_addRRset), METH_VARARGS,
      "Add an RRset to the given section of the message.\n"
      "The first argument is of type Section\n"
      "The second is of type RRset\n"
      "The third argument is an optional Boolean specifying whether "
      "the RRset is signed"},
    { "clear", reinterpret_cast<PyCFunction>(Message_clear), METH_VARARGS,
      "Clears the message content (if any) and reinitialize the "
      "message in the given mode\n"
      "The argument must be either Message.PARSE or Message.RENDER"},
    { "make_response", reinterpret_cast<PyCFunction>(Message_makeResponse), METH_NOARGS,
      "Prepare for making a response from a request.\n"
      "This will clear the DNS header except those fields that should be kept "
      "for the response, and clear answer and the following sections. "
      "See also dns_message_reply() of BIND9."},
    { "to_text", reinterpret_cast<PyCFunction>(Message_toText), METH_NOARGS,
      "Returns the string representation of the message" },
    { "to_wire", reinterpret_cast<PyCFunction>(Message_toWire), METH_VARARGS,
      "Render the message in wire format.\n"
      "The argument must be a MessageRenderer.\n"
      "If the given message is not in RENDER mode, an "
      "InvalidMessageOperation is raised.\n"
       },
    { "from_wire", reinterpret_cast<PyCFunction>(Message_fromWire), METH_VARARGS,
      "Parses the given wire format to a Message object.\n"
      "The first argument is a Message to parse the data into.\n"
      "The second argument must implement the buffer interface.\n"
      "If the given message is not in PARSE mode, an "
      "InvalidMessageOperation is raised.\n"
      "Raises MessageTooShort, DNSMessageFORMERR or DNSMessageBADVERS "
      " if there is a problem parsing the message." },
    { NULL, NULL, 0, NULL }
};

int
Message_init(s_Message* self, PyObject* args) {
    int i;

    if (PyArg_ParseTuple(args, "i", &i)) {
        PyErr_Clear();
        if (i == Message::PARSE) {
            self->cppobj = new Message(Message::PARSE);
            return (0);
        } else if (i == Message::RENDER) {
            self->cppobj = new Message(Message::RENDER);
            return (0);
        } else {
            PyErr_SetString(PyExc_TypeError, "Message mode must be Message.PARSE or Message.RENDER");
            return (-1);
        }
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "no valid type in constructor argument");
    return (-1);
}

void
Message_destroy(s_Message* self) {
    delete self->cppobj;
    self->cppobj = NULL;
    Py_TYPE(self)->tp_free(self);
}

PyObject*
Message_getHeaderFlag(s_Message* self, PyObject* args) {
    unsigned int messageflag;
    if (!PyArg_ParseTuple(args, "I", &messageflag)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "no valid type in get_header_flag argument");
        return (NULL);
    }

    if (self->cppobj->getHeaderFlag(
            static_cast<Message::HeaderFlag>(messageflag))) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject*
Message_setHeaderFlag(s_Message* self, PyObject* args) {
    long messageflag;
    PyObject *on = Py_True;

    if (!PyArg_ParseTuple(args, "l|O!", &messageflag, &PyBool_Type, &on)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "no valid type in set_header_flag argument");
        return (NULL);
    }
    if (messageflag < 0 || messageflag > 0xffff) {
        PyErr_SetString(PyExc_ValueError, "Message header flag out of range");
        return (NULL);
    }

    try {
        self->cppobj->setHeaderFlag(
            static_cast<Message::HeaderFlag>(messageflag), on == Py_True);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_Clear();
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    } catch (const isc::InvalidParameter& ip) {
        PyErr_Clear();
        PyErr_SetString(po_InvalidParameter, ip.what());
        return (NULL);
    }
}

PyObject*
Message_getQid(s_Message* self) {
    return (Py_BuildValue("I", self->cppobj->getQid()));
}

PyObject*
Message_setQid(s_Message* self, PyObject* args) {
    long id;
    if (!PyArg_ParseTuple(args, "l", &id)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "no valid type in set_qid argument");
        return (NULL);
    }
    if (id < 0 || id > 0xffff) {
        PyErr_SetString(PyExc_ValueError,
                        "Message id out of range");
        return (NULL);
    }

    try {
        self->cppobj->setQid(id);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

PyObject*
Message_getRcode(s_Message* self) {
    try {
        return (createRcodeObject(self->cppobj->getRcode()));
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(po_IscException, "Unexpected exception");
        return (NULL);
    }
}

PyObject*
Message_setRcode(s_Message* self, PyObject* args) {
    PyObject* rcode;
    if (!PyArg_ParseTuple(args, "O!", &rcode_type, &rcode)) {
        return (NULL);
    }
    try {
        self->cppobj->setRcode(PyRcode_ToRcode(rcode));
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

PyObject*
Message_getOpcode(s_Message* self) {
    try {
        return (createOpcodeObject(self->cppobj->getOpcode()));
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(po_IscException, "Unexpected exception");
        return (NULL);
    }
}

PyObject*
Message_setOpcode(s_Message* self, PyObject* args) {
    PyObject* opcode;
    if (!PyArg_ParseTuple(args, "O!", &opcode_type, &opcode)) {
        return (NULL);
    }
    try {
        self->cppobj->setOpcode(PyOpcode_ToOpcode(opcode));
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

PyObject*
Message_getEDNS(s_Message* self) {
    ConstEDNSPtr src = self->cppobj->getEDNS();
    if (!src) {
        Py_RETURN_NONE;
    }
    return (createEDNSObject(*src));
}

PyObject*
Message_setEDNS(s_Message* self, PyObject* args) {
    PyObject* edns;
    if (!PyArg_ParseTuple(args, "O!", &edns_type, &edns)) {
        return (NULL);
    }
    try {
        self->cppobj->setEDNS(EDNSPtr(new EDNS(PyEDNS_ToEDNS(edns))));
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

PyObject*
Message_getTSIGRecord(s_Message* self) {
    try {
        const TSIGRecord* tsig_record = self->cppobj->getTSIGRecord();

        if (tsig_record == NULL) {
            Py_RETURN_NONE;
        }
        return (createTSIGRecordObject(*tsig_record));
    } catch (const InvalidMessageOperation& ex) {
        PyErr_SetString(po_InvalidMessageOperation, ex.what());
    } catch (const exception& ex) {
        const string ex_what =
            "Unexpected failure in getting TSIGRecord from message: " +
            string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
    } catch (...) {
        PyErr_SetString(PyExc_SystemError, "Unexpected failure in "
                        "getting TSIGRecord from message");
    }
    return (NULL);
}

PyObject*
Message_getRRCount(s_Message* self, PyObject* args) {
    unsigned int section;
    if (!PyArg_ParseTuple(args, "I", &section)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "no valid type in get_rr_count argument");
        return (NULL);
    }
    try {
        return (Py_BuildValue("I", self->cppobj->getRRCount(
                                  static_cast<Message::Section>(section))));
    } catch (const isc::OutOfRange& ex) {
        PyErr_SetString(PyExc_OverflowError, ex.what());
        return (NULL);
    }
}

// TODO use direct iterators for these? (or simply lists for now?)
PyObject*
Message_getQuestion(s_Message* self) {
    QuestionIterator qi, qi_end;
    try {
        qi = self->cppobj->beginQuestion();
        qi_end = self->cppobj->endQuestion();
    } catch (const InvalidMessageSection& ex) {
        PyErr_SetString(po_InvalidMessageSection, ex.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(po_IscException,
                        "Unexpected exception in getting section iterators");
        return (NULL);
    }

    PyObject* list = PyList_New(0);
    if (list == NULL) {
        return (NULL);
    }

    for (; qi != qi_end; ++qi) {
        if (PyList_Append(list, createQuestionObject(**qi)) == -1) {
            Py_DECREF(list);
            return (NULL);
        }
    }
    return (list);
}

PyObject*
Message_getSection(s_Message* self, PyObject* args) {
    unsigned int section;
    if (!PyArg_ParseTuple(args, "I", &section)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "no valid type in get_section argument");
        return (NULL);
    }
    RRsetIterator rrsi, rrsi_end;
    try {
        rrsi = self->cppobj->beginSection(
            static_cast<Message::Section>(section));
        rrsi_end = self->cppobj->endSection(
            static_cast<Message::Section>(section));
    } catch (const isc::OutOfRange& ex) {
        PyErr_SetString(PyExc_OverflowError, ex.what());
        return (NULL);
    } catch (const InvalidMessageSection& ex) {
        PyErr_SetString(po_InvalidMessageSection, ex.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(po_IscException,
                        "Unexpected exception in getting section iterators");
        return (NULL);
    }

    PyObject* list = PyList_New(0);
    if (list == NULL) {
        return (NULL);
    }
    for (; rrsi != rrsi_end; ++rrsi) {
        PyObject* rrset = createRRsetObject(**rrsi);
        if (PyList_Append(list, rrset) == -1) {
                Py_DECREF(rrset);
                Py_DECREF(list);
                return (NULL);
        }
        // PyList_Append increases refcount, so we remove ours since
        // we don't need it anymore
        Py_DECREF(rrset);
    }
    return (list);
}

//static PyObject* Message_beginQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_endQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_beginSection(s_Message* self, PyObject* args);
//static PyObject* Message_endSection(s_Message* self, PyObject* args);
//static PyObject* Message_addQuestion(s_Message* self, PyObject* args);
PyObject*
Message_addQuestion(s_Message* self, PyObject* args) {
    PyObject* question;

    if (!PyArg_ParseTuple(args, "O!", &question_type, &question)) {
        return (NULL);
    }

    self->cppobj->addQuestion(PyQuestion_ToQuestion(question));

    Py_RETURN_NONE;
}

PyObject*
Message_addRRset(s_Message* self, PyObject* args) {
    PyObject *sign = Py_False;
    int section;
    PyObject* rrset;
    if (!PyArg_ParseTuple(args, "iO!|O!", &section, &rrset_type, &rrset,
                          &PyBool_Type, &sign)) {
        return (NULL);
    }

    try {
        self->cppobj->addRRset(static_cast<Message::Section>(section),
                               PyRRset_ToRRsetPtr(rrset), sign == Py_True);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    } catch (const isc::OutOfRange& ex) {
        PyErr_SetString(PyExc_OverflowError, ex.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(po_IscException,
                        "Unexpected exception in adding RRset");
        return (NULL);
    }
}

PyObject*
Message_clear(s_Message* self, PyObject* args) {
    int i;
    if (PyArg_ParseTuple(args, "i", &i)) {
        PyErr_Clear();
        if (i == Message::PARSE) {
            self->cppobj->clear(Message::PARSE);
            Py_RETURN_NONE;
        } else if (i == Message::RENDER) {
            self->cppobj->clear(Message::RENDER);
            Py_RETURN_NONE;
        } else {
            PyErr_SetString(PyExc_TypeError,
                            "Message mode must be Message.PARSE or Message.RENDER");
            return (NULL);
        }
    } else {
        return (NULL);
    }
}

PyObject*
Message_makeResponse(s_Message* self) {
    self->cppobj->makeResponse();
    Py_RETURN_NONE;
}

PyObject*
Message_toText(s_Message* self) {
    // Py_BuildValue makes python objects from native data
    try {
        return (Py_BuildValue("s", self->cppobj->toText().c_str()));
    } catch (const InvalidMessageOperation& imo) {
        PyErr_Clear();
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(po_IscException, "Unexpected exception");
        return (NULL);
    }
}

PyObject*
Message_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                               const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

PyObject*
Message_toWire(s_Message* self, PyObject* args) {
    PyObject* mr;
    PyObject* tsig_ctx = NULL;

    if (PyArg_ParseTuple(args, "O!|O!", &messagerenderer_type, &mr,
                         &tsigcontext_type, &tsig_ctx)) {
        try {
            if (tsig_ctx == NULL) {
                self->cppobj->toWire(PyMessageRenderer_ToMessageRenderer(mr));
            } else {
                self->cppobj->toWire(PyMessageRenderer_ToMessageRenderer(mr),
                                     PyTSIGContext_ToTSIGContext(tsig_ctx));
            }
            // If we return NULL it is seen as an error, so use this for
            // None returns
            Py_RETURN_NONE;
        } catch (const InvalidMessageOperation& imo) {
            PyErr_Clear();
            PyErr_SetString(po_InvalidMessageOperation, imo.what());
            return (NULL);
        } catch (const TSIGContextError& ex) {
            // toWire() with a TSIG context can fail due to this if the
            // python program has a bug.
            PyErr_SetString(po_TSIGContextError, ex.what());
            return (NULL);
        } catch (const std::exception& ex) {
            // Other exceptions should be rare (most likely an implementation
            // bug)
            PyErr_SetString(po_TSIGContextError, ex.what());
            return (NULL);
        } catch (...) {
            PyErr_SetString(PyExc_RuntimeError,
                            "Unexpected C++ exception in Message.to_wire");
            return (NULL);
        }
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "toWire argument must be a MessageRenderer");
    return (NULL);
}

PyObject*
Message_fromWire(s_Message* self, PyObject* args) {
    const char* b;
    Py_ssize_t len;
    if (!PyArg_ParseTuple(args, "y#", &b, &len)) {
        return (NULL);
    }

    InputBuffer inbuf(b, len);
    try {
        self->cppobj->fromWire(inbuf);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    } catch (const DNSMessageFORMERR& dmfe) {
        PyErr_SetString(po_DNSMessageFORMERR, dmfe.what());
        return (NULL);
    } catch (const DNSMessageBADVERS& dmfe) {
        PyErr_SetString(po_DNSMessageBADVERS, dmfe.what());
        return (NULL);
    } catch (const MessageTooShort& mts) {
        PyErr_SetString(po_MessageTooShort, mts.what());
        return (NULL);
    }
}

} // end of unnamed namespace

namespace isc {
namespace dns {
namespace python {

//
// Declaration of the custom exceptions
// Initialization and addition of these go in the initModulePart
// function in pydnspp.cc
//
PyObject* po_MessageTooShort;
PyObject* po_InvalidMessageSection;
PyObject* po_InvalidMessageOperation;
PyObject* po_InvalidMessageUDPSize;

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_Message
// Most of the functions are not actually implemented and NULL here.
PyTypeObject message_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pydnspp.Message",
    sizeof(s_Message),                  // tp_basicsize
    0,                                  // tp_itemsize
    (destructor)Message_destroy,        // tp_dealloc
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
    Message_str,                        // tp_str
    NULL,                               // tp_getattro
    NULL,                               // tp_setattro
    NULL,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    "The Message class encapsulates a standard DNS message.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    Message_methods,                    // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    (initproc)Message_init,             // tp_init
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

} // end python namespace
} // end dns namespace
} // end isc namespace
