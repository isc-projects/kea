// Copyright (C) 2016  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FUZZ_H
#define FUZZ_H

#include <exceptions/exceptions.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <sys/socket.h>
#include <unistd.h>

#include <mutex>
#include <condition_variable>
#include <thread>

namespace isc {

/// @brief AFL Fuzzing Functions

class Fuzz {
public:
    /// @brief Initializes Kea fuzzing
    ///
    /// This takes one parameter, which is a pointer to the shutdown flag,
    /// Dhcp6Srv::shutdown_. Kea runs until something sets this flag to true,
    /// which is an indication to shutdown Kea.
    ///
    /// In the case of fuzzing, the shutdown flag is set when a fixed number of
    /// packets has been received from the fuzzer.  At this point, the fuzzer
    /// shutdow down Kea and restarts it.
    ///
    /// @param shutdown Pointer to boolean flag that will be set to true to
    ///        trigger the shutdown procedure.
    static void init(volatile bool* shutdown);

    /// @brief Main Kea Fuzzing Function
    ///
    /// This is the main Kea fuzzing function.  It is the entry point for the
    /// thread that handles the interface between AFL and Kea.  The function
    /// receives data from the fuzzing engine via stdin, and then sends it to
    /// the configured UDP socket.  Kea reads it from there, processes it and
    /// when processing is complete, calls the notification function.
    ///
    /// After a given number of packets, this function will shut down Kea.  This
    /// is recommended by AFL as it avoids any resource leaks (which are not
    /// caught by AFL) from getting too large and interfering with the fuzzing.
    ///  AFL will automatically restart the program to continue fuzzing.
    ///
    /// Since this runs in a separate thread, errors are logged via the fuzzing
    /// logger. (Other than initialization - when the thread is not running -
    /// this is the only use of the fuzzing logger.) If the error is fatal, the
    /// thread will terminate, something that may cause the fuzzer to hang.
    static void run(void);

    /// @brief Notify fuzzing thread that processing is complete
    ///
    /// This function is called by the main Kea processing loop when it has
    /// finished processing a packet.  It raises a SIGSTOP signal, which tells
    /// the AFL fuzzer that processing for the data it has just sent has
    /// finished; this causes it to send another fuzzed packet to stdin. It
    /// also sets a condition variable, so releasing the fuzzing thread to
    /// read the next data from AFL.
    static void notify(void);

    /// @brief Wait for fuzzing thread to exit
    ///
    /// A short function, called after the fuzzing thread is supposed to have
    /// finished, to ensure that it really has finished.
    static void wait(void);

    /// @brief size of the buffer used to transfer data between AFL and Kea.
    static constexpr size_t BUFFER_SIZE = 65536;

    // @brief Delay before rereading if read from stdin returns an error (us)
    static constexpr  useconds_t SLEEP_INTERVAL = 50000;

    /// @brief Number of many packets Kea will process until shutting down.
    ///
    /// After the shutdown, AFL ill restart it. This safety switch is here for
    ///  eliminating cases where Kea goes into a weird state and stops
    ///  processing packets properly.
    static constexpr long LOOP_COUNT = 1000;

    // Condition/mutext variables.  The fuzz_XX_ variables are set by the
    // fuzzing thread and waited on by the main thread.  The main_XX_ variables
    // are set by the main thread and waited on by the fuzzing thread.
    static std::condition_variable  fuzz_cond_;     //< Set by fuzzing thread
    static std::mutex               fuzz_mutex_;    //< Set by fuzzing thread
    static std::condition_variable  main_cond_;     //< Set by main thread
    static std::mutex               main_mutex_;    //< Set by main thread

    // The next two variables are used in the condition variables test.  fuzz_ready_
    // i set by the fuzzing thread and cleared by the main thread.  main_ready_
    // is set by the main thread and cleared by the fuzzing thread.
    static volatile bool            fuzz_ready_;    //< Set when data has been read from fuzzer
    static volatile bool            main_ready_;    //< Set when data has been read from fuzzer

    // Other member variables.
    static std::thread              fuzzing_thread_;//< Holds the thread ID
    static struct sockaddr_in6      servaddr_;      //< For sending data to main thread
    static volatile bool*           shutdown_ptr_;  //< Pointer to shutdown flag
};


/// @brief Exception thrown if fuzzing initialization fails.
class FuzzInitFail : public Exception {
public:
    FuzzInitFail(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

}

#endif // FUZZ_H
