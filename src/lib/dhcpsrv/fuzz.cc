// Copyright (C) 2016  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#ifdef ENABLE_AFL

#ifndef __AFL_LOOP
#error To use American Fuzzy Lop you have to set CXX to afl-clang-fast++
#endif

#include <dhcp/dhcp6.h>
#include <dhcpsrv/fuzz.h>
#include <dhcpsrv/fuzz_log.h>

#include <boost/lexical_cast.hpp>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace isc;
using namespace isc::dhcp;
using namespace std;

// Constants defined in the class definition
constexpr size_t        Fuzz::BUFFER_SIZE;
constexpr useconds_t    Fuzz::SLEEP_INTERVAL;
constexpr long          Fuzz::LOOP_COUNT;

// Variables needed to synchronize between main and fuzzing threads.
condition_variable      Fuzz::sync_cond_;
mutex                   Fuzz::sync_mutex_;
thread                  Fuzz::fuzz_thread_;

// Address structure used to send data to address/port on which Kea listens
struct sockaddr_in6     Fuzz::servaddr_;

// Pointer to the shutdown flag used by Kea.  The fuzzing code will set this
// after the appropriate number of packets have been fuzzed.
volatile bool*          Fuzz::shutdown_ptr_ = NULL;

// Flag to state that the 



// Fuzzer initialization: create the thread artifacts and start the
// main thread.
void
Fuzz::init(volatile bool* shutdown_flag) {
    try {
        stringstream reason;

        // Store reference to shutdown flag.  When the fuzzing loop has read
        // the set number of packets from kea, it will set this flag to trigger
        // a Kea shutdown.
        if (shutdown_flag) {
            shutdown_ptr_ = shutdown_flag;
        } else {
            isc_throw(FuzzInitFail, "must pass shutdown flag to kea_fuzz_init");
        }

        // Get the environment for the fuzzing.  First the interface to use.
        const char *iface_ptr = getenv("KEA_AFL_INTERFACE");
        if (! iface_ptr) {
            isc_throw(FuzzInitFail, "no fuzzing interface has been set");
        }

        unsigned int iface_id = if_nametoindex(iface_ptr);
        if (iface_id == 0) {
            reason << "error retrieving interface ID for "
                   << iface_ptr << ": " << strerror(errno);
            isc_throw(FuzzInitFail, reason.str());
        }

        // Now the address.
        const char *address_ptr = getenv("KEA_AFL_ADDRESS");
        if (address_ptr == 0) {
            isc_throw(FuzzInitFail, "no fuzzing address has been set");
        }

        // ... and the port.
        unsigned short port = 0;
        const char *port_ptr = getenv("KEA_AFL_PORT");
        if (port_ptr == 0) {
            isc_throw(FuzzInitFail, "no fuzzing port has been set");
        }
        try {
            port = boost::lexical_cast<uint16_t>(port_ptr);
        } catch (const boost::bad_lexical_cast&) {
            reason << "cannot convert port number specification "
                   << port_ptr << " to an integer";
            isc_throw(FuzzInitFail, reason.str());
        }

        // Set up the IPv6 address structure.
        memset(&servaddr_, 0, sizeof (servaddr_));
        servaddr_.sin6_family = AF_INET6;
        if (inet_pton(AF_INET6, address_ptr, &servaddr_.sin6_addr) != 1) {
            reason << "inet_pton() failed: can't convert "
                   << address_ptr << " to an IPv6 address" << endl;
            isc_throw(FuzzInitFail, reason.str());
        }
        servaddr_.sin6_port = htons(port);
        servaddr_.sin6_scope_id = iface_id;

        // Initialization complete.
        LOG_INFO(fuzz_logger, FUZZ_INTERFACE)
                 .arg(iface_ptr).arg(address_ptr).arg(port);

        // Start the thread that reads the packets sent by AFL from stdin and
        // passes them to the port on which Kea is listening.
        fuzz_thread_ = std::thread(Fuzz::main);

    } catch (const FuzzInitFail& e) {
        // AFL tends to make it difficult to find out what exactly has failed:
        // make sure that the error is logged.
        LOG_ERROR(fuzz_logger, FUZZ_INIT_FAIL).arg(e.what());
        throw;
    }
}

