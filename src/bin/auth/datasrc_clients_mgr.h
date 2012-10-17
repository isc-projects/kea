// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATASRC_CLIENTS_MGR_H
#define DATASRC_CLIENTS_MGR_H 1

#include <util/threads/thread.h>
#include <util/threads/lock.h>

#include <log/logger_support.h>
#include <log/log_dbglevels.h>

#include <cc/data.h>

#include <auth/auth_log.h>

#include <boost/bind.hpp>

#include <list>
#include <utility>

namespace isc {
namespace auth {

namespace datasrc_clientmgr_internal {
// This namespace is essentially private for DataSrcClientsMgr(Base) and
// DataSrcClientsBuilder(Base).  This is exposed in the public header
// only because these classes are templated (for testing purposes) and
// class internal has to be defined here.

/// \brief ID of commands from the DataSrcClientsMgr to DataSrcClientsBuilder.
enum CommandID {
    NOOP,         ///< Do nothing.  Only useful for tests; no argument
    SHUTDOWN      ///< Shutdown the builder; no argument
};

/// \brief The data type passed from DataSrcClientsMgr to
/// DataSrcClientsBuilder.
///
/// The first element of the pair is the command ID, and the second element
/// is its argument.  If the command doesn't take an argument it should be
/// a null pointer.
typedef std::pair<CommandID, data::ConstElementPtr> Command;
} // namespace datasrc_clientmgr_internal

/// \brief Frontend to the manager object for data source clients.
///
/// This class provides interfaces for configuring and updating a set of
/// data source clients "in the background".  The user of this class can
/// assume any operation on this class can be done effectively non-blocking,
/// not suspending any delay-sensitive operations such as DNS query
/// processing.  The only exception is the time when this class object
/// is destroyed (normally as a result of an implicit call to the destructor);
/// in the current implementation it can take time depending on what is
/// running "in the background" at the time of the call.
///
/// Internally, an object of this class invokes a separate thread to perform
/// time consuming operations such as loading large zone data into memory,
/// but such details are completely hidden from the user of this class.
///
/// This class is templated only so that we can test the class without
/// involving actual threads or mutex.  Normal applications will only
/// need one specific specialization that has a typedef of
/// \c DataSrcClientsMgr.
template <typename ThreadType, typename BuilderType, typename MutexType,
          typename CondVarType>
class DataSrcClientsMgrBase {
public:
    /// \brief Constructor.
    ///
    /// It internally invokes a separate thread and waits for further
    /// operations from the user application.
    ///
    /// This method is basically exception free except in case of really
    /// rare system-level errors.  When that happens the only reasonable
    /// action that the application can take would be to terminate the program
    /// in practice.
    ///
    /// \throw std::bad_alloc internal memory allocation failure.
    /// \throw isc::Unexpected general unexpected system errors.
    DataSrcClientsMgrBase() :
        builder_(&command_queue_, &cond_, &queue_mutex_),
        builder_thread_(boost::bind(&BuilderType::run, &builder_))
    {}

    /// \brief The destructor.
    ///
    /// It tells the internal thread to stop and waits for it completion.
    /// In the current implementation, it can block for some unpredictably
    /// long period depending on what the thread is doing at that time
    /// (in future we may want to implement a rapid way of killing the thread
    /// and/or provide a separate interface for waiting so that the application
    /// can choose the timing).
    ///
    /// The waiting operation can result in an exception, but this method
    /// catches any of them so this method itself is exception free.
    ~DataSrcClientsMgrBase() {
        // We share class member variables with the builder, which will be
        // invalidated after the call to the destructor, so we need to make
        // sure the builder thread is terminated.  Depending on the timing
        // this could time; if we don't want that to happen in this context,
        // we may want to introduce a separate 'shutdown()' method.
        // Also, since we don't want to propagate exceptions from a destructor,
        // we catch any possible ones.  In fact the only really expected one
        // is Thread::UncaughtException when the builder thread died due to
        // an exception.  We specifically log it and just ignore others.
        try {
            sendCommand(datasrc_clientmgr_internal::SHUTDOWN,
                        data::ConstElementPtr());
            builder_thread_.wait();
        } catch (const util::thread::Thread::UncaughtException& ex) {
            // technically, logging this could throw, which will be propagated.
            // But such an exception would be a fatal one anyway, so we
            // simply let it go through.
            LOG_ERROR(auth_logger, AUTH_DATASRC_CLIENTS_SHUTDOWN_ERROR).
                arg(ex.what());
        } catch (...) {}
    }

private:
    void sendCommand(datasrc_clientmgr_internal::CommandID command,
                     data::ConstElementPtr arg) {
        {
            typename MutexType::Locker locker(queue_mutex_);
            command_queue_.push_back(
                datasrc_clientmgr_internal::Command(command, arg));
        }
        cond_.signal();
    }

