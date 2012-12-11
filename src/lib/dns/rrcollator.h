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

#ifndef RRCOLLATOR_H
#define RRCOLLATOR_H 1

#include <dns/master_loader_callbacks.h>
#include <dns/rrset.h>

#include <boost/function.hpp>

namespace isc {
namespace dns {

/// \brief A converter from a stream of RRs to a stream of collated RRsets
///
/// This class is mainly intended to be a helper used as an adaptor for
/// user applications of the \c MasterLoader class; it works as a callback
/// for \c MasterLoader, buffers given RRs from the loader, collating
/// consecutive RRs that belong to the same RRset (ones having the same
/// owner name, RR type and class), and produces a stream of RRsets through
/// its own callback.  RRSIGs are also separated if their type covered fields
/// have different values even if the owner name and RR class are the same.
///
/// It also "normalizes" TTLs of the RR; if collated RRs have different TTLs,
/// this class guarantees that the TTL of the resulting RRsets has the
/// smallest TTL among them.
///
/// The conversion will be useful for applications of \c MasterLoader because
/// many of this library have interfaces that take an RRset object (or
/// a pointer to it).  Note, however, that this class doesn't guarantee that
/// all RRs that would belong to the same RRset are collated into the same
/// single RRset.  In fact, it can only collate RRs that are consecutive
/// in the original stream; once it encounters an RR of a different RRset,
/// any subsequent RRs of the previous RRset will form a separate RRset object.
class RRCollator {
public:
    /// \brief
    typedef boost::function<void(const RRsetPtr& rrset)> AddRRsetCallback;

    /// \brief Constructor.
    ///
    /// \throw std::bad_alloc Internal memory allocation fails.  This should
    /// be very rare.
    ///
    /// \param callback The callback functor to be called for each collated
    /// RRset.
    RRCollator(const AddRRsetCallback& callback);

    /// \brief Destructor.
    ///
    /// It only performs trivial internal cleanup.  In particular, even if
    /// it still has a buffered RRset it will be simply discarded.  This is
    /// because the given callback could throw an exception, and it's
    /// impossible to predict how this class is used (to see if it's a very
    /// rare case where propagating an exception from a destructor is
    /// justified).  Instead, the application needs to make sure that
    /// \c finish() is called before the object of this class is destroyed.
    ///
    /// \throw None
    ~RRCollator();

    /// \brief Call the callback on the remaining RRset, if any.
    ///
    /// This method is expected to be called that it's supposed all RRs have
    /// been passed to this class object.  Since there is no explicit
    /// indicator of the end of the stream, the user of this class needs to
    /// explicitly call this method to call the callback for the last buffered
    /// RRset (see also the destructor's description).
    ///
    /// If there is no buffered RRset, this method does nothing.  It can happen
    /// if it's called without receiving any RRs, or called more than once.
    ///
    /// It propagates any exception thrown from the callback; otherwise it
    /// doesn't throw anything.
    void finish();

    /// \brief Return \c MasterLoader compatible callback.
    ///
    /// This method returns a functor in the form of \c AddRRCallback
    /// that works as an adaptor between \c MasterLoader and an application
    /// that needs to get a stream of RRsets.  When the returned callback
    /// is called, this \c RRCollator object accepts the corresponding RR,
    /// and collates it with other RRs of the same RRset if necessary.
    /// Every time the \c RRCollator object encounters an RR of a different
    /// RRset, it calls the callback passed to the constructor with the RRset
    /// built so far.
    ///
    /// Like \c flush(), this \c AddRRCallback functor propagates any exception
    /// thrown from the callback.
    ///
    /// This method is expected to be called only once for a given
    /// \c RRCollator object.  It doesn't prohibit duplicate calls, but
    /// returned functor objects internally refer to the same \c RRCollator
    /// object, and calling the both callbacks randomly will just cause
    /// confusion.
    AddRRCallback getCallback();

private:
    class Impl;
    Impl* impl_;
};

} // namespace dns
} // namespace isc
#endif  // RRCOLLATOR_H

// Local Variables:
// mode: c++
// End:
