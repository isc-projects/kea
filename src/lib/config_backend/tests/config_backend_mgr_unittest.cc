// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config_backend/base_config_backend_mgr.h>
#include <config_backend/base_config_backend_pool.h>
#include <config_backend/base_config_backend.h>
#include <database/database_connection.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <list>
#include <string>
#include <utility>

using namespace isc;
using namespace isc::cb;
using namespace isc::db;

namespace {

/// @brief Defines list of properties retrieved by @c TestConfigBackend.
///
/// A single property is a name/value pair, where value is an integer.
typedef std::list<std::pair<std::string, int> > PropertiesList;

/// @brief Implements configuration backend used in tests.
///
/// @c BaseConfigBackend is an abstract class that must be implemented
/// in order to allow us to test mechanisms implemented in
/// @c BaseConfigBackendMgr and @c BaseConfigBackendPool.
///
/// Normally, a class derived directly from the @c BaseConfigBackend
/// will merely provide an interface for server specific operations,
/// e.g. DHCPv4 specific operations, and the database specific classes
/// will implement this interface. However, for the test purposes it
/// is convenient to implement them here and let the derivations
/// only provide the implementations of the @c getType, @c getHost
/// and @c getPort functions. That way, the logic for adding and
/// retrieving the data from the backend is implemented only once and
/// is common accross all test backends.
///
/// This class provides a logic for managing test data being a collection
/// of name/value pairs, i.e. "properties". It contains a list of
/// properties and the functions for adding the properties, retrieving
/// a single property and retrieving a collection of properties.
class TestConfigBackend : public BaseConfigBackend {
public:

    /// @brief Retrieves first property having a given name.
    ///
    /// @param property_name Name of the property to be retrieved.
    /// @return Value of the property or 0 if property doesn't exist.
    virtual int getProperty(const ServerSelector&,
                            const std::string& property_name) const {
        for (auto property : properties_) {
            if (property.first == property_name) {
                return (property.second);
            }
        }
        return (0);
    }

    /// @brief Retrieves first property matching the name and value.
    ///
    /// @param property_name Name of the property to be retrieved.
    /// @param property_value Value of the property to be retrieved.
    /// @return Value of the property or 0 if the property doesn't exist.
    virtual int getProperty(const ServerSelector&,
                            const std::string& property_name,
                            const int property_value) const {
        for (auto property : properties_) {
            if ((property.first == property_name) &&
                (property.second == property_value)) {
                return (property.second);
            }
        }
        return (0);
    }

    /// @brief Retrieves all properties having a given name.
    ///
    /// @param property_name Name of the properties to be retrieved.
    /// @return List of the properties having a given name. This list is
    /// empty if no property was found.
    virtual PropertiesList getProperties(const ServerSelector&,
                                         const std::string& property_name) const {
        PropertiesList properties;
        for (auto property : properties_) {
            if (property.first == property_name) {
                properties.push_back(property);
            }
        }
        return (properties);
    }

    /// @brief Retrieves all properties.
    ///
    /// @return List of all properties held in the backend.
    virtual PropertiesList getAllProperties(const ServerSelector&) const {
        return (properties_);
    }

    /// @brief Creates new property.
    ///
    /// @param new_property Property to be added to the backend.
    virtual void createProperty(const ServerSelector&,
                                const std::pair<std::string, int>& new_property) {
        properties_.push_back(new_property);
    }

protected:

    /// @brief Holds list of properties (simulates database).
    PropertiesList properties_;

};

/// @brief Shared pointer to the @c TestConfigBackend.
typedef boost::shared_ptr<TestConfigBackend> TestConfigBackendPtr;

/// @brief First implementation of the test config backend.
///
/// It simulates being a MySQL backend installed on the
/// "mysql-host" host and running on port 2345.
class TestConfigBackendImpl1 : public TestConfigBackend {
public:

    /// @brief Returns backend type.
    ///
    /// @return "mysql".
    virtual std::string getType() const {
        return (std::string("mysql"));
    }

