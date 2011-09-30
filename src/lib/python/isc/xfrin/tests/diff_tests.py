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
from isc.dns import Name, RRset, RRClass, RRType, RRTTL, Rdata
from isc.xfrin.diff import Diff, NoSuchZone

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

    def remove_rrset(self, rrset):
        """
        This one is part of pretending to be a zone updater. It writes down
        removal of an rrset was requested.
        """
        self.__data_operations.append(('remove', rrset))

    def get_updater(self, zone_name, replace):
        """
        This one pretends this is the data source client and serves
        getting an updater.

        If zone_name is 'none.example.org.', it returns None, otherwise
        it returns self.
        """
        # The diff should not delete the old data.
        self.assertFalse(replace)
        self.__updater_requested = True
        # Pretend this zone doesn't exist
        if zone_name == Name('none.example.org.'):
            return None
        else:
            return self

    def test_create(self):
        """
        This test the case when the diff is successfuly created. It just
        tries it does not throw and gets the updater.
        """
        diff = Diff(self, Name('example.org.'))
        self.assertTrue(self.__updater_requested)
        self.assertEqual([], diff.get_buffer())

    def test_create_nonexist(self):
        """
        Try to create a diff on a zone that doesn't exist. This should
        raise a correct exception.
        """
        self.assertRaises(NoSuchZone, Diff, self, Name('none.example.org.'))
        self.assertTrue(self.__updater_requested)

    def __data_common(self, diff, method, name):
        """
        Common part of test for test_add and test_remove.
        """
        # Try putting there the bad data first
        self.assertRaises(ValueError, method, self.__rrset_empty)
        self.assertRaises(ValueError, method, self.__rrset_multi)
        # They were not added
        self.assertEqual([], diff.get_buffer())
        # Add some proper data
        method(self.__rrset1)
        method(self.__rrset2)
        dlist = [(name, self.__rrset1), (name, self.__rrset2)]
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

    def test_remove(self):
        """
        Try scheduling removal of few items into the diff and see they are
        stored in there.

        Also try passing an rrset that has different amount of RRs than 1.
        """
        diff = Diff(self, Name('example.org.'))
        self.__data_common(diff, diff.remove_data, 'remove')

    def test_apply(self):
        """
        Schedule few additions and check the apply works by passing the
        data into the updater.
        """
        # Prepare the diff
        diff = Diff(self, Name('example.org.'))
        diff.add_data(self.__rrset1)
        diff.remove_data(self.__rrset2)
        dlist = [('add', self.__rrset1), ('remove', self.__rrset2)]
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
        self.assertRaises(ValueError, diff.remove_data, self.__rrset1)
        diff.apply = orig_apply
        self.assertRaises(ValueError, diff.apply)
        # This one does not state it should raise, so check it doesn't
        # But it is NOP in this situation anyway
        diff.compact()

if __name__ == "__main__":
    isc.log.init("bind10")
    unittest.main()
