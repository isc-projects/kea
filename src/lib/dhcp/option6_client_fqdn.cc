// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/dhcp6.h>
#include <dhcp/option6_client_fqdn.h>
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
/// of the Option6ClientFqdn class from the interface. This implementation
/// uses kea-libdns classes to process FQDNs. At some point it may be
/// desired to split kea-libdhcp++ from kea-libdns. In such case the
/// implementation of this class may be changed. The declaration of the
/// Option6ClientFqdn class holds the pointer to implementation, so
/// the transition to a different implementation would not affect the
/// header file.
class Option6ClientFqdnImpl {
public:
    /// Holds flags carried by the option.
    uint8_t flags_;
    /// Holds the pointer to a domain name carried in the option.
    boost::shared_ptr<isc::dns::Name> domain_name_;
    /// Indicates whether domain name is partial or fully qualified.
    Option6ClientFqdn::DomainNameType domain_name_type_;

    /// @brief Constructor, from domain name.
    ///
    /// @param flags A value of the flags option field.
    /// @param domain_name A domain name carried by the option given in the
    /// textual format.
    /// @param name_type A value which indicates whether domain-name
    /// is partial of fully qualified.
    Option6ClientFqdnImpl(const uint8_t flags,
                          const std::string& domain_name,
                          const Option6ClientFqdn::DomainNameType name_type);

    /// @brief Constructor, from wire data.
    ///
    /// @param first An iterator pointing to the begining of the option data
    /// in the wire format.
    /// @param last An iterator poiting to the end of the option data in the
    /// wire format.
    Option6ClientFqdnImpl(OptionBufferConstIter first,
                          OptionBufferConstIter last);

    /// @brief Copy constructor.
    ///
    /// @param source An object being copied.
    Option6ClientFqdnImpl(const Option6ClientFqdnImpl& source);

    /// @brief Assignment operator.
    ///
    /// @param source An object which is being assigned.
    Option6ClientFqdnImpl& operator=(const Option6ClientFqdnImpl& source);

    /// @brief Set a new domain name for the option.
    ///
    /// @param domain_name A new domain name to be assigned.
    /// @param name_type A value which indicates whether the domain-name is
    /// partial or fully qualified.
    void setDomainName(const std::string& domain_name,
                       const Option6ClientFqdn::DomainNameType name_type);

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

};

Option6ClientFqdnImpl::
Option6ClientFqdnImpl(const uint8_t flags,
                      const std::string& domain_name,
                      // cppcheck 1.57 complains that const enum value is not
                      // passed by reference. Note that it accepts the non-const
                      // enum to be passed by value. In both cases it is
                      // unnecessary to pass the enum by reference.
                      // cppcheck-suppress passedByValue
                      const Option6ClientFqdn::DomainNameType name_type)
    : flags_(flags),
      domain_name_(),
      domain_name_type_(name_type) {

    //  Check if flags are correct. Also check if MBZ bits are set.
    checkFlags(flags_, true);
    // Set domain name. It may throw an exception if domain name has wrong
    // format.
    setDomainName(domain_name, name_type);
}

Option6ClientFqdnImpl::Option6ClientFqdnImpl(OptionBufferConstIter first,
                                             OptionBufferConstIter last) {
    parseWireData(first, last);
    // Verify that flags value was correct. Do not check if MBZ bits are
    // set because we should ignore those bits in received message.
    checkFlags(flags_, false);
}

Option6ClientFqdnImpl::
Option6ClientFqdnImpl(const Option6ClientFqdnImpl& source)
    : flags_(source.flags_),
      domain_name_(),
      domain_name_type_(source.domain_name_type_) {
    if (source.domain_name_) {
        domain_name_.reset(new isc::dns::Name(*source.domain_name_));
    }
}

Option6ClientFqdnImpl&
// This assignment operator handles assignment to self, it copies all
// required values.
// cppcheck-suppress operatorEqToSelf
Option6ClientFqdnImpl::operator=(const Option6ClientFqdnImpl& source) {
    if (source.domain_name_) {
        domain_name_.reset(new isc::dns::Name(*source.domain_name_));

    } else {
        domain_name_.reset();

    }

    // This assignment should be exception safe.
    flags_ = source.flags_;
    domain_name_type_ = source.domain_name_type_;

    return (*this);
}

void
Option6ClientFqdnImpl::
setDomainName(const std::string& domain_name,
              // cppcheck 1.57 complains that const enum value is not
              // passed by reference. Note that it accepts the non-const
              // enum to be passed by value. In both cases it is
              // unnecessary to pass the enum by reference.
              // cppcheck-suppress passedByValue
              const Option6ClientFqdn::DomainNameType name_type) {
    // domain-name must be trimmed. Otherwise, string comprising spaces only
    // would be treated as a fully qualified name.
    std::string name = isc::util::str::trim(domain_name);
    if (name.empty()) {
        if (name_type == Option6ClientFqdn::FULL) {
            isc_throw(InvalidOption6FqdnDomainName,
                      "fully qualified domain-name must not be empty"
                      << " when setting new domain-name for DHCPv6 Client"
                      << " FQDN Option");
        }
        // The special case when domain-name is empty is marked by setting the
        // pointer to the domain-name object to NULL.
        domain_name_.reset();

    } else {
        try {
            domain_name_.reset(new isc::dns::Name(name, true));

        } catch (const Exception&) {
            isc_throw(InvalidOption6FqdnDomainName, "invalid domain-name value '"
                      << domain_name << "' when setting new domain-name for"
                      << " DHCPv6 Client FQDN Option");

        }
    }

    domain_name_type_ = name_type;
}

