#!/bin/sh

# Pulls the latest meson that has fix https://github.com/mesonbuild/meson/pull/13532
# for issue https://github.com/mesonbuild/meson/issues/11322.
#
# Usage: just like meson
# Example: ./meson.sh setup build

if test ! -d venv; then
  python3 -m venv ./venv
  ./venv/bin/pip install --upgrade pip
  ./venv/bin/pip install git+https://github.com/mesonbuild/meson.git
fi
# shellcheck disable=SC1091
# SC1091: Not following: ... was not specified as input (see shellcheck -x).
. ./venv/bin/activate

meson "${@}"
