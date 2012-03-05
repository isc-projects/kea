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

#ifndef __LABELSEQUENCE_H
#define __LABELSEQUENCE_H 1

#include <dns/name.h>
#include <util/buffer.h>

namespace isc {
namespace dns {

/// \brief Light-weight Accessor to Name object
///
/// The purpose of this class is to easily match Names and parts of Names,
/// without needing to copy the underlying data on each label strip.
///
/// It can only work on existing Name objects, and the Name object MUST
/// remain in scope during the entire lifetime of its associated
/// LabelSequence(s).
///
/// Upon creation of a LabelSequence, it records the offsets of the
/// labels in the wireformat data of the Name. When stripLeft() or
/// stripRight() is called on the LabelSequence, no changes in the
/// Name's data occur, but the internal pointers of the
/// LabelSequence are modified.
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
    LabelSequence(const Name& name): name_(name),
                                     first_label_(0),
                                     last_label_(name.getLabelCount())
    {}

    /// \brief Return the wire-format data for this LabelSequence
    ///
    /// The data, is returned as a pointer to the original wireformat
    /// data of the original Name object, and the given len value is
    /// set to the number of octets that match this labelsequence.
    ///
    /// \note The data pointed to is only valid if the original Name
    /// object is still in scope
    ///
    /// \param len Pointer to a size_t where the length of the data
    ///        will be stored (in number of octets)
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

    /// \brief Remove labels from the front of this LabelSequence
    ///
    /// \note No actual memory is changed, this operation merely updates the
    /// internal pointers based on the offsets in the Name object.
    ///
    /// \exeption OutOfRange if i is greater than or equal to the number
    ///           of labels currently pointed to by this LabelSequence
    ///
    /// \param i The number of labels to remove.
    void stripLeft(size_t i);

    /// \brief Remove labels from the end of this LabelSequence
    ///
    /// \note No actual memory is changed, this operation merely updates the
    /// internal pointers based on the offsets in the Name object.
    ///
    /// \exeption OutOfRange if i is greater than or equal to the number
    ///           of labels currently pointed to by this LabelSequence
    ///
    /// \param i The number of labels to remove.
    void stripRight(size_t i);

    /// \brief Returns the current number of labels for this LabelSequence
    ///
    /// \return The number of labels
    size_t getLabelCount() const { return (last_label_ - first_label_); }

    /// \brief Returns the original Name object associated with this
    ///        LabelSequence
    ///
    /// While the Name should still be in scope during the lifetime of
    /// the LabelSequence, it can still be useful to have access to it,
    /// for instance in helper functions that are only passed the
    /// LabelSequence itself.
    ///
    /// \return Reference to the original Name object
    const Name& getName() const { return (name_); }

    /// \brief Checks whether the label sequence is absolute
    ///
    /// \return true if the last label is the root label
    bool isAbsolute() const;

private:
    const Name& name_;
    size_t first_label_;
    size_t last_label_;
};


} // end namespace dns
} // end namespace isc

#endif
