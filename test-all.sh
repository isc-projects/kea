#!/bin/sh

test_cmds=$(meson introspect --tests build -i | jq -r .[].cmd[] | sort -V)

for test_cmd in ${test_cmds}; do
    "${test_cmd}"
done
