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


// We want a lot of different parts of the DNS API in the python
// module, but not one big 10000-line file.
// So we split it up in several 'mini-modules'
// These would be the same as a single module, except for
// the init function, which has to be modified to a unique
// name initModulePart_<name>, and return true/false instead of
// NULL/*mod
//
// The big init function is split up into a separate initModulePart function
// for each class we add.

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include <dns/message.h>
#include <dns/opcode.h>
#include <dns/tsig.h>
#include <util/python/pycppwrapper_util.h>

#include "pydnspp_common.h"

#include "edns_python.h"
#include "message_python.h"
#include "messagerenderer_python.h"
#include "name_python.h"
#include "nsec3hash_python.h"
#include "opcode_python.h"
#include "pydnspp_common.h"
#include "pydnspp_towire.h"
#include "question_python.h"
#include "rcode_python.h"
#include "rdata_python.h"
#include "rrclass_python.h"
#include "rrset_python.h"
#include "rrttl_python.h"
#include "rrtype_python.h"
#include "serial_python.h"
#include "tsigerror_python.h"
#include "tsigkey_python.h"
#include "tsig_python.h"
#include "tsig_rdata_python.h"
#include "tsigrecord_python.h"

using namespace isc::dns;
using namespace isc::dns::python;
using namespace isc::util::python;

namespace {

bool
initModulePart_EDNS(PyObject* mod) {
    // After the type has been initialized, we initialize any exceptions
    // that are defined in the wrapper for this class, and add constants
    // to the type, if any

    if (!initClass(edns_type, "EDNS", mod)) {
        return (false);
    }
    addClassVariable(edns_type, "SUPPORTED_VERSION",
                     Py_BuildValue("B", EDNS::SUPPORTED_VERSION));

    return (true);
}

bool
initModulePart_Message(PyObject* mod) {
    if (!initClass(message_type, "Message", mod)) {
        return (false);
    }

    try {
        //
        // Constant class variables
        //

        // Parse mode
        installClassVariable(message_type, "PARSE",
                             Py_BuildValue("I", Message::PARSE));
        installClassVariable(message_type, "RENDER",
                             Py_BuildValue("I", Message::RENDER));

        // Parse options
        installClassVariable(message_type, "PARSE_DEFAULT",
                             Py_BuildValue("I", Message::PARSE_DEFAULT));
        installClassVariable(message_type, "PRESERVE_ORDER",
                             Py_BuildValue("I", Message::PRESERVE_ORDER));

        // Header flags
        installClassVariable(message_type, "HEADERFLAG_QR",
                             Py_BuildValue("I", Message::HEADERFLAG_QR));
        installClassVariable(message_type, "HEADERFLAG_AA",
                             Py_BuildValue("I", Message::HEADERFLAG_AA));
        installClassVariable(message_type, "HEADERFLAG_TC",
                             Py_BuildValue("I", Message::HEADERFLAG_TC));
        installClassVariable(message_type, "HEADERFLAG_RD",
                             Py_BuildValue("I", Message::HEADERFLAG_RD));
        installClassVariable(message_type, "HEADERFLAG_RA",
                             Py_BuildValue("I", Message::HEADERFLAG_RA));
        installClassVariable(message_type, "HEADERFLAG_AD",
                             Py_BuildValue("I", Message::HEADERFLAG_AD));
        installClassVariable(message_type, "HEADERFLAG_CD",
                             Py_BuildValue("I", Message::HEADERFLAG_CD));

        // Sections
        installClassVariable(message_type, "SECTION_QUESTION",
                             Py_BuildValue("I", Message::SECTION_QUESTION));
        installClassVariable(message_type, "SECTION_ANSWER",
                             Py_BuildValue("I", Message::SECTION_ANSWER));
        installClassVariable(message_type, "SECTION_AUTHORITY",
                             Py_BuildValue("I", Message::SECTION_AUTHORITY));
        installClassVariable(message_type, "SECTION_ADDITIONAL",
                             Py_BuildValue("I", Message::SECTION_ADDITIONAL));

        // Protocol constant
        installClassVariable(message_type, "DEFAULT_MAX_UDPSIZE",
                             Py_BuildValue("I", Message::DEFAULT_MAX_UDPSIZE));

        /* Class-specific exceptions */
        po_MessageTooShort =
            PyErr_NewException("pydnspp.MessageTooShort", NULL, NULL);
        PyObjectContainer(po_MessageTooShort).installToModule(
            mod, "MessageTooShort");
        po_InvalidMessageSection =
            PyErr_NewException("pydnspp.InvalidMessageSection", NULL, NULL);
        PyObjectContainer(po_InvalidMessageSection).installToModule(
            mod, "InvalidMessageSection");
        po_InvalidMessageOperation =
            PyErr_NewException("pydnspp.InvalidMessageOperation", NULL, NULL);
        PyObjectContainer(po_InvalidMessageOperation).installToModule(
            mod, "InvalidMessageOperation");
        po_InvalidMessageUDPSize =
            PyErr_NewException("pydnspp.InvalidMessageUDPSize", NULL, NULL);
        PyObjectContainer(po_InvalidMessageUDPSize).installToModule(
            mod, "InvalidMessageUDPSize");
        po_DNSMessageBADVERS =
            PyErr_NewException("pydnspp.DNSMessageBADVERS", NULL, NULL);
        PyObjectContainer(po_DNSMessageBADVERS).installToModule(
            mod, "DNSMessageBADVERS");
        po_UnknownNSEC3HashAlgorithm =
            PyErr_NewException("pydnspp.UnknownNSEC3HashAlgorithm", NULL, NULL);
        PyObjectContainer(po_UnknownNSEC3HashAlgorithm).installToModule(
            mod, "UnknownNSEC3HashAlgorithm");
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in Message initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in Message initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_MessageRenderer(PyObject* mod) {
    if (!initClass(messagerenderer_type, "MessageRenderer", mod)) {
        return (false);
    }

    addClassVariable(messagerenderer_type, "CASE_INSENSITIVE",
                     Py_BuildValue("I", MessageRenderer::CASE_INSENSITIVE));
    addClassVariable(messagerenderer_type, "CASE_SENSITIVE",
                     Py_BuildValue("I", MessageRenderer::CASE_SENSITIVE));


    return (true);
}

bool
initModulePart_NameComparisonResult(PyObject* mod) {
    if (!initClass(name_comparison_result_type,
                   "NameComparisonResult", mod)) {
        return (false);
    }

    // Add the enums to the module
    po_NameRelation = Py_BuildValue("{i:s,i:s,i:s,i:s}",
        NameComparisonResult::SUPERDOMAIN, "SUPERDOMAIN",
        NameComparisonResult::SUBDOMAIN, "SUBDOMAIN",
        NameComparisonResult::EQUAL, "EQUAL",
        NameComparisonResult::COMMONANCESTOR, "COMMONANCESTOR");
    addClassVariable(name_comparison_result_type, "NameRelation",
                     po_NameRelation);
    // Add the constants themselves too
    addClassVariable(name_comparison_result_type, "SUPERDOMAIN",
                     Py_BuildValue("I", NameComparisonResult::SUPERDOMAIN));
    addClassVariable(name_comparison_result_type, "SUBDOMAIN",
                     Py_BuildValue("I", NameComparisonResult::SUBDOMAIN));
    addClassVariable(name_comparison_result_type, "EQUAL",
                     Py_BuildValue("I", NameComparisonResult::EQUAL));
    addClassVariable(name_comparison_result_type, "COMMONANCESTOR",
                     Py_BuildValue("I", NameComparisonResult::COMMONANCESTOR));

    return (true);
}

bool
initModulePart_Name(PyObject* mod) {
    if (!initClass(name_type, "Name", mod)) {
        return (false);
    }

    // Add the constants to the module
    addClassVariable(name_type, "MAX_WIRE",
                     Py_BuildValue("I", Name::MAX_WIRE));
    addClassVariable(name_type, "MAX_LABELS",
                     Py_BuildValue("I", Name::MAX_LABELS));
    addClassVariable(name_type, "MAX_LABELLEN",
                     Py_BuildValue("I", Name::MAX_LABELLEN));
    addClassVariable(name_type, "MAX_COMPRESS_POINTER",
                     Py_BuildValue("I", Name::MAX_COMPRESS_POINTER));
    addClassVariable(name_type, "COMPRESS_POINTER_MARK8",
                     Py_BuildValue("I", Name::COMPRESS_POINTER_MARK8));
    addClassVariable(name_type, "COMPRESS_POINTER_MARK16",
                     Py_BuildValue("I", Name::COMPRESS_POINTER_MARK16));

    addClassVariable(name_type, "ROOT_NAME",
                     createNameObject(Name::ROOT_NAME()));

    // Add the exceptions to the module
    try {
        po_EmptyLabel = PyErr_NewException("pydnspp.EmptyLabel", NULL, NULL);
        PyObjectContainer(po_EmptyLabel).installToModule(mod, "EmptyLabel");

        po_TooLongName = PyErr_NewException("pydnspp.TooLongName", NULL, NULL);
        PyObjectContainer(po_TooLongName).installToModule(mod, "TooLongName");

        po_TooLongLabel = PyErr_NewException("pydnspp.TooLongLabel", NULL, NULL);
        PyObjectContainer(po_TooLongLabel).installToModule(mod, "TooLongLabel");

        po_BadLabelType = PyErr_NewException("pydnspp.BadLabelType", NULL, NULL);
        PyObjectContainer(po_BadLabelType).installToModule(mod, "BadLabelType");

        po_BadEscape = PyErr_NewException("pydnspp.BadEscape", NULL, NULL);
        PyObjectContainer(po_BadEscape).installToModule(mod, "BadEscape");

        po_IncompleteName = PyErr_NewException("pydnspp.IncompleteName", NULL,
                                               NULL);
        PyObjectContainer(po_IncompleteName).installToModule(mod, "IncompleteName");

        po_InvalidBufferPosition =
            PyErr_NewException("pydnspp.InvalidBufferPosition", NULL, NULL);
        PyObjectContainer(po_InvalidBufferPosition).installToModule(
            mod, "InvalidBufferPosition");

        // This one could have gone into the message_python.cc file, but is
        // already needed here.
        po_DNSMessageFORMERR = PyErr_NewException("pydnspp.DNSMessageFORMERR",
                                                  NULL, NULL);
        PyObjectContainer(po_DNSMessageFORMERR).installToModule(
            mod, "DNSMessageFORMERR");
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in Name initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in Name initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_Opcode(PyObject* mod) {
    if (!initClass(opcode_type, "Opcode", mod)) {
        return (false);
    }

    addClassVariable(opcode_type, "QUERY_CODE",
                     Py_BuildValue("h", Opcode::QUERY_CODE));
    addClassVariable(opcode_type, "IQUERY_CODE",
                     Py_BuildValue("h", Opcode::IQUERY_CODE));
    addClassVariable(opcode_type, "STATUS_CODE",
                     Py_BuildValue("h", Opcode::STATUS_CODE));
    addClassVariable(opcode_type, "RESERVED3_CODE",
                     Py_BuildValue("h", Opcode::RESERVED3_CODE));
    addClassVariable(opcode_type, "NOTIFY_CODE",
                     Py_BuildValue("h", Opcode::NOTIFY_CODE));
    addClassVariable(opcode_type, "UPDATE_CODE",
                     Py_BuildValue("h", Opcode::UPDATE_CODE));
    addClassVariable(opcode_type, "RESERVED6_CODE",
                     Py_BuildValue("h", Opcode::RESERVED6_CODE));
    addClassVariable(opcode_type, "RESERVED7_CODE",
                     Py_BuildValue("h", Opcode::RESERVED7_CODE));
    addClassVariable(opcode_type, "RESERVED8_CODE",
                     Py_BuildValue("h", Opcode::RESERVED8_CODE));
    addClassVariable(opcode_type, "RESERVED9_CODE",
                     Py_BuildValue("h", Opcode::RESERVED9_CODE));
    addClassVariable(opcode_type, "RESERVED10_CODE",
                     Py_BuildValue("h", Opcode::RESERVED10_CODE));
    addClassVariable(opcode_type, "RESERVED11_CODE",
                     Py_BuildValue("h", Opcode::RESERVED11_CODE));
    addClassVariable(opcode_type, "RESERVED12_CODE",
                     Py_BuildValue("h", Opcode::RESERVED12_CODE));
    addClassVariable(opcode_type, "RESERVED13_CODE",
                     Py_BuildValue("h", Opcode::RESERVED13_CODE));
    addClassVariable(opcode_type, "RESERVED14_CODE",
                     Py_BuildValue("h", Opcode::RESERVED14_CODE));
    addClassVariable(opcode_type, "RESERVED15_CODE",
                     Py_BuildValue("h", Opcode::RESERVED15_CODE));

    return (true);
}

bool
initModulePart_Question(PyObject* mod) {
    return (initClass(question_type, "Question", mod));
}

bool
initModulePart_Rcode(PyObject* mod) {
    if (!initClass(rcode_type, "Rcode", mod)) {
        return (false);
    }

    addClassVariable(rcode_type, "NOERROR_CODE",
                     Py_BuildValue("h", Rcode::NOERROR_CODE));
    addClassVariable(rcode_type, "FORMERR_CODE",
                     Py_BuildValue("h", Rcode::FORMERR_CODE));
    addClassVariable(rcode_type, "SERVFAIL_CODE",
                     Py_BuildValue("h", Rcode::SERVFAIL_CODE));
    addClassVariable(rcode_type, "NXDOMAIN_CODE",
                     Py_BuildValue("h", Rcode::NXDOMAIN_CODE));
    addClassVariable(rcode_type, "NOTIMP_CODE",
                     Py_BuildValue("h", Rcode::NOTIMP_CODE));
    addClassVariable(rcode_type, "REFUSED_CODE",
                     Py_BuildValue("h", Rcode::REFUSED_CODE));
    addClassVariable(rcode_type, "YXDOMAIN_CODE",
                     Py_BuildValue("h", Rcode::YXDOMAIN_CODE));
    addClassVariable(rcode_type, "YXRRSET_CODE",
                     Py_BuildValue("h", Rcode::YXRRSET_CODE));
    addClassVariable(rcode_type, "NXRRSET_CODE",
                     Py_BuildValue("h", Rcode::NXRRSET_CODE));
    addClassVariable(rcode_type, "NOTAUTH_CODE",
                     Py_BuildValue("h", Rcode::NOTAUTH_CODE));
    addClassVariable(rcode_type, "NOTZONE_CODE",
                     Py_BuildValue("h", Rcode::NOTZONE_CODE));
    addClassVariable(rcode_type, "RESERVED11_CODE",
                     Py_BuildValue("h", Rcode::RESERVED11_CODE));
    addClassVariable(rcode_type, "RESERVED12_CODE",
                     Py_BuildValue("h", Rcode::RESERVED12_CODE));
    addClassVariable(rcode_type, "RESERVED13_CODE",
                     Py_BuildValue("h", Rcode::RESERVED13_CODE));
    addClassVariable(rcode_type, "RESERVED14_CODE",
                     Py_BuildValue("h", Rcode::RESERVED14_CODE));
    addClassVariable(rcode_type, "RESERVED15_CODE",
                     Py_BuildValue("h", Rcode::RESERVED15_CODE));
    addClassVariable(rcode_type, "BADVERS_CODE",
                     Py_BuildValue("h", Rcode::BADVERS_CODE));

    return (true);
}

bool
initModulePart_Rdata(PyObject* mod) {
    if (!initClass(rdata_type, "Rdata", mod)) {
        return (false);
    }

    // Add the exceptions to the class
    try {
        po_InvalidRdataLength =
            PyErr_NewException("pydnspp.InvalidRdataLength", NULL, NULL);
        PyObjectContainer(po_InvalidRdataLength).installToModule(
            mod, "InvalidRdataLength");

        po_InvalidRdataText = PyErr_NewException("pydnspp.InvalidRdataText",
                                                 NULL, NULL);
        PyObjectContainer(po_InvalidRdataText).installToModule(
            mod, "InvalidRdataText");

        po_CharStringTooLong = PyErr_NewException("pydnspp.CharStringTooLong",
                                                  NULL, NULL);
        PyObjectContainer(po_CharStringTooLong).installToModule(
            mod, "CharStringTooLong");
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in Rdata initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in Rdata initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_RRClass(PyObject* mod) {
    if (!initClass(rrclass_type, "RRClass", mod)) {
        return (false);
    }

    try {
        po_InvalidRRClass = PyErr_NewException("pydnspp.InvalidRRClass",
                                               NULL, NULL);
        PyObjectContainer(po_InvalidRRClass).installToModule(
            mod, "InvalidRRClass");

        po_IncompleteRRClass = PyErr_NewException("pydnspp.IncompleteRRClass",
                                                  NULL, NULL);
        PyObjectContainer(po_IncompleteRRClass).installToModule(
            mod, "IncompleteRRClass");
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in RRClass initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in RRClass initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_RRset(PyObject* mod) {
    if (!initClass(rrset_type, "RRset", mod)) {
        return (false);
    }

    try {
        po_EmptyRRset = PyErr_NewException("pydnspp.EmptyRRset", NULL, NULL);
        PyObjectContainer(po_EmptyRRset).installToModule(mod, "EmptyRRset");
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in RRset initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in RRset initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_RRTTL(PyObject* mod) {
    if (!initClass(rrttl_type, "RRTTL", mod)) {
        return (false);
    }

    try {
        po_InvalidRRTTL = PyErr_NewException("pydnspp.InvalidRRTTL",
                                             NULL, NULL);
        PyObjectContainer(po_InvalidRRTTL).installToModule(mod,
                                                           "InvalidRRTTL");

        po_IncompleteRRTTL = PyErr_NewException("pydnspp.IncompleteRRTTL",
                                                NULL, NULL);
        PyObjectContainer(po_IncompleteRRTTL).installToModule(
            mod, "IncompleteRRTTL");
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in RRTTL initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in RRTTL initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_RRType(PyObject* mod) {
    if (!initClass(rrtype_type, "RRType", mod)) {
        return (false);
    }

    try {
        po_InvalidRRType = PyErr_NewException("pydnspp.InvalidRRType",
                                              NULL, NULL);
        PyObjectContainer(po_InvalidRRType).installToModule(mod,
                                                            "InvalidRRType");

        po_IncompleteRRType = PyErr_NewException("pydnspp.IncompleteRRType",
                                                 NULL, NULL);
        PyObjectContainer(po_IncompleteRRType).installToModule(
            mod, "IncompleteRRType");
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in RRType initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in RRType initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_Serial(PyObject* mod) {
    return (initClass(serial_type, "Serial", mod));
}

bool
initModulePart_TSIGError(PyObject* mod) {
    if (!initClass(tsigerror_type, "TSIGError", mod)) {
        return (false);
    }

    try {
        // Constant class variables
        // Error codes (bare values)
        installClassVariable(tsigerror_type, "BAD_SIG_CODE",
                             Py_BuildValue("H", TSIGError::BAD_SIG_CODE));
        installClassVariable(tsigerror_type, "BAD_KEY_CODE",
                             Py_BuildValue("H", TSIGError::BAD_KEY_CODE));
        installClassVariable(tsigerror_type, "BAD_TIME_CODE",
                             Py_BuildValue("H", TSIGError::BAD_TIME_CODE));

        // Error codes (constant objects)
        installClassVariable(tsigerror_type, "NOERROR",
                             createTSIGErrorObject(TSIGError::NOERROR()));
        installClassVariable(tsigerror_type, "FORMERR",
                             createTSIGErrorObject(TSIGError::FORMERR()));
        installClassVariable(tsigerror_type, "SERVFAIL",
                             createTSIGErrorObject(TSIGError::SERVFAIL()));
        installClassVariable(tsigerror_type, "NXDOMAIN",
                             createTSIGErrorObject(TSIGError::NXDOMAIN()));
        installClassVariable(tsigerror_type, "NOTIMP",
                             createTSIGErrorObject(TSIGError::NOTIMP()));
        installClassVariable(tsigerror_type, "REFUSED",
                             createTSIGErrorObject(TSIGError::REFUSED()));
        installClassVariable(tsigerror_type, "YXDOMAIN",
                             createTSIGErrorObject(TSIGError::YXDOMAIN()));
        installClassVariable(tsigerror_type, "YXRRSET",
                             createTSIGErrorObject(TSIGError::YXRRSET()));
        installClassVariable(tsigerror_type, "NXRRSET",
                             createTSIGErrorObject(TSIGError::NXRRSET()));
        installClassVariable(tsigerror_type, "NOTAUTH",
                             createTSIGErrorObject(TSIGError::NOTAUTH()));
        installClassVariable(tsigerror_type, "NOTZONE",
                             createTSIGErrorObject(TSIGError::NOTZONE()));
        installClassVariable(tsigerror_type, "RESERVED11",
                             createTSIGErrorObject(TSIGError::RESERVED11()));
        installClassVariable(tsigerror_type, "RESERVED12",
                             createTSIGErrorObject(TSIGError::RESERVED12()));
        installClassVariable(tsigerror_type, "RESERVED13",
                             createTSIGErrorObject(TSIGError::RESERVED13()));
        installClassVariable(tsigerror_type, "RESERVED14",
                             createTSIGErrorObject(TSIGError::RESERVED14()));
        installClassVariable(tsigerror_type, "RESERVED15",
                             createTSIGErrorObject(TSIGError::RESERVED15()));
        installClassVariable(tsigerror_type, "BAD_SIG",
                             createTSIGErrorObject(TSIGError::BAD_SIG()));
        installClassVariable(tsigerror_type, "BAD_KEY",
                             createTSIGErrorObject(TSIGError::BAD_KEY()));
        installClassVariable(tsigerror_type, "BAD_TIME",
                             createTSIGErrorObject(TSIGError::BAD_TIME()));
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in TSIGError initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in TSIGError initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_TSIGKey(PyObject* mod) {
    if (!initClass(tsigkey_type, "TSIGKey", mod)) {
        return (false);
    }

    try {
        // Constant class variables
        installClassVariable(tsigkey_type, "HMACMD5_NAME",
                             createNameObject(TSIGKey::HMACMD5_NAME()));
        installClassVariable(tsigkey_type, "HMACSHA1_NAME",
                             createNameObject(TSIGKey::HMACSHA1_NAME()));
        installClassVariable(tsigkey_type, "HMACSHA256_NAME",
                             createNameObject(TSIGKey::HMACSHA256_NAME()));
        installClassVariable(tsigkey_type, "HMACSHA224_NAME",
                             createNameObject(TSIGKey::HMACSHA224_NAME()));
        installClassVariable(tsigkey_type, "HMACSHA384_NAME",
                             createNameObject(TSIGKey::HMACSHA384_NAME()));
        installClassVariable(tsigkey_type, "HMACSHA512_NAME",
                             createNameObject(TSIGKey::HMACSHA512_NAME()));
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in TSIGKey initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in TSIGKey initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_TSIGKeyRing(PyObject* mod) {
    if (!initClass(tsigkeyring_type, "TSIGKeyRing", mod)) {
        return (false);
    }

    addClassVariable(tsigkeyring_type, "SUCCESS",
                     Py_BuildValue("I", TSIGKeyRing::SUCCESS));
    addClassVariable(tsigkeyring_type, "EXIST",
                     Py_BuildValue("I", TSIGKeyRing::EXIST));
    addClassVariable(tsigkeyring_type, "NOTFOUND",
                     Py_BuildValue("I", TSIGKeyRing::NOTFOUND));

    return (true);
}

bool
initModulePart_TSIGContext(PyObject* mod) {
    if (!initClass(tsigcontext_type, "TSIGContext", mod)) {
        return (false);
    }

    try {
        // Class specific exceptions
        po_TSIGContextError = PyErr_NewException("pydnspp.TSIGContextError",
                                                 po_IscException, NULL);
        PyObjectContainer(po_TSIGContextError).installToModule(
            mod, "TSIGContextError");

        // Constant class variables
        installClassVariable(tsigcontext_type, "STATE_INIT",
                             Py_BuildValue("I", TSIGContext::INIT));
        installClassVariable(tsigcontext_type, "STATE_SENT_REQUEST",
                             Py_BuildValue("I", TSIGContext::SENT_REQUEST));
        installClassVariable(tsigcontext_type, "STATE_RECEIVED_REQUEST",
                             Py_BuildValue("I", TSIGContext::RECEIVED_REQUEST));
        installClassVariable(tsigcontext_type, "STATE_SENT_RESPONSE",
                             Py_BuildValue("I", TSIGContext::SENT_RESPONSE));
        installClassVariable(tsigcontext_type, "STATE_VERIFIED_RESPONSE",
                             Py_BuildValue("I",
                                           TSIGContext::VERIFIED_RESPONSE));

        installClassVariable(tsigcontext_type, "DEFAULT_FUDGE",
                             Py_BuildValue("H", TSIGContext::DEFAULT_FUDGE));
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in TSIGContext initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in TSIGContext initialization");
        return (false);
    }

    return (true);
}

bool
initModulePart_TSIG(PyObject* mod) {
    return (initClass(tsig_type, "TSIG", mod));
}

bool
initModulePart_TSIGRecord(PyObject* mod) {
    if (!initClass(tsigrecord_type, "TSIGRecord", mod)) {
        return (false);
    }

    try {
        // Constant class variables
        installClassVariable(tsigrecord_type, "TSIG_TTL",
                             Py_BuildValue("I", 0));
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in TSIGRecord initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (false);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in TSIGRecord initialization");
        return (false);
    }

    return (true);
}

PyModuleDef pydnspp = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "pydnspp",
    "Python bindings for the classes in the isc::dns namespace.\n\n"
    "These bindings match the original C++ API as closely as possible, "
    "but are not complete. Some classes are unnecessary (InputBuffer "
    "and OutputBuffer for instance), and others may be necessary, but "
    "were not up to now.",
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};
}

PyMODINIT_FUNC
PyInit_pydnspp(void) {
    PyObject* mod = PyModule_Create(&pydnspp);
    if (mod == NULL) {
        return (NULL);
    }

    try {
        // Add the exceptions to the class
        po_IscException = PyErr_NewException("pydnspp.IscException", NULL, NULL);
        PyObjectContainer(po_IscException).installToModule(mod, "IscException");

        po_InvalidOperation = PyErr_NewException("pydnspp.InvalidOperation",
                                                 NULL, NULL);
        PyObjectContainer(po_InvalidOperation).installToModule(
            mod, "InvalidOperation");

        po_InvalidParameter = PyErr_NewException("pydnspp.InvalidParameter",
                                                 NULL, NULL);
        PyObjectContainer(po_InvalidParameter).installToModule(
            mod, "InvalidParameter");
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in pydnspp initialization: " +
            std::string(ex.what());
        PyErr_SetString(po_IscException, ex_what.c_str());
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in pydnspp initialization");
        return (NULL);
    }

    // for each part included above, we call its specific initializer

    if (!initModulePart_NameComparisonResult(mod)) {
        return (NULL);
    }

    if (!initModulePart_Name(mod)) {
        return (NULL);
    }

    if (!initModulePart_MessageRenderer(mod)) {
        return (NULL);
    }

    if (!initModulePart_NSEC3Hash(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRClass(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRType(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRTTL(mod)) {
        return (NULL);
    }

    if (!initModulePart_Rdata(mod)) {
        return (NULL);
    }

    if (!initModulePart_RRset(mod)) {
        return (NULL);
    }

    if (!initModulePart_Question(mod)) {
        return (NULL);
    }

    if (!initModulePart_Opcode(mod)) {
        return (NULL);
    }

    if (!initModulePart_Rcode(mod)) {
        return (NULL);
    }

    if (!initModulePart_Message(mod)) {
        return (NULL);
    }

    if (!initModulePart_EDNS(mod)) {
        return (NULL);
    }

    if (!initModulePart_Serial(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGKey(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGKeyRing(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIG(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGError(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGRecord(mod)) {
        return (NULL);
    }

    if (!initModulePart_TSIGContext(mod)) {
        return (NULL);
    }

    return (mod);
}
