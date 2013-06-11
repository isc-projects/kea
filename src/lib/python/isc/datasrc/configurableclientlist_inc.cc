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
Wrapper around C++ ConfigurableClientList::resetMemorySegment\n\
\n\
This resets the zone table segment for a datasource with a new\n\
memory segment.\n\
\n\
Parameters:\n\
  datasrc_name      The name of the data source whose segment to reset.\
  mode              The open mode for the new memory segment.\
  config_params     The configuration for the new memory segment, as a JSON encoded string.\
";

const char* const ConfigurableClientList_get_cached_zone_writer_doc = "\
get_cached_zone_writer(zone, datasrc_name) -> status, zone_writer\n\
\n\
Wrapper around C++ ConfigurableClientList::getCachedZoneWriter\n\
\n\
This returns a ZoneWriter that can be used to (re)load a zone.\n\
\n\
Parameters:\n\
  zone              The name of the zone to (re)load.\
  datasrc_name      The name of the data source where the zone is to be loaded.\
";

const char* const ConfigurableClientList_get_status_doc = "\
get_status() -> list\n\
\n\
Wrapper around C++ ConfigurableClientList::getStatus\n\
\n\
This returns a list of tuples, each containing the status of a data source client.\
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
