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

#ifndef D2_CLIENT_H
#define D2_CLIENT_H

/// @file d2_client.h Defines the D2ClientConfig and D2ClientMgr classes.
/// This file defines the classes Kea uses to act as a client of the b10-
/// dhcp-ddns module (aka D2).
///
#include <asiolink/io_address.h>
#include <dhcp_ddns/ncr_io.h>
#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {


/// An exception that is thrown if an error occurs while configuring
/// the D2 DHCP DDNS client.
class D2ClientError : public isc::Exception {
public:

    /// @brief constructor
    ///
    /// @param file name of the file, where exception occurred
    /// @param line line of the file, where exception occurred
    /// @param what text description of the issue that caused exception
    D2ClientError(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {}
};

/// @brief Acts as a storage vault for D2 client configuration
///
/// A simple container class for storing and retrieving the configuration
/// parameters associated with DHCP-DDNS and acting as a client of D2.
/// Instances of this class may be constructed through configuration parsing.
///
class D2ClientConfig {
public:
    /// @brief Constructor
    ///
    /// @param enable_updates Enables DHCP-DDNS updates
    /// @param server_ip IP address of the b10-dhcp-ddns server (IPv4 or IPv6)
    /// @param server_port IP port of the b10-dhcp-ddns server
    /// @param ncr_protocol Socket protocol to use with b10-dhcp-ddns
    /// Currently only UDP is supported.
    /// @param ncr_format Format of the b10-dhcp-ddns requests.
    /// Currently only JSON format is supported.
    /// @param always_include_fqdn Enables always including the FQDN option in
    /// DHCP responses.
    /// @param override_no_update Enables updates, even if clients request no
    /// updates.
    /// @param override_client_update Perform updates, even if client requested
    /// delegation.
    /// @param replace_client_name enables replacement of the domain-name
    /// supplied by the client with a generated name.
    /// @param generated_prefix Prefix to use when generating domain-names.
    /// @param  qualifying_suffix Suffix to use to qualify partial domain-names.
    ///
    /// @throw D2ClientError if given an invalid protocol or format.
    D2ClientConfig(const bool enable_updates,
                   const isc::asiolink::IOAddress& server_ip,
                   const size_t server_port,
                   const dhcp_ddns::NameChangeProtocol& ncr_protocol,
                   const dhcp_ddns::NameChangeFormat& ncr_format,
                   const bool always_include_fqdn,
                   const bool override_no_update,
                   const bool override_client_update,
                   const bool replace_client_name,
                   const std::string& generated_prefix,
                   const std::string& qualifying_suffix);

    /// @brief Default constructor
    /// The default constructor creates an instance that has updates disabled.
    D2ClientConfig();

    /// @brief Destructor
    virtual ~D2ClientConfig();

    /// @brief Return whether or not DHCP-DDNS updating is enabled.
    bool getEnableUpdates() const {
        return(enable_updates_);
    }

    /// @brief Return the IP address of b10-dhcp-ddns (IPv4 or IPv6).
    const isc::asiolink::IOAddress& getServerIp() const {
        return(server_ip_);
    }

    /// @brief Return the IP port of b10-dhcp-ddns.
    size_t getServerPort() const {
        return(server_port_);
    }

    /// @brief Return the socket protocol to use with b10-dhcp-ddns.
    const dhcp_ddns::NameChangeProtocol& getNcrProtocol() const {
         return(ncr_protocol_);
    }

    /// @brief Return the b10-dhcp-ddns request format.
    const dhcp_ddns::NameChangeFormat& getNcrFormat() const {
        return(ncr_format_);
    }

    /// @brief Return whether or not FQDN is always included in DHCP responses.
    bool getAlwaysIncludeFqdn() const {
        return(always_include_fqdn_);
    }

    /// @brief Return if updates are done even if clients request no updates.
    bool getOverrideNoUpdate() const {
        return(override_no_update_);
    }

    /// @brief Return if updates are done even when clients request delegation.
    bool getOverrideClientUpdate() const {
        return(override_client_update_);
    }

    /// @brief Return whether or not client's domain-name is always replaced.
    bool getReplaceClientName() const {
        return(replace_client_name_);
    }

