namespace {
const char* const Message_fromWire_doc = "\
from_wire(data, options=PARSE_DEFAULT)\n\
\n\
(Re)build a Message object from wire-format data.\n\
\n\
This method parses the given wire format data to build a complete\n\
Message object. On success, the values of the header section fields\n\
can be accessible via corresponding get methods, and the question and\n\
following sections can be accessible via the corresponding iterators.\n\
If the message contains an EDNS or TSIG, they can be accessible via\n\
get_edns() and get_tsig_record(), respectively.\n\
\n\
This Message must be in the PARSE mode.\n\
\n\
This method performs strict validation on the given message based on\n\
the DNS protocol specifications. If the given message data is invalid,\n\
this method throws an exception (see the exception list).\n\
\n\
By default, this method combines RRs of the same name, RR type and RR\n\
class in a section into a single RRset, even if they are interleaved\n\
with a different type of RR (though it would be a rare case in\n\
practice). If the PRESERVE_ORDER option is specified, it handles each\n\
RR separately, in the appearing order, and converts it to a separate\n\
RRset (so this RRset should contain exactly one Rdata). This mode will\n\
be necessary when the higher level protocol is ordering conscious. For\n\
example, in AXFR and IXFR, the position of the SOA RRs are crucial.\n\
\n\
Exceptions:\n\
  InvalidMessageOperation Message is in the RENDER mode\n\
  DNSMessageFORMERR The given message data is syntactically\n\
  MessageTooShort The given data is shorter than a valid header\n\
             section\n\
  Others     Name, Rdata, and EDNS classes can also throw\n\
\n\
Parameters:\n\
  data       A byte object of the wire data\n\
  options    Parse options\n\
\n\
";
} // unnamed namespace
