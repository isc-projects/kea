# Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

import isc.dns
import isc.datasrc
import threading
import json

class ConfigError(Exception):
    """Exception class raised for data source configuration errors."""
    pass

class DataSrcClientsMgr:
    """A container of data source client lists.

    This class represents a set of isc.datasrc.ConfigurableClientList
    objects (currently per RR class), and provides APIs to configure
    the lists and access to a specific list in a thread safe manner.

    It is intended to be used by applications that refer to the global
    'data_sources' module.  The reconfigure() method can be called from
    a configuration callback for the module of the application.  The
    get_client_list() method is a simple search method to get the configured
    ConfigurableClientList object for a specified RR class (if any),
    while still allowing a separate thread to reconfigure the entire lists.

    """
    def __init__(self, use_cache=False):
        """Constructor.

        In the initial implementation, user applications of this class are
        generally expected to NOT use in-memory cache; use_cache would be
        set to True only for tests.  In future, some applications such as
        outbound zone transfer may want to set it to True.

        Parameter:
          use_cache (bool): If set to True, enable in-memory cache on
                            (re)configuration.

        """
        self.__use_cache = use_cache

        # Map from RRClass to ConfigurableClientList.  Resetting this map
        # is protected by __map_lock.  Note that this lock doesn't protect
        # "updates" of the map content.  __clients_map shouldn't be accessed
        # by class users directly.
        self.__clients_map = {}
        self.__map_lock = threading.Lock()

    def get_client_list(self, rrclass):
        """Return the configured ConfigurableClientList for the RR class.

        If no client list is configured for the specified RR class, it
        returns None.

        This method should not raise an exception as long as the parameter
        is of valid type.

        This method can be safely called from a thread even if a different
        thread is calling reconfigure().  Also, it's safe for the caller
        to use the returned list even if reconfigure() is called while or
        after the call to this thread.

        Note that this class does not protect further access to the returned
        list from multiple threads; it's the caller's responsbility to make
        such access thread safe.  In general, the find() method on the list
        and the use of ZoneFinder created by a DataSourceClient in the list
        cannot be done by multiple threads without explicit synchronization.
        On the other hand, multiple threads can create and use ZoneUpdater
        or ZoneIterator on a DataSourceClient in parallel.

        Parameter:
          rrclass (isc.dns.RRClass): the RR class of the ConfigurableClientList
            to be returned.
        """
        with self.__map_lock:
            client_list = self.__clients_map.get(rrclass)
        return client_list

    def reconfigure(self, config):
        """(Re)configure the set of client lists.

        This method takes a new set of data source configuration, builds
        a new set of ConfigurableClientList objects corresponding to the
        configuration, and replaces the internal set with the newly built
        one.  Its parameter is expected to be the "new configuration"
        parameter of a configuration update callback for the global
        "data_sources" module.  It should match the configuration data
        of the module spec (see the datasrc.spec file).

        Any error in reconfiguration is converted to a ConfigError
        exception and is raised from the method.  This method guarantees
        strong exception safety: unless building a new set for the new
        configuration is fully completed, the old set is intact.

        This method can be called from a thread while some other thread
        is calling get_client_list() and using the result (see
        the description of get_client_list()).  In general, however,
        only one thread can call this method at one time; while data
        integrity will still be preserved, the ordering of the change
        will not be guaranteed if multiple threads call this method
        at the same time.

        Parameter:
          config (dict): configuration data for the data_sources module.

        """
        try:
            new_map = {}
            for rrclass_cfg, class_cfg in config.get('classes').items():
                rrclass = isc.dns.RRClass(rrclass_cfg)
                new_client_list = isc.datasrc.ConfigurableClientList(rrclass)
                new_client_list.configure(json.dumps(class_cfg),
                                          self.__use_cache)
                new_map[rrclass] = new_client_list
            with self.__map_lock:
                self.__clients_map = new_map
        except Exception as ex:
            # Catch all types of exceptions as a whole: there won't be much
            # granularity for exceptions raised from the C++ module anyway.
            raise ConfigError(ex)
