#!/usr/bin/env python3

# Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
"""Hammer - Kea development environment management tool."""

from __future__ import print_function
import os
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
import xml.etree.ElementTree as ET

# TODO:
# - add docker provider
#   https://developer.fedoraproject.org/tools/docker/docker-installation.html
# - improve building from tarball
# - improve native-pkg builds
# - avoid using network if possible (e.g. check first if pkgs are installed)


SYSTEMS = {
    'fedora': ['27', '28', '29'],
    'centos': ['7'],
    'rhel': ['8'],
    'ubuntu': ['16.04', '18.04', '18.10'],
    'debian': ['8', '9'],
    'freebsd': ['11.2', '12.0'],
}

# pylint: disable=C0326
IMAGE_TEMPLATES = {
    'fedora-27-lxc':           {'bare': 'lxc-fedora-27',               'kea': 'godfryd/kea-fedora-27'},
    'fedora-27-virtualbox':    {'bare': 'generic/fedora27',            'kea': 'godfryd/kea-fedora-27'},
    'fedora-28-lxc':           {'bare': 'lxc-fedora-28',               'kea': 'godfryd/kea-fedora-28'},
    'fedora-28-virtualbox':    {'bare': 'generic/fedora28',            'kea': 'godfryd/kea-fedora-28'},
    'fedora-29-lxc':           {'bare': 'godfryd/lxc-fedora-29',       'kea': 'godfryd/kea-fedora-29'},
    'fedora-29-virtualbox':    {'bare': 'generic/fedora29',            'kea': 'godfryd/kea-fedora-29'},
    'centos-7-lxc':            {'bare': 'godfryd/lxc-centos-7',        'kea': 'godfryd/kea-centos-7'},
    'centos-7-virtualbox':     {'bare': 'generic/centos7',             'kea': 'godfryd/kea-centos-7'},
    'rhel-8-virtualbox':       {'bare': 'generic/rhel8',               'kea': 'generic/rhel8'},
    'ubuntu-16.04-lxc':        {'bare': 'godfryd/lxc-ubuntu-16.04',    'kea': 'godfryd/kea-ubuntu-16.04'},
    'ubuntu-16.04-virtualbox': {'bare': 'ubuntu/xenial64',             'kea': 'godfryd/kea-ubuntu-16.04'},
    'ubuntu-18.04-lxc':        {'bare': 'godfryd/lxc-ubuntu-18.04',    'kea': 'godfryd/kea-ubuntu-18.04'},
    'ubuntu-18.04-virtualbox': {'bare': 'ubuntu/bionic64',             'kea': 'godfryd/kea-ubuntu-18.04'},
    'ubuntu-18.10-lxc':        {'bare': 'godfryd/lxc-ubuntu-18.10',    'kea': 'godfryd/kea-ubuntu-18.10'},
    'ubuntu-18.10-virtualbox': {'bare': 'ubuntu/cosmic64',             'kea': 'godfryd/kea-ubuntu-18.10'},
    'debian-8-lxc':            {'bare': 'godfryd/lxc-debian-8',        'kea': 'godfryd/kea-debian-8'},
    'debian-8-virtualbox':     {'bare': 'debian/jessie64',             'kea': 'godfryd/kea-debian-8'},
    'debian-9-lxc':            {'bare': 'godfryd/lxc-debian-9',        'kea': 'godfryd/kea-debian-9'},
    'debian-9-virtualbox':     {'bare': 'debian/stretch64',            'kea': 'godfryd/kea-debian-9'},
    'freebsd-11.2-virtualbox': {'bare': 'generic/freebsd11',           'kea': 'godfryd/kea-freebsd-11.2'},
    'freebsd-12.0-virtualbox': {'bare': 'generic/freebsd12',           'kea': 'godfryd/kea-freebsd-12.0'},
}

LXC_VAGRANTFILE_TPL = """# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.hostname = "{name}"

  config.vm.box = "{image_tpl}"

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

Vagrant.configure("2") do |config|
  config.vm.hostname = "{name}"

  config.vm.box = "{image_tpl}"

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
        system, revision, _ = platform.dist()  # pylit: disable=deprecated-method
        if system == 'debian':
            revision = revision[0]
        elif system == 'redhat':
            system = 'rhel'
            revision = revision[0]
        elif system == 'centos':
            revision = revision[0]
    elif system == 'FreeBSD':
        system = system.lower()
        revision = platform.release()
    return system.lower(), revision


class ExecutionError(Exception):
    """Exception thrown when execution encountered an error."""
    pass


def execute(cmd, timeout=60, cwd=None, env=None, raise_error=True, dry_run=False, log_file_path=None,
            quiet=False, check_times=False, capture=False, interactive=False, attempts=1,
            sleep_time_after_attempt=None):
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
    :param int attemts: number of attempts to run the command if it fails
    :param int sleep_time_after_attempt: number of seconds to sleep before taking next attempt
    """
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
            t1 = time.time()
            # repeat until process is running or timeout not occured
            while p.poll() is None and (timeout is None or t1 - t0 < timeout):
                line = p.stdout.readline()
                if line:
                    line_decoded = line.decode(errors='ignore').rstrip() + '\r'
                    if not quiet:
                        print(line_decoded)
                    if capture:
                        output += line_decoded
                    if log_file_path:
                        log_file.write(line)
                t1 = time.time()

            # If no exitcode yet, ie. process is still running then it means that timeout occured.
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
        raise ExecutionError("The command return non-zero exitcode %s, cmd: '%s'" % (exitcode, cmd))

    if capture:
        return exitcode, output
    return exitcode


