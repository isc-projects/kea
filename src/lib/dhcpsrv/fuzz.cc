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

// Constants defined in the Fuzz class definition.
constexpr size_t        Fuzz::BUFFER_SIZE;
constexpr useconds_t    Fuzz::SLEEP_INTERVAL;
constexpr long          Fuzz::LOOP_COUNT;

// Variables needed to synchronize between main and fuzzing threads.  The
// fuzz_sync_ condition is notified by the fuzzing thread and waited for by the
// main thread.  The main_sync_ condition is notified by the main thread and
// waited for by the fuzzing thread.
FuzzSynch               Fuzz::fuzz_sync_;
FuzzSynch               Fuzz::main_sync_;
std::thread             Fuzz::fuzzing_thread_;

// Address structure used to define the address/port used to send
// fuzzing data to the Kea server.
struct sockaddr_in6     Fuzz::servaddr_;

// Pointer to the shutdown flag used by Kea.  The fuzzing code will set this
// after the appropriate number of packets have been fuzzed.
volatile bool*          Fuzz::shutdown_ptr_ = NULL;

// FuzzSynch methods.  FuzSynch is the class that encapsulates the
// synchronization process between the main and fuzzing threads.

// init - just set the predicate as false.
void FuzzSynch::init(const char* name) {
    name_ = name;
    ready_ = false;
}

// Wait to be notified when the predicate is true
void
FuzzSynch::wait(void) {
    LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_WAITING).arg(name_);
    unique_lock<mutex>   lock(mutex_);
    cond_.wait(lock, [=]() { return this->ready_; });
    ready_ = false;
    LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_WAITED).arg(name_);
}

// Set predicate and notify the waiting thread to continue
void
FuzzSynch::notify(void) {
    LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_SETTING).arg(name_);
    unique_lock<mutex>  lock(mutex_);
    ready_ = true;
    cond_.notify_all();
    LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_SET).arg(name_);
}

// Fuzz methods.

// Initialization: create the thread artifacts and start the fuzzing thread.
void
Fuzz::init(volatile bool* shutdown_flag) {
    try {
        stringstream reason;    // Used for exception messages

        // Store reference to shutdown flag.  When the fuzzing loop has read
        // the set number of packets from AFL, it will set this flag to trigger
        // a Kea shutdown.
        if (shutdown_flag) {
            shutdown_ptr_ = shutdown_flag;
        } else {
            isc_throw(FuzzInitFail, "must pass shutdown flag to kea_fuzz_init");
        }

        // Get the environment for the fuzzing: interface, address and port.
        const char *iface_ptr = getenv("KEA_AFL_INTERFACE");
        if (! iface_ptr) {
            isc_throw(FuzzInitFail, "no fuzzing interface has been set");
        }
        // Interface obtained, convert to ID.
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

        // Initialize synchronization variables.
        fuzz_sync_.init("fuzz_synch");
        main_sync_.init("main_synch");

        // Initialization complete.
        LOG_INFO(fuzz_logger, FUZZ_INTERFACE)
                 .arg(iface_ptr).arg(address_ptr).arg(port);

        // Start the thread that reads the packets sent by AFL from stdin and
        // passes them to the port on which Kea is listening.
        fuzzing_thread_ = std::thread(Fuzz::run);

        // Wait for the fuzzing thread to read its first packet from AFL and
        // send it to the port on which Kea is listening.
        fuzz_sync_.wait();

    } catch (const FuzzInitFail& e) {
        // AFL tends to make it difficult to find out what exactly has failed:
        // make sure that the error is logged.
        LOG_FATAL(fuzz_logger, FUZZ_INIT_FAIL).arg(e.what());
        throw;
    }
}

// This is the main fuzzing function. It receives data from fuzzing engine.
// That data is received to stdin and then sent over the configured UDP socket.
// It then waits for the main thread to process the packet, the completion of
// that task being signalled by the main thread calling Fuzz::packetProcessed().
void
Fuzz::run(void) {
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
    // that thread running this function shuts down properly between each
    // restart of Kea.
    auto loop = Fuzz::LOOP_COUNT;
    while (loop-- > 0) {
        // Read from stdin and continue reading (albeit after a pause) even
        // if there is an error.  Do the same with end of files.
        char buf[BUFFER_SIZE];
        ssize_t length = read(0, buf, sizeof(buf));
        if (length <= 0) {
            LOG_ERROR(fuzz_logger, FUZZ_READ_FAIL).arg(strerror(errno));
            usleep(SLEEP_INTERVAL);
            continue;
        }
        LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_DATA_READ)
                  .arg(length);

        // Now send the data to the UDP port on which Kea is listening.
        //
        // The condition variables synchronize the operation: this thread
        // will read from stdin and write to the socket.  It then blocks until
        // the main thread has processed the packet, at which point it can read
        // more data from stdin.
        //
        // Synchronization is required because although the read from stdin is
        // blocking, there is no blocking on the sending of data to the port
        // from which Kea is reading.  It is quite possible to lose packets,
        // and AFL seems to get confused in this case.  At any rate, without
        // some form of synchronization, this approach does not work.

        // Send the data to the main Kea thread.
        ssize_t sent = sendto(sockfd, buf, length, 0,
                          (struct sockaddr *) &servaddr_, sizeof(servaddr_));
        if (sent < 0) {
            LOG_ERROR(fuzz_logger, FUZZ_SEND_ERROR).arg(strerror(errno));
            continue;
        } else if (sent != length) {
            LOG_WARN(fuzz_logger, FUZZ_SHORT_SEND).arg(length).arg(sent);
        } else {
            LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_SEND).arg(sent);
        }

        if (loop <= 0) {
            // If this is the last loop iteration, close everything down.
            // This is done before giving permission for the main thread
            // to run to avoid a race condition.
            *shutdown_ptr_ = true;
            close(sockfd);
            LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE, FUZZ_SHUTDOWN_INITIATED);
        }

        // Tell the main thread to run.
        fuzz_sync_.notify();

        // We now need to synchronize with the main thread.  In particular,
        // we suspend processing until we know that the processing of the
        // packet by Kea has finished and that the completion function has
        // raised a SIGSTOP.
        main_sync_.wait();
    }
    LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE, FUZZ_LOOP_EXIT);

    // If the main thread is waiting, let it terminate as well.
    fuzz_sync_.notify();

    return;
}

// Called by the main thread, this notifies AFL that processing for the
// last packet has finished.
void
Fuzz::packetProcessed(void) {
    LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE_DETAIL, FUZZ_PACKET_PROCESSED_CALLED);

    // Tell AFL that the processing for this packet has finished.
    raise(SIGSTOP);

    // Tell the fuzzing loop that it can continue and wait until it tells
    // us that the main thread can continue.
    main_sync_.notify();
    fuzz_sync_.wait();

    // If the fuzzing thread is shutting down, wait for it to terminate.
    if (*shutdown_ptr_) {
        // We shouldn't need to notify it to continue (the previous call in
        // this method should have done that), but it does no harm to be sure.
        main_sync_.notify();
        LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE, FUZZ_THREAD_WAIT);
        fuzzing_thread_.join();
        LOG_DEBUG(fuzz_logger, FUZZ_DBG_TRACE, FUZZ_THREAD_TERMINATED);
    }
}

#endif  // ENABLE_AFL
