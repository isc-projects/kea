// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <http/listener.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <http/response_creator_factory.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <netconf/http_control_socket.h>
#include <netconf/netconf_config.h>
#include <netconf/stdout_control_socket.h>
#include <netconf/unix_control_socket.h>
#include <testutils/sandbox.h>
#include <testutils/threaded_test.h>
#include <yang/tests/sysrepo_setup.h>

#include <iostream>
#include <sstream>
#include <thread>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::netconf;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::http;
using namespace isc::http::test;
using namespace isc::test;

using isc::yang::test::SysrepoSetup;

namespace {

/// @brief Type definition for the pointer to Thread objects.
using ThreadPtr = shared_ptr<thread>;

//////////////////////////////// STDOUT ////////////////////////////////

/// @brief Test derived StdoutControlSocket class.
///
/// This class exposes the constructor taking the output stream.
class TestStdoutControlSocket : public StdoutControlSocket {
public:
    /// @brief Constructor.
    ///
    /// @param ctrl_sock The control socket configuration.
    /// @param output The output stream.
    TestStdoutControlSocket(CfgControlSocketPtr ctrl_sock, ostream& output)
        : StdoutControlSocket(ctrl_sock, output) {
    }
};  // TestStdoutControlSocket

/// @brief Type definition for the pointer to the @c TestStdoutControlSocket.
using TestStdoutControlSocketPtr = shared_ptr<TestStdoutControlSocket>;

// Verifies that the createControlSocket template can create a stdout
// control socket.
TEST(StdoutControlSocketTest, createControlSocket) {
    CfgControlSocketPtr cfg(new
                    CfgControlSocket(CfgControlSocket::Type::STDOUT,
                                     "",
                                     Url("http://127.0.0.1:8000/")));
    ASSERT_TRUE(cfg);
    ControlSocketBasePtr cs = controlSocketFactory(cfg);
    ASSERT_TRUE(cs);
    StdoutControlSocketPtr scs =
        dynamic_pointer_cast<StdoutControlSocket>(cs);
    EXPECT_TRUE(scs);
}

// Verifies that a stdout control socket does not implement configGet.
TEST(StdoutControlSocketTest, configGet) {
    CfgControlSocketPtr cfg(new
                    CfgControlSocket(CfgControlSocket::Type::STDOUT,
                                     "",
                                     Url("http://127.0.0.1:8000/")));
    ASSERT_TRUE(cfg);
    StdoutControlSocketPtr scs(new StdoutControlSocket(cfg));
    ASSERT_TRUE(scs);
    EXPECT_THROW_MSG(scs->configGet("foo"), NotImplemented,
                     "No config-get for stdout control socket");
}

// Verifies that a stdout control socket does not nothing for configTest.
TEST(StdoutControlSocketTest, configTest) {
    CfgControlSocketPtr cfg(new
                            CfgControlSocket(CfgControlSocket::Type::STDOUT,
                                             "",
                                             Url("http://127.0.0.1:8000/")));
    ASSERT_TRUE(cfg);
    StdoutControlSocketPtr scs(new StdoutControlSocket(cfg));
    ASSERT_TRUE(scs);
    ConstElementPtr answer;
    ASSERT_NO_THROW_LOG(answer = scs->configTest(ElementPtr(), "foo"));

    // Check answer.
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"result\": 0 }", answer->str());
}

// Verifies that a stdout control socket outputs configSet argument.
TEST(StdoutControlSocketTest, configSet) {
    CfgControlSocketPtr cfg(new
                            CfgControlSocket(CfgControlSocket::Type::STDOUT,
                                             "",
                                             Url("http://127.0.0.1:8000/")));
    ASSERT_TRUE(cfg);
    ostringstream os;
    TestStdoutControlSocketPtr tscs(new TestStdoutControlSocket(cfg, os));
    ASSERT_TRUE(tscs);
    ElementPtr json = Element::fromJSON("{ \"bar\": 1 }");
    ConstElementPtr answer;
    ASSERT_NO_THROW_LOG(answer = tscs->configSet(json, "foo"));

    // Check answer.
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"result\": 0 }", answer->str());

    // Check output.
    string expected = "{\n  \"bar\": 1\n}\n";
    EXPECT_EQ(expected, os.str());
}

