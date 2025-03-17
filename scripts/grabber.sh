#!/bin/sh

dir="${1}"
pattern="${2}"

cd "${dir}" || exit 1

find . -mindepth 1 -maxdepth 1 -type f -name "${pattern}" -printf '%P\n' | sort -V
