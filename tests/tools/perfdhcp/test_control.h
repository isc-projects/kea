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
/// \ref LibDHCP::OptionFactoryRegister. Registered factory functions
/// provide a way to create options of the same type in the same way.
///  When new option instance is needed the corresponding factory
/// function is called to create it. This is done by calling
/// \ref Option::factory with DHCP message type specified as one of
///  parameters. Some of the parameters passed to factory function
/// may be ignored (e.g. option buffer).
class TestControl : public boost::noncopyable {
public:

    // Statistics Manager for DHCPv4.
    typedef StatsMgr<dhcp::Pkt4> StatsMgr4;
    // Pointer to Statistics Manager for DHCPv4;
    typedef boost::shared_ptr<StatsMgr4> StatsMgr4Ptr;
    // Statictics Manager for DHCPv6.
    typedef StatsMgr<dhcp::Pkt6> StatsMgr6;
    // Pointer to Statistics Manager for DHCPv6.
    typedef boost::shared_ptr<StatsMgr6> StatsMgr6Ptr;
    // Packet exchange type.
    typedef StatsMgr<>::ExchangeType ExchangeType;
    // Packet template buffer.
    typedef std::vector<uint8_t> TemplateBuffer;
    //Packet template buffers list.
    typedef std::list<TemplateBuffer> TemplateBufferList;

    /// \brief Socket wrapper class.
    ///
    /// This is wrapper class that holds descriptor of the socket
    /// used to run DHCP test. All sockets created with \ref IfaceMgr
    /// are closed in the destructor. This ensures that socket is
    /// closed when the function that created the socket ends
    /// (normally or when exception occurs).
    class TestControlSocket {
    public:

        /// \brief Constructor of socket wrapper class.
        ///
        /// This constructor uses provided socket descriptor to
        /// find the name of the interface where socket has been
        /// bound to.
        ///
        /// \param socket socket descriptor.
        /// \throw isc::BadValue if interface for specified
        /// socket descriptor does not exist.
        TestControlSocket(const int socket);

        /// \brief Destriuctor of the socket wrapper class.
        ///
        /// Destructor closes all open sockets on all interfaces.
        /// TODO: close only the socket being wrapped by this class.
        ~TestControlSocket();

        /// \brief Return name of the interface where socket is bound to.
        ///
        /// \return name of the interface where socket is bound to.
        const std::string& getIface() const { return(iface_); }

        /// \brief Return interface index where socket is bound to.
        ///
        /// \return index fo the interface where sockert is bound to.
        int getIfIndex() const { return(ifindex_); }

        /// \brief Return address where socket is bound to.
        ///
        /// \return address where socket is bound to.
        const asiolink::IOAddress& getAddress() const { return(addr_); }

    private:
        /// \brief Private default constructor.
        ///
        /// Default constructor is private to make sure that valid
        /// socket descriptor is passed to create object.
        TestControlSocket();

        /// \brief Initialize socket data.
        ///
        /// This method initializes members of the class that Interface
        /// Manager holds: interface name, local address.
        ///
        /// \throw isc::BadValue if interface for specified socket
        /// descriptor does not exist.
        void initSocketData();

        int socket_;               ///< Socket descirptor.
        std::string iface_;        ///< Name of the interface.
        int ifindex_;              ///< Index of the interface.
        asiolink::IOAddress addr_; ///< Address bound.
    };

    /// \brief Default transaction id generator class.
    ///
    /// This is default transaction id generator class. The member
    /// function is used to generate unique transaction id value.
    /// Other generator classes should derive from this one to
    /// override the standard generation algorithm (e.g. unit tests
    /// override this class wih algorithm that produces more predictable
    /// transaction id values).
    class TransidGenerator {
    public:
        /// \brief generate transaction id.
        ///
        /// \return generated transazction id value.
        virtual uint32_t generate() {
            return static_cast<uint32_t>(random() % 0x00FFFFFF);
        }
    };

    typedef boost::shared_ptr<TransidGenerator> TransidGeneratorPtr;

    /// \brief Length of the Ethernet HW address (MAC) in bytes.
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
    void setTransidGenerator(TransidGeneratorPtr& generator) {
        transid_gen_.reset();
        transid_gen_ = generator;
    }

protected:

    // We would really like these methods and members to be private but
    // they have to be accessible for unit-testing. Another, possibly better,
    // solution is to make this class friend of test class but this is not
    // what's followed in other classes.

    /// \brief Default constructor.
    ///
    /// Default constructor is protected as the object can be created
    /// only via \ref instance method.
    TestControl();

