// Copyright (C) 2012,2014  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/base32hex.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>

#include <dns/name.h>
#include <dns/labelsequence.h>
#include <dns/nsec3hash.h>
#include <dns/rdataclass.h>
#include <dns/name_internal.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::cryptolink;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {

/// \brief A derived class of \c NSEC3Hash that implements the standard hash
/// calculation specified in RFC5155.
///
/// Currently the only pre-defined algorithm in the RFC is SHA1.  So we don't
/// over-generalize it at the moment, and rather hardcode it and assume that
/// specific algorithm.
///
/// The implementation details are only open within this file, but to avoid
/// an accidental error in this implementation we explicitly make it non
/// copyable.
class NSEC3HashRFC5155 : boost::noncopyable, public NSEC3Hash {
private:
    // This is the algorithm number for SHA1/NSEC3 as defined in RFC5155.
    static const uint8_t NSEC3_HASH_SHA1 = 1;
    // For digest_ allocation
    static const size_t DEFAULT_DIGEST_LENGTH = 32;

public:
    NSEC3HashRFC5155(uint8_t algorithm, uint16_t iterations,
                     const uint8_t* salt_data, size_t salt_length) :
        algorithm_(algorithm), iterations_(iterations),
        salt_data_(NULL), salt_length_(salt_length),
        digest_(DEFAULT_DIGEST_LENGTH), obuf_(Name::MAX_WIRE)
    {
        if (algorithm_ != NSEC3_HASH_SHA1) {
            isc_throw(UnknownNSEC3HashAlgorithm, "Unknown NSEC3 algorithm: " <<
                      static_cast<unsigned int>(algorithm_));
        }

        if (salt_length > 0) {
            salt_data_ = static_cast<uint8_t*>(std::malloc(salt_length));
            if (salt_data_ == NULL) {
                throw std::bad_alloc();
            }
            std::memcpy(salt_data_, salt_data, salt_length);
        }
    }

    virtual ~NSEC3HashRFC5155() {
        std::free(salt_data_);
    }

    virtual std::string calculate(const Name& name) const;
    virtual std::string calculate(const LabelSequence& ls) const;

    virtual bool match(const generic::NSEC3& nsec3) const;
    virtual bool match(const generic::NSEC3PARAM& nsec3param) const;
    bool match(uint8_t algorithm, uint16_t iterations,
               const vector<uint8_t>& salt) const;

private:
    std::string calculateForWiredata(const uint8_t* data, size_t length) const;

    const uint8_t algorithm_;
    const uint16_t iterations_;
    uint8_t* salt_data_;
    const size_t salt_length_;

    // The following members are placeholder of work place and don't hold
    // any state over multiple calls so can be mutable without breaking
    // constness.
    mutable OutputBuffer digest_;
    mutable vector<uint8_t> vdigest_;
    mutable OutputBuffer obuf_;
};

inline void
iterateSHA1(const uint8_t* input, size_t inlength,
            const uint8_t* salt, size_t saltlen,
            OutputBuffer& output)
{
    boost::scoped_ptr<Hash> hash(CryptoLink::getCryptoLink().createHash(SHA1));
    hash->update(input, inlength);
    hash->update(salt, saltlen); // this works whether saltlen == or > 0
    hash->final(output, hash->getOutputLength());
}

string
NSEC3HashRFC5155::calculateForWiredata(const uint8_t* data,
                                       size_t length) const
{
    // We first need to normalize the name by converting all upper case
    // characters in the labels to lower ones.

    uint8_t name_buf[256];
    assert(length < sizeof (name_buf));

    const uint8_t *p1 = data;
    uint8_t *p2 = name_buf;
    while (*p1 != 0) {
        char len = *p1;

        *p2++ = *p1++;
        while (len--) {
            *p2++ = isc::dns::name::internal::maptolower[*p1++];
        }
    }

    *p2 = *p1;

    digest_.clear();
    iterateSHA1(name_buf, length,
                salt_data_, salt_length_, digest_);
    const uint8_t* dgst_data = static_cast<const uint8_t*>(digest_.getData());
    size_t dgst_len = digest_.getLength();
    for (unsigned int n = 0; n < iterations_; ++n) {
        digest_.clear();
        iterateSHA1(dgst_data, dgst_len, salt_data_, salt_length_, digest_);
    }

    vdigest_.resize(dgst_len);
    std::memcpy(&vdigest_[0], dgst_data, dgst_len);
    return (encodeBase32Hex(vdigest_));
}

