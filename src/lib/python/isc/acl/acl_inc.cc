namespace {
const char* const acl_doc = "\
Implementation module for ACL operations\n\n\
This module provides Python bindings for the C++ classes in the\n\
isc::acl namespace.\n\
\n\
Integer constants:\n\
\n\
ACCEPT, REJECT, DROP -- Default actions an ACL could perform.\n\
  These are the commonly used actions in specific ACLs.\n\
  It is possible to specify any other values, as the ACL class does\n\
  nothing about them, but these look reasonable, so they are provided\n\
  for convenience. It is not specified what exactly these mean and it's\n\
  up to whoever uses them.\n\
";
} // unnamed namespace
