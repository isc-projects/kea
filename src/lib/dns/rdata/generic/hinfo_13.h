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

// BEGIN_HEADER_GUARD
#include <stdint.h>

#include <string>

#include <dns/name.h>
#include <dns/rdata.h>
#include <util/buffer.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

/// \brief \c HINFO class represents the HINFO rdata defined in
/// RFC1034, RFC1035
///
/// This class implements the basic interfaces inherited from the
/// \c rdata::Rdata class, and provides accessors specific to the
/// HINFO rdata.
class HINFO : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    // HINFO specific methods
    const std::string& getCPU() const;
    const std::string& getOS() const;

private:
    /// Skip the left whitespaces of the input string
    ///
    /// If \c optional argument is \c true and no spaces occur at the
    /// current location, then nothing happens. If \c optional is
    /// \c false and no spaces occur at the current location, then
    /// the \c InvalidRdataText exception is thrown.
    ///
    /// \param input_str The input string
    /// \param input_iterator From which the skipping started
    /// \param optional If true, the spaces are optionally skipped.
    void skipLeftSpaces(const std::string& input_str,
                        std::string::const_iterator& input_iterator,
                        bool optional);

    /// Helper template function for toWire()
    ///
    /// \param outputer Where to write data in
    template <typename T>
    void toWireHelper(T& outputer) const {
        outputer.writeUint8(cpu_.size());
        outputer.writeData(cpu_.c_str(), cpu_.size());

        outputer.writeUint8(os_.size());
        outputer.writeData(os_.c_str(), os_.size());
    }

    std::string cpu_;
    std::string os_;
};


// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
