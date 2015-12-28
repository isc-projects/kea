// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RDATAFIELDS_H
#define RDATAFIELDS_H 1

#include <stdint.h>

#include <cstddef>

namespace isc {
namespace util {
class OutputBuffer;
}
namespace dns {
class AbstractMessageRenderer;

namespace rdata {
class Rdata;

/// A low-level, RR type-independent representation of DNS RDATA.
///
/// <b>Purpose of the Class</b>
///
/// This class intends to help "serialization" of the content of RDATA
/// in a space-efficient manner.  Specific derived classes of \c Rdata
/// focus on the convenience of accessing RDATA fields for RR type-specific
/// protocol operations, and can be inefficient in terms of space.
/// For example, a DNS character string may be internally represented as a
/// \c std::string object with all of the overhead of the richer class.
/// If an application needs to maintain a very large number of RRs and it
/// does not have to perform RR specific operation so often, it may make more
/// sense to store the data in memory in a lower-level but space efficient
/// form.
///
/// Another purpose of this class is to improve rendering performance for
/// RDATA.  If the only requirement were space efficiency, it would be just
/// sufficient to convert the \c RDATA into a binary sequence in the wire
/// format.  However, to render the data in a DNS message, we'd have to
/// re-construct a corresponding \c Rdata object in the case where name
/// compression is necessary.  This is not desirable, and this class is
/// provided to avoid such unnecessary overhead.
///
/// <b>Data Format</b>
///
/// To meet these goals, this class helps convert an \c Rdata object into
/// two pieces of information: Wire-format representation of the \c Rdata
/// and associated meta information for efficient rendering.
///
/// Specifically, it maintains the wire-format data as a sequence of typed
/// fields.  The types are:
/// - Compressible name: a domain name as an RDATA field that can be compressed
/// - Incompressible name: a domain name as an RDATA field that cannot be
///   compressed
/// - Other data: any other fields of RDATA, which should be treated as opaque
///
/// (See also the description of \c RdataFields::Type)
/// Whether a name can or cannot be compressed is determined according to
/// RFC3597.
///
/// A "other data" field may not always correspond to a single RDATA field.
/// A \c RdataFields field (of other data) is just a contiguous region of the
/// wire-format data that does not involve name compression.
/// For example, the SOA RDATA begins with two "compressible" names followed
/// by 5 32-bit fields.
/// In \c RdataFields the last 5 fields would be considered a single 20-byte
/// field.
///
/// Each \c RdataFields field is identified by the \c FieldSpec structure,
/// which provides the type and length of the field.
/// An \c RdataFields object internally maintains a sequence of \c FieldSpec
/// objects in a form of plain C-style array, which can be referenced via
/// a pointer returned by the \c getFieldSpecData() method.
/// The \c \c FieldSpec for a specific field can also be retrieved by the
/// \c getFieldSpec() method.
///
/// The following diagram shows the internal memory representation of
/// an SOA RDATA in the form of \c RdataFields object and how an application
/// can get access to the memory region.
/** \verbatim
accessible via      |0                               getDataLength() bytes
getData()----------> <MNAME><RNAME><Rest of the data>
                     <---------- 3 * sizeof(FieldSpec) bytes ------------->
getFieldSpecData()-> { compressible name { compressible name { other data
                       len: MNAME-len }    len: RNAME-len }    len: 20    }
\endverbatim
 */
/// where MNAME and RNAME are wire format representations of the MNAME and
/// RNAME fields of the SOA RDATA, respectively, and "Rest of the data"
/// encodes the remaining 20 bytes of the RDATA in network byte order.
///
/// <b>Usage of the Class</b>
///
/// One major and common use case of the \c RdataFields class is to convert
/// a \c Rdata object (possibly given from a DNS message or some configuration
/// source such as a zone file) in the serialized format and store a copy of
/// the data somewhere in memory.  The following code sample implements this
/// scenario:
/// \code // assume "rdata" is a reference type to Rdata
/// const RdataFields fields(rdata);
/// const unsigned int fields_size = fields.getFieldDataSize();
/// memcpy(some_place, fields.getFieldSpecData(), fields_size);
/// const size_t data_length = fields.getDataLength();
/// memcpy(other_place, fields.getData(), data_length);
/// // (fields_size and data_length should be stored somewhere, too)
/// \endcode
///
/// Another typical usage is to render the stored data in the wire format
/// as efficiently as possible.  The following code is an example of such
/// usage:
/// \code // assume "renderer" is of type MessageRenderer
/// // retrieve data_length and fields_size from the storage
/// RdataFields(some_place, fields_size, other_place,
///             data_length).toWire(renderer);
/// \endcode
///
/// <b>Notes to Users</b>
///
/// The main purposes of this class is to help efficient operation
/// for some (limited classes of) performance sensitive application.
/// For this reason the interface and implementation rely on relatively
/// lower-level, riskier primitives such as passing around bare pointers.
///
/// It is therefore discouraged to use this class for general purpose
/// applications that do not need to maximize performance in terms of either
/// memory footprint or rendering speed.
/// All functionality provided by this class can be achieved via higher level
/// interfaces such as the \c Rdata class variants.
/// Normal applications should use those interfaces.
///
/// The data format is public information so that an application can examine
/// and use selected parts of data.  For example, an application may want to
/// encode domain names in RDATA in a different way while storing the other
/// data in a separate place.
/// However, at this moment the format is still in flux, and it may not
/// be compatible with future versions (see below).
///
/// <b>Development Notes</b>
///
/// We should conduct benchmark tests to measure rendering performance.
///
/// The current implementation needs to re-construct name objects from
/// compressible and incompressible name fields as wire-format data.
/// This is not efficient, and we'll probably want to improve this in a
/// future version.  One possibility is to store offset information as well
/// as the name data (at the cost of increasing memory footprint), and
/// to use the pair of data for faster rendering.
class RdataFields {
public:
    /// Types of \c RdataFields fields.
    ///
    /// \c COMPRESSIBLE_NAME and \c INCOMPRESSIBLE_NAME represent a domain
    /// name used as a field of an RDATA that can and cannot be compressed
    /// per RFC3597.
    /// \c DATA means all other types of fields.
    enum Type {
        DATA,              ///< Plain data.
        COMPRESSIBLE_NAME, ///< A domain name subject to name compression.
        INCOMPRESSIBLE_NAME ///< A domain name that shouldn't be compressed.
    };

