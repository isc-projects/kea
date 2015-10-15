// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <exceptions/exceptions.h>
#include <util/process_spawn.h>
#include <util/signal_set.h>
#include <boost/bind.hpp>
#include <map>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

namespace isc {
namespace util {

/// @brief Type for process state
struct ProcessState {

    /// @brief Constructor
    ProcessState() : running_(true), status_(0) {
    }

    /// @brief true until the exit status is collected
    bool running_;

    /// @brief 0 or the exit status
    int status_;
};

typedef std::map<pid_t, ProcessState> ProcessStates;

/// @brief Implementation of the @c ProcessSpawn class.
///
/// This pimpl idiom is used by the @c ProcessSpawn in this case to
/// avoid exposing the internals of the implementation, such as
/// custom handling of a SIGCHLD signal, and the conversion of the
/// arguments of the executable from the STL container to the array.
///
/// This class is made noncopyable so that we don't have attempts
/// to make multiple copies of an object.  This avoid problems
/// with multiple copies of objects for a single global resource
/// such as the SIGCHLD signal handler. In addition making it
/// noncopyable keeps the static check code from flagging the
/// lack of a copy constructor as an issue.
class ProcessSpawnImpl : boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// @param executable A path to the program to be executed.
    /// @param args Arguments for the program to be executed.
    ProcessSpawnImpl(const std::string& executable,
                     const ProcessArgs& args);

    /// @brief Destructor.
    ~ProcessSpawnImpl();

    /// @brief Returns full command line, including arguments, for the process.
    std::string getCommandLine() const;

    /// @brief Spawn the new process.
    ///
    /// This method forks the current process and executes the specified
    /// binary with arguments within the child process.
    ///
    /// The child process will return EXIT_FAILURE if the method was unable
    /// to start the executable, e.g. as a result of insufficient permissions
    /// or when the executable does not exist. If the process ends successfully
    /// the EXIT_SUCCESS is returned.
    ///
    /// @return PID of the spawned process.
    /// @throw ProcessSpawnError if forking a current process failed.
    pid_t spawn();

    /// @brief Checks if the process is still running.
    ///
    /// @param pid ID of the child processes for which state should be checked.
    /// @return true if the child process is running, false otherwise.
    bool isRunning(const pid_t pid) const;

    /// @brief Checks if any of the spawned processes is still running.
    ///
    /// @return true if at least one child process is still running.
    bool isAnyRunning() const;

    /// @brief Returns exit status of the process.
    ///
    /// If the process is still running, the previous status is returned
    /// or 0, if the process is being ran for the first time.
    ///
    /// @param pid ID of the child process for which exit status should be
    /// returned.
    /// @return Exit code of the process.
    int getExitStatus(const pid_t pid) const;

    /// @brief Removes the status of the process with a specified PID.
    ///
    /// This method removes the status of the process with a specified PID.
    /// If the process is still running, the status is not removed and the
    /// exception is thrown.
    ///
    /// @param pid A process pid.
    void clearState(const pid_t pid);

private:

    /// @brief Copies the argument specified as a C++ string to the new
    /// C string.
    ///
    /// This method is used to convert arguments specified as an STL container
    /// holding @c std::string objects to an array of C strings, used by the
    /// @c execvp function in the @c ProcessSpawnImpl::spawn. It allocates a
    /// new C string and copies the contents of the @c src to it.
    ///
    /// @param src A source string.
    ///
    /// @return Allocated C string holding the data from @c src.
    char* allocateArg(const std::string& src) const;

    /// @brief Signal handler for SIGCHLD.
    ///
    /// This handler waits for the child process to finish and retrieves
    /// its exit code into the @c status_ member.
    ///
    /// @return true if the processed signal was SIGCHLD or false if it
    /// was a different signal.
    bool waitForProcess(int signum);

    /// @brief A signal set installing a handler for SIGCHLD.
    SignalSetPtr signals_;

    /// @brief A map holding the status codes of executed processes.
    ProcessStates process_state_;

    /// @brief Path to an executable.
    std::string executable_;