void
Option6ClientFqdnImpl::checkFlags(const uint8_t flags, const bool check_mbz) {
    // The Must Be Zero (MBZ) bits must not be set.
    if (check_mbz && ((flags & ~Option6ClientFqdn::FLAG_MASK) != 0)) {
        isc_throw(InvalidOption6FqdnFlags,
                  "invalid DHCPv6 Client FQDN Option flags: 0x"
                  << std::hex << static_cast<int>(flags) << std::dec);
    }

    // According to RFC 4704, section 4.1. if the N bit is 1, the S bit
    // MUST be 0. Checking it here.
    if ((flags & (Option6ClientFqdn::FLAG_N | Option6ClientFqdn::FLAG_S))
        == (Option6ClientFqdn::FLAG_N | Option6ClientFqdn::FLAG_S)) {
        isc_throw(InvalidOption6FqdnFlags,
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
                  << D6O_CLIENT_FQDN << ") is truncated. Minimal option"
                  << " size is " << Option6ClientFqdn::FLAG_FIELD_LEN
                  << ", got option with size " << std::distance(first, last));
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
            try {
                domain_name_.reset(new isc::dns::Name(name_buf, true));
            } catch (const Exception&) {
                isc_throw(InvalidOption6FqdnDomainName, "failed to parse "
                          "partial domain-name from wire format");
            }
            // Terminating zero was missing, so set the domain-name type
            // to partial.
            domain_name_type_ = Option6ClientFqdn::PARTIAL;
        } else {
            // We are dealing with fully qualified domain name so there is
            // no need to add terminating zero. Simply pass the buffer to
            // Name object constructor.
            isc::util::InputBuffer name_buf(&(*first),
                                            std::distance(first, last));
            try {
                domain_name_.reset(new isc::dns::Name(name_buf, true));
            } catch (const Exception&) {
                isc_throw(InvalidOption6FqdnDomainName, "failed to parse "
                          "fully qualified domain-name from wire format");
            }
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
// This assignment operator handles assignment to self, it uses copy
// constructor of Option6ClientFqdnImpl to copy all required values.
// cppcheck-suppress operatorEqToSelf
Option6ClientFqdn::operator=(const Option6ClientFqdn& source) {
    Option6ClientFqdnImpl* old_impl = impl_;
    impl_ = new Option6ClientFqdnImpl(*source.impl_);
    delete(old_impl);
    return (*this);
}

bool
Option6ClientFqdn::getFlag(const uint8_t flag) const {
    // Caller should query for one of the: N, S or O flags. Any other
    // value is invalid.
    if (flag != FLAG_S && flag != FLAG_O && flag != FLAG_N) {
        isc_throw(InvalidOption6FqdnFlags, "invalid DHCPv6 Client FQDN"
                  << " Option flag specified, expected N, S or O");
    }

    return ((impl_->flags_ & flag) != 0);
}

void
Option6ClientFqdn::setFlag(const uint8_t flag, const bool set_flag) {
    // Check that flag is in range between 0x1 and 0x7. Note that this
    // allows to set or clear multiple flags concurrently. Setting
    // concurrent bits is discouraged (see header file) but it is not
    // checked here so it will work.
    if (((flag & ~FLAG_MASK) != 0) || (flag == 0)) {
        isc_throw(InvalidOption6FqdnFlags, "invalid DHCPv6 Client FQDN"
                  << " Option flag 0x" << std::hex
                  << static_cast<int>(flag) << std::dec
                  << " is being set. Expected: N, S or O");
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
    Option6ClientFqdnImpl::checkFlags(new_flag, true);
    impl_->flags_ = new_flag;
}

void
Option6ClientFqdn::resetFlags() {
    impl_->flags_ = 0;
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
Option6ClientFqdn::packDomainName(isc::util::OutputBuffer& buf) const {
    // There is nothing to do if domain-name is empty.
    if (!impl_->domain_name_) {
        return;
    }

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
    // Domain name.
    packDomainName(buf);
}

void
Option6ClientFqdn::unpack(OptionBufferConstIter first,
                          OptionBufferConstIter last) {
    setData(first, last);
    impl_->parseWireData(first, last);
    // Check that the flags in the received option are valid. Ignore MBZ bits
    // because we don't want to discard the whole option because of MBZ bits
    // being set.
    impl_->checkFlags(impl_->flags_, false);
}

std::string
Option6ClientFqdn::toText(int indent) {
    std::ostringstream stream;
    std::string in(indent, ' '); // base indentation
    stream << in  << "type=" << type_ << "(CLIENT_FQDN)" << ", "
           << "flags: ("
           << "N=" << (getFlag(FLAG_N) ? "1" : "0") << ", "
           << "O=" << (getFlag(FLAG_O) ? "1" : "0") << ", "
           << "S=" << (getFlag(FLAG_S) ? "1" : "0") << "), "
           << "domain-name='" << getDomainName() << "' ("
           << (getDomainNameType() == PARTIAL ? "partial" : "full")
           << ")";

    return (stream.str());
}

uint16_t
Option6ClientFqdn::len() {
    uint16_t domain_name_length = 0;
    if (impl_->domain_name_) {
        // If domain name is partial, the NULL terminating character
        // is not included and the option. Length has to be adjusted.
        domain_name_length = impl_->domain_name_type_ == FULL ?
            impl_->domain_name_->getLength() :
            impl_->domain_name_->getLength() - 1;
    }
    return (getHeaderLen() + FLAG_FIELD_LEN + domain_name_length);
}

} // end of isc::dhcp namespace
} // end of isc namespace
