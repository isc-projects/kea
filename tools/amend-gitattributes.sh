#!/bin/sh

# Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Exit with error if commands exit with non-zero and if undefined variables are
# used.
set -eu

root_path=$(cd "$(dirname "${0}")/.." && pwd)
cd "${root_path}"

# Write to .gitattributes.
find . -type f -name '.gitattributes' -exec rm -f {} \;
for i in $(./tools/print-generated-files.sh); do
    # We need to be lenient because we call this script in premium too. Files might not exist.
    if test ! -f "${i}"; then
        continue
    fi

    # Align to 32 characters.
    dir=$(dirname "${i}")
    name="/$(basename "${i}")"
    length=$(( 32 - ${#name} ))

    printf "%s%${length}s -diff merge=ours\\n" "${name}" ' ' >> "${dir}/.gitattributes"
done