//////////////////////////////// UNIX ////////////////////////////////

/// @brief Test timeout in ms.
const long TEST_TIMEOUT = 1500;

/// @brief Test fixture class for unix control sockets.
class UnixControlSocketTest : public ThreadedTest {
public:
    isc::test::Sandbox sandbox;

    /// @brief Constructor.
    UnixControlSocketTest()
        : ThreadedTest(), io_service_(new IOService()) {
    }

    void SetUp() override {
        SysrepoSetup::cleanSharedMemory();
        removeUnixSocketFile();
    }

    void TearDown() override {
        if (thread_) {
            thread_->join();
            thread_.reset();
        }
        removeUnixSocketFile();
        io_service_->stopAndPoll();
    }

    /// @brief Returns socket file path.
    ///
    /// If the KEA_SOCKET_TEST_DIR environment variable is specified, the
    /// socket file is created in the location pointed to by this variable.
    /// Otherwise, it is created in the build directory.
    string unixSocketFilePath() {
        string socket_path;
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            socket_path = string(env) + "/test-socket";
        } else {
            socket_path = sandbox.join("test-socket");
        }
        return (socket_path);
    }

    /// @brief Removes unix socket descriptor.
    void removeUnixSocketFile() {
        static_cast<void>(remove(unixSocketFilePath().c_str()));
    }

    /// @brief Create configuration of the control socket.
    ///
    /// @return a pointer to a control socket configuration.
    CfgControlSocketPtr createCfgControlSocket() {
        CfgControlSocketPtr cfg;
        cfg.reset(new CfgControlSocket(CfgControlSocket::Type::UNIX,
                                       unixSocketFilePath(),
                                       Url("http://127.0.0.1:8000/")));
        return (cfg);
    }

    /// @brief Thread reflecting server function.
    void reflectServer();

    /// @brief IOService object.
    IOServicePtr io_service_;
};  // UnixControlSocketTest

/// @brief Server method running in a thread reflecting the command.
///
/// It creates the server socket, accepts client connection, read
/// the command and send it back in a received JSON map.
void
UnixControlSocketTest::reflectServer() {
    // Acceptor.
    boost::asio::local::stream_protocol::acceptor
        acceptor(io_service_->getInternalIOService());
    EXPECT_NO_THROW_LOG(acceptor.open());
    boost::asio::local::stream_protocol::endpoint
        endpoint(unixSocketFilePath());
    EXPECT_NO_THROW_LOG(acceptor.bind(endpoint));
    EXPECT_NO_THROW_LOG(acceptor.listen());
    boost::asio::local::stream_protocol::socket
        socket(io_service_->getInternalIOService());

    // Ready.
    signalReady();

    // Timeout.
    IntervalTimer timer(io_service_);
    bool timeout = false;
    timer.setup([&timeout]() {
            timeout = true;
            FAIL() << "timeout";
        }, TEST_TIMEOUT, IntervalTimer::ONE_SHOT);

    // Accept.
    bool accepted = false;
    boost::system::error_code ec;
    acceptor.async_accept(socket,
                          [&ec, &accepted]
                          (const boost::system::error_code& error) {
                              ec = error;
                              accepted = true;
                          });
    while (!accepted && !timeout) {
        io_service_->runOne();
    }
    ASSERT_FALSE(ec);

    // Receive command.
    string rbuf(1024, ' ');
    size_t received = 0;
    socket.async_receive(boost::asio::buffer(&rbuf[0], rbuf.size()),
                         [&ec, &received]
                         (const boost::system::error_code& error, size_t cnt) {
                             ec = error;
                             received = cnt;
                         });
    while (!received && !timeout) {
        io_service_->runOne();
    }
    ASSERT_FALSE(ec);
    rbuf.resize(received);

    // Reflect.
    ElementPtr map = Element::createMap();
    map->set("received", Element::create(rbuf));
    string sbuf = map->str();

    // Send back.
    size_t sent = 0;
    socket.async_send(boost::asio::buffer(&sbuf[0], sbuf.size()),
                      [&ec, &sent]
                      (const boost::system::error_code& error, size_t cnt) {
                          ec = error;
                          sent = cnt;
                      });
    while (!sent && !timeout) {
        io_service_->runOne();
    }
    ASSERT_FALSE(ec);

    // Stop timer.
    timer.cancel();

    // Close socket.
    if (socket.is_open()) {
        EXPECT_NO_THROW_LOG(socket.close());
    }

    EXPECT_FALSE(timeout);
    EXPECT_TRUE(accepted);
    EXPECT_TRUE(received);
    EXPECT_TRUE(sent);
    EXPECT_EQ(sent, sbuf.size());
}

// Verifies that the createControlSocket template can create an unix
// control socket.
TEST_F(UnixControlSocketTest, createControlSocket) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    ControlSocketBasePtr cs = controlSocketFactory(cfg);
    ASSERT_TRUE(cs);
    UnixControlSocketPtr ucs =
        dynamic_pointer_cast<UnixControlSocket>(cs);
    EXPECT_TRUE(ucs);
}

// Verifies that unix control sockets handle configGet() as expected.
TEST_F(UnixControlSocketTest, configGet) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    UnixControlSocketPtr ucs(new UnixControlSocket(cfg));
    ASSERT_TRUE(ucs);

    // Run a reflecting server in a thread.
    thread_.reset(new thread([this]() { reflectServer(); }));

    waitReady();

    // Try configGet.
    ConstElementPtr reflected;
    EXPECT_NO_THROW_LOG(reflected = ucs->configGet("foo"));
    ASSERT_TRUE(reflected);
    ASSERT_EQ(Element::map, reflected->getType());
    ConstElementPtr command = reflected->get("received");
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::string, command->getType());
    string expected = "{ \"command\": \"config-get\" }";
    EXPECT_EQ(expected, command->stringValue());
}

// Verifies that unix control sockets handle configTest() as expected.
TEST_F(UnixControlSocketTest, configTest) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    UnixControlSocketPtr ucs(new UnixControlSocket(cfg));
    ASSERT_TRUE(ucs);

    // Run a reflecting server in a thread.
    thread_.reset(new thread([this]() { reflectServer(); }));

    waitReady();

    // Prepare a config to test.
    ElementPtr json = Element::fromJSON("{ \"bar\": 1 }");

    ConstElementPtr reflected;
    EXPECT_NO_THROW_LOG(reflected = ucs->configTest(json, "foo"));
    ASSERT_TRUE(reflected);
    ASSERT_EQ(Element::map, reflected->getType());
    ConstElementPtr command = reflected->get("received");
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::string, command->getType());
    string expected = "{ \"arguments\": { \"bar\": 1 }, "
        "\"command\": \"config-test\" }";
    EXPECT_EQ(expected, command->stringValue());
}

// Verifies that unix control sockets handle configSet() as expected.
TEST_F(UnixControlSocketTest, configSet) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    UnixControlSocketPtr ucs(new UnixControlSocket(cfg));
    ASSERT_TRUE(ucs);

    // Run a reflecting server in a thread.
    thread_.reset(new thread([this]() { reflectServer(); }));

    waitReady();

    // Prepare a config to set.
    ElementPtr json = Element::fromJSON("{ \"bar\": 1 }");

    ConstElementPtr reflected;
    EXPECT_NO_THROW_LOG(reflected = ucs->configSet(json, "foo"));
    ASSERT_TRUE(reflected);
    ASSERT_EQ(Element::map, reflected->getType());
    ConstElementPtr command = reflected->get("received");
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::string, command->getType());
    string expected = "{ \"arguments\": { \"bar\": 1 }, "
        "\"command\": \"config-set\" }";
    EXPECT_EQ(expected, command->stringValue());
}

