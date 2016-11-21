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

/*
 * We are using pthreads directly because we might be using it with unthreaded
 * version of BIND, where all thread functions are mocks. Since AFL for now only
 * works on Linux it's not a problem.
 */
static pthread_cond_t cond;
static pthread_mutex_t mutex;

static bool ready;

using namespace std;

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
    
    cout << "Kea AFL setup:" << endl;
    cout << "Interface: " << iface << endl;
    cout << "Interface index: " << iface_id << endl;
    cout << "UDP destination addr: " << dst << endl;
    cout << "UDP destination port: " << port << endl;

    memset(&servaddr, 0, sizeof (servaddr));
    servaddr.sin6_family = AF_INET6;
    if (inet_pton(AF_INET6, dst.c_str(), &servaddr.sin6_addr) != 1) {
        cout << "Error: inet_pton() failed: can't convert " << dst
             << " to address." << endl;
        exit(EXIT_FAILURE);
    }
    servaddr.sin6_port = htons(547);
    servaddr.sin6_scope_id = iface_id;

    sockfd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        cout << "Failed to create UDP6 socket" << endl;
        exit(EXIT_FAILURE);
    }

    buf = malloc(65536);
    if (!buf) {
        cout << "Failed to allocate a buffer" << endl;
        exit(EXIT_FAILURE);
    }

    loop = 100000;
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
            cout << "#### Failed to lock mutex" << endl;
        }

        ready = false;

        ssize_t sent;

        cout << "Sending " << length << " bytes to " << dst << "/" << port
             << " over " << iface << "/" << iface_id << endl;

        sent = sendto(sockfd, buf, length, 0,
                      (struct sockaddr *) &servaddr, sizeof(servaddr));
        if (sent != length) {
            cout << "#### Error: expected to send " << length
                 << ", but really sent " << sent << endl;
        }

        /* unclog */
        recvfrom(sockfd, buf, 65536, MSG_DONTWAIT, NULL, NULL);

        while (!ready)
            pthread_cond_wait(&cond, &mutex);

        if (pthread_mutex_unlock(&mutex) != 0) {
            cout << "#### Failed to unlock mutex" << endl;
        }
    }

    free(buf);
    close(sockfd);

    // @todo: shutdown kea
    // ns_server_flushonshutdown(ns_g_server, ISC_FALSE);
    // isc_app_shutdown();

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
    /// @todo: What does this piece of code do?
    /* if (getenv("AFL_CMIN")) {
        ns_server_flushonshutdown(ns_g_server, ISC_FALSE);
        isc_app_shutdown();
        return;
        } */

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
kea_fuzz_setup(void) {
#ifdef ENABLE_AFL

    /// @todo: What are those variables? What do they do?
    if (getenv("__AFL_PERSISTENT") || getenv("AFL_CMIN")) {
        pthread_t thread;
        
        if (pthread_mutex_init(&mutex, NULL) != 0) {
            
        }
        
        if (pthread_cond_init(&cond, NULL) == 0) {

        }

        
        if (pthread_create(&thread, NULL, kea_main_client, NULL) != 0) {
            
        }
    }

#endif /* ENABLE_AFL */
}
