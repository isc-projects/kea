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
#include <util/threads/sync.h>

#include <log/logger_support.h>
#include <log/log_dbglevels.h>

#include <dns/rrclass.h>

#include <cc/data.h>

#include <datasrc/data_source.h>
#include <datasrc/client_list.h>
#include <datasrc/memory/zone_writer.h>

#include <auth/auth_log.h>
#include <auth/datasrc_config.h>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <exception>
#include <cassert>
#include <list>
#include <utility>

namespace isc {
namespace auth {

/// \brief An exception that is thrown if initial checks for a command fail
///
/// This is raised *before* the command to the thread is constructed and
/// sent, so the application can still handle them (and therefore it is
/// public, as opposed to InternalCommandError).
///
/// And example of its use is currently in loadZone().
class CommandError : public isc::Exception {
public:
    CommandError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

namespace datasrc_clientmgr_internal {
// This namespace is essentially private for DataSrcClientsMgr(Base) and
// DataSrcClientsBuilder(Base).  This is exposed in the public header
// only because these classes are templated (for testing purposes) and
// class internal has to be defined here.

/// \brief ID of commands from the DataSrcClientsMgr to DataSrcClientsBuilder.
enum CommandID {
    NOOP,         ///< Do nothing.  Only useful for tests; no argument
    RECONFIGURE,  ///< Reconfigure the datasource client lists,
                  ///  the argument to the command is the full new
                  ///  datasources configuration.
    LOADZONE,     ///< Load a new version of zone into a memory,
                  ///  the argument to the command is a map containing 'class'
                  ///  and 'origin' elements, both should have been validated.
    SHUTDOWN,     ///< Shutdown the builder; no argument
    NUM_COMMANDS
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
class DataSrcClientsMgrBase : boost::noncopyable {
private:
    typedef std::map<dns::RRClass,
                     boost::shared_ptr<datasrc::ConfigurableClientList> >
    ClientListsMap;

public:
    /// \brief Thread-safe accessor to the data source client lists.
    ///
    /// This class provides a simple wrapper for searching the client lists
    /// stored in the DataSrcClientsMgr in a thread-safe manner.
    /// It ensures the result of \c getClientList() can be used without
    /// causing a race condition with other threads that can possibly use
    /// the same manager throughout the lifetime of the holder object.
    ///
    /// This also means the holder object is expected to have a short lifetime.
    /// The application shouldn't try to keep it unnecessarily long.
    /// It's normally expected to create the holder object on the stack
    /// of a small scope and automatically let it be destroyed at the end
    /// of the scope.
    class Holder {
    public:
        Holder(DataSrcClientsMgrBase& mgr) :
            mgr_(mgr), locker_(mgr_.map_mutex_)
        {}

        /// \brief Find a data source client list of a specified RR class.
        ///
        /// It returns a pointer to the list stored in the manager if found,
        /// otherwise it returns NULL.  The manager keeps the ownership of
        /// the pointed object.  Also, it's not safe to get access to the
        /// object beyond the scope of the holder object.
        ///
        /// \note Since the ownership isn't transferred the return value
        /// could be a bare pointer (and it's probably better in several
        /// points).  Unfortunately, some unit tests currently don't work
        /// unless this method effectively shares the ownership with the
        /// tests.  That's the only reason why we return a shared pointer
        /// for now.  We should eventually fix it and change the return value
        /// type (see Trac ticket #2395).  Other applications must not
        /// assume the ownership is actually shared.
        boost::shared_ptr<datasrc::ConfigurableClientList> findClientList(
            const dns::RRClass& rrclass)
        {
            const ClientListsMap::const_iterator
                it = mgr_.clients_map_->find(rrclass);
            if (it == mgr_.clients_map_->end()) {
                return (boost::shared_ptr<datasrc::ConfigurableClientList>());
            } else {
                return (it->second);
            }
        }
    private:
        DataSrcClientsMgrBase& mgr_;
        typename MutexType::Locker locker_;
    };

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
        clients_map_(new ClientListsMap),
        builder_(&command_queue_, &cond_, &queue_mutex_, &clients_map_,
                 &map_mutex_),
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
        // this could take a long time; if we don't want that to happen in
        // this context, we may want to introduce a separate 'shutdown()'
        // method.
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
        } catch (...) {
            LOG_ERROR(auth_logger,
                      AUTH_DATASRC_CLIENTS_SHUTDOWN_UNEXPECTED_ERROR);
        }

