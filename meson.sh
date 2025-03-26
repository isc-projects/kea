#!/bin/sh

set -eu

# Pulls the latest meson that has fix https://github.com/mesonbuild/meson/pull/13532
# for issue https://github.com/mesonbuild/meson/issues/11322.
#
# Usage: just like meson
# Example: ./meson.sh setup build

# Check if ${1} < ${2}.
lt() {
    # Sort numerically and check the first item.
    lesser=$(printf '%s\n%s\n' "${1}" "${2}" | sort -V | head -n 1)
    if test "${lesser}" = "${2}"; then
        # ${1} >= ${2}
        return 1
    fi

    # ${1} < ${2}
    return 0
}

# Change directory to Kea's top level directory.
top_level=$(cd "$(dirname "${0}")" && pwd)
cd "${top_level}" || exit 1

if command -v meson > /dev/null 2>&1 && lt 1.7.98 "$(meson --version)"; then
    # Good to be used. Does not suffer from endless transitional dependency iteration.
    meson='meson'
else
    meson='./.meson/meson'
    if test ! -f "${meson}"; then
        # Starting with Meson 0.62, Python 3.7 is required.
        python3=python3
        v=$(python3 -c 'import platform; print(platform.python_version())')
        if lt "${v}" 3.7.0; then
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

        git clone https://github.com/mesonbuild/meson .meson-src
        (
            cd .meson-src || exit 1
            if git tag -l | grep -E '^1.8.0$' > /dev/null 2>&1; then
                git checkout 1.8.0
            fi
        )

        "${python3}" -m venv ./.venv
        ./.venv/bin/pip install --upgrade pip

        ./.venv/bin/pip install ninja
        ./.venv/bin/pip install pyinstaller
        (
            cd .meson-src || exit 1
            "${top_level}/.venv/bin/pyinstaller" --additional-hooks-dir=packaging --clean --dist "${top_level}/.meson" --onefile ./meson.py
        )
        cp ./.venv/bin/ninja ./.meson/ninja
        rm -fr ./.meson-src ./.venv
    fi
fi

if test -f "${top_level}/.meson/ninja"; then
    # To find ninja in case it went with the pyinstalled version.
    export PATH="${top_level}/.meson:${PATH}"
fi

"${meson}" "${@}"
