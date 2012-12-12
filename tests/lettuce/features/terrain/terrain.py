# Copyright (C) 2011  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#
# This is the 'terrain' in which the lettuce lives. By convention, this is
# where global setup and teardown is defined.
#
# We declare some attributes of the global 'world' variables here, so the
# tests can safely assume they are present.
#
# We also use it to provide scenario invariants, such as resetting data.
#

from lettuce import *
import subprocess
import os.path
import shutil
import re
import sys
import time

# In order to make sure we start all tests with a 'clean' environment,
# We perform a number of initialization steps, like restoring configuration
# files, and removing generated data files.

# This approach may not scale; if so we should probably provide specific
# initialization steps for scenarios. But until that is shown to be a problem,
# It will keep the scenarios cleaner.

# This is a list of files that are freshly copied before each scenario
# The first element is the original, the second is the target that will be
# used by the tests that need them
copylist = [
    ["configurations/bindctl_commands.config.orig",
     "configurations/bindctl_commands.config"],
    ["configurations/example.org.config.orig",
     "configurations/example.org.config"],
    ["configurations/bindctl/bindctl.config.orig",
     "configurations/bindctl/bindctl.config"],
    ["configurations/auth/auth_basic.config.orig",
     "configurations/auth/auth_basic.config"],
    ["configurations/auth/auth_badzone.config.orig",
     "configurations/auth/auth_badzone.config"],
    ["configurations/resolver/resolver_basic.config.orig",
     "configurations/resolver/resolver_basic.config"],
    ["configurations/multi_instance/multi_auth.config.orig",
     "configurations/multi_instance/multi_auth.config"],
    ["configurations/ddns/ddns.config.orig",
     "configurations/ddns/ddns.config"],
    ["configurations/ddns/noddns.config.orig",
     "configurations/ddns/noddns.config"],
    ["configurations/xfrin/retransfer_master.conf.orig",
     "configurations/xfrin/retransfer_master.conf"],
    ["configurations/xfrin/retransfer_slave.conf.orig",
     "configurations/xfrin/retransfer_slave.conf"],
    ["data/inmem-xfrin.sqlite3.orig",
     "data/inmem-xfrin.sqlite3"],
    ["data/xfrin-notify.sqlite3.orig",
     "data/xfrin-notify.sqlite3"],
    ["data/ddns/example.org.sqlite3.orig",
     "data/ddns/example.org.sqlite3"]
]

# This is a list of files that, if present, will be removed before a scenario
removelist = [
"data/test_nonexistent_db.sqlite3"
]

# When waiting for output data of a running process, use OUTPUT_WAIT_INTERVAL
# as the interval in which to check again if it has not been found yet.
# If we have waited OUTPUT_WAIT_MAX_INTERVALS times, we will abort with an
# error (so as not to hang indefinitely)
OUTPUT_WAIT_INTERVAL = 0.5
OUTPUT_WAIT_MAX_INTERVALS = 20

