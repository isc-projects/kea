namespace {

const char* const ZoneUpdater_doc = "\
The base class to make updates to a single zone.\n\
\n\
On construction, each derived class object will start a\n\
\"transaction\" for making updates to a specific zone (this means a\n\
constructor of a derived class would normally take parameters to\n\
identify the zone to be updated). The underlying realization of a\n\
\"transaction\" will differ for different derived classes; if it uses\n\
a general purpose database as a backend, it will involve performing\n\
some form of \"begin transaction\" statement for the database.\n\
\n\
Updates (adding or deleting RRs) are made via add_r_rset() and\n\
delete_r_rset() methods. Until the commit() method is called the\n\
changes are local to the updater object. For example, they won't be\n\
visible via a ZoneFinder object except the one returned by the\n\
updater's own get_finder() method. The commit() completes the\n\
transaction and makes the changes visible to others.\n\
\n\
This class does not provide an explicit \"rollback\" interface. If\n\
something wrong or unexpected happens during the updates and the\n\
caller wants to cancel the intermediate updates, the caller should\n\
simply destruct the updater object without calling commit(). The\n\
destructor is supposed to perform the \"rollback\" operation,\n\
depending on the internal details of the derived class.\n\
\n\
This initial implementation provides a quite simple interface of\n\
adding and deleting RRs (see the description of the related methods).\n\
It may be revisited as we gain more experiences.\n\
\n\
";
/*
const char* const ZoneUpdater_getFinder_doc = "\
get_finder() -> ZoneFinder \n\
\n\
Return a finder for the zone being updated.\n\
\n\
The returned finder provides the functionalities of ZoneFinder for the\n\
zone as updates are made via the updater. That is, before making any\n\
update, the finder will be able to find all RRsets that exist in the\n\
zone at the time the updater is created. If RRsets are added or\n\
deleted via add_r_rset() or delete_r_rset(), this finder will find the\n\
added ones or miss the deleted ones respectively.\n\
\n\
The finder returned by this method is effective only while the updates\n\
are performed, i.e., from the construction of the corresponding\n\
updater until commit() is performed or the updater is destructed\n\
without commit. The result of a subsequent call to this method (or the\n\
use of the result) after that is undefined.\n\
\n\
A reference to a ZoneFinder for the updated zone\n\
\n\
";
*/
const char* const ZoneUpdater_addRRset_doc = "\
add_r_rset(rrset) -> void\n\
\n\
Add an RRset to a zone via the updater.\n\
\n\
- Whether the RR class is identical to that for the zone to be updated\n\
- Whether the RRset is not empty, i.e., it has at least one RDATA\n\
- Whether the RRset is not associated with an RRSIG, i.e., whether\n\
  get_r_rsig() on the RRset returns a NULL pointer.\n\
\n\
and otherwise does not check any oddity. For example, it doesn't check\n\
whether the owner name of the specified RRset is a subdomain of the\n\
zone's origin; it doesn't care whether or not there is already an\n\
RRset of the same name and RR type in the zone, and if there is,\n\
whether any of the existing RRs have duplicate RDATA with the added\n\
ones. If these conditions matter the calling application must examine\n\
the existing data beforehand using the ZoneFinder returned by\n\
get_finder().\n\
\n\
The validation requirement on the associated RRSIG is temporary. If we\n\
find it more reasonable and useful to allow adding a pair of RRset and\n\
its RRSIG RRset as we gain experiences with the interface, we may\n\
remove this restriction. Until then we explicitly check it to prevent\n\
accidental misuse.\n\
\n\
Conceptually, on successful call to this method, the zone will have\n\
the specified RRset, and if there is already an RRset of the same name\n\
and RR type, these two sets will be \"merged\". \"Merged\" means that\n\
a subsequent call to ZoneFinder.find() for the name and type will\n\
result in success and the returned RRset will contain all previously\n\
existing and newly added RDATAs with the TTL being the minimum of the\n\
two RRsets. The underlying representation of the \"merged\" RRsets may\n\
vary depending on the characteristic of the underlying data source.\n\
For example, if it uses a general purpose database that stores each RR\n\
of the same RRset separately, it may simply be a larger sets of RRs\n\
based on both the existing and added RRsets; the TTLs of the RRs may\n\
be different within the database, and there may even be duplicate RRs\n\
in different database rows. As long as the RRset returned via\n\
ZoneFinder.find() conforms to the concept of \"merge\", the actual\n\
internal representation is up to the implementation.\n\
\n\
This method must not be called once commit() is performed. If it calls\n\
after commit() the implementation must throw a DataSourceError\n\
exception.\n\
\n\
TodoAs noted above we may have to revisit the design details as we\n\
gain experiences:\n\
\n\
- we may want to check (and maybe reject) if there is already a\n\
  duplicate RR (that has the same RDATA).\n\
- we may want to check (and maybe reject) if there is already an RRset\n\
  of the same name and RR type with different TTL\n\
- we may even want to check if there is already any RRset of the same\n\
  name and RR type.\n\
- we may want to add an \"options\" parameter that can control the\n\
  above points\n\
- we may want to have this method return a value containing the\n\
  information on whether there's a duplicate, etc.\n\
\n\
Exceptions:\n\
  DataSourceError Called after commit(), RRset is invalid (see above),\n\
             internal data source error\n\
  std.bad_alloc Resource allocation failure\n\
\n\
Parameters:\n\
  rrset      The RRset to be added\n\
\n\
";

const char* const ZoneUpdater_deleteRRset_doc = "\
delete_r_rset(rrset) -> void\n\
\n\
Delete an RRset from a zone via the updater.\n\
\n\
Like add_r_rset(), the detailed semantics and behavior of this method\n\
may have to be revisited in a future version. The following are based\n\
on the initial implementation decisions.\n\
\n\
- Existing RRs that don't match any of the specified RDATAs will\n\
  remain in the zone.\n\
- Any RRs of the specified RRset that doesn't exist in the zone will\n\
  simply be ignored; the implementation of this method is not supposed\n\
  to check that condition.\n\
- The TTL of the RRset is ignored; matching is only performed by the\n\
  owner name, RR type and RDATA\n\
\n\
Ignoring the TTL may not look sensible, but it's based on the\n\
observation that it will result in more intuitive result, especially\n\
when the underlying data source is a general purpose database. See\n\
also DatabaseAccessor.delete_record_in_zone() on this point. It also\n\
matches the dynamic update protocol (RFC2136), where TTLs are ignored\n\
when deleting RRs.\n\
\n\
- Whether the RR class is identical to that for the zone to be updated\n\
- Whether the RRset is not empty, i.e., it has at least one RDATA\n\
- Whether the RRset is not associated with an RRSIG, i.e., whether\n\
  get_r_rsig() on the RRset returns a NULL pointer.\n\
\n\
This method must not be called once commit() is performed. If it calls\n\
after commit() the implementation must throw a DataSourceError\n\
exception.\n\
\n\
TodoAs noted above we may have to revisit the design details as we\n\
gain experiences:\n\
\n\
- we may want to check (and maybe reject) if some or all of the RRs\n\
  for the specified RRset don't exist in the zone\n\
- we may want to allow an option to \"delete everything\" for\n\
  specified name and/or specified name + RR type.\n\
- as mentioned above, we may want to include the TTL in matching the\n\
  deleted RRs\n\
- we may want to add an \"options\" parameter that can control the\n\
  above points\n\
- we may want to have this method return a value containing the\n\
  information on whether there's any RRs that are specified but don't\n\
  exit, the number of actually deleted RRs, etc.\n\
\n\
Exceptions:\n\
  DataSourceError Called after commit(), RRset is invalid (see above),\n\
             internal data source error\n\
  std.bad_alloc Resource allocation failure\n\
\n\
Parameters:\n\
  rrset      The RRset to be deleted\n\
\n\
";

const char* const ZoneUpdater_commit_doc = "\
commit() -> void\n\
\n\
Commit the updates made in the updater to the zone.\n\
\n\
This method completes the \"transaction\" started at the creation of\n\
the updater. After successful completion of this method, the updates\n\
will be visible outside the scope of the updater. The actual internal\n\
behavior will defer for different derived classes. For a derived class\n\
with a general purpose database as a backend, for example, this method\n\
would perform a \"commit\" statement for the database.\n\
\n\
This operation can only be performed at most once. A duplicate call\n\
must result in a DatasourceError exception.\n\
\n\
Exceptions:\n\
  DataSourceError Duplicate call of the method, internal data source\n\
             error\n\
\n\
";
} // unnamed namespace
