// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option_int_array.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <util/buffer.h>
#include <boost/pointer_cast.hpp>
#include <cstdlib>
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
    use_relay_(false),
    use_oro_(false),
    use_client_id_(true),
    prefix_hint_() {
}

Dhcp6Client::Dhcp6Client(boost::shared_ptr<NakedDhcpv6Srv>& srv) :
    relay_link_addr_("3000:1::1"),
    curr_transid_(0),
    dest_addr_(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
    duid_(generateDUID(DUID::DUID_LLT)),
    link_local_("fe80::3a60:77ff:fed5:cdef"),
    srv_(srv),
    use_na_(false),
    use_pd_(false),
    use_relay_(false),
    use_oro_(false),
    use_client_id_(true),
    prefix_hint_() {
}

void
Dhcp6Client::applyRcvdConfiguration(const Pkt6Ptr& reply) {
    typedef OptionCollection Opts;
    // Get all options in the reply message and pick IA_NA, IA_PD and
    // Status code.
    Opts opts = reply->options_;

    // Let's try to get a MAC
    HWAddrPtr hwaddr = reply->getMAC(HWAddr::HWADDR_SOURCE_ANY);

    // Set the global status code to default: success and not received.
    config_.resetGlobalStatusCode();
    for (Opts::const_iterator opt = opts.begin(); opt != opts.end(); ++opt) {
        Option6IAPtr ia = boost::dynamic_pointer_cast<Option6IA>(opt->second);
        if (!ia) {
            // This is not IA, so let's just store it.
            config_.options_.insert(*opt);
            continue;
        }

        const Opts& ia_opts = ia->getOptions();
        for (Opts::const_iterator iter_ia_opt = ia_opts.begin();
             iter_ia_opt != ia_opts.end(); ++iter_ia_opt) {
            OptionPtr ia_opt = iter_ia_opt->second;
            LeaseInfo lease_info;
            switch (ia_opt->getType()) {
            case D6O_IAADDR:
                {
                    Option6IAAddrPtr iaaddr = boost::dynamic_pointer_cast<
                        Option6IAAddr>(ia_opt);

                    if (!iaaddr) {
                        // There is no address. This IA option may simply
                        // contain a status code, so let's just reset the
                        // lease and keep IAID around.
                        lease_info.lease_ = Lease6();
                        lease_info.lease_.type_ = Lease::TYPE_NA;
                        lease_info.lease_.iaid_ = ia->getIAID();
                        break;
                    }

                    lease_info.lease_ = Lease6(Lease::TYPE_NA,
                                               iaaddr->getAddress(),
                                               duid_, ia->getIAID(),
                                               iaaddr->getPreferred(),
                                               iaaddr->getValid(),
                                               ia->getT1(), ia->getT2(), 0,
                                               hwaddr);
                    lease_info.lease_.cltt_ = time(NULL);
                }
                break;

            case D6O_IAPREFIX:
                {
                    Option6IAPrefixPtr iaprefix = boost::dynamic_pointer_cast<
                        Option6IAPrefix>(ia_opt);
                    if (!iaprefix) {
                        // There is no prefix. This IA option may simply
                        // contain a status code, so let's just reset the
                        // lease and keep IAID around.
                        lease_info.lease_ = Lease6();
                        lease_info.lease_.type_ = Lease::TYPE_PD;
                        lease_info.lease_.iaid_ = ia->getIAID();
                        break;
                    }
                    lease_info.lease_ = Lease6(Lease::TYPE_PD,
                                               iaprefix->getAddress(), duid_,
                                               ia->getIAID(),
                                               iaprefix->getPreferred(),
                                               iaprefix->getValid(),
                                               ia->getT1(), ia->getT2(), 0,
                                               hwaddr,
                                               iaprefix->getLength());
                    lease_info.lease_.cltt_ = time(NULL);
                }
                break;

            case D6O_STATUS_CODE:
                {
                    // Check if the server has sent status code. If no status
                    // code, assume the status code to be 0.
                    OptionCustomPtr status_code = boost::dynamic_pointer_cast<
                        OptionCustom>(ia->getOption(D6O_STATUS_CODE));
                    lease_info.status_code_ =
                        status_code ? status_code->readInteger<uint16_t>(0) : 0;
                }
                break;

            default:
                ; // no-op
            }

            applyLease(lease_info);
        }
    }

    // Get the global status code.
    OptionCustomPtr status_code = boost::dynamic_pointer_cast<
        OptionCustom>(reply->getOption(D6O_STATUS_CODE));
    // If status code has been sent, we override the default status code:
    // Success and record that we have received the status code.
    if (status_code) {
        config_.received_status_code_ = true;
        config_.status_code_ = status_code->readInteger<uint16_t>(0);
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
            && (existing_lease.type_ == lease_info.lease_.type_)
            && (lease_info.lease_.addr_ != asiolink::IOAddress("::"))
            && (existing_lease.addr_ == lease_info.lease_.addr_)) {
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
    std::set<uint32_t> iaids = getIAIDs();
    for (std::set<uint32_t>::const_iterator iaid = iaids.begin();
         iaid != iaids.end(); ++iaid) {
        std::vector<Lease6> leases = getLeasesByIAID(*iaid);
        Option6IAPtr opt(new Option6IA(leases[0].type_ == Lease::TYPE_NA ?
                                       D6O_IA_NA : D6O_IA_PD, *iaid));
        opt->setT1(leases[0].t1_);
        opt->setT2(leases[0].t2_);
        for (std::vector<Lease6>::const_iterator lease = leases.begin();
             lease != leases.end(); ++lease) {
            if ((lease->preferred_lft_ != 0) && (lease->valid_lft_ != 0)) {
                if (lease->type_ == Lease::TYPE_NA) {
                    opt->addOption(Option6IAAddrPtr(new Option6IAAddr(
                                                          D6O_IAADDR,
                                                          lease->addr_,
                                                          lease->preferred_lft_,
                                                          lease->valid_lft_)));
                } else if (lease->type_ == Lease::TYPE_PD) {
                    opt->addOption(Option6IAAddrPtr(new Option6IAPrefix(
                                                          D6O_IAPREFIX,
                                                          lease->addr_,
                                                          lease->prefixlen_,
                                                          lease->preferred_lft_,
                                                          lease->valid_lft_)));
                }
            }
        }
        dest->addOption(opt);
    }
}

void
Dhcp6Client::createLease(const Lease6& lease) {
    LeaseInfo info;
    info.lease_ = lease;
    applyLease(info);
}

Pkt6Ptr
Dhcp6Client::createMsg(const uint8_t msg_type) {
    Pkt6Ptr msg(new Pkt6(msg_type, curr_transid_++));

    if (use_client_id_) {
        msg->addOption(getClientId());
    }
    if (use_oro_) {
        OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6, D6O_ORO));
        oro->setValues(oro_);

        msg->addOption(oro);
    };

    // If there are any custom options specified, add them all to the message.
    if (!extra_options_.empty()) {
        for (OptionCollection::iterator opt = extra_options_.begin();
             opt != extra_options_.end(); ++opt) {
            msg->addOption(opt->second);
        }
    }

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
        Option6IAPtr ia(new Option6IA(D6O_IA_PD, 5678));
        if (prefix_hint_) {
            ia->addOption(prefix_hint_);
        }
        context_.query_->addOption(ia);
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
        applyRcvdConfiguration(context_.response_);
    }
}

