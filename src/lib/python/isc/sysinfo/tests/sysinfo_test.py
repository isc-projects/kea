# Copyright (C) 2012  Internet Systems Consortium.
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

from isc.sysinfo import *
import os
import unittest
import platform
import subprocess

def _my_testcase_platform_system():
    return 'BIND10Testcase'

def _my_linux_platform_system():
    return 'Linux'

def _my_linux_os_sysconf(key):
    if key == 'SC_NPROCESSORS_CONF':
        return 42
    assert False, 'Unhandled key'

class MyLinuxFile:
    def __init__(self, filename):
        self._filename = filename

    def read(self):
        if self._filename == '/proc/sys/kernel/hostname':
            return 'myhostname'
        elif self._filename == '/proc/version':
            return 'An SMP version string'
        elif self._filename == '/proc/uptime':
            return '86400.75 139993.71'
        elif self._filename == '/proc/loadavg':
            return '0.1 0.2 0.3 0.4'
        else:
            assert False, 'Unhandled filename'

    def readlines(self):
        if self._filename == '/proc/meminfo':
            return ['MemTotal:        3083872 kB',
                    'MemFree:          870492 kB',
                    'Buffers:           27412 kB',
                    'Cached:          1303860 kB',
                    'SwapTotal:       4194300 kB',
                    'SwapFree:        3999464 kB']
        else:
            assert False, 'Unhandled filename'

    def close(self):
        return

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        return

def _my_linux_open(filename):
    return MyLinuxFile(filename)

def _my_linux_subprocess_check_output(command):
    assert type(command) == list, 'command argument is not a list'
    if command == ['lsb_release', '-a']:
        return b'Description: My Distribution\n'
    elif command == ['ip', 'addr']:
        return b'qB2osV6vUOjqm3P/+tQ4d92xoYz8/U8P9v3KWRpNwlI=\n'
    elif command == ['ip', 'route']:
        return b'VGWAS92AlS14Pl2xqENJs5P2Ihe6Nv9g181Mu6Zz+aQ=\n'
    elif command == ['ip', '-f', 'inet6', 'route']:
        return b'XfizswwNA9NkXz6K36ZExpjV08Y5IXkHI8jjDSV+5Nc=\n'
    elif command == ['netstat', '-s']:
        return b'osuxbrcc1g9VgaF4yf3FrtfodrfATrbSnjhqhuQSAs8=\n'
    elif command == ['netstat', '-apn']:
        return b'Z+w0lwa02/T+5+EIio84rrst/Dtizoz/aL9Im7J7ESA=\n'
    else:
        assert False, 'Unhandled command'

class SysInfoTest(unittest.TestCase):
    def test_sysinfo(self):
        """Test that the various methods on SysInfo exist and return data."""

        s = SysInfo()
        self.assertEqual(-1, s.get_num_processors())
        self.assertEqual('Unknown', s.get_endianness())
        self.assertEqual('', s.get_platform_hostname())
        self.assertEqual('Unknown', s.get_platform_name())
        self.assertEqual('Unknown', s.get_platform_version())
        self.assertEqual('Unknown', s.get_platform_machine())
        self.assertFalse(s.get_platform_is_smp())
        self.assertEqual(-1, s.get_uptime())
        self.assertEqual([-1.0, -1.0, -1.0], s.get_loadavg())
        self.assertEqual(-1, s.get_mem_total())
        self.assertEqual(-1, s.get_mem_free())
        self.assertEqual(-1, s.get_mem_cached())
        self.assertEqual(-1, s.get_mem_buffers())
        self.assertEqual(-1, s.get_mem_swap_total())
        self.assertEqual(-1, s.get_mem_swap_free())
        self.assertEqual('Unknown', s.get_platform_distro())
        self.assertEqual('Unknown', s.get_net_interfaces())
        self.assertEqual('Unknown', s.get_net_routing_table())
        self.assertEqual('Unknown', s.get_net_stats())
        self.assertEqual('Unknown', s.get_net_connections())

    def test_sysinfo_factory(self):
        """Test that SysInfoFromFactory returns a valid system-specific
        SysInfo implementation."""

        old_platform_system = platform.system
        platform.system = _my_testcase_platform_system

        s = SysInfoFromFactory()
        self.assertEqual(-1, s.get_num_processors())
        self.assertEqual('bigrastafarian', s.get_endianness())
        self.assertEqual('', s.get_platform_hostname())
        self.assertEqual('b10test', s.get_platform_name())
        self.assertEqual('Unknown', s.get_platform_version())
        self.assertEqual('Unknown', s.get_platform_machine())
        self.assertFalse(s.get_platform_is_smp())
        self.assertEqual(131072, s.get_uptime())
        self.assertEqual([-1.0, -1.0, -1.0], s.get_loadavg())
        self.assertEqual(-1, s.get_mem_total())
        self.assertEqual(-1, s.get_mem_free())
        self.assertEqual(-1, s.get_mem_cached())
        self.assertEqual(-1, s.get_mem_buffers())
        self.assertEqual(-1, s.get_mem_swap_total())
        self.assertEqual(-1, s.get_mem_swap_free())
        self.assertEqual('Unknown', s.get_platform_distro())
        self.assertEqual('Unknown', s.get_net_interfaces())
        self.assertEqual('Unknown', s.get_net_routing_table())
        self.assertEqual('Unknown', s.get_net_stats())
        self.assertEqual('Unknown', s.get_net_connections())

        platform.system = old_platform_system

    def test_sysinfo_linux(self):
        """Tests the Linux implementation of SysInfo. Note that this
        tests deep into the implementation, and not just the
        interfaces."""

        # Don't run this test on platform other than Linux as some
        # system calls may not even be available.
        osname = platform.system()
        if osname != 'Linux':
            return

        # Save and replace existing implementations of library functions
        # with mock ones for testing.
        old_platform_system = platform.system
        platform.system = _my_linux_platform_system
        old_os_sysconf = os.sysconf
        os.sysconf = _my_linux_os_sysconf
        old_open = __builtins__.open
        __builtins__.open = _my_linux_open
        old_subprocess_check_output = subprocess.check_output
        subprocess.check_output = _my_linux_subprocess_check_output

        s = SysInfoFromFactory()
        self.assertEqual(42, s.get_num_processors())
        self.assertEqual('myhostname', s.get_platform_hostname())
        self.assertTrue(s.get_platform_is_smp())
        self.assertEqual(86401, s.get_uptime())
        self.assertEqual([0.1, 0.2, 0.3], s.get_loadavg())
        self.assertEqual(3157884928, s.get_mem_total())
        self.assertEqual(891383808, s.get_mem_free())
        self.assertEqual(1335152640, s.get_mem_cached())
        self.assertEqual(28069888, s.get_mem_buffers())
        self.assertEqual(4294963200, s.get_mem_swap_total())
        self.assertEqual(4095451136, s.get_mem_swap_free())
        self.assertEqual('My Distribution', s.get_platform_distro())

        # These test that the corresponding tools are being called (and
        # no further processing is done on this data). Please see the
        # implementation functions at the top of this file.
        self.assertEqual('qB2osV6vUOjqm3P/+tQ4d92xoYz8/U8P9v3KWRpNwlI=\n', s.get_net_interfaces())
        self.assertEqual('VGWAS92AlS14Pl2xqENJs5P2Ihe6Nv9g181Mu6Zz+aQ=\n\nXfizswwNA9NkXz6K36ZExpjV08Y5IXkHI8jjDSV+5Nc=\n', s.get_net_routing_table())
        self.assertEqual('osuxbrcc1g9VgaF4yf3FrtfodrfATrbSnjhqhuQSAs8=\n', s.get_net_stats())
        self.assertEqual('Z+w0lwa02/T+5+EIio84rrst/Dtizoz/aL9Im7J7ESA=\n', s.get_net_connections())

        # Restore original implementations.
        platform.system = old_platform_system
        os.sysconf = old_os_sysconf
        __builtins__.open = old_open
        subprocess.check_output = old_subprocess_check_output

if __name__ == "__main__":
    unittest.main()
