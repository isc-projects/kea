// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/asio_wrapper.h>
#include <ha_test.h>
#include <ha_config.h>
#include <ha_service.h>
#include <ha_service_states.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <dhcp/classify.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/subnet_id.h>
#include <hooks/parking_lots.h>
#include <http/date_time.h>
#include <http/http_types.h>
#include <http/listener.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <http/response_creator_factory.h>
#include <http/response_json.h>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;
using namespace isc::ha::test;
using namespace isc::hooks;
using namespace isc::http;

namespace {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Request Timeout used in most of the tests (ms).
const long REQUEST_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in most of the tests (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Generates IPv4 leases to be used by the tests.
///
/// @param [out] leases reference to the container where leases are stored.
void generateTestLeases(std::vector<Lease4Ptr>& leases) {
    for (uint8_t i = 1; i <= 10; ++i) {
        uint32_t lease_address = 0xC0000201 + 256 * i;
        std::vector<uint8_t> hwaddr(6, i);
        Lease4Ptr lease(new Lease4(IOAddress(lease_address),
                                   HWAddrPtr(new HWAddr(hwaddr, HTYPE_ETHER)),
                                   ClientIdPtr(),
                                   60, 30, 40,
                                   static_cast<time_t>(1000 + i),
                                   SubnetID(i)));
        leases.push_back(lease);
    }
}

/// @brief Generates IPv6 leases to be used by the tests.
///
/// @param [out] leases reference to the container where leases are stored.
void generateTestLeases(std::vector<Lease6Ptr>& leases) {
    std::vector<uint8_t> address_bytes = IOAddress("2001:db8:1::1").toBytes();
    for (uint8_t i = 1; i <= 10; ++i) {
        DuidPtr duid(new DUID(std::vector<uint8_t>(10, i)));
        address_bytes[6] += i;
        Lease6Ptr lease(new Lease6(Lease::TYPE_NA,
                                   IOAddress::fromBytes(AF_INET6, &address_bytes[0]),
                                   duid, 1, 50, 60, 30, 40, SubnetID(i)));
        leases.push_back(lease);
    }
}

/// @brief Returns generated leases in JSON format.
///
/// @tparam LeasesVec vector of IPv4 or IPv6 lease pointers.
/// @param leases reference to the container holding leases to be
/// converted to JSON format.
template<typename LeasesVec>
ConstElementPtr getLeasesAsJson(const LeasesVec& leases) {
    ElementPtr leases_json = Element::createList();
    for (auto l = leases.begin(); l != leases.end(); ++l) {
        leases_json->add((*l)->toElement());
    }
    return (leases_json);
}

/// @brief Derivation of the @c HAService which provides access to
/// protected methods and members.
class TestHAService : public HAService {
public:

    /// @brief Constructor.
    ///
    /// @param io_service Pointer to the IO service used by the DHCP server.
    /// @param network_state Objec holding state of the DHCP service
    /// (enabled/disabled).
    /// @param config Parsed HA hook library configuration.
    /// @param server_type Server type, i.e. DHCPv4 or DHCPv6 server.
    TestHAService(const IOServicePtr& io_service,
                  const NetworkStatePtr& network_state,
                  const HAConfigPtr& config,
                  const HAServerType& server_type = HAServerType::DHCPv4)
        : HAService(io_service, network_state, config, server_type) {
    }

    /// @brief Test version of the @c HAService::runModel.
    ///
    /// The original implementation of this method returns control when
    /// @c NOP_EVT is found. This implementation runs a
    /// single handler to allow the tests to verify if the state machine
    /// transitions to an expected state before it is run again.
    virtual void runModel(unsigned int event) {
        try {
            postNextEvent(event);
            getState(getCurrState())->run();

        } catch (const std::exception& ex) {
            abortModel(ex.what());
        }
    }

    /// @brief Schedules asynchronous "dhcp-disable" command to the specified
    /// server.
    ///
    /// This variant of the method uses default HTTP client for communication.
    ///
    /// @param server_name name of the server to which the command should be
    /// sent.
    /// @param max_period maximum number of seconds for which the DHCP service
    /// should be disabled.
    /// @param post_request_action pointer to the function to be executed when
    /// the request is completed.
    void asyncDisable(const std::string& server_name,
                      const unsigned int max_period,
                      const PostRequestCallback& post_request_action) {
        HAService::asyncDisable(client_, server_name, max_period,
                                post_request_action);
    }

    /// @brief Schedules asynchronous "dhcp-enable" command to the specified
    /// server.
    ///
    /// This variant of the method uses default HTTP client for communication.
    ///
    /// @param server_name name of the server to which the command should be
    /// sent.
    /// @param post_request_action pointer to the function to be executed when
    /// the request is completed.
    void asyncEnable(const std::string& server_name,
                     const PostRequestCallback& post_request_action) {
        HAService::asyncEnable(client_, server_name, post_request_action);
    }

    using HAService::asyncSendHeartbeat;
    using HAService::asyncSyncLeases;
    using HAService::postNextEvent;
    using HAService::transition;
    using HAService::verboseTransition;
    using HAService::shouldSendLeaseUpdates;
    using HAService::network_state_;
    using HAService::config_;
    using HAService::communication_state_;
    using HAService::query_filter_;
    using HAService::pending_requests_;
};

/// @brief Pointer to the @c TestHAService.
typedef boost::shared_ptr<TestHAService> TestHAServicePtr;

/// @brief Test HTTP response creator.
///
/// It records received requests and allows the tests to retrieve them
/// to verify that they include expected values.
class TestHttpResponseCreator : public HttpResponseCreator {
public:

    /// @brief Constructor.
    TestHttpResponseCreator() :
        requests_(), control_result_(CONTROL_RESULT_SUCCESS),
        arguments_(), per_request_control_result_(),
        per_request_arguments_() {
    }

    /// @brief Removes all received requests.
    void clearReceivedRequests() {
        requests_.clear();
    }

    /// @brief Returns a vector of received requests.
    std::vector<ConstPostHttpRequestJsonPtr> getReceivedRequests() {
        return (requests_);
    }

    /// @brief Finds a received request which includes two strings.
    ///
    /// @param str1 First string which must be included in the request.
    /// @param str2 Second string which must be included in the request.
    ///
    /// @return Pointer to the request found, or null pointer if there is
    /// no such request.
    ConstPostHttpRequestJsonPtr
    findRequest(const std::string& str1, const std::string& str2) {
        for (auto r = requests_.begin(); r < requests_.end(); ++r) {
            std::string request_as_string = (*r)->toString();
            if (request_as_string.find(str1) != std::string::npos) {
                if (request_as_string.find(str2) != std::string::npos) {
                    return (*r);
                }
            }
        }

        // Request not found.
        return (ConstPostHttpRequestJsonPtr());
    }

    /// @brief Sets control result  to be included in the responses.
    ///
    /// @param control_result new control result value.
    void setControlResult(const int control_result) {
        control_result_ = control_result;
    }

    /// @brief Sets control result to be returned for the particular command.
    ///
    /// @param command_name command name.
    /// @param control_result new control result value.
    void setControlResult(const std::string& command_name,
                          const int control_result) {
        per_request_control_result_[command_name] = control_result;
    }

    /// @brief Sets arguments to be included in the responses.
    ///
    /// @param arguments pointer to the arguments.
    void setArguments(const ElementPtr& arguments) {
        arguments_ = arguments;
    }

    /// @brief Sets arguments to be included in the response to a particular
    /// command.
    ///
    /// @param command_name command name.
    /// @param arguments pointer to the arguments.
    void setArguments(const std::string& command_name,
                      const ElementPtr& arguments) {
        per_request_arguments_[command_name] = arguments;
    }

    /// @brief Create a new request.
    ///
    /// @return Pointer to the new instance of the @ref HttpRequest.
    virtual HttpRequestPtr
    createNewHttpRequest() const {
        return (HttpRequestPtr(new PostHttpRequestJson()));
    }

private:

    /// @brief Creates HTTP response.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP response.
    virtual HttpResponsePtr
    createStockHttpResponse(const ConstHttpRequestPtr& request,
                            const HttpStatusCode& status_code) const {
        // The request hasn't been finalized so the request object
        // doesn't contain any information about the HTTP version number
        // used. But, the context should have this data (assuming the
        // HTTP version is parsed ok).
        HttpVersion http_version(request->context()->http_version_major_,
                                 request->context()->http_version_minor_);
        // This will generate the response holding JSON content.
        HttpResponseJsonPtr response(new HttpResponseJson(http_version, status_code));
        response->finalize();
        return (response);
    }

    /// @brief Creates HTTP response.
    ///
    /// It records received request so it may be later validated by the tests.
    /// The returned status code and arguments are set using @c setControlResult
    /// and @c setArguments methods. The per-request control result and arguments
    /// take precedence over global values.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP OK response.
    virtual HttpResponsePtr
    createDynamicHttpResponse(const ConstHttpRequestPtr& request) {
        // Request must always be JSON.
        ConstPostHttpRequestJsonPtr request_json =
            boost::dynamic_pointer_cast<const PostHttpRequestJson>(request);

        // Remember the request received.
        requests_.push_back(request_json);

        int control_result = -1;
        ElementPtr arguments;

        // First, check if the request contains a body with a command.
        // If so, we may include a specific error code and arguments in the
        // response based on the command name.
        ConstElementPtr body = request_json->getBodyAsJson();
        if (body && (body->getType() == Element::map)) {
            ConstElementPtr command = body->get("command");
            if (command && (command->getType() == Element::string)) {
                std::string command_name = command->stringValue();

                // Check if there is specific error code to be returned for this
                // command.
                if (per_request_control_result_.count(command_name) > 0) {
                    control_result = per_request_control_result_[command_name];
                }

                // Check if there are specific arguments to be returned for this
                // command.
                if (per_request_arguments_.count(command_name) > 0) {
                    arguments = per_request_arguments_[command_name];
                }
            }
        }

        HttpResponseJsonPtr response(new HttpResponseJson(request->getHttpVersion(),
                                                          HttpStatusCode::OK));
        // Body is a list of responses from multiple servers listed in "service"
        // argument of the request.
        ElementPtr response_body = Element::createList();

        // No per-command control result specified, so include the global result.
        if (control_result < 0) {
            control_result = control_result_;
        }

        // No per-command arguments specified, so include the global arguments.
        if (!arguments) {
            arguments = arguments_;
        }

        // Insert current date-time if not statically provided.
        if (arguments && !arguments->contains("date-time")) {
            arguments->set("date-time", Element::create(HttpDateTime().rfc1123Format()));
        }

        response_body->add(boost::const_pointer_cast<Element>
                           (createAnswer(control_result, "response returned",
                                         arguments)));
        response->setBodyAsJson(response_body);
        response->finalize();
        return (response);
    }

    /// @brief Holds received HTTP requests.
    std::vector<ConstPostHttpRequestJsonPtr> requests_;

    /// @brief Control result to be returned in the server responses.
    int control_result_;

    /// @brief Arguments to be included in the responses.
    ElementPtr arguments_;

    /// @brief Command specific control results.
    std::map<std::string, int> per_request_control_result_;

    /// @brief Command specific response arguments.
    std::map<std::string, ElementPtr> per_request_arguments_;
};

/// @brief Shared pointer to the @c TestHttpResponseCreator.
typedef boost::shared_ptr<TestHttpResponseCreator> TestHttpResponseCreatorPtr;

/// @brief Implementation of the test @ref HttpResponseCreatorFactory.
///
/// This factory class creates @ref TestHttpResponseCreator instances.
class TestHttpResponseCreatorFactory : public HttpResponseCreatorFactory {
public:

    /// @brief Constructor.
    ///
    /// Initializes common HTTP response creator instance.
    TestHttpResponseCreatorFactory()
        : creator_(new TestHttpResponseCreator()) {
    }

    /// @brief Creates @ref TestHttpResponseCreator instance.
    virtual HttpResponseCreatorPtr create() const {
        return (creator_);
    }

    /// @brief Returns instance of the response creator constructed by this
    /// factory.
    TestHttpResponseCreatorPtr getResponseCreator() const {
        return (boost::dynamic_pointer_cast<TestHttpResponseCreator>(creator_));
    }

private:

    /// @brief Pointer to the common HTTP response creator.
    HttpResponseCreatorPtr creator_;
};

/// @brief Pointer to the @c TestHttpResponseCreatorFactory.
typedef boost::shared_ptr<TestHttpResponseCreatorFactory>
TestHttpResponseCreatorFactoryPtr;

/// @brief Test fixture class for @c HAService.
///
/// It creates 3 HTTP listeners (servers) which are used in the unit tests.
class HAServiceTest : public HATest {
public:

    struct MyState {
        explicit MyState(const int state)
            : state_(state) {
        }
        int state_;
    };

    struct PartnerState {
        explicit PartnerState(const int state)
            : state_(state) {
        }
        int state_;
    };

    struct FinalState {
        explicit FinalState(const int state)
            : state_(state) {
        }
        int state_;
    };

    /// @brief Constructor.
    HAServiceTest()
        : HATest(),
          factory_(new TestHttpResponseCreatorFactory()),
          factory2_(new TestHttpResponseCreatorFactory()),
          factory3_(new TestHttpResponseCreatorFactory()),
          listener_(new HttpListener(*io_service_, IOAddress(SERVER_ADDRESS),
                                     SERVER_PORT, factory_,
                                     HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                                     HttpListener::IdleTimeout(IDLE_TIMEOUT))),
          listener2_(new HttpListener(*io_service_, IOAddress(SERVER_ADDRESS),
                                      SERVER_PORT + 1, factory2_,
                                      HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                                      HttpListener::IdleTimeout(IDLE_TIMEOUT))),
          listener3_(new HttpListener(*io_service_, IOAddress(SERVER_ADDRESS),
                                      SERVER_PORT + 2, factory3_,
                                      HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                                      HttpListener::IdleTimeout(IDLE_TIMEOUT))),
          leases4_(),
          leases6_() {
    }

    /// @brief Destructor.
    ///
    /// Stops all test servers.
    ~HAServiceTest() {
        listener_->stop();
        listener2_->stop();
        listener3_->stop();
        io_service_->get_io_service().reset();
        io_service_->poll();
    }

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    ///
    /// @param fail_on_timeout Specifies if test failure should be reported.
    void timeoutHandler(const bool fail_on_timeout) {
        if (fail_on_timeout) {
            ADD_FAILURE() << "Timeout occurred while running the test!";
        }
        io_service_->stop();
    }

    /// @brief Generates IPv4 leases to be used by the tests.
    void generateTestLeases4() {
        generateTestLeases(leases4_);
    }

    /// @brief Returns generated IPv4 leases in JSON format.
    ConstElementPtr getTestLeases4AsJson() const {
        return (getLeasesAsJson(leases4_));
    }

    /// @brief Generates IPv6 leases to be used by the tests.
    void generateTestLeases6() {
        generateTestLeases(leases6_);
    }

    /// @brief Returns generated IPv6 leases in JSON format.
    ConstElementPtr getTestLeases6AsJson() const {
        return (getLeasesAsJson(leases6_));
    }

    /// @brief Tests scenarios when lease updates are sent to a partner while
    /// the partner is online or offline.
    ///
    /// @param unpark_handler a function called when packet is unparked.
    /// @param should_pass indicates if the update is expected to be successful.
    /// @param num_updates expected number of servers to which lease updates are
    /// sent.
    /// @param my_state state of the server while lease updates are sent.
    void testSendLeaseUpdates(std::function<void()> unpark_handler,
                              const bool should_pass,
                              const size_t num_updates,
                              const MyState& my_state = MyState(HA_LOAD_BALANCING_ST)) {
        // Create HA configuration for 3 servers. This server is
        // server 1.
        HAConfigPtr config_storage = createValidConfiguration();

        // Create parking lot where query is going to be parked and unparked.
        ParkingLotPtr parking_lot(new ParkingLot());
        ParkingLotHandlePtr parking_lot_handle(new ParkingLotHandle(parking_lot));

        // Create query.
        Pkt4Ptr query(new Pkt4(DHCPREQUEST, 1234));

        // Create leases collection and put the lease there.
        Lease4CollectionPtr leases4(new Lease4Collection());
        HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>(6, 1), HTYPE_ETHER));
        Lease4Ptr lease4(new Lease4(IOAddress("192.1.2.3"), hwaddr,
                                    static_cast<const uint8_t*>(0), 0,
                                    60, 30, 40, 0, 1));
        leases4->push_back(lease4);

        // Create deleted leases collection and put the lease there too.
        Lease4CollectionPtr deleted_leases4(new Lease4Collection());
        Lease4Ptr deleted_lease4(new Lease4(IOAddress("192.2.3.4"), hwaddr,
                                            static_cast<const uint8_t*>(0), 0,
                                            60, 30, 40, 0, 1));
        deleted_leases4->push_back(deleted_lease4);

        // The communication state is the member of the HAServce object. We have to
        // replace this object with our own implementation to have an ability to
        // modify its poke time.
        NakedCommunicationState4Ptr state(new NakedCommunicationState4(io_service_,
                                                                       config_storage));
        // Set poke time 30s in the past. If the state is poked it will be reset
        // to the current time. This allows for testing whether the object has been
        // poked by the HA service.
        state->modifyPokeTime(-30);

        // Create HA service and schedule lease updates.
        TestHAService service(io_service_, network_state_, config_storage);
        service.communication_state_ = state;

        service.transition(my_state.state_, HAService::NOP_EVT);

        EXPECT_EQ(num_updates,
                  service.asyncSendLeaseUpdates(query, leases4, deleted_leases4,
                                                parking_lot_handle));

        EXPECT_FALSE(state->isPoked());

        ASSERT_NO_THROW(parking_lot->reference(query));

        // Let's park the packet and associate it with the callback function which
        // simply records the fact that it has been called. We expect that it wasn't
        // because the parked packet should be dropped as a result of lease updates
        // failures.
        ASSERT_NO_THROW(parking_lot->park(query, unpark_handler));

        // Actually perform the lease updates.
        ASSERT_NO_THROW(runIOService(TEST_TIMEOUT, [&service]() {
            // Finish running IO service when there are no more pending requests.
            return (service.pending_requests_.empty());
        }));

        // Try to drop the packet. We expect that the packet has been already
        // dropped so this should return false.
        EXPECT_FALSE(parking_lot_handle->drop(query));

        // The updates should not be sent to this server.
        EXPECT_TRUE(factory_->getResponseCreator()->getReceivedRequests().empty());

        if (should_pass) {
            EXPECT_TRUE(state->isPoked());
        } else {
            EXPECT_FALSE(state->isPoked());
        }
    }

