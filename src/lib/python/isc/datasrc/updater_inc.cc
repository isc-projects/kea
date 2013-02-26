// Copyright (C) 2011,2013  Internet Systems Consortium, Inc. ("ISC")
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
Updates (adding or deleting RRs) are made via add_rrset() and\n\
delete_rrset() methods. Until the commit() method is called the\n\
changes are local to the updater object. For example, they won't be\n\
visible via a ZoneFinder object, but only by the updater's own find()\n\
method. The commit() completes the transaction and makes the changes\n\
visible to others.\n\
\n\
This class does not provide an explicit \"rollback\" interface. If\n\
something wrong or unexpected happens during the updates and the\n\
caller wants to cancel the intermediate updates, the caller should\n\
simply destroy the updater object without calling commit(). The\n\
destructor is supposed to perform the \"rollback\" operation,\n\
depending on the internal details of the derived class.\n\
\n\
This initial implementation provides a quite simple interface of\n\
adding and deleting RRs (see the description of the related methods).\n\
It may be revisited as we gain more experiences.\n\
\n\
";

const char* const ZoneUpdater_addRRset_doc = "\
add_rrset(rrset) -> No return value\n\
\n\
Add an RRset to a zone via the updater.\n\
It performs a few basic checks:\n\
- Whether the RR class is identical to that for the zone to be updated\n\
- Whether the RRset is not empty, i.e., it has at least one RDATA\n\
- Whether the RRset is not associated with an RRSIG, i.e., whether\n\
  get_rrsig() on the RRset returns a NULL pointer.\n\
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
after commit() the implementation must throw a isc.datasrc.Error\n\
exception.\n\
\n\
Implementations of ZoneUpdater may not allow adding or deleting RRsets\n\
after get_rrset_collection() is called. In this case, implementations\n\
throw an InvalidOperation exception.\n\
\n\
Todo As noted above we may have to revisit the design details as we\n\
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
  isc.datasrc.Error Called after commit(), RRset is invalid (see above),\n\
                    internal data source error, or wrapper error\n\
\n\
Parameters:\n\
  rrset      The RRset to be added\n\
\n\
";

const char* const ZoneUpdater_deleteRRset_doc = "\
delete_rrset(rrset) -> No return value\n\
\n\
Delete an RRset from a zone via the updater.\n\
\n\
Like add_rrset(), the detailed semantics and behavior of this method\n\
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
also the c++ documentation of DatabaseAccessor::DeleteRecordInZone()\n\
on this point. It also matches the dynamic update protocol (RFC2136),\n\
where TTLs are ignored when deleting RRs.\n\
\n\
This method performs a limited level of validation on the specified\n\
RRset:\n\
- Whether the RR class is identical to that for the zone to be updated\n\
- Whether the RRset is not empty, i.e., it has at least one RDATA\n\
- Whether the RRset is not associated with an RRSIG\n\
\n\
This method must not be called once commit() is performed. If it calls\n\
after commit() the implementation must throw a isc.datasrc.Error\n\
exception.\n\
\n\
Implementations of ZoneUpdater may not allow adding or deleting RRsets\n\
after get_rrset_collection() is called. In this case, implementations\n\
throw an InvalidOperation exception.\n\
\n\
Todo: As noted above we may have to revisit the design details as we\n\
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
  isc.datasrc.Error Called after commit(), RRset is invalid (see above),\n\
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
must result in a isc.datasrc.Error exception.\n\
\n\
Exceptions:\n\
  isc.datasrc.Error Duplicate call of the method, internal data source\n\
             error, or wrapper error\n\\n\
\n\
";

// Modifications:
// -  remove reference to isc.datasrc.RRsetCollectionBase (hidden for Python
//    wrapper)
const char* const ZoneUpdater_getRRsetCollection_doc = "\
get_rrset_collection() -> isc.dns.RRsetCollectionBase \n\
\n\
Return an RRsetCollection for the updater.\n\
\n\
This method returns an RRsetCollection for the updater, implementing\n\
the isc.dns.RRsetCollectionBase interface. Typically, the returned\n\
RRsetCollection is a singleton for its ZoneUpdater. The returned\n\
RRsetCollection object must not be used after its corresponding\n\
ZoneUpdater has been destroyed. The returned RRsetCollection object\n\
may be used to search RRsets from the ZoneUpdater. The actual\n\
RRsetCollection returned has a behavior dependent on the ZoneUpdater\n\
implementation.\n\
\n\
The behavior of the RRsetCollection is similar to the behavior of the\n\
Zonefinder returned by get_finder(). In fact, it's redundant in a\n\
sense because one can implement the dns.RRsetCollectionBase interface\n\
using an updater and get_finder() interface (unless it's expected to\n\
support zone iteration, and the initial implementation of the\n\
RRsetCollection returned by this method doesn't support it). We\n\
still provide it as an updater's method so it will be easier for an\n\
updater implementation to customize the RRsetCollection\n\
implementation, and also for making it easy to impose restrictions\n\
described below.\n\
\n\
Specific data sources may have special restrictions. That's especially\n\
the case for database-based data sources. Such restrictions may also\n\
result in limiting the usage of the RRsetCollection as described in\n\
the following paragraphs. A specific updater implementation may\n\
provide more flexible behavior, but applications using this interface\n\
must assume the most restricted case unless it knows it uses a\n\
particular specialized updater implementation that loosens specific\n\
restrictions.\n\
\n\
- An application must not add or delete RRsets after\n\
  get_rrset_collection() is called.\n\
- An application must not use the returned collection from\n\
  get_rrset_collection() once commit() is called on the updater that\n\
  generates the collection.\n\
\n\
Implementations of ZoneUpdater may not allow adding or deleting RRsets\n\
after get_rrset_collection() is called. This is because if an\n\
iterator of the collection is being used at that time the modification\n\
to the zone may break an internal assumption of the iterator and may\n\
result in unexpected behavior. Also, the iterator may conceptually\n\
hold a \"reader lock\" of the zone (in an implementation dependent\n\
manner), which would prevent the addition or deletion, surprising the\n\
caller (who would normally expect it to succeed).\n\
\n\
Implementations of ZoneUpdater may disable a previously returned\n\
RRsetCollection after commit() is called. This is because the returned\n\
RRsetCollection may internally rely on the conceptual transaction of\n\
the updater that generates the collection (which would be literally\n\
the case for database-based data sources), and once the transaction is\n\
committed anything that relies on it won't be valid. If an\n\
RRsetCollection is disabled, using methods such as find() and using\n\
its iterator would cause an exception to be thrown.\n\
\n\
";
} // unnamed namespace
