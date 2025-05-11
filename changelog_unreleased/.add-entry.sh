#!/bin/sh

set -eu

parent_dir=$(cd "$(dirname "${0}")" && pwd)
cd "${parent_dir}" || exit 1
basedir=$(basename "${parent_dir}")

author=$(git show -s --format='%ae' | cut -d '@' -f 1)
branch=$(git branch --show-current)
gitlab_id=$(printf '%s' "${branch}" | cut -d '-' -f 1)
file="${branch}"
if test -e "${file}"; then
  printf 'Nothing done. File already exists: %s\n' "${basedir}/${file}"
  exit 1
fi
content=$(cat .template)
content="$(printf '%s' "${content}" | sed "s/author/${author}/")"
content="$(printf '%s' "${content}" | sed "s/#0000/#${gitlab_id}/")"
printf '%s\n' "${content}" > "${file}"
printf 'File created: %s\n' "${basedir}/${file}"
