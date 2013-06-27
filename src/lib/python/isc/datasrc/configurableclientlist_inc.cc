// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

const char* const ConfigurableClientList_configure_doc = "\
configure(configuration, allow_cache) -> None\n\
\n\
Wrapper around C++ ConfigurableClientList::configure\n\
\n\
This sets the active configuration. It fills the ConfigurableClientList with\
corresponding data source clients.\n\
\n\
If any error is detected, an exception is raised and the previous\
configuration preserved.\n\
\n\
Parameters:\n\
  configuration     The configuration, as a JSON encoded string.\
  allow_cache       If caching is allowed.\
";

const char* const ConfigurableClientList_reset_memory_segment_doc = "\
reset_memory_segment(datasrc_name, mode, config_params) -> None\n\
\n\
This method resets the zone table segment for a datasource with a new\n\
memory segment.\n\
\n\
Parameters:\n\
  datasrc_name      The name of the data source whose segment to reset.\n\
  mode              The open mode for the new memory segment.\n\
  config_params     The configuration for the new memory segment, as a JSON encoded string.\n\
";

const char* const ConfigurableClientList_get_zone_table_accessor_doc = "\
get_zone_table_accessor(datasrc_name, use_cache) -> \
isc.datasrc.ZoneTableAccessor\n\
\n\
Create a ZoneTableAccessor object for the specified data source.\n\
\n\
Parameters:\n\
  datasrc_name      If not empty, the name of the data source\n\
  use_cache         If true, create a zone table for in-memory cache.\n\
";

const char* const ConfigurableClientList_get_cached_zone_writer_doc = "\
get_cached_zone_writer(zone, catch_load_error, datasrc_name) -> status, zone_writer\n\
\n\
This method returns a ZoneWriter that can be used to (re)load a zone.\n\
\n\
By default this method identifies the first data source in the list\n\
that should serve the zone of the given name, and returns a ZoneWriter\n\
object that can be used to load the content of the zone, in a specific\n\
way for that data source.\n\
\n\
If the optional datasrc_name parameter is provided with a non empty\n\
string, this method only tries to load the specified zone into or with\n\
the data source which has the given name, regardless where in the list\n\
that data source is placed.  Even if the given name of zone doesn't\n\
exist in the data source, other data sources are not searched and\n\
this method simply returns ZONE_NOT_FOUND in the first element\n\
of the pair.\n\
\n\
Two elements are returned. The first element is a status\n\
indicating if it worked or not (and in case it didn't, also why). If the\n\
status is ZONE_SUCCESS, the second element contains a ZoneWriter object. If\n\
the status is anything else, the second element is None.\n\
\n\
Parameters:\n\
  zone              The origin of the zone to (re)load.\n\
  catch_load_error  Whether to catch load errors, or to raise them as exceptions.\n\
  datasrc_name      The name of the data source where the zone is to be loaded (optional).\n\
";

const char* const ConfigurableClientList_get_status_doc = "\
get_status() -> list of tuples\n\
\n\
This method returns a list of tuples, with each tuple containing the\n\
status of a data source client. If there are no data source clients\n\
present, an empty list is returned.\n\
\n\
The tuples contain (name, segment_type, segment_state):\n\
  name              The name of the data source.\n\
  segment_type      A string indicating the type of memory segment in use.\n\
  segment_state     The state of the memory segment.\n\
\n\
If segment_state is SEGMENT_UNUSED, None is returned for the segment_type.\n\
";

const char* const ConfigurableClientList_find_doc = "\
find(zone, want_exact_match=False, want_finder=True) -> datasrc_client,\
zone_finder, exact_match\n\
\n\
Look for a data source containing the given zone.\n\
\n\
It searches through the contained data sources and returns a data source\
containing the zone, the zone finder of the zone and a boolean if the answer\
is an exact match.\n\
\n\
The first parameter is isc.dns.Name object of a name in the zone. If the\
want_exact_match is True, only zone with this exact origin is returned.\
If it is False, the best matching zone is returned.\n\
\n\
If the want_finder is False, the returned zone_finder might be None even\
if the data source is identified (in such case, the datasrc_client is not\
None). Setting it to false allows the client list some optimisations, if\
you don't need it, but if you do need it, it is better to set it to True\
instead of getting it from the datasrc_client later.\n\
\n\
If no answer is found, the datasrc_client and zone_finder are None.\
";

} // unnamed namespace
