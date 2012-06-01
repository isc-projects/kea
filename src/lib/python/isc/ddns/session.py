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
from isc.ddns.logger import logger, ClientFormatter, ZoneFormatter,\
                            RRsetFormatter
from isc.log_messages.libddns_messages import *
from isc.datasrc import ZoneFinder
import isc.xfrin.diff
import copy

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

def foreach_rr_in_rrset(rrset, method, *kwargs):
    '''Helper function. For DDNS, in a number of cases, we need to
       treat the various RRs in a single RRset separately.
       Our libdns++ has no concept of RRs, so in that case,
       what we do is create a temporary 1-RR RRset for each Rdata
       in the RRset object.
       This method then calls the given method with the given args
       for each of the temporary rrsets (the rrset in *wargs is
       replaced by the temporary one)
       Note: if this method is useful in more places, we may want
       to move it out of ddns.
       Example:
       Say you have a method that prints a prexif string and an
       rrset, def my_print(prefix, rrset)
       Given an rrset my_rrset, you'd print the entire rrset
       with my_print("foo", rrset)
       And with this helper function, to print each rr invidually,
       you'd call
       foreach_rr_in_rrsetet(rrset, my_print, "foo", rrset)
       Note the rrset is needed twice, the first to identify it,
       the second as the 'real' argument to my_print (which is replaced
       by this function.
    '''
    result = None
    for rdata in rrset.get_rdata():
        tmp_rrset = isc.dns.RRset(rrset.get_name(),
                                  rrset.get_class(),
                                  rrset.get_type(),
                                  rrset.get_ttl())
        tmp_rrset.add_rdata(rdata)
        # Replace the rrset in the original arguments by our rrset
        args = [arg if arg != rrset else tmp_rrset for arg in kwargs]
        result = method(*args)
    return result

def convert_rrset_class(rrset, rrclass):
    '''Returns a (new) rrset with the data from the given rrset,
       but of the given class. Useful to convert from NONE and ANY to
       a real class.
       Note that the caller should be careful what to convert;
       and DNS error that could happen during wire-format reading
       could technically occur here, and is not caught by this helper.
    '''
    new_rrset = isc.dns.RRset(rrset.get_name(), rrclass,
                              rrset.get_type(), rrset.get_ttl())
    for rdata in rrset.get_rdata():
        # Rdata class is nof modifiable, and must match rrset's
        # class, so we need to to some ugly conversion here.
        # And we cannot use to_text() (since the class may be unknown)
        wire = rdata.to_wire(bytes())
        new_rrset.add_rdata(isc.dns.Rdata(rrset.get_type(), rrclass, wire))
    return new_rrset

