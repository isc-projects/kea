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

#ifndef DATASRC_MEMORY_RDATA_READER_H
#define DATASRC_MEMORY_RDATA_READER_H 1

#include "rdata_field.h"

#include <boost/function.hpp>

#include <dns/labelsequence.h>
#include <dns/name.h>

namespace isc {
// Some forward declarations
namespace dns{
class RRClass;
class RRType;
}

namespace datasrc {
namespace memory {

/// \brief Class to read serialized rdata
///
/// This class allows you to read the data encoded by RdataEncoder.
/// It is rather low-level -- it provides sequence of data fields.
/// Each field is either opaque data, passed as a pointer and length,
/// or a name, in the form of dns::LabelSequence (which is always
/// absolute) and attributes.
///
/// Conceptually, these fields correspond to consecutive regions in
/// wire-format representation of the RDATA, varying the type of above
/// two cases depending on whether the region corresponds to a domain
/// name or other data.  For example, for an MX RDATA the field
/// sequence will be
/// - 2 bytes of opaque data (which corresponds to the MX preference)
/// - a domain name (which corresponds to the MX name)
/// If the encoded data contain multiple MX RDATAs, the same type of
/// sequence continues for the number of RDATAs.  Note that the opaque
/// data field does not always correspond to a specific RDATA field
/// as is the 2-byte preference field of MX.  For example, the field
/// sequence for an SOA RDATA in terms of `RdataEncoder` will be:
/// - a domain name (which corresponds to the SOA MNAME)
/// - a domain name (which corresponds to the SOA RNAME)
/// - 20 bytes of opaque data (for the rest of fields)
///
/// So, if you want to construct a general purpose dns::Rdata object
/// from the field sequence, you'll need to build the complete
/// wire-format data, and then construct a dns::Rdata object from it.
///
/// To use it, contstruct it with the data you got from RDataEncoder,
/// provide it with callbacks and then iterate through the data.
/// The callbacks are called with the data fields contained in the
/// data.
///
/// \code
/// void handleName(const dns::LabelSequence& labels, unsigned int flags) {
///     ...
/// }
/// void handleData(const void* data, size_t size) {
///     ...
/// }
///
/// RdataReader reader(RRClass::IN(), RRType::AAAA(), size, data,
///                    &handleName, &handleData);
/// reader.iterate();
/// \endcode
///
/// \note It is caller's responsibility to pass valid data here. This means
///     the data returned by RdataEncoder and the corresponding class and type.
///     If this is not the case, all the kinds of pointer hell might get loose.
class RdataReader {
public:
    /// \brief Function called on each name encountered in the data.
    typedef boost::function<void(const dns::LabelSequence&,
                                 RdataNameAttributes)> NameAction;
    /// \brief Function called on each data field in the data.
    typedef boost::function<void(const void*, size_t)> DataAction;

    /// \brief Constructor
    ///
    /// This constructs the reader on top of some serialized data.
    /// It does not copy the data, you have to make sure the data
    /// is valid for the whole life of this object and that they
    /// don't change.
    ///
    /// \param rrclass The class the encoded rdata belongs to.
    /// \param rrtype The type of the encode rdata.
    /// \param data The actual data.
    /// \param rdata_count The number of Rdata encoded in the data.
    /// \param sig_count The number of RRSig rdata bundled with the data.
    /// \param name_action The callback to be called on each encountered name.
    /// \param data_action The callback to be called on each data chunk.
    RdataReader(const dns::RRClass& rrclass, const dns::RRType& rrtype,
                const void* data, size_t rdata_count, size_t sig_count,
                const NameAction& name_action, const DataAction& data_action);

    /// \brief Result of next() and nextSig()
    ///
    /// This specifies if there's any boundary in the data at the
    /// place where the corresponding call to next() or nextSig()
    /// finished.
    enum Boundary {
        NO_BOUNDARY,    ///< It is in the middle of Rdata
        RDATA_BOUNDARY, ///< At the end of single Rdata
        RRSET_BOUNDARY  ///< At the end of the RRset (past the end)
    };

    /// \brief Step to next data field.
    ///
    /// Iterate over the next field and call appropriate hook (name_action
    /// or data_action, depending on the type) as passed to the constructor.
    ///
    /// \return It returns NO_BOUNDARY if the next call to next() will process
    ///     data of the same rdata as this one. RDATA_BOUNDARY is returned when
    ///     this field is the last of the current rdata. If there are no more
    ///     data to process, no hook is called and RRSET_BOUNDARY is returned.
    ///     Therefore, at the end of the whole data, once it processes the last
    ///     field and returns RDATA_BOUNDARY and then it returns RRSET_BOUNDARY
    ///     on the next call.
    Boundary next();

    /// \brief Call next() until the end.
    ///
    /// This is just convenience method to iterate through all the data.
    /// It calls next until it reaches the end (it does not rewind before,
    /// therefore if you already called next() yourself, it does not start
    /// at the beginning).
    void iterate() {
        while (next() != RRSET_BOUNDARY) { }
    }
    /// \brief Call next() until the end of current rdata.
    ///
    /// This is a convenience method to iterate until the end of current
    /// rdata. Notice this may cause more than one field being processed,
    /// as some rrtypes are more complex.
    ///
    /// \return If there was Rdata to iterate through.
    bool iterateRdata() {
        while (true) {
            switch(next()) {
                case NO_BOUNDARY: break;
                case RDATA_BOUNDARY: return (true);
                case RRSET_BOUNDARY: return (false);
            }
        }
    }

    /// \brief Step to next field of RRSig data.
    ///
    /// This is almost the same as next(), but it iterates through the
    /// associated RRSig data, not the data for the given RRType.
    Boundary nextSig();

    /// \brief Iterate through all RRSig data.
    ///
    /// This is almost the same as iterate(), but it iterates through the
    /// RRSig data instead.
    void iterateAllSigs() {
        while (nextSig() != RRSET_BOUNDARY) { }
    }

    /// \brief Iterate through the current RRSig Rdata.
    ///
    /// This is almote the same as iterateRdata, except it is for single
    /// signature Rdata.
    ///
    /// In practice, this should process one DATA field.
    bool iterateSingleSig() {
        while (true) {
            switch(nextSig()) {
                case NO_BOUNDARY: break;
                case RDATA_BOUNDARY: return (true);
                case RRSET_BOUNDARY: return (false);
            }
        }
    }

    /// \brief Rewind the iterator to the beginnig of data.
    ///
    /// The following next() and nextSig() will start iterating from the
    /// beginning again.
    void rewind();

    /// \brief Returns the size of associated data.
    ///
    /// This should be the same as the return value of
    /// RdataEncoder::getStorageLength() for the same set of data.
    /// The intended use of this method is to tell the caller the size of
    /// data that were possibly dynamically allocated so that the caller can
    /// use it for deallocation.
    ///
    /// This method only uses the parameters given at the construction of the
    /// object, and does not rely on or modify other mutable states.
    /// In practice, when the caller wants to call this method, that would be
    /// the only purpose of that RdataReader object (although it doesn't have
    /// to be so).
    size_t getSize() const;
private:
    const NameAction name_action_;
    const DataAction data_action_;
    const RdataEncodeSpec& spec_;
    // Total number of var-length fields, count of signatures
    const size_t var_count_total_, sig_count_, spec_count_;
    // Pointer to the beginning of length fields
    const uint16_t* const lengths_;
    // Pointer to the beginning of the data (after the lengths)
    const uint8_t* const data_;
    // Pointer to the first data signature
    // Will be computed during the normal RR iteration
    const uint8_t* sigs_;
    // The positions in data.
    size_t data_pos_, spec_pos_, length_pos_;
    size_t sig_pos_, sig_data_pos_;
    Boundary nextInternal(const NameAction& name_action,
                          const DataAction& data_action);
};

}
}
}

#endif