    /// @brief Return the prefix to use when generating domain-names.
    const std::string& getGeneratedPrefix() const {
        return(generated_prefix_);
    }

    /// @brief Return the suffix to use to qualify partial domain-names.
    const std::string& getQualifyingSuffix() const {
        return(qualifying_suffix_);
    }

    /// @brief Compares two D2ClientConfigs for equality
    bool operator == (const D2ClientConfig& other) const;

    /// @brief Compares two D2ClientConfigs for inequality
    bool operator != (const D2ClientConfig& other) const;

    /// @brief Generates a string representation of the class contents.
    std::string toText() const;

protected:
    /// @brief Validates member values.
    ///
    /// Method is used by the constructor to validate member contents.
    ///
    /// @throw D2ClientError if given an invalid protocol or format.
    virtual void validateContents();

private:
    /// @brief Indicates whether or not DHCP DDNS updating is enabled.
    bool enable_updates_;

    /// @brief IP address of the b10-dhcp-ddns server (IPv4 or IPv6).
    isc::asiolink::IOAddress server_ip_;

    /// @brief IP port of the b10-dhcp-ddns server.
    size_t server_port_;

    /// @brief The socket protocol to use with b10-dhcp-ddns.
    /// Currently only UDP is supported.
    dhcp_ddns::NameChangeProtocol ncr_protocol_;

    /// @brief Format of the b10-dhcp-ddns requests.
    /// Currently only JSON format is supported.
    dhcp_ddns::NameChangeFormat ncr_format_;

    /// @brief Should Kea always include the FQDN option in its response.
    bool always_include_fqdn_;

    /// @brief Should Kea perform updates, even if client requested no updates.
    /// Overrides the client request for no updates via the N flag.
    bool override_no_update_;

    /// @brief Should Kea perform updates, even if client requested delegation.
    bool override_client_update_;

    /// @brief Should Kea replace the domain-name supplied by the client.
    bool replace_client_name_;

    /// @brief Prefix Kea should use when generating domain-names.
    std::string generated_prefix_;

    /// @brief Suffix Kea should use when to qualify partial domain-names.
    std::string qualifying_suffix_;
};

std::ostream&
operator<<(std::ostream& os, const D2ClientConfig& config);

/// @brief Defines a pointer for D2ClientConfig instances.
typedef boost::shared_ptr<D2ClientConfig> D2ClientConfigPtr;

/// @brief Defines the type for D2 IO error handler.
/// This callback is invoked when a send to b10-dhcp-ddns completes with a
/// failed status.  This provides the application layer (Kea) with a means to
/// handle the error appropriately.
///
/// @param result Result code of the send operation.
/// @param ncr NameChangeRequest which failed to send.
///
/// @note Handlers are expected not to throw. In the event a hanlder does
/// throw invoking code logs the exception and then swallows it.
typedef
boost::function<void(const dhcp_ddns::NameChangeSender::Result result,
                     dhcp_ddns::NameChangeRequestPtr& ncr)> D2ClientErrorHandler;

/// @brief D2ClientMgr isolates Kea from the details of being a D2 client.
///
/// Provides services for managing the current dhcp-ddns configuration and
/// as well as communications with b10-dhcp-ddns.  Regarding configuration it
/// provides services to store, update, and access the current dhcp-ddns
/// configuration.  As for b10-dhcp-ddns communications, D2ClientMgr creates
/// maintains a NameChangeSender appropriate to the current configuration and
/// provides services to start, stop, and post NCRs to the sender.  Additionally
/// there are methods to examine the queue of requests currently waiting for
/// transmission.
///
/// The manager also provides the mechanics to integrate the ASIO-based IO
/// used by the NCR IPC with the select-driven IO used by Kea.  Senders expose
/// a file descriptor, the "select-fd" that can monitored for read-readiness
/// with the select() function (or variants).  D2ClientMgr provides a method,
/// runReadyIO(), that will process all ready events on a sender's
/// IOservice.  Track# 3315 is extending Kea's IfaceMgr to support the
/// registration of multiple external sockets with callbacks that are then
/// monitored with IO readiness via select().
/// @todo D2ClientMgr will be modified to register the sender's select-fd and
/// runReadyIO() with IfaceMgr when entering the send mode and will
/// unregister when exiting send mode.
///
/// To place the manager in send mode, the calling layer must supply an error
/// handler and optionally an IOService instance.  The error handler is invoked
/// if a send completes with a failed status. This provides the calling layer
/// an opportunity act upon the error.
///
/// If the caller supplies an IOService, that service will be used to process
/// the sender's IO.  If not supplied, D2ClientMgr pass a private IOService
/// into the sender.  Using a private service isolates the sender's IO from
/// any other services.
///
class D2ClientMgr : public dhcp_ddns::NameChangeSender::RequestSendHandler {
public:
    /// @brief Constructor
    ///
    /// Default constructor which constructs an instance which has DHCP-DDNS
    /// updates disabled.
    D2ClientMgr();

