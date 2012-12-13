namespace {
const char* const ZoneLoader_doc = "\
\n\
Class to load data into a data source client.\n\
\n\
This is a small wrapper class that is able to load data into a data source.\n\
It can load either from another data source or from a master file. The\n\
purpose of the class is only to hold the state for incremental loading.\n\
\n\
The old content of zone is discarded and no journal is stored.\n\
\n\
The constructor takes three arguments:\n\
- The datasource (isc.datasrc.DataSourceClient) to load the zone into\n\
- The name (isc.dns.Name) to load\n\
- either a string (for a file) or another DataSourceClient to load from\n\
\n\
Upon construction, no loading is done yet.\n\
\n\
It can throw:\n\
DataSourceError, in case the zone does not exist in destination.\n\
    This class does not support creating brand new zones, only loading\n\
    data into them. In case a new zone is needed, it must be created\n\
    beforehand (with create_zone()).\n\
    DataSourceError is also thrown in case the zone is not present in the\n\
    source DataSourceClient, and in case of other possibly low-level\n\
    errors.\n\
InvalidParameter, in case the class of destination and source\n\
    differs.\n\
NotImplemented in case target data source client doesn't provide an updater\n\
    or the source data source client doesn't provide an iterator.\n\
\n\
";

const char* const ZoneLoader_loadIncremental_doc = "\
\n\
Load up to limit RRs.\n\
\n\
This performs a part of the loading. In case there's enough data in the\n\
source, it copies limit RRs. It can copy less RRs during the final call\n\
(when there's less than limit left).\n\
\n\
This can be called repeatedly until the whole zone is loaded, having\n\
pauses in the loading for some purposes (for example reporting\n\
progress).\n\
\n\
It has one parameter: limit (integer), The maximum allowed number of RRs\n\
to be loaded during this call.\n\
\n\
Returns True in case the loading is completed, and False if there's more\n\
to load.\n\
\n\
It can throw:\n\
InvalidOperation, in case the loading was already completed before this\n\
    call (by load() or by a loadIncremental that returned true).\n\
DataSourceError, in case some error (possibly low-level) happens.\n\
MasterFileError when the master_file is badly formatted or some similar\n\
    problem is found when loading the master file.\n\
\n\
Note: If the limit is exactly the number of RRs available to be loaded,\n\
      the method still returns false and true'll be returned on the next\n\
      call (which will load 0 RRs). This is because the end of iterator or\n\
      master file is detected when reading past the end, not when the last\n\
      one is read.\n\
\n\
";

const char* const ZoneLoader_load_doc = "\
\n\
Performs the entire load operation.\n\
\n\
Depending on zone size, this could take a long time.\n\
\n\
This method has no parameters and does not return anything.\n\
\n\
It can throw:\n\
InvalidOperation, in case the loading was already completed before this call.\n\
MasterFileError, when the master_file is badly formatted or some\n\
                 similar problem is found when loading the master file.\n\
DataSourceError, in case some error (possibly low-level) happens.\n\
\n\
";

} // unnamed namespace