class DDNS_SOA:
    '''Class to handle the SOA in the DNS update '''

    def __get_serial_internal(self, origin_soa):
        '''Get serial number from soa'''
        return Serial(int(origin_soa.get_rdata()[0].to_text().split()[2]))

    def __write_soa_internal(self, origin_soa, soa_num):
        '''Write back serial number to soa'''
        new_soa = RRset(origin_soa.get_name(), origin_soa.get_class(),
                        RRType.SOA(), origin_soa.get_ttl())
        soa_rdata_parts = origin_soa.get_rdata()[0].to_text().split()
        soa_rdata_parts[2] = str(soa_num.get_value())
        new_soa.add_rdata(Rdata(origin_soa.get_type(), origin_soa.get_class(),
                                " ".join(soa_rdata_parts)))
        return new_soa

    def soa_update_check(self, origin_soa, new_soa):
        '''Check whether the new soa is valid. If the serial number is bigger
        than the old one, it is valid, then return True, otherwise, return
        False.
        Parameters:
            origin_soa, old SOA resource record.
            new_soa, new SOA resource record.
        Output:
            if the serial number of new soa is bigger than the old one, return
            True, otherwise return False.
        '''
        old_serial = self.__get_serial_internal(origin_soa)
        new_serial = self.__get_serial_internal(new_soa)
        if(new_serial > old_serial):
            return True
        else:
            return False

    def update_soa(self, origin_soa, inc_number = 1):
        ''' Update the soa number incrementally as RFC 2136. Please make sure
        that the origin_soa exists and not null before invoke this function.
        Parameters:
            origin_soa, the soa resource record which will be updated.
            inc_number, the number which will be added into the serial number of
            origin_soa, the default value is one.
        Output:
            The new origin soa whoes serial number has been updated.
        '''
        soa_num = self.__get_serial_internal(origin_soa)
        soa_num = soa_num + inc_number
        if soa_num.get_value() == 0:
            soa_num = soa_num + 1
        return self.__write_soa_internal(origin_soa, soa_num)

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
        self.__added_soa = None

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
            self.__get_update_zone()
            # conceptual code that would follow
            prereq_result = self.__check_prerequisites()
            if prereq_result != Rcode.NOERROR():
                self.__make_response(prereq_result)
                return UPDATE_ERROR, self.__zname, self.__zclass
            # self.__check_update_acl()
            update_result = self.__do_update()
            if update_result != Rcode.NOERROR():
                self.__make_response(update_result)
                return UPDATE_ERROR, self.__zname, self.__zclass
            self.__make_response(Rcode.NOERROR())
            return UPDATE_SUCCESS, self.__zname, self.__zclass
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
        the configuration, sets private member variables for this session:
        __datasrc_client: A matching data source that contains the specified
                          zone
        __zname: The zone name as a Name object
        __zclass: The zone class as an RRClass object
        __finder: A ZoneFinder for this zone
        If this method raises an exception, these members are not set
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
            self.__zname = zname
            self.__zclass = zclass
            self.__datasrc_client = datasrc_client
            _, self.__finder = datasrc_client.find_zone(zname)
            return
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

    def __prereq_rrset_exists(self, rrset):
        '''Check whether an rrset with the given name and type exists. Class,
           TTL, and Rdata (if any) of the given RRset are ignored.
           RFC2136 Section 2.4.1.
           Returns True if the prerequisite is satisfied, False otherwise.

           Note: the only thing used in the call to find() here is the
           result status. The actual data is immediately dropped. As
           a future optimization, we may want to add a find() option to
           only return what the result code would be (and not read/copy
           any actual data).
        '''
        result, _, _ = self.__finder.find(rrset.get_name(), rrset.get_type(),
                                          ZoneFinder.NO_WILDCARD |
                                          ZoneFinder.FIND_GLUE_OK)
        return result == ZoneFinder.SUCCESS

    def __prereq_rrset_exists_value(self, rrset):
        '''Check whether an rrset that matches name, type, and rdata(s) of the
           given rrset exists.
           RFC2136 Section 2.4.2
           Returns True if the prerequisite is satisfied, False otherwise.
        '''
        result, found_rrset, _ = self.__finder.find(rrset.get_name(),
                                                    rrset.get_type(),
                                                    ZoneFinder.NO_WILDCARD |
                                                    ZoneFinder.FIND_GLUE_OK)
        if result == ZoneFinder.SUCCESS and\
           rrset.get_name() == found_rrset.get_name() and\
           rrset.get_type() == found_rrset.get_type():
            # We need to match all actual RRs, unfortunately there is no
            # direct order-independent comparison for rrsets, so this
            # a slightly inefficient way to handle that.

            # shallow copy of the rdata list, so we are sure that this
            # loop does not mess with actual data.
            found_rdata = copy.copy(found_rrset.get_rdata())
            for rdata in rrset.get_rdata():
                if rdata in found_rdata:
                    found_rdata.remove(rdata)
                else:
                    return False
            return len(found_rdata) == 0
        return False

    def __prereq_rrset_does_not_exist(self, rrset):
        '''Check whether no rrsets with the same name and type as the given
           rrset exist.
           RFC2136 Section 2.4.3.
           Returns True if the prerequisite is satisfied, False otherwise.
        '''
        return not self.__prereq_rrset_exists(rrset)

    def __prereq_name_in_use(self, rrset):
        '''Check whether the name of the given RRset is in use (i.e. has
           1 or more RRs).
           RFC2136 Section 2.4.4
           Returns True if the prerequisite is satisfied, False otherwise.

           Note: the only thing used in the call to find_all() here is
           the result status. The actual data is immediately dropped. As
           a future optimization, we may want to add a find_all() option
           to only return what the result code would be (and not read/copy
           any actual data).
        '''
        result, rrsets, flags = self.__finder.find_all(rrset.get_name(),
                                                       ZoneFinder.NO_WILDCARD |
                                                       ZoneFinder.FIND_GLUE_OK)
        if result == ZoneFinder.SUCCESS and\
           (flags & ZoneFinder.RESULT_WILDCARD == 0):
            return True
        return False

    def __prereq_name_not_in_use(self, rrset):
        '''Check whether the name of the given RRset is not in use (i.e. does
           not exist at all, or is an empty nonterminal.
           RFC2136 Section 2.4.5.
           Returns True if the prerequisite is satisfied, False otherwise.
        '''
        return not self.__prereq_name_in_use(rrset)

    def __check_in_zone(self, rrset):
        '''Returns true if the name of the given rrset is equal to
           or a subdomain of the zname from the Zone Section.'''
        relation = rrset.get_name().compare(self.__zname).get_relation()
        return relation == NameComparisonResult.SUBDOMAIN or\
               relation == NameComparisonResult.EQUAL

    def __check_prerequisites(self):
        '''Check the prerequisites section of the UPDATE Message.
           RFC2136 Section 2.4.
           Returns a dns Rcode signaling either no error (Rcode.NOERROR())
           or that one of the prerequisites failed (any other Rcode).
        '''
        for rrset in self.__message.get_section(SECTION_PREREQUISITE):
            # First check if the name is in the zone
            if not self.__check_in_zone(rrset):
                logger.info(LIBDDNS_PREREQ_NOTZONE,
                            ClientFormatter(self.__client_addr),
                            ZoneFormatter(self.__zname, self.__zclass),
                            RRsetFormatter(rrset))
                return Rcode.NOTZONE()

            # Algorithm taken from RFC2136 Section 3.2
            if rrset.get_class() == RRClass.ANY():
                if rrset.get_ttl().get_value() != 0 or\
                   rrset.get_rdata_count() != 0:
                    logger.info(LIBDDNS_PREREQ_FORMERR_ANY,
                                ClientFormatter(self.__client_addr),
                                ZoneFormatter(self.__zname, self.__zclass),
                                RRsetFormatter(rrset))
                    return Rcode.FORMERR()
                elif rrset.get_type() == RRType.ANY():
                    if not self.__prereq_name_in_use(rrset):
                        rcode = Rcode.NXDOMAIN()
                        logger.info(LIBDDNS_PREREQ_NAME_IN_USE_FAILED,
                                    ClientFormatter(self.__client_addr),
                                    ZoneFormatter(self.__zname, self.__zclass),
                                    RRsetFormatter(rrset), rcode)
                        return rcode
                else:
                    if not self.__prereq_rrset_exists(rrset):
                        rcode = Rcode.NXRRSET()
                        logger.info(LIBDDNS_PREREQ_RRSET_EXISTS_FAILED,
                                    ClientFormatter(self.__client_addr),
                                    ZoneFormatter(self.__zname, self.__zclass),
                                    RRsetFormatter(rrset), rcode)
                        return rcode
            elif rrset.get_class() == RRClass.NONE():
                if rrset.get_ttl().get_value() != 0 or\
                   rrset.get_rdata_count() != 0:
                    logger.info(LIBDDNS_PREREQ_FORMERR_NONE,
                                ClientFormatter(self.__client_addr),
                                ZoneFormatter(self.__zname, self.__zclass),
                                RRsetFormatter(rrset))
                    return Rcode.FORMERR()
                elif rrset.get_type() == RRType.ANY():
                    if not self.__prereq_name_not_in_use(rrset):
                        rcode = Rcode.YXDOMAIN()
                        logger.info(LIBDDNS_PREREQ_NAME_NOT_IN_USE_FAILED,
                                    ClientFormatter(self.__client_addr),
                                    ZoneFormatter(self.__zname, self.__zclass),
                                    RRsetFormatter(rrset), rcode)
                        return rcode
                else:
                    if not self.__prereq_rrset_does_not_exist(rrset):
                        rcode = Rcode.YXRRSET()
                        logger.info(LIBDDNS_PREREQ_RRSET_DOES_NOT_EXIST_FAILED,
                                    ClientFormatter(self.__client_addr),
                                    ZoneFormatter(self.__zname, self.__zclass),
                                    RRsetFormatter(rrset), rcode)
                        return rcode
            elif rrset.get_class() == self.__zclass:
                if rrset.get_ttl().get_value() != 0:
                    logger.info(LIBDDNS_PREREQ_FORMERR,
                                ClientFormatter(self.__client_addr),
                                ZoneFormatter(self.__zname, self.__zclass),
                                RRsetFormatter(rrset))
                    return Rcode.FORMERR()
                else:
                    if not self.__prereq_rrset_exists_value(rrset):
                        rcode = Rcode.NXRRSET()
                        logger.info(LIBDDNS_PREREQ_RRSET_EXISTS_VAL_FAILED,
                                    ClientFormatter(self.__client_addr),
                                    ZoneFormatter(self.__zname, self.__zclass),
                                    RRsetFormatter(rrset), rcode)
                        return rcode
            else:
                logger.info(LIBDDNS_PREREQ_FORMERR_CLASS,
                            ClientFormatter(self.__client_addr),
                            ZoneFormatter(self.__zname, self.__zclass),
                            RRsetFormatter(rrset))
                return Rcode.FORMERR()

        # All prerequisites are satisfied
        return Rcode.NOERROR()

    def __set_soa_rrset(self, rrset):
        '''Sets the given rrset to the member __added_soa (which
           is used by __do_update for updating the SOA record'''
        self.__added_soa = rrset

    def __do_prescan(self):
        '''Perform the prescan as defined in RFC2136 section 3.4.1.
           This method has a side-effect; it sets self._new_soa if
           it encounters the addition of a SOA record in the update
           list (so serial can be checked by update later, etc.).
           It puts the added SOA in self.__added_soa.
        '''
        for rrset in self.__message.get_section(SECTION_UPDATE):
            if not self.__check_in_zone(rrset):
                logger.info(LIBDDNS_UPDATE_NOTZONE,
                            ClientFormatter(self.__client_addr),
                            ZoneFormatter(self.__zname, self.__zclass),
                            RRsetFormatter(rrset))
                return Rcode.NOTZONE()
            if rrset.get_class() == self.__zclass:
                # In fact, all metatypes are in a specific range,
                # so one check can test TKEY to ANY
                # (some value check is needed anyway, since we do
                # not have defined RRtypes for MAILA and MAILB)
                if rrset.get_type().get_code() >=  249:
                    logger.info(LIBDDNS_UPDATE_ADD_BAD_TYPE,
                                ClientFormatter(self.__client_addr),
                                ZoneFormatter(self.__zname, self.__zclass),
                                RRsetFormatter(rrset))
                    return Rcode.FORMERR()
                if rrset.get_type() == RRType.SOA():
                    # In case there's multiple soa records in the update
                    # somehow, just take the last
                    foreach_rr_in_rrset(rrset, self.__set_soa_rrset, rrset)
            elif rrset.get_class() == RRClass.ANY():
                if rrset.get_ttl().get_value() != 0:
                    logger.info(LIBDDNS_UPDATE_DELETE_NONZERO_TTL,
                                ClientFormatter(self.__client_addr),
                                ZoneFormatter(self.__zname, self.__zclass),
                                RRsetFormatter(rrset))
                    return Rcode.FORMERR()
                if rrset.get_rdata_count() > 0:
                    logger.info(LIBDDNS_UPDATE_DELETE_RRSET_NOT_EMPTY,
                                ClientFormatter(self.__client_addr),
                                ZoneFormatter(self.__zname, self.__zclass),
                                RRsetFormatter(rrset))
                    return Rcode.FORMERR()
                if rrset.get_type().get_code() >= 249 and\
                   rrset.get_type().get_code() <= 254:
                    logger.info(LIBDDNS_UPDATE_DELETE_BAD_TYPE,
                                ClientFormatter(self.__client_addr),
                                ZoneFormatter(self.__zname, self.__zclass),
                                RRsetFormatter(rrset))
                    return Rcode.FORMERR()
            elif rrset.get_class() == RRClass.NONE():
                if rrset.get_ttl().get_value() != 0:
                    logger.info(LIBDDNS_UPDATE_DELETE_RR_NONZERO_TTL,
                                ClientFormatter(self.__client_addr),
                                ZoneFormatter(self.__zname, self.__zclass),
                                RRsetFormatter(rrset))
                    return Rcode.FORMERR()
                if rrset.get_type().get_code() >= 249:
                    logger.info(LIBDDNS_UPDATE_DELETE_RR_BAD_TYPE,
                                ClientFormatter(self.__client_addr),
                                ZoneFormatter(self.__zname, self.__zclass),
                                RRsetFormatter(rrset))
                    return Rcode.FORMERR()
            else:
                logger.info(LIBDDNS_UPDATE_BAD_CLASS,
                            ClientFormatter(self.__client_addr),
                            ZoneFormatter(self.__zname, self.__zclass),
                            RRsetFormatter(rrset))
                return Rcode.FORMERR()
        return Rcode.NOERROR()

    def __do_update_add_single_rr(self, diff, rr, existing_rrset):
        '''Helper for __do_update_add_rrs_to_rrset: only add the
           rr if it is not present yet
           (note that rr here should already be a single-rr rrset)
        '''
        if existing_rrset is None:
            diff.add_data(rr)
        else:
            rr_rdata = rr.get_rdata()[0]
            if not rr_rdata in existing_rrset.get_rdata():
                diff.add_data(rr)

    def __do_update_add_rrs_to_rrset(self, diff, rrset):
        '''Add the rrs from the given rrset to the diff.
           There is handling for a number of special cases mentioned
           in RFC2136;
           - If the addition is a CNAME, but existing data at its
             name is not, the addition is ignored, and vice versa.
           - If it is a CNAME, and existing data is too, it is
             replaced (existing data is deleted)
           An additional restriction is that SOA data is ignored as
           well (it is handled separately by the __do_update method).

           Note that in the (near) future, this method may have
           addition special-cases processing.
        '''
        # For a number of cases, we may need to remove data in the zone
        # (note; SOA is handled separately by __do_update, so that one
        # is not explicitely ignored here)
        if rrset.get_type() == RRType.SOA():
            return
        result, orig_rrset, _ = self.__finder.find(rrset.get_name(),
                                                   rrset.get_type(),
                                                   ZoneFinder.NO_WILDCARD |
                                                   ZoneFinder.FIND_GLUE_OK)
        if result == self.__finder.CNAME:
            # Ignore non-cname rrs that try to update CNAME records
            # (if rrset itself is a CNAME, the finder result would be
            # SUCCESS, see next case)
            return
        elif result == ZoneFinder.SUCCESS:
            # if update is cname, and zone rr is not, ignore
            if rrset.get_type() == RRType.CNAME():
                # Remove original CNAME record (the new one
                # is added below)
                diff.delete_data(orig_rrset)
            # We do not have WKS support at this time, but if there
            # are special Update equality rules such as for WKS, and
            # we do have support for the type, this is where the check
            # (and potential delete) would go.
        elif result == ZoneFinder.NXRRSET:
            # There is data present, but not for this type.
            # If this type is CNAME, ignore the update
            if rrset.get_type() == RRType.CNAME():
                return
        foreach_rr_in_rrset(rrset, self.__do_update_add_single_rr, diff, rrset, orig_rrset)

    def __do_update_delete_rrset(self, diff, rrset):
        '''Deletes the rrset with the name and type of the given
           rrset from the zone data (by putting all existing data
           in the given diff as delete statements).
           Special cases: if the delete statement is for the
           zone's apex, and the type is either SOA or NS, it
           is ignored.'''
        result, to_delete, _ = self.__finder.find(rrset.get_name(),
                                                  rrset.get_type(),
                                                  ZoneFinder.NO_WILDCARD |
                                                  ZoneFinder.FIND_GLUE_OK)
        if to_delete.get_name() == self.__zname and\
           (to_delete.get_type() == RRType.SOA() or\
            to_delete.get_type() == RRType.NS()):
            # ignore
            return
        foreach_rr_in_rrset(to_delete, diff.delete_data, to_delete)

    def __ns_deleter_helper(self, diff, rrset):
        '''Special case helper for deleting NS resource records
           at the zone apex. In that scenario, the last NS record
           may never be removed (and any action that would do so
           should be ignored).
        '''
        result, orig_rrset, _ = self.__finder.find(rrset.get_name(),
                                                   rrset.get_type(),
                                                   ZoneFinder.NO_WILDCARD |
                                                   ZoneFinder.FIND_GLUE_OK)
        # Even a real rrset comparison wouldn't help here...
        # The goal is to make sure that after deletion of the
        # given rrset, at least 1 NS record is left (at the apex).
        # So we make a (shallow) copy of the existing rrset,
        # and for each rdata in the to_delete set, we check if it wouldn't
        # delete the last one. If it would, that specific one is ignored.
        # If it would not, the rdata is removed from the temporary list
        orig_rrset_rdata = copy.copy(orig_rrset.get_rdata())
        for rdata in rrset.get_rdata():
            if len(orig_rrset_rdata) == 1 and rdata == orig_rrset_rdata[0]:
                # ignore
                continue
            else:
                # create an individual RRset for deletion
                to_delete = isc.dns.RRset(rrset.get_name(),
                                          rrset.get_class(),
                                          rrset.get_type(),
                                          rrset.get_ttl())
                to_delete.add_rdata(rdata)
                orig_rrset_rdata.remove(rdata)
                diff.delete_data(to_delete)

    def __do_update_delete_name(self, diff, rrset):
        '''Delete all data at the name of the given rrset,
           by adding all data found by find_all as delete statements
           to the given diff.
           Special case: if the name is the zone's apex, SOA and
           NS records are kept.
        '''
        result, rrsets, flags = self.__finder.find_all(rrset.get_name(),
                                                       ZoneFinder.NO_WILDCARD |
                                                       ZoneFinder.FIND_GLUE_OK)
        if result == ZoneFinder.SUCCESS and\
           (flags & ZoneFinder.RESULT_WILDCARD == 0):
            for to_delete in rrsets:
                # if name == self.__zname and type is soa or ns, don't delete!
                if to_delete.get_name() == self.__zname and\
                   (to_delete.get_type() == RRType.SOA() or
                    to_delete.get_type() == RRType.NS()):
                    continue
                else:
                    foreach_rr_in_rrset(to_delete, diff.delete_data, to_delete)

    def __do_update_delete_rrs_from_rrset(self, diff, rrset):
        '''Deletes all resource records in the given rrset from the
           zone. Resource records that do not exist are ignored.
           If the rrset if of type SOA, it is ignored.
           Uses the __ns_deleter_helper if the rrset's name is the
           zone's apex, and the type is NS.
        '''
        # Delete all rrs in the rrset, except if name=self.__zname and type=soa, or
        # type = ns and there is only one left (...)

        # The delete does not want class NONE, we would not have gotten here
        # if it wasn't, but now is a good time to change it to the zclass.
        to_delete = convert_rrset_class(rrset, self.__zclass)

        if rrset.get_name() == self.__zname:
            if rrset.get_type() == RRType.SOA():
                # ignore
                return
            elif rrset.get_type() == RRType.NS():
                # hmm. okay. annoying. There must be at least one left,
                # delegate to helper method
                self.__ns_deleter_helper(diff, to_delete)
                return
        foreach_rr_in_rrset(to_delete, diff.delete_data, to_delete)

    def __update_soa(self, diff):
        '''Checks the member value __added_soa, and depending on
           whether it has been set and what its value is, creates
           a new SOA if necessary.
           Then removes the original SOA and adds the new one,
           by adding the needed operations to the given diff.'''
        # Get the existing SOA
        # if a new soa was specified, add that one, otherwise, do the
        # serial magic and add the newly created one

        # get it from DS and to increment and stuff
        result, old_soa, _ = self.__finder.find(self.__zname, RRType.SOA(),
                                                ZoneFinder.NO_WILDCARD |
                                                ZoneFinder.FIND_GLUE_OK)
        serial_operation = DDNS_SOA()
        if self.__added_soa is not None:
            # serial check goes here
            if serial_operation.soa_update_check(old_soa, self.__added_soa):
                new_soa = self.__added_soa
            else:
                pass
        else:
            new_soa = old_soa
            # increment goes here
            new_soa = serial_operation.update_soa(new_soa)

        diff.delete_data(old_soa)
        diff.add_data(new_soa)

    def __do_update(self):
        '''Scan, check, and execute the Update section in the
           DDNS Update message.
           Returns an Rcode to signal the result (NOERROR upon success,
           any error result otherwise).
        '''
        # prescan
        prescan_result = self.__do_prescan()
        if prescan_result != Rcode.NOERROR():
            return prescan_result

        # update
        try:
            # create an ixfr-out-friendly diff structure to work on
            diff = isc.xfrin.diff.Diff(self.__datasrc_client, self.__zname,
                                       journaling=True, single_update_mode=True)

            # Do special handling for SOA first
            self.__update_soa(diff)

            # Algorithm from RFC2136 Section 3.4
            # Note that this works on full rrsets, not individual RRs.
            # Some checks might be easier with individual RRs, but only if we
            # would use the ZoneUpdater directly (so we can query the
            # 'zone-as-it-would-be-so-far'. However, due to the current use
            # of the Diff class, this is not the case, and therefore it
            # is easier to work with full rrsets for the most parts
            # (less lookups needed; conversion to individual rrs is
            # the same offort whether it is done here or in the several
            # do_update statements)
            for rrset in self.__message.get_section(SECTION_UPDATE):
                if rrset.get_class() == self.__zclass:
                    self.__do_update_add_rrs_to_rrset(diff, rrset)
                elif rrset.get_class() == RRClass.ANY():
                    if rrset.get_type() == RRType.ANY():
                        self.__do_update_delete_name(diff, rrset)
                    else:
                        self.__do_update_delete_rrset(diff, rrset)
                elif rrset.get_class() == RRClass.NONE():
                    self.__do_update_delete_rrs_from_rrset(diff, rrset)

            diff.commit()
            return Rcode.NOERROR()
        except isc.datasrc.Error as dse:
            logger.info(LIBDDNS_UPDATE_DATASRC_ERROR, dse)
            return Rcode.SERVFAIL()
        except Exception as uce:
            logger.error(LIBDDNS_UPDATE_UNCAUGHT_EXCEPTION,
                         ClientFormatter(self.__client_addr),
                         ZoneFormatter(self.__zname, self.__zclass),
                         uce)
            return Rcode.SERVFAIL()
