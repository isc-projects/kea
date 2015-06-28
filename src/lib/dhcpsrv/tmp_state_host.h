// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef TMP_STATE_HOST_H
#define TMP_STATE_HOST_H

#include <util/ntp_utils.h>

namespace isc {
namespace dhcp {

/// Extended Host reservation class with temporary state structure
class TSHost : public Host {
public:

    /// @brief Temporary state structure
    ///
    /// The extend (aka lifetime) of the temporary state is the same
    /// than for the host reservation object.
    struct TmpState {
        /// @brief Date of the last received and accepted packet
        isc::util::Ntp rd_last_;
        /// @brief Date of the last received and accepted timestamp
        isc::util::Ntp ts_last_;
    };

    /// @brief Constructor.
    ///
    /// @ref Host::Host()
    TSHost(const uint8_t* identifier, const size_t identifier_len,
           const IdentifierType& identifier_type,
           const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
           const asiolink::IOAddress& ipv4_reservation,
           const std::string& hostname = "",
           const std::string& dhcp4_client_classes = "",
           const std::string& dhcp6_client_classes = "")
        : Host(identifier, identifier_len, identifier_type,
               ipv4_subnet_id, ipv6_subnet_id,
               ipv4_reservation, hostname,
               dhcp4_client_classes, dhcp6_client_classes),
        tmp_state_(new TmpState) {
    }

    /// @brief Constructor.
    ///
    /// @ref Host::Host()
    TSHost(const std::string& identifier, const std::string& identifier_name,
           const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
           const asiolink::IOAddress& ipv4_reservation,
           const std::string& hostname = "",
           const std::string& dhcp4_client_classes = "",
           const std::string& dhcp6_client_classes = "")
        : Host(identifier, identifier_name,
               ipv4_subnet_id, ipv6_subnet_id,
               ipv4_reservation, hostname,
               dhcp4_client_classes, dhcp6_client_classes),
        tmp_state_(new TmpState) {
    }

    /// @brief Destructor.
    virtual ~TSHost() { }

    /// @brief Sets the date of the last received and accepted packet
    ///
    /// @param timestamp Date in NTP format
    void setRDlast(const isc::util::Ntp& timestamp) const {
        tmp_state_->rd_last_ = timestamp;
    }

    /// @brief Returns the date of the last received and accepted packet
    const isc::util::Ntp& getRDlast() const {
        return (tmp_state_->rd_last_);
    }

    /// @brief Sets the date from the last received and accepted packet
    ///
    /// @param timestamp Date in NTP format
    void setTSlast(const isc::util::Ntp& timestamp) const {
        tmp_state_->ts_last_ = timestamp;
    }

    /// @brief Returns the date from the last received and accepted packet
    const isc::util::Ntp& getTSlast() const {
        return (tmp_state_->ts_last_);
    }

    /// @brief Returns information about the host in the textual format.
    /// @ref Host::toText()
    virtual std::string toText() const {
        std::ostringstream s;

        // Call the super method;
        s << Host::toText();

        // Timestamps
        if (!tmp_state_->rd_last_.is_zero()) {
            s << " RDlast=" << tmp_state_->rd_last_.to_text();
        }
        if (!tmp_state_->ts_last_.is_zero()) {
            s << " TSlast=" << tmp_state_->ts_last_.to_text();
        }

        return (s.str());
    }

private:

    /// @brief Smart pointer to the temporary state
    boost::scoped_ptr<TmpState> tmp_state_;
};

/// @brief Pointer to the @c TSHost object.
typedef boost::shared_ptr<TSHost> TSHostPtr;

/// @brief Const pointer to the @c TSHost object.
typedef boost::shared_ptr<const TSHost> ConstTSHostPtr;

}
}

#endif // TMP_STATE_HOST_H
