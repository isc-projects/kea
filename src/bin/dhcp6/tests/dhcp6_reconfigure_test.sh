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
TEST_NAME="DynamicReconfiguration"
# Path to the temporary configuration file.
CFG_FILE="test_config.json"
# Path to the Kea log file.
LOG_FILE="test.log"
# Kea configuration to be stored in the configuration file.
CONFIG="{
    \"Dhcp6\":
    {
        \"interfaces\": [ ],
        \"preferred-lifetime\": 3000,
        \"valid-lifetime\": 4000,
        \"renew-timer\": 1000,
        \"rebind-timer\": 2000,
        \"lease-database\":
        {
            \"type\": \"memfile\",
            \"persist\": false
        },
        \"subnet6\": [
        {
            \"subnet\": \"2001:db8:1::/64\",
            \"pool\": [ \"2001:db8:1::10-2001:db8:1::100\" ]
        } ]
    }
}"
# Invalid configuration (negative preferred-lifetime) to check that Kea
# gracefully handles reconfiguration errors.
CONFIG_INVALID="{
    \"Dhcp6\":
    {
        \"interfaces\": [ ],
        \"preferred-lifetime\": -3,
        \"valid-lifetime\": 4000,
        \"renew-timer\": 1000,
        \"rebind-timer\": 2000,
        \"lease-database\":
        {
            \"type\": \"memfile\",
            \"persist\": false
        },
        \"subnet6\": [
        {
            \"subnet\": \"2001:db8:1::/64\",
            \"pool\": [ \"2001:db8:1::10-2001:db8:1::100\" ]
        } ]
    }
}"

# Import common test library.
. $(dirname $0)/dhcp6_test_func.sh

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
    printf "ERROR: timeout waiting for Kea to start.\n"
    clean_exit 1
fi

# Check if it is still running. It could have terminated (e.g. as a result
# of configuration failure).
get_pids
if [ ${_GET_PIDS_NUM} -ne 1 ]; then
    printf "ERROR: expected one Kea process to be started. Found %d processes started.\n" ${_GET_PIDS_NUM}
    clean_exit 1
fi

# Check in the log file, how many times server has been configured. It should
# be just once on startup.
get_reconfigs
if [ ${_GET_RECONFIGS} -ne 1 ]; then
    printf "ERROR: server hasn't been configured.\n"
    clean_exit 1
else
    printf "Server successfully configured.\n"
fi

# Now use invalid configuration.
create_config "${CONFIG_INVALID}"

# Try to reconfigure by sending SIGHUP
send_signal 1

# The configuration should fail and the error message should be there.
wait_for_message 10 "DHCP6_CONFIG_LOAD_FAIL" 1

# After receiving SIGHUP the server should try to reconfigure itself.
# The configuration provided is invalid so it should result in
# reconfiguration failure but the server should still be running.
get_reconfigs
if [ ${_GET_RECONFIGS} -ne 1 ]; then
    printf "ERROR: server has been reconfigured despite bogus configuration.\n"
    clean_exit 1
elif [ ${_GET_RECONFIG_ERRORS} -ne 1 ]; then
    printf "ERROR: server did not report reconfiguration error despite attempt" \
        " to configure it with invalid configuration.\n"
    clean_exit 1
fi

# Make sure the server is still operational.
get_pids
if [ ${_GET_PIDS_NUM} -ne 1 ]; then
    printf "ERROR: Kea process was killed when attempting reconfiguration.\n"
    clean_exit 1
fi

# Restore the good configuration.
create_config "${CONFIG}"

# Reconfigure the server with SIGHUP.
send_signal 1

# There should be two occurrences of the DHCP6_CONFIG_COMPLETE messages.
# Wait for it up to 10s.
wait_for_message 10 "DHCP6_CONFIG_COMPLETE" 2

# After receiving SIGHUP the server should get reconfigured and the
# reconfiguration should be noted in the log file. We should now
# have two configurations logged in the log file.
if [ ${_WAIT_FOR_MESSAGE} -eq 0 ]; then
    printf "ERROR: server hasn't been reconfigured.\n"
    clean_exit 1
else
    printf "Server successfully reconfigured.\n"
fi

# Make sure the server is still operational.
get_pids
if [ ${_GET_PIDS_NUM} -ne 1 ]; then
    printf "ERROR: Kea process was killed when attempting reconfiguration.\n"
    clean_exit 1
fi

# All ok. Shut down Kea and exit.
clean_exit 0
