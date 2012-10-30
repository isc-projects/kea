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

#ifndef NSEC3PARAM_COMMON_H
#define NSEC3PARAM_COMMON_H 1

#include <util/buffer.h>

#include <stdint.h>

#include <sstream>
#include <string>
#include <vector>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {
namespace nsec3 {

/// \file
///
/// This helper module provides some utilities that handle NSEC3 and
/// NSEC3PARAM RDATA.  They share the first few fields, and some operations
/// on these fields are sufficiently complicated, so it would make sense to
/// consolidate the processing logic into a single implementation module.
///
/// The functions defined here are essentially private and are only expected
/// to be called from the \c NSEC3 and \c NSEC3PARAM class implementations.

/// \brief Result values of the utilities.
///
/// This structure encapsulates a tuple of NSEC3/NSEC3PARAM algorithm,
/// flags and iterations field values.  This is used as the return value
/// of the utility functions defined in this module so the caller can
/// use it for constructing the corresponding RDATA.
struct ParseNSEC3ParamResult {
    ParseNSEC3ParamResult(uint8_t param_algorithm, uint8_t param_flags,
                          uint16_t param_iterations) :
        algorithm(param_algorithm), flags(param_flags),
        iterations(param_iterations)
    {}
    const uint8_t algorithm;
    const uint8_t flags;
    const uint16_t iterations;
};

/// \brief Convert textual representation of NSEC3 parameters.
///
/// This function takes an input string stream that consists of a complete
/// textual representation of an NSEC3 or NSEC3PARAM RDATA and parses it
/// extracting the hash algorithm, flags, iterations, and salt fields.
///
/// The first three fields are returned as the return value of this function.
/// The salt will be stored in the given vector.  The vector is expected
/// to be empty, but if not, the existing content will be overridden.
///
/// On successful return the given input stream will reach the end of the
/// salt field.
///
/// \exception isc::BadValue The salt is not a valid hex string.
/// \exception InvalidRdataText The given string is otherwise invalid for
/// NSEC3 or NSEC3PARAM fields.
///
/// \param rrtype_name Either "NSEC3" or "NSEC3PARAM"; used as part of
/// exception messages.
/// \param rdata_str A complete textual string of the RDATA; used as part of
/// exception messages.
/// \param iss Input stream that consists of a complete textual string of
/// the RDATA.
/// \param salt A placeholder for the salt field value of the RDATA.
/// Expected to be empty, but it's not checked (and will be overridden).
///
/// \return The hash algorithm, flags, iterations in the form of
/// ParseNSEC3ParamResult.
ParseNSEC3ParamResult parseNSEC3ParamText(const char* const rrtype_name,
                                          const std::string& rdata_str,
                                          std::istringstream& iss,
                                          std::vector<uint8_t>& salt);

/// \brief Extract NSEC3 parameters from wire-format data.
///
/// This function takes an input buffer that stores wire-format NSEC3 or
/// NSEC3PARAM RDATA and parses it extracting the hash algorithm, flags,
/// iterations, and salt fields.
///
/// The first three fields are returned as the return value of this function.
/// The salt will be stored in the given vector.  The vector is expected
/// to be empty, but if not, the existing content will be overridden.
///
/// On successful return the input buffer will point to the end of the
/// salt field; rdata_len will be the length of the rest of RDATA
/// (in the case of a valid NSEC3PARAM, it should be 0).
///
/// \exception DNSMessageFORMERR The wire data is invalid.
///
/// \param rrtype_name Either "NSEC3" or "NSEC3PARAM"; used as part of
/// exception messages.
/// \param buffer An input buffer that stores wire-format RDATA.  It must
/// point to the beginning of the data.
/// \param rdata_len The total length of the RDATA.
/// \param salt A placeholder for the salt field value of the RDATA.
/// Expected to be empty, but it's not checked (and will be overridden).
///
/// \return The hash algorithm, flags, iterations in the form of
/// ParseNSEC3ParamResult.
ParseNSEC3ParamResult parseNSEC3ParamWire(const char* const rrtype_name,
                                          isc::util::InputBuffer& buffer,
                                          size_t& rdata_len,
                                          std::vector<uint8_t>& salt);
}
}
}
}
}
}

#endif  // NSEC3PARAM_COMMON_H

// Local Variables:
// mode: c++
// End:
