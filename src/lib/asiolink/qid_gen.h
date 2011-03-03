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

#ifndef __QID_GEN_
#define __QID_GEN_

#include <dns/message.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>


namespace asiolink {
    
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
    /// Initializes a new instance if there is none.
    static QidGenerator* getInstance();

    /// \brief Cleans up the singleton instance.
    ///
    /// This is added so that we can run memory checkers and
    /// not get complaints about leaking data. If getInstance()
    /// is called after cleanInstance, a new one would be created.
    static void cleanInstance();

    /// Generate a Qid
    ///
    /// \return A random Qid
    isc::dns::qid_t generateQid();

    /// \brief Seeds the QidGenerator (based on the current time)
    ///
    /// This is automatically called when getInstance() is called
    /// the first time.
    void seed();
    
private:
    QidGenerator();
    boost::mt19937 generator;
    boost::uniform_int<> dist;
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > vgen;
};


} // namespace asiolink

#endif // __QID_GEN_
