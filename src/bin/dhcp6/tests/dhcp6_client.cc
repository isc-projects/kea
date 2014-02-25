// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/dhcp6.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <util/buffer.h>
#include <boost/pointer_cast.hpp>
#include <time.h>

using namespace isc::test;

namespace isc {
namespace dhcp {
namespace test {

Dhcp6Client::Dhcp6Client() :
    relay_link_addr_("3000:1::1"),
    curr_transid_(0),
    dest_addr_(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
    duid_(generateDUID(DUID::DUID_LLT)),
    link_local_("fe80::3a60:77ff:fed5:cdef"),
    srv_(boost::shared_ptr<NakedDhcpv6Srv>(new NakedDhcpv6Srv(0))),
    use_na_(false),
    use_pd_(false),
    use_relay_(false) {
}

void
Dhcp6Client::applyConfiguration(const Pkt6Ptr& reply) {
    typedef OptionCollection Opts;
    // Get all options in the reply message and pick IA_NA and IA_PD.
    Opts opts = reply->options_;
    for (Opts::const_iterator opt = opts.begin(); opt != opts.end(); ++opt) {
        Option6IAPtr ia = boost::dynamic_pointer_cast<Option6IA>(opt->second);
        // If the current one is not IA option, get the next one.
        if (!ia) {
            continue;
        }
        // The default value of the prefix length is 128 (as for IPv6 address),
        // as at this point we don't know if we are dealing with the address
        // of prefix.
        int prefix_len = 128;
        // Check if this is the address.
        Option6IAAddrPtr iaaddr = boost::dynamic_pointer_cast<
            Option6IAAddr>(ia->getOption(D6O_IAADDR));
        // If this is not the address it may be a prefix.
        if (!iaaddr) {
            iaaddr = boost::dynamic_pointer_cast<
                Option6IAAddr>(ia->getOption(D6O_IAPREFIX));
            // If this is a prefix, modify the prefix length accordingly.
            if (iaaddr) {
                prefix_len = boost::dynamic_pointer_cast<
                    Option6IAPrefix>(ia->getOption(D6O_IAPREFIX))->getLength();
            }
        }
        /// Set the lease information if we have a prefix or address.
        LeaseInfo lease_info;
        if (iaaddr) {
            Lease6 lease((prefix_len == 128 ? Lease::TYPE_NA : Lease::TYPE_PD),
                         iaaddr->getAddress(), duid_,
                         ia->getIAID(), iaaddr->getPreferred(),
                         iaaddr->getValid(), ia->getT1(), ia->getT2(), 0,
                         prefix_len);
            lease.cltt_ = time(NULL);

            lease_info.lease_ = lease;
        } else {
            // There is no prefix and no address. This IA option may simply
            // contain a status code, so let's just reset the lease and keep
            // IAID around.
            lease_info.lease_ = Lease6();
            lease_info.lease_.iaid_ = ia->getIAID();
        }

        // Check if the server has sent status code. If no status code, assume
        // the status code to be 0.
        OptionCustomPtr status_code = boost::dynamic_pointer_cast<
            OptionCustom>(ia->getOption(D6O_STATUS_CODE));
        if (status_code) {
            lease_info.status_code_ = status_code->readInteger<uint16_t>(0);
        } else {
            lease_info.status_code_ = 0;
        }
        applyLease(lease_info);
    }
}

void
Dhcp6Client::applyLease(const LeaseInfo& lease_info) {
    // Go over existing leases and try to match the one that we have.
    for (int i = 0; i < config_.leases_.size(); ++i) {
        Lease6 existing_lease = config_.leases_[i].lease_;
        // If IAID is matching and there is an actual address assigned
        // replace the current lease. The default address is :: if the
        // server hasn't sent the IA option. In this case, there is no
        // lease assignment so we keep what we have.
        if ((existing_lease.iaid_ == lease_info.lease_.iaid_)
            && (lease_info.lease_.addr_ != asiolink::IOAddress("::"))) {
            config_.leases_[i] = lease_info;
            return;

        } else if (lease_info.lease_.addr_ == asiolink::IOAddress("::")) {
            config_.leases_[i].status_code_ = lease_info.status_code_;
            return;

        }
    }
    // It is a new lease. Add it.
    config_.leases_.push_back(lease_info);
}


void
Dhcp6Client::copyIAs(const Pkt6Ptr& source, const Pkt6Ptr& dest) {
    typedef OptionCollection Opts;
    // Copy IA_NAs.
    Opts opts = source->getOptions(D6O_IA_NA);
    for (Opts::const_iterator opt = opts.begin(); opt != opts.end(); ++opt) {
        dest->addOption(opt->second);
    }
    // Copy IA_PDs.
    opts = source->getOptions(D6O_IA_PD);
    for (Opts::const_iterator opt = opts.begin(); opt != opts.end(); ++opt) {
        dest->addOption(opt->second);
    }
}

void
Dhcp6Client::copyIAsFromLeases(const Pkt6Ptr& dest) const {
    // Go over leases and create IA_NA and IA_PD options from them.
    // Create one IA per lease.
    for (std::vector<LeaseInfo>::const_iterator info = config_.leases_.begin();
         info != config_.leases_.end(); ++info) {
        Lease6 lease = info->lease_;
        if (lease.type_ == Lease::TYPE_NA) {
            Option6IAPtr opt(new Option6IA(D6O_IA_NA, lease.iaid_));
            opt->setT1(lease.t1_);
            opt->setT2(lease.t1_);
            opt->addOption(Option6IAAddrPtr(new
                                            Option6IAAddr(D6O_IAADDR,
                                                          lease.addr_,
                                                          lease.preferred_lft_,
                                                          lease.valid_lft_)));
            dest->addOption(opt);
        } else if (lease.type_ == Lease::TYPE_PD) {
            Option6IAPtr opt(new Option6IA(D6O_IA_PD, lease.iaid_));
            opt->setT1(lease.t1_);
            opt->setT2(lease.t1_);
            opt->addOption(Option6IAPrefixPtr(new Option6IAPrefix(D6O_IAPREFIX,
                                                                  lease.addr_,
                                                                  lease.prefixlen_,
                                                                  lease.preferred_lft_,
                                                                  lease.valid_lft_)));
            dest->addOption(opt);
        }
    }
}

Pkt6Ptr
Dhcp6Client::createMsg(const uint8_t msg_type) {
    Pkt6Ptr msg(new Pkt6(msg_type, curr_transid_++));
    msg->addOption(getClientId());
    return (msg);
}

void
Dhcp6Client::doSARR() {
    doSolicit();
    // Don't send the Request if there was no Advertise.
    if (context_.response_) {
        doRequest();
    }
}

void
Dhcp6Client::doSolicit() {
    context_.query_ = createMsg(DHCPV6_SOLICIT);
    if (use_na_) {
        context_.query_->addOption(Option6IAPtr(new Option6IA(D6O_IA_NA,
                                                              1234)));
    }
    if (use_pd_) {
        context_.query_->addOption(Option6IAPtr(new Option6IA(D6O_IA_PD,
                                                              5678)));
    }
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();

    /// @todo Sanity check here
}

void
Dhcp6Client::doRequest() {
    Pkt6Ptr query = createMsg(DHCPV6_REQUEST);
    query->addOption(context_.response_->getOption(D6O_SERVERID));
    copyIAs(context_.response_, query);
    context_.query_ = query;
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();

    /// @todo sanity check here.

    // Apply new configuration only if the server has responded.
    if (context_.response_) {
        applyConfiguration(context_.response_);
    }
}

void
Dhcp6Client::doRebind() {
    Pkt6Ptr query = createMsg(DHCPV6_REBIND);
    copyIAsFromLeases(query);
    context_.query_ = query;
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();
    // Apply configuration only if the server has responded.
    if (context_.response_) {
        applyConfiguration(context_.response_);
    }
}

void
Dhcp6Client::fastFwdTime(const uint32_t secs) {
    // Iterate over all leases and move their cltt backwards.
    for (int i = 0; i < config_.leases_.size(); ++i) {
        config_.leases_[i].lease_.cltt_ -= secs;
    }
}

DuidPtr
Dhcp6Client::generateDUID(DUID::DUIDType duid_type) const {
    std::vector<uint8_t> duid;

    /// @todo remove this check once other DUID types are implemented.
    if (duid_type != DUID::DUID_LLT) {
        isc_throw(NotImplemented, "currently the Dhcp6Client only supports"
                  " generation of DUID LLT");
    }
    duid.push_back(static_cast<uint8_t>(duid_type));
    duid.insert(duid.end(), 4, 0);
    for (int i = 0; i < 6; ++i) {
        duid.push_back(static_cast<uint8_t>(i));
    }

    return (DuidPtr(new DUID(duid)));
}

OptionPtr
Dhcp6Client::getClientId() const {
    OptionPtr opt_client_id(new Option(Option::V6,
                                       D6O_CLIENTID,
                                       duid_->getDuid().begin(),
                                       duid_->getDuid().end()));
    return (opt_client_id);
}

void
Dhcp6Client::modifyDUID() {
    if (!duid_) {
        duid_ = generateDUID(DUID::DUID_LLT);
        return;
    }
    std::vector<uint8_t> new_duid = duid_->getDuid();
    // Modify the DUID by adding 1 to its last byte.
    ++new_duid[new_duid.size() - 1];
    duid_.reset(new DUID(new_duid));
}

Pkt6Ptr
Dhcp6Client::receiveOneMsg() {
    // Return empty pointer if server hasn't responded.
    if (srv_->fake_sent_.empty()) {
        return (Pkt6Ptr());
    }
    Pkt6Ptr msg = srv_->fake_sent_.front();
    srv_->fake_sent_.pop_front();
    return (msg);
}

void
Dhcp6Client::sendMsg(const Pkt6Ptr& msg) {
    srv_->shutdown_ = false;
    // The client is configured to send through the relay. We achieve that
    // adding the relay structure.
    if (use_relay_) {
        Pkt6::RelayInfo relay;
        relay.linkaddr_ = relay_link_addr_;
        relay.peeraddr_ = asiolink::IOAddress("fe80::1");
        relay.msg_type_ = DHCPV6_RELAY_FORW;
        relay.hop_count_ = 1;
        msg->relay_info_.push_back(relay);
    }
    // Repack the message to simulate wire-data parsing.
    msg->pack();
    Pkt6Ptr msg_copy(new Pkt6(static_cast<const uint8_t*>
                              (msg->getBuffer().getData()),
                              msg->getBuffer().getLength()));
    msg_copy->setRemoteAddr(link_local_);
    msg_copy->setLocalAddr(dest_addr_);
    msg_copy->setIface("eth0");
    srv_->fakeReceive(msg_copy);
    srv_->run();
}


}
}
}
