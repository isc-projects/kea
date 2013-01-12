namespace {
const char* const ZoneLoader_doc = "\
Class to load data into a data source client.\n\
\n\
This is a small wrapper class that is able to load data into a data\n\
source. It can load either from another data source or from a master\n\
file. The purpose of the class is only to hold the state for\n\
incremental loading.\n\
\n\
The old content of zone is discarded and no journal is stored.\n\
\n\
ZoneLoader(destination, zone_name, master_file)\n\
\n\
    Constructor from master file.\n\
\n\
    This initializes the zone loader to load from a master file.\n\
\n\
    Exceptions:\n\
      DataSourceError in case the zone does not exist in destination.\n\
                 This class does not support creating brand new zones,\n\
                 only loading data into them. In case a new zone is\n\
                 needed, it must be created beforehand.\n\
      DataSourceError in case of other (possibly low-level) errors,\n\
                 such as read-only data source or database error.\n\
\n\
    Parameters:\n\
      destination (isc.datasrc.DataSourceClient) The data source into\n\
                  which the loaded data should go.\n\
      zone_name   (isc.dns.Name) The origin of the zone. The class is\n\
                  implicit in the destination.\n\
      master_file (string) Path to the master file to read data from.\n\
\n\
ZoneLoader(destination, zone_name, source)\n\
\n\
    Constructor from another data source.\n\
\n\
    Parameters:\n\
      destination (isc.datasrc.DataSourceClient) The data source into\n\
                  which the loaded data should go.\n\
      zone_name   (isc.dns.Name) The origin of the zone. The class is\n\
                  implicit in the destination.\n\
      source      (isc.datasrc.DataSourceClient) The data source from\n\
                  which the data would be read.\n\
\n\
    Exceptions:\n\
      InvalidParameter in case the class of destination and source\n\
                 differs.\n\
      NotImplemented in case the source data source client doesn't\n\
                 provide an iterator.\n\
      DataSourceError in case the zone does not exist in destination.\n\
                 This class does not support creating brand new zones,\n\
                 only loading data into them. In case a new zone is\n\
                 needed, it must be created beforehand.\n\
      DataSourceError in case the zone does not exist in the source.\n\
      DataSourceError in case of other (possibly low-level) errors,\n\
                 such as read-only data source or database error.\n\
\n\
    Parameters:\n\
      destination The data source into which the loaded data should\n\
                 go.\n\
      zone_name  The origin of the zone.\n\
      source     The data source from which the data would be read.\n\
\n\
";

const char* const ZoneLoader_load_doc = "\
load() -> None\n\
\n\
Perform the whole load.\n\
\n\
This performs the whole loading operation. It may take a long time.\n\
\n\
Exceptions:\n\
  InvalidOperation in case the loading was already completed before\n\
             this call.\n\
  DataSourceError in case some error (possibly low-level) happens.\n\
  MasterFileError when the master_file is badly formatted or some\n\
             similar problem is found when loading the master file.\n\
\n\
";

const char* const ZoneLoader_loadIncremental_doc = "\
load_incremental(limit) -> bool\n\
\n\
Load up to limit RRs.\n\
\n\
This performs a part of the loading. In case there's enough data in\n\
the source, it copies limit RRs. It can copy less RRs during the final\n\
call (when there's less than limit left).\n\
\n\
This can be called repeatedly until the whole zone is loaded, having\n\
pauses in the loading for some purposes (for example reporting\n\
progress).\n\
\n\
Exceptions:\n\
  InvalidOperation in case the loading was already completed before\n\
             this call (by load() or by a load_incremental that\n\
             returned true).\n\
  DataSourceError in case some error (possibly low-level) happens.\n\
  MasterFileError when the master_file is badly formatted or some\n\
             similar problem is found when loading the master file.\n\
\n\
Parameters:\n\
  limit      (integer) The maximum allowed number of RRs to be\n\
             loaded during this call.\n\
\n\
Return Value(s): True in case the loading is completed, false if\n\
there's more to load.\n\
\n\
Note that if the limit is exactly the number of RRs available to be\n\
loaded, the method will still return False, and True will be returned\n\
on the next call (which will load 0 RRs). This is because the end of\n\
iterator or master file is detected when reading past the end, not\n\
when the last one is read.\n\
";

const char* const ZoneLoader_getRRCount_doc = "\
get_rr_count() -> integer\n\
\n\
Return the number of RRs loaded.\n\
\n\
This method returns the number of RRs loaded via this loader by the\n\
time of the call. Before starting the load it will return 0. It will\n\
return the total number of RRs of the zone on and after completing the\n\
load.\n\
\n\
Exceptions:\n\
  None\n\
\n\
";

const char* const ZoneLoader_getSize_doc = "\
get_size() -> integer\n\
\n\
Return the (estimated) total size of the entire zone.\n\
\n\
This method returns some hint on how large the zone will be when\n\
completing the load. The returned size is a conceptual value that can\n\
internally mean anything. The intended usage of the value is to\n\
compare it to the return value of get_position() to estimate the\n\
progress of the load at the time of the call.\n\
\n\
In this implementation, if the loader is constructed with a file name,\n\
the returned size is the size of the zone file. If it includes other\n\
files via the $INCLUDE directive, it will be the sum of the file sizes\n\
of all such files that the loader has handled. Note that it may be\n\
smaller than the final size if there are more files to be included\n\
which the loader has not seen by the time of the call.\n\
\n\
Currently, if the loader is constructed with another data source\n\
client, this method always returns 0. In future, it may be possible to\n\
return something more effective, e.g, the total number of RRs if the\n\
underlying data source can provide that information efficiently.\n\
\n\
In any case, the caller shouldn't assume anything specific about the\n\
meaning of the value other than for comparing it to the result of\n\
get_position().\n\
\n\
Exceptions:\n\
  None\n\
\n\
";

const char* const ZoneLoader_getPosition_doc = "\
get_position() -> integer\n\
\n\
Return the current position of the loader in the zone being loaded.\n\
\n\
This method returns a conceptual \"position\" of this loader in the\n\
loader relative to the return value of get_size(). Before starting the\n\
load the position is set to 0; on successful completion, it will be\n\
equal to the get_size() value; in the middle of the load, it's\n\
expected to be between these values, which would give some hint about\n\
the progress of the loader.\n\
\n\
In the current implementation, if the loader is constructed with a\n\
file name, the returned value is the number of characters from the\n\
zone file (and any included files) recognized by the underlying zone\n\
file parser.\n\
\n\
If it's constructed with another data source client, it's always 0 for\n\
now; however, if get_position() is extended in this case as documented\n\
(see the method description), the result of get_rr_count() could be\n\
used for the current position.\n\
\n\
Like get_size(), the value is conceptual and the caller shouldn't\n\
assume any specific meaning of the value except for comparing it to\n\
get_size() results.\n\
\n\
Exceptions:\n\
  None\n\
\n\
";
} // unnamed namespace
