// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file pkt_send_co.cc Defines the pkt4_send and pkt6_send callout functions.

#include <config.h>
#include <asiolink/io_address.h>
#include <hooks/hooks.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_string.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <user_chk.h>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace user_chk;
using namespace std;

// prototypes for local helper functions
void generate_output_record(const std::string& id_type_str,
                            const std::string& id_val_str,
                            const std::string& addr_str,
                            const bool& registered);
std::string getV6AddrStr (Pkt6Ptr response);
std::string getAddrStrIA_NA(OptionPtr options);
std::string getAddrStrIA_PD(OptionPtr options);
bool checkIAStatus(boost::shared_ptr<Option6IA>& ia_opt);

void add4Options(Pkt4Ptr& response, const UserPtr& user);
void add4Option(Pkt4Ptr& response, uint8_t opt_code, std::string& opt_value);
void add6Options(Pkt6Ptr& response, const UserPtr& user);
void add6Option(OptionPtr& vendor, uint8_t opt_code, std::string& opt_value);
const UserPtr& getDefaultUser4();
const UserPtr& getDefaultUser6();

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief  This callout is called at the "pkt4_send" hook.
///
/// This function generates the user check outcome and modifies options
/// to the IPv4 response packet based on whether the user is registered or not.
///
/// It retrieves a pointer to the registered user from the callout context.
/// This value should have been set upstream.  If the registered user pointer
/// is non-null (i.e the user is registered), then a registered user outcome
/// is recorded in the outcome output and the vendor properties are altered
/// based upon this user's properties.
///
/// A null value means the user is not registered and a unregistered user
/// outcome is recorded in the outcome output and the vendor properties
/// are altered based upon the default IPv4 user in the registry (if defined).
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_send(CalloutHandle& handle) {
    try {
        Pkt4Ptr response;
        handle.getArgument("response4", response);

        uint8_t packet_type = response->getType();
        if (packet_type == DHCPNAK) {
            std::cout << "DHCP UserCheckHook : pkt4_send"
                      << "skipping packet type: "
                      << static_cast<int>(packet_type) << std::endl;
            return (0);
        }

        // Get the user id saved from the query packet.
        HWAddrPtr hwaddr;
        handle.getContext(query_user_id_label, hwaddr);

        // Get registered_user pointer.
        UserPtr registered_user;
        handle.getContext(registered_user_label, registered_user);

        // Fetch the lease address.
        isc::asiolink::IOAddress addr = response->getYiaddr();

        if (registered_user) {
            // add options based on user
            // then generate registered output record
            std::cout << "DHCP UserCheckHook : pkt4_send registered_user is: "
                      << registered_user->getUserId() << std::endl;

            // Add the outcome entry to the output file.
            generate_output_record(UserId::HW_ADDRESS_STR, hwaddr->toText(),
                                   addr.toText(), true);
            add4Options(response, registered_user);
        } else {
            // add default options based
            // then generate not registered output record
            std::cout << "DHCP UserCheckHook : pkt4_send no registered_user"
                      << std::endl;
            // Add the outcome entry to the output file.
            generate_output_record(UserId::HW_ADDRESS_STR, hwaddr->toText(),
                                   addr.toText(), false);

            add4Options(response, getDefaultUser4());
        }
    } catch (const std::exception& ex) {
        std::cout << "DHCP UserCheckHook : pkt4_send unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

/// @brief  This callout is called at the "pkt6_send" hook.
///
/// This function generates the user check outcome and modifies options
/// to the IPv6 response packet based on whether the user is registered or not.
///
/// It retrieves a pointer to the registered user from the callout context.
/// This value should have been set upstream.  If the registered user pointer
/// is non-null (i.e the user is registered), then a registered user outcome
/// is recorded in the outcome output and the vendor properties are altered
/// based upon this user's properties.
///
/// A null value means the user is not registered and a unregistered user
/// outcome is recorded in the outcome output and the vendor properties
/// are altered based upon the default IPv6 user in the registry (if defined).
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt6_send(CalloutHandle& handle) {
    try {
        Pkt6Ptr response;
        handle.getArgument("response6", response);

        // Fetch the lease address as a string
        std::string addr_str = getV6AddrStr(response);
        if (addr_str.empty()) {
            // packet did not contain an address, must be failed.
            std::cout << "pkt6_send: Skipping packet address is blank"
                      << std::endl;
            return (0);
        }

        // Get the user id saved from the query packet.
        DuidPtr duid;
        handle.getContext(query_user_id_label, duid);

        // Get registered_user pointer.
        UserPtr registered_user;
        handle.getContext(registered_user_label, registered_user);

        if (registered_user) {
            // add options based on user
            // then generate registered output record
            std::cout << "DHCP UserCheckHook : pkt6_send registered_user is: "
                      << registered_user->getUserId() << std::endl;
            // Add the outcome entry to the output file.
            generate_output_record(UserId::DUID_STR, duid->toText(),
                                   addr_str, true);
            add6Options(response, registered_user);
        } else {
            // add default options based
            // then generate not registered output record
            std::cout << "DHCP UserCheckHook : pkt6_send no registered_user"
                      << std::endl;
            // Add the outcome entry to the output file.
            generate_output_record(UserId::DUID_STR, duid->toText(),
                                   addr_str, false);
            add6Options(response, getDefaultUser6());
        }
    } catch (const std::exception& ex) {
        std::cout << "DHCP UserCheckHook : pkt6_send unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

} // extern C

/// @brief Adds IPv4 options to the response packet based on given user
///
/// Adds or replaces IPv4 options with values from the given user, if
/// the user has corresponding properties defined. Currently it supports
/// the following options:
///
/// - DHO_BOOT_FILE_NAME from user property "bootfile"
/// - DHO_TFTP_SERVER_NAME from user property "tftp_server"
///
/// @param response IPv4 response packet
/// @param user User from whom properties are sourced
void add4Options(Pkt4Ptr& response, const UserPtr& user) {
    // If user is null, do nothing.
    if (!user) {
        return;
    }

    // If the user has bootfile property, update it in the response.
    std::string opt_value = user->getProperty("bootfile");
    if (!opt_value.empty()) {
        std::cout << "DHCP UserCheckHook : add4Options "
              << "adding boot file:" << opt_value << std::endl;

        // Add boot file to packet.
        add4Option(response, DHO_BOOT_FILE_NAME, opt_value);

        // Boot file also goes in file field.
        response->setFile((const uint8_t*)(opt_value.c_str()),
                          opt_value.length());
    }

    // If the user has tftp server property, update it in the response.
    opt_value = user->getProperty("tftp_server");
    if (!opt_value.empty()) {
        std::cout << "DHCP UserCheckHook : add4Options "
              << "adding TFTP server:" << opt_value << std::endl;

        // Add tftp server option to packet.
        add4Option(response, DHO_TFTP_SERVER_NAME, opt_value);
    }
    // add next option here
}

/// @brief Adds/updates are specific IPv4 string option in response packet.
///
/// @param response IPV4 response packet to update
/// @param opt_code DHCP standard numeric code of the option
/// @param opt_value String value of the option
void add4Option(Pkt4Ptr& response, uint8_t opt_code, std::string& opt_value) {
    // Remove the option if it exists.
    OptionPtr opt = response->getOption(opt_code);
    if (opt) {
        response->delOption(opt_code);
    }

    // Now add the option.
    opt.reset(new OptionString(Option::V4, opt_code, opt_value));
    response->addOption(opt);
}


/// @brief Adds IPv6 vendor options to the response packet based on given user
///
/// Adds or replaces IPv6 vendor options with values from the given user, if
/// the user has the corresponding properties defined. Currently it supports
/// the following options:
///
/// - DOCSIS3_V6_CONFIG_FILE from user property "bootfile"
/// - DOCSIS3_V6_TFTP_SERVERS from user property "tftp_server"
///
/// @param response IPv5 reponse packet
/// @param user User from whom properties are sourced
void add6Options(Pkt6Ptr& response, const UserPtr& user) {
    if (!user) {
        return;
    }

    /// @todo: if packets have no vendor opt... do we need to add it
    /// if its not there?  If so how?
    OptionPtr vendor = response->getOption(D6O_VENDOR_OPTS);
    if (!vendor) {
        std::cout << "DHCP UserCheckHook : add6Options "
              << "response has no vendor option to update" << std::endl;
        return;
    }

    // If the user defines bootfile, set the option in response.
    std::string opt_value = user->getProperty("bootfile");
    if (!opt_value.empty()) {
        std::cout << "DHCP UserCheckHook : add6Options "
                  << "adding boot file:" << opt_value << std::endl;
        add6Option(vendor, DOCSIS3_V6_CONFIG_FILE, opt_value);
    }

    // If the user defines tftp server, set the option in response.
    opt_value = user->getProperty("tftp_server");
    if (!opt_value.empty()) {
        std::cout << "DHCP UserCheckHook : add6Options "
                  << "adding tftp server:" << opt_value << std::endl;

        add6Option(vendor, DOCSIS3_V6_TFTP_SERVERS, opt_value);
    }

    // add next option here
}

/// @brief Adds/updates a specific IPv6 string vendor option.
///
/// @param vendor IPv6 vendor option set to update
/// @param opt_code DHCP standard numeric code of the option
/// @param opt_value String value of the option
void add6Option(OptionPtr& vendor, uint8_t opt_code, std::string& opt_value) {
    vendor->delOption(opt_code);
    OptionPtr option(new OptionString(Option::V6, opt_code, opt_value));
    vendor->addOption(option);
}


/// @brief Adds an entry to the end of the user check outcome file.
///
/// @todo This ought to be replaced with an abstract output similar to
/// UserDataSource to allow greater flexibility.
///
/// Each user entry is written in an ini-like format, with one name-value pair
/// per line as follows:
///
/// id_type=&lt;id type&gt;<br/>
/// client=&lt;id str&gt;<br/>
/// subnet=&lt;addr str&gt;<br/>
/// registered=&lt;is registered&gt;
///
/// where:
/// &lt;id type&gt; text label of the id type: "HW_ADDR" or "DUID"
/// &lt;id str&gt; user's id formatted as either isc::dhcp::Hwaddr.toText() or
/// isc::dhcp::DUID.toText()
/// &lt;addr str&gt; selected subnet formatted as isc::dhcp::Subnet4::toText() or
/// isc::dhcp::Subnet6::toText() as appropriate.
/// &lt;is registered&gt; "yes" or "no"
///
/// Sample IPv4 entry would like this:
///
/// @code
/// id_type=DUID
/// client=00:01:00:01:19:ef:e6:3b:00:0c:01:02:03:04
/// subnet=2001:db8:2::/64
/// registered=yes
/// id_type=duid
/// @endcode
///
/// Sample IPv4 entry would like this:
///
/// @code
/// id_type=DUID
/// id_type=HW_ADDR
/// client=hwtype=1 00:0c:01:02:03:05
/// subnet=152.77.5.0/24
/// registered=no
/// @endcode
///
/// @param id_type_str text label identify the id type
/// @param id_val_str text representation of the user id
/// @param addr_str text representation  of the selected subnet
/// @param registered boolean indicating if the user is registered or not
void generate_output_record(const std::string& id_type_str,
                            const std::string& id_val_str,
                            const std::string& addr_str,
                            const bool& registered)
{
    user_chk_output << "id_type=" << id_type_str << std::endl
                    << "client=" << id_val_str << std::endl
                    << "addr=" << addr_str << std::endl
                    << "registered=" << (registered ? "yes" : "no")
                    << std::endl
                    << std::endl;   // extra line in between

    // @todo Flush is here to ensure output is immediate for demo purposes.
    // Performance would generally dictate not using it.
    flush(user_chk_output);
}

/// @brief Stringify the lease address or prefix IPv6 response packet
///
/// Converts the lease value, either an address or a prefix, into a string
/// suitable for the user check outcome output.  Note that this will use
/// the first address or prefix in the response for responses with more than
/// one value.
///
/// @param response IPv6 response packet from which to extract the lease value.
///
/// @return A string containing the lease value.
/// @throw isc::BadValue if the response contains neither an IA_NA nor IA_PD
/// option.
std::string getV6AddrStr(Pkt6Ptr response) {
    OptionPtr tmp = response->getOption(D6O_IA_NA);
    if (tmp) {
        return(getAddrStrIA_NA(tmp));
    }

    // IA_NA not there so try IA_PD
    tmp = response->getOption(D6O_IA_PD);
    if (!tmp) {
        isc_throw (isc::BadValue, "Response has neither IA_NA nor IA_PD");
    }

    return(getAddrStrIA_PD(tmp));
}

/// @brief Stringify the lease address in an D6O_IA_NA option set
///
/// Converts the IA_NA lease address into a string suitable for the user check
/// outcome output.
///
/// @param options pointer to the Option6IA instance from which to extract the
/// lease address.
///
/// @return A string containing the lease address.
///
/// @throw isc::BadValue if the lease address cannot be extracted from options.
std::string getAddrStrIA_NA(OptionPtr options) {
    boost::shared_ptr<Option6IA> ia =
        boost::dynamic_pointer_cast<Option6IA>(options);

    if (!ia) {
        isc_throw (isc::BadValue, "D6O_IA_NA option invalid");
    }

    // If status indicates a failure return a blank string.
    if (!checkIAStatus(ia)) {
        return (std::string(""));
    }

    options = ia->getOption(D6O_IAADDR);
    if (!options) {
        isc_throw (isc::BadValue, "D6O_IAADDR option missing");
    }

    boost::shared_ptr<Option6IAAddr> addr_option;
    addr_option  = boost::dynamic_pointer_cast<Option6IAAddr>(options);
    if (!addr_option) {
        isc_throw (isc::BadValue, "D6O_IAADDR Option6IAAddr missing");
    }

    isc::asiolink::IOAddress addr = addr_option->getAddress();
    return (addr.toText());
}

/// @brief Stringify the lease prefix in an D6O_IA_PD option set
///
/// Converts the IA_PD lease prefix into a string suitable for the user check
/// outcome output.
///
/// @param options pointer to the Option6IA instance from which to extract the
/// lease prefix.
///
/// @return A string containing lease prefix
///
/// @throw isc::BadValue if the prefix cannot be extracted from options.
std::string getAddrStrIA_PD(OptionPtr options) {
    boost::shared_ptr<Option6IA> ia =
        boost::dynamic_pointer_cast<Option6IA>(options);

    // Make sure we have an IA_PD option.
    if (!ia) {
        isc_throw (isc::BadValue, "D6O_IA_PD option invalid");
    }

    // Check the response for success status.  If it isn't a success response
    // there will not be a lease prefix value which is denoted by returning
    // an empty string.
    if (!checkIAStatus(ia)) {
        return (std::string(""));
    }

    // Get the prefix option the IA_PD option.
    options = ia->getOption(D6O_IAPREFIX);
    if (!options) {
        isc_throw(isc::BadValue, "D60_IAPREFIX option is missing");
    }

    boost::shared_ptr<Option6IAPrefix> addr_option;
    addr_option = boost::dynamic_pointer_cast<Option6IAPrefix>(options);
    if (!addr_option) {
        isc_throw (isc::BadValue, "D6O_IA_PD addr option bad");
    }

    // Get the address and prefix length values.
    isc::asiolink::IOAddress addr = addr_option->getAddress();
    uint8_t prefix_len = addr_option->getLength();

    // Build the output string and return it.
    stringstream buf;
    buf << addr.toText() << "/" << static_cast<int>(prefix_len);
    return (buf.str());
}

/// @brief Tests given IA option set for successful status.
///
/// This function is used to determine if the given  Option6IA represents
/// a successful lease operation.  If it contains no status option or a status
/// option of 0 (which is defined to mean success), then the option represents
/// success and should contain a lease value (address or prefix).
///
/// @param ia pointer to the Option6IA to test
///
/// @return True if the option represents success, false otherwise.
bool checkIAStatus(boost::shared_ptr<Option6IA>& ia) {
    OptionCustomPtr status =
            boost::dynamic_pointer_cast
                <OptionCustom>(ia->getOption(D6O_STATUS_CODE));

   // If a non-zero status is present, bail.
   if (status) {
        int status_val = status->readInteger<uint16_t>(0);
        if (status_val != 0) {
            std::cout << "SKIPPING PACKET STATUS is not success:"
                      << status_val << std::endl;
            return (false);
        }
    }

    return (true);
}

/// @brief Fetches the default IPv4 user from the registry.
///
/// The default user may be used to provide default property values.
///
/// @return A pointer to the IPv4 user or null if not defined.
const UserPtr& getDefaultUser4() {
   return (user_registry->findUser(UserId(UserId::HW_ADDRESS,
                                          default_user4_id_str)));
}

/// @brief Fetches the default IPv6 user from the registry.
///
/// The default user may be used to provide default property values.
///
/// @return A pointer to the IPv6 user or null if not defined.
const UserPtr& getDefaultUser6() {
   return (user_registry->findUser(UserId(UserId::DUID,
                                          default_user6_id_str)));
}

