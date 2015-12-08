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

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <util/buffer.h>
#include <boost/foreach.hpp>
#include <boost/pointer_cast.hpp>
#include <cstdlib>
#include <time.h>

using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Functor searching for the leases using a specified property.
///
/// @tparam BaseType Base type to which the property belongs: @c Lease or
/// @c Lease6.
/// @tparam PropertyType A type of the property, e.g. @c uint32_t for IAID.
/// @tparam MemberPointer A pointer to the member, e.g. @c &Lease6::iaid_.
template<typename BaseType, typename PropertyType,
         PropertyType BaseType::*MemberPointer>
struct getLeasesByPropertyFun {

    /// @brief Returns leases matching the specified condition.
    ///
    /// @param config DHCP client configuration structure holding leases.
    /// @param property A value of the lease property used to search the lease.
    /// @param equals A flag which indicates if the operator should search for
    /// the leases which property is equal to the value of @c property parameter
    /// (if true), or unequal (if false).
    /// @param [out] leases A vector in which the operator will store leases
    /// found.
    void operator()(const Dhcp6Client::Configuration& config,
                    const PropertyType& property, const bool equals,
                    std::vector<Lease6>& leases) {

        // Iterate over the leases and match the property with a given lease
        //field.
        for (typename std::vector<Lease6>::const_iterator lease =
                 config.leases_.begin(); lease != config.leases_.end();
             ++lease) {
            // Check if fulfils the condition.
            if ((equals && ((*lease).*MemberPointer) == property) ||
                (!equals && ((*lease).*MemberPointer) != property)) {
                // Found the matching lease.
                leases.push_back(*lease);
            }
        }
    }
};

}; // end of anonymous namespace

