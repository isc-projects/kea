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

""" This is a logging utility module for other modules of the ddns library
package.

"""

import isc.log

# The logger for this package
logger = isc.log.Logger('libddns')

class ClientFormatter:
    """A utility class to convert a client address to string.

    This class is constructed with a Python standard socket address tuple.
    If it's 2-element tuple, it's assumed to be an IPv4 socket address
    and will be converted to the form of '<addr>:<port>(/key=<tsig-key>)'.
    If it's 4-element tuple, it's assumed to be an IPv6 socket address.
    and will be converted to the form of '[<addr>]:<por>(/key=<tsig-key>)'.
    The optional key=<tsig-key> will be added if a TSIG record is given
    on construction.  tsig-key is the TSIG key name in that case.

    This class is designed to delay the conversion until it's explicitly
    requested, so the conversion doesn't happen if the corresponding log
    message is suppressed because of its log level (which is often the case
    for debug messages).

    Note: this optimization comes with the cost of instantiating the
    formatter object itself.  It's not really clear which overhead is
    heavier, and we may conclude it's actually better to just generate
    the strings unconditionally.  Alternatively, we can make the stored
    address of this object replaceable so that this object can be reused.
    Right now this is an open issue.

    """
    def __init__(self, addr, tsig_record=None):
        self.__addr = addr
        self.__tsig_record = tsig_record

    def __format_addr(self):
        if len(self.__addr) == 2:
            return self.__addr[0] + ':' + str(self.__addr[1])
        elif len(self.__addr) == 4:
            return '[' + self.__addr[0] + ']:' + str(self.__addr[1])
        return None

    def __str__(self):
        format = self.__format_addr()
        if format is not None and self.__tsig_record is not None:
            format += '/key=' + self.__tsig_record.get_name().to_text(True)
        return format

class ZoneFormatter:
    """A utility class to convert zone name and class to string.

    This class is constructed with a name of a zone (isc.dns.Name object)
    and its RR class (isc.dns.RRClass object).  Its text conversion method
    (__str__) converts them into a string in the form of
    '<zone name>/<zone class>' where the trailing dot of the zone name
    is omitted.

    If the given zone name on construction is None, it's assumed to be
    the zone isn't identified but needs to be somehow logged.  The conversion
    method returns a special string to indicate this case.

    This class is designed to delay the conversion until it's explicitly
    requested, so the conversion doesn't happen if the corresponding log
    message is suppressed because of its log level (which is often the case
    for debug messages).

    See the note for the ClientFormatter class about overhead tradeoff.
    This class shares the same discussion.

    """
    def __init__(self, zname, zclass):
        self.__zname = zname
        self.__zclass = zclass

    def __str__(self):
        if self.__zname is None:
            return '(zone unknown/not determined)'
        return self.__zname.to_text(True) + '/' + self.__zclass.to_text()

class RRsetFormatter:
    """A utility class to convert rrsets to a short descriptive string.

    This class is constructed with an rrset (isc.dns.RRset object).
    Its text conversion method (__str__) converts it into a string
    with only the name, class and type of the rrset.
    This is used in logging so that the RRset can be identified, without
    being completely printed, which would result in an unnecessary
    multi-line message.

    This class is designed to delay the conversion until it's explicitly
    requested, so the conversion doesn't happen if the corresponding log
    message is suppressed because of its log level.

    See the note for the ClientFormatter class about overhead tradeoff.
    This class shares the same discussion.
    """
    def __init__(self, rrset):
        self.__rrset = rrset

    def __str__(self):
        return self.__rrset.get_name().to_text() + " " +\
               self.__rrset.get_class().to_text() + " " +\
               self.__rrset.get_type().to_text()
