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

#include <dhcp/dhcp4.h>
#include <dhcp/option4_client_fqdn.h>
#include <dns/labelsequence.h>
#include <util/buffer.h>
#include <util/io_utilities.h>
#include <util/strutil.h>
#include <sstream>

namespace isc {
namespace dhcp {

class Option4ClientFqdnImpl {
public:
    uint8_t flags_;
    Option4ClientFqdn::Rcode rcode1_;
    Option4ClientFqdn::Rcode rcode2_;
    boost::shared_ptr<isc::dns::Name> domain_name_;
    Option4ClientFqdn::DomainNameType domain_name_type_;

    Option4ClientFqdnImpl(const uint8_t flag,
                          const Option4ClientFqdn::Rcode& rcode,
                          const std::string& domain_name,
                          const Option4ClientFqdn::DomainNameType name_type);

    Option4ClientFqdnImpl(OptionBufferConstIter first,
                          OptionBufferConstIter last);

    Option4ClientFqdnImpl(const Option4ClientFqdnImpl& source);

    Option4ClientFqdnImpl& operator=(const Option4ClientFqdnImpl& source);

    void setDomainName(const std::string& domain_name,
                       const Option4ClientFqdn::DomainNameType name_type);

    static void checkFlags(const uint8_t flags);

    void parseWireData(OptionBufferConstIter first,
                       OptionBufferConstIter last);

    void parseCanonicalDomainName(OptionBufferConstIter first,
                                  OptionBufferConstIter last);