namespace isc {
namespace dhcp {
namespace test {

Dhcp6Client::Dhcp6Client() :
    relay_link_addr_("3000:1::1"),
    curr_transid_(0),
    dest_addr_(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
    duid_(generateDUID(DUID::DUID_LLT)),
    link_local_("fe80::3a60:77ff:fed5:cdef"),
    iface_name_("eth0"),
    srv_(boost::shared_ptr<NakedDhcpv6Srv>(new NakedDhcpv6Srv(0))),
    use_na_(false),
    use_pd_(false),
    use_relay_(false),
    use_oro_(false),
    use_client_id_(true),
    use_rapid_commit_(false),
    address_hint_(),
    prefix_hint_(),
    fqdn_(),
    na_iaid_(1234),
    pd_iaid_(5678),
    include_address_(true) {
}

Dhcp6Client::Dhcp6Client(boost::shared_ptr<NakedDhcpv6Srv>& srv) :
    relay_link_addr_("3000:1::1"),
    curr_transid_(0),
    dest_addr_(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
    duid_(generateDUID(DUID::DUID_LLT)),
    link_local_("fe80::3a60:77ff:fed5:cdef"),
    iface_name_("eth0"),
    srv_(srv),
    use_na_(false),
    use_pd_(false),
    use_relay_(false),
    use_oro_(false),
    use_client_id_(true),
    use_rapid_commit_(false),
    address_hint_(),
    prefix_hint_(),
    fqdn_(),
    na_iaid_(1234),
    pd_iaid_(5678),
    include_address_(true) {
}

void
Dhcp6Client::applyRcvdConfiguration(const Pkt6Ptr& reply, uint32_t state) {
    typedef OptionCollection Opts;
    // Get all options in the reply message and pick IA_NA, IA_PD and
    // Status code.
    Opts opts = reply->options_;

    // Let's try to get a MAC
    HWAddrPtr hwaddr = reply->getMAC(HWAddr::HWADDR_SOURCE_ANY);

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
            Lease6 lease;
            lease.type_ = (ia->getType() == D6O_IA_NA ? Lease::TYPE_NA : Lease::TYPE_PD);
            lease.iaid_ = ia->getIAID();

            switch (ia_opt->getType()) {
            case D6O_IAADDR:
                {
                    Option6IAAddrPtr iaaddr = boost::dynamic_pointer_cast<
                        Option6IAAddr>(ia_opt);

                    if (iaaddr) {
                        lease = Lease6(Lease::TYPE_NA,
                                       iaaddr->getAddress(),
                                       duid_, ia->getIAID(),
                                       iaaddr->getPreferred(),
                                       iaaddr->getValid(),
                                       ia->getT1(), ia->getT2(), 0,
                                       hwaddr);
                        lease.cltt_ = time(NULL);
                        lease.state_ = state;
                        applyLease(lease);
                    }
                }
                break;

            case D6O_IAPREFIX:
                {
                    Option6IAPrefixPtr iaprefix = boost::dynamic_pointer_cast<
                        Option6IAPrefix>(ia_opt);

                    if (iaprefix) {
                        lease = Lease6(Lease::TYPE_PD,
                                       iaprefix->getAddress(), duid_,
                                       ia->getIAID(),
                                       iaprefix->getPreferred(),
                                       iaprefix->getValid(),
                                       ia->getT1(), ia->getT2(), 0,
                                       hwaddr,
                                       iaprefix->getLength());
                        lease.cltt_ = time(NULL);
                        applyLease(lease);
                    }
                }
                break;

            case D6O_STATUS_CODE:
                {
                    // Check if the server has sent status code. If no status
                    // code, assume the status code to be 0.
                    Option6StatusCodePtr status_code = boost::dynamic_pointer_cast<
                        Option6StatusCode>(ia->getOption(D6O_STATUS_CODE));
                    config_.status_codes_[ia->getIAID()] =
                        (status_code ? status_code->getStatusCode() : 0);
                }
                break;

            default:
                ; // no-op
            }

        }
    }

    // Get the global status code.
    Option6StatusCodePtr status_code = boost::dynamic_pointer_cast<
        Option6StatusCode>(reply->getOption(D6O_STATUS_CODE));
    // If status code has been sent, we override the default status code:
    // Success and record that we have received the status code.
    if (status_code) {
        config_.received_status_code_ = true;
        config_.status_code_ = status_code->getStatusCode();
    }
}

void
Dhcp6Client::applyLease(const Lease6& lease) {
    // Go over existing leases and try to match the one that we have.
    for (size_t i = 0; i < config_.leases_.size(); ++i) {
        Lease6 existing_lease = config_.leases_[i];
        // If IAID is matching and there is an actual address assigned
        // replace the current lease. The default address is :: if the
        // server hasn't sent the IA option. In this case, there is no
        // lease assignment so we keep what we have.
        if ((existing_lease.iaid_ == lease.iaid_)
            && (existing_lease.type_ == lease.type_)
            && (lease.addr_ != asiolink::IOAddress("::"))
            && (existing_lease.addr_ == lease.addr_)) {
            config_.leases_[i] = lease;
            return;
        }
    }

    // It is a new lease. Add it.
    config_.leases_.push_back(lease);
}

void
Dhcp6Client::appendFQDN() {
    if (fqdn_) {
        context_.query_->addOption(fqdn_);
    }
}

void
Dhcp6Client::appendRequestedIAs(const Pkt6Ptr& query) const {
    if (use_na_) {
        conditionallyAppendRequestedIA(query, D6O_IA_NA, na_iaid_);
    }

    if (use_pd_) {
        conditionallyAppendRequestedIA(query, D6O_IA_PD, pd_iaid_);
    }
}

void
Dhcp6Client::conditionallyAppendRequestedIA(const Pkt6Ptr& query,
                                            const uint8_t ia_type,
                                            const uint32_t iaid) const {
    // Get existing options of the specified type.
    OptionCollection options = query->getOptions(ia_type);
    std::pair<unsigned int, OptionPtr> option_pair;

    // Check if the option we want to add is already present.
    BOOST_FOREACH(option_pair, options) {
        Option6IAPtr ia = boost::dynamic_pointer_cast<Option6IA>(option_pair.second);
        // This shouldn't happen.
        if (!ia) {
            isc_throw(Unexpected, "Dhcp6Client: IA option has an invalid C++ type;"
                      " this is a programming issue");
        }
        // There is an option of the specific type already. If it has our
        // IAID we return here, because we don't want to duplicate the IA.
        // If IAID is different, we check other existing IAs.
        if (ia->getIAID() == iaid) {
            return;
        }
    }

    // If we're here, it means that there is no instance of our IA yet.
    Option6IAPtr requested_ia(new Option6IA(ia_type, iaid));
    // Add prefix hint if specified.
    if (prefix_hint_ && (ia_type == D6O_IA_PD)) {
        requested_ia->addOption(prefix_hint_);

    } else if (address_hint_ && (ia_type == D6O_IA_NA)) {
        requested_ia->addOption(address_hint_);
    }

    query->addOption(requested_ia);
}


void
Dhcp6Client::copyIAs(const Pkt6Ptr& source, const Pkt6Ptr& dest) {
    typedef OptionCollection Opts;
    // Copy IA_NAs.
    Opts opts = source->getOptions(D6O_IA_NA);
    for (Opts::const_iterator opt = opts.begin(); opt != opts.end(); ++opt) {
        // Only copy the entire IA_NA if there is at lease one IA Address option.
        if (opt->second->getOption(D6O_IAADDR)) {
            dest->addOption(opt->second);
        }
    }
    // Copy IA_PDs.
    opts = source->getOptions(D6O_IA_PD);
    for (Opts::const_iterator opt = opts.begin(); opt != opts.end(); ++opt) {
        // Only copy the entire IA_PD if there is at least one IA Prefix option
        // in it.
        if (opt->second->getOption(D6O_IAPREFIX)) {
            dest->addOption(opt->second);
        }
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
        // Only a valid lease should be included. Do not copy a
        // lease which have been marked by the server as invalid.
        if (leases[0].valid_lft_ == 0) {
            continue;
        }
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
    applyLease(lease);
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
    if (forced_server_id_) {
        context_.query_->addOption(forced_server_id_);
    }

    // Append requested (empty) IAs.
    appendRequestedIAs(context_.query_);

    if (use_rapid_commit_) {
        context_.query_->addOption(OptionPtr(new Option(Option::V6,
                                                        D6O_RAPID_COMMIT)));
    }
    // Add Client FQDN if configured.
    appendFQDN();

    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();

    // If using Rapid Commit and the server has responded with Reply,
    // let's apply received configuration.
    if (use_rapid_commit_ && context_.response_ &&
        context_.response_->getType() == DHCPV6_REPLY) {
        config_.clear();
        applyRcvdConfiguration(context_.response_);
    }
}

void
Dhcp6Client::doRequest() {
    Pkt6Ptr query = createMsg(DHCPV6_REQUEST);
    if (!forced_server_id_) {
        query->addOption(context_.response_->getOption(D6O_SERVERID));
    } else {
        query->addOption(forced_server_id_);
    }
    copyIAs(context_.response_, query);
    appendRequestedIAs(query);

    // Add Client FQDN if configured.
    appendFQDN();

    context_.query_ = query;
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();

    /// @todo sanity check here.

    // Apply new configuration only if the server has responded.
    if (context_.response_) {
        config_.clear();
        applyRcvdConfiguration(context_.response_);
    }
}

void
Dhcp6Client::doInfRequest() {
    context_.query_ = createMsg(DHCPV6_INFORMATION_REQUEST);

    // IA_NA, IA_TA and IA_PD options are not allowed in INF-REQUEST,
    // but hey! Let's test it.
    if (use_na_) {
        // Insert IA_NA option.
        context_.query_->addOption(Option6IAPtr(new Option6IA(D6O_IA_NA,
                                                              na_iaid_)));
    }

    // IA-PD is also not allowed. So it may be useful in testing, too.
    if (use_pd_) {
        // Insert IA_PD option.
        Option6IAPtr ia(new Option6IA(D6O_IA_PD, pd_iaid_));
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

    // During the Renew the client may request additional bindings per
    // RFC7550.
    appendRequestedIAs(query);

    // Add Client FQDN if configured.
    appendFQDN();

    context_.query_ = query;
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();
    // Apply configuration only if the server has responded.
    if (context_.response_) {
        config_.clear();
        applyRcvdConfiguration(context_.response_);
    }
}

void
Dhcp6Client::doRebind() {
    Pkt6Ptr query = createMsg(DHCPV6_REBIND);
    copyIAsFromLeases(query);

    // During the Rebind the client may request additional bindings per
    // RFC7550.
    appendRequestedIAs(query);

    // Add Client FQDN if configured.
    appendFQDN();

    context_.query_ = query;
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();
    // Apply configuration only if the server has responded.
    if (context_.response_) {
        config_.clear();
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
        config_.resetGlobalStatusCode();
        applyRcvdConfiguration(context_.response_);
    }
}

void
Dhcp6Client::doDecline() {
    Pkt6Ptr query = createMsg(DHCPV6_DECLINE);
    if (!forced_server_id_) {
        query->addOption(context_.response_->getOption(D6O_SERVERID));
    } else {
        query->addOption(forced_server_id_);
    }

    generateIAFromLeases(query);

    context_.query_ = query;
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();

    // Apply new configuration only if the server has responded.
    if (context_.response_) {
        config_.clear();
        applyRcvdConfiguration(context_.response_);
    }
}

void
Dhcp6Client::generateIAFromLeases(const Pkt6Ptr& query) {
    /// @todo: add support for IAPREFIX here.

    if (!use_na_) {
        // If we're told to not use IA_NA at all, there's nothing to be done here
        return;
    }

    for (std::vector<Lease6>::const_iterator lease = config_.leases_.begin();
         lease != config_.leases_.end(); ++lease) {
        if (lease->type_ != Lease::TYPE_NA) {
            continue;
        }

        Option6IAPtr ia(new Option6IA(D6O_IA_NA, lease->iaid_));

        if (include_address_) {
            ia->addOption(OptionPtr(new Option6IAAddr(D6O_IAADDR,
                  lease->addr_, lease->preferred_lft_, lease->valid_lft_)));
        }
        query->addOption(ia);
    }
}

void
Dhcp6Client::fastFwdTime(const uint32_t secs) {
    // Iterate over all leases and move their cltt backwards.
    for (size_t i = 0; i < config_.leases_.size(); ++i) {
        config_.leases_[i].cltt_ -= secs;
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
    for (std::vector<Lease6>::const_iterator lease = config_.leases_.begin();
         lease != config_.leases_.end(); ++lease) {
        iaids.insert(lease->iaid_);
    }
    return (iaids);
}

std::vector<Lease6>
Dhcp6Client::getLeasesByIAID(const uint32_t iaid) const {
    std::vector<Lease6> leases;
    getLeasesByProperty<Lease6, uint32_t, &Lease6::iaid_>(iaid, true, leases);
    return (leases);
}

template<typename BaseType, typename PropertyType, PropertyType BaseType::*MemberPointer>
void
Dhcp6Client::getLeasesByProperty(const PropertyType& property, const bool equals,
                                 std::vector<Lease6>& leases) const {
    getLeasesByPropertyFun<BaseType, PropertyType, MemberPointer> fun;
    fun(config_, property, equals, leases);
}

std::vector<Lease6>
Dhcp6Client::getLeasesByType(const Lease6::Type& lease_type) const {
    std::vector<Lease6> leases;
    getLeasesByProperty<Lease6, Lease6::Type, &Lease6::type_>(lease_type, true, leases);
    return (leases);
}

std::vector<Lease6>
Dhcp6Client::getLeasesWithNonZeroLifetime() const {
    std::vector<Lease6> leases;
    getLeasesByProperty<Lease, uint32_t, &Lease::valid_lft_>(0, false, leases);
    return (leases);
}

std::vector<Lease6>
Dhcp6Client::getLeasesWithZeroLifetime() const {
    std::vector<Lease6> leases;
    getLeasesByProperty<Lease, uint32_t, &Lease::valid_lft_>(0, true, leases);
    return (leases);
}

uint16_t
Dhcp6Client::getStatusCode(const uint32_t iaid) const {
    std::map<uint32_t, uint16_t>::const_iterator status_code =
        config_.status_codes_.find(iaid);
    if (status_code == config_.status_codes_.end()) {
        if (!getLeasesByIAID(iaid).empty()) {
            return (STATUS_Success);
        }

    } else {
        return (status_code->second);
    }

    return (0xFFFF);
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
    msg_copy->setIface(iface_name_);
    srv_->fakeReceive(msg_copy);
    srv_->run();
}

void
Dhcp6Client::useHint(const uint32_t pref_lft, const uint32_t valid_lft,
                     const std::string& address) {
    address_hint_.reset(new Option6IAAddr(D6O_IAADDR,
                                          asiolink::IOAddress(address),
                                          pref_lft, valid_lft));
}

void
Dhcp6Client::useHint(const uint32_t pref_lft, const uint32_t valid_lft,
                     const uint8_t len, const std::string& prefix) {
    prefix_hint_.reset(new Option6IAPrefix(D6O_IAPREFIX,
                                           asiolink::IOAddress(prefix),
                                           len, pref_lft, valid_lft));
}

void
Dhcp6Client::useFQDN(const uint8_t flags, const std::string& fqdn_name,
                     Option6ClientFqdn::DomainNameType fqdn_type) {
    fqdn_.reset(new Option6ClientFqdn(flags, fqdn_name, fqdn_type));
}

void
Dhcp6Client::addExtraOption(const OptionPtr& opt) {
    extra_options_.insert(std::make_pair(opt->getType(), opt));
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
