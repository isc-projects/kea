# Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

if [ $# -ne 2 ]; then
    printf "USAGE: d2_shutdown_test.sh <test_name> <signal_num>\n"
    exit 1
fi

# Test name
TEST_NAME=$1
# Signal number to be used for this test.
SIG_NUM=$2
# Path to the temporary configuration file.
CFG_FILE="test_config.json"
# Path to the Kea log file.
LOG_FILE="test.log"
# Kea configuration to be stored in the configuration file.
CONFIG="{
    \"DhcpDdns\":
    {
        \"ip_address\": \"127.0.0.1\",
        \"port\": 53001,
        \"tsig_keys\": [],
        \"forward_ddns\" : {},
        \"reverse_ddns\" : {}
    }
}"

# Set the location of the executable.
BIN="b10-dhcp-ddns"
BIN_PATH=".."

# Import common test library.
. $(dirname $0)/../../../lib/testutils/dhcp_test_lib.sh

# Log the start of the test and print test name.
test_start
# Remove dangling Kea instances and remove log files.
cleanup
# Create new configuration file.
create_config "${CONFIG}"
# Instruct Kea to log to the specific file.
set_logger
# Start Kea.
start_kea
# Wait up to 20s for Kea to start.
wait_for_kea 20
if [ ${_WAIT_FOR_KEA} -eq 0 ]; then
    printf "ERROR: timeout waiting for D2 to start.\n".
    clean_exit 1
fi

# Check if it is still running. It could have terminated (e.g. as a result
# of configuration failure).
get_pids
if [ ${_GET_PIDS_NUM} -ne 1 ]; then
    printf "ERROR: expected one Kea process to be started. Found %d processes\
 started.\n" ${_GET_PIDS_NUM}
    clean_exit 1
fi

# Check in the log file, how many times D2 been configured. It should
# be just once on startup.
get_reconfigs
if [ ${_GET_RECONFIGS} -ne 1 ]; then
    printf "ERROR: D2 hasn't been configured.\n"
    clean_exit 1
else
    printf "D2 successfully configured.\n"
fi

# Send signal to D2 (SIGTERM, SIGINT etc.)
send_signal ${SIG_NUM}

# Wait up to 10s for the D2Controller to log shutdown received.
wait_for_message 10 "DHCP_DDNS_SHUTDOWN_SIGNAL_RECVD" 1
if [ ${_WAIT_FOR_MESSAGE} -eq 0 ]; then
    printf "ERROR: D2Process did report the shutdown signal receipt.\n"
    clean_exit 1
fi

# Wait up to 10s for the D2Process to log graceful shutdown.
wait_for_message 10 "DHCP_DDNS_CLEARED_FOR_SHUTDOWN" 1
if [ ${_WAIT_FOR_MESSAGE} -eq 0 ]; then
    printf "ERROR: D2Process did not log orderly shutdown.\n"
    clean_exit 1
fi

# Now wait for D2Controller to log that it is exiting.
wait_for_message 10 "DCTL_STOPPING" 1
if [ ${_WAIT_FOR_MESSAGE} -eq 0 ]; then
    printf "ERROR: D2Controller did not log shutdown.\n"
    clean_exit 1
fi

# Server should have shut down.
get_pids
if [ ${_GET_PIDS_NUM} -ne 0 ]; then
    printf "ERROR: D2 did not shut down after receiving signal.\n"\
 ${_GET_PIDS_NUM}
    clean_exit 1
fi

clean_exit 0
