// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __LABELSEQUENCE_H
#define __LABELSEQUENCE_H 1

#include <dns/name.h>
#include <util/buffer.h>

namespace isc {
namespace dns {

/// \brief Light-weight Accessor to Name object
///
/// The purpose of this class is to easily match Names and parts of Names,
/// without needing to copy the underlying data on each split.
///
/// It can only work on existing Name objects, and the Name object MUST
/// remain in scope during the entire lifetime of its associated
/// LabelSequence(s).
///
/// Upon creation of a LabelSequence, it records the offsets of the
/// labels in the wireformat data of the Name. When split() is called on
/// the LabelSequence, no changes in the Name's data occur, but the
/// internal pointers of the LabelSequence are modified.
///
/// \note For consistency reasons, when talking about labels and label
/// counts, LabelSequence objects never include the root label in their
/// calculations or return values. Wireformat data resulting from
/// getData() is never absolute, and the result of a labelCount(),
/// even if split() has never been called on the LabelSequence, is
/// always smaller than the labelCount of the original Name object.
///
/// LabelSequences can be compared to other LabelSequences, and their
/// data can be requested (which then points to part of the original
/// data of the associated Name object).
///
class LabelSequence {
public:
    /// \brief Constructs a LabelSequence for the given name
    ///
    /// \note The associated Name MUST remain in scope during the lifetime
    /// of this LabelSequence, since getData() refers to data from the
    /// Name object (the only data the LabelSequence stores are pointers
    /// to the labels in the Name object).
    ///
    /// \param name The Name to construct a LabelSequence for
    LabelSequence(const Name& name);

    /// \brief Destructor
    ~LabelSequence();

    /// \brief Return the wire-format data for this LabelSequence
    ///
    /// The data, is returned as a pointer to the original wireformat
    /// data of the original Name object, and the given len value is
    /// set to the number of octets that match this labelsequence.
    ///
    /// \note The data pointed to here is never absolute (i.e. it does
    /// not include the root label), so if this data is used anywhere
    /// you probably need to add an empty label (one octet with value
    /// zero).
    ///
    /// \note The data pointed to is only valid if the original Name
    /// object is still in scope
    ///
    /// \param len Pointer to a size_t where the length of the data
    ///        is stored
    /// \return Pointer to the wire-format data of this label sequence
    const char* getData(size_t* len) const;

    /// \brief Compares two label sequences.
    ///
    /// Performs a (optionally case-insensitive) comparison between this
    /// LabelSequence and another LabelSequence.
    ///
    /// \param other The LabelSequence to compare with
    /// \param case_sensitive If true, comparison is case-insensitive
    /// \return true if The label sequences consist are the same length,
    ///         and contain the same data.
    bool equals(const LabelSequence& other, bool case_sensitive = false) const;

    /// \brief Remove one or more labels from this LabelSequence
    ///
    /// Removes labels from either the front or the back of the LabelSequence
    ///
    /// \note No actual memory is changed, this operation merely updates the
    /// internal pointers based on the offsets at creation time.
    ///
    /// \exeption OutOfRange if abs(i) is greater than the number of labels
    ///           currently pointed to by this LabelSequence
    ///
    /// \param i When positive, removes i labels from the front of the
    ///        LabelSequence. When negative, removes i labels from the
    ///        end of it.
    void split(int i);

    /// \brief Returns the current number of labels for this LabelSequence
    ///
    /// \note This count does NOT include the root label
    ///
    /// \return The number of labels
    size_t getLabelCount() const { return last_label_ - first_label_; }

    /// \brief Returns the original Name object associated with this
    ///        LabelSequence
    ///
    /// While the Name should still be in scope during the lifetime of
    /// the LabelSequence, it can still be useful to have access to it,
    /// for instance in helper functions that are only passed the
    /// LabelSequence itself.
    ///
    /// \return Reference to the original Name object
    const Name& getName() const { return name_; }

private:
    const Name& name_;
    size_t first_label_;
    size_t last_label_;
    size_t* offsets_;
};


} // end namespace dns
} // end namespace isc

#endif
