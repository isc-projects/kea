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
import random
import socket
import threading
import time
from isc.datasrc import sqlite3_ds
import isc
try: 
    from libdns_python import * 
except ImportError as e: 
    # C++ loadable module may not be installed; 
    sys.stderr.write('[b10-xfrout] failed to import DNS or XFR module: %s\n' % str(e)) 

ZONE_NEW_DATA_READY_CMD = 'zone_new_data_ready'
_MAX_NOTIFY_NUM = 30
_MAX_NOTIFY_TRY_NUM = 5
_EVENT_NONE = 0
_EVENT_READ = 1
_EVENT_TIMEOUT = 2
_NOTIFY_TIMEOUT = 2

def addr_to_str(addr):
    return '%s#%s' % (addr[0], addr[1])

def dispatcher(notifier):
    while True:
        replied_zones, not_replied_zones = notifier._wait_for_notify_reply()
        if len(replied_zones) == 0 and len(not_replied_zones) == 0:
            time.sleep(0.5) # A better time?
            continue

        for name_ in replied_zones:
            notifier._zone_notify_handler(replied_zones[name_], _EVENT_READ)
            
        for name_ in not_replied_zones:
            if not_replied_zones[name_].notify_timeout < time.time():
                notifier._zone_notify_handler(not_replied_zones[name_], _EVENT_TIMEOUT)
 
class ZoneNotifyInfo:
    '''This class keeps track of notify-out information for one zone.
    timeout_: absolute time for next notify reply.
    '''    
    def __init__(self, zone_name_, klass):
        self._notify_slaves = []
        self._notify_current = None
        self._slave_index = 0
        self._sock = None

        self.zone_name = zone_name_
        self.zone_class = klass
        self.notify_msg_id = 0
        self.notify_timeout = 0
        # Notify times sending to one target.
        self.notify_try_num = 0 
       
    def set_next_notify_target(self):
        if self._slave_index < (len(self._notify_slaves) - 1):
            self._slave_index += 1
            self._notify_current = self._notify_slaves[self._slave_index]
        else:
            self._notify_current = None

    def prepare_notify_out(self):
        '''Create the socket and set notify timeout time to now'''
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #TODO support IPv6?
        self.notify_timeout = time.time()
        self.notify_try_num = 0
        self._slave_index = 0
        if len(self._notify_slaves) > 0:
            self._notify_current = self._notify_slaves[0]

    def finish_notify_out(self):
        if self._sock:
            self._sock.close()
            self._sock = None

    def get_socket(self):
        return self._sock

    def get_current_notify_target(self):
        return self._notify_current

