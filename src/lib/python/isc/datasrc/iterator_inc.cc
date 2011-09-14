namespace {

const char* const ZoneIterator_doc = "\
Read-only iterator to a zone.\n\
\n\
You can get an instance of (descendand of) ZoneIterator from\n\
DataSourceClient.get_iterator() method. The actual concrete\n\
implementation will be different depending on the actual data source\n\
used. This is the abstract interface.\n\
\n\
There's no way to start iterating from the beginning again or return.\n\
\n\
";

const char* const ZoneIterator_getNextRRset_doc = "\
get_next_r_rset() -> isc.dns.ConstRRset\n\
\n\
Get next RRset from the zone.\n\
\n\
This returns the next RRset in the zone as a shared pointer. The\n\
shared pointer is used to allow both accessing in-memory data and\n\
automatic memory management.\n\
\n\
Any special order is not guaranteed.\n\
\n\
While this can potentially throw anything (including standard\n\
allocation errors), it should be rare.\n\
\n\
Pointer to the next RRset or NULL pointer when the iteration gets to\n\
the end of the zone.\n\
\n\
";
} // unnamed namespace