# class that keeps track of one running process and the files
# we created for it.
class RunningProcess:
    def __init__(self, step, process_name, args):
        # set it to none first so destructor won't error if initializer did
        """
        Initialize the long-running process structure, and start the process.
        Parameters:
        step: The scenario step it was called from. This is used for
              determining the output files for redirection of stdout
              and stderr.
        process_name: The name to refer to this running process later.
        args: Array of arguments to pass to Popen().
        """
        self.process = None
        self.step = step
        self.process_name = process_name
        self.remove_files_on_exit = True
        self._check_output_dir()
        self._create_filenames()
        self._start_process(args)

    def _start_process(self, args):
        """
        Start the process.
        Parameters:
        args:
        Array of arguments to pass to Popen().
        """
        stderr_write = open(self.stderr_filename, "w")
        stdout_write = open(self.stdout_filename, "w")
        self.process = subprocess.Popen(args, 1, None, subprocess.PIPE,
                                        stdout_write, stderr_write)
        # open them again, this time for reading
        self.stderr = open(self.stderr_filename, "r")
        self.stdout = open(self.stdout_filename, "r")

    def mangle_filename(self, filebase, extension):
        """
        Remove whitespace and non-default characters from a base string,
        and return the substituted value. Whitespace is replaced by an
        underscore. Any other character that is not an ASCII letter, a
        number, a dot, or a hyphen or underscore is removed.
        Parameter:
        filebase: The string to perform the substitution and removal on
        extension: An extension to append to the result value
        Returns the modified filebase with the given extension
        """
        filebase = re.sub("\s+", "_", filebase)
        filebase = re.sub("[^a-zA-Z0-9.\-_]", "", filebase)
        return filebase + "." + extension

    def _check_output_dir(self):
        # We may want to make this overridable by the user, perhaps
        # through an environment variable. Since we currently expect
        # lettuce to be run from our lettuce dir, we shall just use
        # the relative path 'output/'
        """
        Make sure the output directory for stdout/stderr redirection
        exists.
        Fails if it exists but is not a directory, or if it does not
        and we are unable to create it.
        """
        self._output_dir = os.getcwd() + os.sep + "output"
        if not os.path.exists(self._output_dir):
            os.mkdir(self._output_dir)
        assert os.path.isdir(self._output_dir),\
            self._output_dir + " is not a directory."

    def _create_filenames(self):
        """
        Derive the filenames for stdout/stderr redirection from the
        feature, scenario, and process name. The base will be
        "<Feature>-<Scenario>-<process name>.[stdout|stderr]"
        """
        filebase = self.step.scenario.feature.name + "-" +\
                   self.step.scenario.name + "-" + self.process_name
        self.stderr_filename = self._output_dir + os.sep +\
                               self.mangle_filename(filebase, "stderr")
        self.stdout_filename = self._output_dir + os.sep +\
                               self.mangle_filename(filebase, "stdout")

    def stop_process(self):
        """
        Stop this process by calling terminate(). Blocks until process has
        exited. If remove_files_on_exit is True, redirected output files
        are removed.
        """
        if self.process is not None:
            self.process.terminate()
            self.process.wait()
        self.process = None
        if self.remove_files_on_exit:
            self._remove_files()

    def _remove_files(self):
        """
        Remove the files created for redirection of stdout/stderr output.
        """
        os.remove(self.stderr_filename)
        os.remove(self.stdout_filename)

    def _wait_for_output_str(self, filename, running_file, strings, only_new, matches = 1):
        """
        Wait for a line of output in this process. This will (if only_new is
        False) first check all previous output from the process, and if not
        found, check all output since the last time this method was called.
        For each line in the output, the given strings array is checked. If
        any output lines checked contains one of the strings in the strings
        array, that string (not the line!) is returned.
        Parameters:
        filename: The filename to read previous output from, if applicable.
        running_file: The open file to read new output from.
        strings: Array of strings to look for.
        only_new: If true, only check output since last time this method was
                  called. If false, first check earlier output.
        matches: Check for the string this many times.
        Returns a tuple containing the matched string, and the complete line
        it was found in.
        Fails if none of the strings was read after 10 seconds
        (OUTPUT_WAIT_INTERVAL * OUTPUT_WAIT_MAX_INTERVALS).
        """
        match_count = 0
        if not only_new:
            full_file = open(filename, "r")
            for line in full_file:
                for string in strings:
                    if line.find(string) != -1:
                        match_count += 1
                        if match_count >= matches:
                            full_file.close()
                            return (string, line)
        wait_count = 0
        while wait_count < OUTPUT_WAIT_MAX_INTERVALS:
            where = running_file.tell()
            line = running_file.readline()
            if line:
                for string in strings:
                    if line.find(string) != -1:
                        match_count += 1
                        if match_count >= matches:
                            return (string, line)
            else:
                wait_count += 1
                time.sleep(OUTPUT_WAIT_INTERVAL)
                running_file.seek(where)
        assert False, "Timeout waiting for process output: " + str(strings)

    def wait_for_stderr_str(self, strings, only_new = True, matches = 1):
        """
        Wait for one of the given strings in this process's stderr output.
        Parameters:
        strings: Array of strings to look for.
        only_new: If true, only check output since last time this method was
                  called. If false, first check earlier output.
        matches: Check for the string this many times.
        Returns a tuple containing the matched string, and the complete line
        it was found in.
        Fails if none of the strings was read after 10 seconds
        (OUTPUT_WAIT_INTERVAL * OUTPUT_WAIT_MAX_INTERVALS).
        """
        return self._wait_for_output_str(self.stderr_filename, self.stderr,
                                         strings, only_new, matches)

    def wait_for_stdout_str(self, strings, only_new = True, matches = 1):
        """
        Wait for one of the given strings in this process's stdout output.
        Parameters:
        strings: Array of strings to look for.
        only_new: If true, only check output since last time this method was
                  called. If false, first check earlier output.
        matches: Check for the string this many times.
        Returns a tuple containing the matched string, and the complete line
        it was found in.
        Fails if none of the strings was read after 10 seconds
        (OUTPUT_WAIT_INTERVAL * OUTPUT_WAIT_MAX_INTERVALS).
        """
        return self._wait_for_output_str(self.stdout_filename, self.stdout,
                                         strings, only_new, matches)

