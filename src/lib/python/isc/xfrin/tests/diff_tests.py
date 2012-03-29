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

import isc.log
import unittest
import isc.datasrc
from isc.dns import Name, RRset, RRClass, RRType, RRTTL, Rdata
from isc.xfrin.diff import Diff, NoSuchZone

class TestError(Exception):
    """
    Just to have something to be raised during the tests.
    Not used outside.
    """
    pass

class DiffTest(unittest.TestCase):
    """
    Tests for the isc.xfrin.diff.Diff class.

    It also plays role of a data source and an updater, so it can manipulate
    some test variables while being called.
    """
    def setUp(self):
        """
        This sets internal variables so we can see nothing was called yet.

        It also creates some variables used in multiple tests.
        """
        # Track what was called already
        self.__updater_requested = False
        self.__compact_called = False
        self.__data_operations = []
        self.__apply_called = False
        self.__commit_called = False
        self.__broken_called = False
        self.__warn_called = False
        self.__should_replace = False
        # Some common values
        self.__rrclass = RRClass.IN()
        self.__type = RRType.A()
        self.__ttl = RRTTL(3600)
        # And RRsets
        # Create two valid rrsets
        self.__rrset1 = RRset(Name('a.example.org.'), self.__rrclass,
                              self.__type, self.__ttl)
        self.__rdata = Rdata(self.__type, self.__rrclass, '192.0.2.1')
        self.__rrset1.add_rdata(self.__rdata)
        self.__rrset2 = RRset(Name('b.example.org.'), self.__rrclass,
                              self.__type, self.__ttl)
        self.__rrset2.add_rdata(self.__rdata)
        # And two invalid
        self.__rrset_empty = RRset(Name('empty.example.org.'), self.__rrclass,
                                   self.__type, self.__ttl)
        self.__rrset_multi = RRset(Name('multi.example.org.'), self.__rrclass,
                                   self.__type, self.__ttl)
        self.__rrset_multi.add_rdata(self.__rdata)
        self.__rrset_multi.add_rdata(Rdata(self.__type, self.__rrclass,
                                           '192.0.2.2'))

    def __mock_compact(self):
        """
        This can be put into the diff to hook into its compact method and see
        if it gets called.
        """
        self.__compact_called = True

    def __mock_apply(self):
        """
        This can be put into the diff to hook into its apply method and see
        it gets called.
        """
        self.__apply_called = True

    def __broken_operation(self, *args):
        """
        This can be used whenever an operation should fail. It raises TestError.
        It should take whatever amount of parameters needed, so it can be put
        quite anywhere.
        """
        self.__broken_called = True
        raise TestError("Test error")

    def warn(self, *args):
        """
        This is for checking the warn function was called, we replace the logger
        in the tested module.
        """
        self.__warn_called = True
        # Also log the message so we can check the log format (manually)
        self.orig_logger.warn(*args)

    def commit(self):
        """
        This is part of pretending to be a zone updater. This notes the commit
        was called.
        """
        self.__commit_called = True

    def add_rrset(self, rrset):
        """
        This one is part of pretending to be a zone updater. It writes down
        addition of an rrset was requested.
        """
        self.__data_operations.append(('add', rrset))

    def delete_rrset(self, rrset):
        """
        This one is part of pretending to be a zone updater. It writes down
        removal of an rrset was requested.
        """
        self.__data_operations.append(('delete', rrset))

    def get_class(self):
        """
        This one is part of pretending to be a zone updater. It returns
        the IN class.
        """
        return self.__rrclass

    def get_updater(self, zone_name, replace, journaling=False):
        """
        This one pretends this is the data source client and serves
        getting an updater.

        If zone_name is 'none.example.org.', it returns None, otherwise
        it returns self.
        """
        # The diff should not delete the old data.
        self.assertEqual(self.__should_replace, replace)
        self.__updater_requested = True
        if zone_name == Name('none.example.org.'):
            # Pretend this zone doesn't exist
            return None

        # If journaling is enabled, record the fact; for a special zone
        # pretend that we don't support journaling.
        if journaling:
            if zone_name == Name('nodiff.example.org'):
                raise isc.datasrc.NotImplemented('journaling not supported')
            self.__journaling_enabled = True
        else:
            self.__journaling_enabled = False

        return self

    def test_create(self):
        """
        This test the case when the diff is successfuly created. It just
        tries it does not throw and gets the updater.
        """
        diff = Diff(self, Name('example.org.'))
        self.assertTrue(self.__updater_requested)
        self.assertEqual([], diff.get_buffer())
        # By default journaling is disabled
        self.assertFalse(self.__journaling_enabled)

    def test_create_nonexist(self):
        """
        Try to create a diff on a zone that doesn't exist. This should
        raise a correct exception.
        """
        self.assertRaises(NoSuchZone, Diff, self, Name('none.example.org.'))
        self.assertTrue(self.__updater_requested)

    def test_create_withjournal(self):
        Diff(self, Name('example.org'), False, True)
        self.assertTrue(self.__journaling_enabled)

    def test_create_nojournal(self):
        Diff(self, Name('nodiff.example.org'), False, True)
        self.assertFalse(self.__journaling_enabled)

    def __data_common(self, diff, method, operation):
        """
        Common part of test for test_add and test_delte.
        """
        # Try putting there the bad data first
        self.assertRaises(ValueError, method, self.__rrset_empty)
        self.assertRaises(ValueError, method, self.__rrset_multi)
        # They were not added
        self.assertEqual([], diff.get_buffer())
        # Put some proper data into the diff
        method(self.__rrset1)
        method(self.__rrset2)
        dlist = [(operation, self.__rrset1), (operation, self.__rrset2)]
        self.assertEqual(dlist, diff.get_buffer())
        # Check the data are not destroyed by raising an exception because of
        # bad data
        self.assertRaises(ValueError, method, self.__rrset_empty)
        self.assertEqual(dlist, diff.get_buffer())

    def test_add(self):
        """
        Try to add few items into the diff and see they are stored in there.

        Also try passing an rrset that has differnt amount of RRs than 1.
        """
        diff = Diff(self, Name('example.org.'))
        self.__data_common(diff, diff.add_data, 'add')

    def test_delete(self):
        """
        Try scheduling removal of few items into the diff and see they are
        stored in there.

        Also try passing an rrset that has different amount of RRs than 1.
        """
        diff = Diff(self, Name('example.org.'))
        self.__data_common(diff, diff.delete_data, 'delete')

    def test_apply(self):
        """
        Schedule few additions and check the apply works by passing the
        data into the updater.
        """
        # Prepare the diff
        diff = Diff(self, Name('example.org.'))
        diff.add_data(self.__rrset1)
        diff.delete_data(self.__rrset2)
        dlist = [('add', self.__rrset1), ('delete', self.__rrset2)]
        self.assertEqual(dlist, diff.get_buffer())
        # Do the apply, hook the compact method
        diff.compact = self.__mock_compact
        diff.apply()
        # It should call the compact
        self.assertTrue(self.__compact_called)
        # And pass the data. Our local history of what happened is the same
        # format, so we can check the same way
        self.assertEqual(dlist, self.__data_operations)
        # And the buffer in diff should become empty, as everything
        # got inside.
        self.assertEqual([], diff.get_buffer())

    def test_commit(self):
        """
        If we call a commit, it should first apply whatever changes are
        left (we hook into that instead of checking the effect) and then
        the commit on the updater should have been called.

        Then we check it raises value error for whatever operation we try.
        """
        diff = Diff(self, Name('example.org.'))
        diff.add_data(self.__rrset1)
        orig_apply = diff.apply
        diff.apply = self.__mock_apply
        diff.commit()
        self.assertTrue(self.__apply_called)
        self.assertTrue(self.__commit_called)
        # The data should be handled by apply which we replaced.
        self.assertEqual([], self.__data_operations)
        # Now check all range of other methods raise ValueError
        self.assertRaises(ValueError, diff.commit)
        self.assertRaises(ValueError, diff.add_data, self.__rrset2)
        self.assertRaises(ValueError, diff.delete_data, self.__rrset1)
        diff.apply = orig_apply
        self.assertRaises(ValueError, diff.apply)
        # This one does not state it should raise, so check it doesn't
        # But it is NOP in this situation anyway
        diff.compact()

    def test_autoapply(self):
        """
        Test the apply is called all by itself after 100 tasks are added.
        """
        diff = Diff(self, Name('example.org.'))
        # A method to check the apply is called _after_ the 100th element
        # is added. We don't use it anywhere else, so we define it locally
        # as lambda function
        def check():
            self.assertEqual(100, len(diff.get_buffer()))
            self.__mock_apply()
        orig_apply = diff.apply
        diff.apply = check
        # If we put 99, nothing happens yet
        for i in range(0, 99):
            diff.add_data(self.__rrset1)
        expected = [('add', self.__rrset1)] * 99
        self.assertEqual(expected, diff.get_buffer())
        self.assertFalse(self.__apply_called)
        # Now we push the 100th and it should call the apply method
        # This will _not_ flush the data yet, as we replaced the method.
        # It, however, would in the real life.
        diff.add_data(self.__rrset1)
        # Now the apply method (which is replaced by our check) should
        # have been called. If it wasn't, this is false. If it was, but
        # still with 99 elements, the check would complain
        self.assertTrue(self.__apply_called)
        # Reset the buffer by calling the original apply.
        orig_apply()
        self.assertEqual([], diff.get_buffer())
        # Similar with delete
        self.__apply_called = False
        for i in range(0, 99):
            diff.delete_data(self.__rrset2)
        expected = [('delete', self.__rrset2)] * 99
        self.assertEqual(expected, diff.get_buffer())
        self.assertFalse(self.__apply_called)
        diff.delete_data(self.__rrset2)
        self.assertTrue(self.__apply_called)

    def test_compact(self):
        """
        Test the compaction works as expected, eg. it compacts only consecutive
        changes of the same operation and on the same domain/type.

        The test case checks that it does merge them, but also puts some
        different operations "in the middle", changes the type and name and
        places the same kind of change further away of each other to see they
        are not merged in that case.
        """
        diff = Diff(self, Name('example.org.'))
        # Check we can do a compact on empty data, it shouldn't break
        diff.compact()
        self.assertEqual([], diff.get_buffer())
        # This data is the way it should look like after the compact
        # ('operation', 'domain.prefix', 'type', ['rdata', 'rdata'])
        # The notes say why the each of consecutive can't be merged
        data = [
            ('add', 'a', 'A', ['192.0.2.1', '192.0.2.2']),
            # Different type.
            ('add', 'a', 'AAAA', ['2001:db8::1', '2001:db8::2']),
            # Different operation
            ('delete', 'a', 'AAAA', ['2001:db8::3']),
            # Different domain
            ('delete', 'b', 'AAAA', ['2001:db8::4']),
            # This does not get merged with the first, even if logically
            # possible. We just don't do this.
            ('add', 'a', 'A', ['192.0.2.3'])
            ]
        # Now, fill the data into the diff, in a "flat" way, one by one
        for (op, nprefix, rrtype, rdata) in data:
            name = Name(nprefix + '.example.org.')
            rrtype_obj = RRType(rrtype)
            for rdatum in rdata:
                rrset = RRset(name, self.__rrclass, rrtype_obj, self.__ttl)
                rrset.add_rdata(Rdata(rrtype_obj, self.__rrclass, rdatum))
                if op == 'add':
                    diff.add_data(rrset)
                else:
                    diff.delete_data(rrset)
        # Compact it
        diff.compact()
        # Now check they got compacted. They should be in the same order as
        # pushed inside. So it should be the same as data modulo being in
        # the rrsets and isc.dns objects.
        def check():
            buf = diff.get_buffer()
            self.assertEqual(len(data), len(buf))
            for (expected, received) in zip(data, buf):
                (eop, ename, etype, edata) = expected
                (rop, rrrset) = received
                self.assertEqual(eop, rop)
                ename_obj = Name(ename + '.example.org.')
                self.assertEqual(ename_obj, rrrset.get_name())
                # We check on names to make sure they are printed nicely
                self.assertEqual(etype, str(rrrset.get_type()))
                rdata = rrrset.get_rdata()
                self.assertEqual(len(edata), len(rdata))
                # It should also preserve the order
                for (edatum, rdatum) in zip(edata, rdata):
                    self.assertEqual(edatum, str(rdatum))
        check()
        # Try another compact does nothing, but survives
        diff.compact()
        check()

    def test_wrong_class(self):
        """
        Test a wrong class of rrset is rejected.
        """
        diff = Diff(self, Name('example.org.'))
        rrset = RRset(Name('a.example.org.'), RRClass.CH(), RRType.NS(),
                      self.__ttl)
        rrset.add_rdata(Rdata(RRType.NS(), RRClass.CH(), 'ns.example.org.'))
        self.assertRaises(ValueError, diff.add_data, rrset)
        self.assertRaises(ValueError, diff.delete_data, rrset)

    def __do_raise_test(self):
        """
        Do a raise test. Expects that one of the operations is exchanged for
        broken version.
        """
        diff = Diff(self, Name('example.org.'))
        diff.add_data(self.__rrset1)
        diff.delete_data(self.__rrset2)
        self.assertRaises(TestError, diff.commit)
        self.assertTrue(self.__broken_called)
        self.assertRaises(ValueError, diff.add_data, self.__rrset1)
        self.assertRaises(ValueError, diff.delete_data, self.__rrset2)
        self.assertRaises(ValueError, diff.commit)
        self.assertRaises(ValueError, diff.apply)

    def test_raise_add(self):
        """
        Test the exception from add_rrset is propagated and the diff can't be
        used afterwards.
        """
        self.add_rrset = self.__broken_operation
        self.__do_raise_test()

    def test_raise_delete(self):
        """
        Test the exception from delete_rrset is propagated and the diff can't be
        used afterwards.
        """
        self.delete_rrset = self.__broken_operation
        self.__do_raise_test()

    def test_raise_commit(self):
        """
        Test the exception from updater's commit gets propagated and it can't be
        used afterwards.
        """
        self.commit = self.__broken_operation
        self.__do_raise_test()

    def test_ttl(self):
        """
        Test the TTL handling. A warn function should have been called if they
        differ, but that's all, it should not crash or raise.
        """
        self.orig_logger = isc.xfrin.diff.logger
        try:
            isc.xfrin.diff.logger = self
            diff = Diff(self, Name('example.org.'))
            diff.add_data(self.__rrset1)
            rrset2 = RRset(Name('a.example.org.'), self.__rrclass,
                                  self.__type, RRTTL(120))
            rrset2.add_rdata(Rdata(self.__type, self.__rrclass, '192.10.2.2'))
            diff.add_data(rrset2)
            rrset2 = RRset(Name('a.example.org.'), self.__rrclass,
                                  self.__type, RRTTL(6000))
            rrset2.add_rdata(Rdata(self.__type, self.__rrclass, '192.10.2.3'))
            diff.add_data(rrset2)
            # They should get compacted together and complain.
            diff.compact()
            self.assertEqual(1, len(diff.get_buffer()))
            # The TTL stays on the first value, no matter if smaller or bigger
            # ones come later.
            self.assertEqual(self.__ttl, diff.get_buffer()[0][1].get_ttl())
            self.assertTrue(self.__warn_called)
        finally:
            isc.xfrin.diff.logger = self.orig_logger

    def test_rrsig_ttl(self):
        '''Similar to the previous test, but for RRSIGs of different covered
        types.

        They shouldn't be compacted.

        '''
        diff = Diff(self, Name('example.org.'))
        rrsig1 = RRset(Name('example.org'), self.__rrclass,
                       RRType.RRSIG(), RRTTL(3600))
        rrsig1.add_rdata(Rdata(RRType.RRSIG(), self.__rrclass,
                               'A 5 3 3600 20000101000000 20000201000000 ' +
                               '0 example.org. FAKEFAKEFAKE'))
        diff.add_data(rrsig1)
        rrsig2 = RRset(Name('example.org'), self.__rrclass,
                       RRType.RRSIG(), RRTTL(1800))
        rrsig2.add_rdata(Rdata(RRType.RRSIG(), self.__rrclass,
                               'AAAA 5 3 3600 20000101000000 20000201000000 ' +
                               '1 example.org. FAKEFAKEFAKE'))
        diff.add_data(rrsig2)
        diff.compact()
        self.assertEqual(2, len(diff.get_buffer()))

    def test_relpace(self):
        """
        Test that when we want to replace the whole zone, it is propagated.
        """
        self.__should_replace = True
        diff = Diff(self, "example.org.", True)
        self.assertTrue(self.__updater_requested)

if __name__ == "__main__":
    isc.log.init("bind10")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
