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

#include <stdint.h>

#include <cassert>
#include <cstring>
#include <string>
#include <vector>

#include <boost/noncopyable.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/base32hex.h>
#include <util/hash/sha1.h>

#include <dns/name.h>
#include <dns/nsec3hash.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::util::hash;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {

/// \brief A derived class of \c NSEC3Hash that implements the standard hash
/// calculation specified in RFC5155.
///
/// Currently the only pre-defined algorithm in the RFC is SHA1.  So we don't
/// over-generalize it at the moment, and rather hardocde it and assume that
/// specific algorithm.
///
/// The implementation details are only open within this file, but to avoid
/// an accidental error in this implementation we explicitly make it non
/// copyable.
class NSEC3HashRFC5155 : boost::noncopyable, public NSEC3Hash {
private:
    // This is the algorithm number for SHA1/NSEC3 as defined in RFC5155.
    static const uint8_t NSEC3_HASH_SHA1 = 1;

public:
    NSEC3HashRFC5155(uint8_t algorithm, uint16_t iterations,
                     const vector<uint8_t>& salt) :
        algorithm_(algorithm), iterations_(iterations),
        salt_(salt), digest_(SHA1_HASHSIZE), obuf_(Name::MAX_WIRE)
    {
        if (algorithm_ != NSEC3_HASH_SHA1) {
            isc_throw(UnknownNSEC3HashAlgorithm, "Unknown NSEC3 algorithm: " <<
                      static_cast<unsigned int>(algorithm_));
        }
        SHA1Reset(&sha1_ctx_);
    }

    virtual std::string calculate(const Name& name) const;

    virtual bool match(const generic::NSEC3& nsec3) const;
    virtual bool match(const generic::NSEC3PARAM& nsec3param) const;
    bool match(uint8_t algorithm, uint16_t iterations,
               const vector<uint8_t>& salt) const;

private:
    const uint8_t algorithm_;
    const uint16_t iterations_;
    const vector<uint8_t> salt_;

    // The following members are placeholder of work place and don't hold
    // any state over multiple calls so can be mutable without breaking
    // constness.
    mutable SHA1Context sha1_ctx_;
    mutable vector<uint8_t> digest_;
    mutable OutputBuffer obuf_;
};

inline void
iterateSHA1(SHA1Context* ctx, const uint8_t* input, size_t inlength,
            const uint8_t* salt, size_t saltlen,
            uint8_t output[SHA1_HASHSIZE])
{
    SHA1Reset(ctx);
    SHA1Input(ctx, input, inlength);
    SHA1Input(ctx, salt, saltlen); // this works whether saltlen == or > 0
    SHA1Result(ctx, output);
}

string
NSEC3HashRFC5155::calculate(const Name& name) const {
    // We first need to normalize the name by converting all upper case
    // characters in the labels to lower ones.
    obuf_.clear();
    Name name_copy(name);
    name_copy.downcase();
    name_copy.toWire(obuf_);

    const uint8_t saltlen = salt_.size();
    const uint8_t* const salt = (saltlen > 0) ? &salt_[0] : NULL;
    uint8_t* const digest = &digest_[0];
    assert(digest_.size() == SHA1_HASHSIZE);

    iterateSHA1(&sha1_ctx_, static_cast<const uint8_t*>(obuf_.getData()),
                obuf_.getLength(), salt, saltlen, digest);
    for (unsigned int n = 0; n < iterations_; ++n) {
        iterateSHA1(&sha1_ctx_, digest, SHA1_HASHSIZE, salt, saltlen, digest);
    }

    return (encodeBase32Hex(digest_));
}

bool
NSEC3HashRFC5155::match(uint8_t algorithm, uint16_t iterations,
                        const vector<uint8_t>& salt) const
{
    return (algorithm_ == algorithm && iterations_ == iterations &&
            salt_.size() == salt.size() &&
            (salt_.empty() || memcmp(&salt_[0], &salt[0], salt_.size()) == 0));
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
                  const vector<uint8_t>& salt) {
    return (getNSEC3HashCreator()->create(algorithm, iterations, salt));
}

NSEC3Hash*
DefaultNSEC3HashCreator::create(const generic::NSEC3PARAM& param) const {
    return (new NSEC3HashRFC5155(param.getHashalg(), param.getIterations(),
                                 param.getSalt()));
}

NSEC3Hash*
DefaultNSEC3HashCreator::create(const generic::NSEC3& nsec3) const {
    return (new NSEC3HashRFC5155(nsec3.getHashalg(), nsec3.getIterations(),
                                 nsec3.getSalt()));
}

NSEC3Hash*
DefaultNSEC3HashCreator::create(uint8_t algorithm, uint16_t iterations,
                                const vector<uint8_t>& salt) const {
    return (new NSEC3HashRFC5155(algorithm, iterations, salt));
}

void
setNSEC3HashCreator(const NSEC3HashCreator* new_creator) {
    creator = new_creator;
}

} // namespace dns
} // namespace isc
