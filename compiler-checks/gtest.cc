#include <gtest/gtest.h>

// musl's mallocng memory allocator stupidly crash for test names that are
// lengthier than 16 characters. Hence the long test name.
TEST(Fixture, testWithLongLongLongName) {
    EXPECT_LT(1, 2);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
