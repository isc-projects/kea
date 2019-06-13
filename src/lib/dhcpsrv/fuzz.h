// Copyright (C) 2016  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FUZZ_H
#define FUZZ_H

#ifdef ENABLE_AFL

#include <exceptions/exceptions.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <sys/socket.h>
#include <unistd.h>

#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

namespace isc {

/// @brief Helper class to manage synchronization between fuzzing threads
///
/// This contains the variables and encapsulates the primitives required
/// to manage the condition variables between the two threads.

class FuzzSync {
public:
    /// @brief Constructor
    ///
    /// Just set the name of the variable for debug message purposes.
    ///
    /// @param name The name of the object, output in debug messages.
    FuzzSync(const char* name);

    /// @brief Waits for condition notification
    ///
    /// Called by a thread, this function will wait for another thread to
    /// notify it that it can proceed: in other words, this function calls
    /// <condition_variable>.wait() and waits for the other to call
    /// <condition_variable>.notify().
    ///
    /// As it is possible to miss a notification - if one thread reaches the
    /// notification point before the other thread reaches the wait point -
    /// the operation is mediated by a predicate (in this case, a boolean
    /// variable).  If this is set when the waiting thread reaches the wait
    /// point, the thread does not wait.  If it is not set, the thread will
    /// wait until it is notified through the condition variable.  At this
    /// point, if the variable is still not set, the thread will re-enter the
    /// wait state.
    ///
    /// In both cases, the predicate variable is cleared on exit.
    void wait(void);

    /// @brief Notifies other thread to continue
    ///
    /// Called by a thread, this function will notify another thread that is
    /// waiting on the condition variable that it can continue.  As noted
    /// in the documentation for wait(), the operation is mediated by a
    /// predicate variable; in this case, the variable is explicitly set
    /// before the notification is sent.
    void notify(void);

private:
    std::condition_variable cond_;
    std::mutex              mutex_;
    volatile bool           ready_;
    std::string             name_;
};
    

/// @brief AFL Fuzzing Functions

class Fuzz {
public:
    /// @brief Constructor
    ///
    /// Initializes member variables.
    Fuzz();

    /// @brief Constructor
    ///
    /// Initializes fuzzing object and starts the fuzzing thread.
    ///
    /// @param ipversion Either 4 or 6 depending on what IP version the
    ///                  server responds to.
    /// @param shutdown Pointer to boolean flag that will be set to true to
    ///                 trigger the shutdown procedure.
    Fuzz(int ipversion, volatile bool* shutdown);

    /// @brief Destructor
    ///
    /// Does some basic checks when going out of scope.  The purpose of these
    /// checks is to aid diagnosis in the event of problems with the fuzzing.
    ~Fuzz();

    /// @brief Main Kea Fuzzing Function
    ///
    /// This is the main Kea fuzzing method.  It is the entry point for the
    /// thread that handles the interface between AFL and Kea.  The method
    /// receives data from the fuzzing engine via stdin, and then sends it to
    /// the configured UDP socket.  The main thread of Kea reads it from there,
    /// processes it and when processing is complete, calls the
    /// packetProcessed() method to notify the fuzzing thread that processing
    /// of the packet is complete.
    ///
    /// After a given number of packets, this method will set the flag shut
    /// down Kea.  This is recommended by the AFL documentation as it avoids
    /// any resource leaks (which are not caught by AFL) from getting too large
    /// and interfering with the fuzzing.  AFL will automatically restart the
    /// program to continue fuzzing.
    void run(void);

    /// @brief Notify fuzzing thread that processing is complete
    ///
    /// This function is called by the Kea processing loop running in the main
    /// thread when it has finished processing a packet.  It raises a SIGSTOP
    /// signal, which tells the AFL fuzzer that processing for the data it has
    /// just sent has finished; this causes it to send another fuzzed packet
    /// to stdin. It also sets a condition variable, so releasing the fuzzing
    /// thread to read the next data from AFL.
    ///
    /// If a shutdown has been initiated, this method waits for the fuzzing
    /// thread to exit before allowing the shutdown to continue.
    void packetProcessed(void);

    /// @brief Populate address structures
    ///
    /// Decodes the environment variables used to pass address/port information
    /// to the program and sets up the appropriate address structures.
    ///
    /// @param ipversion Either 4 or 6 depending on which IP version address
    ///                  is expected.
    ///
    /// @throws FuzzInitFail Thrown if the address is not in the expected
    ///                      format.
    void setAddress(int ipversion);

    /// @brief size of the buffer used to transfer data between AFL and Kea.
    static constexpr size_t BUFFER_SIZE = 65536;

    /// @brief Delay before rereading if read from stdin returns an error (us)
    static constexpr  useconds_t SLEEP_INTERVAL = 50000;

    /// @brief Number of many packets Kea will process until shutting down.
    ///
    /// After the shutdown, AFL will restart it. This safety switch is here for
    /// eliminating cases where Kea goes into a weird state and stops
    /// processing packets properly.
    static constexpr long LOOP_COUNT = 1000;

    // Condition/mutex variables.  The fuzz_XX_ variables are set by the
    // fuzzing thread and waited on by the main thread.  The main_XX_ variables
    // are set by the main thread and waited on by the fuzzing thread.
    FuzzSync            fuzz_sync_;     // Set by fuzzing thread
    FuzzSync            main_sync_;     // Set by main thread

    // Other member variables.
    const char*         address_;       //< Pointer to address string
    std::thread         fuzzing_thread_;//< Holds the thread ID
    const char*         interface_;     //< Pointer to interface string
    long                loop_max_;      //< Maximum number of loop iterations
    uint16_t            port_;          //< Port number to use
    volatile bool       running_;       //< Set if the thread is running
    struct sockaddr*    sockaddr_ptr;   //< Pointer to structure used
    size_t              sockaddr_len;   //< Length of the structure
    struct sockaddr_in  servaddr4_;     //< IPv6 address information
    struct sockaddr_in6 servaddr6_;     //< IPv6 address information
    volatile bool*      shutdown_ptr_;  //< Pointer to shutdown flag
};


/// @brief Exception thrown if fuzzing initialization fails.
class FuzzInitFail : public Exception {
public:
    FuzzInitFail(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

}

#endif // ENABLE_AFL

#endif // FUZZ_H
