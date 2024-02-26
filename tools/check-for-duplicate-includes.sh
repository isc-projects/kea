#!/bin/sh

# Copyright (C) 2020-2024 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Usage:
#
# check-for-duplicate-includes.sh [-d|--debug] [-h|--help]
#
# Run from the root of Kea repository to detect duplicate `#include`  lines.

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

# Get the source files that have at least one '#include' line minus the
# generated files.
get_source_files() {
  mandatory_commands cut find grep sed sort

  # Get the files that have at least one include line.
  source_files=$(cd "${root_path}" && find . -type f | grep -Fv '.git' | \
    grep -E '\.cc$|\.h$' | xargs grep -El '#include' | \
    cut -d ':' -f 1 | sort -uV)

  # Filter out the generated files.
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

# Writing to file and the -u argument are required to make a POSIX worthy diff.
# So it gets it's own function.
posix_diff() {
  local left="${1}"; shift
  local right="${1}"; shift

  # Print to files.
  left_file="/tmp/${$}-left"
  right_file="/tmp/${$}-right"
  printf '%s\n' "${left}" > "${left_file}"
  printf '%s\n' "${right}" > "${right_file}"

  diff -u "${left_file}" "${right_file}"

  # Clean up.
  rm -f "${left_file}" "${right_file}"
}

# Get root path.
root_path=$(cd "$(dirname "${0}")/.." && pwd)

# Generated files will be filtered out.
filtered_out=$("${root_path}/tools/print-generated-files.sh")
# Exceptions:
# src/lib/asiolink/asio_wrapper.h includes <boost/asio.hpp> in both
# conditionals of an #ifdef.
filtered_out="${filtered_out}
src/lib/asiolink/asio_wrapper.h
"

found=false
for i in $(get_source_files); do
  includes=$(grep -E '^#include' "${i}" | sort -V)
  unique_includes=$(grep -E '^#include' "${i}" | sort -uV)
  diff=$(posix_diff "${includes}" "${unique_includes}" | \
    grep -F '#include' | grep -E '^-|^\+' | sed -E 's/^([^-+ ]*)[-+ ]/\1/' )
  if test -n "${diff}"; then
    printf '%s has the following duplicate includes:\n%s\n\n' "${i}" "${diff}"
    found=true
  fi
done

if "${found}"; then
  exit 1
fi
