#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

std::string nodiff(std::string text) {
    std::vector<std::string> lines;
    boost::split(lines, text, boost::is_any_of("\n"));
    using namespace testing::internal;
    return (edit_distance::CreateUnifiedDiff(lines, lines));
}

int main() {
    return 0;
}
