#!/usr/bin/env python3

# Copyright (C) 2018-2026 Internet Systems Consortium, Inc. ("ISC")
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
import argparse
import textwrap
import functools
import grp
import pwd
import getpass
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
        '43': False,
        '44': True,
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
        '26.04': True,
    },
    'debian': {
        '8': False,
        '9': False,
        '10': False,
        '11': False,
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
        '3.24': True,
    },
    'arch': {},
}


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
    meson_version = '1.12.0'
    pyinstaller_version = '6.22.0'

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
            execute(f'sudo /usr/local/share/.venv/bin/pip install pyinstaller=={pyinstaller_version}')
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
    execute('.venv/bin/pip install -r doc/sphinx/src/requirements.in')
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

    # Second cmd attempt.
    cmd2 = None

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
        cmd = 'sudo pkg install --no-repo-update --yes'
        cmd2 = 'sudo pkg install --yes'  # with repo update
    elif system == 'alpine':
        cmd = 'sudo apk add'
    elif system == 'arch':
        cmd = 'sudo pacman -S --needed --noconfirm --overwrite \'*\''
    else:
        raise NotImplementedError('no implementation for %s' % system)

    pkgs_str = ' '.join(pkgs)
    if system == 'freebsd':
        execute(f'sudo pkg fetch --dependencies --yes {pkgs_str}')

    if one_package_at_a_time:
        for p in pkgs:
            exit_code, _ = execute(
                f"{cmd} {p}",
                timeout=timeout,
                env=env,
                check_times=check_times,
                capture=True,
                raise_error=(cmd2 is None),  # if there is no cmd2 to run afterwards, treat failure as error
                attempts=3,
                sleep_time_after_attempt=10,
            )
            if exit_code != 0 and cmd2 is not None:
                execute(
                    f"{cmd2} {p}",
                    timeout=timeout,
                    env=env,
                    check_times=check_times,
                    attempts=3,
                    sleep_time_after_attempt=10,
                )

    else:
        exit_code, _ = execute(
            f"{cmd} {pkgs_str}",
            timeout=timeout,
            env=env,
            check_times=check_times,
            capture=True,
            raise_error=(cmd2 is None),  # if there is no cmd2 to run afterwards, treat failure as error
            attempts=3,
            sleep_time_after_attempt=10,
        )
        if exit_code != 0 and cmd2 is not None:
            execute(
                f"{cmd2} {pkgs_str}",
                timeout=timeout,
                env=env,
                check_times=check_times,
                attempts=3,
                sleep_time_after_attempt=10,
            )


def _get_full_repo_url(repository_url, system, revision):
    if not repository_url:
        return None
    repo_name = 'kea-%s-%s' % (system, revision)
    repo_url = urljoin(repository_url, 'repository')
    repo_url += '/%s/' % repo_name
    return repo_url


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


def _is_libyang_already_installed(version):
    libdirs = [f'{usr}/{lib}' for usr in ['/usr', '/usr/local'] for lib in ['lib', 'lib64']]
    for libdir in libdirs:
        pc_file = f'{libdir}/pkgconfig/libyang.pc'
        if os.path.exists(pc_file):
            with open(pc_file, encoding='utf-8') as file:
                for line in file:
                    if line.rstrip('\n') == f'Version: {version}':
                        log.info(f'libyang is already installed: {pc_file}.')
                        return True
    return False


def _install_libyang_from_sources(version, ignore_errors=False):
    """Install libyang from sources."""
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


def _is_sysrepo_already_installed(version):
    libdirs = [f'{usr}/{lib}' for usr in ['/usr', '/usr/local'] for lib in ['lib', 'lib64']]
    for libdir in libdirs:
        pc_file = f'{libdir}/pkgconfig/sysrepo.pc'
        if os.path.exists(pc_file):
            with open(pc_file, encoding='utf-8') as file:
                for line in file:
                    if line.rstrip('\n') == f'Version: {version}':
                        log.info(f'sysrepo is already installed: {pc_file}.')
                        return True
    return False


def _install_sysrepo_from_sources(version, ignore_errors=False):
    """Install sysrepo from sources."""
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


