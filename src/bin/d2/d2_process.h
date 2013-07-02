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

#ifndef D2_PROCESS_H
#define D2_PROCESS_H

#include <d2/d_process.h>

namespace isc {
namespace d2 {

/// @brief DHCP-DDNS Application Process
///
/// D2Process provides the top level application logic for DHCP-driven DDNS
/// update processing.  It provides the asynchronous event processing required
/// to receive DNS mapping change requests and carry them out.
/// It implements the DProcessBase interface, which structures it such that it
/// is a managed "application", controlled by a management layer.

class D2Process : public DProcessBase {
public:
    /// @brief Constructor
    ///
    /// @param name name is a text label for the process. Generally used
    /// in log statements, but otherwise arbitrary.
    /// @param io_service is the io_service used by the caller for
    /// asynchronous event handling.
    ///
    /// @throw DProcessBaseError is io_service is NULL.
    D2Process(const char* name, IOServicePtr io_service);

    /// @brief Will be used after instantiation to perform initialization
    /// unique to D2. @todo This will likely include interactions with
    /// QueueMgr and UpdateMgr, to prepare for request receipt and processing.
    /// Current implementation successfully does nothing.
    /// @throw throws a DProcessBaseError if the initialization fails.
    virtual void init();

    /// @brief Implements the process's event loop.
    /// The initial implementation is quite basic, surrounding calls to
    /// io_service->runOne() with a test of the shutdown flag.
    /// Once invoked, the method will continue until the process itself is
    /// exiting due to a request to shutdown or some anomaly forces an exit.
    /// @throw throws a DProcessBaseError if an error is encountered.
    virtual void run();

    /// @brief Implements the process's shutdown processing. When invoked, it
    /// should ensure that the process gracefully exits the run method.
    /// Current implementation simply sets the shutdown flag monitored by the
    /// run method. @todo this may need to expand as the implementation evolves.
    /// @throw throws a DProcessBaseError if an error is encountered.
    virtual void shutdown();

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
                                                 config_set);

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
    virtual isc::data::ConstElementPtr command(const std::string& command,
                                               isc::data::ConstElementPtr args);
    /// @brief Destructor
    virtual ~D2Process();
};

}; // namespace isc::d2
}; // namespace isc

#endif
