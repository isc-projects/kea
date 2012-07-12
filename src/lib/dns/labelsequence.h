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
    // Name calls the private toText(bool) method of LabelSequence.
    friend std::string Name::toText(bool) const;

public:
    /// \brief Constructs a LabelSequence for the given label sequence
    ///
    /// \note The associated data MUST remain in scope during the lifetime
    /// of this LabelSequence, since only the pointers are copied.
    ///
    /// \note No validation is done on the given data upon construction;
    ///       use with care.
    ///
    /// \param ls The LabelSequence to construct a LabelSequence from
    explicit LabelSequence(const LabelSequence& ls):
                                     data_(ls.data_),
                                     offsets_(ls.offsets_),
                                     offsets_size_(ls.offsets_size_),
                                     first_label_(ls.first_label_),
                                     last_label_(ls.last_label_)
    {}

    /// \brief Constructs a LabelSequence for the given name
    ///
    /// \note The associated Name MUST remain in scope during the lifetime
    /// of this LabelSequence, since getData() refers to data from the
    /// Name object (the only data the LabelSequence stores are pointers
    /// to the labels in the Name object).
    ///
    /// \param name The Name to construct a LabelSequence for
    explicit LabelSequence(const Name& name):
                                     data_(&name.ndata_[0]),
                                     offsets_(&name.offsets_[0]),
                                     offsets_size_(name.offsets_.size()),
                                     first_label_(0),
                                     last_label_(name.getLabelCount())
    {}

    /// \brief Constructs a LabelSequence for the given data
    ///
    /// \note The associated data MUST remain in scope during the lifetime
    /// of this LabelSequence, since only the pointers are copied.
    ///
    /// \note No validation is done on the given data upon construction;
    ///       use with care.
    ///
    /// \param data The Name data, in wire format
    /// \param offsets The offsets of the labels in the Name, as given
    ///        by the Name object or another LabelSequence
    /// \param offsets_size The size of the offsets data
    LabelSequence(const uint8_t* data,
                  const uint8_t* offsets,
                  size_t offsets_size) : data_(data),
                                         offsets_(offsets),
                                         offsets_size_(offsets_size),
                                         first_label_(0),
                                         last_label_(offsets_size_)
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
    const uint8_t* getData(size_t* len) const;

    /// \brief Return the offset data for this LabelSequence
    ///
    /// The offsets are returned in the <code>placeholder</code> array.
    ///
    /// \param len Pointer to a size_t where the number of offsets
    ///        will be stored
    /// \param placeholder Array where the offset data will be returned
    void getOffsetData(size_t* len,
                       uint8_t placeholder[Name::MAX_LABELS]) const;

    /// \brief Return the length of the wire-format data of this LabelSequence
    ///
    /// This method returns the number of octets for the data that would
    /// be returned by the \c getData() method.
    ///
    /// Note that the return value of this method is always positive.
    /// Note also that if the return value of this method is 1, it means the
    /// sequence consists of the null label, i.e., a single "dot", and vice
    /// versa.
    ///
    /// \note The data pointed to is only valid if the original Name
    /// object is still in scope
    ///
    /// \return The length of the data of the label sequence in octets.
    size_t getDataLength() const;

    /// \brief Compares two label sequences for equality.
    ///
    /// Performs a (optionally case-insensitive) comparison between this
    /// LabelSequence and another LabelSequence for equality.
    ///
    /// \param other The LabelSequence to compare with
    /// \param case_sensitive If true, comparison is case-insensitive
    /// \return true if The label sequences consist are the same length,
    ///         and contain the same data.
    bool equals(const LabelSequence& other, bool case_sensitive = false) const;

    /// \brief Compares two label sequences.
    ///
    /// Performs a (optionally case-insensitive) comparison between this
    /// LabelSequence and another LabelSequence.
    ///
    /// \param other The LabelSequence to compare with
    /// \param case_sensitive If true, comparison is case-insensitive
    /// \return a <code>NameComparisonResult</code> object representing the
    /// comparison result.
    NameComparisonResult compare(const LabelSequence& other,
                                 bool case_sensitive = false) const;

    /// \brief Remove labels from the front of this LabelSequence
    ///
    /// \note No actual memory is changed, this operation merely updates the
    /// internal pointers based on the offsets in the Name object.
    ///
    /// \exception OutOfRange if i is greater than or equal to the number
    ///           of labels currently pointed to by this LabelSequence
    ///
    /// \param i The number of labels to remove.
    void stripLeft(size_t i);

    /// \brief Remove labels from the end of this LabelSequence
    ///
    /// \note No actual memory is changed, this operation merely updates the
    /// internal pointers based on the offsets in the Name object.
    ///
    /// \exception OutOfRange if i is greater than or equal to the number
    ///           of labels currently pointed to by this LabelSequence
    ///
    /// \param i The number of labels to remove.
    void stripRight(size_t i);

    /// \brief Returns the current number of labels for this LabelSequence
    ///
    /// \return The number of labels
    size_t getLabelCount() const { return (last_label_ - first_label_); }

    /// \brief Convert the LabelSequence to a string.
    ///
    /// This method returns a <code>std::string</code> object representing the
    /// LabelSequence as a string.  The returned string ends with a dot
    /// '.' if the label sequence is absolute.
    ///
    /// This function assumes the underlying name is in proper
    /// uncompressed wire format.  If it finds an unexpected label
    /// character including compression pointer, an exception of class
    /// \c BadLabelType will be thrown.  In addition, if resource
    /// allocation for the result string fails, a corresponding standard
    /// exception will be thrown.
    //
    /// \return a string representation of the <code>LabelSequence</code>.
    std::string toText() const;

private:
    /// \brief Convert the LabelSequence to a string.
    ///
    /// This method is a version of the zero-argument toText() method,
    /// that accepts a <code>omit_final_dot</code> argument. The
    /// returned string ends with a dot '.' if
    /// <code>omit_final_dot</code> is <code>false</code>.
    ///
    /// This method is used as a helper for <code>Name::toText()</code>
    /// only.
    ///
    /// \param omit_final_dot whether to omit the trailing dot in the output.
    /// \return a string representation of the <code>LabelSequence</code>.
    std::string toText(bool omit_final_dot) const;

public:
    /// \brief Calculate a simple hash for the label sequence.
    ///
    /// This method calculates a hash value for the label sequence as binary
    /// data.  If \c case_sensitive is false, it ignores the case stored in
    /// the labels; specifically, it normalizes the labels by converting all
    /// upper case characters to lower case ones and calculates the hash value
    /// for the result.
    ///
    /// This method is intended to provide a lightweight way to store a
    /// relatively small number of label sequences in a hash table.
    /// For this reason it only takes into account data up to 16 octets
    /// (16 was derived from BIND 9's implementation).  Also, the function does
    /// not provide any unpredictability; a specific sequence will always have
    /// the same hash value.  It should therefore not be used in the context
    /// where an untrusted third party can mount a denial of service attack by
    /// forcing the application to create a very large number of label
    /// sequences that have the same hash value and expected to be stored in
    /// a hash table.
    ///
    /// \exception None
    ///
    /// \param case_sensitive
    /// \return A hash value for this label sequence.
    size_t getHash(bool case_sensitive) const;

    /// \brief Checks whether the label sequence is absolute
    ///
    /// \return true if the last label is the root label
    bool isAbsolute() const;

private:
    const uint8_t* data_;
    const uint8_t* offsets_;
    size_t offsets_size_;
    size_t first_label_;
    size_t last_label_;
};


///
/// \brief Insert the label sequence as a string into stream.
///
/// This method convert the \c label_sequence into a string and inserts
/// it into the output stream \c os.
///
/// This function overloads the global operator<< to behave as described in
/// ostream::operator<< but applied to \c LabelSequence objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param name The \c LabelSequence object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream&
operator<<(std::ostream& os, const LabelSequence& label_sequence);

} // end namespace dns
} // end namespace isc

#endif
