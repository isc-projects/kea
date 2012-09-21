# Copyright (C) 2010  Internet Systems Consortium.
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

import select
import sys
import random
import socket
import threading
import time
import errno
from isc.datasrc import sqlite3_ds
from isc.datasrc import DataSourceClient
from isc.net import addr
import isc
from isc.log_messages.notify_out_messages import *

logger = isc.log.Logger("notify_out")

# there used to be a printed message if this import failed, but if
# we can't import we should not start anyway, and logging an error
# is a bad idea since the logging system is most likely not
# initialized yet. see trac ticket #1103
from isc.dns import *

ZONE_NEW_DATA_READY_CMD = 'zone_new_data_ready'
ZONE_XFRIN_FAILED = 'zone_xfrin_failed'

_MAX_NOTIFY_NUM = 30
_MAX_NOTIFY_TRY_NUM = 5
_EVENT_NONE = 0
_EVENT_READ = 1
_EVENT_TIMEOUT = 2
_NOTIFY_TIMEOUT = 1

# define the rcode for parsing notify reply message
_REPLY_OK = 0
_BAD_QUERY_ID = 1
_BAD_QUERY_NAME = 2
_BAD_OPCODE = 3
_BAD_QR = 4
_BAD_REPLY_PACKET = 5

SOCK_DATA = b's'

# borrowed from xfrin.py @ #1298.  We should eventually unify it.
def format_zone_str(zone_name, zone_class):
    """Helper function to format a zone name and class as a string of
       the form '<name>/<class>'.
       Parameters:
       zone_name (isc.dns.Name) name to format
       zone_class (isc.dns.RRClass) class to format
    """
    return zone_name.to_text() + '/' + str(zone_class)

class NotifyOutDataSourceError(Exception):
    """An exception raised when data source error happens within notify out.

    This exception is expected to be caught within the notify_out module.

    """
    pass

class ZoneNotifyInfo:
    '''This class keeps track of notify-out information for one zone.'''

    def __init__(self, zone_name_, class_):
        self._notify_current = None
        self._slave_index = 0
        self._sock = None

        self.notify_slaves = []
        self.zone_name = zone_name_
        self.zone_class = class_
        self.notify_msg_id = 0
        # Absolute time for next notify reply. When the zone is preparing for
        # sending notify message, notify_timeout_ is set to now, that means
        # the first sending is triggered by the 'Timeout' mechanism.
        self.notify_timeout = None
        self.notify_try_num = 0  # Notify times sending to one target.

    def set_next_notify_target(self):
        if self._slave_index < (len(self.notify_slaves) - 1):
            self._slave_index += 1
            self._notify_current = self.notify_slaves[self._slave_index]
        else:
            self._notify_current = None

    def prepare_notify_out(self):
        '''Set notify timeout time to now'''
        self.notify_timeout = time.time()
        self.notify_try_num = 0
        self._slave_index = 0
        if len(self.notify_slaves) > 0:
            self._notify_current = self.notify_slaves[0]

    def finish_notify_out(self):
        if self._sock:
            self._sock.close()
            self._sock = None
        self.notify_timeout = None

    def create_socket(self, dest_addr):
        self._sock = socket.socket(addr.IPAddr(dest_addr).family,
                                   socket.SOCK_DGRAM)
        return self._sock

    def get_socket(self):
        return self._sock

    def get_current_notify_target(self):
        return self._notify_current