def install_pkgs(pkgs, timeout=60, env=None, check_times=False):
    """Install native packages in a system.

    :param dict pkgs: specifies a list of packages to be installed
    :param int timeout: timeout in number of seconds, after that time the command
                        is terminated but only if check_times is True
    :param dict env: dictionary with environment variables (optional)
    :param bool check_times: specifies if timeouts should be enabled (optional)
    """
    system, revision = get_system_revision()

    if system in ['centos', 'rhel'] and revision == '7':
        # skip_missing_names_on_install used to detect case when one packet is not found and no error is returned
        # but we want an error
        cmd = 'sudo yum install -y --setopt=skip_missing_names_on_install=False'
    elif system == 'fedora' or (system in ['centos', 'rhel'] and revision == '8'):
        cmd = 'sudo dnf -y install'
    elif system in ['debian', 'ubuntu']:
        if not env:
            env = os.environ.copy()
        env['DEBIAN_FRONTEND'] = 'noninteractive'
        cmd = 'sudo apt install --no-install-recommends -y'
    elif system == 'freebsd':
        cmd = 'sudo pkg install -y'

    if isinstance(pkgs, list):
        pkgs = ' '.join(pkgs)

    cmd += ' ' + pkgs

    execute(cmd, timeout=timeout, env=env, check_times=check_times, attempts=3, sleep_time_after_attempt=10)


