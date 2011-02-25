#!/bin/bash
# Yes, really bash, there are some bashisms

###########################################
# This script runs all tests in valgrind. Configure and compile bind the way
# you want it to be tested (you should use --with-gtest, however, or you get
# no tests). Then run this script from the top build directory.
#
# Note that the test isn't what you would call "production quality" (it is
# expected to be used by the bind10 developers, not end user) and might break,
# some ways of breaking it are known.
#
# There are two variables that modify it's behaviour.
# * VALGRIND_FLAGS are the flag passed to valgrind. There are some, hopefully
#      reasonable defaults which you can overwrite. Note that the variable is
#      used unmodified inside a sed pattern with # as a modifier, which can
#      easily break it. There was no motivation to fix this.
# * VALGRIND_FILE is the file to store the output into. Default is valgrind.log
###########################################

# First, make sure the tests are up to date
make

if [ $? = 2 ] ; then
    echo "Did you run configure? Do you call me from the top bind10 directory?" >&2
    exit 1
fi

set -e

# Some configuration
# TODO Escape for sed, this might break
LOGFILE="${VALGRIND_FILE:-`pwd`/valgrind.log}"
FLAGS="${VALGRIND_FLAGS:---read-var-info=yes --leak-check=full --track-fds=yes}"
FLAGS="$FLAGS --log-file=$LOGFILE.%p"

FOUND_ANY=false
FAILED=

# Find all the tests (yes, doing it by a name is a nasty hack)
# Since the while runs in a subprocess, we need to get the assignments out, done by the eval
eval $(find . -type f -executable -name run_unittests -print | grep -v '\.libs/run_unittests$' | while read testname ; do
    sed -e 's#exec "#exec valgrind '"$FLAGS"' "#' "$testname" > "$testname.valgrind"
    chmod +x "$testname.valgrind"
    echo "$testname" >>"$LOGFILE"
    echo "===============" >>"$LOGFILE"
    pushd $(dirname "$testname") >/dev/null
    "./run_unittests.valgrind" >&2 &
    PID="$!"
    set +e
    wait "$PID"
    CODE="$?"
    set -e
    popd >/dev/null
    if [ "$CODE" != 0 ] ; then
        echo 'FAILED="$FAILED
'"$testname"'"'
    fi
    NAME="$LOGFILE.$PID"
    rm "$testname.valgrind"
    # Remove the ones from death tests
    grep "==$PID==" "$NAME" >>"$LOGFILE"
    rm "$NAME"
    echo 'FOUND_ANY=true'
done)

if [ -n "$FAILED" ] ; then
    echo "These tests failed:" >&2
    echo "$FAILED" >&2
fi

if ! $FOUND_ANY ; then
    echo "No test was found. It is possible you configured witouth --with-gtest or you run it from wrong directory" >&2
    exit 1
fi