    /// @brief An array holding arguments for the executable.
    char** args_;
};

ProcessSpawnImpl::ProcessSpawnImpl(const std::string& executable,
                                   const ProcessArgs& args)
    : signals_(new SignalSet(SIGCHLD)), process_state_(),
      executable_(executable), args_(new char*[args.size() + 2]) {
    // Set the handler which is invoked immediately when the signal
    // is received.
    signals_->setOnReceiptHandler(boost::bind(&ProcessSpawnImpl::waitForProcess,
                                              this, _1));
    // Conversion of the arguments to the C-style array we start by setting
    // all pointers within an array to NULL to indicate that they haven't
    // been allocated yet.
    memset(args_, 0, (args.size() + 2) * sizeof(char*));
    // By convention, the first argument points to an executable name.
    args_[0] = allocateArg(executable_);
    // Copy arguments to the array.
    for (int i = 1; i <= args.size(); ++i) {
        args_[i] = allocateArg(args[i-1]);
    }
}

ProcessSpawnImpl::~ProcessSpawnImpl() {
    int i = 0;
    // Deallocate strings in the array of arguments.
    while (args_[i] != NULL) {
        delete[] args_[i];
        ++i;
    }
    // Deallocate the array.
    delete[] args_;
}

std::string
ProcessSpawnImpl::getCommandLine() const {
    std::ostringstream s;
    s << executable_;
    // Start with index 1, because the first argument duplicates the
    // path to the executable. Note, that even if there are no parameters
    // the minimum size of the table is 2.
    int i = 1;
    while (args_[i] != NULL) {
        s << " " << args_[i];
        ++i;
    }
    return (s.str());
}

pid_t
ProcessSpawnImpl::spawn() {
    // Protect us against SIGCHLD signals
    sigset_t sset;
    sigemptyset(&sset);
    sigaddset(&sset, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sset, 0);
    // Create the child
    pid_t pid = fork();
    if (pid < 0) {
        isc_throw(ProcessSpawnError, "unable to fork current process");

    } else if (pid == 0) {
        // We're in the child process.
        sigprocmask(SIG_UNBLOCK, &sset, 0);
        // Run the executable.
        if (execvp(executable_.c_str(), args_) != 0) {
            // We may end up here if the execvp failed, e.g. as a result
            // of issue with permissions or invalid executable name.
            _exit(EXIT_FAILURE);
        }
        // Process finished, exit the child process.
        _exit(EXIT_SUCCESS);
    }

    // We're in the parent process.
    process_state_.insert(std::pair<pid_t, ProcessState>(pid, ProcessState()));
    sigprocmask(SIG_UNBLOCK, &sset, 0);
    return (pid);
}

bool
ProcessSpawnImpl::isRunning(const pid_t pid) const {
    ProcessStates::const_iterator proc = process_state_.find(pid);
    if (proc == process_state_.end()) {
        isc_throw(BadValue, "the process with the pid '" << pid
                  << "' hasn't been spawned and it status cannot be"
                  " returned");
    }
    return (proc->second.running_); 
}

bool
ProcessSpawnImpl::isAnyRunning() const {
    for (ProcessStates::const_iterator proc = process_state_.begin();
         proc != process_state_.end(); ++proc) {
        if (proc->second.running_) {
            return (true);
        }
    }
    return (false);
}

int
ProcessSpawnImpl::getExitStatus(const pid_t pid) const {
    ProcessStates::const_iterator proc = process_state_.find(pid);
    if (proc == process_state_.end()) {
        isc_throw(InvalidOperation, "the process with the pid '" << pid
                  << "' hasn't been spawned and it status cannot be"
                  " returned");
    }
    return (WEXITSTATUS(proc->second.status_));
}

char*
ProcessSpawnImpl::allocateArg(const std::string& src) const {
    const size_t src_len = src.length();
    // Allocate the C-string with one byte more for the null termination.
    char* dest = new char[src_len + 1];
    // copy doesn't append the null at the end.
    src.copy(dest, src_len);
    // Append null on our own.
    dest[src_len] = '\0';
    return (dest);
}

bool
ProcessSpawnImpl::waitForProcess(int signum) {
    // We're only interested in SIGCHLD.
    if (signum != SIGCHLD) {
        return (false);
    }

    // Need to store current value of errno, so we could restore it
    // after this signal handler does his work.
    int errno_value = errno;

    for (;;) {
        int status = 0;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        if (pid <= 0) {
            break;
        }
        ProcessStates::iterator proc = process_state_.find(pid);
        /// Check that the terminating process was started
        /// by our instance of ProcessSpawn
        if (proc != process_state_.end()) {
            // In this order please
            proc->second.status_ = status;
            proc->second.running_ = false;
        }
    }

    // Need to restore previous value of errno. We called waitpid(),
    // which likely indicated its result by setting errno to ECHILD.
    // This is a signal handler, which can be called while virtually
    // any other code being run. If we're unlucky, we could receive a
    // signal when running a code that is about to check errno. As a
    // result the code would detect errno=ECHILD in places which are
    // completely unrelated to child or processes in general.
    errno = errno_value;

    return (true);
}

void
ProcessSpawnImpl::clearState(const pid_t pid) {
    if (isRunning(pid)) {
        isc_throw(InvalidOperation, "unable to remove the status for the"
                  "process (pid: " << pid << ") which is still running");
    }
    process_state_.erase(pid);
}

ProcessSpawn::ProcessSpawn(const std::string& executable,
                           const ProcessArgs& args)
    : impl_(new ProcessSpawnImpl(executable, args)) {
}

ProcessSpawn::~ProcessSpawn() {
    delete impl_;
}

std::string
ProcessSpawn::getCommandLine() const {
    return (impl_->getCommandLine());
}

pid_t
ProcessSpawn::spawn() {
    return (impl_->spawn());
}

bool
ProcessSpawn::isRunning(const pid_t pid) const {
    return (impl_->isRunning(pid));
}

bool
ProcessSpawn::isAnyRunning() const {
    return (impl_->isAnyRunning());
}

int
ProcessSpawn::getExitStatus(const pid_t pid) const {
    return (impl_->getExitStatus(pid));
}

void
ProcessSpawn::clearState(const pid_t pid) {
    return (impl_->clearState(pid));
}

}
}
