#!/usr/bin/env python3

# Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

"""Hammer - Kea development environment management tool."""

from __future__ import print_function

import os
import random
import re
import sys
import glob
import time
import json
import logging
import datetime
import platform
import binascii
import argparse
import textwrap
import functools
import subprocess
import multiprocessing
import grp
import pwd
import getpass

try:
    import urllib.request
except:
    pass
try:
    from urllib.parse import urljoin
except:
    from urlparse import urljoin

import xml.etree.ElementTree as ET


SYSTEMS = {
    'fedora': [
        #'27',  # EOLed
        #'28',  # EOLed
        #'29',  # EOLed
        #'30',  # EOLed
        #'31',  # EOLed
        '32',   # EOLed
        '33',   # EOLed
        '34',
        '35',
        '36'
    ],
    'centos': [
        '7',
        '8',
        '9',
    ],
    'rhel': [
        '8',
        '9',
    ],
    'ubuntu': [
        #'16.04',
        '18.04',
        #'18.10',  # EOLed
        #'19.04',  # EOLed
        #'19.10',  # EOLed
        '20.04',
        '20.10',
        '21.04',
        '22.04',
    ],
    'debian': [
        #'8',
        '9',
        '10',
        '11'
    ],
    'freebsd': [
        '11.2',
        '11.4',
        '12.0',
        '12.1',
        '13.0',
    ],
    'alpine': [
        #'3.10',   # EOLed
        #'3.11',   # EOLed
        #'3.12',   # EOLed
        '3.13',
        '3.14',
        '3.15',
        '3.16',
    ],
    'arch': []
}

# pylint: disable=C0326
IMAGE_TEMPLATES = {
    # fedora
    'fedora-27-lxc':           {'bare': 'lxc-fedora-27',               'kea': 'godfryd/kea-fedora-27'},
    'fedora-27-virtualbox':    {'bare': 'generic/fedora27',            'kea': 'godfryd/kea-fedora-27'},
    'fedora-28-lxc':           {'bare': 'godfryd/lxc-fedora-28',       'kea': 'godfryd/kea-fedora-28'},
    'fedora-28-virtualbox':    {'bare': 'generic/fedora28',            'kea': 'godfryd/kea-fedora-28'},
    'fedora-29-lxc':           {'bare': 'godfryd/lxc-fedora-29',       'kea': 'godfryd/kea-fedora-29'},
    'fedora-29-virtualbox':    {'bare': 'generic/fedora29',            'kea': 'godfryd/kea-fedora-29'},
    'fedora-30-lxc':           {'bare': 'godfryd/lxc-fedora-30',       'kea': 'godfryd/kea-fedora-30'},
    'fedora-30-virtualbox':    {'bare': 'generic/fedora30',            'kea': 'godfryd/kea-fedora-30'},
    'fedora-31-lxc':           {'bare': 'isc/lxc-fedora-31',           'kea': 'isc/kea-fedora-31'},
    'fedora-31-virtualbox':    {'bare': 'isc/vbox-fedora-31',          'kea': 'isc/kea-fedora-31'},
    'fedora-32-lxc':           {'bare': 'isc/lxc-fedora-32',           'kea': 'isc/kea-fedora-32'},
    'fedora-33-lxc':           {'bare': 'isc/lxc-fedora-33',           'kea': 'isc/kea-fedora-33'},
    'fedora-34-lxc':           {'bare': 'isc/lxc-fedora-34',           'kea': 'isc/kea-fedora-34'},
    'fedora-35-lxc':           {'bare': 'isc/lxc-fedora-35',           'kea': 'isc/kea-fedora-35'},
    'fedora-36-lxc':           {'bare': 'isc/lxc-fedora-36',           'kea': 'isc/kea-fedora-36'},

    # centos
    'centos-7-lxc':            {'bare': 'isc/lxc-centos-7',            'kea': 'isc/kea-centos-7'},
    'centos-7-virtualbox':     {'bare': 'generic/centos7',             'kea': 'godfryd/kea-centos-7'},
    'centos-8-lxc':            {'bare': 'isc/lxc-centos-8',            'kea': 'isc/kea-centos-8'},
    'centos-8-virtualbox':     {'bare': 'generic/centos8',             'kea': 'isc/kea-centos-8'},

    # rhel
    'rhel-8-virtualbox':       {'bare': 'generic/rhel8',               'kea': 'generic/rhel8'},

    # ubuntu
    'ubuntu-16.04-lxc':        {'bare': 'godfryd/lxc-ubuntu-16.04',    'kea': 'godfryd/kea-ubuntu-16.04'},
    'ubuntu-16.04-virtualbox': {'bare': 'ubuntu/xenial64',             'kea': 'godfryd/kea-ubuntu-16.04'},
    'ubuntu-18.04-lxc':        {'bare': 'isc/lxc-ubuntu-18.04',        'kea': 'isc/kea-ubuntu-18.04'},
    'ubuntu-18.04-virtualbox': {'bare': 'ubuntu/bionic64',             'kea': 'godfryd/kea-ubuntu-18.04'},
    'ubuntu-18.10-lxc':        {'bare': 'godfryd/lxc-ubuntu-18.10',    'kea': 'godfryd/kea-ubuntu-18.10'},
    'ubuntu-18.10-virtualbox': {'bare': 'ubuntu/cosmic64',             'kea': 'godfryd/kea-ubuntu-18.10'},
    'ubuntu-19.04-lxc':        {'bare': 'godfryd/lxc-ubuntu-19.04',    'kea': 'godfryd/kea-ubuntu-19.04'},
    'ubuntu-19.04-virtualbox': {'bare': 'ubuntu/disco64',              'kea': 'godfryd/kea-ubuntu-19.04'},
    'ubuntu-19.10-lxc':        {'bare': 'isc/lxc-ubuntu-19.10',        'kea': 'isc/kea-ubuntu-19.10'},
    'ubuntu-19.10-virtualbox': {'bare': 'generic/ubuntu1910',          'kea': 'isc/kea-ubuntu-19.10'},
    'ubuntu-20.04-lxc':        {'bare': 'isc/lxc-ubuntu-20.04',        'kea': 'isc/kea-ubuntu-20.04'},
    'ubuntu-20.10-lxc':        {'bare': 'isc/lxc-ubuntu-20.10',        'kea': 'isc/kea-ubuntu-20.10'},
    'ubuntu-21.04-lxc':        {'bare': 'isc/lxc-ubuntu-21.04',        'kea': 'isc/kea-ubuntu-21.04'},
    'ubuntu-22.04-lxc':        {'bare': 'isc/lxc-ubuntu-22.04',        'kea': 'isc/lxc-ubuntu-22.04'},

    # debian
    'debian-8-lxc':            {'bare': 'godfryd/lxc-debian-8',        'kea': 'godfryd/kea-debian-8'},
    'debian-8-virtualbox':     {'bare': 'debian/jessie64',             'kea': 'godfryd/kea-debian-8'},
    'debian-9-lxc':            {'bare': 'isc/lxc-debian-9',            'kea': 'isc/kea-debian-9'},
    'debian-9-virtualbox':     {'bare': 'debian/stretch64',            'kea': 'godfryd/kea-debian-9'},
    'debian-10-lxc':           {'bare': 'isc/lxc-debian-10',           'kea': 'isc/kea-debian-10'},
    'debian-10-virtualbox':    {'bare': 'debian/buster64',             'kea': 'godfryd/kea-debian-10'},
    'debian-11-lxc':           {'bare': 'isc/lxc-debian-11',           'kea': 'isc/kea-debian-11'},

    # freebsd
    'freebsd-11.2-virtualbox': {'bare': 'generic/freebsd11',           'kea': 'godfryd/kea-freebsd-11.2'},
    'freebsd-12.0-virtualbox': {'bare': 'generic/freebsd12',           'kea': 'godfryd/kea-freebsd-12.0'},
    'freebsd-13.0-virtualbox': {'bare': 'isc/vbox-freebsd-13.0',       'kea': 'isc/kea-freebsd-13.0'},

    # alpine
    'alpine-3.10-lxc':         {'bare': 'godfryd/lxc-alpine-3.10',     'kea': 'godfryd/kea-alpine-3.10'},
    'alpine-3.11-lxc':         {'bare': 'isc/lxc-alpine-3.11',         'kea': 'isc/kea-alpine-3.11'},
    'alpine-3.12-lxc':         {'bare': 'isc/lxc-alpine-3.12',         'kea': 'isc/kea-alpine-3.12'},
    'alpine-3.13-lxc':         {'bare': 'isc/lxc-alpine-3.13',         'kea': 'isc/kea-alpine-3.13'},
    'alpine-3.14-lxc':         {'bare': 'isc/lxc-alpine-3.14',         'kea': 'isc/kea-alpine-3.14'},
    'alpine-3.15-lxc':         {'bare': 'isc/lxc-alpine-3.15',         'kea': 'isc/kea-alpine-3.15'},
    'alpine-3.16-lxc':         {'bare': 'isc/lxc-alpine-3.16',         'kea': 'isc/kea-alpine-3.16'},
}

# NOTES
# ** Alpine **
# 1. Extracting rootfs is failing:
#    It requires commenting out checking if rootfs has been extracted as it checks for file /bin/true which is a link.
#    Comment out in ~/.vagrant.d/gems/2.X.Y/gems/vagrant-lxc-1.4.3/scripts/lxc-template near 'Failed to extract rootfs'


LXC_VAGRANTFILE_TPL = """# -*- mode: ruby -*-
# vi: set ft=ruby :
ENV["LC_ALL"] = "C"

Vagrant.configure("2") do |config|
  {hostname}

  config.vm.box = "{image_tpl}"
  {box_version}

  config.vm.provider "lxc" do |lxc|
    lxc.container_name = "{name}"
    lxc.customize 'rootfs.path', "/var/lib/lxc/{name}/rootfs"
  end

  config.vm.synced_folder '.', '/vagrant', disabled: true
  config.vm.synced_folder '{ccache_dir}', '/ccache'
end
"""

VBOX_VAGRANTFILE_TPL = """# -*- mode: ruby -*-
# vi: set ft=ruby :
ENV["LC_ALL"] = "C"

Vagrant.configure("2") do |config|
  config.vm.hostname = "{name}"

  config.vm.box = "{image_tpl}"
  {box_version}

  config.vm.provider "virtualbox" do |v|
    v.name = "{name}"
    v.memory = 8192

    nproc = Etc.nprocessors
    if nproc > 8
      nproc -= 2
    elsif nproc > 1
      nproc -= 1
    end
    v.cpus = nproc
  end

  config.vm.synced_folder '.', '/vagrant', disabled: true
end
"""

RECOMMENDED_VAGRANT_VERSION='2.2.16'

log = logging.getLogger()


def red(txt):
    """Return colorized (if the terminal supports it) or plain text."""
    if sys.stdout.isatty():
        return '\033[1;31m%s\033[0;0m' % txt
    return txt

def green(txt):
    """Return colorized (if the terminal supports it) or plain text."""
    if sys.stdout.isatty():
        return '\033[0;32m%s\033[0;0m' % txt
    return txt

def blue(txt):
    """Return colorized (if the terminal supports it) or plain text."""
    if sys.stdout.isatty():
        return '\033[0;34m%s\033[0;0m' % txt
    return txt


def get_system_revision():
    """Return tuple containing system name and its revision."""
    system = platform.system()
    if system == 'Linux':
        system, revision = None, None
        try:
            system, revision, _ = platform.dist()  # pylint: disable=deprecated-method
            if system == 'debian':
                revision = revision.split('.')[0]
            elif system == 'redhat':
                system = 'rhel'
                revision = revision[0]
            elif system == 'centos':
                revision = revision[0]
            if not system or not revision:
                raise Exception('fallback to /etc/os-release')
        except:
            if os.path.exists('/etc/os-release'):
                vals = {}
                with open('/etc/os-release') as f:
                    for l in f.readlines():
                        if '=' in l:
                            key, val = l.split('=', 1)
                            vals[key.strip()] = val.strip().replace('"', '')

                for i in ['ID', 'ID_LIKE']:
                    if i in vals:
                        system_candidate=vals[i].strip('"')
                        if system_candidate in SYSTEMS:
                            system = system_candidate
                            break
                if system is None:
                    raise Exception('cannot determine system')

                for i in ['VERSION_ID', 'BUILD_ID']:
                    if i in vals:
                        revision = vals[i]
                        break
                if revision is None:
                    raise Exception('cannot determine revision')

                if system in ['alpine', 'rhel']:
                    revision = revision.rsplit('.', 1)[0]
            else:
                raise Exception('cannot determine system or its revision')
    elif system == 'FreeBSD':
        system = system.lower()
        revision = platform.release()
    if '"' in revision:
        revision = revision.replace('"', '')
    if '"' in system:
        system = system.replace('"', '')

    system = system.lower()
    return system, revision


class ExecutionError(Exception):
    """Exception thrown when execution encountered an error."""
    pass


