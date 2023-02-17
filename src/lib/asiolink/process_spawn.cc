// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service_signal.h>
#include <asiolink/process_spawn.h>
#include <exceptions/exceptions.h>
#include <cstring>
#include <functional>
#include <map>
#include <mutex>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <boost/make_shared.hpp>

using namespace std;
namespace ph = std::placeholders;

namespace isc {
namespace asiolink {

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

/// @brief Defines a pointer to a ProcessState.
typedef boost::shared_ptr<ProcessState> ProcessStatePtr;

/// @brief ProcessStates container which stores a ProcessState for each process
/// identified by PID.
typedef std::map<pid_t, ProcessStatePtr> ProcessStates;

class ProcessSpawnImpl;

/// @brief ProcessCollection container which stores all ProcessStates for each
/// instance of @ref ProcessSpawnImpl.
typedef std::map<const ProcessSpawnImpl*, ProcessStates> ProcessCollection;

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
    /// @param io_service The IOService which handles signal handlers.
    /// @param executable A full path to the program to be executed.
    /// @param args Arguments for the program to be executed.
    /// @param vars Environment variables for the program to be executed.
    ProcessSpawnImpl(IOServicePtr io_service,
                     const std::string& executable,
                     const ProcessArgs& args,
                     const ProcessEnvVars& vars);

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
    /// @param dismiss The flag which indicated if the process status can be
    /// disregarded.
    /// @return PID of the spawned process.
    /// @throw ProcessSpawnError if forking a current process failed.
    pid_t spawn(bool dismiss);

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

    /// @brief Initializer class for the SIGCHLD signal handler.
    ///
    /// This is a singleton class used to initialize the SIGCHLD signal handler
    /// only on the first call of @ref initIOSignalSet which happens on each
    /// call of @ref ProcessSpawn::spawn.
    class IOSignalSetInitializer {
    private:

        /// @brief Constructor
        ///
        /// @param io_service The IOService which handles signal handlers.
        IOSignalSetInitializer(IOServicePtr io_service) {
            if (!io_service) {
                isc_throw(ProcessSpawnError, "NULL IOService instance");
            }
            io_signal_set_ = boost::make_shared<IOSignalSet>(io_service,
                    std::bind(&ProcessSpawnImpl::waitForProcess, ph::_1));
            io_signal_set_->add(SIGCHLD);
        }

        /// @brief Destructor
        ~IOSignalSetInitializer() {
            io_signal_set_->remove(SIGCHLD);
        }

    public:

        /// @brief Initialize the SIGCHLD signal handler.
        ///
        /// It creates the single instance of @ref IOSignalSetInitializer.
        ///
        /// @param io_service The IOService which handles signal handlers.
        static void initIOSignalSet(IOServicePtr io_service);

    private:

        /// @brief ASIO signal set.
        IOSignalSetPtr io_signal_set_;
    };

    /// @brief Copies the argument specified as a C++ string to the new
    /// C string.
    ///
    /// This method is used to convert arguments specified as an STL container
    /// holding @c std::string objects to an array of C strings, used by the
    /// @c execve function in the @c ProcessSpawnImpl::spawn. It allocates a
    /// new C string and copies the contents of the @c src to it.
    /// The data is stored in an internal container so that the caller of the
    /// function can be exception safe.
    ///
    /// @param src A source string.
    ///
    /// @return Allocated C string holding the data from @c src.
    char* allocateInternal(const std::string& src);

    /// @brief Signal handler for SIGCHLD.
    ///
    /// This handler waits for the child process to finish and retrieves
    /// its exit code into the @c status_ member.
    ///
    /// @return true if the processed signal was SIGCHLD or false if it
    /// was a different signal.
    static bool waitForProcess(int signum);

    /// @brief A map holding the status codes of executed processes.
    static ProcessCollection process_collection_;

    /// @brief Path to an executable.
    std::string executable_;

    /// @brief An array holding arguments for the executable.
    boost::shared_ptr<char*[]> args_;

    /// @brief An array holding environment variables for the executable.
    boost::shared_ptr<char*[]> vars_;

    /// @brief Typedef for CString pointer.
    typedef boost::shared_ptr<char[]> CStringPtr;

    /// @brief An storage container for all allocated C strings.
    std::vector<CStringPtr> storage_;

    /// @brief Flag to indicate if process status must be stored.
    bool store_;

    /// @brief Mutex to protect internal state.
    static std::mutex mutex_;

