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
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

namespace isc {
namespace util {

/// @brief Implementation of the @c ProcessSpawn class.
///
/// This pimpl idiom is used by the @c ProcessSpawn in this case to
/// avoid exposing the internals of the implementation, such as
/// custom handling of a SIGCHLD signal, and the conversion of the
/// arguments of the executable from the STL container to the array.
class ProcessSpawnImpl {
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
    /// This method forks the current process and execues the specified
    /// binary with arguments within the child process.
    ///
    /// The child process will return EXIT_FAILURE if the method was unable
    /// to start the exuctable, e.g. as a result of insufficient permissions
    /// or when the executable does not exist. If the process ends successfully
    /// the EXIT_SUCCESS is returned.
    ///
    /// @throw ProcessSpawnError if forking a current process failed.
    void spawn();

    /// @brief Checks if the process is still running.
    ///
    /// @return true if the child process is running, false otherwise.
    bool isRunning() const;

    /// @brief Returns exit status of the process.
    ///
    /// If the process is still running, the previous status is returned
    /// or 0, if the process is being ran for the first time.
    ///
    /// @return Exit code of the process.
    int getExitStatus() const;

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

    /// @brief PID of the child process.
    pid_t pid_;

    /// @brief Last returned status code by the child process.
    int status_;

    /// @brief Path to an executable.
    std::string executable_;

    /// @brief An array holding arguments for the executable.
    char** args_;
};

ProcessSpawnImpl::ProcessSpawnImpl(const std::string& executable,
                                   const ProcessArgs& args)
    : signals_(new SignalSet(SIGCHLD)), pid_(0), status_(0),
      executable_(executable), args_(new char*[args.size() + 2]) {
    // Set the handler which is invoked immediatelly when the signal
    // is received.
    signals_->setOnReceiptHandler(boost::bind(&ProcessSpawnImpl::waitForProcess,
                                              this, _1));
    // Convertion of the arguments to the C-style array we start by setting
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

void
ProcessSpawnImpl::spawn() {
    pid_ = fork();
    if (pid_ < 0) {
        isc_throw(ProcessSpawnError, "unable to fork current process");

    } else if (pid_ == 0) {
        // We're in the child process. Run the executable.
        if (execvp(executable_.c_str(), args_) != 0) {
            // We may end up here if the execvp failed, e.g. as a result
            // of issue with permissions or invalid executable name.
            exit(EXIT_FAILURE);
        }
        // Process finished, exit the child process.
        exit(EXIT_SUCCESS);
    }
}

bool
ProcessSpawnImpl::isRunning() const {
    return ((pid_ != 0) && (kill(pid_, 0) == 0));
}

int
ProcessSpawnImpl::getExitStatus() const {
    return (WEXITSTATUS(status_));
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
    if (signum == SIGCHLD) {
        status_ = 0;
        while (wait4(pid_, &status_, WNOHANG, NULL) > 0) {
            // continue
        }
        pid_ = 0;
        return (true);
    }
    return (false);
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

void
ProcessSpawn::spawn() {
    impl_->spawn();
}

bool
ProcessSpawn::isRunning() const {
    return (impl_->isRunning());
}

int
ProcessSpawn::getExitStatus() const {
    return (impl_->getExitStatus());
}

}
}
