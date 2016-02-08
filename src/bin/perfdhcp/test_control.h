// Copyright (C) 2012-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_CONTROL_H
#define TEST_CONTROL_H

#include "packet_storage.h"
#include "rate_control.h"
#include "stats_mgr.h"

#include <dhcp/iface_mgr.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>
#include <vector>

namespace isc {
namespace perfdhcp {

/// Default transaction id offset in the packet template.
static const size_t DHCPV4_TRANSID_OFFSET = 4;
/// Default offset of MAC's last octet in the packet template..
static const size_t DHCPV4_RANDOMIZATION_OFFSET = 35;
/// Default elapsed time offset in the packet template.
static const size_t DHCPV4_ELAPSED_TIME_OFFSET = 8;
/// Default server id offset in the packet template.
static const size_t DHCPV4_SERVERID_OFFSET = 54;
/// Default requested ip offset in the packet template.
static const size_t DHCPV4_REQUESTED_IP_OFFSET = 240;
/// Default DHCPV6 transaction id offset in t the packet template.
static const size_t DHCPV6_TRANSID_OFFSET = 1;
/// Default DHCPV6 randomization offset (last octet of DUID)
/// in the packet template.
static const size_t DHCPV6_RANDOMIZATION_OFFSET = 21;
/// Default DHCPV6 elapsed time offset in the packet template.
static const size_t DHCPV6_ELAPSED_TIME_OFFSET = 84;
/// Default DHCPV6 server id offset in the packet template.
static const size_t DHCPV6_SERVERID_OFFSET = 22;
/// Default DHCPV6 IA_NA offset in the packet template.
static const size_t DHCPV6_IA_NA_OFFSET = 40;

/// @brief Exception thrown when the required option is not found in a packet.
class OptionNotFound : public Exception {
public:
    OptionNotFound(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// \brief Test Control class.
///
/// This singleton class is used to run the performance test with
/// with \ref TestControl::run function. This function can be executed
/// multiple times if desired because it resets TestControl's internal
/// state every time it is executed. Prior to running \ref TestControl::run,
/// one must make sure to parse command line options by calling
/// \ref CommandOptions::parse. Failing to do this will result in an exception.
///
/// The following major stages of the test are performed by this class:
/// - set default transaction id and MAC address generators - the generator
/// is an object of \ref TestControl::NumberGenerator type and it provides
/// the custom randomization algorithms,
/// - print command line arguments,
/// - register option factory functions which are used to generate DHCP options
/// being sent to a server,
/// - create the socket for communication with a server,
/// - read packet templates if user specified template files with '-T' command
/// line option,
/// - set the interrupt handler (invoked when ^C is pressed) which makes
/// perfdhcp stop gracefully and print the test results before exiting,
/// - executes an external command (if specified '-w' option), e.g. if user
/// specified -w ./foo in the command line then program will execute
/// "./foo start" at the beginning of the test and "./foo stop" when the test
/// ends,
/// - initialize the Statistics Manager,
/// - executes the main loop:
///   - calculate how many packets must be send to satisfy desired rate,
///   - receive incoming packets from the server,
///   - check the exit conditions - terminate the program if the exit criteria
///   are fulfilled, e.g. reached maximum number of packet drops,
///   - send the number of packets appropriate to satisfy the desired rate,
///   - optionally print intermediate reports,
/// - print statistics, e.g. achieved rate,
/// - optionally print some diagnostics.
///
/// With the '-w' command line option user may specify the external application
/// or script to be executed. This is executed twice, first when the test starts
/// and second time when the test ends. This external script or application must
/// accept 'start' and 'stop' arguments. The first time it is called, it is
/// called with the argument 'start' and the second time with the argument
/// 'stop'.
///
/// The application is executed by calling fork() to fork the current perfdhcp
/// process and then call execlp() to replace the current process image with
/// the new one.
///
/// Option factory functions are registered using
/// \ref dhcp::LibDHCP::OptionFactoryRegister. Registered factory functions
/// provide a way to create options of the same type in the same way.
///  When a new option instance is needed, the corresponding factory
/// function is called to create it. This is done by calling
/// \ref dhcp::Option::factory with DHCP message type specified as one of
///  parameters. Some of the parameters passed to factory function
/// may be ignored (e.g. option buffer).
/// Please note that naming convention for factory functions within this
/// class is as follows:
/// - factoryABC4 - factory function for DHCPv4 option,
/// - factoryDEF6 - factory function for DHCPv6 option,
/// - factoryGHI - factory function that can be used to create either
/// DHCPv4 or DHCPv6 option.
class TestControl : public boost::noncopyable {
public:

    /// Statistics Manager for DHCPv4.
    typedef StatsMgr<dhcp::Pkt4> StatsMgr4;
    /// Pointer to Statistics Manager for DHCPv4;
    typedef boost::shared_ptr<StatsMgr4> StatsMgr4Ptr;
    /// Statistics Manager for DHCPv6.
    typedef StatsMgr<dhcp::Pkt6> StatsMgr6;
    /// Pointer to Statistics Manager for DHCPv6.
    typedef boost::shared_ptr<StatsMgr6> StatsMgr6Ptr;
    /// Packet exchange type.
    typedef StatsMgr<>::ExchangeType ExchangeType;
    /// Packet template buffer.
    typedef std::vector<uint8_t> TemplateBuffer;
    /// Packet template buffers list.
    typedef std::vector<TemplateBuffer> TemplateBufferCollection;

    /// \brief Socket wrapper structure.
    ///
    /// This is the wrapper that holds descriptor of the socket
    /// used to run DHCP test. The wrapped socket is closed in
    /// the destructor. This prevents resource leaks when when
    /// function that created the socket ends (normally or
    /// when exception occurs). This structure extends parent
    /// structure with new field ifindex_ that holds interface
    /// index where socket is bound to.
    struct TestControlSocket : public dhcp::SocketInfo {
        /// Interface index.
        uint16_t ifindex_;
        /// Is socket valid. It will not be valid if the provided socket
        /// descriptor does not point to valid socket.
        bool valid_;

        /// \brief Constructor of socket wrapper class.
        ///
        /// This constructor uses provided socket descriptor to
        /// find the name of the interface where socket has been
        /// bound to. If provided socket descriptor is invalid then
        /// valid_ field is set to false;
        ///
        /// \param socket socket descriptor.
        TestControlSocket(const int socket);

        /// \brief Destructor of the socket wrapper class.
        ///
        /// Destructor closes wrapped socket.
        ~TestControlSocket();

    private:
        /// \brief Initialize socket data.
        ///
        /// This method initializes members of the class that Interface
        /// Manager holds: interface name, local address.
        ///
        /// \throw isc::BadValue if interface for specified socket
        /// descriptor does not exist.
        void initSocketData();
    };

    /// \brief Number generator class.
    ///
    /// This is default numbers generator class. The member function is
    /// used to generate uint32_t values. Other generator classes should
    /// derive from this one to implement generation algorithms
    /// (e.g. sequential or based on random function).
    class NumberGenerator {
    public:

        /// \brief Destructor.
        virtual ~NumberGenerator() { }

        /// \brief Generate number.
        ///
        /// \return Generate number.
        virtual uint32_t generate() = 0;
    };

    /// The default generator pointer.
    typedef boost::shared_ptr<NumberGenerator> NumberGeneratorPtr;

    /// \brief Sequential numbers generator class.
    class SequentialGenerator : public NumberGenerator {
    public:
        /// \brief Constructor.
        ///
        /// \param range maximum number generated. If 0 is given then
        /// range defaults to maximum uint32_t value.
        SequentialGenerator(uint32_t range = 0xFFFFFFFF) :
            NumberGenerator(),
            num_(0),
            range_(range) {
            if (range_ == 0) {
                range_ = 0xFFFFFFFF;
            }
        }

        /// \brief Generate number sequentially.
        ///
        /// \return generated number.
        virtual uint32_t generate() {
            uint32_t num = num_;
            num_ = (num_ + 1) % range_;
            return (num);
        }
    private:
        uint32_t num_;   ///< Current number.
        uint32_t range_; ///< Number of unique numbers generated.
    };

    /// \brief Length of the Ethernet HW address (MAC) in bytes.
    ///
    /// \todo Make this variable length as there are cases when HW
    /// address is longer than this (e.g. 20 bytes).
    static const uint8_t HW_ETHER_LEN = 6;

    /// TestControl is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// \return the only existing instance of test control
    static TestControl& instance();

    /// brief\ Run performance test.
    ///
    /// Method runs whole performance test. Command line options must
    /// be parsed prior to running this function. Otherwise function will
    /// throw exception.
    ///
    /// \throw isc::InvalidOperation if command line options are not parsed.
    /// \throw isc::Unexpected if internal Test Controller error occurred.
    /// \return error_code, 3 if number of received packets is not equal
    /// to number of sent packets, 0 if everything is ok.
    int run();

    /// \brief Set new transaction id generator.
    ///
    /// \param generator generator object to be used.
    void setTransidGenerator(const NumberGeneratorPtr& generator) {
        transid_gen_.reset();
        transid_gen_ = generator;
    }

    /// \brief Set new MAC address generator.
    ///
    /// Set numbers generator that will be used to generate various
    /// MAC addresses to simulate number of clients.
    ///
    /// \param generator object to be used.
    void setMacAddrGenerator(const NumberGeneratorPtr& generator) {
        macaddr_gen_.reset();
        macaddr_gen_ = generator;
    }

    // We would really like following methods and members to be private but
    // they have to be accessible for unit-testing. Another, possibly better,
    // solution is to make this class friend of test class but this is not
    // what's followed in other classes.
protected:
    /// \brief Default constructor.
    ///
    /// Default constructor is protected as the object can be created
    /// only via \ref instance method.
    TestControl();

    /// \brief Check if test exit conditions fulfilled.
    ///
    /// Method checks if the test exit conditions are fulfilled.
    /// Exit conditions are checked periodically from the
    /// main loop. Program should break the main loop when
    /// this method returns true. It is calling function
    /// responsibility to break main loop gracefully and
    /// cleanup after test execution.
    ///
    /// \return true if any of the exit conditions is fulfilled.
    bool checkExitConditions() const;

    /// \brief Removes cached DHCPv6 Reply packets every second.
    ///
    /// This function wipes cached Reply packets from the storage.
    /// The number of packets left in the storage after the call
    /// to this function should guarantee that the Renew packets
    /// can be sent at the given rate. Note that the Renew packets
    /// are generated for the existing leases, represented here as
    /// replies from the server.
    /// @todo Instead of cleaning packets periodically we could
    /// just stop adding new packets when the certain threshold
    /// has been reached.
    void cleanCachedPackets();

    /// \brief Creates DHCPREQUEST from a DHCPACK message.
    ///
    /// \param ack An instance of the DHCPACK message to be used to
    /// create a new message.
    ///
    /// \return Pointer to the created message.
    dhcp::Pkt4Ptr createRequestFromAck(const dhcp::Pkt4Ptr& ack);

    /// \brief Creates DHCPv6 message from the Reply packet.
    ///
    /// This function creates DHCPv6 Renew or Release message using the
    /// data from the Reply message by copying options from the Reply
    /// message.
    ///
    /// \param msg_type A type of the message to be created.
    /// \param reply An instance of the Reply packet which contents should
    /// be used to create an instance of the new message.
    ///
    /// \return created Release or Renew message
    /// \throw isc::BadValue if the msg_type is neither DHCPV6_RENEW nor
    /// DHCPV6_RELEASE or if the reply is NULL.
    /// \throw isc::Unexpected if mandatory options are missing in the
    /// Reply message.
    dhcp::Pkt6Ptr createMessageFromReply(const uint16_t msg_type,
                                         const dhcp::Pkt6Ptr& reply);

    /// \brief Factory function to create DHCPv6 ELAPSED_TIME option.
    ///
    /// This factory function creates DHCPv6 ELAPSED_TIME option instance.
    /// If empty buffer is passed the option buffer will be initialized
    /// to length 2 and values will be initialized to zeros. Otherwise
    /// function will initialize option buffer with values in passed buffer.
    ///
    /// \param u universe (ignored)
    /// \param type option-type (ignored).
    /// \param buf option-buffer containing option content (2 bytes) or
    /// empty buffer if option content has to be set to default (0) value.
    /// \throw if elapsed time buffer size is neither 2 nor 0.
    /// \return instance o the option.
    static dhcp::OptionPtr
    factoryElapsedTime6(dhcp::Option::Universe u,
                        uint16_t type,
                        const dhcp::OptionBuffer& buf);

    /// \brief Factory function to create generic option.
    ///
    /// This factory function creates option with specified universe,
    /// type and buf. It does not have any additional logic validating
    /// the buffer contents, size  etc.
    ///
    /// \param u universe (V6 or V4).
    /// \param type option-type (ignored).
    /// \param buf option-buffer.
    /// \return instance o the option.
    static dhcp::OptionPtr factoryGeneric(dhcp::Option::Universe u,
                                          uint16_t type,
                                          const dhcp::OptionBuffer& buf);

    /// \brief Factory function to create IA_NA option.
    ///
    /// This factory function creates DHCPv6 IA_NA option instance.
    ///
    /// \todo add support for IA Address options.
    ///
    /// \param u universe (ignored).
    /// \param type option-type (ignored).
    /// \param buf option-buffer carrying IANA suboptions.
    /// \return instance of IA_NA option.
    static dhcp::OptionPtr factoryIana6(dhcp::Option::Universe u,
                                        uint16_t type,
                                        const dhcp::OptionBuffer& buf);

    /// \brief Factory function to create IA_PD option.
    ///
    /// this factory function creates DHCPv6 IA_PD option instance.
    ///
    /// \param u universe (ignored).
    /// \param type option-type (ignored).
    /// \param buf option-buffer carrying sub-options.
    static dhcp::OptionPtr factoryIapd6(dhcp::Option::Universe u,
                                        uint16_t type,
                                        const dhcp::OptionBuffer& buf);

    /// \brief Factory function to create DHCPv6 ORO option.
    ///
    /// This factory function creates DHCPv6 Option Request Option instance.
    /// The created option will contain the following set of requested options:
    /// - D6O_NAME_SERVERS
    /// - D6O_DOMAIN_SEARCH
    ///
    /// \param u universe (ignored).
    /// \param type option-type (ignored).
    /// \param buf option-buffer (ignored).
    /// \return instance of ORO option.
    static dhcp::OptionPtr
    factoryOptionRequestOption6(dhcp::Option::Universe u,
                                uint16_t type,
                                const dhcp::OptionBuffer& buf);

    /// \brief Factory function to create DHCPv6 RAPID_COMMIT option instance.
    ///
    /// This factory function creates DHCPv6 RAPID_COMMIT option instance.
    /// The buffer passed to this option must be empty because option does
    /// not have any payload.
    ///
    /// \param u universe (ignored).
    /// \param type option-type (ignored).
    /// \param buf option-buffer (ignored).
    /// \return instance of RAPID_COMMIT option..
    static dhcp::OptionPtr factoryRapidCommit6(dhcp::Option::Universe u,
                                               uint16_t type,
                                               const dhcp::OptionBuffer& buf);


    /// \brief Factory function to create DHCPv4 Request List option.
    ///
    /// This factory function creates DHCPv4 PARAMETER_REQUEST_LIST option
    /// instance with the following set of requested options:
    /// - DHO_SUBNET_MASK,
    /// - DHO_BROADCAST_ADDRESS,
    /// - DHO_TIME_OFFSET,
    /// - DHO_ROUTERS,
    /// - DHO_DOMAIN_NAME,
    /// - DHO_DOMAIN_NAME_SERVERS,
    /// - DHO_HOST_NAME.
    ///
    /// \param u universe (ignored).
    /// \param type option-type (ignored).
    /// \param buf option-buffer (ignored).
    /// \return instance o the generic option.
     static dhcp::OptionPtr factoryRequestList4(dhcp::Option::Universe u,
                                               uint16_t type,
                                               const dhcp::OptionBuffer& buf);

    /// \brief Generate DHCPv4 client identifier from HW address.
    ///
    /// This method generates DHCPv4 client identifier option from a
    /// HW address.
    ///
    /// \param hwaddr HW address.
    ///
    /// \return Pointer to an instance of the generated option.
    dhcp::OptionPtr generateClientId(const dhcp::HWAddrPtr& hwaddr) const;

    /// \brief Generate DUID.
    ///
    /// Method generates unique DUID. The number of DUIDs it can generate
    /// depends on the number of simulated clients, which is specified
    /// from the command line. It uses \ref CommandOptions object to retrieve
    /// number of clients. Since the last six octets of DUID are constructed
    /// from the MAC address, this function uses \ref generateMacAddress
    /// internally to randomize the DUID.
    ///
    /// \todo add support for other types of DUID.
    ///
    /// \param [out] randomized number of bytes randomized (initial value
    /// is ignored).
    /// \throw isc::BadValue if \ref generateMacAddress throws.
    /// \return vector representing DUID.
    std::vector<uint8_t> generateDuid(uint8_t& randomized) const;

    /// \brief Generate MAC address.
    ///
    /// This method generates MAC address. The number of unique
    /// MAC addresses it can generate is determined by the number
    /// simulated DHCP clients specified from command line. It uses
    /// \ref CommandOptions object to retrieve number of clients.
    /// Based on this the random value is generated and added to
    /// the MAC address template (default MAC address).
    ///
    /// \param [out] randomized number of bytes randomized (initial
    /// value is ignored).
    /// \throw isc::BadValue if MAC address template (default or specified
    /// from the command line) has invalid size (expected 6 octets).
    /// \return generated MAC address.
    std::vector<uint8_t> generateMacAddress(uint8_t& randomized) const;

    /// \brief generate transaction id.
    ///
    /// Generate transaction id value (32-bit for DHCPv4,
    /// 24-bit for DHCPv6).
    ///
    /// \return generated transaction id.
    uint32_t generateTransid() {
        return (transid_gen_->generate());
    }

    /// \brief Returns a timeout for packet reception.
    ///
    /// The calculation is based on the value of the timestamp
    /// when the next set of packets is to be sent. If no packet is
    /// received until then, new packets are sent.
    ///
    /// \return A current timeout in microseconds.
    uint32_t getCurrentTimeout() const;

    /// \brief Return template buffer.
    ///
    /// Method returns template buffer at specified index.
    ///
    /// \param idx index of template buffer.
    /// \throw isc::OutOfRange if buffer index out of bounds.
    /// \return reference to template buffer.
    TemplateBuffer getTemplateBuffer(const size_t idx) const;

    /// \brief Reads packet templates from files.
    ///
    /// Method iterates through all specified template files, reads
    /// their content and stores it in class internal buffers. Template
    /// file names are specified from the command line with -T option.
    ///
    /// \throw isc::BadValue if any of the template files does not exist,
    /// contains characters other than hexadecimal digits or spaces.
    /// \throw OutOfRange if any of the template files is empty or has
    /// odd number of hexadecimal digits.
    void initPacketTemplates();

    /// \brief Initializes Statistics Manager.
    ///
    /// This function initializes Statistics Manager. If there is
    /// the one initialized already it is released.
    void initializeStatsMgr();

    /// \brief Open socket to communicate with DHCP server.
    ///
    /// Method opens socket and binds it to local address. Function will
    /// use either interface name, local address or server address
    /// to create a socket, depending on what is available (specified
    /// from the command line). If socket can't be created for any
    /// reason, exception is thrown.
    /// If destination address is broadcast (for DHCPv4) or multicast
    /// (for DHCPv6) than broadcast or multicast option is set on
    /// the socket. Opened socket is registered and managed by IfaceMgr.
    ///
    /// \throw isc::BadValue if socket can't be created for given
    /// interface, local address or remote address.
    /// \throw isc::InvalidOperation if broadcast option can't be
    /// set for the v4 socket or if multicast option can't be set
    /// for the v6 socket.
    /// \throw isc::Unexpected if internal unexpected error occurred.
    /// \return socket descriptor.
    int openSocket() const;

    /// \brief Print intermediate statistics.
    ///
    /// Print brief statistics regarding number of sent packets,
    /// received packets and dropped packets so far.
    void printIntermediateStats();

    /// \brief Print rate statistics.
    ///
    /// Method print packet exchange rate statistics.
    void printRate() const;

    /// \brief Print performance statistics.
    ///
    /// Method prints performance statistics.
    /// \throws isc::InvalidOperation if Statistics Manager was
    /// not initialized.
    void printStats() const;

    /// \brief Process received DHCPv4 packet.
    ///
    /// Method performs processing of the received DHCPv4 packet,
    /// updates statistics and responds to the server if required,
    /// e.g. when OFFER packet arrives, this function will initiate
    /// REQUEST message to the server.
    ///
    /// \warning this method does not check if provided socket is
    /// valid (specifically if v4 socket for received v4 packet).
    ///
    /// \param [in] socket socket to be used.
    /// \param [in] pkt4 object representing DHCPv4 packet received.
    /// \throw isc::BadValue if unknown message type received.
    /// \throw isc::Unexpected if unexpected error occurred.
    void processReceivedPacket4(const TestControlSocket& socket,
                                const dhcp::Pkt4Ptr& pkt4);

    /// \brief Process received DHCPv6 packet.
    ///
    /// Method performs processing of the received DHCPv6 packet,
    /// updates statistics and responds to the server if required,
    /// e.g. when ADVERTISE packet arrives, this function will initiate
    /// REQUEST message to the server.
    ///
    /// \warning this method does not check if provided socket is
    /// valid (specifically if v4 socket for received v4 packet).
    ///
    /// \param [in] socket socket to be used.
    /// \param [in] pkt6 object representing DHCPv6 packet received.
    /// \throw isc::BadValue if unknown message type received.
    /// \throw isc::Unexpected if unexpected error occurred.
    void processReceivedPacket6(const TestControlSocket& socket,
                                const dhcp::Pkt6Ptr& pkt6);

    /// \brief Receive DHCPv4 or DHCPv6 packets from the server.
    ///
    /// Method receives DHCPv4 or DHCPv6 packets from the server.
    /// This function will call \ref processReceivedPacket4 or
    /// \ref processReceivedPacket6 depending if DHCPv4 or DHCPv6 packet
    /// has arrived.
    ///
    /// \warning this method does not check if provided socket is
    /// valid. Ensure that it is valid prior to calling it.
    ///
    /// \param socket socket to be used.
    /// \throw isc::BadValue if unknown message type received.
    /// \throw isc::Unexpected if unexpected error occurred.
    /// \return number of received packets.
    uint64_t receivePackets(const TestControlSocket& socket);

    /// \brief Register option factory functions for DHCPv4
    ///
    /// Method registers option factory functions for DHCPv4.
    /// These functions are called to create instances of DHCPv4
    /// options. Call \ref dhcp::Option::factory to invoke factory
    /// function for particular option. Don't use this function directly.
    /// Use \ref registerOptionFactories instead.
    void registerOptionFactories4() const;

    /// \brief Register option factory functions for DHCPv6
    ///
    /// Method registers option factory functions for DHCPv6.
    /// These functions are called to create instances of DHCPv6
    /// options. Call \ref dhcp::Option::factory to invoke factory
    /// function for particular option. Don't use this function directly.
    /// Use \ref registerOptionFactories instead.
    void registerOptionFactories6() const;

    /// \brief Register option factory functions for DHCPv4 or DHCPv6.
    ///
    /// Method registers option factory functions for DHCPv4 or DHCPv6,
    /// depending in which mode test is currently running.
    void registerOptionFactories() const;


    /// \brief Resets internal state of the object.
    ///
    /// Method resets internal state of the object. It has to be
    /// called before new test is started.
    void reset();

    /// \brief Save the first DHCPv4 sent packet of the specified type.
    ///
    /// This method saves first packet of the specified being sent
    /// to the server if user requested diagnostics flag 'T'. In
    /// such case program has to print contents of selected packets
    /// being sent to the server. It collects first packets of each
    /// type and keeps them around until test finishes. Then they
    /// are printed to the user. If packet of specified type has
    /// been already stored this function perfroms no operation.
    /// This function does not perform sanity check if packet
    /// pointer is valid. Make sure it is before calling it.
    ///
    /// \param pkt packet to be stored.
    inline void saveFirstPacket(const dhcp::Pkt4Ptr& pkt);

    /// \brief Save the first DHCPv6 sent packet of the specified type.
    ///
    /// This method saves first packet of the specified being sent
    /// to the server if user requested diagnostics flag 'T'. In
    /// such case program has to print contents of selected packets
    /// being sent to the server. It collects first packets of each
    /// type and keeps them around until test finishes. Then they
    /// are printed to the user. If packet of specified type has
    /// been already stored this function perfroms no operation.
    /// This function does not perform sanity check if packet
    /// pointer is valid. Make sure it is before calling it.
    ///
    /// \param pkt packet to be stored.
    inline void saveFirstPacket(const dhcp::Pkt6Ptr& pkt);

    /// \brief Send DHCPv4 DISCOVER message.
    ///
    /// Method creates and sends DHCPv4 DISCOVER message to the server
    /// with the following options:
    /// - MESSAGE_TYPE set to DHCPDISCOVER
    /// - PARAMETER_REQUEST_LIST with the same list of requested options
    /// as described in \ref factoryRequestList4.
    /// The transaction id and MAC address are randomly generated for
    /// the message. Range of unique MAC addresses generated depends
    /// on the number of clients specified from the command line.
    /// Copy of sent packet is stored in the stats_mgr4_ object to
    /// update statistics.
    ///
    /// \param socket socket to be used to send the message.
    /// \param preload preload mode, packets not included in statistics.
    ///
    /// \throw isc::Unexpected if failed to create new packet instance.
    /// \throw isc::BadValue if MAC address has invalid length.
    /// \throw isc::dhcp::SocketWriteError if failed to send the packet.
    void sendDiscover4(const TestControlSocket& socket,
                       const bool preload = false);

    /// \brief Send DHCPv4 DISCOVER message from template.
    ///
    /// Method sends DHCPv4 DISCOVER message from template. The
    /// template data is expected to be in binary format. Provided
    /// buffer is copied and parts of it are replaced with actual
    /// data (e.g. MAC address, transaction id etc.).
    /// Copy of sent packet is stored in the stats_mgr4_ object to
    /// update statistics.
    ///
    /// \param socket socket to be used to send the message.
    /// \param template_buf buffer holding template packet.
    /// \param preload preload mode, packets not included in statistics.
    ///
    /// \throw isc::OutOfRange if randomization offset is out of bounds.
    /// \throw isc::dhcp::SocketWriteError if failed to send the packet.
    void sendDiscover4(const TestControlSocket& socket,
                       const std::vector<uint8_t>& template_buf,
                       const bool preload = false);

    /// \brief Send number of packets to initiate new exchanges.
    ///
    /// Method initiates the new DHCP exchanges by sending number
    /// of DISCOVER (DHCPv4) or SOLICIT (DHCPv6) packets. If preload
    /// mode was requested sent packets will not be counted in
    /// the statistics. The responses from the server will be
    /// received and counted as orphans because corresponding sent
    /// packets are not included in StatsMgr for match.
    /// When preload mode is disabled and diagnostics flag 'i' is
    /// specified then function will be trying to receive late packets
    /// before new packets are sent to the server. Statistics of
    /// late received packets is updated accordingly.
    ///
    /// \todo do not count responses in preload mode as orphans.
    ///
    /// \param socket socket to be used to send packets.
    /// \param packets_num number of packets to be sent.
    /// \param preload preload mode, packets not included in statistics.
    /// \throw isc::Unexpected if thrown by packet sending method.
    /// \throw isc::InvalidOperation if thrown by packet sending method.
    /// \throw isc::OutOfRange if thrown by packet sending method.
    void sendPackets(const TestControlSocket &socket,
                     const uint64_t packets_num,
                     const bool preload = false);

    /// \brief Send number of DHCPREQUEST (renew) messages to a server.
    ///
    /// \param socket An object representing socket to be used to send packets.
    /// \param msg_num A number of messages to be sent.
    ///
    /// \return A number of messages actually sent.
    uint64_t sendMultipleRequests(const TestControlSocket& socket,
                                  const uint64_t msg_num);

    /// \brief Send number of DHCPv6 Renew or Release messages to the server.
    ///
    /// \param socket An object representing socket to be used to send packets.
    /// \param msg_type A type of the messages to be sent (DHCPV6_RENEW or
    /// DHCPV6_RELEASE).
    /// \param msg_num A number of messages to be sent.
    ///
    /// \return A number of messages actually sent.
    uint64_t sendMultipleMessages6(const TestControlSocket& socket,
                                   const uint32_t msg_type,
                                   const uint64_t msg_num);

    /// \brief Send DHCPv4 renew (DHCPREQUEST) using specified socket.
    ///
    /// \param socket An object encapsulating socket to be used to send
    /// a packet.
    ///
    /// \return true if the message has been sent, false otherwise.
    bool sendRequestFromAck(const TestControlSocket& socket);

    /// \brief Send DHCPv6 Renew or Release message using specified socket.
    ///
    /// This method will select an existing lease from the Reply packet cache
    /// If there is no lease that can be renewed or released this method will
    /// return false.
    ///
    /// \param msg_type A type of the message to be sent (DHCPV6_RENEW or
    /// DHCPV6_RELEASE).
    /// \param socket An object encapsulating socket to be used to send
    /// a packet.
    ///
    /// \return true if the message has been sent, false otherwise.
    bool sendMessageFromReply(const uint16_t msg_type,
                              const TestControlSocket& socket);

    /// \brief Send DHCPv4 REQUEST message.
    ///
    /// Method creates and sends DHCPv4 REQUEST message to the server.
    /// Copy of sent packet is stored in the stats_mgr4_ object to
    /// update statistics.
    ///
    /// \param socket socket to be used to send message.
    /// \param discover_pkt4 DISCOVER packet sent.
    /// \param offer_pkt4 OFFER packet object.
    ///
    /// \throw isc::Unexpected if unexpected error occurred.
    /// \throw isc::InvalidOperation if Statistics Manager has not been
    /// initialized.
    /// \throw isc::dhcp::SocketWriteError if failed to send the packet.
    void sendRequest4(const TestControlSocket& socket,
                      const dhcp::Pkt4Ptr& discover_pkt4,
                      const dhcp::Pkt4Ptr& offer_pkt4);

    /// \brief Send DHCPv4 REQUEST message from template.
    ///
    /// Method sends DHCPv4 REQUEST message from template.
    /// Copy of sent packet is stored in the stats_mgr4_ object to
    /// update statistics.
    ///
    /// \param socket socket to be used to send message.
    /// \param template_buf buffer holding template packet.
    /// \param discover_pkt4 DISCOVER packet sent.
    /// \param offer_pkt4 OFFER packet received.
    ///
    /// \throw isc::dhcp::SocketWriteError if failed to send the packet.
    void sendRequest4(const TestControlSocket& socket,
                      const std::vector<uint8_t>& template_buf,
                      const dhcp::Pkt4Ptr& discover_pkt4,
                      const dhcp::Pkt4Ptr& offer_pkt4);

    /// \brief Send DHCPv6 REQUEST message.
    ///
    /// Method creates and sends DHCPv6 REQUEST message to the server
    /// with the following options:
    /// - D6O_ELAPSED_TIME
    /// - D6O_CLIENTID
    /// - D6O_SERVERID
    /// Copy of sent packet is stored in the stats_mgr6_ object to
    /// update statistics.
    ///
    /// \param socket socket to be used to send message.
    /// \param advertise_pkt6 ADVERTISE packet object.
    /// \throw isc::Unexpected if unexpected error occurred.
    /// \throw isc::InvalidOperation if Statistics Manager has not been
    /// initialized.
    ///
    /// \throw isc::dhcp::SocketWriteError if failed to send the packet.
    void sendRequest6(const TestControlSocket& socket,
                      const dhcp::Pkt6Ptr& advertise_pkt6);

    /// \brief Send DHCPv6 REQUEST message from template.
    ///
    /// Method sends DHCPv6 REQUEST message from template.
    /// Copy of sent packet is stored in the stats_mgr6_ object to
    /// update statistics.
    ///
    /// \param socket socket to be used to send message.
    /// \param template_buf packet template buffer.
    /// \param advertise_pkt6 ADVERTISE packet object.
    ///
    /// \throw isc::dhcp::SocketWriteError if failed to send the packet.
    void sendRequest6(const TestControlSocket& socket,
                      const std::vector<uint8_t>& template_buf,
                      const dhcp::Pkt6Ptr& advertise_pkt6);

    /// \brief Send DHCPv6 SOLICIT message.
    ///
    /// Method creates and sends DHCPv6 SOLICIT message to the server
    /// with the following options:
    /// - D6O_ELAPSED_TIME,
    /// - D6O_RAPID_COMMIT if rapid commit is requested in command line,
    /// - D6O_CLIENTID,
    /// - D6O_ORO (Option Request Option),
    /// - D6O_IA_NA.
    /// Copy of sent packet is stored in the stats_mgr6_ object to
    /// update statistics.
    ///
    /// \param socket socket to be used to send the message.
    /// \param preload mode, packets not included in statistics.
    ///
    /// \throw isc::Unexpected if failed to create new packet instance.
    /// \throw isc::dhcp::SocketWriteError if failed to send the packet.
    void sendSolicit6(const TestControlSocket& socket,
                      const bool preload = false);

    /// \brief Send DHCPv6 SOLICIT message from template.
    ///
    /// Method sends DHCPv6 SOLICIT message from template.
    /// Copy of sent packet is stored in the stats_mgr6_ object to
    /// update statistics.
    ///
    /// \param socket socket to be used to send the message.
    /// \param template_buf packet template buffer.
    /// \param preload mode, packets not included in statistics.
    ///
    /// \throw isc::dhcp::SocketWriteError if failed to send the packet.
    void sendSolicit6(const TestControlSocket& socket,
                      const std::vector<uint8_t>& template_buf,
                      const bool preload = false);

    /// \brief Set default DHCPv4 packet parameters.
    ///
    /// This method sets default parameters on the DHCPv4 packet:
    /// - interface name,
    /// - local port = 68 (DHCP client port),
    /// - remote port = 67 (DHCP server port),
    /// - server's address,
    /// - GIADDR = local address where socket is bound to,
    /// - hops = 1 (pretending that we are a relay)
    ///
    /// \param socket socket used to send the packet.
    /// \param pkt reference to packet to be configured.
    void setDefaults4(const TestControlSocket& socket,
                      const dhcp::Pkt4Ptr& pkt);

    /// \brief Set default DHCPv6 packet parameters.
    ///
    /// This method sets default parameters on the DHCPv6 packet:
    /// - interface name,
    /// - interface index,
    /// - local port,
    /// - remote port,
    /// - local address,
    /// - remote address (server).
    ///
    /// \param socket socket used to send the packet.
    /// \param pkt reference to packet to be configured.
    void setDefaults6(const TestControlSocket& socket,
                      const dhcp::Pkt6Ptr& pkt);

    /// \brief Find if diagnostic flag has been set.
    ///
    /// \param diag diagnostic flag (a,e,i,s,r,t,T).
    /// \return true if diagnostics flag has been set.
    bool testDiags(const char diag) const;

protected:

    /// \brief Increments counter of late sent messages if required.
    ///
    /// This function checks if the message or set of messages of a given type,
    /// were sent later than their due time. If they were sent late, it is
    /// an indication that the perfdhcp doesn't catch up with the desired rate
    /// for sending messages.
    ///
    /// \param rate_control An object tracking due times for a particular
    /// type of messages.
    void checkLateMessages(RateControl& rate_control);

    /// \brief Copies IA_NA or IA_PD option from one packet to another.
    ///
    /// This function checks the lease-type specified in the command line
    /// with option -e<lease-type>. If 'address-only' value has been specified
    /// this function expects that IA_NA option is present in the packet
    /// encapsulated by pkt_from object. If 'prefix-only' value has been
    /// specified, this function expects that IA_PD option is present in the
    /// packet encapsulated by pkt_to object.
    ///
    /// \param [in] pkt_from A packet from which options should be copied.
    /// \param [out] pkt_to A packet to which options should be copied.
    ///
    /// \throw isc::perfdhcp::OptionNotFound if a required option is not
    /// found in the packet from which options should be copied.
    /// \throw isc::BadValue if any of the specified pointers to packets
    /// is NULL.
    void copyIaOptions(const dhcp::Pkt6Ptr& pkt_from, dhcp::Pkt6Ptr& pkt_to);

    /// \brief Convert binary value to hex string.
    ///
    /// \todo Consider moving this function to src/lib/util.
    ///
    /// \param b byte to convert.
    /// \return hex string.
    std::string byte2Hex(const uint8_t b) const;

    /// \brief Calculate elapsed time between two packets.
    ///
    /// This function calculates the time elapsed between two packets. If
    /// the timestamp of the pkt2 is greater than timestamp of the pkt1,
    /// the positive value is returned. If the pkt2 timestamp is equal or
    /// less than pkt1 timestamp, 0 is returned.
    ///
    /// \tparam T Pkt4Ptr or Pkt6Ptr class.
    /// \param pkt1 first packet.
    /// \param pkt2 second packet.
    /// \throw InvalidOperation if packet timestamps are invalid.
    /// \return elapsed time in milliseconds between pkt1 and pkt2.
    template<class T>
    uint32_t getElapsedTime(const T& pkt1, const T& pkt2);

    /// \brief Return elapsed time offset in a packet.
    ///
    /// \return elapsed time offset in packet.
    int getElapsedTimeOffset() const;

    /// \brief Return randomization offset in a packet.
    ///
    /// \return randomization offset in packet.
    int getRandomOffset(const int arg_idx) const;

    /// \brief Return requested ip offset in a packet.
    ///
    /// \return randomization offset in a packet.
    int getRequestedIpOffset() const;

    /// \brief Return server id offset in a packet.
    ///
    /// \return server id offset in packet.
    int getServerIdOffset() const;

    /// \brief Return transaction id offset in a packet.
    ///
    /// \param arg_idx command line argument index to be used.
    /// If multiple -X parameters specified it points to the
    /// one to be used.
    /// \return transaction id offset in packet.
    int getTransactionIdOffset(const int arg_idx) const;

    /// \brief Get number of received packets.
    ///
    /// Get the number of received packets from the Statistics Manager.
    /// Function may throw if Statistics Manager object is not
    /// initialized.
    ///
    /// \note The method parameter is non-const to suppress the cppcheck
    /// warning about the object being passed by value. However, passing
    /// an enum by reference doesn't make much sense. At the same time,
    /// removing the constness should be pretty safe for this function.
    ///
    /// \param xchg_type packet exchange type.
    /// \return number of received packets.
    uint64_t getRcvdPacketsNum(ExchangeType xchg_type) const;

    /// \brief Get number of sent packets.
    ///
    /// Get the number of sent packets from the Statistics Manager.
    /// Function may throw if Statistics Manager object is not
    /// initialized.
    ///
    /// \note The method parameter is non-const to suppress the cppcheck
    /// warning about the object being passed by value. However, passing
    /// an enum by reference doesn't make much sense. At the same time,
    /// removing the constness should be pretty safe for this function.
    ///
    /// \param xchg_type packet exchange type.
    /// \return number of sent packets.
    uint64_t getSentPacketsNum(ExchangeType xchg_type) const;

    /// \brief Handle child signal.
    ///
    /// Function handles child signal by waiting for
    /// the process to complete.
    ///
    /// \param sig signal (ignored)
    static void handleChild(int sig);

    /// \brief Handle interrupt signal.
    ///
    /// Function sets flag indicating that program has been
    /// interrupted.
    ///
    /// \param sig signal (ignored)
    static void handleInterrupt(int sig);

    /// \brief Print main diagnostics data.
    ///
    /// Method prints main diagnostics data.
    void printDiagnostics() const;

    /// \brief Print template information
    ///
    /// \param packet_type packet type.
    void printTemplate(const uint8_t packet_type) const;

    /// \brief Print templates information.
    ///
    /// Method prints information about data offsets
    /// in packet templates and their contents.
    void printTemplates() const;

    /// \brief Read DHCP message template from file.
    ///
    /// Method reads DHCP message template from file and
    /// converts it to binary format. Read data is appended
    /// to template_buffers_ vector.
    ///
    /// \param file_name name of the packet template file.
    /// \throw isc::OutOfRange if file is empty or has odd number
    /// of hexadecimal digits.
    /// \throw isc::BadValue if file contains characters other than
    /// spaces or hexadecimal digits.
    void readPacketTemplate(const std::string& file_name);

    /// \brief Run wrapped command.
    ///
    /// \param do_stop execute wrapped command with "stop" argument.
    void runWrapped(bool do_stop = false) const;

    /// \brief Convert vector in hexadecimal string.
    ///
    /// \todo Consider moving this function to src/lib/util.
    ///
    /// \param vec vector to be converted.
    /// \param separator separator.
    std::string vector2Hex(const std::vector<uint8_t>& vec,
                           const std::string& separator = "") const;

    /// \brief A rate control class for Discover and Solicit messages.
    RateControl basic_rate_control_;
    /// \brief A rate control class for Renew messages.
    RateControl renew_rate_control_;
    /// \brief A rate control class for Release messages.
    RateControl release_rate_control_;

    boost::posix_time::ptime last_report_; ///< Last intermediate report time.

    StatsMgr4Ptr stats_mgr4_;  ///< Statistics Manager 4.
    StatsMgr6Ptr stats_mgr6_;  ///< Statistics Manager 6.

    PacketStorage<dhcp::Pkt4> ack_storage_; ///< A storage for DHCPACK messages.
    PacketStorage<dhcp::Pkt6> reply_storage_; ///< A storage for reply messages.

    NumberGeneratorPtr transid_gen_; ///< Transaction id generator.
    NumberGeneratorPtr macaddr_gen_; ///< Numbers generator for MAC address.

    /// Buffer holding server id received in first packet
    dhcp::OptionBuffer first_packet_serverid_;

    /// Packet template buffers.
    TemplateBufferCollection template_buffers_;

    /// First packets send. They are used at the end of the test
    /// to print packet templates when diagnostics flag T is specified.
    std::map<uint8_t, dhcp::Pkt4Ptr> template_packets_v4_;
    std::map<uint8_t, dhcp::Pkt6Ptr> template_packets_v6_;

    static bool interrupted_;  ///< Is program interrupted.
};

} // namespace perfdhcp
} // namespace isc

#endif // TEST_CONTROL_H