    /// @brief Destructor.
    ~D2ClientMgr();

    /// @brief Updates the DHCP-DDNS client configuration to the given value.
    ///
    /// @param new_config pointer to the new client configuration.
    /// @throw D2ClientError if passed an empty pointer.
    void setD2ClientConfig(D2ClientConfigPtr& new_config);

    /// @brief Convenience method for checking if DHCP-DDNS is enabled.
    ///
    /// @return True if the D2 configuration is enabled.
    bool ddnsEnabled();

    /// @brief Fetches the DHCP-DDNS configuration pointer.
    ///
    /// @return a reference to the current configuration pointer.
    const D2ClientConfigPtr& getD2ClientConfig() const;

    /// @brief Determines server flags based on configuration and  client flags.
    ///
    /// This method uses input values for the client's FQDN S and N flags, in
    /// conjunction with the configuration parameters updates-enabled, override-
    /// no-updates, and override-client-updates to determine the values that
    /// should be used for the server's FQDN S and N flags.
    /// The logic in this method is based upon RFCs 4702 and 4704.
    ///
    /// @param client_s  S Flag from the client's FQDN
    /// @param client_n  N Flag from the client's FQDN
    /// @param server_s [out] S Flag for the server's FQDN
    /// @param server_n [out] N Flag for the server's FQDN
    ///
    /// @throw isc::BadValue if client_s and client_n are both 1 as this is
    /// an invalid combination per RFCs.
    void analyzeFqdn(const bool client_s, const bool client_n, bool& server_s,
                     bool& server_n) const;

    /// @brief Builds a FQDN based on the configuration and given IP address.
    ///
    /// Using the current values for generated-prefix, qualifying-suffix and
    /// an IP address, this method constructs a fully qualified domain name.
    /// It supports both IPv4 and IPv6 addresses.  The format of the name
    /// is as follows:
    ///
    ///     <generated-prefix>-<ip address>.<qualifying-suffix>.
    ///
    /// <ip-address> is the result of IOAddress.toText() with the delimiters
    /// ('.' for IPv4 or ':' for IPv6) replaced with a hyphen, '-'.
    ///
    /// @param address IP address from which to derive the name (IPv4 or IPv6)
    ///
    /// @return std::string containing the generated name.
    std::string generateFqdn(const asiolink::IOAddress& address) const;

    /// @brief Adds a qualifying suffix to a given domain name
    ///
    /// Constructs a FQDN based on the configured qualifying-suffix and
    /// a partial domain name as follows:
    ///
    ///     <partial_name>.<qualifying-suffix>.
    /// Note it will add a trailing '.' should qualifying-suffix not end with
    /// one.
    ///
    /// @param partial_name domain name to qualify
    ///
    /// @return std::string containing the qualified name.
    std::string qualifyName(const std::string& partial_name) const;

    /// @brief Set server FQDN flags based on configuration and a given FQDN
    ///
    /// Templated wrapper around the analyzeFqdn() allowing that method to
    /// be used for either IPv4 or IPv6 processing.  This methods resets all
    /// of the flags in the response to zero and then sets the S,N, and O
    /// flags.  Any other flags are the responsiblity of the invoking layer.
    ///
    /// @param fqdn FQDN option from which to read client (inbound) flags
    /// @param fqdn_resp FQDN option to update with the server (outbound) flags
    /// @tparam T FQDN Option class containing the FQDN data such as
    /// dhcp::Option4ClientFqdn or dhcp::Option6ClientFqdn
    template <class T>
    void adjustFqdnFlags(const T& fqdn, T& fqdn_resp);

