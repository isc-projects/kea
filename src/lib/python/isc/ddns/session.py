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

# Result codes for UpdateSession.handle()
UPDATE_DONE = 0        # handled completely, and the response is ready
UPDATE_DROP = 1        # critical error happened, no response should be sent

# Convenient aliases of update-specific section names
SECTION_ZONE = isc.dns.Message.SECTION_QUESTION
SECTION_PREREQUISITE = isc.dns.Message.SECTION_ANSWER
SECTION_UPDATE = isc.dns.Message.SECTION_AUTHORITY

class UpdateSession:
    '''Protocol handling for a single dynamic update request.

    TBD

    '''
    def __init__(self, req_message, req_data, client_addr, datasrc_client):
        self.__message = req_message

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
        # Interpret the zone section.  It must contain exactly one
        # "question", and it must be of type SOA.
        if self.__message.get_rr_count(SECTION_ZONE) == 0:
            self.__message.make_response()
            self.__message.set_rcode(isc.dns.Rcode.FORMERR())
            return UPDATE_DONE
        return UPDATE_DONE