class NotifyOut:
    def __init__(self, datasrc_file, log=None, verbose=True):
        self._notify_infos = {} # key is (zone_name, zone_class)
        self._waiting_zones = []
        self._notifying_zones = []
        self._log = log
        self.notify_num = 0  # the count of in progress notifies
        self._verbose = verbose
        self._lock = threading.Lock()
        self._db_file = datasrc_file
        self._init_notify_out(datasrc_file)

    def _init_notify_out(self, datasrc_file):
        '''Get all the zones name and its notify target's address
        TODO, currently the zones are got by going through the zone 
        table in database. There should be a better way to get them 
        and also the setting 'also_notify', and there should be one 
        mechanism to cover the changed datasrc.'''
        self._db_file = datasrc_file
        for zone_name, zone_class in sqlite3_ds.get_zones_info(datasrc_file):
            zone_id = (zone_name, zone_class)
            self._notify_infos[zone_id] = ZoneNotifyInfo(zone_name, zone_class)
            slaves = self._get_notify_slaves_from_ns(zone_name)
            for item in slaves:
                self._notify_infos[zone_id]._notify_slaves.append((item, 53))

    def _get_rdata_data(self, rr):
        return rr[7].strip()

    def _get_notify_slaves_from_ns(self, zone_name):
        '''The simplest way to get the address of slaves, but not correct.
        TODO. the function should be provided by one library.'''
        ns_rrset = sqlite3_ds.get_zone_rrset(zone_name, zone_name, 'NS', self._db_file)
        soa_rrset = sqlite3_ds.get_zone_rrset(zone_name, zone_name, 'SOA', self._db_file)
        ns_rr_name = []
        for ns in ns_rrset:
            ns_rr_name.append(self._get_rdata_data(ns)) 
       
        if len(soa_rrset) > 0:
            sname = (soa_rrset[0][7].split(' '))[0].strip() #TODO, bad hardcode to get rdata part
            if sname in ns_rr_name:
                ns_rr_name.remove(sname)

        addr_list = []
        for rr_name in ns_rr_name:
            a_rrset = sqlite3_ds.get_zone_rrset(zone_name, rr_name, 'A', self._db_file)
            aaaa_rrset = sqlite3_ds.get_zone_rrset(zone_name, rr_name, 'AAAA', self._db_file)
            for rr in a_rrset:
                addr_list.append(self._get_rdata_data(rr))
            for rr in aaaa_rrset:
                addr_list.append(self._get_rdata_data(rr))

        return addr_list

    def send_notify(self, zone_name, zone_class='IN'):
        if zone_name[len(zone_name) - 1] != '.':
            zone_name += '.'

        zone_id = (zone_name, zone_class)
        if zone_id not in self._notify_infos:
            return

        with self._lock:
            if (self.notify_num >= _MAX_NOTIFY_NUM) or (zone_id in self._notifying_zones):
                if zone_id not in self._waiting_zones:
                    self._waiting_zones.append(zone_id)
            else:
                self._notify_infos[zone_id].prepare_notify_out()
                self.notify_num += 1 
                self._notifying_zones.append(zone_id)

    def _wait_for_notify_reply(self):
        '''receive notify replies in specified time. returned value 
        is one tuple:(replied_zones, not_replied_zones)
        replied_zones: the zones which receive notify reply.
        not_replied_zones: the zones which haven't got notify reply.
        '''
        valid_socks = []
        notifying_zones = {}
        min_timeout = time.time()
        for info in self._notify_infos:
            sock = self._notify_infos[info].get_socket()
            if sock:
                valid_socks.append(sock)
                notifying_zones[info] = self._notify_infos[info]
                tmp_timeout = self._notify_infos[info].notify_timeout
                if min_timeout > tmp_timeout:
                    min_timeout = tmp_timeout
        
        block_timeout = min_timeout - time.time()
        if block_timeout < 0:
            block_timeout = 0
        try:
            r_fds, w, e = select.select(valid_socks, [], [], block_timeout)
        except select.error as err:
            if err.args[0] != EINTR:
                return [], []
        
        not_replied_zones = {}
        replied_zones = {}
        for info in notifying_zones:
            if notifying_zones[info].get_socket() in r_fds:
                replied_zones[info] = notifying_zones[info]
            else:
                not_replied_zones[info] = notifying_zones[info]

        return replied_zones, not_replied_zones

    def _zone_notify_handler(self, zone_notify_info, event_type):
        tgt = zone_notify_info.get_current_notify_target()
        if event_type == _EVENT_READ:
            reply = self._get_notify_reply(zone_notify_info.get_socket(), tgt)
            if reply:
                if self._handle_notify_reply(zone_notify_info, reply):
                    self._notify_next_target(zone_notify_info)

        elif event_type == _EVENT_TIMEOUT and zone_notify_info.notify_try_num > 0:
            self._log_msg('info', 'notify retry to %s' % addr_to_str(tgt))

        tgt = zone_notify_info.get_current_notify_target()
        if tgt:
            zone_notify_info.notify_try_num += 1
            if zone_notify_info.notify_try_num > _MAX_NOTIFY_TRY_NUM:
                self._log_msg('info', 'notify to %s: retried exceeded' % addr_to_str(tgt))
                self._notify_next_target(zone_notify_info)
            else:
                retry_timeout = _NOTIFY_TIMEOUT * pow(2, zone_notify_info.notify_try_num)
                # set exponential backoff according rfc1996 section 3.6
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

    def _send_notify_message_udp(self, zone_notify_info, addrinfo):
        msg, qid = self._create_notify_message(zone_notify_info.zone_name, 
                                               zone_notify_info.zone_class)
        render = MessageRenderer()
        render.set_length_limit(512) 
        msg.to_wire(render)
        zone_notify_info.notify_msg_id = qid
        sock = zone_notify_info.get_socket()
        try:
            sock.sendto(render.get_data(), 0, addrinfo)
            self._log_msg('info', 'sending notify to %s' % addr_to_str(addrinfo))
        except socket.error as err:
            self._log_msg('error', 'send notify to %s failed: %s' % (addr_to_str(addrinfo), str(err)))
            return False

        return True

    def _create_rrset_from_db_record(self, record):
        '''Create one rrset from one record of datasource, if the schema of record is changed, 
        This function should be updated first. TODO, the function is copied from xfrout, there
        should be library for creating one rrset. '''
        rrtype_ = RRType(record[5])
        rdata_ = Rdata(rrtype_, RRClass("IN"), " ".join(record[7:]))
        rrset_ = RRset(Name(record[2]), RRClass("IN"), rrtype_, RRTTL( int(record[4])))
        rrset_.add_rdata(rdata_)
        return rrset_

    def _create_notify_message(self, zone_name, zone_class):
        msg = Message(Message.RENDER)
        qid = random.randint(0, 0xFFFF)
        msg.set_qid(qid)
        msg.set_opcode(Opcode.NOTIFY())
        msg.set_rcode(Rcode.NOERROR())
        msg.set_header_flag(MessageFlag.AA())
        question = Question(Name(zone_name), RRClass(zone_class), RRType('SOA'))
        msg.add_question(question)
        # Add soa record to answer section
        soa_record = sqlite3_ds.get_zone_rrset(zone_name, zone_name, 'SOA', self._db_file) 
        rrset_soa = self._create_rrset_from_db_record(soa_record[0])
        msg.add_rrset(Section.ANSWER(), rrset_soa)
        return msg, qid

    def _handle_notify_reply(self, zone_notify_info, msg_data):
        '''Parse the notify reply message.
        TODO, the error message should be refined properly.
        rcode will not checked here, If we get the response
        from the slave, it means the slaves has got the notify.'''
        msg = Message(Message.PARSE)
        try:
            errstr = 'notify reply error: '
            msg.from_wire(msg_data)
            if not msg.get_header_flag(MessageFlag.QR()):
                self._log_msg('error', errstr + 'bad flags')
                return False

            if msg.get_qid() != zone_notify_info.notify_msg_id: 
                self._log_msg('error', errstr + 'bad query ID')
                return False

            if msg.get_opcode != Opcode.NOTIFY():
                self._log_msg('error', errstr + 'bad opcode')
                return False
        except Exception as err:
            # We don't care what exception, just report it? 
            self._log_msg('error', errstr + str(err))
            return False

        return True

    def _get_notify_reply(self, sock, tgt_addr):
        try:
            msg, addr = sock.recvfrom(512)
        except socket.error:
            self._log_msg('error', "notify to %s failed: can't read notify reply" % addr_to_str(tgt_addr))
            return None

        return msg


    def _log_msg(self, level, msg):
        if self._log:
            self._log.log_message(level, msg)

