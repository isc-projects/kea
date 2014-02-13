// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp_ddns/ncr_udp.h>
#include <dhcpsrv/d2_client_cfg.h>
#include <dhcpsrv/dhcpsrv_log.h>

#include <string>

using namespace std;

namespace isc {
namespace dhcp {

D2ClientConfig::D2ClientConfig(const  bool enable_updates,
                               const isc::asiolink::IOAddress& server_ip,
                               const size_t server_port,
                               const dhcp_ddns::
                                     NameChangeProtocol& ncr_protocol,
                               const dhcp_ddns::
                                     NameChangeFormat& ncr_format,
                               const bool always_include_fqdn,
                               const bool override_no_update,
                               const bool override_client_update,
                               const bool replace_client_name,
                               const std::string& generated_prefix,
                               const std::string& qualifying_suffix)
    : enable_updates_(enable_updates),
    server_ip_(server_ip),
    server_port_(server_port),
    ncr_protocol_(ncr_protocol),
    ncr_format_(ncr_format),
    always_include_fqdn_(always_include_fqdn),
    override_no_update_(override_no_update),
    override_client_update_(override_client_update),
    replace_client_name_(replace_client_name),
    generated_prefix_(generated_prefix),
    qualifying_suffix_(qualifying_suffix) {
    validateContents();
}

D2ClientConfig::D2ClientConfig()
    : enable_updates_(false),
      server_ip_(isc::asiolink::IOAddress("0.0.0.0")),
      server_port_(0),
      ncr_protocol_(dhcp_ddns::NCR_UDP),
      ncr_format_(dhcp_ddns::FMT_JSON),
      always_include_fqdn_(false),
      override_no_update_(false),
      override_client_update_(false),
      replace_client_name_(false),
      generated_prefix_("myhost"),
      qualifying_suffix_("example.com") {
    validateContents();
}

D2ClientConfig::~D2ClientConfig(){};

void
D2ClientConfig::enableUpdates(bool enable) {
    enable_updates_ = enable;
}

void
D2ClientConfig::validateContents() {
    if (ncr_format_ != dhcp_ddns::FMT_JSON) {
        isc_throw(D2ClientError, "D2ClientConfig: NCR Format:"
                    << dhcp_ddns::ncrFormatToString(ncr_format_)
                    << " is not yet supported");
    }

    if (ncr_protocol_ != dhcp_ddns::NCR_UDP) {
        isc_throw(D2ClientError, "D2ClientConfig: NCR Protocol:"
                    << dhcp_ddns::ncrProtocolToString(ncr_protocol_)
                    << " is not yet supported");
    }

    /// @todo perhaps more validation we should do yet?
    /// Are there any invalid combinations of options we need to test against?
}

bool
D2ClientConfig::operator == (const D2ClientConfig& other) const {
    return ((enable_updates_ == other.enable_updates_) &&
            (server_ip_ == other.server_ip_) &&
            (server_port_ == other.server_port_) &&
            (ncr_protocol_ == other.ncr_protocol_) &&
            (ncr_format_ == other.ncr_format_) &&
            (always_include_fqdn_ == other.always_include_fqdn_) &&
            (override_no_update_ == other.override_no_update_) &&
            (override_client_update_ == other.override_client_update_) &&
            (replace_client_name_ == other.replace_client_name_) &&
            (generated_prefix_ == other.generated_prefix_) &&
            (qualifying_suffix_ == other.qualifying_suffix_));
}

bool
D2ClientConfig::operator != (const D2ClientConfig& other) const {
    return (!(*this == other));
}

std::string
D2ClientConfig::toText() const {
    std::ostringstream stream;

    stream << "enable_updates: " << (enable_updates_ ? "yes" : "no");
    if (enable_updates_) {
        stream << ", server_ip: " << server_ip_.toText()
               << ", server_port: " << server_port_
               << ", ncr_protocol: " << ncr_protocol_
               << ", ncr_format: " << ncr_format_
               << ", always_include_fqdn: " << (always_include_fqdn_ ?
                                                "yes" : "no")
               << ", override_no_update: " << (override_no_update_ ?
                                               "yes" : "no")
               << ", override_client_update: " << (override_client_update_ ?
                                                   "yes" : "no")
               << ", replace_client_name: " << (replace_client_name_ ?
                                                "yes" : "no")
               << ", generated_prefix: [" << generated_prefix_ << "]"
               << ", qualifying_suffix: [" << qualifying_suffix_ << "]";
    }

    return (stream.str());
}

std::ostream&
operator<<(std::ostream& os, const D2ClientConfig& config) {
    os << config.toText();
    return (os);
}

};  // namespace dhcp

};  // namespace isc
