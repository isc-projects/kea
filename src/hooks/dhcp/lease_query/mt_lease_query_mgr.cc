// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <asiolink/io_service.h>
#include <mt_lease_query_mgr.h>
#include <util/multi_threading_mgr.h>

#include <boost/pointer_cast.hpp>

using namespace isc::asiolink;
using namespace isc::tcp;
using namespace isc::util;

namespace ph = std::placeholders;

namespace isc {
namespace lease_query {

MtLeaseQueryListenerMgr::MtLeaseQueryListenerMgr(const IOAddress& address,
                                                 const uint16_t port,
                                                 const uint16_t family,
                                                 const tcp::TcpListener::IdleTimeout& idle_timeout,
                                                 const uint16_t thread_pool_size /* = 1 */,
                                                 TlsContextPtr context /* = () */,
                                                 TcpConnectionFilterCallback connection_filter /* = 0 */,
                                                 const size_t max_concurrent_queries /* = 0 */)
    : MtTcpListenerMgr(std::bind(&MtLeaseQueryListenerMgr::listenerFactory,
                                 this, ph::_1, ph::_2, ph::_3, ph::_4, ph::_5,
                                 ph::_6),
                       address, port, thread_pool_size, context,
                       connection_filter),
      family_(family),
      max_concurrent_queries_(max_concurrent_queries) {
      setIdleTimeout(idle_timeout.value_);
}

TcpListenerPtr
MtLeaseQueryListenerMgr::listenerFactory(const asiolink::IOServicePtr& io_service,
                                         const asiolink::IOAddress& server_address,
                                         const unsigned short server_port,
                                         const asiolink::TlsContextPtr& tls_context,
                                         const TcpListener::IdleTimeout& idle_timeout,
                                         const TcpConnectionFilterCallback& connection_filter) {
    TcpListenerPtr listener(new LeaseQueryListener(io_service,
                                                   server_address,
                                                   server_port,
                                                   tls_context,
                                                   idle_timeout,
                                                   connection_filter,
                                                   family_,
                                                   max_concurrent_queries_));
    return (listener);
}


MtLeaseQueryListenerMgr::~MtLeaseQueryListenerMgr() {
    stop();
}

} // namespace isc::lease_query
} // namespace isc
