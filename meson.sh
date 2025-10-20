#!/bin/sh

# Pulls the latest meson that has fix https://github.com/mesonbuild/meson/pull/13532
# for issue https://github.com/mesonbuild/meson/issues/11322.
#
# Usage: just like meson
# Example: ./meson.sh setup build

set -eu

meson_version=1.9.1

# Check if ${1} <= ${2}.
le() {
    # Sort numerically and check the first item.
    lesser=$(printf '%s\n%s\n' "${1}" "${2}" | sort -V | head -n 1)
    if test "${lesser}" = "${1}"; then
        # ${1} <= ${2}
        return 0
    fi

    # ${1} > ${2}
    return 1
}

# Print usage.
print_usage() {
    printf \
'Usage: %s {{options}}
Options:
    [-i|--install]                 install meson and ninja to gobal scope. attempts to acquire root privileges
    [-l|--latest]                  use latest meson instead of %s
    [-v|--venv]                    use venv instead of pyinstaller
    [-h|--help]                    print usage (this text)
' \
    "$(basename "${0}")" "${meson_version}"
}

# Parse parameters.
while test ${#} -gt 0; do
    case "${1}" in
        '-i'|'--install') install=true ;;
        '-l'|'--latest') latest=true ;;
        '-v'|'--venv') use_venv=true ;;
        '-h'|'--help') print_usage; exit 0 ;;
        *) break ;;
    esac; shift
done

# Default parameters
test -z "${install+x}" && install=false
test -z "${latest+x}" && latest=false
test -z "${use_venv+x}" && use_venv=false

if "${install}" &&  "${use_venv}"; then
    sudo='sudo'
    venv='/usr/local/share/.venv'
else
    sudo=
    venv='.venv'
fi

# Change directory to Kea's top level directory.
top_level=$(cd "$(dirname "${0}")" && pwd)
cd "${top_level}" || exit 1

if command -v meson > /dev/null 2>&1 && ! "${latest}" && le "${meson_version}" "$(meson --version)"; then
    # Good to be used. Does not suffer from endless transitional dependency iteration fixed in 1.8.0.
    meson='meson'
else
    meson='.meson/meson'
    if test ! -f "${meson}"; then
        # Starting with Meson 0.62, Python 3.7 is required.
        python3=python3
        v=$(python3 -c 'import platform; print(platform.python_version())')
        if ! le 3.7.0 "${v}"; then
            # Search for a newer Python.
            if command -V compgen >/dev/null; then
                # shellcheck disable=SC3044
                # SC3044 (warning): In POSIX sh, 'compgen' is undefined.
                newer=$(compgen -c python3 | grep -E '^python3.[0-9]+$' | sort -V | tail -n 1)
                if test -n "${newer}"; then
                    python3="${newer}"
                fi
            fi
        fi

        v=$("${python3}" -c 'import platform; print(platform.python_version())')
        printf 'Python version: %s\n' "${v}"

        ${sudo} "${python3}" -m venv "${venv}"
        ${sudo} "${venv}/bin/pip" install --upgrade pip
        ${sudo} "${venv}/bin/pip" install ninja
        mkdir -p .meson
        ${sudo} cp "${venv}/bin/ninja" .meson/ninja

        if "${use_venv}"; then
            if "${latest}"; then
                ${sudo} "${venv}/bin/pip" install git+https://github.com/mesonbuild/meson.git
            else
                ${sudo} "${venv}/bin/pip" install "meson==${meson_version}"
            fi
            ${sudo} cp "${venv}/bin/meson" .meson/meson
        else
            if test ! -d .meson-src; then
                git clone https://github.com/mesonbuild/meson .meson-src
            fi
            if ! "${latest}"; then
                (
                    cd .meson-src || exit 1
                    git checkout "${meson_version}"
                )
            fi
            ${sudo} "${venv}/bin/pip" install pyinstaller
            (
                cd .meson-src || exit 1
                "${top_level}/${venv}/bin/pyinstaller" --additional-hooks-dir=packaging --clean --dist "${top_level}/.meson" --onefile ./meson.py
            )
            rm -fr .meson-src "${venv}"
        fi
    fi
fi

if "${install}"; then
    sudo cp .meson/meson /usr/local/bin/meson
    sudo cp .meson/ninja /usr/local/bin/ninja
    rm -fr .meson
    exit 0
fi

if test -f "${top_level}/.meson/ninja"; then
    # To find ninja in case it went with the pyinstalled version.
    export PATH="${top_level}/.meson:${PATH}"
fi

"${meson}" "${@}"
