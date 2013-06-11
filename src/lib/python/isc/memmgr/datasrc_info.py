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
import json

class SegmentInfoError(Exception):
    """An exception raised for general errors in the SegmentInfo class."""
    pass

class SegmentInfo:
    """A base class to maintain information about memory segments.

    An instance of this class corresponds to the memory segment used
    for in-memory cache of a specific single data source.  It manages
    information to set/reset the latest effective segment (such as
    path to a memory mapped file) and sets of other modules using the
    segment.

    Since there can be several different types of memory segments,
    the top level class provides abstract interfaces independent from
    segment-type specific details.  Such details are expected to be
    delegated to subclasses corresponding to specific types of segments.

    The implementation is still incomplete.  It will have more attributes
    such as a set of current readers, methods for adding or deleting
    the readers.  These will probably be implemented in this base class
    as they will be independent from segment-type specific details.

    """
    # Common constants of user type: reader or writer
    READER = 0
    WRITER = 1

    def create(type, genid, rrclass, datasrc_name, mgr_config):
        """Factory of specific SegmentInfo subclass instance based on the
        segment type.

        This is specifically for the memmgr, and segments that are not of
        its interest will be ignored.  This method returns None in these
        cases.  At least 'local' type segments will be ignored this way.

        If an unknown type of segment is specified, this method throws an
        SegmentInfoError exception.  The assumption is that this method
        is called after the corresponding data source configuration has been
        validated, at which point such unknown segments should have been
        rejected.

        Parameters:
          type (str or None): The type of memory segment; None if the segment
              isn't used.
          genid (int): The generation ID of the corresponding data source
              configuration.
          rrclass (isc.dns.RRClass): The RR class of the data source.
          datasrc_name (str): The name of the data source.
          mgr_config (dict): memmgr configuration related to memory segment
              information.  The content of the dict is type specific; each
              subclass is expected to know which key is necessary and the
              semantics of its value.

        """
        if type == 'mapped':
            return MappedSegmentInfo(genid, rrclass, datasrc_name, mgr_config)
        elif type is None or type == 'local':
            return None
        raise SegmentInfoError('unknown segment type to create info: ' + type)

    def get_reset_param(self, user_type):
        """Return parameters to reset the zone table memory segment.

        It returns a json expression in string that contains parameters for
        the specified type of user to reset a zone table segment with
        isc.datasrc.ConfigurableClientList.reset_memory_segment().
        It can also be passed to the user module as part of command
        parameters.

        Each subclass must implement this method.

        Parameter:
          user_type (READER or WRITER): specifies the type of user to reset
              the segment.

        """
        raise SegmentInfoError('get_reset_param is not implemented')

    def switch_versions(self):
        """Switch internal information for the reader segment and writer
        segment.

        This method is expected to be called when the writer on one version
        of memory segment completes updates and the memmgr is going to
        have readers switch to the updated version.  Details of the
        information to be switched would depend on the segment type, and
        are delegated to the specific subclass.

        Each subclass must implement this method.

        """
        raise SegmentInfoError('switch_versions is not implemented')

class MappedSegmentInfo(SegmentInfo):
    """SegmentInfo implementation of 'mapped' type memory segments.

    It maintains paths to mapped files both readers and the writer.

    While objets of this class are expected to be shared by multiple
    threads, it assumes operations are serialized through message passing,
    so access to this class itself is not protected by any explicit
    synchronization mechanism.

    """
    def __init__(self, genid, rrclass, datasrc_name, mgr_config):
        super().__init__()

        # Something like "/var/bind10/zone-IN-1-sqlite3-mapped"
        self.__mapped_file_base = mgr_config['mapped_file_dir'] + os.sep + \
            'zone-' + str(rrclass) + '-' + str(genid) + '-' + datasrc_name + \
            '-mapped'

        # Current versions (suffix of the mapped files) for readers and the
        # writer.  In this initial implementation we assume that all possible
        # readers are waiting for a new version (not using pre-existing one),
        # and the writer is expected to build a new segment as version "0".
        self.__reader_ver = None # => 0 => 1 => 0 => 1 ...
        self.__writer_ver = 0    # => 1 => 0 => 1 => 0 ...

    def get_reset_param(self, user_type):
        ver = self.__reader_ver if user_type == self.READER else \
            self.__writer_ver
        if ver is None:
            return None
        mapped_file = self.__mapped_file_base + '.' + str(ver)
        return json.dumps({'mapped-file': mapped_file})

    def switch_versions(self):
        # Swith the versions as noted in the constructor.
        self.__writer_ver ^= 1

        if self.__reader_ver is None:
            self.__reader_ver = 0
        else:
            self.__reader_ver ^= 1

        # Versions should be different
        assert(self.__reader_ver != self.__writer_ver)

class DataSrcInfo:
    """A container for datasrc.ConfigurableClientLists and associated
    in-memory segment information corresponding to a given geration of
    configuration.

    This class maintains all datasrc.ConfigurableClientLists in a form
    of dict from RR classes corresponding to a given single generation
    of data source configuration, along with sets of memory segment
    information that needs to be used by memmgr.

    Once constructed, mappings do not change (different generation of
    configuration will result in another DataSrcInfo objects).  Status
    of SegmentInfo objects stored in this class object may change over time.

    Attributes: these are all constant and read only.  For dict objects,
          mapping shouldn't be modified either.
      gen_id (int): The corresponding configuration generation ID.
      clients_map (dict, isc.dns.RRClass=>isc.datasrc.ConfigurableClientList):
          The configured client lists for all RR classes of the generation.
      segment_info_map (dict, (isc.dns.RRClass, str)=>SegmentInfo):
          SegmentInfo objects managed in the DataSrcInfo objects.  Can be
          retrieved by (RRClass, <data source name>).

    """
    def __init__(self, genid, clients_map, mgr_config):
        """Constructor.

        As long as given parameters are of valid type and have been
        validated, this constructor shouldn't raise an exception.

        Parameters:
          genid (int): see gen_id attribute
          clients_map (dict): see clients_map attribute
          mgr_config (dict, str=>key-dependent-value): A copy of the current
            memmgr configuration, in case it's needed to construct a specific
            type of SegmentInfo.  The specific SegmentInfo class is expected
            to know the key-value mappings that it needs.

        """
        self.__gen_id = genid
        self.__clients_map = clients_map
        self.__segment_info_map = {}
        for (rrclass, client_list) in clients_map.items():
            for (name, sgmt_type, _) in client_list.get_status():
                sgmt_info = SegmentInfo.create(sgmt_type, genid, rrclass, name,
                                               mgr_config)
                if sgmt_info is not None:
                    self.__segment_info_map[(rrclass, name)] = sgmt_info

    @property
    def gen_id(self):
        return self.__gen_id

    @property
    def clients_map(self):
        return self.__clients_map

    @property
    def segment_info_map(self):
        return self.__segment_info_map
