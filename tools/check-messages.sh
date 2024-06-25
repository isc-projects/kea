#!/bin/sh

# Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Usage:
#
# ./tools/check-messages.sh [-a|--amend] [-d|--debug] [-h|--help]
#
# Run from anywhere to check the following in the repository this belongs to:
# * that there are no two messages with the same name
# * that there are no unused messages (run with -a to get rid of them)
# * that messages are only logged once (outside of an exhonerated list
# meant to only warn about new occurences of this type; the list was snapshotted
# in august 2021 and contains all multiple occurences prior to this date)

# shellcheck disable=SC3043
# SC3043: In POSIX sh, 'local' is undefined.

# shellcheck disable=SC2013
# SC2013: To read lines rather than words, pipe/redirect to a 'while read' loop.

# shellcheck disable=SC2044
# SC2044: For loops over find output are fragile. Use find -exec or a while read loop.

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
  [-a|--amend]                 remove unused messages from message files and
                               add missing mentions of debug log levels in
                               message files
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

    # [-a|--amend]                 remove unused messages from message files and
    #                              add missing mentions of debug log levels in
    #                              message files
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

# Remove a given message from a given message file. Matches only the first
# occurrence.
remove_message() {
  local message="${1}"; shift
  local file="${1}"; shift

  start_pattern="^% ${message}"
  end_pattern='^%'

  # Remove with sed.
  sed "/${start_pattern}/,/${end_pattern}/{/${end_pattern}/!{/${end_pattern}/!d}}" "${file}" | grep -Ev "${start_pattern}" > "${file}.bak"
  mv "${file}.bak" "${file}"
}

is_message_exhonerated_from_being_logged_multiple_times() {
  grep "${*}" > /dev/null ./tools/.exhonerated_messages
}

mandatory_commands cut find grep sed sort

mistake=false

