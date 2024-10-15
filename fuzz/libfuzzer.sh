#!/bin/sh

# Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

set -eux

exec "${2}" "${1}/$(basename "${2}").in" -max_total_time=5 -print_pcs=1 -print_final_stats=1 -print_corpus_stats=1 -print_coverage=1
