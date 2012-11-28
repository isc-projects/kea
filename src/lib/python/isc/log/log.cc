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
#include <log/logger_support.h>
#include <log/logger.h>

#include <config/ccsession.h>

#include <string>
#include <boost/bind.hpp>

#include <util/python/pycppwrapper_util.h>
#include <log/log_dbglevels.h>

using namespace isc::log;
using namespace isc::util::python;
using std::string;
using boost::bind;

// We encountered a strange problem with Clang (clang version 2.8
// (tags/RELEASE_28 115909)) on OSX, where unwinding the stack
// segfaults the moment this exception was thrown and caught.
//
// Placing it in a named namespace instead of the originalRecommend
// unnamed namespace appears to solve this, so as a temporary
// workaround, we create a local randomly named namespace here
// to solve this issue.
namespace clang_unnamed_namespace_workaround {
    // To propagate python exceptions through our code
    // This exception is used to signal to the calling function that a
    // proper Python Exception has already been set, and the caller
    // should now return NULL.
    // Since it is only used internally, and should not pass any
    // information itself, is is not derived from std::exception
    class InternalError : public std::exception {};
}
using namespace clang_unnamed_namespace_workaround;

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

    try {
        delete testDictionary;
        testDictionary = NULL;
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
    LoggerManager::reset();
    Py_RETURN_NONE;
}

PyObject*
init(PyObject*, PyObject* args, PyObject* arg_keywords) {
    const char* root;
    const char* file(NULL);
    const char* severity("INFO");
    bool buffer = false;
    int dbglevel(0);
    const char* keywords[] = { "name", "severity", "debuglevel", "file",
                               "buffer", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, arg_keywords, "s|sizb",
                                     const_cast<char**>(keywords), &root,
                                     &severity, &dbglevel, &file,
                                     &buffer)) {
        return (NULL);
    }

    try {
        LoggerManager::init(root, getSeverity(severity), dbglevel, file,
                            buffer);
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

// This initialization is for unit tests.  It allows message settings to
// be determined by a set of B10_xxx environment variables.  (See the
// description of initLogger() for more details.)  The function has been named
// resetUnitTestRootLogger() here as being more descriptive and
// trying to avoid confusion.
PyObject*
resetUnitTestRootLogger(PyObject*, PyObject*) {
    try {
        isc::log::resetUnitTestRootLogger();
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
logConfigUpdate(PyObject*, PyObject* args) {
    // we have no wrappers for ElementPtr and ConfigData,
    // So we expect JSON strings and convert them.
    // The new_config object is assumed to have been validated.

    const char* new_config_json;
    const char* mod_spec_json;
    if (!PyArg_ParseTuple(args, "ss",
                          &new_config_json, &mod_spec_json)) {
        return (NULL);
    }

    try {
        isc::data::ConstElementPtr new_config =
            isc::data::Element::fromJSON(new_config_json);
        isc::data::ConstElementPtr mod_spec_e =
            isc::data::Element::fromJSON(mod_spec_json);
        isc::config::ModuleSpec mod_spec(mod_spec_e);
        isc::config::ConfigData config_data(mod_spec);
        isc::config::default_logconfig_handler("logging", new_config,
                                               config_data);

        Py_RETURN_NONE;
    } catch (const isc::data::JSONError& je) {
        std::string error_msg = std::string("JSON format error: ") + je.what();
        PyErr_SetString(PyExc_TypeError, error_msg.c_str());
    } catch (const isc::data::TypeError&) {
        PyErr_SetString(PyExc_TypeError, "argument 1 of log_config_update "
                                         "is not a map of config data");
    } catch (const isc::config::ModuleSpecError&) {
        PyErr_SetString(PyExc_TypeError, "argument 2 of log_config_update "
                                         "is not a correct module specification");
    } catch (const std::exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Unknown C++ exception");
    }
    return (NULL);
}

PyMethodDef methods[] = {
    {"set_test_dictionary", setTestDictionary, METH_VARARGS,
        "Set or unset testing mode for message dictionary. In testing, "
        "the create_message and get_message functions work on different "
        "than the logger-global dictionary, not polluting it."},
    {"create_message", createMessage, METH_VARARGS,
        "Creates a new message in the dictionary. You shouldn't need to "
        "call this directly, it should be called by the generated message "
        "file. Returns the identifier to be used in logging. The text "
        "shouldn't be empty."},
    {"get_message", getMessage, METH_VARARGS,
        "Get a message. This function is for testing purposes and you don't "
        "need to call it. It returns None if the message does not exist."},
    {"reset", reset, METH_NOARGS,
        "Reset all logging. For testing purposes only, do not use."},
    {"init", reinterpret_cast<PyCFunction>(init), METH_VARARGS | METH_KEYWORDS,
        "Run-time initialization. You need to call this before you do any "
        "logging, to configure the root logger name. You may also provide "
        "Arguments:\n"
        "name: root logger name\n"
        "severity (optional): one of 'DEBUG', 'INFO', 'WARN', 'ERROR' or "
        "'FATAL')\n"
        "debuglevel (optional): a debug level (integer in the range 0-99) "
        "file (optional): a file name of a dictionary with message text "
        "translations\n"
        "buffer (optional), boolean, when True, causes all log messages "
        "to be stored internally until log_config_update is called, at "
        "which pointed they shall be logged."},
    {"resetUnitTestRootLogger", resetUnitTestRootLogger, METH_VARARGS,
        "Resets the configuration of the root logger to that set by the "
        "B10_XXX environment variables.  It is aimed at unit tests, where "
        "the logging is initialized by the code under test; called before "
        "the unit test starts, this function resets the logging configuration "
        "to that in use for the C++ unit tests."},
    {"log_config_update", logConfigUpdate, METH_VARARGS,
        "Update logger settings. This method is automatically used when "
        "ModuleCCSession is initialized with handle_logging_config set "
        "to True. When called, the first argument is the new logging "
        "configuration (in JSON format). The second argument is "
        "the raw specification (as returned from "
        "ConfigData.get_module_spec().get_full_spec(), and converted to "
        "JSON format).\n"
        "Raises a TypeError if either argument is not a (correct) JSON "
        "string, or if the spec is not a correct spec.\n"
        "If this call succeeds, the global logger settings have "
        "been updated."
    },
    {NULL, NULL, 0, NULL}
};

class LoggerWrapper : public PyObject {
// Everything is public here, as it is accessible only inside this .cc file.
public:
    Logger *logger_;
};

extern PyTypeObject logger_type;

int
Logger_init(PyObject* po_self, PyObject* args, PyObject*) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return (-1);
    }
    try {
        self->logger_ = new Logger(name);
        return (0);
    }
    catch (const std::exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return (-1);
    }
    catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Unknown C++ exception");
        return (-1);
    }
}

