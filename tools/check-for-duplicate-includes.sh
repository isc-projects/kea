#!/bin/sh

# Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# shellcheck disable=SC2039
# SC2039: In POSIX sh, 'local' is undefined.

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
    '-h'|'--help') print_usage ;;

    # Unrecognized argument
    *)
    printf "${red}ERROR: Unrecognized argument '%s'${reset}\\n" "${1}" 1>&2; print_usage; exit 1 ;;
  esac; shift
done

# Get source files that have duplicate '#include' lines.
get_source_files() {
  mandatory_commands cut find grep sed sort uniq

  # Get the files that have duplicate includes.
  source_files=$(cd "${root_path}" && find . -type f | grep -Fv '.git' | \
    grep -E '\.cc$|\.h$' | xargs grep -El '#include' | \
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

# Generated files will be filtered out. Hardcoded list
filtered_out='
  ./src/bin/admin/messages.cc
  ./src/bin/agent/agent_lexer.cc
  ./src/bin/agent/agent_parser.cc
  ./src/bin/agent/ca_messages.cc
  ./src/lib/cfgrpt/config_report.cc
  ./src/lib/dns/rdataclass.h
  ./src/lib/dns/rdataclass.cc
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

found=false
for i in $(get_source_files); do
  includes=$(grep -E '^#include' "${i}" | sort -V)
  unique_includes=$(grep -E '^#include' "${i}" | sort -uV)
  diff=$(posix_diff "${includes}" "${unique_includes}" | \
    grep -F '#include' | grep -E '^\-|^\+' | sed -E 's/^([^-+ ]*)[-+ ]/\1/' )
  if test -n "${diff}"; then
    printf '%s has the following duplicate includes:\n%s\n\n' "${i}" "${diff}"
    found=true
  fi
done

if "${found}"; then
  exit 1
fi
