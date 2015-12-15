// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/command_interpreter.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <string>

namespace isc {
namespace dhcp {
namespace test {

using namespace isc;
using namespace isc::data;

bool errorContainsPosition(ConstElementPtr error_element,
                           const std::string& file_name) {
    if (error_element->contains(isc::config::CONTROL_RESULT)) {
        ConstElementPtr result = error_element->get(isc::config::CONTROL_RESULT);
        ConstElementPtr text = error_element->get(isc::config::CONTROL_TEXT);
        if (!result || (result->getType() != Element::integer) || !text
            || (text->getType() != Element::string)) {
            return (false);
        }

        // Get the error message in the textual format.
        std::string error_string = text->stringValue();

        // The position of the data element causing an error has the following
        // format: <filename>:<linenum>:<pos>. The <filename> has been specified
        // by a caller, so let's first check if this file name is present in the
        // error message.
        size_t pos = error_string.find(file_name);

        // If the file name is present, check that it is followed by the line
        // number and position within the line.
        if (pos != std::string::npos) {
            // Split the string starting at the begining of the <filename>. It
            // should return a vector of strings.
            std::string sub = error_string.substr(pos);
            std::vector<std::string> split_pos;
            boost::split(split_pos, sub, boost::is_any_of(":"),
                         boost::algorithm::token_compress_off);

            // There should be at least three elements: <filename>, <linenum>
            // and <pos>. There can be even more, because one error string may
            // contain more positions of data elements for multiple
            // configuration nesting levels. We want at least one position.
            if ((split_pos.size() >= 3) && (split_pos[0] == file_name) &&
                (!split_pos[1].empty()) && !(split_pos[2].empty())) {

                // Make sure that the line number comprises only digits.
                for (int i = 0; i < split_pos[1].size(); ++i) {
                    if (!isdigit(split_pos[1][i])) {
                        return (false);
                    }
                }

                // Go over digits of the position within the line.
                int i = 0;
                while (isdigit(split_pos[2][i])) {
                    ++i;
                }

                // Make sure that there has been at least one digit and that the
                // position is followed by the paren.
                if ((i == 0) || (split_pos[2][i] != ')')) {
                    return (false);
                }

                // All checks passed.
                return (true);
            }
        }
    }

    return (false);
}

}
}
}
