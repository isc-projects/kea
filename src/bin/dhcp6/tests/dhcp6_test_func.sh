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

# Begins a test by prining its name.
# It requires the ${TEST_NAME} variable to be hold the test name.
test_start() {
    printf "\nSTART TEST ${TEST_NAME}\n"
}

# Stores the configuration specified as a parameter in the configuration
# file which name has been set in the ${CFG_FILE} variable.
create_config() {
    printf "Creating Kea configuration file: %s.\n" ${CFG_FILE}
    printf "%b" ${1} > ${CFG_FILE}
}

# Sets Kea logger to write to the file specified by the global value
# ${LOG_FILE}.
set_logger() {
    printf "Kea log will be stored in %s.\n" ${LOG_FILE}
    export B10_LOGGER_DESTINATION=${LOG_FILE}
}

# Returns the number of running b10-dhcp6 process pids and
# the list of pids.
_GET_PIDS=     # Holds space separated list of DHCPv6 pids.
_GET_PIDS_NUM= # Holds the number of DHCPv6 server pids.
get_pids() {
    _GET_PIDS=`ps -o pid,command | grep b10-dhcp6 | grep -v grep | awk '{print $1}'`
    _GET_PIDS_NUM=`printf "%s" "${_GET_PIDS}" | wc -w | awk '{print $1}'`
}

# Returns the number of occurrences of the Kea log message in the
# log file.
_GET_LOG_MESSAGES= # Holds the number of log message occurrences.
get_log_messages() {
    # Grep log file for the logger message occurrences.
    _GET_LOG_MESSAGES=`grep -o ${1} ${LOG_FILE} | wc -w`
    # Remove whitespaces.
    ${_GET_LOG_MESSAGES##*[! ]}
}

# Returns the number of server configurations performed so far. Also
# returns the number of configuration errors.
_GET_RECONFIGS=      # Number of configurations so far.
_GET_RECONFIG_ERRORS=  # Number of configuration errors.
get_reconfigs() {
    # Grep log file for DHCP6_CONFIG_COMPLETE occurences. There should
    # be one occurence per (re)configuration.
    _GET_RECONFIGS=`grep -o DHCP6_CONFIG_COMPLETE ${LOG_FILE} | wc -w`
    # Grep log file for DHCP6_CONFIG_LOAD_FAIL to check for configuration
    # failures.
    _GET_RECONFIG_ERRORS=`grep -o DHCP6_CONFIG_LOAD_FAIL ${LOG_FILE} | wc -w`
    # Remove whitespaces
    ${_GET_RECONFIGS##*[! ]}
    ${_GET_RECONFIG_ERRORS##*[! ]}
}

# Performs cleanup for a test.
# It shuts down running Kea processes and removes temporary files.
cleanup() {
    get_pids
    # Shut down running Kea processes.
    for pid in ${_GET_PIDS}
    do
        printf "Shutting down Kea proccess having pid %d.\n" ${pid}
        kill -9 ${pid}
    done
    # Remove temporary files.
    rm -rf ${LOG_FILE}
    rm -rf ${CFG_FILE}
}

# Exists the test in the clean way.
# It peformes the cleanup and prints whether the test has passed or failed.
# If a test fails, the Kea log is dumped.
clean_exit() {
    if [ $1 -eq 0 ]; then
        cleanup
        printf "PASSED ${TEST_NAME}\n\n"
    else
        # Dump log file if exists for debugging purposes.
        if [ -s ${LOG_FILE} ]; then
            printf "Log file dump:\n"
            cat ${LOG_FILE}
        fi
        cleanup
        printf "FAILED ${TEST_NAME}\n\n"
    fi
    exit $1
}

# Starts Kea process in background using a configuration file specified
# in the global variable ${CFG_FILE}
start_kea() {
    printf "Running command %s.\n" "\"$BIN -c ${CFG_FILE}\""
    $BIN -c ${CFG_FILE} &
}

# Waits for Kea to startup with timeout.
# This function repeatedly checs if the Kea log file has been created
# and is non-empty. If it is, the function assumes that Kea has started.
# It doesn't check the contents of the log file though. 
# If the log file doesn't exist the function sleeps for a second and
# checks again. This is repeated until timeout is reached or non-empty
# log file is found. If timeout is reached, the function reports an
# error.
_WAIT_FOR_KEA=0  # Holds 0 if Kea hasn't started, 1 otherwise
wait_for_kea() {
    timeout=${1} # Desired timeout in seconds.
    loops=0
    _WAIT_FOR_KEA=0
    while [ ! -s ${LOG_FILE} ] && [ ${loops} -le ${timeout} ]; do
        printf "."
        sleep 1
        loops=`expr $loops + 1`
    done
    printf "\n"
    if [ ${loops} -le ${timeout} ]; then
        _WAIT_FOR_KEA=1
    fi
}

# Waits for a specific message to occur in the Kea log file.
# This function is called when the test expects specific message
# to show up in the log file as a result of some action that has
# been taken. Typically, the test expects that the message
# is logged when the SIGHUP or SIGTERM signal has been sent to the
# Kea process.
# This function waits a specified number of seconds for the number
# of message occurrences to show up. If the expected number of
# message doesn't occur, the error status is returned.
_WAIT_FOR_MESSAGE=0  # Holds 0 if the message hasn't occured, 1 otherwise.
wait_for_message() {
    timeout=${1}     # Timeout value in seconds.
    message=${2}     # Expected message id.
    occurrences=${3} # Number of expected occurrences.
    loops=0          # Number of loops performed so far.
    _WAIT_FOR_MESSAGE=0
    # Check if log file exists and if we reached timeout.
    while [ ! -s {LOG_FILE} ] && [ ${loops} -le ${timeout} ]; do
        printf "."
        # Check if the message has been logged.
        get_log_messages ${message}
        if [ ${_GET_LOG_MESSAGES} -eq ${occurrences} ]; then
            printf "\n"
            _WAIT_FOR_MESSAGE=1            
            return
        fi
        # Message not recorded. Keep going.
        sleep 1
        loops=`expr ${loops} + 1`
    done
    printf "\n"
    # Timeout.
}

# Sends specified signal to the Kea process.
send_signal() {
    sig=$1   # Signal number.
    # Get Kea pid.
    get_pids
    if [ ${_GET_PIDS_NUM} -ne 1 ]; then
        printf "ERROR: expected one Kea process to be started. Found %d processes started.\n" ${_GET_PIDS_NUM}
        clean_exit 1
    fi 
    printf "Sending signal ${sig} to Kea process (pid=%s).\n" ${_GET_PIDS}
    # Actually send a signal.
    kill -${sig} ${_GET_PIDS}
}
