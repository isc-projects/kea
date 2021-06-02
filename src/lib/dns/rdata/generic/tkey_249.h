// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// BEGIN_HEADER_GUARD

#include <stdint.h>

#include <string>

#include <dns/name.h>
#include <dns/rdata.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

struct TKEYImpl;

/// \brief \c rdata::TKEY class represents the TKEY RDATA as defined %in
/// RFC2930.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// TKEY RDATA.
class TKEY : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    /// \brief Constructor from RDATA field parameters.
    ///
    /// The parameters are a straightforward mapping of %TKEY RDATA
    /// fields as defined %in RFC2930.
    ///
    /// This RR is pretty close to the TSIG RR with 32 bit timestamps,
    /// or the RRSIG RR with a second "other" data field.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    ///
    /// \param algorithm The DNS name of the algorithm e.g. gss-tsig.
    /// \param inception The inception time (in seconds since 1970).
    /// \param expire The expire time (in seconds since 1970).
    /// \param mode The mode e.g. Diffie-Hellman (2) or GSS-API (3).
    /// \param error The error code (extended error space shared with TSIG).
    /// \param key_len The key length (0 means no key).
    /// \param key The key (can be 0).
    /// \param other_len The other data length (0 means no other data).
    /// \param other_data The other data (can be and usually is 0).
    TKEY(const Name& algorithm, uint32_t inception, uint32_t expire,
         uint16_t mode, uint16_t error, uint16_t key_len,
         const void* key, uint16_t other_len, const void* other_data);

    /// \brief Assignment operator.
    ///
    /// It internally allocates a resource, and if it fails a corresponding
    /// standard exception will be thrown.
    /// This operator never throws an exception otherwise.
    ///
    /// This operator provides the strong exception guarantee: When an
    /// exception is thrown the content of the assignment target will be
    /// intact.
    TKEY& operator=(const TKEY& source);

    /// \brief The destructor.
    ~TKEY();

    /// \brief Return the algorithm name.
    ///
    /// This method never throws an exception.
    const Name& getAlgorithm() const;

    /// \brief Return the value of the Inception field as a number.
    ///
    /// This method never throws an exception.
    uint32_t getInception() const;

    /// \brief Return the value of the Inception field as a string.
    std::string getInceptionDate() const;

    /// \brief Return the value of the Expire field as a number.
    ///
    /// This method never throws an exception.
    uint32_t getExpire() const;

    /// \brief Return the value of the Expire field as a string.
    std::string getExpireDate() const;

    /// \brief Return the value of the Mode field.
    ///
    /// This method never throws an exception.
    uint16_t getMode() const;

    /// \brief Return the value of the Error field.
    ///
    /// This method never throws an exception.
    uint16_t getError() const;

    /// \brief Return the value of the Key Len field.
    ///
    /// This method never throws an exception.
    uint16_t getKeyLen() const;

    /// \brief Return the value of the Key field.
    ///
    /// This method never throws an exception.
    const void* getKey() const;

    /// \brief Return the value of the Other Len field.
    ///
    /// This method never throws an exception.
    uint16_t getOtherLen() const;

    /// \brief Return the value of the Other Data field.
    ///
    /// The same note as \c getMAC() applies.
    ///
    /// This method never throws an exception.
    const void* getOtherData() const;

    /// \brief The GSS_API constant for the Mode field.
    static const uint16_t GSS_API_MODE;

private:
    TKEYImpl* constructFromLexer(MasterLexer& lexer, const Name* origin);

    TKEYImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
