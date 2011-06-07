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

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include <config.h>

#include <log/message_dictionary.h>
#include <log/logger_manager.h>

using namespace isc::log;

namespace {


// This is for testing only. The real module will have it always set as
// NULL and will use the global dictionary.
MessageDictionary* testDictionary = NULL;

PyObject*
setTestDictionary(PyObject*, PyObject* args) {
    PyObject* enableO;
    // The API doesn't seem to provide conversion to bool,
    // so we do it little bit manually
    if (!PyArg_ParseTuple(args, "O", &enableO)) {
        return (NULL);
    }
    int enableI(PyObject_IsTrue(enableO));
    if (enableI == -1) {
        return (NULL);
    }
    bool enable(enableI != 0);

    delete testDictionary;
    testDictionary = NULL;
    try {
        if (enable) {
            testDictionary = new MessageDictionary;
        }
    }
    catch (const std::exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return (NULL);
    }
    catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Unknown C++ exception");
        return (NULL);
    }
    Py_RETURN_NONE;
}

PyObject*
createMessage(PyObject*, PyObject* args) {
    const char* mid;
    const char* text;
    // We parse the strings
    if (!PyArg_ParseTuple(args, "ss", &mid, &text)) {
        return (NULL);
    }
    PyObject* origMid;
    // And extract the original representation of the message
    // ID, so we can return it instead of creating another instance.
    // This call shouldn't fail if the previous suceeded.
    if (!PyArg_ParseTuple(args, "Os", &origMid, &text)) {
        return (NULL);
    }

    try {
        MessageDictionary* dict = testDictionary ? testDictionary :
            &MessageDictionary::globalDictionary();

        // We ignore the result, they will be in some kind of dupe list
        // if there's a problem
        dict->add(mid, text);
    }
    catch (const std::exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return (NULL);
    }
    catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Unknown C++ exception");
        return (NULL);
    }

    // Return the ID
    Py_INCREF(origMid);
    return (origMid);
}

PyObject*
getMessage(PyObject*, PyObject* args) {
    const char* mid;
    if (!PyArg_ParseTuple(args, "s", &mid)) {
        return (NULL);
    }

    try {
        MessageDictionary* dict = testDictionary ? testDictionary :
            &MessageDictionary::globalDictionary();

        const std::string& result(dict->getText(mid));
        if (result.empty()) {
            Py_RETURN_NONE;
        } else {
            return (Py_BuildValue("s", result.c_str()));
        }
    }
    catch (const std::exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return (NULL);
    }
    catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Unknown C++ exception");
        return (NULL);
    }
}

PyObject*
reset(PyObject*, PyObject*) {
    // TODO Should we check we got exactly 0 arguments?
    // But who cares, it's testing function only
    LoggerManager::reset();
    Py_RETURN_NONE;
}

PyObject*
init(PyObject*, PyObject* args) {
    const char* root;
    const char* file(NULL);
    const char* severity("INFO");
    int dbglevel(0);
    if (!PyArg_ParseTuple(args, "s|zsi", &root, &file, &severity, &dbglevel)) {
        return (NULL);
    }

    try {
        LoggerManager::init(root, file, getSeverity(severity), dbglevel);
    }
    catch (const std::exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return (NULL);
    }
    catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Unknown C++ exception");
        return (NULL);
    }
    Py_RETURN_NONE;
}

PyMethodDef methods[] = {
    {"set_test_dictionary", &setTestDictionary, METH_VARARGS,
        "Set or unset testing mode for message dictionary. In testing, "
        "the create_message and get_message functions work on different "
        "than the logger-global dictionary, not polluting it."},
    {"create_message", &createMessage, METH_VARARGS,
        "Creates a new message in the dictionary. You shouldn't need to "
        "call this directly, it should be called by the generated message "
        "file. Returns the identifier to be used in logging. The text "
        "shouldn't be empty."},
    {"get_message", &getMessage, METH_VARARGS,
        "Get a message. This function is for testing purposes and you don't "
        "need to call it. It returns None if the message does not exist."},
    {"reset", &reset, METH_VARARGS,
        "Reset all logging. For testing purposes only, do not use."},
    {"init", &init, METH_VARARGS,
        "Run-time initialization. You need to call this before you do any "
        "logging, to configure the root logger name. You may also provide "
        "a filename with message translations (or None if you don't want "
        "any), logging severity (one of 'DEBUG', 'INFO', 'WARN', 'ERROR' or "
        "'FATAL') and a debug level (integer in the range 0-99)."},
    {NULL, NULL, 0, NULL}
};

PyModuleDef iscLog = {
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL},
    "log",
    "Python bindings for the classes in the isc::log namespace.\n\n"
    "These bindings are close match to the C++ API, but they are not complete "
    "(some parts are not needed) and some are done in more python-like ways.",
    -1,
    methods,
    NULL,
    NULL,
    NULL,
    NULL
};

}

PyMODINIT_FUNC
PyInit_log(void) {
    PyObject* mod = PyModule_Create(&iscLog);
    if (mod == NULL) {
        return (NULL);
    }

    return (mod);
}
