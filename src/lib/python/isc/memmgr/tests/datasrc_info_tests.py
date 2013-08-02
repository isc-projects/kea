# Copyright (C) 2013  Internet Systems Consortium.
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

import os
import unittest

from isc.dns import *
import isc.config
import isc.datasrc
import isc.log
from isc.server_common.datasrc_clients_mgr import DataSrcClientsMgr
from isc.memmgr.datasrc_info import *

# Defined for easier tests with DataSrcClientsMgr.reconfigure(), which
# only needs get_value() method
class MockConfigData:
    def __init__(self, data):
        self.__data = data

    def get_value(self, identifier):
        return self.__data[identifier], False

class TestSegmentInfo(unittest.TestCase):
    def setUp(self):
        self.__mapped_file_dir = os.environ['TESTDATA_WRITE_PATH']
        self.__sgmt_info = SegmentInfo.create('mapped', 0, RRClass.IN,
                                              'sqlite3',
                                              {'mapped_file_dir':
                                                   self.__mapped_file_dir})

    def __check_sgmt_reset_param(self, user_type, expected_ver):
        """Common check on the return value of get_reset_param() for
        MappedSegmentInfo.

        Unless it's expected to return None, it should be a map that
        maps "mapped-file" to the expected version of mapped-file.

        """
        if expected_ver is None:
            self.assertIsNone(self.__sgmt_info.get_reset_param(user_type))
            return
        param = self.__sgmt_info.get_reset_param(user_type)
        self.assertEqual(self.__mapped_file_dir +
                         '/zone-IN-0-sqlite3-mapped.' + str(expected_ver),
                         param['mapped-file'])

    def test_initial_params(self):
        self.__check_sgmt_reset_param(SegmentInfo.WRITER, 0)
        self.__check_sgmt_reset_param(SegmentInfo.READER, None)

        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.READY)
        self.assertEqual(len(self.__sgmt_info.get_readers()), 0)
        self.assertEqual(len(self.__sgmt_info.get_old_readers()), 0)
        self.assertEqual(len(self.__sgmt_info.get_events()), 0)

    def __si_to_ready_state(self):
        # Go to a default starting state
        self.__sgmt_info = SegmentInfo.create('mapped', 0, RRClass.IN,
                                              'sqlite3',
                                              {'mapped_file_dir':
                                                   self.__mapped_file_dir})
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.READY)

    def __si_to_updating_state(self):
        self.__si_to_ready_state()
        self.__sgmt_info.add_reader(3)
        self.__sgmt_info.add_event((42,))
        e = self.__sgmt_info.start_update()
        self.assertTupleEqual(e, (42,))
        self.assertSetEqual(self.__sgmt_info.get_readers(), {3})
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.UPDATING)

    def __si_to_synchronizing_state(self):
        self.__si_to_updating_state()
        self.__sgmt_info.complete_update()
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

    def __si_to_copying_state(self):
        self.__si_to_synchronizing_state()
        self.__sgmt_info.sync_reader(3)
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.COPYING)

    def test_add_event(self):
        self.assertEqual(len(self.__sgmt_info.get_events()), 0)
        self.__sgmt_info.add_event(None)
        self.assertEqual(len(self.__sgmt_info.get_events()), 1)
        self.assertListEqual(self.__sgmt_info.get_events(), [None])

    def test_add_reader(self):
        self.assertSetEqual(self.__sgmt_info.get_readers(), set())
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), set())
        self.__sgmt_info.add_reader(1)
        self.assertSetEqual(self.__sgmt_info.get_readers(), {1})
        self.__sgmt_info.add_reader(3)
        self.assertSetEqual(self.__sgmt_info.get_readers(), {1, 3})
        self.__sgmt_info.add_reader(2)
        self.assertSetEqual(self.__sgmt_info.get_readers(), {1, 2, 3})

        # adding the same existing reader must throw
        self.assertRaises(SegmentInfoError, self.__sgmt_info.add_reader, (1))
        # but the existing readers must be untouched
        self.assertSetEqual(self.__sgmt_info.get_readers(), {1, 3, 2})

        # none of this touches the old readers
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), set())

    def test_start_update(self):
        # in READY state
        # a) there are no events
        self.__si_to_ready_state()
        e = self.__sgmt_info.start_update()
        self.assertIsNone(e)
        # if there are no events, there is nothing to update
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.READY)

        # b) there are events. this is the same as calling
        # self.__si_to_updating_state(), but let's try to be
        # descriptive.
        self.__si_to_ready_state()
        self.__sgmt_info.add_event((42,))
        e = self.__sgmt_info.start_update()
        self.assertTupleEqual(e, (42,))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.UPDATING)

        # in UPDATING state, it should always raise an exception and not
        # change state.
        self.__si_to_updating_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.start_update)
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.UPDATING)

        # in SYNCHRONIZING state, it should always raise an exception
        # and not change state.
        self.__si_to_synchronizing_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.start_update)
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

        # in COPYING state, it should always raise an exception and not
        # change state.
        self.__si_to_copying_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.start_update)
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.COPYING)

    def test_complete_update(self):
        # in READY state
        self.__si_to_ready_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.complete_update)
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.READY)

        # in UPDATING state this is the same as calling
        # self.__si_to_synchronizing_state(), but let's try to be
        # descriptive.
        #
        # a) with no events
        self.__si_to_updating_state()
        e = self.__sgmt_info.complete_update()
        self.assertIsNone(e)
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

        # b) with events
        self.__si_to_updating_state()
        self.__sgmt_info.add_event((81,))
        e = self.__sgmt_info.complete_update()
        self.assertIsNone(e) # old_readers is not empty
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

        # c) with no readers, complete_update() from UPDATING must go
        # directly to READY state
        self.__si_to_ready_state()
        self.__sgmt_info.add_event((42,))
        e = self.__sgmt_info.start_update()
        self.assertTupleEqual(e, (42,))
        self.assertSetEqual(self.__sgmt_info.get_readers(), set())
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.UPDATING)
        e = self.__sgmt_info.complete_update()
        self.assertTupleEqual(e, (42,))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.READY)

        # in SYNCHRONIZING state
        self.__si_to_synchronizing_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.complete_update)
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

        # in COPYING state
        self.__si_to_copying_state()
        e = self.__sgmt_info.complete_update()
        self.assertIsNone(e)
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.READY)

    def test_sync_reader(self):
        # in READY state, it must raise an exception
        self.__si_to_ready_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.sync_reader, (0))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.READY)

        # in UPDATING state, it must raise an exception
        self.__si_to_updating_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.sync_reader, (0))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.UPDATING)

        # in COPYING state, it must raise an exception
        self.__si_to_copying_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.sync_reader, (0))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.COPYING)

        # in SYNCHRONIZING state:
        #
        # a) ID is not in old readers set. The following call sets up ID 3
        # to be in the old readers set.
        self.__si_to_synchronizing_state()
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {3})
        self.assertSetEqual(self.__sgmt_info.get_readers(), set())
        self.assertRaises(SegmentInfoError, self.__sgmt_info.sync_reader, (1))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

        # b) ID is in old readers set, but also in readers set.
        self.__si_to_synchronizing_state()
        self.__sgmt_info.add_reader(3)
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {3})
        self.assertSetEqual(self.__sgmt_info.get_readers(), {3})
        self.assertRaises(SegmentInfoError, self.__sgmt_info.sync_reader, (3))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

        # c) ID is in old readers set, but not in readers set, and
        # old_readers becomes empty.
        self.__si_to_synchronizing_state()
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {3})
        self.assertSetEqual(self.__sgmt_info.get_readers(), set())
        self.assertListEqual(self.__sgmt_info.get_events(), [(42,)])
        e = self.__sgmt_info.sync_reader(3)
        self.assertTupleEqual(e, (42,))
        # the ID should be moved from old readers to readers set
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), set())
        self.assertSetEqual(self.__sgmt_info.get_readers(), {3})
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.COPYING)

        # d) ID is in old readers set, but not in readers set, and
        # old_readers doesn't become empty.
        self.__si_to_updating_state()
        self.__sgmt_info.add_reader(4)
        self.__sgmt_info.complete_update()
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {3, 4})
        self.assertSetEqual(self.__sgmt_info.get_readers(), set())
        self.assertListEqual(self.__sgmt_info.get_events(), [(42,)])
        e = self.__sgmt_info.sync_reader(3)
        self.assertIsNone(e)
        # the ID should be moved from old readers to readers set
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {4})
        self.assertSetEqual(self.__sgmt_info.get_readers(), {3})
        # we should be left in SYNCHRONIZING state
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

    def test_remove_reader(self):
        # in READY state, it must raise an exception
        self.__si_to_ready_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.remove_reader, (0))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.READY)

        # in UPDATING state, it must raise an exception
        self.__si_to_updating_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.remove_reader, (0))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.UPDATING)

        # in COPYING state, it must raise an exception
        self.__si_to_copying_state()
        self.assertRaises(SegmentInfoError, self.__sgmt_info.remove_reader, (0))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.COPYING)

        # in SYNCHRONIZING state:
        #
        # a) ID is not in old readers set or readers set.
        self.__si_to_synchronizing_state()
        self.__sgmt_info.add_reader(4)
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {3})
        self.assertSetEqual(self.__sgmt_info.get_readers(), {4})
        self.assertListEqual(self.__sgmt_info.get_events(), [(42,)])
        self.assertRaises(SegmentInfoError, self.__sgmt_info.remove_reader, (1))
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

        # b) ID is in readers set.
        self.__si_to_synchronizing_state()
        self.__sgmt_info.add_reader(4)
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {3})
        self.assertSetEqual(self.__sgmt_info.get_readers(), {4})
        self.assertListEqual(self.__sgmt_info.get_events(), [(42,)])
        e = self.__sgmt_info.remove_reader(4)
        self.assertIsNone(e)
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {3})
        self.assertSetEqual(self.__sgmt_info.get_readers(), set())
        self.assertListEqual(self.__sgmt_info.get_events(), [(42,)])
        # we only change state if it was removed from old_readers
        # specifically and it became empty.
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

        # c) ID is in old_readers set and it becomes empty.
        self.__si_to_synchronizing_state()
        self.__sgmt_info.add_reader(4)
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {3})
        self.assertSetEqual(self.__sgmt_info.get_readers(), {4})
        self.assertListEqual(self.__sgmt_info.get_events(), [(42,)])
        e = self.__sgmt_info.remove_reader(3)
        self.assertTupleEqual(e, (42,))
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), set())
        self.assertSetEqual(self.__sgmt_info.get_readers(), {4})
        self.assertListEqual(self.__sgmt_info.get_events(), [])
        # we only change state if it was removed from old_readers
        # specifically and it became empty.
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.COPYING)

        # d) ID is in old_readers set and it doesn't become empty.
        self.__si_to_updating_state()
        self.__sgmt_info.add_reader(4)
        self.__sgmt_info.complete_update()
        self.__sgmt_info.add_reader(5)
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {3, 4})
        self.assertSetEqual(self.__sgmt_info.get_readers(), {5})
        self.assertListEqual(self.__sgmt_info.get_events(), [(42,)])
        e = self.__sgmt_info.remove_reader(3)
        self.assertIsNone(e)
        self.assertSetEqual(self.__sgmt_info.get_old_readers(), {4})
        self.assertSetEqual(self.__sgmt_info.get_readers(), {5})
        self.assertListEqual(self.__sgmt_info.get_events(), [(42,)])
        # we only change state if it was removed from old_readers
        # specifically and it became empty.
        self.assertEqual(self.__sgmt_info.get_state(), SegmentInfo.SYNCHRONIZING)

    def test_switch_versions(self):
        self.__sgmt_info.switch_versions()
        self.__check_sgmt_reset_param(SegmentInfo.WRITER, 1)
        self.__check_sgmt_reset_param(SegmentInfo.READER, 0)

        self.__sgmt_info.switch_versions()
        self.__check_sgmt_reset_param(SegmentInfo.WRITER, 0)
        self.__check_sgmt_reset_param(SegmentInfo.READER, 1)

    def test_init_others(self):
        # For local type of segment, information isn't needed and won't be
        # created.
        self.assertIsNone(SegmentInfo.create('local', 0, RRClass.IN,
                                             'sqlite3', {}))

        # Unknown type of segment will result in an exception.
        self.assertRaises(SegmentInfoError, SegmentInfo.create, 'unknown', 0,
                          RRClass.IN, 'sqlite3', {})

    def test_missing_methods(self):
        # Bad subclass of SegmentInfo that doesn't implement mandatory methods.
        class TestSegmentInfo(SegmentInfo):
            pass

        self.assertRaises(SegmentInfoError,
                          TestSegmentInfo().get_reset_param,
                          SegmentInfo.WRITER)
        self.assertRaises(SegmentInfoError, TestSegmentInfo().switch_versions)

class MockClientList:
    """A mock ConfigurableClientList class.

    Just providing minimal shortcut interfaces needed for DataSrcInfo class.

    """
    def __init__(self, status_list):
        self.__status_list = status_list

    def get_status(self):
        return self.__status_list

class TestDataSrcInfo(unittest.TestCase):
    def setUp(self):
        self.__mapped_file_dir = os.environ['TESTDATA_WRITE_PATH']
        self.__mgr_config = {'mapped_file_dir': self.__mapped_file_dir}
        self.__sqlite3_dbfile = os.environ['TESTDATA_WRITE_PATH'] + '/' + 'zone.db'
        self.__clients_map = {
            # mixture of 'local' and 'mapped' and 'unused' (type =None)
            # segments
            RRClass.IN: MockClientList([('datasrc1', 'local', None),
                                        ('datasrc2', 'mapped', None),
                                        ('datasrc3', None, None)]),
            RRClass.CH: MockClientList([('datasrc2', 'mapped', None),
                                        ('datasrc1', 'local', None)]) }

    def tearDown(self):
        if os.path.exists(self.__sqlite3_dbfile):
            os.unlink(self.__sqlite3_dbfile)

    def __check_sgmt_reset_param(self, sgmt_info, writer_file):
        # Check if the initial state of (mapped) segment info object has
        # expected values.
        self.assertIsNone(sgmt_info.get_reset_param(SegmentInfo.READER))
        param = sgmt_info.get_reset_param(SegmentInfo.WRITER)
        self.assertEqual(writer_file, param['mapped-file'])

    def test_init(self):
        """Check basic scenarios of constructing DataSrcInfo."""

        # This checks that all data sources of all RR classes are covered,
        # "local" segments are ignored, info objects for "mapped" segments
        # are created and stored in segment_info_map.
        datasrc_info = DataSrcInfo(42, self.__clients_map, self.__mgr_config)
        self.assertEqual(42, datasrc_info.gen_id)
        self.assertEqual(self.__clients_map, datasrc_info.clients_map)
        self.assertEqual(2, len(datasrc_info.segment_info_map))
        sgmt_info = datasrc_info.segment_info_map[(RRClass.IN, 'datasrc2')]
        self.__check_sgmt_reset_param(sgmt_info, self.__mapped_file_dir +
                                      '/zone-IN-42-datasrc2-mapped.0')
        sgmt_info = datasrc_info.segment_info_map[(RRClass.CH, 'datasrc2')]
        self.__check_sgmt_reset_param(sgmt_info, self.__mapped_file_dir +
                                      '/zone-CH-42-datasrc2-mapped.0')

        # A case where clist.get_status() returns an empty list; shouldn't
        # cause disruption
        self.__clients_map = { RRClass.IN: MockClientList([])}
        datasrc_info = DataSrcInfo(42, self.__clients_map, self.__mgr_config)
        self.assertEqual(42, datasrc_info.gen_id)
        self.assertEqual(0, len(datasrc_info.segment_info_map))

        # A case where clients_map is empty; shouldn't cause disruption
        self.__clients_map = {}
        datasrc_info = DataSrcInfo(42, self.__clients_map, self.__mgr_config)
        self.assertEqual(42, datasrc_info.gen_id)
        self.assertEqual(0, len(datasrc_info.segment_info_map))

    # This test uses real "mmaped" segment and doesn't work without shared
    # memory support.
    @unittest.skipIf(os.environ['HAVE_SHARED_MEMORY'] != 'yes',
                     'shared memory support is not available')
    def test_production(self):
        """Check the behavior closer to a production environment.

        Instead of using a mock classes, just for confirming we didn't miss
        something.

        """
        cfg_data = MockConfigData(
            {"classes":
                 {"IN": [{"type": "sqlite3", "cache-enable": True,
                          "cache-type": "mapped", "cache-zones": [],
                          "params": {"database_file": self.__sqlite3_dbfile}}]
                  }
             })
        cmgr = DataSrcClientsMgr(use_cache=True)
        cmgr.reconfigure({}, cfg_data)

        genid, clients_map = cmgr.get_clients_map()
        datasrc_info = DataSrcInfo(genid, clients_map, self.__mgr_config)

        self.assertEqual(1, datasrc_info.gen_id)
        self.assertEqual(clients_map, datasrc_info.clients_map)
        self.assertEqual(1, len(datasrc_info.segment_info_map))
        sgmt_info = datasrc_info.segment_info_map[(RRClass.IN, 'sqlite3')]
        self.assertIsNone(sgmt_info.get_reset_param(SegmentInfo.READER))

if __name__ == "__main__":
    isc.log.init("bind10-test")
    isc.log.resetUnitTestRootLogger()
    unittest.main()
