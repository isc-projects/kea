# Copyright (C) 2012  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

import isc.dns
import isc.ddns.zone_config

# Result codes for UpdateSession.handle()
UPDATE_SUCCESS = 0     # update request granted and succeeded
UPDATE_ERROR = 1       # some error happened with a corresponding response
UPDATE_DROP = 2        # critical error happened, no response should be sent

# Convenient aliases of update-specific section names
SECTION_ZONE = isc.dns.Message.SECTION_QUESTION
SECTION_PREREQUISITE = isc.dns.Message.SECTION_ANSWER
SECTION_UPDATE = isc.dns.Message.SECTION_AUTHORITY

class ZoneError(Exception):
    def __init__(self, msg, rcode):
        Exception(msg)
        self.rcode = rcode

class UpdateSession:
    '''Protocol handling for a single dynamic update request.

    TBD

    '''
    def __init__(self, req_message, req_data, client_addr, zone_config):
        self.__message = req_message
        self.__zone_config = zone_config

    def get_message(self):
        '''Return the update message.

        After handle() is called, it's generally transformed to the response
        to be returned to the client; otherwise it would be identical to
        the request message passed on construction.

        '''
        return self.__message

    def handle(self):
        '''Handle the update request according to RFC2136.

        Return: the result code of the session, indicating the next action
                to be taken.

        '''
        try:
            datasrc_client, zname, zclass = self.__get_update_zone()
            # conceptual code that would follow
            # self.__check_prerequisites()
            # self.__check_update_acl()
            # self.__do_update()
            # self.__make_response(Rcode.NOERROR())
            return UPDATE_SUCCESS
        except ZoneError as e:
            self.__make_response(e.rcode)
        return UPDATE_ERROR

    def __get_update_zone(self):
        '''Parse the zone section and find the zone to be updated.

        If the zone section is valid and the specified zone is found in
        the configuration, it returns a tuple of:
        - A matching data source that contains the specified zone
        - The zone name as a Name object
        - The zone class as an RRClass object

        '''
        # Validation: the zone section must contain exactly one question,
        # and it must be of type SOA.
        if self.__message.get_rr_count(SECTION_ZONE) != 1:
            raise ZoneError('Invalid number of records in zone section: ' +
                            str(1), isc.dns.Rcode.FORMERR())
        zrecord = self.__message.get_question()[0]
        if zrecord.get_type() != isc.dns.RRType.SOA():
            raise ZoneError('update zone section contains non-SOA',
                            isc.dns.Rcode.FORMERR())

        # See if we're serving a primary zone specified in the zone section.
        zname = zrecord.get_name()
        zclass = zrecord.get_class()
        zone_type, datasrc_client = self.__zone_config.find_zone(zname, zclass)
        if zone_type == isc.ddns.zone_config.ZONE_PRIMARY:
            return datasrc_client, zname, zclass
        elif zone_type == isc.ddns.zone_config.ZONE_SECONDARY:
            # unconditionally refused forwarding (we don't support it yet)
            raise ZoneError('Update forwarding not supported',
                            isc.dns.Rcode.REFUSED())

    def __make_response(self, rcode):
        '''Transform the internal message to the update response.

        According RFC2136 Section 3.8, the zone section will be cleared
        as well as other sections.  The response Rcode will be set to the
        given value.

        '''
        self.__message.make_response()
        self.__message.clear_section(SECTION_ZONE)
        self.__message.set_rcode(rcode)
