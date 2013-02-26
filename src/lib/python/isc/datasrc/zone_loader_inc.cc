// Copyright (C) 2012-2013  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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

// Modifications
// - double => float
const char* const ZoneLoader_getProgress_doc = "\
get_progress() -> float\n\
\n\
Return the current progress of the loader.\n\
\n\
This method returns the current estimated progress of loader as a\n\
value between 0 and 1 (inclusive); it's 0 before starting the load,\n\
and 1 at the completion, and a value between these (exclusive) in the\n\
middle of loading. It's an implementation detail how to calculate the\n\
progress, which may vary depending on how the loader is constructed\n\
and may even be impossible to detect effectively.\n\
\n\
If the progress cannot be determined, this method returns a special\n\
value of PROGRESS_UNKNOWN, which is not included in the range between\n\
0 and 1.\n\
\n\
As such, the application should use the return value only for\n\
informational purposes such as logging. For example, it shouldn't be\n\
used to determine whether loading is completed by comparing it to 1.\n\
It should also expect the possibility of getting PROGRESS_UNKNOWN at\n\
any call to this method; it shouldn't assume the specific way of\n\
internal implementation as described below (which is provided for\n\
informational purposes only).\n\
\n\
In this implementation, if the loader is constructed with a file name,\n\
the progress value is measured by the number of characters read from\n\
the zone file divided by the size of the zone file (with taking into\n\
account any included files). Note that due to the possibility of\n\
intermediate included files, the total file size cannot be fully fixed\n\
until the completion of the load. And, due to this possibility, return\n\
values from this method may not always increase monotonically.\n\
\n\
If it's constructed with another data source client, this method\n\
always returns PROGRESS_UNKNOWN; in future, however, it may become\n\
possible to return something more useful, e.g, based on the result of\n\
get_rr_count() and the total number of RRs if the underlying data\n\
source can provide the latter value efficiently.\n\
\n\
Exceptions:\n\
  None\n\
\n\
";
} // unnamed namespace
