// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LIBDNS_PYTHON_COMMON_H
#define LIBDNS_PYTHON_COMMON_H 1

#include <Python.h>

#include <boost/static_assert.hpp>

#include <climits>  // for CHAR_BIT
#include <stdexcept>
#include <string>

namespace isc {
namespace dns {
namespace python {
// For our 'general' isc::Exceptions
extern PyObject* po_IscException;
extern PyObject* po_InvalidParameter;

// For our own isc::dns::Exception
extern PyObject* po_DNSMessageBADVERS;

// This function reads 'bytes' from a sequence
// This sequence can be anything that implements the Sequence interface,
// but must consist of Numbers between 0 and 255 for every value.
//
// The data is stored in *data.
// Data must be allocated and have at least len bytes available.
//
// The current implementation removes read items from the
// head of the sequence, unless it fails (and returns -1), in which
// case nothing is removed
int readDataFromSequence(uint8_t *data, size_t len, PyObject* sequence);

int addClassVariable(PyTypeObject& c, const char* name, PyObject* obj);

// Short term workaround for unifying the return type of tp_hash
#if PY_MINOR_VERSION < 2
typedef long Py_hash_t;
#endif

/// \brief Convert a hash value of arbitrary type to a Python hash value.
///
/// This templated function is a convenient wrapper to produce a valid hash
/// value of type Py_hash_t, which is expected to be used as the return value
/// of a PyTypeObject.tp_hash implementation.  Py_hash_t is a signed integer
/// the same size as Py_ssize_t.
///
/// The major concern is that -1 means an error in tp_hash and so we need to
/// ensure that this value is never returned.
///
/// If the size of the original hash type is small enough, we convert
/// the original hash value to a value of Py_hash_t, resetting all higher bits
/// to 0.  Due to the assumption on the sizes, the conversion to HashvalType
/// is safe, and (after clearing the higher bits) results in a valid positive
/// value.
///
/// If the size of the input and return types is the same, we clear the
/// highest bit of the original hash so the resulting value will be in a valid
/// positive range of Py_hash_t.  If the original type is unsigned, there's
/// probably no better conversion than this because otherwise the conversion
/// to Py_hash_t could result in an undefined behavior.  If the original type
/// is signed, this conversion reduces the effective value range of the
/// original hash.  If this is not desired, the caller should convert it
/// by itself (note that -1 should be still avoided).
///
/// This function does not support the case where the size of the original
/// hash type is larger than that of Py_hash_t.
template <typename HashvalType>
Py_hash_t
convertToPyHash(HashvalType val) {
    BOOST_STATIC_ASSERT(sizeof(HashvalType) <= sizeof(Py_hash_t));

    // Some versions of g++ doesn't ignore the impossible case of if/else
    // below (depending on the size of HashvalType) and triggers a false
    // warning.
    // To work around it we use an intermediate mutable variable.
    // See Trac #1883 for details.
    size_t hash_val_bits = CHAR_BIT * sizeof(HashvalType);

    if (sizeof(HashvalType) < sizeof(Py_hash_t)) {
        // The original hash type is small enough.  Do trivial conversion.
        const Py_hash_t mask = ~(static_cast<Py_hash_t>(-1) << hash_val_bits);
        return (static_cast<Py_hash_t>(val) & mask);
    } else {
        // Clear the highest bit of the original hash so the conversion is
        // safe and avoids -1.
        HashvalType mask = ~(static_cast<HashvalType>(1) <<
                             (hash_val_bits - 1));
        return (val & mask);
    }
}
} // namespace python
} // namespace dns
} // namespace isc
#endif // LIBDNS_PYTHON_COMMON_H

// Local Variables:
// mode: c++
// End:
