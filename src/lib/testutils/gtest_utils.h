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

/// @brief Expect two values to be equal with a given margin of error.
///
/// Output is similar to official gtest expect macro outputs.
/// Static casts avoid comparison of integers of different signs.
///
/// @param val1 the first value being tested
/// @param val2 the second value being tested
/// @param margin the allowed margin of error
#define EXPECT_EQ_MARGIN(val1_statement, val2_statement, margin_statement)                \
    {                                                                                     \
        auto const val1(val1_statement);                                                  \
        auto const val2(static_cast<decltype(val1)>(val2_statement));                     \
        auto const margin(static_cast<decltype(val1)>(margin_statement));                 \
        if (val1 < val2 && val1 + margin < val2 || val2 < val1 && val2 + margin < val1) { \
            ADD_FAILURE() << "Expected equality of these values:\n"                       \
                          << "  " << #val1_statement << "\n"                              \
                          << "    Which is: " << val1 << "\n"                             \
                          << "  " << #val2_statement << "\n"                              \
                          << "    Which is: " << val2 << "\n"                             \
                          << "With a margin of error of:\n"                               \
                          << "  " << #margin_statement << "\n"                            \
                          << "    Which is: " << margin << "";                            \
        }                                                                                 \
    }

/// @brief Expect a value to be between two other given values.
///
/// Output is similar to official gtest expect macro outputs.
/// Static casts avoid comparison of integers of different signs.
///
/// @param value_statement the statement for the value being tested
/// @param low_statement the low reference value being tested against
/// @param high_statement the high reference value being tested against
#define EXPECT_IN_RANGE(value_statement, low_statement, high_statement)                  \
    {                                                                                    \
        auto const value(value_statement);                                               \
        auto const low(static_cast<decltype(value)>(low_statement));                     \
        auto const high(static_cast<decltype(value)>(high_statement));                   \
        if (value < low || high < value) {                                               \
            ADD_FAILURE() << "Expected this value:\n"                                    \
                          << "  " << #value_statement << "\n"                            \
                          << "    Which is: " << value << "\n"                           \
                          << "To be in range:\n"                                         \
                          << "  [" << #low_statement << ", " << #high_statement << "]\n" \
                          << "    Which is: [" << low << ", " << high << "]";            \
        }                                                                                \
    }

}  // namespace test
}  // namespace isc

#endif // GTEST_UTILS_H
