// Copyright (C) 2012-2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATASRC_CONTAINER_H
#define DATASRC_CONTAINER_H

#include <util/memory_segment.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/zone_table_accessor.h>

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace isc {
namespace datasrc {

class ZoneFinder;
typedef boost::shared_ptr<ZoneFinder> ZoneFinderPtr;
class DataSourceClient;
typedef boost::shared_ptr<DataSourceClient> DataSourceClientPtr;
class DataSourceClientContainer;
typedef boost::shared_ptr<DataSourceClientContainer>
    DataSourceClientContainerPtr;
// XXX: it's better to even hide the existence of the "memory" namespace.
// We should probably consider pimpl for details of ConfigurableClientList
// and hide real definitions except for itself and tests.
namespace memory {
class InMemoryClient;
class ZoneWriter;
}

namespace internal {
class CacheConfig;
}

/// \brief Segment status of the cache
///
/// Describes the status in which the memory segment for the in-memory cache of
// /given data source is.
enum MemorySegmentState {
    /// \brief No segment used for this data source.
    ///
    /// This is usually a result of the cache being disabled.
    SEGMENT_UNUSED,

    /// \brief It is a mapped segment and we wait for information how to map
    ///     it.
    SEGMENT_WAITING,

    /// \brief The segment is ready to be used.
    SEGMENT_INUSE
};

/// \brief Status of one data source.
///
/// This indicates the status a data soure is in. It is used with segment
/// and cache management, to discover the data sources that need external
/// mapping or local loading.
///
/// In future, it may be extended for other purposes, such as performing an
/// operation on named data source.
class DataSourceStatus {
public:
    /// \brief Constructor
    ///
    /// Sets initial values. If you want to use \c SEGMENT_UNUSED as the
    /// state, please use the other constructor.
    DataSourceStatus(const std::string& name, MemorySegmentState state,
                     const std::string& type) :
        name_(name),
        type_(type),
        state_(state)
    {
        assert (state != SEGMENT_UNUSED);
        assert (!type.empty());
    }

    /// \brief Constructor
    ///
    /// Sets initial values. The state is set as \c SEGMENT_UNUSED and
    /// the type is effectively unspecified.
    DataSourceStatus(const std::string& name) :
        name_(name),
        type_(""),
        state_(SEGMENT_UNUSED)
    {}

    /// \brief Get the segment state
    MemorySegmentState getSegmentState() const {
        return (state_);
    }

    /// \brief Get the segment type
    ///
    /// \note Specific values of the type are only meaningful for the
    ///     corresponding memory segment implementation and modules that
    ///     directly manage the segments. Other normal applications should
    ///     treat them as opaque identifiers.
    ///
    /// \throw isc::InvalidOperation if called and state is SEGMENT_UNUSED.
    const std::string& getSegmentType() const {
        if (getSegmentState() == SEGMENT_UNUSED) {
            isc_throw(isc::InvalidOperation,
                      "No segment used, no type therefore.");
        }
        return (type_);
    }

    /// \brief Get the name.
    const std::string& getName() const {
        return (name_);
    }
private:
    std::string name_;
    std::string type_;
    MemorySegmentState state_;
};

/// \brief The list of data source clients.
///
/// The purpose of this class is to hold several data source clients and search
/// through them to find one containing a zone best matching a request.
///
/// All the data source clients should be for the same class. If you need
/// to handle multiple classes, you need to create multiple separate lists.
///
/// This is an abstract base class. It is not expected we would use multiple
/// implementation inside the servers (but it is not forbidden either), we
/// have it to allow easy testing. It is possible to create a mock-up class
/// instead of creating a full-blown configuration. The real implementation
/// is the ConfigurableClientList.
class ClientList : public boost::noncopyable {
protected:
    /// \brief Constructor.
    ///
    /// It is protected to prevent accidental creation of the abstract base
    /// class.
    ClientList() {}
public:
    /// \brief Virtual destructor
    virtual ~ClientList() {}
    /// \brief Structure holding the (compound) result of find.
    ///
    /// As this is read-only structure, we don't bother to create accessors.
    /// Instead, all the member variables are defined as const and can be
    /// accessed directly.
    struct FindResult {
        /// \brief Internal class for holding a reference.
        ///
        /// This is used to make sure the data source client isn't released
        /// too soon.
        ///
        /// \see life_keeper_;
        class LifeKeeper {
        public:
            virtual ~LifeKeeper() {};
        };
        /// \brief Constructor.
        ///
        /// It simply fills in the member variables according to the
        /// parameters. See the member descriptions for their meaning.
        FindResult(DataSourceClient* dsrc_client, const ZoneFinderPtr& finder,
                   bool exact_match,
                   const boost::shared_ptr<LifeKeeper>& life_keeper) :
            dsrc_client_(dsrc_client),
            finder_(finder),
            exact_match_(exact_match),
            life_keeper_(life_keeper)
        {}

        /// \brief Negative answer constructor.
        ///
        /// This constructs a result for negative answer. Both pointers are
        /// NULL, and exact_match_ is false.
        FindResult() :
            dsrc_client_(NULL),
            exact_match_(false)
        {}

        /// \brief Comparison operator.
        ///
        /// It is needed for tests and it might be of some use elsewhere
        /// too.
        bool operator ==(const FindResult& other) const {
        return (dsrc_client_ == other.dsrc_client_ &&
                finder_ == other.finder_ &&
                exact_match_ == other.exact_match_);
        }

        /// \brief The found data source client.
        ///
        /// The client of the data source containing the best matching zone.
        /// If no such data source exists, this is NULL pointer.
        ///
        /// Note that the pointer is valid only as long the ClientList which
        /// returned the pointer is alive and was not reconfigured or you hold
        /// a reference to life_keeper_. The ownership is preserved within the
        /// ClientList.
        DataSourceClient* const dsrc_client_;

        /// \brief The finder for the requested zone.
        ///
        /// This is the finder corresponding to the best matching zone.
        /// This may be NULL even in case the datasrc_ is something
        /// else, depending on the find options.
        ///
        /// \see find
        const ZoneFinderPtr finder_;

        /// \brief If the result is an exact match.
        const bool exact_match_;

        /// \brief Something that holds the dsrc_client_ valid.
        ///
        /// As long as you hold the life_keeper_, the dsrc_client_ is
        /// guaranteed to be valid.
        const boost::shared_ptr<LifeKeeper> life_keeper_;
    };

    /// \brief Search for a zone through the data sources.
    ///
    /// This searches the contained data source clients for a one that best
    /// matches the zone name.
    ///
    /// There are two expected usage scenarios. One is answering queries. In
    /// this case, the zone finder is needed and the best matching superzone
    /// of the searched name is needed. Therefore, the call would look like:
    ///
    /// \code FindResult result(list->find(queried_name));
    ///   if (result.dsrc_client_) {
    ///       if (result.finder_) {
    ///           createTheAnswer(result.finder_);
    ///       } else { // broken zone, return SERVFAIL
    ///           createErrorMessage(Rcode.SERVFAIL());
    ///       }
    ///   } else {
    ///       createNotAuthAnswer();
    /// } \endcode
    ///
    /// Note that it is possible that \c finder_ is NULL while \c datasrc_
    /// is not.  This happens if the zone is configured to be served from
    /// the data source but it is broken in some sense and doesn't hold any
    /// zone data, e.g., when the zone file has an error or the secondary
    /// zone hasn't been transferred yet.  The caller needs to expect the case
    /// and handle it accordingly.
    ///
    /// The other scenario is manipulating zone data (XfrOut, XfrIn, DDNS,
    /// ...). In this case, the finder itself is not so important. However,
    /// we need an exact match (if we want to manipulate zone data, we must
    /// know exactly, which zone we are about to manipulate). Then the call
    ///
    /// \code FindResult result(list->find(zone_name, true, false));
    ///   if (result.datasrc_) {
    ///       ZoneUpdaterPtr updater(result.datasrc_->getUpdater(zone_name);
    ///       ...
    /// } \endcode
    ///
    /// \param zone The name of the zone to look for.
    /// \param want_exact_match If it is true, it returns only exact matches.
    ///     If the best possible match is partial, a negative result is
    ///     returned instead. It is possible the caller could check it and
    ///     act accordingly if the result would be partial match, but with this
    ///     set to true, the find might be actually faster under some
    ///     circumstances.
    /// \param want_finder If this is false, the finder_ member of FindResult
    ///     might be NULL even if the corresponding data source is found. This
    ///     is because of performance, in some cases the finder is a side
    ///     result of the searching algorithm (therefore asking for it again
    ///     would be a waste), but under other circumstances it is not, so
    ///     providing it when it is not needed would also be wasteful.
    ///
    ///     Other things are never the side effect of searching, therefore the
    ///     caller can get them explicitly (the updater, journal reader and
    ///     iterator).
    /// \return A FindResult describing the data source and zone with the
    ///     longest match against the zone parameter.
    virtual FindResult find(const dns::Name& zone,
                            bool want_exact_match = false,
                            bool want_finder = true) const = 0;

    /// \brief Creates a ZoneTableAccessor object for the specified data
    /// source.
    ///
    /// \param datasrc_name If not empty, the name of the data source.
    /// \param use_cache If true, create a zone table for in-memory cache.
    /// \throw NotImplemented if this method is not implemented.
    /// \return A pointer to the accessor, or NULL if the requested data
    /// source is not found.
    virtual ConstZoneTableAccessorPtr
    getZoneTableAccessor(const std::string& datasrc_name,
                         bool use_cache) const = 0;

};

/// \brief Shared pointer to the list.
typedef boost::shared_ptr<ClientList> ClientListPtr;
/// \brief Shared const pointer to the list.
typedef boost::shared_ptr<const ClientList> ConstClientListPtr;

/// \brief Concrete implementation of the ClientList, which is constructed
/// based on configuration.
///
/// This is the implementation which is expected to be used in the servers.
/// However, it is expected most of the code will use it as the ClientList,
/// only the creation is expected to be direct.
///
/// While it is possible to inherit this class, it is not expected to be
/// inherited except for tests.
class ConfigurableClientList : public ClientList {
public:
    /// \brief Constructor
    ///
    /// \param rrclass For which class the list should work.
    ConfigurableClientList(const isc::dns::RRClass& rrclass);

    /// \brief Exception thrown when there's an error in configuration.
    class ConfigurationError : public Exception {
    public:
        ConfigurationError(const char* file, size_t line, const char* what) :
            Exception(file, line, what)
        {}
    };

    /// \brief Sets the configuration.
    ///
    /// This fills the ClientList with data source clients corresponding to the
    /// configuration. The data source clients are newly created or recycled
    /// from previous configuration.
    ///
    /// If any error is detected, an exception is thrown and the current
    /// configuration is preserved.
    ///
    /// \param configuration The JSON element describing the configuration to
    ///     use.
    /// \param allow_cache If it is true, the 'cache' option of the
    ///     configuration is used and some zones are cached into an In-Memory
    ///     data source according to it. If it is false, it is ignored and
    ///     no In-Memory data sources are created.
    /// \throw DataSourceError if there's a problem creating a data source
    ///     client.
    /// \throw ConfigurationError if the configuration is invalid in some
    ///     sense.
    /// \throw BadValue if configuration is NULL
    /// \throw Unexpected if something misbehaves (like the data source
    ///     returning NULL iterator).
    /// \throw NotImplemented if the auto-detection of list of zones is
    ///     needed.
    /// \throw Whatever is propagated from within the data source.
    void configure(const isc::data::ConstElementPtr& configuration,
                   bool allow_cache);

    /// \brief Returns the currently active configuration.
    ///
    /// In case configure was not called yet, it returns an empty
    /// list, which corresponds to the default content.
    const isc::data::ConstElementPtr& getConfiguration() const {
        return (configuration_);
    }

    /// \brief Resets the zone table segment for a datasource with a new
    /// memory segment.
    ///
    /// See documentation of \c ZoneTableSegment interface
    /// implementations (such as \c ZoneTableSegmentMapped) for the
    /// syntax of \c config_params.
    ///
    /// \param datasrc_name The name of the data source whose segment to reset
    /// \param mode The open mode for the new memory segment
    /// \param config_params The configuration for the new memory segment.
    void resetMemorySegment
        (const std::string& datasrc_name,
         memory::ZoneTableSegment::MemorySegmentOpenMode mode,
         isc::data::ConstElementPtr config_params);

    /// \brief Convenience type shortcut
    typedef boost::shared_ptr<memory::ZoneWriter> ZoneWriterPtr;

    /// \brief Codes indicating in-memory cache status for a given zone name.
    ///
    /// This is used as a result of the getCachedZoneWriter() method.
    enum CacheStatus {
        CACHE_DISABLED,     ///< The cache is not enabled in this list.
        ZONE_NOT_CACHED,    ///< Zone is not to be cached (including the case
                            ///  where caching is disabled for the specific
                            ///  data source).
        ZONE_NOT_FOUND,     ///< Zone does not exist in this list.
        CACHE_NOT_WRITABLE, ///< The cache is not writable (and zones can't
                            ///  be loaded)
        DATASRC_NOT_FOUND,  ///< Specific data source for load is specified
                            ///  but it's not in the list
        ZONE_SUCCESS        ///< Zone to be cached is successfully found and
                            ///  is ready to be loaded
    };

    /// \brief Return value of getCachedZoneWriter()
    ///
    /// A pair containing status and the zone writer, for the
    /// getCachedZoneWriter() method.
    typedef std::pair<CacheStatus, ZoneWriterPtr> ZoneWriterPair;

    /// \brief Return a zone writer that can be used to (re)load a zone.
    ///
    /// By default this method identifies the first data source in the list
    /// that should serve the zone of the given name, and returns a ZoneWriter
    /// object that can be used to load the content of the zone, in a specific
    /// way for that data source.
    ///
    /// If the optional \c datasrc_name parameter is provided with a non empty
    /// string, this method only tries to load the specified zone into or with
    /// the data source which has the given name, regardless where in the list
    /// that data source is placed.  Even if the given name of zone doesn't
    /// exist in the data source, other data sources are not searched and
    /// this method simply returns ZONE_NOT_FOUND in the first element
    /// of the pair.
    ///
    /// \param zone The origin of the zone to load.
    /// \param catch_load_errors Whether to make the zone writer catch
    /// load errors (see \c ZoneWriter constructor documentation).
    /// \param datasrc_name If not empty, the name of the data source
    /// to be used for loading the zone (see above).
    /// \return The result has two parts. The first one is a status indicating
    ///     if it worked or not (and in case it didn't, also why). If the
    ///     status is ZONE_SUCCESS, the second part contains a shared pointer
    ///     to the writer. If the status is anything else, the second part is
    ///     NULL.
    /// \throw DataSourceError or anything else that the data source
    ///      containing the zone might throw is propagated.
    ZoneWriterPair getCachedZoneWriter(const dns::Name& zone,
                                       bool catch_load_error,
                                       const std::string& datasrc_name = "");

    /// \brief Implementation of the ClientList::find.
    virtual FindResult find(const dns::Name& zone,
                            bool want_exact_match = false,
                            bool want_finder = true) const;

    /// \brief This holds one data source client and corresponding information.
    struct DataSourceInfo {
        DataSourceInfo(DataSourceClient* data_src_client,
                       const DataSourceClientContainerPtr& container,
                       boost::shared_ptr<internal::CacheConfig> cache_conf,
                       const dns::RRClass& rrclass,
                       const std::string& name);
        DataSourceClient* data_src_client_;
        DataSourceClientContainerPtr container_;

        // Accessor to cache_ in the form of DataSourceClient, hiding
        // the existence of InMemoryClient as much as possible.  We should
        // really consider cleaner abstraction, but for now it works.
        // This is also only intended to be used in auth unit tests right now.
        // No other applications or tests may use it.
        const DataSourceClient* getCacheClient() const;
        boost::shared_ptr<memory::InMemoryClient> cache_;
        boost::shared_ptr<memory::ZoneTableSegment> ztable_segment_;
        std::string name_;

        // cache_conf_ can be accessed only from this read-only getter,
        // to protect its integrity as much as possible.
        const internal::CacheConfig* getCacheConfig() const {
            return (cache_conf_.get());
        }
    private:
        boost::shared_ptr<internal::CacheConfig> cache_conf_;
    };

    /// \brief The collection of data sources.
    typedef std::vector<DataSourceInfo> DataSources;

    /// \brief Convenience type alias.
    ///
    /// \see getDataSource
    typedef std::pair<DataSourceClient*, DataSourceClientContainerPtr>
        DataSourcePair;

    /// \brief Create a data source client of given type and configuration.
    ///
    /// This is a thin wrapper around the DataSourceClientContainer
    /// constructor. The function is here to make it possible for tests
    /// to replace the DataSourceClientContainer with something else.
    /// Also, derived classes could want to create the data source clients
    /// in a different way, though inheriting this class is not recommended.
    ///
    /// Some types of data sources can be internal to the \c ClientList
    /// implementation and do not require a corresponding dynamic module
    /// loaded via \c DataSourceClientContainer.  In such a case, this method
    /// simply returns a pair of null pointers.  It will help the caller reduce
    /// type dependent processing.  Currently, "MasterFiles" is considered to
    /// be this type of data sources.
    ///
    /// The parameters are the same as of the constructor.
    /// \return Pair containing both the data source client and the container.
    ///     The container might be NULL in the derived class, it is
    ///     only stored so the data source client is properly destroyed when
    ///     not needed. However, in such case, it is the caller's
    ///     responsibility to ensure the data source client is deleted when
    ///     needed.
    virtual DataSourcePair getDataSourceClient(const std::string& type,
                                               const data::ConstElementPtr&
                                               configuration);

    /// \brief Get status information of all internal data sources.
    ///
    /// Get a DataSourceStatus for current state of each data source client
    /// in this list.
    ///
    /// This may throw standard exceptions, such as std::bad_alloc. Otherwise,
    /// it is exception free.
    std::vector<DataSourceStatus> getStatus() const;
public:
    /// \brief Access to the data source clients.
    ///
    /// It can be used to examine the loaded list of data sources clients
    /// directly. It is not known if it is of any use other than testing, but
    /// it might be, so it is just made public (there's no real reason to
    /// hide it).
    const DataSources& getDataSources() const { return (data_sources_); }

    /// \brief Creates a ZoneTableAccessor object for the specified data
    /// source.
    ///
    /// \param datasrc_name If not empty, the name of the data source
    /// \param use_cache If true, create a zone table for in-memory cache.
    /// \note At present, the only concrete implementation of
    /// ZoneTableAccessor is ZoneTableAccessorCache, so \c use_cache must be
    /// true.
    /// \throw NotImplemented if \c use_cache is false.
    /// \return A pointer to the accessor, or NULL if the requested data
    /// source is not found.
    ConstZoneTableAccessorPtr
    getZoneTableAccessor(const std::string& datasrc_name,
                         bool use_cache) const;

private:
    struct MutableResult;
    /// \brief Internal implementation of find.
    ///
    /// The class itself needs to do some internal searches in other methods,
    /// so the implementation is shared.
    ///
    /// The result is returned as parameter because MutableResult is not
    /// defined in the header file.
    ///
    /// If there's no match, the result is not modified. Therefore, this
    /// expects to get a fresh result object each time it is called, not
    /// to reuse it.
    void findInternal(MutableResult& result, const dns::Name& name,
                      bool want_exact_match, bool want_finder) const;
    const isc::dns::RRClass rrclass_;

    /// \brief Currently active configuration.
    isc::data::ConstElementPtr configuration_;

    /// \brief The last set value of allow_cache.
    bool allow_cache_;

protected:
    /// \brief The data sources held here.
    ///
    /// All our data sources are stored here. It is protected to let the
    /// tests in. You should consider it private if you ever want to
    /// derive this class (which is not really recommended anyway).
    DataSources data_sources_;
};

/// \brief Shortcut typedef for maps of client_lists.
typedef boost::shared_ptr<std::map<
    isc::dns::RRClass, boost::shared_ptr<ConfigurableClientList> > >
        ClientListMapPtr;

} // namespace datasrc
} // namespace isc

#endif // DATASRC_CONTAINER_H
