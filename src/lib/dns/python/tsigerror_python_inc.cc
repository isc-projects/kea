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

namespace {
const char* const TSIGError_doc = "\n\
TSIG errors.\n\
\n\
\n\
The TSIGError class objects represent standard errors related to TSIG\n\
protocol operations as defined in related specifications, mainly in\n\
RFC2845.\n\
\n\
TSIGError(error_code)\n\
\n\
Constructor from the code value.\n\
\n\
Exceptions:\n\
  None: \n\
\n\
Parameters:\n\
  error_code: The underlying 16-bit error code value of the TSIGError.\n\
\n\
TSIGError(rcode)\n\
\n\
Constructor from Rcode.\n\
\n\
As defined in RFC2845, error code values from 0 to 15 (inclusive) are\n\
derived from the DNS RCODEs, which are represented via the Rcode class\n\
in this library. This constructor works as a converter from these\n\
RCODEs to corresponding TSIGError objects.\n\
\n\
Exceptions:\n\
  ValueError: Given rcode is not convertible to TSIGErrors.\n\
\n\
Parameters:\n\
  rcode: the Rcode from which the TSIGError should be derived.\n\
\n\
";
const char* const TSIGError_getCode_doc = "get_code() -> integer\n\
\n\
Returns the TSIGCode error code value.\n\
\n\
Exceptions:\n\
  None: \n\
\n\
Return Value(s):\n\
  The underlying code value corresponding to the TSIGError.\n\
";
const char* const TSIGError_toText_doc = "to_text() -> string\n\
\n\
Convert the TSIGError to a string.\n\
\n\
For codes derived from RCODEs up to 15, this method returns the same\n\
string as Rcode.to_text() for the corresponding code. For other pre-\n\
defined code values (see TSIGError.CodeValue), this method returns a\n\
string representation of the \"mnemonic' used for the enum and\n\
constant objects as defined in RFC2845. For example, the string for\n\
code value 16 is \"BADSIG\", etc. For other code values it returns a\n\
string representation of the decimal number of the value, e.g. \"32\",\n\
\"100\", etc.\n\
\n\
Exceptions:\n\
  None\n\
\n\
Return Value(s):\n\
  A string representation of the TSIGError.\n\
";
const char* const TSIGError_toRcode_doc = "to_rcode() -> Rcode\n\
\n\
Convert the TSIGError to a Rcode.\n\
\n\
This method returns an Rcode object that is corresponding to the TSIG\n\
error. The returned Rcode is expected to be used by a verifying server\n\
to specify the RCODE of a response when TSIG verification fails.\n\
\n\
Specifically, this method returns Rcode.NOTAUTH() for the TSIG\n\
specific errors, BADSIG, BADKEY, BADTIME, as described in RFC2845. For\n\
errors derived from the standard Rcode (code 0-15), it returns the\n\
corresponding Rcode. For others, this method returns Rcode.SERVFAIL()\n\
as a last resort.\n\
\n\
Exceptions:\n\
  None: \n\
\n\
";
}
