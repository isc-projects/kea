namespace {
const char* const RequestACL_doc = "\
The DNS Request ACL.\n\
\n\
It holds bunch of ordered entries, each one consisting of a check for\n\
a given DNS Request context and an action, which is one of ACCEPT,\n\
REJECT, or DROP, as defined in the isc.acl.acl module.\n\
The checks are tested in the order and first match counts.\n\
\n\
A RequestACL object cannot be constructed directly; an application\n\
must use isc.acl.dns.load_request_acl() to create a RequestACL object.\n\
\n\
";

const char* const RequestACL_execute_doc = "\
execute(context) -> action \n\
\n\
The returned action is one of ACCEPT, REJECT or DROP as defined in\n\
the isc.acl.acl module.\n\
\n\
This is the function that takes the ACL entries one by one, checks the\n\
context against conditions and if it matches, returns the action that\n\
belongs to the first matched entry or default action if nothing\n\
matches.\n\
\n\
Parameters:\n\
  context    The thing that should be checked. It is directly passed\n\
             to the checks.\n\
\n\
Return Value(s): The action for the ACL entry that first matches the\n\
context.\n\
";
} // unnamed namespace
