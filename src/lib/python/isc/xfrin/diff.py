# Copyright (C) 2011  Internet Systems Consortium.
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

"""
This helps the XFR in process with accumulating parts of diff and applying
it to the datasource.
"""

class NoSuchZone(Exception):
    """
    This is raised if a diff for non-existant zone is being created.
    """
    pass

class Diff:
    """
    The class represents a diff against current state of datasource on
    one zone. The usual way of working with it is creating it, then putting
    bunch of changes in and commiting at the end.

    If you change your mind, you can just stop using the object without
    really commiting it. In that case no changes will happen in the data
    sounce.

    The class works as a kind of a buffer as well, it does not direct
    the changes to underlying data source right away, but keeps them for
    a while.
    """
    def __init__(self, datasource, zone):
        """
        Initializes the diff to a ready state. It checks the zone exists
        in the datasource and if not, NoSuchZone is raised. This also creates
        a transaction in the data source.

        The datasource is the one containing the zone. Zone is isc.dns.Name
        object representing the name of the zone (its apex).

        You can also expect isc.datasrc.Error or isc.datasrc.NotImplemented
        exceptions.
        """
        self.__updater = datasource.get_updater(zone, False)
        if self.__updater is None:
            # The no such zone case
            raise NoSuchZone("Zone " + str(zone) +
                             " does not exist in the data source " +
                             str(datasource))
        self.__buffer = []

    def add_data(self, rr):
        """
        Schedules addition of an RR into the zone in this diff.

        The rr is of isc.dns.RRset type and it must contain only one RR.
        If this is not the case or if the diff was already commited, this
        raises the ValueError exception.
        """
        if rr.get_rdata_count() != 1:
            raise ValueError('The rrset must contain exactly 1 Rdata, but ' +
                             'it holds ' + str(rr.get_rdata_count()))
        self.__buffer.append(('add', rr))

    def remove_data(self, rr):
        """
        Schedules removal of an RR from the zone in this diff.

        The rr is of isc.dns.RRset type and it must contain only one RR.
        If this is not the case or if the diff was already commited, this
        raises the ValueError exception.
        """
        pass

    def apply(self):
        """
        Push the buffered changes inside this diff down into the data source.
        This does not stop you from adding more changes later through this
        diff and it does not close the datasource transaction, so the changes
        will not be shown to others yet. It just means the internal memory
        buffer is flushed.

        This is called from time to time automatically, but you can call it
        manually if you really want to.

        This raises ValueError if the diff was already commited.

        It also can raise isc.datasrc.Error.
        """
        pass

    def commit(self):
        """
        Writes all the changes into the data source and makes them visible.
        This closes the diff, you may not use it any more. If you try to use
        it, you'll get ValueError.

        This might raise isc.datasrc.Error.
        """
        pass

    def get_buffer(self):
        """
        Returns the current buffer of changes not yet passed into the data
        source. It is in a form like [('add', rrset), ('remove', rrset),
        ('remove', rrset), ...].

        Probably useful only for testing and introspection purposes.
        """
        return self.__buffer