    //
    // The following are shared with the builder.
    //
    // The list is used as a one-way queue: back-in, front-out
    std::list<datasrc_clientmgr_internal::Command> command_queue_;
    CondVarType cond_;          // condition variable for queue operations
    MutexType queue_mutex_;     // mutex to protect the queue
#ifdef notyet                   // until #2210 or #2212
    boost::shared_ptr<DataSrcClientListMap> clients_map_;
    MutexType map_mutex_;
#endif

    BuilderType builder_;
    ThreadType builder_thread_; // for safety this should be placed last
};

namespace datasrc_clientmgr_internal {

/// \brief A class that maintains a set of data source clients.
///
/// An object of this class is supposed to run on a dedicated thread, whose
/// main function is a call to its \c run() method.  It runs in a loop
/// waiting for commands from the manager and handle each command (including
/// reloading a new version of zone data into memory or fully reconfiguration
/// of specific set of data source clients.  When it receives a SHUTDOWN
/// command, it exits from the loop, which will terminate the thread.
///
/// This class is a server of \c DataSrcClientsMgr.  Except for tests,
/// applications should not directly access to this class.
///
/// This class is templated so that we can test it without involving actual
/// threads or locks.
template <typename MutexType, typename CondVarType>
class DataSrcClientsBuilderBase {
public:
    /// \brief Constructor.
    ///
    /// It simply sets up a local copy of shared data with the manager.
    ///
    /// Note: this will take actual set (map) of data source clients and
    /// a mutex object for it in #2210 or #2212.
    ///
    /// \throw None
    DataSrcClientsBuilderBase(std::list<Command>* command_queue,
                              CondVarType* cond, MutexType* queue_mutex
#ifdef notyet
                              // In #2210 or #2212 we pass other data
#endif
        ) :
        command_queue_(command_queue), cond_(cond), queue_mutex_(queue_mutex)
    {}

    /// \brief The main loop.
    void run();

    /// \brief Handle one command from the manager.
    ///
    /// This is a dedicated subroutine of run() and is essentially private,
    /// but is defined as a separate public method so we can test each
    /// command test individually.  In any case, this class itself is
    /// generally considered private.
    ///
    /// \return true if the builder should keep running; false otherwise.
    bool handleCommand(const Command& command);

private:
    // NOOP command handler.  We use this so tests can override it; the default
    // implementation really does nothing.
    void doNoop() {}

    // The following are shared with the manager
    std::list<Command>* command_queue_;
    CondVarType* cond_;
    MutexType* queue_mutex_;
};

// Shortcut typedef for normal use
typedef DataSrcClientsBuilderBase<util::thread::Mutex, util::thread::CondVar>
DataSrcClientsBuilder;

template <typename MutexType, typename CondVarType>
void
DataSrcClientsBuilderBase<MutexType, CondVarType>::run() {
    LOG_INFO(auth_logger, AUTH_DATASRC_CLIENTS_BUILDER_STARTED);

    try {
        bool keep_running = true;
        while (keep_running) {
            std::list<Command> current_commands;
            {
                // Move all new commands to local queue under the protection of
                // queue_mutex_.  Note that list::splice() should never throw.
                typename MutexType::Locker locker(*queue_mutex_);
                while (command_queue_->empty()) {
                    cond_->wait(*queue_mutex_);
                }
                current_commands.splice(current_commands.end(),
                                        *command_queue_);
            } // the lock is release here.

            while (keep_running && !current_commands.empty()) {
                keep_running = handleCommand(current_commands.front());
                current_commands.pop_front();
            }
        }

        LOG_INFO(auth_logger, AUTH_DATASRC_CLIENTS_BUILDER_STOPPED);
    } catch (const std::exception& ex) {
        // We explicitly catch exceptions so we can log it as soon as possible.
        LOG_ERROR(auth_logger, AUTH_DATASRC_CLIENTS_BUILDER_FAILED).
            arg(ex.what());
        throw;
    } catch (...) {
        LOG_ERROR(auth_logger, AUTH_DATASRC_CLIENTS_BUILDER_FAILED_UNEXPECTED);
        throw;
    }
}

template <typename MutexType, typename CondVarType>
bool
DataSrcClientsBuilderBase<MutexType, CondVarType>::handleCommand(
    const Command& command)
{
    LOG_DEBUG(auth_logger, DBGLVL_TRACE_BASIC,
              AUTH_DATASRC_CLIENTS_BUILDER_COMMAND).arg(command.first);

    switch (command.first) {
    case SHUTDOWN:
        return (false);
    case NOOP:
        doNoop();
    }
    return (true);
}
} // namespace datasrc_clientmgr_internal

/// \brief Shortcut type for normal data source clients manager.
///
/// In fact, for non test applications this is the only type of this kind
/// to be considered.
typedef DataSrcClientsMgrBase<
    util::thread::Thread,
    datasrc_clientmgr_internal::DataSrcClientsBuilder,
    util::thread::Mutex, util::thread::CondVar> DataSrcClientsMgr;
} // namespace auth
} // namespace isc

#endif  // DATASRC_CLIENTS_MGR_H

// Local Variables:
// mode: c++
// End:
