namespace {
const char* const RequestContext_doc = "\
DNS request to be checked.\n\
\n\
This plays the role of ACL context for the RequestACL object.\n\
\n\
Based on the minimalist philosophy, the initial implementation only\n\
maintains the remote (source) IP address of the request and\n\
(optionally) the TSIG record included in the request. We may add more\n\
parameters of the request as we see the need for them. Possible\n\
additional parameters are the local (destination) IP address, the\n\
remote and local port numbers, various fields of the DNS request (e.g.\n\
a particular header flag value).\n\
\n\
RequestContext(remote_address, tsig)\n\
\n\
    In this initial implementation, the constructor only takes a\n\
    remote IP address in the form of a socket address as used in the\n\
    Python socket module, and optionally a pydnspp.TSIGRecord object.\n\
\n\
    Exceptions:\n\
      isc.acl.ACLError Normally shouldn't happen, but still possible\n\
                     for unexpected errors such as memory allocation\n\
                     failure or an invalid address text being passed.\n\
\n\
    Parameters:\n\
      remote_address The remote IP address\n\
      tsig   The TSIG record included in the request message, if any.\n\
             If the request doesn't include a TSIG, this will be None.\n\
             If this parameter is omitted None will be assumed.\n\
\n\
";
} // unnamed namespace