class VagrantEnv(object):
    """Helper class that makes interacting with Vagrant easier.

    It creates Vagrantfile according to specified system. It exposes basic Vagrant functions
    like up, upload, destro, ssh. It also provides more complex function for preparing system
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

        if provider == "virtualbox":
            vagrantfile_tpl = VBOX_VAGRANTFILE_TPL
        elif provider == "lxc":
            vagrantfile_tpl = LXC_VAGRANTFILE_TPL

        key = "%s-%s-%s" % (system, revision, provider)
        image_tpl = IMAGE_TEMPLATES[key][image_template_variant]
        self.repo_dir = os.getcwd()

        sys_dir = "%s-%s" % (system, revision)
        if provider == "virtualbox":
            self.vagrant_dir = os.path.join(self.repo_dir, 'hammer', sys_dir, 'vbox')
        elif provider == "lxc":
            self.vagrant_dir = os.path.join(self.repo_dir, 'hammer', sys_dir, 'lxc')

        if dry_run:
            return

        if not os.path.exists(self.vagrant_dir):
            os.makedirs(self.vagrant_dir)

        vagrantfile_path = os.path.join(self.vagrant_dir, "Vagrantfile")

        if os.path.exists(vagrantfile_path):
            # TODO: destroy any existing VM
            pass

        crc = binascii.crc32(self.vagrant_dir.encode())
        self.name = "hmr-%s-%s-kea-srv-%08d" % (system, revision.replace('.', '-'), crc)

        if ccache_dir is None:
            ccache_dir = '/'
            self.ccache_enabled = False
        else:
            self.ccache_enabled = True

        vagrantfile = vagrantfile_tpl.format(image_tpl=image_tpl,
                                             name=self.name,
                                             ccache_dir=ccache_dir)

        with open(vagrantfile_path, "w") as f:
            f.write(vagrantfile)

        log.info('Prepared vagrant system %s in %s', self.name, self.vagrant_dir)

    def up(self):
        """Do Vagrant up."""
        execute("vagrant box update", cwd=self.vagrant_dir, timeout=20 * 60, dry_run=self.dry_run)
        execute("vagrant up --no-provision --provider %s" % self.provider,
                cwd=self.vagrant_dir, timeout=15 * 60, dry_run=self.dry_run)

    def package(self):
        """Package Vagrant system into Vagrant box."""

        if self.provider == 'virtualbox':
            cmd = "vagrant package --output kea-%s-%s.box" % (self.system, self.revision)
            execute(cmd, cwd=self.vagrant_dir, timeout=4 * 60, dry_run=self.dry_run)

        elif self.provider == 'lxc':
            execute('vagrant halt', cwd=self.vagrant_dir, dry_run=self.dry_run, raise_error=False)

            box_path = os.path.join(self.vagrant_dir, 'kea-%s-%s.box' % (self.system, self.revision))
            if os.path.exists(box_path):
                os.unlink(box_path)

            lxc_box_dir = os.path.join(self.vagrant_dir, 'lxc-box')
            if os.path.exists(lxc_box_dir):
                execute('sudo rm -rf %s' % lxc_box_dir)
            os.mkdir(lxc_box_dir)
            lxc_container_path = os.path.join('/var/lib/lxc', self.name)
            execute('sudo bash -c \'echo "ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEA6NF8ia'
                    'llvQVp22WDkTkyrtvp9eWW6A8YVr+kz4TjGYe7gHzIw+niNltGEFHzD8+v1I2YJ'
                    '6oXevct1YeS0o9HZyN1Q9qgCgzUFtdOKLv6IedplqoPkcmF0aYet2PkEDo3MlTB'
                    'ckFXPITAMzF8dJSIFo9D8HfdOV0IAdx4O7PtixWKn5y2hMNG0zQPyUecp4pzC6k'
                    'ivAIhyfHilFR61RGL+GPXQ2MWZWFYbAGjyiYJnAmCP3NOTd0jMZEnDkbUvxhMmB'
                    'YSdETk1rRgm+R4LOzFUGaHqHDLKLX+FIPKcF96hrucXzcWyLbIbEgE98OHlnVYC'
                    'zRdK8jlqm8tehUc9c9WhQ== vagrant insecure public key"'
                    '> %s/rootfs/home/vagrant/.ssh/authorized_keys\'' % lxc_container_path)
            cmd = 'sudo bash -c "'
            cmd += 'cd %s '
            cmd += '&& tar --numeric-owner --anchored --exclude=./rootfs/dev/log -czf %s/rootfs.tar.gz ./rootfs/*'
            cmd += '"'
            execute(cmd % (lxc_container_path, lxc_box_dir))
            execute('sudo cp %s/config %s/lxc-config' % (lxc_container_path, lxc_box_dir))
            execute('sudo chown `id -un`:`id -gn` *', cwd=lxc_box_dir)
            with open(os.path.join(lxc_box_dir, 'metadata.json'), 'w') as f:
                now = datetime.datetime.now()
                f.write('{\n')
                f.write('  "provider": "lxc",\n')
                f.write('  "version":  "1.0.0",\n')
                f.write('  "built-on": "%s"\n' % now.strftime('%c'))
                f.write('}\n')

            execute('tar -czf %s ./*' % box_path, cwd=lxc_box_dir)
            execute('sudo rm -rf %s' % lxc_box_dir)

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

    def run_build_and_test(self, tarball_path, jobs):
        """Run build and unit tests inside Vagrant system."""
        if self.dry_run:
            return 0, 0

        # prepare tarball if needed and upload it to vagrant system
        if not tarball_path:
            name_ver = 'kea-1.5.0'
            cmd = 'tar --transform "flags=r;s|^|%s/|" --exclude hammer ' % name_ver
            cmd += ' --exclude "*~" --exclude .git --exclude .libs '
            cmd += ' --exclude .deps --exclude \'*.o\'  --exclude \'*.lo\' '
            cmd += ' -zcf /tmp/%s.tar.gz .' % name_ver
            execute(cmd)
            tarball_path = '/tmp/%s.tar.gz' % name_ver
        self.upload(tarball_path)

        log_file_path = os.path.join(self.vagrant_dir, 'build.log')
        log.info('Build log file stored to %s', log_file_path)

        t0 = time.time()

        # run build command
        bld_cmd = "%s hammer.py build -p local -t %s.tar.gz -j %d" % (self.python, name_ver, jobs)
        if self.features_arg:
            bld_cmd += ' ' + self.features_arg
        if self.nofeatures_arg:
            bld_cmd += ' ' + self.nofeatures_arg
        if self.check_times:
            bld_cmd += ' -i'
        if self.ccache_enabled:
            bld_cmd += ' --ccache-dir /ccache'
        timeout = _calculate_build_timeout(self.features) + 5 * 60
        self.execute(bld_cmd, timeout=timeout, log_file_path=log_file_path, quiet=self.quiet)  # timeout: 40 minutes

        ssh_cfg_path = self.dump_ssh_config()

        if 'native-pkg' in self.features:
            execute('scp -F %s -r default:/home/vagrant/rpm-root/RPMS/x86_64/ .' % ssh_cfg_path)

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
        except:  # pylint: disable=bare-except
            log.exception('ignored issue with parsing unit test results')

        return total, passed

    def destroy(self):
        """Remove the VM completely."""
        cmd = 'vagrant destroy --force'
        execute(cmd, cwd=self.vagrant_dir, timeout=3 * 60, dry_run=self.dry_run)  # timeout: 3 minutes

    def ssh(self):
        """Open interactive session to the VM."""
        execute('vagrant ssh', cwd=self.vagrant_dir, timeout=None, dry_run=self.dry_run, interactive=True)

    def dump_ssh_config(self):
        """Dump ssh config that allows getting into Vagrant system via SSH."""
        ssh_cfg_path = os.path.join(self.vagrant_dir, 'ssh.cfg')
        execute('vagrant ssh-config > %s' % ssh_cfg_path, cwd=self.vagrant_dir)
        return ssh_cfg_path

    def execute(self, cmd, timeout=None, raise_error=True, log_file_path=None, quiet=False, env=None):
        """Execute provided command inside Vagrant system."""
        if not env:
            env = os.environ.copy()
        env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

        return execute('vagrant ssh -c "%s"' % cmd, env=env, cwd=self.vagrant_dir, timeout=timeout,
                       raise_error=raise_error, dry_run=self.dry_run, log_file_path=log_file_path,
                       quiet=quiet, check_times=self.check_times)

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

        # select proper python version for running Hammer inside Vagrant system
        if (self.system == 'centos' and self.revision == '7' or
            (self.system == 'debian' and self.revision == '8' and self.provider != 'lxc')):
            self.python = 'python'
        elif self.system == 'freebsd':
            self.python = 'python3.6'
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

        # upload Hammer to Vagrant system
        hmr_py_path = os.path.join(self.repo_dir, 'hammer.py')
        self.upload(hmr_py_path)

        log_file_path = os.path.join(self.vagrant_dir, 'prepare.log')
        log.info('Prepare log file stored to %s', log_file_path)

        # run prepare-system inside Vagrant system
        cmd = "{python} hammer.py prepare-system -p local {features} {nofeatures} {check_times} {ccache}"
        cmd = cmd.format(features=self.features_arg,
                         nofeatures=self.nofeatures_arg,
                         python=self.python,
                         check_times='-i' if self.check_times else '',
                         ccache='--ccache-dir /ccache' if self.ccache_enabled else '')
        self.execute(cmd, timeout=40 * 60, log_file_path=log_file_path, quiet=self.quiet)


def _install_gtest_sources():
    """Install gtest sources."""
    # download gtest sources only if it is not present as native package
    if not os.path.exists('/usr/src/googletest-release-1.8.0/googletest'):
        cmd = 'wget --no-verbose -O /tmp/gtest.tar.gz '
        cmd += 'https://github.com/google/googletest/archive/release-1.8.0.tar.gz'
        execute(cmd)
        execute('sudo tar -C /usr/src -zxf /tmp/gtest.tar.gz')
        os.unlink('/tmp/gtest.tar.gz')


def _configure_mysql(system, revision, features):
    """Configure MySQL database."""
    if system in ['fedora', 'centos']:
        execute('sudo systemctl enable mariadb.service')
        execute('sudo systemctl start mariadb.service')
        time.sleep(5)

    if system == 'freebsd':
        cmd = "echo 'SET PASSWORD = \"\";' "
        cmd += "| sudo mysql -u root --password=\"$(sudo cat /root/.mysql_secret | grep -v '#')\" --connect-expired-password"
        execute(cmd, raise_error=False)

    cmd = "echo 'DROP DATABASE IF EXISTS keatest;' | sudo mysql -u root"
    execute(cmd)
    cmd = "echo 'DROP USER 'keatest'@'localhost';' | sudo mysql -u root"
    execute(cmd, raise_error=False)
    cmd = "echo 'DROP USER 'keatest_readonly'@'localhost';' | sudo mysql -u root"
    execute(cmd, raise_error=False)
    cmd = "bash -c \"cat <<EOF | sudo mysql -u root\n"
    cmd += "CREATE DATABASE keatest;\n"
    cmd += "CREATE USER 'keatest'@'localhost' IDENTIFIED BY 'keatest';\n"
    cmd += "CREATE USER 'keatest_readonly'@'localhost' IDENTIFIED BY 'keatest';\n"
    cmd += "GRANT ALL ON keatest.* TO 'keatest'@'localhost';\n"
    cmd += "GRANT SELECT ON keatest.* TO 'keatest_readonly'@'localhost';\n"
    cmd += "EOF\n\""
    execute(cmd)

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

    log.info("FIX FOR ISSUE: %s %s", system, revision)
    if system == 'debian' and revision == '9':
        log.info("FIX FOR ISSUE 2: %s %s", system, revision)
        # fix for issue: https://gitlab.isc.org/isc-projects/kea/issues/389
        cmd = "bash -c \"cat <<EOF | sudo mysql -u root\n"
        cmd += "use keatest;\n"
        cmd += "set global innodb_large_prefix=on;\n"
        cmd += "set global innodb_file_format=Barracuda;\n"
        cmd += "set global innodb_file_per_table=true;\n"
        cmd += "set global innodb_default_row_format=dynamic;\n"
        cmd += "EOF\n\""
        execute(cmd)


def _configure_pgsql(system, features):
    if system in ['fedora', 'centos']:
        # https://fedoraproject.org/wiki/PostgreSQL
        exitcode = execute('sudo ls /var/lib/pgsql/data/postgresql.conf', raise_error=False)
        if exitcode != 0:
            execute('sudo postgresql-setup --initdb --unit postgresql')
    execute('sudo systemctl start postgresql.service')
    cmd = "bash -c \"cat <<EOF | sudo -u postgres psql postgres\n"
    cmd += "DROP DATABASE IF EXISTS keatest;\n"
    cmd += "DROP USER IF EXISTS keatest;\n"
    cmd += "DROP USER IF EXISTS keatest_readonly;\n"
    cmd += "CREATE USER keatest WITH PASSWORD 'keatest';\n"
    cmd += "CREATE USER keatest_readonly WITH PASSWORD 'keatest';\n"
    cmd += "CREATE DATABASE keatest;\n"
    cmd += "GRANT ALL PRIVILEGES ON DATABASE keatest TO keatest;\n"
    cmd += "ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT SELECT ON TABLES to keatest_readonly;\n"
    cmd += "EOF\n\""
    execute(cmd)

    if 'forge' in features:
        cmd = "bash -c \"cat <<EOF | sudo -u postgres psql postgres\n"
        cmd += "DROP DATABASE IF EXISTS keadb;\n"
        cmd += "DROP USER IF EXISTS keauser;\n"
        cmd += "CREATE USER keauser WITH PASSWORD 'keapass';\n"
        cmd += "CREATE DATABASE keadb;\n"
        cmd += "GRANT ALL PRIVILEGES ON DATABASE keauser TO keadb;\n"
        cmd += "EOF\n\""
        execute(cmd)


def _install_cassandra_deb(env, check_times):
    """Install Cassandra and cpp-driver using DEB package."""
    if not os.path.exists('/usr/sbin/cassandra'):
        cmd = 'echo "deb http://www.apache.org/dist/cassandra/debian 311x main" '
        cmd += '| sudo tee /etc/apt/sources.list.d/cassandra.sources.list'
        execute(cmd, env=env, check_times=check_times)
        execute('wget -qO- https://www.apache.org/dist/cassandra/KEYS | sudo apt-key add -',
                env=env, check_times=check_times)
        execute('sudo apt update', env=env, check_times=check_times)
        install_pkgs('cassandra libuv1 pkgconf', env=env, check_times=check_times)

    if not os.path.exists('/usr/include/cassandra.h'):
        execute('wget http://downloads.datastax.com/cpp-driver/ubuntu/18.04/cassandra/v2.11.0/cassandra-cpp-driver-dev_2.11.0-1_amd64.deb',
                env=env, check_times=check_times)
        execute('wget http://downloads.datastax.com/cpp-driver/ubuntu/18.04/cassandra/v2.11.0/cassandra-cpp-driver_2.11.0-1_amd64.deb',
                env=env, check_times=check_times)
        execute('sudo dpkg -i cassandra-cpp-driver-dev_2.11.0-1_amd64.deb cassandra-cpp-driver_2.11.0-1_amd64.deb',
                env=env, check_times=check_times)
        execute('rm -rf cassandra-cpp-driver-dev_2.11.0-1_amd64.deb cassandra-cpp-driver_2.11.0-1_amd64.deb',
                env=env, check_times=check_times)


def _install_freeradius_client(env, check_times):
    """Install FreeRADIUS-client with necessary patches from Francis Dupont."""
    execute('rm -rf freeradius-client')
    execute('git clone https://github.com/fxdupont/freeradius-client.git', env=env, check_times=check_times)
    execute('git checkout iscdev', cwd='freeradius-client', env=env, check_times=check_times)
    execute('./configure', cwd='freeradius-client', env=env, check_times=check_times)
    execute('make', cwd='freeradius-client', env=env, check_times=check_times)
    execute('sudo make install', cwd='freeradius-client', env=env, check_times=check_times)
    execute('sudo ldconfig', env=env, check_times=check_times)
    execute('rm -rf freeradius-client')


def _install_cassandra_rpm(env, check_times):
    """Install Cassandra and cpp-driver using RPM package."""
    if not os.path.exists('/usr/bin/cassandra'):
        #execute('sudo dnf config-manager --add-repo https://www.apache.org/dist/cassandra/redhat/311x/')
        #execute('sudo rpm --import https://www.apache.org/dist/cassandra/KEYS')
        install_pkgs('cassandra cassandra-server libuv libuv-devel', env=env, check_times=check_times)

    execute('sudo systemctl start cassandra')

    if not os.path.exists('/usr/include/cassandra.h'):
        execute('wget http://downloads.datastax.com/cpp-driver/centos/7/cassandra/v2.11.0/cassandra-cpp-driver-2.11.0-1.el7.x86_64.rpm')
        execute('wget http://downloads.datastax.com/cpp-driver/centos/7/cassandra/v2.11.0/cassandra-cpp-driver-devel-2.11.0-1.el7.x86_64.rpm')
        execute('sudo rpm -i cassandra-cpp-driver-2.11.0-1.el7.x86_64.rpm cassandra-cpp-driver-devel-2.11.0-1.el7.x86_64.rpm')
        execute('rm -rf cassandra-cpp-driver-2.11.0-1.el7.x86_64.rpm cassandra-cpp-driver-devel-2.11.0-1.el7.x86_64.rpm')


def prepare_system_local(features, check_times):
    """Prepare local system for Kea development based on requested features."""
    env = os.environ.copy()
    env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

    system, revision = get_system_revision()
    log.info('Preparing deps for %s %s', system, revision)

    # prepare fedora
    if system == 'fedora':
        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel',
                    'log4cplus-devel', 'boost-devel']

        if 'native-pkg' in features:
            packages.extend(['rpm-build', 'mariadb-connector-c-devel'])

        if 'docs' in features:
            packages.extend(['libxslt', 'elinks', 'docbook-style-xsl'])

        if 'mysql' in features:
            packages.extend(['mariadb', 'mariadb-server', 'community-mysql-devel'])

        if 'pgsql' in features:
            packages.extend(['postgresql-devel', 'postgresql-server'])

        if 'radius' in features:
            packages.extend(['git'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        install_pkgs(packages, timeout=300, env=env, check_times=check_times)

        if 'unittest' in features:
            _install_gtest_sources()

        execute('sudo dnf clean packages', env=env, check_times=check_times)

        if 'cql' in features:
            _install_cassandra_rpm(env, check_times)

    # prepare centos
    elif system == 'centos':
        install_pkgs('epel-release', env=env, check_times=check_times)

        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel',
                    'log4cplus-devel', 'boost-devel', 'mariadb-devel', 'postgresql-devel']

        if 'docs' in features:
            packages.extend(['libxslt', 'elinks', 'docbook-style-xsl'])

        if 'mysql' in features:
            packages.extend(['mariadb', 'mariadb-server', 'mariadb-devel'])

        if 'pgsql' in features:
            packages.extend(['postgresql-devel', 'postgresql-server'])

        if 'radius' in features:
            packages.extend(['git'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        install_pkgs(packages, env=env, check_times=check_times)

        if 'unittest' in features:
            _install_gtest_sources()

        if 'cql' in features:
            _install_cassandra_rpm(env, check_times)

    # prepare rhel
    elif system == 'rhel':
        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel', 'boost-devel',
                    'mariadb-devel', 'postgresql-devel']
        packages.extend(['rpm-build'])

        if 'docs' in features and not revision == '8':
            packages.extend(['libxslt', 'elinks', 'docbook-style-xsl'])

        # TODO:
        # if 'mysql' in features:
        #     packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev', 'mysql-server'])

        # if 'pgsql' in features:
        #     packages.extend(['postgresql-client', 'libpq-dev', 'postgresql-all'])

        if 'radius' in features:
            packages.extend(['git'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        install_pkgs(packages, env=env, timeout=120, check_times=check_times)

        # prepare lib4cplus as epel repos are not available for rhel 8 yet
        if revision == '8' and not os.path.exists('/usr/include/log4cplus/logger.h'):
            if not os.path.exists('srpms'):
                execute('mkdir srpms')
            execute('rm -rf srpms/*')
            execute('rm -rf rpmbuild')
            execute('wget --no-verbose -O srpms/log4cplus-1.1.3-0.4.rc3.el7.src.rpm '
                    'https://rpmfind.net/linux/epel/7/SRPMS/Packages/l/log4cplus-1.1.3-0.4.rc3.el7.src.rpm',
                    check_times=check_times)
            execute('rpmbuild --rebuild srpms/log4cplus-1.1.3-0.4.rc3.el7.src.rpm',
                    env=env, timeout=120, check_times=check_times)
            execute('sudo rpm -i rpmbuild/RPMS/x86_64/log4cplus-1.1.3-0.4.rc3.el8.x86_64.rpm',
                    env=env, check_times=check_times)
            execute('sudo rpm -i rpmbuild/RPMS/x86_64/log4cplus-devel-1.1.3-0.4.rc3.el8.x86_64.rpm',
                    env=env, check_times=check_times)

        if 'unittest' in features:
            _install_gtest_sources()

        if 'cql' in features:
            _install_cassandra_rpm(env, check_times)

    # prepare ubuntu
    elif system == 'ubuntu':
        execute('sudo apt update', env=env, check_times=check_times, attempts=3, sleep_time_after_attempt=10)

        packages = ['gcc', 'g++', 'make', 'autoconf', 'automake', 'libtool', 'libssl-dev', 'liblog4cplus-dev',
                    'libboost-system-dev']

        if 'unittest' in features:
            if revision.startswith('16.'):
                _install_gtest_sources()
            else:
                packages.append('googletest')

        if 'docs' in features:
            packages.extend(['dblatex', 'xsltproc', 'elinks', 'docbook-xsl'])

        if 'native-pkg' in features:
            packages.extend(['build-essential', 'fakeroot', 'devscripts'])
            packages.extend(['bison', 'debhelper', 'default-libmysqlclient-dev', 'libmysqlclient-dev',
                             'docbook', 'docbook-xsl', 'flex', 'libboost-dev', 'libpq-dev',
                             'postgresql-server-dev-all', 'python3-dev'])

        if 'mysql' in features:
            if revision == '16.04':
                packages.extend(['mysql-client', 'libmysqlclient-dev', 'mysql-server'])
            else:
                packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev', 'mysql-server'])

        if 'pgsql' in features:
            packages.extend(['postgresql-client', 'libpq-dev', 'postgresql-all'])

        if 'radius' in features:
            packages.extend(['git'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        install_pkgs(packages, env=env, timeout=240, check_times=check_times)

        if 'cql' in features:
            _install_cassandra_deb(env, check_times)

    # prepare debian
    elif system == 'debian':
        execute('sudo apt update', env=env, check_times=check_times, attempts=3, sleep_time_after_attempt=10)

        packages = ['gcc', 'g++', 'make', 'autoconf', 'automake', 'libtool', 'libssl-dev',
                    'liblog4cplus-dev', 'libboost-system-dev']

        if 'docs' in features:
            packages.extend(['dblatex', 'xsltproc', 'elinks', 'docbook-xsl'])

        if 'unittest' in features:
            if revision == '8':
                # libgtest-dev does not work and googletest is not available
                _install_gtest_sources()
            else:
                packages.append('googletest')

        if 'mysql' in features:
            if revision == '8':
                packages.extend(['mysql-client', 'libmysqlclient-dev', 'mysql-server'])
            else:
                packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev', 'mysql-server'])

        if 'radius' in features:
            packages.extend(['git'])

        if 'ccache' in features:
            packages.extend(['ccache'])

        install_pkgs(packages, env=env, timeout=240, check_times=check_times)

        if 'cql' in features and revision != '8':
            # there is no libuv1 package in case of debian 8
            _install_cassandra_deb(env, check_times)

    # prepare freebsd
    elif system == 'freebsd':
        packages = ['autoconf', 'automake', 'libtool', 'openssl', 'log4cplus', 'boost-libs']

        if 'docs' in features:
            packages.extend(['libxslt', 'elinks', 'docbook-xsl'])

        if 'unittest' in features:
            _install_gtest_sources()

        if 'mysql' in features:
            packages.extend(['mysql57-server', 'mysql57-client'])

        if 'radius' in features:
            packages.extend(['git'])

        install_pkgs(packages, env=env, timeout=6 * 60, check_times=check_times)

        if 'mysql' in features:
            execute('sudo sysrc mysql_enable="yes"', env=env, check_times=check_times)
            execute('sudo service mysql-server start', env=env, check_times=check_times,
                    raise_error=False)

    else:
        raise NotImplementedError

    if 'mysql' in features:
        _configure_mysql(system, revision, features)

    if 'pgsql' in features:
        _configure_pgsql(system, features)

    if 'radius' in features:
        _install_freeradius_client(env, check_times)

    #execute('sudo rm -rf /usr/share/doc')

    log.info('Preparing deps completed successfully.')


def prepare_system_in_vagrant(provider, system, revision, features, dry_run, check_times,
                              clean_start, ccache_dir=None):
    """Prepare specified system in Vagrant according to specified features."""
    ve = VagrantEnv(provider, system, revision, features, 'kea', dry_run, check_times=check_times,
                    ccache_dir=ccache_dir)
    if clean_start:
        ve.destroy()
    ve.up()
    ve.prepare_system()


def _calculate_build_timeout(features):
    """Return maximum allowed time for build (in seconds)."""
    timeout = 60
    if 'mysql' in features:
        timeout += 60
    timeout *= 60
    return timeout


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
    if 'mysql' in features:
        cmd += ' --with-mysql'
    if 'pgsql' in features:
        cmd += ' --with-pgsql'
    if 'cql' in features and not (system == 'debian' and revision == '8'):
        # debian 8 does not have all deps required
        cmd += ' --with-cql=/usr/bin/pkg-config'
    if 'unittest' in features:
        # prepare gtest switch - use downloaded gtest sources only if it is not present as native package
        if system in ['centos', 'fedora', 'rhel', 'freebsd']:
            cmd += ' --with-gtest-source=/usr/src/googletest-release-1.8.0/googletest/'
        elif system == 'debian' and revision == '8':
            cmd += ' --with-gtest-source=/usr/src/googletest-release-1.8.0/googletest/'
        elif system == 'debian':
            cmd += ' --with-gtest-source=/usr/src/googletest/googletest'
        elif system == 'ubuntu':
            if revision.startswith('16.'):
                cmd += ' --with-gtest-source=/usr/src/googletest-release-1.8.0/googletest/'
            else:
                cmd += ' --with-gtest-source=/usr/src/googletest/googletest'
        else:
            raise NotImplementedError
    if 'docs' in features and not (system == 'rhel' and revision == '8'):
        cmd += ' --enable-generate-docs'
    if 'radius' in features:
        cmd += ' --with-freeradius=/usr/local'
    if 'shell' in features:
        cmd += ' --enable-shell'
    if 'perfdhcp' in features:
        cmd += ' --enable-perfdhcp'

    # do ./configure
    execute(cmd, cwd=src_path, env=env, timeout=120, check_times=check_times, dry_run=dry_run)

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
    if 'ccache' in features or ccache_dir is not None:
        if system in ['debian', 'ubuntu']:
            ccache_bin_path = '/usr/lib/ccache/'
        else:
            ccache_bin_path = '/usr/lib64/ccache'
        env['PATH'] = ccache_bin_path + ':' + env['PATH']
        env['CCACHE_DIR'] = ccache_dir

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
        for fn in os.listdir(results_dir):
            if not fn.endswith('.xml'):
                continue
            fp = os.path.join(results_dir, fn)
            tree = ET.parse(fp)
            root = tree.getroot()
            total = int(root.get('tests'))
            failures = int(root.get('failures'))
            disabled = int(root.get('disabled'))
            errors = int(root.get('errors'))
            results[fn] = dict(total=total, failures=failures, disabled=disabled, errors=errors)
            grand_total += total
            grand_not_passed += failures + errors

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

    if 'install' in features:
        execute('sudo make install', timeout=2 * 60,
                cwd=src_path, env=env, check_times=check_times, dry_run=dry_run)
        execute('sudo ldconfig', dry_run=dry_run)  # TODO: this shouldn't be needed

        if 'forge' in features:
            if 'mysql' in features:
                execute('kea-admin lease-init mysql -u keauser -p keapass -n keadb', dry_run=dry_run)
            if 'pgsql' in features:
                execute('kea-admin lease-init pgsql -u keauser -p keapass -n keadb', dry_run=dry_run)


def _build_native_pkg(system, features, tarball_path, env, check_times, dry_run):
    """Build native (RPM or DEB) packages."""
    if system in ['fedora', 'centos', 'rhel']:
        # prepare RPM environment
        execute('rm -rf rpm-root', dry_run=dry_run)
        os.mkdir('rpm-root')
        os.mkdir('rpm-root/BUILD')
        os.mkdir('rpm-root/BUILDROOT')
        os.mkdir('rpm-root/RPMS')
        os.mkdir('rpm-root/SOURCES')
        os.mkdir('rpm-root/SPECS')
        os.mkdir('rpm-root/SRPMS')

        # get rpm.spec from tarball
        execute('sudo rm -rf kea-src', dry_run=dry_run)
        os.mkdir('kea-src')
        execute('tar -zxf %s' % tarball_path, cwd='kea-src', check_times=check_times, dry_run=dry_run)
        src_path = glob.glob('kea-src/*')[0]
        rpm_dir = os.path.join(src_path, 'rpm')
        for f in os.listdir(rpm_dir):
            if f == 'kea.spec':
                continue
            execute('cp %s rpm-root/SOURCES' % os.path.join(rpm_dir, f), check_times=check_times, dry_run=dry_run)
        execute('cp %s rpm-root/SPECS' % os.path.join(rpm_dir, 'kea.spec'), check_times=check_times, dry_run=dry_run)
        execute('cp %s rpm-root/SOURCES' % tarball_path, check_times=check_times, dry_run=dry_run)

        # do rpm build
        cmd = "rpmbuild -ba rpm-root/SPECS/kea.spec -D'_topdir /home/vagrant/rpm-root'"
        execute(cmd, env=env, timeout=60 * 40, check_times=check_times, dry_run=dry_run)

        if 'install' in features:
            execute('sudo rpm -i rpm-root/RPMS/x86_64/*rpm', check_times=check_times, dry_run=dry_run)

    elif system in ['ubuntu', 'debian']:
        # unpack tarball
        execute('sudo rm -rf kea-src', check_times=check_times, dry_run=dry_run)
        os.mkdir('kea-src')
        execute('tar -zxf %s' % tarball_path, cwd='kea-src', check_times=check_times, dry_run=dry_run)
        src_path = glob.glob('kea-src/*')[0]

        # do deb build
        execute('debuild -i -us -uc -b', env=env, cwd=src_path,
                timeout=60 * 40, check_times=check_times, dry_run=dry_run)

        if 'install' in features:
            execute('sudo dpkg -i kea-src/*deb', check_times=check_times, dry_run=dry_run)

    else:
        raise NotImplementedError


def build_local(features, tarball_path, check_times, jobs, dry_run, ccache_dir):
    """Prepare local system for Kea development based on requested features.

    If tarball_path is provided then instead of Kea sources from current directory
    use provided tarball.
    """
    env = os.environ.copy()
    env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

    system, revision = get_system_revision()

    execute('df -h', dry_run=dry_run)

    if tarball_path:
        tarball_path = os.path.abspath(tarball_path)

    if 'native-pkg' in features:
        _build_native_pkg(system, features, tarball_path, env, check_times, dry_run)
    else:
        _build_binaries_and_run_ut(system, revision, features, tarball_path, env, check_times, jobs,
                                   dry_run, ccache_dir)

    execute('df -h', dry_run=dry_run)


def build_in_vagrant(provider, system, revision, features, leave_system, tarball_path,
                     dry_run, quiet, clean_start, check_times, jobs, ccache_dir):
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
        ve.up()
        ve.prepare_system()
        total, passed = ve.run_build_and_test(tarball_path, jobs)
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


def package_box(provider, system, revision, features, dry_run, check_times):
    """Prepare Vagrant box of specified system."""
    ve = VagrantEnv(provider, system, revision, features, 'bare', dry_run, check_times=check_times)
    ve.destroy()
    ve.up()
    ve.prepare_system()
    # TODO cleanup
    ve.package()


def ssh(provider, system, revision):
    """Invoke Vagrant ssh for given system."""
    ve = VagrantEnv(provider, system, revision, [], 'kea', False)
    ve.up()
    ve.ssh()


def _install_vagrant(ver='2.2.4', upgrade=False):
    system, _ = get_system_revision()
    if system in ['fedora', 'centos', 'rhel']:
        if upgrade:
            execute('sudo rpm -e vagrant')
        rpm = 'vagrant_%s_x86_64.rpm' % ver
        cmd = 'wget --no-verbose -O /tmp/%s ' % rpm
        cmd += 'https://releases.hashicorp.com/vagrant/%s/%s' % (ver, rpm)
        execute(cmd)
        execute('sudo rpm -i /tmp/%s' % rpm)
        os.unlink('/tmp/%s' % rpm)
    elif system in ['debian', 'ubuntu']:
        if upgrade:
            execute('sudo dpkg --purge vagrant')
        deb = 'vagrant_%s_x86_64.deb' % ver
        cmd = 'wget --no-verbose -O /tmp/%s ' % deb
        cmd += 'https://releases.hashicorp.com/vagrant/%s/%s' % (ver, deb)
        execute(cmd)
        execute('sudo dpkg -i /tmp/%s' % deb)
        os.unlink('/tmp/%s' % deb)
    else:
        # TODO: check for packages here: https://www.vagrantup.com/downloads.html
        raise NotImplementedError


def ensure_hammer_deps():
    """Install Hammer dependencies onto current, host system."""
    exitcode, out = execute('vagrant version', raise_error=False, capture=True)
    if exitcode != 0:
        _install_vagrant()
    else:
        m = re.search('Installed Version: ([\d\.]+)', out, re.I)
        ver = m.group(1)
        major, minor, patch = [int(v) for v in ver.split('.')]
        # if ver < 2.2.3
        if major < 2 or (major == 2 and (minor < 2 or (minor == 2 and patch < 3))):
            m = re.search('Latest Version: ([\d\.]+)', out, re.I)
            ver = m.group(1)
            _install_vagrant(ver, upgrade=True)


    exitcode = execute('vagrant plugin list | grep vagrant-lxc', raise_error=False)
    if exitcode != 0:
        execute('vagrant plugin install vagrant-lxc')


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


DEFAULT_FEATURES = ['install', 'unittest', 'docs', 'perfdhcp']
ALL_FEATURES = ['install', 'distcheck', 'unittest', 'docs', 'mysql', 'pgsql', 'cql', 'native-pkg',
                'radius', 'shell', 'forge', 'perfdhcp', 'ccache']


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
    parent_parser2.add_argument('-l', '--leave-system', action='store_true',
                                help='At the end of the command do not destroy vagrant system. Default behavior is '
                                'destroing the system.')
    parent_parser2.add_argument('-c', '--clean-start', action='store_true',
                                help='If there is pre-existing system then it is destroyed first.')
    parent_parser2.add_argument('-i', '--check-times', action='store_true',
                                help='Do not allow executing commands infinitelly.')
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
    parser = subparsers.add_parser('prepare-system',
                                   help="Prepare system for doing Kea development i.e. install all required "
                                   "dependencies and pre-configure the system. build command always first calls "
                                   "prepare-system internally.",
                                   parents=[parent_parser1, parent_parser2])
    parser.add_argument('--ccache-dir', default=None,
                        help='Path to CCache directory on host system.')
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
                                   help="Package currently running system into Vagrant Box. Prepared box can be "
                                   "later deployed to Vagrant Cloud.",
                                   parents=[parent_parser1, parent_parser2])

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
    _, output = execute('vagrant global-status', quiet=True, capture=True)
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
    "Destroy Vagrant system under given path."""
    execute('vagrant destroy', cwd=path, interactive=True)


