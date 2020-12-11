#!/bin/sh

# Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Usage:
#
# ./tools/bump-lib-versions.sh Kea-1.9.1 Kea-1.9.2

set -eu

# Define some ANSI color codes.
if test -t 1; then
  red='\033[91m'
  reset='\033[0m'
else
  red=
  reset=
fi

# Print usage.
# Expressions don't expand in single quotes, use double quotes for that. [SC2016]
# shellcheck disable=SC2016
print_usage() {
  printf \
'Usage: %s {{options}} $old_release_tag $new_release_tag
Options:
  [-d|--debug]                 enable debug mode, showing every executed command
  [-h|--help]                  print usage (this text)
Example:
  ./tools/bump_lib_versions.sh Kea-1.9.1 Kea-1.9.2
' \
    "$(basename "${0}")"
}

error() {
  printf "${red}ERROR: %s${reset}\\n" "${1}" 1>&2
  print_usage
  exit 1
}

# Parse parameters.
while test ${#} -gt 0; do
  case "${1}" in
    # [-d|--debug]             enable debug mode, showing every executed command
    '-d'|'--debug') set -vx ;;

    # [-h|--help]              print usage (this text).
    '-h'|'--help') print_usage; exit 0 ;;

    *)
    test -z "${old_release_tag+x}" && old_release_tag=${1} && shift && continue
    test -z "${new_release_tag+x}" && new_release_tag=${1} && shift && continue

    # Unrecognized argument
    error "Unrecognized argument '${1}'" ;;
  esac; shift
done

# Check for mandatory arguments.
# Expressions don't expand in single quotes, use double quotes for that. [SC2016]
# shellcheck disable=SC2016
test -z "${old_release_tag+x}" && error '$old_release_tag is mandatory'
# shellcheck disable=SC2016
test -z "${new_release_tag+x}" && error '$new_release_tag is mandatory'

is_stable_release() {
  version_number=$(printf '%s' "${1}" | cut -d . -f2)
  if test $((version_number % 2)) -eq 0; then
    return 0
  else
    return 1
  fi
}

find_latest_stable_release_tag() {
  tag_pattern=${1}
  for version in $(git tag | grep -F "${tag_pattern}" | tac); do
    if is_stable_release "${version}"; then
      printf '%s' "${version}"
      return
    fi
  done
}

is_old_tag_stable_release=$(is_stable_release "${old_release_tag}" && printf true || printf false)
is_new_tag_stable_release=$(is_stable_release "${new_release_tag}" && printf true || printf false)

# if any file has changed in a specific library director
# there are 4 possible cases
# 1. old release is stable and new release is stable
#    new_version = old_version + 1
# 2. old release is stable and new release is development
#    new_version = old_version + 11
# 3. old release is development and new release is development
#    if latest development has already added 10 it means that the old_release version is different than latest_stable version
#        new_version = old_version + 1
#    else it means that the old_release has not incremented the version since latest_stable
#        new_version = old_version + 11
# 4. old release is development and new release is stable
#    illegal as there should only be stable to stable bump lib versions

if ! ${is_old_tag_stable_release} && ${is_new_tag_stable_release}; then
  printf 'illegal bump in lib versions from development release to stable release'
  exit 1
fi

# Get root path.
root_path=$(cd "$(dirname "${0}")/.." && pwd)

cd "${root_path}"

# Check if there are any unstaged changes.
diff=$(git diff 2>&1)
if test -n "${diff}"; then
  printf 'Stage changes for %s before running this script...\n' "${root_path}"
  exit 1
fi

latest_stable_release_tag=$(find_latest_stable_release_tag "$(printf '%s' "${old_release_tag}" | cut -d '.' -f1)")
increment_extra=10
increment=1

old_hooks_version=$(grep KEA_HOOKS_VERSION "src/lib/hooks/hooks.h" | cut -d '=' -f 2 | tr -d ' ' | tr -d ';')
new_hooks_version=$((old_hooks_version + increment))

if ! ${is_new_tag_stable_release} && ${is_old_tag_stable_release}; then
  major=$(echo "${new_release_tag}" | cut -d '-' -f 2 | cut -d '.' -f 1)
  middle=$(echo "${new_release_tag}" | cut -d '-' -f 2 | cut -d '.' -f 2)
  minor=$(echo "${new_release_tag}" | cut -d '-' -f 2 | cut -d '.' -f 3)
  new_hooks_version="${major}$(printf '%02d' "${middle}")$(printf '%02d' "${minor}")"
fi

sed -i "s/^\/\/ Version .* of the hooks framework, set for Kea .*/\/\/ Version ${new_hooks_version} of the hooks framework, set for $(echo "${new_release_tag}" | tr '-' ' ')/" "src/lib/hooks/hooks.h"
sed -i "s/KEA_HOOKS_VERSION.*/KEA_HOOKS_VERSION = ${new_hooks_version};/" "src/lib/hooks/hooks.h"

for lib in $(git diff "${old_release_tag}" --name-only src/lib/ | cut -d '/' -f 3 | sort -uV); do
  old_version=$(grep '\-version\-info' "src/lib/${lib}/Makefile.am" | tr -s ' ' | rev | cut -d ' ' -f 1 | rev | cut -d ':' -f 1)
  new_version=$((old_version + increment))
  if ! ${is_new_tag_stable_release}; then
    if ${is_old_tag_stable_release} || test "$(git diff -U0 "${latest_stable_release_tag}" "${old_release_tag}" "src/lib/${lib}/Makefile.am" | grep '^+' | grep -v '^+++ ' | grep -c '\-version\-info')" -eq 0; then
      new_version=$((new_version + increment_extra))
    fi
  fi
  sed -i "s/version-info .*/version-info ${new_version}:0:0/" "src/lib/${lib}/Makefile.am"
done
