// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMAND_OPTIONS_H
#define COMMAND_OPTIONS_H

#include <boost/noncopyable.hpp>

#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace perfdhcp {

/// \brief Command Options.
///
/// This class is responsible for parsing the command-line and storing the
/// specified options.
///
class CommandOptions : public boost::noncopyable {
public:

    /// \brief A class encapsulating the type of lease being requested from the
    /// server.
    ///
    /// This class comprises convenience functions to convert the lease type
    /// to the textual format and to match the appropriate lease type with the
    /// value of the -e<lease-type> parameter specified from the command line.
    class LeaseType {
    public:

        /// The lease type code.
        enum Type {
            ADDRESS,
            PREFIX,
            ADDRESS_AND_PREFIX
        };

        LeaseType();

        /// \brief Constructor from lease type code.
        ///
        /// \param lease_type A lease type code.
        LeaseType(const Type lease_type);

        /// \brief Checks if lease type has the specified code.
        ///
        /// \param lease_type A lease type code to be checked.
        ///
        /// \return true if lease type is matched with the specified code.
        bool is(const Type lease_type) const;

        /// \brief Checks if lease type implies request for the address,
        /// prefix (or both) as specified by the function argument.
        ///
        /// This is a convenience function to check that, for the lease type
        /// specified from the command line, the address or prefix
        /// (IA_NA or IA_PD) option should be sent to the server.
        /// For example, if user specified '-e address-and-prefix' in the
        /// command line this function will return true for both ADDRESS
        /// and PREFIX, because both address and prefix is requested from
        /// the server.
        ///
        /// \param lease_type A lease type.
        ///
        /// \return true if the lease type implies creation of the address,
        /// prefix or both as specified by the argument.
        bool includes(const Type lease_type) const;

        /// \brief Sets the lease type code.
        ///
        /// \param lease_type A lease type code.
        void set(const Type lease_type);

        /// \brief Sets the lease type from the command line argument.
        ///
        /// \param cmd_line_arg An argument specified in the command line
        /// as -e<lease-type>:
        /// - address-only
        /// - prefix-only
        ///
        /// \throw isc::InvalidParameter if the specified argument is invalid.
        void fromCommandLine(const std::string& cmd_line_arg);

        /// \brief Return textual representation of the lease type.
        ///
        /// \return A textual representation of the lease type.
        std::string toText() const;

    private:
        Type type_; ///< A lease type code.

    };

    /// 2-way (cmd line param -i) or 4-way exchanges
    enum ExchangeMode {
        DO_SA,
        DORA_SARR
    };

    /// CommandOptions is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// \return the only existing instance of command options
    static CommandOptions& instance();

    /// \brief Reset to defaults
    ///
    /// Reset data members to default values. This is specifically
    /// useful when unit tests are performed using different
    /// command line options.
    void reset();

    /// \brief Parse command line.
    ///
    /// Parses the command line and stores the selected options
    /// in class data members.
    ///
    /// \param argc Argument count passed to main().
    /// \param argv Argument value array passed to main().
    /// \param print_cmd_line Print the command line being run to the console.
    /// \throws isc::InvalidParameter if parse fails.
    /// \return true if program has been run in help or version mode ('h' or 'v' flag).
    bool parse(int argc, char** const argv, bool print_cmd_line = false);

    /// \brief Returns IP version.
    ///
    /// \return IP version to be used.
    uint8_t getIpVersion() const { return ipversion_; }

    /// \brief Returns packet exchange mode.
    ///
    /// \return packet exchange mode.
    ExchangeMode getExchangeMode() const { return exchange_mode_; }

    /// \ brief Returns the type of lease being requested.
    ///
    /// \return type of lease being requested by perfdhcp.
    LeaseType getLeaseType() const { return (lease_type_); }

    /// \brief Returns echange rate.
    ///
    /// \return exchange rate per second.
    int getRate() const { return rate_; }

    /// \brief Returns a rate at which DHCPv6 Renew messages are sent.
    ///
    /// \return A rate at which IPv6 Renew messages are sent.
    int getRenewRate() const { return (renew_rate_); }

    /// \brief Returns a rate at which DHCPv6 Release messages are sent.
    ///
    /// \return A rate at which DHCPv6 Release messages are sent.
    int getReleaseRate() const { return (release_rate_); }

    /// \brief Returns delay between two performance reports.
    ///
    /// \return delay between two consecutive performance reports.
    int getReportDelay() const { return report_delay_; }

