namespace {
// Modifications
//   - callbacks => (error, warn)
//   - recover paragraph before itemization (it's a bug of convert script)
//   - correct broken format for nested items (another bug of script)
//   - true/false => True/False
//   - removed Exception section (for simplicity)
const char* const dns_checkZone_doc = "\
check_zone(zone_name, zone_class, zone_rrsets, (error, warn)) -> bool\n\
\n\
Perform basic integrity checks on zone RRsets.\n\
\n\
This function performs some lightweight checks on zone's SOA and\n\
(apex) NS records. Here, lightweight means it doesn't require\n\
traversing the entire zone, and should be expected to complete\n\
reasonably quickly regardless of the size of the zone.\n\
\n\
It distinguishes \"critical\" errors and other undesirable issues: the\n\
former should be interpreted as the resulting zone shouldn't be used\n\
further, e.g, by an authoritative server implementation; the latter\n\
means the issues are better to be addressed but are not necessarily\n\
considered to make the zone invalid. Critical errors are reported via\n\
the error() function, and non critical issues are reported via warn().\n\
\n\
Specific checks performed by this function is as follows.  Failure of\n\
a check is considered a critical error unless noted otherwise:\n\
\n\
- There is exactly one SOA RR at the zone apex.\n\
- There is at least one NS RR at the zone apex.\n\
- For each apex NS record, if the NS name (the RDATA of the record) is\n\
  in the zone (i.e., it's a subdomain of the zone origin and above any\n\
  zone cut due to delegation), check the following:\n\
  - the NS name should have an address record (AAAA or A). Failure of\n\
    this check is considered a non critical issue.\n\
  - the NS name does not have a CNAME. This is prohibited by Section\n\
    10.3 of RFC 2181.\n\
  - the NS name is not subject to DNAME substitution. This is prohibited\n\
    by Section 4 of RFC 6672.\n\
\n\
In addition, when the check is completed without any\n\
critical error, this function guarantees that RRsets for the SOA and\n\
(apex) NS stored in the passed RRset collection have the expected\n\
type of Rdata objects, i.e., generic.SOA and generic.NS,\n\
respectively. (This is normally expected to be the case, but not\n\
guaranteed by the API).\n\
\n\
As for the check on the existence of AAAA or A records for NS names,\n\
it should be noted that BIND 9 treats this as a critical error. It's\n\
not clear whether it's an implementation dependent behavior or based\n\
on the protocol standard (it looks like the former), but to make it\n\
sure we need to confirm there is even no wildcard match for the names.\n\
This should be a very rare configuration, and more expensive to\n\
detect, so we do not check this condition, and treat this case as a\n\
non critical issue.\n\
\n\
This function indicates the result of the checks (whether there is a\n\
critical error) via the return value: It returns True if there is no\n\
critical error and returns False otherwise. It doesn't throw an\n\
exception on encountering an error so that it can report as many\n\
errors as possible in a single call. If an exception is a better way\n\
to signal the error, the caller can pass a callable object as error()\n\
that throws.\n\
\n\
This function can still throw an exception if it finds a really bogus\n\
condition that is most likely to be an implementation bug of the\n\
caller. Such cases include when an RRset contained in the RRset\n\
collection is empty.\n\
\n\
Parameters:\n\
  zone_name  The name of the zone to be checked\n\
  zone_class The RR class of the zone to be checked\n\
  zone_rrsets The collection of RRsets of the zone\n\
  error      Callable object used to report errors\n\
  warn       Callable object used to report non-critical issues\n\
\n\
Return Value(s): True if no critical errors are found; False\n\
otherwise.\n\
";
} // unnamed namespace
