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

#ifndef PROCESS_SPAWN_H
#define PROCESS_SPAWN_H

#include <exceptions/exceptions.h>
#include <string>
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
/// @warning It is not recommended to use multiple instances of the
/// @c ProcessSpawn classes at the same time, because each newly
/// created instance would replace the SIGCHLD handler. This means that
/// it would not be possible to gather the exit code of all but one
/// (newly created) process, because the SIGCHLD handler is responsible
/// for checking the exit code of the process.
class ProcessSpawn {
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

    /// @brief A pointer to the implementation of this class.
    ProcessSpawnImpl* impl_;

};

}
}

#endif // PROCESS_SPAWN_H
