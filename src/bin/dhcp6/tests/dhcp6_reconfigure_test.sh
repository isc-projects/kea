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

# Name of the Kea executable.
BIN="../b10-dhcp6"
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

_GETPIDS1=
_GETPIDS2=
getpids() {
    _GETPIDS1=`ps -o pid,command | grep b10-dhcp | grep -v grep | awk '{print $1}'`
    _GETPIDS2=`printf "%s" "${_GETPIDS1}" | wc -w | awk '{print $1}'`
}

cleanup() {
    getpids
    for pid in ${_GETPIDS1}
    do
        printf "Shutting down Kea proccess having pid %d.\n" ${pid}
        kill -9 ${pid}
    done
}

cleanexit() {
    cleanup
    exit $1
}

printf "Creating Kea configuration file: %s.\n" ${CFG_FILE}
printf "%b" ${CONFIG} > ${CFG_FILE}

printf "Kea log will be stored in %s.\n" ${LOG_FILE}
export B10_LOGGER_DESTINATION=${LOG_FILE}

# Kill any dangling Kea processes.
cleanup

# Start fresh Kea process using a test configuration.
printf "Running command %s.\n" "\"$BIN -c ${CFG_FILE}\""
$BIN -c ${CFG_FILE} &

# Wait a second. It may take a bit before it starts.
sleep 1

# Make sure that exactly one process has been started.
getpids
if [ ${_GETPIDS2} -ne 1 ]; then
    printf "ERROR: expected one Kea process to be started. Found %d processes started.\n" ${_GETPIDS2}
    cleanexit 1
fi

# Reconfigure the server with SIGUP.
printf "Sending SIGUP to Kea process (pid=%s) to reconfigure the server.\n" ${_GETPIDS1}
kill -1 ${_GETPIDS1}

# Be patient. Kea may need a while to reconfigure or shut down if reconfiguration
# didn't work.
sleep 1

# Make sure it is still operational.
getpids
if [ ${_GETPIDS2} -ne 1 ]; then
    printf "ERROR: Kea process was killed when attempting reconfiguration.\n"
    cleanexit 1
fi

# All ok. Shut down Kea and exit.
cleanexit 0
