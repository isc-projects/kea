#!/bin/sh

if test ! -d venv; then
  python3 -m venv ./venv
  ./venv/bin/pip install --upgrade pip
  ./venv/bin/pip install git+https://github.com/serebit/meson.git@iterative-transitive-link-dep-resolve
fi
# shellcheck disable=SC1091
# SC1091: Not following: ... was not specified as input (see shellcheck -x).
. ./venv/bin/activate

meson "${@}"