    void
    parseASCIIDomainName(OptionBufferConstIter first,
                         OptionBufferConstIter last);

};

Option4ClientFqdnImpl::
Option4ClientFqdnImpl(const uint8_t flag,
                      const Option4ClientFqdn::Rcode& rcode,
                      const std::string& domain_name,
                      const Option4ClientFqdn::DomainNameType name_type)
    : flags_(flag),
      rcode1_(rcode),
      rcode2_(rcode),
      domain_name_(),
      domain_name_type_(name_type) {

    //  Check if flags are correct.
    checkFlags(flags_);
    // Set domain name. It may throw an exception if domain name has wrong
    // format.
    setDomainName(domain_name, name_type);
}

Option4ClientFqdnImpl::Option4ClientFqdnImpl(OptionBufferConstIter first,
                                             OptionBufferConstIter last)
    : rcode1_(Option4ClientFqdn::RCODE_CLIENT()),
      rcode2_(Option4ClientFqdn::RCODE_CLIENT()) {
    parseWireData(first, last);
    // Verify that flags value was correct.
    checkFlags(flags_);
}

Option4ClientFqdnImpl::
Option4ClientFqdnImpl(const Option4ClientFqdnImpl& source)
    : flags_(source.flags_),
      rcode1_(source.rcode1_),
      rcode2_(source.rcode2_),
      domain_name_(),
      domain_name_type_(source.domain_name_type_) {
    if (source.domain_name_) {
        domain_name_.reset(new isc::dns::Name(*source.domain_name_));
    }
}

Option4ClientFqdnImpl&
Option4ClientFqdnImpl::operator=(const Option4ClientFqdnImpl& source) {
    domain_name_.reset(new isc::dns::Name(*source.domain_name_));

    // Assignment is exception safe.
    flags_ = source.flags_;
    rcode1_ = source.rcode1_;
    rcode2_ = source.rcode2_;
    domain_name_type_ = source.domain_name_type_;

    return (*this);
}

void
Option4ClientFqdnImpl::
setDomainName(const std::string& domain_name,
              const Option4ClientFqdn::DomainNameType name_type) {
    // domain-name must be trimmed. Otherwise, string comprising spaces only
    // would be treated as a fully qualified name.
    std::string name = isc::util::str::trim(domain_name);
    if (name.empty()) {
        if (name_type == Option4ClientFqdn::FULL) {
            isc_throw(InvalidOption4ClientFqdnDomainName,
                      "fully qualified domain-name must not be empty"
                      << " when setting new domain-name for DHCPv4 Client"
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
            isc_throw(InvalidOption4ClientFqdnDomainName,
                      "invalid domain-name value '"
                      << domain_name << "' when setting new domain-name for"
                      << " DHCPv4 Client FQDN Option");

        }
    }
}

void
Option4ClientFqdnImpl::checkFlags(const uint8_t flags) {
    // The Must Be Zero (MBZ) bits must not be set.
    if ((flags & ~Option4ClientFqdn::FLAG_MASK) != 0) {
        isc_throw(InvalidOption4ClientFqdnFlags,
                  "invalid DHCPv4 Client FQDN Option flags: 0x"
                  << std::hex << static_cast<int>(flags) << std::dec);
    }

    // According to RFC 4702, section 2.1. if the N bit is 1, the S bit
    // MUST be 0. Checking it here.
    if ((flags & (Option4ClientFqdn::FLAG_N | Option4ClientFqdn::FLAG_S))
        == (Option4ClientFqdn::FLAG_N | Option4ClientFqdn::FLAG_S)) {
        isc_throw(InvalidOption4ClientFqdnFlags,
                  "both N and S flag of the DHCPv4 Client FQDN Option are set."
                  << " According to RFC 4702, if the N bit is 1 the S bit"
                  << " MUST be 0");
    }
}

void
Option4ClientFqdnImpl::parseWireData(OptionBufferConstIter first,
                                     OptionBufferConstIter last) {

    // Buffer must comprise at least one byte with the flags.
    // The domain-name may be empty.
    if (std::distance(first, last) < Option4ClientFqdn::FIXED_FIELDS_LEN) {
        isc_throw(OutOfRange, "DHCPv4 Client FQDN Option ("
                  << DHO_FQDN << ") is truncated");
    }

    // Parse flags
    flags_ = *(first++);

    // Parse RCODE1 and RCODE2.
    rcode1_ = Option4ClientFqdn::Rcode(*(first++));
    rcode2_ = Option4ClientFqdn::Rcode(*(first++));

    try {
        if ((flags_ & Option4ClientFqdn::FLAG_E) != 0) {
            parseCanonicalDomainName(first, last);

        } else {
            parseASCIIDomainName(first, last);

        }
    } catch (const Exception& ex) {
        isc_throw(InvalidOption4ClientFqdnDomainName,
                  "failed to parse the domain-name in DHCPv4 Client FQDN"
                  << " Option: " << ex.what());
    }
}

void
Option4ClientFqdnImpl::parseCanonicalDomainName(OptionBufferConstIter first,
                                                OptionBufferConstIter last) {
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
            domain_name_type_ = Option4ClientFqdn::PARTIAL;
        } else {
            // We are dealing with fully qualified domain name so there is
            // no need to add terminating zero. Simply pass the buffer to
            // Name object constructor.
            isc::util::InputBuffer name_buf(&(*first),
                                            std::distance(first, last));
            domain_name_.reset(new isc::dns::Name(name_buf));
            // Set the domain-type to fully qualified domain name.
            domain_name_type_ = Option4ClientFqdn::FULL;
        }
    }
}

void
Option4ClientFqdnImpl::parseASCIIDomainName(OptionBufferConstIter first,
                                            OptionBufferConstIter last) {
    if (std::distance(first, last) > 0) {
        std::string domain_name(first, last);
        domain_name_.reset(new isc::dns::Name(domain_name));
        domain_name_type_ = domain_name[domain_name.length() - 1] == '.' ?
            Option4ClientFqdn::FULL : Option4ClientFqdn::PARTIAL;
    }
}

Option4ClientFqdn::Option4ClientFqdn(const uint8_t flag, const Rcode& rcode)
    : Option(Option::V4, DHO_FQDN),
      impl_(new Option4ClientFqdnImpl(flag, rcode, "", PARTIAL)) {
}

Option4ClientFqdn::Option4ClientFqdn(const uint8_t flag,
                                     const Rcode& rcode,
                                     const std::string& domain_name,
                                     const DomainNameType domain_name_type)
    : Option(Option::V4, DHO_FQDN),
      impl_(new Option4ClientFqdnImpl(flag, rcode, domain_name,
                                      domain_name_type)) {
}

Option4ClientFqdn::Option4ClientFqdn(OptionBufferConstIter first,
                                     OptionBufferConstIter last)
    : Option(Option::V4, DHO_FQDN, first, last),
      impl_(new Option4ClientFqdnImpl(first, last)) {
}

Option4ClientFqdn::~Option4ClientFqdn() {
    delete(impl_);
}

Option4ClientFqdn::Option4ClientFqdn(const Option4ClientFqdn& source)
    : Option(source),
      impl_(new Option4ClientFqdnImpl(*source.impl_)) {
}

Option4ClientFqdn&
Option4ClientFqdn::operator=(const Option4ClientFqdn& source) {
    Option4ClientFqdnImpl* old_impl = impl_;
    impl_ = new Option4ClientFqdnImpl(*source.impl_);
    delete(old_impl);
    return (*this);
}

bool
Option4ClientFqdn::getFlag(const Flag flag) const {
    // Caller should query for one of the: E, N, S or O flags. However, there 
    // are valid enumerator values which should not be accepted by this function.
    // For example a value of 0x3 is valid (because it belongs to the range between the
    // lowest and highest enumerator). The value 0x3 represents two flags:
    // S and O and would cause ambiguity. Therefore, we selectively check
    // that the flag is equal to one of the explicit enumerator values. If
    // not, throw an exception.
    if (flag != FLAG_S && flag != FLAG_O && flag != FLAG_N && flag != FLAG_E) {
        isc_throw(InvalidOption4ClientFqdnFlags, "invalid DHCPv4 Client FQDN"
                  << " Option flag specified, expected E, N, S or O");
    }

    return ((impl_->flags_ & flag) != 0);
}

void
Option4ClientFqdn::setFlag(const Flag flag, const bool set_flag) {
    // Check that flag is in range between 0x1 and 0x7. Note that this
    // allows to set or clear multiple flags concurrently.
    if (((flag & ~FLAG_MASK) != 0) || (flag == 0)) {
        isc_throw(InvalidOption4ClientFqdnFlags, "invalid DHCPv4 Client FQDN"
                  << " Option flag " << std::hex
                  << static_cast<int>(flag) << std::dec
                  << "is being set. Expected combination of E, N, S and O");
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
    Option4ClientFqdnImpl::checkFlags(new_flag);
    impl_->flags_ = new_flag;
}

void
Option4ClientFqdn::setRcode(const Rcode& rcode) {
    impl_->rcode1_ = rcode;
    impl_->rcode2_ = rcode;
}

void
Option4ClientFqdn::resetFlags() {
    impl_->flags_ = 0;
}

std::string
Option4ClientFqdn::getDomainName() const {
    if (impl_->domain_name_) {
        return (impl_->domain_name_->toText(impl_->domain_name_type_ ==
                                            PARTIAL));
    }
    // If an object holding domain-name is NULL it means that the domain-name
    // is empty.
    return ("");
}

void
Option4ClientFqdn::packDomainName(isc::util::OutputBuffer& buf) const {
    if (getFlag(FLAG_E)) {
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

    } else {
        std::string domain_name = impl_->domain_name_->toText();
        buf.writeData(&domain_name[0], domain_name.size());

    }
}

void
Option4ClientFqdn::setDomainName(const std::string& domain_name,
                                 const DomainNameType domain_name_type) {
    impl_->setDomainName(domain_name, domain_name_type);
}

void
Option4ClientFqdn::resetDomainName() {
    setDomainName("", PARTIAL);
}

Option4ClientFqdn::DomainNameType
Option4ClientFqdn::getDomainNameType() const {
    return (impl_->domain_name_type_);
}

void
Option4ClientFqdn::pack(isc::util::OutputBuffer& buf) {
    // Header = option code and length.
    packHeader(buf);
    // Flags field.
    buf.writeUint8(impl_->flags_);
    // RCODE1 and RCODE2
    buf.writeUint8(impl_->rcode1_.getCode());
    buf.writeUint8(impl_->rcode2_.getCode());
    // Domain name.
    packDomainName(buf);
}

void
Option4ClientFqdn::unpack(OptionBufferConstIter first,
                          OptionBufferConstIter last) {
    setData(first, last);
    impl_->parseWireData(first, last);
}

std::string
Option4ClientFqdn::toText(int indent) {
    std::ostringstream stream;
    std::string in(indent, ' '); // base indentation
    std::string in_add(2, ' ');  // second-level indentation is 2 spaces long
    stream << in  << "type=" << type_ << "(CLIENT_FQDN)" << std::endl
           << in << "flags:" << std::endl
           << in << in_add << "N=" << (getFlag(FLAG_N) ? "1" : "0") << std::endl
           << in << in_add << "E=" << (getFlag(FLAG_E) ? "1" : "0") << std::endl
           << in << in_add << "O=" << (getFlag(FLAG_O) ? "1" : "0") << std::endl
           << in << in_add << "S=" << (getFlag(FLAG_S) ? "1" : "0") << std::endl
           << in << "domain-name='" << getDomainName() << "' ("
           << (getDomainNameType() == PARTIAL ? "partial" : "full")
           << ")" << std::endl;

    return (stream.str());
}

uint16_t
Option4ClientFqdn::len() {
    // If domain name is partial, the NULL terminating character
    // is not included and the option length have to be adjusted.
    uint16_t domain_name_length = impl_->domain_name_type_ == FULL ?
        impl_->domain_name_->getLength() : impl_->domain_name_->getLength() - 1;

    return (getHeaderLen() + FIXED_FIELDS_LEN + domain_name_length);
}

} // end of isc::dhcp namespace
} // end of isc namespace