// Verifies that unix control sockets handle timeouts.
TEST_F(UnixControlSocketTest, timeout) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    UnixControlSocketPtr ucs(new UnixControlSocket(cfg));
    ASSERT_TRUE(ucs);

    // Run a timeout server in a thread.
    thread_.reset(new thread([this]() { waitReady(); }));

    // Try configGet: it should get a communication error,
    EXPECT_THROW_MSG(ucs->configGet("foo"), ControlSocketError,
                     "communication error: No such file or directory");
    signalReady();
}

//////////////////////////////// HTTP ////////////////////////////////

/// @brief IP address to which HTTP service is bound.
const string SERVER_ADDRESS = "127.0.0.1";

/// @brief Port number to which HTTP service is bound.
const uint16_t SERVER_PORT = 18123;

/// @brief Test HTTP JSON response.
using Response = TestHttpResponseBase<HttpResponseJson>;

/// @brief Pointer to test HTTP JSON response.
using ResponsePtr = boost::shared_ptr<Response>;

/// @brief Generic test HTTP response.
using GenericResponse = TestHttpResponseBase<HttpResponse>;

/// @brief Pointer to generic test HTTP response.
using GenericResponsePtr = boost::shared_ptr<GenericResponse>;

/// @brief Implementation of the HttpResponseCreator.
///
/// Send back the request in a received JSON map.
class TestHttpResponseCreator : public HttpResponseCreator {
public:
    /// @brief Create a new request.
    ///
    /// @return Pointer to the new instance of the HttpRequest.
    HttpRequestPtr createNewHttpRequest() const override final {
        return (HttpRequestPtr(new PostHttpRequestJson()));
    }

protected:
    /// @brief Creates HTTP response.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP response.
    HttpResponsePtr
    createStockHttpResponse(const HttpRequestPtr& request,
                            const HttpStatusCode& status_code) const override final {
        // Data is in the request context.
        HttpVersion http_version(request->context()->http_version_major_,
                                 request->context()->http_version_minor_);
        ResponsePtr response(new Response(http_version, status_code));
        response->finalize();
        return (response);
    }

    /// @brief Creates HTTP response.
    ///
    /// Build a response with reflected request in a received JSON map.
    /// It can be told to respond with a partial JSON.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to an object representing HTTP response.
    virtual HttpResponsePtr
    createDynamicHttpResponse(HttpRequestPtr request) override {
        // Request must always be JSON.
        PostHttpRequestJsonPtr request_json =
            boost::dynamic_pointer_cast<PostHttpRequestJson>(request);
        if (!request_json) {
            isc_throw(Unexpected, "request is not JSON");
        }
        ConstElementPtr body = request_json->getBodyAsJson();
        if (!body) {
            isc_throw(Unexpected, "can't get JSON from request");
        }

        // Check for the special partial JSON.
        ConstElementPtr arguments = body->get("arguments");
        if (arguments && (arguments->contains("want-partial"))) {
            // Use a generic response.
            GenericResponsePtr
                response(new GenericResponse(request->getHttpVersion(),
                                             HttpStatusCode::OK));
            HttpResponseContextPtr ctx = response->context();
            // Generate JSON response.
            ctx->headers_.push_back(HttpHeaderContext("Content-Type",
                                                      "application/json"));
            // Not closed JSON map so it will fail.
            ctx->body_ = "{";
            response->finalize();
            // Take into account the missing '}'.
            response->setContentLength(2);
            return (response);
        }

        // Reflect.
        ResponsePtr response(new Response(request->getHttpVersion(),
                                          HttpStatusCode::OK));
        ElementPtr map = Element::createMap();
        map->set("received", Element::create(body->str()));
        response->setBodyAsJson(map);
        response->finalize();
        return (response);
    }
};  // TestHttpResponseCreator