class NotifyOut:
    '''This class is used to handle notify logic for all zones(sending
    notify message to its slaves). notify service can be started by
    calling  dispatcher(), and it can be stopped by calling shutdown()
    in another thread. '''
    def __init__(self, datasrc_file, counter_handler=None, verbose=True,
                 counter_notifyoutv4=None, counter_notifyoutv6=None):
        self._notify_infos = {} # key is (zone_name, zone_class)
        self._waiting_zones = []
        self._notifying_zones = []
        self._serving = False
        self._read_sock, self._write_sock = socket.socketpair()
        self._read_sock.setblocking(False)
        self.notify_num = 0  # the count of in progress notifies
        self._verbose = verbose
        self._lock = threading.Lock()
        self._db_file = datasrc_file
        self._init_notify_out(datasrc_file)
        # Use nonblock event to eliminate busy loop
        # If there are no notifying zones, clear the event bit and wait.
        self._nonblock_event = threading.Event()
        # Set counter handlers for counting notifies. An argument is
        # required for zone name.
        self._counter_notifyoutv4 = counter_notifyoutv4
        self._counter_notifyoutv6 = counter_notifyoutv6

    def _init_notify_out(self, datasrc_file):
        '''Get all the zones name and its notify target's address.

        TODO, currently the zones are got by going through the zone
        table in database. There should be a better way to get them
        and also the setting 'also_notify', and there should be one
        mechanism to cover the changed datasrc.

        '''
        self._db_file = datasrc_file
        for zone_name, zone_class in sqlite3_ds.get_zones_info(datasrc_file):
            zone_id = (zone_name, zone_class)
            self._notify_infos[zone_id] = ZoneNotifyInfo(zone_name, zone_class)
            slaves = self._get_notify_slaves_from_ns(Name(zone_name),
                                                     RRClass(zone_class))
            for item in slaves:
                self._notify_infos[zone_id].notify_slaves.append((item, 53))

    def add_slave(self, address, port):
        for zone_name, zone_class in sqlite3_ds.get_zones_info(self._db_file):
            zone_id = (zone_name, zone_class)
            if zone_id in self._notify_infos:
                self._notify_infos[zone_id].notify_slaves.append((address, port))

    def send_notify(self, zone_name, zone_class='IN'):
        '''Send notify to one zone's slaves, this function is
        the only interface for class NotifyOut which can be called
        by other object.
          Internally, the function only set the zone's notify-reply
        timeout to now, then notify message will be sent out.
        Returns False if the zone/class is not known, True if it is
        (even if there are no slaves)'''
        if zone_name[len(zone_name) - 1] != '.':
            zone_name += '.'

        zone_id = (zone_name, zone_class)
        if zone_id not in self._notify_infos:
            return False

        # Has no slave servers, skip it.
        if (len(self._notify_infos[zone_id].notify_slaves) <= 0):
            return True

        with self._lock:
            if (self.notify_num >= _MAX_NOTIFY_NUM) or (zone_id in self._notifying_zones):
                if zone_id not in self._waiting_zones:
                    self._waiting_zones.append(zone_id)
            else:
                self._notify_infos[zone_id].prepare_notify_out()
                self.notify_num += 1
                self._notifying_zones.append(zone_id)
                if not self._nonblock_event.isSet():
                    self._nonblock_event.set()
        return True

    def _dispatcher(self, started_event):
        started_event.set() # Let the master know we are alive already
        while self._serving:
            replied_zones, not_replied_zones = self._wait_for_notify_reply()

            for name_ in replied_zones:
                self._zone_notify_handler(replied_zones[name_], _EVENT_READ)

            for name_ in not_replied_zones:
                if not_replied_zones[name_].notify_timeout <= time.time():
                    self._zone_notify_handler(not_replied_zones[name_], _EVENT_TIMEOUT)

    def dispatcher(self, daemon=False):
        """Spawns a thread that will handle notify related events.

        If one zone get the notify reply before timeout, call the
        handle to process the reply. If one zone can't get the notify
        before timeout, call the handler to resend notify or notify
        next slave.

        The thread can be stopped by calling shutdown().

        Returns the thread object to anyone interested.
        """

        if self._serving:
            raise RuntimeError(
                'Dispatcher already running, tried to start twice')

        # Prepare for launch
        self._serving = True
        started_event = threading.Event()

        # Start
        self._thread = threading.Thread(target=self._dispatcher,
            args=[started_event])
        if daemon:
            self._thread.daemon = daemon
        self._thread.start()

        # Wait for it to get started
        started_event.wait()

        # Return it to anyone listening
        return self._thread

    def shutdown(self):
        """Stop the dispatcher() thread. Blocks until the thread stopped."""

        if not self._serving:
            raise RuntimeError('Tried to stop while not running')

        # Ask it to stop
        self._serving = False
        if not self._nonblock_event.isSet():
            # set self._nonblock_event to stop waiting for new notifying zones.
            self._nonblock_event.set()
        self._write_sock.send(SOCK_DATA) # make self._read_sock be readable.

        # Wait for it
        self._thread.join()

        # Clean up
        self._write_sock.close()
        self._write_sock = None
        self._read_sock.close()
        self._read_sock = None
        self._thread = None

    def _get_rdata_data(self, rr):
        return rr[7].strip()

    def _get_notify_slaves_from_ns(self, zone_name, zone_class):
        '''Get all NS records, then remove the primary master from ns rrset,
        then use the name in NS record rdata part to get the a/aaaa records
        in the same zone. the targets listed in a/aaaa record rdata are treated
        as the notify slaves.
        Note: this is the simplest way to get the address of slaves,
        but not correct, it can't handle the delegation slaves, or the CNAME
        and DNAME logic.
        TODO. the function should be provided by one library.

        '''
        # Prepare data source client.  This should eventually be moved to
        # an earlier stage of initialization and also support multiple
        # data sources.
        datasrc_config = '{ "database_file": "' + self._db_file + '"}'
        try:
            ds_client = DataSourceClient('sqlite3', datasrc_config)
        except isc.datasrc.Error as ex:
            logger.error(NOTIFY_OUT_DATASRC_ACCESS_FAILURE, ex)
            return []

        result, finder = ds_client.find_zone(zone_name)
        if result is not DataSourceClient.SUCCESS:
            logger.error(NOTIFY_OUT_DATASRC_ZONE_NOT_FOUND,
                         format_zone_str(zone_name, zone_class))
            return []

        result, ns_rrset, _ = finder.find(zone_name, RRType.NS())
        if result is not finder.SUCCESS or ns_rrset is None:
            logger.warn(NOTIFY_OUT_ZONE_NO_NS,
                        format_zone_str(zone_name, zone_class))
            return []
        result, soa_rrset, _ = finder.find(zone_name, RRType.SOA())
        if result is not finder.SUCCESS or soa_rrset is None or \
                soa_rrset.get_rdata_count() != 1:
            logger.warn(NOTIFY_OUT_ZONE_BAD_SOA,
                        format_zone_str(zone_name, zone_class))
            return []           # broken zone anyway, stop here.
        soa_mname = Name(soa_rrset.get_rdata()[0].to_text().split(' ')[0])

        addrs = []
        for ns_rdata in ns_rrset.get_rdata():
            ns_name = Name(ns_rdata.to_text())
            if soa_mname == ns_name:
                continue
            ns_result, ns_finder = ds_client.find_zone(ns_name)
            if ns_result is DataSourceClient.SUCCESS or \
               ns_result is DataSourceClient.PARTIALMATCH:
                result, rrset, _ = ns_finder.find(ns_name, RRType.A())
                if result is ns_finder.SUCCESS and rrset is not None:
                    addrs.extend([a.to_text() for a in rrset.get_rdata()])

                result, rrset, _ = ns_finder.find(ns_name, RRType.AAAA())
                if result is ns_finder.SUCCESS and rrset is not None:
                    addrs.extend([aaaa.to_text()
                                    for aaaa in rrset.get_rdata()])

        return addrs

    def _prepare_select_info(self):
        '''
        Prepare the information for select(), returned
        value is one tuple
        (block_timeout, valid_socks, notifying_zones)
        block_timeout: the timeout for select()
        valid_socks: sockets list for waiting ready reading.
        notifying_zones: the zones which have been triggered
                        for notify.
        '''
        valid_socks = []
        notifying_zones = {}
        min_timeout = None
        for info in self._notify_infos:
            sock = self._notify_infos[info].get_socket()
            if sock:
                valid_socks.append(sock)

            # If a non null timeout is specified notify has been scheduled
            # (in which case socket is still None) or sent (with a valid
            # socket).  In either case we need add the zone to notifying_zones
            # so that we can invoke the appropriate event for the zone after
            # select.
            tmp_timeout = self._notify_infos[info].notify_timeout
            if tmp_timeout is not None:
                notifying_zones[info] = self._notify_infos[info]
                if min_timeout is not None:
                    if tmp_timeout < min_timeout:
                        min_timeout = tmp_timeout
                else:
                    min_timeout = tmp_timeout

        block_timeout = None
        if min_timeout is not None:
            block_timeout = min_timeout - time.time()
            if block_timeout < 0:
                block_timeout = 0

        return (block_timeout, valid_socks, notifying_zones)

    def _wait_for_notify_reply(self):
        '''
        Receive notify replies in specified time. returned value
        is one tuple:(replied_zones, not_replied_zones). ({}, {}) is
        returned if shutdown() was called.

        replied_zones: the zones which receive notify reply.
        not_replied_zones: the zones which haven't got notify reply.

        '''
        (block_timeout, valid_socks, notifying_zones) = \
            self._prepare_select_info()
        # This is None only during some tests
        if self._read_sock is not None:
            valid_socks.append(self._read_sock)

        # Currently, there is no notifying zones, waiting for zones to send notify
        if block_timeout is None:
            self._nonblock_event.clear()
            self._nonblock_event.wait()
            # has new notifying zone, check immediately
            block_timeout = 0

        try:
            r_fds, w, e = select.select(valid_socks, [], [], block_timeout)
        except select.error as err:
            if err.args[0] != errno.EINTR:
                return {}, {}

        if self._read_sock in r_fds: # user has called shutdown()
            try:
                # Noone should write anything else than shutdown
                assert self._read_sock.recv(len(SOCK_DATA)) == SOCK_DATA
                return {}, {}
            except socket.error as e: # Workaround around rare linux bug
                if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
                    raise

        not_replied_zones = {}
        replied_zones = {}
        for info in notifying_zones:
            if notifying_zones[info].get_socket() in r_fds:
                replied_zones[info] = notifying_zones[info]
            else:
                not_replied_zones[info] = notifying_zones[info]

        return replied_zones, not_replied_zones

    def _zone_notify_handler(self, zone_notify_info, event_type):
        '''Notify handler for one zone. The first notify message is
        always triggered by the event "_EVENT_TIMEOUT" since when
        one zone prepares to notify its slaves, its notify_timeout
        is set to now, which is used to trigger sending notify
        message when dispatcher() scanning zones. '''
        tgt = zone_notify_info.get_current_notify_target()
        if event_type == _EVENT_READ:
            reply = self._get_notify_reply(zone_notify_info.get_socket(), tgt)
            if reply is not None:
                if self._handle_notify_reply(zone_notify_info, reply, tgt):
                    self._notify_next_target(zone_notify_info)

        elif event_type == _EVENT_TIMEOUT and zone_notify_info.notify_try_num > 0:
            logger.info(NOTIFY_OUT_TIMEOUT, tgt[0], tgt[1])

        tgt = zone_notify_info.get_current_notify_target()
        if tgt:
            zone_notify_info.notify_try_num += 1
            if zone_notify_info.notify_try_num > _MAX_NOTIFY_TRY_NUM:
                logger.warn(NOTIFY_OUT_RETRY_EXCEEDED, tgt[0], tgt[1],
                            _MAX_NOTIFY_TRY_NUM)
                self._notify_next_target(zone_notify_info)
            else:
                # set exponential backoff according rfc1996 section 3.6
                retry_timeout = _NOTIFY_TIMEOUT * pow(2, zone_notify_info.notify_try_num)
                zone_notify_info.notify_timeout = time.time() + retry_timeout
                self._send_notify_message_udp(zone_notify_info, tgt)

    def _notify_next_target(self, zone_notify_info):
        '''Notify next address for the same zone. If all the targets
        has been notified, notify the first zone in waiting list. '''
        zone_notify_info.notify_try_num = 0
        zone_notify_info.set_next_notify_target()
        tgt = zone_notify_info.get_current_notify_target()
        if not tgt:
            zone_notify_info.finish_notify_out()
            with self._lock:
                self.notify_num -= 1
                self._notifying_zones.remove((zone_notify_info.zone_name,
                                              zone_notify_info.zone_class))
                # trigger notify out for waiting zones
                if len(self._waiting_zones) > 0:
                    zone_id = self._waiting_zones.pop(0)
                    self._notify_infos[zone_id].prepare_notify_out()
                    self.notify_num += 1
                    self._notifying_zones.append(zone_id)
                    if not self._nonblock_event.isSet():
                        self._nonblock_event.set()

    def _send_notify_message_udp(self, zone_notify_info, addrinfo):
        msg, qid = self._create_notify_message(
            Name(zone_notify_info.zone_name),
            RRClass(zone_notify_info.zone_class))
        render = MessageRenderer()
        render.set_length_limit(512)
        msg.to_wire(render)
        zone_notify_info.notify_msg_id = qid
        try:
            sock = zone_notify_info.create_socket(addrinfo[0])
            sock.sendto(render.get_data(), 0, addrinfo)
            # count notifying by IPv4 or IPv6 for statistics
            if zone_notify_info.get_socket().family \
                    == socket.AF_INET \
                    and self._counter_notifyoutv4 is not None:
                self._counter_notifyoutv4(zone_notify_info.zone_name)
            elif zone_notify_info.get_socket().family \
                    == socket.AF_INET6 \
                    and self._counter_notifyoutv6 is not None:
                self._counter_notifyoutv6(zone_notify_info.zone_name)
            logger.info(NOTIFY_OUT_SENDING_NOTIFY, addrinfo[0],
                        addrinfo[1])
        except (socket.error, addr.InvalidAddress) as err:
            logger.error(NOTIFY_OUT_SOCKET_ERROR, addrinfo[0],
                         addrinfo[1], err)
            return False
        except addr.InvalidAddress as iae:
            logger.error(NOTIFY_OUT_INVALID_ADDRESS, addrinfo[0],
                         addrinfo[1], iae)
            return False

        return True

    def _create_notify_message(self, zone_name, zone_class):
        msg = Message(Message.RENDER)
        qid = random.randint(0, 0xFFFF)
        msg.set_qid(qid)
        msg.set_opcode(Opcode.NOTIFY())
        msg.set_rcode(Rcode.NOERROR())
        msg.set_header_flag(Message.HEADERFLAG_AA)
        msg.add_question(Question(zone_name, zone_class, RRType.SOA()))
        msg.add_rrset(Message.SECTION_ANSWER, self._get_zone_soa(zone_name,
                                                                 zone_class))
        return msg, qid

    def _get_zone_soa(self, zone_name, zone_class):
        # We create (and soon drop) the data source client here because
        # clients should be thread specific.  We could let the main thread
        # loop (_dispatcher) create and retain the client in order to avoid
        # the overhead when we generalize the interface (and we may also
        # revisit the design of notify_out more substantially anyway).
        datasrc_config = '{ "database_file": "' + self._db_file + '"}'
        result, finder = DataSourceClient('sqlite3',
                                          datasrc_config).find_zone(zone_name)
        if result is not DataSourceClient.SUCCESS:
            raise NotifyOutDataSourceError('_get_zone_soa: Zone ' +
                                           zone_name.to_text() + '/' +
                                           zone_class.to_text() + ' not found')

        result, soa_rrset, _ = finder.find(zone_name, RRType.SOA())
        if result is not finder.SUCCESS or soa_rrset is None or \
                soa_rrset.get_rdata_count() != 1:
            raise NotifyOutDataSourceError('_get_zone_soa: Zone ' +
                                           zone_name.to_text() + '/' +
                                           zone_class.to_text() +
                                           ' is broken: no valid SOA found')

        return soa_rrset

    def _handle_notify_reply(self, zone_notify_info, msg_data, from_addr):
        '''Parse the notify reply message.
        rcode will not checked here, If we get the response
        from the slave, it means the slaves has got the notify.'''
        msg = Message(Message.PARSE)
        try:
            msg.from_wire(msg_data)
            if not msg.get_header_flag(Message.HEADERFLAG_QR):
                logger.warn(NOTIFY_OUT_REPLY_QR_NOT_SET, from_addr[0],
                            from_addr[1])
                return _BAD_QR

            if msg.get_qid() != zone_notify_info.notify_msg_id:
                logger.warn(NOTIFY_OUT_REPLY_BAD_QID, from_addr[0],
                            from_addr[1], msg.get_qid(),
                            zone_notify_info.notify_msg_id)
                return _BAD_QUERY_ID

            question = msg.get_question()[0]
            if question.get_name() != Name(zone_notify_info.zone_name):
                logger.warn(NOTIFY_OUT_REPLY_BAD_QUERY_NAME, from_addr[0],
                            from_addr[1], question.get_name().to_text(),
                            Name(zone_notify_info.zone_name).to_text())
                return _BAD_QUERY_NAME

            if msg.get_opcode() != Opcode.NOTIFY():
                logger.warn(NOTIFY_OUT_REPLY_BAD_OPCODE, from_addr[0],
                            from_addr[1], msg.get_opcode().to_text())
                return _BAD_OPCODE
        except Exception as err:
            # We don't care what exception, just report it?
            logger.error(NOTIFY_OUT_REPLY_UNCAUGHT_EXCEPTION, err)
            return _BAD_REPLY_PACKET

        return _REPLY_OK

    def _get_notify_reply(self, sock, tgt_addr):
        try:
            msg, addr = sock.recvfrom(512)
        except socket.error as err:
            logger.error(NOTIFY_OUT_SOCKET_RECV_ERROR, tgt_addr[0],
                         tgt_addr[1], err)
            return None

        return msg
