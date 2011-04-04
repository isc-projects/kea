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

#include <exceptions/exceptions.h>
#include <dns/message.h>
using namespace isc::dns;

//
// Declaration of the custom exceptions
// Initialization and addition of these go in the initModulePart
// function at the end of this file
//
static PyObject* po_MessageTooShort;
static PyObject* po_InvalidMessageSection;
static PyObject* po_InvalidMessageOperation;
static PyObject* po_InvalidMessageUDPSize;

//
// Definition of the classes
//

// For each class, we need a struct, a helper functions (init, destroy,
// and static wrappers around the methods we export), a list of methods,
// and a type description

//
// Section
//

//
// Message
//

// The s_* Class simply coverst one instantiation of the object
class s_Message : public PyObject {
public:
    Message* message;
};

//
// We declare the functions here, the definitions are below
// the type definition of the object, since both can use the other
//

// General creation and destruction
static int Message_init(s_Message* self, PyObject* args);
static void Message_destroy(s_Message* self);

static PyObject* Message_getHeaderFlag(s_Message* self, PyObject* args);
static PyObject* Message_setHeaderFlag(s_Message* self, PyObject* args);
static PyObject* Message_getQid(s_Message* self);
static PyObject* Message_setQid(s_Message* self, PyObject* args);
static PyObject* Message_getRcode(s_Message* self);
static PyObject* Message_setRcode(s_Message* self, PyObject* args);
static PyObject* Message_getOpcode(s_Message* self);
static PyObject* Message_setOpcode(s_Message* self, PyObject* args);
static PyObject* Message_getEDNS(s_Message* self);
static PyObject* Message_setEDNS(s_Message* self, PyObject* args);
static PyObject* Message_getRRCount(s_Message* self, PyObject* args);
// use direct iterators for these? (or simply lists for now?)
static PyObject* Message_getQuestion(s_Message* self);
static PyObject* Message_getSection(s_Message* self, PyObject* args);
//static PyObject* Message_beginQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_endQuestion(s_Message* self, PyObject* args);
//static PyObject* Message_beginSection(s_Message* self, PyObject* args);
//static PyObject* Message_endSection(s_Message* self, PyObject* args);

static PyObject* Message_addQuestion(s_Message* self, PyObject* args);
static PyObject* Message_addRRset(s_Message* self, PyObject* args);
static PyObject* Message_clear(s_Message* self, PyObject* args);
static PyObject* Message_makeResponse(s_Message* self);
static PyObject* Message_toText(s_Message* self);
static PyObject* Message_str(PyObject* self);
static PyObject* Message_toWire(s_Message* self, PyObject* args);
static PyObject* Message_fromWire(s_Message* self, PyObject* args);