    /// @brief Tests scenarios when IPv6 lease updates are sent to a partner while
    /// the partner is online or offline.
    ///
    /// @param unpark_handler a function called when packet is unparked.
    /// @param should_pass indicates if the update is expected to be successful.
    /// @param num_updates expected number of servers to which lease updates are
    /// sent.
    /// @param my_state state of the server while lease updates are sent.
    void testSendLeaseUpdates6(std::function<void()> unpark_handler,
                               const bool should_pass,
                               const size_t num_updates,
                               const MyState& my_state = MyState(HA_LOAD_BALANCING_ST)) {
        // Create HA configuration for 3 servers. This server is
        // server 1.
        HAConfigPtr config_storage = createValidConfiguration();

        // Create parking lot where query is going to be parked and unparked.
        ParkingLotPtr parking_lot(new ParkingLot());
        ParkingLotHandlePtr parking_lot_handle(new ParkingLotHandle(parking_lot));

        // Create query.
        Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));

        // Create leases collection and put the lease there.
        Lease6CollectionPtr leases6(new Lease6Collection());
        DuidPtr duid(new DUID(std::vector<uint8_t>(8, 2)));
        Lease6Ptr lease6(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::cafe"), duid,
                                    1234, 50, 60, 30, 40, 1));
        leases6->push_back(lease6);

        // Create deleted leases collection and put the lease there too.
        Lease6CollectionPtr deleted_leases6(new Lease6Collection());
        Lease6Ptr deleted_lease6(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::efac"),
                                            duid, 1234, 50, 60, 30, 40, 1));
        deleted_leases6->push_back(deleted_lease6);

        // The communication state is the member of the HAServce object. We have to
        // replace this object with our own implementation to have an ability to
        // modify its poke time.
        NakedCommunicationState6Ptr state(new NakedCommunicationState6(io_service_,
                                                                       config_storage));
        // Set poke time 30s in the past. If the state is poked it will be reset
        // to the current time. This allows for testing whether the object has been
        // poked by the HA service.
        state->modifyPokeTime(-30);

        // Create HA service and schedule lease updates.
        TestHAService service(io_service_, network_state_, config_storage);
        service.communication_state_ = state;

        service.transition(my_state.state_, HAService::NOP_EVT);

        EXPECT_EQ(num_updates,
                  service.asyncSendLeaseUpdates(query, leases6, deleted_leases6,
                                                parking_lot_handle));

        EXPECT_FALSE(state->isPoked());

        ASSERT_NO_THROW(parking_lot->reference(query));

        // Let's park the packet and associate it with the callback function which
        // simply records the fact that it has been called. We expect that it wasn't
        // because the parked packet should be dropped as a result of lease updates
        // failures.
        ASSERT_NO_THROW(parking_lot->park(query, unpark_handler));

        // Actually perform the lease updates.
        ASSERT_NO_THROW(runIOService(TEST_TIMEOUT, [&service]() {
            // Finish running IO service when there are no more pending requests.
            return (service.pending_requests_.empty());
        }));

        // Try to drop the packet. We expect that the packet has been already
        // dropped so this should return false.
        EXPECT_FALSE(parking_lot_handle->drop(query));

        // The updates should not be sent to this server.
        EXPECT_TRUE(factory_->getResponseCreator()->getReceivedRequests().empty());

        if (should_pass) {
            EXPECT_TRUE(state->isPoked());
        } else {
            EXPECT_FALSE(state->isPoked());
        }
    }

    /// @brief Tests scenarios when recurring heartbeat has been enabled
    /// and the partner is online or offline.
    ///
    /// @param control_result control result that the servers should return.
    /// @param should_pass boolean value indicating if the heartbeat should
    /// be successful or not.
    void testRecurringHeartbeat(const int control_result,
                                const bool should_pass) {
        // Create HA configuration for 3 servers. This server is
        // server 1.
        HAConfigPtr config_storage = createValidConfiguration();
        config_storage->setHeartbeatDelay(1000);

        // Create a valid static response to the heartbeat command.
        ElementPtr response_arguments = Element::createMap();
        response_arguments->set("state", Element::create(std::string("load-balancing")));

        // Both server 2 and server 3 are configured to send this response.
        factory2_->getResponseCreator()->setArguments(response_arguments);
        factory3_->getResponseCreator()->setArguments(response_arguments);

        // Configure server 2 and server 3 to send a specified control result.
        factory2_->getResponseCreator()->setControlResult(control_result);
        factory3_->getResponseCreator()->setControlResult(control_result);

        // The communication state is the member of the HAServce object. We have to
        // replace this object with our own implementation to have an ability to
        // modify its poke time.
        NakedCommunicationState4Ptr state(new NakedCommunicationState4(io_service_,
                                                                       config_storage));
        // Set poke time 30s in the past. If the state is poked it will be reset
        // to the current time. This allows for testing whether the object has been
        // poked by the HA service.
        state->modifyPokeTime(-30);

        // Create the service and replace the default communication state object.
        TestHAService service(io_service_, network_state_, config_storage);
        service.communication_state_ = state;

        EXPECT_FALSE(state->isPoked());

        // Let's explicitly transition the state machine to the load balancing state
        // in which the periodic heartbeats should be generated.
        ASSERT_NO_THROW(service.verboseTransition(HA_LOAD_BALANCING_ST));
        ASSERT_NO_THROW(service.runModel(HAService::NOP_EVT));

        // Run the IO service to allow the heartbeat interval timers to execute.
        ASSERT_NO_THROW(runIOService(2000));

        // Server 1 and server 3 must never receive heartbeats because the former
        // is the one that generates them and the latter is a backup server.
        EXPECT_TRUE(factory_->getResponseCreator()->getReceivedRequests().empty());
        EXPECT_TRUE(factory3_->getResponseCreator()->getReceivedRequests().empty());

        // If should pass, the communication state should be poked.
        if (should_pass) {
            EXPECT_TRUE(state->isPoked());
        } else {
            EXPECT_FALSE(state->isPoked());
        }
    }

    /// @brief Runs HAService::processSynchronize for the DHCPv4 server and
    /// returns a response.
    ///
    /// The HAService::processSynchronize is synchronous. Therefore, the IO service
    /// for HTTP servers is run in a thread. The unit test is responsible for setting
    /// up the status codes to be returned by the servers, verifying a response and
    /// leases in the lease database.
    ///
    /// @param [out] rsp pointer to the object where response will be stored.
    void runProcessSynchronize4(ConstElementPtr& rsp) {
        // Create lease manager.
        ASSERT_NO_THROW(LeaseMgrFactory::create("universe=4 type=memfile persist=false"));

        // Create IPv4 leases which will be fetched from the other server.
        ASSERT_NO_THROW(generateTestLeases4());

        // Create HA configuration for 3 servers. This server is
        // server 1.
        HAConfigPtr config_storage = createValidConfiguration();

        // Convert leases to the JSON format, the same as used by the lease_cmds
        // hook library. Configure our test HTTP servers to return those
        // leases in this format.
        ElementPtr response_arguments = Element::createMap();
        response_arguments->set("leases", getTestLeases4AsJson());

        factory2_->getResponseCreator()->setArguments("lease4-get-all", response_arguments);
        factory3_->getResponseCreator()->setArguments("lease4-get-all", response_arguments);

        // Start the servers.
        ASSERT_NO_THROW({
            listener_->start();
            listener2_->start();
            listener3_->start();
        });

        HAService service(io_service_, network_state_, config_storage);

        // The tested function is synchronous, so we need to run server side IO service
        // in bakckground to not block the main thread.
        auto thread = runIOServiceInThread();

        // Process ha-sync command.
        ASSERT_NO_THROW(rsp = service.processSynchronize("server2", 20));

        // Stop the IO service. This should cause the thread to terminate.
        io_service_->stop();
        thread->wait();
        io_service_->get_io_service().reset();
        io_service_->poll();
    }

    /// @brief Runs HAService::processSynchronize for the DHCPv6 server
    /// and returns a response.
    ///
    /// The HAService::processSynchronize is synchronous. Therefore, the IO service
    /// for HTTP servers is run in a thread. The unit test is responsible for setting
    /// up the status codes to be returned by the servers, verifying a response and
    /// leases in the lease database.
    ///
    /// @param [out] rsp pointer to the object where response will be stored.
    void runProcessSynchronize6(ConstElementPtr& rsp) {
        // Create lease manager.
        ASSERT_NO_THROW(LeaseMgrFactory::create("universe=6 type=memfile persist=false"));

        // Create IPv4 leases which will be fetched from the other server.
        ASSERT_NO_THROW(generateTestLeases6());

        // Create HA configuration for 3 servers. This server is
        // server 1.
        HAConfigPtr config_storage = createValidConfiguration();

        // Convert leases to the JSON format, the same as used by the lease_cmds
        // hook library. Configure our test HTTP servers to return those
        // leases in this format.
        ElementPtr response_arguments = Element::createMap();
        response_arguments->set("leases", getTestLeases6AsJson());

        factory2_->getResponseCreator()->setArguments("lease6-get-all", response_arguments);
        factory3_->getResponseCreator()->setArguments("lease6-get-all", response_arguments);

        // Start the servers.
        ASSERT_NO_THROW({
            listener_->start();
            listener2_->start();
            listener3_->start();
        });

        HAService service(io_service_, network_state_, config_storage,
                          HAServerType::DHCPv6);

        // The tested function is synchronous, so we need to run server side IO service
        // in bakckground to not block the main thread.
        auto thread = runIOServiceInThread();

        // Process ha-sync command.
        ASSERT_NO_THROW(rsp = service.processSynchronize("server2", 20));

        // Stop the IO service. This should cause the thread to terminate.
        io_service_->stop();
        thread->wait();
        io_service_->get_io_service().reset();
        io_service_->poll();
    }

    /// @brief HTTP response factory for server 1.
    TestHttpResponseCreatorFactoryPtr factory_;

    /// @brief HTTP response factory for server 2.
    TestHttpResponseCreatorFactoryPtr factory2_;

    /// @brief HTTP response factory for server 3.
    TestHttpResponseCreatorFactoryPtr factory3_;

    /// @brief Test HTTP server 1.
    HttpListenerPtr listener_;

    /// @brief Test HTTP server 2.
    HttpListenerPtr listener2_;

    /// @brief Test HTTP server 2.
    HttpListenerPtr listener3_;

    /// @brief IPv4 leases to be used in the tests.
    std::vector<Lease4Ptr> leases4_;

    /// @brief IPv6 leases to be used in the tests.
    std::vector<Lease6Ptr> leases6_;
};

// Test that server performs load balancing and assigns appropriate classes
// to the queries.
TEST_F(HAServiceTest, loadBalancingScopeSelection) {
    // Create HA configuration for load balancing.
    HAConfigPtr config_storage = createValidConfiguration();
    // ... and HA service using this configuration.
    TestHAService service(io_service_, network_state_, config_storage);
    service.verboseTransition(HA_LOAD_BALANCING_ST);
    service.runModel(HAService::NOP_EVT);

    // Count number of in scope packets.
    unsigned in_scope = 0;
    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));

        // Some queries should be processed by this server, some not.
        if (service.inScope(query4)) {
            // If the query is to be processed by this server the query
            // should be assigned to the "HA_server1" class but not to
            // the "HA_server2" class.
            ASSERT_TRUE(query4->inClass(ClientClass("HA_server1")));
            ASSERT_FALSE(query4->inClass(ClientClass("HA_server2")));
            ++in_scope;

        } else {
            // If the query is to be processed by another server, the
            // "HA_server2" class should be assigned instead.
            ASSERT_FALSE(query4->inClass(ClientClass("HA_server1")));
            ASSERT_TRUE(query4->inClass(ClientClass("HA_server2")));
        }
    }

    // We should have roughly 50/50 split of in scope and out of scope queries.
    // However, we don't know exactly how many. To be safe we simply assume that
    // we got more than 25% of in scope and more than 25% out of scope queries.
    EXPECT_GT(in_scope, static_cast<unsigned>(queries_num / 4));
    EXPECT_GT(queries_num - in_scope, static_cast<unsigned>(queries_num / 4));
}

// Test that primary server in hot standby configuration processes all queries.
TEST_F(HAServiceTest, hotStandbyScopeSelectionThisPrimary) {
    // Create HA configuration for load balancing.
    HAConfigPtr config_storage = createValidConfiguration();

    // Turn it into hot-standby configuration.
    config_storage->setHAMode("hot-standby");
    config_storage->getPeerConfig("server2")->setRole("standby");

    // ... and HA service using this configuration.
    TestHAService service(io_service_, network_state_, config_storage);
    service.verboseTransition(HA_HOT_STANDBY_ST);
    service.runModel(HAService::NOP_EVT);

    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));

        // All queries should be processed by this server.
        ASSERT_TRUE(service.inScope(query4));
        // The query should be assigned to the "HA_server1" class but not to
        // the "HA_server2" class.
        ASSERT_TRUE(query4->inClass(ClientClass("HA_server1")));
        ASSERT_FALSE(query4->inClass(ClientClass("HA_server2")));
    }
}

// Test that secondary server in hot standby configuration processes no queries.
TEST_F(HAServiceTest, hotStandbyScopeSelectionThisStandby) {
    // Create HA configuration for load balancing.
    HAConfigPtr config_storage = createValidConfiguration();

    // Turn it into hot-standby configuration.
    config_storage->setHAMode("hot-standby");
    config_storage->getPeerConfig("server2")->setRole("standby");
    config_storage->setThisServerName("server2");

    // ... and HA service using this configuration.
    TestHAService service(io_service_, network_state_, config_storage);

    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));

        // No queries should be processed by this server.
        ASSERT_FALSE(service.inScope(query4));
        // The query should be assigned to the "HA_server1" class but not to
        // the "HA_server2" class.
        ASSERT_TRUE(query4->inClass(ClientClass("HA_server1")));
        ASSERT_FALSE(query4->inClass(ClientClass("HA_server2")));
    }
}

