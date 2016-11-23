/*
 * Copyright (C) 2016  Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "config.h"

#include <dhcp6/fuzz.h>

#define ENABLE_AFL

#ifdef ENABLE_AFL
#include <sys/errno.h>

#include <dhcp/dhcp6.h>

#include <iostream>
#include <fstream>
#include <ctime>

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <pthread.h>


#ifndef __AFL_LOOP
#error To use American Fuzzy Lop you have to set CC to afl-clang-fast!!!
#endif

/// This is how many packets Kea will process until shutting itself down.
/// AFL should restart it. This safety switch is here for eliminating cases
/// where Kea goes into a weird state and stops processing packets properly.
const unsigned int LOOP_COUNT = 100000;

/// This mechanism limits down the number of logs this harness prints.
/// E.g. when set to 100, it will print a message every 100 packets.
const unsigned int PRINT_EVERY = 5;

/// This is the place where the harness log message will be printed.
const std::string PRINT_LOG("/tmp/kea-fuzz-harness.txt");

/*
 * We are using pthreads directly because we might be using it with unthreaded
 * version of BIND, where all thread functions are mocks. Since AFL for now only
 * works on Linux it's not a problem.
 */
static pthread_cond_t cond;
static pthread_mutex_t mutex;

static bool ready;

using namespace std;

bool * shutdown_reference = NULL;


void kea_shutdown() {
    if (shutdown_reference) {
        // do we have the reference to shutdown flag from Dhcp6Srv?
        // If yes, then let's set it to true. Kea will shutdown on
        // its own.
        *shutdown_reference = true;
    } else {
        // We don't have the pointer yet. Let's terminate abruptly.
        exit(EXIT_SUCCESS);
    }
}


// This is the main fuzzing function. It receives data from fuzzing engine.
// That data is received to stdin and then sent over the configured UDP socket.
// Then it wait for a conditional, which is called in kea_fuzz_notify() from
// Kea main loop.
static void *
kea_main_client(void *arg) {
    const char *host;
    struct sockaddr_in6 servaddr;
    int sockfd;
    int loop;
    void *buf;

    string iface("eth0");
    string dst(ALL_DHCP_RELAY_AGENTS_AND_SERVERS);
    string port("547");

    ofstream f(PRINT_LOG.c_str(), ios::ate);

    const char *iface_ptr = getenv("KEA_AFL_INTERFACE");
    if (iface_ptr) {
        iface = string(iface_ptr);
    }

    const char *dst_ptr = getenv("KEA_AFL_ADDR");
    if (dst_ptr) {
        dst = string(dst_ptr);
    }

    const char *port_ptr = getenv("KEA_AFL_PORT");
    if (port_ptr) {
        port = string(port_ptr);
    }

    unsigned int iface_id = if_nametoindex(iface.c_str());

    f << "Kea AFL setup:" << endl;
    f << "Interface: " << iface << endl;
    f << "Interface index: " << iface_id << endl;
    f << "UDP destination addr: " << dst << endl;
    f << "UDP destination port: " << port << endl;

    memset(&servaddr, 0, sizeof (servaddr));
    servaddr.sin6_family = AF_INET6;
    if (inet_pton(AF_INET6, dst.c_str(), &servaddr.sin6_addr) != 1) {
        f << "Error: inet_pton() failed: can't convert " << dst
          << " to address." << endl;
        exit(EXIT_FAILURE);
    }
    servaddr.sin6_port = htons(547);
    servaddr.sin6_scope_id = iface_id;

    sockfd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        f << "Failed to create UDP6 socket" << endl;
        exit(EXIT_FAILURE);
    }

    buf = malloc(65536);
    if (!buf) {
        f << "Failed to allocate a buffer" << endl;
        exit(EXIT_FAILURE);
    }

    time_t t;

    loop = LOOP_COUNT;
    while (loop--) {
        ssize_t length;

        length = read(0, buf, 65536);
        if (length <= 0) {
            usleep(1000000);
            continue;
        }

        /* if (length > 4096) {
            if (getenv("AFL_CMIN")) {
                ns_server_flushonshutdown(ns_g_server,
                                          ISC_FALSE);
                isc_app_shutdown();
                return (NULL);
            }
            raise(SIGSTOP);
            continue;
            } */

        if (pthread_mutex_lock(&mutex) != 0) {
            f << "#### Failed to lock mutex" << endl;
        }

        ready = false;

        ssize_t sent;

        t = time(0);
        struct tm * now = localtime(&t);

        if (! (loop%PRINT_EVERY)) {
            f << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << (now->tm_mday)
              << " " << (now->tm_hour) << ":" << (now->tm_min) << ":" << (now->tm_sec)
              << " Sending " << length << " bytes to " << dst << "/" << port
              << " over " << iface << "/" << iface_id << ", loop iteration << "
              << loop << endl;
        }

        sent = sendto(sockfd, buf, length, 0,
                      (struct sockaddr *) &servaddr, sizeof(servaddr));
        if (sent != length) {
            f << "#### Error: expected to send " << length
              << ", but really sent " << sent << endl;
        }

        /* unclog */
        recvfrom(sockfd, buf, 65536, MSG_DONTWAIT, NULL, NULL);

        while (!ready)
            pthread_cond_wait(&cond, &mutex);

        if (pthread_mutex_unlock(&mutex) != 0) {
            f << "#### Failed to unlock mutex" << endl;
        }
    }

    f << LOOP_COUNT << " packets processed, terminating." << endl;
    f.close();

    free(buf);
    close(sockfd);

    // @todo: shutdown kea
    // ns_server_flushonshutdown(ns_g_server, ISC_FALSE);
    // isc_app_shutdown();
    kea_shutdown();

    /*
     * It's here just for the signature, that's how AFL detects if it's
     * a 'persistent mode' binary.
     */
    __AFL_LOOP(0);

    return (NULL);
}

#endif /* ENABLE_AFT */

void
kea_fuzz_notify(void) {
#ifdef ENABLE_AFL
    if (getenv("AFL_CMIN")) {
        kea_shutdown();
        /// @todo: What does this piece of code do?
        /* ns_server_flushonshutdown(ns_g_server, ISC_FALSE);
           isc_app_shutdown(); */
        return;
    }

    raise(SIGSTOP);

    if (pthread_mutex_lock(&mutex) != 0) {
        cout << "#### unable to lock mutex" << endl;
    }

    ready = true;

    if (pthread_cond_signal(&cond) != 0) {

    }

    if (pthread_mutex_unlock(&mutex) != 0) {
        cout << "Unable to unlock mutex" << endl;
    }
#endif /* ENABLE_AFL */
}

void
kea_fuzz_setup(volatile bool* shutdown) {
#ifdef ENABLE_AFL

    /// @todo: What are those variables? What do they do?
    if (getenv("__AFL_PERSISTENT") || getenv("AFL_CMIN")) {
        pthread_t thread;

        if (pthread_mutex_init(&mutex, NULL) != 0) {

        }

        if (pthread_cond_init(&cond, NULL) == 0) {

        }


        if (pthread_create(&thread, NULL, kea_main_client, (void*)shutdown) != 0) {

        }
    }

#endif /* ENABLE_AFL */
}