def execute(cmd, timeout=60, cwd=None, env=None, raise_error=True, dry_run=False, log_file_path=None,
            quiet=False, check_times=False, capture=False, interactive=False, attempts=1,
            sleep_time_after_attempt=None, super_quiet=False):
    """Execute a command in shell.

    :param str cmd: a command to be executed
    :param int timeout: timeout in number of seconds, after that time the command is terminated
                        but only if check_times is True
    :param str cwd: current working directory for the command
    :param dict env: dictionary with environment variables
    :param bool raise_error: if False then in case of error exception is not raised,
                             default: True ie exception is raise
    :param bool dry_run: if True then the command is not executed
    :param str log_file_path: if provided then all traces from the command are stored in indicated file
    :param bool quiet: if True then the command's traces are not printed to stdout
    :param bool check_times: if True then timeout is taken into account
    :param bool capture: if True then the command's traces are captured and returned by the function
    :param bool interactive: if True then stdin and stdout are not redirected, traces handling is disabled,
                             used for e.g. SSH
    :param int attempts: number of attempts to run the command if it fails
    :param int sleep_time_after_attempt: number of seconds to sleep before taking next attempt
    :param bool super_quiet: if True, set quiet to True and don't log command
    """
    if super_quiet:
        quiet = True
    if cwd and "~/" in cwd:
        # replace relative home directory
        cwd = cwd.replace('~', os.environ['HOME'])
    if not super_quiet:
        log.info('>>>>> Executing %s in %s', cmd, cwd if cwd else os.getcwd())
    if not check_times:
        timeout = None
    if dry_run:
        return 0

    if 'sudo' in cmd and env:
        # if sudo is used and env is overridden then to preserve env add -E to sudo
        cmd = cmd.replace('sudo', 'sudo -E')

    if log_file_path:
        log_file = open(log_file_path, "wb")

    for attempt in range(attempts):
        if interactive:
            p = subprocess.Popen(cmd, cwd=cwd, env=env, shell=True)
            exitcode = p.wait()

        else:
            p = subprocess.Popen(cmd, cwd=cwd, env=env, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

            if capture:
                output = ''
            t0 = time.time()
            # repeat until process is running or timeout not occurred
            while True:
                line = p.stdout.readline()
                if line:
                    line_decoded = line.decode(encoding='ascii', errors='ignore').rstrip() + '\r'
                    if not quiet:
                        log.info(line_decoded)
                    if capture:
                        output += line_decoded
                    if log_file_path:
                        log_file.write(line)
                t1 = time.time()
                if p.poll() is not None or (timeout is not None and timeout < t1 - t0):
                    break

            # If no exitcode yet, ie. process is still running then it means that timeout occurred.
            # In such case terminate the process and raise an exception.
            if p.poll() is None:
                # kill using sudo to be able to kill other sudo commands
                execute('sudo kill -s TERM %s' % p.pid)
                time.sleep(5)
                # if still running, kill harder
                if p.poll() is None:
                    execute('sudo kill -s KILL %s' % p.pid)
                msg = "Execution timeout, %d > %d seconds elapsed (start: %d, stop %d), cmd: '%s'"
                msg = msg % (t1 - t0, timeout, t0, t1, cmd)
                raise ExecutionError(msg)
            exitcode = p.returncode

        if exitcode == 0:
            break
        elif attempt < attempts - 1:
            txt = 'command failed, retry, attempt %d/%d' % (attempt, attempts)
            if log_file_path:
                txt_to_file = '\n\n[HAMMER] %s\n\n\n' % txt
                log_file.write(txt_to_file.encode('ascii'))
            log.info(txt)
            if sleep_time_after_attempt:
                time.sleep(sleep_time_after_attempt)

    if log_file_path:
        log_file.close()

    if exitcode != 0 and raise_error:
        if capture and quiet:
            log.error(output)
        raise ExecutionError("The command return non-zero exitcode %s, cmd: '%s'" % (exitcode, cmd))

    if capture:
        return exitcode, output
    return exitcode


def _append_to_file(file_name, line):
    with open(file_name, encoding='utf-8', mode='a') as f:
        f.write(line + '\n')


def _prepare_installed_packages_cache_for_debs():
    pkg_cache = {}

    _, out = execute("dpkg -l", timeout=15, capture=True, quiet=True)

    for line in out.splitlines():
        line = line.strip()
        m = re.search('^([^\s]+)\s+([^\s]+)\s+([^\s]+)\s+([^\s]+)\s+(.+)', line)
        if not m:
            continue
        status, name, version, arch, descr = m.groups()
        name = name.split(':')[0]
        pkg_cache[name] = dict(status=status, version=version, arch=arch, descr=descr)

    return pkg_cache


def _prepare_installed_packages_cache_for_rpms():
    pkg_cache = {}

    _, out = execute("rpm -qa --qf '%{NAME}\\n'", timeout=15, capture=True, quiet=True)

    for line in out.splitlines():
        name = line.strip()
        pkg_cache[name] = dict(status='ii')

    return pkg_cache


def _prepare_installed_packages_cache_for_alpine():
    pkg_cache = {}

    _, out = execute("apk list -I\\n'", timeout=15, capture=True, quiet=True)

    for line in out.splitlines():
        name = line.strip()
        pkg_cache[name] = dict(status='ii')

    return pkg_cache


def install_pkgs(pkgs, timeout=60, env=None, check_times=False, pkg_cache=None):
    """Install native packages in a system.

    :param dict pkgs: specifies a list of packages to be installed
    :param int timeout: timeout in number of seconds, after that time the command
                        is terminated but only if check_times is True
    :param dict env: dictionary with environment variables (optional)
    :param bool check_times: specifies if timeouts should be enabled (optional)
    """
    system, revision = get_system_revision()

    if not isinstance(pkgs, list):
        pkgs = pkgs.split()

    if pkg_cache is None:
        pkg_cache = {}

    # prepare cache if needed
    if not pkg_cache and system in ['centos', 'rhel', 'fedora', 'debian', 'ubuntu']:#, 'alpine']: # TODO: complete caching support for alpine
        if system in ['centos', 'rhel', 'fedora']:
            pkg_cache.update(_prepare_installed_packages_cache_for_rpms())
        elif system in ['debian', 'ubuntu']:
            pkg_cache.update(_prepare_installed_packages_cache_for_debs())
        elif system in ['alpine']:
            pkg_cache.update(_prepare_installed_packages_cache_for_alpine())

    # check if packages actually need to be installed
    if pkg_cache:
        pkgs_to_install = []
        pkgs_installed = []
        for pkg in pkgs:
            if pkg not in pkg_cache or pkg_cache[pkg]['status'] != 'ii':
                pkgs_to_install.append(pkg)
            else:
                pkgs_installed.append(pkg)
        if pkgs_installed:
            log.info('packages already installed: %s', ', '.join(pkgs_installed))
        pkgs = pkgs_to_install

    if not pkgs:
        log.info('all packages already installed')
        return

    if system in ['centos', 'fedora', 'rhel']:
        if system in ['centos', 'rhel'] and revision == '7':
            execute('sudo yum install -y dnf')
        cmd = 'sudo dnf -y install'
    elif system in ['debian', 'ubuntu']:
        # prepare the command for ubuntu/debian
        if not env:
            env = os.environ.copy()
        env['DEBIAN_FRONTEND'] = 'noninteractive'
        cmd = 'sudo apt install --no-install-recommends -y'
    elif system == 'freebsd':
        cmd = 'sudo pkg install -y'
    elif system == 'alpine':
        cmd = 'sudo apk add'
    elif system == 'arch':
        cmd = 'sudo pacman -S --needed --noconfirm --overwrite \'*\''
    else:
        raise NotImplementedError('no implementation for %s' % system)

    pkgs = ' '.join(pkgs)
    cmd += ' ' + pkgs
    execute(cmd, timeout=timeout, env=env, check_times=check_times, attempts=3, sleep_time_after_attempt=10)


def get_image_template(key, variant):
    if key not in IMAGE_TEMPLATES:
        print('ERROR: Image {} is not available.'.format(key), file=sys.stderr)
        sys.exit(1)
    if variant not in IMAGE_TEMPLATES[key]:
        print('ERROR: Variant {} is not available for image {}.'.format(variant, key), file=sys.stderr)
        sys.exit(1)
    return IMAGE_TEMPLATES[key][variant]


def _get_full_repo_url(repository_url, system, revision, pkg_version):
    if not repository_url:
        return None
    repo_name = 'kea-%s-%s-%s' % (pkg_version.rsplit('.', 1)[0], system, revision)
    repo_url = urljoin(repository_url, 'repository')
    repo_url += '/%s-ci/' % repo_name
    return repo_url


class VagrantEnv(object):
    """Helper class that makes interacting with Vagrant easier.

    It creates Vagrantfile according to specified system. It exposes basic Vagrant functions
    like up, upload, destroy, ssh. It also provides more complex function for preparing system
    for Kea build and building Kea.
    """

    def __init__(self, provider, system, revision, features, image_template_variant,
                 dry_run, quiet=False, check_times=False, ccache_dir=None):
        """VagrantEnv initializer.

        :param str provider: indicate backend type: virtualbox or lxc
        :param str system: name of the system eg. ubuntu
        :param str revision: revision of the system e.g. 18.04
        :param list features: list of requested features
        :param str image_template_variant: variant of images' templates: bare or kea
        :param bool dry_run: if False then system commands are not really executed
        :param bool quiet: if True then commands will not trace to stdout
        :param bool check_times: if True then commands will be terminated after given timeout
        """
        self.provider = provider
        self.system = system
        self.revision = revision
        self.features = features
        self.dry_run = dry_run
        self.quiet = quiet
        self.check_times = check_times

        # set properly later
        self.features_arg = None
        self.nofeatures_arg = None
        self.python = None

        self.key = key = "%s-%s-%s" % (system, revision, provider)
        self.image_tpl = image_tpl = get_image_template(key, image_template_variant)
        self.repo_dir = os.getcwd()

        sys_dir = "%s-%s" % (system, revision)
        if provider == "virtualbox":
            self.vagrant_dir = os.path.join(self.repo_dir, 'hammer', sys_dir, 'vbox')
        elif provider == "lxc":
            self.vagrant_dir = os.path.join(self.repo_dir, 'hammer', sys_dir, 'lxc')

        if ccache_dir is None:
            self.ccache_dir = '/'
            self.ccache_enabled = False
        else:
            self.ccache_dir = ccache_dir
            self.ccache_enabled = True

        self.init_files()

    def init_files(self):
        if not os.path.exists(self.vagrant_dir):
            os.makedirs(self.vagrant_dir)

        vagrantfile_path = os.path.join(self.vagrant_dir, "Vagrantfile")

        crc = binascii.crc32(self.vagrant_dir.encode())
        self.name = "hmr-%s-%s-kea-srv-%08d" % (self.system, self.revision.replace('.', '-'), crc)

        if '/' in self.image_tpl:
            self.latest_version = self._get_latest_cloud_version()
            box_version = 'config.vm.box_version = "%s"' % self.latest_version
        else:
            self.latest_version = None
            box_version = ""

        # alpine has a problem with setting hostname so skip it
        if self.system == 'alpine':
            hostname = ''
        else:
            hostname = 'config.vm.hostname = "%s"' % self.name

        if self.provider == "virtualbox":
            vagrantfile_tpl = VBOX_VAGRANTFILE_TPL
        elif self.provider == "lxc":
            vagrantfile_tpl = LXC_VAGRANTFILE_TPL

        vagrantfile = vagrantfile_tpl.format(image_tpl=self.image_tpl,
                                             name=self.name,
                                             ccache_dir=self.ccache_dir,
                                             box_version=box_version,
                                             hostname=hostname)

        with open(vagrantfile_path, "w") as f:
            f.write(vagrantfile)

        log.info('Prepared vagrant system %s in %s', self.name, self.vagrant_dir)

    def up(self):
        """Do Vagrant up."""
        exitcode, out = execute("vagrant up --no-provision --provider %s" % self.provider,
                                cwd=self.vagrant_dir, timeout=15 * 60, dry_run=self.dry_run,
                                capture=True, raise_error=False)
        if exitcode != 0:
            if 'There is container on your system' in out and 'lxc-destroy' in out:
                m = re.search('`lxc-destroy.*?`', out)
                if m:
                    # destroy some old container
                    cmd = m.group(0)[1:-1]
                    cmd = 'sudo ' + cmd + ' -f'
                    execute(cmd, timeout=60)

                    # try again spinning up new
                    execute("vagrant up --no-provision --provider %s" % self.provider,
                            cwd=self.vagrant_dir, timeout=15 * 60, dry_run=self.dry_run)
                    return
            raise ExecutionError('There is a problem with putting up a system')

    def _get_cloud_meta(self, image_tpl=None):
        if '/' not in self.image_tpl:
            return {}
        url = 'https://app.vagrantup.com/api/v1/box/' + (image_tpl if image_tpl else self.image_tpl)
        try:
            with urllib.request.urlopen(url) as response:
                data = response.read()
        except:
            log.exception('ignored exception')
            return {}
        data = json.loads(data)
        return data

    def _get_local_meta(self):
        meta_file = os.path.join(self.vagrant_dir, '.vagrant/machines/default', self.provider, 'box_meta')
        if not os.path.exists(meta_file):
            return {}
        with open(meta_file) as f:
            data = f.read()
        data = json.loads(data)
        return data

    def _get_latest_cloud_version(self, image_tpl=None):
        cloud_meta = self._get_cloud_meta(image_tpl)
        if not cloud_meta and 'versions' not in cloud_meta:
            return 0
        latest_version = 0
        for ver in cloud_meta['versions']:
            provider_found = False
            for p in ver['providers']:
                if p['name'] == self.provider:
                    provider_found = True
                    break
            if provider_found:
                try:
                    v = int(ver['number'])
                except:
                    return ver['number']
                if v > latest_version:
                    latest_version = v
        return latest_version

    def get_status(self):
        """Return system status.

        Status can be: 'not created', 'running', 'stopped', etc.
        """
        if not os.path.exists(self.vagrant_dir):
            return "not created"

        _, out = execute("vagrant status", cwd=self.vagrant_dir, timeout=15, capture=True, quiet=True)
        m = re.search('default\s+(.+)\(', out)
        if not m:
            raise Exception('cannot get status in:\n%s' % out)
        return m.group(1).strip()

    def bring_up_latest_box(self):
        if self.get_status() == 'running':
            self.reload()
        else:
            self.up()

    def reload(self):
        """Do Vagrant reload."""
        execute("vagrant reload --no-provision --force",
                cwd=self.vagrant_dir, timeout=15 * 60, dry_run=self.dry_run)


    def package(self):
        """Package Vagrant system into Vagrant box."""
        execute('vagrant halt', cwd=self.vagrant_dir, dry_run=self.dry_run, raise_error=False, attempts=3)

        box_path = os.path.join(self.vagrant_dir, 'kea-%s-%s.box' % (self.system, self.revision))
        if os.path.exists(box_path):
            os.unlink(box_path)

        if self.provider == 'virtualbox':
            cmd = "vagrant package --output %s" % box_path
            execute(cmd, cwd=self.vagrant_dir, timeout=4 * 60, dry_run=self.dry_run)

        elif self.provider == 'lxc':
            lxc_box_dir = os.path.join(self.vagrant_dir, 'lxc-box')
            if os.path.exists(lxc_box_dir):
                execute('sudo rm -rf %s' % lxc_box_dir)
            os.mkdir(lxc_box_dir)
            lxc_container_path = os.path.join('/var/lib/lxc', self.name)

            # add vagrant universal key to accepted keys
            execute('sudo bash -c \'echo "ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEA6NF8ia'
                    'llvQVp22WDkTkyrtvp9eWW6A8YVr+kz4TjGYe7gHzIw+niNltGEFHzD8+v1I2YJ'
                    '6oXevct1YeS0o9HZyN1Q9qgCgzUFtdOKLv6IedplqoPkcmF0aYet2PkEDo3MlTB'
                    'ckFXPITAMzF8dJSIFo9D8HfdOV0IAdx4O7PtixWKn5y2hMNG0zQPyUecp4pzC6k'
                    'ivAIhyfHilFR61RGL+GPXQ2MWZWFYbAGjyiYJnAmCP3NOTd0jMZEnDkbUvxhMmB'
                    'YSdETk1rRgm+R4LOzFUGaHqHDLKLX+FIPKcF96hrucXzcWyLbIbEgE98OHlnVYC'
                    'zRdK8jlqm8tehUc9c9WhQ== vagrant insecure public key"'
                    '> %s/rootfs/home/vagrant/.ssh/authorized_keys\'' % lxc_container_path)

            # reset machine-id
            execute('sudo rm -f %s/rootfs/var/lib/dbus/machine-id' % lxc_container_path)
            #execute('sudo truncate -s 0 %s/rootfs/etc/machine-id' % lxc_container_path)
            execute('sudo rm -f %s/rootfs/etc/machine-id' % lxc_container_path)

            # pack rootfs
            cmd = 'sudo bash -c "'
            cmd += 'cd %s '
            cmd += '&& tar --numeric-owner --anchored --exclude=./rootfs/dev/log -czf %s/rootfs.tar.gz ./rootfs/*'
            cmd += '"'
            execute(cmd % (lxc_container_path, lxc_box_dir))

            # copy lxc config from runtime container
            execute('sudo cp %s/config %s/lxc-config' % (lxc_container_path, lxc_box_dir))
            # remove mac address from eth0 - it should be dynamically assigned
            execute("sudo sed -i '/lxc.net.0.hwaddr/d' %s/lxc-config" % lxc_box_dir)
            # correct files ownership
            execute('sudo chown `id -un`:`id -gn` *', cwd=lxc_box_dir)
            # and other metadata
            with open(os.path.join(lxc_box_dir, 'metadata.json'), 'w') as f:
                now = datetime.datetime.now()
                f.write('{\n')
                f.write('  "provider": "lxc",\n')
                f.write('  "version":  "1.0.0",\n')
                f.write('  "built-on": "%s"\n' % now.strftime('%c'))
                f.write('}\n')

            # pack vagrant box with metadata and config
            execute('tar -czf %s ./*' % box_path, cwd=lxc_box_dir)
            execute('sudo rm -rf %s' % lxc_box_dir)

        return box_path

    def upload_to_cloud(self, box_path):
        image_tpl = get_image_template(self.key, 'kea')
        if '/' not in image_tpl:
            return

        latest_version = self._get_latest_cloud_version(image_tpl)
        new_version = latest_version + 1

        cmd = "vagrant cloud publish --no-private -f -r %s %s %s %s"
        cmd = cmd % (image_tpl, new_version, self.provider, box_path)

        execute(cmd, cwd=self.vagrant_dir, timeout=60 * 60)

    def upload(self, src):
        """Upload src to Vagrant system, home folder."""
        attempt = 4
        while attempt > 0:
            exitcode = execute('vagrant upload %s' % src, cwd=self.vagrant_dir, dry_run=self.dry_run, raise_error=False)
            if exitcode == 0:
                break
            attempt -= 1
        if exitcode != 0:
            msg = 'cannot upload %s' % src
            log.error(msg)
            raise ExecutionError(msg)

    def run_build_and_test(self, tarball_path, jobs, pkg_version, pkg_isc_version, upload, repository_url):
        """Run build and unit tests inside Vagrant system."""
        if self.dry_run:
            return 0, 0

        # prepare tarball if needed and upload it to vagrant system
        if not tarball_path:
            execute('mkdir -p ~/.hammer-tmp')
            name_ver = 'kea-%s' % pkg_version
            cmd = 'tar --transform "flags=r;s|^|%s/|" --exclude hammer ' % name_ver
            cmd += ' --exclude "*~" --exclude .git --exclude .libs '
            cmd += ' --exclude .deps --exclude \'*.o\'  --exclude \'*.lo\' '
            cmd += ' -zcf ~/.hammer-tmp/%s.tar.gz .' % name_ver
            execute(cmd)
            tarball_path = '~/.hammer-tmp/%s.tar.gz' % name_ver
        self.upload(tarball_path)
        execute('rm -rf ~/.hammer-tmp')

        log_file_path = os.path.join(self.vagrant_dir, 'build.log')
        log.info('Build log file stored to %s', log_file_path)

        t0 = time.time()

        # run build command
        bld_cmd = "{python} hammer.py build -p local {features} {nofeatures} {check_times} {ccache}"
        bld_cmd += " {tarball} {jobs} {pkg_version} {pkg_isc_version} {repository_url}"
        bld_cmd = bld_cmd.format(python=self.python,
                                 features=self.features_arg,
                                 nofeatures=self.nofeatures_arg,
                                 check_times='-i' if self.check_times else '',
                                 ccache='--ccache-dir /ccache' if self.ccache_enabled else '',
                                 tarball='-t ~/%s.tar.gz' % name_ver,
                                 jobs='-j %d' % jobs,
                                 pkg_version='--pkg-version %s' % pkg_version,
                                 pkg_isc_version='--pkg-isc-version %s' % pkg_isc_version,
                                 repository_url=('--repository-url %s' % repository_url) if repository_url else '')

        timeout = _calculate_build_timeout(self.features) + 5 * 60
        # executes hammer.py inside LXC container
        self.execute(bld_cmd, timeout=timeout, log_file_path=log_file_path, quiet=self.quiet)  # timeout: 40 minutes

        ssh_cfg_path = self.dump_ssh_config()

        if 'native-pkg' in self.features:
            pkgs_dir = os.path.join(self.vagrant_dir, 'pkgs')
            if os.path.exists(pkgs_dir):
                execute('rm -rf %s' % pkgs_dir)
            os.makedirs(pkgs_dir)

            # copy results of _build_native_pkg
            execute('scp -F %s -r default:~/kea-pkg/* .' % ssh_cfg_path, cwd=pkgs_dir)

            if upload:
                repo_url = _get_full_repo_url(repository_url, self.system, self.revision, pkg_version)
                assert repo_url is not None
                upload_cmd = 'curl -v --netrc -f'

                if self.system in ['ubuntu', 'debian']:
                    upload_cmd += ' -X POST -H "Content-Type: multipart/form-data" --data-binary "@%s" '
                    file_ext = '.deb'

                elif self.system in ['fedora', 'centos', 'rhel']:
                    upload_cmd += ' --upload-file %s '
                    file_ext = '.rpm'

                elif self.system == 'alpine':
                    upload_cmd += ' --upload-file %s '
                    file_ext = ''
                    repo_url = urljoin(repo_url, '%s/v%s/x86_64/' % (pkg_isc_version, self.revision))

                upload_cmd += ' ' + repo_url

                for fn in os.listdir(pkgs_dir):
                    if file_ext and not fn.endswith(file_ext):
                        continue
                    fp = os.path.join(pkgs_dir, fn)
                    cmd = upload_cmd % fp
                    execute(cmd)

        t1 = time.time()
        dt = int(t1 - t0)

        log.info('Build log file stored to %s', log_file_path)
        log.info("")
        log.info(">>>>>> Build time %s:%s", dt // 60, dt % 60)
        log.info("")

        # run unit tests if requested
        total = 0
        passed = 0
        try:
            if 'unittest' in self.features:
                cmd = 'scp -F %s -r default:/home/vagrant/unit-test-results.json .' % ssh_cfg_path
                execute(cmd, cwd=self.vagrant_dir)
                results_file = os.path.join(self.vagrant_dir, 'unit-test-results.json')
                if os.path.exists(results_file):
                    with open(results_file) as f:
                        txt = f.read()
                        results = json.loads(txt)
                        total = results['grand_total']
                        passed = results['grand_passed']

                cmd = 'scp -F %s -r default:/home/vagrant/aggregated_tests.xml .' % ssh_cfg_path
                execute(cmd, cwd=self.vagrant_dir)
        except:  # pylint: disable=bare-except
            log.exception('ignored issue with parsing unit test results')

        return total, passed

    def destroy(self):
        """Remove the VM completely."""
        if os.path.exists(self.vagrant_dir):
            cmd = 'vagrant destroy --force'
            execute(cmd, cwd=self.vagrant_dir, timeout=3 * 60, dry_run=self.dry_run)  # timeout: 3 minutes
            execute('rm -rf %s' % self.vagrant_dir)

    def ssh(self):
        """Open interactive session to the VM."""
        execute('vagrant ssh', cwd=self.vagrant_dir, timeout=None, dry_run=self.dry_run, interactive=True)

    def dump_ssh_config(self):
        """Dump ssh config that allows getting into Vagrant system via SSH."""
        ssh_cfg_path = os.path.join(self.vagrant_dir, 'ssh.cfg')
        execute('vagrant ssh-config > %s' % ssh_cfg_path, cwd=self.vagrant_dir)
        return ssh_cfg_path

    def execute(self, cmd, timeout=None, raise_error=True, log_file_path=None, quiet=False, env=None,
                attempts=1, sleep_time_after_attempt=None):
        """Execute provided command inside Vagrant system."""
        if not env:
            env = os.environ.copy()
        env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

        return execute('vagrant ssh -c "%s"' % cmd, env=env, cwd=self.vagrant_dir, timeout=timeout,
                       raise_error=raise_error, dry_run=self.dry_run, log_file_path=log_file_path,
                       quiet=quiet, check_times=self.check_times,
                       attempts=attempts, sleep_time_after_attempt=sleep_time_after_attempt)

    def prepare_system(self):
        """Prepare Vagrant system for building Kea."""
        if self.features:
            self.features_arg = '--with ' + ' '.join(self.features)
        else:
            self.features_arg = ''

        nofeatures = set(DEFAULT_FEATURES) - self.features
        if nofeatures:
            self.nofeatures_arg = '--without ' + ' '.join(nofeatures)
        else:
            self.nofeatures_arg = ''

        # install python3 on some systems
        if self.system == 'centos':
            if self.revision == '7':
                self.execute("sudo yum remove -y python-devel")
                self.execute("sudo yum install -y python36 rpm-build python3-virtualenv", attempts=3)
            else:
                self.execute("sudo dnf install -y python36 rpm-build python3-virtualenv", attempts=3)
        elif self.system == 'freebsd':
            if self.revision.startswith('13'):
                self.execute("sudo pkg install -y python3", attempts=3)

        # select proper python version for running Hammer inside Vagrant system
        if self.system == 'freebsd':
            if self.revision.startswith(('11', '12')):
                self.python = 'python3.6'
            else:
                self.python = 'python3'
        else:
            self.python = 'python3'

        # to get python in RHEL 8 beta it is required first register machine in RHEL account
        if self.system == 'rhel' and self.revision == '8':
            cmd = "sudo subscription-manager repos --list-enabled | grep rhel-8-for-x86_64-baseos-beta-rpms"
            exitcode = self.execute(cmd, raise_error=False)
            if exitcode != 0:
                env = os.environ.copy()
                with open(os.path.expanduser('~/rhel-creds.txt')) as f:
                    env['RHEL_USER'] = f.readline().strip()
                    env['RHEL_PASSWD'] = f.readline().strip()
                self.execute('sudo subscription-manager register --user $RHEL_USER --password "$RHEL_PASSWD"', env=env)
                self.execute("sudo subscription-manager refresh")
                self.execute("sudo subscription-manager attach --pool 8a85f99a67cdc3e70167e45c85f47429")
                self.execute("sudo subscription-manager repos --enable rhel-8-for-x86_64-baseos-beta-rpms")
                self.execute("sudo dnf install -y python36")

        # RPM-based distributions install libraries in /usr/local/lib64, but they
        # tend to not look there at runtime without explicit mention in ld.so.conf.d.
        if self.system in ['centos', 'fedora', 'rhel']:
            self.execute('sudo echo /usr/local/lib64 > /etc/ld.so.conf.d/kea.conf')
            # ldconfig only in case the change above was not there before system startup
            self.execute('sudo ldconfig')

        # upload Hammer to Vagrant system
        hmr_py_path = os.path.join(self.repo_dir, 'hammer.py')
        self.upload(hmr_py_path)

        log_file_path = os.path.join(self.vagrant_dir, 'prepare.log')
        log.info('Prepare log file stored to %s', log_file_path)

        t0 = time.time()

        # run prepare-system inside Vagrant system
        cmd = "{python} hammer.py prepare-system -p local {features} {nofeatures} {check_times} {ccache}"
        cmd = cmd.format(python=self.python,
                         features=self.features_arg,
                         nofeatures=self.nofeatures_arg,
                         check_times='-i' if self.check_times else '',
                         ccache='--ccache-dir /ccache' if self.ccache_enabled else '')
        self.execute(cmd, timeout=40 * 60, log_file_path=log_file_path, quiet=self.quiet)

        t1 = time.time()
        dt = int(t1 - t0)

        log.info('')
        log.info(">>> Preparing %s, %s, %s completed in %s:%s", self.provider, self.system, self.revision,
                 dt // 60, dt % 60)
        log.info('')

    def prepare_for_boxing(self):
        if self.system in ['debian', 'ubuntu', 'fedora', 'centos', 'rhel']:
            # setup a script that on first boot will set machine-id
            cmd = 'bash -c \'cat <<EOF | sudo tee /usr/lib/systemd/system/systemd-firstboot.service\n'
            cmd += '[Unit]\n'
            cmd += 'Description=Generate New Machine ID\n'
            cmd += 'Documentation=man:systemd-firstboot(1)\n'
            cmd += 'DefaultDependencies=no\n'
            cmd += 'Conflicts=shutdown.target\n'
            cmd += 'After=systemd-remount-fs.service\n'
            cmd += 'Before=systemd-sysusers.service sysinit.target shutdown.target\n'
            cmd += 'ConditionPathIsReadWrite=/etc\n'
            cmd += 'ConditionFirstBoot=yes\n'
            cmd += '[Service]\n'
            cmd += 'Type=oneshot\n'
            cmd += 'RemainAfterExit=yes\n'
            cmd += 'ExecStart=/usr/bin/systemd-firstboot --setup-machine-id\n'
            cmd += '[Install]\n'
            cmd += 'WantedBy=sysinit.target\n'
            cmd += "EOF\n\'"
            self.execute(cmd)
            self.execute('sudo systemctl enable systemd-firstboot.service')

        elif self.system == 'freebsd':
            self.execute('sudo pkg clean -a -y')
            self.execute('sudo rm -rf /usr/lib/debug')


def _install_gtest_sources():
    """Install gtest sources."""
    # download gtest sources only if it is not present as native package
    gtest_version = '1.10.0'
    gtest_path = f'/usr/src/googletest-release-{gtest_version}/googletest'
    if os.path.exists(gtest_path):
            log.info(f'gtest is already installed in {gtest_path}.')
            return

    execute('mkdir -p ~/.hammer-tmp')
    cmd = 'wget --no-verbose -O ~/.hammer-tmp/gtest.tar.gz '
    cmd += f'https://github.com/google/googletest/archive/release-{gtest_version}.tar.gz'
    execute(cmd)
    execute('sudo mkdir -p /usr/src')
    execute('sudo tar -C /usr/src -zxf ~/.hammer-tmp/gtest.tar.gz')
    execute(f'sudo ln -sf /usr/src/googletest-release-{gtest_version} /usr/src/googletest')
    os.unlink('~/.hammer-tmp/gtest.tar.gz')
    execute('rm -rf ~/.hammer-tmp')


def _install_libyang_from_sources(ignore_errors = False):
    """Install libyang from sources."""
    for prefix in ['/usr', '/usr/local']:
        libyang_so = f'{prefix}/lib/libyang.so'
        libyang_header = f'{prefix}/include/libyang/version.h'
        if (os.path.exists(libyang_so) and os.path.exists(libyang_header) and
            execute(f"grep -F '#define LY_VERSION_MAJOR 2' '{libyang_header}'", raise_error=False) == 0):
            log.info(f'libyang is already installed at {libyang_so}.')
            return

    version='v2.1.4'

    execute('rm -rf ~/.hammer-tmp')
    execute('mkdir -p ~/.hammer-tmp')
    try:
        execute('git clone https://github.com/CESNET/libyang.git ~/.hammer-tmp/libyang')
        execute(f'git checkout {version}', cwd='~/.hammer-tmp/libyang')
        execute('mkdir ~/.hammer-tmp/libyang/build')
        execute('cmake  ..', cwd='~/.hammer-tmp/libyang/build')
        execute('make -j $(nproc || gnproc || echo 1)', cwd='~/.hammer-tmp/libyang/build')
        execute('sudo make install', cwd='~/.hammer-tmp/libyang/build')
        system, revision = get_system_revision()
        if system != 'alpine':
            execute('sudo ldconfig')
    except Exception as e:
        log.exception(str(e))
        if not ignore_errors:
            raise e
    finally:
        execute('rm -rf ~/.hammer-tmp')


def _install_sysrepo_from_sources(ignore_errors = False):
    """Install sysrepo from sources."""
    for prefix in ['/usr', '/usr/local']:
        sysrepo_so = f'{prefix}/lib/libsysrepo.so'
        sysrepo_header = f'{prefix}/include/sysrepo/version.h'
        if (os.path.exists(sysrepo_so) and os.path.exists(sysrepo_header) and
            execute(f"grep -F '#define SR_VERSION_MAJOR 7' '{sysrepo_header}'", raise_error=False) == 0):
            log.info(f'sysrepo is already installed at {sysrepo_so}.')
            return

    version='v2.2.12'

    # Create repository for YANG modules and change ownership to current user.
    execute('sudo mkdir -p /etc/sysrepo')
    execute('sudo chown -R "${USER}:$(id -gn)" /etc/sysrepo')

    execute('rm -rf ~/.hammer-tmp')
    execute('mkdir -p ~/.hammer-tmp')
    try:
        execute('git clone https://github.com/sysrepo/sysrepo.git ~/.hammer-tmp/sysrepo')
        execute(f'git checkout {version}', cwd='~/.hammer-tmp/sysrepo')
        execute('mkdir ~/.hammer-tmp/sysrepo/build')
        execute('cmake -DREPO_PATH=/etc/sysrepo ..', cwd='~/.hammer-tmp/sysrepo/build')
        execute('make -j $(nproc || gnproc || echo 1)', cwd='~/.hammer-tmp/sysrepo/build')
        execute('sudo make install', cwd='~/.hammer-tmp/sysrepo/build')
        system, revision = get_system_revision()
        if system != 'alpine':
            execute('sudo ldconfig')
    except Exception as e:
        log.exception(str(e))
        if not ignore_errors:
            raise e
    finally:
        execute('rm -rf ~/.hammer-tmp')


def _install_libyang_cpp_from_sources(ignore_errors = False):
    """Install libyang-cpp from sources."""
    for prefix in ['/usr', '/usr/local']:
        libyang_cpp_so = f'{prefix}/lib/libyang-cpp.so'
        libyang_cpp_pc = f'{prefix}/lib/pkgconfig/libyang-cpp.pc'
        if (os.path.exists(libyang_cpp_so) and os.path.exists(libyang_cpp_pc) and
            execute(f"grep -F 'Version: 1.1.0' '{libyang_cpp_pc}'", raise_error=False) == 0):
            log.info(f'libyang-cpp is already installed at {libyang_cpp_so}.')
            return

    version='ae7d649ea75da081725c119dd553b2ef3121a6f8'

    execute('rm -rf ~/.hammer-tmp')
    execute('mkdir -p ~/.hammer-tmp')
    try:
        execute('git clone https://github.com/CESNET/libyang-cpp.git ~/.hammer-tmp/libyang-cpp')
        execute(f'git checkout {version}', cwd='~/.hammer-tmp/libyang-cpp')
        execute('mkdir ~/.hammer-tmp/libyang-cpp/build')
        execute('cmake -DBUILD_TESTING=OFF .. ', cwd='~/.hammer-tmp/libyang-cpp/build')
        execute('make -j $(nproc || gnproc || echo 1)', cwd='~/.hammer-tmp/libyang-cpp/build')
        execute('sudo make install', cwd='~/.hammer-tmp/libyang-cpp/build')
        system, revision = get_system_revision()
        if system != 'alpine':
            execute('sudo ldconfig')
    except Exception as e:
        log.exception(str(e))
        if not ignore_errors:
            raise e
    finally:
        execute('rm -rf ~/.hammer-tmp')


def _install_sysrepo_cpp_from_sources(ignore_errors = False):
    """Install sysrepo-cpp from sources."""
    for prefix in ['/usr', '/usr/local']:
        sysrepo_cpp_so = f'{prefix}/lib/libsysrepo-cpp.so'
        sysrepo_cpp_pc = f'{prefix}/lib/pkgconfig/sysrepo-cpp.pc'
        if (os.path.exists(sysrepo_cpp_so) and os.path.exists(sysrepo_cpp_pc) and
            execute(f"grep -F 'Version: 1.1.0' '{sysrepo_cpp_pc}'", raise_error=False) == 0):
            log.info(f'sysrepo-cpp is already installed at {sysrepo_cpp_so}.')
            return

    version='02634174ffc60568301c3d9b9b7cf710cff6a586'

    execute('rm -rf ~/.hammer-tmp')
    execute('mkdir -p ~/.hammer-tmp')
    try:
        execute('git clone https://github.com/sysrepo/sysrepo-cpp.git ~/.hammer-tmp/sysrepo-cpp')
        execute(f'git checkout {version}', cwd='~/.hammer-tmp/sysrepo-cpp')
        execute('mkdir ~/.hammer-tmp/sysrepo-cpp/build')
        execute('cmake -DBUILD_TESTING=OFF .. ', cwd='~/.hammer-tmp/sysrepo-cpp/build')
        execute('make -j $(nproc || gnproc || echo 1)', cwd='~/.hammer-tmp/sysrepo-cpp/build')
        execute('sudo make install', cwd='~/.hammer-tmp/sysrepo-cpp/build')
        system, revision = get_system_revision()
        if system != 'alpine':
            execute('sudo ldconfig')
    except Exception as e:
        log.exception(str(e))
        if not ignore_errors:
            raise e
    finally:
        execute('rm -rf ~/.hammer-tmp')


def _install_netconf_libraries_from_sources(ignore_errors = False):
    _install_libyang_from_sources(ignore_errors)
    _install_sysrepo_from_sources(ignore_errors)
    _install_libyang_cpp_from_sources(ignore_errors)
    _install_sysrepo_cpp_from_sources(ignore_errors)


def _get_local_timezone():
    _, output = execute('''
      # timedatectl
      if command -v timedatectl > /dev/null 2>&1; then
        timedatectl | grep 'Time zone' | cut -d ':' -f 2 | cut -d '(' -f 1 | xargs
        exit ${?}
      fi

      # brute force: for Alpine, FreeBSD
      for i in $(find /usr/share/zoneinfo | cut -d '/' -f 5- | grep -E '^[A-Z][a-z]+/[A-Z][a-z]+.*$' | sort -ruV); do
        unset TZ
        if test "$(date)" = "$(TZ="${i}" date)"; then
          printf '%s\n' "${i}"
          break
        fi
      done
    ''', capture=True, quiet=True)
    return output.rstrip()


def _configure_mysql(system, revision, features):
    """Configure MySQL database."""

    # Find MySQL's configuration directory which differs on various systems.
    conf_d = None
    for i in ['/etc/mysql/conf.d', '/etc/my.cnf.d']:
        if os.path.isdir(i):
            conf_d = i
            break
    if conf_d is None:
        # No configuration directory found. This happens on some systems like
        # Alpine. Consider /etc/my.cnf.d as default.
        conf_d = '/etc/my.cnf.d'
        execute('sudo mkdir -p {}'.format(conf_d))

    # Some systems like Alpine only listen on the unix socket and have to have
    # the bind-address configured manually.
    return_code = execute("sudo grep -Er '^bind-address' {}".format(conf_d), raise_error=False)
    if return_code != 0:
        execute("printf '[mysqld]\nbind-address = 127.0.0.1\n' > ./bind-address.cnf")
        bind_address_cnf = os.path.join(conf_d, 'bind-address.cnf')
        execute('sudo cp ./bind-address.cnf {}'.format(bind_address_cnf))
        execute('sudo chown mysql:mysql {}'.format(bind_address_cnf))
        execute('sudo rm -f ./bind-address.cnf')

    # If requested, configure TLS.
    cert_dir = '/etc/mysql/ssl'
    kea_cnf = os.path.join(conf_d, 'kea.cnf')
    # But start fresh first. Not enabling TLS in hammer leaves TLS support removed.
    execute('sudo rm -rf {} {}'.format(cert_dir, kea_cnf))
    if 'tls' in features:
        if not os.path.isdir(cert_dir):
            execute('sudo mkdir -p {}'.format(cert_dir))
        for file in [
            './src/lib/asiolink/testutils/ca/kea-ca.crt',
            './src/lib/asiolink/testutils/ca/kea-client.crt',
            './src/lib/asiolink/testutils/ca/kea-client.key',
            './src/lib/asiolink/testutils/ca/kea-server.crt',
            './src/lib/asiolink/testutils/ca/kea-server.key',
        ]:
            if not os.path.exists(file):
                print('ERROR: File {} is needed to prepare TLS.'.format(file), file=sys.stderr)
                sys.exit(1)
            basename = os.path.basename(file)
            execute('sudo cp {} {}'.format(file, os.path.join(cert_dir, basename)))
        with open('kea.cnf', 'w', encoding='utf-8') as f:
            f.write('''\
[mysqld]
ssl_ca = {cert_dir}/kea-ca.crt
ssl_cert = {cert_dir}/kea-server.crt
ssl_key = {cert_dir}/kea-server.key

[client-mariadb]
ssl_ca = {cert_dir}/kea-ca.crt
ssl_cert = {cert_dir}/kea-client.crt
ssl_key = {cert_dir}/kea-client.key
'''.format(cert_dir=cert_dir))
        execute('sudo mv ./kea.cnf {}'.format(kea_cnf))
        # For all added files and directories, change owner to mysql.
        execute('sudo chown -R mysql:mysql {} {}'.format(cert_dir, kea_cnf))

    if system in ['debian', 'fedora', 'centos', 'rhel']:
        execute('sudo systemctl enable mariadb.service')
        execute('sudo systemctl restart mariadb.service')

    elif system == 'ubuntu':
        execute('sudo systemctl enable mysql.service')
        execute('sudo systemctl restart mysql.service')

    elif system == 'freebsd':
        cmd = "echo 'SET PASSWORD = \"\";' "
        cmd += "| sudo mysql -u root --password=\"$(sudo cat /root/.mysql_secret | grep -v '^#')\" --connect-expired-password"
        execute(cmd, raise_error=False)

    elif system == 'alpine':
        execute('sudo sed -i "/^skip-networking$/d" /etc/my.cnf.d/mariadb-server.cnf')
        execute('sudo rc-update add mariadb')
        execute('sudo /etc/init.d/mariadb setup', raise_error=False)
        execute('sudo /etc/init.d/mariadb restart')

    cmd = "echo 'DROP DATABASE IF EXISTS keatest;' | sudo mysql -u root"
    execute(cmd)
    cmd = "echo 'DROP USER 'keatest'@'localhost';' | sudo mysql -u root"
    execute(cmd, raise_error=False)
    cmd = "echo 'DROP USER 'keatest_readonly'@'localhost';' | sudo mysql -u root"
    execute(cmd, raise_error=False)
    cmd = "echo 'DROP USER 'keatest_secure'@'localhost';' | sudo mysql -u root"
    execute(cmd, raise_error=False)
    cmd = "bash -c \"cat <<EOF | sudo mysql -u root\n"
    cmd += "CREATE DATABASE keatest;\n"
    cmd += "CREATE USER 'keatest'@'localhost' IDENTIFIED BY 'keatest';\n"
    cmd += "CREATE USER 'keatest_readonly'@'localhost' IDENTIFIED BY 'keatest';\n"
    if 'tls' in features:
        cmd += "CREATE USER 'keatest_secure'@'localhost' IDENTIFIED BY 'keatest';\n"
    cmd += "GRANT ALL ON keatest.* TO 'keatest'@'localhost';\n"
    cmd += "GRANT SELECT ON keatest.* TO 'keatest_readonly'@'localhost';\n"
    cmd += "EOF\n\""
    execute(cmd)
    if 'tls' in features:
        # ALTER USER is the best place to put the REQUIRE but, if it is not
        # supported, then downgrade to GRANT.
        exit_code = execute('''sudo mysql -u root -e "ALTER USER 'keatest_secure'@'localhost' REQUIRE X509;"''', raise_error=False)
        if exit_code == 0:
            # If ALTER succeeds, then we still have to GRANT without REQUIRE.
            execute('''sudo mysql -u root -e "GRANT ALL ON keatest.* TO 'keatest_secure'@'localhost';"''')
        else:
            execute('''sudo mysql -u root -e "GRANT ALL ON keatest.* TO 'keatest_secure'@'localhost' REQUIRE X509;"''')
    execute('sudo mysql -u root -e "SET @@global.log_bin_trust_function_creators = 1;"')

    if 'forge' in features:
        cmd = "echo 'DROP DATABASE IF EXISTS keadb;' | sudo mysql -u root"
        execute(cmd)
        cmd = "echo 'DROP USER 'keauser'@'localhost';' | sudo mysql -u root"
        execute(cmd, raise_error=False)
        cmd = "bash -c \"cat <<EOF | sudo mysql -u root\n"
        cmd += "CREATE DATABASE keadb;\n"
        cmd += "CREATE USER 'keauser'@'localhost' IDENTIFIED BY 'keapass';\n"
        cmd += "GRANT ALL ON keadb.* TO 'keauser'@'localhost';\n"
        cmd += "EOF\n\""
        execute(cmd)

    if system == 'debian' and revision == '9':
        log.info('FIX FOR ISSUE kea#389: {} {}'.format(system, revision))
        cmd = "bash -c \"cat <<EOF | sudo mysql -u root\n"
        cmd += "use keatest;\n"
        cmd += "set global innodb_large_prefix=on;\n"
        cmd += "set global innodb_file_format=Barracuda;\n"
        cmd += "set global innodb_file_per_table=true;\n"
        cmd += "set global innodb_default_row_format=dynamic;\n"
        cmd += "EOF\n\""
        execute(cmd)


def _enable_postgresql(system, revision):
    if system == 'alpine':
        execute('sudo rc-update add postgresql')
    elif system == 'freebsd':
        execute('sudo sysrc postgresql_enable="yes"')
    else:
        # Disable all PostgreSQL services first to avoid conflicts.
        # raise_error=False for when there are no matches
        _, output = execute("systemctl list-unit-files | grep postgres | grep -Fv '@.service' | cut -d ' ' -f 1",
                            capture=True, raise_error=False)
        for service in output.split():
            execute(f'sudo systemctl disable {service}')

        execute('sudo systemctl enable postgresql.service')


def _restart_postgresql(system, revision):
    if system == 'freebsd':
        # redirecting output from start script to /dev/null otherwise the postgresql rc.d script will hang
        # calling restart instead of start allow hammer.py to pass even if postgresql is already installed
        execute('sudo service postgresql restart > /dev/null')
    elif system == 'alpine':
        execute('sudo /etc/init.d/postgresql restart')
    else:
        # Stop all PostgreSQL services first to avoid conflicts.
        # raise_error=False for when there are no matches
        _, output = execute("systemctl list-unit-files | grep postgres | grep -Fv '@.service' | cut -d ' ' -f 1",
                            capture=True, raise_error=False)
        for service in output.split():
            execute(f'sudo systemctl stop {service}')

        exit_code = execute('sudo systemctl restart postgresql.service', raise_error=False)
        if exit_code != 0:
            log.error('Command "sudo systemctl restart postgresql.service" failed. Here is the journal:')
            _, output = execute('sudo journalctl -xu postgresql.service', capture=True)
            log.error(output)
            log.error('And here are logs:')
            _, output = execute("sudo -u postgres psql -A -t -c 'SELECT pg_current_logfile()'", capture=True)
            logfile = os.path.basename(output.strip())
            _, output = execute(f'sudo find /var -type f -name "{logfile}" -exec cat {{}} \;', capture=True, raise_error=False)
            log.error(output)
            sys.exit(exit_code)


# Change authentication type for given connection type. Usual inputs for
# connection type are 'host' or 'local'. Only affects entries with database
# and user both set to 'all'. This is to not affect authentication of
# `postgres` user which should have a separate entry.
def _change_postgresql_auth_method(connection_type, auth_method, hba_file):
    execute("sudo sed -i.bak 's/^{}\(.*\)all\(.*\)all\(.*\) [a-z0-9]*$/{}\\1all\\2all\\3 {}/g' '{}'".format(
        connection_type, connection_type, auth_method, hba_file), cwd='/tmp')


def _configure_pgsql(system, features, revision):
    """ Configure PostgreSQL DB """

    # execute() calls will set cwd='/tmp' when switching user to postgres to
    # avoid the error:
    #   could not change as postgres user directory to "/home/jenkins": Permission denied

    if system in ['fedora', 'centos', 'rhel']:
        # https://fedoraproject.org/wiki/PostgreSQL
        exitcode = execute('sudo ls /var/lib/pgsql/data/postgresql.conf', raise_error=False)
        if exitcode != 0:
            if system == 'centos':
                execute('sudo postgresql-setup initdb')
            else:
                execute('sudo postgresql-setup --initdb --unit postgresql')
    elif system == 'freebsd':
        # Stop any hypothetical existing postgres service.
        execute('sudo service postgresql stop || true')

        # Get the path to the data directory e.g. /var/db/postgres/data11 for
        # FreeBSD 12 and /var/db/postgres/data13 for FreeBSD 13.
        _, output = execute('ls -1d /var/db/postgres/data*', capture=True)
        var_db_postgres_data = output.rstrip()

        # Create postgres internals.
        execute('sudo test ! -d {} && sudo /usr/local/etc/rc.d/postgresql oneinitdb || true'.format(var_db_postgres_data))

        # if the file '/var/db/postgres/data*/postmaster.opts' does not exist the 'restart' of postgresql will fail with error:
        #    pg_ctl: could not read file "/var/db/postgres/data*/postmaster.opts"
        # the initial start of the postgresql will create the 'postmaster.opts' file
        execute('sudo test ! -f {}/postmaster.opts && sudo service postgresql onestart || true'.format(var_db_postgres_data))

    _enable_postgresql(system, revision)
    _restart_postgresql(system, revision)

    # Change auth-method to 'md5' on all connections.
    cmd = "sudo -u postgres psql -t -c 'SHOW hba_file' | xargs"
    _, output = execute(cmd, capture=True, cwd='/tmp')
    hba_file = output.rstrip()
    _change_postgresql_auth_method('host', 'md5', hba_file)
    _change_postgresql_auth_method('local', 'md5', hba_file)

    # Make sure hba file has a postgres superuser entry. It needs to be placed
    # before any other local auth method for higher priority. Let's simulate
    # that by putting it just after the auth header.
    if 0 != execute("sudo cat {} | grep -E '^local.*all.*postgres'".format(hba_file), raise_error=False):
        auth_header='# TYPE  DATABASE        USER            ADDRESS                 METHOD'
        postgres_auth_line='local   all             postgres                                ident'
        # The "\\" followed by newline is for BSD support.
        execute("""sudo sed -i.bak '/{}/a\\
{}
' '{}'""".format(auth_header, postgres_auth_line, hba_file))

    _restart_postgresql(system, revision)

    cmd = """bash -c \"cat <<EOF | sudo -u postgres psql postgres
        DROP DATABASE IF EXISTS keatest;
        DROP USER IF EXISTS keatest;
        DROP USER IF EXISTS keatest_readonly;
        CREATE USER keatest WITH PASSWORD 'keatest';
        CREATE USER keatest_readonly WITH PASSWORD 'keatest';
        CREATE DATABASE keatest;
        GRANT ALL PRIVILEGES ON DATABASE keatest TO keatest;
        ALTER DATABASE keatest SET TIMEZONE='{}';\n""".format(_get_local_timezone())
    cmd += 'EOF\n"'
    execute(cmd, cwd='/tmp')

    cmd = """bash -c \"cat <<EOF | sudo -u postgres psql -U keatest keatest
        ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT SELECT ON TABLES TO keatest_readonly;\n"""
    cmd += 'EOF\n"'
    env = os.environ.copy()
    env['PGPASSWORD'] = 'keatest'
    execute(cmd, cwd='/tmp', env=env)

    if 'forge' in features:
        cmd = "bash -c \"cat <<EOF | sudo -u postgres psql postgres\n"
        cmd += "DROP DATABASE IF EXISTS keadb;\n"
        cmd += "DROP USER IF EXISTS keauser;\n"
        cmd += "CREATE USER keauser WITH PASSWORD 'keapass';\n"
        cmd += "CREATE DATABASE keadb;\n"
        cmd += "GRANT ALL PRIVILEGES ON DATABASE keauser TO keadb;\n"
        cmd += "EOF\n\""
        execute(cmd, cwd='/tmp')

    log.info('postgresql just configured')


def _apt_update(system, revision, env=None, check_times=False, attempts=1, sleep_time_after_attempt=None,
                capture=False):
    cmd = 'sudo apt update'
    if system == 'debian' and int(revision) >= 10:
        cmd += ' --allow-releaseinfo-change'
    return execute(cmd, env=env, check_times=check_times, attempts=attempts,
                   sleep_time_after_attempt=sleep_time_after_attempt, capture=capture)


def _install_freeradius_client(system, revision, features, env, check_times):
    """Install FreeRADIUS-client with necessary patches from Francis Dupont."""
    # check if it is already installed
    if (os.path.exists('/usr/local/lib/libfreeradius-client.so') and
        os.path.exists('/usr/local/include/freeradius-client.h')):
        log.info('freeradius-client is already installed.')
        return

    # Install freeradius-client dependencies.
    if system in ['centos', 'rhel', 'fedora']:
        install_pkgs('nettle-devel', env=env, check_times=check_times)
    elif system in ['alpine', 'debian', 'ubuntu']:
        install_pkgs('nettle-dev', env=env, check_times=check_times)
    elif system in ['arch', 'freebsd']:
        install_pkgs('nettle', env=env, check_times=check_times)
    else:
        raise NotImplementedError('no implementation for %s' % system)

    # checkout sources, build them and install
    execute('rm -rf freeradius-client')
    execute('git clone https://github.com/fxdupont/freeradius-client.git', env=env, check_times=check_times)
    execute('git checkout iscdev', cwd='freeradius-client', env=env, check_times=check_times)
    execute('./configure --with-nettle', cwd='freeradius-client', env=env, check_times=check_times)
    execute('make', cwd='freeradius-client', env=env, check_times=check_times)
    execute('sudo make install', cwd='freeradius-client', env=env, check_times=check_times)
    execute('rm -rf freeradius-client')
    if system != 'alpine':
        execute('sudo ldconfig', env=env)
    log.info('freeradius-client successfully installed.')


def _get_package_version(package: str):
    """
    Returns the version available in the package manager's repository for the requested package.
    :param package: the name of the package whose version is retrieved
    """
    system, revision = get_system_revision()
    if system == 'alpine':
        cmd = "apk search --exact {0} | sed 's/{0}-//g'"
    elif system in ['debian', 'ubuntu']:
        cmd = "apt-cache show {} | grep -F 'Version:' | cut -d ' ' -f 2"
    elif system in ['centos', 'fedora', 'rhel']:
        cmd = "dnf list {} | tr -s ' ' | cut -d ' ' -f 2 | tail -n 1"
    elif system == 'freebsd':
        cmd = "pkg search {0} | grep -Eo '^{0}-[0-9_,\.]+' | sed 's/{0}-//g'"
    elif system == 'arch':
        cmd = "pacman -Qi {} | tr -s ' ' | grep -F 'Version :' | cut -d ' ' -f 3"
    else:
        raise NotImplementedError(f'_get_package_version not implemented for {system}')

    cmd = cmd.format(package)
    _, output = execute(cmd, capture=True)
    return output.strip()


def require_minimum_package_version(package: str, minimum: str):
    """
    Returns true if a given package is available to be installed with
    the given minimum version or greater.
    :param package: the name of the package that is checked
    :param minimum: the semantic version that the package is checked against
    """
    version = _get_package_version(package)
    if version < minimum:
        message = f"ERROR: {package} has version {version}, but must be >= {minimum}"
        log.error(message)
        raise Exception(message)


def prepare_system_local(features, check_times, ignore_errors_for):
    """Prepare local system for Kea development based on requested features."""
    env = os.environ.copy()
    env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

    # Actions decided before installing packages, but run afterwards
    deferred_functions = []

    system, revision = get_system_revision()
    log.info('Preparing deps for %s %s', system, revision)

    # Check if package versions cannot be met.
    if 'netconf' in features and 'netconf' not in ignore_errors_for:
        require_minimum_package_version('cmake', '3.19')

    # prepare fedora
    if system == 'fedora':
        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel',
                    'log4cplus-devel', 'boost-devel', 'libpcap-devel']

        if 'native-pkg' in features:
            packages.extend(['rpm-build', 'python3-devel'])

        if 'docs' in features:
            packages.extend(['python3-sphinx', 'texlive', 'texlive-collection-latexextra'])
            if int(revision) >= 31:
                packages.extend(['python3-sphinx_rtd_theme'])

        if 'mysql' in features:
            execute('sudo dnf remove -y community-mysql-devel || true')
            packages.extend(['mariadb', 'mariadb-server', 'mariadb-connector-c-devel'])

        if 'pgsql' in features:
            if int(revision) >= 30:
                packages.extend(['postgresql-server-devel'])
            if int(revision) <= 34:
                packages.extend(['postgresql-devel'])
            packages.extend(['postgresql-server'])

        if 'radius' in features:
            packages.extend(['freeradius', 'git'])

        if 'gssapi' in features:
            packages.extend(['krb5-devel'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        if 'netconf' in features:
            packages.extend(['cmake', 'pcre2-devel'])

        install_pkgs(packages, timeout=300, env=env, check_times=check_times)

        if 'unittest' in features:
            _install_gtest_sources()

        execute('sudo dnf clean packages', env=env, check_times=check_times)

    # prepare centos
    elif system == 'centos':
        install_pkgs('epel-release', env=env, check_times=check_times)

        packages = ['autoconf', 'automake', 'boost-devel', 'gcc-c++',
                    'libtool', 'log4cplus-devel', 'make',
                    'openssl-devel']

        if revision in ['7', '8']:
            # Install newer version of Boost in case users want to opt-in with:
            # --with-boost-include=/usr/include/boost169 --with-boost-lib-dir=/usr/lib64/boost169
            packages.append('boost169-devel')

        if 'native-pkg' in features:
            packages.extend(['bison', 'flex', 'python3-devel', 'rpm-build'])

        if 'mysql' in features:
            packages.extend(['mariadb', 'mariadb-server'])
            if int(revision) < 9:
                packages.extend(['mariadb-devel'])
            else:
                packages.extend(['mariadb-connector-c-devel'])

        if 'pgsql' in features:
            packages.extend(['postgresql', 'postgresql-server'])
            if revision == '9':
                packages.append('postgresql13-devel')
                def link_pg_config():
                    if not os.path.exists('/usr/bin/pg_config'):
                        execute('sudo ln -s /usr/pgsql-13/bin/pg_config /usr/bin/pg_config')
                deferred_functions.append(link_pg_config)
            else:
                packages.append('postgresql-devel')

        if 'radius' in features:
            packages.extend(['freeradius', 'git'])

        if 'gssapi' in features:
            packages.extend(['krb5-devel'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        if 'netconf' in features:
            packages.extend(['cmake', 'pcre2-devel'])

        if 'unittest' in features:
            packages.append('wget')
            deferred_functions.append(_install_gtest_sources)

        install_pkgs(packages, env=env, check_times=check_times)

        if 'docs' in features:
            execute('python3 -m venv ~/venv',
                    env=env, timeout=60, check_times=check_times)
            execute('~/venv/bin/pip install sphinx sphinx-rtd-theme',
                    env=env, timeout=120, check_times=check_times)

    # prepare rhel
    elif system == 'rhel':
        packages = ['autoconf', 'automake', 'boost-devel', 'gcc-c++',
                    'libtool', 'log4cplus-devel', 'make',
                    'openssl-devel']

        if revision in ['7', '8']:
            # Install newer version of Boost in case users want to opt-in with:
            # --with-boost-include=/usr/include/boost169 --with-boost-lib-dir=/usr/lib64/boost169
            packages.append('boost169-devel')

        if 'native-pkg' in features:
            packages.extend(['bison', 'flex', 'python3-devel', 'rpm-build'])

        if 'mysql' in features:
            packages.extend(['mariadb', 'mariadb-server'])
            if int(revision) < 9:
                packages.extend(['mariadb-devel'])
            else:
                packages.extend(['mariadb-connector-c-devel'])

        if 'pgsql' in features:
            packages.extend(['postgresql', 'postgresql-server'])
            if revision == '9':
                packages.append('postgresql13-devel')
                def link_pg_config():
                    if not os.path.exists('/usr/bin/pg_config'):
                        execute('sudo ln -s /usr/pgsql-13/bin/pg_config /usr/bin/pg_config')
                deferred_functions.append(link_pg_config)
            else:
                packages.append('postgresql-devel')

        if 'radius' in features:
            packages.extend(['freeradius', 'git'])

        if 'gssapi' in features:
            packages.extend(['krb5-devel'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        if 'netconf' in features:
            packages.extend(['cmake', 'pcre2-devel'])

        if 'unittest' in features:
            packages.append('wget')
            deferred_functions.append(_install_gtest_sources)

        install_pkgs(packages, env=env, timeout=120, check_times=check_times)

        if 'docs' in features:
            execute('python3 -m venv ~/venv',
                    env=env, timeout=60, check_times=check_times)
            execute('~/venv/bin/pip install sphinx sphinx-rtd-theme',
                    env=env, timeout=120, check_times=check_times)

    # prepare ubuntu
    elif system == 'ubuntu':
        _apt_update(system, revision, env=env, check_times=check_times, attempts=3, sleep_time_after_attempt=10)

        packages = ['gcc', 'g++', 'make', 'autoconf', 'automake', 'libtool', 'libssl-dev', 'liblog4cplus-dev',
                    'libboost-system-dev', 'gnupg', 'libpcap-dev', 'python3-venv']

        if 'unittest' in features:
            if revision.startswith('16.'):
                _install_gtest_sources()
            else:
                packages.append('googletest')

        if 'docs' in features:
            packages.extend(['python3-sphinx', 'python3-sphinx-rtd-theme', 'texlive', 'texlive-latex-extra'])
            if revision == '22.04':
                packages.extend(['tex-gyre'])

        if 'native-pkg' in features:
            packages.extend(['build-essential', 'fakeroot', 'devscripts'])
            packages.extend(['bison', 'debhelper', 'flex', 'libboost-dev', 'python3-dev'])
            if 20.04 <= float(revision):
                packages.extend(['dh-python'])

        if 'mysql' in features:
            if revision == '16.04':
                packages.extend(['mysql-client', 'libmysqlclient-dev', 'mysql-server'])
            else:
                packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev', 'mysql-server'])

        if 'pgsql' in features:
            if revision == '16.04':
                packages.extend(['postgresql-client', 'libpq-dev', 'postgresql', 'postgresql-server-dev-all'])
            else:
                packages.extend(['postgresql-client', 'libpq-dev', 'postgresql-all'])

        if 'radius' in features:
            packages.extend(['freeradius', 'git'])

        if 'gssapi' in features:
            packages.extend(['libkrb5-dev'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        if 'netconf' in features:
            packages.extend(['cmake', 'libpcre2-dev'])

        install_pkgs(packages, env=env, timeout=240, check_times=check_times)

    # prepare debian
    elif system == 'debian':
        _apt_update(system, revision, env=env, check_times=check_times, attempts=3, sleep_time_after_attempt=10)

        packages = ['gcc', 'g++', 'make', 'autoconf', 'automake', 'libtool', 'libssl-dev',
                    'liblog4cplus-dev', 'libboost-system-dev', 'gnupg']

        if 'unittest' in features:
            if revision == '8':
                # libgtest-dev does not work and googletest is not available
                _install_gtest_sources()
            else:
                packages.append('googletest')

        if 'netconf' in features:
            packages.extend(['cmake', 'libpcre2-dev'])

        if 'docs' in features:
            if revision == '8':
                packages.extend(['virtualenv'])
            else:
                packages.extend(['python3-sphinx', 'python3-sphinx-rtd-theme', 'texlive', 'texlive-latex-extra'])
                if revision == '9':
                    packages.extend(['texlive-generic-extra'])

        if 'native-pkg' in features:
            packages.extend(['build-essential', 'fakeroot', 'devscripts'])
            packages.extend(['bison', 'debhelper', 'flex', 'libboost-dev', 'python3-dev'])
            if int(revision) >= 11:
                packages.extend(['dh-python'])

        if 'mysql' in features:
            if revision == '8':
                packages.extend(['mysql-client', 'libmysqlclient-dev'])
            else:
                packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev'])
            if revision in ['8', '9']:
                packages.append('mysql-server')
            else:
                packages.append('mariadb-server')

        if 'pgsql' in features:
            packages.extend(['postgresql-client', 'libpq-dev'])
            if revision == '8':
                packages.extend(['postgresql', 'postgresql-client'])
            else:
                packages.append('postgresql-all')

        if 'radius' in features:
            packages.extend(['freeradius', 'git'])

        if 'gssapi' in features:
            packages.extend(['libkrb5-dev'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        install_pkgs(packages, env=env, timeout=240, check_times=check_times)

        if 'docs' in features:
            if revision == '8':
                execute('python3 -m venv ~/venv',
                        env=env, timeout=60, check_times=check_times)
                execute('~/venv/bin/pip install sphinx sphinx-rtd-theme',
                        env=env, timeout=120, check_times=check_times)

    # prepare freebsd
    elif system == 'freebsd':
        # Packages are already upgraded by default when installing a package,
        # so to avoid mismatching dependency versions, inaccurate dynamic
        # version fetching and other troubles, clean up local cache and
        # install an arbitrary package to fetch remote first.
        execute('sudo pkg clean -a -y')
        execute('sudo pkg install -y pkg')

        packages = ['autoconf', 'automake', 'libtool', 'openssl', 'log4cplus', 'boost-libs', 'wget']

        if 'docs' in features:
            # Get the python version from the remote repositories.
            pyv = _get_package_version('python')
            pyv = pyv.split('_')[0].replace('.', '')
            log.info(">>>>> Detected Sphinx packages version: py%s-sphinx", pyv)
            packages.extend([f'py{pyv}-sphinx', f'py{pyv}-sphinx_rtd_theme'])

        if 'mysql' in features:
            if revision.startswith(('11', '12')):
                packages.extend(['mysql57-server', 'mysql57-client'])
            else:
                packages.extend(['mysql80-server', 'mysql80-client'])

        if 'pgsql' in features:
            if revision.startswith(('11', '12')):
                packages.extend(['postgresql11-server', 'postgresql11-client'])
            else:
                packages.extend(['postgresql13-server', 'postgresql13-client'])

        if 'radius' in features:
            packages.extend(['freeradius3', 'git'])

        if 'gssapi' in features:
            packages.extend(['krb5', 'krb5-devel'])
            # FreeBSD comes with a Heimdal krb5-config by default. Make sure
            # it's deleted so that Kea uses the MIT packages added just above.
            execute('sudo rm -f /usr/bin/krb5-config')

        if 'ccache' in features:
            packages.extend(['ccache'])

        if 'netconf' in features:
            packages.extend(['cmake', 'pcre2'])

        install_pkgs(packages, env=env, timeout=6 * 60, check_times=check_times)

        if 'unittest' in features:
            _install_gtest_sources()

        if 'mysql' in features:
            execute('sudo sysrc mysql_enable="yes"', env=env, check_times=check_times)
            execute('sudo service mysql-server start', env=env, check_times=check_times,
                    raise_error=False)

        execute('sudo pkg clean -a -y')
        execute('sudo rm -rf /usr/lib/debug')

    # prepare alpine
    elif system == 'alpine':

        packages = ['gcc', 'g++', 'make', 'autoconf', 'automake', 'libtool', 'openssl-dev',
                    'boost-libs', 'boost-dev', 'procps', 'tar', 'log4cplus', 'log4cplus-dev',
                    'gzip']

        if 'docs' in features:
            if revision == '3.10':
                packages.extend(['py-sphinx', 'py-sphinx_rtd_theme'])
            elif revision == '3.11':
                packages.extend(['py3-sphinx'])
            elif float(revision) < 3.16:
                packages.extend(['py3-sphinx', 'py3-sphinx_rtd_theme'])
            else:
                packages.extend(['py3-pip'])

        if 'unittest' in features:
            _install_gtest_sources()

        if 'netconf' in features:
            packages.extend(['cmake', 'pcre2-dev'])

        if 'mysql' in features:
            packages.extend(['mariadb-dev', 'mariadb', 'mariadb-client'])

        if 'pgsql' in features:
            packages.extend(['postgresql-dev', 'postgresql'])
            packages.extend(['bison', 'flex', 'boost-dev', 'python3-dev'])

        if 'gssapi' in features:
            packages.extend(['krb5-dev'])

        if 'native-pkg' in features:
            packages.extend(['alpine-sdk'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        install_pkgs(packages, env=env, timeout=6 * 60, check_times=check_times)

        # work around outdated sphinx packages on alpine 3.16
        if 'docs' in features:
            if float(revision) >= 3.16:
                execute('sudo pip3 install -U sphinx sphinx_rtd_theme')

        # check for existence of 'vagrant' user and 'abuild' group before adding him to the group
        try:
            pwd.getpwnam('vagrant')
            grp.getgrnam('abuild')
        except KeyError:
            log.info("Can't add 'vagrant' user to 'abuild' group. Vagrant or abuild does not exist.")
        else:
            execute('sudo adduser vagrant abuild')

        try:
            current_user = getpass.getuser()
            pwd.getpwnam(current_user)
            grp.getgrnam('abuild')
        except KeyError:
            log.info("Can't add %s user to 'abuild' group. %s or abuild does not exist.", current_user, current_user)
        else:
            execute('sudo adduser %s abuild' % current_user)

    else:
        raise NotImplementedError('no implementation for %s' % system)

    if 'netconf' in features:
        _install_netconf_libraries_from_sources('netconf' in ignore_errors_for)

    # Packages required by these functions have been installed. Now call them.
    for f in deferred_functions:
        f()

    if 'mysql' in features:
        _configure_mysql(system, revision, features)

    if 'pgsql' in features:
        _configure_pgsql(system, features, revision)

    if 'radius' in features:
        _install_freeradius_client(system, revision, features, env, check_times)

    #execute('sudo rm -rf /usr/share/doc')

    log.info('Preparing deps completed successfully.')


def prepare_system_in_vagrant(provider, system, revision, features, dry_run, check_times,
                              clean_start, ccache_dir=None):
    """Prepare specified system in Vagrant according to specified features."""
    ve = VagrantEnv(provider, system, revision, features, 'kea', dry_run, check_times=check_times,
                    ccache_dir=ccache_dir)
    if clean_start:
        ve.destroy()
        ve.init_files()
    ve.bring_up_latest_box()
    ve.prepare_system()


def _calculate_build_timeout(features):
    """Return maximum allowed time for build (in seconds)."""
    timeout = 60
    if 'mysql' in features:
        timeout += 60
    timeout *= 60
    return timeout


def _prepare_ccache_if_needed(system, ccache_dir, env):
    if ccache_dir is not None:
        if system in ['debian', 'ubuntu']:
            ccache_bin_path = '/usr/lib/ccache/'
        elif system in ['centos', 'rhel', 'fedora']:
            ccache_bin_path = '/usr/lib64/ccache'
            env['CC'] = 'ccache gcc'
            env['CXX'] = 'ccache g++'
        elif system == 'alpine':
            # TODO: it doesn't work yet, new abuild is needed and add 'USE_CCACHE=1' to /etc/abuild.conf
            ccache_bin_path = '/usr/lib/ccache/bin'
        env['PATH'] = ccache_bin_path + ':' + env['PATH']
        env['CCACHE_DIR'] = ccache_dir
    return env


def _build_binaries_and_run_ut(system, revision, features, tarball_path, env, check_times, jobs, dry_run,
                               ccache_dir):
    if tarball_path:
        # unpack tarball with sources
        execute('sudo rm -rf kea-src')
        os.mkdir('kea-src')
        execute('tar -zxf %s' % tarball_path, cwd='kea-src', check_times=check_times)
        src_path = glob.glob('kea-src/*')[0]
    else:
        src_path = '.'

    execute('autoreconf -f -i', cwd=src_path, env=env, dry_run=dry_run)

    # prepare switches for ./configure
    cmd = './configure'
    log.info('OS: %s Revision: %s', system, revision)
    if 'mysql' in features:
        cmd += ' --with-mysql'
    if 'pgsql' in features:
        cmd += ' --with-pgsql'
    if 'unittest' in features:
        # prepare gtest switch - use downloaded gtest sources only if it is not present as native package
        if system in ['centos', 'fedora', 'rhel', 'freebsd', 'alpine']:
            cmd += ' --with-gtest-source=/usr/src/googletest-release-1.10.0/googletest/'
        elif system == 'debian' and revision == '8':
            cmd += ' --with-gtest-source=/usr/src/googletest-release-1.10.0/googletest/'
        elif system == 'debian':
            cmd += ' --with-gtest-source=/usr/src/googletest/googletest'
        elif system == 'ubuntu':
            if revision.startswith('16.'):
                cmd += ' --with-gtest-source=/usr/src/googletest-release-1.10.0/googletest/'
            else:
                cmd += ' --with-gtest-source=/usr/src/googletest/googletest'
        elif system == 'arch':
            pass
        else:
            raise NotImplementedError('no implementation for %s' % system)
    if 'docs' in features and not system == 'rhel':
        cmd += ' --enable-generate-docs'
        if system == 'debian' and revision == '8' or system == 'centos' and revision in ['7', '8']:
            cmd += ' --with-sphinx=~/venv/bin/sphinx-build'
    if 'radius' in features:
        cmd += ' --with-freeradius=/usr/local'
    if 'gssapi' in features:
        cmd += ' --with-gssapi'
    if 'shell' in features:
        cmd += ' --enable-shell'
    if 'perfdhcp' in features:
        cmd += ' --enable-perfdhcp'
    if 'netconf' in features:
        cmd += ' --with-libyang --with-sysrepo --with-libyang-cpp --with-sysrepo-cpp'

    # do ./configure
    execute(cmd, cwd=src_path, env=env, timeout=120, check_times=check_times, dry_run=dry_run)

    if 'netconf' in features:
        # ./configure has created reinstall.sh from reinstall.sh.in. Call it.
        execute('./src/share/yang/modules/utils/reinstall.sh', cwd=src_path, env=env)

    # estimate number of processes (jobs) to use in compilation if jobs are not provided
    if jobs == 0:
        cpus = multiprocessing.cpu_count() - 1
        if system == 'centos':
            cpus = cpus // 2
        if cpus == 0:
            cpus = 1
    else:
        cpus = jobs

    # enable ccache if requested
    env = _prepare_ccache_if_needed(system, ccache_dir, env)

    # do build
    timeout = _calculate_build_timeout(features)
    if 'distcheck' in features:
        cmd = 'make distcheck'
    else:
        cmd = 'make -j%s' % cpus
    execute(cmd, cwd=src_path, env=env, timeout=timeout, check_times=check_times, dry_run=dry_run)

    if 'unittest' in features:
        results_dir = os.path.abspath(os.path.join(src_path, 'tests_result'))
        execute('rm -rf %s' % results_dir, dry_run=dry_run)
        if not os.path.exists(results_dir):
            os.mkdir(results_dir)
        env['GTEST_OUTPUT'] = 'xml:%s/' % results_dir
        env['KEA_SOCKET_TEST_DIR'] = '/tmp/'
        # run unit tests
        execute('make check -k',
                cwd=src_path, env=env, timeout=90 * 60, raise_error=False,
                check_times=check_times, dry_run=dry_run)

        # parse unit tests results
        results = {}
        grand_total = 0
        grand_not_passed = 0
        aggregated_root = ET.Element('testsuites')
        for fn in os.listdir(results_dir):
            if not fn.endswith('.xml'):
                continue
            fp = os.path.join(results_dir, fn)
            tree = ET.parse(fp)
            root = tree.getroot()

            # prepare stats for json
            total = int(root.get('tests'))
            failures = int(root.get('failures'))
            disabled = int(root.get('disabled'))
            errors = int(root.get('errors'))
            results[fn] = dict(total=total, failures=failures, disabled=disabled, errors=errors)
            grand_total += total
            grand_not_passed += failures + errors

            # append test suites to aggregated root
            for ts in root.findall('testsuite'):
                if not ts:
                    continue
                aggregated_root.append(ts)

        # prepare and stats in json
        grand_passed = grand_total - grand_not_passed
        results['grand_passed'] = grand_total - grand_not_passed
        results['grand_total'] = grand_total

        result = '%s/%s passed' % (grand_passed, grand_total)
        if grand_not_passed > 0 or grand_total == 0:
            result = red(result)
        else:
            result = green(result)
        log.info('Unit test results: %s', result)

        with open('unit-test-results.json', 'w') as f:
            f.write(json.dumps(results))

        # store aggregated results in XML
        if os.path.exists('aggregated_tests.xml'):
            os.unlink('aggregated_tests.xml')
        aggr = ET.ElementTree(aggregated_root)
        aggr.write('aggregated_tests.xml')

    if 'install' in features:
        execute('sudo make install', timeout=2 * 60,
                cwd=src_path, env=env, check_times=check_times, dry_run=dry_run)
        if system != 'alpine':
            execute('sudo ldconfig', dry_run=dry_run, env=env)

        if 'forge' in features:
            if 'mysql' in features:
                execute('kea-admin db-init mysql -u keauser -p keapass -n keadb', dry_run=dry_run)
            if 'pgsql' in features:
                execute('kea-admin db-init pgsql -u keauser -p keapass -n keadb', dry_run=dry_run)


def _check_installed_rpm_or_debs(services_list):
    for svc in services_list:
        execute('sudo systemctl stop %s' % svc)
        now = datetime.datetime.now()
        timestamp = now.strftime('%Y-%m-%d%H:%M:%S')
        execute('sudo systemctl start %s' % svc)
        time.sleep(3)
        cmd = "sudo journalctl --since %s -u %s | grep '_STARTED Kea'" % (timestamp, svc)
        execute(cmd, attempts=10, sleep_time_after_attempt=1)


def _build_rpm(system, revision, features, tarball_path, env, check_times, dry_run,
               pkg_version, pkg_isc_version, repo_url):
    # install our freeradius-client but now from rpm
    cmd = 'bash -c "cat <<EOF | sudo tee /etc/yum.repos.d/isc.repo\n'
    cmd += '[nexus]\n'
    cmd += 'name=ISC Repo\n'
    cmd += 'baseurl=%s\n' % repo_url
    cmd += 'enabled=1\n'
    cmd += 'gpgcheck=0\n'
    cmd += "EOF\n\""
    execute(cmd)
    if system == 'fedora' and revision == '28':
        frc_version = 'isc20190916210635.fc28'
    elif system == 'fedora' and revision == '29':
        frc_version = 'isc20190916210635.fc29'
    elif system == 'fedora' and revision == '30':
        frc_version = 'isc20200318150024.fc30'
    elif system == 'fedora' and revision == '31':
        frc_version = 'isc20200318122047.fc31'
    elif system == 'fedora' and revision == '32':
        frc_version = 'isc20200511114306.fc32'
    elif system == 'fedora' and revision == '33':
        frc_version = 'isc20210415094816.fc33'
    elif system == 'fedora' and revision == '34':
        frc_version = 'isc20210528132302.fc34'
    elif system == 'fedora' and revision == '35':
        frc_version = 'isc20220516091026.fc35'
    elif system == 'fedora' and revision == '36':
        frc_version = 'isc20220516091651.fc36'
    elif system == 'centos' and revision == '7':
        frc_version = 'isc20200318122047.el7'
    elif system in ['centos', 'rhel'] and revision == '8':
        frc_version = 'isc20200318134606.el8'
    elif system == 'rhel' and revision == '9':
        frc_version = 'isc20220613134625.el9'
    else:
        raise NotImplementedError('missing freeradius-client version for %s-%s' % (system, revision))

    install_pkgs([
        f'freeradius-client-1.1.7-{frc_version}',
        f'freeradius-client-devel-1.1.7-{frc_version}',
    ], env=env, check_times=check_times)

    _append_to_file('freeradius-pkgs.txt', f'freeradius-client-1.1.7-{frc_version}.x86_64.rpm')
    _append_to_file('freeradius-pkgs.txt', f'freeradius-client-devel-1.1.7-{frc_version}.x86_64.rpm')

    # unpack kea sources tarball
    execute('sudo rm -rf kea-src', dry_run=dry_run)
    os.mkdir('kea-src')
    execute('tar -zxf %s' % tarball_path, cwd='kea-src', check_times=check_times, dry_run=dry_run)
    src_path = glob.glob('kea-src/*')[0]

    # prepare folder for all pkgs
    if os.path.exists('pkgs'):
        execute('rm -rf pkgs')
    os.mkdir('pkgs')

    # prepare RPM environment
    rpm_root_path = os.path.expanduser('~/rpm-root')
    # ensure rm -rf will not wipe out a whole disk
    if rpm_root_path.endswith("rpm-root"):
        execute('rm -rf %s' % rpm_root_path)
    execute('mkdir -p %s/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}' % rpm_root_path)

    # get rpm.spec from tarball
    rpm_dir = os.path.join(src_path, 'rpm')
    for f in os.listdir(rpm_dir):
        if f == 'kea.spec':
            continue
        execute('cp %s %s/SOURCES' % (os.path.join(rpm_dir, f), rpm_root_path), check_times=check_times, dry_run=dry_run)
    execute('cp %s %s/SPECS' % (os.path.join(rpm_dir, 'kea.spec'), rpm_root_path), check_times=check_times, dry_run=dry_run)
    execute('cp %s %s/SOURCES' % (tarball_path, rpm_root_path), check_times=check_times, dry_run=dry_run)

    execute('sed -i -e s/{FREERADIUS_CLIENT_VERSION}/%s/g %s/SPECS/kea.spec' % (frc_version, rpm_root_path), check_times=check_times, dry_run=dry_run)

    # do rpm build
    cmd = "rpmbuild --define 'kea_version %s' --define 'isc_version %s' -ba %s/SPECS/kea.spec"
    cmd += " -D'_topdir %s'"
    cmd += " --undefine=_debugsource_packages"  # disable creating debugsource package
    cmd = cmd % (pkg_version, pkg_isc_version, rpm_root_path, rpm_root_path)
    execute(cmd, env=env, timeout=60 * 40, check_times=check_times, dry_run=dry_run)

    if 'install' in features:
        # install packages
        execute('rpm -qa | grep isc-kea | xargs sudo rpm -e', check_times=check_times, dry_run=dry_run, raise_error=False)
        execute('sudo rpm -i %s/RPMS/x86_64/*rpm' % rpm_root_path, check_times=check_times, dry_run=dry_run)

        # check if kea services can be started
        services_list = ['kea-dhcp4.service', 'kea-dhcp6.service', 'kea-dhcp-ddns.service', 'kea-ctrl-agent.service']
        _check_installed_rpm_or_debs(services_list)

    execute('mv %s/RPMS/x86_64/*rpm pkgs' % rpm_root_path, check_times=check_times, dry_run=dry_run)


def _build_deb(system, revision, features, tarball_path, env, check_times, dry_run,
               pkg_version, pkg_isc_version, repository_url, repo_url):
    if system == 'debian' and revision == '9':
        # debian 9 does not support apt-installing over https, so install proper transport
        install_pkgs('apt-transport-https', env=env, check_times=check_times)

    # See if a .deb package had been previously uploaded.
    _, output = execute("curl -o /dev/null -s -w '%{{http_code}}' {}/dists/kea/Release 2>/dev/null".format(repo_url), capture=True)
    http_code = output.rstrip()
    release_file_exists = (http_code == '200')
    if release_file_exists:
        log.info(f'{repo_url}/dists/kea/Release exists.')
    else:
        repo_name = 'kea-%s-%s-%s' % (pkg_version.rsplit('.', 1)[0], system, revision)
        log.error(f'{repo_url}/dists/kea/Release does not exist. '
             f'This is usually caused by no package existing in {repo_name}. '
             'You can solve this by uploading the freeradius-client packages '
             'which are also needed further to build packages. '
             'Continuing, but the build will likely fail.')

    # install our freeradius-client but now from deb
    execute("echo 'deb %s kea main' | sudo tee /etc/apt/sources.list.d/isc.list" % repo_url)
    key_url = "%s/repository/repo-keys/repo-key.gpg" % repository_url
    execute('wget -qO- %s | sudo apt-key add -' % key_url,
            env=env, check_times=check_times)

    # try apt update for up to 10 times if there is an error
    for _ in range(10):
        _, out = _apt_update(system, revision, capture=True)
        if 'Bad header data' not in out:
            break
        time.sleep(4)
    if system == 'debian' or (system == 'ubuntu' and revision == '18.04'):
        frc_version = 'isc20200318122047'
    elif system == 'ubuntu' and revision == '19.04':
        frc_version = 'isc20200319090824'
    elif system == 'ubuntu' and revision == '20.04':
        frc_version = 'isc20200511114306'
    elif system == 'ubuntu' and revision == '20.10':
        frc_version = 'isc20210419151920'
    elif system == 'ubuntu' and revision == '21.04':
        frc_version = 'isc20210528123038'
    elif system == 'ubuntu' and revision == '22.04':
        frc_version = 'isc20220608134906'
    else:
        raise NotImplementedError('missing freeradius-client version for %s-%s' % (system, revision))

    install_pkgs([
        f'libfreeradius-client=1.1.7-{frc_version}',
        f'libfreeradius-client-dev=1.1.7-{frc_version}',
    ], env=env, check_times=check_times)

    _append_to_file('freeradius-pkgs.txt', f'libfreeradius-client_1.1.7-{frc_version}_amd64.deb')
    _append_to_file('freeradius-pkgs.txt', f'libfreeradius-client-dev_1.1.7-{frc_version}_amd64.deb')

    # unpack tarball
    execute('sudo rm -rf kea-src', check_times=check_times, dry_run=dry_run)
    os.mkdir('kea-src')
    execute('tar -zxf %s' % tarball_path, cwd='kea-src', check_times=check_times, dry_run=dry_run)
    src_path = glob.glob('kea-src/*')[0]

    # update version, etc
    execute('sed -i -e s/{VERSION}/%s/ changelog' % pkg_version, cwd='kea-src/kea-%s/debian' % pkg_version, check_times=check_times, dry_run=dry_run)
    execute('sed -i -e s/{ISC_VERSION}/%s/ changelog' % pkg_isc_version, cwd='kea-src/kea-%s/debian' % pkg_version, check_times=check_times, dry_run=dry_run)
    execute('sed -i -e s/{FREERADIUS_CLIENT_VERSION}/%s/g control' % frc_version, cwd='kea-src/kea-%s/debian' % pkg_version, check_times=check_times, dry_run=dry_run)

    services_list = ['isc-kea-dhcp4-server.service', 'isc-kea-dhcp6-server.service', 'isc-kea-dhcp-ddns-server.service', 'isc-kea-ctrl-agent.service']

    # debian 9 does not support some fields in systemd unit files so they need to be commented out
    if system == 'debian' and revision == '9':
        for f in services_list:
            for k in ['RuntimeDirectory', 'RuntimeDirectoryPreserve', 'LogsDirectory', 'LogsDirectoryMode', 'StateDirectory', 'ConfigurationDirectory']:
                cmd = "sed -i -E 's/^(%s=.*)/#\\1/' %s" % (k, f)
                execute(cmd, cwd='kea-src/kea-%s/debian' % pkg_version, check_times=check_times, dry_run=dry_run)

    # do deb build
    env['LIBRARY_PATH'] = '/usr/lib/x86_64-linux-gnu'
    env['LD_LIBRARY_PATH'] = '/usr/lib/x86_64-linux-gnu'
    cmd = 'debuild --preserve-envvar=LD_LIBRARY_PATH --preserve-envvar=LIBRARY_PATH --preserve-envvar=CCACHE_DIR --prepend-path=/usr/lib/ccache -i -us -uc -b'
    execute(cmd, env=env, cwd=src_path, timeout=60 * 40, check_times=check_times, dry_run=dry_run)

    if 'install' in features:
        # install packages
        execute('sudo dpkg -i kea-src/*deb', check_times=check_times, dry_run=dry_run)
        # check if kea services can be started
        _check_installed_rpm_or_debs(services_list)


def _build_alpine_apk(system, revision, features, tarball_path, env, check_times, dry_run,
                      pkg_version, pkg_isc_version, repo_url):
    # unpack tarball
    execute('sudo rm -rf kea-src packages', check_times=check_times, dry_run=dry_run)
    os.makedirs('kea-src/src')
    execute('tar -zxf %s' % tarball_path, check_times=check_times, dry_run=dry_run)
    if revision == '3.10':
        sys_suffix = '-3.10'
    else:
        sys_suffix = ''
    execute('mv kea-%s/alpine%s/* kea-src' % (pkg_version, sys_suffix), check_times=check_times, dry_run=dry_run)
    execute('rm -rf kea-%s' % pkg_version, check_times=check_times, dry_run=dry_run)
    tardir = os.path.dirname(tarball_path)
    if not tardir:
        tardir = '.'
    cmd = 'cd %s; export kea_chks=`sha512sum kea-%s.tar.gz`; cd -; sed -i -e "s/KEA_CHECKSUM/${kea_chks}/" kea-src/APKBUILD' % (tardir, pkg_version)
    execute(cmd, check_times=check_times, dry_run=dry_run)
    cmd = 'sed -i -e s/KEA_VERSION/%s/ kea-src/APKBUILD' % pkg_version
    execute(cmd, check_times=check_times, dry_run=dry_run)
    cmd = 'sed -i -e s/KEA_ISC_VERSION/%s/ kea-src/APKBUILD' % pkg_isc_version[3:]
    execute(cmd, check_times=check_times, dry_run=dry_run)
    log.info('Moving %s to kea-src folder', tarball_path)
    execute('mv %s kea-src' % tarball_path, check_times=check_times, dry_run=dry_run)
    execute('abuild-keygen -n -a -i', check_times=check_times, dry_run=dry_run)
    execute('abuild -v -r', cwd='kea-src', check_times=check_times, dry_run=dry_run)

    # copy packages from alpine specific dir with produced pkgs to common place
    alpine_repo_dir = os.path.basename(os.getcwd())
    src_dir = '~/packages/%s/x86_64' % alpine_repo_dir
    execute('cp %s/*.apk kea-pkg' % src_dir, check_times=check_times, dry_run=dry_run)

    if 'install' in features:
        # install packages
        execute('sudo apk add *.apk', cwd='kea-pkg', check_times=check_times, dry_run=dry_run)

        # check if kea services can be started
        for svc in ['kea-dhcp4', 'kea-dhcp6', 'kea-ctrl-agent', 'kea-dhcp-ddns']:
            execute('sudo rc-service %s start' % svc)
            time.sleep(3)
            if svc == 'kea-dhcp-ddns':
                svc = 'kea-ddns'
            log_path = '/var/log/kea/%s.log' % svc
            if revision == '3.10':
                log_path = '/var/log/%s.log' % svc
            cmd = "sudo cat %s | grep '_STARTED Kea'" % log_path
            execute(cmd, attempts=10, sleep_time_after_attempt=1)


def _build_native_pkg(system, revision, features, tarball_path, env, check_times, dry_run, ccache_dir,
                      pkg_version, pkg_isc_version, repository_url, pkgs_dir):
    """Build native (RPM or DEB or Alpine APK) packages."""

    # enable ccache if requested
    env = _prepare_ccache_if_needed(system, ccache_dir, env)

    repo_url = _get_full_repo_url(repository_url, system, revision, pkg_version)
    assert repo_url is not None

    if system in ['fedora', 'centos', 'rhel']:
        _build_rpm(system, revision, features, tarball_path, env, check_times, dry_run,
                   pkg_version, pkg_isc_version, repo_url)

    elif system in ['ubuntu', 'debian']:
        _build_deb(system, revision, features, tarball_path, env, check_times, dry_run,
                   pkg_version, pkg_isc_version, repository_url, repo_url)

    elif system in ['alpine']:
        _build_alpine_apk(system, revision, features, tarball_path, env, check_times, dry_run,
                          pkg_version, pkg_isc_version, repo_url)

    elif system in ['arch']:
        pass

    else:
        raise NotImplementedError('no implementation for %s' % system)

    if system in ['ubuntu', 'debian']:
        execute('mv kea-src/isc-kea_* %s' % pkgs_dir)
        execute('mv kea-src/*deb %s' % pkgs_dir)
    elif system in ['fedora', 'centos', 'rhel']:
        execute('mv pkgs/* %s' % pkgs_dir)
    elif system in ['alpine']:
        #execute('mv kea-src/* %s' % pkgs_dir)
        execute('mv kea-pkg/* %s' % pkgs_dir)
    elif system in ['arch']:
        pass
    else:
        raise NotImplementedError('no implementation for %s' % system)


def build_local(features, tarball_path, check_times, jobs, dry_run, ccache_dir, pkg_version, pkg_isc_version,
                repository_url, pkgs_dir):
    """Prepare local system for Kea development based on requested features.

    If tarball_path is provided then instead of Kea sources from current directory
    use provided tarball.
    """
    env = os.environ.copy()
    env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

    system, revision = get_system_revision()
    log.info('Building for %s %s', system, revision)

    execute('sudo df -h', dry_run=dry_run)

    # NOTE: the old code expects having tarball in tarball_path
    if not tarball_path:
        name_ver = 'kea-%s' % pkg_version
        cmd = 'tar --transform "flags=r;s|^|%s/|" --exclude hammer ' % name_ver
        cmd += ' --exclude "*~" --exclude .git --exclude .libs '
        cmd += ' --exclude .deps --exclude \'*.o\'  --exclude \'*.lo\' '
        cmd += ' -zcf /tmp/%s.tar.gz .' % name_ver
        execute(cmd)
        tarball_path = '/tmp/%s.tar.gz' % name_ver

    if 'native-pkg' in features:
        _build_native_pkg(system, revision, features, tarball_path, env, check_times, dry_run, ccache_dir,
                          pkg_version, pkg_isc_version, repository_url, pkgs_dir)
    else:
        _build_binaries_and_run_ut(system, revision, features, tarball_path, env, check_times, jobs,
                                   dry_run, ccache_dir)

    execute('sudo df -h', dry_run=dry_run)


def build_in_vagrant(provider, system, revision, features, leave_system, tarball_path,
                     dry_run, quiet, clean_start, check_times, jobs, ccache_dir,
                     pkg_version, pkg_isc_version, upload, repository_url):
    """Build Kea via Vagrant in specified system with specified features."""
    log.info('')
    log.info(">>> Building %s, %s, %s", provider, system, revision)
    log.info('')

    t0 = time.time()

    ve = None
    error = None
    total = 0
    passed = 0
    try:
        ve = VagrantEnv(provider, system, revision, features, 'kea', dry_run, quiet, check_times,
                        ccache_dir)
        if clean_start:
            ve.destroy()
            ve.init_files()
        ve.bring_up_latest_box()
        ve.prepare_system()
        total, passed = ve.run_build_and_test(tarball_path, jobs, pkg_version, pkg_isc_version, upload, repository_url)
        msg = ' - ' + green('all ok')
    except KeyboardInterrupt as e:
        error = e
        msg = ' - keyboard interrupt'
    except ExecutionError as e:
        error = e
        msg = ' - ' + red(str(e))
    except Exception as e:  # pylint: disable=broad-except
        log.exception('Building erred')
        error = e
        msg = ' - ' + red(str(e))
    finally:
        if not leave_system and ve:
            ve.destroy()

    t1 = time.time()
    dt = int(t1 - t0)

    log.info('')
    log.info(">>> Building %s, %s, %s completed in %s:%s%s", provider, system, revision, dt // 60, dt % 60, msg)
    log.info('')

    return dt, error, total, passed


def package_box(provider, system, revision, features, dry_run, check_times, reuse, skip_upload):
    """Prepare Vagrant box of specified system."""
    ve = VagrantEnv(provider, system, revision, features, 'bare', dry_run, check_times=check_times)
    if not reuse:
        ve.destroy()
        ve.init_files()
    ve.bring_up_latest_box()
    ve.prepare_system()
    ve.prepare_for_boxing()
    box_path = ve.package()
    if not skip_upload:
        ve.upload_to_cloud(box_path)


def ssh(provider, system, revision):
    """Invoke Vagrant ssh for given system."""
    ve = VagrantEnv(provider, system, revision, [], 'kea', False)
    ve.up()
    ve.ssh()


def _install_vagrant(ver=RECOMMENDED_VAGRANT_VERSION, upgrade=False):
    system, _ = get_system_revision()
    if system in ['fedora', 'centos', 'rhel']:
        if upgrade:
            execute('sudo yum remove -y vagrant')
        execute('mkdir -p ~/.hammer-tmp')
        rpm = 'vagrant_%s_x86_64.rpm' % ver
        cmd = 'wget --no-verbose -O ~/.hammer-tmp/%s ' % rpm
        cmd += 'https://releases.hashicorp.com/vagrant/%s/%s' % (ver, rpm)
        execute(cmd)
        execute('sudo rpm -i ~/.hammer-tmp/%s' % rpm)
        os.unlink('~/.hammer-tmp/%s' % rpm)
        execute('rm -rf ~/.hammer-tmp')
    elif system in ['debian', 'ubuntu']:
        if upgrade:
            execute('sudo apt-get purge -y vagrant')
        execute('mkdir -p ~/.hammer-tmp')
        deb = 'vagrant_%s_x86_64.deb' % ver
        cmd = 'wget --no-verbose -O ~/.hammer-tmp/%s ' % deb
        cmd += 'https://releases.hashicorp.com/vagrant/%s/%s' % (ver, deb)
        execute(cmd)
        execute('sudo dpkg -i ~/.hammer-tmp/%s' % deb)
        os.unlink('~/.hammer-tmp/%s' % deb)
        execute('rm -rf ~/.hammer-tmp')
    elif system in ['arch']:
        pass
    else:
        # TODO: check for packages here: https://www.vagrantup.com/downloads.html
        raise NotImplementedError('no implementation for %s' % system)


def ensure_hammer_deps():
    """Install Hammer dependencies onto current, host system."""
    exitcode, out = execute('vagrant version', raise_error=False, capture=True)
    if exitcode != 0:
        _install_vagrant()
    else:
        m = re.search('Installed Version: ([\d\.]+)', out, re.I)
        ver = m.group(1)
        vagrant = [int(v) for v in ver.split('.')]
        recommended_vagrant = [int(v) for v in RECOMMENDED_VAGRANT_VERSION.split('.')]
        if vagrant < recommended_vagrant:
            m = re.search('Latest Version: ([\d\.]+)', out, re.I)
            if m is None:
                # Vagrant was unable to check for the latest version of Vagrant.
                # Attempt to upgrade to the recommended version to fix it.
                _install_vagrant(upgrade=True)
                return
            ver = m.group(1)
            _install_vagrant(ver, upgrade=True)


    exitcode = execute('vagrant plugin list | grep vagrant-lxc', raise_error=False)
    if exitcode != 0:
        execute('vagrant plugin install vagrant-lxc')

    # Install lxc-create.
    system, _ = get_system_revision()
    if system == 'debian':
        execute('sudo apt-get -y install lxc')
    if system in ['ubuntu']:
        execute('sudo apt-get -y install lxc-utils')


class CollectCommaSeparatedArgsAction(argparse.Action):
    """Helper argparse action class that can split multi-argument options by space and by comma."""

    def __call__(self, parser, namespace, values, option_string=None):
        values2 = []
        for v1 in values:
            for v2 in v1.split():
                values2.extend(v2.split(','))

        for v in values2:
            if v not in ALL_FEATURES:
                msg = "feature '%s' is not supported. List of supported features: %s."
                msg = msg % (v, ", ".join(ALL_FEATURES))
                raise argparse.ArgumentError(self, msg)

        setattr(namespace, self.dest, values2)


DEFAULT_FEATURES = ['docs', 'install', 'perfdhcp', 'unittest']
ALL_FEATURES = ['all', 'ccache', 'distcheck', 'docs', 'forge', 'gssapi',
                'install', 'mysql', 'native-pkg', 'netconf', 'perfdhcp',
                'pgsql', 'radius', 'shell', 'tls', 'unittest']


def parse_args():
    """Parse arguments."""
    # used lambda to change args order and able to substitute width
    fl = functools.partial(lambda w, t: textwrap.fill(t, w), 80)
    description = [
        "Hammer - Kea development environment management tool.\n",
        fl("At first it is required to install Hammer dependencies which is Vagrant and either "
           "VirtualBox or LXC. To make life easier Hammer can install Vagrant and required "
           "Vagrant plugins using the command:"),
        "\n  ./hammer.py ensure-hammer-deps\n",
        "Still VirtualBox and LXC need to be installed manually.",
        fl("Basic functionality provided by Hammer is preparing building environment and "
           "performing actual build and running unit tests locally, in current system. "
           "This can be achieved by running the command:"),
        "\n  ./hammer.py build -p local\n",
        fl("The scope of the process can be defined using --with (-w) and --without (-x) options. "
           "By default the build command will build Kea with documentation, install it locally "
           "and run unit tests."),
        "To exclude installation and generating docs do:",
        "\n  ./hammer.py build -p local -x install docs\n",
        fl("The whole list of available features is: %s." % ", ".join(ALL_FEATURES)),
        fl("Hammer can be told to set up a new virtual machine with specified operating system "
           "and not running the build:"),
        "\n  ./hammer.py prepare-system -p virtualbox -s freebsd -r 12.0\n",
        fl("This way we can prepare a system for our own use. To get to such system using SSH invoke:"),
        "\n  ./hammer.py ssh -p virtualbox -s freebsd -r 12.0\n",
        "To list all created system on a host invoke:",
        "\n  ./hammer.py created-systems\n",
        "And then to destroy a given system run:",
        "\n  ./hammer.py destroy -d /path/to/dir/with/Vagrantfile\n",
    ]
    description = "\n".join(description)
    main_parser = argparse.ArgumentParser(description=description,
                                          formatter_class=argparse.RawDescriptionHelpFormatter)

    main_parser.add_argument('-v', '--verbose', action='store_true', help='Enable verbose mode.')
    main_parser.add_argument('-q', '--quiet', action='store_true', help='Enable quiet mode.')

    subparsers = main_parser.add_subparsers(dest='command',
                                            title="Hammer commands",
                                            description=fl("The following commands are provided by Hammer. "
                                                           "To get more information about particular command invoke: "
                                                           "./hammer.py <command> -h."))

    parent_parser1 = argparse.ArgumentParser(add_help=False)
    parent_parser1.add_argument('-p', '--provider', default='virtualbox',
                                choices=['lxc', 'virtualbox', 'local', 'all'],
                                help="Backend build executor. If 'all' then build is executed several times "
                                "on all providers. If 'local' then build is executed on current system. "
                                "Default is 'virtualbox'.")
    parent_parser1.add_argument('-s', '--system', default='all', choices=list(SYSTEMS.keys()) + ['all'],
                                help="Build is executed on selected system. If 'all' then build is executed "
                                "several times on all systems. If provider is 'local' then this option is ignored. "
                                "Default is 'all'.")
    parent_parser1.add_argument('-r', '--revision', default='all',
                                help="Revision of selected system. If 'all' then build is executed several times "
                                "on all revisions of selected system. To list supported systems and their revisions "
                                "invoke 'supported-systems'. Default is 'all'.")

    parent_parser2 = argparse.ArgumentParser(add_help=False)
    hlp = "Enable features. Separate them by space or comma. List of available features: %s. Default is '%s'."
    hlp = hlp % (", ".join(ALL_FEATURES), ' '.join(DEFAULT_FEATURES))
    parent_parser2.add_argument('-w', '--with', metavar='FEATURE', nargs='+', default=set(),
                                action=CollectCommaSeparatedArgsAction, help=hlp)
    hlp = "Disable features. Separate them by space or comma. List of available features: %s. Default is ''."
    hlp = hlp % ", ".join(ALL_FEATURES)
    parent_parser2.add_argument('-x', '--without', metavar='FEATURE', nargs='+', default=set(),
                                action=CollectCommaSeparatedArgsAction, help=hlp)
    parent_parser2.add_argument('--with-randomly', metavar='FEATURE', nargs='+', default=set(),
                                action=CollectCommaSeparatedArgsAction, help=hlp)
    parent_parser2.add_argument('--ignore-errors-for', metavar='FEATURE', nargs='+', default=set(),
                                action=CollectCommaSeparatedArgsAction, help=hlp)
    parent_parser2.add_argument('-l', '--leave-system', action='store_true',
                                help='At the end of the command do not destroy vagrant system. Default behavior is '
                                'destroying the system.')
    parent_parser2.add_argument('-c', '--clean-start', action='store_true',
                                help='If there is pre-existing system then it is destroyed first.')
    parent_parser2.add_argument('-i', '--check-times', action='store_true',
                                help='Do not allow executing commands infinitely.')
    parent_parser2.add_argument('-n', '--dry-run', action='store_true', help='Print only what would be done.')


    parser = subparsers.add_parser('ensure-hammer-deps',
                                   help="Install Hammer dependencies on current, host system.")
    parser = subparsers.add_parser('supported-systems',
                                   help="List system supported by Hammer for doing Kea development.")
    parser = subparsers.add_parser('build', help="Prepare system and run Kea build in indicated system.",
                                   parents=[parent_parser1, parent_parser2])
    parser.add_argument('-j', '--jobs', default=0,
                        help='Number of processes used in compilation. Override make -j default value.')
    parser.add_argument('-t', '--from-tarball', metavar='TARBALL_PATH',
                        help='Instead of building sources in current folder use provided tarball '
                        'package (e.g. tar.gz).')
    parser.add_argument('--ccache-dir', default=None,
                        help='Path to CCache directory on host system.')
    parser.add_argument('--pkg-version', default='0.0.1',
                        help='Kea version.')
    parser.add_argument('--pkg-isc-version', default='isc0',
                        help='ISC build version of Kea.')
    parser.add_argument('--upload', action='store_true',
                        help='Request uploading native packages to repository indicated by --repository-url.')
    parser.add_argument('--repository-url', default=None,
                        help='Repository for 3rd party dependencies and for uploading built packages.')
    parser = subparsers.add_parser('prepare-system',
                                   help="Prepare system for doing Kea development i.e. install all required "
                                   "dependencies and pre-configure the system. build command always first calls "
                                   "prepare-system internally.",
                                   parents=[parent_parser1, parent_parser2])
    parser.add_argument('--ccache-dir', default=None,
                        help='Path to CCache directory on host system.')
    parser.add_argument('--repository-url', default=None,
                        help='Repository for 3rd party dependencies and for uploading built packages.')
    parser = subparsers.add_parser('ssh', help="SSH to indicated system.",
                                   formatter_class=argparse.RawDescriptionHelpFormatter,
                                   description="Allows getting into the system using SSH. If the system is "
                                   "not present then it will be created first but not prepared. The command "
                                   "can be run in 2 way: \n"
                                   "1) ./hammer.py ssh -p <provider> -s <system> -r <revision>\n"
                                   "2) ./hammer.py ssh -d <path-to-vagrant-dir>",
                                   parents=[parent_parser1])
    parser.add_argument('-d', '--directory', help='Path to directory with Vagrantfile.')
    parser = subparsers.add_parser('created-systems', help="List ALL systems created by Hammer.")
    parser = subparsers.add_parser('destroy', help="Destroy indicated system.",
                                   description="Destroys system indicated by a path to directory with Vagrantfile. "
                                   "To get the list of created systems run: ./hammer.py created-systems.")
    parser.add_argument('-d', '--directory', help='Path to directory with Vagrantfile.')
    parser = subparsers.add_parser('package-box',
                                   help="Prepare system from scratch and package it into Vagrant Box. Prepared box can be "
                                   "later deployed to Vagrant Cloud.",
                                   parents=[parent_parser1, parent_parser2])
    parser.add_argument('--repository-url', default=None,
                        help='Repository for 3rd party dependencies and for uploading built packages.')
    parser.add_argument('-u', '--reuse', action='store_true',
                        help='Reuse existing system image, otherwise (default case) if there is any existing then destroy it first.')
    parser.add_argument('-k', '--skip-upload', action='store_true',
                        help='Skip uploading prepared box to cloud, otherwise (default case) upload it.')


    args = main_parser.parse_args()

    return args, main_parser


def list_supported_systems():
    """List systems hammer can support (with supported providers)."""
    for system, revisions in SYSTEMS.items():
        print('%s:' % system)
        for r in revisions:
            providers = []
            for p in ['lxc', 'virtualbox']:
                k = '%s-%s-%s' % (system, r, p)
                if k in IMAGE_TEMPLATES:
                    providers.append(p)
            providers = ', '.join(providers)
            print('  - %s: %s' % (r, providers))


def list_created_systems():
    """List VMs that are created on this host by Hammer."""
    _, output = execute('vagrant global-status --prune', quiet=True, capture=True)
    systems = []
    for line in output.splitlines():
        if 'hammer' not in line:
            continue
        elems = line.split()
        state = elems[3]
        path = elems[4]
        systems.append([path, state])

    print('')
    print('%-10s %s' % ('State', 'Path'))
    print('-' * 80)
    for path, state, in sorted(systems):
        print('%-10s %s' % (state, path))
    print('-' * 80)
    print('To destroy a system run: ./hammer.py destroy -d <path>')
    print('')


def destroy_system(path):
    """Destroy Vagrant system under given path."""
    vf = os.path.join(path, 'Vagrantfile')
    if not os.path.exists(vf):
        print('Wrong directory. It does not have Vagrantfile.')
        sys.exit(1)
    execute('vagrant destroy', cwd=path, interactive=True)


def _coin_toss():
    if random.randint(0, 65535) % 2 == 0:
        return True
    return False


def _get_features(args):
    features = set(vars(args)['with'])

    # establish initial set of features
    if 'all' in features:
        # special case 'all' but some features need to be removed
        # as they are not compatible with others
        features = set(ALL_FEATURES)
        features.discard('all')
        features.discard('native-pkg')

    # if we build native packages then some features are required and some not
    if 'native-pkg' in features:
        features.add('docs')
        features.add('perfdhcp')
        features.add('shell')
        features.add('mysql')
        features.add('pgsql')
        features.add('radius')
        features.add('gssapi')
        # in case of build command of native packages, unittest should not
        # be run as they are not built
        if args.command == 'build':
            features.discard('unittest')

    nofeatures = set(args.without)
    features = features.difference(nofeatures)

    for i in args.with_randomly:
        if _coin_toss():
            features.add(i)
            log.info(f'Feature enabled through coin toss: {i}')
        else:
            features.discard(i)
            log.info(f'Feature disabled through coin toss: {i}')

    if hasattr(args, 'ccache_dir') and args.ccache_dir:
        features.add('ccache')

    return features


def _print_summary(results, features):
    """Print summary of build times and unit-test results."""
    print("")
    print("+===== Hammer Summary ====================================================+")
    print("|   provider |     system | revision |  duration |  status |   unit tests |")
    print("+------------+------------+----------+-----------+---------+--------------+")
    total_dt = 0
    for key, result in results.items():
        provider, system, revision = key
        dt, error, ut_total, ut_passed = result

        total_dt += dt
        if error is None:
            status = '     %s' % green('ok')
        elif error == 'not run':
            status = blue('not run')
        else:
            status = '  %s' % red('error')

        if 'unittest' in features:
            ut_results = '%s/%s' % (ut_passed, ut_total)
            padding = ' ' * (12 - len(ut_results))
            if ut_passed < ut_total or ut_total == 0:
                ut_results = padding + red(ut_results)
            else:
                ut_results = padding + green(ut_results)
        else:
            ut_results = ' not planned'
        txt = '| %10s | %10s | %8s | %6d:%02d | %s | %s |' % (provider, system, revision,
                                                              dt // 60, dt % 60, status, ut_results)
        print(txt)
    print("+------------+------------+----------+-----------+---------+--------------+")
    txt = "|                               Total: %6d:%02d |                        |" % (total_dt // 60,
                                                                                          total_dt % 60)
    print(txt)
    print("+=========================================================================+")


def _check_system_revision(system, revision):
    if revision == 'all':
        return
    revs = SYSTEMS[system]
    if revision not in revs:
        msg = "hammer.py error: argument -r/--revision: invalid choice: '%s' (choose from '%s')"
        msg = msg % (revision, "', '".join(revs))
        print(msg)
        sys.exit(1)


def _prepare_ccache_dir(ccache_dir, system, revision):
    if not ccache_dir:
        return None

    ccache_dir = os.path.join(ccache_dir, "%s-%s" % (system, revision))
    ccache_dir = os.path.abspath(ccache_dir)
    if not os.path.exists(ccache_dir):
        os.makedirs(ccache_dir)
    return ccache_dir


def prepare_system_cmd(args):
    """Check command args and run the prepare-system command."""
    if args.provider != 'local' and (args.system == 'all' or args.revision == 'all'):
        print('Please provide required system and its version.')
        print('Example: ./hammer.py prepare-system -s fedora -r 28.')
        print('To get list of supported systems run: ./hammer.py supported-systems.')
        sys.exit(1)

    _check_system_revision(args.system, args.revision)

    features = _get_features(args)
    log.info('Enabled features: %s', ' '.join(features))

    if args.provider == 'local':
        prepare_system_local(features, args.check_times, args.ignore_errors_for)
        return

    ccache_dir = _prepare_ccache_dir(args.ccache_dir, args.system, args.revision)

    _check_deps_presence()
    prepare_system_in_vagrant(args.provider, args.system, args.revision, features,
                              args.dry_run, args.check_times, args.clean_start,
                              ccache_dir)


def upload_to_repo(args, pkgs_dir):
    # NOTE: note the differences (if any) in system/revision vs args.system/revision
    system, revision = get_system_revision()
    repo_url = _get_full_repo_url(args.repository_url, system, revision, args.pkg_version)
    assert repo_url is not None
    upload_cmd = 'curl -v --netrc -f'
    log.info('args.system %s, system = %s', args.system, system)

    file_ext = ''
    if system in ['ubuntu', 'debian']:
        upload_cmd += ' -X POST -H "Content-Type: multipart/form-data" --data-binary "@%s" '
        file_ext = '.deb'

    elif system in ['fedora', 'centos', 'rhel']:
        upload_cmd += ' --upload-file %s '
        file_ext = '.rpm'

    elif system == 'alpine':
        upload_cmd += ' --upload-file %s '
        file_ext = ''
        repo_url = urljoin(repo_url, '%s/v%s/x86_64/' % (args.pkg_isc_version, revision))

    upload_cmd += ' ' + repo_url

    for fn in os.listdir(pkgs_dir):
        log.info("debug: fn = %s", fn)
        if file_ext and not fn.endswith(file_ext):
            log.info('File extension "%s" is not supported by upload_to_repo function', file_ext)
            continue
        fp = os.path.join(pkgs_dir, fn)
        log.info("upload cmd: %s", upload_cmd)
        log.info("fp: %s", fp)
        cmd = upload_cmd % fp

        attempts=4
        while attempts > 0:
            exitcode, output = execute(cmd, capture=True)
            if exitcode != 0 and '504 Gateway Time-out' in output:
                log.info('Trying again after 8 seconds...')
                attempts -= 1
                time.sleep(8)
            else:
                break


def build_cmd(args):
    """Check command args and run the build command."""
    features = _get_features(args)
    log.info('Enabled features: %s', ' '.join(features))
    if args.provider == 'local':
        # NOTE: working dir is /tmp/workspace/kea-dev/pkg
        pkgs_dir = "kea-pkg"
        if os.path.exists(pkgs_dir):
            execute('rm -rf %s' % pkgs_dir)
        os.makedirs(pkgs_dir)

        build_local(features, args.from_tarball, args.check_times, int(args.jobs), args.dry_run,
                    args.ccache_dir, args.pkg_version, args.pkg_isc_version, args.repository_url, pkgs_dir)
        # NOTE: upload the locally build packages and leave; the rest of the code is vagrant specific
        if args.upload:
            upload_to_repo(args,pkgs_dir)

        return

    _check_system_revision(args.system, args.revision)

    if 'native-pkg' in features and not args.repository_url:
        msg = "Enabling 'native-pkg' requires passing --repository-url."
        print(msg)
        sys.exit(1)

    _check_deps_presence()

    if args.provider == 'all':
        providers = ['lxc', 'virtualbox']
    else:
        providers = [args.provider]

    if args.system == 'all':
        systems = SYSTEMS.keys()
    else:
        systems = [args.system]

    plan = []
    results = {}
    log.info('Build plan:')
    for provider in providers:
        for system in systems:
            if args.revision == 'all':
                revisions = SYSTEMS[system]
            else:
                revisions = [args.revision]

            for revision in revisions:
                if args.revision == 'all':
                    key = '%s-%s-%s' % (system, revision, provider)
                    if key not in IMAGE_TEMPLATES:
                        continue
                plan.append((provider, system, revision))
                log.info(' - %s, %s, %s', provider, system, revision)
                results[(provider, system, revision)] = (0, 'not run')

    fail = False
    for provider, system, revision in plan:
        ccache_dir = _prepare_ccache_dir(args.ccache_dir, args.system, args.revision)
        result = build_in_vagrant(provider, system, revision, features, args.leave_system, args.from_tarball,
                                  args.dry_run, args.quiet, args.clean_start, args.check_times, int(args.jobs),
                                  ccache_dir, args.pkg_version, args.pkg_isc_version, args.upload, args.repository_url)
        results[(provider, system, revision)] = result

        error = result[1]
        if error:
            fail = True
            if isinstance(error, KeyboardInterrupt):
                break

    _print_summary(results, features)

    if fail:
        sys.exit(1)


def _check_deps_presence():
    ret = execute('vagrant -v', super_quiet=True, raise_error=False)
    if ret != 0:
        print('Missing vagrant. Please install it from https://www.vagrantup.com/')
        sys.exit(1)


def main():
    """Main function - parse args and invoke proper command."""
    args, parser = parse_args()

    # prepare logging
    if args.verbose:
        level = logging.DEBUG
        fmt = '[HAMMER]  %(asctime)-15s L%(lineno)04d %(message)s'
    else:
        level = logging.INFO
        fmt = '[HAMMER]  %(asctime)-15s %(message)s'
    logging.basicConfig(format=fmt, level=level)

    # dispatch command
    if args.command == 'supported-systems':
        list_supported_systems()

    elif args.command == 'created-systems':
        _check_deps_presence()
        list_created_systems()

    elif args.command == "package-box":
        _check_deps_presence()
        _check_system_revision(args.system, args.revision)
        features = set(['docs', 'perfdhcp', 'shell', 'mysql', 'pgsql', 'radius', 'gssapi', 'native-pkg'])

        log.info('Enabled features: %s', ' '.join(features))
        package_box(args.provider, args.system, args.revision, features, args.dry_run, args.check_times, args.reuse, args.skip_upload)

    elif args.command == "prepare-system":
        prepare_system_cmd(args)

    elif args.command == "build":
        build_cmd(args)

    elif args.command == "ssh":
        _check_system_revision(args.system, args.revision)
        if not args.system or not args.revision or args.system == 'all' or args.revision == 'all':
            print('System (-s) and revision (-r) parameters are required')
            sys.exit(1)
        _check_deps_presence()
        ssh(args.provider, args.system, args.revision)

    elif args.command == "ensure-hammer-deps":
        ensure_hammer_deps()

    elif args.command == "destroy":
        if not args.directory:
            print('Missing directory (-d) parameter')
            sys.exit(1)
        _check_deps_presence()
        destroy_system(args.directory)

    else:
        parser.print_help()


if __name__ == '__main__':
    main()
