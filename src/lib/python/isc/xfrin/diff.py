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
it to the datasource. It also has a 'single update mode' which is useful
for DDNS.

The name of the module is not yet fully decided. We might want to move it
under isc.datasrc or somewhere else, because we are reusing it with DDNS.
But for now, it lives here.
"""

import isc.dns
import isc.log
from isc.log_messages.libxfrin_messages import *

class NoSuchZone(Exception):
    """
    This is raised if a diff for non-existant zone is being created.
    """
    pass

"""
This is the amount of changes we accumulate before calling Diff.apply
automatically.

The number 100 is just taken from BIND 9. We don't know the rationale
for exactly this amount, but we think it is just some randomly chosen
number.
"""
# If changing this, modify the tests accordingly as well.
DIFF_APPLY_TRESHOLD = 100

logger = isc.log.Logger('libxfrin')

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
    def __init__(self, ds_client, zone, replace=False, journaling=False,
                 single_update_mode=False):
        """
        Initializes the diff to a ready state. It checks the zone exists
        in the datasource and if not, NoSuchZone is raised. This also creates
        a transaction in the data source.

        The ds_client is the datasource client containing the zone. Zone is
        isc.dns.Name object representing the name of the zone (its apex).
        If replace is True, the content of the whole zone is wiped out before
        applying the diff.

        If journaling is True, the history of subsequent updates will be
        recorded as well as the updates themselves as long as the underlying
        data source support the journaling.  If the data source allows
        incoming updates but does not support journaling, the Diff object
        will still continue applying the diffs with disabling journaling.

        If single_update_mode is true, the update is expected to only contain
        1 set of changes (i.e. one set of additions, and one set of deletions).
        If so, the additions and deletions are kept separately, and applied
        in one go upon commit() or apply(). In this mode, additions and
        deletions can be done in any order. The first addition and the
        first addition still have to be the new and old SOA records,
        respectively. Once apply() or commit() has been called, this
        requirement is renewed (since the diff object is essentialy reset).

        In this single_update_mode, upon commit, the deletions are performed
        first, and then the additions. With the previously mentioned
        restrictions, this means that the actual update looks like a single
        IXFR changeset (which can then be journaled). Apart from those
        restrictions, this class does not do any checking of data; it is
        the caller's responsibility to keep the data 'sane', and this class
        does not presume to have any knowledge of DNS zone content sanity.
        For instance, while it enforces the SOA to be deleted first, and added
        first, it does no checks on the SERIAL value.

        You can also expect isc.datasrc.Error or isc.datasrc.NotImplemented
        exceptions.
        """
        try:
            self.__updater = ds_client.get_updater(zone, replace, journaling)
        except isc.datasrc.NotImplemented as ex:
            if not journaling:
                raise ex
            self.__updater = ds_client.get_updater(zone, replace, False)
            logger.info(LIBXFRIN_NO_JOURNAL, zone, ds_client)
        if self.__updater is None:
            # The no such zone case
            raise NoSuchZone("Zone " + str(zone) +
                             " does not exist in the data source " +
                             str(ds_client))
        self.__single_update_mode = single_update_mode
        if single_update_mode:
            self.__additions = []
            self.__deletions = []
        else:
            self.__buffer = []

    def __check_commited(self):
        """
        This checks if the diff is already commited or broken. If it is, it
        raises ValueError. This check is for methods that need to work only on
        yet uncommited diffs.
        """
        if self.__updater is None:
            raise ValueError("The diff is already commited or it has raised " +
                             "an exception, you come late")

    def __data_common(self, rr, operation):
        """
        Schedules an operation with rr.

        It does all the real work of add_data and delete_data, including
        all checks.

        Raises a ValueError in several cases:
        - if the rrset contains multiple rrs
        - if the class of the rrset does not match that of the update
        - in single_update_mode if the first rr is not of type SOA (both
          for addition and deletion)
        - in single_update_mode if any later rr is of type SOA (both for
          addition and deletion)
        """
        self.__check_commited()
        if rr.get_rdata_count() != 1:
            raise ValueError('The rrset must contain exactly 1 Rdata, but ' +
                             'it holds ' + str(rr.get_rdata_count()))
        if rr.get_class() != self.__updater.get_class():
            raise ValueError("The rrset's class " + str(rr.get_class()) +
                             " does not match updater's " +
                             str(self.__updater.get_class()))
        if self.__single_update_mode:
            if operation == 'add':
                # First addition must be SOA
                if len(self.__additions) == 0 and\
                   rr.get_type() != isc.dns.RRType.SOA():
                    raise ValueError("First addition in single update mode " +
                                     "must be of type SOA")
                # And later additions may not
                elif len(self.__additions) != 0 and\
                   rr.get_type() == isc.dns.RRType.SOA():
                    raise ValueError("Multiple SOA records in single " +
                                     "update mode addition")
                self.__additions.append((operation, rr))
            elif operation == 'delete':
                if len(self.__deletions) == 0 and\
                   rr.get_type() != isc.dns.RRType.SOA():
                    raise ValueError("First deletion in single update mode " +
                                     "must be of type SOA")
                # And later deletions may not
                elif len(self.__deletions) != 0 and\
                   rr.get_type() == isc.dns.RRType.SOA():
                    raise ValueError("Multiple SOA records in single " +
                                     "update mode deletion")
                self.__deletions.append((operation, rr))
        else:
            self.__buffer.append((operation, rr))
            if len(self.__buffer) >= DIFF_APPLY_TRESHOLD:
                # Time to auto-apply, so the data don't accumulate too much
                # This is not done for DDNS type data
                self.apply()

    def add_data(self, rr):
        """
        Schedules addition of an RR into the zone in this diff.

        The rr is of isc.dns.RRset type and it must contain only one RR.
        If this is not the case or if the diff was already commited, this
        raises the ValueError exception.

        The rr class must match the one of the datasource client. If
        it does not, ValueError is raised.
        """
        self.__data_common(rr, 'add')

    def delete_data(self, rr):
        """
        Schedules deleting an RR from the zone in this diff.

        The rr is of isc.dns.RRset type and it must contain only one RR.
        If this is not the case or if the diff was already commited, this
        raises the ValueError exception.

        The rr class must match the one of the datasource client. If
        it does not, ValueError is raised.
        """
        self.__data_common(rr, 'delete')


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
        def same_type(rrset1, rrset2):
            '''A helper routine to identify whether two RRsets are of the
            same 'type'.  For RRSIGs we should consider type covered, too.
            '''
            if rrset1.get_type() != isc.dns.RRType.RRSIG() or \
                    rrset2.get_type != isc.dns.RRType.RRSIG():
                return rrset1.get_type() == rrset2.get_type()
            # RR type of the both RRsets is RRSIG.  Compare type covered.
            # We know they have exactly one RDATA.
            sigdata1 = rrset1.get_rdata()[0].to_text().split()[0]
            sigdata2 = rrset2.get_rdata()[0].to_text().split()[0]
            return sigdata1 == sigdata2

        def compact_buffer(buffer_to_compact):
            '''Internal helper function for compacting buffers, compacts the
               given buffer.
               Returns the compacted buffer.
            '''
            buf = []
            for (op, rrset) in buffer_to_compact:
                old = buf[-1][1] if len(buf) > 0 else None
                if old is None or op != buf[-1][0] or \
                    rrset.get_name() != old.get_name() or \
                    (not same_type(rrset, old)):
                    buf.append((op, isc.dns.RRset(rrset.get_name(),
                                                  rrset.get_class(),
                                                  rrset.get_type(),
                                                  rrset.get_ttl())))
                if rrset.get_ttl() != buf[-1][1].get_ttl():
                    logger.warn(LIBXFRIN_DIFFERENT_TTL, rrset.get_ttl(),
                                buf[-1][1].get_ttl(), rrset.get_name(),
                                rrset.get_class(), rrset.get_type())
                for rdatum in rrset.get_rdata():
                    buf[-1][1].add_rdata(rdatum)
            return buf

        if self.__single_update_mode:
            self.__additions = compact_buffer(self.__additions)
            self.__deletions = compact_buffer(self.__deletions)
        else:
            self.__buffer = compact_buffer(self.__buffer)

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
        def apply_buffer(buf):
            '''
            Helper method to apply all operations in the given buffer
            '''
            for (operation, rrset) in buf:
                if operation == 'add':
                    self.__updater.add_rrset(rrset)
                elif operation == 'delete':
                    self.__updater.delete_rrset(rrset)
                else:
                    raise ValueError('Unknown operation ' + operation)

        self.__check_commited()
        # First, compact the data
        self.compact()
        try:
            # Then pass the data inside the data source
            if self.__single_update_mode:
                apply_buffer(self.__deletions)
                apply_buffer(self.__additions)
            else:
                apply_buffer(self.__buffer)

            # As everything is already in, drop the buffer
        except:
            # If there's a problem, we can't continue.
            self.__updater = None
            raise

        # all went well, reset state of buffers
        if self.__single_update_mode:
            self.__additions = []
            self.__deletions = []
        else:
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
        try:
            self.__updater.commit()
        finally:
            # Remove the updater. That will free some resources for one, but
            # mark this object as already commited, so we can check

            # We delete it even in case the commit failed, as that makes us
            # unusable.
            self.__updater = None

    def get_buffer(self):
        """
        Returns the current buffer of changes not yet passed into the data
        source. It is in a form like [('add', rrset), ('delete', rrset),
        ('delete', rrset), ...].

        Probably useful only for testing and introspection purposes. Don't
        modify the list.

        Raises a ValueError if the buffer is in single_update_mode.
        """
        if self.__single_update_mode:
            raise ValueError("Compound buffer requested in single-update mode")
        else:
            return self.__buffer

    def get_single_update_buffers(self):
        """
        Returns the current buffers of changes not yet passed into the data
        source. It is a tuple of the current deletions and additions, which
        each are in a form like [('add', rrset), ('delete', rrset),
        ('delete', rrset), ...].

        Probably useful only for testing and introspection purposes. Don't
        modify the list.

        Raises a ValueError if the buffer is not in single_update_mode.
        """
        if not self.__single_update_mode:
            raise ValueError("Separate buffers requested in single-update mode")
        else:
            return (self.__deletions, self.__additions)