    /// @brief Set server FQDN name based on configuration and a given FQDN
    ///
    /// Templated method which adjusts the domain name value and type in
    /// a server FQDN from a client (inbound) FQDN and the current
    /// configuration.  The logic is as follows:
    ///
    /// If replace-client-name is true or the supplied name is empty, the
    /// server FQDN is set to ""/PARTIAL.
    ///
    /// If replace-client-name is false and the supplied name is a partial
    /// name the server FQDN is set to the supplied name qualified by
    /// appending the qualifying-suffix.
    ///
    /// If replace-client-name is false and the supplied name is a fully
    /// qualified name, set the server FQDN to the supplied name.
    ///
    /// @param fqdn FQDN option from which to get client (inbound) name
    /// @param fqdn_resp FQDN option to update with the adjusted name
    /// @tparam T  FQDN Option class containing the FQDN data such as
    /// dhcp::Option4ClientFqdn or dhcp::Option6ClientFqdn
    template <class T>
    void adjustDomainName(const T& fqdn, T& fqdn_resp);

    /// @brief Enables sending NameChangeRequests to b10-dhcp-ddns
    ///
    /// Places the NameChangeSender into send mode. This instructs the
    /// sender to begin dequeuing and transmitting requests and to accept
    /// additional requests via the sendRequest() method.
    ///
    /// @param error_handler application level error handler to cope with
    /// sends that complete with a failed status.  A valid function must be
    /// supplied as the manager cannot know how an application should deal
    /// with send failures.
    /// @param io_service IOService to be used for sender IO event processing
    /// @warning It is up to the invoking layer to ensure the io_service
    /// instance used outlives the D2ClientMgr send mode. When the send mode
    /// is exited, either expliclity by callind stopSender() or implicitly
    /// through D2CLientMgr destruction, any ASIO objects such as sockets or
    /// timers will be closed and released.  If the io_service goes out of scope
    /// first this behavior could be unpredictable.
    ///
    /// @throw D2ClientError if sender instance is null. Underlying layer
    /// may throw NCRSenderExceptions exceptions.
    void startSender(D2ClientErrorHandler error_handler,
                     isc::asiolink::IOService& io_service);

    /// @brief Enables sending NameChangeRequests to b10-dhcp-ddns
    ///
    /// Places the NameChangeSender into send mode. This instructs the
    /// sender to begin dequeuing and transmitting requests and to accept
    /// additional requests via the sendRequest() method.  The manager
    /// will create a new, private instance of an IOService for the sender
    /// to use for IO event processing.
    ///
    /// @param error_handler application level error handler to cope with
    /// sends that complete with a failed status.  A valid function must be
    /// supplied as the manager cannot know how an application should deal
    /// with send failures.
    ///
    /// @throw D2ClientError if sender instance is null. Underlying layer
    /// may throw NCRSenderExceptions exceptions.
    void startSender(D2ClientErrorHandler error_handler);

    /// @brief Returns true if the sender is in send mode, false otherwise.
    ///
    /// A true value indicates that the sender is present and in accepting
    /// messages for transmission, false otherwise.
    bool amSending() const;

    /// @brief Disables sending NameChangeRequests to b10-dhcp-ddns
    ///
    /// Takes the NameChangeSender out of send mode.  The sender will stop
    /// transmitting requests, though any queued requests remain queued.
    /// Attempts to queue additional requests via sendRequest will fail.
    ///
    /// @throw D2ClientError if sender instance is null. Underlying layer
    /// may throw NCRSenderExceptions exceptions.
    void stopSender();

    /// @brief Send the given NameChangeRequests to b10-dhcp-ddns
    ///
    /// Passes NameChangeRequests to the NCR sender for transmission to
    /// b10-dhcp-ddns.
    ///
    /// @param ncr NameChangeRequest to send
    ///
    /// @throw D2ClientError if sender instance is null. Underlying layer
    /// may throw NCRSenderExceptions exceptions.
    void sendRequest(dhcp_ddns::NameChangeRequestPtr& ncr);

    /// @brief Returns the number of NCRs queued for transmission.
    size_t getQueueSize() const;

    /// @brief Returns the nth NCR queued for transmission.
    ///
    /// Note that the entry is not removed from the queue.
    /// @param index the index of the entry in the queue to fetch.
    /// Valid values are 0 (front of the queue) to (queue size - 1).
    /// @note This method is for test purposes only.
    ///
    /// @return Pointer reference to the queue entry.
    ///
    /// @throw D2ClientError if sender instance is null. Underlying layer
    /// may throw NCRSenderExceptions exceptions.
    const dhcp_ddns::NameChangeRequestPtr& peekAt(const size_t index) const;

    /// @brief Removes all NCRs queued for transmission.
    ///
    /// @throw D2ClientError if sender instance is null. Underlying layer
    /// may throw NCRSenderExceptions exceptions.
    void clearQueue();

    /// @brief Processes sender IO events
    ///
    /// Runs all handlers ready for execution on the sender's IO service.
    void runReadyIO();

protected:
    /// @brief Function operator implementing the NCR sender callback.
    ///
    /// This method is invoked each time the NameChangeSender completes
    /// an asychronous send.
    ///
    /// @param result contains that send outcome status.
    /// @param ncr is a pointer to the NameChangeRequest that was
    /// delivered (or attempted).
    ///
    /// @throw This method MUST NOT throw.
    virtual void operator ()(const dhcp_ddns::NameChangeSender::Result result,
                             dhcp_ddns::NameChangeRequestPtr& ncr);

    /// @brief Fetches the sender's select-fd.
    ///
    /// The select-fd may be used with select() or poll().  If the sender has
    /// IO waiting to process, the fd will evaluate as !EWOULDBLOCK.
    /// @note This is only exposed for testing purposes.
    ///
    /// @return The sender's select-fd
    ///
    /// @throw D2ClientError if the sender does not exist or is not in send
    /// mode.
    int getSelectFd();

private:
    /// @brief Container class for DHCP-DDNS configuration parameters.
    D2ClientConfigPtr d2_client_config_;

    /// @brief Pointer to the current interface to DHCP-DDNS.
    dhcp_ddns::NameChangeSenderPtr name_change_sender_;

    /// @brief Private IOService to use if calling layer doesn't wish to
    /// supply one.
    boost::shared_ptr<asiolink::IOService> private_io_service_;

    /// @brief Application supplied error handler invoked when a send
    /// completes with a failed status.
    D2ClientErrorHandler client_error_handler_;

    /// @brief Pointer to the IOService currently being used by the sender.
    /// @note We need to remember the io_service given to the sender however
    /// we may have received only a referenece to it from the calling layer.
    /// Use a raw pointer to store it.  This value should never be exposed
    /// and is only valid while in send mode.
    asiolink::IOService* sender_io_service_;
};

template <class T>
void
D2ClientMgr::adjustFqdnFlags(const T& fqdn, T& fqdn_resp) {
    bool server_s = false;
    bool server_n = false;
    analyzeFqdn(fqdn.getFlag(T::FLAG_S), fqdn.getFlag(T::FLAG_N),
                server_s, server_n);

    // Reset the flags to zero to avoid triggering N and S both 1 check.
    fqdn_resp.resetFlags();

    // Set S and N flags.
    fqdn_resp.setFlag(T::FLAG_S, server_s);
    fqdn_resp.setFlag(T::FLAG_N, server_n);

    // Set O flag true if server S overrides client S.
    fqdn_resp.setFlag(T::FLAG_O, (fqdn.getFlag(T::FLAG_S) != server_s));
}


template <class T>
void
D2ClientMgr::adjustDomainName(const T& fqdn, T& fqdn_resp) {
    // If we're configured to replace it or the supplied name is blank
    // set the response name to blank.
    if (d2_client_config_->getReplaceClientName() ||
        fqdn.getDomainName().empty()) {
        fqdn_resp.setDomainName("", T::PARTIAL);
    } else {
        // If the supplied name is partial, qualify it by adding the suffix.
        if (fqdn.getDomainNameType() == T::PARTIAL) {
            fqdn_resp.setDomainName(qualifyName(fqdn.getDomainName()), T::FULL);
        }
    }
}

/// @brief Defines a pointer for D2ClientMgr instances.
typedef boost::shared_ptr<D2ClientMgr> D2ClientMgrPtr;


} // namespace isc
} // namespace dhcp

#endif
