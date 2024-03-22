#!/bin/sh

# Copyright (C) 2020-2024 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Usage:
#
# ./tools/uncrustify.sh [-d|--debug] [-h|--help] [$directory|$file ...]
#
# Run from the root of the repository to format all C++ files under specified
# directories or specified files or current directory in case of no arguments.

#------------------------------------------------------------------------------#

set -eu

# Customizations
extensions_regex='(\.cpp|\.cc|\.C|\.cxx|\.m|\.hpp|\.hh|\.h|\.H|\.hxx|\.tpp)$'

# Print usage.
print_usage() {
  printf \
'Usage: %s {{options}}
Options:
  [-d|--debug]                 enable debug mode, showing every executed command
  [-h|--help]                  print usage (this text)
  [$directory|$file ...]       one or multiple files to format; if directories
                               are passed instead, they are searched for all C++
                               files under it which are then formatted
' \
    "$(basename "${0}")"
}

# Parse parameters.
while test ${#} -gt 0; do
  case "${1}" in
    # [-d|--debug]             enable debug mode, showing every executed command
    '-d'|'--debug') set -vx ;;

    # [-h|--help]              print usage (this text).
    '-h'|'--help') print_usage; exit 0 ;;

    # [-c|--changed]           format changed files only
    '-c'|'--changed') changed=true ;;

    # Allow extra arguments, they should be directories or files to be formatted.
    *) break ;;
  esac; shift
done

# Get script path.
script_path=$(cd "$(dirname "${0}")" && pwd)

list_of_files=
if ${changed-false}; then
  list_of_files=$(git diff $(git merge-base origin/master HEAD) --name-only | grep -E "${extensions_regex}")
elif test ${#} = 0; then
  # Use current directory when called without an argument.
  set -- .
fi

# Generated files will be filtered out.
filtered_out=$("${script_path}/print-generated-files.sh")

# For all arguments...
parameters=
while test ${#} -gt 0 || test -n "${list_of_files}"; do
  # Preserve parameters that begin with dash and pass them to uncrustify.
  if test ${#} -gt 0 && test "$(printf '%s' "${1}" | cut -c 1)" = '-'; then
    parameters="${parameters} ${1}"
    shift
    continue
  fi

  if test -n "${list_of_files}"; then
    # First exhaust list_of_files.
    file=$(printf '%s\n' "${list_of_files}" | head -n 1)
    list_of_files=$(printf '%s\n' "${list_of_files}" | tail -n +2)
  else
    # Then exhaust parameters.
    file=${1}
    shift
  fi

  # Get absolute path.
  if test "$(printf '%s' "${file}" | grep -Eo '^.')" != '/'; then
    basename=$(basename "${file}")
    if test "${basename}" = .; then
      basename=
    fi
    file="$(cd "$(dirname "${file}")" && pwd)/${basename}"
  fi
  printf '%s\n' "${file}"

  if test -f "${file}"; then
    # Format file.
    # shellcheck disable=SC2046
    # We specifically want word splitting for the parameters.
    uncrustify -c "${script_path}/../.uncrustify.cfg" --replace $(printf '%s' "${parameters}") "${file}"
  elif test -d "${file}"; then
    # Keep CWD for later use.
    pwd="${PWD}"

    # First checkout target directory so that the following "git ls-files" call
    # acts on the proper git repository.
    cd "${file}"

    # Get list of files to format.
    cd "$(git rev-parse --show-toplevel)"
    files=$(git ls-files | xargs -n1 printf "${PWD}/%s\\n" | grep -F "${file}" | grep -E "${extensions_regex}")

    # Filter out generated files.
    for file in ${filtered_out}; do
      files=$(printf '%s\n' "${files}" | grep -Fv "${file}" | sed '/^$/d')
    done

    # Restore directory to what it initially was because ${files} contains
    # relative paths.
    cd "${pwd}"

    # For all files...
    for i in ${files}; do
      # Run recursively to format file or iterate further through directories.
      "${0}" "${i}"
    done
  fi
done
