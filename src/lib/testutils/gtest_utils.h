// Copyright (C) 2019-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GTEST_UTILS_H
#define GTEST_UTILS_H

#include <gtest/gtest.h>

namespace isc {
namespace test {

/// @brief Verifies an expected exception type and message
///
/// If the statement does not generate the expected exception
/// containing the expected message it will generate a non-fatal
/// failure.
///
/// @param statement - statement block to execute
/// @param etype - type of exception expected
/// @param emsg - exact content expected to be returned by ex.what()
#define EXPECT_THROW_MSG(statement,etype,emsg) \
{ \
    try { \
        statement; \
        ADD_FAILURE() << "no exception, expected: " << #etype; \
    } catch (const etype& ex)  { \
        EXPECT_EQ(std::string(ex.what()), emsg); \
    } catch (...) { \
        ADD_FAILURE() << "wrong exception type thrown, expected: " << #etype; \
    } \
} \

/// @brief Verifies an expected exception type and message
///
/// If the statement does not generate the expected exception
/// containing the expected message it will generate a fatal
/// failure.
///
/// @param statement - statement block to execute
/// @param etype - type of exception expected
/// @param emsg - exact content expected to be returned by ex.what()
#define ASSERT_THROW_MSG(statement,etype,emsg) \
{ \
    try { \
        statement; \
        GTEST_FAIL() << "no exception, expected: " << #etype; \
    } catch (const etype& ex)  { \
        ASSERT_EQ(std::string(ex.what()), emsg); \
    } catch (...) { \
        GTEST_FAIL() << "wrong exception type thrown, expected: " << #etype; \
    } \
} \

/// @brief Adds a non-fatal failure with exception info, if the given
/// expression throws.  Note the type name emitted may be mangled.
///
/// @param statement - statement block to execute
#define EXPECT_NO_THROW_LOG(statement) \
{ \
    try { \
        statement; \
    } catch (const std::exception& ex)  { \
        ADD_FAILURE() << #statement <<  " threw type: " << typeid(ex).name() \
                      << ", what: " << ex.what(); \
    } catch (...) { \
        ADD_FAILURE() << #statement <<  "threw non-std::exception"; \
    } \
} \

/// @brief Generates a fatal failure with exception info, if the given
/// expression throws.  Note the type name emitted may be mangled.
///
/// @param statement - statement block to execute
#define ASSERT_NO_THROW_LOG(statement) \
{ \
    try { \
        statement; \
    } catch (const std::exception& ex)  { \
        GTEST_FAIL() << #statement <<  " threw type: " << typeid(ex).name() \
                     << ", what: " << ex.what(); \
    } catch (...) { \
        GTEST_FAIL() << #statement <<  " threw non-std::exception"; \
    } \
} \

/// @brief Skip a test without failure if the given expression is true.
///
/// SKIP_IF(exp) provides a means to exit a test without failing
/// if the given expression is true.  This works around the lack of
/// GTEST_SKIP prior to googletest 1.10.
///
/// @note This macro cannot be used in testing::Test::SetUp()
/// to skip tests (unless running with googletest 1.10 or later).
/// It must be used directly within the body of each unit test.
///
/// @param expression logical expression to execute
#ifndef GTEST_SKIP
#define SKIP_IF(expression) \
{ \
    if (expression) { \
        auto const info = ::testing::UnitTest::GetInstance()->current_test_info(); \
        std::cerr << "SKIPPING: " << info->test_case_name() << ":" << info->name() \
                  << ": '" << #expression << "' is true" << std::endl; \
        return; \
    } \
}
#else
#define SKIP_IF(expression) \
{ \
    if (expression) { \
        auto const info = ::testing::UnitTest::GetInstance()->current_test_info(); \
        GTEST_SKIP() << "SKIPPING: " << info->test_case_name() << ":" << info->name() \
                  << ": '" << #expression << "' is true"; \
    } \
}
#endif

}  // namespace test
}  // namespace isc

#endif // GTEST_UTILS_H
