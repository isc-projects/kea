#!/bin/sh

set -eu

script_path=$(cd "$(dirname "${0}")" && pwd)

cd "${script_path}"

generate() {
  source="${1}"
  target="${2}"

  source_content=$(cat "${source}")
  variable_name=$(echo "${source}" | tr '[:lower:]' '[:upper:]' | sed 's/\./_/' | sed 's/-/_/')

  cat > "${target}" <<HERE_DOCUMENT
#include <string>

extern std::string ${variable_name} = R"(
${source_content}
)";
HERE_DOCUMENT
}

generate kea-dhcp4.conf ../kea-dhcp4.h
generate kea-dhcp6.conf ../kea-dhcp6.h
