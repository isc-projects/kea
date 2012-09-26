// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __TEST_CONTROL_H
#define __TEST_CONTROL_H

#include <string>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <dhcp/iface_mgr.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

#include "stats_mgr.h"

namespace isc {
namespace perfdhcp {

/// \brief Test Control class.
///
/// This class is responsible for executing DHCP performance
/// test end to end.
///
/// Option factory functions are registered using
/// \ref dhcp::LibDHCP::OptionFactoryRegister. Registered factory functions
/// provide a way to create options of the same type in the same way.
///  When new option instance is needed the corresponding factory
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

    /// Default transaction id offset.
    static const size_t DHCPV4_TRANSID_OFFSET = 4;
    /// Default offset of MAC's last octet.
    static const size_t DHCPV4_RANDOMIZATION_OFFSET = 35;
    /// Default elapsed time offset.
    static const size_t DHCPV4_ELAPSED_TIME_OFFSET = 8;
    /// Default server id offset.
    static const size_t DHCPV4_SERVERID_OFFSET = 54;
    /// Default requested ip offset.
    static const size_t DHCPV4_REQUESTED_IP_OFFSET = 240;
    /// Default DHCPV6 transaction id offset.
    static const size_t DHCPV6_TRANSID_OFFSET = 1;
    /// Default DHCPV6 randomization offset (last octet of DUID)
    static const size_t DHCPV6_RANDOMIZATION_OFFSET = 21;
    /// Default DHCPV6 elapsed time offset.
    static const size_t DHCPV6_ELAPSED_TIME_OFFSET = 84;
    /// Default DHCPV6 server id offset.
    static const size_t DHCPV6_SERVERID_OFFSET = 22;
    /// Default DHCPV6 IA_NA offset.
    static const size_t DHCPV6_IA_NA_OFFSET = 40;

    /// Statistics Manager for DHCPv4.
    typedef StatsMgr<dhcp::Pkt4> StatsMgr4;
    /// Pointer to Statistics Manager for DHCPv4;
    typedef boost::shared_ptr<StatsMgr4> StatsMgr4Ptr;
    /// Statictics Manager for DHCPv6.
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
    struct TestControlSocket : public dhcp::IfaceMgr::SocketInfo {
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

        /// \brief Destriuctor of the socket wrapper class.
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
    /// (e.g. sequencial or based on random function).
    class NumberGenerator {
    public:
        /// \brief Generate number.
        ///
        /// \return Generate number.
        virtual uint32_t generate() = 0;
    };

    /// The default generator pointer.
    typedef boost::shared_ptr<NumberGenerator> NumberGeneratorPtr;

    /// \brief Sequencial numbers generatorc class.
    class SequencialGenerator : public NumberGenerator {
    public:
        /// \brief Constructor.
        ///
        /// \param range maximum number generated. If 0 is given then
        /// range defaults to maximym uint32_t value.
        SequencialGenerator(uint32_t range = 0xFFFFFFFF) :
            NumberGenerator(),
            num_(0),
            range_(range) {
            if (range_ == 0) {
                range_ = 0xFFFFFFFF;
            }
        }

        /// \brief Generate number sequencialy.
        ///
        /// \return generated number.
        virtual uint32_t generate() {
            uint32_t num = num_;
            num_ = (num_ + 1) % range_;
            return (num);
        }
    private:
        uint32_t num_;   ///< Current number.
        uint32_t range_; ///< Maximum number generated.
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
    /// be parsed prior to running this function. Othewise function will
    /// throw exception.
    ///
    /// \throw isc::InvalidOperation if command line options are not parsed.
    /// \throw isc::Unexpected if internal Test Controler error occured.
    void run();

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

    /// \brief Check if test exit condtitions fulfilled.
    ///
    /// Method checks if the test exit conditions are fulfiled.
    /// Exit conditions are checked periodically from the
    /// main loop. Program should break the main loop when
    /// this method returns true. It is calling function
    /// responsibility to break main loop gracefully and
    /// cleanup after test execution.
    ///
    /// \return true if any of the exit conditions is fulfiled.
    bool checkExitConditions() const;

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
    /// This factory function creayes DHCPv4 PARAMETER_REQUEST_LIST option
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

    /// \brief Returns number of exchanges to be started.
    ///
    /// Method returns number of new exchanges to be started as soon
    /// as possible to satisfy expected rate. Calculation used here
    /// is based on current time, due time calculated with
    /// \ref updateSendDue function and expected rate.
    ///
    /// \return number of exchanges to be started immediately.
    uint64_t getNextExchangesNum() const;

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
    /// \throw isc::BadValue if any of the template files does not exist
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
    /// set for the v4 socket or if multicast option cat't be set
    /// for the v6 socket.
    /// \throw isc::Unexpected if interal unexpected error occured.
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
    /// \throw isc::Unexpected if unexpected error occured.
    void processReceivedPacket4(const TestControlSocket& socket,
                                const dhcp::Pkt4Ptr& pkt4);

    /// \brief Process received DHCPv6 packet.
    ///
    /// Method performs processing of the received DHCPv6 packet,
    /// updates statistics and responsds to the server if required,
    /// e.g. when ADVERTISE packet arrives, this function will initiate
    /// REQUEST message to the server.
    ///
    /// \warning this method does not check if provided socket is
    /// valid (specifically if v4 socket for received v4 packet).
    ///
    /// \param [in] socket socket to be used.
    /// \param [in] pkt6 object representing DHCPv6 packet received.
    /// \throw isc::BadValue if unknown message type received.
    /// \throw isc::Unexpected if unexpected error occured.
    void processReceivedPacket6(const TestControlSocket& socket,
                                const dhcp::Pkt6Ptr& pkt6);

    /// \brief Receive DHCPv4 or DHCPv6 packets from the server.
    ///
    /// Method receives DHCPv4 or DHCPv6 packets from the server.
    /// This function will call \ref receivePacket4 or
    /// \ref receivePacket6 depending if DHCPv4 or DHCPv6 packet
    /// has arrived.
    ///
    /// \warning this method does not check if provided socket is
    /// valid. Ensure that it is valid prior to calling it.
    ///
    /// \param socket socket to be used.
    /// \throw isc::BadValue if unknown message type received.
    /// \throw isc::Unexpected if unexpected error occured.
    void receivePackets(const TestControlSocket& socket);

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
    /// depending in whch mode test is currently running.
    void registerOptionFactories() const;


    /// \brief Resets internal state of the object.
    ///
    /// Method resets internal state of the object. It has to be
    /// called before new test is started.
    void reset();

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
    /// template data is exepcted to be in binary format. Provided
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
    /// \throw isc::Unexpected if unexpected error occured.
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
    /// \throw isc::Unexpected if unexpected error occured.
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

    /// \brief Update due time to initiate next chunk of exchanges.
    ///
    /// Method updates due time to initiate next chunk of exchanges.
    /// Function takes current time, last sent packet's time and
    /// expected rate in its calculations.
    void updateSendDue();

private:

    /// \brief Convert binary value to hex string.
    ///
    /// \todo Consider moving this function to src/lib/util.
    ///
    /// \param b byte to convert.
    /// \return hex string.
    std::string byte2Hex(const uint8_t b) const;

    /// \brief Calculate elapsed time between two packets.
    ///
    /// \param T Pkt4Ptr or Pkt6Ptr class.
    /// \param pkt1 first packet.
    /// \param pkt2 second packet.
    /// \throw InvalidOperation if packet timestamps are invalid.
    /// \return elapsed time in milliseconds between pkt1 and pkt2.
    template<class T>
    uint32_t getElapsedTime(const T& pkt1, const T& pkt2);

    /// \brief Get number of received packets.
    ///
    /// Get the number of received packets from the Statistics Manager.
    /// Function may throw if Statistics Manager object is not
    /// initialized.
    /// \param xchg_type packet exchange type.
    /// \return number of received packets.
    uint64_t getRcvdPacketsNum(const ExchangeType xchg_type) const;

    /// \brief Get number of sent packets.
    ///
    /// Get the number of sent packets from the Statistics Manager.
    /// Function may throw if Statistics Manager object is not
    /// initialized.
    /// \param xchg_type packet exchange type.
    /// \return number of sent packets.
    uint64_t getSentPacketsNum(const ExchangeType xchg_type) const;

    /// \brief Handle interrupt signal.
    ///
    /// Function sets flag indicating that program has been
    /// interupted.
    ///
    /// \param sig signal (ignored)
    static void handleInterrupt(int sig);

    /// \brief Print main diagnostics data.
    ///
    /// Method prints main diagnostics data.
    void printDiagnostics() const;

    /// \brief Read DHCP message template from file.
    ///
    /// Method reads DHCP message template from file and
    /// converts it to binary format. Read data is appended
    /// to template_buffers_ vector.
    void readPacketTemplate(const std::string& file_name);

    /// \brief Convert vector in hexadecimal string.
    ///
    /// \todo Consider moving this function to src/lib/util.
    ///
    /// \param vec vector to be converted.
    /// \param separator separator.
    std::string vector2Hex(const std::vector<uint8_t>& vec,
                           const std::string& separator = "") const;

    boost::posix_time::ptime send_due_;    ///< Due time to initiate next chunk
                                           ///< of exchanges.
    boost::posix_time::ptime last_sent_;   ///< Indicates when the last exchange
                                           /// was initiated.

    boost::posix_time::ptime last_report_; ///< Last intermediate report time.

    StatsMgr4Ptr stats_mgr4_;  ///< Statistics Manager 4.
    StatsMgr6Ptr stats_mgr6_;  ///< Statistics Manager 6.

    NumberGeneratorPtr transid_gen_; ///< Transaction id generator.
    NumberGeneratorPtr macaddr_gen_; ///< Numbers generator for MAC address.

    /// Buffer holiding server id received in first packet
    dhcp::OptionBuffer first_packet_serverid_;

    /// Packet template buffers.
    TemplateBufferCollection template_buffers_;

    static bool interrupted_;  ///< Is program interrupted.
};

} // namespace perfdhcp
} // namespace isc

#endif // __COMMAND_OPTIONS_H