    /// @brief Returns backend host.
    ///
    /// @return "mysql-host".
    virtual std::string getHost() const {
        return (std::string("mysql-host"));
    }

    /// @brief Returns backend port.
    ///
    /// @return Port number 2345.
    virtual uint16_t getPort() const {
        return (2345);
    }

};

/// @brief Shared pointer to the @c TestConfigBackendImpl1.
typedef boost::shared_ptr<TestConfigBackendImpl1> TestConfigBackendImpl1Ptr;

/// @brief Second implementation of the test config backend.
///
/// It simulates being a Postgres backend installed on the
/// "postgresql-host" host and running on port 1234.
class TestConfigBackendImpl2 : public TestConfigBackend {
public:

    /// @brief Returns backend type.
    ///
    /// @return "postgresql".
    virtual std::string getType() const {
        return (std::string("postgresql"));
    }

    /// @brief Returns backend host.
    ///
    /// @return "postgresql-host".
    virtual std::string getHost() const {
        return (std::string("postgresql-host"));
    }

    /// @brief Returns backend port.
    ///
    /// @return Port number 1234.
    virtual uint16_t getPort() const {
        return (1234);
    }
};

/// @brief Shared pointer to the @c TestConfigBackendImpl2.
typedef boost::shared_ptr<TestConfigBackendImpl2> TestConfigBackendImpl2Ptr;

/// @brief Implements test pool of configuration backends.
///
/// @c BaseConfigBackendPool template provides mechanics for managing the data
/// stored in multiple backends. Server specific pools must extend this class
/// with methods for managing the data appropriate for the server types.
/// This class provides an example pool implementation for managing the
/// "properties" being name/value pairs. It extends the base class with
/// new methods to retrieve a single property and multiple properties. It
/// also adds a method to create new property. Those methods correspond to
/// the ones implemented in the @c TestConfigBackend, but also each of
/// them includes a "database selector" used to indicate the backend to
/// be used.
class TestConfigBackendPool : public BaseConfigBackendPool<TestConfigBackend> {
public:

    /// @brief Retrieves a value of the property.
    ///
    /// @param property_name Name of the property which value should be returned.
    /// @param backend_selector Backend selector. The default value of the selector
    /// is @c UNSPEC which means that the property will be searched in all backends
    /// and the first value found will be returned.
    /// @param server_selector Server selector. The default value is set to @c ALL,
    /// which means that the property for all servers will be returned.
    virtual int getProperty(const std::string& property_name,
                            const BackendSelector& backend_selector =
                            BackendSelector::UNSPEC(),
                            const ServerSelector& server_selector =
                            ServerSelector::ALL()) const {
        int property;

        // If the selector is specified, this method will pick the appropriate
        // backend and will call getProperty method on this backend. If the
        // selector is not specified, this method will iterate over existing
        // backends and call getProperty on them. It will return after finding
        // the first non-zero value of the property. For example, if the first
        // backend contains a non-zero value this value will be returned and
        // the value held in the second backend (if any) won't be fetched.
        // The template arguments specify the returned value type and the
        // argument of the getProperty method.
        getPropertyPtrConst<int, const std::string&>
            (&TestConfigBackend::getProperty, backend_selector, server_selector,
             property, property_name);
        return (property);
    }

    /// @brief Retrieves value of the property.
    ///
    /// @param property_name Name of the property which value should be returned.
    /// @param property_value Value of the property to be retrieved.
    /// @param backend_selector Backend selector. The default value of the selector
    /// is @c UNSPEC which means that the property will be searched in all backends
    /// and the first value found will be returned.
    /// @param server_selector Server selector. The default value is set to @c ALL,
    /// which means that the property for all servers will be returned.
    virtual int getProperty(const std::string& property_name,
                            const int property_value,
                            const BackendSelector& backend_selector =
                            BackendSelector::UNSPEC(),
                            const ServerSelector& server_selector =
                            ServerSelector::ALL()) const {
        int property;
        getPropertyPtrConst<int, const std::string&, int>
            (&TestConfigBackend::getProperty, backend_selector, server_selector,
             property, property_name, property_value);
        return (property);
    }


    /// @brief Retrieves multiple properties.
    ///
    /// @param property_name Name of the properties which should be retrieved.
    /// @param backend_selector Backend selector. The default value of the selector
    /// is @c UNSPEC which means that the properties will be searched in all
    /// backends and the first non-empty list will be returned.
    /// @param server_selector Server selector. The default value is set to @c ALL,
    /// which means that the properties for all servers will be returned.
    virtual PropertiesList getProperties(const std::string& property_name,
                                         const BackendSelector& backend_selector =
                                         BackendSelector::UNSPEC(),
                                         const ServerSelector& server_selector =
                                         ServerSelector::ALL()) const {
        PropertiesList properties;

        // If the selector is specified, this method will pick the appropriate
        // backend and will call getProperties method on this backend. If the
        // selector is not specified, this method will iterate over existing
        // backends and call getProperties on them. It will return after finding
        // the first non-empty list of properties in one of the backends.
        // The template arguments specify the type of the list of properties
        // and the argument of the getProperties method.
        getMultiplePropertiesConst<PropertiesList, const std::string&>
            (&TestConfigBackend::getProperties, backend_selector, server_selector,
             properties, property_name);
        return (properties);
    }

    /// @brief Retrieves all properties.
    ///
    /// @param backend_selector Backend selector. The default value of the selector
    /// is @c UNSPEC which means that the properties will be searched in all
    /// backends and the first non-empty list will be returned.
    /// @param server_selector Server selector. The default value is set to @c ALL,
    /// which means that the properties for all servers will be returned.
    virtual PropertiesList getAllProperties(const BackendSelector& backend_selector =
                                            BackendSelector::UNSPEC(),
                                            const ServerSelector& server_selector =
                                            ServerSelector::ALL()) const {
        PropertiesList properties;

        // This method is similar to getMultiplePropertiesConst but it lacks
        // an argument and it simply returns all properties.
        getAllPropertiesConst<PropertiesList>
            (&TestConfigBackend::getAllProperties, backend_selector, server_selector,
             properties);
        return (properties);
    }

    /// @brief Creates new property in a selected backend.
    ///
    /// @param new_property New property to be added to a backend.
    /// @param backend_selector Backend selector. It has no default value.
    /// @param server_selector The default value is @c ALL which means that
    /// new property is going to be shared by all servers.
    virtual void createProperty(const std::pair<std::string, int>& new_property,
                                const BackendSelector& backend_selector,
                                const ServerSelector& server_selector =
                                ServerSelector::ALL()) {
        createUpdateDeleteProperty<void, const std::pair<std::string, int>&>
            (&TestConfigBackend::createProperty, backend_selector, server_selector,
             new_property);
    }
};

using TestConfigBackendMgr = BaseConfigBackendMgr<TestConfigBackendPool>;

/// @brief Test fixture class for testing @c ConfigBackendMgr.
class ConfigBackendMgrTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ConfigBackendMgrTest()
        : config_mgr_() {
    }

    /// @brief Destructor.
    ///
    /// Removes backend instances.
    ~ConfigBackendMgrTest() {
        config_mgr_.delAllBackends();
    }

    /// @brief Creates example database backend called "mysql".
    ///
    /// It uses @c TestConfigBackendImpl1.
    void addTestMySQLBackend() {
        config_mgr_.registerBackendFactory("mysql", [](const DatabaseConnection::ParameterMap&)
                                          -> TestConfigBackendPtr {
            return (TestConfigBackendImpl1Ptr(new TestConfigBackendImpl1()));
        });

        config_mgr_.addBackend("type=mysql");
    }

    /// @brief Creates example database backend called "postgresql".
    ///
    /// It uses @c TestConfigBackendImpl2.
    void addTestPgSQLBackend() {
        config_mgr_.registerBackendFactory("postgresql", [](const DatabaseConnection::ParameterMap&)
                                          -> TestConfigBackendPtr {
            return (TestConfigBackendImpl2Ptr(new TestConfigBackendImpl2()));
        });

        // Actually create the backends.
        config_mgr_.addBackend("type=postgresql");
    }

    /// @brief Creates two example database backends called "mysql" and "postgresql".
    ///
    /// It uses @c TestConfigBackendImpl1 and @c TestConfigBackendImpl2.
    void addTestBackends() {
        addTestMySQLBackend();
        addTestPgSQLBackend();
    }

    /// @brief Adds test data into the backends.
    void addTestData() {
        // Add two properties with different names into the first backend.
        config_mgr_.getPool()->createProperty(std::make_pair("dogs", 1),
                                             BackendSelector(BackendSelector::Type::MYSQL));
        config_mgr_.getPool()->createProperty(std::make_pair("wolves", 3),
                                             BackendSelector(BackendSelector::Type::MYSQL));

        // Add two properties into the second backend. Both properties share the
        // name so as we can test retrieving multiple records from the same backend.
        config_mgr_.getPool()->createProperty(std::make_pair("cats", 2),
                                             BackendSelector(BackendSelector::Type::POSTGRESQL));
        config_mgr_.getPool()->createProperty(std::make_pair("cats", 4),
                                             BackendSelector(BackendSelector::Type::POSTGRESQL));
    }

    /// Instance of the test configuration manager.
    TestConfigBackendMgr config_mgr_;
};

// Test that selector can be left "unspecified" if there is only one backend,
// when manipulating the data.
TEST_F(ConfigBackendMgrTest, createPropertySingleBackendUnspec) {
    addTestMySQLBackend();

    ASSERT_NO_THROW(
        config_mgr_.getPool()->createProperty(std::make_pair("dogs", 1),
                                              BackendSelector(BackendSelector::Type::UNSPEC))
    );

    // We should be able to retrieve stored value without having to specify
    // the backend.
    EXPECT_EQ(1, config_mgr_.getPool()->getProperty("dogs"));
}

// Test that selector must be specified if there is more than one backend,
// when manipulating the data.
TEST_F(ConfigBackendMgrTest, createPropertyTwoBackendsUnspec) {
    addTestBackends();

    // Backend must be selected if there is more than one backend present.
    EXPECT_THROW(
        config_mgr_.getPool()->createProperty(std::make_pair("dogs", 1),
                                              BackendSelector(BackendSelector::Type::UNSPEC)),
        NoSuchDatabase
    );
}

// Test that exception is thrown when multiple backends are selected.
TEST_F(ConfigBackendMgrTest, createPropertyAmbiguousSelection) {
    addTestBackends();

    // Add another MySQL backend to cause the selection to give ambiguous
    // result.
    config_mgr_.addBackend("type=mysql");

    EXPECT_THROW(
        config_mgr_.getPool()->createProperty(std::make_pair("dogs", 1),
                                              BackendSelector(BackendSelector::Type::MYSQL)),
        AmbiguousDatabase
    );
}

// Test that a single property can be retrieved from a selected backend.
TEST_F(ConfigBackendMgrTest, getSingleProperty) {

    addTestBackends();
    addTestData();

    // Backend is not specified, so it should find the dogs in first one and
    // cats in the second one.
    EXPECT_EQ(1, config_mgr_.getPool()->getProperty("dogs"));
    EXPECT_EQ(2, config_mgr_.getPool()->getProperty("cats"));

    // No dogs in the postgresql backend and no cats in mysql backend.
    EXPECT_EQ(0, config_mgr_.getPool()->getProperty("dogs",
                                                   BackendSelector(BackendSelector::Type::POSTGRESQL)));
    EXPECT_EQ(0, config_mgr_.getPool()->getProperty("cats",
                                                   BackendSelector(BackendSelector::Type::MYSQL)));

    // If the selectors are pointing to the right databases, the dogs and cats
    // should be returned properly.
    EXPECT_EQ(1, config_mgr_.getPool()->getProperty("dogs",
                                                   BackendSelector(BackendSelector::Type::MYSQL)));
    EXPECT_EQ(2, config_mgr_.getPool()->getProperty("cats",
                                                   BackendSelector(BackendSelector::Type::POSTGRESQL)));

    // Also make sure that the variant of getProperty function taking two arguments
    // would return the value.
    EXPECT_EQ(1, config_mgr_.getPool()->getProperty("dogs", 1,
                                                   BackendSelector(BackendSelector::Type::MYSQL)));

    // If the value is not matching it should return 0.
    EXPECT_EQ(0, config_mgr_.getPool()->getProperty("dogs", 2,
                                                   BackendSelector(BackendSelector::Type::MYSQL)));

    // Try to use the backend that is not present.
    EXPECT_THROW(config_mgr_.getPool()->getProperty("cats",
                                                    BackendSelector(BackendSelector::Type::CQL)),
                 NoSuchDatabase);
}

// Test that multiple properties can be retrieved with filtering.
TEST_F(ConfigBackendMgrTest, getMultipleProperties) {

    addTestBackends();
    addTestData();

    // There is one dogs entry in mysql.
    PropertiesList mysql_list =
        config_mgr_.getPool()->getProperties("dogs",
                                            BackendSelector(BackendSelector::Type::MYSQL));
    ASSERT_EQ(1, mysql_list.size());

    // There is also one wolves entry in mysql.
    mysql_list = config_mgr_.getPool()->getProperties("wolves",
                                                     BackendSelector(BackendSelector::Type::MYSQL));
    ASSERT_EQ(1, mysql_list.size());

    // There are two cats entries in postgresql.
    PropertiesList postgresql_list =
        config_mgr_.getPool()->getProperties("cats",
                                            BackendSelector(BackendSelector::Type::POSTGRESQL));
    ASSERT_EQ(2, postgresql_list.size());

    // Try to use the backend that is not present.
    EXPECT_THROW(config_mgr_.getPool()->getProperties("cats",
                                                      BackendSelector(BackendSelector::Type::CQL)),
                 NoSuchDatabase);

}

// Test that all properties can be retrieved from each backend.
TEST_F(ConfigBackendMgrTest, getAllProperties) {

    addTestBackends();
    addTestData();

    // The mysql backend holds two entries.
    PropertiesList mysql_list =
        config_mgr_.getPool()->getAllProperties(BackendSelector(BackendSelector::Type::MYSQL));
    ASSERT_EQ(2, mysql_list.size());

    // The postgresql backends also holds two entries.
    PropertiesList postgresql_list =
        config_mgr_.getPool()->getAllProperties(BackendSelector(BackendSelector::Type::POSTGRESQL));
    ASSERT_EQ(2, postgresql_list.size());

    // Try to use the backend that is not present.
    EXPECT_THROW(config_mgr_.getPool()->getProperties("cats",
                                                      BackendSelector(BackendSelector::Type::CQL)),
                 NoSuchDatabase);
}

// Verify that unregistering a factory works.
TEST_F(ConfigBackendMgrTest, unregister) {

    // Verify we can't remove what is not there.
    ASSERT_FALSE(config_mgr_.unregisterBackendFactory("mysql"));

    // Add both MySQL and Postgresql backends
    addTestBackends();

    // Backend should be present.
    EXPECT_NO_THROW(config_mgr_.getPool()->getProperties("cats",
                                                         BackendSelector(BackendSelector::Type::MYSQL)));

    // Verify that unregistering MySQL factory returns true.
    ASSERT_TRUE(config_mgr_.unregisterBackendFactory("mysql"));

    // Verify that the factory is actually gone.
    ASSERT_THROW(config_mgr_.addBackend("type=mysql"), db::InvalidType);

    // Verify we can't remove what is not there.
    ASSERT_FALSE(config_mgr_.unregisterBackendFactory("mysql"));

    // Try to use the backend that is not present.
    EXPECT_THROW(config_mgr_.getPool()->getProperties("cats",
                                                       BackendSelector(BackendSelector::Type::MYSQL)),
                 NoSuchDatabase);
}

}
