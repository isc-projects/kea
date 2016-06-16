# Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

'''Support for Kea hook in python'''

print("hook.py is loading")

import kea

NEXT_STEP_CONTINUE = 0
NEXT_STEP_SKIP = 1
NEXT_STEP_DROP = 2

def pkt4_receive(query4):
    """pkt4_receive hook point.

    parameter: inout Pkt4Ptr query4
    return: next step
    """
    print("pkt4_receive: handler is called with", query4)
    return NEXT_STEP_CONTINUE

print("hook.py loaded")
