#!/bin/sh

# Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Check hashes
#
# This developer script verifies recorded hashes still match the
# result of SHA-256 checksums of the YIN format.
# Requires yanglint to translate YANG to YIN formats and openssl
# for a system independent SHA-256.

# Exit with error if commands exit with non-zero and if undefined variables are
# used.
set -eu

# Change directory to the YANG modules' directory.
script_path=$(cd "$(dirname "${0}")" && pwd)
cd "${script_path}/.."

amend=false
if test "${1-}" = '-a' || test "${1-}" = '--amend'; then
    amend=true
fi

exit_code=0
for m in *.yang
do
    hash1=$(yanglint -f yin "${m}" | openssl dgst -sha256 | sed 's/(stdin)= //')
    h="hashes/$(basename "${m}" .yang).hash"
    if test -f "${h}"
    then
        hash2=$(cat "${h}")
        if test "$hash1" != "$hash2"
        then
            exit_code=$((exit_code | 1))
            printf 'hash mismatch on %s expected %s in %s\n' "${m}" "${hash1}" "${h}"
            if "${amend}"; then
                printf '%s\n' "${hash1}" > "${h}"
            fi
        fi
    else
        exit_code=$((exit_code | 2))
        printf 'missing hash file %s for %s\n' "${h}" "${m}"
        if "${amend}"; then
            printf '%s\n' "${hash1}" > "${h}"
        fi
    fi
done

exit "${exit_code}"
