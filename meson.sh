#!/bin/sh

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

if test ! -d venv; then
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

    "${python3}" -m venv ./venv
    ./venv/bin/pip install --upgrade pip

    # When meson 1.8 will be released, we can pin the versions.
    ./venv/bin/pip install git+https://github.com/mesonbuild/meson.git
    ./venv/bin/pip install ninja
fi

# shellcheck disable=SC1091
# SC1091: Not following: ... was not specified as input (see shellcheck -x).
. ./venv/bin/activate

meson "${@}"