string
NSEC3HashRFC5155::calculate(const Name& name) const {
    obuf_.clear();
    name.toWire(obuf_);

    return (calculateForWiredata(static_cast<const uint8_t*>(obuf_.getData()),
                                 obuf_.getLength()));
}

string
NSEC3HashRFC5155::calculate(const LabelSequence& ls) const {
    assert(ls.isAbsolute());

    size_t length;
    const uint8_t* data = ls.getData(&length);

    return (calculateForWiredata(data, length));
}

bool
NSEC3HashRFC5155::match(uint8_t algorithm, uint16_t iterations,
                        const vector<uint8_t>& salt) const
{
    return (algorithm_ == algorithm && iterations_ == iterations &&
            salt_length_ == salt.size() &&
            ((salt_length_ == 0) ||
             memcmp(salt_data_, &salt[0], salt_length_) == 0));
}

bool
NSEC3HashRFC5155::match(const generic::NSEC3& nsec3) const {
    return (match(nsec3.getHashalg(), nsec3.getIterations(),
                  nsec3.getSalt()));
}

bool
NSEC3HashRFC5155::match(const generic::NSEC3PARAM& nsec3param) const {
    return (match(nsec3param.getHashalg(), nsec3param.getIterations(),
                  nsec3param.getSalt()));
}

// A static pointer that refers to the currently usable creator.
// Only get/setNSEC3HashCreator are expected to get access to this variable
// directly.
const NSEC3HashCreator* creator;

// The accessor to the current creator.  If it's not explicitly set or has
// been reset from a customized one, the default creator will be used.
const NSEC3HashCreator*
getNSEC3HashCreator() {
    static DefaultNSEC3HashCreator default_creator;
    if (creator == NULL) {
        creator = &default_creator;
    }
    return (creator);
}

} // end of unnamed namespace

namespace isc {
namespace dns {

NSEC3Hash*
NSEC3Hash::create(const generic::NSEC3PARAM& param) {
    return (getNSEC3HashCreator()->create(param));
}

NSEC3Hash*
NSEC3Hash::create(const generic::NSEC3& nsec3) {
    return (getNSEC3HashCreator()->create(nsec3));
}

NSEC3Hash*
NSEC3Hash::create(uint8_t algorithm, uint16_t iterations,
                  const uint8_t* salt_data, size_t salt_length) {
    return (getNSEC3HashCreator()->create(algorithm, iterations,
                                          salt_data, salt_length));
}

NSEC3Hash*
DefaultNSEC3HashCreator::create(const generic::NSEC3PARAM& param) const {
    const vector<uint8_t>& salt = param.getSalt();
    return (new NSEC3HashRFC5155(param.getHashalg(), param.getIterations(),
                                 salt.empty() ? NULL : &salt[0],
                                 salt.size()));
}

NSEC3Hash*
DefaultNSEC3HashCreator::create(const generic::NSEC3& nsec3) const {
    const vector<uint8_t>& salt = nsec3.getSalt();
    return (new NSEC3HashRFC5155(nsec3.getHashalg(), nsec3.getIterations(),
                                 salt.empty() ? NULL : &salt[0],
                                 salt.size()));
}

NSEC3Hash*
DefaultNSEC3HashCreator::create(uint8_t algorithm, uint16_t iterations,
                                const uint8_t* salt_data,
                                size_t salt_length) const
{
    return (new NSEC3HashRFC5155(algorithm, iterations,
                                 salt_data, salt_length));
}

void
setNSEC3HashCreator(const NSEC3HashCreator* new_creator) {
    creator = new_creator;
}

} // namespace dns
} // namespace isc
