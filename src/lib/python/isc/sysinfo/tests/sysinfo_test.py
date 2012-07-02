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
import unittest
import platform

def _my_system():
    return 'BIND10Testcase'

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

        old_system = platform.system
        platform.system = _my_system

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

        platform.system = old_system

if __name__ == "__main__":
    unittest.main()
