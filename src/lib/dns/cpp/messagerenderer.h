// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __MESSAGERENDERER_H
#define __MESSAGERENDERER_H 1

namespace isc {
namespace dns {
// forward declarations
class OutputBuffer;
class Name;
class MessageRendererImpl;

///
/// \brief The \c MessageRenderer class encapsulates implementation details
/// of rendering a DNS message into a buffer in wire format.
///
/// In effect, it's simply responsible for name compression at least in the
/// current implementation.  A \c MessageRenderer class object manages the
/// positions of names rendered in a buffer and uses that information to render
/// subsequent names with compression.
///
/// This class is mainly intended to be used as a helper for a more
/// comprehensive \c Message class internally; normal applications won't have
/// to care about this class.
///
/// A \c MessageRenderer class object is constructed with a \c OutputBuffer
/// object, which is the buffer into which the rendered data will be written.
/// Normally the buffer is expected to be empty on construction, but it doesn't
/// have to be so; the \c MessageRenderer object will start rendering from the
/// end of the buffer at the time of construction.  However, if the
/// pre-existing portion of the buffer contains DNS names, these names won't
/// be considered for name compression.
///
/// Once a \c MessageRenderer object is constructed with a buffer, it is
/// generally expected that all rendering operations are performed via the
/// \c MessageRenderer object.  If the application modifies the buffer in
/// parallel with the \c MessageRenderer, the result will be undefined.
///
/// Note to developers: we introduced a separate class for name compression
/// because previous benchmark with BIND9 showed compression affects overall
/// response performance very much.  By having a separate class dedicated for
/// this purpose, we'll be able to change the internal implementation of name
/// compression in the future without affecting other part of the API and
/// implementation.  For the same reason, we adopt the "pimpl" idiom in the
/// class definition (i.e., using a pointer to a \c MessageRendererImpl class,
/// which is defined with the class implementation, not in the header file):
/// we may want to modify the compression implementation without modifying the
/// header file thereby requesting rebuild the package.
///
/// Furthermore, we may eventually want to allow other developers to develop
/// and use their own compression implementation.  Should such a case become
/// realistic, we may want to make the \c MessageRendererImpl class an abstract
/// base class and let concrete derived classes have their own implementations.
/// At the moment we don't the strong need for it, so we rather avoid over
/// abstraction and keep the definition simpler.
class MessageRenderer {
public:
    ///
    /// \name Constructors and Destructor
    //@{
    /// \brief Constructor from an output buffer.
    ///
    /// \param buffer An \c OutputBuffer object to which wire format data is
    /// written.
    MessageRenderer(OutputBuffer& buffer);
    /// \brief The default destructor.
    ///
    /// The destructor does nothing on the given \c buffer on construction;
    /// in fact, it is expected that the user will use the resulting buffer
    /// for some post rendering purposes (e.g., send the data to the network).
    /// It's user's responsibility to do any necessary cleanup for the
    /// \c buffer.
    ~MessageRenderer();
    //@}

    ///
    /// \name Rendering Methods
    ///
    //@{
    /// \brief Write a \c Name object into the internal buffer in wire format,
    /// with or without name compression.
    ///
    /// If the optional parameter \c compress is \c true, this method tries to
    /// compress the \c name if possible, searching the entire message that has
    /// been rendered.  Otherwise name compression is omitted.  Its default
    /// value is \c true.
    ///
    /// Note: even if \c compress is \c true, the position of the \c name (and
    /// possibly its ancestor names) in the message is recorded and may be used
    /// for compressing subsequent names.
    ///
    /// \param name A \c Name object to be written.
    /// \param compress A boolean indicating whether to enable name compression.
    void writeName(const Name& name, bool compress = true);
private:
    MessageRendererImpl* impl_;
};
}
}
#endif // __MESSAGERENDERER_H

// Local Variables: 
// mode: c++
// End: 
