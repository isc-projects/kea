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

'''This module returns CPU information.'''

import os
import sys
import re
import subprocess
import os.path

class SysInfo:
    def __init__(self):
        self._num_processors = os.sysconf('SC_NPROCESSORS_CONF')
        self._endianness = sys.byteorder

        with open('/proc/sys/kernel/hostname') as f:
            self._hostname = f.read().strip()

        u = os.uname()
        self._platform_name = u[0]
        self._platform_version = u[2]
        self._platform_machine = u[4]

        with open('/proc/version') as f:
            self._platform_is_smp = ' SMP ' in f.read().strip()

        with open('/proc/uptime') as f:
            u = f.read().strip().split(' ')
            self._uptime = int(round(float(u[0])))

        with open('/proc/loadavg') as f:
            l = f.read().strip().split(' ')
            self._loadavg = [float(l[0]), float(l[1]), float(l[2])]

        with open('/proc/meminfo') as f:
            m = f.readlines()
            for line in m:
                r = re.match('^MemTotal:\s+(.*)\s*kB', line)
                if r:
                    self._mem_total = int(r.group(1).strip()) * 1024
                    continue
                r = re.match('^MemFree:\s+(.*)\s*kB', line)
                if r:
                    self._mem_free = int(r.group(1).strip()) * 1024
                    continue
                r = re.match('^Cached:\s+(.*)\s*kB', line)
                if r:
                    self._mem_cached = int(r.group(1).strip()) * 1024
                    continue
                r = re.match('^Buffers:\s+(.*)\s*kB', line)
                if r:
                    self._mem_buffers = int(r.group(1).strip()) * 1024
                    continue
                r = re.match('^SwapTotal:\s+(.*)\s*kB', line)
                if r:
                    self._mem_swap_total = int(r.group(1).strip()) * 1024
                    continue
                r = re.match('^SwapFree:\s+(.*)\s*kB', line)
                if r:
                    self._mem_swap_free = int(r.group(1).strip()) * 1024
                    continue

        self._platform_distro = None

        try:
            s = subprocess.check_output(['lsb_release', '-a'])
            for line in s.decode('utf-8').split('\n'):
                r = re.match('^Description:(.*)', line)
                if r:
                    self._platform_distro = r.group(1).strip()
                    break
        except (subprocess.CalledProcessError, OSError):
            pass

        if self._platform_distro is None:
            files = ['/etc/debian_release',
                     '/etc/debian_version',
                     '/etc/SuSE-release',
                     '/etc/UnitedLinux-release',
                     '/etc/mandrake-release',
                     '/etc/gentoo-release',
                     '/etc/fedora-release',
                     '/etc/redhat-release',
                     '/etc/redhat_version',
                     '/etc/slackware-release',
                     '/etc/slackware-version',
                     '/etc/arch-release',
                     '/etc/lsb-release',
                     '/etc/mageia-release']
            for fn in files:
                if os.path.exists(fn):
                    with open(fn) as f:
                        self._platform_distro = f.read().strip()
                    break

        if self._platform_distro is None:
            self._platform_distro = 'Unknown'

    def get_num_processors(self):
        # This is the number of hyperthreads when hyper-threading is
        # used. This is not entirely portable, so we'll have to handle
        # the case when it's not available.
        return self._num_processors

    def get_endianness(self):
        return self._endianness

    def get_hostname(self):
        return self._hostname

    def get_platform_name(self):
        return self._platform_name

    def get_platform_version(self):
        return self._platform_version

    def get_platform_machine(self):
        return self._platform_machine

    def get_platform_is_smp(self):
        return self._platform_is_smp

    def get_platform_distro(self):
        return self._platform_distro

    def get_uptime(self):
        return self._uptime

    def get_loadavg(self):
        return self._loadavg

    def get_mem_total(self):
        return self._mem_total

    def get_mem_free(self):
        return self._mem_free

    def get_mem_cached(self):
        return self._mem_cached

    def get_mem_buffers(self):
        return self._mem_buffers

    def get_mem_swap_total(self):
        return self._mem_swap_total

    def get_mem_swap_free(self):
        return self._mem_swap_free
