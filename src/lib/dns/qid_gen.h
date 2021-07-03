// Copyright (C) 2011-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// qid_gen defines a generator for query id's
//
// We probably want to merge this with the weighted random in the nsas
// (and other parts where we need randomness, perhaps another thing
// for a general libutil?)

#ifndef QID_GEN_H
#define QID_GEN_H

#include <cryptolink/crypto_rng.h>
#include <stdint.h>

namespace isc {
namespace dns {

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
};

} // namespace dns
} // namespace isc

#endif // QID_GEN_H
