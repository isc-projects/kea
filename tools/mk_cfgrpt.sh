#!/bin/sh
# Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# This script embeds config.report into src/bin/cfgrpt/config_report.cc
# Called by configure

# shellcheck disable=SC2129
# SC2129: Consider using { cmd1; cmd2; } >> file instead of individual redirects.

# Exit with error if commands exit with non-zero and if undefined variables are
# used.
set -eu

report_file="${1-}"
dest="${2-}"

if [ -z "${report_file}" ]
then
    echo "ERROR mk_cfgrpt.sh - expected report_file parameter"
    exit 1
fi

if [ -z "${dest}" ]
then
    echo "ERROR mk_cfgrpt.sh - expected dest parameter"
    exit 1
fi

if [ ! -f "${report_file}" ]
then
    echo "ERROR mk_cfgrpt.sh - input report: $report_file does not exist"
    exit 1
fi

# Initializes
if ! cat /dev/null > "${dest}"
then
    echo "ERROR mk_cfgrpt.sh - cannot create config output file: ${dest}"
    exit 2
fi

# Header
cat >> "${dest}" << END
// config_report.cc. Generated from config.report by tools/mk_cfgrpt.sh

namespace isc {
namespace detail {

extern const char* const config_report[] = {
END

# Body: escape '\'s and '"'s, preprend '    ";;;; ' and append '",'
sed -e 's/\\/\\\\/g' -e 's/"/\\"/g' -e 's/^/    ";;;; /' -e 's/$/",/' \
    < "${report_file}" >> "${dest}"

# Trailer
cat >> "${dest}" <<END
    ""
};

}
}
END
