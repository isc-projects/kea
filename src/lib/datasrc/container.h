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

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace isc {
namespace datasrc {

class ZoneFinder;
typedef boost::shared_ptr<ZoneFinder> ZoneFinderPtr;
class DataSourceClient;
typedef boost::shared_ptr<DataSourceClient> DataSourceClientPtr;

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
    /// \brief Constructur.
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
        SearchResult(const DataSourceClientPtr& datasrc,
                     const ZoneFinderPtr& finder,
                     uint8_t matched_labels, bool exact_match) :
            datasrc_(datasrc),
            finder_(finder),
            matched_labels_(matched_labels),
            exact_match(exact_match)
        { }
        /// \brief Negative answer constructor.
        ///
        /// This conscructs a result for negative answer. Both pointers are
        /// NULL, matched_labels_ is 0 and exact_match_ is false.
        SearchResult() :
            matched_labels_(0),
            exact_match_(false)
        { }
        /// \brief The found data source.
        ///
        /// The data source containing the best matching zone. If no such
        /// data source exists, this is NULL pointer.
        const DataSourceClientPtr datasrc_;
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
    /// \brief Search for a zone thourgh the data sources.
    ///
    /// This searches the contained data sources for a one that best matches
    /// the zone name.
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

class ConfigurableContainer : public Container {

};

} // namespace datasrc
} // namespace isc

#endif // DATASRC_CONTAINER_H