    /// \brief Check if test exit condtitions fulfiled.
    ///
    /// Method checks if test exit conditions are fulfiled.
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
    /// \param u universe (V6 or V4).
    /// \param type option-type.
    /// \param buf option-buffer.
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
    /// \param type option-type.
    /// \param buf option-buffer.
    /// \return instance o the option.
    static dhcp::OptionPtr factoryGeneric(dhcp::Option::Universe u,
                                          uint16_t type,
                                          const dhcp::OptionBuffer& buf);

    /// \brief Factory function to create IA_NA option.
    ///
    /// This factory function creates DHCPv6 IA_NA option instance.
    /// \TODO: add support for IA Address options.
    /// \param u universe (V6 or V4).
    /// \param type option-type.
    /// \param buf option-buffer.
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
    /// \param u universe (V6 or V4).
    /// \param type option-type.
    /// \param buf option-buffer (ignored and should be empty).
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
    /// \param u universe (V6 or V4).
    /// \param type option-type.
    /// \param buf option-buffer (ignored and should be empty).
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
    /// \param u universe (V6 or V4).
    /// \param type option-type.
    /// \param buf option-buffer (ignored and should be empty).
    /// \return instance o the generic option.
     static dhcp::OptionPtr factoryRequestList4(dhcp::Option::Universe u,
                                               uint16_t type,
                                               const dhcp::OptionBuffer& buf);

    /// \brief Generate DUID.
    ///
    /// Method generates unique DUID. The number of DUIDs it can generate
    /// depends on the number of simulated clinets, which is specified
    /// from the command line. It uses \ref CommandOptions object to retrieve
    /// number of clinets. Since the last six octets of DUID are constructed
    /// from the MAC address, this function uses \ref generateMacAddress
    /// internally to randomize the DUID.
    ///
    /// \throw isc::BadValue if \ref generateMacAddress throws.
    /// \return vector representing DUID.
    std::vector<uint8_t> generateDuid() const;

    /// \brief Generate MAC address.
    ///
    /// This method generates MAC address. The number of unique
    /// MAC addresses it can generate is determined by the number
    /// simulated DHCP clients specified from command line. It uses
    /// \ref CommandOptions object to retrieve number of clients.
    /// Based on this the random value is generated and added to
    /// the MAC address prefix (default MAC address).
    ///
    /// \throw isc::BadValue if MAC address prefix (default or specified
    /// from the command line) has invalid size (expected 6 octets).
    /// \return generated MAC address.
    std::vector<uint8_t> generateMacAddress() const;

    /// \brief generate transaction id.
    ///
    /// \return generated transaction id.
    uint32_t generateTransid() {
        return(transid_gen_->generate());
    }

    /// \brief Returns number of exchanges to be started.
    ///
    /// Method returns number of new exchanges to be started as soon
    /// as possible to satisfy expected rate. Calculation used here
    /// is based on current time, due time calculated with
    /// \ref updateSendTime function and expected rate.
    ///
    /// \return number of exchanges to be started immediatelly.
    uint64_t getNextExchangesNum() const;

    void initPacketTemplates();

    /// \brief Initializes Statistics Manager.
    ///
    /// This function initializes Statistics Manager. If there is
    /// the one initialized already it is released.
    void initializeStatsMgr();

    /// \brief Open socket to communicate with DHCP server.
    ///
    /// Method opens socket and binds it to local address. Function will
    /// can use either interface name, local address or server address
    /// to create a socket, depending on what is available (specified
    /// from the command line). If socket can't be created for any
    /// reason, exception is thrown.
    /// If destination address is broadcast (for DHCPv4) or multicast
    /// (for DHCPv6) than broadcast or multicast option is set on
    /// the socket.
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

    /// \brief Receive DHCPv4 packet.
    ///
    /// Method performs reception of the DHCPv4 packet, updates
    /// statistics and responsds to the server if required, e.g.
    /// when OFFER packet arrives, this function will initiate
    /// REQUEST message to the server.
    ///
    /// \param socket socket to be used.
    /// \param pkt4 object representing DHCPv4 packet received.
    /// \throw isc::BadValue if unknown message type received.
    /// \throw isc::Unexpected if unexpected error occured.
    void receivePacket4(const TestControlSocket& socket,
                        const dhcp::Pkt4Ptr& pkt4);

    /// \brief Receive DHCPv6 packet.
    ///
    /// Method performs reception of the DHCPv6 packet, updates
    /// statistics and responsds to the server if required, e.g.
    /// when ADVERTISE packet arrives, this function will initiate
    /// REQUEST message to the server.
    ///
    /// \param socket socket to be used.
    /// \param pkt6 object representing DHCPv6 packet received.
    /// \throw isc::BadValue if unknown message type received.
    /// \throw isc::Unexpected if unexpected error occured.
    void receivePacket6(const TestControlSocket& socket,
                        const dhcp::Pkt6Ptr& pkt6);

