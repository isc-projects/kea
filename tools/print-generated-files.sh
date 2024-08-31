#!/bin/sh

# Copyright (C) 2020-2024 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Usage:
#
# ./tools/print-generated-files.sh [-d|--debug] [-h|--help] [-a|--amend]
#
# Run from the root of the repository to get the list of generated files. They
# may or may not be part of the repository. These consist of messages, parser
# files and built sources (as called in Makefile.am files). While messages and
# parser files are included with the source files, the built sources are only
# created when building or some of them included in the Kea installation.

# shellcheck disable=SC2013
# SC2013: To read lines rather than words, pipe/redirect to a 'while read' loop.
# reason: `while read` reads lines, we need to read words

# shellcheck disable=SC2044
# SC2044: For loops over find output are fragile. Use find -exec or a while read loop.
# reason: I need to embed complicated logic inside the for, avoiding SC2044
# makes us run into other problems.

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
  [-a|--amend]                 amend .gitattributes
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
    # [-d|--debug]                 enable debug mode, showing every executed command
    '-d'|'--debug') set -vx ;;

    # [-h|--help]                  print usage (this text)
    '-h'|'--help') print_usage; exit 0 ;;

    # [-a|--amend]                 amend .gitattributes
    '-a'|'--amend') amend=true ;;

    # Unrecognized argument
    *)
    printf "${red}ERROR: Unrecognized argument '%s'${reset}\\n" "${1}" 1>&2; print_usage; exit 1 ;;
  esac; shift
done

# Default parameters
test -z "${amend+x}" && amend=false

# Change directory to root path.
root_path=$(cd "$(dirname "${0}")/.." && pwd)
cd "${root_path}"

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

# Print the lines between two matching regex patterns from a file. Excludes the
# lines that contain the patterns themselves. Matches only the first occurrence.
print_lines_between_matching_patterns() {
  mandatory_commands sed

  local start_pattern="${1}"; shift
  local end_pattern="${1}"; shift
  local file="${1}"; shift

  # Escape all slashes.
  start_pattern=$(printf '%s' "${start_pattern}" | sed 's#\/#\\\/#g')
  end_pattern=$(printf '%s' "${end_pattern}" | sed 's#\/#\\\/#g')

  # Print with sed.
  sed -n "/${start_pattern}/,/${end_pattern}/p;/${end_pattern}/q" "${file}" \
    | sed '$d' | tail -n +2
}

# Print file name if a file with that name exists.
print_file_name() {
  local file_name="${1}"
  if test -f "${file_name}"; then
    printf '%s\n' "${file_name}" | cut -d '/' -f '2-'
  fi
}

# Generated messages
# shellcheck disable=SC1003
# SC1003: Want to escape a single quote? echo 'This is how it'\''s done'
# reason: No, we don't want to escape a single quote, we want a backslash.
print_generated_messages() {
  local makefile_am="${1}"; shift
  local directory="${1}"; shift

  for j in $(grep -F 'messages:' "${makefile_am}" | cut -d ':' -f '2-' | \
    cut -d '\' -f 1); do
    print_file_name "${directory}/${j}"
  done

  # Include message files that span multiple lines in the Makefile.am.
  for j in $(print_lines_between_matching_patterns 'messages:' '@echo' "${makefile_am}" | \
    cut -d ':' -f '2-' | cut -d '\' -f 1); do
    print_file_name "${directory}/${j}"
  done
}

# Generated parsers
print_generated_parsers() {
  local makefile_am="${1}"; shift
  local directory="${1}"; shift

  for j in $(grep -F 'parser:' "${makefile_am}" | cut -d ':' -f '2-'); do
    print_file_name "${directory}/${j}"
  done
}

# Other generated files
print_built_sources() {
  local makefile_am="${1}"; shift
  local directory="${1}"; shift

  for j in $(grep -E 'BUILT_SOURCES (=|\+=)' "${makefile_am}" | cut -d '=' -f '2-'); do
    print_file_name "${directory}/${j}"
  done
}

# Print all files of interest sorted alphabetically.
print_all_sorted() {
  local built_sources="${1-true}"

  for i in $(find . -type f -name 'Makefile.am'); do
    directory=$(dirname "${i}")
    print_generated_messages "${i}" "${directory}"
    print_generated_parsers "${i}" "${directory}"
    if ${built_sources}; then
      print_built_sources "${i}" "${directory}"
    fi
  done | sort -uV
}

mandatory_commands cut find grep sort

if "${amend}"; then
  # Write to .gitattributes.
  find . -type f -name '.gitattributes' -exec rm -f {} \;
  for i in $(print_all_sorted false); do
    # Align to 32 characters.
    name="/$(basename "${i}")"
    length=$(( 32 - ${#name} ))

    printf "%s%${length}s -diff merge=ours\\n" "${name}" ' ' >> \
      "$(dirname "${i}")/.gitattributes"
  done
else
  print_all_sorted
fi
