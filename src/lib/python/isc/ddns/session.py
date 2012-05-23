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

from isc.dns import *
import isc.ddns.zone_config
from isc.log import *
from isc.ddns.logger import logger, ClientFormatter, ZoneFormatter
from isc.log_messages.libddns_messages import *

# Result codes for UpdateSession.handle()
UPDATE_SUCCESS = 0
UPDATE_ERROR = 1
UPDATE_DROP = 2

# Convenient aliases of update-specific section names
SECTION_ZONE = Message.SECTION_QUESTION
SECTION_PREREQUISITE = Message.SECTION_ANSWER
SECTION_UPDATE = Message.SECTION_AUTHORITY

# Shortcut
DBGLVL_TRACE_BASIC = logger.DBGLVL_TRACE_BASIC

class UpdateError(Exception):
    '''Exception for general error in update request handling.

    This exception is intended to be used internally within this module.
    When UpdateSession.handle() encounters an error in handling an update
    request it can raise this exception to terminate the handling.

    This class is constructed with some information that may be useful for
    subsequent possible logging:
    - msg (string) A string explaining the error.
    - zname (isc.dns.Name) The zone name.  Can be None when not identified.
    - zclass (isc.dns.RRClass) The zone class.  Like zname, can be None.
    - rcode (isc.dns.RCode) The RCODE to be set in the response message.
    - nolog (bool) If True, it indicates there's no more need for logging.

    '''
    def __init__(self, msg, zname, zclass, rcode, nolog=False):
        Exception.__init__(self, msg)
        self.zname = zname
        self.zclass = zclass
        self.rcode = rcode
        self.nolog = nolog