        cleanup();              // see below
    }

    /// \brief Handle new full configuration for data source clients.
    ///
    /// This method simply passes the new configuration to the builder
    /// and immediately returns.  This method is basically exception free
    /// as long as the caller passes a non NULL value for \c config_arg;
    /// it doesn't validate the argument further.
    ///
    /// \brief isc::InvalidParameter config_arg is NULL.
    /// \brief std::bad_alloc
    ///
    /// \param config_arg The new data source configuration.  Must not be NULL.
    void reconfigure(data::ConstElementPtr config_arg) {
        if (!config_arg) {
            isc_throw(InvalidParameter, "Invalid null config argument");
        }
        sendCommand(datasrc_clientmgr_internal::RECONFIGURE, config_arg);
        reconfigureHook();      // for test's customization
    }

    /// \brief Set the underlying data source client lists to new lists.
    ///
    /// This is provided only for some existing tests until we support a
    /// cleaner way to use faked data source clients.  Non test code or
    /// newer tests must not use this.
    void setDataSrcClientLists(datasrc::ClientListMapPtr new_lists) {
        typename MutexType::Locker locker(map_mutex_);
        clients_map_ = new_lists;
    }

    /// \brief Instruct internal thread to (re)load a zone
    ///
    /// \param args Element argument that should be a map of the form
    /// { "class": "IN", "origin": "example.com" }
    /// (but class is optional and will default to IN)
    ///
    /// \exception CommandError if the args value is null, or not in
    ///                                 the expected format, or contains
    ///                                 a bad origin or class string
    void
    loadZone(data::ConstElementPtr args) {
        if (!args) {
            isc_throw(CommandError, "loadZone argument empty");
        }
        if (args->getType() != isc::data::Element::map) {
            isc_throw(CommandError, "loadZone argument not a map");
        }
        if (!args->contains("origin")) {
            isc_throw(CommandError,
                      "loadZone argument has no 'origin' value");
        }
        // Also check if it really is a valid name
        try {
            dns::Name(args->get("origin")->stringValue());
        } catch (const isc::Exception& exc) {
            isc_throw(CommandError, "bad origin: " << exc.what());
        }

        if (args->get("origin")->getType() != data::Element::string) {
            isc_throw(CommandError,
                      "loadZone argument 'origin' value not a string");
        }
        if (args->contains("class")) {
            if (args->get("class")->getType() != data::Element::string) {
                isc_throw(CommandError,
                          "loadZone argument 'class' value not a string");
            }
            // Also check if it is a valid class
            try {
                dns::RRClass(args->get("class")->stringValue());
            } catch (const isc::Exception& exc) {
                isc_throw(CommandError, "bad class: " << exc.what());
            }
        }

        // Note: we could do some more advanced checks here,
        // e.g. check if the zone is known at all in the configuration.
        // For now these are skipped, but one obvious way to
        // implement it would be to factor out the code from
        // the start of doLoadZone(), and call it here too

        sendCommand(datasrc_clientmgr_internal::LOADZONE, args);
    }

private:
    // This is expected to be called at the end of the destructor.  It
    // actually does nothing, but provides a customization point for
    // specialized class for tests so that the tests can inspect the last
    // state of the class.
    void cleanup() {}

    // same as cleanup(), for reconfigure().
    void reconfigureHook() {}

