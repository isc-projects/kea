// Copyright (C) 2016-2019  Internet Systems Consortium, Inc. ("ISC")
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
    

/// @brief AFL Fuzzing
///
/// Persistent-mode AFL fuzzing has the AFL fuzzer send packets of data to
/// stdin of the program being tested. The program processes the data and
/// signals to AFL that it is complete.
///
/// To reduce the code changes required, the scheme adopted for Kea is that
/// the AFL data read from stdin is written to an address/port on which Kea
/// is listening.  Kea then reads the data from that port and processes it
/// in the usual way.
///
/// The Fuzz class handles the transfer of data between AFL and Kea.  After
/// suitable initialization, its transfer() method is called in the main
/// processing loop, right before Kea waits for input. The method handles the
/// read from stdin and the write to the selected address port.

class Fuzz {
public:
    /// @brief size of the buffer used to transfer data between AFL and Kea.
    ///
    /// This is much larger than the data that will be sent to Kea (so AFL
    /// data may be trimmed).  However, it does allow for AFL to send quite
    /// large packets without resulting in AFL synchronization problems because
    /// Kea has not read all the data sent.
    static constexpr size_t BUFFER_SIZE = 256 * 1024;

    /// @brief maximum size of packets fuzzing thread will send to Kea
    ///
    /// This is below the maximum size of data that we will allow Kea to put
    /// into a single UDP datagram so as to avoid any "data too big" errors
    /// when trying to send it to the port on which Kea listens.
    static constexpr size_t MAX_SEND_SIZE = 64000;

    /// @brief Number of packets Kea will process before shutting down.
    ///
    /// After the shutdown, AFL will restart it. This safety switch is here for
    /// eliminating cases where Kea goes into a weird state and stops
    /// processing packets properly.  This can be overridden by setting the
    /// environment variable KEA_AFL_LOOP_MAX.
    static constexpr long MAX_LOOP_COUNT = 1000;


    /// @brief Constructor
    ///
    /// Sets up data structures to access the address/port being used to
    /// transfer data from AFL to Kea.
    ///
    /// @param ipversion Either 4 or 6 depending on what IP version the
    ///                  server responds to.
    /// @param port      Port on which the server is listening, and hence the
    ///                  port to which the fuzzer will send input from AFL.
    Fuzz(int ipversion, uint16_t port);

    /// @brief Destructor
    ///
    /// Closes the socket used for transferring data from stdin to the selected
    /// interface.
    ~Fuzz();

    /// @brief Transfer Data
    ///
    /// Called immediately prior to Kea reading data, this reads stdin (where
    /// AFL will have sent the packet being tested) and copies the data to the
    /// interface on which Kea is listening.
    void transfer(void) const;

    /// @brief Return Max Loop Count
    ///
    /// Returns the maximum number of loops (i.e. AFL packets processed) before
    /// Kea exits.  This is the value of the environment variable
    /// FUZZ_AFL_LOOP_MAX, or the class constant MAX_LOOP_COUNT if that is not
    /// defined.
    ///
    /// @return Maximum loop count
    long maxLoopCount() const {
        return loop_max_;
    }

private:
    /// @brief Create address structures
    ///
    /// Create the address structures describing the address/port on whick Kea
    /// is listening for packets from AFL.
    ///
    /// @param ipversion Either 4 or 6 depending on which IP version address
    ///                  is expected.
    /// @param interface Interface through which the fuzzer is sending packets
    ///                  to Kea.
    /// @param address   Address on the interface that will be used.
    /// @param port      Port to be used.
    ///
    /// @throws FuzzInitFail Thrown if the address is not in the expected
    ///                      format.
    void createAddressStructures(int ipversion, const char* interface,
                                 const char* address, uint16_t port);

    // Other member variables.
    long                loop_max_;      //< Maximum number of loop iterations
    size_t              sockaddr_len_;  //< Length of the structure
    struct sockaddr*    sockaddr_ptr_;  //< Pointer to structure used
    struct sockaddr_in  servaddr4_;     //< IPv6 address information
    struct sockaddr_in6 servaddr6_;     //< IPv6 address information
    int                 sockfd_;        //< Socket used to transfer data
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
