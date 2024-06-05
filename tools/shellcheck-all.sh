#!/bin/sh

# Copyright (C) 2020-2024 Internet Systems Consortium, Inc. ("ISC")
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

# Disable shellcheck warnings:
# SC1117: Backslash is literal in "\/". Prefer explicit escaping: "\\/".
# SC2119: Use "$@" if function's $1 should mean script's $1.
# SC2039: In POSIX sh, 'local' is undefined.
# SC3043: In POSIX sh, 'local' is undefined.
shellcheck_opts="--exclude=SC1117 --exclude=SC2119 --exclude=SC2039 --exclude=SC3043"

files="$(find . -type f -name '*.sh' -or -name '*.sh.in' | sort)"

# Add shell script files that don't end in .sh or .sh.in.
for i in \
  src/bin/admin/kea-admin.in \
  src/bin/keactrl/keactrl.conf.in \
  src/bin/keactrl/keactrl.in \
; do
  if test -f "${i}"; then
    files="${files} ${i}"
  fi
done

# shellcheck disable=SC2046
# SC2046: Quote this to prevent word splitting.
# Reason: We explicitly want the parameters split.
shellcheck ${shellcheck_opts} ${files}
