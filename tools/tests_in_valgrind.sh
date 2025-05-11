#!/bin/sh

################################################################################
# This script runs all tests in valgrind. Set up and compile Kea the way
# you want it to be tested (you should use "-D tests=enabled" however, or you
# get no tests). Then run this script.
#
# Note that the test isn't what you would call "production quality" (it is
# expected to be used by the kea developers, not end user) and might break,
# some ways of breaking it are known.
#
# There are two variables that modify it's behaviour.
# * VALGRIND_FLAGS are the flag passed to valgrind. There are some, hopefully
#      reasonable defaults which you can overwrite. Note that the variable is
#      used unmodified inside a sed pattern with # as a modifier, which can
#      easily break it. There was no motivation to fix this.
# * VALGRIND_FILE is the file to store the output into. Default is valgrind.log
################################################################################

# Change directory to Kea's top build directory.
script_path=$(cd "$(dirname "${0}")" && pwd)
cd "${script_path}/.."

# First, make sure the tests are up to date
meson compile -C build

if test $? = 2; then
    printf 'Did you run meson setup?\n'
    exit 1
fi

# Exit with error if commands exit with non-zero and if undefined variables are
# used.
set -eu

# Some configuration
# TODO Escape for sed, this might break
LOGFILE="${VALGRIND_FILE:-$(pwd)/valgrind.log}"
FLAGS="${VALGRIND_FLAGS:---leak-check=full --track-fds=yes}"
FLAGS="$FLAGS --log-file=$LOGFILE.%p"

FOUND_ANY=false
FAILED=

# Find all the tests (yes, doing it by a name is a nasty hack)
# Since the while runs in a subprocess, we need to get the assignments out, done by the eval
set -x
for testname in $(find . -type f -name '*_unittests' -print | grep -Fv '.libs/'); do
    sed -e 's#exec "#exec valgrind '"$FLAGS"' "#' "$testname" > "$testname.valgrind"
    chmod +x "$testname.valgrind"
    echo "$testname" >>"$LOGFILE"
    echo "===============" >>"$LOGFILE"
    OLDDIR=$(pwd)
    cd "$(dirname "$testname")"
    "./$(basename "$testname").valgrind" >&2 &
    PID="$!"
    cd "$OLDDIR"
    if ! wait "$PID"; then
        printf 'FAILED="%s
%s"' "${FAILED}" "${testname}"
    fi
    NAME="$LOGFILE.$PID"
    rm "$testname.valgrind"
    # Remove the ones from death tests
    if test -e "${NAME}"; then
        grep "==$PID==" "$NAME" >>"$LOGFILE"
        rm "$NAME"
    fi
    FOUND_ANY=true
done

if test -n "$FAILED"; then
    echo "These tests failed:" >&2
    echo "$FAILED" >&2
fi

if ! $FOUND_ANY; then
    echo "No test was found. Is it possible you configured without '-D tests=enabled'?" >&2
    exit 1
fi