    /// \brief Receive DHCPv4 or DHCPv6 packets from the server.
    ///
    /// Method receives DHCPv4 or DHCPv6 packets from the server.
    /// This function will call \ref receivePacket4 or
    /// \ref receivePacket6 depending if DHCPv4 or DHCPv6 packet
    /// has arrived.
    ///
    /// \param socket socket to be used.
    /// \throw::BadValue if unknown message type received.
    /// \throw::Unexpected if unexpected error occured.
    void receivePackets(const TestControlSocket& socket);

    /// \brief Register option factory functions for DHCPv4
    ///
    /// Method registers option factory functions for DHCPv4.
    /// These functions are called to create instances of DHCPv4
    /// options. Call \ref Option::factory to invoke factory
    /// function for particular option. Don't use this function directly.
    /// Use \ref registerOptionFactories instead.
    void registerOptionFactories4() const;

    /// \brief Register option factory functions for DHCPv6
    ///
    /// Method registers option factory functions for DHCPv6.
    /// These functions are called to create instances of DHCPv6
    /// options. Call \ref Option::factory to invoke factory
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
    /// as described in \ref factoryRequestList.
    /// The transaction id and MAC address are randomly generated for
    /// the message. Range of unique MAC addresses generated depends
    /// on the number of clients specified from the command line.
    ///
    /// \param socket socket to be used to send the message.
    /// \param preload preload mode, packets not included in statistics.
    /// \throw isc::Unexpected if failed to create new packet instance.
    /// \throw isc::BadValue if MAC address has invalid length.
    void sendDiscover4(const TestControlSocket& socket,
                       const bool preload = false);

    /// \brief Send DHCPv4 REQUEST message.
    ///
    /// Method creates and sends DHCPv4 REQUEST message to the server.
    ///
    /// \param socket socket to be used to send message.
    /// \param offer_pkt4 OFFER packet object.
    /// \throw isc::Unexpected if unexpected error occured.
    /// \throw isc::InvalidOperation if Statistics Manager has not been
    /// initialized.
    void sendRequest4(const TestControlSocket& socket,
                      const dhcp::Pkt4Ptr& offer_pkt4);

    /// \brief Send DHCPv6 REQUEST message.
    ///
    /// Method creates and sends DHCPv6 REQUEST message to the server
    /// with the following options:
    /// - D6O_ELAPSED_TIME
    /// - D6O_CLIENTID
    /// - D6O_SERVERID
    /// The elapsed time is calculated based on the duration between
    /// sending a SOLICIT and receiving the ADVERTISE packet prior.
    /// For this reason both solicit and advertise packet objects have
    /// to be passed when calling this function.
    ///
    /// \param socket socket to be used to send message.
    /// \param solicit_pkt6 SOLICIT packet object.
    /// \param advertise_pkt6 ADVERTISE packet object.
    /// \throw isc::Unexpected if unexpected error occured.
    /// \throw isc::InvalidOperation if Statistics Manager has not been
    /// initialized.
    void sendRequest6(const TestControlSocket& socket,
                      const dhcp::Pkt6Ptr& solicit_pkt6,
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
    ///
    /// \param socket socket to be used to send the message.
    /// \param preload mode, packets not included in statistics.
    /// \throw isc::Unexpected if failed to create new packet instance.
    void sendSolicit6(const TestControlSocket& socket,
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

    /// \brief Update due time to initiate next chunk of exchanges.
    ///
    /// Method updates due time to initiate next chunk of exchanges.
    /// Function takes current time, last sent packet's time and
    /// expected rate in its calculations.
    void updateSendDue();

private:

    /// \brief Generate transaction id using random function.
    ///
    /// \return generated transaction id value.
    static uint32_t generateTransidRandom();

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

    boost::posix_time::ptime send_due_;    ///< Due time to initiate next chunk
                                           ///< of exchanges.
    boost::posix_time::ptime last_sent_;   ///< Indicates when the last exchange
                                           /// was initiated.

    boost::posix_time::ptime last_report_; ///< Last intermediate report time.

    StatsMgr4Ptr stats_mgr4_;  ///< Statistics Manager 4.
    StatsMgr6Ptr stats_mgr6_;  ///< Statistics Manager 6.

    TransidGeneratorPtr transid_gen_; ///< Transaction id generator.

    /// Buffer holiding server id received in first packet
    dhcp::OptionBuffer first_packet_serverid_; 

    /// Packet template buffers.
    TemplateBufferList template_buffers_;

    uint64_t sent_packets_0_;
    uint64_t sent_packets_1_;
};

} // namespace perfdhcp
} // namespace isc

#endif // __COMMAND_OPTIONS_H
