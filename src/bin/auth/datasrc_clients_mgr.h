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
#include <boost/scoped_ptr.hpp>

#include <list>
#include <utility>

namespace isc {
namespace auth {

namespace internal {
enum CommandID {
    NOOP,                       ///< Do nothing.  Only useful for tests
    SHUTDOWN                    ///< Shutdown the builder.
};
typedef std::pair<CommandID, data::ConstElementPtr> Command;

template <typename MutexType, typename CondVarType>
class DataSrcClientsBuilderBase {
public:
    DataSrcClientsBuilderBase(std::list<Command>* command_queue,
                              CondVarType* cond, MutexType* queue_mutex) :
        command_queue_(command_queue), cond_(cond), queue_mutex_(queue_mutex)
    {}

    /// Not sure if we need this.  It depends on test details.
    /// \brief Destructor.
    ///
    /// This does nothing, but explicitly defined to silence 'unused variable'
    /// warnings from some versions of clang++.
    ///~DataSrcClientsBuilderBase() {}

    void run();

    /// separated from run() and made public for the purpose of tests.
    ///
    /// \return true if it the builder should keep running; false otherwise.
    bool handleCommand(const Command& command);

private:
    // NOOP command handler.  We use this so tests can override it.
    void doNoop() {}

    // end-in, front-out queue
    std::list<Command>* command_queue_;
    CondVarType* cond_;
    MutexType* queue_mutex_;
    //boost::shared_ptr<DataSrcClientListMap>* map;
    //MutexType* data_mutex_;
};

// Shortcut typedef for normal use
typedef DataSrcClientsBuilderBase<util::thread::Mutex, util::thread::CondVar>
DataSrcClientsBuilder;
}

template <typename ThreadType, typename BuilderType, typename MutexType,
          typename CondVarType>
class DataSrcClientsMgrBase {
public:
    DataSrcClientsMgrBase() :
        builder_(&command_queue_, &cond_, &queue_mutex_),
        builder_thread_(new ThreadType(boost::bind(&BuilderType::run,
                                                   &builder_)))
    {}
    ~DataSrcClientsMgrBase() {
        if (builder_thread_) {
            // An unexpected case.  The manager is being destroyed without
            // a prior shutdown().  We notify the builder to minimize the risk
            // of leaving it as a zombie, but doesn't wait to avoid hangup.
            LOG_INFO(auth_logger, AUTH_DATASRC_CLIENTS_MANAGER_UNEXPECTED_STOP);
            sendCommand(internal::SHUTDOWN, data::ConstElementPtr());
        }
    }
    void shutdown() {
        sendCommand(internal::SHUTDOWN, data::ConstElementPtr());
        builder_thread_->wait();
        builder_thread_.reset();
    }

private:
    void sendCommand(internal::CommandID command, data::ConstElementPtr arg) {
        {
            typename MutexType::Locker locker(queue_mutex_);
            command_queue_.push_back(internal::Command(command, arg));
        }
        cond_.signal();
    }

    std::list<internal::Command> command_queue_;
    CondVarType cond_;
    MutexType queue_mutex_;
    BuilderType builder_;
    boost::scoped_ptr<ThreadType> builder_thread_;
};

namespace internal {
template <typename MutexType, typename CondVarType>
void
DataSrcClientsBuilderBase<MutexType, CondVarType>::run() {
    LOG_INFO(auth_logger, AUTH_DATASRC_CLIENTS_BUILDER_STARTED);

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
            current_commands.splice(current_commands.end(), *command_queue_);
        } // the lock is release here.

        while (keep_running && !current_commands.empty()) {
            keep_running = handleCommand(current_commands.front());
            current_commands.pop_front();
        }
    }

    LOG_INFO(auth_logger, AUTH_DATASRC_CLIENTS_BUILDER_STOPPED);
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
} // namespace internal

/// \brief Shortcut type for normal data source clients manager.
///
/// In fact, for non test applications this is the only type of this kind
/// to be considered.
typedef DataSrcClientsMgrBase<util::thread::Thread,
                              internal::DataSrcClientsBuilder,
                              util::thread::Mutex, util::thread::CondVar>
DataSrcClientsMgr;
} // namespace auth
} // namespace isc

#endif  // DATASRC_CLIENTS_MGR_H

// Local Variables:
// mode: c++
// End:
