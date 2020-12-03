#!/bin/sh

# Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Check revisions
#
# This developer script verifies versions in module contents match
# the version in the name.
# Requires yanglint to translate YANG to YIN formats.
# Fixme: use xlstproc to extract the revision.

# Exit with error if commands exit with non-zero and if undefined variables are
# used.
set -eu

# Change directory to the YANG modules' directory.
script_path=$(cd "$(dirname "${0}")" && pwd)
cd "${script_path}/.."

error=0
for m in *.yang
do
    rev1=$(yanglint -f yin "${m}" | grep '<revision date=' | head -1 | sed \
 's/.*<revision date="\([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]\)".*/\1/')
    rev2=$(echo "${m}" | sed \
 's/.*@\([0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]\)\..*/\1/')

    if test "${rev1}" != "${rev2}"
    then
        error=1
        printf 'revision mismatch on %s got %s\n' "${m}" "${rev1}"
    fi
done
exit $error
