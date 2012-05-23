// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __COMMAND_OPTIONS_H
#define __COMMAND_OPTIONS_H

#include <string>
#include <vector>

#include <boost/noncopyable.hpp>

namespace isc {
namespace perfdhcp {

/// \brief Command Options
///
/// This class is responsible for parsing the command-line and storing the
/// specified options.
///
class CommandOptions : public boost::noncopyable {
public:
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
    /// Resets the CommandOptions object to default values.
    void reset();

    /// \brief Parse command line
    ///
    /// Parses the command line and stores the selected options.
    ///
    /// \param argc Argument count passed to main().
    /// \param argv Argument value array passed to main().
    /// \param force_reset Force  reset of state variables
    /// \throws isc::InvalidParameter if parsing fails
    void parse(int argc, char** const argv);

    /// \brief Returns IP version
    ///
    /// \return IP version to be used
    uint8_t getIpVersion() const { return ipversion_; }

    /// \brief Returns packet exchange mode
    ///
    /// \return packet exchange mode
    ExchangeMode getExchangeMode() const { return exchange_mode_; }

    /// \brief Returns echange rate
    ///
    /// \return exchange rate per second
    int getRate() const { return rate_; }

    /// \brief Returns report delay
    ///
    /// \return delay between two consecutive reports
    int getReportDelay() const { return report_delay_; }

    /// \brief Returns randomization range
    ///
    /// \return randomization range
    uint32_t getRandomRange() const { return random_range_; }

    /// \brief Returns MAC addr prefix
    ///
    /// \ return MAC addr prefix to generate different clients
    std::vector<uint8_t> getMacPrefix() const { return mac_prefix_; }

    /// \brief Returns DUID prefix
    ///
    /// \return DUID prefix to generate different clients
    std::vector<uint8_t> getDuidPrefix() const { return duid_prefix_; }

    /// \brief Returns base values
    ///
    /// \return base values for xid generation
    std::vector<std::string> getBase() const { return base_; }

    /// \brief Returns number of exchanges
    ///
    /// \return number of exchange requests
    std::vector<int> getNumRequests() const { return num_request_; }

    /// \brief Returns test period
    ///
    /// \return test period
    int getPeriod() const { return period_; }

    /// \brief Returns lost time
    ///
    /// \return return time before request is lost
    std::vector<double> getDropTime() const { return drop_time_; }

    /// \brief Returns max drops number
    ///
    /// \return maximum number of lost requests
    std::vector<int> getMaxDrop() const { return max_drop_; }

    /// \brief Returns max percentage of drops
    ///
    /// \return maximum percentage of lost requests
    std::vector<double> getMaxDropPercentage() const { return max_pdrop_; }

    /// \brief Returns local address or interface
    ///
    /// \return local address or interface
    std::string getLocalName() const { return localname_; }

    /// \brief Checks if interface name is used
    ///
    /// \return true if interface name was specified
    bool isInterface() const { return is_interface_; }

    /// \brief Returns number of preload exchanges
    ///
    /// \return number of preload exchanges
    int getPreload() const { return preload_; }

    /// \brief Returns aggressivity value
    ///
    /// \return aggressivity value
    int getAggressivity() const { return aggressivity_; }

    /// \brief Returns local port number
    ///
    /// \return local port number
    int getLocalPort() const { return local_port_; }

    /// \brief Checks if seed provided
    ///
    /// \return true if seed was provided
    bool isSeeded() const { return seeded_; }

    /// \brief Returns radom seed
    ///
    /// \return random seed
    uint32_t getSeed() const { return seed_; }

    /// \brief Checks if broadcast
    ///
    /// \return true if broadcast handling
    bool isBroadcast() const { return broadcast_; }

    /// \brief Check if rapid commit used
    ///
    /// \return true if rapid commit is used
    bool isRapidCommit() const { return rapid_commit_; }

    /// \brief Check if server-ID taken from first package
    ///
    /// \return true if server-iD to be taken from first package
    bool isUseFirst() const { return use_first_; }

    /// \brief Returns template file names
    ///
    /// \return template file names
    std::vector<std::string> getTemplateFiles() const { return template_file_; }

    /// brief Returns template offsets for xid
    ///
    /// \return template offsets for xid
    std::vector<int> getTransactionIdOffset() const { return xid_offset_; }

    /// \brief Returns template offsets for rnd
    ///
    /// \return template offsets for rnd
    std::vector<int> getRandomOffset() const { return rnd_offset_; }

    /// \brief Returns template offset for elapsed time
    ///
    /// \return template offset for elapsed time
    int getElapsedTimeOffset() const { return elp_offset_; }

    /// \brief Returns template offset for server-ID
    ///
    /// \return template offset for server-ID
    int getServerIdOffset() const { return sid_offset_; }

    /// \brief Returns template offset for requested IP
    ///
    /// \return template offset for requested IP
    int getRequestedIpOffset() const { return rip_offset_; }

    /// \brief Returns diagnostic selectors
    ///
    /// \return diagnostic selector
    std::string getDiags() const { return diags_; }

    /// \brief Returns wrapped command
    ///
    /// \return wrapped command
    std::string getWrapped() const { return wrapped_; }

    /// \brief Returns server name
    ///
    /// \return server name
    std::string getServerName() const { return server_name_; }

    /// \brief Print usage
    ///
    /// Prints perfdhcp usage
    void usage() const;

    /// \brief Print program version
    ///
    /// Prints perfdhcp version
    void version() const;

private:

    /// \brief Default Constructor
    ///
    /// Protected constructor as this is a singleton class.
    /// Use CommandOptions::instance() to get instance of it.
    CommandOptions() {
        reset();
    }

private:
    /// \brief Initializes class members based command line
    ///
    /// Reads each command line parameter and sets class member values
    ///
    /// \param argc Argument count passed to main().
    /// \param argv Argument value array passed to main().
    /// \throws isc::InvalidParameter if command line options initialization fails
    void initialize(int argc, char** argv);

    /// \brief Validates initialized options
    ///
    /// \throws isc::InvalidParameter if command line validation fails
    void validate() const;

    /// \brief Throws !InvalidParameter exception if condition is true
    ///
    /// Convenience function that throws an !InvalidParameter exception if
    /// the condition argument is true
    ///
    /// \param condition Condition to be checked
    /// \param errmsg Error message in exception
    /// \throws isc::InvalidParameter if condition argument true
    inline void check(bool condition, const std::string& errmsg) const;

    /// \brief Casts command line arg to positive int
    ///
    /// \param errmsg Error message if lexical cast fails
    /// \throw InvalidParameter if lexical cast fails
    int positiveInteger(const std::string& errmsg);

    /// \brief Casts command line arg to non-negative int
    ///
    /// \param errmsg Error message if lexical cast fails
    /// \throw InvalidParameter if lexical cast fails
    int nonNegativeInteger(const std::string& errmsg);

    /// \brief Returns command line string if it is non-empty
    ///
    /// \param errmsg Error message if string is empty
    /// \throw InvalidParameter if string is empty
    std::string nonEmptyString(const std::string& errmsg);

    /// \brief Calculates max_random_ and random_range_
    ///
    /// \param opt Value of -R option
    /// \throw InvalidParameter if -R<value> is wrong
    void initRandomRange(const std::string& opt);

    /// \brief Decodes base provided with -b<base>
    ///
    /// Function decodes parameters given with -b<base>
    /// parameter. Currently it supports the following command line options e.g.:
    /// -b mac=00:01:02:03:04:05
    /// -b duid=0F1234 (duid can be up to 128 hex digits)
    //  Function will decode 00:01:02:03:04:05 and/or
    /// 0F1234 repsectively and initialize mac_prefix_
    /// and/or duid_prefix_ members
    ///
    /// \param base Base in string format
    /// \throws isc::InvalidParameter if base is invalid
    void decodeBase(const std::string& base);

    /// \brief Decodes base MAC address provided with -b<base>
    ///
    /// Function decodes parameter given as -b mac=00:01:02:03:04:05
    /// Function will decode 00:01:02:03:04:05 initialize mac_prefix_
    /// class member.
    /// Provided MAC address is for example only
    ///
    /// \param base Base string given as -b mac=00:01:02:03:04:05
    /// \throws isc::InvalidParameter if mac address is invalid
    void decodeMac(const std::string& base);

    /// \brief Decodes base DUID provided with -b<base>
    ///
    /// Function decodes parameter given as -b duid=0F1234
    /// Function will decode 0F1234 and initialize duid_prefix_
    /// class member.
    /// Provided DUID is for example only.
    ///
    /// \param base Base string given as -b mac=00:01:02:03:04:05
    /// \throws isc::InvalidParameter if DUID is invalid
    void decodeDuid(const std::string& base);

    /// \brief converts two digit hex string to byte
    ///
    /// \param s hex string e.g. AF
    /// \throw isc::InvalidParameter if string does not represent hex byte
    uint8_t convertHexString(const std::string& s);

    uint8_t ipversion_;                      ///< IP version
    ExchangeMode exchange_mode_  ;           ///< Packet exchange mode (e.g. DORR/SARR)
    int rate_;                               ///< rate in exchange per second
    int report_delay_;                       ///< delay between two reports
    uint32_t random_range_;                  ///< number of simulated clients
    uint32_t max_random_;                    ///< maximum random value
    std::vector<uint8_t> mac_prefix_;        ///< MAC addr prefix
    std::vector<uint8_t> duid_prefix_;       ///< DUID prefix
    std::vector<std::string> base_;          ///< base values for xid
    std::vector<int> num_request_;           ///< number of exchanges
    int period_;                             ///< test period
    int drop_time_set_;                      ///< losttime[0] was set
    std::vector<double> drop_time_;          ///< time before a request is lost
    int max_drop_set_;                       ///< max{p}drop[0] was set
    std::vector<int> max_drop_;              ///< maximum number of lost requests
    std::vector<double> max_pdrop_;          ///< maximum percentage
    std::string localname_;                  ///< local address or interface
    bool is_interface_;                      ///< interface vs local address
    int preload_;                            ///< preload exchanges
    int aggressivity_;                       ///< back to back exchanges
    int local_port_;                         ///< local port number (host endian)
    bool seeded_;                            ///< is a seed provided
    uint32_t seed_;                          ///< randomization seed
    bool broadcast_;                         ///< use broadcast
    bool rapid_commit_;                      ///< add rapid commit option
    bool use_first_;                         ///< where to take the server-ID
    std::vector<std::string> template_file_; ///< template file name
    std::vector<int> xid_offset_;            ///< template offsets (xid)*/
    std::vector<int> rnd_offset_;            ///< template offsets (random)
    int elp_offset_;                         ///< template offset (elapsed time)
    int sid_offset_;                         ///< template offset (server ID)
    int rip_offset_;                         ///< template offset (requested IP)
    std::string diags_;                      ///< diagnostic selectors
    std::string wrapped_;                    ///< wrapped command
    std::string server_name_;                ///< server
};

} // namespace perfdhcp
} // namespace isc

#endif // __COMMAND_OPTIONS_H
