// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Implements the logic for the Option6ClientFqdn class.
///
/// The purpose of the class is to separate the implementation details
/// of the Option4ClientFqdn class from the interface. This implementation
/// uses libdns classes to process FQDNs. At some point it may be
/// desired to split libdhcp++ from libdns. In such case the
/// implementation of this class may be changed. The declaration of the
/// Option6ClientFqdn class holds the pointer to implementation, so
/// the transition to a different implementation would not affect the
/// header file.
class Option4ClientFqdnImpl {
public:
    /// Holds flags carried by the option.
    uint8_t flags_;
    /// Holds RCODE1 and RCODE2 values.
    Option4ClientFqdn::Rcode rcode1_;
    Option4ClientFqdn::Rcode rcode2_;
    /// Holds the pointer to a domain name carried in the option.
    boost::shared_ptr<isc::dns::Name> domain_name_;
    /// Indicates whether domain name is partial or fully qualified.
    Option4ClientFqdn::DomainNameType domain_name_type_;

    /// @brief Constructor, from domain name.
    ///
    /// @param flags A value of the flags option field.
    /// @param rcode An object representing the RCODE1 and RCODE2 values.
    /// @param domain_name A domain name carried by the option given in the
    /// textual format.
    /// @param name_type A value which indicates whether domain-name is partial
    /// or fully qualified.
    Option4ClientFqdnImpl(const uint8_t flags,
                          const Option4ClientFqdn::Rcode& rcode,
                          const std::string& domain_name,
                          const Option4ClientFqdn::DomainNameType name_type);

    /// @brief Constructor, from wire data.
    ///
    /// @param first An iterator pointing to the begining of the option data
    /// in the wire format.
    /// @param last An iterator poiting to the end of the option data in the
    /// wire format.
    Option4ClientFqdnImpl(OptionBufferConstIter first,
                          OptionBufferConstIter last);

    /// @brief Copy constructor.
    ///
    /// @param source An object being copied.
    Option4ClientFqdnImpl(const Option4ClientFqdnImpl& source);

    /// @brief Assignment operator.
    ///
    /// @param source An object which is being assigned.
    Option4ClientFqdnImpl& operator=(const Option4ClientFqdnImpl& source);

    /// @brief Set a new domain name for the option.
    ///
    /// @param domain_name A new domain name to be assigned.
    /// @param name_type A value which indicates whether the domain-name is
    /// partial or fully qualified.
    void setDomainName(const std::string& domain_name,
                       const Option4ClientFqdn::DomainNameType name_type);

    /// @brief Check if flags are valid.
    ///
    /// In particular, this function checks if the N and S bits are not
    /// set to 1 in the same time.
    ///
    /// @param flags A value carried by the flags field of the option.
    /// @param check_mbz A boolean value which indicates if this function should
    /// check if the MBZ bits are set (if true). This parameter should be set
    /// to false when validating flags in the received message. This is because
    /// server should ignore MBZ bits in received messages.
    /// @throw InvalidOption6FqdnFlags if flags are invalid.
    static void checkFlags(const uint8_t flags, const bool check_mbz);

    /// @brief Parse the Option provided in the wire format.
    ///
    /// @param first An iterator pointing to the begining of the option data
    /// in the wire format.
    /// @param last An iterator poiting to the end of the option data in the
    /// wire format.
    void parseWireData(OptionBufferConstIter first,
                       OptionBufferConstIter last);

    /// @brief Parse domain-name encoded in the canonical format.
    ///
    void parseCanonicalDomainName(OptionBufferConstIter first,
                                  OptionBufferConstIter last);

    /// @brief Parse domain-name emcoded in the deprecated ASCII format.
    ///
    /// @param first An iterator pointing to the begining of the option data
    /// where domain-name is stored.
    /// @param last An iterator poiting to the end of the option data where
    /// domain-name is stored.
    void parseASCIIDomainName(OptionBufferConstIter first,
                              OptionBufferConstIter last);

};