// Test scenario when all lease updates are sent successfully.
TEST_F(HAServiceTest, sendSuccessfulUpdates) {
    // Start HTTP servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    // This flag will be set to true if unpark is called.
    bool unpark_called = false;
    testSendLeaseUpdates([&unpark_called] {
        unpark_called = true;
    }, true, 2);

    // Expecting that the packet was unparked because lease updates are expected
    // to be successful.
    EXPECT_TRUE(unpark_called);

    // The server 2 should have received two commands.
    EXPECT_EQ(2, factory2_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 2 has received lease4-update command.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_TRUE(update_request2);

    // Check that the server 2 has received lease4-del command.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_TRUE(delete_request2);

    // Lease updates should be successfully sent to server3.
    EXPECT_EQ(2, factory3_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 3 has received lease4-update command.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_TRUE(update_request3);

    // Check that the server 3 has received lease4-del command.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_TRUE(delete_request3);
}

// Test scenario when lease updates are sent successfully to the backup server
// and not sent to the failover peer when this server is in patrtner-down state.
TEST_F(HAServiceTest, sendUpdatesPartnerDown) {
    // Start HTTP servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    // This flag will be set to true if unpark is called.
    bool unpark_called = false;
    testSendLeaseUpdates([&unpark_called] {
        unpark_called = true;
    }, false, 1, MyState(HA_PARTNER_DOWN_ST));

    // Expecting that the packet was unparked because lease updates are expected
    // to be successful.
    EXPECT_TRUE(unpark_called);

    // Server 2 should not receive lease4-update.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_FALSE(update_request2);

    // Server 2 should not receive lease4-del.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_FALSE(delete_request2);

    // Lease updates should be successfully sent to server3.
    EXPECT_EQ(2, factory3_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 3 has received lease4-update command.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_TRUE(update_request3);

    // Check that the server 3 has received lease4-del command.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_TRUE(delete_request3);
}

// Test scenario when one of the servers to which updates are sent is offline.
TEST_F(HAServiceTest, sendUpdatesActiveServerOffline) {
    // Start only two servers out of three. The server 3 is not running.
    ASSERT_NO_THROW({
            listener_->start();
            listener3_->start();
    });

    testSendLeaseUpdates([] {
        ADD_FAILURE() << "unpark function called but expected that the packet"
            " is dropped";
    }, false, 2);

    // Server 2 should not receive lease4-update.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_FALSE(update_request2);

    // Server 2 should not receive lease4-del.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_FALSE(delete_request2);

    // Lease updates should be successfully sent to server3.
    EXPECT_EQ(2, factory3_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 3 has received lease4-update command.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_TRUE(update_request3);

    // Check that the server 3 has received lease4-del command.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_TRUE(delete_request3);
}

// Test scenario when one of the servers to which updates are sent is offline.
TEST_F(HAServiceTest, sendUpdatesBackupServerOffline) {
    // Start only two servers out of three. The server 2 is not running.
    ASSERT_NO_THROW({
            listener_->start();
            listener2_->start();
    });

    bool unpark_called = false;
    testSendLeaseUpdates([&unpark_called] {
        unpark_called = true;
    }, true, 2);

    EXPECT_TRUE(unpark_called);

    // The server 2 should have received two commands.
    EXPECT_EQ(2, factory2_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 2 has received lease4-update command.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_TRUE(update_request2);

    // Check that the server 2 has received lease4-del command.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_TRUE(delete_request2);

    // Server 3 should not receive lease4-update.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_FALSE(update_request3);

    // Server 3 should not receive lease4-del.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_FALSE(delete_request3);
}

// Test scenario when one of the servers to which a lease update is sent
// returns an error.
TEST_F(HAServiceTest, sendUpdatesControlResultError) {
    // Instruct the server 2 to return an error as a result of receiving a command.
    factory2_->getResponseCreator()->setControlResult(CONTROL_RESULT_ERROR);

    // Start only two servers out of three. The server 3 is not running.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    testSendLeaseUpdates([] {
        ADD_FAILURE() << "unpark function called but expected that the packet"
            " is dropped";
    }, false, 2);

    // The updates should be sent to server 2 and this server should return error code.
    EXPECT_EQ(2, factory2_->getResponseCreator()->getReceivedRequests().size());

    // Server 2 should receive lease4-update.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_TRUE(update_request2);

    // Server 2 should receive lease4-del.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_TRUE(delete_request2);

    // Lease updates should be successfully sent to server3.
    EXPECT_EQ(2, factory3_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 3 has received lease4-update command.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease4-update",
                                                                        "192.1.2.3");
    EXPECT_TRUE(update_request3);

    // Check that the server 3 has received lease4-del command.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease4-del",
                                                                        "192.2.3.4");
    EXPECT_TRUE(delete_request3);
}

// Test scenario when all lease updates are sent successfully.
TEST_F(HAServiceTest, sendSuccessfulUpdates6) {
    // Start HTTP servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    // This flag will be set to true if unpark is called.
    bool unpark_called = false;
    testSendLeaseUpdates6([&unpark_called] {
        unpark_called = true;
    }, true, 2);

    // Expecting that the packet was unparked because lease updates are expected
    // to be successful.
    EXPECT_TRUE(unpark_called);

    // The server 2 should have received two commands.
    EXPECT_EQ(2, factory2_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 2 has received lease6-update command.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_TRUE(update_request2);

    // Check that the server 2 has received lease6-del command.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_TRUE(delete_request2);

    // Lease updates should be successfully sent to server3.
    EXPECT_EQ(2, factory3_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 3 has received lease6-update command.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_TRUE(update_request3);

    // Check that the server 3 has received lease6-del command.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_TRUE(delete_request3);
}

// Test scenario when lease updates are sent successfully to the backup server
// and not sent to the failover peer when this server is in patrtner-down state.
TEST_F(HAServiceTest, sendUpdatesPartnerDown6) {
    // Start HTTP servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    // This flag will be set to true if unpark is called.
    bool unpark_called = false;
    testSendLeaseUpdates6([&unpark_called] {
        unpark_called = true;
    }, false, 1, MyState(HA_PARTNER_DOWN_ST));

    // Expecting that the packet was unparked because lease updates are expected
    // to be successful.
    EXPECT_TRUE(unpark_called);

    // Server 2 should not receive lease6-update.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_FALSE(update_request2);

    // Server 2 should not receive lease6-del.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_FALSE(delete_request2);

    // Lease updates should be successfully sent to server3.
    EXPECT_EQ(2, factory3_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 3 has received lease6-update command.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_TRUE(update_request3);

    // Check that the server 3 has received lease6-del command.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_TRUE(delete_request3);
}

// Test scenario when one of the servers to which updates are sent is offline.
TEST_F(HAServiceTest, sendUpdatesActiveServerOffline6) {
    // Start only two servers out of three. The server 3 is not running.
    ASSERT_NO_THROW({
            listener_->start();
            listener3_->start();
    });

    testSendLeaseUpdates6([] {
        ADD_FAILURE() << "unpark function called but expected that the packet"
            " is dropped";
    }, false, 2);

    // Server 2 should not receive lease6-update.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_FALSE(update_request2);

    // Server 2 should not receive lease6-del.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_FALSE(delete_request2);

    // Lease updates should be successfully sent to server3.
    EXPECT_EQ(2, factory3_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 3 has received lease6-update command.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_TRUE(update_request3);

    // Check that the server 3 has received lease6-del command.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_TRUE(delete_request3);
}

// Test scenario when one of the servers to which updates are sent is offline.
TEST_F(HAServiceTest, sendUpdatesBackupServerOffline6) {
    // Start only two servers out of three. The server 2 is not running.
    ASSERT_NO_THROW({
            listener_->start();
            listener2_->start();
    });

    bool unpark_called = false;
    testSendLeaseUpdates6([&unpark_called] {
        unpark_called = true;
    }, true, 2);

    EXPECT_TRUE(unpark_called);

    // The server 2 should have received two commands.
    EXPECT_EQ(2, factory2_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 2 has received lease6-update command.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_TRUE(update_request2);

    // Check that the server 2 has received lease6-del command.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_TRUE(delete_request2);

    // Server 3 should not receive lease6-update.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_FALSE(update_request3);

    // Server 3 should not receive lease6-del.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_FALSE(delete_request3);
}

// Test scenario when one of the servers to which a lease update is sent
// returns an error.
TEST_F(HAServiceTest, sendUpdatesControlResultError6) {
    // Instruct the server 2 to return an error as a result of receiving a command.
    factory2_->getResponseCreator()->setControlResult(CONTROL_RESULT_ERROR);

    // Start only two servers out of three. The server 3 is not running.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    testSendLeaseUpdates6([] {
        ADD_FAILURE() << "unpark function called but expected that the packet"
            " is dropped";
    }, false, 2);

    // The updates should be sent to server 2 and this server should return error code.
    EXPECT_EQ(2, factory2_->getResponseCreator()->getReceivedRequests().size());

    // Server 2 should receive lease6-update.
    auto update_request2 = factory2_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_TRUE(update_request2);

    // Server 2 should receive lease6-del.
    auto delete_request2 = factory2_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_TRUE(delete_request2);

    // Lease updates should be successfully sent to server3.
    EXPECT_EQ(2, factory3_->getResponseCreator()->getReceivedRequests().size());

    // Check that the server 3 has received lease6-update command.
    auto update_request3 = factory3_->getResponseCreator()->findRequest("lease6-update",
                                                                        "2001:db8:1::cafe");
    EXPECT_TRUE(update_request3);

    // Check that the server 3 has received lease6-del command.
    auto delete_request3 = factory3_->getResponseCreator()->findRequest("lease6-del",
                                                                        "2001:db8:1::efac");
    EXPECT_TRUE(delete_request3);
}

// This test verifies that the heartbeat command is processed successfully.
TEST_F(HAServiceTest, processHeartbeat) {
    // Create HA configuration for 3 servers. This server is
    // server 1.
    std::string config_text =
        "["
        "     {"
        "         \"this-server-name\": \"server1\","
        "         \"mode\": \"load-balancing\","
        "         \"peers\": ["
        "             {"
        "                 \"name\": \"server1\","
        "                 \"url\": \"http://127.0.0.1:18123/\","
        "                 \"role\": \"primary\","
        "                 \"auto-failover\": true"
        "             },"
        "             {"
        "                 \"name\": \"server2\","
        "                 \"url\": \"http://127.0.0.1:18124/\","
        "                 \"role\": \"secondary\","
        "                 \"auto-failover\": true"
        "             },"
        "             {"
        "                 \"name\": \"server3\","
        "                 \"url\": \"http://127.0.0.1:18125/\","
        "                 \"role\": \"backup\","
        "                 \"auto-failover\": false"
        "             }"
        "         ]"
        "     }"
        "]";

    // Parse the HA configuration.
    HAConfigPtr config_storage(new HAConfig());
    HAConfigParser parser;
    ASSERT_NO_THROW(parser.parse(config_storage, Element::fromJSON(config_text)));

    HAService service(io_service_,  network_state_, config_storage);

    // Process heartbeat command.
    ConstElementPtr rsp;
    ASSERT_NO_THROW(rsp = service.processHeartbeat());

    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_SUCCESS, "HA peer status returned.");
    // Response must include arguments.
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);

    // Response must include server state as string.
    ConstElementPtr state = args->get("state");
    ASSERT_TRUE(state);
    EXPECT_EQ(Element::string, state->getType());
    EXPECT_EQ("waiting", state->stringValue());

    // Response must include timestamp when the response was generated.
    ConstElementPtr date_time = args->get("date-time");
    ASSERT_TRUE(date_time);
    EXPECT_EQ(Element::string, date_time->getType());

    // The response should contain the timestamp in the format specified
    // in RFC1123. We use the HttpDateTime method to parse this timestamp.
    HttpDateTime t;
    ASSERT_NO_THROW(t = HttpDateTime::fromRfc1123(date_time->stringValue()));

    // Let's test if the timestamp is accurate. We do it by checking current
    // time and comparing with the received timestamp.
    HttpDateTime now;
    boost::posix_time::time_duration td = now.getPtime() - t.getPtime();

    // Let's allow the response propagation time of 5 seconds to make
    // sure this test doesn't fail on slow systems.
    EXPECT_LT(td.seconds(), 5);
}

// This test verifies that the correct value of the heartbeat-delay is used.
TEST_F(HAServiceTest, recurringHeartbeatDelay) {
    HAConfigPtr config_storage = createValidConfiguration();

    // Set the heartbeat delay to 6 seconds.
    config_storage->setHeartbeatDelay(6000);

    // The communication state is the member of the HAServce object. We have to
    // replace this object with our own implementation to have an ability to
    // test the setup of the interval timer.
    NakedCommunicationState4Ptr state(new NakedCommunicationState4(io_service_,
                                                                   config_storage));

    TestHAService service(io_service_, network_state_, config_storage);
    service.communication_state_ = state;

    // Let's explicitly transition the state machine to the load balancing state
    // in which the periodic heartbeats should be generated.
    ASSERT_NO_THROW(service.verboseTransition(HA_LOAD_BALANCING_ST));
    ASSERT_NO_THROW(service.runModel(HAService::NOP_EVT));

    ASSERT_TRUE(state->timer_);
    EXPECT_EQ(6000, state->timer_->getInterval());
}

// This test verifies that the heartbeat is periodically sent to the
// other server.
TEST_F(HAServiceTest, recurringHeartbeat) {
    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    // All servers are configured to return success and all servers are online.
    // The heartbeat should be successful (as indicated by the 'true' argument).
    ASSERT_NO_FATAL_FAILURE(testRecurringHeartbeat(CONTROL_RESULT_SUCCESS, true));

    // Server 2 should have received the heartbeat
    EXPECT_GE(factory2_->getResponseCreator()->getReceivedRequests().size(), 0);
}

// This test verifies that the heartbeat is considered being unsuccessful if the
// partner is offline.
TEST_F(HAServiceTest, recurringHeartbeatServerOffline) {
    // Start the servers but do not start server 2.
    ASSERT_NO_THROW({
        listener_->start();
        listener3_->start();
    });

    // The servers are configured to return success but the server 2 is offline
    // so the heartbeat should be unsuccessul.
    ASSERT_NO_FATAL_FAILURE(testRecurringHeartbeat(CONTROL_RESULT_SUCCESS, false));

    // Server 2 is offline so it would be very weird if it received any command.
    EXPECT_TRUE(factory2_->getResponseCreator()->getReceivedRequests().empty());
}

// This test verifies that the heartbeat is considered being unsuccessful if the
// partner returns error control result.
TEST_F(HAServiceTest, recurringHeartbeatControlResultError) {
    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    // Run the actual test. The servers return a control error and it is expected
    // that the state is not poked.
    ASSERT_NO_FATAL_FAILURE(testRecurringHeartbeat(CONTROL_RESULT_ERROR, false));

    // Server 2 should have received the heartbeat.
    EXPECT_EQ(1, factory2_->getResponseCreator()->getReceivedRequests().size());
}

// This test verifies that IPv4 leases can be fetched from the peer and inserted
// or updated in the local lease database.
TEST_F(HAServiceTest, asyncSyncLeases) {
    // Create lease manager.
    ASSERT_NO_THROW(LeaseMgrFactory::create("universe=4 type=memfile persist=false"));

    // Create IPv4 leases which will be fetched from the other server.
    ASSERT_NO_THROW(generateTestLeases4());

    for (size_t i = 0; i < leases4_.size(); ++i) {
        // For every even lease index we add this lease to the database to exercise
        // the scenario when a lease is already in the database and may be updated
        // by the lease synchronization procedure.
        if ((i % 2) == 0) {
            // Add a copy of the lease to make sure that by modifying the lease
            // contents we don't affect the lease in the database.
            Lease4Ptr lease_to_add(new Lease4(*leases4_[i]));
            // Modify valid lifetime of the lease in the database so we can
            // later use this value to verify if the lease has been updated.
            --lease_to_add->valid_lft_;
            LeaseMgrFactory::instance().addLease(lease_to_add);
        }
    }

    // Modify cltt of the first lease. This lease should be updated as a result
    // of synchrnonization process because cltt is checked and the lease is
    // updated if the cltt of the fetched lease is later than the cltt of the
    // existing lease.
    ++leases4_[0]->cltt_;

    // For the second lease, set the wrong subnet identifier. This should be
    // rejected and this lease shouldn't be inserted into the database.
    // Other leases should be inserted/updated just fine.
    ++leases4_[1]->subnet_id_ = 0;

    // Modify the partner's lease cltt so it is earlier than the local lease.
    // Therfore, this lease update should be rejected.
    --leases4_[2]->cltt_;

    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();

    // Convert leases to the JSON format, the same as used by the lease_cmds
    // hook library. Configure our test HTTP servers to return those
    // leases in this format.
    ElementPtr response_arguments = Element::createMap();
    response_arguments->set("leases", getTestLeases4AsJson());

    factory2_->getResponseCreator()->setArguments(response_arguments);
    factory3_->getResponseCreator()->setArguments(response_arguments);

    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    TestHAService service(io_service_, network_state_, config_storage);
    // Setting the heartbeat delay to 0 disables the recurring heartbeat.
    // We just want to synchronize leases and not send the heartbeat.
    config_storage->setHeartbeatDelay(0);

    // Start fetching leases asynchronously.
    ASSERT_NO_THROW(service.asyncSyncLeases());

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(TEST_TIMEOUT, []() {
        // Stop running the IO service if we see a lease in the lease
        // database which is expected to be inserted as a result of lease
        // syncing.
        return (!LeaseMgrFactory::instance().getLeases4(SubnetID(4)).empty());
    }));

    // Check if all leases have been stored in the local database.
    for (size_t i = 0; i < leases4_.size(); ++i) {
        if (i == 1) {
            // This lease was purposely malformed and thus shouldn't be
            // inserted into the database.
            EXPECT_FALSE(LeaseMgrFactory::instance().getLease4(leases4_[i]->addr_))
                << "lease " << leases4_[i]->addr_.toText()
                << " was inserted into the database, but it shouldn't";

        } else {
            // All other leases should be in the database.
            Lease4Ptr existing_lease = LeaseMgrFactory::instance().getLease4(leases4_[i]->addr_);
            ASSERT_TRUE(existing_lease) << "lease " << leases4_[i]->addr_.toText()
                                        << " not in the lease database";
            // The lease with #2 returned by the partner is older than its local instance.
            // The local server should reject this lease.
            if (i == 2) {
                // The existing lease should have unmodified timestamp because the
                // update is expected to be rejected. Same for valid lifetime.
                EXPECT_LT(leases4_[i]->cltt_, existing_lease->cltt_);
                EXPECT_NE(leases4_[i]->valid_lft_, existing_lease->valid_lft_);

            } else {
                // All other leases should have the same cltt.
                EXPECT_EQ(leases4_[i]->cltt_, existing_lease->cltt_);

                // Leases with even indexes were added to the database with modified
                // valid lifetime. Thus the local copy of each such lease should have
                // this modified valid lifetime. The lease #0 should be updated from
                // the partner because of the partner's cltt was set to later time.
                if ((i != 0) && (i % 2) == 0) {
                    EXPECT_EQ(leases4_[i]->valid_lft_ - 1, existing_lease->valid_lft_);

                } else {
                    // All other leases should have been fetched from the partner and
                    // inserted with no change.
                    EXPECT_EQ(leases4_[i]->valid_lft_, existing_lease->valid_lft_);
                }
            }
        }
    }
}

// Test that there is no exception thrown during leases synchronization
// when server returns a wrong answer.
TEST_F(HAServiceTest, asyncSyncLeasesWrongAnswer) {
    // Create lease manager.
    ASSERT_NO_THROW(LeaseMgrFactory::create("universe=4 type=memfile persist=false"));

    // Create IPv4 leases which will be fetched from the other server.
    ASSERT_NO_THROW(generateTestLeases4());

    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();
    // Setting the heartbeat delay to 0 disables the recurring heartbeat.
    // We just want to synchronize leases and not send the heartbeat.
    config_storage->setHeartbeatDelay(0);

    // Set empty response. This should cause the HA service to log an
    // error but not crash.
    ElementPtr response_arguments = Element::createMap();

    factory2_->getResponseCreator()->setArguments(response_arguments);
    factory3_->getResponseCreator()->setArguments(response_arguments);

    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    TestHAService service(io_service_, network_state_, config_storage);

    // Start fetching leases asynchronously.
    ASSERT_NO_THROW(service.asyncSyncLeases());

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(1000));
}

// Test that there is no exception thrown during leases synchronization
// when servers are offline.
TEST_F(HAServiceTest, asyncSyncLeasesServerOffline) {
    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();
    // Setting the heartbeat delay to 0 disables the recurring heartbeat.
    // We just want to synchronize leases and not send the heartbeat.
    config_storage->setHeartbeatDelay(0);

    TestHAService service(io_service_, network_state_, config_storage);

    // Start fetching leases asynchronously.
    ASSERT_NO_THROW(service.asyncSyncLeases());

    // Run IO service for 1 second.
    ASSERT_NO_THROW(runIOService(1000));
}

// This test verifies that IPv6 leases can be fetched from the peer and inserted
// or updated in the local lease database.
TEST_F(HAServiceTest, asyncSyncLeases6) {
    // Create lease manager.
    ASSERT_NO_THROW(LeaseMgrFactory::create("universe=6 type=memfile persist=false"));

    // Create IPv6 leases which will be fetched from the other server.
    ASSERT_NO_THROW(generateTestLeases6());

    for (size_t i = 0; i < leases6_.size(); ++i) {
        // For every even lease index we add this lease to the database to exercise
        // the scenario when a lease is already in the database and may be updated
        // by the lease synchronization procedure.
        if ((i % 2) == 0) {
            // Add a copy of the lease to make sure that by modifying the lease
            // contents we don't affect the lease in the database.
            Lease6Ptr lease_to_add(new Lease6(*leases6_[i]));
            // Modify valid lifetime of the lease in the database so we can
            // later use this value to verify if the lease has been updated.
            --lease_to_add->valid_lft_;
            LeaseMgrFactory::instance().addLease(lease_to_add);
        }
    }

    // Modify cltt of the first lease. This lease should be updated as a result
    // of synchrnonization process because cltt is checked and the lease is
    // updated if the cltt of the fetched lease is later than the cltt of the
    // existing lease.
    ++leases6_[0]->cltt_;

    // For the second lease, set the wrong subnet identifier. This should be
    // rejected and this lease shouldn't be inserted into the database.
    // Other leases should be inserted/updated just fine.
    ++leases6_[1]->subnet_id_ = 0;

    // Modify the partner's lease cltt so it is earlier than the local lease.
    // Therfore, this lease update should be rejected.
    --leases6_[2]->cltt_;

    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();

    // Convert leases to the JSON format, the same as used by the lease_cmds
    // hook library. Configure our test HTTP servers to return those
    // leases in this format.
    ElementPtr response_arguments = Element::createMap();
    response_arguments->set("leases", getTestLeases6AsJson());

    factory2_->getResponseCreator()->setArguments(response_arguments);
    factory3_->getResponseCreator()->setArguments(response_arguments);

    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    TestHAService service(io_service_, network_state_, config_storage,
                          HAServerType::DHCPv6);
    // Setting the heartbeat delay to 0 disables the recurring heartbeat.
    // We just want to synchronize leases and not send the heartbeat.
    config_storage->setHeartbeatDelay(0);

    // Start fetching leases asynchronously.
    ASSERT_NO_THROW(service.asyncSyncLeases());

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(TEST_TIMEOUT, []() {
        // Stop running the IO service if we see a lease in the lease
        // database which is expected to be inserted as a result of lease
        // syncing.
        return (!LeaseMgrFactory::instance().getLeases6(SubnetID(4)).empty());
    }));

    // Check if all leases have been stored in the local database.
    for (size_t i = 0; i < leases6_.size(); ++i) {
        if (i == 1) {
            // This lease was purposely malformed and thus shouldn't be
            // inserted into the database.
            EXPECT_FALSE(LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                               leases6_[i]->addr_))
                << "lease " << leases6_[i]->addr_.toText()
                << " was inserted into the database, but it shouldn't";
        } else {
            // Other leases should be inserted/updated.
            Lease6Ptr existing_lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                                             leases6_[i]->addr_);
            ASSERT_TRUE(existing_lease) << "lease " << leases6_[i]->addr_.toText()
                                        << " not in the lease database";

            if (i == 2) {
                // The existing lease should have unmodified timestamp because the
                // update is expected to be rejected. Same for valid lifetime.
                EXPECT_LT(leases6_[i]->cltt_, existing_lease->cltt_);
                EXPECT_NE(leases6_[i]->valid_lft_, existing_lease->valid_lft_);

            } else {
                // All other leases should have the same cltt.
                EXPECT_EQ(leases6_[i]->cltt_, existing_lease->cltt_);

                // Leases with even indexes were added to the database with modified
                // valid lifetime. Thus the local copy of each such lease should have
                // this modified valid lifetime. The lease #0 should be updated from
                // the partner because of the partner's cltt was set to later time.
                if ((i != 0) && (i % 2) == 0) {
                    EXPECT_EQ(leases6_[i]->valid_lft_ - 1, existing_lease->valid_lft_);

                } else {
                    // All other leases should have been fetched from the partner and
                    // inserted with no change.
                    EXPECT_EQ(leases6_[i]->valid_lft_, existing_lease->valid_lft_);
                }
            }
        }
    }
}