    /// \brief Returns number of simulated clients.
    ///
    /// \return number of simulated clients.
    uint32_t getClientsNum() const { return clients_num_; }

    /// \brief Returns MAC address template.
    ///
    /// \return MAC address template to simulate different clients.
    std::vector<uint8_t> getMacTemplate() const { return mac_template_; }

    /// \brief Returns DUID template.
    ///
    /// \return DUID template to simulate different clients.
    std::vector<uint8_t> getDuidTemplate() const { return duid_template_; }

    /// \brief Returns base values.
    ///
    /// \return all base values specified.
    std::vector<std::string> getBase() const { return base_; }

    /// \brief Returns maximum number of exchanges.
    ///
    /// \return number of exchange requests before test is aborted.
    std::vector<int> getNumRequests() const { return num_request_; }

    /// \brief Returns test period.
    ///
    /// \return test period before it is aborted.
    int getPeriod() const { return period_; }

    /// \brief Returns drop time
    ///
    /// The method returns maximum time elapsed from
    /// sending the packet before it is assumed dropped.
    ///
    /// \return return time before request is assumed dropped.
    std::vector<double> getDropTime() const { return drop_time_; }

    /// \brief Returns maximum drops number.
    ///
    /// Returns maximum number of packet drops before
    /// aborting a test.
    ///
    /// \return maximum number of dropped requests.
    std::vector<int> getMaxDrop() const { return max_drop_; }

    /// \brief Returns maximal percentage of drops.
    ///
    /// Returns maximal percentage of packet drops
    /// before aborting a test.
    ///
    /// \return maximum percentage of lost requests.
    std::vector<double> getMaxDropPercentage() const { return max_pdrop_; }

    /// \brief Returns local address or interface name.
    ///
    /// \return local address or interface name.
    std::string getLocalName() const { return localname_; }

    /// \brief Checks if interface name was used.
    ///
    /// The method checks if interface name was used
    /// rather than address.
    ///
    /// \return true if interface name was used.
    bool isInterface() const { return is_interface_; }

    /// \brief Returns number of preload exchanges.
    ///
    /// \return number of preload exchanges.
    int getPreload() const { return preload_; }

    /// \brief Returns aggressivity value.
    ///
    /// \return aggressivity value.
    int getAggressivity() const { return aggressivity_; }

    /// \brief Returns local port number.
    ///
    /// \return local port number.
    int getLocalPort() const { return local_port_; }

    /// \brief Checks if seed provided.
    ///
    /// \return true if seed was provided.
    bool isSeeded() const { return seeded_; }

    /// \brief Returns radom seed.
    ///
    /// \return random seed.
    uint32_t getSeed() const { return seed_; }

    /// \brief Checks if broadcast address is to be used.
    ///
    /// \return true if broadcast address is to be used.
    bool isBroadcast() const { return broadcast_; }

    /// \brief Check if rapid commit option used.
    ///
    /// \return true if rapid commit option is used.
    bool isRapidCommit() const { return rapid_commit_; }

    /// \brief Check if server-ID to be taken from first package.
    ///
    /// \return true if server-iD to be taken from first package.
    bool isUseFirst() const { return use_first_; }

    /// \brief Returns template file names.
    ///
    /// \return template file names.
    std::vector<std::string> getTemplateFiles() const { return template_file_; }

    /// brief Returns template offsets for xid.
    ///
    /// \return template offsets for xid.
    std::vector<int> getTransactionIdOffset() const { return xid_offset_; }

    /// \brief Returns template offsets for rnd.
    ///
    /// \return template offsets for rnd.
    std::vector<int> getRandomOffset() const { return rnd_offset_; }

    /// \brief Returns template offset for elapsed time.
    ///
    /// \return template offset for elapsed time.
    int getElapsedTimeOffset() const { return elp_offset_; }

    /// \brief Returns template offset for server-ID.
    ///
    /// \return template offset for server-ID.
    int getServerIdOffset() const { return sid_offset_; }

    /// \brief Returns template offset for requested IP.
    ///
    /// \return template offset for requested IP.
    int getRequestedIpOffset() const { return rip_offset_; }

    /// \brief Returns diagnostic selectors.
    ///
    /// \return diagnostics selector.
    std::string getDiags() const { return diags_; }

    /// \brief Returns wrapped command.
    ///
    /// \return wrapped command (start/stop).
    std::string getWrapped() const { return wrapped_; }

    /// \brief Returns server name.
    ///
    /// \return server name.
    std::string getServerName() const { return server_name_; }

