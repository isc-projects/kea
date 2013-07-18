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
#include <util/buffer.h>
#include <util/io_utilities.h>
#include <util/strutil.h>
#include <sstream>

namespace isc {
namespace dhcp {

class Option6ClientFqdnImpl {
public:
    uint8_t flags_;
    boost::shared_ptr<isc::dns::Name> domain_name_;
    Option6ClientFqdn::DomainNameType domain_name_type_;

    Option6ClientFqdnImpl(const uint8_t flag,
                          const std::string& domain_name,
                          const Option6ClientFqdn::DomainNameType name_type);

    Option6ClientFqdnImpl(OptionBufferConstIter first,
                          OptionBufferConstIter last);

    Option6ClientFqdnImpl(const Option6ClientFqdnImpl& source);

    Option6ClientFqdnImpl& operator=(const Option6ClientFqdnImpl& source);

    void setDomainName(const std::string& domain_name,
                       const Option6ClientFqdn::DomainNameType name_type);

    static void checkFlags(const uint8_t flags);

    void parseWireData(OptionBufferConstIter first,
                       OptionBufferConstIter last);

};

Option6ClientFqdnImpl::
Option6ClientFqdnImpl(const uint8_t flag,
                      const std::string& domain_name,
                      const Option6ClientFqdn::DomainNameType name_type)
    : flags_(flag),
      domain_name_(),
      domain_name_type_(name_type) {

    //  Check if flags are correct.
    checkFlags(flags_);
    // Set domain name. It may throw an exception if domain name has wrong
    // format.
    setDomainName(domain_name, name_type);
}

Option6ClientFqdnImpl::Option6ClientFqdnImpl(OptionBufferConstIter first,
                                             OptionBufferConstIter last) {
    parseWireData(first, last);
    // Verify that flags value was correct.
    checkFlags(flags_);
}

Option6ClientFqdnImpl::
Option6ClientFqdnImpl(const Option6ClientFqdnImpl& source)
    : flags_(source.flags_),
      domain_name_(new isc::dns::Name(*source.domain_name_)),
      domain_name_type_(source.domain_name_type_) {
}

Option6ClientFqdnImpl&
Option6ClientFqdnImpl::operator=(const Option6ClientFqdnImpl& source) {
    domain_name_.reset(new isc::dns::Name(*source.domain_name_));

    // This assignment should be exception safe.
    flags_ = source.flags_;
    domain_name_type_ = source.domain_name_type_;

    return (*this);
}

void
Option6ClientFqdnImpl::
setDomainName(const std::string& domain_name,
              const Option6ClientFqdn::DomainNameType name_type) {
    // domain-name must be trimmed. Otherwise, string comprising spaces only
    // would be treated as a fully qualified name.
    std::string name = isc::util::str::trim(domain_name);
    if (name.empty()) {
        if (name_type == Option6ClientFqdn::FULL) {
            isc_throw(InvalidFqdnOptionDomainName,
                      "fully qualified domain-name must not be empty"
                      << " when setting new domain-name for DHCPv6 Client"
                      << " FQDN Option");
        }
        // The special case when domain-name is empty is marked by setting the
        // pointer to the domain-name object to NULL.
        domain_name_.reset();

    } else {
        try {
            domain_name_.reset(new isc::dns::Name(name));
            domain_name_type_ = name_type;

        } catch (const Exception& ex) {
            isc_throw(InvalidFqdnOptionDomainName, "invalid domain-name value '"
                      << domain_name << "' when setting new domain-name for"
                      << " DHCPv6 Client FQDN Option");

        }
    }
}

void
Option6ClientFqdnImpl::checkFlags(const uint8_t flags) {
    // The Must Be Zero (MBZ) bits must not be set.
    if ((flags & ~Option6ClientFqdn::FLAG_MASK) != 0) {
        isc_throw(InvalidFqdnOptionFlags,
                  "invalid DHCPv6 Client FQDN Option flags: 0x"
                  << std::hex << static_cast<int>(flags) << std::dec);
    }

    // According to RFC 4704, section 4.1. if the N bit is 1, the S bit
    // MUST be 0. Checking it here.
    if ((flags & (Option6ClientFqdn::FLAG_N | Option6ClientFqdn::FLAG_S))
        == (Option6ClientFqdn::FLAG_N | Option6ClientFqdn::FLAG_S)) {
        isc_throw(InvalidFqdnOptionFlags,
                  "both N and S flag of the DHCPv6 Client FQDN Option are set."
                  << " According to RFC 4704, if the N bit is 1 the S bit"
                  << " MUST be 0");
    }
}

void
Option6ClientFqdnImpl::parseWireData(OptionBufferConstIter first,
                                     OptionBufferConstIter last) {

    // Buffer must comprise at least one byte with the flags.
    // The domain-name may be empty.
    if (std::distance(first, last) < Option6ClientFqdn::FLAG_FIELD_LEN) {
        isc_throw(OutOfRange, "DHCPv6 Client FQDN Option ("
                  << D6O_CLIENT_FQDN << ") is truncated");
    }

    // Parse flags
    flags_ = *(first++);

    // Parse domain-name if any.
    if (std::distance(first, last) > 0) {
        // The FQDN may comprise a partial domain-name. In this case it lacks
        // terminating 0. If this is the case, we will need to add zero at
        // the end because Name object constructor requires it.
        if (*(last - 1) != 0) {
            // Create temporary buffer and add terminating zero.
            OptionBuffer buf(first, last);
            buf.push_back(0);
            // Reset domain name.
            isc::util::InputBuffer name_buf(&buf[0], buf.size());
            domain_name_.reset(new isc::dns::Name(name_buf));
            // Terminating zero was missing, so set the domain-name type
            // to partial.
            domain_name_type_ = Option6ClientFqdn::PARTIAL;
        } else {
            // We are dealing with fully qualified domain name so there is
            // no need to add terminating zero. Simply pass the buffer to
            // Name object constructor.
            isc::util::InputBuffer name_buf(&(*first),
                                            std::distance(first, last));
            domain_name_.reset(new isc::dns::Name(name_buf));
            // Set the domain-type to fully qualified domain name.
            domain_name_type_ = Option6ClientFqdn::FULL;
        }
    }
}

Option6ClientFqdn::Option6ClientFqdn(const uint8_t flag)
    : Option(Option::V6, D6O_CLIENT_FQDN),
      impl_(new Option6ClientFqdnImpl(flag, "", PARTIAL)) {
}

Option6ClientFqdn::Option6ClientFqdn(const uint8_t flag,
                                     const std::string& domain_name,
                                     const DomainNameType domain_name_type)
    : Option(Option::V6, D6O_CLIENT_FQDN),
      impl_(new Option6ClientFqdnImpl(flag, domain_name, domain_name_type)) {
}

Option6ClientFqdn::Option6ClientFqdn(OptionBufferConstIter first,
                                     OptionBufferConstIter last)
    : Option(Option::V6, D6O_CLIENT_FQDN, first, last),
      impl_(new Option6ClientFqdnImpl(first, last)) {
}

Option6ClientFqdn::~Option6ClientFqdn() {
    delete(impl_);
}

Option6ClientFqdn::Option6ClientFqdn(const Option6ClientFqdn& source)
    : Option(source),
      impl_(new Option6ClientFqdnImpl(*source.impl_)) {
}

Option6ClientFqdn&
Option6ClientFqdn::operator=(const Option6ClientFqdn& source) {
    Option6ClientFqdnImpl* old_impl = impl_;
    impl_ = new Option6ClientFqdnImpl(*source.impl_);
    delete(old_impl);
    return (*this);
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

    return ((impl_->flags_ & flag) != 0);
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
    uint8_t new_flag = impl_->flags_;
    if (set_flag) {
        new_flag |= flag;
    } else {
        new_flag &= ~flag;
    }

    // Check new flags. If they are valid, apply them.
    Option6ClientFqdnImpl::checkFlags(new_flag);
    impl_->flags_ = new_flag;
}

std::string
Option6ClientFqdn::getDomainName() const {
    if (impl_->domain_name_) {
        return (impl_->domain_name_->toText(impl_->domain_name_type_ ==
                                            PARTIAL));
    }
    // If an object holding domain-name is NULL it means that the domain-name
    // is empty.
    return ("");
}

void
Option6ClientFqdn::setDomainName(const std::string& domain_name,
                                 const DomainNameType domain_name_type) {
    impl_->setDomainName(domain_name, domain_name_type);
}

void
Option6ClientFqdn::resetDomainName() {
    setDomainName("", PARTIAL);
}

Option6ClientFqdn::DomainNameType
Option6ClientFqdn::getDomainNameType() const {
    return (impl_->domain_name_type_);
}

void
Option6ClientFqdn::pack(isc::util::OutputBuffer& buf) {
    // Header = option code and length.
    packHeader(buf);
    // Flags field.
    buf.writeUint8(impl_->flags_);
    // Domain name, encoded as a set of labels.
    isc::dns::LabelSequence labels(*impl_->domain_name_);
    if (labels.getDataLength() > 0) {
        size_t read_len = 0;
        const uint8_t* data = labels.getData(&read_len);
        if (impl_->domain_name_type_ == PARTIAL) {
            --read_len;
        }
        buf.writeData(data, read_len);
    }


}

void
Option6ClientFqdn::unpack(OptionBufferConstIter first,
                          OptionBufferConstIter last) {
    setData(first, last);
    impl_->parseWireData(first, last);
}

std::string
Option6ClientFqdn::toText(int indent) {
    std::ostringstream stream;
    std::string in(indent, ' '); // base indentation
    std::string in_add(2, ' ');  // second-level indentation is 2 spaces long
    stream << in  << "type=" << type_ << "(CLIENT_FQDN)" << std::endl
           << in << "flags:" << std::endl
           << in << in_add << "N=" << (getFlag(FLAG_N) ? "1" : "0") << std::endl
           << in << in_add << "O=" << (getFlag(FLAG_O) ? "1" : "0") << std::endl
           << in << in_add << "S=" << (getFlag(FLAG_S) ? "1" : "0") << std::endl
           << in << "domain-name='" << getDomainName() << "' ("
           << (getDomainNameType() == PARTIAL ? "partial" : "full")
           << ")" << std::endl;

    return (stream.str());
}

uint16_t
Option6ClientFqdn::len() {
    // If domain name is partial, the NULL terminating character
    // is not included and the option length have to be adjusted.
    uint16_t domain_name_length = impl_->domain_name_type_ == FULL ?
        impl_->domain_name_->getLength() : impl_->domain_name_->getLength() - 1;

    return (getHeaderLen() + FLAG_FIELD_LEN + domain_name_length);
}

} // end of isc::dhcp namespace
} // end of isc namespace
