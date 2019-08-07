// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/pool.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <util/buffer.h>
#include <boost/foreach.hpp>
#include <boost/pointer_cast.hpp>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <utility>

using namespace isc::asiolink;
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
            // Check if fulfills the condition.
            if ((equals && ((*lease).*MemberPointer) == property) ||
                (!equals && ((*lease).*MemberPointer) != property)) {
                // Found the matching lease.
                leases.push_back(*lease);
            }
        }
    }
};

/// @brief Returns leases which belong to specified pool.
///
/// @param config DHCP client configuration structure holding leases.
/// @param pool Pool to which returned leases belong.
/// @param [out] leases A vector in which the function will store leases
/// found.
void getLeasesByPool(const Dhcp6Client::Configuration& config,
                     const Pool6& pool, std::vector<Lease6>& leases) {
    for (std::vector<Lease6>::const_iterator lease =
             config.leases_.begin(); lease != config.leases_.end();
         ++lease) {
        // Check if prefix in range.
        if (pool.inRange(lease->addr_)) {
            // Found the matching lease.
            leases.push_back(*lease);
        }
    }
}

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
    use_relay_(false),
    use_oro_(false),
    use_docsis_oro_(false),
    use_client_id_(true),
    use_rapid_commit_(false),
    client_ias_(),
    fqdn_(),
    interface_id_() {
}

