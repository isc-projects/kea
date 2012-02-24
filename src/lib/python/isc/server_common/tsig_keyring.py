# Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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
This module conveniently keeps a copy of TSIG keyring loaded from the
tsig_keys module.
"""

import isc.dns
import isc.log
from isc.log_messages.server_common_messages import *

updater = None
logger = isc.log.Logger("server_common")

class Unexpected(Exception):
    """
    Raised when an unexpected operation is requested by the user of this
    module. For example if calling keyring() before init_keyring().
    """
    pass

class AddError(Exception):
    """
    Raised when a key can not be added. This usually means there's a
    duplicate.
    """
    pass

class Updater:
    """
    The updater of tsig key ring. Not to be used directly.
    """
    def __init__(self, session):
        """
        Constructor. Pass the ccsession object so the key ring can be
        downloaded.
        """
        logger.debug(logger.DBGLVL_TRACE_BASIC,
                     PYSERVER_COMMON_TSIG_KEYRING_INIT)
        self.__session = session
        self.__keyring = isc.dns.TSIGKeyRing()
        session.add_remote_config_by_name('tsig_keys', self.__update)
        self.__update()

    def __update(self, value=None, module_cfg=None):
        """
        Update the key ring by the configuration.

        Note that this function is used as a callback, but can raise
        on bad data. The bad data is expected to be handled by the
        configuration plugin and not be allowed as far as here.

        The parameters are there just to match the signature which
        the callback should have (i.e. they are ignored).
        """
        logger.debug(logger.DBGLVL_TRACE_BASIC,
                     PYSERVER_COMMON_TSIG_KEYRING_UPDATE)
        (data, default) = self.__session.get_remote_config_value('tsig_keys',
                                                                 'keys')
        if data is not None: # There's an update
            keyring = isc.dns.TSIGKeyRing()
            for key_data in data:
                key = isc.dns.TSIGKey(key_data)
                if keyring.add(key) != isc.dns.TSIGKeyRing.SUCCESS:
                    raise AddError("Can't add key " + str(key))
            self.__keyring = keyring

    def get_keyring(self):
        """
        Return the current key ring.
        """
        return self.__keyring

    def deinit(self):
        """
        Unregister from getting updates. The object will not be
        usable any more after this.
        """
        logger.debug(logger.DBGLVL_TRACE_BASIC,
                     PYSERVER_COMMON_TSIG_KEYRING_DEINIT)
        self.__session.remove_remote_config('tsig_keys')

def get_keyring():
    """
    Get the current key ring. You need to call init_keyring first.
    """
    if updater is None:
        raise Unexpected("You need to initialize the keyring first by " +
                         "init_keyring()")
    return updater.get_keyring()

def init_keyring(session):
    """
    Initialize the key ring for future use. It does nothing if already
    initialized.
    """
    global updater
    if updater is None:
        updater = Updater(session)

def deinit_keyring():
    """
    Deinit key ring. Yoeu can no longer access keyring() after this.
    Does nothing if not initialized.
    """
    global updater
    if updater is not None:
        updater.deinit()
        updater = None
