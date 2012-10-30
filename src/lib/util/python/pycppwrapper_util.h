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

#ifndef PYCPPWRAPPER_UTIL_H
#define PYCPPWRAPPER_UTIL_H 1

#include <Python.h>

#include <exceptions/exceptions.h>

/**
 * @file pycppwrapper_util.h
 * @short Shared definitions for python/C(++) API
 *
 * This utility defines a set of convenient wrappers for the python C API
 * to use it safely from our C++ bindings.  The python C API has many pitfalls
 * such as not-so-consistent reference count policies.  Also, many existing
 * examples are careless about error handling.  It's easy to find on the net
 * example (even of "production use") python extensions like this:
 *
 * \code
 *     new_exception = PyErr_NewException("mymodule.Exception", NULL, NULL);
 *     // new_exception can be NULL, in which case the call to
 *     // PyModule_AddObject will cause a surprising disruption.
 *     PyModule_AddObject(mymodule, "Exception", new_exception); \endcode
 *
 * When using the python C API with C++, we should also be careful about
 * exception safety.  The underlying C++ code (including standard C++ libraries
 * and memory allocation) can throw exceptions, in which case we need to
 * make sure any intermediate python objects are cleaned up (we also need to
 * catch the C++ exceptions inside the binding and convert them to python
 * errors, but that's a different subject).  This is not a trivial task
 * because the python objects are represented as bare C pointers (so there's
 * no destructor) and we need to address the exception safety along with python
 * reference counters (so we cannot naively apply standard smart pointers).
 *
 * This utility tries to help address these issues.
 *
 * Also, it's intentional that this is a header-only utility.  This way the
 * C++ loadable module won't depend on another C++ library (which is not
 * necessarily wrong, but would increase management cost such as link-time
 * troubles only for a small utility feature).
 */