    /// Structure that specifies a single \c RdataFields field.
    ///
    /// This is a straightforward pair of the type and length of a single
    /// \c RdataFields field.
    ///
    /// In some cases an application may want to do deeper inspection of
    /// some \c RdataFields field(s).  For example, an application may want
    /// to construct a \c Name object for each domain name field of an RDATA
    /// and use it for some special purpose.
    /// The \c FieldSpec structure provides necessary parameters to get access
    /// to a specific \c RdataFields field.
    ///
    /// The following code snippet implements the above example scenario:
    /// \code // assume "fields" is of type RdataFields
    /// size_t offset = 0;
    /// for (int i = 0; i < fields.getFieldCount(); ++i) {
    ///     const FieldSpec spec = fields.getFieldSpec(i);
    ///     if (spec.type == RdataFields::COMPRESSIBLE_NAME ||
    ///         spec.type == RdataFields::INCOMPRESSIBLE_NAME) {
    ///         InputBuffer ibuffer(fields.getData() + offset, spec.len);
    ///         Name name(ibuffer);
    ///         // do something with name
    ///     }
    ///     offset += spec.len;
    /// } \endcode
    ///
    /// Note that the offset is not included in \c FieldSpec.
    /// This is because such deeper inspection would be a relatively rare
    /// operation while it is desirable to keep this structure as small as
    /// possible for the purpose of space efficiency.
    /// Also, if and when an application wants to look into a specific field,
    /// it would be quite likely that the application iterates over all fields
    /// and does something special for selected fields like the above example.
    /// In that case the application can easily and efficiently identify the
    /// necessary offset, again, as shown in the above code example.
    ///
    /// \todo We might find that 16bits per field is generally too much and
    ///     squeeze the two bit type into it as well, having 14bit length
    ///     (in the rare case of having too long field, it could be split into
    ///     multiple ones). That would save 2 bytes per item (one for the type,
    ///     one for padding).
    struct FieldSpec {
        FieldSpec(Type type_param, uint16_t len_param) :
            type(type_param), len(len_param)
        {}
        Type type;              ///< The type of the field.
        uint16_t len;           ///< The length of the field in bytes.
    };