// Test that there is no exception thrown during IPv6 leases synchronization
// when server returns a wrong answer.
TEST_F(HAServiceTest, asyncSyncLeases6WrongAnswer) {
    // Create lease manager.
    ASSERT_NO_THROW(LeaseMgrFactory::create("universe=6 type=memfile persist=false"));

    // Create IPv6 leases which will be fetched from the other server.
    ASSERT_NO_THROW(generateTestLeases6());

    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();
    // Setting the heartbeat delay to 0 disables the recurring heartbeat.
    // We just want to synchronize leases and not send the heartbeat.
    config_storage->setHeartbeatDelay(0);

    // Set empty response. This should cause the HA service to log an
    // error but not crash.
    ElementPtr response_arguments = Element::createMap();

    factory2_->getResponseCreator()->setArguments(response_arguments);
    factory3_->getResponseCreator()->setArguments(response_arguments);

    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    TestHAService service(io_service_, network_state_, config_storage,
                          HAServerType::DHCPv6);

    // Start fetching leases asynchronously.
    ASSERT_NO_THROW(service.asyncSyncLeases());

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(1000));
}

// Test that there is no exception thrown during IPv6 leases synchronization
// when servers are offline.
TEST_F(HAServiceTest, asyncSyncLeases6ServerOffline) {
    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();
    // Setting the heartbeat delay to 0 disables the recurring heartbeat.
    // We just want to synchronize leases and not send the heartbeat.
    config_storage->setHeartbeatDelay(0);

    TestHAService service(io_service_, network_state_, config_storage,
                          HAServerType::DHCPv6);

    // Start fetching leases asynchronously.
    ASSERT_NO_THROW(service.asyncSyncLeases());

    // Run IO service for 1 second.
    ASSERT_NO_THROW(runIOService(1000));
}

// This test verifies that the ha-sync command is processed successfully for the
// DHCPv4 server.
TEST_F(HAServiceTest, processSynchronize4) {

    // Run HAService::processSynchronize and gather a response.
    ConstElementPtr rsp;
    runProcessSynchronize4(rsp);

    // The response should indicate success.
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_SUCCESS, "Lease database synchronization"
                " complete.");

    // All leases should have been inserted into the database.
    for (size_t i = 0; i < leases4_.size(); ++i) {
        Lease4Ptr existing_lease = LeaseMgrFactory::instance().getLease4(leases4_[i]->addr_);
        ASSERT_TRUE(existing_lease) << "lease " << leases4_[i]->addr_.toText()
                                    << " not in the lease database";
    }

    // The following commands should have been sent to the server2: dhcp-disable,
    // lease4-get-all and dhcp-enable.
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-disable","20"));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("lease4-get-all",""));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-enable",""));
}

// This test verifies that an error is reported when sending a dhcp-disable
// command causes an error.
TEST_F(HAServiceTest, processSynchronizeDisableError) {
    // Setup the server2 to return an error to dhcp-disable commands.
    factory2_->getResponseCreator()->setControlResult("dhcp-disable",
                                                      CONTROL_RESULT_ERROR);

    // Run HAService::processSynchronize and gather a response.
    ConstElementPtr rsp;
    runProcessSynchronize4(rsp);

    // The response should indicate an error
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_ERROR);

    // The server2 should only receive dhcp-disable commands. Remaining two should
    // not be sent.
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-disable","20"));
    EXPECT_FALSE(factory2_->getResponseCreator()->findRequest("lease4-get-all",""));
    EXPECT_FALSE(factory2_->getResponseCreator()->findRequest("dhcp-enable",""));
}

// This test verifies that an error is reported when sending a lease4-get-all
// command causes an error.
TEST_F(HAServiceTest, processSynchronizeLease4GetAllError) {
    // Setup the server2 to return an error to dhcp-disable commands.
    factory2_->getResponseCreator()->setControlResult("lease4-get-all",
                                                      CONTROL_RESULT_ERROR);

    // Run HAService::processSynchronize and gather a response.
    ConstElementPtr rsp;
    runProcessSynchronize4(rsp);

    // The response should indicate an error
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_ERROR);

    // The server2 should receive all commands. The dhcp-disable was successful, so
    // the dhcp-enable command must be sent to re-enable the service after failure.
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-disable","20"));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("lease4-get-all",""));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-enable",""));
}

// This test verifies that an error is reported when sending a dhcp-enable
// command causes an error.
TEST_F(HAServiceTest, processSynchronizeEnableError) {
    // Setup the server2 to return an error to dhcp-disable commands.
    factory2_->getResponseCreator()->setControlResult("dhcp-enable",
                                                      CONTROL_RESULT_ERROR);

    // Run HAService::processSynchronize and gather a response.
    ConstElementPtr rsp;
    runProcessSynchronize4(rsp);

    // The response should indicate an error
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_ERROR);

    // The server2 should receive all commands.
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-disable","20"));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("lease4-get-all",""));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-enable",""));
}

// This test verifies that the ha-sync command is processed successfully for the
// DHCPv6 server.
TEST_F(HAServiceTest, processSynchronize6) {

    // Run HAService::processSynchronize and gather a response.
    ConstElementPtr rsp;
    runProcessSynchronize6(rsp);

    // The response should indicate success.
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_SUCCESS, "Lease database synchronization"
                " complete.");

    // All leases should have been inserted into the database.
    for (size_t i = 0; i < leases6_.size(); ++i) {
        Lease6Ptr existing_lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                                         leases6_[i]->addr_);
        ASSERT_TRUE(existing_lease) << "lease " << leases6_[i]->addr_.toText()
                                    << " not in the lease database";
    }

    // The following commands should have been sent to the server2: dhcp-disable,
    // lease6-get-all and dhcp-enable.
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-disable","20"));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("lease6-get-all",""));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-enable",""));
}

// This test verifies that an error is reported when sending a dhcp-disable
// command causes an error.
TEST_F(HAServiceTest, processSynchronize6DisableError) {
    // Setup the server2 to return an error to dhcp-disable commands.
    factory2_->getResponseCreator()->setControlResult("dhcp-disable",
                                                      CONTROL_RESULT_ERROR);

    // Run HAService::processSynchronize and gather a response.
    ConstElementPtr rsp;
    runProcessSynchronize6(rsp);

    // The response should indicate an error
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_ERROR);

    // The server2 should only receive dhcp-disable commands. Remaining two should
    // not be sent.
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-disable","20"));
    EXPECT_FALSE(factory2_->getResponseCreator()->findRequest("lease6-get-all",""));
    EXPECT_FALSE(factory2_->getResponseCreator()->findRequest("dhcp-enable",""));
}

// This test verifies that an error is reported when sending a lease6-get-all
// command causes an error.
TEST_F(HAServiceTest, processSynchronizeLease6GetAllError) {
    // Setup the server2 to return an error to dhcp-disable commands.
    factory2_->getResponseCreator()->setControlResult("lease6-get-all",
                                                      CONTROL_RESULT_ERROR);

    // Run HAService::processSynchronize and gather a response.
    ConstElementPtr rsp;
    runProcessSynchronize6(rsp);

    // The response should indicate an error
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_ERROR);

    // The server2 should receive all commands. The dhcp-disable was successful, so
    // the dhcp-enable command must be sent to re-enable the service after failure.
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-disable","20"));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("lease6-get-all",""));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-enable",""));
}

// This test verifies that an error is reported when sending a dhcp-enable
// command causes an error.
TEST_F(HAServiceTest, processSynchronize6EnableError) {
    // Setup the server2 to return an error to dhcp-disable commands.
    factory2_->getResponseCreator()->setControlResult("dhcp-enable",
                                                      CONTROL_RESULT_ERROR);

    // Run HAService::processSynchronize and gather a response.
    ConstElementPtr rsp;
    runProcessSynchronize6(rsp);

    // The response should indicate an error
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_ERROR);

    // The server2 should receive all commands.
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-disable","20"));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("lease6-get-all",""));
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-enable",""));
}

