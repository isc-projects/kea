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
import time

# This is a list of files that are freshly copied before each scenario
# The first element is the original, the second is the target that will be
# used by the tests that need them
copylist = [
["configurations/example.org.config.orig", "configurations/example.org.config"]
]

# class that keeps track of one running process and the files
# we created for it. This needs to be moved to our framework-framework
# as it is not specifically for bind10
class RunningProcess:
    def __init__(self, step, process_name, args):
        # set it to none first so destructor won't error if initializer did
        self.process = None
        self.step = step
        self.process_name = process_name
        self.remove_files_on_exit = True
        self._create_filenames()
        self._start_process(args)

    def _start_process(self, args):
        stderr_write = open(self.stderr_filename, "w")
        stdout_write = open(self.stdout_filename, "w")
        self.process = subprocess.Popen(args, 1, None, subprocess.PIPE,
                                        stdout_write, stderr_write)
        # open them again, this time for reading
        self.stderr = open(self.stderr_filename, "r")
        self.stdout = open(self.stdout_filename, "r")

    def mangle_filename(self, filebase, extension):
        filebase = re.sub("\s+", "_", filebase)
        filebase = re.sub("[^a-zA-Z.\-_]", "", filebase)
        return filebase + "." + extension

    def _create_filenames(self):
        filebase = self.step.scenario.feature.name + "-" +\
                   self.step.scenario.name + "-" + self.process_name
        self.stderr_filename = self.mangle_filename(filebase, "stderr")
        self.stdout_filename = self.mangle_filename(filebase, "stdout")

    def stop_process(self):
        if self.process is not None:
            self.process.terminate()
            self.process.wait()
        self.process = None
        if self.remove_files_on_exit:
            self._remove_files()

    def _remove_files(self):
        os.remove(self.stderr_filename)
        os.remove(self.stdout_filename)

    def _wait_for_output_str(self, filename, running_file, strings, only_new):
        if not only_new:
            full_file = open(filename, "r")
            for line in full_file:
                for string in strings:
                    if line.find(string) != -1:
                        full_file.close()
                        return string
        while True:
            where = running_file.tell()
            line = running_file.readline()
            if line:
                for string in strings:
                    if line.find(string) != -1:
                        return string
            else:
                time.sleep(0.5)
                running_file.seek(where)

    def wait_for_stderr_str(self, strings, only_new = True):
        return self._wait_for_output_str(self.stderr_filename, self.stderr,
                                         strings, only_new)

    def wait_for_stdout_str(self, strings, only_new = True):
        return self._wait_for_output_str(self.stdout_filename, self.stdout,
                                         strings, only_new)

# Container class for a number of running processes
# i.e. servers like bind10, etc
# one-shot programs like dig or bindctl are started and closed separately
class RunningProcesses:
    def __init__(self):
        self.processes = {}
    
    def add_process(self, step, process_name, args):
        assert process_name not in self.processes,\
            "Process " + name + " already running"
        self.processes[process_name] = RunningProcess(step, process_name, args)

    def get_process(self, process_name):
        assert process_name in self.processes,\
            "Process " + name + " unknown"
        return self.processes[process_name]

    def stop_process(self, process_name):
        assert process_name in self.processes,\
            "Process " + name + " unknown"
        self.processes[process_name].stop_process()
        del self.processes[process_name]
        
    def stop_all_processes(self):
        for process in self.processes.values():
            process.stop_process()
    
    def keep_files(self):
        for process in self.processes.values():
            process.remove_files_on_exit = False

    def wait_for_stderr_str(self, process_name, strings, only_new = True):
        """Wait for any of the given strings in the given processes stderr 
        output. If only_new is True, it will only look at the lines that are 
        printed to stderr since the last time this method was called. If 
        False, it will also look at the previously printed lines. This will 
        block until one of the strings is found. TODO: we may want to put in 
        a timeout for this... Returns the string that is found"""
        assert process_name in self.processes,\
           "Process " + process_name + " unknown"
        return self.processes[process_name].wait_for_stderr_str(strings,
                                                                only_new)

    def wait_for_stdout_str(self, process_name, strings, only_new = True):
        """Wait for any of the given strings in the given processes stderr 
        output. If only_new is True, it will only look at the lines that are 
        printed to stderr since the last time this method was called. If 
        False, it will also look at the previously printed lines. This will 
        block until one of the strings is found. TODO: we may want to put in 
        a timeout for this... Returns the string that is found"""
        assert process_name in self.processes,\
           "Process " + process_name + " unknown"
        return self.processes[process_name].wait_for_stdout_str(strings,
                                                                only_new)

@before.each_scenario
def initialize(feature):
    # Keep track of running processes
    world.processes = RunningProcesses()

    # Convenience variable to access the last query result from querying.py
    world.last_query_result = None

    # Some tests can modify the settings. If the tests fail half-way, or
    # don't clean up, this can leave configurations or data in a bad state,
    # so we copy them from originals before each scenario
    for item in copylist:
        shutil.copy(item[0], item[1])

@after.each_scenario
def cleanup(feature):
    # Stop any running processes we may have had around
    world.processes.stop_all_processes()
