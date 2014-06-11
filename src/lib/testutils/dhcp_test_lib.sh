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

# A list of Kea processes, mainly used by the cleanup functions.
KEA_PROCS="b10-dhcp4 b10-dhcp6 b10-dhcp-ddns"

### Logging functions ###

# Prints error message.
test_lib_error() {
    printf "ERROR/test_lib: %s\n" "${1}"
}

# Prints info message.
test_lib_info() {
    printf "INFO/test_lib: %s\n" "${1}"
}

### Assertions ###

# Assertion that checks if two numbers are equal.
# If numbers are not equal, the mismatched values are presented and the
# detailed error is printed. The detailed error must use the printf
# formatting like this:
#    "Expected that some value 1 %d is equal to some other value %d".
assert_eq() {
    val1=${1}         # Reference value
    val2=${2}         # Tested value
    detailed_err=${3} # Detailed error format string
    # If nothing found, present an error an exit.
    if [ ${val1} -ne ${val2} ]; then
        printf "Assertion failure: ${val1} != ${val2}, for val1=${val1}, val2=${val2}\n"
        printf "${detailed_err}\n" ${val1} ${val2}
        clean_exit 1
    fi
}

# Assertion that checks if one string contains another string.
# If assertion fails, both strings are displayed and the detailed
# error is printed. The detailed error must use the printf formatting
# like this:
#    "Expected some string to contain this string: %s".
assert_string_contains() {
    pattern=${1}      # Substring or awk pattern
    text=${2}         # Text to be searched for substring
    detailed_err=${3} # Detailed error format string
    # Search for a pattern
    match=$( printf "%s" "${text}" | awk /"${pattern}"/ )
    # If nothing found, present an error and exit.
    if [ -z "${match}" ]; then
        printf "Assertion failure: \n\"%s\"\n\ndoesn't contain pattern:\n
\"%s\"\n\n" "${text}" "${pattern}"
        printf "${detailed_err}\n" "\"${pattern}\""
        clean_exit 1
    fi
}

# Begins a test by prining its name.
test_start() {
    TEST_NAME=${1}
    if [ -z ${TEST_NAME} ]; then
        test_lib_error "test_start requires test name as an argument"
        clean_exit 1
    fi
    printf "\nSTART TEST ${TEST_NAME}\n"
}

# Prints test result an cleans up after the test.
test_finish() {
    local exit_code=${1}  # Exit code to be returned by the exit function.
    if [ ${exit_code} -eq 0 ]; then
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
}

# Stores the configuration specified as a parameter in the configuration
# file which name has been set in the ${CFG_FILE} variable.
create_config() {
    local cfg=${1}  # Configuration string.
    if [ -z ${CFG_FILE} ]; then
        test_lib_error "create_config requires CFG_FILE variable be set"
        clean_exit 1

    elif [ -z "${cfg}" ]; then
        test_lib_error "create_config requires argument holding a configuration"
        clean_exit 1
    fi
    printf "Creating Kea configuration file: %s.\n" ${CFG_FILE}
    printf "%b" ${cfg} > ${CFG_FILE}
}

# Stores the keactrl configuration specified as a parameter in the
# configuration file which name has been set in the ${KEACTRL_CFG_FILE}
# variable.
create_keactrl_config() {
    local cfg=${1} # Configuration string.
    if [ -z ${KEACTRL_CFG_FILE} ]; then
        test_lib_error "create_keactrl_config requires KEACTRL_CFG_FILE \
variable be set"
        clean_exit 1

    elif [ -z "${cfg}" ]; then
        test_lib_error "create_keactrl_config requires argument holding a \
configuration"
        clean_exit 1
    fi
    printf "Creating keactrl configuration file: %s.\n" ${KEACTRL_CFG_FILE}
    printf "%b" ${cfg} > ${KEACTRL_CFG_FILE}
}

