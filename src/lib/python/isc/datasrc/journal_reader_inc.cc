namespace {
const char* const ZoneJournalReader_doc = "\
The base class for retrieving differences between two versions of a\n\
zone.\n\
\n\
On construction, each derived class object will internally set up\n\
retrieving sequences of differences between two specific version of a\n\
specific zone managed in a particular data source. So the constructor\n\
of a derived class would normally take parameters to identify the zone\n\
and the two versions for which the differences should be retrieved.\n\
See DataSourceClient.get_journal_reader for more concrete details used\n\
in this API.\n\
\n\
Once constructed, an object of this class will act like an iterator\n\
over the sequences. Every time the get_next_diff() method is called it\n\
returns one element of the differences in the form of an RRset until\n\
it reaches the end of the entire sequences.\n\
\n\
";

// Modifications from C++ doc:
//   ConstRRsetPtr -> RRset
//   Null -> None
//   InvalidOperation -> ValueError
const char* const ZoneJournalReader_getNextDiff_doc = "\
get_next_diff() -> isc.dns.RRset\n\
\n\
Return the next difference RR of difference sequences.\n\
\n\
In this API, the difference between two versions of a zone is\n\
conceptually represented as IXFR-style difference sequences: Each\n\
difference sequence is a sequence of RRs: an older version of SOA (to\n\
be deleted), zero or more other deleted RRs, the post-transaction SOA\n\
(to be added), and zero or more other added RRs. (Note, however, that\n\
the underlying data source implementation may or may not represent the\n\
difference in straightforward realization of this concept. The mapping\n\
between the conceptual difference and the actual implementation is\n\
hidden in each derived class).\n\
\n\
This method provides an application with a higher level interface to\n\
retrieve the difference along with the conceptual model: the\n\
ZoneJournalReader object iterates over the entire sequences from the\n\
beginning SOA (which is to be deleted) to one of the added RR of with\n\
the ending SOA, and each call to this method returns one RR in the\n\
form of an RRset that contains exactly one RDATA in the order of the\n\
sequences.\n\
\n\
Note that the ordering of the sequences specifies the semantics of\n\
each difference: add or delete. For example, the first RR is to be\n\
deleted, and the last RR is to be added. So the return value of this\n\
method does not explicitly indicate whether the RR is to be added or\n\
deleted.\n\
\n\
This method ensures the returned RRset represents an RR, that is, it\n\
contains exactly one RDATA. However, it does not necessarily ensure\n\
that the resulting sequences are in the form of IXFR-style. For\n\
example, the first RR is supposed to be an SOA, and it should normally\n\
be the case, but this interface does not necessarily require the\n\
derived class implementation ensure this. Normally the differences are\n\
expected to be stored using this API (via a ZoneUpdater object), and\n\
as long as that is the case and the underlying implementation follows\n\
the requirement of the API, the result of this method should be a\n\
valid IXFR-style sequences. So this API does not mandate the almost\n\
redundant check as part of the interface. If the application needs to\n\
make it sure 100%, it must check the resulting sequence itself.\n\
\n\
Once the object reaches the end of the sequences, this method returns\n\
None. Any subsequent call will result in an exception of class\n\
ValueError.\n\
\n\
Exceptions:\n\
  ValueError The method is called beyond the end of the\n\
             difference sequences.\n\
  isc.datasrc.Error Underlying data is broken and the RR cannot be\n\
             created or other low level data source error.\n\
\n\
Return Value(s): An RRset that contains one RDATA corresponding to the\n\
next difference in the sequences.\n\
";
} // unnamed namespace
