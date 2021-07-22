#!/bin/sh

# Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Usage:
#
# ./tools/add-config-h.sh [-d|--debug] [-h|--help] [-n|--name-only]
#
# Run from the root of the repository to add `#include <config.h>` lines to
# non-generated .cc files.

# shellcheck disable=SC1004
# SC1004: This backslash+linefeed is literal. Break outside single quotes if you
# just want to break the line.
# Reason: backslash+linefeed inside single quotes in sed are needed for
# POSIX-compliance. \n works only with GNU sed.

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
  [-n|--name-only]             only show names of files that will be modified
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

    # [-n|--name-only]         only show names of files that will be modified
    '-n'|'--name-only') name_only=true ;;

    # Unrecognized argument
    *)
    printf "${red}ERROR: Unrecognized argument '%s'${reset}\\n" "${1}" 1>&2; print_usage; exit 1 ;;
  esac; shift
done

# Default parameters
test -z "${name_only+x}" && name_only=false

# Get root path.
root_path=$(cd "$(dirname "${0}")/.." && pwd)

# Get source files that are missing an '#include <config.h>' line.
get_source_files() {
  mandatory_commands cut find grep sed sort

  # Get the files that are missing the include.
  source_files=$(cd "${root_path}" && find . -type f | grep -Fv '.git' | \
    grep -E '\.cc$' | xargs grep -EL '#include\s*[\"|\<]config.h[\"|\>]' | \
    cut -d ':' -f 1 | sort -uV)

  # Filter out generated files.
  for file in ${filtered_out}; do
    source_files=$(printf '%s\n' "${source_files}" | grep -Fv "${file}" | sed '/^$/d')
  done

  printf '%s' "${source_files}"
}

# Check if given commands are available and if not, then warn the user that they
# need to be installed for the script to work and then exit with error code.
mandatory_commands() {
  while test ${#} -gt 0; do
    if ! command -v "${1}" > /dev/null 2>&1; then
      printf "${red}%s${reset} is mandatory.\\n" "${1}" >&2
      exit 3
    fi
    shift
  done
}

# Generated files will be filtered out.
filtered_out=$("${root_path}/tools/print-generated-files.sh")

if "${name_only}"; then
  # Only display file names.
  get_source_files
  if test -n "${source_files}"; then
    printf '\n'
  fi
else
  # Create a temporary file.
  file=$(mktemp)

  # Run once for files that have at least one include.
  for i in $(get_source_files); do
    sed '1,/#include/s/#include/#include <config.h>\
\
#include/' "${i}" > "${file}"
    mv "${file}" "${i}"
  done

  # Run again for files that don't have any includes. The second command would
  # work for the first case, but the first command is more elegant.
  for i in $(get_source_files); do
    sed '1,/\(\/\/ file, You can obtain one.*\)/s/\(\/\/ file, You can obtain one.*\)/\1\
\
#include <config.h>/' "${i}" > "${file}"
    mv "${file}" "${i}"
  done

  # Cleanup temporary file.
  rm -f "${file}"
fi