// This test verifies that the DHCPv4 service can be disabled on the remote server.
TEST_F(HAServiceTest, asyncDisable4) {
    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();

    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    TestHAService service(io_service_, network_state_, config_storage);

    // Send dhcp-disable command with max-period of 10 seconds.
    // When the transaction is finished, the IO service gets stopped.
    ASSERT_NO_THROW(service.asyncDisable("server3", 10,
                                         [this](const bool success,
                                                const std::string& error_message) {
        EXPECT_TRUE(success);
        EXPECT_TRUE(error_message.empty());
        io_service_->stop();
    }));

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(TEST_TIMEOUT));

    // The second server should not receive the command.
    EXPECT_FALSE(factory2_->getResponseCreator()->findRequest("dhcp-disable","10"));
    // The third server should receive the dhcp-disable command with the max-period
    // value of 10.
    EXPECT_TRUE(factory3_->getResponseCreator()->findRequest("dhcp-disable","10"));
}

// This test verifies that there is no exception thrown as a result of dhcp-disable
// command when the server is offline.
TEST_F(HAServiceTest, asyncDisable4ServerOffline) {
    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();

    TestHAService service(io_service_, network_state_, config_storage);

    // Send dhcp-disable command with max-period of 10 seconds.
    // When the transaction is finished, the IO service gets stopped.
    ASSERT_NO_THROW(service.asyncDisable("server2", 10,
                                         [this](const bool success,
                                                const std::string& error_message) {
        EXPECT_FALSE(success);
        EXPECT_FALSE(error_message.empty());
        io_service_->stop();
    }));

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(TEST_TIMEOUT));
}

// This test verifies that an error is returned when the remote server
// returns control status error.
TEST_F(HAServiceTest, asyncDisable4ControlResultError) {
    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();

    // Set the servers to return error code in response to the dhcp-enable
    // command.
    factory2_->getResponseCreator()->setControlResult(CONTROL_RESULT_ERROR);
    factory3_->getResponseCreator()->setControlResult(CONTROL_RESULT_ERROR);

    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    TestHAService service(io_service_, network_state_, config_storage);

    // Send dhcp-disable command with max-period of 10 seconds.
    // When the transaction is finished, the IO service gets stopped.
    ASSERT_NO_THROW(service.asyncDisable("server3", 10,
                                         [this](const bool success,
                                                const std::string& error_message) {
        EXPECT_FALSE(success);
        EXPECT_FALSE(error_message.empty());
        io_service_->stop();
    }));

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(TEST_TIMEOUT));
}

// This test verifies that the DHCPv4 service can be enabled on the remote server.
TEST_F(HAServiceTest, asyncEnable4) {
    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();

    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    TestHAService service(io_service_, network_state_, config_storage);

    // Send dhcp-enable command. When the transaction is finished,
    // the IO service gets stopped.
    ASSERT_NO_THROW(service.asyncEnable("server2", [this](const bool success,
                                                          const std::string& error_message) {
        EXPECT_TRUE(success);
        EXPECT_TRUE(error_message.empty());
        io_service_->stop();
    }));

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(TEST_TIMEOUT));

    // The second server should receive the dhcp-enable.
    EXPECT_TRUE(factory2_->getResponseCreator()->findRequest("dhcp-enable",""));
    // The third server should not receive the command.
    EXPECT_FALSE(factory3_->getResponseCreator()->findRequest("dhcp-enable",""));
}

// This test verifies that there is no exception thrown as a result of dhcp-enable
// command when the server is offline.
TEST_F(HAServiceTest, asyncEnable4ServerOffline) {
    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();

    TestHAService service(io_service_, network_state_, config_storage);

    // Send dhcp-enable command. When the transaction is finished,
    // the IO service gets stopped.
    ASSERT_NO_THROW(service.asyncEnable("server2", [this](const bool success,
                                                          const std::string& error_message) {
        EXPECT_FALSE(success);
        EXPECT_FALSE(error_message.empty());
        io_service_->stop();
    }));

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(TEST_TIMEOUT));
}

// This test verifies that an error is returned when the remote server
// returns control status error.
TEST_F(HAServiceTest, asyncEnable4ControlResultError) {
    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();

    // Set the servers to return error code in response to the dhcp-enable
    // command.
    factory2_->getResponseCreator()->setControlResult(CONTROL_RESULT_ERROR);
    factory3_->getResponseCreator()->setControlResult(CONTROL_RESULT_ERROR);

    // Start the servers.
    ASSERT_NO_THROW({
        listener_->start();
        listener2_->start();
        listener3_->start();
    });

    TestHAService service(io_service_, network_state_, config_storage);

    // Send dhcp-enable command. When the transaction is finished,
    // the IO service gets stopped.
    ASSERT_NO_THROW(service.asyncEnable("server2", [this](const bool success,
                                                          const std::string& error_message) {
        EXPECT_FALSE(success);
        EXPECT_FALSE(error_message.empty());
        io_service_->stop();
    }));

    // Run IO service to actually perform the transaction.
    ASSERT_NO_THROW(runIOService(TEST_TIMEOUT));
}

// This test verifies that the "ha-scopes" command is processed correctly.
TEST_F(HAServiceTest, processScopes) {
    // Create HA configuration.
    HAConfigPtr config_storage = createValidConfiguration();

    // Create HA service using this configuration.
    TestHAService service(io_service_, network_state_, config_storage);

    // Enable "server1" and "server2" scopes.
    ConstElementPtr rsp;
    ASSERT_NO_THROW(rsp = service.processScopes({ "server1", "server2" }));

    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_SUCCESS, "New HA scopes configured.");

    // Verify that "server1" and "server2" scopes are enabled.
    EXPECT_TRUE(service.query_filter_.amServingScope("server1"));
    EXPECT_TRUE(service.query_filter_.amServingScope("server2"));
    EXPECT_FALSE(service.query_filter_.amServingScope("server3"));

    // Enable "server2" scope only.
    ASSERT_NO_THROW(rsp = service.processScopes({ "server2" }));
    checkAnswer(rsp, CONTROL_RESULT_SUCCESS, "New HA scopes configured.");
    EXPECT_FALSE(service.query_filter_.amServingScope("server1"));
    EXPECT_TRUE(service.query_filter_.amServingScope("server2"));
    EXPECT_FALSE(service.query_filter_.amServingScope("server3"));

    // Clear scopes.
    ASSERT_NO_THROW(rsp = service.processScopes({ }));
    checkAnswer(rsp, CONTROL_RESULT_SUCCESS, "New HA scopes configured.");
    EXPECT_FALSE(service.query_filter_.amServingScope("server1"));
    EXPECT_FALSE(service.query_filter_.amServingScope("server2"));
    EXPECT_FALSE(service.query_filter_.amServingScope("server3"));

    // Unsupported scope.
    ASSERT_NO_THROW(rsp = service.processScopes({ "server1", "unsupported", "server3" }));
    checkAnswer(rsp, CONTROL_RESULT_ERROR, "invalid server name specified 'unsupported'"
                " while enabling/disabling HA scopes");
    // Even though the "server1" is a valid scope name, it should not be
    // enabled because we expect scopes enabling to be atomic operation,
    // i.e. all or nothing.
    EXPECT_FALSE(service.query_filter_.amServingScope("server1"));
    EXPECT_FALSE(service.query_filter_.amServingScope("server2"));
    EXPECT_FALSE(service.query_filter_.amServingScope("server3"));
}

// This test verifies that the ha-continue command is processed successfully.
TEST_F(HAServiceTest, processContinue) {
    HAConfigPtr config_storage = createValidConfiguration();

    // State machine is to be paused in the waiting state.
    ASSERT_NO_THROW(config_storage->getStateMachineConfig()->
                    getStateConfig(HA_WAITING_ST)->setPausing("always"));

    TestHAService service(io_service_, network_state_, config_storage);

    // Pause the state machine.
    EXPECT_NO_THROW(service.transition(HA_WAITING_ST, HAService::NOP_EVT));
    EXPECT_TRUE(service.isModelPaused());

    // Process ha-continue command that should unpause the state machine.
    ConstElementPtr rsp;
    ASSERT_NO_THROW(rsp = service.processContinue());

    // The server should have responded.
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_SUCCESS, "HA state machine continues.");

    // State machine should have been unpaused as a result of processing the
    // command.
    EXPECT_FALSE(service.isModelPaused());

    // Response should include no arguments.
    EXPECT_FALSE(rsp->get("arguments"));

    // Sending ha-continue command again which should return success but
    // slightly different textual status.
    ASSERT_NO_THROW(rsp = service.processContinue());

    // The server should have responded.
    ASSERT_TRUE(rsp);
    checkAnswer(rsp, CONTROL_RESULT_SUCCESS, "HA state machine is not paused.");

    // The state machine should not be paused.
    EXPECT_FALSE(service.isModelPaused());

    // Response should include no arguments.
    EXPECT_FALSE(rsp->get("arguments"));
}

/// @brief HA partner to the server under test.
///
/// This is a wrapper class around @c HttpListener which simulates a
/// partner server. It provides convenient methods to start, stop the
/// parter (its listener) and to transition the partner between various
/// HA states. Depending on the state and whether the partner is started
/// or stopped, different answers are returned in response to the
/// ha-heartbeat commands.
class HAPartner {
public:

    /// @brief Constructor.
    ///
    /// Creates the partner instance from a listner and the corresponding
    /// response factory. It automatically transitions the partner to the
    /// "waiting" state unless otherwise specified with the third parameter.
    ///
    /// @param listner pointer to the listner to be used.
    /// @param factory pointer to the response factory to be used. This
    /// must be the same factory that the listener is using.
    /// @param initial_state initial state for the partner. Default is to
    /// transition the partner to the "waiting" state which is the default
    /// state for each starting server.
    HAPartner(const HttpListenerPtr& listener,
              const TestHttpResponseCreatorFactoryPtr& factory,
              const std::string& initial_state = "waiting")
        : listener_(listener), factory_(factory), running_(false),
          static_date_time_() {
        transition(initial_state);
    }

    /// @brief Sets control result to be returned as a result of the
    /// communication with the partner.
    ///
    /// @param control_result new control result value.
    void setControlResult(const int control_result) {
        factory_->getResponseCreator()->setControlResult(control_result);
    }

    /// @brief Sets static date-time value to be used in responses.
    ///
    /// @param static_date_time fixed date-time value.
    void setDateTime(const std::string& static_date_time) {
        static_date_time_ = static_date_time;
    }

    /// @brief Enable response to commands required for leases synchronization.
    ///
    /// Enables dhcp-disable, dhcp-enable and lease4-get-all commands. The last
    /// of them returns a bunch of test leases.
    void enableRespondLeaseFetching() {
        // Create IPv4 leases which will be fetched from the other server.
        std::vector<Lease4Ptr> leases4;
        ASSERT_NO_THROW(generateTestLeases(leases4));

        // Convert leases to the JSON format, the same as used by the lease_cmds
        // hook library. Configure our test HTTP servers to return those
        // leases in this format.
        ElementPtr response_arguments = Element::createMap();
        response_arguments->set("leases", getLeasesAsJson(leases4));

        factory_->getResponseCreator()->setArguments("lease4-get-all", response_arguments);
    }

    /// @brief Starts up the partner.
    void startup() {
        if (!running_) {
            listener_->start();
            running_ = true;
        }
    }

    /// @brief Shuts down the partner.
    ///
    /// It may be used to simulate partner's crash as well as graceful
    /// shutdown.
    void shutdown() {
        if (running_) {
            listener_->stop();
            running_ = false;
        }
    }

    /// @brief Transitions the partner to the specified state.
    ///
    /// The state is provided in the textual form and the function doesn't
    /// validate whether it is correct or not.
    ///
    /// @param state new partner state.
    void transition(const std::string& state) {
        ElementPtr response_arguments = Element::createMap();
        response_arguments->set("state", Element::create(state));
        if (!static_date_time_.empty()) {
            response_arguments->set("date-time", Element::create(static_date_time_));
        }
        factory_->getResponseCreator()->setArguments(response_arguments);
    }


private:

    /// @brief Instance of the listener wrapped by this class.
    HttpListenerPtr listener_;
    /// @brief Instance of the response factory used by the listener.
    TestHttpResponseCreatorFactoryPtr factory_;

    /// @brief IPv4 leases to be used in the tests.
    std::vector<Lease4Ptr> leases4_;

    /// @brief Boolean flag indicating if the partner is running.
    bool running_;

    /// @brief Static date-time value to be returned.
    std::string static_date_time_;
};

/// @brief Shared pointer to a partner.
typedef boost::shared_ptr<HAPartner> HAPartnerPtr;

/// @brief Test fixture class for the HA service state machine.
class HAServiceStateMachineTest : public HAServiceTest {
public:
    /// @brief Constructor.
    HAServiceStateMachineTest()
        : HAServiceTest(), service_(), state_(),
          partner_(new HAPartner(listener2_, factory2_)) {
    }

    /// @brief Creates common HA service instance from the provided configuration.
    ///
    /// The custom @c state_ object is created and it replaces the default
    /// @c state_ object of the HA service.
    ///
    /// @param config pointer to the configuration to be used by the service.
    /// @param server_type server type, i.e. DHCPv4 or DHCPv6.
    void startService(const HAConfigPtr& config,
                      const HAServerType& server_type = HAServerType::DHCPv4) {
        config->setHeartbeatDelay(1);
        service_.reset(new TestHAService(io_service_, network_state_, config,
                                         server_type));
        // Replace default communication state with custom state which exposes
        // protected members and methods.
        state_.reset(new NakedCommunicationState4(io_service_, config));
        service_->communication_state_ = state_;
        // Move the state machine from initial state to "waiting" state.
        service_->runModel(HAService::NOP_EVT);
    }

    /// @brief Runs IO service until specified event occurs.
    ///
    /// This method runs IO service until state machine is run as a result
    /// of receiving a response to an IO operation. IO operations such as
    /// lease updates, heartbeats etc. trigger state machine changes.
    /// We can capture certain events to detect when a response to the heartbeat
    /// or other control commands  is received. This is useful to return control
    /// to a test to verify that the state machine remains in the expected state
    /// after receiving such response.
    ///
    /// @param event an event which should trigger IO service to stop.
    void waitForEvent(const int event) {
        ASSERT_NE(event, HAService::NOP_EVT);

        service_->postNextEvent(HAService::NOP_EVT);

        // Run IO service until the event occurs.
        runIOService(TEST_TIMEOUT, [this, event]() {
            return (service_->getLastEvent() == event);
        });

        service_->postNextEvent(HAService::NOP_EVT);
    }

    /// @brief Convenience method checking if HA service is currently running
    /// recurring heartbeat.
    ///
    /// @return true if the heartbeat is run.
    bool isDoingHeartbeat() {
        return (state_->isHeartbeatRunning());
    }

    /// @brief Convenience method checking if HA service has detected communications
    /// interrupted condition.
    ///
    /// @return true if the communications interrupted condition deemed, false
    /// otherwise.
    bool isCommunicationInterrupted() {
        return (state_->isCommunicationInterrupted());
    }

    /// @brief Convenience method checking if communication failure has been
    /// detected by the HA service based on the analysis of the DHCP traffic.
    ///
    /// @return true if the communication failure is deemed, false otherwise.
    bool isFailureDetected() {
        return (state_->failureDetected());
    }

    /// @brief Simulates a case when communication with the partner has failed
    /// for a time long enough to assume communications interrupted condition.
    ///
    /// This case is simulated by modifying the last poking time far into the
    /// past.
    void simulateNoCommunication() {
        state_->modifyPokeTime(-1000);
    }