    /// \brief Print command line arguments.
    void printCommandLine() const;

    /// \brief Print usage.
    ///
    /// Prints perfdhcp usage.
    void usage() const;

    /// \brief Print program version.
    ///
    /// Prints perfdhcp version.
    void version() const;

private:

    /// \brief Default Constructor.
    ///
    /// Private constructor as this is a singleton class.
    /// Use CommandOptions::instance() to get instance of it.
    CommandOptions() {
        reset();
    }

    /// \brief Initializes class members based on the command line.
    ///
    /// Reads each command line parameter and sets class member values.
    ///
    /// \param argc Argument count passed to main().
    /// \param argv Argument value array passed to main().
    /// \param print_cmd_line Print the command line being run to the console.
    /// \throws isc::InvalidParameter if command line options initialization fails.
    /// \return true if program has been run in help or version mode ('h' or 'v' flag).
    bool initialize(int argc, char** argv, bool print_cmd_line);

    /// \brief Validates initialized options.
    ///
    /// \throws isc::InvalidParameter if command line validation fails.
    void validate() const;

    /// \brief Throws !InvalidParameter exception if condition is true.
    ///
    /// Convenience function that throws an InvalidParameter exception if
    /// the condition argument is true.
    ///
    /// \param condition Condition to be checked.
    /// \param errmsg Error message in exception.
    /// \throws isc::InvalidParameter if condition argument true.
    inline void check(bool condition, const std::string& errmsg) const;

    /// \brief Casts command line argument to positive integer.
    ///
    /// \param errmsg Error message if lexical cast fails.
    /// \throw InvalidParameter if lexical cast fails.
    int positiveInteger(const std::string& errmsg) const;

    /// \brief Casts command line argument to non-negative integer.
    ///
    /// \param errmsg Error message if lexical cast fails.
    /// \throw InvalidParameter if lexical cast fails.
    int nonNegativeInteger(const std::string& errmsg) const;

    /// \brief Returns command line string if it is not empty.
    ///
    /// \param errmsg Error message if string is empty.
    /// \throw InvalidParameter if string is empty.
    std::string nonEmptyString(const std::string& errmsg) const;

    /// \brief Decodes the lease type requested by perfdhcp from optarg.
    ///
    /// \throw InvalidParameter if lease type value specified is invalid.
    void initLeaseType();

    /// \brief Set number of clients.
    ///
    /// Interprets the getopt() "opt" global variable as the number of clients
    /// (a non-negative number).  This value is specified by the "-R" switch.
    ///
    /// \throw InvalidParameter if -R<value> is wrong.
    void initClientsNum();

    /// \brief Sets value indicating if interface name was given.
    ///
    /// Method checks if the command line argument given with
    /// '-l' option is the interface name. The is_interface_ member
    /// is set accordingly.
    void initIsInterface();

    /// \brief Decodes base provided with -b<base>.
    ///
    /// Function decodes argument of -b switch, which
    /// specifies a base value used to generate unique
    /// mac or duid values in packets sent to system
    /// under test.
    /// The following forms of switch arguments are supported:
    /// - -b mac=00:01:02:03:04:05
    /// - -b duid=0F1234 (duid can be up to 128 hex digits)
    //  Function will decode 00:01:02:03:04:05 and/or
    /// 0F1234 respectively and initialize mac_template_
    /// and/or duid_template_ members.
    ///
    /// \param base Base in string format.
    /// \throws isc::InvalidParameter if base is invalid.
    void decodeBase(const std::string& base);

    /// \brief Decodes base MAC address provided with -b<base>.
    ///
    /// Function decodes parameter given as -b mac=00:01:02:03:04:05
    /// The function will decode 00:01:02:03:04:05 initialize mac_template_
    /// class member.
    /// Provided MAC address is for example only.
    ///
    /// \param base Base string given as -b mac=00:01:02:03:04:05.
    /// \throws isc::InvalidParameter if mac address is invalid.
    void decodeMac(const std::string& base);

    /// \brief Decodes base DUID provided with -b<base>.
    ///
    /// Function decodes parameter given as -b duid=0F1234.
    /// The function will decode 0F1234 and initialize duid_template_
    /// class member.
    /// Provided DUID is for example only.
    ///
    /// \param base Base string given as -b duid=0F1234.
    /// \throws isc::InvalidParameter if DUID is invalid.
    void decodeDuid(const std::string& base);

