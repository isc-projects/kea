#!/bin/bash

# Yes, really bash, there are some bashisms

# First, make sure the tests are up to date
make

if [ $? = 2 ] ; then
    echo "Did you run configure? Do you call me from the top bind10 directory?" >&2
    exit 1
fi

set -ex

# Some configuration
# TODO Escape for sed, this might break
LOGFILE="${VALGRIND_FILE:-valgrind.log}"
FLAGS="${VALGRIND_FLAGS:---read-var-info=yes --leak-check=full}"
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
    "$testname.valgrind" >&2 &
    PID="$!"
    wait "$PID"
    CODE="$?"
    if [ "$CODE" != 0 ] ; then
        echo 'FAILED="$FAILED
'"'$testname'"
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