def _get_features(args):
    features = set(vars(args)['with'])
    # distcheck is not compatible with defaults so do not add them
    if 'distcheck' not in features:
        features = features.union(DEFAULT_FEATURES)
    nofeatures = set(args.without)
    features = features.difference(nofeatures)
    if hasattr(args, 'ccache_dir') and args.ccache_dir:
        features.add('ccache')
    return features


def _print_summary(results, features):
    """Print summart of build times and unit-test results."""
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
        prepare_system_local(features, args.check_times)
        return

    ccache_dir = _prepare_ccache_dir(args.ccache_dir, args.system, args.revision)

    prepare_system_in_vagrant(args.provider, args.system, args.revision, features,
                              args.dry_run, args.check_times, args.clean_start,
                              ccache_dir)


def build_cmd(args):
    """Check command args and run the build command."""
    features = _get_features(args)
    log.info('Enabled features: %s', ' '.join(features))
    if args.provider == 'local':
        build_local(features, args.from_tarball, args.check_times, int(args.jobs), args.dry_run,
                    args.ccache_dir)
        return

    _check_system_revision(args.system, args.revision)

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
                                  ccache_dir)
        results[(provider, system, revision)] = result

        error = result[1]
        if error:
            fail = True
            if isinstance(error, KeyboardInterrupt):
                break

    _print_summary(results, features)

    if fail:
        sys.exit(1)


def main():
    """Main function - parse args and invoke proper command."""
    args, parser = parse_args()

    # prepare logging
    level = logging.INFO
    if args.verbose:
        level = logging.DEBUG
    fmt = '[HAMMER]  %(asctime)-15s  %(message)s'
    logging.basicConfig(format=fmt, level=level)

    # dispatch command
    if args.command == 'supported-systems':
        list_supported_systems()

    elif args.command == 'created-systems':
        list_created_systems()

    elif args.command == "package-box":
        _check_system_revision(args.system, args.revision)
        features = _get_features(args)
        log.info('Enabled features: %s', ' '.join(features))
        package_box(args.provider, args.system, args.revision, features, args.dry_run, args.check_times)

    elif args.command == "prepare-system":
        prepare_system_cmd(args)

    elif args.command == "build":
        build_cmd(args)

    elif args.command == "ssh":
        _check_system_revision(args.system, args.revision)
        ssh(args.provider, args.system, args.revision)

    elif args.command == "ensure-hammer-deps":
        ensure_hammer_deps()

    elif args.command == "destroy":
        destroy_system(args.directory)

    else:
        parser.print_help()


if __name__ == '__main__':
    main()