    /// \brief Generates DUID-LLT (based on link layer address).
    ///
    /// Function generates DUID based on link layer address and
    /// initiates duid_template_ value with it.
    /// \todo add support to generate DUIDs other than based on
    /// 6-octets long MACs (e.g. DUID-UUID.
    void generateDuidTemplate();

    /// \brief Converts two-digit hexadecimal string to a byte.
    ///
    /// \param hex_text Hexadecimal string e.g. AF.
    /// \throw isc::InvalidParameter if string does not represent hex byte.
    uint8_t convertHexString(const std::string& hex_text) const;

    /// IP protocol version to be used, expected values are:
    /// 4 for IPv4 and 6 for IPv6, default value 0 means "not set"
    uint8_t ipversion_;
    /// Packet exchange mode (e.g. DORA/SARR)
    ExchangeMode exchange_mode_;
    /// Lease Type to be obtained: address only, IPv6 prefix only.
    LeaseType lease_type_;
    /// Rate in exchange per second
    int rate_;
    /// A rate at which DHCPv6 Renew messages are sent.
    int renew_rate_;
    /// A rate at which DHCPv6 Release messages are sent.
    int release_rate_;
    /// Delay between generation of two consecutive
    /// performance reports
    int report_delay_;
    /// Number of simulated clients (aka randomization range).
    uint32_t clients_num_;
    /// MAC address template used to generate unique MAC
    /// addresses for simulated clients.
    std::vector<uint8_t> mac_template_;
    /// DUID template used to generate unique DUIDs for
    /// simulated clients
    std::vector<uint8_t> duid_template_;
    /// Collection of base values specified with -b<value>
    /// options. Supported "bases" are mac=<mac> and duid=<duid>
    std::vector<std::string> base_;
    /// Number of 2 or 4-way exchanges to perform.
    std::vector<int> num_request_;
    /// Test period in seconds
    int period_;
    /// Indicates number of -d<value> parameters specified by user.
    /// If this value goes above 2, command line parsing fails.
    uint8_t drop_time_set_;
    /// Time to elapse before request is lost. The first value of
    /// two-element vector refers to DO/SA exchanges,
    /// second value refers to RA/RR. Default values are { 1, 1 }
    std::vector<double> drop_time_;
    /// Maximum number of drops request before aborting test.
    /// First value of two-element vector specifies maximum
    /// number of drops for DO/SA exchange, second value
    /// specifies maximum number of drops for RA/RR.
    std::vector<int> max_drop_;
    /// Maximal percentage of lost requests before aborting test.
    /// First value of two-element vector specifies percentage for
    /// DO/SA exchanges, second value for RA/RR.
    std::vector<double> max_pdrop_;
    /// Local address or interface specified with -l<value> option.
    std::string localname_;
    /// Indicates that specified value with -l<value> is
    /// rather interface (not address)
    bool is_interface_;
    /// Number of preload packets. Preload packets are used to
    /// initiate communication with server before doing performance
    /// measurements.
    int preload_;
    /// Number of exchanges sent before next pause.
    int aggressivity_;
    /// Local port number (host endian)
    int local_port_;
    /// Randomization seed.
    uint32_t seed_;
    /// Indicates that randomization seed was provided.
    bool seeded_;
    /// Indicates that we use broadcast address.
    bool broadcast_;
    /// Indicates that we do rapid commit option.
    bool rapid_commit_;
    /// Indicates that we take server id from first received packet.
    bool use_first_;
    /// Packet template file names. These files store template packets
    /// that are used for initiating exchanges. Template packets
    /// read from files are later tuned with variable data.
    std::vector<std::string> template_file_;
    /// Offset of transaction id in template files. First vector
    /// element points to offset for DISCOVER/SOLICIT messages,
    /// second element points to transaction id offset for
    /// REQUEST messages
    std::vector<int> xid_offset_;
    /// Random value offset in templates. Random value offset
    /// points to last octet of DUID. Up to 4 last octets of
    /// DUID are randomized to simulate different clients.
    std::vector<int> rnd_offset_;
    /// Offset of elapsed time option in template packet.
    int elp_offset_;
    /// Offset of server id option in template packet.
    int sid_offset_;
    /// Offset of requested ip data in template packet
    int rip_offset_;
    /// String representing diagnostic selectors specified
    /// by user with -x<value>.
    std::string diags_;
    /// Command to be executed at the beginning/end of the test.
    /// This command is expected to expose start and stop argument.
    std::string wrapped_;
    /// Server name specified as last argument of command line.
    std::string server_name_;
};

} // namespace perfdhcp
} // namespace isc

#endif // COMMAND_OPTIONS_H
