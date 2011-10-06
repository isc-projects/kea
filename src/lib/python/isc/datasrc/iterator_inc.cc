namespace {

const char* const ZoneIterator_doc = "\
Read-only iterator to a zone.\n\
\n\
You can get an instance of the ZoneIterator from\n\
DataSourceClient.get_iterator() method. The actual concrete\n\
c++ implementation will be different depending on the actual data source\n\
used. This is the abstract interface.\n\
\n\
There's no way to start iterating from the beginning again or return.\n\
\n\
The ZoneIterator is a python iterator, and can be iterated over directly.\n\
";

const char* const ZoneIterator_getNextRRset_doc = "\
get_next_rrset() -> isc.dns.RRset\n\
\n\
Get next RRset from the zone.\n\
\n\
This returns the next RRset in the zone.\n\
\n\
Any special order is not guaranteed.\n\
\n\
While this can potentially throw anything (including standard\n\
allocation errors), it should be rare.\n\
\n\
Pointer to the next RRset or None pointer when the iteration gets to\n\
the end of the zone.\n\
\n\
Raises an isc.datasrc.Error exception if it is called again after returning\n\
None\n\
";
} // unnamed namespace