void
//Logger_destroy(LoggerWrapper* const self) {
Logger_destroy(PyObject* po_self) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    delete self->logger_;
    self->logger_ = NULL;
    Py_TYPE(self)->tp_free(self);
}

// The isc::log doesn't contain function to convert this way
const char*
severityToText(const Severity& severity) {
    switch (severity) {
        case DEFAULT:
            return ("DEFAULT");
        case DEBUG:
            return ("DEBUG");
        case INFO:
            return ("INFO");
        case WARN:
            return ("WARN");
        case ERROR:
            return ("ERROR");
        case FATAL:
            return ("FATAL");
        default:
            return (NULL);
    }
}

PyObject*
Logger_getEffectiveSeverity(PyObject* po_self, PyObject*) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    try {
        return (Py_BuildValue("s",
                              severityToText(
                                  self->logger_->getEffectiveSeverity())));
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
Logger_getEffectiveDebugLevel(PyObject* po_self, PyObject*) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    try {
        return (Py_BuildValue("i", self->logger_->getEffectiveDebugLevel()));
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
Logger_setSeverity(PyObject* po_self, PyObject* args) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    const char* severity;
    int dbgLevel = 0;
    if (!PyArg_ParseTuple(args, "z|i", &severity, &dbgLevel)) {
        return (NULL);
    }
    try {
        self->logger_->setSeverity((severity == NULL) ? DEFAULT :
                                   getSeverity(severity), dbgLevel);
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

template<class FPtr> // Who should remember the pointer-to-method syntax
PyObject*
Logger_isLevelEnabled(LoggerWrapper* self, FPtr function) {
    try {
        if ((self->logger_->*function)()) {
            Py_RETURN_TRUE;
        } else {
            Py_RETURN_FALSE;
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
Logger_isInfoEnabled(PyObject* po_self, PyObject*) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    return (Logger_isLevelEnabled(self, &Logger::isInfoEnabled));
}

PyObject*
Logger_isWarnEnabled(PyObject* po_self, PyObject*) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    return (Logger_isLevelEnabled(self, &Logger::isWarnEnabled));
}

PyObject*
Logger_isErrorEnabled(PyObject* po_self, PyObject*) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    return (Logger_isLevelEnabled(self, &Logger::isErrorEnabled));
}

PyObject*
Logger_isFatalEnabled(PyObject* po_self, PyObject*) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    return (Logger_isLevelEnabled(self, &Logger::isFatalEnabled));
}

PyObject*
Logger_isDebugEnabled(PyObject* po_self, PyObject* args) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    int level = MIN_DEBUG_LEVEL;
    if (!PyArg_ParseTuple(args, "|i", &level)) {
        return (NULL);
    }

    try {
        if (self->logger_->isDebugEnabled(level)) {
            Py_RETURN_TRUE;
        } else {
            Py_RETURN_FALSE;
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

string
objectToStr(PyObject* object, bool convert) {
    PyObjectContainer objstr_container;
    if (convert) {
        PyObject* text_obj = PyObject_Str(object);
        if (text_obj == NULL) {
            // PyObject_Str could fail for various reasons, including because
            // the object cannot be converted to a string.  We exit with
            // InternalError to preserve the PyErr set in PyObject_Str.
            throw InternalError();
        }
        objstr_container.reset(text_obj);
        object = objstr_container.get();
    }

    PyObjectContainer tuple_container(Py_BuildValue("(O)", object));
    const char* value;
    if (!PyArg_ParseTuple(tuple_container.get(), "s", &value)) {
        throw InternalError();
    }
    return (string(value));
}

// Generic function to output the logging message. Called by the real functions.
template <class Function>
PyObject*
Logger_performOutput(Function function, PyObject* args, bool dbgLevel) {
    try {
        const Py_ssize_t number(PyObject_Length(args));
        if (number < 0) {
            return (NULL);
        }

        // Which argument is the first to format?
        const size_t start = dbgLevel ? 2 : 1;
        if (number < start) {
            return (PyErr_Format(PyExc_TypeError, "Too few arguments to "
                                 "logging call, at least %zu needed and %zd "
                                 "given", start, number));
        }

        // Extract the fixed arguments
        long dbg(0);
        if (dbgLevel) {
            PyObjectContainer dbg_container(PySequence_GetItem(args, 0));
            dbg = PyLong_AsLong(dbg_container.get());
            if (PyErr_Occurred()) {
                return (NULL);
            }
        }

        // We create the logging message right now. If we fail to convert a
        // parameter to string, at least the part that we already did will
        // be output
        PyObjectContainer msgid_container(PySequence_GetItem(args, start - 1));
        const string mid(objectToStr(msgid_container.get(), false));
        Logger::Formatter formatter(function(dbg, mid.c_str()));

        // Now process the rest of parameters, convert each to string and put
        // into the formatter. It will print itself in the end.
        for (size_t i(start); i < number; ++ i) {
            PyObjectContainer param_container(PySequence_GetItem(args, i));
            try {
                formatter = formatter.arg(objectToStr(param_container.get(),
                                                      true));
            }
            catch (...) {
                formatter.deactivate();
                throw;
            }
        }
        Py_RETURN_NONE;
    }
    catch (const InternalError&) {
        return (NULL);
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

// Now map the functions into the performOutput. I wish C++ could do
// functional programming.
PyObject*
Logger_debug(PyObject* po_self, PyObject* args) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    return (Logger_performOutput(bind(&Logger::debug, self->logger_, _1, _2),
                                 args, true));
}

PyObject*
Logger_info(PyObject* po_self, PyObject* args) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    return (Logger_performOutput(bind(&Logger::info, self->logger_, _2),
                                 args, false));
}

PyObject*
Logger_warn(PyObject* po_self, PyObject* args) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    return (Logger_performOutput(bind(&Logger::warn, self->logger_, _2),
                                 args, false));
}

PyObject*
Logger_error(PyObject* po_self, PyObject* args) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    return (Logger_performOutput(bind(&Logger::error, self->logger_, _2),
                                 args, false));
}

PyObject*
Logger_fatal(PyObject* po_self, PyObject* args) {
    LoggerWrapper* self = static_cast<LoggerWrapper*>(po_self);
    return (Logger_performOutput(bind(&Logger::fatal, self->logger_, _2),
                                 args, false));
}

PyMethodDef loggerMethods[] = {
    { "get_effective_severity", Logger_getEffectiveSeverity, METH_NOARGS,
        "Returns the effective logging severity as string" },
    { "get_effective_debug_level", Logger_getEffectiveDebugLevel, METH_NOARGS,
        "Returns the current debug level." },
    { "set_severity", Logger_setSeverity, METH_VARARGS,
        "Sets the severity of a logger. The parameters are severity as a "
        "string and, optionally, a debug level (integer in range 0-99). "
        "The severity may be NULL, in which case an inherited value is taken."
    },
    { "is_debug_enabled", Logger_isDebugEnabled, METH_VARARGS,
      "Returns if the logger would log debug message now. "
            "You can provide a desired debug level." },
    { "is_info_enabled", Logger_isInfoEnabled, METH_NOARGS,
      "Returns if the logger would log info message now." },
    { "is_warn_enabled", Logger_isWarnEnabled, METH_NOARGS,
      "Returns if the logger would log warn message now." },
    { "is_error_enabled", Logger_isErrorEnabled, METH_NOARGS,
      "Returns if the logger would log error message now." },
    { "is_fatal_enabled", Logger_isFatalEnabled, METH_NOARGS,
      "Returns if the logger would log fatal message now." },
    { "debug", Logger_debug, METH_VARARGS,
        "Logs a debug-severity message. It takes the debug level, message ID "
        "and any number of stringifiable arguments to the message." },
    { "info", Logger_info, METH_VARARGS,
        "Logs a info-severity message. It taskes the message ID and any "
        "number of stringifiable arguments to the message." },
    { "warn", Logger_warn, METH_VARARGS,
        "Logs a warn-severity message. It taskes the message ID and any "
        "number of stringifiable arguments to the message." },
    { "error", Logger_error, METH_VARARGS,
        "Logs a error-severity message. It taskes the message ID and any "
        "number of stringifiable arguments to the message." },
    { "fatal", Logger_fatal, METH_VARARGS,
        "Logs a fatal-severity message. It taskes the message ID and any "
        "number of stringifiable arguments to the message." },
    { NULL, NULL, 0, NULL }
};

PyTypeObject logger_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "isc.log.Logger",
    sizeof(LoggerWrapper),                 // tp_basicsize
    0,                                  // tp_itemsize
    Logger_destroy,                     // tp_dealloc
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
    "Wrapper around the C++ isc::log::Logger class."
    "It is not complete, but everything important should be here.",
    NULL,                               // tp_traverse
    NULL,                               // tp_clear
    NULL,                               // tp_richcompare
    0,                                  // tp_weaklistoffset
    NULL,                               // tp_iter
    NULL,                               // tp_iternext
    loggerMethods,                      // tp_methods
    NULL,                               // tp_members
    NULL,                               // tp_getset
    NULL,                               // tp_base
    NULL,                               // tp_dict
    NULL,                               // tp_descr_get
    NULL,                               // tp_descr_set
    0,                                  // tp_dictoffset
    Logger_init,                        // tp_init
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

} // end anonymous namespace

PyMODINIT_FUNC
PyInit_log(void) {
    PyObject* mod = PyModule_Create(&iscLog);
    if (mod == NULL) {
        return (NULL);
    }

    // Finalize logger class and add in the definitions of the standard debug
    // levels.  These can then be referred to in Python through the constants
    // log.DBGLVL_XXX.
    // N.B. These should be kept in sync with the constants defined in
    // log_dbglevels.h.
    try {
        if (PyType_Ready(&logger_type) < 0) {
            throw InternalError();
        }
        void* p = &logger_type;
        if (PyModule_AddObject(mod, "Logger",
                               static_cast<PyObject*>(p)) < 0) {
            throw InternalError();
        }

        installClassVariable(logger_type, "DBGLVL_START_SHUT",
                             Py_BuildValue("I", DBGLVL_START_SHUT));
        installClassVariable(logger_type, "DBGLVL_COMMAND",
                             Py_BuildValue("I", DBGLVL_COMMAND));
        installClassVariable(logger_type, "DBGLVL_COMMAND_DATA",
                             Py_BuildValue("I", DBGLVL_COMMAND_DATA));
        installClassVariable(logger_type, "DBGLVL_TRACE_BASIC",
                             Py_BuildValue("I", DBGLVL_TRACE_BASIC));
        installClassVariable(logger_type, "DBGLVL_TRACE_BASIC_DATA",
                             Py_BuildValue("I", DBGLVL_TRACE_BASIC_DATA));
        installClassVariable(logger_type, "DBGLVL_TRACE_DETAIL",
                             Py_BuildValue("I", DBGLVL_TRACE_DETAIL));
        installClassVariable(logger_type, "DBGLVL_TRACE_DETAIL_DATA",
                             Py_BuildValue("I", DBGLVL_TRACE_DETAIL_DATA));
    } catch (const InternalError&) {
        Py_DECREF(mod);
        return (NULL);
    } catch (const std::exception& ex) {
        const std::string ex_what =
            "Unexpected failure in Log initialization: " +
            std::string(ex.what());
        PyErr_SetString(PyExc_SystemError, ex_what.c_str());
        Py_DECREF(mod);
        return (NULL);
    } catch (...) {
        PyErr_SetString(PyExc_SystemError,
                        "Unexpected failure in Log initialization");
        Py_DECREF(mod);
        return (NULL);
    }

    Py_INCREF(&logger_type);
    return (mod);
}