# Sets Kea logger to write to the file specified by the global value
# ${LOG_FILE}.
set_logger() {
    if [ -z ${LOG_FILE} ]; then
        test_lib_error "set_logger requies LOG_FILE variable be set"
        clean_exit 1
    fi
    printf "Kea log will be stored in %s.\n" ${LOG_FILE}
    export B10_LOGGER_DESTINATION=${LOG_FILE}
}

# Returns the number of running process pids and the list of pids.
# Return values:
#   _GET_PIDS: holds space separated list of pids.
#   _GET_PIDS_NUM: holds the number pids.
get_pids() {
    local proc_name=${1} # Process name
    if [ -z ${proc_name} ]; then
        test_lib_error "get_pids requires process name"
        clean_exit 1
    fi
    _GET_PIDS=$( ps axwwo pid,command | grep ${proc_name} \
        | grep -v grep | awk '{print $1}' )
    _GET_PIDS_NUM=$( printf "%s" "${_GET_PIDS}" | wc -w | awk '{print $1}' )
}

# Returns the number of occurrences of the Kea log message in the log file.
# Return value:
#   _GET_LOG_MESSAGES: number of log message occurrences.
get_log_messages() {
    local msg=${1}  # Message id, e.g. DHCP6_SHUTDOWN
    if [ -z ${msg} ]; then
        test_lib_error "get_log_messages require message identifier"
        clean_exit 1
    fi
    _GET_LOG_MESSAGES=0
    # If log file is not present, the number of occurrences is 0.
    if [ -s ${LOG_FILE} ]; then
        # Grep log file for the logger message occurrences.
        _GET_LOG_MESSAGES=$( grep -o ${msg} ${LOG_FILE} | wc -w )
        # Remove whitespaces.
        ${_GET_LOG_MESSAGES##*[! ]}
    fi
}

# Returns the number of server configurations performed so far. Also
# returns the number of configuration errors.
# Return values:
#   _GET_RECONFIGS: number of configurations so far.
#   _GET_RECONFIG_ERRORS: number of configuration errors.
get_reconfigs() {
    # Grep log file for CONFIG_COMPLETE occurences. There should
    # be one occurence per (re)configuration.
    _GET_RECONFIGS=$( grep -o CONFIG_COMPLETE ${LOG_FILE} | wc -w )
    # Grep log file for CONFIG_LOAD_FAIL to check for configuration
    # failures.
    _GET_RECONFIG_ERRORS=$( grep -o CONFIG_LOAD_FAIL ${LOG_FILE} | wc -w )
    # Remove whitespaces
    ${_GET_RECONFIGS##*[! ]}
    ${_GET_RECONFIG_ERRORS##*[! ]}
}

# Performs cleanup after test.
# It shuts down running Kea processes and removes temporary files.
# The location of the log file and the configuration files should be set
# in the ${LOG_FILE}, ${CFG_FILE} and ${KEACTRL_CFG_FILE} variables
# recpectively, prior to calling this function.
cleanup() {
    # KEA_PROCS holds the name of all Kea processes. Shut down each
    # of them if running.
    for proc_name in ${KEA_PROCS}
    do
        get_pids ${proc_name}
        # Shut down running Kea processes.
        for pid in ${_GET_PIDS}
        do
            printf "Shutting down Kea proccess having pid %d.\n" ${pid}
            kill -9 ${pid}
        done
    done
    # Remove temporary files.
    rm -rf ${LOG_FILE}
    rm -rf ${CFG_FILE}
    rm -rf ${KEACTRL_CFG_FILE}
}

# Exists the test in the clean way.
# It peformes the cleanup and prints whether the test has passed or failed.
# If a test fails, the Kea log is dumped.
clean_exit() {
    exit_code=${1}  # Exit code to be returned by the exit function.
    case ${exit_code} in
        ''|*[!0-9]*)
            test_lib_error "argument passed to clean_exit must be a number" ;;
    esac
    # Print test result and perform a cleanup
    test_finish ${exit_code}
    exit ${exit_code}
}

# Starts Kea process in background using a configuration file specified
# in the global variable ${CFG_FILE}.
start_kea() {
    bin=${1}
    if [ -z ${bin} ]; then
        test_lib_error "binary name must be specified for start_kea"
        clean_exit 1
    fi
    printf "Running command %s.\n" "\"${bin} -c ${CFG_FILE}\""
    ${bin} -c ${CFG_FILE} &
}

# Waits with timeout for Kea to start.
# This function repeatedly checs if the Kea log file has been created
# and is non-empty. If it is, the function assumes that Kea has started.
# It doesn't check the contents of the log file though.
# If the log file doesn't exist the function sleeps for a second and
# checks again. This is repeated until timeout is reached or non-empty
# log file is found. If timeout is reached, the function reports an
# error.
# Return value:
#    _WAIT_FOR_KEA: 0 if Kea hasn't started, 1 otherwise
wait_for_kea() {
    local timeout=${1} # Desired timeout in seconds.
    case ${timeout} in
        ''|*[!0-9]*)
            test_lib_error "argument passed to wait_for_kea must be a number"
            clean_exit 1 ;;
    esac
    local loops=0 # Loops counter
    _WAIT_FOR_KEA=0
    while [ ! -s ${LOG_FILE} ] && [ ${loops} -le ${timeout} ]; do
        printf "."
        sleep 1
        loops=$( expr $loops + 1 )
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
# Return value:
#    _WAIT_FOR_MESSAGE: 0 if the message hasn't occured, 1 otherwise.
wait_for_message() {
    local timeout=${1}     # Expected timeout value in seconds.
    local message=${2}     # Expected message id.
    local occurrences=${3} # Number of expected occurrences.

    # Validate timeout
    case ${timeout} in
        ''|*[!0-9]*)
            test_lib_error "argument timeout passed to wait_for_message must \
be a number"
        clean_exit 1 ;;
    esac

    # Validate message
    if [ -z ${message} ]; then
        test_lib_error "message id is a required argument for wait_for_message"
        clean_exit 1
    fi

    # Validate occurrences
    case ${occurrences} in
        ''|*[!0-9]*)
            test_lib_error "argument occurrences passed to wait_for_message \
must be a number"
        clean_exit 1 ;;
    esac

    local loops=0          # Number of loops performed so far.
    _WAIT_FOR_MESSAGE=0
    # Check if log file exists and if we reached timeout.
    while [ ${loops} -le ${timeout} ]; do
        printf "."
        # Check if the message has been logged.
        get_log_messages ${message}
        if [ ${_GET_LOG_MESSAGES} -ge ${occurrences} ]; then
            printf "\n"
            _WAIT_FOR_MESSAGE=1
            return
        fi
        # Message not recorded. Keep going.
        sleep 1
        loops=$( expr ${loops} + 1 )
    done
    printf "\n"
    # Timeout.
}

# Sends specified signal to the Kea process.
send_signal() {
    local sig=${1}       # Signal number.
    local proc_name=${2} # Process name

    # Validate signal
    case ${sig} in
        ''|*[!0-9]*)
            test_lib_error "signal number passed to send_signal \
must bea number"
        clean_exit 1 ;;
    esac
    # Validate process name
    if [ -z ${proc_name} ]; then
        test_lib_error "send_signal requires process name be passed as argument"
        clean_exit 1
    fi
    # Get Kea pid.
    get_pids ${proc_name}
    if [ ${_GET_PIDS_NUM} -ne 1 ]; then
        printf "ERROR: expected one Kea process to be started.\
 Found %d processes started.\n" ${_GET_PIDS_NUM}
        clean_exit 1
    fi
    printf "Sending signal ${sig} to Kea process (pid=%s).\n" ${_GET_PIDS}
    # Actually send a signal.
    kill -${sig} ${_GET_PIDS}
}
