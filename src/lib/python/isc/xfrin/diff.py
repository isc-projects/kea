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

import isc.dns

class NoSuchZone(Exception):
    """
    This is raised if a diff for non-existant zone is being created.
    """
    pass

"""
This is the amount of changes we accumulate before calling Diff.apply
automatically.

The number 100 is just taken from Bind9. We don't know the rationale
for exactly this amount, but we think it is just some randomly chosen
number.
"""
# If changing this, modify the tests accordingly as well.
DIFF_APPLY_TRESHOLD = 100

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

    def __check_commited(self):
        """
        This checks if the diff is already commited. If it is, it raises
        ValueError. This check is for methods that need to work only on
        yet uncommited diffs.
        """
        if self.__updater is None:
            raise ValueError("The diff is already commited, you come late")

    def __data_common(self, rr, operation):
        """
        Schedules an operation with rr.

        It does all the real work of add_data and remove_data, including
        all checks.
        """
        self.__check_commited()
        if rr.get_rdata_count() != 1:
            raise ValueError('The rrset must contain exactly 1 Rdata, but ' +
                             'it holds ' + str(rr.get_rdata_count()))
        self.__buffer.append((operation, rr))
        if len(self.__buffer) >= DIFF_APPLY_TRESHOLD:
            # Time to auto-apply, so the data don't accumulate too much
            self.apply()

    def add_data(self, rr):
        """
        Schedules addition of an RR into the zone in this diff.

        The rr is of isc.dns.RRset type and it must contain only one RR.
        If this is not the case or if the diff was already commited, this
        raises the ValueError exception.
        """
        self.__data_common(rr, 'add')

    def remove_data(self, rr):
        """
        Schedules removal of an RR from the zone in this diff.

        The rr is of isc.dns.RRset type and it must contain only one RR.
        If this is not the case or if the diff was already commited, this
        raises the ValueError exception.
        """
        self.__data_common(rr, 'remove')

    def compact(self):
        """
        Tries to compact the operations in buffer a little by putting some of
        the operations together, forming RRsets with more than one RR.

        This is called by apply before putting the data into datasource. You
        may, but not have to, call this manually.

        Currently it merges consecutive same operations on the same
        domain/type. We could do more fancy things, like sorting by the domain
        and do more merging, but such diffs should be rare in practice anyway,
        so we don't bother and do it this simple way.
        """
        buf = []
        for (op, rrset) in self.__buffer:
            old = buf[-1][1] if len(buf) > 0 else None
            if old is None or op != buf[-1][0] or \
                rrset.get_name() != old.get_name() or \
                rrset.get_type() != old.get_type():
                buf.append((op, isc.dns.RRset(rrset.get_name(),
                                              rrset.get_class(),
                                              rrset.get_type(),
                                              rrset.get_ttl())))
            for rdatum in rrset.get_rdata():
                buf[-1][1].add_rdata(rdatum)
        self.__buffer = buf

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

        It also can raise isc.datasrc.Error. If that happens, you should stop
        using this object and abort the modification.
        """
        self.__check_commited()
        # First, compact the data
        self.compact()
        # Then pass the data inside the data source
        for (operation, rrset) in self.__buffer:
            if operation == 'add':
                self.__updater.add_rrset(rrset)
            elif operation == 'remove':
                self.__updater.remove_rrset(rrset)
            else:
                raise ValueError('Unknown operation ' + operation)
        # As everything is already in, drop the buffer
        self.__buffer = []

    def commit(self):
        """
        Writes all the changes into the data source and makes them visible.
        This closes the diff, you may not use it any more. If you try to use
        it, you'll get ValueError.

        This might raise isc.datasrc.Error.
        """
        self.__check_commited()
        # Push the data inside the data source
        self.apply()
        # Make sure they are visible.
        self.__updater.commit()
        # Remove the updater. That will free some resources for one, but
        # mark this object as already commited, so we can check
        self.__updater = None

    def get_buffer(self):
        """
        Returns the current buffer of changes not yet passed into the data
        source. It is in a form like [('add', rrset), ('remove', rrset),
        ('remove', rrset), ...].

        Probably useful only for testing and introspection purposes. Don't
        modify the list.
        """
        return self.__buffer
