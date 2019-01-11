// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SYSREPO_SETUP_H
#define SYSREPO_SETUP_H

#include <config.h>

#include <yang/translator.h>
#include <gtest/gtest.h>

namespace isc {
namespace yang {
namespace test {

/// @brief Test Fixture template for translator tests.
///
/// @tparam Name The name of the translator to test.
/// @tparam Type The type of the translator to test.
template<char const* Name, typename Type>
class GenericTranslatorTest : public ::testing::Test {
public:

    /// @brief Constructor.
    GenericTranslatorTest() : conn_(), sess_(), t_obj_() { }

    /// @brief useModel
    ///
    /// Open a sysrepo session and create a translator object using
    /// the given model.
    ///
    /// @param model The model to use.
    void useModel(std::string model) {
        std::string full_name =
            "translator " + std::string(Name) + " unittests";
#ifndef HAVE_PRE_0_7_6_SYSREPO
        conn_.reset(new sysrepo::Connection(full_name.c_str()));
        sess_.reset(new sysrepo::Session(conn_, SR_DS_CANDIDATE));
#else
        conn_.reset(new Connection(full_name.c_str()));
        sess_.reset(new Session(conn_, SR_DS_CANDIDATE));
#endif
        EXPECT_NO_THROW(t_obj_.reset(new Type(sess_, model)));
    }

    /// @brief Destructor.
    ///
    /// Destroy all objects.
    virtual ~GenericTranslatorTest() {
        t_obj_.reset();
        sess_.reset();
        conn_.reset();
    }

    /// @brief Sysrepo connection.
#ifndef HAVE_PRE_0_7_6_SYSREPO
    sysrepo::S_Connection conn_;
#else
    S_Connection conn_;
#endif

    /// @brief Sysrepo session.
#ifndef HAVE_PRE_0_7_6_SYSREPO
    sysrepo::S_Session sess_;
#else
    S_Session sess_;
#endif

    /// @brief Shared pointer to the transaction object.
    boost::shared_ptr<Type> t_obj_;
};

} // namespace test
} // namespace yang
} // namespace isc

#endif // SYSREPO_SETUP_H