void
Dhcp6Client::doInfRequest() {
    context_.query_ = createMsg(DHCPV6_INFORMATION_REQUEST);

    // IA_NA, IA_TA and IA_PD options are not allowed in INF-REQUEST,
    // but hey! Let's test it.
    if (use_na_) {
        // Insert IA_NA option with iaid=1234.
        context_.query_->addOption(Option6IAPtr(new Option6IA(D6O_IA_NA,
                                                              1234)));
    }

    // IA-PD is also not allowed. So it may be useful in testing, too.
    if (use_pd_) {
        // Insert IA_PD option with iaid=5678
        Option6IAPtr ia(new Option6IA(D6O_IA_PD, 5678));
        if (prefix_hint_) {
            ia->addOption(prefix_hint_);
        }
        context_.query_->addOption(ia);
    }

    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();
}

void
Dhcp6Client::doRenew() {
    Pkt6Ptr query = createMsg(DHCPV6_RENEW);
    query->addOption(context_.response_->getOption(D6O_SERVERID));
    copyIAsFromLeases(query);
    context_.query_ = query;
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();
    // Apply configuration only if the server has responded.
    if (context_.response_) {
        applyRcvdConfiguration(context_.response_);
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
        applyRcvdConfiguration(context_.response_);
    }
}

void
Dhcp6Client::doConfirm() {
    context_.query_ = createMsg(DHCPV6_CONFIRM);
    copyIAsFromLeases(context_.query_);
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();
    // Set the global status code to default: success and not received.
    config_.resetGlobalStatusCode();
    if (context_.response_) {
        applyRcvdConfiguration(context_.response_);
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
    for (int i = 0; i < 4; ++i) {
        duid.push_back(static_cast<uint8_t>(rand() % 255));
    }
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

std::set<uint32_t>
Dhcp6Client::getIAIDs() const {
    std::set<uint32_t> iaids;
    for (std::vector<LeaseInfo>::const_iterator lease_info =
             config_.leases_.begin(); lease_info != config_.leases_.end();
         ++lease_info) {
        iaids.insert(lease_info->lease_.iaid_);
    }
    return (iaids);
}

std::vector<Lease6>
Dhcp6Client::getLeasesByIAID(const uint32_t iaid) const {
    std::vector<Lease6> leases;
    for (std::vector<LeaseInfo>::const_iterator lease_info =
             config_.leases_.begin(); lease_info != config_.leases_.end();
         ++lease_info) {
        if (lease_info->lease_.iaid_ == iaid) {
            leases.push_back(lease_info->lease_);
        }
    }
    return (leases);
}

void
Dhcp6Client::setDUID(const std::string& str) {
    DUID d = DUID::fromText(str);
    duid_.reset(new DUID(d));
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
    if (use_relay_ || !relay_info_.empty()) {
        if (relay_info_.empty()) {
            // Let's craft the relay info by hand
            Pkt6::RelayInfo relay;
            relay.linkaddr_ = relay_link_addr_;
            relay.peeraddr_ = asiolink::IOAddress("fe80::1");
            relay.msg_type_ = DHCPV6_RELAY_FORW;
            relay.hop_count_ = 1;
            msg->relay_info_.push_back(relay);
        } else {
            // The test provided relay_info_, let's use that.
            msg->relay_info_ = relay_info_;
        }
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

void
Dhcp6Client::useHint(const uint32_t pref_lft, const uint32_t valid_lft,
                     const uint8_t len, const std::string& prefix) {
    prefix_hint_.reset(new Option6IAPrefix(D6O_IAPREFIX,
                                           asiolink::IOAddress(prefix),
                                           len, pref_lft, valid_lft));
}

void
Dhcp6Client::addExtraOption(const OptionPtr& opt) {
    extra_options_.insert(std::make_pair(opt->getType(), opt));
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
