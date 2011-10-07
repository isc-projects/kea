namespace {
const char* const ZoneFinder_doc = "\
The base class to search a zone for RRsets.\n\
\n\
The ZoneFinder class is a wrapper for the c++ base class for representing an\n\
object that performs DNS lookups in a specific zone accessible via a\n\
data source. In general, different types of data sources (in-memory,\n\
database-based, etc) define their own derived c++ classes of ZoneFinder,\n\
implementing ways to retrieve the required data through the common\n\
interfaces declared in the base class. Each concrete ZoneFinder object\n\
is therefore (conceptually) associated with a specific zone of one\n\
specific data source instance.\n\
\n\
The origin name and the RR class of the associated zone are available\n\
via the get_origin() and get_class() methods, respectively.\n\
\n\
The most important method of this class is find(), which performs the\n\
lookup for a given domain and type. See the description of the method\n\
for details.\n\
\n\
It's not clear whether we should request that a zone finder form a\n\
\"transaction\", that is, whether to ensure the finder is not\n\
susceptible to changes made by someone else than the creator of the\n\
finder. If we don't request that, for example, two different lookup\n\
results for the same name and type can be different if other threads\n\
or programs make updates to the zone between the lookups. We should\n\
revisit this point as we gain more experiences.\n\
\n\
";

const char* const ZoneFinder_getOrigin_doc = "\
get_origin() -> isc.dns.Name\n\
\n\
Return the origin name of the zone.\n\
\n\
";

const char* const ZoneFinder_getClass_doc = "\
get_class() -> isc.dns.RRClass\n\
\n\
Return the RR class of the zone.\n\
\n\
";

const char* const ZoneFinder_find_doc = "\
find(name, type, target=NULL, options=FIND_DEFAULT) -> (code, FindResult)\n\
\n\
Search the zone for a given pair of domain name and RR type.\n\
\n\
- If the search name belongs under a zone cut, it returns the code of\n\
  DELEGATION and the NS RRset at the zone cut.\n\
- If there is no matching name, it returns the code of NXDOMAIN, and,\n\
  if DNSSEC is requested, the NSEC RRset that proves the non-\n\
  existence.\n\
- If there is a matching name but no RRset of the search type, it\n\
  returns the code of NXRRSET, and, if DNSSEC is required, the NSEC\n\
  RRset for that name.\n\
- If there is a CNAME RR of the searched name but there is no RR of\n\
  the searched type of the name (so this type is different from\n\
  CNAME), it returns the code of CNAME and that CNAME RR. Note that if\n\
  the searched RR type is CNAME, it is considered a successful match,\n\
  and the code of SUCCESS will be returned.\n\
- If the search name matches a delegation point of DNAME, it returns\n\
  the code of DNAME and that DNAME RR.\n\
- If the result was synthesized by a wildcard match, it returns the\n\
  code WILDCARD and the synthesized RRset\n\
- If the query matched a wildcard name, but not its type, it returns the\n\
  code WILDCARD_NXRRSET, and None\n\
- If the target is a list, all RRsets under the domain are inserted\n\
  there and SUCCESS (or NXDOMAIN, in case of empty domain) is returned\n\
  instead of normall processing. This is intended to handle ANY query.\n\
  : this behavior is controversial as we discussed in\n\
  https://lists.isc.org/pipermail/bind10-dev/2011-January/001918.html\n\
  We should revisit the interface before we heavily rely on it. The\n\
  options parameter specifies customized behavior of the search. Their\n\
  semantics is as follows:\n\
  (This feature is disable at this time)\n\
- GLUE_OK Allow search under a zone cut. By default the search will\n\
  stop once it encounters a zone cut. If this option is specified it\n\
  remembers information about the highest zone cut and continues the\n\
  search until it finds an exact match for the given name or it\n\
  detects there is no exact match. If an exact match is found, RRsets\n\
  for that name are searched just like the normal case; otherwise, if\n\
  the search has encountered a zone cut, DELEGATION with the\n\
  information of the highest zone cut will be returned.\n\
\n\
This method raises an isc.datasrc.Error exception if there is an internal\n\
error in the datasource.\n\
\n\
Parameters:\n\
  name       The domain name to be searched for.\n\
  type       The RR type to be searched for.\n\
  target     If target is not NULL, insert all RRs under the domain\n\
             into it.\n\
  options    The search options.\n\
\n\
Return Value(s): A tuple of a result code an a FindResult object enclosing\n\
the search result (see above).\n\
";

const char* const ZoneFinder_find_previous_name_doc = "\
find_previous_name(isc.dns.Name) -> isc.dns.Name\n\
\n\
Gets the previous name in the DNSSEC order. This can be used\n\
to find the correct NSEC records for proving nonexistence\n\
of domains.\n\
\n\
This method does not include under-zone-cut data (glue data).\n\
\n\
Raises isc.datasrc.NotImplemented in case the data source backend\n\
doesn't support DNSSEC or there is no previous in the zone (NSEC\n\
records might be missing in the DB, the queried name is less or\n\
equal to the apex).\n\
\n\
Raises isc.datasrc.Error for low-level or internal datasource errors\n\
(like broken connection to database, wrong data living there).\n\
";
} // unnamed namespace