def _is_libyang_cpp_already_installed(version):
    libdirs = [f'{usr}/{lib}' for usr in ['/usr', '/usr/local'] for lib in ['lib', 'lib64']]
    for libdir in libdirs:
        pc_file = f'{libdir}/pkgconfig/libyang-cpp.pc'
        if os.path.exists(pc_file):
            with open(pc_file, encoding='utf-8') as file:
                for line in file:
                    if line.rstrip('\n') == f'Version: {version}':
                        log.info(f'libyang-cpp is already installed: {pc_file}.')
                        return True
    return False


def _install_libyang_cpp_from_sources(version, ignore_errors=False):
    """Install libyang-cpp from sources."""
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


def _is_sysrepo_cpp_already_installed(version):
    libdirs = [f'{usr}/{lib}' for usr in ['/usr', '/usr/local'] for lib in ['lib', 'lib64']]
    for libdir in libdirs:
        pc_file = f'{libdir}/pkgconfig/sysrepo-cpp.pc'
        if os.path.exists(pc_file):
            with open(pc_file, encoding='utf-8') as file:
                for line in file:
                    if line.rstrip('\n') == f'Version: {version}':
                        log.info(f'sysrepo-cpp is already installed: {pc_file}.')
                        return True
    return False


def _install_sysrepo_cpp_from_sources(version, ignore_errors=False):
    """Install sysrepo-cpp from sources."""
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


def _clean_old_netconf_installations():
    includedirs = [f'{usr}/include' for usr in ['/usr', '/usr/local']]
    libdirs = [f'{usr}/{lib}' for usr in ['/usr', '/usr/local'] for lib in ['lib', 'lib64']]
    paths = (
        [
            '/usr/local/bin/sysrepocfg',
            '/usr/local/bin/sysrepoctl',
            '/usr/local/bin/sysrepo-plugind',
            '/usr/local/bin/yanglint',
            '/usr/local/bin/yangre',
        ]
        + [
            f'{includedir}/{sub}'
            for includedir in includedirs
            for sub in ['libyang', 'libyang-cpp', 'sysrepo', 'sysrepo.h', 'sysrepo-cpp']
        ]
        + [
            f'{libdir}/{sub}'
            for libdir in libdirs
            for sub in [
                'libsysrepo.so*',
                'libsysrepo-cpp.so*',
                'libyang.so*',
                'libyang-cpp.so*',
                'pkgconfig/libyang.pc',
                'pkgconfig/libyang-cpp.pc',
                'pkgconfig/sysrepo.pc',
                'pkgconfig/sysrepo-cpp.pc',
                'sysrepo-plugind',
            ]
        ]
    )
    for p in paths:
        execute(f'sudo rm -rf {p}')

    # Clear shared memory, YANG data, and YANG modules.
    execute('sudo rm -rf /dev/shm/sr_*')
    execute('sudo rm -rf /dev/shm/srsub_*')
    execute('sudo rm -rf /etc/sysrepo')
    execute('sudo rm -rf /usr/local/share/yang/modules')


def _install_netconf_libraries_from_sources(ignore_errors=False):
    libyang_version = '3.13.5'
    sysrepo_version = '3.7.11'
    libyang_cpp_version = '3'
    sysrepo_cpp_version = '3'

    if (
        _is_libyang_already_installed(libyang_version)
        and _is_sysrepo_already_installed(sysrepo_version)
        and _is_libyang_cpp_already_installed(libyang_cpp_version)
        and _is_sysrepo_cpp_already_installed(sysrepo_cpp_version)
    ):
        return

    _clean_old_netconf_installations()

    _install_libyang_from_sources(libyang_version, ignore_errors)
    _install_sysrepo_from_sources(sysrepo_version, ignore_errors)
    _install_libyang_cpp_from_sources(libyang_cpp_version, ignore_errors)
    _install_sysrepo_cpp_from_sources(sysrepo_cpp_version, ignore_errors)


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

    # If requested, configure TLS. Except for MariaDB >= 11.8 which introduces zero-config TLS.
    mariadbd_version = None
    using_mariadb = None
    zero_conf_tls = False
    if system in ['alpine', 'freebsd']:
        using_mariadb = True
    else:
        _, output = execute('sudo systemctl status mysql', capture=True, raise_error=False)
        using_mariadb = 'mariadb.service' in output
    if using_mariadb:
        return_code, output = execute('mariadbd --version', capture=True, raise_error=False)
        if return_code == 0:
            matches = re.search(r'Ver ([0-9]+\.[0-9]+)', output)
            if matches is None:
                log.error('Could not detect version of mariadbd')
                sys.exit(1)
            mariadbd_version = matches.group(1)
            zero_conf_tls = float('11.8') <= float(mariadbd_version)
    log.info(
        'using_mariadb: %s, mariadbd_version: %s, zero_conf_tls: %s', using_mariadb, mariadbd_version, zero_conf_tls
    )
    if not zero_conf_tls:
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
    cmd = """
      sudo mysql -u root -e "
        CREATE DATABASE keatest;
        CREATE USER 'keatest'@'localhost' IDENTIFIED BY 'keatest';
        CREATE USER 'keatest_readonly'@'localhost' IDENTIFIED BY 'keatest';
    """
    if 'tls' in features:
        cmd += "CREATE USER 'keatest_secure'@'localhost' IDENTIFIED BY 'keatest';\n"
    cmd += "GRANT ALL ON keatest.* TO 'keatest'@'localhost';\n"
    cmd += "GRANT SELECT ON keatest.* TO 'keatest_readonly'@'localhost';\n"
    cmd += '"'
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
        cmd = """
          sudo mysql -u root -e "
            CREATE DATABASE keadb;
            CREATE USER 'keauser'@'localhost' IDENTIFIED BY 'keapass';
            GRANT ALL ON keadb.* TO 'keauser'@'localhost';
          "
        """
        execute(cmd)

    if system == 'debian' and revision == '9':
        log.info('FIX FOR ISSUE kea#389: %s %s', system, revision)
        cmd = """
          sudo mysql -u root -e '
            use keatest;
            set global innodb_large_prefix=on;
            set global innodb_file_format=Barracuda;
            set global innodb_file_per_table=true;
            set global innodb_default_row_format=dynamic;
          '
        """
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

    local_timezone = _get_local_timezone()

    cmd = f"""
      sudo -u postgres psql postgres \
        -c "DROP DATABASE IF EXISTS keatest;" \
        -c "DROP USER IF EXISTS keatest;" \
        -c "DROP USER IF EXISTS keatest_readonly;" \
        -c "CREATE USER keatest WITH PASSWORD 'keatest';" \
        -c "CREATE USER keatest_readonly WITH PASSWORD 'keatest';" \
        -c "CREATE DATABASE keatest;" \
        -c "GRANT ALL PRIVILEGES ON DATABASE keatest TO keatest;" \
        -c "ALTER DATABASE keatest SET TIMEZONE='{local_timezone}';"
    """
    execute(cmd, cwd='/tmp')

    # This is needed for postgres >= 15
    cmd = "sudo -u postgres psql -U postgres -d keatest -c 'GRANT ALL PRIVILEGES ON SCHEMA public TO keatest'"
    execute(cmd, cwd='/tmp')

    cmd = """
      sudo -u postgres env PGPASSWORD=keatest psql -U keatest keatest \
        -c 'ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT SELECT ON TABLES TO keatest_readonly'
    """
    execute(cmd, cwd='/tmp')

    if 'forge' in features:
        cmd = """
          sudo -u postgres psql postgres \
            -c "DROP DATABASE IF EXISTS keadb;" \
            -c "DROP USER IF EXISTS keauser;" \
            -c "CREATE USER keauser WITH PASSWORD 'keapass';" \
            -c "CREATE DATABASE keadb;" \
            -c "GRANT ALL PRIVILEGES ON DATABASE keadb TO keauser;"
        """
        execute(cmd, cwd='/tmp')

        # This is needed for postgres >= 15
        cmd = "sudo -u postgres psql -U postgres -d keadb -c 'GRANT ALL PRIVILEGES ON SCHEMA public TO keauser'"
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
        packages.extend(['bison', 'doxygen', 'flex'])

    if 'unittest' in features:
        packages.append('valgrind')

    # prepare fedora
    if system == 'fedora':
        packages.extend(['boost-devel', 'gcc-c++', 'openssl-devel', 'log4cplus-devel', 'libpcap-devel'])
        deferred_functions.append(install_meson)

        if 'native-pkg' in features:
            packages.extend(['rpm-build', 'python3-devel'])

        if 'docs' in features:
            packages.extend(
                [
                    'python3-sphinx',
                    'python3-sphinx_rtd_theme',
                    'texlive',
                    'texlive-collection-latexextra',
                    'texlive-times',
                ]
            )

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
        if int(revision) < 9:
            packages.remove('doxygen')

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
                'libboost-all-dev',
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
            packages.extend(
                [
                    'python3-sphinx',
                    'python3-sphinx-rtd-theme',
                    'python3-sphinxcontrib.applehelp',
                    'python3-sphinxcontrib.devhelp',
                    'python3-sphinxcontrib.htmlhelp',
                    'python3-sphinxcontrib.qthelp',
                    'python3-sphinxcontrib.serializinghtml',
                    'texlive',
                    'texlive-latex-extra',
                    'tex-gyre',
                ]
            )

        if 'unittest' in features:
            packages.append('googletest')

        if 'native-pkg' in features:
            packages.extend(['build-essential', 'fakeroot', 'devscripts'])
            packages.extend(['debhelper', 'python3-dev'])
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
            packages.extend(['cmake', 'git', 'libpcre2-dev', 'make'])

        install_pkgs(packages, env=env, timeout=240, check_times=check_times)

    # prepare debian
    elif system == 'debian':
        _apt_update(system, revision, env=env, check_times=check_times, attempts=3, sleep_time_after_attempt=10)

        packages.extend(
            [
                'gcc',
                'g++',
                'gnupg',
                'libboost-all-dev',
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
            packages.extend(
                [
                    'graphviz',
                    'python3-sphinx',
                    'python3-sphinx-rtd-theme',
                    'tex-gyre',
                    'texlive',
                    'texlive-latex-extra',
                ]
            )
            if int(revision) >= 12:
                packages.extend(
                    [
                        'python3-sphinxcontrib.applehelp',
                        'python3-sphinxcontrib.devhelp',
                        'python3-sphinxcontrib.htmlhelp',
                        'python3-sphinxcontrib.qthelp',
                        'python3-sphinxcontrib.serializinghtml',
                    ]
                )

        if 'unittest' in features:
            packages.append('googletest')

        if 'netconf' in features:
            packages.extend(['cmake', 'git', 'libpcre2-dev', 'make'])

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
        packages.append('pcre2')  # dependency of git
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

        # Try to use full path for meson install due to some distros (i.e. rocky)
        # do not have /usr/local/bin in secure_path. As result 'meson' is not found with sudo.
        res, meson_cmd = execute('command -v meson', capture=True, quiet=True, raise_error=False)
        if res != 0:
            meson_cmd = 'meson'
        else:
            meson_cmd = meson_cmd.rstrip()

        execute(f'sudo {meson_cmd} install -C build', timeout=2 * 60,
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
               pkg_version, pkg_isc_version, jobs):

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

    services_list = ['kea-dhcp4.service', 'kea-dhcp6.service', 'kea-dhcp-ddns.service']

    # centos/rhel 7 does not support some fields in systemd unit files so they need to be commented out
    if system == 'centos' and revision == '7':
        for f in services_list:
            for k in ['RuntimeDirectory', 'RuntimeDirectoryPreserve', 'LogsDirectory', 'LogsDirectoryMode',
                      'StateDirectory', 'ConfigurationDirectory']:
                replace_in_file(f, fr'^({k}=.*)', r'# \1')

    # do rpm build
    cmd = (
        f'rpmbuild -ba {rpm_root_path}/SPECS/kea.spec'
        f" --define '_topdir {rpm_root_path}'"
        f" --define 'kea_version {pkg_version}'"
        f" --define 'isc_version {pkg_isc_version}'"
        f" --define 'meson_job_count {jobs}'"
        ' --undefine=_debugsource_packages'  # disable creating debugsource package
    )
    execute(cmd, env=env, timeout=60 * 40, check_times=check_times, dry_run=dry_run)

    if 'install' in features:
        # install packages
        execute('rpm -qa | grep isc-kea | xargs sudo rpm -e', check_times=check_times, dry_run=dry_run,
                raise_error=False)
        execute(f'sudo rpm -i {rpm_root_path}/RPMS/{arch.strip()}/*rpm', check_times=check_times, dry_run=dry_run)

        # check if kea services can be started
        services_list = ['kea-dhcp4.service', 'kea-dhcp6.service', 'kea-dhcp-ddns.service']
        _check_installed_rpm_or_debs(services_list, '_STARTED Kea')

    execute(f'mv {rpm_root_path}/RPMS/{arch.strip()}/*rpm pkgs', check_times=check_times, dry_run=dry_run)


def _build_deb(system, revision, features, env, check_times, dry_run,
               pkg_version, pkg_isc_version, repo_url, jobs):

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
                     'isc-kea-dhcp-ddns.isc-kea-dhcp-ddns-server.service']

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
    env['MESON_JOB_COUNT'] = str(jobs)
    cmd = (
        'debuild'
        ' --preserve-envvar=CCACHE_DIR'
        ' --preserve-envvar=LD_LIBRARY_PATH'
        ' --preserve-envvar=LIBRARY_PATH'
        ' --preserve-envvar=MESON_JOB_COUNT'
        ' --prepend-path=/usr/lib/ccache'
        ' --prepend-path=/usr/local/bin'
        ' -b -i -uc -us'
    )
    execute(cmd, env=env, cwd='kea-src', timeout=60 * 40, check_times=check_times, dry_run=dry_run)

    if 'install' in features:
        # install packages
        execute('sudo dpkg -i *deb', check_times=check_times, dry_run=dry_run)

        # check if kea services can be started
        services_list = ['isc-kea-dhcp4-server.service', 'isc-kea-dhcp6-server.service',
                         'isc-kea-dhcp-ddns-server.service']
        _check_installed_rpm_or_debs(services_list, '_STARTED Kea')


def _build_alpine_apk(features, check_times, dry_run, pkg_version, pkg_isc_version, jobs):
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
    env = os.environ.copy()
    env['MESON_JOB_COUNT'] = str(jobs)
    execute('abuild -r -v', cwd='kea-src', check_times=check_times, dry_run=dry_run, env=env)

    # copy packages from alpine specific dir with produced pkgs to common place
    alpine_repo_dir = os.path.basename(os.getcwd())
    src_dir = f'~/packages/{alpine_repo_dir}/{arch.strip()}'
    execute(f'cp {src_dir}/*.apk kea-pkg', check_times=check_times, dry_run=dry_run)

    if 'install' in features:
        # install packages
        execute('sudo apk add *.apk', cwd='kea-pkg', check_times=check_times, dry_run=dry_run)

        # check if kea services can be started
        for svc in ['kea-dhcp4', 'kea-dhcp6', 'kea-dhcp-ddns']:
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
                      ccache_dir, pkg_version, pkg_isc_version, repository_url, pkgs_dir, jobs):
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
                   pkg_version, pkg_isc_version, jobs)

    elif system in ['ubuntu', 'debian']:
        _build_deb(system, revision, features, env, check_times, dry_run,
                   pkg_version, pkg_isc_version, repo_url, jobs)

    elif system in ['alpine']:
        _build_alpine_apk(features, check_times, dry_run, pkg_version, pkg_isc_version, jobs)

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
                          ccache_dir, pkg_version, pkg_isc_version, repository_url, pkgs_dir, jobs)
    else:
        _build_binaries_and_run_ut(
            system, revision, features, tarball_paths, env, check_times, dry_run, ccache_dir, jobs
        )

    execute('sudo df -h', dry_run=dry_run)


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
        fl("Basic functionality provided by Hammer is preparing building environment and "
           "performing actual build and running unit tests locally, in current system. "
           "This can be achieved by running the command:"),
        "\n  ./hammer.py build\n",
        fl("The scope of the process can be defined using --with (-w) and --without (-x) options. "
           "By default the build command will build Kea with documentation, install it locally "
           "and run unit tests."),
        "To exclude installation and generating docs do:",
        "\n  ./hammer.py build -x install docs\n",
        fl("The whole list of available features is: %s." % ", ".join(ALL_FEATURES)),
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

    parent_parser = argparse.ArgumentParser(add_help=False)
    hlp = "Enable features. Separate them by space or comma. List of available features: %s. Default is '%s'."
    hlp = hlp % (", ".join(ALL_FEATURES), ' '.join(DEFAULT_FEATURES))
    parent_parser.add_argument('-w', '--with', metavar='FEATURE', nargs='+', default=set(),
                               action=CollectCommaSeparatedArgsAction, help=hlp)
    hlp = "Disable features. Separate them by space or comma. List of available features: %s. Default is ''."
    hlp = hlp % ", ".join(ALL_FEATURES)
    parent_parser.add_argument('-x', '--without', metavar='FEATURE', nargs='+', default=set(),
                               action=CollectCommaSeparatedArgsAction, help=hlp)
    parent_parser.add_argument('--with-randomly', metavar='FEATURE', nargs='+', default=set(),
                               action=CollectCommaSeparatedArgsAction, help=hlp)
    parent_parser.add_argument('--ignore-errors-for', metavar='FEATURE', nargs='+', default=set(),
                               action=CollectCommaSeparatedArgsAction, help=hlp)
    parent_parser.add_argument('-i', '--check-times', action='store_true',
                               help='Do not allow executing commands infinitely.')
    parent_parser.add_argument('-n', '--dry-run', action='store_true', help='Print only what would be done.')

    parser = subparsers.add_parser('supported-systems',
                                   help="List system supported by Hammer for doing Kea development.")
    parser = subparsers.add_parser('build', help="Prepare system and run Kea build in indicated system.",
                                   parents=[parent_parser])
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
                                   parents=[parent_parser])
    parser.add_argument('--just-configure', action='store_true',
                        help='Whether to prevent installation of packages and only proceed to set them up.')
    parser.add_argument('--one-package-at-a-time', action='store_true',
                        help='Whether to install packages one at a time instead of all at once.')
    parser.add_argument('--ccache-dir', default=None,
                        help='Path to CCache directory on host system.')
    parser.add_argument('--repository-url', default=None,
                        help='Repository for 3rd party dependencies and for uploading built packages.')

    args = main_parser.parse_args()

    return args, main_parser


def list_supported_systems():
    """List systems hammer can support."""
    for system, revisions in sorted(SYSTEMS.items()):
        if any(r for r in revisions.values()):
            print(f'{system}:')
        for r in (revision for revision, supported in revisions.items() if supported):
            print(f'  - {r}')


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


def prepare_system_cmd(args):
    """Check command args and run the prepare-system command."""
    features = _get_features(args)
    log.info('Enabled features: %s', ' '.join(features))

    prepare_system_local(
        features,
        args.check_times,
        args.ignore_errors_for,
        args.just_configure,
        args.one_package_at_a_time,
    )


def upload_to_repo(args, pkgs_dir):
    system, revision = get_system_revision()
    repo_url = _get_full_repo_url(args.repository_url, system, revision)
    if repo_url is None:
        raise ValueError('repo_url is None')
    upload_cmd = 'curl -v --netrc -f'
    log.info('system = %s', system)

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
    pkgs_dir = "kea-pkg"
    if os.path.exists(pkgs_dir):
        execute('rm -rf %s' % pkgs_dir)
    os.makedirs(pkgs_dir)

    tarball_paths = None if args.from_tarballs is None else list(map(pathlib.Path.resolve, args.from_tarballs))
    build_local(features, tarball_paths, args.kea_packaging_path, args.check_times, args.dry_run,
                args.ccache_dir, args.pkg_version, args.pkg_isc_version, args.repository_url, pkgs_dir, args.jobs)
    if args.upload:
        upload_to_repo(args, pkgs_dir)


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

    elif args.command == "prepare-system":
        prepare_system_cmd(args)

    elif args.command == "build":
        build_cmd(args)

    else:
        parser.print_help()


if __name__ == '__main__':
    main()