/// @brief Implementation of the test HttpResponseCreatorFactory.
class TestHttpResponseCreatorFactory : public HttpResponseCreatorFactory {
public:

    /// @brief Creates @ref TestHttpResponseCreator instance.
    HttpResponseCreatorPtr create() const override final {
        HttpResponseCreatorPtr response_creator(new TestHttpResponseCreator());
        return (response_creator);
    }
};  // TestHttpResponseCreatorFactory

/// @brief Test fixture class for http control sockets.
class HttpControlSocketTest : public ThreadedTest {
public:
    /// @brief Constructor.
    HttpControlSocketTest() : io_service_(new IOService()) {
    }

    void SetUp() override {
        SysrepoSetup::cleanSharedMemory();
    }

    void TearDown() override {
        SysrepoSetup::cleanSharedMemory();
        if (thread_) {
            thread_->join();
            thread_.reset();
        }
        if (listener_) {
            listener_->stop();
        }
        io_service_->stopAndPoll();
        listener_.reset();
    }

    /// @brief Returns socket URL.
    static Url httpSocketUrl() {
        ostringstream s;
        s << "http://" << SERVER_ADDRESS << ":" << SERVER_PORT << "/";
        return (Url(s.str()));
    }

    /// @brief Create configuration of the control socket.
    ///
    /// @return a pointer to a control socket configuration.
    CfgControlSocketPtr createCfgControlSocket() {
        CfgControlSocketPtr cfg;
        cfg.reset(new CfgControlSocket(CfgControlSocket::Type::HTTP,
                                       "", httpSocketUrl()));
        return (cfg);
    }

    /// @brief Create the reflecting listener.
    void createReflectListener();

    /// @brief Start listener.
    ///
    /// Run IO in a thread.
    void start() {
        // If the thread is ready to go, start the listener.
        if (listener_) {
            ASSERT_NO_THROW_LOG(listener_->start());
        }

        thread_.reset(new thread([this]() {
            // The thread is ready to go. Signal it to the main
            // thread so it can start the actual test.
            signalReady();
            // Until stop() is called run IO service.
            while (!isStopping()) {
                io_service_->runOne();
            }
            // Main thread signaled that the thread should
            // terminate. Launch any outstanding IO service
            // handlers.
            io_service_->poll();
            // Nothing more to do. Signal that the thread is
            // done so as the main thread can close HTTP
            // listener and clean up after the test.
            signalStopped();
        }));

        // Main thread waits here for the thread to start.
        waitReady();
    }

    /// @brief Stop listener.
    ///
    /// Post an empty action to finish current runOne.
    void stop() {
        // Notify the thread that it should terminate.
        signalStopping();
        // If the thread is blocked on running the IO
        // service, post the empty handler to cause
        // runOne to return.
        io_service_->post([]() { return; });
        // We asked that the thread stops. Let's wait
        // for it to signal that it has stopped.
        waitStopped();

        // Thread has terminated. We can stop the HTTP
        // listener safely.
        if (listener_) {
            ASSERT_NO_THROW_LOG(listener_->stop());
        }
    }

    /// @brief IOService object.
    IOServicePtr io_service_;

    /// @brief Pointer to listener.
    HttpListenerPtr listener_;
};  // HttpControlSocketTest

/// @brief Create the reflecting listener.
void
HttpControlSocketTest::createReflectListener() {
    HttpResponseCreatorFactoryPtr
        factory(new TestHttpResponseCreatorFactory());
    listener_.reset(new HttpListener(io_service_,
                                     IOAddress(SERVER_ADDRESS), SERVER_PORT,
                                     TlsContextPtr(), factory,
                                     HttpListener::RequestTimeout(2000),
                                     HttpListener::IdleTimeout(2000)));
}

