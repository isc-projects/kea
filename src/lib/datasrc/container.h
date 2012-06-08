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

#ifndef DATASRC_CONTAINER_H
#define DATASRC_CONTAINER_H

#include <dns/name.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>

#include <vector>
#include <boost/shared_ptr.hpp>
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

/// \brief The container of data sources.
///
/// The purpose of this class is to hold several data sources and search
/// through them to find one containing a zone best matching a request.
///
/// This is an abstract base class. It is not expected we would use multiple
/// implementation inside the servers (but it is not forbidden either), we
/// have it to allow easy testing. It is possible to create a mock-up class
/// instead of creating a full-blown configuration. The real implementation
/// is the ConfigurableContainer.
class Container : public boost::noncopyable {
protected:
    /// \brief Constructor.
    ///
    /// It is protected to prevent accidental creation of the abstract base
    /// class.
    Container() {}
public:
    /// \brief Structure holding the (compound) result of search.
    ///
    /// As this is read-only structure, we don't bother to create accessors.
    /// Instead, all the member variables are defined as const and can be
    /// accessed directly.
    struct SearchResult {
        /// \brief Constructor.
        ///
        /// It simply fills in the member variables according to the
        /// parameters. See the member descriptions for their meaning.
        SearchResult(DataSourceClient* datasrc,
                     const ZoneFinderPtr& finder,
                     uint8_t matched_labels, bool exact_match) :
            datasrc_(datasrc),
            finder_(finder),
            matched_labels_(matched_labels),
            exact_match_(exact_match)
        { }

        /// \brief Negative answer constructor.
        ///
        /// This conscructs a result for negative answer. Both pointers are
        /// NULL, matched_labels_ is 0 and exact_match_ is false.
        SearchResult() :
            datasrc_(NULL),
            matched_labels_(0),
            exact_match_(false)
        { }

        /// \brief Comparison operator.
        ///
        /// It is needed for tests and it might be of some use elsewhere
        /// too.
        bool operator ==(const SearchResult& other) const {
            return (datasrc_ == other.datasrc_ &&
                    finder_ == other.finder_ &&
                    matched_labels_ == other.matched_labels_ &&
                    exact_match_ == other.exact_match_);
        }

        /// \brief The found data source.
        ///
        /// The data source containing the best matching zone. If no such
        /// data source exists, this is NULL pointer.
        DataSourceClient* const datasrc_;

        /// \brief The finder for the requested zone.
        ///
        /// This is the finder corresponding to the best matching zone.
        /// This may be NULL even in case the datasrc_ is something
        /// else, depending on the search options.
        ///
        /// \see search
        const ZoneFinderPtr finder_;

        /// \brief Number of matching labels.
        ///
        /// The number of labels the result have in common with the queried
        /// name of zone.
        const uint8_t matched_labels_;

        /// \brief If the result is an exact match.
        const bool exact_match_;
    };

    /// \brief Search for a zone through the data sources.
    ///
    /// This searches the contained data sources for a one that best matches
    /// the zone name.
    ///
    /// There are two expected usage scenarios. One is answering queries. In
    /// this case, the zone finder is needed and the best matching superzone
    /// of the searched name is needed. Therefore, the call would look like:
    ///
    ///   SearchResult result(container->search(queried_name));
    ///   if (result.datasrc_) {
    ///       createTheAnswer(result.finder_);
    ///   } else {
    ///       createNotAuthAnswer();
    ///   }
    ///
    /// The other scenario is manipulating zone data (XfrOut, XfrIn, DDNS,
    /// ...). In this case, the finder itself is not so important. However,
    /// we need an exact match (if we want to manipulate zone data, we must
    /// know exactly, which zone we are about to manipulate). Then the call
    ///
    ///   SearchResult result(container->search(zone_name, true, false));
    ///   if (result.datasrc_) {
    ///       ZoneUpdaterPtr updater(result.datasrc_->getUpdater(zone_name);
    ///       ...
    ///   }
    ///
    /// \param zone The name of the zone to search.
    /// \param want_exact_match If it is true, it returns only exact matches.
    ///     If the best possible match is partial, a negative result is
    ///     returned instead. It is possible the caller could check it and
    ///     act accordingly if the result would be partial match, but with this
    ///     set to true, the search might be actually faster under some
    ///     circumstances.
    /// \param want_finder If this is false, the finder_ member of SearchResult
    ///     might be NULL even if the corresponding data source is found. This
    ///     is because of performance, in some cases the finder is a side
    ///     result of the searching algorithm (therefore asking for it again
    ///     would be a waste), but under other circumstances it is not, so
    ///     providing it when it is not needed would also be wasteful.
    ///
    ///     Other things are never the side effect of searching, therefore the
    ///     caller can get them explicitly (the updater, journal reader and
    ///     iterator).
    /// \return A SearchResult describing the data source and zone with the
    ///     longest match against the zone parameter.
    virtual SearchResult search(const dns::Name& zone,
                                bool want_exact_match = false,
                                bool want_finder = true) const = 0;
};

/// \brief Shared pointer to the container.
typedef boost::shared_ptr<Container> ContainerPtr;
/// \brief Shared const pointer to the container.
typedef boost::shared_ptr<const Container> ConstContainerPtr;

/// \Concrete implementation of the Container, which is constructed based on
///     configuration.
///
/// This is the implementation which is expected to be used in the servers.
/// However, it is expected most of the code will use it as the Container,
/// only the creation is expected to be direct.
class ConfigurableContainer : public Container {
public:
    /// \brief Exception thrown when there's an error in configuration.
    class ConfigurationError : public Exception {
    public:
        ConfigurationError(const char* file, size_t line, const char* what) :
            Exception(file, line, what)
        { }
    };

    /// \brief Sets the configuration.
    ///
    /// This fills the Container with data sources corresponding to the
    /// configuration. The data sources are newly created or recycled from
    /// previous configuration.
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
    /// \throw DataSourceError if there's a problem creating a data source.
    /// \throw ConfigurationError if the configuration is invalid in some
    ///     sense.
    void configure(const data::ConstElementPtr& configuration,
                   bool allow_cache);

    /// \brief Implementation of the Container::search.
    virtual SearchResult search(const dns::Name& zone,
                                bool want_exact_match = false,
                                bool want_finder = true) const;

    /// \brief This holds one data source and corresponding information.
    ///
    /// \todo The content yet to be defined.
    struct DataSourceInfo {
        DataSourceClient* data_src_;
        DataSourceClientContainerPtr container_;
    };

    /// \brief The collection of data sources.
    typedef std::vector<DataSourceInfo> DataSources;
protected:
    /// \brief The data sources held here.
    ///
    /// All our data sources are stored here. It is protected to let the
    /// tests in.
    DataSources data_sources_;

    /// \brief Convenience type alias.
    ///
    /// \see getDataSource
    typedef std::pair<DataSourceClient*, DataSourceClientContainerPtr>
        DataSourcePair;

    /// \brief Create a data source of given type and configuration.
    ///
    /// This is a thin wrapper around the DataSourceClientContainer
    /// constructor. The function is here to make it possible for tests
    /// to replace the DataSourceClientContainer with something else.
    /// Also, derived classes might want to create the data sources
    /// in a different way.
    ///
    /// The parameters are the same as of the constructor.
    /// \return Pair containing both the data source and the container.
    ///     The container might be NULL in the derived class, it is
    ///     only stored so the data source is properly destroyed when
    ///     not needed. However, in such case, it is the caller's
    ///     responsibility to ensure the data source is deleted when
    ///     needed.
    virtual DataSourcePair getDataSource(const std::string& type,
                                         const data::ConstElementPtr&
                                         configuration);
public:
    /// \brief Access to the data sources.
    ///
    /// It can be used to examine the loaded list of data sources directly.
    /// It is not known if it is of any use other than testing, but it might
    /// be, so it is just made public.
    const DataSources& dataSources() const { return (data_sources_); }
};

} // namespace datasrc
} // namespace isc

#endif // DATASRC_CONTAINER_H