    ///
    /// \name Constructors and Destructor.
    ///
    /// \b Note:
    /// The copy constructor and the assignment operator are intentionally
    /// defined as private, making this class non copyable.
    //@{
private:
    RdataFields(const RdataFields& source);
    RdataFields& operator=(const RdataFields& source);

public:
    /// Constructor from Rdata.
    ///
    /// This constructor converts the data of a given \c Rdata object into
    /// an \c RdataFields object so that the resulting data can be stored
    /// in memory in a space-efficient way.
    ///
    /// It makes a local copy of the original data and dynamically allocates
    /// necessary memory, so is not very efficient.
    /// The basic idea is to perform the expensive conversion once and keep
    /// using the result as long as possible to improve overall performance
    /// in a longer term.
    ///
    /// If the internal resource allocation fails, a corresponding standard
    /// exception will be thrown.
    /// The current implementation of this constructor internally calls
    /// the <code>Rdata::toWire(AbstractMessageRenderer&) const</code> method
    /// for the conversion.
    /// If that method throws an exception it will be propagated to the caller
    /// of this constructor.
    ///
    /// \param rdata The RDATA for which the \c RdataFields to be constructed.
    RdataFields(const Rdata& rdata);

    /// Constructor from field parameters.
    ///
    /// The intended usage of this version of constructor is to form a
    /// structured representation of \c RDATA encoded by the other
    /// constructor so that the resulting object can be used for subsequent
    /// operations such as rendering in the wire format.
    /// This version is intended to be efficient by not making any copy
    /// of variable length data or expensive data inspection.
    ///
    /// This constructor is basically exception free, except against bogus
    /// input parameters.
    /// Specifically, the parameters must meet the following conditions;
    /// otherwise an exception of class \c InvalidParameter will be thrown.
    /// - \c fields can be \c NULL if and only if \c nfields is 0
    /// - \c data can be \c NULL if and only if \c data_length is 0
    /// - the sum of the lengths of \c fields entries must be equal to
    ///   \c data_length
    ///
    /// This constructor assumes that the memory region pointed by \c data (if
    /// non \c NULL) is encoded as a sequence of valid \c RdataFields fields,
    /// and does not perform deep inspection on each field.
    /// In particular, for fields of type \c COMPRESSIBLE_NAME or
    /// \c INCOMPRESSIBLE_NAME, this constructor assumes the corresponding
    /// memory region is a valid representation of domain name.
    /// Otherwise, a subsequent method call such as
    /// <code>toWire(AbstractMessageRenderer&) const</code>
    /// may trigger an unexpected exception. It also expects the fields reside
    /// on address that is valid for them (eg. it has valid alignment), see
    /// getFieldSpecData() for details.
    ///
    /// It is the caller's responsibility to ensure this assumption.
    /// In general, this constructor is expected to be used for serialized data
    /// generated by the other constructor from a valid \c Rdata.
    /// The result is not guaranteed if the data is generated in any other
    /// ways.
    ///
    /// The resulting \c RdataFields object does not maintain a copy of
    /// \c fields or \c data.  It is the caller's responsibility to ensure
    /// the memory regions pointed to by these parameters are valid and intact
    /// as long as the \c RdataFields object is used.
    ///
    /// \param fields An array of \c FieldSpec entries.  This can be \c NULL.
    /// \param fields_length The total length of the \c fields.
    /// \param data A pointer to memory region for the entire RDATA.  This can
    /// be NULL.
    /// \param data_length The length of \c data in bytes.
    RdataFields(const void* fields, const unsigned int fields_length,
                const void* data, const size_t data_length);

