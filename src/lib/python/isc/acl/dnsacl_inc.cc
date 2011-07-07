namespace {
const char* const load_request_acl_doc = "\
load_request_acl(description) -> RequestACL\n\
\n\
Load a DNS ACL.\n\
\n\
This parses an ACL list, creates internal data for each rule\n\
and returns a RequestACl object that contains all given rules.\n\
\n\
Exceptions:\n\
  LoaderError Load failed.  The most likely cause of this is a syntax\n\
              error in the description.  Other internal errors such as\n\
              memory allocation failure is also converted to this\n\
              exception.\n\
\n\
Parameters:\n\
  description String representation of the JSON list of ACL.\n\
\n\
Return Value(s): The newly created RequestACL object\n\
";
} // unnamed namespace
