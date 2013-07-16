// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option6_client_fqdn.h>
#include <dns/labelsequence.h>

namespace isc {
namespace dhcp {

Option6ClientFqdn::Option6ClientFqdn(const uint8_t flag,
                                     const std::string& domain_name,
                                     const DomainNameType domain_name_type)
    : Option(Option::V6, D6O_CLIENT_FQDN),
      flags_(flag),
      domain_name_(NULL),
      domain_name_type_(domain_name_type) {
    //  Check if flags are correct.
    checkFlags(flags_);

    try {
        domain_name_ = new isc::dns::Name(domain_name);

    } catch (const Exception& ex) {
        isc_throw(InvalidFqdnOptionDomainName, "invalid domain-name value: "
                  << domain_name);

    }
}

Option6ClientFqdn::Option6ClientFqdn(OptionBufferConstIter first,
                                     OptionBufferConstIter last)
    : Option(Option::V6, D6O_CLIENT_FQDN, first, last),
      domain_name_(NULL) {
}

Option6ClientFqdn::~Option6ClientFqdn() {
    delete (domain_name_);
}

bool
Option6ClientFqdn::getFlag(const Flag flag) const {
    // Caller should query for one of the: N, S or O flags. However, enumerator
    // value of 0x3 is valid (because it belongs to the range between the
    // lowest and highest enumerator). The value 0x3 represents two flags:
    // S and O and would cause ambiguity. Therefore, we selectively check
    // that the flag is equal to one of the explicit enumerator values. If
    // not, throw an exception.
    if (flag != FLAG_S && flag != FLAG_O && flag != FLAG_N) {
        isc_throw(InvalidFqdnOptionFlags, "invalid DHCPv6 Client FQDN"
                  << " Option flag specified, expected N, S or O");
    }

    return ((flags_ & flag) != 0);
}

void
Option6ClientFqdn::setFlag(const Flag flag, const bool set_flag) {
    // Check that flag is in range between 0x1 and 0x7. Note that this
    // allows to set or clear multiple flags concurrently.
    if (((flag & ~FLAG_MASK) != 0) || (flag == 0)) {
        isc_throw(InvalidFqdnOptionFlags, "invalid DHCPv6 Client FQDN"
                  << " Option flag " << std::hex
                  << static_cast<int>(flag) << std::dec
                  << "is being set. Expected combination of N, S and O");
    }

    // Copy the current flags into local variable. That way we will be able
    // to test new flags settings before applying them.
    uint8_t new_flag = flags_;
    if (set_flag) {
        new_flag |= flag;
    } else {
        new_flag &= ~flag;
    }

    // Check new flags. If they are valid, apply them.
    checkFlags(new_flag);
    flags_ = new_flag;
}

void
Option6ClientFqdn::pack(isc::util::OutputBuffer& buf) {
    // Header = option code and length.
    packHeader(buf);
    // Flags field.
    buf.writeUint8(flags_);
    // Domain name, encoded as a set of labels.
    isc::dns::LabelSequence labels(*domain_name_);
    if (labels.getDataLength() > 0) {
        size_t read_len = 0;
        const uint8_t* data = labels.getData(&read_len);
        if (domain_name_type_ == PARTIAL) {
            --read_len;
        }
        buf.writeData(data, read_len);
    }


}

void
Option6ClientFqdn::unpack(OptionBufferConstIter,
                          OptionBufferConstIter) {
}

std::string
Option6ClientFqdn::toText(int) {
    return std::string();
}

uint16_t
Option6ClientFqdn::len() {
    // If domain name is partial, the NULL terminating character
    // is not included and the option length have to be adjusted.
    uint16_t domain_name_length = domain_name_type_ == FULL ?
        domain_name_->getLength() : domain_name_->getLength() - 1;

    return (getHeaderLen() + FLAG_FIELD_LEN + domain_name_length);
}

void
Option6ClientFqdn::checkFlags(const uint8_t flags) {
    // The Must Be Zero (MBZ) bits must not be set.
    if ((flags & ~FLAG_MASK) != 0) {
        isc_throw(InvalidFqdnOptionFlags,
                  "invalid DHCPv6 Client FQDN Option flags: 0x"
                  << std::hex << static_cast<int>(flags) << std::dec);
    }

    // According to RFC 4704, section 4.1. if the N bit is 1, the S bit
    // MUST be 0. Checking it here.
    if ((flags & (FLAG_N | FLAG_S)) == (FLAG_N | FLAG_S)) {
        isc_throw(InvalidFqdnOptionFlags,
                  "both N and S flag of the DHCPv6 Client FQDN Option are set."
                  << " According to RFC 4704, if the N bit is 1 the S bit"
                  << " MUST be 0");
    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
