#!/bin/sh

# Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
'Usage: %s {{options}} [$new_release_tag]
Options:
  [-d|--debug]                 enable debug mode, showing every executed command
  [-h|--help]                  print usage (this text)
Example:
  ./tools/bump_lib_versions.sh Kea-1.2.3
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
    test -z "${new_release_tag+x}" && new_release_tag=${1} && shift && continue

    # Unrecognized argument
    error "Unrecognized argument '${1}'" ;;
  esac; shift
done


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

old_release_tag=$(git describe --tags HEAD | grep -Eo 'Kea-[0-9]+\.[0-9]+\.[0-9]+')
if test -z "${new_release_tag+x}"; then
  patch_version=$(echo "${old_release_tag}" | grep -Eo '[0-9]+$')
  patch_version=$((patch_version + 1))
  new_release_tag=$(echo "${old_release_tag}" | sed "s/.[0-9]*$/.${patch_version}/")
  printf 'No version provided. Assuming that the target version is "%s".' "${new_release_tag}"
  if test -t 1; then
    printf ' Press any key to continue... '
    read -r _
  fi
  printf '\n'
fi

is_old_tag_stable_release=$(is_stable_release "${old_release_tag}" && printf true || printf false)
is_new_tag_stable_release=$(is_stable_release "${new_release_tag}" && printf true || printf false)

# if any file has changed in a specific library director
# there are 4 possible cases
# 1. old release is stable and new release is stable
#    new_version = old_version + 1 (only for updated libs)
# 2. old release is stable and new release is development
#    new_version = old_version + 1 (only for updated libs) and + 10 (for all libs)
# 3. old release is development and new release is development
#    new_version = old_version + 1 (only for updated libs)
# 4. old release is development and new release is stable
#    new_version = old_version + 1 (only for updated libs)

# Get root path.
root_path=$(cd "$(dirname "${0}")/.." && pwd)

cd "${root_path}"

# Check if there are any unstaged changes.
diff=$(git diff 2>&1)
if test -n "${diff}"; then
  printf 'ERROR: stage changes for %s before running this script\n' "${root_path}" >&2
  exit 1
fi

increment_extra=10
increment=1

major=$(echo "${new_release_tag}" | cut -d '-' -f 2 | cut -d '.' -f 1)
middle=$(echo "${new_release_tag}" | cut -d '-' -f 2 | cut -d '.' -f 2)
minor=$(echo "${new_release_tag}" | cut -d '-' -f 2 | cut -d '.' -f 3)
new_hooks_version="${major}$(printf '%02d' "${middle}")$(printf '%02d' "${minor}")"

sed -i'' "s/^\/\/ Version .* of the hooks framework, set for Kea .*/\/\/ Version ${new_hooks_version} of the hooks framework, set for $(echo "${new_release_tag}" | tr '-' ' ')/" "src/lib/hooks/hooks.h"
sed -i'' "s/KEA_HOOKS_VERSION.*/KEA_HOOKS_VERSION = ${new_hooks_version};/" "src/lib/hooks/hooks.h"

for lib in $(git diff --name-only "${old_release_tag}" src/lib | cut -d '/' -f 3- | grep -v test | sed "s/\/[^\/]*$//" | sort -uV); do
  # Skip over files and anything that is not a directory.
  if test ! -d "src/lib/${lib}"; then
    continue
  fi
  # Skip over directories that do not contain a meson.build file.
  if test ! -f "src/lib/${lib}/meson.build"; then
    continue
  fi

  old_version=$(grep -Eo "version: '[0-9.]+'," "src/lib/${lib}/meson.build" | grep -Eo '[0-9.]+' | cut -d '.' -f 1)
  new_version=$((old_version + increment))
  sed -i'' "s/version: '.*',/version: '${new_version}.0.0',/" "src/lib/${lib}/meson.build"
  sed -i'' "s/version-info .*/version-info ${new_version}:0:0/" "src/lib/${lib}/Makefile.am"
done

if ! ${is_new_tag_stable_release} && ${is_old_tag_stable_release}; then
  for lib in $(find 'src/lib' -type d | cut -d '/' -f 3- | grep -v test | sed "s/\/[^\/]*$//" | sort -uV); do
    # Skip over files and anything that is not a directory.
    if test ! -d "src/lib/${lib}"; then
      continue
    fi
    # Skip over directories that do not contain a meson.build file.
    if test ! -f "src/lib/${lib}/meson.build"; then
      continue
    fi

    old_version=$(grep -Eo "version: '[0-9.]+'," "src/lib/${lib}/meson.build" | grep -Eo '[0-9.]+' | cut -d '.' -f 1)
    new_version=$((old_version + increment_extra))
    sed -i'' "s/version: '.*',/version: '${new_version}.0.0',/" "src/lib/${lib}/meson.build"
    sed -i'' "s/version-info .*/version-info ${new_version}:0:0/" "src/lib/${lib}/Makefile.am"
  done
fi

if ${is_new_tag_stable_release}; then
  release='stable'
else
  release='development'
fi

(echo "\
TODO.	[build]		TODO
	The library version numbers have been bumped up for the Kea ${major}.${middle}.${minor}
	${release} release.
	(Gitlab #TODO)
" && cat ./ChangeLog) > ./ChangeLog.tmp
mv ./ChangeLog.tmp ./ChangeLog
