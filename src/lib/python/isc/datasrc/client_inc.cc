namespace {

const char* const DataSourceClient_doc = "\
The base class of data source clients.\n\
\n\
This is the python wrapper for the abstract base class that defines\n\
the common interface for various types of data source clients. A data\n\
source client is a top level access point to a data source, allowing \n\
various operations on the data source such as lookups, traversing or \n\
updates.\n\
This class serves as both the factory and the main interface to those \n\
classes.\n\
\n\
The constructor takes two arguments; a type (string), and\n\
configuration data for a datasource client of that type. The configuration\n\
data is currently passed as a JSON in string form, and its contents depend\n\
on the type of datasource from the first argument. For instance, a\n\
datasource of type \"sqlite3\" takes the config \n\
{ \"database_file\": \"/var/example.org\" }\n\
We may in the future add support for passing configuration data,\n\
but right now we limit it to a JSON-formatted string\n\
\n\
The client class itself has limited focus and delegates \n\
the responsibility for these specific operations to other (c++) classes;\n\
in general methods of this class act as factories of these other classes.\n\
\n\
- InMemoryClient: A client of a conceptual data source that stores all\n\
  necessary data in memory for faster lookups\n\
- DatabaseClient: A client that uses a real database backend (such as\n\
  an SQL database). It would internally hold a connection to the\n\
  underlying database system.\n\
\n\
It is intentional that while the term these derived classes don't\n\
contain \"DataSource\" unlike their base class. It's also noteworthy\n\
that the naming of the base class is somewhat redundant because the\n\
namespace datasrc would indicate that it's related to a data source.\n\
The redundant naming comes from the observation that namespaces are\n\
often omitted with using directives, in which case \"Client\" would be\n\
too generic. On the other hand, concrete derived classes are generally\n\
not expected to be referenced directly from other modules and\n\
applications, so we'll give them more concise names such as\n\
InMemoryClient. A single DataSourceClient object is expected to handle\n\
only a single RR class even if the underlying data source contains\n\
records for multiple RR classes. Likewise, (when we support views) a\n\
DataSourceClient object is expected to handle only a single view.\n\
\n\
If the application uses multiple threads, each thread will need to\n\
create and use a separate DataSourceClient. This is because some\n\
database backend doesn't allow multiple threads to share the same\n\
connection to the database.\n\
\n\
For a client using an in memory backend, this may result in having a\n\
multiple copies of the same data in memory, increasing the memory\n\
footprint substantially. Depending on how to support multiple CPU\n\
cores for concurrent lookups on the same single data source (which is\n\
not fully fixed yet, and for which multiple threads may be used), this\n\
design may have to be revisited. This class (and therefore its derived\n\
classes) are not copyable. This is because the derived classes would\n\
generally contain attributes that are not easy to copy (such as a\n\
large size of in memory data or a network connection to a database\n\
server). In order to avoid a surprising disruption with a naive copy\n\
it's prohibited explicitly. For the expected usage of the client\n\
classes the restriction should be acceptable.\n\
\n\
Todo: This class is still not complete. It will need more factory\n\
methods, e.g. for (re)loading a zone.\n\
";

const char* const DataSourceClient_findZone_doc = "\
find_zone(name) -> (code, ZoneFinder)\n\
\n\
Returns a ZoneFinder for a zone that best matches the given name.\n\
\n\
code: The result code of the operation (integer).\n\
- DataSourceClient.SUCCESS: A zone that gives an exact match is found\n\
- DataSourceClient.PARTIALMATCH: A zone whose origin is a super domain of name\n\
  is found (but there is no exact match)\n\
- DataSourceClient.NOTFOUND: For all other cases.\n\
ZoneFinder: ZoneFinder object for the found zone if one is found;\n\
otherwise None.\n\
\n\
Any internal error will be raised as an isc.datasrc.Error exception\n\
\n\
Parameters:\n\
  name       A domain name for which the search is performed.\n\
\n\
Return Value(s): A tuple containing a result value and a ZoneFinder object or\n\
None\n\
";

const char* const DataSourceClient_createZone_doc = "\
create_zone(name) -> bool\n\
\n\
Create a zone in the data source.\n\
\n\
Creates a new (empty) zone in the data source backend, which can\n\
subsequently be filled with data (through get_updater()).\n\
\n\
Note: This is a tentative API, and this method is likely to change or\n\
be removed in the near future. For that reason, it currently provides\n\
a default implementation that throws NotImplemented.\n\
\n\
Apart from the two exceptions mentioned below, in theory this call can\n\
throw anything, depending on the implementation of the datasource\n\
backend.\n\
\n\
Exceptions:\n\
  NotImplemented If the datasource backend does not support direct\n\
             zone creation.\n\
  DataSourceError If something goes wrong in the data source while\n\
             creating the zone.\n\
\n\
Parameters:\n\
  name       The (fully qualified) name of the zone to create\n\
\n\
Return Value(s): True if the zone was added, False if it already\n\
existed\n\
";

const char* const DataSourceClient_getIterator_doc = "\
get_iterator(name, separate_rrs=False) -> ZoneIterator\n\
\n\
Returns an iterator to the given zone.\n\
\n\
This allows for traversing the whole zone. The returned object can\n\
provide the RRsets one by one.\n\
\n\
This throws isc.datasrc.Error when the zone does not exist in the\n\
datasource, or when an internal error occurs.\n\
\n\
The default implementation throws isc.datasrc.NotImplemented. This allows for\n\
easy and fast deployment of minimal custom data sources, where the\n\
user/implementator doesn't have to care about anything else but the\n\
actual queries. Also, in some cases, it isn't possible to traverse the\n\
zone from logic point of view (eg. dynamically generated zone data).\n\
\n\
It is not fixed if a concrete implementation of this method can throw\n\
anything else.\n\
\n\
Parameters:\n\
  isc.dns.Name The name of zone apex to be traversed. It doesn't do\n\
               nearest match as find_zone.\n\
  separate_rrs If true, the iterator will return each RR as a\n\
               new RRset object. If false, the iterator will\n\
               combine consecutive RRs with the name and type\n\
               into 1 RRset. The capitalization of the RRset will\n\
               be that of the first RR read, and TTLs will be\n\
               adjusted to the lowest one found.\n\
\n\
Return Value(s): Pointer to the iterator.\n\
";

const char* const DataSourceClient_getUpdater_doc = "\
get_updater(name, replace, journaling=False) -> ZoneUpdater\n\
\n\
Return an updater to make updates to a specific zone.\n\
\n\
The RR class of the zone is the one that the client is expected to\n\
handle (see the detailed description of this class).\n\
\n\
If the specified zone is not found via the client, a None object will\n\
be returned; in other words a completely new zone cannot be created\n\
using an updater. It must be created beforehand (even if it's an empty\n\
placeholder) in a way specific to the underlying data source.\n\
\n\
Conceptually, the updater will trigger a separate transaction for\n\
subsequent updates to the zone within the context of the updater (the\n\
actual implementation of the \"transaction\" may vary for the specific\n\
underlying data source). Until commit() is performed on the updater,\n\
the intermediate updates won't affect the results of other methods\n\
(and the result of the object's methods created by other factory\n\
methods). Likewise, if the updater is destructed without performing\n\
commit(), the intermediate updates will be effectively canceled and\n\
will never affect other methods.\n\
\n\
If the underlying data source allows concurrent updates, this method\n\
can be called multiple times while the previously returned updater(s)\n\
are still active. In this case each updater triggers a different\n\
\"transaction\". Normally it would be for different zones for such a\n\
case as handling multiple incoming AXFR streams concurrently, but this\n\
interface does not even prohibit an attempt of getting more than one\n\
updater for the same zone, as long as the underlying data source\n\
allows such an operation (and any conflict resolution is left to the\n\
specific implementation).\n\
\n\
If replace is true, any existing RRs of the zone will be deleted on\n\
successful completion of updates (after commit() on the updater); if\n\
it's false, the existing RRs will be intact unless explicitly deleted\n\
by delete_rrset() on the updater.\n\
\n\
A data source can be \"read only\" or can prohibit partial updates. In\n\
such cases this method will result in an isc.datasrc.NotImplemented exception\n\
unconditionally or when replace is false).\n\
\n\
If journaling is True, the data source should store a journal of\n\
changes. These can be used later on by, for example, IXFR-out.\n\
However, the parameter is a hint only. It might be unable to store\n\
them and they would be silently discarded. Or it might need to store\n\
them no matter what (for example a git-based data source would store\n\
journal implicitly). When the journaling is True, it requires that the\n\
following update be formatted as IXFR transfer (SOA to be removed,\n\
bunch of RRs to be removed, SOA to be added, bunch of RRs to be added,\n\
and possibly repeated). However, it is not required that the updater\n\
checks that. If it is False, it must not require so and must accept\n\
any order of changes.\n\
\n\
We don't support erasing the whole zone (by replace being True) and\n\
saving a journal at the same time. In such situation, isc.datasrc.Error\n\
is thrown.\n\
\n\
Exceptions:\n\
  isc.datasrc. NotImplemented The underlying data source does not support\n\
               updates.\n\
  isc.datasrc.Error Internal error in the underlying data source.\n\
\n\
Parameters:\n\
  name       The zone name to be updated\n\
  replace    Whether to delete existing RRs before making updates\n\
  journaling The zone updater should store a journal of the changes.\n\
\n\
";

// Modifications from C++ doc:
//   pointer -> (removed)
//   Null -> None
//   exception types
const char* const DataSourceClient_getJournalReader_doc = "\
get_journal_reader(zone, begin_serial, end_serial) ->\n\
   (int, ZoneJournalReader)\n\
\n\
Return a journal reader to retrieve differences of a zone.\n\
\n\
A derived version of this method creates a concrete ZoneJournalReader\n\
object specific to the underlying data source for the specified name\n\
of zone and differences between the versions specified by the\n\
beginning and ending serials of the corresponding SOA RRs. The RR\n\
class of the zone is the one that the client is expected to handle\n\
(see the detailed description of this class).\n\
\n\
Note that the SOA serials are compared by the semantics of the serial\n\
number arithmetic. So, for example, begin_serial can be larger than\n\
end_serial as bare unsigned integers. The underlying data source\n\
implementation is assumed to keep track of sufficient history to\n\
identify (if exist) the corresponding difference between the specified\n\
versions.\n\
\n\
This method returns the result as a pair of a result code and a\n\
ZoneJournalReader object. On success, the result code is\n\
SUCCESS and the object must not be None; otherwise the result code is\n\
something other than SUCCESS and the object must be None.\n\
\n\
If the specified zone is not found in the data source, the result code\n\
is NO_SUCH_ZONE. Otherwise, if specified range of difference for the\n\
zone is not found in the data source, the result code is\n\
NO_SUCH_VERSION.\n\
\n\
Handling differences is an optional feature of data source. If the\n\
underlying data source does not support difference handling, this\n\
method for that type of data source can throw an exception of class\n\
isc.datasrc.NotImplemented.\n\
\n\
Exceptions:\n\
  isc.datasrc.NotImplemented The data source does not support differences.\n\
  isc.datasrc.Error Other operational errors at the data source level.\n\
  SystemError An unexpected error in the backend C++ code.  Either a rare\n\
              system error such as short memory or an implementation bug.\n\
\n\
Parameters:\n\
  zone       The name of the zone for which the difference should be\n\
             retrieved.\n\
  begin_serial The SOA serial of the beginning version of the\n\
             differences.\n\
  end_serial The SOA serial of the ending version of the differences.\n\
\n\
Return Value(s): A pair of result code and a ZoneJournalReader object\n\
(which can be None)\n                                                  \
";
} // unnamed namespace