# Container class for a number of running processes
# i.e. servers like bind10, etc
# one-shot programs like dig or bindctl are started and closed separately
class RunningProcesses:
    def __init__(self):
        """
        Initialize with no running processes.
        """
        self.processes = {}

    def add_process(self, step, process_name, args):
        """
        Start a process with the given arguments, and store it under the given
        name.
        Parameters:
        step: The scenario step it was called from. This is used for
              determining the output files for redirection of stdout
              and stderr.
        process_name: The name to refer to this running process later.
        args: Array of arguments to pass to Popen().
        Fails if a process with the given name is already running.
        """
        assert process_name not in self.processes,\
            "Process " + process_name + " already running"
        self.processes[process_name] = RunningProcess(step, process_name, args)

    def get_process(self, process_name):
        """
        Return the Process with the given process name.
        Parameters:
        process_name: The name of the process to return.
        Fails if the process is not running.
        """
        assert process_name in self.processes,\
            "Process " + name + " unknown"
        return self.processes[process_name]

    def stop_process(self, process_name):
        """
        Stop the Process with the given process name.
        Parameters:
        process_name: The name of the process to return.
        Fails if the process is not running.
        """
        assert process_name in self.processes,\
            "Process " + name + " unknown"
        self.processes[process_name].stop_process()
        del self.processes[process_name]

    def stop_all_processes(self):
        """
        Stop all running processes.
        """
        for process in self.processes.values():
            process.stop_process()

    def keep_files(self):
        """
        Keep the redirection files for stdout/stderr output of all processes
        instead of removing them when they are stopped later.
        """
        for process in self.processes.values():
            process.remove_files_on_exit = False

    def wait_for_stderr_str(self, process_name, strings, only_new = True, matches = 1):
        """
        Wait for one of the given strings in the given process's stderr output.
        Parameters:
        process_name: The name of the process to check the stderr output of.
        strings: Array of strings to look for.
        only_new: If true, only check output since last time this method was
                  called. If false, first check earlier output.
        matches: Check for the string this many times.
        Returns the matched string.
        Fails if none of the strings was read after 10 seconds
        (OUTPUT_WAIT_INTERVAL * OUTPUT_WAIT_MAX_INTERVALS).
        Fails if the process is unknown.
        """
        assert process_name in self.processes,\
           "Process " + process_name + " unknown"
        return self.processes[process_name].wait_for_stderr_str(strings,
                                                                only_new,
                                                                matches)

    def wait_for_stdout_str(self, process_name, strings, only_new = True, matches = 1):
        """
        Wait for one of the given strings in the given process's stdout output.
        Parameters:
        process_name: The name of the process to check the stdout output of.
        strings: Array of strings to look for.
        only_new: If true, only check output since last time this method was
                  called. If false, first check earlier output.
        matches: Check for the string this many times.
        Returns the matched string.
        Fails if none of the strings was read after 10 seconds
        (OUTPUT_WAIT_INTERVAL * OUTPUT_WAIT_MAX_INTERVALS).
        Fails if the process is unknown.
        """
        assert process_name in self.processes,\
           "Process " + process_name + " unknown"
        return self.processes[process_name].wait_for_stdout_str(strings,
                                                                only_new,
                                                                matches)

@before.each_scenario
def initialize(scenario):
    """
    Global initialization for each scenario.
    """
    # Keep track of running processes
    world.processes = RunningProcesses()

    # Convenience variable to access the last query result from querying.py
    world.last_query_result = None

    # For slightly better errors, initialize a process_pids for the relevant
    # steps
    world.process_pids = None

    # Some tests can modify the settings. If the tests fail half-way, or
    # don't clean up, this can leave configurations or data in a bad state,
    # so we copy them from originals before each scenario
    for item in copylist:
        shutil.copy(item[0], item[1])

    for item in removelist:
        if os.path.exists(item):
            os.remove(item)

@after.each_scenario
def cleanup(scenario):
    """
    Global cleanup for each scenario.
    """
    # Keep output files if the scenario failed
    if not scenario.passed:
        world.processes.keep_files()
    # Stop any running processes we may have had around
    world.processes.stop_all_processes()

# Environment check
# Checks if LETTUCE_SETUP_COMPLETED is set in the environment
# If not, abort with an error to use the run-script
if 'LETTUCE_SETUP_COMPLETED' not in os.environ:
    print("Environment check failure; LETTUCE_SETUP_COMPLETED not set")
    print("Please use the run_lettuce.sh script. If you want to test an")
    print("installed version of bind10 with these tests, use")
    print("run_lettuce.sh -I [lettuce arguments]")
    sys.exit(1)