// Verifies that the createControlSocket template can create a http
// control socket.
TEST_F(HttpControlSocketTest, createControlSocket) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    ControlSocketBasePtr cs = controlSocketFactory(cfg);
    ASSERT_TRUE(cs);
    HttpControlSocketPtr hcs =
        dynamic_pointer_cast<HttpControlSocket>(cs);
    EXPECT_TRUE(hcs);
}

// Verifies that http control sockets handle configGet() as expected.
TEST_F(HttpControlSocketTest, configGet) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    HttpControlSocketPtr hcs(new HttpControlSocket(cfg));
    ASSERT_TRUE(hcs);

    // Run a reflecting server in a thread.
    createReflectListener();
    start();

    // Try configGet.
    ConstElementPtr reflected;
    EXPECT_NO_THROW_LOG(reflected = hcs->configGet("foo"));
    stop();

    // Check result.
    ASSERT_TRUE(reflected);
    ASSERT_EQ(Element::map, reflected->getType());
    ConstElementPtr command = reflected->get("received");
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::string, command->getType());
    string expected = "{ \"command\": \"config-get\", "
        "\"remote-address\": \"127.0.0.1\", \"service\": [ \"foo\" ] }";
    EXPECT_EQ(expected, command->stringValue());
}

// Verifies that http control sockets handle configGet() for a control agent
// as expected.
TEST_F(HttpControlSocketTest, configGetCA) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    HttpControlSocketPtr hcs(new HttpControlSocket(cfg));
    ASSERT_TRUE(hcs);

    // Run a reflecting server in a thread.
    createReflectListener();
    start();

    // Try configGet.
    ConstElementPtr reflected;
    EXPECT_NO_THROW_LOG(reflected = hcs->configGet("ca"));
    stop();

    // Check result.
    ASSERT_TRUE(reflected);
    ASSERT_EQ(Element::map, reflected->getType());
    ConstElementPtr command = reflected->get("received");
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::string, command->getType());
    string expected = "{ \"command\": \"config-get\", \"remote-address\": \"127.0.0.1\" }";
    EXPECT_EQ(expected, command->stringValue());
}

// Verifies that http control sockets handle configTest() as expected.
TEST_F(HttpControlSocketTest, configTest) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    HttpControlSocketPtr hcs(new HttpControlSocket(cfg));
    ASSERT_TRUE(hcs);

    // Run a reflecting server in a thread.
    createReflectListener();
    start();

    // Prepare a config to test.
    ElementPtr json = Element::fromJSON("{ \"bar\": 1 }");

    // Try configTest.
    ConstElementPtr reflected;
    EXPECT_NO_THROW_LOG(reflected = hcs->configTest(json, "foo"));
    stop();

    // Check result.
    ASSERT_TRUE(reflected);
    ASSERT_EQ(Element::map, reflected->getType());
    ConstElementPtr command = reflected->get("received");
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::string, command->getType());
    string expected = "{ \"arguments\": { \"bar\": 1 }, "
        "\"command\": \"config-test\", "
        "\"remote-address\": \"127.0.0.1\", \"service\": [ \"foo\" ] }";
    EXPECT_EQ(expected, command->stringValue());
}

// Verifies that http control sockets handle configTest() for a control agent
// as expected.
TEST_F(HttpControlSocketTest, configTestCA) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    HttpControlSocketPtr hcs(new HttpControlSocket(cfg));
    ASSERT_TRUE(hcs);

    // Run a reflecting server in a thread.
    createReflectListener();
    start();

    // Prepare a config to test.
    ElementPtr json = Element::fromJSON("{ \"bar\": 1 }");

    // Try configTest.
    ConstElementPtr reflected;
    EXPECT_NO_THROW_LOG(reflected = hcs->configTest(json, "ca"));
    stop();

    // Check result.
    ASSERT_TRUE(reflected);
    ASSERT_EQ(Element::map, reflected->getType());
    ConstElementPtr command = reflected->get("received");
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::string, command->getType());
    string expected = "{ \"arguments\": { \"bar\": 1 }, "
        "\"command\": \"config-test\", \"remote-address\": \"127.0.0.1\" }";
    EXPECT_EQ(expected, command->stringValue());
}