    /// The destructor.
    ~RdataFields();
    //@}

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Return the length of the entire RDATA encoded in the
    /// \c RdataFields in bytes.
    ///
    /// This method never throws an exception.
    unsigned int getDataLength() const { return (data_length_); }

    /// \brief Return a pointer to the RDATA encoded in the \c RdataFields.
    ///
    /// The RdataFields holds ownership of the data.
    ///
    /// This method never throws an exception.
    const void* getData() const { return (data_); }

    /// \brief Return the number of bytes the buffer returned by
    ///      getFieldSpecData() will occupy.
    ///
    /// This method never throws an exception.
    unsigned int getFieldSpecDataSize() const { return (nfields_ *
                                                    sizeof (*fields_)); }

    /// \brief Return the number of specs fields.
    ///
    /// It specifies the range of parameter for getFieldSpec().
    ///
    /// This method never throws.
    unsigned int getFieldCount() const { return (nfields_); }

    /// \brief Return a pointer to a sequence of \c FieldSpec for the
    /// \c RdataFields.
    ///
    /// This should be treated as an opaque internal representation you can
    /// just store off somewhere and use it to construct a new RdataFields.
    /// from it. If you are really interested, you can typecast it to
    /// FieldSpec * (which is what it really is internally).
    ///
    /// The RdataFields holds ownership of the data.
    ///
    /// \note You should, however, be aware of alignment issues. The pointer
    ///     you pass to the constructor must be an address where the FieldSpec
    ///     can live. If you store it at a wrong address (eg. even one with
    ///     current implementation on most architectures), it might lead bad
    ///     things from slow access to SIGBUS. The easiest way is not to
    ///     interleave the fields with data from getData(). It is OK to place
    ///     all the fields first (even from multiple RdataFields) and then
    ///     place all the data after them.
    ///
    /// This method never throws an exception.
    const void* getFieldSpecData() const {
        return (fields_);
    }

    /// \brief Return the specification of the field identified by the given
    /// index.
    ///
    /// \c field_id is the field index, which must be in the range of
    /// <code>[0, getFieldCount())</code>.  0 means the first field, and
    /// <code>getFieldCount()-1</code> means the last.
    ///
    /// If the given index is not in the valid range, an exception of class
    /// \c OutOfRange will be thrown.
    /// This method never throws an exception otherwise.
    ///
    /// \param field_id The index of an \c RdataFields field to be returned.
    /// \return A \c FieldSpec structure that contains the information of
    /// the \c field_id-th field.
    FieldSpec getFieldSpec(const unsigned int field_id) const;
    //@}

    ///
    /// \name Converter Methods
    ///
    //@{
    /// \brief Render the RdataFields in the wire format with name compression.
    ///
    /// This method may require resource allocation in \c renderer.
    /// If it fails, a corresponding standard exception will be thrown.
    /// It should not throw any other exception as long as the \c RdataFields
    /// object was constructed from valid parameters (see the description of
    /// constructors).  The result is not guaranteed if it's constructed in
    /// any other ways.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer and name compression information.
    void toWire(AbstractMessageRenderer& renderer) const;

    /// \brief Render the RdataFields in the wire format without name
    /// compression.
    ///
    /// This method may require resource allocation in \c buffer.
    /// If it fails, a corresponding standard exception will be thrown.
    ///
    /// \param buffer An output buffer to store the wire data.
    void toWire(isc::util::OutputBuffer& buffer) const;
    //@}

private:
    const FieldSpec* fields_;
    unsigned int nfields_;
    const uint8_t* data_;
    size_t data_length_;

    // hide further details within the implementation and don't create vectors
    // every time we don't need them.
    struct RdataFieldsDetail;
    RdataFieldsDetail* detail_;
};
}
}
}
#endif  // RDATAFIELDS_H

// Local Variables:
// mode: c++
// End:
