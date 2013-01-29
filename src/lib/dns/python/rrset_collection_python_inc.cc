namespace {
// Modifications
//   - libdns++ => isc.dns, libdatasrc => isc.datasrc
//   - note about the direct construction.
//   - add note about iteration
const char* const RRsetCollectionBase_doc = "\
Generic class to represent a set of RRsets.\n\
\n\
This is a generic container and the stored set of RRsets does not\n\
necessarily form a valid zone (e.g. there doesn't necessarily have to\n\
be an SOA at the \"origin\"). Instead, it will be used to represent a\n\
single zone for the purpose of zone loading/checking. It provides a\n\
simple find() method to find an RRset for the given name and type (and\n\
maybe class) and a way to iterate over all RRsets.\n\
\n\
    Note: in the initial version, iteration is not yet supported.\n\
\n\
See RRsetCollection for a simple isc.dns implementation. Other modules\n\
such as isc.datasrc will have another implementation.\n\
\n\
This base class cannot be directly instantiated.  Such an attempt will\n\
result in a TypeError exception.\n\
\n\
";

// Modifications
//   - ConstRRset => RRset
//   - NULL => None
//   - added types of params
const char* const RRsetCollectionBase_find_doc = "\
find(name, rrclass, rrtype) -> isc.dns.RRset\n\
\n\
Find a matching RRset in the collection.\n\
\n\
Returns the RRset in the collection that exactly matches the given\n\
name, rrclass and rrtype. If no matching RRset is found, None is\n\
returned.\n\
\n\
This method's implementations currently are not specified to handle\n\
RRTypes such as RRSIG and NSEC3. This interface may be refined to\n\
clarify this point in the future, and perhaps, provide additional API\n\
for these RRType.\n\
\n\
As for RRSIG, there are some fundamental open questions. For example,\n\
it's not clear whether we want to return all RRSIGs of the given name\n\
covering any RR types (in which case, we need to figure out how), or\n\
we need to extend the interface so we can specify the covered type. A\n\
specific derived implementation may return something if type RRSIG is\n\
specified, but this is not specified here at the base class level. So,\n\
for RRSIGs the behavior should be assumed as undefined.\n\
\n\
As for NSEC3, it's not clear whether owner names (which included\n\
hashed labels) are the best choice of search key, because in many\n\
cases, what the application wants to find is an NSEC3 that has the\n\
hash of some particular \"normal\" domain names. Also, if the\n\
underlying implementation encapsulates a single zone, NSEC3 records\n\
conceptually belong to a separate name space, which may cause\n\
implementation difficulty.\n\
\n\
Behavior with meta types such as ANY and AXFR are also undefined. A\n\
specific implementation may return something for these. But, unlike\n\
the case of RRSIGs, these types of RRsets are not expected to be added\n\
to any implementation of collection in the first place (by the\n\
definition of \"meta types\"), so querying for such types is\n\
basically an invalid operation. The API doesn't require\n\
implementations to check this condition and reject it, so the behavior\n\
is undefined. This interface will not be refined in future versions\n\
for these meta types.\n\
\n\
Exceptions:\n\
  RRsetCollectionError if find() results in some implementation-\n\
             specific error.\n\
\n\
Parameters:\n\
  name       (isc.dns.Name) The name of the RRset to search for.\n\
  rrtype     (isc.dns.RRType) The type of the RRset to search for.\n\
  rrclass    (isc.dns.RRClass) The class of the RRset to search for.\n\
\n\
Return Value(s): The RRset if found, None otherwise.\n\
";


// Modifications
//   - libdns++ => isc.dns
//   - remove STL
//   - MasterLoaderError => IscException
//   - added types of params
//  - input_stream => input, stream => bytes
const char* const RRsetCollection_doc = "\
Derived class implementation of RRsetCollectionBase for isc.dns module.\n\
\n\
RRsetCollection()\n\
\n\
    Constructor.\n\
\n\
    This constructor creates an empty collection without any data in\n\
    it. RRsets can be added to the collection with the add_rrset()\n\
    method.\n\
\n\
RRsetCollection(filename, origin, rrclass)\n\
\n\
    Constructor.\n\
\n\
    The origin and rrclass arguments are required for the zone\n\
    loading, but RRsetCollection itself does not do any validation,\n\
    and the collection of RRsets does not have to form a valid zone.\n\
    The constructor throws IscException if there is an error\n\
    during loading.\n\
\n\
    Parameters:\n\
      filename   (str) Name of a file containing a collection of RRs in the\n\
                 master file format (which may or may not form a valid\n\
                 zone).\n\
      origin     (isc.dns.Name) The zone origin.\n\
      rrclass    (isc.dns.RRClass) The zone class.\n\
\n\
RRsetCollection(input, origin, rrclass)\n\
\n\
    Constructor.\n\
\n\
    This constructor is similar to the previous one, but instead of\n\
    taking a filename to load a zone from, it takes a bytes object,\n\
    representing the zone contents in text.\n\
    The constructor throws IscException if there is an error\n\
    during loading.\n\
\n\
    Parameters:\n\
      input      (bytes) Textual representation of the zone.\n\
      origin     (isc.dns.Name) The zone origin.\n\
      rrclass    (isc.dns.RRClass) The zone class.\n\
\n\
";

// Modifications
//   - void => None
//   - InvalidParameter => ValueError
//   - remove ownership related points (doesn't apply here)
const char* const RRsetCollection_addRRset_doc = "\
add_rrset(rrset) -> None\n\
\n\
Add an RRset to the collection.\n\
\n\
Does not do any validation whether rrset belongs to a particular zone\n\
or not.\n\
\n\
It throws a ValueError exception if an rrset with the same\n\
class, type and name already exists.\n\
\n\
";

// Modifications
//   - ConstRRset => RRset
const char* const RRsetCollection_find_doc = "\
find(name, rrclass, rrtype) -> isc.dns.RRset\n\
\n\
Find a matching RRset in the collection.\n\
\n\
Returns the RRset in the collection that exactly matches the given\n\
name, rrclass and rrtype. If no matching RRset is found, None is\n\
returned.\n\
\n\
Parameters:\n\
  name       The name of the RRset to search for.\n\
  rrclass    The class of the RRset to search for.\n\
  rrtype     The type of the RRset to search for.\n\
\n\
Return Value(s): The RRset if found, None otherwise.\n\
";

// Modifications
//   //   - true/false => True/False
const char* const RRsetCollection_removeRRset_doc = "\
remove_rrset(name, rrclass, rrtype) -> bool\n\
\n\
Remove an RRset from the collection.\n\
\n\
RRset(s) matching the name, rrclass and rrtype are removed from the\n\
collection.\n\
\n\
True if a matching RRset was deleted, False if no such RRset exists.\n\
\n\
";
} // unnamed namespace
