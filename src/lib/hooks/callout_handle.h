// Copyright (C) 2013,2015  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CALLOUT_HANDLE_H
#define CALLOUT_HANDLE_H

#include <exceptions/exceptions.h>
#include <hooks/library_handle.h>

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace hooks {

class ServerHooks;

/// @brief No such argument
///
/// Thrown if an attempt is made access an argument that does not exist.

class NoSuchArgument : public Exception {
public:
    NoSuchArgument(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief No such callout context item
///
/// Thrown if an attempt is made to get an item of data from this callout's
/// context and either the context or an item in the context with that name
/// does not exist.

class NoSuchCalloutContext : public Exception {
public:
    NoSuchCalloutContext(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

// Forward declaration of the library handle and related collection classes.

class CalloutManager;
class LibraryHandle;
class LibraryManagerCollection;

/// @brief Per-packet callout handle
///
/// An object of this class is associated with every packet (or request)
/// processed by the server.  It forms the principle means of passing data
/// between the server and the user-library callouts.
///
/// The class allows access to the following information:
///
/// - Arguments.  When the callouts associated with a hook are called, they
///   are passed information by the server (and can return information to it)
///   through name/value pairs.  Each of these pairs is an argument and the
///   information is accessed through the {get,set}Argument() methods.
///
/// - Per-packet context.  Each packet has a context associated with it, this
///   context being  on a per-library basis.  In other words, As a packet passes
///   through the callouts associated with a given library, the callouts can
///   associate and retrieve information with the packet.  The per-library
///   nature of the context means that the callouts within a given library can
///   pass packet-specific information between one another, but they cannot pass
///   information to callous within another library.  Typically such context
///   is created in the "context_create" callout and destroyed in the
///   "context_destroy" callout.  The information is accessed through the
///   {get,set}Context() methods.
///
/// - Per-library handle (LibraryHandle). The library handle allows the
///   callout to dynamically register and deregister callouts. In the latter
///   case, only functions registered by functions in the same library as the
///   callout doing the deregistration can be removed: callouts registered by
///   other libraries cannot be modified.

class CalloutHandle {
public:

    /// @brief Specifies allowed next steps
    ///
    /// Those values are used to designate the next step in packet processing.
    /// They are set by hook callouts and read by the Kea server. See
    /// @ref setStatus for detailed description of each value.
    enum CalloutNextStep {
        NEXT_STEP_CONTINUE = 0, ///< continue normally
        NEXT_STEP_SKIP = 1,     ///< skip the next processing step
        NEXT_STEP_DROP = 2      ///< drop the packet
    };


    /// Typedef to allow abbreviation of iterator specification in methods.
    /// The std::string is the argument name and the "boost::any" is the
    /// corresponding value associated with it.
    typedef std::map<std::string, boost::any> ElementCollection;

    /// Typedef to allow abbreviations in specifications when accessing
    /// context.  The ElementCollection is the name/value collection for
    /// a particular context.  The "int" corresponds to the index of an
    /// associated library - there is a 1:1 correspondence between libraries
    /// and a name.value collection.
    ///
    /// The collection of contexts is stored in a map, as not every library
    /// will require creation of a context associated with each packet.  In
    /// addition, the structure is more flexible in that the size does not
    /// need to be set when the CalloutHandle is constructed.
    typedef std::map<int, ElementCollection> ContextCollection;

    /// @brief Constructor
    ///
    /// Creates the object and calls the callouts on the "context_create"
    /// hook.
    ///
    /// Of the two arguments passed, only the pointer to the callout manager is
    /// actively used.  The second argument, the pointer to the library manager
    /// collection, is used for lifetime control: after use, the callout handle
    /// may contain pointers to memory allocated by the loaded libraries.  The
    /// used of a shared pointer to the collection of library managers means
    /// that the libraries that could have allocated memory in a callout handle
    /// will not be unloaded until all such handles have been destroyed.  This
    /// issue is discussed in more detail in the documentation for
    /// isc::hooks::LibraryManager.
    ///
    /// @param manager Pointer to the callout manager object.
    /// @param lmcoll Pointer to the library manager collection.  This has a
    ///        null default for testing purposes.
    CalloutHandle(const boost::shared_ptr<CalloutManager>& manager,
                  const boost::shared_ptr<LibraryManagerCollection>& lmcoll =
                        boost::shared_ptr<LibraryManagerCollection>());

    /// @brief Destructor
    ///
    /// Calls the context_destroy callback to release any per-packet context.
    /// It also clears stored data to avoid problems during member destruction.
    ~CalloutHandle();

    /// @brief Set argument
    ///
    /// Sets the value of an argument.  The argument is created if it does not
    /// already exist.
    ///
    /// @param name Name of the argument.
    /// @param value Value to set.  That can be of any data type.
    template <typename T>
    void setArgument(const std::string& name, T value) {
        arguments_[name] = value;
    }

    /// @brief Get argument
    ///
    /// Gets the value of an argument.
    ///
    /// @param name Name of the element in the argument list to get.
    /// @param value [out] Value to set.  The type of "value" is important:
    ///        it must match the type of the value set.
    ///
    /// @throw NoSuchArgument No argument with the given name is present.
    /// @throw boost::bad_any_cast An argument with the given name is present,
    ///        but the data type of the value is not the same as the type of
    ///        the variable provided to receive the value.
    template <typename T>
    void getArgument(const std::string& name, T& value) const {
        ElementCollection::const_iterator element_ptr = arguments_.find(name);
        if (element_ptr == arguments_.end()) {
            isc_throw(NoSuchArgument, "unable to find argument with name " <<
                      name);
        }

        value = boost::any_cast<T>(element_ptr->second);
    }

    /// @brief Get argument names
    ///
    /// Returns a vector holding the names of arguments in the argument
    /// vector.
    ///
    /// @return Vector of strings reflecting argument names.
    std::vector<std::string> getArgumentNames() const;

    /// @brief Delete argument
    ///
    /// Deletes an argument of the given name.  If an argument of that name
    /// does not exist, the method is a no-op.
    ///
    /// N.B. If the element is a raw pointer, the pointed-to data is NOT deleted
    /// by this method.
    ///
    /// @param name Name of the element in the argument list to set.
    void deleteArgument(const std::string& name) {
        static_cast<void>(arguments_.erase(name));
    }

    /// @brief Delete all arguments
    ///
    /// Deletes all arguments associated with this context.
    ///
    /// N.B. If any elements are raw pointers, the pointed-to data is NOT
    /// deleted by this method.
    void deleteAllArguments() {
        arguments_.clear();
    }

    /// @brief Sets the next processing step.
    ///
    /// This method is used by the callouts to determine the next step
    /// in processing. This method replaces former setSkip() method
    /// that allowed only two values.
    ///
    /// Currently there are three possible value allowed:
    /// NEXT_STEP_CONTINUE - tells the server to continue processing as usual
    ///                      (equivalent of previous setSkip(false) )
    ///
    /// NEXT_STEP_SKIP - tells the server to skip the processing. Exact meaning
    ///                  is hook specific. See hook documentation for details.
    ///                  (equivalent of previous setSkip(true))
    ///
    /// NEXT_STEP_DROP - tells the server to unconditionally drop the packet
    ///                  and do not process it further.
    ///
    /// This variable is interrogated by the server to see if the remaining
    /// callouts associated with the current hook should be bypassed.
    ///
    /// @param skip New value of the "skip" flag.
    void setStatus(const CalloutNextStep next) {
        next_step_ = next;
    }

    /// @brief Returns the next processing step.
    ///
    /// Gets the current value of the next step. See @ref setStatus for detailed
    /// definition.
    ///
    /// @return Current value of the skip flag.
    CalloutNextStep getStatus() const {
        return (next_step_);
    }

    /// @brief Access current library handle
    ///
    /// Returns a reference to the current library handle.  This function is
    /// only available when called by a callout (which in turn is called
    /// through the "callCallouts" method), as it is only then that the current
    /// library index is valid.  A callout uses the library handle to
    /// dynamically register or deregister callouts.
    ///
    /// @return Reference to the library handle.
    ///
    /// @throw InvalidIndex thrown if this method is called when the current
    ///        library index is invalid (typically if it is called outside of
    ///        the active callout).
    LibraryHandle& getLibraryHandle() const;

    /// @brief Set context
    ///
    /// Sets an element in the context associated with the current library.  If
    /// an element of the name is already present, it is replaced.
    ///
    /// @param name Name of the element in the context to set.
    /// @param value Value to set.
    template <typename T>
    void setContext(const std::string& name, T value) {
        getContextForLibrary()[name] = value;
    }

    /// @brief Get context
    ///
    /// Gets an element from the context associated with the current library.
    ///
    /// @param name Name of the element in the context to get.
    /// @param value [out] Value to set.  The type of "value" is important:
    ///        it must match the type of the value set.
    ///
    /// @throw NoSuchCalloutContext Thrown if no context element with the name
    ///        "name" is present.
    /// @throw boost::bad_any_cast Thrown if the context element is present
    ///        but the type of the data is not the same as the type of the
    ///        variable provided to receive its value.
    template <typename T>
    void getContext(const std::string& name, T& value) const {
        const ElementCollection& lib_context = getContextForLibrary();

        ElementCollection::const_iterator element_ptr = lib_context.find(name);
        if (element_ptr == lib_context.end()) {
            isc_throw(NoSuchCalloutContext, "unable to find callout context "
                      "item " << name << " in the context associated with "
                      "current library");
        }

        value = boost::any_cast<T>(element_ptr->second);
    }

    /// @brief Get context names
    ///
    /// Returns a vector holding the names of items in the context associated
    /// with the current library.
    ///
    /// @return Vector of strings reflecting the names of items in the callout
    ///         context associated with the current library.
    std::vector<std::string> getContextNames() const;

    /// @brief Delete context element
    ///
    /// Deletes an item of the given name from the context associated with the
    /// current library.  If an item  of that name does not exist, the method is
    /// a no-op.
    ///
    /// N.B. If the element is a raw pointer, the pointed-to data is NOT deleted
    /// by this.
    ///
    /// @param name Name of the context item to delete.
    void deleteContext(const std::string& name) {
        static_cast<void>(getContextForLibrary().erase(name));
    }

    /// @brief Delete all context items
    ///
    /// Deletes all items from the context associated with the current library.
    ///
    /// N.B. If any elements are raw pointers, the pointed-to data is NOT
    /// deleted by this.
    void deleteAllContext() {
        getContextForLibrary().clear();
    }

    /// @brief Get hook name
    ///
    /// Get the name of the hook to which the current callout is attached.
    /// This can be the null string if the CalloutHandle is being accessed
    /// outside of the CalloutManager's "callCallouts" method.
    ///
    /// @return Name of the current hook or the empty string if none.
    std::string getHookName() const;

private:
    /// @brief Check index
    ///
    /// Gets the current library index, throwing an exception if it is not set
    /// or is invalid for the current library collection.
    ///
    /// @return Current library index, valid for this library collection.
    ///
    /// @throw InvalidIndex current library index is not valid for the library
    ///        handle collection.
    int getLibraryIndex() const;

    /// @brief Return reference to context for current library
    ///
    /// Called by all context-setting functions, this returns a reference to
    /// the callout context for the current library, creating a context if it
    /// does not exist.
    ///
    /// @return Reference to the collection of name/value pairs associated
    ///         with the current library.
    ///
    /// @throw InvalidIndex current library index is not valid for the library
    ///        handle collection.
    ElementCollection& getContextForLibrary();

    /// @brief Return reference to context for current library (const version)
    ///
    /// Called by all context-accessing functions, this a reference to the
    /// callout context for the current library.  An exception is thrown if
    /// it does not exist.
    ///
    /// @return Reference to the collection of name/value pairs associated
    ///         with the current library.
    ///
    /// @throw NoSuchCalloutContext Thrown if there is no ElementCollection
    ///        associated with the current library.
    const ElementCollection& getContextForLibrary() const;

    // Member variables

    /// Pointer to the collection of libraries for which this handle has been
    /// created.
    boost::shared_ptr<LibraryManagerCollection> lm_collection_;

    /// Collection of arguments passed to the callouts
    ElementCollection arguments_;

    /// Context collection - there is one entry per library context.
    ContextCollection context_collection_;

    /// Callout manager.
    boost::shared_ptr<CalloutManager> manager_;

    /// Reference to the singleton ServerHooks object.  See the
    /// @ref hooksmgMaintenanceGuide for information as to why the class holds
    /// a reference instead of accessing the singleton within the code.
    ServerHooks& server_hooks_;

    /// Next processing step, indicating what the server should do next.
    CalloutNextStep next_step_;
};

/// A shared pointer to a CalloutHandle object.
typedef boost::shared_ptr<CalloutHandle> CalloutHandlePtr;

} // namespace hooks
} // namespace isc


#endif // CALLOUT_HANDLE_H
