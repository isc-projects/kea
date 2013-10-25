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

/// @file Defines the pkt4_send and pkt6_send callout functions.

#include <asiolink/io_address.h>
#include <hooks/hooks.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_string.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <user_chk.h>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

extern void generate_output_record(const std::string& id_type_str,
                            const std::string& id_val_str,
                            const std::string& addr_str,
                            const bool& registered);
extern std::string getV6AddrStr (Pkt6Ptr response);
extern std::string getAddrStrIA_NA(OptionPtr options);
extern std::string getAddrStrIA_PD(OptionPtr options);
extern bool checkIAStatus(boost::shared_ptr<Option6IA>& ia_opt);

extern void add4Options(Pkt4Ptr& response, UserPtr& user);
extern void add6Options(Pkt6Ptr& response, UserPtr& user);

/// @brief  This callout is called at the "pkt4_send" hook.
///
/// This function searches the UserRegistry for the client indicated by the
/// inbound IPv4 DHCP packet. If the client is found  @todo
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
            // @todo store defaults in a defualt user
            // add4Options(response, default_user4);
        }
    } catch (const std::exception& ex) {
        std::cout << "DHCP UserCheckHook : pkt4_send unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

void add4Options(Pkt4Ptr& response, UserPtr& user) {
    std::string opt_value = user->getProperty("bootfile");
    if (!opt_value.empty()) {
        std::cout << "DHCP UserCheckHook : add4Options "
              << "adding boot file:" << opt_value << std::endl;

        // Set file field
        response->setFile((const uint8_t*)(opt_value.c_str()),
                          opt_value.length());

        // Remove the option if it exists.
        OptionPtr opt = response->getOption(DHO_BOOT_FILE_NAME);
        if (opt) {
            response->delOption(DHO_BOOT_FILE_NAME);
        }

        // Now add the boot file option.
        opt.reset(new OptionString(Option::V4, DHO_BOOT_FILE_NAME, opt_value));
        response->addOption(opt);
    }

    opt_value = user->getProperty("tftp_server");
    if (!opt_value.empty()) {
        std::cout << "DHCP UserCheckHook : add4Options "
              << "adding TFTP server:" << opt_value << std::endl;

        // Remove the option if it exists.
        OptionPtr opt = response->getOption(DHO_TFTP_SERVER_NAME);
        if (opt) {
            response->delOption(DHO_TFTP_SERVER_NAME);
        }

        // Now add the boot file option.
        opt.reset(new OptionString(Option::V4, DHO_TFTP_SERVER_NAME,
                                   opt_value));
        response->addOption(opt);
    }
    // add next option here
}

void add6Options(Pkt6Ptr& response, UserPtr& user) {
    OptionPtr vendor = response->getOption(D6O_VENDOR_OPTS);
    if (!vendor) {
        return;
    }

    /// @todo: This will be DOCSIS3_V6_CONFIG_FILE.
    /// Unfortunately, 3207 was branched from master before
    /// 3194 was merged in, so this branch does not have
    /// src/lib/dhcp/docsis3_option_defs.h.

    std::string opt_value = user->getProperty("bootfile");
    if (!opt_value.empty()) {
        std::cout << "DHCP UserCheckHook : add6Options "
                  << "adding boot file:" << opt_value << std::endl;
        vendor->delOption(33);
        OptionPtr boot_opt(new OptionString(Option::V6, 33, opt_value));
        vendor->addOption(boot_opt);
    }

    opt_value = user->getProperty("tftp_server");
    if (!opt_value.empty()) {
        std::cout << "DHCP UserCheckHook : add6Options "
                  << "adding tftp server:" << opt_value << std::endl;

        vendor->delOption(32);
        OptionPtr opt(new OptionString(Option::V6, 32, opt_value));
        vendor->addOption(opt);
    }

    // add next option here
}

/// @brief  This callout is called at the "pkt6_send" hook.
///
/// This function searches the UserRegistry for the client indicated by the
/// inbound IPv6 DHCP packet. If the client is found  @todo
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt6_send(CalloutHandle& handle) {
    try {
        Pkt6Ptr response;
        handle.getArgument("response6", response);

        uint8_t packet_type = response->getType();
        if (packet_type == DHCPV6_DECLINE) {
            std::cout << "DHCP UserCheckHook : pkt6_send"
                      << "skipping packet type: "
                      << static_cast<int>(packet_type) << std::endl;
            return (0);
        }

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
            // @todo store defaults in a default user
            //add6Options(response, default_user6);
        }
    } catch (const std::exception& ex) {
        std::cout << "DHCP UserCheckHook : pkt6_send unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

/// @brief Adds an entry to the end of the user check outcome file.
///
/// Each user entry is written in an ini-like format, with one name-value pair
/// per line as follows:
///
/// id_type=<id type>
/// client=<id str>
/// subnet=<subnet str>
/// registered=<is registered>"
///
/// where:
/// <id type> text label of the id type: "HW_ADDR" or "DUID"
/// <id str> user's id formatted as either isc::dhcp::Hwaddr.toText() or
/// isc::dhcp::DUID.toText()
/// <subnet str> selected subnet formatted as isc::dhcp::Subnet4::toText() or
/// isc::dhcp::Subnet6::toText() as appropriate.
/// <is registered> "yes" or "no"
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
/// @param subnet_str text representation  of the selected subnet
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
std::string getV6AddrStr (Pkt6Ptr response) {
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
/// @todo fill out this out
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

/// @brief Stringify the delegated prefix in an D6O_IA_DP option set
std::string getAddrStrIA_PD(OptionPtr options) {
    boost::shared_ptr<Option6IA> ia =
        boost::dynamic_pointer_cast<Option6IA>(options);

    if (!ia) {
        isc_throw (isc::BadValue, "D6O_IA_PD option invalid");
    }

    // If status indicates a failure return a blank string.
    if (!checkIAStatus(ia)) {
        return (std::string(""));
    }

    options = ia->getOption(D6O_IAPREFIX);
    if (!options) {
        isc_throw(isc::BadValue, "D60_IAPREFIX option is missing");
    }

    boost::shared_ptr<Option6IAPrefix> addr_option;
    addr_option = boost::dynamic_pointer_cast<Option6IAPrefix>(options);
    if (!addr_option) {
        isc_throw (isc::BadValue, "D6O_IA_PD addr option bad");
    }

    isc::asiolink::IOAddress addr = addr_option->getAddress();
    uint8_t prefix_len = addr_option->getLength();

    stringstream buf;
    buf << addr.toText() << "/" << static_cast<int>(prefix_len);
    return (buf.str());
}

/// @brief Tests given IA option set for successful status.
/// @todo fill out this out
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


} // end extern "C"