    void sendCommand(datasrc_clientmgr_internal::CommandID command,
                     data::ConstElementPtr arg)
    {
        // The lock will be held until the end of this method.  Only
        // push_back has to be protected, but we can avoid having an extra
        // block this way.
        typename MutexType::Locker locker(queue_mutex_);
        command_queue_.push_back(
            datasrc_clientmgr_internal::Command(command, arg));
        cond_.signal();
    }

    //
    // The following are shared with the builder.
    //
    // The list is used as a one-way queue: back-in, front-out
    std::list<datasrc_clientmgr_internal::Command> command_queue_;
    CondVarType cond_;          // condition variable for queue operations
    MutexType queue_mutex_;     // mutex to protect the queue
    datasrc::ClientListMapPtr clients_map_;
                                // map of actual data source client objects
    MutexType map_mutex_;       // mutex to protect the clients map

    BuilderType builder_;
    ThreadType builder_thread_; // for safety this should be placed last
};

namespace datasrc_clientmgr_internal {

/// \brief A class that maintains a set of data source clients.
///
/// An object of this class is supposed to run on a dedicated thread, whose
/// main function is a call to its \c run() method.  It runs in a loop
/// waiting for commands from the manager and handles each command (including
/// reloading a new version of zone data into memory or fully reconfiguration
/// of specific set of data source clients).  When it receives a SHUTDOWN
/// command, it exits from the loop, which will terminate the thread.
///
/// While this class is defined in a publicly visible namespace, it's
/// essentially private to \c DataSrcClientsMgr.  Except for tests,
/// applications should not directly access this class.
///
/// This class is templated so that we can test it without involving actual
/// threads or locks.
template <typename MutexType, typename CondVarType>
class DataSrcClientsBuilderBase : boost::noncopyable {
private:
    typedef std::map<dns::RRClass,
                     boost::shared_ptr<datasrc::ConfigurableClientList> >
    ClientListsMap;

public:
    /// \brief Internal errors in handling commands.
    ///
    /// This exception is expected to be caught within the
    /// \c DataSrcClientsBuilder implementation, but is defined as public
    /// so tests can be checked it.
    class InternalCommandError : public isc::Exception {
    public:
        InternalCommandError(const char* file, size_t line, const char* what) :
            isc::Exception(file, line, what) {}
    };

    /// \brief Constructor.
    ///
    /// It simply sets up a local copy of shared data with the manager.
    ///
    /// \throw None
    DataSrcClientsBuilderBase(std::list<Command>* command_queue,
                              CondVarType* cond, MutexType* queue_mutex,
                              datasrc::ClientListMapPtr* clients_map,
                              MutexType* map_mutex
        ) :
        command_queue_(command_queue), cond_(cond), queue_mutex_(queue_mutex),
        clients_map_(clients_map), map_mutex_(map_mutex)
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

    void doReconfigure(const data::ConstElementPtr& config) {
        if (config) {
            LOG_INFO(auth_logger,
                     AUTH_DATASRC_CLIENTS_BUILDER_RECONFIGURE_STARTED);
            try {
                // Define new_clients_map outside of the block that
                // has the lock scope; this way, after the swap,
                // the lock is guaranteed to be released before
                // the old data is destroyed, minimizing the lock
                // duration.
                datasrc::ClientListMapPtr new_clients_map =
                    configureDataSource(config);
                {
                    typename MutexType::Locker locker(*map_mutex_);
                    new_clients_map.swap(*clients_map_);
                } // lock is released by leaving scope
                LOG_INFO(auth_logger,
                         AUTH_DATASRC_CLIENTS_BUILDER_RECONFIGURE_SUCCESS);
            } catch (const datasrc::ConfigurableClientList::ConfigurationError&
                     config_error) {
                LOG_ERROR(auth_logger,
                    AUTH_DATASRC_CLIENTS_BUILDER_RECONFIGURE_CONFIG_ERROR).
                    arg(config_error.what());
            } catch (const datasrc::DataSourceError& ds_error) {
                LOG_ERROR(auth_logger,
                    AUTH_DATASRC_CLIENTS_BUILDER_RECONFIGURE_DATASRC_ERROR).
                    arg(ds_error.what());
            } catch (const isc::Exception& isc_error) {
                LOG_ERROR(auth_logger,
                    AUTH_DATASRC_CLIENTS_BUILDER_RECONFIGURE_ERROR).
                    arg(isc_error.what());
            }
            // other exceptions are propagated, see
            // http://bind10.isc.org/ticket/2210#comment:13

            // old clients_map_ data is released by leaving scope
        }
    }

