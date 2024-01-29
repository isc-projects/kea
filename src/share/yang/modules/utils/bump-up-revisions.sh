#!/bin/sh

# Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# This script can be used to bump up YANG module revisions.

# Exit with error if commands exit with non-zero and if undefined variables are
# used.
set -eu

# Print usage.
# Expressions don't expand in single quotes, use double quotes for that. [SC2016]
# shellcheck disable=SC2016
print_usage() {
  printf \
'Usage: %s {{options}}
Options:
  [-d|--debug]                              enable debug mode, showing every executed command
  [-h|--help]                               print usage (this text)
' \
    "$(basename "${0}")"
}

# Parse parameters.
while test ${#} -gt 0; do
  case "${1}" in
    # [-d|--debug]                              enable debug mode, showing every executed command
    '-d'|'--debug') set -vx ;;

    # [-h|--help]                               print usage (this text)
    '-h'|'--help') print_usage; exit 0 ;;

    # Unrecognized argument
    *)
    printf "${red}ERROR: Unrecognized argument '%s'${reset}\\n" "${1}" 1>&2; print_usage; exit 1 ;;
  esac; shift
done

#------------------------------------------------------------------------------#

# Get script path.
script_path=$(cd "$(dirname "${0}")" && pwd)
pushd "${script_path}/.."

# Get the last wednesday of the month.
this_month=$(date +%Y-%m)
wednesday=$(date -dwednesday +%Y-%m-%d)
i="${wednesday}"
while test "$(date -d "${i}" +%Y-%m)" == "${this_month}"; do
  wednesday="${i}"
  i=$(date -d"${wednesday} +7 days" +%Y-%m-%d)
done

# For all modules that were modified in this branch:
# - rename it to the new revision
# - change its name in Makefile.am
# - change its name in yang_revisions.h
ca=$(git merge-base origin/master $(git rev-parse --abbrev-ref HEAD))
for module in $(git diff "${ca}" --name-only . | grep  -E '\.yang$'); do
  module=$(basename "${module}")
  new_module="$(printf '%s' "${module}" | sed "s/@.*\.yang/@${wednesday}.yang/g")"
  if test "${module}" != "${new_module}"; then
    mv "${module}" "${new_module}"
    sed -i "s/${module}/${new_module}/g" ./Makefile.am
    sed -i "s/${module}/${new_module}/g" ../../../lib/yang/yang_revisions.h
  fi
done

# Regenerate hashes.
rm hashes/*
./utils/check-hashes.sh -a 2> /dev/null || true

# Check hashes were regenerated succesfully.
./utils/check-hashes.sh
