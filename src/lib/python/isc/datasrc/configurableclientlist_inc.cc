namespace {

const char* const ConfigurableClientList_doc = "\
The list of data source clients\n\
\n\
The purpose is to have several data source clients of the same class\
and then be able to search through them to identify the one containing\
a given zone.\n\
\n\
Unlike the C++ version, we don't have the abstract base class. Abstract\
classes are not needed due to the duck typing nature of python.\
";
} // unnamed namespace