    /// @brief The IOService which handles IO operations.
    IOServicePtr io_service_;
};

ProcessCollection ProcessSpawnImpl::process_collection_;
std::mutex ProcessSpawnImpl::mutex_;

void ProcessSpawnImpl::IOSignalSetInitializer::initIOSignalSet(IOServicePtr io_service) {
    static IOSignalSetInitializer init(io_service);
}

ProcessSpawnImpl::ProcessSpawnImpl(IOServicePtr io_service,
                                   const std::string& executable,
                                   const ProcessArgs& args,
                                   const ProcessEnvVars& vars)
    : executable_(executable), args_(new char*[args.size() + 2]),
      vars_(new char*[vars.size() + 1]), store_(false), io_service_(io_service) {

    struct stat st;

    if (stat(executable_.c_str(), &st)) {
        isc_throw(ProcessSpawnError, "File not found: " << executable_);
    }

    if (!(st.st_mode & S_IEXEC)) {
        isc_throw(ProcessSpawnError, "File not executable: " << executable_);
    }

    // Conversion of the arguments to the C-style array we start by setting
    // all pointers within an array to NULL to indicate that they haven't
    // been allocated yet.
    memset(args_.get(), 0, (args.size() + 2) * sizeof(char*));
    memset(vars_.get(), 0, (vars.size() + 1) * sizeof(char*));
    // By convention, the first argument points to an executable name.
    args_[0] = allocateInternal(executable_);
    // Copy arguments to the array.
    for (int i = 1; i <= args.size(); ++i) {
        args_[i] = allocateInternal(args[i - 1]);
    }
    // Copy environment variables to the array.
    for (int i = 0; i < vars.size(); ++i) {
        vars_[i] = allocateInternal(vars[i]);
    }
}

ProcessSpawnImpl::~ProcessSpawnImpl() {
    if (store_) {
        lock_guard<std::mutex> lk(mutex_);
        process_collection_.erase(this);
    }
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
ProcessSpawnImpl::spawn(bool dismiss) {
    lock_guard<std::mutex> lk(mutex_);
    ProcessSpawnImpl::IOSignalSetInitializer::initIOSignalSet(io_service_);
    // Create the child
    pid_t pid = fork();
    if (pid < 0) {
        isc_throw(ProcessSpawnError, "unable to fork current process");

    } else if (pid == 0) {
        // Reset masked signals for the child process.
        sigset_t sset;
        sigemptyset(&sset);
        pthread_sigmask(SIG_SETMASK, &sset, 0);
        // Run the executable.
        execve(executable_.c_str(), args_.get(), vars_.get());
        // We may end up here if the execve failed, e.g. as a result
        // of issue with permissions or invalid executable name.
        _exit(EXIT_FAILURE);
    }

    // We're in the parent process.
    if (!dismiss) {
        store_ = true;
        process_collection_[this].insert(std::pair<pid_t, ProcessStatePtr>(pid, ProcessStatePtr(new ProcessState())));
    }
    return (pid);
}

bool
ProcessSpawnImpl::isRunning(const pid_t pid) const {
    lock_guard<std::mutex> lk(mutex_);
    ProcessStates::const_iterator proc;
    if (process_collection_.find(this) == process_collection_.end() ||
        (proc = process_collection_[this].find(pid)) == process_collection_[this].end()) {
        isc_throw(BadValue, "the process with the pid '" << pid
                  << "' hasn't been spawned and it status cannot be"
                  " returned");
    }
    return (proc->second->running_);
}

bool
ProcessSpawnImpl::isAnyRunning() const {
    lock_guard<std::mutex> lk(mutex_);
    if (process_collection_.find(this) != process_collection_.end()) {
        for (auto const& proc : process_collection_[this]) {
            if (proc.second->running_) {
                return (true);
            }
        }
    }
    return (false);
}

int
ProcessSpawnImpl::getExitStatus(const pid_t pid) const {
    lock_guard<std::mutex> lk(mutex_);
    ProcessStates::const_iterator proc;
    if (process_collection_.find(this) == process_collection_.end() ||
        (proc = process_collection_[this].find(pid)) == process_collection_[this].end()) {
        isc_throw(InvalidOperation, "the process with the pid '" << pid
                  << "' hasn't been spawned and it status cannot be"
                  " returned");
    }
    return (WEXITSTATUS(proc->second->status_));
}

char*
ProcessSpawnImpl::allocateInternal(const std::string& src) {
    const size_t src_len = src.length();
    storage_.push_back(CStringPtr(new char[src_len + 1]));
    // Allocate the C-string with one byte more for the null termination.
    char* dest = storage_[storage_.size() - 1].get();
    // copy doesn't append the null at the end.
    src.copy(dest, src_len);
    // Append null on our own.
    dest[src_len] = '\0';
    return (dest);
}

bool
ProcessSpawnImpl::waitForProcess(int) {
    lock_guard<std::mutex> lk(mutex_);
    for (;;) {
        int status = 0;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        if (pid <= 0) {
            break;
        }
        for (auto const& instance : process_collection_) {
            auto const& proc = instance.second.find(pid);
            /// Check that the terminating process was started
            /// by our instance of ProcessSpawn
            if (proc != instance.second.end()) {
                // In this order please
                proc->second->status_ = status;
                proc->second->running_ = false;
            }
        }
    }
    return (true);
}

void
ProcessSpawnImpl::clearState(const pid_t pid) {
    if (isRunning(pid)) {
        isc_throw(InvalidOperation, "unable to remove the status for the "
                  "process (pid: " << pid << ") which is still running");
    }
    lock_guard<std::mutex> lk(mutex_);
    if (process_collection_.find(this) != process_collection_.end()) {
        process_collection_[this].erase(pid);
    }
}

ProcessSpawn::ProcessSpawn(IOServicePtr io_service,
                           const std::string& executable,
                           const ProcessArgs& args,
                           const ProcessEnvVars& vars)
    : impl_(new ProcessSpawnImpl(io_service, executable, args, vars)) {
}

std::string
ProcessSpawn::getCommandLine() const {
    return (impl_->getCommandLine());
}

pid_t
ProcessSpawn::spawn(bool dismiss) {
    return (impl_->spawn(dismiss));
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

} // namespace asiolink
} // namespace isc
