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

// qid_gen defines a generator for query id's
//
// We probably want to merge this with the weighted random in the nsas
// (and other parts where we need randomness, perhaps another thing
// for a general libutil?)

#ifndef QID_GEN_H
#define QID_GEN_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

namespace isc {
namespace util {
namespace random {

/// This class generates Qids for outgoing queries
///
/// It is implemented as a singleton; the public way to access it
/// is to call getInstance()->generateQid().
///
/// It automatically seeds it with the current time when it is first
/// used.
class QidGenerator {
public:
    /// \brief Returns the singleton instance of the QidGenerator
    ///
    /// Returns a reference to the singleton instance of the generator
    static QidGenerator& getInstance();

    /// \brief Default constructor
    ///
    /// It is recommended that getInstance is used rather than creating
    /// separate instances of this class.
    ///
    /// The constructor automatically seeds the generator with the
    /// current time.
    QidGenerator();

    /// Generate a Qid
    ///
    /// \return A random Qid
    uint16_t generateQid();

    /// \brief Seeds the QidGenerator (based on the current time)
    ///
    /// This is automatically called by the constructor
    void seed();

private:
    // "Mersenne Twister: A 623-dimensionally equidistributed
    // uniform pseudo-random number generator", Makoto Matsumoto and
    // Takuji Nishimura, ACM Transactions on Modeling and Computer
    // Simulation: Special Issue on Uniform Random Number Generation,
    // Vol. 8, No. 1, January 1998, pp. 3-30.
    //
    // mt19937 is an implementation of one of the pseudo random
    // generators described in this paper.
    boost::mt19937 generator_;

    // For qid's we want a uniform distribution
    boost::uniform_int<> dist_;

    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > vgen_;
};


} // namespace random
} // namespace util
} // namespace isc

#endif // QID_GEN_H
