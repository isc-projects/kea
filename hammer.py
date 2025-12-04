#!/usr/bin/env python3

# Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# pylint: disable=broad-exception-caught
# pylint: disable=logging-fstring-interpolation

"""Hammer - Kea development environment management tool."""

from __future__ import print_function

import os
import pathlib
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
import grp
import pwd
import getpass
import urllib.request
from urllib.parse import urljoin

# [B404:blacklist] Consider possible security implications associated with subprocess module.
import subprocess  # nosec B404

# Issue: [B405:blacklist] Using xml.etree.ElementTree to parse untrusted XML data is known to be vulnerable to XML
#        attacks. Replace xml.etree.ElementTree with the equivalent defusedxml package, or make sure
#        defusedxml.defuse_stdlib() is called.
import xml.etree.ElementTree as ET  # nosec B405


# SYSTEMS = {
#     'os': {
#         'version': True if supported else False,
#         ...
#     },
#     ...
# }

SYSTEMS = {
    'fedora': {
        '27': False,
        '28': False,
        '29': False,
        '30': False,
        '31': False,
        '32': False,
        '33': False,
        '34': False,
        '35': False,
        '36': False,
        '37': False,
        '38': False,
        '39': False,
        '40': False,
        '41': False,
        '42': False,
        '43': True,
    },
    'centos': {
        '7': False,
        '8': False,
        '9': False,
    },
    'rhel': {
        '8': True,
        '9': True,
        '10': True,
    },
    'rocky': {
        '9': True,
        '10': True,
    },
    'ubuntu': {
        '16.04': False,
        '18.04': False,
        '18.10': False,
        '19.04': False,
        '19.10': False,
        '20.04': False,
        '20.10': False,
        '21.04': False,
        '22.04': True,
        '24.04': True,
    },
    'debian': {
        '8': False,
        '9': False,
        '10': False,
        '11': True,
        '12': True,
        '13': True,
    },
    'freebsd': {
        '11': False,
        '12': False,
        '13': False,
        '14': False,
        '15': True,
    },
    'alpine': {
        '3.10': False,
        '3.11': False,
        '3.12': False,
        '3.13': False,
        '3.14': False,
        '3.15': False,
        '3.16': False,
        '3.17': False,
        '3.18': False,
        '3.19': False,
        '3.20': False,
        '3.21': True,
        '3.22': True,
        '3.23': True,
    },
    'arch': {},
}

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
    'fedora-37-lxc':           {'bare': 'isc/lxc-fedora-37',           'kea': 'isc/kea-fedora-37'},

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
    'debian-12-lxc':           {'bare': 'isc/lxc-debian-12',           'kea': 'isc/kea-debian-12'},

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
    'alpine-3.17-lxc':         {'bare': 'isc/lxc-alpine-3.17',         'kea': 'isc/kea-alpine-3.17'},
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

RECOMMENDED_VAGRANT_VERSION = '2.2.16'

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
    revision = 'unknown'
    if system == 'Linux':
        system, revision = None, None
        if not os.path.exists('/etc/os-release'):
            raise UnexpectedError('/etc/os-release does not exist. Cannot determine system or its revision.')
        vals = {}
        with open('/etc/os-release', encoding='utf-8') as f:
            for line in f.readlines():
                if '=' in line:
                    key, val = line.split('=', 1)
                    vals[key.strip()] = val.strip().replace('"', '')

        for i in ['ID', 'ID_LIKE']:
            if i in vals:
                system_candidates = vals[i].strip('"').split()
                for system_candidate in system_candidates:
                    if system_candidate in SYSTEMS:
                        system = system_candidate
                        break
                else:
                    continue
                break
        if system is None:
            raise UnexpectedError('cannot determine system')

        for i in ['VERSION_ID', 'BUILD_ID']:
            if i in vals:
                revision = vals[i]
                break
        if revision is None:
            raise UnexpectedError('cannot determine revision')

        if system in ['alpine', 'rhel', 'rocky']:
            revision = revision.rsplit('.', 1)[0]
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


class UnexpectedError(Exception):
    """Exception thrown when an unexpected error occurred that hammer does not know how to recover from."""


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

    log_file = None
    if log_file_path:
        with open(log_file_path, "wb", encoding='utf-8') as file:
            log_file = file.read()

    exitcode = 1
    output = ''
    for attempt in range(attempts):
        if interactive:
            # Issue: [B602:subprocess_popen_with_shell_equals_true] subprocess call with shell=True identified,
            #        security issue.
            with subprocess.Popen(cmd, cwd=cwd, env=env, shell=True) as pipe:  # nosec: B602
                pipe.communicate()
                exitcode = pipe.returncode

        else:
            # Issue: [B602:subprocess_popen_with_shell_equals_true] subprocess call with shell=True identified,
            #        security issue.
            with subprocess.Popen(cmd, cwd=cwd, env=env, shell=True,  # nosec: B602
                                  stdout=subprocess.PIPE, stderr=subprocess.STDOUT) as pipe:
                try:
                    if timeout is not None:
                        pipe.wait(timeout)
                    stdout, _ = pipe.communicate()
                    if stdout is not None:
                        output += stdout.decode('utf-8')
                except subprocess.TimeoutExpired as e:
                    pipe.kill()
                    stdout2, _ = pipe.communicate()
                    if stdout2 is not None:
                        output += stdout2.decode('utf-8')
                    raise ExecutionError(f'Execution timeout: {e}, cmd: {cmd}') from e
                exitcode = pipe.returncode
                if not quiet:
                    print(output)
                if log_file is not None:
                    log_file.write(stdout)

        if exitcode == 0:
            break

        if attempt < attempts - 1:
            txt = 'command failed, retry, attempt %d/%d' % (attempt, attempts)
            if log_file is not None:
                txt_to_file = '\n\n[HAMMER] %s\n\n\n' % txt
                log_file.write(txt_to_file.encode('ascii'))
            log.info(txt)
            if sleep_time_after_attempt:
                time.sleep(sleep_time_after_attempt)

    if log_file is not None:
        log_file.close()

    if exitcode != 0 and raise_error:
        if capture and quiet:
            log.error(output)
        raise ExecutionError("The command return non-zero exitcode %s, cmd: '%s'" % (exitcode, cmd))

    if capture:
        return exitcode, output.strip()
    return exitcode


def wait_for_process_to_start(process_name):
    for _ in range(10):
        exit_code = execute(f'sudo pidof {process_name}', raise_error=False)
        if exit_code == 0:
            # Process is there.
            break
        time.sleep(1)


def wait_for_process_to_exit(process_name):
    for _ in range(100):
        exit_code = execute(f'sudo pidof {process_name}', raise_error=False)
        if exit_code != 0:
            # Process exited or there was no process to begin with.
            break
        time.sleep(1)


def _append_to_file(file_name, line):
    with open(file_name, encoding='utf-8', mode='a') as f:
        f.write(line + '\n')


def replace_in_file(file_name, pattern, replacement):
    with open(file_name, 'r', encoding='utf-8') as file:
        content = file.read()
        content = re.sub(pattern, replacement, content)
    with open(file_name, 'w', encoding='utf-8') as file:
        file.write(content)


def install_meson(python_v: str = 'python3',
                  mode: str = 'pyinstaller',
                  only: str = None,
                  system: str = None,
                  revision: str = None):
    """ Install meson and ninja with pyinstaller or venv.

    Pyinstaller is needed as opposed to venv to overcome package building errors such as:
    venv/bin/python3 is needed by isc-kea-admin-2.7.7-isc20250320085254.el9.x86_64

    :param python_v: python executable
    :type python_v: str
    :param mode: whether installation is through pyinstaller or plain venv
    :type mode: str
    :param only: what to install: meson or ninja. None (default) means both.
    :type only: str
    :param system: system name (e.g., 'ubuntu')
    :type system: str
    :param revision: system revision (e.g., '20.04')
    :type revision: str
    """
    meson_version = '1.9.1'

    exit_code = execute('meson --version', quiet=True, raise_error=False)
    if exit_code == 0:
        return
    execute('sudo rm -fr .meson-src')
    execute(f'sudo {python_v} -m venv /usr/local/share/.venv')
    execute('sudo /usr/local/share/.venv/bin/pip install --upgrade pip setuptools wheel')
    # Install backports.tarfile for Ubuntu 20.04 (Python 3.8 compatibility)
    if system == 'ubuntu' and revision == '20.04':
        execute('sudo /usr/local/share/.venv/bin/pip install backports.tarfile')
    if only is None or only == 'ninja':
        execute('sudo /usr/local/share/.venv/bin/pip install ninja')
    if mode == 'pyinstaller':
        if only is None or only == 'meson':
            execute('git clone https://github.com/mesonbuild/meson .meson-src')
            execute(f'git checkout {meson_version}', cwd='.meson-src')
            execute('sudo /usr/local/share/.venv/bin/pip install pyinstaller')
            execute('sudo /usr/local/share/.venv/bin/pyinstaller --additional-hooks-dir=packaging --clean '
                    '--dist ../.meson --onefile ./meson.py',
                    cwd='.meson-src')
            execute('sudo cp .meson/meson /usr/local/bin')
        if only is None or only == 'ninja':
            execute('sudo cp /usr/local/share/.venv/bin/ninja /usr/local/bin')

    elif mode == 'venv':
        if only is None or only == 'meson':
            execute(f'sudo /usr/local/share/.venv/bin/pip install meson=={meson_version}')
            execute('sudo ln -s /usr/local/share/.venv/bin/meson /usr/local/bin/meson')
        if only is None or only == 'ninja':
            execute('sudo ln -s /usr/local/share/.venv/bin/ninja /usr/local/bin/ninja')
    else:
        raise UnexpectedError(f'Unknown mode in install_meson(mode={mode})')

    execute('sudo rm -fr .meson-src')


def install_sphinx(python_v: str = 'python3'):
    """ Install sphinx with pyinstaller.

    :param python_v: python executable
    :type python_v: str
    """

    exit_code = execute('sphinx-build --version', quiet=True, raise_error=False)
    if exit_code == 0:
        return
    execute(f'{python_v} -m venv .venv')
    execute('.venv/bin/pip install --upgrade pip')
    execute('.venv/bin/pip install pyinstaller')
    execute('.venv/bin/pip install sphinx')
    execute('.venv/bin/pip install sphinx_rtd_theme')
    execute('.venv/bin/pyinstaller --clean --collect-all sphinx_rtd_theme --collect-all sphinxcontrib --clean '
            '--onefile .venv/bin/sphinx-build')
    execute('sudo cp dist/sphinx-build /usr/local/bin')


def _prepare_installed_packages_cache_for_debs():
    pkg_cache = {}

    _, out = execute("dpkg -l", timeout=15, capture=True, quiet=True)

    for line in out.splitlines():
        line = line.strip()
        m = re.search(r'^([^\s]+)\s+([^\s]+)\s+([^\s]+)\s+([^\s]+)\s+(.+)', line)
        if not m:
            continue
        status, name, version, arch, descr = m.groups()
        name = name.split(':')[0]
        pkg_cache[name] = {
            'status': status,
            'version': version,
            'arch': arch,
            'descr': descr,
        }

    return pkg_cache


def _prepare_installed_packages_cache_for_rpms():
    pkg_cache = {}

    _, out = execute("rpm -qa --qf '%{NAME}\\n'", timeout=15, capture=True, quiet=True)

    for line in out.splitlines():
        name = line.strip()
        pkg_cache[name] = {'status': 'ii'}

    return pkg_cache


def _prepare_installed_packages_cache_for_alpine():
    pkg_cache = {}

    _, out = execute("apk list -I\\n'", timeout=15, capture=True, quiet=True)

    for line in out.splitlines():
        name = line.strip()
        pkg_cache[name] = {'status': 'ii'}

    return pkg_cache


def install_pkgs(pkgs, timeout=60, env=None, check_times=False, pkg_cache=None, one_package_at_a_time=False):
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
    if not pkg_cache and system in ['centos', 'rhel', 'fedora', 'debian', 'ubuntu',
                                    'rocky']:  # , 'alpine']:  # TODO: complete caching support for alpine
        if system in ['centos', 'rhel', 'fedora', 'rocky']:
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

    if system in ['centos', 'fedora', 'rhel', 'rocky']:
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
        cmd = 'sudo pkg clean --all --yes; sudo pkg install --no-repo-update --yes'
    elif system == 'alpine':
        cmd = 'sudo apk add'
    elif system == 'arch':
        cmd = 'sudo pacman -S --needed --noconfirm --overwrite \'*\''
    else:
        raise NotImplementedError('no implementation for %s' % system)

    if one_package_at_a_time:
        for p in pkgs:
            execute(
                f"{cmd} {p}",
                timeout=timeout,
                env=env,
                check_times=check_times,
                attempts=3,
                sleep_time_after_attempt=10,
            )
    else:
        pkgs = ' '.join(pkgs)
        execute(
            f"{cmd} {pkgs}",
            timeout=timeout,
            env=env,
            check_times=check_times,
            attempts=3,
            sleep_time_after_attempt=10,
        )


def get_image_template(key, variant):
    if key not in IMAGE_TEMPLATES:
        print('ERROR: Image {} is not available.'.format(key), file=sys.stderr)
        sys.exit(1)
    if variant not in IMAGE_TEMPLATES[key]:
        print('ERROR: Variant {} is not available for image {}.'.format(variant, key), file=sys.stderr)
        sys.exit(1)
    return IMAGE_TEMPLATES[key][variant]


def _get_full_repo_url(repository_url, system, revision):
    if not repository_url:
        return None
    repo_name = 'kea-%s-%s' % (system, revision)
    repo_url = urljoin(repository_url, 'repository')
    repo_url += '/%s/' % repo_name
    return repo_url


class VagrantEnv():
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
        self.image_tpl = get_image_template(key, image_template_variant)
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
        else:
            raise UnexpectedError('Unknown vagrantfile_tpl')

        vagrantfile = vagrantfile_tpl.format(image_tpl=self.image_tpl,
                                             name=self.name,
                                             ccache_dir=self.ccache_dir,
                                             box_version=box_version,
                                             hostname=hostname)

        with open(vagrantfile_path, "w", encoding='utf-8') as f:
            f.write(vagrantfile)

        log.info('Prepared vagrant system %s in %s', self.name, self.vagrant_dir)

    def up(self):
        """Do Vagrant up."""
        exitcode, out = execute("vagrant up --no-provision --provider %s" % self.provider,
                                cwd=self.vagrant_dir, timeout=15 * 60, dry_run=self.dry_run,
                                capture=True, raise_error=False)
        if exitcode != 0:
            if 'There is container on your system' in out and 'lxc-destroy' in out:
                m = re.search(r'`lxc-destroy.*?`', out)
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
            # Issue: [B310:blacklist] Audit url open for permitted schemes.
            #        Allowing use of file:/ or custom schemes is often unexpected.
            # Reason for nosec: it is clearly a https link.
            with urllib.request.urlopen(url) as response:  # nosec B310
                data = response.read()
        except Exception as e:
            log.exception('ignored exception: %s', e)
            return {}
        data = json.loads(data)
        return data

    def _get_local_meta(self):
        meta_file = os.path.join(self.vagrant_dir, '.vagrant/machines/default', self.provider, 'box_meta')
        if not os.path.exists(meta_file):
            return {}
        with open(meta_file, encoding='utf-8') as f:
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
                except ValueError:
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
        m = re.search(r'default\s+(.+)\(', out)
        if not m:
            raise UnexpectedError('cannot get status in:\n%s' % out)
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
            execute('sudo sh -c \'echo "ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEA6NF8ia'
                    'llvQVp22WDkTkyrtvp9eWW6A8YVr+kz4TjGYe7gHzIw+niNltGEFHzD8+v1I2YJ'
                    '6oXevct1YeS0o9HZyN1Q9qgCgzUFtdOKLv6IedplqoPkcmF0aYet2PkEDo3MlTB'
                    'ckFXPITAMzF8dJSIFo9D8HfdOV0IAdx4O7PtixWKn5y2hMNG0zQPyUecp4pzC6k'
                    'ivAIhyfHilFR61RGL+GPXQ2MWZWFYbAGjyiYJnAmCP3NOTd0jMZEnDkbUvxhMmB'
                    'YSdETk1rRgm+R4LOzFUGaHqHDLKLX+FIPKcF96hrucXzcWyLbIbEgE98OHlnVYC'
                    'zRdK8jlqm8tehUc9c9WhQ== vagrant insecure public key"'
                    '> %s/rootfs/home/vagrant/.ssh/authorized_keys\'' % lxc_container_path)

            # reset machine-id
            execute('sudo rm -f %s/rootfs/var/lib/dbus/machine-id' % lxc_container_path)
            # execute('sudo truncate -s 0 %s/rootfs/etc/machine-id' % lxc_container_path)
            execute('sudo rm -f %s/rootfs/etc/machine-id' % lxc_container_path)

            # pack rootfs
            cmd = 'sudo sh -c "'
            cmd += 'cd %s '
            cmd += '&& tar --numeric-owner --anchored --exclude=./rootfs/dev/log -czf %s/rootfs.tar.gz ./rootfs/*'
            cmd += '"'
            execute(cmd % (lxc_container_path, lxc_box_dir))

            # copy lxc config from runtime container
            execute('sudo cp %s/config %s/lxc-config' % (lxc_container_path, lxc_box_dir))
            # remove mac address from eth0 - it should be dynamically assigned
            execute("sudo sed -i'' '/lxc.net.0.hwaddr/d' %s/lxc-config" % lxc_box_dir)
            # correct files ownership
            execute('sudo chown `id -un`:`id -gn` *', cwd=lxc_box_dir)
            # and other metadata
            with open(os.path.join(lxc_box_dir, 'metadata.json'), 'w', encoding='utf-8') as f:
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
        exitcode = 1
        while attempt > 0:
            exitcode = execute('vagrant upload %s' % src, cwd=self.vagrant_dir, dry_run=self.dry_run, raise_error=False)
            if exitcode == 0:
                break
            attempt -= 1
        if exitcode != 0:
            msg = 'cannot upload %s' % src
            log.error(msg)
            raise ExecutionError(msg)

    def run_build_and_test(self, tarball_paths, jobs, pkg_version, pkg_isc_version, upload, repository_url):
        """Run build and unit tests inside Vagrant system."""
        if self.dry_run:
            return 0, 0

        # prepare tarball if needed and upload it to vagrant system
        name_ver = None
        if tarball_paths is None:
            execute('mkdir -p ~/.hammer-tmp')
            name_ver = 'kea-%s' % pkg_version
            cmd = 'tar --transform "flags=r;s|^|%s/|" --exclude hammer ' % name_ver
            cmd += ' --exclude "*~" --exclude .git --exclude .libs '
            cmd += ' --exclude .deps --exclude \'*.o\'  --exclude \'*.lo\' '
            cmd += ' -Jcvf ~/.hammer-tmp/%s.tar.xz .' % name_ver
            execute(cmd)
            tarball_paths = [f'~/.hammer-tmp/{name_ver}.tar.xz']
        self.upload(tarball_paths)
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
                                 tarball='-t ~/%s.tar.xz' % name_ver,
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

            file_ext = None
            if upload:
                repo_url = _get_full_repo_url(repository_url, self.system, self.revision)
                if repo_url is None:
                    raise ValueError('repo_url is None')
                upload_cmd = 'curl -v --netrc -f'

                if self.system in ['ubuntu', 'debian']:
                    upload_cmd += ' -X POST -H "Content-Type: multipart/form-data" --data-binary "@%s" '
                    file_ext = 'deb'  # include both '.deb' and '.ddeb' files

                elif self.system in ['fedora', 'centos', 'rhel', 'rocky']:
                    upload_cmd += ' --upload-file %s '
                    file_ext = '.rpm'

                elif self.system == 'alpine':
                    upload_cmd += ' --upload-file %s '
                    file_ext = ''
                    _, arch = self.execute('arch', raise_error=False, capture=True)
                    arch = arch.strip()
                    repo_url = urljoin(repo_url, f'{pkg_isc_version}/v{self.revision}/{arch}/')

                upload_cmd += ' ' + repo_url

                for fn in os.listdir(pkgs_dir):
                    if file_ext and not fn.endswith(file_ext):
                        continue
                    fp = os.path.join(pkgs_dir, fn)
                    cmd = upload_cmd % fp
                    exit_code, txt = execute(cmd, raise_error=False, capture=True, attempts=3)
                    log.info('code: %s, txt: %s', exit_code, txt)
                    # debian doc packages is arch "all" in both x86 and aarch so we want to ignore error
                    # while second is uploaded
                    if exit_code != 0 and "Repository does not allow updating assets" in txt:
                        continue

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
                    with open(results_file, encoding='utf-8') as f:
                        txt = f.read()
                        results = json.loads(txt)
                        total = results['grand_total']
                        passed = results['grand_passed']

                cmd = 'scp -F %s -r default:/home/vagrant/aggregated_tests.xml .' % ssh_cfg_path
                execute(cmd, cwd=self.vagrant_dir)
        except Exception as e:
            log.exception('ignored issue with parsing unit test results: %s', e)

        return total, passed

    def destroy(self):
        """Remove the VM completely."""
        if os.path.exists(self.vagrant_dir):
            cmd = 'vagrant destroy --force'
            execute(cmd, cwd=self.vagrant_dir, timeout=3 * 60, dry_run=self.dry_run)  # timeout: 3 minutes
            execute('rm -rf %s' % self.vagrant_dir)

    def ssh(self):
        """Open interactive session to the VM."""
        execute('vagrant ssh', cwd=self.vagrant_dir, dry_run=self.dry_run, interactive=True)

    def dump_ssh_config(self):
        """Dump ssh config that allows getting into Vagrant system via SSH."""
        ssh_cfg_path = os.path.join(self.vagrant_dir, 'ssh.cfg')
        execute('vagrant ssh-config > %s' % ssh_cfg_path, cwd=self.vagrant_dir)
        return ssh_cfg_path

    def execute(self, cmd, timeout=60, raise_error=True, log_file_path=None, quiet=False, env=None, capture=False,
                attempts=1, sleep_time_after_attempt=None):
        """Execute provided command inside Vagrant system."""
        if not env:
            env = os.environ.copy()
        env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

        return execute('vagrant ssh -c "%s"' % cmd, env=env, cwd=self.vagrant_dir, timeout=timeout,
                       raise_error=raise_error, dry_run=self.dry_run, log_file_path=log_file_path,
                       quiet=quiet, check_times=self.check_times, capture=capture,
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
                self.execute("sudo yum install -y python36 rpm-build python3-virtualenv", attempts=3)
            else:
                self.execute("sudo dnf install -y python36 rpm-build python3-virtualenv", attempts=3)
        elif self.system == 'freebsd':
            if self.revision.startswith('13'):
                self.execute("sudo pkg install --no-repo-update --yes python3", attempts=3)

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
                with open(os.path.expanduser('~/rhel-creds.txt'), encoding='utf-8') as f:
                    env['RHEL_USER'] = f.readline().strip()
                    env['RHEL_PASSWD'] = f.readline().strip()
                self.execute('sudo subscription-manager register --user $RHEL_USER --password "$RHEL_PASSWD"', env=env)
                self.execute("sudo subscription-manager refresh")
                self.execute("sudo subscription-manager attach --pool 8a85f99a67cdc3e70167e45c85f47429")
                self.execute("sudo subscription-manager repos --enable rhel-8-for-x86_64-baseos-beta-rpms")
                self.execute("sudo dnf install -y python36")

        # RPM-based distributions install libraries in /usr/local/lib64, but they
        # tend to not look there at runtime without explicit mention in ld.so.conf.d.
        if self.system in ['centos', 'fedora', 'rhel', 'rocky']:
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
        if self.system in ['debian', 'ubuntu', 'fedora', 'centos', 'rhel', 'rocky']:
            # setup a script that on first boot will set machine-id
            cmd = 'sh -c \'cat <<EOF | sudo tee /usr/lib/systemd/system/systemd-firstboot.service\n'
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
    gtest_version = '1.16.0'
    gtest_path = f'/usr/src/googletest-release-{gtest_version}/googletest'
    if os.path.exists(gtest_path):
        log.info('gtest is already installed in %s.', gtest_path)
        return

    execute('mkdir -p ~/.hammer-tmp')
    cmd = 'wget --no-verbose -O ~/.hammer-tmp/gtest.tar.gz '
    cmd += f'https://github.com/google/googletest/archive/refs/tags/v{gtest_version}.tar.gz'
    execute(cmd)
    execute('sudo mkdir -p /usr/src')
    execute('sudo tar -C /usr/src -zxf ~/.hammer-tmp/gtest.tar.gz')
    execute(f'sudo ln -sf /usr/src/googletest-{gtest_version} /usr/src/googletest')
    execute('rm -rf ~/.hammer-tmp')


def _install_libyang_from_sources(ignore_errors=False):
    """Install libyang from sources."""
    version = '3.13.5'

    libdirs = [f'{usr}/{lib}' for usr in ['/usr', '/usr/local'] for lib in ['lib', 'lib64']]
    for libdir in libdirs:
        pc_file = f'{libdir}/pkgconfig/libyang.pc'
        if os.path.exists(pc_file):
            with open(pc_file, encoding='utf-8') as file:
                for line in file:
                    if line.rstrip('\n') == f'Version: {version}':
                        log.info(f'libyang is already installed: {pc_file}.')
                        return

    execute('rm -rf ~/.hammer-tmp')
    execute('mkdir -p ~/.hammer-tmp')
    try:
        execute('git clone https://github.com/CESNET/libyang.git ~/.hammer-tmp/libyang')
        execute(f'git checkout v{version}', cwd='~/.hammer-tmp/libyang')
        execute('mkdir ~/.hammer-tmp/libyang/build')
        execute('cmake -DBUILD_TESTING=OFF ..',
                cwd='~/.hammer-tmp/libyang/build')
        execute('make -j $(nproc || gnproc)', cwd='~/.hammer-tmp/libyang/build')
        execute('sudo make install', cwd='~/.hammer-tmp/libyang/build')
        system, _ = get_system_revision()
        if system != 'alpine':
            execute('sudo ldconfig')
    except Exception as e:
        log.exception(str(e))
        if not ignore_errors:
            raise e
    finally:
        execute('rm -rf ~/.hammer-tmp')


def _install_sysrepo_from_sources(ignore_errors=False):
    """Install sysrepo from sources."""
    version = '3.7.11'

    libdirs = [f'{usr}/{lib}' for usr in ['/usr', '/usr/local'] for lib in ['lib', 'lib64']]
    for libdir in libdirs:
        pc_file = f'{libdir}/pkgconfig/sysrepo.pc'
        if os.path.exists(pc_file):
            with open(pc_file, encoding='utf-8') as file:
                for line in file:
                    if line.rstrip('\n') == f'Version: {version}':
                        log.info(f'sysrepo is already installed: {pc_file}.')
                        return

    # Create repository for YANG modules and change ownership to current user.
    execute('sudo mkdir -p /etc/sysrepo')
    execute('sudo chown -R "${USER}:$(id -gn)" /etc/sysrepo')

    execute('rm -rf ~/.hammer-tmp')
    execute('mkdir -p ~/.hammer-tmp')
    try:
        execute('git clone https://github.com/sysrepo/sysrepo.git ~/.hammer-tmp/sysrepo')
        execute(f'git checkout v{version}', cwd='~/.hammer-tmp/sysrepo')
        execute('mkdir ~/.hammer-tmp/sysrepo/build')
        execute('cmake -DBUILD_TESTING=OFF -DREPO_PATH=/etc/sysrepo ..', cwd='~/.hammer-tmp/sysrepo/build')
        execute('make -j $(nproc || gnproc)', cwd='~/.hammer-tmp/sysrepo/build')
        execute('sudo make install', cwd='~/.hammer-tmp/sysrepo/build')
        system, _ = get_system_revision()
        if system != 'alpine':
            execute('sudo ldconfig')
    except Exception as e:
        log.exception(str(e))
        if not ignore_errors:
            raise e
    finally:
        execute('rm -rf ~/.hammer-tmp')


def _install_libyang_cpp_from_sources(ignore_errors=False):
    """Install libyang-cpp from sources."""
    version = '3'

    libdirs = [f'{usr}/{lib}' for usr in ['/usr', '/usr/local'] for lib in ['lib', 'lib64']]
    for libdir in libdirs:
        pc_file = f'{libdir}/pkgconfig/libyang-cpp.pc'
        if os.path.exists(pc_file):
            with open(pc_file, encoding='utf-8') as file:
                for line in file:
                    if line.rstrip('\n') == f'Version: {version}':
                        log.info(f'libyang-cpp is already installed: {pc_file}.')
                        return

    execute('rm -rf ~/.hammer-tmp')
    execute('mkdir -p ~/.hammer-tmp')
    try:
        execute('git clone https://github.com/CESNET/libyang-cpp.git ~/.hammer-tmp/libyang-cpp')
        execute(f'git checkout v{version}', cwd='~/.hammer-tmp/libyang-cpp')
        execute('mkdir ~/.hammer-tmp/libyang-cpp/build')
        execute('cmake -DBUILD_TESTING=OFF .. ', cwd='~/.hammer-tmp/libyang-cpp/build')
        execute('make -j $(nproc || gnproc)', cwd='~/.hammer-tmp/libyang-cpp/build')
        execute('sudo make install', cwd='~/.hammer-tmp/libyang-cpp/build')
        system, _ = get_system_revision()
        if system != 'alpine':
            execute('sudo ldconfig')
    except Exception as e:
        log.exception(str(e))
        if not ignore_errors:
            raise e
    finally:
        execute('rm -rf ~/.hammer-tmp')


def _install_sysrepo_cpp_from_sources(ignore_errors=False):
    """Install sysrepo-cpp from sources."""
    version = '3'

    libdirs = [f'{usr}/{lib}' for usr in ['/usr', '/usr/local'] for lib in ['lib', 'lib64']]
    for libdir in libdirs:
        pc_file = f'{libdir}/pkgconfig/sysrepo-cpp.pc'
        if os.path.exists(pc_file):
            with open(pc_file, encoding='utf-8') as file:
                for line in file:
                    if line.rstrip('\n') == f'Version: {version}':
                        log.info(f'sysrepo-cpp is already installed: {pc_file}.')
                        return

    execute('rm -rf ~/.hammer-tmp')
    execute('mkdir -p ~/.hammer-tmp')
    try:
        execute('git clone https://github.com/sysrepo/sysrepo-cpp.git ~/.hammer-tmp/sysrepo-cpp')
        execute(f'git checkout v{version}', cwd='~/.hammer-tmp/sysrepo-cpp')
        execute('mkdir ~/.hammer-tmp/sysrepo-cpp/build')
        execute('cmake -DBUILD_TESTING=OFF .. ', cwd='~/.hammer-tmp/sysrepo-cpp/build')
        execute('make -j $(nproc || gnproc)', cwd='~/.hammer-tmp/sysrepo-cpp/build')
        execute('sudo make install', cwd='~/.hammer-tmp/sysrepo-cpp/build')
        system, _ = get_system_revision()
        if system != 'alpine':
            execute('sudo ldconfig')
    except Exception as e:
        log.exception(str(e))
        if not ignore_errors:
            raise e
    finally:
        execute('rm -rf ~/.hammer-tmp')


def _install_netconf_libraries_from_sources(ignore_errors=False):
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
        # Parent dir of hammer.py.
        p = os.path.dirname(os.path.realpath(os.path.abspath(sys.argv[0])))
        if not os.path.isdir(f'{p}/src/lib/asiolink/testutils/ca'):
            # Sometimes we call a standalone hammer.py on another Kea source tree. Let's use cwd in that case.
            p = '.'
        for file in [
            f'{p}/src/lib/asiolink/testutils/ca/kea-ca.crt',
            f'{p}/src/lib/asiolink/testutils/ca/kea-client.crt',
            f'{p}/src/lib/asiolink/testutils/ca/kea-client.key',
            f'{p}/src/lib/asiolink/testutils/ca/kea-server.crt',
            f'{p}/src/lib/asiolink/testutils/ca/kea-server.key',
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

    if system in ['debian', 'fedora', 'centos', 'rhel', 'rocky']:
        execute('sudo systemctl enable mariadb.service')
        exit_code = execute('sudo systemctl restart mariadb.service', raise_error=False)
        if exit_code != 0:
            log.error('Command "sudo systemctl restart mariadb.service" failed. Here is the journal:')
            execute('sudo journalctl -xu mariadb.service', raise_error=False)
            log.error('And here are the logs:')
            execute('cat /var/log/mysql/error.log', raise_error=False)
            sys.exit(exit_code)

    elif system == 'ubuntu':
        execute('sudo systemctl enable mysql.service')
        exit_code = execute('sudo systemctl restart mysql.service', raise_error=False)
        if exit_code != 0:
            log.error('Command "sudo systemctl restart mysql.service" failed. Here is the journal:')
            execute('sudo journalctl -xu mysql.service', raise_error=False)
            log.error('And here are the logs:')
            execute('cat /var/log/mysql/error.log', raise_error=False)
            sys.exit(exit_code)

    elif system == 'alpine':
        execute('sudo sed -i"" "/^skip-networking$/d" /etc/my.cnf.d/mariadb-server.cnf')
        execute('sudo rc-update add mariadb')
        execute('sudo rc-service mariadb stop')
        wait_for_process_to_start('start-stop-daemon')  # mysqld_safe
        wait_for_process_to_exit('start-stop-daemon')  # mysqld_safe
        execute('sudo pkill -f mysqld_safe', raise_error=False)  # If no graceful shutdown, force kill.
        execute('sudo rc-service mariadb setup')
        execute('sudo rc-service mariadb restart', raise_error=False)

    cmd = "echo 'DROP DATABASE IF EXISTS keatest;' | sudo mysql -u root"
    execute(cmd)
    cmd = "echo 'DROP USER 'keatest'@'localhost';' | sudo mysql -u root"
    execute(cmd, raise_error=False)
    cmd = "echo 'DROP USER 'keatest_readonly'@'localhost';' | sudo mysql -u root"
    execute(cmd, raise_error=False)
    cmd = "echo 'DROP USER 'keatest_secure'@'localhost';' | sudo mysql -u root"
    execute(cmd, raise_error=False)
    cmd = "sh -c \"cat <<EOF | sudo mysql -u root\n"
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
        exit_code = execute('''sudo mysql -u root -e "ALTER USER 'keatest_secure'@'localhost' REQUIRE X509;"''',
                            raise_error=False)
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
        cmd = "sh -c \"cat <<EOF | sudo mysql -u root\n"
        cmd += "CREATE DATABASE keadb;\n"
        cmd += "CREATE USER 'keauser'@'localhost' IDENTIFIED BY 'keapass';\n"
        cmd += "GRANT ALL ON keadb.* TO 'keauser'@'localhost';\n"
        cmd += "EOF\n\""
        execute(cmd)

    if system == 'debian' and revision == '9':
        log.info('FIX FOR ISSUE kea#389: %s %s', system, revision)
        cmd = "sh -c \"cat <<EOF | sudo mysql -u root\n"
        cmd += "use keatest;\n"
        cmd += "set global innodb_large_prefix=on;\n"
        cmd += "set global innodb_file_format=Barracuda;\n"
        cmd += "set global innodb_file_per_table=true;\n"
        cmd += "set global innodb_default_row_format=dynamic;\n"
        cmd += "EOF\n\""
        execute(cmd)


def _enable_postgresql(system):
    if system == 'alpine':
        execute('sudo rc-update add postgresql')
    elif system == 'freebsd':
        execute('sudo sysrc postgresql_enable="yes"')
    else:
        # Disable all PostgreSQL services first to avoid conflicts.
        # raise_error=False for when there are no matches
        _, output = execute("sudo systemctl list-unit-files | grep postgres | grep -Fv '@.service' | cut -d ' ' -f 1",
                            capture=True, raise_error=False)
        for service in output.split():
            execute(f'sudo systemctl disable {service}')

        execute('sudo systemctl enable postgresql.service')


def _restart_postgresql(system):
    if system == 'freebsd':
        # redirecting output from start script to /dev/null otherwise the postgresql rc.d script will hang
        # calling restart instead of start allow hammer.py to pass even if postgresql is already installed
        execute('sudo service postgresql restart > /dev/null')
    elif system == 'alpine':
        execute('sudo /etc/init.d/postgresql restart')
    else:
        # Stop all PostgreSQL services first to avoid conflicts.
        # raise_error=False for when there are no matches
        _, output = execute("sudo systemctl list-unit-files | grep postgres | grep -Fv '@.service' | cut -d ' ' -f 1",
                            capture=True, raise_error=False)
        for service in output.split():
            execute(f'sudo systemctl stop {service}')

        exit_code = execute('sudo systemctl restart postgresql.service', raise_error=False)
        if exit_code != 0:
            log.error('Command "sudo systemctl restart postgresql.service" failed. Here is the journal:')
            execute('sudo journalctl -xu postgresql.service', raise_error=False)
            log.error('And here are the logs:')
            _, output = execute("sudo -u postgres psql -A -t -c 'SELECT pg_current_logfile()'",
                                capture=True, quiet=True)
            logfile = os.path.basename(output.strip())
            execute(fr'sudo find /var -type f -name "{logfile}" -exec cat {{}} \;', raise_error=False)
            sys.exit(exit_code)


# Change authentication type for given connection type. Usual inputs for
# connection type are 'host' or 'local'. Only affects entries with database
# and user both set to 'all'. This is to not affect authentication of
# `postgres` user which should have a separate entry.
def _change_postgresql_auth_method(connection_type, auth_method, hba_file):
    execute(fr"sudo sed -i.bak 's/^{connection_type}\(.*\)all\(.*\)all\(.*\) [a-z0-9]*$"
            fr"/{connection_type}\1all\2all\3 {auth_method}/g' '{hba_file}'",
            cwd='/tmp')


def _configure_pgsql(system, features):
    """ Configure PostgreSQL DB """

    # Some execute() calls set cwd='/tmp' when switching user to postgres to
    # avoid the error:
    #   could not change as postgres user directory to "/home/jenkins": Permission denied

    if system in ['fedora', 'centos', 'rhel', 'rocky']:
        # https://fedoraproject.org/wiki/PostgreSQL
        exitcode = execute('sudo ls /var/lib/pgsql/data/postgresql.conf', raise_error=False)
        if exitcode != 0:
            if system == 'centos':
                execute('sudo postgresql-setup initdb')
            else:
                execute('sudo postgresql-setup --initdb --unit postgresql')
    elif system == 'freebsd':
        # If data directory is not created, then initdb.
        var_db_postgres_data = glob.glob('/var/db/postgres/data*')
        if len(var_db_postgres_data) == 0:
            execute('sudo service postgresql oneinitdb')

        # Get data directory again. It will be needed later.
        var_db_postgres_data = glob.glob('/var/db/postgres/data*')
        if len(var_db_postgres_data) == 0:
            raise UnexpectedError('Could not find /var/db/postgres/data*')
        var_db_postgres_data = var_db_postgres_data[-1]

        # if the file '/var/db/postgres/data*/postmaster.opts' does not exist the 'restart' of postgresql will fail
        # with error:
        #    pg_ctl: could not read file "/var/db/postgres/data*/postmaster.opts"
        # the initial start of the postgresql will create the 'postmaster.opts' file
        # There might be a bug that makes execute freeze when the subprocess exits before reaching communicate().
        # In reality, this should never happen. I'm suspecting a bug in python. interactive=True prevents the freeze.
        execute(f'if sudo test ! -f {var_db_postgres_data}/postmaster.opts; then sudo service postgresql onestart; fi',
                interactive=True)

    _enable_postgresql(system)
    _restart_postgresql(system)

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
        auth_header = '# TYPE  DATABASE        USER            ADDRESS                 METHOD'
        postgres_auth_line = 'local   all             postgres                                ident'
        # The "\\" followed by newline is for BSD support.
        execute("""sudo sed -i.bak '/{}/a\\
{}
' '{}'""".format(auth_header, postgres_auth_line, hba_file))

    _restart_postgresql(system)

    cmd = """sh -c \"cat <<EOF | sudo -u postgres psql postgres
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

    # This is needed for postgres >= 15
    cmd = """sh -c \"cat <<EOF | sudo -u postgres psql -U postgres -d keatest
        GRANT ALL PRIVILEGES ON SCHEMA public TO keatest;\n"""
    cmd += 'EOF\n"'
    execute(cmd, cwd='/tmp')

    cmd = """sh -c \"cat <<EOF | sudo -u postgres psql -U keatest keatest
        ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT SELECT ON TABLES TO keatest_readonly;\n"""
    cmd += 'EOF\n"'
    env = os.environ.copy()
    env['PGPASSWORD'] = 'keatest'
    execute(cmd, cwd='/tmp', env=env)

    if 'forge' in features:
        cmd = "sh -c \"cat <<EOF | sudo -u postgres psql postgres\n"
        cmd += "DROP DATABASE IF EXISTS keadb;\n"
        cmd += "DROP USER IF EXISTS keauser;\n"
        cmd += "CREATE USER keauser WITH PASSWORD 'keapass';\n"
        cmd += "CREATE DATABASE keadb;\n"
        cmd += "GRANT ALL PRIVILEGES ON DATABASE keauser TO keadb;\n"
        cmd += "EOF\n\""
        execute(cmd, cwd='/tmp')

        # This is needed for postgres >= 15
        cmd = """sh -c \"cat <<EOF | sudo -u postgres psql -U postgres -d keadb
            GRANT ALL PRIVILEGES ON SCHEMA public TO keauser;\n"""
        cmd += 'EOF\n"'
        execute(cmd, cwd='/tmp')

    log.info('postgresql just configured')


def _apt_update(system, revision, env=None, check_times=False, attempts=1, sleep_time_after_attempt=None,
                capture=False):
    cmd = 'sudo apt update'
    if system == 'debian' and int(revision) >= 10:
        cmd += ' --allow-releaseinfo-change'
    return execute(cmd, env=env, check_times=check_times, attempts=attempts,
                   sleep_time_after_attempt=sleep_time_after_attempt, capture=capture)


def _get_package_version(package: str):
    """
    Returns the version available in the package manager's repository for the requested package.
    :param package: the name of the package whose version is retrieved
    """
    system, _ = get_system_revision()
    if system == 'alpine':
        cmd = "apk search --exact {0} | sed 's/{0}-//g'"
    elif system in ['debian', 'ubuntu']:
        cmd = "apt-cache show {} | grep -F 'Version:' | cut -d ' ' -f 2"
    elif system in ['centos', 'fedora', 'rhel', 'rocky']:
        cmd = "dnf list {} -y | tr -s ' ' | cut -d ' ' -f 2 | tail -n 1"
    elif system == 'freebsd':
        cmd = r"pkg search {0} | grep -Eo '^{0}-[0-9_,\.]+' | sed 's/{0}-//g'"
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
        raise UnexpectedError(message)


def prepare_system_local(features, check_times, ignore_errors_for, just_configure, one_package_at_a_time):
    """Prepare local system for Kea development based on requested features."""
    system, revision = get_system_revision()
    log.info('Preparing deps for %s %s...', system, revision)

    if not just_configure:
        install_packages_local(system, revision, features, check_times, ignore_errors_for, one_package_at_a_time)

    if 'mysql' in features:
        _configure_mysql(system, revision, features)

    if 'pgsql' in features:
        _configure_pgsql(system, features)

    log.info('Preparing deps completed successfully.')


def install_packages_local(system, revision, features, check_times, ignore_errors_for, one_package_at_a_time):
    """Install packages for Kea development based on requested features."""
    env = os.environ.copy()
    env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

    # Actions decided before installing packages, but run afterwards
    deferred_functions = []

    # Check if package versions cannot be met.
    if 'netconf' in features and 'netconf' not in ignore_errors_for:
        require_minimum_package_version('cmake', '3.19')

    packages = []

    # Common packages
    packages.append('pkgconf')
    if 'ccache' in features:
        packages.append('ccache')

    if 'docs' in features:
        packages.extend(['bison', 'flex'])

    # prepare fedora
    if system == 'fedora':
        packages.extend(['boost-devel', 'gcc-c++', 'openssl-devel', 'log4cplus-devel', 'libpcap-devel'])
        deferred_functions.append(install_meson)

        if 'native-pkg' in features:
            packages.extend(['rpm-build', 'python3-devel'])

        if 'docs' in features:
            packages.extend(['python3-sphinx', 'python3-sphinx_rtd_theme', 'texlive', 'texlive-collection-latexextra'])

        if 'mysql' in features:
            packages.extend(['mariadb', 'mariadb-server', 'mariadb-connector-c-devel'])

        if 'pgsql' in features:
            packages.extend(['libpq-devel', 'postgresql', 'postgresql-server'])

        if 'gssapi' in features:
            packages.extend(['krb5-devel'])

        if 'netconf' in features:
            packages.extend(['cmake', 'git', 'pcre2-devel'])
            # Even though meson sets rpath, it does not work in fedora.
            # This is even more stupid since it's a fairly standard path that could have worked out of the box.
            # Set it manually and persistently at a global level...
            execute('echo /usr/local/lib64 | sudo tee /etc/ld.so.conf.d/netconf.conf')

        if 'unittest' in features:
            packages.append('wget')
            deferred_functions.append(_install_gtest_sources)

        if 'sanitizers' in features:
            packages.extend(['compiler-rt', 'llvm', 'libasan', 'libtsan', 'libubsan'])

        install_pkgs(packages, timeout=300, env=env, check_times=check_times)

        execute('sudo dnf clean packages', env=env, check_times=check_times)

    # prepare centos
    elif system == 'centos':
        install_pkgs('epel-release', env=env, check_times=check_times)

        packages.extend(['boost-devel', 'gcc-c++', 'git', 'log4cplus-devel', 'openssl-devel'])
        deferred_functions.append(install_meson)

        if revision in ['7', '8']:
            # Install newer version of Boost in case users want to opt-in with:
            # --with-boost-include=/usr/include/boost169 --with-boost-lib-dir=/usr/lib64/boost169
            packages.append('boost169-devel')

        if 'docs' in features:
            packages.extend(['python3-sphinx', 'python3-sphinx_rtd_theme'])

        if 'native-pkg' in features:
            packages.extend(['python3-devel', 'rpm-build'])

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

        if 'gssapi' in features:
            packages.extend(['krb5-devel'])

        if 'netconf' in features:
            packages.extend(['cmake', 'git', 'pcre2-devel'])

        if 'unittest' in features:
            packages.append('wget')
            deferred_functions.append(_install_gtest_sources)

        if 'sanitizers' in features:
            packages.extend(['compiler-rt', 'llvm', 'libasan', 'libtsan', 'libubsan'])

        install_pkgs(packages, env=env, check_times=check_times)

    # prepare rhel
    elif system == 'rhel':
        packages.extend(['boost-devel', 'gcc-c++', 'log4cplus-devel', 'openssl-devel'])

        # RHEL tends to stay behind on Python versions. Install the latest Python alongside the one running this
        # hammer.py.
        python_v = 'python3'
        _, output = execute(r"sudo dnf search 'python3\.[0-9]*'", capture=True, env=env, check_times=check_times)
        output = sorted(output.splitlines())
        if len(output) > 0:
            m = re.search(r'^(python3\.[0-9]+)\.', output[-1])
            if m is not None:
                python_v = m.group(1)
                packages.append(python_v)

        deferred_functions.append(lambda: install_meson(python_v))

        if revision in ['7', '8']:
            # Install newer version of Boost in case users want to opt-in with:
            # --with-boost-include=/usr/include/boost169 --with-boost-lib-dir=/usr/lib64/boost169
            packages.append('boost169-devel')

        if 'docs' in features:
            packages.extend(['texlive', 'texlive-capt-of', 'texlive-fncychap', 'texlive-framed', 'texlive-needspace',
                             'texlive-tabulary', 'texlive-titlesec', 'texlive-upquote', 'texlive-wrapfig'])
            deferred_functions.append(lambda: install_sphinx(python_v))

        if 'native-pkg' in features:
            packages.extend(['python3-devel', 'rpm-build'])

        if 'mysql' in features:
            packages.extend(['mariadb', 'mariadb-server'])
            if int(revision) < 9:
                packages.extend(['mariadb-devel'])
            else:
                packages.extend(['mariadb-connector-c-devel'])

        if 'pgsql' in features:
            packages.extend(['libpq-devel', 'postgresql', 'postgresql-server'])

        if 'gssapi' in features:
            packages.extend(['krb5-devel'])

        if 'netconf' in features:
            packages.extend(['cmake', 'git', 'pcre2-devel'])

        if 'unittest' in features:
            packages.append('wget')
            deferred_functions.append(_install_gtest_sources)

        if 'sanitizers' in features:
            packages.extend(['compiler-rt', 'llvm', 'libasan', 'libtsan', 'libubsan'])

        install_pkgs(packages, env=env, timeout=120, check_times=check_times)

    # prepare rocky
    elif system == 'rocky':
        install_pkgs('epel-release', env=env, check_times=check_times)

        packages.extend(['boost-devel', 'gcc-c++', 'log4cplus-devel', 'openssl-devel', 'ninja-build'])
        deferred_functions.append(install_meson)

        if 'docs' in features:
            packages.extend(['texlive', 'texlive-capt-of', 'texlive-fncychap', 'texlive-framed', 'texlive-needspace',
                             'texlive-tabulary', 'texlive-titlesec', 'texlive-upquote', 'texlive-wrapfig'])
            deferred_functions.append(install_sphinx)

        if 'native-pkg' in features:
            packages.extend(['python3-devel', 'rpm-build'])

        if 'mysql' in features:
            packages.extend(['mariadb', 'mariadb-server', 'mariadb-connector-c-devel'])

        if 'pgsql' in features:
            packages.extend(['libpq-devel', 'postgresql', 'postgresql-server'])

        if 'gssapi' in features:
            packages.extend(['krb5-devel'])

        if 'netconf' in features:
            packages.extend(['cmake', 'git', 'pcre2-devel'])

        if 'unittest' in features:
            packages.append('wget')
            deferred_functions.append(_install_gtest_sources)

        if 'sanitizers' in features:
            packages.extend(['compiler-rt', 'llvm', 'libasan', 'libtsan', 'libubsan'])

        execute('sudo dnf config-manager --set-enabled crb')
        execute('sudo dnf config-manager --set-enabled devel')
        install_pkgs(packages, env=env, timeout=120, check_times=check_times)

    # prepare ubuntu
    elif system == 'ubuntu':
        _apt_update(system, revision, env=env, check_times=check_times, attempts=3, sleep_time_after_attempt=10)

        packages.extend(
            [
                'gcc',
                'g++',
                'gnupg',
                'libboost-system-dev',
                'liblog4cplus-dev',
                'libpcap-dev',
                'libssl-dev',
                'python3-dev',
                'python3-venv',
            ]
        )
        deferred_functions.append(lambda: install_meson(system=system, revision=revision))

        if 'coverage' in features:
            packages.extend(['gcovr', 'lcov'])

        if 'docs' in features:
            packages.extend(['python3-sphinx', 'python3-sphinx-rtd-theme',
                             'texlive', 'texlive-latex-extra', 'tex-gyre'])

        if 'unittest' in features:
            packages.append('googletest')

        if 'native-pkg' in features:
            packages.extend(['build-essential', 'fakeroot', 'devscripts'])
            packages.extend(['debhelper', 'libboost-dev', 'python3-dev'])
            if 20.04 <= float(revision):
                packages.extend(['dh-python'])

        if 'mysql' in features:
            if int(revision.split(".")[0]) < 24:
                if revision == '16.04':
                    packages.extend(['mysql-client', 'libmysqlclient-dev', 'mysql-server'])
                else:
                    packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev', 'mysql-server'])
            else:
                packages.extend(['mariadb-client', 'mariadb-server', 'libmariadb-dev-compat'])

        if 'pgsql' in features:
            packages.extend(['libpq-dev', 'postgresql', 'postgresql-client'])

        if 'gssapi' in features:
            packages.extend(['libkrb5-dev'])

        if 'netconf' in features:
            packages.extend(['cmake', 'git', 'libpcre2-dev'])

        install_pkgs(packages, env=env, timeout=240, check_times=check_times)

    # prepare debian
    elif system == 'debian':
        _apt_update(system, revision, env=env, check_times=check_times, attempts=3, sleep_time_after_attempt=10)

        packages.extend(
            [
                'gcc',
                'g++',
                'gnupg',
                'libboost-system-dev',
                'liblog4cplus-dev',
                'libpcap-dev',
                'libssl-dev',
                'python3-dev',
                'python3-venv',
            ]
        )
        deferred_functions.append(install_meson)

        if 'coverage' in features:
            packages.extend(['gcovr', 'lcov'])

        if 'docs' in features:
            packages.extend(['doxygen', 'graphviz', 'python3-sphinx', 'python3-sphinx-rtd-theme', 'tex-gyre',
                             'texlive', 'texlive-latex-extra'])

        if 'unittest' in features:
            packages.append('googletest')

        if 'netconf' in features:
            packages.extend(['cmake', 'git', 'libpcre2-dev'])

        if 'native-pkg' in features:
            packages.extend(['build-essential', 'fakeroot', 'devscripts'])
            packages.extend(['debhelper', 'libboost-dev', 'python3-dev'])
            if int(revision) >= 11:
                packages.extend(['dh-python'])

        if 'mysql' in features:
            packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev'])
            if int(revision) <= 8:
                packages.extend(['mysql-client', 'libmysqlclient-dev', 'mysql-server'])
            elif int(revision) <= 9:
                packages.append('mysql-server')
            else:
                packages.append('mariadb-server')

        if 'pgsql' in features:
            packages.extend(['libpq-dev', 'postgresql', 'postgresql-client'])

        if 'gssapi' in features:
            packages.extend(['libkrb5-dev'])

        install_pkgs(packages, env=env, timeout=240, check_times=check_times)

    # prepare freebsd
    elif system == 'freebsd':
        packages.extend(['bash', 'boost-libs', 'botan3', 'coreutils', 'git', 'log4cplus', 'openssl', 'ninja'])
        deferred_functions.append(lambda: install_meson(only='meson'))

        if 'docs' in features:
            # Get the python version from the remote repositories.
            pyv = _get_package_version('python')
            pyv = pyv.split('_')[0].replace('.', '')
            log.info(">>>>> Detected python package version: py%s", pyv)
            packages.extend([f'py{pyv}-sphinx', f'py{pyv}-sphinx_rtd_theme', 'texlive-full'])

        if 'mysql' in features:
            if revision.startswith(('11', '12')):
                packages.extend(['mysql57-server', 'mysql57-client'])
            else:
                packages.extend(['mysql80-server', 'mysql80-client'])

        if 'pgsql' in features:
            # Install the latest postgresql-client and postgresql-server,
            # unless any postgresql-client or postgresql-server version is already installed.
            for i in ['client', 'server']:
                # Check if already installed.
                _, output = execute('pkg info', capture=True, quiet=True)
                m = re.search(f'postgresql[0-9]+-{i}', output)
                if m is None:
                    # If not, go ahead and install.
                    _, output = execute('pkg search postgresql', capture=True)
                    found = re.findall(f'postgresql[0-9]+-{i}', output)
                    if len(found) == 0:
                        print(f'No postgresql[0-9]+-{i} found?')
                        sys.exit(1)
                    # There may be more matches. Results are sorted by pkg.
                    # Choose the last from the list which should be the latest version.
                    packages.append(found[-1])

        if 'gssapi' in features:
            packages.extend(['krb5'])
            # FreeBSD comes with a Heimdal krb5-config by default. Make sure
            # it's deleted so that Kea uses the MIT packages added just above.
            execute('sudo rm -f /usr/bin/krb5-config')

        if 'netconf' in features:
            packages.extend(['cmake', 'git', 'pcre2'])

        if 'unittest' in features:
            packages.extend(['wget'])
            deferred_functions.append(_install_gtest_sources)

        install_pkgs(
            packages,
            env=env,
            timeout=6 * 60,
            check_times=check_times,
            one_package_at_a_time=one_package_at_a_time,
        )

        if 'mysql' in features:
            execute('sudo sysrc mysql_enable="yes"', env=env, check_times=check_times)
            execute('sudo service mysql-server start', env=env, check_times=check_times,
                    raise_error=False)

        execute('sudo pkg clean -a -y')
        execute('sudo rm -rf /usr/lib/debug')

    # prepare alpine
    elif system == 'alpine':
        if 0 != execute("grep -E '^ulimit -s unlimited$' ~/.profile", quiet=True, raise_error=False):
            execute("echo 'ulimit -s unlimited' >> ~/.profile")
        packages.extend(['boost-libs', 'boost-dev', 'botan3-dev', 'build-base', 'gcompat', 'gcc', 'g++', 'gzip',
                         'log4cplus', 'log4cplus-dev', 'musl-dev', 'openssl-dev', 'procps', 'python3-dev',
                         'tar'])
        deferred_functions.append(install_meson)

        if 'docs' in features:
            packages.extend(['py3-sphinx', 'py3-sphinx_rtd_theme', 'texlive-full'])

        if 'netconf' in features:
            packages.extend(['cmake', 'git', 'pcre2-dev'])

        if 'mysql' in features:
            packages.extend(['mariadb-dev', 'mariadb', 'mariadb-client'])

        if 'pgsql' in features:
            packages.extend(['postgresql-dev', 'postgresql'])

        if 'gssapi' in features:
            packages.extend(['krb5-dev'])

        if 'native-pkg' in features:
            packages.extend(['alpine-sdk', 'python3-dev'])

        if 'unittest' in features:
            packages.append('wget')
            deferred_functions.append(_install_gtest_sources)

        # Remove duplicates and sort.
        packages = sorted(set(packages))

        install_pkgs(packages, env=env, timeout=6 * 60, check_times=check_times)

        # check for existence of 'vagrant' user and 'abuild' group before adding him to the group
        try:
            pwd.getpwnam('vagrant')
            grp.getgrnam('abuild')
        except KeyError:
            log.info("Can't add 'vagrant' user to 'abuild' group. Vagrant or abuild does not exist.")
        else:
            execute('sudo adduser vagrant abuild')

        current_user = getpass.getuser()
        try:
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
        elif system in ['centos', 'rhel', 'fedora', 'rocky']:
            ccache_bin_path = '/usr/lib64/ccache'
            env['CC'] = 'ccache gcc'
            env['CXX'] = 'ccache g++'
        elif system == 'alpine':
            # TODO: it doesn't work yet, new abuild is needed and add 'USE_CCACHE=1' to /etc/abuild.conf
            ccache_bin_path = '/usr/lib/ccache/bin'
        else:
            raise UnexpectedError(f'Unknown system "{system}"')
        env['PATH'] = ccache_bin_path + ':' + env['PATH']
        env['CCACHE_DIR'] = ccache_dir
    return env


def _build_binaries_and_run_ut(system, revision, features, tarball_paths, env, check_times, dry_run, ccache_dir, jobs):
    if tarball_paths is not None:
        # unpack tarball with sources
        execute('sudo rm -rf kea-src')
        os.mkdir('kea-src')
        for i in tarball_paths:
            execute(f'tar -Jxf {i}', cwd='kea-src', check_times=check_times)
        src_path = glob.glob('kea-src/*')[0]
    else:
        src_path = '.'

    log.info('OS: %s Revision: %s', system, revision)

    # Prepare build options.
    cmd = 'meson setup build'
    if 'all' in features:
        cmd += ' --auto_features enabled -D cpp_std=c++20'
    if 'mysql' in features:
        cmd += ' -D mysql=enabled'
    if 'pgsql' in features:
        cmd += ' -D postgresql=enabled'
    if 'unittest' in features:
        cmd += ' -D tests=enabled'
    if 'gssapi' in features:
        cmd += ' -D krb5=enabled'
    if 'netconf' in features:
        cmd += ' -D netconf=enabled -D cpp_std=c++20'

    # Set up the build.
    execute(cmd, cwd=src_path, env=env, timeout=120, check_times=check_times, dry_run=dry_run)

    if 'netconf' in features:
        # Install YANG modules.
        execute('./build/src/share/yang/modules/utils/reinstall.sh', cwd=src_path, env=env)

    # enable ccache if requested
    env = _prepare_ccache_if_needed(system, ccache_dir, env)

    # do build
    timeout = _calculate_build_timeout(features)
    if 'distcheck' in features:
        cmd = 'meson dist -C build'
    else:
        cmd = f'meson compile -C build -j {jobs}'
    execute(cmd, cwd=src_path, env=env, timeout=timeout, check_times=check_times, dry_run=dry_run)

    if 'unittest' in features:
        results_dir = os.path.abspath(os.path.join(src_path, 'tests_result'))
        execute('rm -rf %s' % results_dir, dry_run=dry_run)
        if not os.path.exists(results_dir):
            os.mkdir(results_dir)
        env['GTEST_OUTPUT'] = 'xml:%s/' % results_dir
        env['KEA_SOCKET_TEST_DIR'] = '/tmp/'
        # run unit tests
        execute('meson test -C build',
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
            results[fn] = {
                'total': total,
                'failures': failures,
                'disabled': disabled,
                'errors': errors,
            }
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

        with open('unit-test-results.json', 'w', encoding='utf-8') as f:
            f.write(json.dumps(results))

        # store aggregated results in XML
        if os.path.exists('aggregated_tests.xml'):
            os.unlink('aggregated_tests.xml')
        aggr = ET.ElementTree(aggregated_root)
        aggr.write('aggregated_tests.xml')

    if 'install' in features:
        execute('sudo meson install -C build', timeout=2 * 60,
                cwd=src_path, env=env, check_times=check_times, dry_run=dry_run)
        if system != 'alpine':
            execute('sudo ldconfig', dry_run=dry_run, env=env)

        if 'forge' in features:
            if 'mysql' in features:
                execute('kea-admin db-init mysql -u keauser -p keapass -n keadb', dry_run=dry_run)
            if 'pgsql' in features:
                execute('kea-admin db-init pgsql -u keauser -p keapass -n keadb', dry_run=dry_run)


def _check_installed_rpm_or_debs(services_list, log_text, expect_success_on_start=True):
    """Check that services log the given text after stopping and starting.

    :param services_list: services to check
    :type services_list: list
    :param log_text: text to search
    :type log_text: str
    :param expect_success_on_start: whether to expect success on "systemctl start", otherwise expect error.
                                    Useful for negative checks.
    :type expect_success_on_start: bool
    """
    for svc in services_list:
        execute(f'sudo systemctl stop {svc}')
        now = datetime.datetime.now()
        timestamp = now.strftime('%Y-%m-%d%H:%M:%S')
        rc, _ = execute(f'sudo systemctl start {svc}', capture=True, raise_error=expect_success_on_start)
        assert rc == 0 if expect_success_on_start else 2
        logs = ''
        for _ in range(10):
            _, logs = execute(f'sudo journalctl --since {timestamp} -u {svc}', capture=True)
            if log_text in logs:
                break
            time.sleep(1)
        if log_text not in logs:
            print(logs)
            raise UnexpectedError(f'{log_text} not in logs')


def _build_rpm(system, revision, features, env, check_times, dry_run,
               pkg_version, pkg_isc_version):

    # unpack kea sources tarball
    _, arch = execute('arch', capture=True)

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
    rpm_dir = os.path.join('kea-src', 'rpm')
    for f in os.listdir(rpm_dir):
        if f == 'kea.spec':
            continue
        execute('cp %s %s/SOURCES' % (os.path.join(rpm_dir, f), rpm_root_path), check_times=check_times,
                dry_run=dry_run)
    execute('cp %s %s/SPECS' % (os.path.join(rpm_dir, 'kea.spec'), rpm_root_path), check_times=check_times,
            dry_run=dry_run)
    execute(f'cp *.tar.xz {rpm_root_path}/SOURCES', cwd='kea-src', check_times=check_times, dry_run=dry_run)

    services_list = ['kea-dhcp4.service', 'kea-dhcp6.service', 'kea-dhcp-ddns.service', 'kea-ctrl-agent.service']

    # centos/rhel 7 does not support some fields in systemd unit files so they need to be commented out
    if system == 'centos' and revision == '7':
        for f in services_list:
            for k in ['RuntimeDirectory', 'RuntimeDirectoryPreserve', 'LogsDirectory', 'LogsDirectoryMode',
                      'StateDirectory', 'ConfigurationDirectory']:
                replace_in_file(f, fr'^({k}=.*)', r'# \1')

    # do rpm build
    cmd = "rpmbuild --define 'kea_version %s' --define 'isc_version %s' -ba %s/SPECS/kea.spec"
    cmd += " -D'_topdir %s'"
    cmd += " --undefine=_debugsource_packages"  # disable creating debugsource package
    cmd = cmd % (pkg_version, pkg_isc_version, rpm_root_path, rpm_root_path)
    execute(cmd, env=env, timeout=60 * 40, check_times=check_times, dry_run=dry_run)

    if 'install' in features:
        # install packages
        execute('rpm -qa | grep isc-kea | xargs sudo rpm -e', check_times=check_times, dry_run=dry_run,
                raise_error=False)
        execute(f'sudo rpm -i {rpm_root_path}/RPMS/{arch.strip()}/*rpm', check_times=check_times, dry_run=dry_run)

        _check_installed_rpm_or_debs(
            ['kea-ctrl-agent.service'],
            "Expected a file at path '/etc/kea/kea-api-user'",
            expect_success_on_start=False,
        )

        # Wait for systemd's rate limit period to pass to avoid "Start request repeated too quickly" after the failed
        # implicit start from the installation of isc-kea-ctrl-agent above.
        time.sleep(10)
        # Reset systemd's rate limit period. Redundant, but just to be safe.
        execute('sudo systemctl reset-failed kea-ctrl-agent.service', raise_error=False)

        execute('echo kea-api-user | sudo tee /etc/kea/kea-api-user > /dev/null')
        execute('sudo touch /etc/kea/kea-api-password')

        # check if kea services can be started
        services_list = ['kea-dhcp4.service', 'kea-dhcp6.service', 'kea-dhcp-ddns.service', 'kea-ctrl-agent.service']
        _check_installed_rpm_or_debs(services_list, '_STARTED Kea')

    execute(f'mv {rpm_root_path}/RPMS/{arch.strip()}/*rpm pkgs', check_times=check_times, dry_run=dry_run)


def _build_deb(system, revision, features, env, check_times, dry_run,
               pkg_version, pkg_isc_version, repo_url):

    _, arch = execute('arch', capture=True)
    if system == 'debian' and revision == '9':
        # debian 9 does not support apt-installing over https, so install proper transport
        install_pkgs('apt-transport-https', env=env, check_times=check_times)

    # See if a .deb package had been previously uploaded.
    _, output = execute("curl -o /dev/null -s -w '%{{http_code}}' {}/dists/kea/Release 2>/dev/null".format(repo_url),
                        capture=True)
    http_code = output.rstrip()
    release_file_exists = http_code == '200'
    if release_file_exists:
        log.info('%s/dists/kea/Release exists.', repo_url)
    else:
        repo_name = 'kea-%s-%s-%s' % (pkg_version.rsplit('.', 1)[0], system, revision)
        log.error('%s/dists/kea/Release does not exist. '
                  'This is usually caused by no package existing in %s. '
                  'You can solve this by uploading any package.'
                  'Continuing, but the build will likely fail.', repo_url, repo_name)

    # try apt update for up to 10 times if there is an error
    for _ in range(10):
        _, out = _apt_update(system, revision, capture=True)
        if 'Bad header data' not in out:
            break
        time.sleep(4)

    # update version, etc
    replace_in_file('kea-src/debian/changelog', '{VERSION}', pkg_version)
    replace_in_file('kea-src/debian/changelog', '{ISC_VERSION}', pkg_isc_version)
    replace_in_file('kea-src/debian/rules', '{ISC_VERSION}', pkg_isc_version)

    services_list = ['isc-kea-dhcp4.isc-kea-dhcp4-server.service', 'isc-kea-dhcp6.isc-kea-dhcp6-server.service',
                     'isc-kea-dhcp-ddns.isc-kea-dhcp-ddns-server.service', 'isc-kea-ctrl-agent.service']

    # debian 9 does not support some fields in systemd unit files so they need to be commented out
    if system == 'debian' and revision == '9':
        for f in services_list:
            for k in ['RuntimeDirectory', 'RuntimeDirectoryPreserve', 'LogsDirectory', 'LogsDirectoryMode',
                      'StateDirectory', 'ConfigurationDirectory']:
                replace_in_file(f, fr'^({k}=.*)', r'# \1')

    # Extract tarballs.
    for path in glob.glob('kea-src/*.tar.xz'):
        # TODO:turn replace into glob.glob(root_dir=...) when Python 3.10+ is available everywhere.
        tar = path.replace('kea-src/', '')
        execute(f'tar -Jxf {tar}', cwd='kea-src', check_times=check_times, dry_run=dry_run)
    tardir = [i for i in glob.glob(f'kea-src/kea-{pkg_version}*') if not i.endswith('.tar.xz')][0]
    execute(f'mv {tardir}/* kea-src/', check_times=check_times, dry_run=dry_run)

    # do deb build
    env['LIBRARY_PATH'] = f'/usr/lib/{arch.strip()}-linux-gnu'
    env['LD_LIBRARY_PATH'] = f'/usr/lib/{arch.strip()}-linux-gnu'
    cmd = ('debuild --preserve-envvar=CCACHE_DIR --preserve-envvar=LD_LIBRARY_PATH --preserve-envvar=LIBRARY_PATH '
           '--prepend-path=/usr/lib/ccache --prepend-path=/usr/local/bin -b -i -us -uc')
    execute(cmd, env=env, cwd='kea-src', timeout=60 * 40, check_times=check_times, dry_run=dry_run)

    if 'install' in features:
        # install packages
        execute('sudo dpkg -i *deb', check_times=check_times, dry_run=dry_run)

        _check_installed_rpm_or_debs(
            ['isc-kea-ctrl-agent.service'],
            "Expected a file at path '/etc/kea/kea-api-user'",
            expect_success_on_start=False,
        )

        # Wait for systemd's rate limit period to pass to avoid "Start request repeated too quickly" after the failed
        # explicit start above.
        time.sleep(10)
        # Reset systemd's rate limit period. Redundant, but just to be safe.
        execute('sudo systemctl reset-failed isc-kea-ctrl-agent.service')

        execute('echo kea-api-user | sudo tee /etc/kea/kea-api-user > /dev/null')
        execute('sudo touch /etc/kea/kea-api-password')

        # check if kea services can be started
        services_list = ['isc-kea-dhcp4-server.service', 'isc-kea-dhcp6-server.service',
                         'isc-kea-dhcp-ddns-server.service', 'isc-kea-ctrl-agent.service']
        _check_installed_rpm_or_debs(services_list, '_STARTED Kea')


def _build_alpine_apk(features, check_times, dry_run, pkg_version, pkg_isc_version):
    _, arch = execute('arch', capture=True)

    execute('sudo rm -rf packages', check_times=check_times, dry_run=dry_run)
    execute('cp kea-src/alpine/* kea-src/', check_times=check_times, dry_run=dry_run)

    # Populate APKBUILD.
    _, kea_hashes = execute('cd kea-src && sha512sum kea-*.tar.xz', capture=True)
    replace_in_file('kea-src/APKBUILD', 'KEA_CHECKSUM', kea_hashes)
    replace_in_file('kea-src/APKBUILD', 'KEA_VERSION', pkg_version)
    replace_in_file('kea-src/APKBUILD', 'KEA_ISC_VERSION', pkg_isc_version[3:])

    # Build packages.
    execute('abuild-keygen -n -a -i', check_times=check_times, dry_run=dry_run)
    execute('abuild -v -r', cwd='kea-src', check_times=check_times, dry_run=dry_run)

    # copy packages from alpine specific dir with produced pkgs to common place
    alpine_repo_dir = os.path.basename(os.getcwd())
    src_dir = f'~/packages/{alpine_repo_dir}/{arch.strip()}'
    execute(f'cp {src_dir}/*.apk kea-pkg', check_times=check_times, dry_run=dry_run)

    if 'install' in features:
        # install packages
        execute('sudo apk add *.apk', cwd='kea-pkg', check_times=check_times, dry_run=dry_run)

        exitcode, _ = execute('sudo rc-service kea-ctrl-agent start', capture=True, raise_error=False)
        assert exitcode == 1
        _, logs = execute('sudo cat /var/log/kea/kea-ctrl-agent.log', capture=True)
        assert "Expected a file at path '/etc/kea/kea-api-user'" in logs

        execute('echo kea-api-user | sudo tee /etc/kea/kea-api-user > /dev/null')
        execute('sudo touch /etc/kea/kea-api-password')

        # check if kea services can be started
        for svc in ['kea-dhcp4', 'kea-dhcp6', 'kea-ctrl-agent', 'kea-dhcp-ddns']:
            execute(f'sudo rc-service {svc} start')
            if svc == 'kea-dhcp-ddns':
                svc = 'kea-ddns'
            logs = ''
            log_path = f'/var/log/kea/{svc}.log'
            for _ in range(10):
                _, logs = execute(f'sudo cat {log_path}', capture=True)
                if '_STARTED Kea' in logs:
                    break
                time.sleep(1)
            if '_STARTED Kea' not in logs:
                print(logs)
                raise UnexpectedError(f'"_STARTED Kea" not in logs for {svc}')


def _build_native_pkg(system, revision, features, tarball_paths, kea_packaging_path, env, check_times, dry_run,
                      ccache_dir, pkg_version, pkg_isc_version, repository_url, pkgs_dir):
    """Build native (RPM or DEB or Alpine APK) packages."""

    # enable ccache if requested
    env = _prepare_ccache_if_needed(system, ccache_dir, env)

    repo_url = _get_full_repo_url(repository_url, system, revision)
    if repo_url is None:
        raise ValueError('repo_url is None')

    # Copy tarball to kea-src.
    execute('sudo rm -rf kea-src', dry_run=dry_run)
    os.mkdir('kea-src')
    if tarball_paths is not None:
        for i in tarball_paths:
            execute(f'cp {i} kea-src/', check_times=check_times, dry_run=dry_run)

    # Copy kea-packaging to kea-src.
    if kea_packaging_path is not None:
        execute(f'cp -r {kea_packaging_path}/* kea-src/', check_times=check_times, dry_run=dry_run)

    if system in ['fedora', 'centos', 'rhel', 'rocky']:
        _build_rpm(system, revision, features, env, check_times, dry_run,
                   pkg_version, pkg_isc_version)

    elif system in ['ubuntu', 'debian']:
        _build_deb(system, revision, features, env, check_times, dry_run,
                   pkg_version, pkg_isc_version, repo_url)

    elif system in ['alpine']:
        _build_alpine_apk(features, check_times, dry_run, pkg_version, pkg_isc_version)

    elif system in ['arch']:
        pass

    else:
        raise NotImplementedError('no implementation for %s' % system)

    if system in ['ubuntu', 'debian']:
        execute(f'mv isc-kea_* {pkgs_dir}')
        execute(f'mv *deb {pkgs_dir}')
    elif system in ['fedora', 'centos', 'rhel', 'rocky']:
        execute('mv pkgs/* %s' % pkgs_dir)
    elif system in ['alpine']:
        # Don't move files if the source and the target locations are the same.
        if pkgs_dir != 'kea-pkg':
            execute('mv kea-pkg/* %s' % pkgs_dir)
    elif system in ['arch']:
        pass
    else:
        raise NotImplementedError('no implementation for %s' % system)


def build_local(features, tarball_paths, kea_packaging_path, check_times, dry_run, ccache_dir, pkg_version,
                pkg_isc_version, repository_url, pkgs_dir, jobs):
    """Prepare local system for Kea development based on requested features.

    If tarball_paths is provided then instead of Kea sources from current directory
    use provided tarball.
    """
    env = os.environ.copy()
    env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

    system, revision = get_system_revision()
    log.info('Building for %s %s', system, revision)

    execute('sudo df -h', dry_run=dry_run)

    if 'native-pkg' in features:
        _build_native_pkg(system, revision, features, tarball_paths, kea_packaging_path, env, check_times, dry_run,
                          ccache_dir, pkg_version, pkg_isc_version, repository_url, pkgs_dir)
    else:
        _build_binaries_and_run_ut(
            system, revision, features, tarball_paths, env, check_times, dry_run, ccache_dir, jobs
        )

    execute('sudo df -h', dry_run=dry_run)


def build_in_vagrant(provider, system, revision, features, leave_system, tarball_paths,
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
        total, passed = ve.run_build_and_test(tarball_paths, jobs, pkg_version, pkg_isc_version, upload, repository_url)
        msg = ' - ' + green('all ok')
    except KeyboardInterrupt as e:
        error = e
        msg = ' - keyboard interrupt'
    except ExecutionError as e:
        error = e
        msg = ' - ' + red(str(e))
    except Exception as e:
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
    if system in ['fedora', 'centos', 'rhel', 'rocky']:
        if upgrade:
            execute('sudo yum remove -y vagrant')
        execute('mkdir -p ~/.hammer-tmp')
        rpm = 'vagrant_%s_x86_64.rpm' % ver
        cmd = 'wget --no-verbose -O ~/.hammer-tmp/%s ' % rpm
        cmd += 'https://releases.hashicorp.com/vagrant/%s/%s' % (ver, rpm)
        execute(cmd)
        execute('sudo rpm -i ~/.hammer-tmp/%s' % rpm)
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
        m = re.search(r'Installed Version: ([\d\.]+)', out, re.I)
        if m is None:
            raise UnexpectedError(r'No match for "Installed Version: ([\d\.\+)"')
        ver = m.group(1)
        vagrant = [int(v) for v in ver.split('.')]
        recommended_vagrant = [int(v) for v in RECOMMENDED_VAGRANT_VERSION.split('.')]
        if vagrant < recommended_vagrant:
            m = re.search(r'Latest Version: ([\d\.]+)', out, re.I)
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
ALL_FEATURES = ['all', 'ccache', 'coverage', 'distcheck', 'docs', 'forge', 'gssapi',
                'install', 'mysql', 'native-pkg', 'netconf', 'perfdhcp',
                'pgsql', 'sanitizers', 'shell', 'tls', 'unittest']


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
    parser.add_argument('-j', '--jobs', default=os.cpu_count(), type=int,
                        help='Number of processes used in compilation. Override make -j default value. Obsolete.')
    parser.add_argument('--kea-packaging-path', metavar='KEA_PACKAGING_PATH',
                        help='Path to the kea-packaging directory when building packages.')
    parser.add_argument('-t', '--from-tarballs', metavar='TARBALL_PATHS', nargs='+', type=pathlib.Path,
                        help='Instead of building sources in current folder use the provided tar.xz tarballs.')
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
    parser.add_argument('--just-configure', action='store_true',
                        help='Whether to prevent installation of packages and only proceed to set them up. '
                             'Only has an effect when preparing system locally, as opposed to inside vagrant.')
    parser.add_argument('--one-package-at-a-time', action='store_true',
                        help='Whether to install packages one at a time instead of all at once.')
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
                                   help="Prepare system from scratch and package it into Vagrant Box. "
                                   "Prepared box can be later deployed to Vagrant Cloud.",
                                   parents=[parent_parser1, parent_parser2])
    parser.add_argument('--repository-url', default=None,
                        help='Repository for 3rd party dependencies and for uploading built packages.')
    parser.add_argument('-u', '--reuse', action='store_true',
                        help='Reuse existing system image, otherwise (default case) if there is any existing then '
                        'destroy it first.')
    parser.add_argument('-k', '--skip-upload', action='store_true',
                        help='Skip uploading prepared box to cloud, otherwise (default case) upload it.')

    args = main_parser.parse_args()

    return args, main_parser


def list_supported_systems():
    """List systems hammer can support (with supported providers)."""
    for system, revision in SYSTEMS.items():
        print(f'{system}:')
        for release, supported in revision.items():
            if not supported:
                continue
            providers = []
            for p in ['lxc', 'virtualbox']:
                k = '%s-%s-%s' % (system, release, p)
                if k in IMAGE_TEMPLATES:
                    providers.append(p)
            providers = ', '.join(providers)
            print(f'  - {release}: {providers}')


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
    # Issue: [B311:blacklist] Standard pseudo-random generators are not suitable for security/cryptographic
    #        purposes.
    # Reason for nosec: It is not used in a security context.
    if random.randint(0, 65535) % 2 == 0:  # nosec B311
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
        # do not include `native-pkg` in `all` if not set explicitly in parameters
        if 'native-pkg' not in set(vars(args)['with']):
            features.discard('native-pkg')

    # if we build native packages then some features are required and some not
    if 'native-pkg' in features:
        features.add('docs')
        features.add('perfdhcp')
        features.add('shell')
        features.add('mysql')
        features.add('pgsql')
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
            log.info('Feature enabled through coin toss: %s', i)
        else:
            features.discard(i)
            log.info('Feature disabled through coin toss: %s', i)

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
    if system not in SYSTEMS:
        msg = "hammer.py error: argument -s/--system: invalid choice: '%s' (choose from '%s')"
        msg = msg % (revision, "', '".join(SYSTEMS.keys()))
        log.error(msg)
        sys.exit(1)
    if revision not in SYSTEMS[system]:
        msg = "hammer.py error: argument -r/--revision: invalid choice: '%s' (choose from '%s')"
        msg = msg % (revision, "', '".join(SYSTEMS[system].keys()))
        log.error(msg)
        sys.exit(1)
    if not SYSTEMS[system][revision]:
        log.warning('%s %s is no longer officially supported. '
                    'The script will continue in a best-effort manner.', system, revision)


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
        prepare_system_local(
            features,
            args.check_times,
            args.ignore_errors_for,
            args.just_configure,
            args.one_package_at_a_time,
        )
        return

    ccache_dir = _prepare_ccache_dir(args.ccache_dir, args.system, args.revision)

    _check_deps_presence()
    prepare_system_in_vagrant(args.provider, args.system, args.revision, features,
                              args.dry_run, args.check_times, args.clean_start,
                              ccache_dir)


def upload_to_repo(args, pkgs_dir):
    # NOTE: note the differences (if any) in system/revision vs args.system/revision
    system, revision = get_system_revision()
    repo_url = _get_full_repo_url(args.repository_url, system, revision)
    if repo_url is None:
        raise ValueError('repo_url is None')
    upload_cmd = 'curl -v --netrc -f'
    log.info('args.system %s, system = %s', args.system, system)

    file_ext = ''
    if system in ['ubuntu', 'debian']:
        upload_cmd += ' -X POST -H "Content-Type: multipart/form-data" --data-binary "@%s" '
        file_ext = 'deb'  # include both '.deb' and '.ddeb' files

    elif system in ['fedora', 'centos', 'rhel', 'rocky']:
        upload_cmd += ' --upload-file %s '
        file_ext = '.rpm'

    elif system == 'alpine':
        upload_cmd += ' --upload-file %s '
        file_ext = ''
        _, arch = execute('arch', raise_error=False, capture=True)
        arch = arch.strip()
        repo_url = urljoin(repo_url, f'{args.pkg_isc_version}/v{revision}/{arch}/')

    upload_cmd += ' ' + repo_url

    for fn in os.listdir(pkgs_dir):
        log.info("debug: fn = %s", fn)
        if file_ext and not fn.endswith(file_ext):
            log.info('File extension "%s" is not supported by upload_to_repo function', file_ext)
            continue
        fp = os.path.join(pkgs_dir, fn)
        log.info("upload cmd: %s", upload_cmd)
        log.info("file path: %s", fp)
        cmd = upload_cmd % fp

        attempts = 4
        while attempts > 0:
            exitcode, output = execute(cmd, capture=True, raise_error=False)
            if exitcode != 0 and '504 Gateway Time-out' in output:
                log.info('Trying again after 8 seconds...')
                attempts -= 1
                time.sleep(8)
            elif exitcode != 0 and "pository does not allow updating assets" in output:
                log.info("Asset already exists in the repository. Skipping upload.")
                break
            elif exitcode != 0:
                raise UnexpectedError('Upload failed: %s' % output)
            else:
                break


def build_cmd(args):
    """Check command args and run the build command."""
    features = _get_features(args)
    log.info('Enabled features: %s', ' '.join(features))
    if args.provider == 'local':
        pkgs_dir = "kea-pkg"
        if os.path.exists(pkgs_dir):
            execute('rm -rf %s' % pkgs_dir)
        os.makedirs(pkgs_dir)

        tarball_paths = None if args.from_tarballs is None else list(map(pathlib.Path.resolve, args.from_tarballs))
        build_local(features, tarball_paths, args.kea_packaging_path, args.check_times, args.dry_run,
                    args.ccache_dir, args.pkg_version, args.pkg_isc_version, args.repository_url, pkgs_dir, args.jobs)
        # NOTE: upload the locally build packages and leave; the rest of the code is vagrant specific
        if args.upload:
            upload_to_repo(args, pkgs_dir)

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
                revisions = SYSTEMS[system].keys()
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
        tarball_paths = list(map(pathlib.Path.resolve, args.from_tarballs))
        result = build_in_vagrant(provider, system, revision, features, args.leave_system, tarball_paths,
                                  args.dry_run, args.quiet, args.clean_start, args.check_times, args.jobs,
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
        features = set(['docs', 'perfdhcp', 'shell', 'mysql', 'pgsql', 'gssapi', 'native-pkg'])

        log.info('Enabled features: %s', ' '.join(features))
        package_box(args.provider, args.system, args.revision, features, args.dry_run, args.check_times, args.reuse,
                    args.skip_upload)

    elif args.command == "prepare-system":
        prepare_system_cmd(args)

    elif args.command == "build":
        os.environ['MESON_NUM_PROCESSES'] = str(args.jobs)
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
