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
import time

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

def _my_openbsd_platform_system():
    return 'OpenBSD'

def _my_openbsd_os_sysconf(key):
    if key == 'SC_NPROCESSORS_CONF':
        return 53
    assert False, 'Unhandled key'

def _my_openbsd_subprocess_check_output(command):
    assert type(command) == list, 'command argument is not a list'
    if command == ['hostname']:
        return b'blowfish.example.com\n'
    elif command == ['sysctl', '-n', 'kern.boottime']:
        return bytes(str(int(time.time() - 76632)), 'utf-8')
    elif command == ['sysctl', '-n', 'vm.loadavg']:
        return b'0.7 0.9 0.8\n'
    elif command == ['sysctl', '-n', 'hw.physmem']:
        return b'543214321\n'
    elif command == ['vmstat']:
        return b' procs    memory       page                    disks    traps          cpu\n r b w    avm     fre  flt  re  pi  po  fr  sr wd0 cd0  int   sys   cs us sy id\n 0 0 0   121212  123456   47   0   0   0   0   0   2   0    2    80   14  0  1 99\n'
    elif command == ['swapctl', '-s', '-k']:
        return b'total: 553507 1K-blocks allocated, 2 used, 553505 available'
    elif command == ['ifconfig']:
        return b'qB2osV6vUOjqm3P/+tQ4d92xoYz8/U8P9v3KWRpNwlI=\n'
    elif command == ['route', '-n', 'show']:
        return b'XfizswwNA9NkXz6K36ZExpjV08Y5IXkHI8jjDSV+5Nc=\n'
    elif command == ['netstat', '-s']:
        return b'osuxbrcc1g9VgaF4yf3FrtfodrfATrbSnjhqhuQSAs8=\n'
    elif command == ['netstat', '-an']:
        return b'Z+w0lwa02/T+5+EIio84rrst/Dtizoz/aL9Im7J7ESA=\n'
    else:
        assert False, 'Unhandled command'

def _my_freebsd_platform_system():
    return 'FreeBSD'

def _my_freebsd_os_sysconf(key):
    if key == 'SC_NPROCESSORS_CONF':
        return 91
    assert False, 'Unhandled key'

def _my_freebsd_subprocess_check_output(command):
    assert type(command) == list, 'command argument is not a list'
    if command == ['hostname']:
        return b'daemon.example.com\n'
    elif command == ['sysctl', '-n', 'kern.smp.active']:
        return b'1\n'
    elif command == ['sysctl', '-n', 'kern.boottime']:
        return bytes('{ sec = ' + str(int(time.time() - 76632)) + ', usec = 0 }\n', 'utf-8')
    elif command == ['sysctl', '-n', 'vm.loadavg']:
        return b'{ 0.2 0.4 0.6 }\n'
    elif command == ['sysctl', '-n', 'hw.physmem']:
        return b'987654321\n'
    elif command == ['vmstat', '-H']:
        return b' procs    memory       page                    disks    traps          cpu\n r b w    avm     fre  flt  re  pi  po  fr  sr wd0 cd0  int   sys   cs us sy id\n 0 0 0   343434  123456   47   0   0   0   0   0   2   0    2    80   14  0  1 99\n'
    elif command == ['swapctl', '-s', '-k']:
        return b'Total:         1013216    0\n'
    elif command == ['ifconfig']:
        return b'qB2osV6vUOjqm3P/+tQ4d92xoYz8/U8P9v3KWRpNwlI=\n'
    elif command == ['netstat', '-nr']:
        return b'XfizswwNA9NkXz6K36ZExpjV08Y5IXkHI8jjDSV+5Nc=\n'
    elif command == ['netstat', '-s']:
        return b'osuxbrcc1g9VgaF4yf3FrtfodrfATrbSnjhqhuQSAs8=\n'
    elif command == ['netstat', '-an']:
        return b'Z+w0lwa02/T+5+EIio84rrst/Dtizoz/aL9Im7J7ESA=\n'
    else:
        assert False, 'Unhandled command'

def _my_osx_platform_system():
    return 'Darwin'

def _my_osx_os_sysconf(key):
    if key == 'SC_NPROCESSORS_CONF':
        return 91
    assert False, 'Unhandled key'

