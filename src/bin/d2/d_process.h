// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef D_PROCESS_H
#define D_PROCESS_H

#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

typedef boost::shared_ptr<isc::asiolink::IOService> IOServicePtr;

namespace isc {
namespace d2 {

/// @brief Exception thrown if the process encountered an operational error.
class DProcessBaseError : public isc::Exception {
public:
    DProcessBaseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Application Process Interface
///
/// DProcessBase is an abstract class represents the primary "application" 
/// level object in a "managed" asynchronous application. It provides a uniform 
/// interface such that a managing layer can construct, intialize, and start
/// the application's event loop.  The event processing is centered around the
/// use of isc::asiolink::io_service. The io_service is shared between the 
/// the managing layer and the DProcessBase.  This allows management layer IO 
/// such as directives to be sensed and handled, as well as processing IO 
/// activity specific to the application.  In terms of management layer IO,
/// there are methods shutdown, configuration updates, and commands unique
/// to the application.  
class DProcessBase {
public:
    /// @brief Constructor
    ///
    /// @param name name is a text label for the process. Generally used
    /// in log statements, but otherwise arbitrary. 
    /// @param io_service is the io_service used by the caller for
    /// asynchronous event handling.
    ///
    /// @throw DProcessBaseError is io_service is NULL. 
    DProcessBase(const char* name, IOServicePtr io_service) : name_(name),
        io_service_(io_service), shut_down_flag(false) {

        if (!io_service_) {
            isc_throw (DProcessBaseError, "IO Service cannot be null");
        }
    };

    /// @brief May be used after instantiation to perform initialization unique
    /// to application. It must be invoked prior to invoking run. This would 
    /// likely include the creation of additional IO sources and their 
    /// integration into the io_service. 
    virtual void init() = 0; 

    /// @brief Implements the process's event loop. In its simplest form it 
    /// would an invocation io_service_->run().  This method should not exit 
    /// until the process itself is exiting due to a request to shutdown or 
    /// some anomaly is forcing an exit.   
    /// @return  returns EXIT_SUCCESS upon a successful, normal termination, 
    /// and EXIT_FAILURE to indicate an abnormal termination.    
    virtual int run() = 0; 

    /// @brief Implements the process's shutdown processing. When invoked, it 
    /// should ensure that the process gracefully exits the run method. 
    virtual int shutdown() = 0;

    /// @brief Processes the given configuration. 
    /// 
    /// This method may be called multiple times during the process lifetime.
    /// Certainly once during process startup, and possibly later if the user
    /// alters configuration. This method must not throw, it should catch any
    /// processing errors and return a success or failure answer as described
    /// below. 
    ///
    /// @param config_set a new configuration (JSON) for the process
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome. 
    virtual isc::data::ConstElementPtr configure(isc::data::ConstElementPtr
                                                 config_set) = 0; 

    /// @brief Processes the given command. 
    /// 
    /// This method is called to execute any custom commands supported by the 
    /// process. This method must not throw, it should catch any processing 
    /// errors and return a success or failure answer as described below.
    ///
    /// @param command is a string label representing the command to execute.
    /// @param args is a set of arguments (if any) required for the given
    /// command. 
    /// @return an Element that contains the results of command composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.  
    virtual isc::data::ConstElementPtr command(
            const std::string& command, isc::data::ConstElementPtr args) = 0; 

    /// @brief Destructor 
    virtual ~DProcessBase(){};

    bool shouldShutDown() { 
        return shut_down_flag; 
    }

    void setShutdownFlag(bool value) { 
        shut_down_flag = value; 
    }

    const std::string& getName() {
        return (name_);
    }

    IOServicePtr& getIoService() {
        return (io_service_);
    }

private:
    /// @brief Text label for the process. Generally used in log statements, 
    /// but otherwise can be arbitrary. 
    std::string name_;

    /// @brief The IOService to be used for asynchronous event handling. 
    IOServicePtr io_service_;

    /// @brief Boolean flag set when shutdown has been requested.
    bool shut_down_flag;
};

/// @brief Defines a shared pointer to DProcessBase.
typedef boost::shared_ptr<DProcessBase> DProcessBasePtr;

}; // namespace isc::d2 
}; // namespace isc

#endif