namespace isc {
namespace util {
namespace python {

/// This is thrown inside this utility when it finds a NULL pointer is passed
/// when it should not be NULL.
class PyCPPWrapperException : public isc::Exception {
public:
    PyCPPWrapperException(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// This helper class is similar to the standard autoptr and manages PyObject
/// using some kind of RAII techniques.  It is, however, customized for the
/// python C API.
///
/// A PyObjectContainer object is constructed with a pointer to PyObject,
/// which is often just created dynamically.  The caller will eventually
/// attach the object to a different python object (often a module or class)
/// via specific methods or directly return it to the python interpreter.
///
/// There are two cases in destructing the object: with or without decreasing
/// a reference to the PyObject.  If the object is intended to be an argument
/// to another python C library that increases the reference to the object for
/// itself, we should normally release our own reference; otherwise the
/// reference will leak and the object won't be garbage collected.  Also, when
/// an unexpected error happens in the form of C++ exception, we should
/// release the reference to prevent resource leak.
///
/// In some other cases, we should simply give our reference to the caller.
/// That is the case when the created object itself is a return value of
/// an extended python method written in the C++ binding.  Likewise, some
/// python C library functions "steal" the reference.  In these cases we
/// should not decrease the reference; otherwise it would cause duplicate free.
///
/// By default, the destructor of this class releases the reference to the
/// PyObject.  If this behavior is desirable, you can extract the original
/// bare pointer to the PyObject by the \c get() method.  If you don't want
/// the reference to be decreased, the original bare pointer should be
/// extracted using the \c release() method.
///
/// In some other cases, it would be convenient if it's possible to create
/// an "empty" container and reset it with a Python object later.
/// For example, we may want to create a temporary Python object in the
/// middle of a function and make sure that it's valid within the rest of
/// the function scope, while we want to make sure its reference is released
/// when the function returns (either normally or as a result of exception).
/// To allow this scenario, this class defines the default constructor
/// and the \c reset() method.  The default constructor allows the class
/// object with an "empty" (NULL) Python object, while \c reset() allows
/// the stored object to be replaced with a new one.  If there's a valid
/// object was already set, \c reset() releases its reference.
/// In general, it's safer to construct the container object with a valid
/// Python object pointer.  The use of the default constructor and
/// \c reset() should therefore be restricted to cases where it's
/// absolutely necessary.
///
/// There are two convenience methods for commonly used operations:
/// \c installAsClassVariable() to add the PyObject as a class variable
/// and \c installToModule to add the PyObject to a specified python module.
/// These methods (at least to some extent) take care of the reference to
/// the object (either release or keep) depending on the usage context so
/// that the user don't have to worry about it.
///
/// On construction, this class expects the pointer can be NULL.
/// If it happens it immediately throws a \c PyCPPWrapperException exception.
/// This behavior is to convert failures in the python C API (such as
/// PyObject_New() returning NULL) to C++ exception so that we can unify
/// error handling in the style of C++ exceptions.
///
/// Examples 1: To create a tuple of two python objects, do this:
///
/// \code
///     try {
///         PyObjectContainer container0(Py_BuildValue("I", 0));
///         PyObjectContainer container1(Py_BuildValue("s", cppobj.toText().c_str()));
///         return (Py_BuildValue("OO", container0.get(), container1.get()));
///     } catch { ... set python exception, etc ... } \endcode
///
/// Commonly deployed buggy implementation to achieve this would be like this:
/// \code
///    return (Py_BuildValue("OO", Py_BuildValue("I", 0),
///                          Py_BuildValue("s", cppobj.toText().c_str())));
/// \endcode
/// One clear bug of this code is that references to the element objects of
/// the tuple will leak.
/// (Assuming \c cppobj.toText() can throw) this code is also not exception
/// safe; if \c cppobj.toText() throws the reference to the first object
/// will leak, even if the code tried to do the necessary cleanup in the
/// successful case.
/// Further, this code naively passes the result of the first two calls to
/// \c Py_BuildValue() to the third one even if they can be NULL.
/// In this specific case, it happens to be okay because \c Py_BuildValue()
/// accepts NULL and treats it as an indication of error.  But not all
/// python C library works that way (remember, the API is so inconsistent)
/// and we need to refer to the API manual every time we have to worry about
/// passing a NULL object to a library function.  We'd certainly like to
/// avoid such development overhead.  The code using \c PyObjectContainer
/// addresses all these problems.
///
/// Examples 2: Install a (constant) variable to a class.
///
/// \code
///    try {
///        // installClassVariable is a wrapper of
///        // PyObjectContainer::installAsClassVariable.  See below.
///        installClassVariable(myclass_type, "SOME_CONSTANT",
///                             Py_BuildValue("I", 0));
///    } catch { ... }
/// \endcode
///
/// Examples 3: Install a custom exception to a module.
///
/// \code
///    PyObject* new_exception; // publicly visible
///    ...
///    try {
///        new_exception = PyErr_NewException("mymodule.NewException",
///                                           NULL, NULL);
///        PyObjectContainer(new_exception).installToModule(mymodule,
///                                                         "NewException");
///    } catch { ... }
/// \endcode
///
/// Note that \c installToModule() keeps the reference to \c new_exception
/// by default.  This is a common practice when we introduce a custom
/// exception in a python biding written in C/C++.  See the code comment
/// of the method for more details.
struct PyObjectContainer {
    PyObjectContainer() : obj_(NULL) {}
    PyObjectContainer(PyObject* obj) : obj_(obj) {
        if (obj_ == NULL) {
            isc_throw(PyCPPWrapperException, "Unexpected NULL PyObject, "
                      "probably due to short memory");
        }
    }
    ~PyObjectContainer() {
        if (obj_ != NULL) {
            Py_DECREF(obj_);
        }
    }
    void reset(PyObject* obj) {
        if (obj == NULL) {
            isc_throw(PyCPPWrapperException, "Unexpected NULL PyObject, "
                      "probably due to short memory");
        }
        if (obj_ != NULL) {
            Py_DECREF(obj_);
        }
        obj_ = obj;
    }
    PyObject* get() {
        return (obj_);
    }
    PyObject* release() {
        PyObject* ret = obj_;
        obj_ = NULL;
        return (ret);
    }

    // Install the enclosed PyObject to the specified python class 'pyclass'
    // as a variable named 'name'.
    void installAsClassVariable(PyTypeObject& pyclass, const char* name) {
        if (PyDict_SetItemString(pyclass.tp_dict, name, obj_) < 0) {
            isc_throw(PyCPPWrapperException, "Failed to set a class variable, "
                      "probably due to short memory");
        }
        // Ownership successfully transferred to the class object.  We'll let
        // it be released in the destructor.
    }

    // Install the enclosed PyObject to the specified module 'mod' as an
    // object named 'name'.
    // By default, this method explicitly keeps the reference to the object
    // even after the module "steals" it.  To cancel this behavior and give
    // the reference to the module completely, the third parameter 'keep_ref'
    // should be set to false.
    void installToModule(PyObject* mod, const char* name,
                         bool keep_ref = true)
    {
        if (PyModule_AddObject(mod, name, obj_) < 0) {
            isc_throw(PyCPPWrapperException, "Failed to add an object to "
                      "module, probably due to short memory");
        }
        // PyModule_AddObject has "stolen" the reference, so unless we
        // have to retain it ourselves we don't (shouldn't) decrease it.
        // However, we actually often need to keep our own reference because
        // objects added to a module are often referenced via non local
        // C/C++ variables in various places of the C/C++ code.  In order
        // for the code to run safely even if some buggy/evil python program
        // performs 'del mod.obj', we need the extra reference.  See, e.g.:
        // http://docs.python.org/py3k/c-api/init.html#Py_Initialize
        // http://mail.python.org/pipermail/python-dev/2005-June/054238.html
        if (keep_ref) {
            Py_INCREF(obj_);
        }
        obj_ = NULL;
    }

protected:
    PyObject* obj_;
};

/// This templated class is a derived class of \c PyObjectContainer and
/// manages C++-class based python objects.
///
/// The template parameter \c PYSTRUCT must be a derived class (structure) of
/// \c PyObject that has a member variable named \c cppobj, which must be a
/// a pointer to \c CPPCLASS (the second template parameter).
///
/// For example, to define a custom python class based on a C++ class, MyClass,
/// we'd define a class (struct) named \c s_MyClass like this:
/// \code
///    class s_MyClass : public PyObject {
///    public:
///       s_MyClass() : cppobj(NULL) {}
///       MyClass* cppobj;
///    };
/// \endcode
///
/// And, to build and return a python version of MyClass object, write the
/// following C++ code:
/// \code
///    typedef CPPPyObjectContainer<s_MyClass, MyClass> MyContainer;
///    try {
///        // below, myclass_type is of \c PyTypeObject that defines
///        // a python class (type) for MyClass
///        MyContainer container(PyObject_New(s_MyClass, myclass_type));
///        container.set(new MyClass());
///        return (container.release()); // give the reference to the caller
///    } catch { ... }
/// \endcode
///
/// This code prevents bugs like NULL pointer dereference when \c PyObject_New
/// fails or resource leaks when new'ing \c MyClass results in an exception.
/// Note that we use \c release() (derived from the base class) instead of
/// \c get(); in this case we should simply pass the reference generated in
/// \c PyObject_New() to the caller.
template <typename PYSTRUCT, typename CPPCLASS>
struct CPPPyObjectContainer : public PyObjectContainer {
    explicit CPPPyObjectContainer(PYSTRUCT* obj) : PyObjectContainer(obj) {}

    // This method associates a C++ object with the corresponding python
    // object enclosed in this class.
    void set(CPPCLASS* value) {
        if (value == NULL) {
            isc_throw(PyCPPWrapperException, "Unexpected NULL C++ object, "
                      "probably due to short memory");
        }
        static_cast<PYSTRUCT*>(obj_)->cppobj = value;
    }

    // This is a convenience short cut to associate a C++ object with the
    // python object and install it to the specified python class \c pyclass
    // as a variable named \c name.
    void installAsClassVariable(PyTypeObject& pyclass, const char* name,
                                CPPCLASS* value)
    {
        set(value);
        PyObjectContainer::installAsClassVariable(pyclass, name);
    }
};

/// A shortcut function to install a python class variable.
///
/// It installs a python object \c obj to a specified class \c pyclass
/// as a variable named \c name.
inline void
installClassVariable(PyTypeObject& pyclass, const char* name, PyObject* obj) {
    PyObjectContainer(obj).installAsClassVariable(pyclass, name);
}

} // namespace python
} // namespace util
} // namespace isc
#endif // PYCPPWRAPPER_UTIL_H

// Local Variables:
// mode: c++
// End:
