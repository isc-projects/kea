#!/bin/sh

# Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Usage:
#
# ./tools/shellcheck-all.sh [-d|--debug] [-h|--help]
#
# Run to shellcheck all shell scripts inside this repository.

# Exit with error if commands exit with non-zero and if undefined variables are
# used.
set -eu

# Print usage.
print_usage() {
  printf \
'Usage: %s {{options}}
Options:
  [-d|--debug]                 enable debug mode, showing every executed command
  [-h|--help]                  print usage (this text)
' \
    "$(basename "${0}")"
}

# Define some ANSI color codes.
if test -t 1; then
  red='\033[91m'
  reset='\033[0m'
else
  red=
  reset=
fi

# Parse parameters.
while test ${#} -gt 0; do
  case "${1}" in
    # [-d|--debug]             enable debug mode, showing every executed command
    '-d'|'--debug') set -vx ;;

    # [-h|--help]              print usage (this text).
    '-h'|'--help') print_usage; exit 0 ;;

    # Unrecognized argument
    *)
    printf "${red}ERROR: Unrecognized argument '%s'${reset}\\n" "${1}" 1>&2; print_usage; exit 1 ;;
  esac; shift
done

# Change directory to Kea' top level build directory.
root_path=$(cd "$(dirname "${0}")/.." && pwd)
cd "${root_path}"

# shellcheck disable=SC2046
# SC2046: Quote this to prevent word splitting.
# Reason: We explicitly want the parameters split.
shellcheck $(grep -F 'SHELLCHECK_OPTS:' ./.gitlab-ci.yml | cut -d '"' -f 2 | xargs | sort -uV) $(grep -F 'SCRIPTS+=' ./.gitlab-ci.yml | cut -d '"' -f 2 | xargs | sort -uV)