class UpdateSession:
    '''Protocol handling for a single dynamic update request.

    This class is instantiated with a request message and some other
    information that will be used for handling the request.  Its main
    method, handle(), will process the request, and normally build
    a response message according to the result.  The application of this
    class can use the message to send a response to the client.

    '''
    def __init__(self, req_message, req_data, client_addr, zone_config):
        '''Constructor.

        Note: req_data is not really used as of #1512 but is listed since
        it's quite likely we need it in a subsequent task soon.  We'll
        also need to get other parameters such as ACLs, for which, it's less
        clear in which form we want to get the information, so it's left
        open for now.

        Parameters:
        - req_message (isc.dns.Message) The request message.  This must be
          in the PARSE mode.
        - req_data (binary) Wire format data of the request message.
          It will be used for TSIG verification if necessary.
        - client_addr (socket address) The address/port of the update client
          in the form of Python socket address object.  This is mainly for
          logging and access control.
        - zone_config (ZoneConfig) A tentative container that encapsulates
          the server's zone configuration.  See zone_config.py.

        (It'll soon need to be passed ACL in some way, too)

        '''
        self.__message = req_message
        self.__client_addr = client_addr
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

        This method returns a tuple of the following three elements that
        indicate the result of the request.
        - Result code of the request processing, which are:
          UPDATE_SUCCESS Update request granted and succeeded.
          UPDATE_ERROR Some error happened to be reported in the response.
          UPDATE_DROP Error happened and no response should be sent.
          Except the case of UPDATE_DROP, the UpdateSession object will have
          created a response that is to be returned to the request client,
          which can be retrieved by get_message().
        - The name of the updated zone (isc.dns.Name object) in case of
          UPDATE_SUCCESS; otherwise None.
        - The RR class of the updated zone (isc.dns.RRClass object) in case
          of UPDATE_SUCCESS; otherwise None.

        '''
        try:
            datasrc_client, zname, zclass = self.__get_update_zone()
            # conceptual code that would follow
            prereq_result = self.__check_prerequisites(datasrc_client,
                                                       zname, zclass)
            if prereq_result != Rcode.NOERROR():
                logger.info(LIBDDNS_UPDATE_PREREQUISITE_FAILED,
                            ClientFormatter(self.__client_addr),
                            zname, prereq_result)
                self.__make_response(prereq_result)
                return UPDATE_ERROR, zname, zclass
            # self.__check_update_acl()
            # self.__do_update()
            # self.__make_response(Rcode.NOERROR())
            return UPDATE_SUCCESS, zname, zclass
        except UpdateError as e:
            if not e.nolog:
                logger.debug(logger.DBGLVL_TRACE_BASIC, LIBDDNS_UPDATE_ERROR,
                             ClientFormatter(self.__client_addr),
                             ZoneFormatter(e.zname, e.zclass), e)
            self.__make_response(e.rcode)
            return UPDATE_ERROR, None, None

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
        n_zones = self.__message.get_rr_count(SECTION_ZONE)
        if n_zones != 1:
            raise UpdateError('Invalid number of records in zone section: ' +
                              str(n_zones), None, None, Rcode.FORMERR())
        zrecord = self.__message.get_question()[0]
        if zrecord.get_type() != RRType.SOA():
            raise UpdateError('update zone section contains non-SOA',
                              None, None, Rcode.FORMERR())

        # See if we're serving a primary zone specified in the zone section.
        zname = zrecord.get_name()
        zclass = zrecord.get_class()
        zone_type, datasrc_client = self.__zone_config.find_zone(zname, zclass)
        if zone_type == isc.ddns.zone_config.ZONE_PRIMARY:
            return datasrc_client, zname, zclass
        elif zone_type == isc.ddns.zone_config.ZONE_SECONDARY:
            # We are a secondary server; since we don't yet support update
            # forwarding, we return 'not implemented'.
            logger.debug(DBGLVL_TRACE_BASIC, LIBDDNS_UPDATE_FORWARD_FAIL,
                         ClientFormatter(self.__client_addr),
                         ZoneFormatter(zname, zclass))
            raise UpdateError('forward', zname, zclass, Rcode.NOTIMP(), True)
        # zone wasn't found
        logger.debug(DBGLVL_TRACE_BASIC, LIBDDNS_UPDATE_NOTAUTH,
                     ClientFormatter(self.__client_addr),
                     ZoneFormatter(zname, zclass))
        raise UpdateError('notauth', zname, zclass, Rcode.NOTAUTH(), True)

    def __make_response(self, rcode):
        '''Transform the internal message to the update response.

        According RFC2136 Section 3.8, the zone section will be cleared
        as well as other sections.  The response Rcode will be set to the
        given value.

        '''
        self.__message.make_response()
        self.__message.clear_section(SECTION_ZONE)
        self.__message.set_rcode(rcode)

    def __check_prerequisite_rrset_exists(self, datasrc_client, rrset):
        '''Check whether an rrset with the given name and type exists. Class,
           TTL, and Rdata (if any) of the given RRset are ignored.
           RFC2136 Section 2.4.1.
        '''
        _, finder = datasrc_client.find_zone(rrset.get_name())
        result, _, _ = finder.find(rrset.get_name(), rrset.get_type(),
                                   finder.NO_WILDCARD | finder.FIND_GLUE_OK)
        return result == finder.SUCCESS

    def __check_prerequisite_rrset_exists_value(self, datasrc_client, rrset):
        '''Check whether an rrset that matches name, type, and rdata(s) of the
           given rrset exists.
           RFC2136 Section 2.4.2
        '''
        _, finder = datasrc_client.find_zone(rrset.get_name())
        result, found_rrset, _ = finder.find(rrset.get_name(), rrset.get_type(),
                                             finder.NO_WILDCARD | finder.FIND_GLUE_OK)
        if result == finder.SUCCESS and\
           rrset.get_name() == found_rrset.get_name() and\
           rrset.get_type() == found_rrset.get_type():
            # We need to match all actual RRs, unfortunately there is no
            # direct order-independent comparison for rrsets, so this
            # a slightly inefficient way to handle that.
            found_rdata = found_rrset.get_rdata()
            for rdata in rrset.get_rdata():
                if rdata in found_rdata:
                    found_rdata.remove(rdata)
                else:
                    return False
            return len(found_rdata) == 0
        return False

    def __check_prerequisite_rrset_does_not_exist(self, datasrc_client, rrset):
        '''Check whether no rrsets with the same name and type as the given
           rrset exist.
           RFC2136 Section 2.4.3.
        '''
        return not self.__check_prerequisite_rrset_exists(datasrc_client, rrset)

    def __check_prerequisite_name_in_use(self, datasrc_client, rrset):
        '''Check whether the name of the given RRset is in use (i.e. has
           1 or more RRs).
           RFC2136 Section 2.4.4
        '''
        _, finder = datasrc_client.find_zone(rrset.get_name())
        result, rrsets, flags = finder.find_all(rrset.get_name(),
                                                finder.NO_WILDCARD |
                                                finder.FIND_GLUE_OK)
        if result == finder.SUCCESS and\
           (flags & finder.RESULT_WILDCARD == 0):
            return True
        return False

    def __check_prerequisite_name_not_in_use(self, datasrc_client, rrset):
        '''Check whether the name of the given RRset is not in use (i.e. does
           not exist at all, or is an empty nonterminal.
           RFC2136 Section 2.4.5.
        '''
        return not self.__check_prerequisite_name_in_use(datasrc_client, rrset)

    def __check_prerequisites(self, datasrc_client, zname, zclass):
        '''Check the prerequisites section of the UPDATE Message.
           RFC2136 Section 2.4'''
        for rrset in self.__message.get_section(SECTION_PREREQUISITE):
            # First check if the name is in the zone
            relation = rrset.get_name().compare(zname).get_relation()
            if relation != NameComparisonResult.SUBDOMAIN and\
               relation != NameComparisonResult.EQUAL:
                return NOTZONE

            # Algorithm taken from RFC2136 Section 3.2
            if rrset.get_class() == RRClass.ANY():
                if rrset.get_ttl().get_value() != 0 or\
                   rrset.get_rdata_count() != 0:
                    return Rcode.FORMERR()
                elif rrset.get_type() == RRType.ANY():
                    if not self.__check_prerequisite_name_in_use(datasrc_client, rrset):
                        return Rcode.NXDOMAIN()
                else:
                    if not self.__check_prerequisite_rrset_exists(datasrc_client, rrset):
                        return Rcode.NXRRSET()
            elif rrset.get_class() == RRClass.NONE():
                if rrset.get_ttl().get_value() != 0 or\
                   rrset.get_rdata_count() != 0:
                    return Rcode.FORMERR()
                elif rrset.get_type() == RRType.ANY():
                    if not self.__check_prerequisite_name_not_in_use(datasrc_client, rrset):
                        return Rcode.YXDOMAIN()
                else:
                    if not self.__check_prerequisite_rrset_does_not_exist(datasrc_client, rrset):
                        return Rcode.YXRRSET()
            elif rrset.get_class() == zclass:
                if rrset.get_ttl().get_value() != 0:
                    return Rcode.FORMERR()
                else:
                    if not self.__check_prerequisite_rrset_exists_value(datasrc_client, rrset):
                        return Rcode.NXRRSET()
            else:
                return Rcode.FORMERR()

        return Rcode.NOERROR()
