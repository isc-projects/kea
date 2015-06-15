#!/bin/sh
# Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
#
# This script embeds config.report into src/bin/cfgrpt/config_report.cc
# Called by configure
#

dest=$1

# Initializes
cat > $dest

# Header
cat >> $dest << END
// config_report.cc. Generated from config.report by tools/mk_cfgrpt_header.sh

namespace isc {
namespace detail {

extern const char* const config_report[] = {
END

# Body: escape '\'s and '"'s, preprend '    ";;;; ' and append '",'
sed -e 's/\\/\\\\/g' -e 's/"/\\"/g' -e 's/^/    ";;;; /' -e 's/$/",/' \
    < config.report >> $dest

# Trailer
cat >> $dest <<END
    ""
};

}
}
END