// Verifies that http control sockets handle configSet() as expected.
TEST_F(HttpControlSocketTest, configSet) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    HttpControlSocketPtr hcs(new HttpControlSocket(cfg));
    ASSERT_TRUE(hcs);

    // Run a reflecting server in a thread.
    createReflectListener();
    start();

    // Prepare a config to set.
    ElementPtr json = Element::fromJSON("{ \"bar\": 1 }");

    // Try configSet.
    ConstElementPtr reflected;
    EXPECT_NO_THROW_LOG(reflected = hcs->configSet(json, "foo"));
    stop();

    // Check result.
    ASSERT_TRUE(reflected);
    ASSERT_EQ(Element::map, reflected->getType());
    ConstElementPtr command = reflected->get("received");
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::string, command->getType());
    string expected = "{ \"arguments\": { \"bar\": 1 }, "
        "\"command\": \"config-set\", "
        "\"remote-address\": \"127.0.0.1\", \"service\": [ \"foo\" ] }";
    EXPECT_EQ(expected, command->stringValue());
}

// Verifies that http control sockets handle configSet() for a control agent
// as expected.
TEST_F(HttpControlSocketTest, configSetCA) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    HttpControlSocketPtr hcs(new HttpControlSocket(cfg));
    ASSERT_TRUE(hcs);

    // Run a reflecting server in a thread.
    createReflectListener();
    start();

    // Prepare a config to set.
    ElementPtr json = Element::fromJSON("{ \"bar\": 1 }");

    // Try configSet.
    ConstElementPtr reflected;
    EXPECT_NO_THROW_LOG(reflected = hcs->configSet(json, "ca"));
    stop();

    // Check result.
    ASSERT_TRUE(reflected);
    ASSERT_EQ(Element::map, reflected->getType());
    ConstElementPtr command = reflected->get("received");
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::string, command->getType());
    string expected = "{ \"arguments\": { \"bar\": 1 }, "
        "\"command\": \"config-set\", \"remote-address\": \"127.0.0.1\" }";
    EXPECT_EQ(expected, command->stringValue());
}

// Verifies that http control sockets handle can't connect errors.
TEST_F(HttpControlSocketTest, connectionRefused) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    HttpControlSocketPtr hcs(new HttpControlSocket(cfg));
    ASSERT_TRUE(hcs);

    // Try configGet: it should get a communication error,
    try {
        hcs->configGet("foo");
    } catch (const ControlSocketError& ex) {
        EXPECT_EQ("communication error (code): Connection refused",
                  string(ex.what()));
    } catch (exception const& ex) {
        FAIL() << "unexpected exception: " << ex.what();
    } catch (...) {
        FAIL() << "unexpected exception";
    }
}

// Verifies that http control sockets handle timeout errors.
TEST_F(HttpControlSocketTest, partial) {
    CfgControlSocketPtr cfg = createCfgControlSocket();
    ASSERT_TRUE(cfg);
    HttpControlSocketPtr hcs(new HttpControlSocket(cfg));
    ASSERT_TRUE(hcs);

    // Create the server but do not start it.
    createReflectListener();
    start();

    // Prepare a special config to set.
    ElementPtr json = Element::fromJSON("{ \"want-partial\": true }");

    // Warn this makes time.
    cout << "Waiting 2s..." << endl;

    // Try configSet: it should get a communication error,
    try {
        hcs->configSet(json, "foo");
    } catch (const ControlSocketError& ex) {
        EXPECT_EQ("communication error (code): End of file",
                  string(ex.what()));
    } catch (exception const& ex) {
        FAIL() << "unexpected exception: " << ex.what();
    } catch (...) {
        FAIL() << "unexpected exception";
    }
    stop();
}

}  // namespace
