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

# Test name
TEST_NAME="D2.dynamicReconfiguration"
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

# Invalid configuration (negative valid-lifetime) to check that Kea
# gracefully handles reconfiguration errors.
CONFIG_INVALID="{
    \"DhcpDdns\":
    {
        \"ip_address\": \"127.0.0.1\",
        \"port\": BOGUS,
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
    printf "ERROR: timeout waiting for D2 to start.\n"
    clean_exit 1
fi

# Check if it is still running. It could have terminated (e.g. as a result
# of configuration failure).
get_pids
if [ ${_GET_PIDS_NUM} -ne 1 ]; then
    printf "ERROR: expected one D2 process to be started. Found %d processes\
 started.\n" ${_GET_PIDS_NUM}
    clean_exit 1
fi

# Check in the log file, how many times server has been configured. It should
# be just once on startup.
get_reconfigs
if [ ${_GET_RECONFIGS} -ne 1 ]; then
    printf "ERROR: D2 hasn't been configured.\n"
    clean_exit 1
else
    printf "D2 successfully configured.\n"
fi

# Now use invalid configuration.
create_config "${CONFIG_INVALID}"

# Try to reconfigure by sending SIGHUP
send_signal 1

# Wait up to 10s for the D2Controller to log reload signal received.
wait_for_message 10 "DHCP_DDNS_CFG_FILE_RELOAD_SIGNAL_RECVD"  1
if [ ${_WAIT_FOR_MESSAGE} -eq 0 ]; then
    printf "ERROR: D2Process did report the reload signal receipt.\n"
    clean_exit 1
fi

# After receiving SIGHUP the server should try to reconfigure itself.
# The configuration provided is invalid so it should result in
# reconfiguration failure but the server should still be running.
wait_for_message 10 "DHCP_DDNS_CFG_FILE_RELOAD_ERROR" 1
if [ ${_WAIT_FOR_MESSAGE} -eq 0 ]; then
    printf "ERROR: D2 did not report reload error.\n"
    clean_exit 1
fi

# Make sure the server is still operational.
get_pids
if [ ${_GET_PIDS_NUM} -ne 1 ]; then
    printf "ERROR: D2 process was killed when attempting reconfiguration.\n"
    clean_exit 1
fi

# Restore the good configuration.
create_config "${CONFIG}"

# Reconfigure the server with SIGHUP.
send_signal 1

# There should be two occurrences of the DCTL_CONFIG_COMPLETE messages.
# Wait for it up to 10s.
wait_for_message 10 "DCTL_CONFIG_COMPLETE" 2

# After receiving SIGHUP the server should get reconfigured and the
# reconfiguration should be noted in the log file. We should now
# have two configurations logged in the log file.
if [ ${_WAIT_FOR_MESSAGE} -eq 0 ]; then
    printf "ERROR: D2 hasn't been reconfigured.\n"
    clean_exit 1
else
    printf "D2 successfully reconfigured.\n"
fi

# Make sure the server is still operational.
get_pids
if [ ${_GET_PIDS_NUM} -ne 1 ]; then
    printf "ERROR: D2 process was killed when attempting reconfiguration.\n"
    clean_exit 1
fi

# All ok. Shut down Kea and exit.
clean_exit 0
