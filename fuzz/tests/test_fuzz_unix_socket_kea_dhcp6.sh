#!/bin/sh

if ! sudo -n true; then exec sudo -E -- "${0}" "${@}"; fi

script_path=$(cd "$(dirname "${0}")" && pwd)

script_basename=$(basename "${0}")

tested_binary=$(printf '%s' "${script_basename}" | sed 's/test_//g;s/.sh//g')

"${script_path}/../${tested_binary}"
