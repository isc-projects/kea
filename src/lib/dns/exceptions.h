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

#ifndef __EXCEPTIONS_HH
#define __EXCEPTIONS_HH 1

//
// Quick hack exception classes for rapid prototyping.  This shouldn't belong
// here.  Also, exceptions should inherit from standard exception classes.

namespace isc {
class ISCException {};
class ISCUnexpected : public ISCException {};
class ISCNoSpace : public ISCException {};
class ISCInvalidAddressString : public ISCException {};
class ISCBufferInvalidPosition : public ISCException {};

namespace dns {
class DNSException {};
class DNSEmptyLabel : public DNSException {};
class DNSNameTooLong : public DNSException {};
class DNSLabelTooLong : public DNSException {};
class DNSBadEscape : public DNSException {};
class DNSBadLabelType : public DNSException {};
class DNSInvalidRRClass : public DNSException {};
class DNSInvalidRRType : public DNSException {};
class DNSRRtypeMismatch : public DNSException {};
class DNSInvalidWireRdata : public DNSException {};
class DNSNoMessageBuffer : public DNSException {};
class DNSNoNameCompressor : public DNSException {};
class DNSNoNameDecompressor : public DNSException {};
class DNSNoMessageParser : public DNSException {};
class DNSInvalidMessageSection : public DNSException {};
class DNSInvalidRendererPosition : public DNSException {};
class DNSMessageTooShort : public DNSException {};
class DNSCharStringTooLong : public DNSException {};
class DNSNameDecompressionProhibited : public DNSException {};
class DNSNameBadPointer : public DNSException {};
class DNSInvalidRdata : public DNSException {};
}
}
#endif  // __EXCEPTIONS_HH

// Local Variables: 
// mode: c++
// End: 