    void doLoadZone(const isc::data::ConstElementPtr& arg);
    boost::shared_ptr<datasrc::memory::ZoneWriter> getZoneWriter(
        datasrc::ConfigurableClientList& client_list,
        const dns::RRClass& rrclass, const dns::Name& origin);

    // The following are shared with the manager
    std::list<Command>* command_queue_;
    CondVarType* cond_;
    MutexType* queue_mutex_;
    datasrc::ClientListMapPtr* clients_map_;
    MutexType* map_mutex_;
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
                // queue_mutex_.
                typename MutexType::Locker locker(*queue_mutex_);
                while (command_queue_->empty()) {
                    cond_->wait(*queue_mutex_);
                }
                current_commands.swap(*command_queue_);
            } // the lock is released here.

            while (keep_running && !current_commands.empty()) {
                try {
                    keep_running = handleCommand(current_commands.front());;
                } catch (const InternalCommandError& e) {
                    LOG_ERROR(auth_logger,
                              AUTH_DATASRC_CLIENTS_BUILDER_COMMAND_ERROR).
                        arg(e.what());
                }
                current_commands.pop_front();
            }
        }

        LOG_INFO(auth_logger, AUTH_DATASRC_CLIENTS_BUILDER_STOPPED);
    } catch (const std::exception& ex) {
        // We explicitly catch exceptions so we can log it as soon as possible.
        LOG_FATAL(auth_logger, AUTH_DATASRC_CLIENTS_BUILDER_FAILED).
            arg(ex.what());
        std::terminate();
    } catch (...) {
        LOG_FATAL(auth_logger, AUTH_DATASRC_CLIENTS_BUILDER_FAILED_UNEXPECTED);
        std::terminate();
    }
}

template <typename MutexType, typename CondVarType>
bool
DataSrcClientsBuilderBase<MutexType, CondVarType>::handleCommand(
    const Command& command)
{
    const CommandID cid = command.first;
    if (cid >= NUM_COMMANDS) {
        // This shouldn't happen except for a bug within this file.
        isc_throw(Unexpected, "internal bug: invalid command, ID: " << cid);
    }

    const boost::array<const char*, NUM_COMMANDS> command_desc = {
        {"NOOP", "RECONFIGURE", "LOADZONE", "SHUTDOWN"}
    };
    LOG_DEBUG(auth_logger, DBGLVL_TRACE_BASIC,
              AUTH_DATASRC_CLIENTS_BUILDER_COMMAND).arg(command_desc.at(cid));
    switch (command.first) {
    case RECONFIGURE:
        doReconfigure(command.second);
        break;
    case LOADZONE:
        doLoadZone(command.second);
        break;
    case SHUTDOWN:
        return (false);
    case NOOP:
        doNoop();
        break;
    case NUM_COMMANDS:
        assert(false);          // we rejected this case above
    }
    return (true);
}

template <typename MutexType, typename CondVarType>
void
DataSrcClientsBuilderBase<MutexType, CondVarType>::doLoadZone(
    const isc::data::ConstElementPtr& arg)
{
    // We assume some basic level validation as this method can only be
    // called via the manager in practice.  manager is expected to do the
    // minimal validation.
    assert(arg);
    assert(arg->get("origin"));

    // TODO: currently, we hardcode IN as the default for the optional
    // 'class' argument. We should really derive this from the specification,
    // but at the moment the config/command API does not allow that to be
    // done easily. Once that is in place (tickets have yet to be created,
    // as we need to do a tiny bit of design work for that), this
    // code can be replaced with the original part:
    // assert(arg->get("class"));
    // const dns::RRClass(arg->get("class")->stringValue());
    isc::data::ConstElementPtr class_elem = arg->get("class");
    const dns::RRClass rrclass(class_elem ?
                                dns::RRClass(class_elem->stringValue()) :
                                dns::RRClass::IN());
    const dns::Name origin(arg->get("origin")->stringValue());
    ClientListsMap::iterator found = (*clients_map_)->find(rrclass);
    if (found == (*clients_map_)->end()) {
        isc_throw(InternalCommandError, "failed to load a zone " << origin <<
                  "/" << rrclass << ": not configured for the class");
    }

    boost::shared_ptr<datasrc::ConfigurableClientList> client_list =
        found->second;
    assert(client_list);

    try {
        boost::shared_ptr<datasrc::memory::ZoneWriter> zwriter =
            getZoneWriter(*client_list, rrclass, origin);

        zwriter->load(); // this can take time but doesn't cause a race
        {   // install() can cause a race and must be in a critical section
            typename MutexType::Locker locker(*map_mutex_);
            zwriter->install();
        }
        LOG_DEBUG(auth_logger, DBG_AUTH_OPS,
                  AUTH_DATASRC_CLIENTS_BUILDER_LOAD_ZONE)
            .arg(origin).arg(rrclass);

        // same as load(). We could let the destructor do it, but do it
        // ourselves explicitly just in case.
        zwriter->cleanup();
    } catch (const InternalCommandError& ex) {
        throw;     // this comes from getZoneWriter.  just let it go through.
    } catch (const isc::Exception& ex) {
        // We catch our internal exceptions (which will be just ignored) and
        // propagated others (which should generally be considered fatal and
        // will make the thread terminate)
        isc_throw(InternalCommandError, "failed to load a zone " << origin <<
                  "/" << rrclass << ": error occurred in reload: " <<
                  ex.what());
    }
}

// A dedicated subroutine of doLoadZone().  Separated just for keeping the
// main method concise.
template <typename MutexType, typename CondVarType>
boost::shared_ptr<datasrc::memory::ZoneWriter>
DataSrcClientsBuilderBase<MutexType, CondVarType>::getZoneWriter(
    datasrc::ConfigurableClientList& client_list,
    const dns::RRClass& rrclass, const dns::Name& origin)
{
    // getCachedZoneWriter() could get access to an underlying data source
    // that can cause a race condition with the main thread using that data
    // source for lookup.  So we need to protect the access here.
    datasrc::ConfigurableClientList::ZoneWriterPair writerpair;
    {
        typename MutexType::Locker locker(*map_mutex_);
        writerpair = client_list.getCachedZoneWriter(origin);
    }

    switch (writerpair.first) {
    case datasrc::ConfigurableClientList::ZONE_SUCCESS:
        assert(writerpair.second);
        return (writerpair.second);
    case datasrc::ConfigurableClientList::ZONE_NOT_FOUND:
        isc_throw(InternalCommandError, "failed to load zone " << origin
                  << "/" << rrclass << ": not found in any configured "
                  "data source.");
    case datasrc::ConfigurableClientList::ZONE_NOT_CACHED:
        isc_throw(InternalCommandError, "failed to load zone " << origin
                  << "/" << rrclass << ": not served from memory");
    case datasrc::ConfigurableClientList::CACHE_DISABLED:
        // This is an internal error. Auth server must have the cache
        // enabled.
        isc_throw(InternalCommandError, "failed to load zone " << origin
                  << "/" << rrclass << ": internal failure, in-memory cache "
                  "is somehow disabled");
    }

    // all cases above should either return or throw, but some compilers
    // still need a return statement
    return (boost::shared_ptr<datasrc::memory::ZoneWriter>());
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
