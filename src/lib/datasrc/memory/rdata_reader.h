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
/// This class allows you to read the data encoded by RDataEncoder.
/// It is rather low-level -- it provides sequence of data fields
/// and names. It does not give you convenient Rdata or RRset class.
///
/// It allows two types of operation. First one is by providing callbacks
/// to the constructor and then iterating by repeatedly calling next, or
/// calling iterate once. The callbacks are then called with each part of
/// the data.
///
/// \code
/// void handleLabel(const dns::LabelSequence& label, unsigned int flags) {
///     ...
/// }
/// void handleData(const uint8_t* data, size_t size) {
///     ...
/// }
///
/// RdataReader reader(RRClass::IN(), RRType::AAAA(), size, data,
///                    &handleLabel, handleData);
/// reader.iterate();
/// \endcode
///
/// The other way is to use the return value of next() and loop through
/// it manually. It has the inconvenience of having the type condition, but
/// the code is in one place. The used way is matter of personal preferrence,
/// there's no much difference on the technical side.
///
/// \code
/// RdataReader reader(RRClass::IN(), RRType::AAAA(), size, data,
///                    &handleLabel, handleData);
/// RdataReader::Result data;
/// while (data = reader.next()) {
///     switch(data.type()) {
///         case RdataReader::NAME:
///             ...
///             break;
///         case RdataReader::DATA:
///             ...
///             break;
///         default: assert(0); // Can not happen
///     }
/// }
/// \endcode
class RdataReader {
public:
    /// \brief Function called on each name encountered in the data.
    typedef boost::function<void(const dns::LabelSequence&, unsigned)>
        NameAction;
    /// \brief Function called on each data field in the data.
    typedef boost::function<void(const uint8_t*, size_t)> DataAction;

    /// \brief a NameAction that does nothing.
    ///
    /// This is a NameAction function that does nothing. It is used
    /// as a default in the constructor.
    static void emptyNameAction(const dns::LabelSequence& label,
                                unsigned attributes);
    /// \brief a DataAction that does nothing.
    ///
    /// This is a DataAction function that does nothing. It is used
    /// as a default in the constructor.
    static void emptyDataAction(const uint8_t* data, size_t size);

    /// \brief Constructor
    ///
    /// This constructs the reader on top of some serialized data.
    /// It does not copy the data, you have to make sure the data
    /// is valid for the whole life of this object and that they
    /// don't change.
    ///
    /// \param rrclass The class the encoded rdata belongs to.
    /// \param rrtype The type of the encode rdata.
    /// \param size Number of bytes the data have in serialized form.
    /// \param data The actual data.
    /// \param name_action The callback to be called on each encountered name.
    /// \param data_action The callback to be called on each data chunk.
    RdataReader(const dns::RRClass& rrclass, const dns::RRType& rrtype,
                size_t size, const uint8_t* data,
                const NameAction& name_action = &emptyNameAction,
                const DataAction& data_action = &emptyDataAction);

    /// \brief The type of data returned from this iteration.
    enum DataType {
        NAME, ///< This iteration returns domain label
        DATA, ///< This iteration returns unstructuder data
        END   ///< No more data to return
    };

    /// \brief Data from one iteration
    ///
    /// Each time you call next() or nextSig(), it returns some data.
    /// This holds the data.
    ///
    /// It is valid only for as long as the RdataReader that returned it.
    ///
    /// All the methods can be called under any circumstances. However,
    /// if the required property is not valid for the given type (eg.
    /// when calling size() on type() == NAME), it returns some "empty"
    /// value (0, NULL, or the like).
    class Result {
    public:
        /// \brief Default constructor
        ///
        /// It creates an empty result (with no data) of type END.
        Result() :
            // TODO: Do we maybe want to have a static one to copy
            // instead of constructing new one from the root Name?
            label_(dns::Name::ROOT_NAME()),
            data_(NULL),
            size_(0),
            type_(END),
            compressible_(false),
            additional_(false)
        {}
        /// \brief Constructor from a domain label
        ///
        /// Creates the NAME type result. Used internally from RdataReader.
        ///
        /// \param label The label to hold
        /// \param attributes The attributes, as stored by the serialized
        ///     data.
        Result(const dns::LabelSequence& label, unsigned attributes);
        /// \brief Constructor from data
        ///
        /// Creates the DATA type result. Used internally from RdataReader.
        ///
        /// \param data The data pointer to hold.
        /// \param size The size to hold.
        Result(const uint8_t* data, size_t size);
        /// \brief The type of data returned.
        DataType type() const { return (type_); }
        /// \brief The raw data.
        ///
        /// This is only valid if type() == DATA.
        const uint8_t* data() const { return (data_); }
        /// \brief The size of the raw data.
        ///
        /// This is the number of bytes the data takes. It is valid only
        /// if type() == DATA.
        size_t size() const { return (size_); }
        /// \brief The domain label.
        ///
        /// This holds the domain label. It is only valid if type() == NAME.
        const dns::LabelSequence& label() const { return (label_); }
        /// \brief Is the name in label() compressible?
        ///
        /// This is valid only if type() == NAME.
        bool compressible() const { return (compressible_); }
        /// \brief Does the name expect additional processing?
        ///
        /// This is valid only if type() == NAME.
        bool additional() const { return (additional_); }
        /// \brief If there are data returned.
        ///
        /// This returns if there are any data at all returned. This is
        /// equivalent to action != END, but it allows for more convenient
        /// code of a loop through the data.
        operator bool() const {
            return (type() != END);
        }
    private:
        dns::LabelSequence label_;
        const uint8_t* data_;
        size_t size_;
        DataType type_;
        bool compressible_;
        bool additional_;
    };

    /// \brief Step to next piece of data.
    ///
    /// This returns the next available data. Also, the apropriate hook
    /// (name_action or data_action, depending on the data type) as passed
    /// to the constructor is called.
    ///
    /// If there are no more data, a Result with type END is returned and
    /// no callback is called.
    Result next();
    /// \brief Call next() until the end.
    ///
    /// This is just convenience method to iterate through all the data.
    /// It calls next until it reaches the end (it does not revind before,
    /// therefore if you already called next() yourself, it does not start
    /// at the beginning).
    ///
    /// The method only makes sense if you set the callbacks in constructor.
    void iterate() {
        while (next()) { }
    }
    /// \brief Step to next piece of RRSig data.
    ///
    /// This is almost the same as next(), but it iterates through the
    /// associated RRSig data, not the data for the given RRType.
    Result nextSig();
    /// \brief Iterate through all RRSig data.
    ///
    /// This is almost the same as iterate(), but it iterates through the
    /// RRSig data instead.
    void iterateSig() {
        while (nextSig()) { }
    }
    /// \brief Rewind the iterator to the beginnig of data.
    ///
    /// The following next() and nextSig() will start iterating from the
    /// beginning again.
    void rewind();

    /// \brief Returns the size of associated data.
    ///
    /// This just returns whatever was passed to the constructor as size.
    size_t getSize() const;
};

}
}
}

#endif