    /// @brief Simulates reception of unanswered DHCP queries by the partner.
    ///
    /// This case is simulated by creating a large number of queries with
    /// secs field set to high value.
    void simulateDroppedQueries() {
        // Create 100 packets. Around 50% of them should be assigned to the
        // partner if load balancing is performed.
        const unsigned queries_num = 100;
        for (unsigned i = 0; i < queries_num; ++i) {
            // Create query with random HW address.
            Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));
            // Set large secs field value.
            query4->setSecs(0x00EF);
            // This function, besides checking if the query is in scope,
            // updates unanswered message counters. If the counters exceed
            // a configured value the communication failure is assumed.
            static_cast<void>(service_->inScope(query4));
        }
        // The state machine needs to react to the dropped queries. Therefore
        // we run the machine now.
        service_->runModel(HAService::NOP_EVT);
    }

    /// @brief Checks transitions dependent on the partner's state.
    ///
    /// This method uses @c partner_ object to control the state of the partner.
    /// This method must not be used to test transitions from the syncing state
    /// because this state includes synchronous IO operations. There is a
    /// separate test for the transitions from the syncing state.
    ///
    /// @param my_state initial state of this server.
    /// @param partner_state state of the partner.
    /// @param final_state expected state to transition to.
    void testTransition(const MyState& my_state, const PartnerState& partner_state,
                        const FinalState& final_state) {
        // We need to shutdown the partner only if the partner is to be in the
        // 'unavailable state'.
        if (partner_state.state_ != HA_UNAVAILABLE_ST) {
            // This function is not meant for testing transitions from the syncing
            // state when partner is available.
            ASSERT_NE(my_state.state_, HA_SYNCING_ST);
            partner_->setControlResult(CONTROL_RESULT_SUCCESS);

        } else {
            partner_->setControlResult(CONTROL_RESULT_ERROR);
        }

        // Transition this server to the desired initial state.
        service_->transition(my_state.state_, HAService::NOP_EVT);
        // Transition the partner to the desired state.
        partner_->transition(service_->getStateLabel(partner_state.state_));
        // Run the heartbeat.
        waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT);
        // Make sure that this server ended up in the expected state.
        EXPECT_EQ(final_state.state_, service_->getCurrState())
            << "expected transition to the '"
            << service_->getStateLabel(final_state.state_)
            << "' state for the partner state '" << service_->getStateLabel(partner_state.state_)
            << "', but transitioned to the '"
            << service_->getStateLabel(service_->getCurrState())
            << "' state";

        // If the partner is unavailable we also have to verify the case when
        // we detect that the partner is considered offline (after running the
        // whole failure detection algorithm).
        if (partner_state.state_ == HA_UNAVAILABLE_ST) {
            // Transition this server back to the initial state.
            service_->transition(my_state.state_, HAService::NOP_EVT);
            // Simulate lack of communication between the servers.
            simulateNoCommunication();
            // Send the heartbeat again.
            waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT);

            // The load balancing server or the standby server is monitoring the stream
            // of packets directed to the partner to detect delays in responses. The
            // primary server in the hot standby configuration doesn't do it, because
            // the partner is not meant to process any queries until it detects that
            // the primary server is down. This is only done in states in which the
            // DHCP service is enabled. Otherwise, the server doesn't receive DHCP
            // queries it could analyze.
            if (service_->network_state_->isServiceEnabled() &&
                ((service_->config_->getHAMode() == HAConfig::LOAD_BALANCING) ||
                 service_->config_->getThisServerConfig()->getRole() == HAConfig::PeerConfig::STANDBY)) {
                // The server should remain in its current state until we also detect
                // that the partner is not answering the queries.
                ASSERT_EQ(final_state.state_, service_->getCurrState())
                    << "expected transition to the '"
                    << service_->getStateLabel(final_state.state_)
                    << "' state for the partner state '" << service_->getStateLabel(partner_state.state_)
                    << "', but transitioned to the '"
                    << service_->getStateLabel(service_->getCurrState())
                    << "' state";

                // Back to the original state again.
                service_->transition(my_state.state_, HAService::NOP_EVT);
                // This time simulate no responses from the partner to the DHCP clients'
                // requests. This should cause the server to transition to the partner
                // down state regardless of the initial state.
                simulateDroppedQueries();
                waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT);
                EXPECT_EQ(HA_PARTNER_DOWN_ST, service_->getCurrState())
                    << "expected transition to the 'partner-down' state, but transitioned"
                    " to the '" << service_->getStateLabel(service_->getCurrState())
                    << "' state";

            // The primary server in the hot-standby configuration should transition to
            // the partner-down state when there is no communication with the partner
            // over the control channel.
            } else {
                EXPECT_EQ(HA_PARTNER_DOWN_ST, service_->getCurrState())
                    << "expected transition to the 'partner-down' state, but transitioned"
                    " to the '" << service_->getStateLabel(service_->getCurrState())
                    << "' state";
            }
        }
    }

    /// @brief Checks transitions from the syncing state.
    ///
    /// This method uses @c partner_ object to control the state of the partner.
    ///
    /// @param final_state expected final server state.
    void testSyncingTransition(const FinalState& final_state) {
        // Transition to the syncing state.
        service_->transition(HA_SYNCING_ST, HAService::NOP_EVT);
        partner_->transition("ready");
        state_->stopHeartbeat();

        testSynchronousCommands([this]() {
            service_->runModel(HAService::NOP_EVT);
        });

        state_->stopHeartbeat();

        EXPECT_EQ(final_state.state_, service_->getCurrState())
            << "expected transition to the '"
            << service_->getStateLabel(final_state.state_)
            << "' state" << ", but transitioned to the '"
            << service_->getStateLabel(service_->getCurrState())
            << "' state";
    }

    /// @brief Tests transition from any state to "terminated".
    ///
    /// @pasram my_state initial server state.
    void testTerminateTransition(const MyState& my_state) {
        // Set the partner's time way in the past so as the clock skew gets high.
        partner_->setDateTime("Sun, 06 Nov 1994 08:49:37 GMT");
        partner_->transition("ready");
        // Transition this server to the desired initial state.
        service_->transition(my_state.state_, HAService::NOP_EVT);
        // Run the heartbeat.
        waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT);
        // The server should get into terminated state because of the high
        // clock skew.
        EXPECT_EQ(HA_TERMINATED_ST, service_->getCurrState())
            << "expected transition to the 'terminated' state"
            << "', but transitioned to the '"
            << service_->getStateLabel(service_->getCurrState())
            << "' state";
    }

    /// @brief Test that the server is serving expected scopes while being in a
    /// certain state.
    ///
    /// @param my_state state of the server.
    /// @param scopes vector of scopes which the server is expected to handle in this
    /// state.
    /// @param dhcp_enabled Indicates whether DHCP service is expected to be enabled
    /// or disabled in the given state.
    void expectScopes(const MyState& my_state, const std::vector<std::string>& scopes,
                      const bool dhcp_enabled) {

        // If expecting no scopes, let's enable some scope to make sure that the
        // code changes this setting.
        if (scopes.empty()) {
            service_->query_filter_.serveScope("server1");

        } else {
            // If expecting some scopes, let's initially clear the scopes to make
            // sure that the code sets it.
            service_->query_filter_.serveNoScopes();
        }

        // Also, let's preset the DHCP server state to the opposite of the expected
        // state.
        if (dhcp_enabled) {
            service_->network_state_->disableService();

        } else {
            service_->network_state_->enableService();
        }

        // Transition to the desired state.
        service_->verboseTransition(my_state.state_);
        // Run the handler.
        service_->runModel(TestHAService::NOP_EVT);
        // First, check that the number of handlded scope is equal to the number of
        // scopes specified as an argument.
        ASSERT_EQ(scopes.size(), service_->query_filter_.getServedScopes().size())
                << "test failed for state '" << service_->getStateLabel(my_state.state_)
                << "'";

        // Now, verify that each specified scope is handled.
        for(auto scope : scopes) {
            EXPECT_TRUE(service_->query_filter_.amServingScope(scope))
                << "test failed for state '" << service_->getStateLabel(my_state.state_)
                << "'";
        }
        // Verify if the DHCP service is enabled or disabled.
        EXPECT_EQ(dhcp_enabled, service_->network_state_->isServiceEnabled())
            << "test failed for state '" << service_->getStateLabel(my_state.state_)
            << "'";
    }

    /// @brief Transitions the server to the specified state and checks if the
    /// HA service would send lease updates in this state.
    ///
    /// @param my_state this server's state
    /// @param peer_config configuration of the server to which lease updates are
    /// to be sent.
    /// @return true if the lease updates would be sent, false otherwise.
    bool expectLeaseUpdates(const MyState& my_state,
                            const HAConfig::PeerConfigPtr& peer_config) {
        service_->verboseTransition(my_state.state_);
        return (service_->shouldSendLeaseUpdates(peer_config));
    }

    /// @brief Transitions the server to the specified state and checks if the
    /// HA service is sending heartbeat in this state.
    ///
    /// @param my_state this server's state
    /// @return true if the heartbeat is sent in this state, false otherwise.
    bool expectHeartbeat(const MyState& my_state) {
        service_->verboseTransition(my_state.state_);
        service_->runModel(TestHAService::NOP_EVT);
        return (isDoingHeartbeat());
    }

    /// @brief Pointer to the HA service under test.
    TestHAServicePtr service_;
    /// @brief Pointer to the communication state used in the tests.
    NakedCommunicationState4Ptr state_;
    /// @brief Pointer to the partner used in some tests.
    HAPartnerPtr partner_;
};


// Test the following scenario:
// 1. I show up in waiting state and look around
// 2. My partner doesn't respond over control channel
// 3. I start analyzing partner's packets and see that
//    it doesn't respond.
// 4. I transition to partner down state.
// 5. Partner finally shows up and eventually transitions to the ready state.
// 6. I see the partner being ready, so I fall back to load balancing.
// 7. Next, the partner crashes again.
// 8. I detect partner's crash and transition back to partner down.
// 9. While being in the partner down state, we find that the partner
//    is available and it is doing load balancing.
// 10. Our server transitions to the waiting state to synchronize the
//    database and then transition to the load balancing state.
TEST_F(HAServiceStateMachineTest, waitingParterDownLoadBalancingPartnerDown) {
    // Start the server: offline ---> WAITING state.
    startService(createValidConfiguration());
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());

    // WAITING state: no heartbeat response for a long period of time.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    simulateNoCommunication();
    ASSERT_TRUE(isDoingHeartbeat());

    // WAITING state: communication interrupted. In this state we don't analyze
    // packets ('secs' field) because the DHCP service is disabled.
    // WAITING ---> PARTNER DOWN
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_PARTNER_DOWN_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());

    // PARTNER DOWN state: still no response from the partner.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_PARTNER_DOWN_ST, service_->getCurrState());

    // Partner shows up and (eventually) transitions to READY state.
    HAPartner partner(listener2_, factory2_, "ready");
    partner.startup();

    // PARTNER DOWN state: receive a response from the partner indicating that
    // the partner is in READY state.
    // PARTNER DOWN ---> LOAD BALANCING
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_LOAD_BALANCING_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_FALSE(isCommunicationInterrupted());
    ASSERT_FALSE(isFailureDetected());

    // Crash the partner and see whether our server can return to the partner
    // down state.
    partner.setControlResult(CONTROL_RESULT_ERROR);

    // LOAD BALANCING state: wait for the next heartbeat to occur and make
    // sure that a single heartbeat loss is not yet causing us to assume
    // partner down condition.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_LOAD_BALANCING_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_FALSE(isCommunicationInterrupted());
    ASSERT_FALSE(isFailureDetected());

    // LOAD BALANCING state: simulate lack of communication for a longer
    // period of time. We should still be in the load balancing state
    // because we still need to wait for unanswered DHCP traffic.
    simulateNoCommunication();
    EXPECT_EQ(HA_LOAD_BALANCING_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_TRUE(isCommunicationInterrupted());
    ASSERT_FALSE(isFailureDetected());

    // LOAD BALANCING state: simulate a lot of unanswered DHCP messages to
    // the partner. This server should detect that the partner is not
    // answering and transition to partner down state.
    // LOAD BALANCING ---> PARTNER DOWN
    simulateDroppedQueries();
    EXPECT_EQ(HA_PARTNER_DOWN_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_TRUE(isCommunicationInterrupted());
    ASSERT_TRUE(isFailureDetected());

    // Start the partner again and transition it to the load balancing state.
    partner.setControlResult(CONTROL_RESULT_SUCCESS);
    partner.transition("load-balancing");

    // PARTNER DOWN state: it is weird situation that the partner shows up in
    // the load-balancing state, but you can't really preclude that. Our server
    // would rather expect it to be in the waiting or syncing state after being
    // down but we need to deal with any status returned. If the other server
    // is doing load balancing then the queries sent to our server aren't
    // handled. Since this is so unusual situation we transition to the waiting
    // state to synchronize the database and gracefully transition to the load
    // balancing state.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_FALSE(isCommunicationInterrupted());
    ASSERT_FALSE(isFailureDetected());
}

// Test the following scenario:
// 1. I show up in waiting state and look around.
// 2. My partner is offline and is not responding over the control channel.
// 3. I can't communicate with the partner so I transition to the partner-down
//    state.
// 4. Partner shows up and eventually transitions to the ready state.
// 5. I can communicate with the partner so I transition to the hot-standby
//    state as a standby server.
// 6. Patrtner stops responding again.
// 7. I monitor communication with the partner and eventually consider the
//    communication to be interrupted.
// 8. I start monitoring the DHCP traffic directed to the partner and observe
//    delays in responses.
// 9. I transition to the partner-down state again seeing that the certain
//    number of clients can't communicate with the partner.
// 10. The partner unexpectedly shows up in the hot-standby mode, which causes
//     me to transition to the waiting state and then synchronize my lease
//     database.
TEST_F(HAServiceStateMachineTest, waitingParterDownHotStandbyPartnerDown) {
    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setThisServerName("server2");
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    // Start the server: offline ---> WAITING state.
    startService(valid_config);

    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());

    // WAITING state: no heartbeat reponse for a long period of time.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    simulateNoCommunication();
    ASSERT_TRUE(isDoingHeartbeat());

    // WAITING state: communication interrupted. In this state we don't analyze
    // packets ('secs' field) because the DHCP service is disabled.
    // WAITING ---> PARTNER DOWN
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_PARTNER_DOWN_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());

    // PARTNER DOWN state: still no response from the partner.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_PARTNER_DOWN_ST, service_->getCurrState());

    // Partner shows up and (eventually) transitions to READY state.
    partner_.reset(new HAPartner(listener_, factory_, "ready"));
    partner_->startup();

    // PARTNER DOWN state: receive a response from the partner indicating that
    // the partner is in READY state.
    // PARTNER DOWN ---> HOT STANDBY
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_HOT_STANDBY_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_FALSE(isCommunicationInterrupted());
    ASSERT_FALSE(isFailureDetected());

    // Crash the partner and see whether our server can return to the partner
    // down state.
    partner_->setControlResult(CONTROL_RESULT_ERROR);

    // HOT STANDBY state: wait for the next heartbeat to occur and make
    // sure that a single heartbeat loss is not yet causing us to assume
    // partner down condition.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_HOT_STANDBY_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_FALSE(isCommunicationInterrupted());
    ASSERT_FALSE(isFailureDetected());

    // HOT STANDBY state: simulate lack of communication for a longer
    // period of time. We should still be in the hot standby state
    // because we still need to wait for unanswered DHCP traffic.
    simulateNoCommunication();
    EXPECT_EQ(HA_HOT_STANDBY_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_TRUE(isCommunicationInterrupted());
    ASSERT_FALSE(isFailureDetected());

    // HOT STANDBY state: simulate a lot of unanswered DHCP messages to
    // the partner. This server should detect that the partner is not
    // answering and transition to partner down state.
    // HOT STANDBY ---> PARTNER DOWN
    simulateDroppedQueries();
    EXPECT_EQ(HA_PARTNER_DOWN_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_TRUE(isCommunicationInterrupted());
    ASSERT_TRUE(isFailureDetected());

    // Start the partner again and transition it to the hot standby state.
    partner_->setControlResult(CONTROL_RESULT_SUCCESS);
    partner_->transition("hot-standby");

    // HOT STANDBY state: it is weird situation that the partner shows up in
    // the hot-standby state, but you can't really preclude that. Our server
    // would rather expect it to be in the waiting or syncing state after being
    // down but we need to deal with any status returned. If the other server
    // is in hot standby then the queries sent to our server aren't handled.
    // Since this is so unusual situation we transition to the waiting
    // state to synchronize the database and gracefully transition to the hot
    // standby state.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());
    ASSERT_TRUE(isDoingHeartbeat());
    ASSERT_FALSE(isCommunicationInterrupted());
    ASSERT_FALSE(isFailureDetected());
}

// Test the following scenario:
// 1. I show up in the waiting state.
// 2. My partner appears to be in the partner-down state.
// 3. I proceed to the syncing state to fetch leases from the partner.
// 4. The first attempt to fetch leases is unsuccessful.
// 5. I remain in the syncing state until I am finally successful.
// 6. I proceed to the ready state.
// 7. I see that the partner is still in partner-down state, so I
//    wait for the partner to transition to load-balancing state.
TEST_F(HAServiceStateMachineTest, waitingSyncingReadyLoadBalancing) {
    // Partner is present and is in the PARTNER DOWN state.
    HAPartner partner(listener2_, factory2_, "partner-down");
    partner.startup();

    // Start the server: offline ---> WAITING state.
    startService(createValidConfiguration());
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());

    // WAITING state: receive a response from the partner indicating that the
    // partner is in the load balancing state. I should transition to the
    // SYNCING state to fetch leases from the partner.
    // WAITING ---> SYNCING state
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_SYNCING_ST, service_->getCurrState());

    // We better stop the heartbeat to not interfere with the synchronous
    // commands.
    state_->stopHeartbeat();

    // The database synchronization is synchronous operation so we need to run
    // the partner's IO service in thread (in background).
    testSynchronousCommands([this, &partner]() {

        // SYNCING state: the partner is up but it won't respond to the lease4-get-all
        // command correctly. This should leave us in the SYNCING state until we finally
        // can synchronize.
        service_->runModel(HAService::NOP_EVT);
        EXPECT_EQ(HA_SYNCING_ST, service_->getCurrState());

        // Enable the partner to correctly respond to the lease fetching and retry.
        // We should successfully update the database and transition.
        // SYNCING ---> READY
        partner.enableRespondLeaseFetching();
        // After previous attempt to synchronize the recorded partner state became
        // "unavailable". This server won't synchronize until the heartbeat is
        // sent which would indicate that the server is running. Therefore, we
        // manually set the state of the partner to "partner-down".
        state_->setPartnerState("partner-down");
        service_->runModel(HAService::NOP_EVT);
        EXPECT_EQ(HA_READY_ST, service_->getCurrState());
    });

    // READY state: I do another heartbeat but my partner still seems to be in the
    // partner down state, so I can't transition to load balancing just yet. I
    // still remain the READY state.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_READY_ST, service_->getCurrState());

    // READY state: partner transitions to the LOAD BALANCING state seeing that I
    // am ready. I should see this transition and also transition to that state.
    // READY ---> LOAD BALANCING.
    partner.transition("load-balancing");
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_LOAD_BALANCING_ST, service_->getCurrState());
}

// Test the following scenario:
// 1. I am a primary server which is started at the same time as secondary.
// 2. I determine that we're the primary server so I go ahead and start
//    synchronizing.
// 3. Partner should also determine that it is a secondary server so it should
//    remain in the waiting state until we're ready.
// 4. I synchronize the database and transition to the ready state.
// 5. The partner should see that I am ready and should start the transition.
// 6. I remain ready until the partner gets to the ready state.
// 7. I transition to the load balancing state when the partner is ready.
// 8. The partner transitions to the load balancing state which doesn't
//    affect my state.
TEST_F(HAServiceStateMachineTest, waitingSyncingReadyLoadBalancingPrimary) {
    // Partner is present and is in the WAITING state.
    HAPartner partner(listener2_, factory2_);
    partner.enableRespondLeaseFetching();
    partner.startup();

    // Start the server: offline ---> WAITING state.
    startService(createValidConfiguration());
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());

    // WAITING state: both servers are in this state but our server is primary,
    // so it transitions to the syncing state. The peer remains in the WAITING
    // state until we're ready.
    // WAITING --->SYNCING
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_SYNCING_ST, service_->getCurrState());

    // We better stop the heartbeat to not interfere with the synchronous
    // commands.
    state_->stopHeartbeat();

    // SYNCING state: this server will synchronously fetch leases from the peer.
    // Therefore, we need to run the IO service in the thread to allow for
    // synchronous operations to complete. Once the leases are fetched it should
    // transition to the READY state.
    // SYNCING ---> READY.
    testSynchronousCommands([this]() {
        service_->runModel(HAService::NOP_EVT);
        EXPECT_EQ(HA_READY_ST, service_->getCurrState());
    });

    // READY state: our partner sees that we're ready so it will start to
    // synchronize. We reamain the READY state as long as the partner is not
    // ready.
    partner.transition("syncing");
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_READY_ST, service_->getCurrState());

    // READY state: our partner appears to be ready. We can now start load
    // balancing.
    // READY ---> LOAD BALANCING.
    partner.transition("ready");
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_LOAD_BALANCING_ST, service_->getCurrState());

    // LOAD BALANCING state: our partner should eventually transition to the
    // LOAD BALANCING state. This should not affect us doing load balancing.
    partner.transition("load-balancing");
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_LOAD_BALANCING_ST, service_->getCurrState());
}

// Test the following scenario:
// 1. I am secondary server configured for load balancing and started at the
//    same time as the primary server.
// 2. I determine that I am a secondary server, so I remain in the waiting
//    state until the primary server indicates that it is ready.
// 3. I start synchronizing my lease database when the partner is ready.
// 4. I transition to the ready state and leave in that state until I see
//    the primary transition to the load balancing state.
// 5. I also transition to the load balancing state at that point.
TEST_F(HAServiceStateMachineTest, waitingSyncingReadyLoadBalancingSecondary) {
    // Partner is present and is in the WAITING state.
    HAPartner partner(listener_, factory_);
    partner.enableRespondLeaseFetching();
    partner.startup();

    // Create the configuration in which we're the secondary server doing
    // load balancing.
    HAConfigPtr valid_config = createValidConfiguration();
    valid_config->setThisServerName("server2");

    // Start the server: offline ---> WAITING state.
    startService(valid_config);
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());

    // WAITING state: our partner is a primary so we remain in the WAITING state
    // until it indicates it is ready.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());

    // WAITING state: the partner is synchronizing the lease database. We still
    // remain in the WAITING state.
    partner.transition("syncing");
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_WAITING_ST, service_->getCurrState());

    // WAITING state: partner transitions to the READY state. This is a signal
    // for us to start synchronization of the lease database.
    // WAITING ---> SYNCING.
    partner.transition("ready");
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_SYNCING_ST, service_->getCurrState());

    // We better stop the heartbeat to not interfere with the synchronous
    // commands.
    state_->stopHeartbeat();

    // SYNCING state: this server will synchronously fetch leases from the peer.
    // Therefore, we need to run the IO service in the thread to allow for
    // synchronous operations to complete. Once the leases are fetched it should
    // transition to the READY state.
    // SYNCING ---> READY.
    testSynchronousCommands([this]() {
        service_->runModel(HAService::NOP_EVT);
        EXPECT_EQ(HA_READY_ST, service_->getCurrState());
    });

    // READY state: we remain ready until the other server transitions to the
    // LOAD BALANCING state.
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_READY_ST, service_->getCurrState());

    // READY state: our primary server transitions to the LOAD BALANCING state.
    // We can now also transition to this state.
    // READY ---> LOAD BALANCING.
    partner.transition("load-balancing");
    ASSERT_NO_FATAL_FAILURE(waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT));
    EXPECT_EQ(HA_LOAD_BALANCING_ST, service_->getCurrState());
}

// This test checks all combinations of server and partner states and the
// resulting state to which the server transitions. This server is primary.
// There is another test which validates state transitions from the
// secondary server perspective.
TEST_F(HAServiceStateMachineTest, stateTransitionsLoadBalancingPrimary) {
    partner_->startup();

    startService(createValidConfiguration());

    // LOAD BALANCING state transitions
    {
        SCOPED_TRACE("LOAD BALANCING state transitions");

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_LOAD_BALANCING_ST));
    }

    // PARTNER DOWN state transitions
    {
        SCOPED_TRACE("PARTNER DOWN state transitions");

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_PARTNER_DOWN_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_PARTNER_DOWN_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_PARTNER_DOWN_ST));
    }

    // READY state transitions
    {
        SCOPED_TRACE("READY state transitions");

        testTransition(MyState(HA_READY_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_READY_ST));
    }

    // WAITING state transitions
    {
        SCOPED_TRACE("WAITING state transitions");

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_WAITING_ST));
    }
}

// This test checks that the server in the load balancing mode does not
// transition to the "syncing" state when "sync-leases" is disabled.
TEST_F(HAServiceStateMachineTest, noSyncingTransitionsLoadBalancingPrimary) {
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();
    valid_config->setSyncLeases(false);
    startService(valid_config);

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                   FinalState(HA_READY_ST));

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                   FinalState(HA_READY_ST));

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_READY_ST),
                   FinalState(HA_READY_ST));
}

// This test checks that the server in the load balancing mode transitions to
// the "terminated" state when the clock skew gets high.
TEST_F(HAServiceStateMachineTest, terminateTransitionsLoadBalancingPrimary) {
    partner_->startup();

    startService(createValidConfiguration());

    testTerminateTransition(MyState(HA_LOAD_BALANCING_ST));
    testTerminateTransition(MyState(HA_PARTNER_DOWN_ST));
    testTerminateTransition(MyState(HA_READY_ST));
    testTerminateTransition(MyState(HA_WAITING_ST));
}

// This test checks all combinations of server and partner states and the
// resulting state to which the server transitions. This server is secondary.
// There is another test which validates state transitions from the
// primary server perspective.
TEST_F(HAServiceStateMachineTest, stateTransitionsLoadBalancingSecondary) {
    partner_.reset(new HAPartner(listener_, factory_));
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();
    valid_config->setThisServerName("server2");
    startService(valid_config);

    partner_->startup();

    // LOAD BALANCING state transitions
    {
        SCOPED_TRACE("LOAD BALANCING state transitions");

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_UNAVAILABLE_ST),
                         FinalState(HA_LOAD_BALANCING_ST));
    }

    // PARTNER DOWN state transitions
    {
        SCOPED_TRACE("PARTNER DOWN state transitions");

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_PARTNER_DOWN_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_PARTNER_DOWN_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_PARTNER_DOWN_ST));
    }

    // READY state transitions
    {
        SCOPED_TRACE("READY state transitions");

        testTransition(MyState(HA_READY_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_LOAD_BALANCING_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_READY_ST));
    }

    // WAITING state transitions
    {
        SCOPED_TRACE("WAITING state transitions");

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_WAITING_ST));
    }
}

// This test checks that the server in the load balancing mode does not
// transition to the "syncing" state when "sync-leases" is disabled.
// This is the secondary server case.
TEST_F(HAServiceStateMachineTest, noSyncingTransitionsLoadBalancingSecondary) {
    partner_.reset(new HAPartner(listener_, factory_));
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();
    valid_config->setThisServerName("server2");
    valid_config->setSyncLeases(false);
    startService(valid_config);

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                   FinalState(HA_READY_ST));

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                   FinalState(HA_READY_ST));

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_READY_ST),
                   FinalState(HA_READY_ST));
}

// This test checks that the secondary server in the load balancing mode
// transitions to the "terminated" state when the clock skew gets high.
TEST_F(HAServiceStateMachineTest, terminateTransitionsLoadBalancingSecondary) {
    partner_.reset(new HAPartner(listener_, factory_));
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();
    valid_config->setThisServerName("server2");
    startService(valid_config);

    testTerminateTransition(MyState(HA_LOAD_BALANCING_ST));
    testTerminateTransition(MyState(HA_PARTNER_DOWN_ST));
    testTerminateTransition(MyState(HA_READY_ST));
    testTerminateTransition(MyState(HA_WAITING_ST));
}

// This test verifies that the backup server transitions to its own state.
TEST_F(HAServiceStateMachineTest, stateTransitionsLoadBalancingBackup) {
    HAConfigPtr valid_config = createValidConfiguration();

    // server3 is marked as a backup server.
    valid_config->setThisServerName("server3");
    startService(valid_config);

    // The server should transition to the backup state and stay there.
    for (unsigned i = 0; i < 10; ++i) {
        service_->runModel(HAService::NOP_EVT);
        ASSERT_EQ(HA_BACKUP_ST, service_->getCurrState());
        // In the backup state the DHCP service is disabled by default.
        // It can only be enabled manually.
        ASSERT_FALSE(service_->network_state_->isServiceEnabled());
        ASSERT_EQ(0, service_->query_filter_.getServedScopes().size());
    }
}

// This test verifies transitions from the syncing state in the load
// balancing configuration.
TEST_F(HAServiceStateMachineTest, syncingTransitionsLoadBalancing) {
    HAConfigPtr valid_config = createValidConfiguration();
    startService(valid_config);
    waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT);

    // The syncing state handler doesn't start synchronization until it
    // detects that the partner is online. It may remember that from the
    // previous heartbeat attempts. If the partner appears to be unavailable
    // it will continue heartbeats before it synchronizes. This prevents the
    // server from making endless attempts to synchronize without any chance
    // to succeed. We verify that the server is not trying to synchronize
    // by checking that the last event is not the one associated with the
    // synchronization attempt.
    ASSERT_NE(service_->getLastEvent(), HAService::HA_SYNCING_FAILED_EVT);
    ASSERT_NE(service_->getLastEvent(), HAService::HA_SYNCING_SUCCEEDED_EVT);

    // Run the syncing state handler.
    testSyncingTransition(FinalState(HA_SYNCING_ST));

    // We should see no synchronization attempts because the partner is
    // offline.
    EXPECT_NE(service_->getLastEvent(), HAService::HA_SYNCING_FAILED_EVT);
    EXPECT_NE(service_->getLastEvent(), HAService::HA_SYNCING_SUCCEEDED_EVT);

    // Startup the partner.
    partner_->enableRespondLeaseFetching();
    partner_->startup();

    // We haven't been running heartbeats so we have to manually set the
    // partner's state to something other than 'unavailable'.
    state_->setPartnerState("ready");

    // Retry the test.
    testSyncingTransition(FinalState(HA_READY_ST));
    // This time the server should have synchronized.
    EXPECT_EQ(HAService::HA_SYNCING_SUCCEEDED_EVT, service_->getLastEvent());
}

// This test verifies that the HA state machine can be paused in certain states
// when the server is operating in load balancing mode. The test also verifies
// that heartbeat is active even if the state machine is paused.
TEST_F(HAServiceStateMachineTest, stateTransitionsLoadBalancingPause) {
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();
    auto state_machine = valid_config->getStateMachineConfig();

    // Set state machine pausing in various states.
    state_machine->getStateConfig(HA_LOAD_BALANCING_ST)->setPausing("always");
    state_machine->getStateConfig(HA_PARTNER_DOWN_ST)->setPausing("always");
    state_machine->getStateConfig(HA_READY_ST)->setPausing("always");
    state_machine->getStateConfig(HA_SYNCING_ST)->setPausing("always");
    state_machine->getStateConfig(HA_TERMINATED_ST)->setPausing("always");
    state_machine->getStateConfig(HA_WAITING_ST)->setPausing("always");

    startService(valid_config);

    {
        SCOPED_TRACE("LOAD BALANCING state transitions");

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_LOAD_BALANCING_ST));
        EXPECT_TRUE(state_->isHeartbeatRunning());

        EXPECT_TRUE(service_->unpause());
        // An additional attempt to unpause should return false.
        EXPECT_FALSE(service_->unpause());

        testTransition(MyState(HA_LOAD_BALANCING_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));
        EXPECT_TRUE(state_->isHeartbeatRunning());
    }

    {
        SCOPED_TRACE("PARTNER DOWN state transitions");

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_PARTNER_DOWN_ST));
        EXPECT_TRUE(state_->isHeartbeatRunning());

        EXPECT_TRUE(service_->unpause());

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_WAITING_ST));
        EXPECT_TRUE(state_->isHeartbeatRunning());
    }


    {
        SCOPED_TRACE("READY state transitions");

        testTransition(MyState(HA_READY_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_READY_ST));
        EXPECT_TRUE(state_->isHeartbeatRunning());

        EXPECT_TRUE(service_->unpause());

        testTransition(MyState(HA_READY_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_LOAD_BALANCING_ST));
        EXPECT_TRUE(state_->isHeartbeatRunning());
    }


    {
        SCOPED_TRACE("WAITING state transitions");

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_WAITING_ST));
        EXPECT_TRUE(state_->isHeartbeatRunning());

        EXPECT_TRUE(service_->unpause());

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                       FinalState(HA_SYNCING_ST));
        EXPECT_TRUE(state_->isHeartbeatRunning());
    }
}

// This test verifies that the HA state machine can be paused in the syncing
// state.
TEST_F(HAServiceStateMachineTest, syncingTransitionsLoadBalancingPause) {
    HAConfigPtr valid_config = createValidConfiguration();

    auto state_machine = valid_config->getStateMachineConfig();

    // Pause state machine in various states.
    state_machine->getStateConfig(HA_LOAD_BALANCING_ST)->setPausing("always");
    state_machine->getStateConfig(HA_PARTNER_DOWN_ST)->setPausing("always");
    state_machine->getStateConfig(HA_READY_ST)->setPausing("always");
    state_machine->getStateConfig(HA_SYNCING_ST)->setPausing("always");
    state_machine->getStateConfig(HA_TERMINATED_ST)->setPausing("always");
    state_machine->getStateConfig(HA_WAITING_ST)->setPausing("always");

    startService(valid_config);
    waitForEvent(HAService::HA_HEARTBEAT_COMPLETE_EVT);

    // The syncing state handler doesn't start synchronization until it
    // detects that the partner is online. It may remember that from the
    // previous heartbeat attempts. If the partner appears to be unavailable
    // it will continue heartbeats before it synchronizes. This prevents the
    // server from making endless attempts to synchronize without any chance
    // to succeed. We verify that the server is not trying to synchronize
    // by checking that the last event is not the one associated with the
    // synchronization attempt.
    ASSERT_NE(service_->getLastEvent(), HAService::HA_SYNCING_FAILED_EVT);
    ASSERT_NE(service_->getLastEvent(), HAService::HA_SYNCING_SUCCEEDED_EVT);

    // Startup the partner.
    partner_->enableRespondLeaseFetching();
    partner_->startup();

    // We haven't been running heartbeats so we have to manually set the
    // partner's state to something other than 'unavailable'.
    state_->setPartnerState("ready");

    // Run the syncing state handler.
    testSyncingTransition(FinalState(HA_SYNCING_ST));

    // We should see no synchronization attempts because the server is paused
    // in this state.
    EXPECT_NE(service_->getLastEvent(), HAService::HA_SYNCING_FAILED_EVT);
    EXPECT_NE(service_->getLastEvent(), HAService::HA_SYNCING_SUCCEEDED_EVT);

    // Unpause the state machine.
    EXPECT_TRUE(service_->unpause());

    // Retry the test. It should now transition to the ready state.
    testSyncingTransition(FinalState(HA_READY_ST));

    // This time the server should have synchronized.
    EXPECT_EQ(HAService::HA_SYNCING_SUCCEEDED_EVT, service_->getLastEvent());
}

// This test verifies that the server takes ownership of the given scopes
// and whether the DHCP service is disabled or enabled in certain states.
TEST_F(HAServiceStateMachineTest, scopesServingLoadBalancing) {
    startService(createValidConfiguration());

    // LOAD BALANCING and TERMINATED: serving my own scope.
    expectScopes(MyState(HA_LOAD_BALANCING_ST), { "server1" }, true);
    expectScopes(MyState(HA_TERMINATED_ST), { "server1" }, true);

    // PARTNER DOWN: serving both scopes.
    expectScopes(MyState(HA_PARTNER_DOWN_ST), { "server1", "server2" }, true);

    // READY & WAITING: serving no scopes.
    expectScopes(MyState(HA_READY_ST), { }, false);
    expectScopes(MyState(HA_WAITING_ST), { }, false);
}

// This test verifies that the server does not take ownership of the
// partner's scope when auto-failover parameter is set to false.
TEST_F(HAServiceStateMachineTest, scopesServingLoadBalancingNoFailover) {
    HAConfigPtr valid_config = createValidConfiguration();
    valid_config->getThisServerConfig()->setAutoFailover(false);
    startService(valid_config);

    // LOAD BALANCING and TERMINATED: serving my own scope.
    expectScopes(MyState(HA_LOAD_BALANCING_ST), { "server1" }, true);
    expectScopes(MyState(HA_TERMINATED_ST), { "server1" }, true);

    // PARTNER DOWN: still serving my own scope because auto-failover
    // is disabled.
    expectScopes(MyState(HA_PARTNER_DOWN_ST), { "server1" }, true);

    // READY & WAITING: serving no scopes.
    expectScopes(MyState(HA_READY_ST), { }, false);
    expectScopes(MyState(HA_WAITING_ST), { }, false);
}

// This test verifies if the server would send lease updates to the partner
// while being in various states. The HA configuration is load balancing.
TEST_F(HAServiceStateMachineTest, shouldSendLeaseUpdatesLoadBalancing) {
    HAConfigPtr valid_config = createValidConfiguration();
    startService(valid_config);

    HAConfig::PeerConfigPtr peer_config = valid_config->getFailoverPeerConfig();

    EXPECT_TRUE(expectLeaseUpdates(MyState(HA_LOAD_BALANCING_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_PARTNER_DOWN_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_READY_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_SYNCING_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_TERMINATED_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_WAITING_ST), peer_config));
}


// This test verifies if the server would not send lease updates to the
// partner if lease updates are administratively disabled.
TEST_F(HAServiceStateMachineTest, shouldSendLeaseUpdatesDisabledLoadBalancing) {
    HAConfigPtr valid_config = createValidConfiguration();
    valid_config->setSendLeaseUpdates(false);
    startService(valid_config);

    HAConfig::PeerConfigPtr peer_config = valid_config->getFailoverPeerConfig();

    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_LOAD_BALANCING_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_PARTNER_DOWN_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_READY_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_SYNCING_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_TERMINATED_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_WAITING_ST), peer_config));
}

// This test verifies if the server would send heartbeat to the partner
// while being in various states. The HA configuration is load balancing.
TEST_F(HAServiceStateMachineTest, heartbeatLoadBalancing) {
    HAConfigPtr valid_config = createValidConfiguration();
    startService(valid_config);

    EXPECT_TRUE(expectHeartbeat(MyState(HA_LOAD_BALANCING_ST)));
    EXPECT_TRUE(expectHeartbeat(MyState(HA_PARTNER_DOWN_ST)));
    EXPECT_TRUE(expectHeartbeat(MyState(HA_READY_ST)));
    EXPECT_FALSE(expectHeartbeat(MyState(HA_TERMINATED_ST)));
    EXPECT_TRUE(expectHeartbeat(MyState(HA_WAITING_ST)));
}

// This test checks all combinations of server and partner states and the
// resulting state to which the server transitions. This server is primary.
// There is another test which validates state transitions from the
// standby server perspective.
TEST_F(HAServiceStateMachineTest, stateTransitionsHotStandbyPrimary) {
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    startService(valid_config);


    // HOT STANDBY state transitions
    {
        SCOPED_TRACE("HOT STANDBY state transitions");

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_HOT_STANDBY_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_HOT_STANDBY_ST));
    }

    // PARTNER DOWN state transitions
    {
        SCOPED_TRACE("PARTNER DOWN state transitions");

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_HOT_STANDBY_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_PARTNER_DOWN_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_PARTNER_DOWN_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_PARTNER_DOWN_ST));
    }

    // READY state transitions
    {
        SCOPED_TRACE("READY state transitions");

        testTransition(MyState(HA_READY_ST), PartnerState(HA_HOT_STANDBY_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_READY_ST));
    }

    // WAITING state transitions
    {
        SCOPED_TRACE("WAITING state transitions");

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_HOT_STANDBY_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_WAITING_ST));
    }
}

// This test checks that the server in the hot standby mode does not
// transition to the "syncing" state when "sync-leases" is disabled.
// This is the primary server case.
TEST_F(HAServiceStateMachineTest, noSyncingTransitionsHotStandbyPrimary) {
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");
    valid_config->setSyncLeases(false);

    startService(valid_config);

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                   FinalState(HA_READY_ST));

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                   FinalState(HA_READY_ST));

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_READY_ST),
                   FinalState(HA_READY_ST));
}

// This test checks that the primary server in the hot standby mode
// transitions to the "terminated" state when the clock skew gets high.
TEST_F(HAServiceStateMachineTest, terminateTransitionsHotStandbyPrimary) {
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    startService(valid_config);

    testTerminateTransition(MyState(HA_HOT_STANDBY_ST));
    testTerminateTransition(MyState(HA_PARTNER_DOWN_ST));
    testTerminateTransition(MyState(HA_READY_ST));
    testTerminateTransition(MyState(HA_WAITING_ST));
}

// This test checks all combinations of server and partner states and the
// resulting state to which the server transitions. This server is standby.
// There is another test which validates state transitions from the
// primary server perspective.
TEST_F(HAServiceStateMachineTest, stateTransitionsHotStandbyStandby) {
    partner_.reset(new HAPartner(listener_, factory_));
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setThisServerName("server2");
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    startService(valid_config);

    // HOT STANDBY state transitions
    {
        SCOPED_TRACE("HOT STANDBY state transitions");

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_HOT_STANDBY_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_HOT_STANDBY_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_HOT_STANDBY_ST));
    }

    // PARTNER DOWN state transitions
    {
        SCOPED_TRACE("PARTNER DOWN state transitions");

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_HOT_STANDBY_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_PARTNER_DOWN_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_PARTNER_DOWN_ST));

        testTransition(MyState(HA_PARTNER_DOWN_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_PARTNER_DOWN_ST));
    }

    // READY state transitions
    {
        SCOPED_TRACE("READY state transitions");

        testTransition(MyState(HA_READY_ST), PartnerState(HA_HOT_STANDBY_ST),
                       FinalState(HA_HOT_STANDBY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_READY_ST));

        testTransition(MyState(HA_READY_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_READY_ST));
    }

    // WAITING state transitions
    {
        SCOPED_TRACE("WAITING state transitions");

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_HOT_STANDBY_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_READY_ST),
                       FinalState(HA_SYNCING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_SYNCING_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_TERMINATED_ST),
                       FinalState(HA_TERMINATED_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_WAITING_ST),
                       FinalState(HA_WAITING_ST));

        testTransition(MyState(HA_WAITING_ST), PartnerState(HA_UNAVAILABLE_ST),
                       FinalState(HA_WAITING_ST));
    }
}

// This test checks that the server in the hot standby mode does not
// transition to the "syncing" state when "sync-leases" is disabled.
// This is the standby server case.
TEST_F(HAServiceStateMachineTest, noSyncingTransitionsHotStandbyStandby) {
    partner_.reset(new HAPartner(listener_, factory_));
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setThisServerName("server2");
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");
    valid_config->setSyncLeases(false);

    startService(valid_config);

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_LOAD_BALANCING_ST),
                   FinalState(HA_READY_ST));

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_PARTNER_DOWN_ST),
                   FinalState(HA_READY_ST));

    testTransition(MyState(HA_WAITING_ST), PartnerState(HA_READY_ST),
                   FinalState(HA_READY_ST));
}

// This test checks that the standby server in the hot standby mode
// transitions to the "terminated" state when the clock skew gets high.
TEST_F(HAServiceStateMachineTest, terminateTransitionsHotStandbyStandby) {
    partner_.reset(new HAPartner(listener_, factory_));
    partner_->startup();

    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setThisServerName("server2");
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    startService(valid_config);

    testTerminateTransition(MyState(HA_HOT_STANDBY_ST));
    testTerminateTransition(MyState(HA_PARTNER_DOWN_ST));
    testTerminateTransition(MyState(HA_READY_ST));
    testTerminateTransition(MyState(HA_WAITING_ST));
}

// This test verifies that the server takes ownership of the given scopes
// and whether the DHCP service is disabled or enabled in certain states.
// This is primary server.
TEST_F(HAServiceStateMachineTest, scopesServingHotStandbyPrimary) {
    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    startService(valid_config);

    // HOT STANDBY and TERMINATED: serving my own scope
    expectScopes(MyState(HA_HOT_STANDBY_ST), { "server1" }, true);
    expectScopes(MyState(HA_TERMINATED_ST), { "server1" }, true);

    // PARTNER DOWN: still serving my own scope.
    expectScopes(MyState(HA_PARTNER_DOWN_ST), { "server1" }, true);

    // READY & WAITING: serving no scopes.
    expectScopes(MyState(HA_READY_ST), { }, false);
    expectScopes(MyState(HA_WAITING_ST), { }, false);
}

// This test verifies that auto-failover setting does not affect scopes
// handling by the primary server in the hot-standby mode.
TEST_F(HAServiceStateMachineTest, scopesServingHotStandbyPrimaryNoFailover) {
    HAConfigPtr valid_config = createValidConfiguration();
    // Turn it into hot-standby configuration.
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    // Disable auto-failover.
    valid_config->getThisServerConfig()->setAutoFailover(false);

    startService(valid_config);

    // HOT STANDBY and TERMINATED: serving my own scope
    expectScopes(MyState(HA_HOT_STANDBY_ST), { "server1" }, true);
    expectScopes(MyState(HA_TERMINATED_ST), { "server1" }, true);

    // PARTNER DOWN: still serving my own scope.
    expectScopes(MyState(HA_PARTNER_DOWN_ST), { "server1" }, true);

    // READY & WAITING: serving no scopes.
    expectScopes(MyState(HA_READY_ST), { }, false);
    expectScopes(MyState(HA_WAITING_ST), { }, false);
}

// This test verifies if the server would send lease updates to the partner
// while being in various states. The HA configuration is hot standby and
// the server is primary.
TEST_F(HAServiceStateMachineTest, shouldSendLeaseUpdatesHotStandbyPrimary) {
    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    startService(valid_config);

    HAConfig::PeerConfigPtr peer_config = valid_config->getFailoverPeerConfig();

    EXPECT_TRUE(expectLeaseUpdates(MyState(HA_HOT_STANDBY_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_PARTNER_DOWN_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_READY_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_SYNCING_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_TERMINATED_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_WAITING_ST), peer_config));
}

// This test verifies if the server would send heartbeat to the partner
// while being in various states. The HA configuration is hot standby.
TEST_F(HAServiceStateMachineTest, heartbeatHotstandby) {
    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    startService(valid_config);

    EXPECT_TRUE(expectHeartbeat(MyState(HA_HOT_STANDBY_ST)));
    EXPECT_TRUE(expectHeartbeat(MyState(HA_PARTNER_DOWN_ST)));
    EXPECT_TRUE(expectHeartbeat(MyState(HA_READY_ST)));
    EXPECT_FALSE(expectHeartbeat(MyState(HA_TERMINATED_ST)));
    EXPECT_TRUE(expectHeartbeat(MyState(HA_WAITING_ST)));
}

// This test verifies that the server takes ownership of the given scopes
// and whether the DHCP service is disabled or enabled in certain states.
// This is standby server.
TEST_F(HAServiceStateMachineTest, scopesServingHotStandbyStandby) {
    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setThisServerName("server2");
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    startService(valid_config);

    // HOT STANDBY: serving no scopes because the primary is active.
    // The DHCP is enabled to be able to monitor activity of the
    // primary.
    expectScopes(MyState(HA_HOT_STANDBY_ST), { }, true);

    // TERMINATED: serving no scopes because the primary is active.
    expectScopes(MyState(HA_TERMINATED_ST), { }, true);

    // PARTNER DOWN: serving server1's scope.
    expectScopes(MyState(HA_PARTNER_DOWN_ST), { "server1" }, true);

    // READY & WAITING: serving no scopes.
    expectScopes(MyState(HA_READY_ST), { }, false);
    expectScopes(MyState(HA_WAITING_ST), { }, false);
}

// This test verifies that the standby server does not take ownership
// of the primary server's scope when auto-failover is set to false
TEST_F(HAServiceStateMachineTest, scopesServingHotStandbyStandbyNoFailover) {
    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setThisServerName("server2");
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    // Disable auto-failover.
    valid_config->getThisServerConfig()->setAutoFailover(false);

    startService(valid_config);

    // HOT STANDBY: serving no scopes because the primary is active.
    // The DHCP is enabled to be able to monitor activity of the
    // primary.
    expectScopes(MyState(HA_HOT_STANDBY_ST), { }, true);

    // TERMINATED: serving no scopes because the primary is active.
    expectScopes(MyState(HA_TERMINATED_ST), { }, true);

    // PARTNER DOWN: still serving no scopes because auto-failover is
    // set to false.
    expectScopes(MyState(HA_PARTNER_DOWN_ST), { }, true);

    // READY & WAITING: serving no scopes.
    expectScopes(MyState(HA_READY_ST), { }, false);
    expectScopes(MyState(HA_WAITING_ST), { }, false);
}

// This test verifies if the server would send lease updates to the partner
// while being in various states. The HA configuration is hot standby and
// the server is secondary.
TEST_F(HAServiceStateMachineTest, shouldSendLeaseUpdatesHotStandbyStandby) {
    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setThisServerName("server2");
    valid_config->setHAMode("hot-standby");
    valid_config->getPeerConfig("server2")->setRole("standby");

    startService(valid_config);

    HAConfig::PeerConfigPtr peer_config = valid_config->getFailoverPeerConfig();

    EXPECT_TRUE(expectLeaseUpdates(MyState(HA_HOT_STANDBY_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_PARTNER_DOWN_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_READY_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_SYNCING_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_TERMINATED_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_WAITING_ST), peer_config));
}

// This test verifies if the backup server doesn't send lease updates.
TEST_F(HAServiceStateMachineTest, shouldSendLeaseUpdatesBackup) {
    HAConfigPtr valid_config = createValidConfiguration();

    // Turn it into hot-standby configuration.
    valid_config->setThisServerName("server3");

    startService(valid_config);

    HAConfig::PeerConfigPtr peer_config = valid_config->getPeerConfig("server1");

    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_BACKUP_ST), peer_config));
    EXPECT_FALSE(expectLeaseUpdates(MyState(HA_WAITING_ST), peer_config));
}

}
