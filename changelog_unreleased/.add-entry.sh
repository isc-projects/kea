#!/bin/sh

set -eu

parent_dir=$(cd "$(dirname "${0}")" && pwd)
cd "${parent_dir}" || exit 1

author=$(git show -s --format='%ae' | cut -d '@' -f 1)
branch=$(git branch --show-current)
file="${branch}"
gitlab_id=$(printf '%s' "${branch}" | cut -d '-' -f 1)
printf '[category]\t\t%s\n' "${author}" > "${file}"
printf '\tdescription\n' >> "${file}"
printf '\t(Gitlab #%s)\n' "${gitlab_id}" >> "${file}"
printf 'Created changelog_unreleased/%s.\n' "${file}"