Option4ClientFqdnImpl::
Option4ClientFqdnImpl(const uint8_t flags,
                      const Option4ClientFqdn::Rcode& rcode,
                      const std::string& domain_name,
                      // cppcheck 1.57 complains that const enum value is not passed
                      // by reference. Note that, it accepts the non-const enum value
                      // to be passed by value. In both cases it is unneccessary to
                      // pass the enum by reference.
                      // cppcheck-suppress passedByValue
                      const Option4ClientFqdn::DomainNameType name_type)
    : flags_(flags),
      rcode1_(rcode),
      rcode2_(rcode),
      domain_name_(),
      domain_name_type_(name_type) {

    //  Check if flags are correct. Also, check that MBZ bits are not set. If
    // they are, throw exception.
    checkFlags(flags_, true);
    // Set domain name. It may throw an exception if domain name has wrong
    // format.
    setDomainName(domain_name, name_type);
}

Option4ClientFqdnImpl::Option4ClientFqdnImpl(OptionBufferConstIter first,
                                             OptionBufferConstIter last)
    : rcode1_(Option4ClientFqdn::RCODE_CLIENT()),
      rcode2_(Option4ClientFqdn::RCODE_CLIENT()) {
    parseWireData(first, last);
    // Verify that flags value was correct. This constructor is used to parse
    // incoming packet, so don't check MBZ bits. They are ignored because we
    // don't want to discard the whole option because MBZ bits are set.
    checkFlags(flags_, false);
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
// This assignment operator handles assignment to self, it copies all
// required values.
// cppcheck-suppress operatorEqToSelf
Option4ClientFqdnImpl::operator=(const Option4ClientFqdnImpl& source) {
    if (source.domain_name_) {
        domain_name_.reset(new isc::dns::Name(*source.domain_name_));

    } else {
        domain_name_.reset();
    }

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
              // cppcheck 1.57 complains that const enum value is not passed
              // by reference. Note that, it accepts the non-const enum
              // to be passed by value. In both cases it is unneccessary to
              // pass the enum by reference.
              // cppcheck-suppress passedByValue
              const Option4ClientFqdn::DomainNameType name_type) {
    // domain-name must be trimmed. Otherwise, string comprising spaces only
    // would be treated as a fully qualified name.
    std::string name = isc::util::str::trim(domain_name);
    if (name.empty()) {
        if (name_type == Option4ClientFqdn::FULL) {
            isc_throw(InvalidOption4FqdnDomainName,
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

        } catch (const Exception& ex) {
            isc_throw(InvalidOption4FqdnDomainName,
                      "invalid domain-name value '"
                      << domain_name << "' when setting new domain-name for"
                      << " DHCPv4 Client FQDN Option");

        }
    }

    domain_name_type_ = name_type;
}

void
Option4ClientFqdnImpl::checkFlags(const uint8_t flags, const bool check_mbz) {
    // The Must Be Zero (MBZ) bits must not be set.
    if (check_mbz && ((flags & ~Option4ClientFqdn::FLAG_MASK) != 0)) {
        isc_throw(InvalidOption4FqdnFlags,
                  "invalid DHCPv4 Client FQDN Option flags: 0x"
                  << std::hex << static_cast<int>(flags) << std::dec);
    }

    // According to RFC 4702, section 2.1. if the N bit is 1, the S bit
    // MUST be 0. Checking it here.
    if ((flags & (Option4ClientFqdn::FLAG_N | Option4ClientFqdn::FLAG_S))
        == (Option4ClientFqdn::FLAG_N | Option4ClientFqdn::FLAG_S)) {
        isc_throw(InvalidOption4FqdnFlags,
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
        isc_throw(InvalidOption4FqdnDomainName,
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
// This assignment operator handles assignment to self, it uses copy
// constructor of Option4ClientFqdnImpl to copy all required values.
// cppcheck-suppress operatorEqToSelf
Option4ClientFqdn::operator=(const Option4ClientFqdn& source) {
    Option4ClientFqdnImpl* old_impl = impl_;
    impl_ = new Option4ClientFqdnImpl(*source.impl_);
    delete(old_impl);
    return (*this);
}

bool
Option4ClientFqdn::getFlag(const uint8_t flag) const {
    // Caller should query for one of the: E, N, S or O flags. Any other value
    /// is invalid and results in the exception.
    if (flag != FLAG_S && flag != FLAG_O && flag != FLAG_N && flag != FLAG_E) {
        isc_throw(InvalidOption4FqdnFlags, "invalid DHCPv4 Client FQDN"
                  << " Option flag specified, expected E, N, S or O");
    }

    return ((impl_->flags_ & flag) != 0);
}

void
Option4ClientFqdn::setFlag(const uint8_t flag, const bool set_flag) {
    // Check that flag is in range between 0x1 and 0x7. Although it is
    // discouraged this check doesn't preclude the caller from setting
    // multiple flags concurrently.
    if (((flag & ~FLAG_MASK) != 0) || (flag == 0)) {
        isc_throw(InvalidOption4FqdnFlags, "invalid DHCPv4 Client FQDN"
                  << " Option flag 0x" << std::hex
                  << static_cast<int>(flag) << std::dec
                  << " is being set. Expected combination of E, N, S and O");
    }

    // Copy the current flags into local variable. That way we will be able
    // to test new flags settings before applying them.
    uint8_t new_flag = impl_->flags_;
    if (set_flag) {
        new_flag |= flag;
    } else {
        new_flag &= ~flag;
    }

    // Check new flags. If they are valid, apply them. Also, check that MBZ
    // bits are not set.
    Option4ClientFqdnImpl::checkFlags(new_flag, true);
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
    // If domain-name is empty, do nothing.
    if (!impl_->domain_name_) {
        return;
    }

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
        std::string domain_name = getDomainName();
        if (!domain_name.empty()) {
            buf.writeData(&domain_name[0], domain_name.size());
        }

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
    // Check that the flags in the received option are valid. Ignore MBZ bits,
    // because we don't want to discard the whole option because of MBZ bits
    // being set.
    impl_->checkFlags(impl_->flags_, false);
}

std::string
Option4ClientFqdn::toText(int indent) {
    std::ostringstream stream;
    std::string in(indent, ' '); // base indentation
    stream << in  << "type=" << type_ << " (CLIENT_FQDN), "
           <<  "flags: ("
           << "N=" << (getFlag(FLAG_N) ? "1" : "0") << ", "
           << "E=" << (getFlag(FLAG_E) ? "1" : "0") << ", "
           << "O=" << (getFlag(FLAG_O) ? "1" : "0") << ", "
           << "S=" << (getFlag(FLAG_S) ? "1" : "0") << "), "
           << "domain-name='" << getDomainName() << "' ("
           << (getDomainNameType() == PARTIAL ? "partial" : "full")
           << ")";

    return (stream.str());
}

uint16_t
Option4ClientFqdn::len() {
    uint16_t domain_name_length = 0;
    // Try to calculate the length of the domain name only if there is
    // any domain name specified.
    if (impl_->domain_name_) {
        // If the E flag is specified, the domain name is encoded in the
        // canonical format. The length of the domain name depends on
        // whether it is a partial or fully qualified names. For the
        // former the length is 1 octet lesser because it lacks terminating
        // zero.
        if (getFlag(FLAG_E)) {
            domain_name_length = impl_->domain_name_type_ == FULL ?
                impl_->domain_name_->getLength() :
                impl_->domain_name_->getLength() - 1;

        // ASCII encoded domain name. Its length is just a length of the
        // string holding the name.
        } else {
            domain_name_length = getDomainName().length();
        }
    }

    return (getHeaderLen() + FIXED_FIELDS_LEN + domain_name_length);
}

} // end of isc::dhcp namespace
} // end of isc namespace
