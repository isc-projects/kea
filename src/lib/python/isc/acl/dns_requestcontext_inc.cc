namespace {
const char* const RequestContext_doc = "\
DNS request to be checked.\n\
\n\
This plays the role of ACL context for the RequestACL object.\n\
\n\
Based on the minimalist philosophy, the initial implementation only\n\
maintains the remote (source) IP address of the request. The plan is\n\
to add more parameters of the request. A scheduled next step is to\n\
support the TSIG key (if it's included in the request). Other\n\
possibilities are the local (destination) IP address, the remote and\n\
local port numbers, various fields of the DNS request (e.g. a\n\
particular header flag value).\n\
\n\
RequestContext(remote_address)\n\
\n\
    In this initial implementation, the constructor only takes a\n\
    remote IP address in the form of a socket address as used in the\n\
    Python socket module.\n\
\n\
    Exceptions:\n\
      isc.acl.ACLError Normally shouldn't happen, but still possible\n\
                     for unexpected errors such as memory allocation\n\
                     failure or an invalid address text being passed.\n\
\n\
    Parameters:\n\
      remote_address The remote IP address\n\
\n\
";
} // unnamed namespace