// This list contains the actual set of functions we have in
// python. Each entry has
// 1. Python method name
// 2. Our static function here
// 3. Argument type
// 4. Documentation
static PyMethodDef Message_methods[] = {
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

// This defines the complete type for reflection in python and
// parsing of PyObject* to s_Message
// Most of the functions are not actually implemented and NULL here.
static PyTypeObject message_type = {
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

static int
Message_init(s_Message* self, PyObject* args) {
    unsigned int i;
    
    if (PyArg_ParseTuple(args, "I", &i)) {
        PyErr_Clear();
        if (i == Message::PARSE) {
            self->message = new Message(Message::PARSE);
            return (0);
        } else if (i == Message::RENDER) {
            self->message = new Message(Message::RENDER);
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

static void
Message_destroy(s_Message* self) {
    delete self->message;
    self->message = NULL;
    Py_TYPE(self)->tp_free(self);
}

static PyObject*
Message_getHeaderFlag(s_Message* self, PyObject* args) {
    unsigned int messageflag;
    if (!PyArg_ParseTuple(args, "I", &messageflag)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "no valid type in get_header_flag argument");
        return (NULL);
    }

    if (self->message->getHeaderFlag(
            static_cast<Message::HeaderFlag>(messageflag))) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyObject*
Message_setHeaderFlag(s_Message* self, PyObject* args) {
    int messageflag;
    PyObject *on = Py_True;

    if (!PyArg_ParseTuple(args, "i|O!", &messageflag, &PyBool_Type, &on)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "no valid type in set_header_flag argument");
        return (NULL);
    }
    if (messageflag < 0) {
        PyErr_SetString(PyExc_TypeError, "invalid Message header flag");
        return (NULL);
    }

    try {
        self->message->setHeaderFlag(
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

static PyObject*
Message_getQid(s_Message* self) {
    return (Py_BuildValue("I", self->message->getQid()));
}

static PyObject*
Message_setQid(s_Message* self, PyObject* args) {
    uint16_t id;
    if (!PyArg_ParseTuple(args, "H", &id)) {
        return (NULL);
    }
    try {
        self->message->setQid(id);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_getRcode(s_Message* self) {
    s_Rcode* rcode;

    rcode = static_cast<s_Rcode*>(rcode_type.tp_alloc(&rcode_type, 0));
    if (rcode != NULL) {
        rcode->rcode = NULL;
        try {
            rcode->rcode = new Rcode(self->message->getRcode());
        } catch (const InvalidMessageOperation& imo) {
            PyErr_SetString(po_InvalidMessageOperation, imo.what());
        } catch (...) {
            PyErr_SetString(po_IscException, "Unexpected exception");
        }
        if (rcode->rcode == NULL) {
            Py_DECREF(rcode);
            return (NULL);
        }
    }

    return (rcode);
}

static PyObject*
Message_setRcode(s_Message* self, PyObject* args) {
    s_Rcode* rcode;
    if (!PyArg_ParseTuple(args, "O!", &rcode_type, &rcode)) {
        return (NULL);
    }
    try {
        self->message->setRcode(*rcode->rcode);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_getOpcode(s_Message* self) {
    s_Opcode* opcode;

    opcode = static_cast<s_Opcode*>(opcode_type.tp_alloc(&opcode_type, 0));
    if (opcode != NULL) {
        opcode->opcode = NULL;
        try {
            opcode->opcode = new Opcode(self->message->getOpcode());
        } catch (const InvalidMessageOperation& imo) {
            PyErr_SetString(po_InvalidMessageOperation, imo.what());
        } catch (...) {
            PyErr_SetString(po_IscException, "Unexpected exception");
        }
        if (opcode->opcode == NULL) {
            Py_DECREF(opcode);
            return (NULL);
        }
    }

    return (opcode);
}

static PyObject*
Message_setOpcode(s_Message* self, PyObject* args) {
    s_Opcode* opcode;
    if (!PyArg_ParseTuple(args, "O!", &opcode_type, &opcode)) {
        return (NULL);
    }
    try {
        self->message->setOpcode(*opcode->opcode);
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_getEDNS(s_Message* self) {
    s_EDNS* edns;
    EDNS* edns_body;
    ConstEDNSPtr src = self->message->getEDNS();

    if (!src) {
        Py_RETURN_NONE;
    }
    if ((edns_body = new(nothrow) EDNS(*src)) == NULL) {
        return (PyErr_NoMemory());
    }
    edns = static_cast<s_EDNS*>(opcode_type.tp_alloc(&edns_type, 0));
    if (edns != NULL) {
        edns->edns = edns_body;
    }

    return (edns);
}

static PyObject*
Message_setEDNS(s_Message* self, PyObject* args) {
    s_EDNS* edns;
    if (!PyArg_ParseTuple(args, "O!", &edns_type, &edns)) {
        return (NULL);
    }
    try {
        self->message->setEDNS(EDNSPtr(new EDNS(*edns->edns)));
        Py_RETURN_NONE;
    } catch (const InvalidMessageOperation& imo) {
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    }
}

static PyObject*
Message_getRRCount(s_Message* self, PyObject* args) {
    unsigned int section;
    if (!PyArg_ParseTuple(args, "I", &section)) {
        PyErr_Clear();
        PyErr_SetString(PyExc_TypeError,
                        "no valid type in get_rr_count argument");
        return (NULL);
    }
    try {
        return (Py_BuildValue("I", self->message->getRRCount(
                                  static_cast<Message::Section>(section))));
    } catch (const isc::OutOfRange& ex) {
        PyErr_SetString(PyExc_OverflowError, ex.what());
        return (NULL);
    }
}

// TODO use direct iterators for these? (or simply lists for now?)
static PyObject*
Message_getQuestion(s_Message* self) {
    QuestionIterator qi, qi_end;
    try {
        qi = self->message->beginQuestion();
        qi_end = self->message->endQuestion();
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
        s_Question *question = static_cast<s_Question*>(
            question_type.tp_alloc(&question_type, 0));
        if (question == NULL) {
            Py_DECREF(question);
            Py_DECREF(list);
            return (NULL);
        }
        question->question = *qi;
        if (PyList_Append(list, question) == -1) {
            Py_DECREF(question);
            Py_DECREF(list);
            return (NULL);
        }
        Py_DECREF(question);
    }
    return (list);
}

static PyObject*
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
        rrsi = self->message->beginSection(
            static_cast<Message::Section>(section));
        rrsi_end = self->message->endSection(
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
        s_RRset *rrset = static_cast<s_RRset*>(
            rrset_type.tp_alloc(&rrset_type, 0));
        if (rrset == NULL) {
                Py_DECREF(rrset);
                Py_DECREF(list);
                return (NULL);
        }
        rrset->rrset = *rrsi;
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
static PyObject*
Message_addQuestion(s_Message* self, PyObject* args) {
    s_Question *question;

    if (!PyArg_ParseTuple(args, "O!", &question_type, &question)) {
        return (NULL);
    }

    self->message->addQuestion(question->question);
    
    Py_RETURN_NONE;
}

static PyObject*
Message_addRRset(s_Message* self, PyObject* args) {
    PyObject *sign = Py_False;
    unsigned int section;
    s_RRset* rrset;
    if (!PyArg_ParseTuple(args, "IO!|O!", &section, &rrset_type, &rrset,
                          &PyBool_Type, &sign)) {
        return (NULL);
    }

    try {
        self->message->addRRset(static_cast<Message::Section>(section),
                                rrset->rrset, sign == Py_True);
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

static PyObject*
Message_clear(s_Message* self, PyObject* args) {
    unsigned int i;
    if (PyArg_ParseTuple(args, "I", &i)) {
        PyErr_Clear();
        if (i == Message::PARSE) {
            self->message->clear(Message::PARSE);
            Py_RETURN_NONE;
        } else if (i == Message::RENDER) {
            self->message->clear(Message::RENDER);
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

static PyObject*
Message_makeResponse(s_Message* self) {
    self->message->makeResponse();
    Py_RETURN_NONE;
}

static PyObject*
Message_toText(s_Message* self) {
    // Py_BuildValue makes python objects from native data
    try {
        return (Py_BuildValue("s", self->message->toText().c_str()));
    } catch (const InvalidMessageOperation& imo) {
        PyErr_Clear();
        PyErr_SetString(po_InvalidMessageOperation, imo.what());
        return (NULL);
    } catch (...) {
        PyErr_SetString(po_IscException, "Unexpected exception");
        return (NULL);
    }
}

static PyObject*
Message_str(PyObject* self) {
    // Simply call the to_text method we already defined
    return (PyObject_CallMethod(self,
                               const_cast<char*>("to_text"),
                                const_cast<char*>("")));
}

static PyObject*
Message_toWire(s_Message* self, PyObject* args) {
    s_MessageRenderer* mr;
    
    if (PyArg_ParseTuple(args, "O!", &messagerenderer_type, &mr)) {
        try {
            self->message->toWire(*mr->messagerenderer);
            // If we return NULL it is seen as an error, so use this for
            // None returns
            Py_RETURN_NONE;
        } catch (const InvalidMessageOperation& imo) {
            PyErr_Clear();
            PyErr_SetString(po_InvalidMessageOperation, imo.what());
            return (NULL);
        }
    }
    PyErr_Clear();
    PyErr_SetString(PyExc_TypeError,
                    "toWire argument must be a MessageRenderer");
    return (NULL);
}

static PyObject*
Message_fromWire(s_Message* self, PyObject* args) {
    const char* b;
    Py_ssize_t len;
    if (!PyArg_ParseTuple(args, "y#", &b, &len)) {
        return (NULL);
    }
    
    InputBuffer inbuf(b, len);
    try {
        self->message->fromWire(inbuf);
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

// Module Initialization, all statics are initialized here
bool
initModulePart_Message(PyObject* mod) {
    if (PyType_Ready(&message_type) < 0) {
        return (false);
    }
    Py_INCREF(&message_type);
    
    // Class variables
    // These are added to the tp_dict of the type object
    //
    addClassVariable(message_type, "PARSE",
                     Py_BuildValue("I", Message::PARSE));
    addClassVariable(message_type, "RENDER",
                     Py_BuildValue("I", Message::RENDER));

    addClassVariable(message_type, "HEADERFLAG_QR",
                     Py_BuildValue("I", Message::HEADERFLAG_QR));
    addClassVariable(message_type, "HEADERFLAG_AA",
                     Py_BuildValue("I", Message::HEADERFLAG_AA));
    addClassVariable(message_type, "HEADERFLAG_TC",
                     Py_BuildValue("I", Message::HEADERFLAG_TC));
    addClassVariable(message_type, "HEADERFLAG_RD",
                     Py_BuildValue("I", Message::HEADERFLAG_RD));
    addClassVariable(message_type, "HEADERFLAG_RA",
                     Py_BuildValue("I", Message::HEADERFLAG_RA));
    addClassVariable(message_type, "HEADERFLAG_AD",
                     Py_BuildValue("I", Message::HEADERFLAG_AD));
    addClassVariable(message_type, "HEADERFLAG_CD",
                     Py_BuildValue("I", Message::HEADERFLAG_CD));

    addClassVariable(message_type, "SECTION_QUESTION",
                     Py_BuildValue("I", Message::SECTION_QUESTION));
    addClassVariable(message_type, "SECTION_ANSWER",
                     Py_BuildValue("I", Message::SECTION_ANSWER));
    addClassVariable(message_type, "SECTION_AUTHORITY",
                     Py_BuildValue("I", Message::SECTION_AUTHORITY));
    addClassVariable(message_type, "SECTION_ADDITIONAL",
                     Py_BuildValue("I", Message::SECTION_ADDITIONAL));

    addClassVariable(message_type, "DEFAULT_MAX_UDPSIZE",
                     Py_BuildValue("I", Message::DEFAULT_MAX_UDPSIZE));

    /* Class-specific exceptions */
    po_MessageTooShort = PyErr_NewException("pydnspp.MessageTooShort", NULL,
                                            NULL);
    PyModule_AddObject(mod, "MessageTooShort", po_MessageTooShort);
    po_InvalidMessageSection =
        PyErr_NewException("pydnspp.InvalidMessageSection", NULL, NULL);
    PyModule_AddObject(mod, "InvalidMessageSection", po_InvalidMessageSection);
    po_InvalidMessageOperation =
        PyErr_NewException("pydnspp.InvalidMessageOperation", NULL, NULL);
    PyModule_AddObject(mod, "InvalidMessageOperation",
                       po_InvalidMessageOperation);
    po_InvalidMessageUDPSize =
        PyErr_NewException("pydnspp.InvalidMessageUDPSize", NULL, NULL);
    PyModule_AddObject(mod, "InvalidMessageUDPSize", po_InvalidMessageUDPSize);
    po_DNSMessageBADVERS = PyErr_NewException("pydnspp.DNSMessageBADVERS",
                                              NULL, NULL);
    PyModule_AddObject(mod, "DNSMessageBADVERS", po_DNSMessageBADVERS);

    PyModule_AddObject(mod, "Message",
                       reinterpret_cast<PyObject*>(&message_type));


    return (true);
}
