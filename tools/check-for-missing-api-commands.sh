#!/bin/sh

# Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Usage:
#
# check-for-missing-api-commands.sh [$kea_repo]
#
# $kea_repo is by default ${script_path}/..

set -eu

script_path=$(cd "$(dirname "${0}")" && pwd)
cd "${script_path}/.."

if test "${#}" -gt 0; then
  kea_repo=${1}
else
  kea_repo="${script_path}/.."
fi

# In order:
# 1. grep perl-regexp with-filename only-matching recursive null-output
# 2. Exclude doxygen files.
# 3. Exclude tests directories.
# 4. Grep for all calls to registerCommandCallout even if they span multiple lines.
# 5. Remove the null byte to be able to assign it to a variable.
# 6. Remove the newlines to be able to more easily grep further.
# 7. Remove the spaces to be able to more easily grep further.
# 8. Turn commas into newlines so that each command is on its own line.
# 9. Remove commands that are commented out in code.
# 10. Grep for the name of the command alone.
# 11. Remove double quotes from the command name.
commands=$(grep -Phorz \
          --exclude '*.dox' \
          --exclude-dir 'tests' \
          '.*registerCommandCallout\(\s*\n*\s*".*?",' . | \
          tr -d '\0' | \
          tr -d '\n' | \
          tr -d ' ' | \
          tr ',' '\n' | \
          grep -Ev '//.*registerCommandCallout' | \
          grep -Eo '".*?"' | \
          tr -d '"')

# Check if there is a file with the ${command}.json format in src/share/api.
failed=false
for i in ${commands}; do
  if test -f "${kea_repo}/src/share/api/${i}.json"; then
    printf '[ SUCCESS ] %s\n' "${i}"
  else
    failed=true
    printf '[ FAILURE ] %s  - not found in src/share/api\n' "${i}"
  fi
done

if "${failed}"; then
  return 1
fi