def _my_osx_subprocess_check_output(command):
    assert type(command) == list, 'command argument is not a list'
    if command == ['hostname']:
        return b'daemon.example.com\n'
    elif command == ['sysctl', '-n', 'hw.physmem']:
        return b'987654321\n'
    elif command == ['sysctl', '-n', 'hw.memsize']:
        # Something different than physmem
        return b'123456789\n'
    elif command == ['ifconfig']:
        return b'qB2osV6vUOjqm3P/+tQ4d92xoYz8/U8P9v3KWRpNwlI=\n'
    elif command == ['netstat', '-s']:
        return b'osuxbrcc1g9VgaF4yf3FrtfodrfATrbSnjhqhuQSAs8=\n'
    elif command == ['netstat', '-an']:
        return b'Z+w0lwa02/T+5+EIio84rrst/Dtizoz/aL9Im7J7ESA=\n'
    elif command == ['sysctl', '-n', 'kern.smp.active']:
        return b'0\n'
    elif command == ['sysctl', '-n', 'kern.boottime']:
        return bytes('{ sec = ' + str(int(time.time() - 76632)) + ', usec = 0 }\n', 'utf-8')
    elif command == ['sysctl', '-n', 'vm.loadavg']:
        return b'{ 0.2 0.4 0.6 }\n'
    elif command == ['vm_stat']:
        return b'Mach Virtual Memory Statistics: (page size of 4096 bytes)\nPages free: 12345.\nPages speculative: 11111.\n'
    elif command == ['sysctl', '-n', 'vm.swapusage']:
        return b'total = 18432.00M  used = 17381.23M  free = 1050.77M\n'
    elif command == ['netstat', '-nr']:
        return b'XfizswwNA9NkXz6K36ZExpjV08Y5IXkHI8jjDSV+5Nc=\n'
    else:
        assert False, 'Unhandled command: ' + str(command)

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
        self.assertEqual('Unknown\n', s.get_net_interfaces())
        self.assertEqual('Unknown\n', s.get_net_routing_table())
        self.assertEqual('Unknown\n', s.get_net_stats())
        self.assertEqual('Unknown\n', s.get_net_connections())

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
        self.assertEqual('Unknown\n', s.get_net_interfaces())
        self.assertEqual('Unknown\n', s.get_net_routing_table())
        self.assertEqual('Unknown\n', s.get_net_stats())
        self.assertEqual('Unknown\n', s.get_net_connections())

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

    def test_sysinfo_openbsd(self):
        """Tests the OpenBSD implementation of SysInfo. Note that this
        tests deep into the implementation, and not just the
        interfaces."""

        # Don't run this test on platform other than OpenBSD as some
        # system calls may not even be available.
        osname = platform.system()
        if osname != 'OpenBSD':
            return

        # Save and replace existing implementations of library functions
        # with mock ones for testing.
        old_platform_system = platform.system
        platform.system = _my_openbsd_platform_system
        old_os_sysconf = os.sysconf
        os.sysconf = _my_openbsd_os_sysconf
        old_subprocess_check_output = subprocess.check_output
        subprocess.check_output = _my_openbsd_subprocess_check_output

        s = SysInfoFromFactory()
        self.assertEqual(53, s.get_num_processors())
        self.assertEqual('blowfish.example.com', s.get_platform_hostname())
        self.assertFalse(s.get_platform_is_smp())

        self.assertLess(abs(76632 - s.get_uptime()), 4)
        self.assertEqual([0.7, 0.9, 0.8], s.get_loadavg())
        self.assertEqual(543214321, s.get_mem_total())
        self.assertEqual(543214321 - (121212 * 1024), s.get_mem_free())
        self.assertEqual(-1, s.get_mem_cached())
        self.assertEqual(-1, s.get_mem_buffers())
        self.assertEqual(566791168, s.get_mem_swap_total())
        self.assertEqual(566789120, s.get_mem_swap_free())
        self.assertRegexpMatches(s.get_platform_distro(), '^OpenBSD\s+.*')

        # These test that the corresponding tools are being called (and
        # no further processing is done on this data). Please see the
        # implementation functions at the top of this file.
        self.assertEqual('qB2osV6vUOjqm3P/+tQ4d92xoYz8/U8P9v3KWRpNwlI=\n', s.get_net_interfaces())
        self.assertEqual('XfizswwNA9NkXz6K36ZExpjV08Y5IXkHI8jjDSV+5Nc=\n', s.get_net_routing_table())
        self.assertEqual('osuxbrcc1g9VgaF4yf3FrtfodrfATrbSnjhqhuQSAs8=\n', s.get_net_stats())
        self.assertEqual('Z+w0lwa02/T+5+EIio84rrst/Dtizoz/aL9Im7J7ESA=\n', s.get_net_connections())

        # Restore original implementations.
        platform.system = old_platform_system
        os.sysconf = old_os_sysconf
        subprocess.check_output = old_subprocess_check_output

    def test_sysinfo_freebsd(self):
        """Tests the FreeBSD implementation of SysInfo. Note that this
        tests deep into the implementation, and not just the
        interfaces."""

        # Don't run this test on platform other than FreeBSD as some
        # system calls may not even be available.
        osname = platform.system()
        if osname != 'FreeBSD':
            return

        # Save and replace existing implementations of library functions
        # with mock ones for testing.
        old_platform_system = platform.system
        platform.system = _my_freebsd_platform_system
        old_os_sysconf = os.sysconf
        os.sysconf = _my_freebsd_os_sysconf
        old_subprocess_check_output = subprocess.check_output
        subprocess.check_output = _my_freebsd_subprocess_check_output

        s = SysInfoFromFactory()
        self.assertEqual(91, s.get_num_processors())
        self.assertEqual('daemon.example.com', s.get_platform_hostname())
        self.assertTrue(s.get_platform_is_smp())

        self.assertLess(abs(76632 - s.get_uptime()), 4)
        self.assertEqual([0.2, 0.4, 0.6], s.get_loadavg())
        self.assertEqual(987654321, s.get_mem_total())
        self.assertEqual(987654321 - (343434 * 1024), s.get_mem_free())
        self.assertEqual(-1, s.get_mem_cached())
        self.assertEqual(-1, s.get_mem_buffers())
        self.assertEqual(1037533184, s.get_mem_swap_total())
        self.assertEqual(1037533184, s.get_mem_swap_free())
        self.assertRegexpMatches(s.get_platform_distro(), '^FreeBSD\s+.*')

        # These test that the corresponding tools are being called (and
        # no further processing is done on this data). Please see the
        # implementation functions at the top of this file.
        self.assertEqual('qB2osV6vUOjqm3P/+tQ4d92xoYz8/U8P9v3KWRpNwlI=\n', s.get_net_interfaces())
        self.assertEqual('XfizswwNA9NkXz6K36ZExpjV08Y5IXkHI8jjDSV+5Nc=\n', s.get_net_routing_table())
        self.assertEqual('osuxbrcc1g9VgaF4yf3FrtfodrfATrbSnjhqhuQSAs8=\n', s.get_net_stats())
        self.assertEqual('Z+w0lwa02/T+5+EIio84rrst/Dtizoz/aL9Im7J7ESA=\n', s.get_net_connections())

        # Restore original implementations.
        platform.system = old_platform_system
        os.sysconf = old_os_sysconf
        subprocess.check_output = old_subprocess_check_output

    def test_sysinfo_osx(self):
        """Tests the OS X implementation of SysInfo. Note that this
        tests deep into the implementation, and not just the
        interfaces."""

        # Don't run this test on platform other than OS X as some
        # system calls may not even be available.
        osname = platform.system()
        if osname != 'Darwin':
            return

        # Save and replace existing implementations of library functions
        # with mock ones for testing.
        old_platform_system = platform.system
        platform.system = _my_osx_platform_system
        old_os_sysconf = os.sysconf
        os.sysconf = _my_osx_os_sysconf
        old_subprocess_check_output = subprocess.check_output
        subprocess.check_output = _my_osx_subprocess_check_output

        s = SysInfoFromFactory()
        self.assertEqual(91, s.get_num_processors())
        self.assertEqual('daemon.example.com', s.get_platform_hostname())
        self.assertFalse(s.get_platform_is_smp())

        self.assertLess(abs(76632 - s.get_uptime()), 4)
        self.assertEqual([0.2, 0.4, 0.6], s.get_loadavg())
        self.assertEqual(123456789, s.get_mem_total())
        self.assertEqual((23456 * 4096), s.get_mem_free())
        self.assertEqual(-1, s.get_mem_cached())
        self.assertEqual(-1, s.get_mem_buffers())
        self.assertEqual(18874368.0, s.get_mem_swap_total())
        self.assertEqual(1075988.48, s.get_mem_swap_free())
        self.assertRegexpMatches(s.get_platform_distro(), '^Darwin\s+.*')

        # These test that the corresponding tools are being called (and
        # no further processing is done on this data). Please see the
        # implementation functions at the top of this file.
        self.assertEqual('qB2osV6vUOjqm3P/+tQ4d92xoYz8/U8P9v3KWRpNwlI=\n', s.get_net_interfaces())
        self.assertEqual('XfizswwNA9NkXz6K36ZExpjV08Y5IXkHI8jjDSV+5Nc=\n', s.get_net_routing_table())
        self.assertEqual('osuxbrcc1g9VgaF4yf3FrtfodrfATrbSnjhqhuQSAs8=\n', s.get_net_stats())
        self.assertEqual('Z+w0lwa02/T+5+EIio84rrst/Dtizoz/aL9Im7J7ESA=\n', s.get_net_connections())

        # Restore original implementations.
        platform.system = old_platform_system
        os.sysconf = old_os_sysconf
        subprocess.check_output = old_subprocess_check_output

if __name__ == "__main__":
    unittest.main()
