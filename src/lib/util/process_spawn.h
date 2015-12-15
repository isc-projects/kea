// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PROCESS_SPAWN_H
#define PROCESS_SPAWN_H

#include <exceptions/exceptions.h>
#include <boost/noncopyable.hpp>
#include <string>
#include <sys/types.h>
#include <vector>

namespace isc {
namespace util {

/// @brief Exception thrown when error occurs during spawning a process.
class ProcessSpawnError : public Exception {
public:
    ProcessSpawnError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Forward declaration to the implementation of the @c ProcessSpawn
/// class.
class ProcessSpawnImpl;

/// @brief Type of the container holding arguments of the executable
/// being run as a background process.
typedef std::vector<std::string> ProcessArgs;

/// @brief Utility class for spawning new processes.
///
/// This class is used to spawn new process by Kea. It forks the current
/// process and then uses the @c execvp function to execute the specified
/// binary with parameters. The @c ProcessSpawn installs the handler for
/// the SIGCHLD signal, which is executed when the child process ends.
/// The handler checks the exit code returned by the process and records
/// it. The exit code can be retrieved by the caller using the
/// @c ProcessSpawn::getExitStatus method.
///
/// @warning Only one instance of the @c ProcessSpawn class may exist
/// at the given time. Creating additional instance would cause an
/// attempt to register a new SIGCHLD signal handler and, as a
/// consequence, the new @c ProcessSpawn object will fail to create.
///
/// This class is made noncopyable so that we don't have attempts
/// to make multiple copies of an object.  This avoid problems
/// with multiple copies of objects for a single global resource
/// such as the SIGCHLD signal handler. In addition making it
/// noncopyable keeps the static check code from flagging the
/// lack of a copy constructor as an issue.
///
/// @todo The SIGCHLD handling logic should be moved to the @c SignalSet
/// class so as multiple instances of the @c ProcessSpawn use the same
/// SIGCHLD signal handler.

class ProcessSpawn : boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// @param executable A path to the program to be executed.
    /// @param args Arguments for the program to be executed.
    ProcessSpawn(const std::string& executable,
                 const ProcessArgs& args = ProcessArgs());

    /// @brief Destructor.
    ~ProcessSpawn();

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
    /// @throw ProcessSpawnError if forking a current process failed.
    pid_t spawn();

    /// @brief Checks if the process is still running.
    ///
    /// Note that only a negative (false) result is reliable as the child
    /// process can exit between the time its state is checked and this
    /// function returns.
    ///
    /// @param pid ID of the child processes for which state should be checked.
    ///
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
    /// @note @c ProcessSpawn::isRunning should be called and have returned
    /// false before using @c ProcessSpawn::getExitStatus.
    ///
    /// @param pid ID of the child process for which exit status should be
    /// returned.
    ///
    /// @return Exit code of the process.
    int getExitStatus(const pid_t pid) const;

    /// @brief Removes the status of the process with a specified PID.
    ///
    /// This method removes the status of the process with a specified PID.
    /// If the process is still running, the status is not removed and the
    /// exception is thrown.
    ///
    /// Note @c ProcessSpawn::isRunning must be called and have returned
    /// false before using clearState(). And of course
    /// @c ProcessSpawn::getExitStatus should be called first, if there is
    /// some interest in the status.
    ///
    /// @param pid A process pid.
    void clearState(const pid_t pid);

private:

    /// @brief A pointer to the implementation of this class.
    ProcessSpawnImpl* impl_;

};

}
}

#endif // PROCESS_SPAWN_H