Dhcp6Client::Dhcp6Client(boost::shared_ptr<NakedDhcpv6Srv>& srv) :
    relay_link_addr_("3000:1::1"),
    curr_transid_(0),
    dest_addr_(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
    duid_(generateDUID(DUID::DUID_LLT)),
    link_local_("fe80::3a60:77ff:fed5:cdef"),
    iface_name_("eth0"),
    srv_(srv),
    use_relay_(false),
    use_oro_(false),
    use_docsis_oro_(false),
    use_client_id_(true),
    use_rapid_commit_(false),
    client_ias_(),
    fqdn_(),
    interface_id_() {
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
                                       iaaddr->getValid(), 0,
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
                                       iaprefix->getValid(), 0,
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
    BOOST_FOREACH(const ClientIA& ia, client_ias_) {
        OptionCollection options =
            query->getOptions(ia.type_ == Lease::TYPE_NA ?
                              D6O_IA_NA : D6O_IA_PD);
        std::pair<unsigned int, OptionPtr> option_pair;
        Option6IAPtr existing_ia;
        BOOST_FOREACH(option_pair, options) {
            Option6IAPtr ia_opt =
                boost::dynamic_pointer_cast<Option6IA>(option_pair.second);
            // This shouldn't happen.
            if (!ia_opt) {
                isc_throw(Unexpected,
                          "Dhcp6Client: IA option has an invalid C++ type;"
                          " this is a programming issue");
            }
            if (ia_opt->getIAID() == ia.iaid_) {
                existing_ia = ia_opt;
            }
        }
        if (!existing_ia) {
            existing_ia.reset(new Option6IA(ia.type_ == Lease::TYPE_NA ?
                                            D6O_IA_NA : D6O_IA_PD, ia.iaid_));
            query->addOption(existing_ia);
        }

        bool option_exists = false;
        if ((ia.type_ == Lease::TYPE_NA) && !ia.prefix_.isV6Zero()) {
            Option6IAAddrPtr ia_addr(new Option6IAAddr(D6O_IAADDR, ia.prefix_,
                                                       0, 0));
            BOOST_FOREACH(option_pair, existing_ia->getOptions()) {
                Option6IAAddrPtr existing_addr = boost::dynamic_pointer_cast<
                    Option6IAAddr>(option_pair.second);
                if (existing_addr &&
                    (existing_addr->getAddress() == ia.prefix_)) {
                    option_exists = true;
                }
            }

            if (!option_exists) {
                existing_ia->addOption(ia_addr);
            }

        } else if ((ia.type_ == Lease::TYPE_PD) &&
                   (!ia.prefix_.isV6Zero() || (ia.prefix_len_ > 0))) {
            Option6IAPrefixPtr ia_prefix(new Option6IAPrefix(D6O_IAPREFIX,
                                                             ia.prefix_,
                                                             ia.prefix_len_,
                                                             0, 0));
            BOOST_FOREACH(option_pair, existing_ia->getOptions()) {
                Option6IAPrefixPtr existing_prefix =
                    boost::dynamic_pointer_cast<Option6IAPrefix>(option_pair.second);
                if (existing_prefix &&
                    (existing_prefix->getAddress() == ia.prefix_) &&
                    existing_prefix->getLength()) {
                    option_exists = true;
                }
            }

            if (!option_exists) {
                existing_ia->addOption(ia_prefix);
            }
        }
    }
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

    if (use_docsis_oro_) {
        OptionUint16ArrayPtr vendor_oro(new OptionUint16Array(Option::V6,
                                                              DOCSIS3_V6_ORO));
        vendor_oro->setValues(docsis_oro_);
        OptionPtr vendor(new OptionVendor(Option::V6, 4491));
        vendor->addOption(vendor_oro);
        msg->addOption(vendor);
    }

    // If there are any custom options specified, add them all to the message.
    if (!extra_options_.empty()) {
        for (OptionCollection::iterator opt = extra_options_.begin();
             opt != extra_options_.end(); ++opt) {
            msg->addOption(opt->second);
        }
    }

    // Add classes.
    for (ClientClasses::const_iterator cclass = classes_.cbegin();
         cclass != classes_.cend(); ++cclass) {
        msg->addClass(*cclass);
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
Dhcp6Client::doSolicit(const bool always_apply_config) {
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
    // let's apply received configuration. We also apply the configuration
    // for the Advertise if instructed to do so.
    if (context_.response_ &&
        (always_apply_config ||
         (use_rapid_commit_ &&
          context_.response_->getType() == DHCPV6_REPLY))) {
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

    context_.query_ = query;

    // Add Client FQDN if configured.
    appendFQDN();

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
    appendRequestedIAs(context_.query_);

    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();
    // Apply new configuration only if the server has responded.
    if (context_.response_) {
        config_.clear();
        applyRcvdConfiguration(context_.response_);
    }
}

void
Dhcp6Client::doRenew() {
    Pkt6Ptr query = createMsg(DHCPV6_RENEW);
    query->addOption(context_.response_->getOption(D6O_SERVERID));
    copyIAsFromLeases(query);

    // During the Renew the client may request additional bindings per
    // RFC 8415.
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
    // RFC 8415.
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
        config_.options_.clear();
        applyRcvdConfiguration(context_.response_);
    }
}

void
Dhcp6Client::doDecline(const bool include_address) {
    Pkt6Ptr query = createMsg(DHCPV6_DECLINE);
    if (!forced_server_id_) {
        query->addOption(context_.response_->getOption(D6O_SERVERID));
    } else {
        query->addOption(forced_server_id_);
    }

    generateIAFromLeases(query, include_address);

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
Dhcp6Client::doRelease() {
    Pkt6Ptr query = createMsg(DHCPV6_RELEASE);
    query->addOption(context_.response_->getOption(D6O_SERVERID));
    copyIAsFromLeases(query);

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
Dhcp6Client::generateIAFromLeases(const Pkt6Ptr& query,
                                  const bool include_address) {
    /// @todo: add support for IAPREFIX here.

    for (std::vector<Lease6>::const_iterator lease = config_.leases_.begin();
         lease != config_.leases_.end(); ++lease) {
        if (lease->type_ != Lease::TYPE_NA) {
            continue;
        }

        Option6IAPtr ia(new Option6IA(D6O_IA_NA, lease->iaid_));

        if (include_address) {
            ia->addOption(OptionPtr(new Option6IAAddr(D6O_IAADDR,
                  lease->addr_, lease->preferred_lft_, lease->valid_lft_)));
        }
        query->addOption(ia);
    }
}

void
Dhcp6Client::fastFwdTime(const uint32_t secs, const bool update_server) {
    // Iterate over all leases and move their cltt backwards.
    for (size_t i = 0; i < config_.leases_.size(); ++i) {
        config_.leases_[i].cltt_ -= secs;
        if (update_server) {
            Lease6Ptr lease(new Lease6(config_.leases_[i]));
            LeaseMgrFactory::instance().updateLease6(lease);
        }
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

std::vector<Lease6>
Dhcp6Client::getLeasesByAddress(const IOAddress& address) const {
    std::vector<Lease6> leases;
    getLeasesByProperty<Lease, IOAddress, &Lease::addr_>(address, true, leases);
    return (leases);
}

std::vector<Lease6>
Dhcp6Client::getLeasesByAddressRange(const IOAddress& first,
                                     const IOAddress& second) const {
    std::vector<Lease6> leases;
    getLeasesByPool(config_, Pool6(Lease::TYPE_NA, first, second), leases);
    return (leases);
}

std::vector<Lease6>
Dhcp6Client::getLeasesByPrefixPool(const asiolink::IOAddress& prefix,
                                   const uint8_t prefix_len,
                                   const uint8_t delegated_len) const {
    std::vector<Lease6> leases;
    getLeasesByPool(config_, Pool6(Lease::TYPE_PD, prefix, prefix_len,
                                   delegated_len), leases);
    return (leases);
}

bool
Dhcp6Client::hasLeaseForAddress(const asiolink::IOAddress& address) const {
    std::vector<Lease6> leases = getLeasesByAddress(address);
    return (!leases.empty());
}

bool
Dhcp6Client::hasLeaseForAddress(const asiolink::IOAddress& address,
                                const IAID& iaid) const {
    std::vector<Lease6> leases = getLeasesByAddress(address);
    BOOST_FOREACH(const Lease6& lease, leases) {
        if (lease.iaid_ == iaid) {
            return (true);
        }
    }
    return (false);
}

bool
Dhcp6Client::hasLeaseForAddressRange(const asiolink::IOAddress& first,
                                     const asiolink::IOAddress& last) const {
    std::vector<Lease6> leases = getLeasesByAddressRange(first, last);
    return (!leases.empty());
}

bool
Dhcp6Client::
hasLeaseWithZeroLifetimeForAddress(const asiolink::IOAddress& address) const {
    std::vector<Lease6> leases = getLeasesByAddress(address);
    BOOST_FOREACH(const Lease6& lease, leases) {
        if ((lease.preferred_lft_ == 0) && (lease.valid_lft_ == 0)) {
            return (true);
        }
    }
    return (false);
}


bool
Dhcp6Client::hasLeaseForPrefix(const asiolink::IOAddress& prefix,
                               const uint8_t prefix_len) const {
    std::vector<Lease6> leases = getLeasesByAddress(prefix);
    BOOST_FOREACH(const Lease6& lease, leases) {
        if (lease.prefixlen_ == prefix_len) {
            return (true);
        }
    }
    return (false);
}

bool
Dhcp6Client::hasLeaseForPrefix(const asiolink::IOAddress& prefix,
                               const uint8_t prefix_len,
                               const IAID& iaid) const {
    std::vector<Lease6> leases = getLeasesByAddress(prefix);
    BOOST_FOREACH(const Lease6& lease, leases) {
        if ((lease.prefixlen_ == prefix_len) &&
            (lease.iaid_ == iaid)) {
            return (true);
        }
    }
    return (false);
}

bool
Dhcp6Client::hasLeaseForPrefixPool(const asiolink::IOAddress& prefix,
                                   const uint8_t prefix_len,
                                   const uint8_t delegated_len) const {
    std::vector<Lease6> leases = getLeasesByPrefixPool(prefix, prefix_len,
                                                       delegated_len);
    return (!leases.empty());
}

bool
Dhcp6Client::hasLeaseWithZeroLifetimeForPrefix(const asiolink::IOAddress& prefix,
                                               const uint8_t prefix_len) const {
    std::vector<Lease6> leases = getLeasesByAddress(prefix);
    BOOST_FOREACH(const Lease6& lease, leases) {
        if ((lease.prefixlen_ == prefix_len) && (lease.preferred_lft_ == 0) &&
            (lease.valid_lft_ == 0)) {
            return (true);
        }
    }
    return (false);
}

bool
Dhcp6Client::hasOptionWithAddress(const uint16_t option_type,
                                  const std::string& expected_address) const {
    Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(config_.findOption(option_type));
    if (opt) {
        Option6AddrLst::AddressContainer addrs = opt->getAddresses();
        if (!addrs.empty()) {
            return (std::find(addrs.begin(), addrs.end(),
                              IOAddress(expected_address)) != addrs.end());
        }
    }
    return (false);
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

bool
Dhcp6Client::getTeeTimes(const uint32_t iaid, uint32_t& t1, uint32_t& t2) const {
    // Sanity check.
    if (!context_.response_) {
        return (false);
    }

    // Get all options in the response message and pick IA_NA, IA_PD.
    OptionCollection opts = context_.response_->options_;

    for (auto opt = opts.begin(); opt != opts.end(); ++opt) {
        Option6IAPtr ia = boost::dynamic_pointer_cast<Option6IA>(opt->second);
        if (!ia) {
            // This is not IA, so let's just skip it.
            continue;
        }
        if (ia->getIAID() != iaid) {
            // This is not the right IA, so let's just skip it.
            continue;
        }
        // Found the IA.
        t1 = ia->getT1();
        t2 = ia->getT2();
        return (true);
    }

    // Not found the IA.
    return (false);
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
Dhcp6Client::receiveResponse() {
    context_.response_ = receiveOneMsg();
    // If the server has responded, store the configuration received.
    if (context_.response_) {
        config_.clear();
        applyRcvdConfiguration(context_.response_);
    }
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

            // Interface identifier, if specified.
            if (interface_id_) {
                relay.options_.insert(std::make_pair(D6O_INTERFACE_ID, interface_id_));
            }

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

    // Copy classes
    const ClientClasses& classes = msg->getClasses();
    for (ClientClasses::const_iterator cclass = classes.cbegin();
         cclass != classes.cend(); ++cclass) {
        msg_copy->addClass(*cclass);
    }

    srv_->fakeReceive(msg_copy);

    try {
        // Invoke run_one instead of run, because we want to avoid triggering
        // IO service.
        srv_->run_one();
    } catch (...) {
        // Suppress errors, as the DHCPv6 server does.
    }
}

void
Dhcp6Client::requestAddress(const uint32_t iaid,
                            const asiolink::IOAddress& address) {
    client_ias_.push_back(ClientIA(Lease::TYPE_NA, iaid, address, 128));
}

void
Dhcp6Client::requestPrefix(const uint32_t iaid,
                           const uint8_t prefix_len,
                           const asiolink::IOAddress& prefix) {
    client_ias_.push_back(ClientIA(Lease::TYPE_PD, iaid, prefix, prefix_len));
}

void
Dhcp6Client::useInterfaceId(const std::string& interface_id) {
    OptionBuffer buf(interface_id.begin(), interface_id.end());
    interface_id_.reset(new Option(Option::V6, D6O_INTERFACE_ID, buf));
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

void
Dhcp6Client::clearExtraOptions() {
    extra_options_.clear();
}

void
Dhcp6Client::addClass(const ClientClass& client_class) {
    if (!classes_.contains(client_class)) {
        classes_.insert(client_class);
    }
}

void
Dhcp6Client::clearClasses() {
    classes_.clear();
}

void
Dhcp6Client::printConfiguration() const {

    // Print DUID
    std::cout << "Client " << (duid_ ? duid_->toText() : "(without duid)")
              << " got " << getLeaseNum() << " lease(s): ";

    // Print leases
    for (int i = 0; i < getLeaseNum(); i++) {
        Lease6 lease = getLease(i);
        std::cout << lease.addr_.toText() << " ";
    }

    /// @todo: Print many other parameters.
    std::cout << std::endl;
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
