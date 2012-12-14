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
} // unnamed namespace