// This is the main fuzzing function. It receives data from fuzzing engine.
// That data is received to stdin and then sent over the configured UDP socket.
// Then it wait for a conditional, which is called in kea_fuzz_notify() from
// Kea main loop.
void
Fuzz::main(void) {
    // Create the socket throw which packets read from stdin will be send
    // to the port on which Kea is listening.
    int sockfd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        LOG_FATAL(fuzz_logger, FUZZ_SOCKET_CREATE_FAIL).arg(strerror(errno));
        return;
    }

    // Main loop.  This runs for a fixed number of iterations, after which
    // Kea will be terminated and AFL will restart it.  The counting of loop
    // iterations is done here with a separate variable (instead of inside
    // inside the read loop in the server process using __AFL_LOOP) to ensure
    // that thread running this function shutdown down between each restart
    // of the fuzzing process.
    auto loop = Fuzz::LOOP_COUNT;
    while (loop-- > 0) {

        // Read from stdin and continue reading (albeit after a pause) even
        // if there is an error.  Do the same with end of files although, as
        // the fuzzer generates them in normal operation, don't log them.
        char buf[BUFFER_SIZE];
        ssize_t length = read(0, buf, sizeof(buf));
        if (length <= 0) {
            LOG_ERROR(fuzz_logger, FUZZ_READ_FAIL).arg(strerror(errno));
            usleep(SLEEP_INTERVAL);
            continue;
        }
        LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_DATA_READ)
                  .arg(length);

        // Now send the data to the socket.  This will be picked up by the main
        // loop and acted upon, after which kea_fuzz_notify will be called.
        //
        // The condition variables synchronize the operation: this thread
        // will read from stdin and write to the socket.  It then blocks until
        // the main thread has processed the packet, at which point it can read
        // more data from stdin.
        //
        // Since the read() and sendto() calls are blocking, one would think
        // that the two threads would synchronize even without locks.  However,
        // the problem seems to arise in the generation of SIGSTOP and the
        // tying it to a particular packet set to Kea by the fuzzer.  But this
        // is speculation: the fact is that without the synchronization, the
        // code doesn't work.

        // Block the completion function until the data has been sent:
        unique_lock<std::mutex> lock(sync_mutex_);

        // Send the data to the main Kea thread.
        ssize_t sent = sendto(sockfd, buf, length, 0,
                          (struct sockaddr *) &servaddr_, sizeof(servaddr_));
        if (sent < 0) {
            LOG_ERROR(fuzz_logger, FUZZ_SEND_ERROR).arg(strerror(errno));
        } else if (sent != length) {
            LOG_WARN(fuzz_logger, FUZZ_SHORT_SEND).arg(length).arg(sent);
        } else {
            LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_SEND).arg(sent);
        }

        // If this is the last loop iteration, set the shutdown flag.  This
        // is done under the protection of the mutex to avoid the following
        // scenario:
        // 
        // a) This loop reaches its last iteration, then waits for
        //    notify() to complete.
        // b) notify() completes and returns.  The main processing loop checks
        //    the shutdown flag and finds that it is not set.  It enters the
        //    next iteration of the loop and waits to read something from the
        //    configured interface.
        // c) This thread resumes execution, sets the shutdown flag and exits.
        //
        // This would leave the main processing loop waiting for a packet that
        // will never arrive.
        //
        // By setting the shutdown flag under the protection of the mutex,
        // the notify() call will not take place until the flag is set, and
        // the main thread will see the flag being set and exit.  We might
        // as well close the socket at the same time.
        if (loop <= 0) {
            *shutdown_ptr_ = true;
            close(sockfd);
        }

        // We now need to synchronize with the main thread.  In particular,
        // we suspend processing until we know that the processing of the
        // packet by Kea has finished and that the completion function has
        // raised a SIGSTOP.
        sync_cond_.wait(lock);
        lock.unlock();
    }

    // Loop has exited, so we should shut down Kea.  Tidy up and signal Kea
    // to exit.
    LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE, FUZZ_LOOP_EXIT);

    return;
}

// Waits for the fuzzing thread to terminate.
void
Fuzz::wait(void) {
    fuzz_thread_.join();
}

// Called by the main thread, this notifies AFL that processing for the
// // last packet has finished.
void
Fuzz::notify(void) {
    LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_NOTIFY_CALLED);
    raise(SIGSTOP);
    lock_guard<std::mutex> lock(sync_mutex_);
    sync_cond_.notify_all();
}

#endif  // ENABLE_AFL
