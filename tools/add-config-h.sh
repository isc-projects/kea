#!/bin/sh

# Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
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
# Reason: blackslash+linefeed inside single quotes in sed are needed for
# POSIX-compliance. \n works only with GNU sed.

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

# Parse parameters.
while test ${#} -gt 0; do
  case "${1}" in
    # [-d|--debug]             enable debug mode, showing every executed command
    '-d'|'--debug') set -vx ;;

    # [-h|--help]              print usage (this text).
    '-h'|'--help') print_usage ;;

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

# Define some ANSI color codes.
red='\e[1m\e[31m'
reset='\e[1m\e[0m'

# Get source files that are missing an '#include <config.h>' line.
get_source_files() {
  mandatory_commands cut find grep sed sort uniq
  source_files=$(cd "${root_path}" && find . -type f | grep -Fv '.git' | grep -E '\.cc$' | xargs grep -EL '#include\s*[\"|\<]config.h[\"|\>]' | cut -d ':' -f 1 | sort -uV | uniq)
  for file in ${filtered_out}; do
    source_files=$(printf '%s\n' "${source_files}" | sed "s#${file}##g" | sed '/^$/d')
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

# Generated files will be filtered out. Hardcoded list
filtered_out='
  ./src/bin/admin/messages.cc
  ./src/bin/agent/agent_lexer.cc
  ./src/bin/agent/agent_parser.cc
  ./src/bin/agent/ca_messages.cc
  ./src/lib/cfgrpt/config_report.cc
  ./src/bin/d2/d2_lexer.cc
  ./src/bin/d2/d2_messages.cc
  ./src/bin/d2/d2_parser.cc
  ./src/bin/dhcp4/dhcp4_lexer.cc
  ./src/bin/dhcp4/dhcp4_messages.cc
  ./src/bin/dhcp4/dhcp4_parser.cc
  ./src/bin/dhcp6/dhcp6_lexer.cc
  ./src/bin/dhcp6/dhcp6_messages.cc
  ./src/bin/dhcp6/dhcp6_parser.cc
  ./src/bin/lfc/lfc_messages.cc
  ./src/bin/netconf/netconf_lexer.cc
  ./src/bin/netconf/netconf_messages.cc
  ./src/bin/netconf/netconf_parser.cc
  ./src/hooks/dhcp/bootp/bootp_messages.cc
  ./src/hooks/dhcp/flex_option/flex_option_messages.cc
  ./src/hooks/dhcp/high_availability/ha_messages.cc
  ./src/hooks/dhcp/lease_cmds/lease_cmds_messages.cc
  ./src/hooks/dhcp/mysql_cb/mysql_cb_messages.cc
  ./src/hooks/dhcp/stat_cmds/stat_cmds_messages.cc
  ./src/hooks/dhcp/user_chk/user_chk_messages.cc
  ./src/lib/asiodns/asiodns_messages.cc
  ./src/lib/config/config_messages.cc
  ./src/lib/database/db_messages.cc
  ./src/lib/database/server_selector.cc
  ./src/lib/dhcp_ddns/dhcp_ddns_messages.cc
  ./src/lib/dhcpsrv/alloc_engine_messages.cc
  ./src/lib/dhcpsrv/dhcpsrv_messages.cc
  ./src/lib/dhcpsrv/fuzz_messages.cc
  ./src/lib/dhcpsrv/hosts_messages.cc
  ./src/lib/eval/eval_messages.cc
  ./src/lib/eval/lexer.cc
  ./src/lib/eval/parser.cc
  ./src/lib/hooks/hooks_messages.cc
  ./src/lib/http/http_messages.cc
  ./src/lib/log/tests/log_test_messages.cc
  ./src/lib/process/process_messages.cc
'

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
  # shellcheck disable=SC1004
  for i in $(get_source_files); do
    sed '1,/#include/s/#include/#include <config.h>\
\
#include/' "${i}" > "${file}"
    mv "${file}" "${i}"
  done

  # Run again for files that don't have any includes. The second command would
  # work for the first case, but the first command is more elegant.
  # shellcheck disable=SC1004
  for i in $(get_source_files); do
    sed '1,/\(\/\/ file, You can obtain one.*\)/s/\(\/\/ file, You can obtain one.*\)/\1\
\
#include <config.h>/' "${i}" > "${file}"
    mv "${file}" "${i}"
  done

  # Cleanup temporary file.
  rm -f "${file}"
fi