# For all the message files:
for message_file in $(find . -type f -name '*.mes' | sort -uV); do
  printf 'Checking %s...\n' "$(basename "${message_file}")"

  # For all the messages in a message file:
  for message in $(grep -E '^%' "${message_file}" | cut -d ' ' -f 2); do

    # Get all occurences.
    occurences="$(grep -EIR "\b${message}\b" "${root_path}"/* | grep -Fv '.git')"

    # Check for duplicate message names.
    occurences_in_message_files="$(printf '%s\n' "${occurences}" | grep "% ${message}\b" | grep -E 'messages\.mes:' || true)"
    occurence_count="$(printf '%s\n' "${occurences_in_message_files}" | wc -l)"
    if test -z "${occurence_count}"; then
      printf 'ERROR: could not find number of occurences for message %s. Fix this in the script.\n' "${message}"
      exit 2
    fi
    if test "${occurence_count}" -ne 1; then
      printf "${red}%% expected %s to be found in one message file, but it is found in %s.${reset}\\n" "${message}" "${occurence_count}"
      mistake=true
    fi

    # Get occurences that appear in code.
    occurences_in_sources="$(printf '%s\n' "${occurences}" | grep -E '\.cc:|\.h:' | grep -Ev 'messages\.cc:|messages\.h|test' || true)"
    occurence_count="$(printf '%s\n' "${occurences_in_sources}" | wc -l)"
    if test -z "${occurence_count}"; then
      printf 'ERROR: could not find number of occurences for message %s. Fix this in the script.\n' "${message}"
      exit 2
    fi

    # If not found in any source file, print it for the developer to take action.
    if test "${occurence_count}" -eq 0; then
      printf "${red}%% %s is not used.${reset}\\n" "${message}"
      mistake=true

      # If the caller decided to amend the message files, then remove the unused
      # message.
      if "${amend}"; then
        remove_message "${message}" "${message_file}"
      fi

    # If found multiple times and it is due to a recent change, print it for the developer to take
    # action.
    elif test "${occurence_count}" -gt 1; then
      if ! is_message_exhonerated_from_being_logged_multiple_times "${message}"; then
        printf "${red}%% %s is used %s times${reset}:\n%s\n\n" "${message}" "${occurence_count}" "${occurences_in_sources}"
        mistake=true
      fi
    fi

    # For this iterated message, iterate further through all the occurences in
    # sources mainly find the log level used so that you can check further if it
    # is mentioned in its .mes file.
    for i in $(printf '%s\n' "${occurences_in_sources}" | cut -d ':' -f 1); do

      # Get the log level used in sources and make sure a single log level is
      # used everywhere.
      loglevel="$(tr -s '\n' ' ' < "${i}" | grep -Po "LOG_DEBUG[^;]*?\b${message}\b" | cut -d ',' -f 2 | sed 's/.*:://g' | sed 's/^ *//g;s/ *$//g' | sort -uV || true)"
      if test -z "${loglevel}"; then
        # A log level could not be found. This most probably means that this
        # message is not logged as a debug message, but as an info, warning, or
        # error message. In that case a log level is not required. So skip this occurrence.
        continue
      fi
      lines="$(printf '%s\n' "${loglevel}" | wc -l)"
      if test "${lines}" != 1; then
        printf "${red}%% message %s logged under %s different debug levels: \n%s${reset}\n\n" "${message}" "${lines}" "${loglevel}" >&2
        mistake=true
        continue
      fi

      # Resolve log level variable names into numerals. This may require
      # multiple recursions e.g. DBG_DHCP6_BASIC -> DBGLVL_TRACE_BASIC -> 40.
      # If 16 recursions are reached, stop and return an error so that either
      # this script or complex C++ definitions of these log levels (like this
      # previous one: const int DBG_ALL = DBGLVL_TRACE_DETAIL + 20) may be
      # fixed.
      recursions=16
      while test "$(printf '%s\n' "${loglevel}" | grep -Ec '^[0-9]+$')" != 1; do
        loglevel_define_file="$(grep -EIR "\b${loglevel}\b =" "${root_path}"/* | grep -Fv '.git' | cut -d ':' -f 1)"
        lines="$(printf '%s\n' "${loglevel_define_file}" | wc -l)"
        if test "${lines}" != 1; then
          printf "${red}%% found %s files instead of 1 when searching for the numeral version of debug log level %s which message %s is logged under${reset}\n\n" "${lines}" "${loglevel}" "${message}" >&2
          mistake=true
          continue
        fi
        loglevel="$(tr -s '\n' ' ' < "${loglevel_define_file}" | grep -Po "\b${loglevel}\b =[^;]+?;" | cut -d '=' -f 2 | cut -d ';' -f 1 | sed 's/.*:://g' | sed 's/^ *//g;s/ *$//g')"
        recursions=$((recursions - 1))
        if test "${recursions}" = 0; then
          printf "${red}%% could not find log level of message %s after 16 recursions. Breaking endless loop...${reset}\n\n" "${message}" >&2
          mistake=true
          break
        fi
      done

      # Finally, do the actual check of the line being mentioned in the .mes
      # file.
      message_file=$(printf '%s\n' "${occurences_in_message_files}" | cut -d ':' -f 1 | sort -uV)
      logged_at_message="Logged at debug log level ${loglevel}."
      if test "$(grep -F -A1 "${message}" "${message_file}" | grep -Ec "^${logged_at_message}$")" = 0; then
        printf "${red}%% debug level %s is not mentioned for message %s in %s${reset}\n\n" "${loglevel}" "${message}" "${message_file}"
        mistake=true

        # And if amendment is commanded by the user...
        if "${amend}"; then
          # Delete any different log level, it has changed in the meantime.
          if test "$(grep -F -A1 "${message}" "${message_file}" | grep -Ec '^Logged at debug log level ')" -gt 0; then
            line_number="$(grep -En "\b${message}\b" "${message_file}" | cut -d ':' -f 1)"
            line_number="$(( line_number + 1 ))"
            sed "${line_number}d" "${message_file}" > "${message_file}.tmp"
          fi
          # And add the right one.
          sed "/^% ${message}/a Logged at debug log level ${loglevel}." "${message_file}" > "${message_file}.tmp"
          mv "${message_file}.tmp" "${message_file}"
        fi
      fi
    done
  done
done

# exit 1 if any unused message was found so that CI properly fails.
if "${mistake}"; then
  exit 1
fi
