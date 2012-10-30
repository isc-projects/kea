// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PYTHON_TSIGKEY_H
#define PYTHON_TSIGKEY_H 1

#include <Python.h>

namespace isc {
namespace dns {
class TSIGKey;
class TSIGKeyRing;

namespace python {

extern PyTypeObject tsigkey_type;
extern PyTypeObject tsigkeyring_type;

/// \brief Checks if the given python object is a TSIGKey object
///
/// \exception PyCPPWrapperException if obj is NULL
///
/// \param obj The object to check the type of
/// \return true if the object is of type TSIGKey, false otherwise
bool PyTSIGKey_Check(PyObject* obj);

/// \brief Returns a reference to the TSIGKey object contained within the given
///        Python object.
///
/// \note The given object MUST be of type TSIGKey; this can be checked with
///       either the right call to ParseTuple("O!"), or with PyTSIGKey_Check()
///
/// \note This is not a copy; if the TSIGKey is needed when the PyObject
/// may be destroyed, the caller must copy it itself.
///
/// \param tsigkey_obj The tsigkey object to convert
const TSIGKey& PyTSIGKey_ToTSIGKey(const PyObject* tsigkey_obj);

/// \brief Checks if the given python object is a TSIGKeyRing object
///
/// \param obj The object to check the type of
/// \return true if the object is of type TSIGKeyRing, false otherwise
bool PyTSIGKeyRing_Check(PyObject* obj);

/// \brief Returns a reference to the TSIGKeyRing object contained within the given
///        Python object.
///
/// \note The given object MUST be of type TSIGKeyRing; this can be checked with
///       either the right call to ParseTuple("O!"), or with PyTSIGKeyRing_Check()
///
/// \note This is not a copy; if the TSIGKeyRing is needed when the PyObject
/// may be destroyed, the caller must copy it itself.
///
/// \param tsigkeyring_obj The tsigkeyring object to convert
const TSIGKeyRing& PyTSIGKeyRing_ToTSIGKeyRing(const PyObject* tsigkeyring_obj);

} // namespace python
} // namespace dns
} // namespace isc
#endif // PYTHON_TSIGKEY_H

// Local Variables:
// mode: c++
// End:
