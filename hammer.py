#!/usr/bin/env python3

# Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

from __future__ import print_function
import os
import sys
import glob
import time
import json
import logging
import datetime
import platform
import binascii
import argparse
import subprocess
import multiprocessing
import xml.etree.ElementTree as ET

# TODO:
# - add docker provider
#   https://developer.fedoraproject.org/tools/docker/docker-installation.html
# - add CCACHE support
# - improve building from tarball
# - improve native-pkg builds
# - avoid using network if possible (e.g. check first if pkgs are installed)


SYSTEMS = {
    'fedora': ['27', '28', '29'],
    'centos': ['7'],
    #'rhel': ['7', '8'],
    'rhel': ['8'],
    'ubuntu': ['16.04', '18.04', '18.10'],
    'debian': ['8', '9'],
    #'freebsd': ['11.0', '11.1', '11.2', '12.0'],
    'freebsd': ['11.2', '12.0'],
}

IMAGE_TEMPLATES = {
    'fedora-27-lxc':           {'bare': 'lxc-fedora-27',               'kea': 'godfryd/kea-fedora-27'},
    'fedora-27-virtualbox':    {'bare': 'generic/fedora27',            'kea': 'godfryd/kea-fedora-27'},
    'fedora-28-lxc':           {'bare': 'lxc-fedora-28',               'kea': 'godfryd/kea-fedora-28'},
    'fedora-28-virtualbox':    {'bare': 'generic/fedora28',            'kea': 'godfryd/kea-fedora-28'},
    'fedora-29-lxc':           {'bare': 'godfryd/lxc-fedora-29',       'kea': 'godfryd/kea-fedora-29'},
    'fedora-29-virtualbox':    {'bare': 'generic/fedora29',            'kea': 'godfryd/kea-fedora-29'},
    'centos-7-lxc':            {'bare': 'godfryd/lxc-centos-7',        'kea': 'godfryd/kea-centos-7'},
    'centos-7-virtualbox':     {'bare': 'generic/centos7',             'kea': 'godfryd/kea-centos-7'},
#    'rhel-7-virtualbox':       {'bare': 'generic/rhel7',               'kea': 'generic/rhel7'},   # TODO: subsciption needed
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
  end

  config.vm.synced_folder '.', '/vagrant', disabled: true
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
    if sys.stdout.isatty():
        return '\033[1;31m%s\033[0;0m' % txt
    else:
        return txt

def green(txt):
    if sys.stdout.isatty():
        return '\033[0;32m%s\033[0;0m' % txt
    else:
        return txt

def blue(txt):
    if sys.stdout.isatty():
        return '\033[0;34m%s\033[0;0m' % txt
    else:
        return txt


def get_system_revision():
    system = platform.system()
    if system == 'Linux':
        system, revision, _ = platform.dist()
        if system == 'debian':
            if revision.startswith('8.'):
                revision = '8'
        elif system == 'redhat':
            system = 'rhel'
            if revision.startswith('8.'):
                revision = '8'
    elif system == 'FreeBSD':
        system = system.lower()
        revision = platform.release()
    return system.lower(), revision


class ExecutionError(Exception): pass

def execute(cmd, timeout=60, cwd=None, env=None, raise_error=True, dry_run=False, log_file_path=None, quiet=False, check_times=False):
    log.info('>>>>> Executing %s in %s', cmd, cwd if cwd else os.getcwd())
    if not check_times:
        timeout = None
    if dry_run:
        return 0
    if log_file_path:
        p = subprocess.Popen(cmd, cwd=cwd, env=env, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        with open(log_file_path, "wb") as log_file:
            t0 = time.time()
            t1 = time.time()
            while p.poll() is None and (timeout is None or t1 - t0 < timeout):
                line = p.stdout.readline()
                if line:
                    if not quiet:
                        print(line.decode(errors='ignore').strip() + '\r')
                    log_file.write(line)
                t1 = time.time()

            if p.poll() is None:
                raise ExecutionError('Execution timeout')
            exitcode = p.returncode

    else:
        p = subprocess.Popen(cmd, cwd=cwd, env=env, shell=True)
        ver = platform.python_version()
        if ver.startswith('2'):
            exitcode = p.wait()
        else:
            exitcode = p.wait(timeout)

    if exitcode != 0 and raise_error:
        raise ExecutionError("The command return non-zero exitcode %s, cmd: '%s'" % (exitcode, cmd))
    return exitcode


def install_yum(pkgs, env=None, check_times=False):
    if isinstance(pkgs, list):
        pkgs = ' '.join(pkgs)
    # skip.... to detect case when one packet is not found and no error is returned
    cmd = 'sudo yum install -y --setopt=skip_missing_names_on_install=False %s' % pkgs
    execute(cmd, env=env, check_times=check_times)


class VagrantEnv(object):
    def __init__(self, provider, system, sys_revision, features, image_template_variant, dry_run, quiet=False, check_times=False):
        self.provider = provider
        self.system = system
        self.sys_revision = sys_revision
        self.features = features
        self.dry_run = dry_run
        self.quiet = quiet
        self.check_times = check_times

        if provider == "virtualbox":
            vagrantfile_tpl = VBOX_VAGRANTFILE_TPL
        elif provider == "lxc":
            vagrantfile_tpl = LXC_VAGRANTFILE_TPL

        image_tpl = IMAGE_TEMPLATES["%s-%s-%s" % (system, sys_revision, provider)][image_template_variant]
        self.repo_dir = os.getcwd()

        sys_dir = "%s-%s" % (system, sys_revision)
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
        self.name = "hmr-%s-%s-kea-srv-%08d" % (system, sys_revision.replace('.', '-'), crc)

        vagrantfile = vagrantfile_tpl.format(image_tpl=image_tpl,
                                             name=self.name)

        with open(vagrantfile_path, "w") as f:
            f.write(vagrantfile)

        log.info('Prepared vagrant system %s in %s', self.name, self.vagrant_dir)

    def up(self):
        execute("vagrant box update", cwd=self.vagrant_dir, timeout=20 * 60, dry_run=self.dry_run)
        execute("vagrant up --no-provision --provider %s" % self.provider, cwd=self.vagrant_dir, timeout=15 * 60, dry_run=self.dry_run)

    def package(self):
        if self.provider == 'virtualbox':
            cmd = "vagrant package --output kea-%s-%s.box" % (self.system, self.sys_revision)
            execute(cmd, cwd=self.vagrant_dir, timeout=4 * 60, dry_run=self.dry_run)

        elif self.provider == 'lxc':
            execute('vagrant halt', cwd=self.vagrant_dir, dry_run=self.dry_run, raise_error=False)

            box_path = os.path.join(self.vagrant_dir, 'kea-%s-%s.box' % (self.system, self.sys_revision))
            if os.path.exists(box_path):
                os.unlink(box_path)

            lxc_box_dir = os.path.join(self.vagrant_dir, 'lxc-box')
            if os.path.exists(lxc_box_dir):
                execute('sudo rm -rf %s' % lxc_box_dir)
            os.mkdir(lxc_box_dir)
            lxc_container_path = os.path.join('/var/lib/lxc', self.name)
            execute('sudo bash -c \'echo "ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEA6NF8iallvQVp22WDkTkyrtvp9eWW6A8YVr+kz4TjGYe7gHzIw+niNltGEFHzD8+v1I2YJ6oXevct1YeS0o9HZyN1Q9qgCgzUFtdOKLv6IedplqoPkcmF0aYet2PkEDo3MlTBckFXPITAMzF8dJSIFo9D8HfdOV0IAdx4O7PtixWKn5y2hMNG0zQPyUecp4pzC6kivAIhyfHilFR61RGL+GPXQ2MWZWFYbAGjyiYJnAmCP3NOTd0jMZEnDkbUvxhMmBYSdETk1rRgm+R4LOzFUGaHqHDLKLX+FIPKcF96hrucXzcWyLbIbEgE98OHlnVYCzRdK8jlqm8tehUc9c9WhQ== vagrant insecure public key" > %s/rootfs/home/vagrant/.ssh/authorized_keys\'' % lxc_container_path)
            execute('sudo bash -c "cd %s && tar --numeric-owner --anchored --exclude=./rootfs/dev/log -czf %s/rootfs.tar.gz ./rootfs/*"' % (lxc_container_path, lxc_box_dir))
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

    def run_build_and_test(self, tarball_path, jobs):
        if self.dry_run:
            return 0, 0

        if not tarball_path:
            name_ver = 'kea-1.5.0'
            cmd = 'tar --transform "flags=r;s|^|%s/|" --exclude hammer ' % name_ver
            cmd += ' --exclude "*~" --exclude .git --exclude .libs --exclude .deps --exclude \'*.o\'  --exclude \'*.lo\' '
            cmd += ' -zcf /tmp/%s.tar.gz .' % name_ver
            execute(cmd)
            tarball_path = '/tmp/%s.tar.gz' % name_ver
        execute('vagrant upload %s %s.tar.gz' % (tarball_path, name_ver), cwd=self.vagrant_dir)

        log_file_path = os.path.join(self.vagrant_dir, 'build.log')
        log.info('Build log file stored to %s', log_file_path)

        t0 = time.time()

        bld_cmd = "%s hammer.py build -p local -t %s.tar.gz -j %d" % (self.python, name_ver, jobs)
        if self.features_arg:
            bld_cmd += ' ' + self.features_arg
        if self.nofeatures_arg:
            bld_cmd += ' ' + self.nofeatures_arg
        if self.check_times:
            bld_cmd += ' -i'
        self.execute(bld_cmd, timeout=40 * 60, log_file_path=log_file_path, quiet=self.quiet)  # timeout: 40 minutes

        ssh_cfg_path = self.dump_ssh_config()

        if 'native-pkg' in self.features:
            execute('scp -F %s -r default:/home/vagrant/rpm-root/RPMS/x86_64/ .' % ssh_cfg_path)

        t1 = time.time()
        dt = int(t1 - t0)

        log.info('Build log file stored to %s', log_file_path)
        log.info("")
        log.info(">>>>>> Build time %s:%s", dt // 60, dt % 60)
        log.info("")

        total = 0
        passed = 0
        try:
            if 'unittest' in self.features:
                execute('scp -F %s -r default:/home/vagrant/unit-test-results.json .' % ssh_cfg_path, cwd=self.vagrant_dir)
                results_file = os.path.join(self.vagrant_dir, 'unit-test-results.json')
                if os.path.exists(results_file):
                    with open(results_file) as f:
                        txt = f.read()
                        results = json.loads(txt)
                        total = results['grand_total']
                        passed = results['grand_passed']
        except:
            log.exception('ignored issue with parsing unit test results')

        return total, passed

    def destroy(self, force=False):
        cmd = 'vagrant destroy'
        if force:
            cmd += ' --force'
        execute(cmd, cwd=self.vagrant_dir, timeout=3 * 60, dry_run=self.dry_run)  # timeout: 3 minutes

    def ssh(self):
        execute('vagrant ssh', cwd=self.vagrant_dir, timeout=None, dry_run=self.dry_run)

    def dump_ssh_config(self):
        ssh_cfg_path = os.path.join(self.vagrant_dir, 'ssh.cfg')
        execute('vagrant ssh-config > %s' % ssh_cfg_path, cwd=self.vagrant_dir)
        return ssh_cfg_path

    def execute(self, cmd, timeout=None, raise_error=True, log_file_path=None, quiet=False, env=None):
        if not env:
            env = os.environ.copy()
        env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

        return execute('vagrant ssh -c "%s"' % cmd, env=env, cwd=self.vagrant_dir, timeout=timeout, raise_error=raise_error,
                       dry_run=self.dry_run, log_file_path=log_file_path, quiet=quiet, check_times=self.check_times)

    def prepare_deps(self):
        if self.features:
            self.features_arg = '--with ' + ' '.join(self.features)
        else:
            self.features_arg = ''

        nofeatures = set(DEFAULT_FEATURES) - self.features
        if nofeatures:
            self.nofeatures_arg = '--without ' + ' '.join(nofeatures)
        else:
            self.nofeatures_arg = ''

        if self.system == 'centos' and self.sys_revision == '7' or (self.system == 'debian' and self.sys_revision == '8' and self.provider != 'lxc'):
            self.python = 'python'
        elif self.system == 'freebsd':
            self.python = 'python3.6'
        else:
            self.python = 'python3'

        if self.system == 'rhel' and self.sys_revision == '8':
            exitcode = self.execute("sudo subscription-manager repos --list-enabled | grep rhel-8-for-x86_64-baseos-beta-rpms", raise_error=False)
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

        hmr_py_path = os.path.join(self.repo_dir, 'hammer.py')
        execute('vagrant upload %s' % hmr_py_path, cwd=self.vagrant_dir, dry_run=self.dry_run)

        log_file_path = os.path.join(self.vagrant_dir, 'prepare.log')
        log.info('Prepare log file stored to %s', log_file_path)

        cmd = "{python} hammer.py prepare-deps {features} {nofeatures} {check_times}"
        cmd = cmd.format(features=self.features_arg,
                         nofeatures=self.nofeatures_arg,
                         python=self.python,
                         check_times='-i' if self.check_times else '')
        self.execute(cmd, timeout=40 * 60, log_file_path=log_file_path, quiet=self.quiet)


def _install_gtest_sources():
    if not os.path.exists('/usr/src/googletest-release-1.8.0/googletest'):
        execute('wget --no-verbose -O /tmp/gtest.tar.gz https://github.com/google/googletest/archive/release-1.8.0.tar.gz')
        execute('sudo tar -C /usr/src -zxf /tmp/gtest.tar.gz')
        os.unlink('/tmp/gtest.tar.gz')


def _configure_mysql(system):
    if system in ['fedora', 'centos']:
        execute('sudo systemctl enable mariadb.service')
        execute('sudo systemctl start mariadb.service')
        time.sleep(5)
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


def _configure_pgsql(system):
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


def _install_cassandra_deb():
    if not os.path.exists('/usr/sbin/cassandra'):
        execute('echo "deb http://www.apache.org/dist/cassandra/debian 311x main" | sudo tee /etc/apt/sources.list.d/cassandra.sources.list')
        execute('curl https://www.apache.org/dist/cassandra/KEYS | sudo apt-key add -')
        execute('sudo apt update')
        execute('sudo apt install -y cassandra libuv1 pkgconf')

    if not os.path.exists('/usr/include/cassandra.h'):
        execute('wget http://downloads.datastax.com/cpp-driver/ubuntu/18.04/cassandra/v2.11.0/cassandra-cpp-driver-dev_2.11.0-1_amd64.deb')
        execute('wget http://downloads.datastax.com/cpp-driver/ubuntu/18.04/cassandra/v2.11.0/cassandra-cpp-driver_2.11.0-1_amd64.deb')
        execute('sudo dpkg -i cassandra-cpp-driver-dev_2.11.0-1_amd64.deb cassandra-cpp-driver_2.11.0-1_amd64.deb')
        execute('rm -rf cassandra-cpp-driver-dev_2.11.0-1_amd64.deb cassandra-cpp-driver_2.11.0-1_amd64.deb')


def _install_freeradius_client():
    execute('rm -rf freeradius-client')
    execute('git clone https://github.com/fxdupont/freeradius-client.git')
    execute('git checkout iscdev', cwd='freeradius-client')
    execute('./configure', cwd='freeradius-client')
    execute('make', cwd='freeradius-client')
    execute('sudo make install', cwd='freeradius-client')
    execute('sudo ldconfig')
    execute('rm -rf freeradius-client')


def _install_cassandra_rpm(system):
    if not os.path.exists('/usr/bin/cassandra'):
        #execute('sudo dnf config-manager --add-repo https://www.apache.org/dist/cassandra/redhat/311x/')
        #execute('sudo rpm --import https://www.apache.org/dist/cassandra/KEYS')
        if system == 'fedora':
            install_yum('cassandra cassandra-server libuv libuv-devel')
        #elif system == 'centos':
        else:
            raise NotImplementedError

    execute('sudo systemctl start cassandra')

    if not os.path.exists('/usr/include/cassandra.h'):
        execute('wget http://downloads.datastax.com/cpp-driver/centos/7/cassandra/v2.11.0/cassandra-cpp-driver-2.11.0-1.el7.x86_64.rpm')
        execute('wget http://downloads.datastax.com/cpp-driver/centos/7/cassandra/v2.11.0/cassandra-cpp-driver-devel-2.11.0-1.el7.x86_64.rpm')
        execute('sudo rpm -i cassandra-cpp-driver-2.11.0-1.el7.x86_64.rpm cassandra-cpp-driver-devel-2.11.0-1.el7.x86_64.rpm')
        execute('rm -rf cassandra-cpp-driver-2.11.0-1.el7.x86_64.rpm cassandra-cpp-driver-devel-2.11.0-1.el7.x86_64.rpm')


def prepare_deps_local(features, check_times):
    env = os.environ.copy()
    env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

    system, revision = get_system_revision()
    log.info('Preparing deps for %s %s', system, revision)

    if system == 'fedora':
        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel', 'log4cplus-devel', 'boost-devel']

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

        cmd = 'sudo dnf -y install %s' % ' '.join(packages)
        execute(cmd, env=env, timeout=300, check_times=check_times)

        if 'unittest' in features:
            _install_gtest_sources()

        execute('sudo dnf clean packages', env=env, check_times=check_times)

        if 'cql' in features:
            _install_cassandra_rpm(system)

    elif system == 'centos':
        install_yum('epel-release', env=env, check_times=check_times)

        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel', 'log4cplus-devel', 'boost-devel',
                    'mariadb-devel', 'postgresql-devel']

        if 'docs' in features:
            packages.extend(['libxslt', 'elinks', 'docbook-style-xsl'])

        if 'mysql' in features:
            packages.extend(['mariadb', 'mariadb-server', 'mariadb-devel'])

        if 'pgsql' in features:
            packages.extend(['postgresql-devel', 'postgresql-server'])

        if 'radius' in features:
            packages.extend(['git'])

        install_yum(packages, env=env, check_times=check_times)

        if 'unittest' in features:
            _install_gtest_sources()

        if 'cql' in features:
            _install_cassandra_rpm(system)

    elif system == 'rhel':
        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel', 'boost-devel',
                    'mariadb-devel', 'postgresql-devel']
        packages.extend(['rpm-build'])

        if 'docs' in features and not revision == '8':
            packages.extend(['libxslt', 'elinks', 'docbook-style-xsl'])

        # if 'mysql' in features:
        #     packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev', 'mysql-server'])

        # if 'pgsql' in features:
        #     packages.extend(['postgresql-client', 'libpq-dev', 'postgresql-all'])

        if 'radius' in features:
            packages.extend(['git'])

        install_cmd = 'sudo dnf -y install %s'
        execute(install_cmd % ' '.join(packages), env=env, check_times=check_times)

        # prepare lib4cplus as epel repos are not available for rhel 8 yet
        if revision == '8' and not os.path.exists('/usr/include/log4cplus/logger.h'):
            if not os.path.exists('srpms'):
                execute('mkdir srpms')
            execute('rm -rf srpms/*')
            execute('rm -rf rpmbuild')
            execute('wget --no-verbose -O srpms/log4cplus-1.1.3-0.4.rc3.el7.src.rpm https://rpmfind.net/linux/epel/7/SRPMS/Packages/l/log4cplus-1.1.3-0.4.rc3.el7.src.rpm',
                    check_times=check_times)
            execute('rpmbuild --rebuild srpms/log4cplus-1.1.3-0.4.rc3.el7.src.rpm', env=env, check_times=check_times)
            execute('sudo rpm -i rpmbuild/RPMS/x86_64/log4cplus-1.1.3-0.4.rc3.el8.x86_64.rpm', env=env, check_times=check_times)
            execute('sudo rpm -i rpmbuild/RPMS/x86_64/log4cplus-devel-1.1.3-0.4.rc3.el8.x86_64.rpm', env=env, check_times=check_times)

        if 'unittest' in features:
            _install_gtest_sources()

        if 'cql' in features:
            _install_cassandra_rpm(system)

    elif system == 'ubuntu':
        execute('sudo apt update', env=env, check_times=check_times)

        packages = ['gcc', 'g++', 'make', 'autoconf', 'automake', 'libtool', 'libssl-dev', 'liblog4cplus-dev', 'libboost-system-dev']

        if 'unittest' in features:
            if revision.startswith('16.'):
                _install_gtest_sources()
            else:
                packages.append('googletest')

        if 'docs' in features:
            packages.extend(['dblatex', 'xsltproc', 'elinks', 'docbook-xsl'])

        if 'native-pkg' in features:
            packages.extend(['build-essential', 'fakeroot', 'devscripts'])
            packages.extend(['bison', 'debhelper', 'default-libmysqlclient-dev', 'libmysqlclient-dev', 'docbook', 'docbook-xsl', 'flex', 'libboost-dev',
                             'libpq-dev', 'postgresql-server-dev-all', 'python3-dev'])

        if 'mysql' in features:
            packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev', 'mysql-server'])

        if 'pgsql' in features:
            packages.extend(['postgresql-client', 'libpq-dev', 'postgresql-all'])

        if 'radius' in features:
            packages.extend(['git'])

        done = False
        while not done:
            try:
                execute('sudo apt install --no-install-recommends -y %s' % ' '.join(packages), env=env, timeout=240, check_times=check_times)
                done = True
            except:
                log.exception('ble')
                time.sleep(20)

        if 'cql' in features:
            _install_cassandra_deb()

    elif system == 'debian':
        execute('sudo apt update', env=env, check_times=check_times)

        packages = ['gcc', 'g++', 'make', 'autoconf', 'automake', 'libtool', 'libssl-dev', 'liblog4cplus-dev', 'libboost-system-dev']

        if 'docs' in features:
            packages.extend(['dblatex', 'xsltproc', 'elinks', 'docbook-xsl'])

        if 'unittest' in features:
            if revision == '8':
                _install_gtest_sources()
                #packages.append('libgtest-dev') # it does not work
            else:
                packages.append('googletest')

        if 'mysql' in features:
            packages.extend(['default-mysql-client-core', 'default-libmysqlclient-dev', 'mysql-server'])

        if 'radius' in features:
            packages.extend(['git'])

        execute('sudo apt install --no-install-recommends -y %s' % ' '.join(packages), env=env, timeout=240, check_times=check_times)

        if 'cql' in features:
            _install_cassandra_deb()

    elif system == 'freebsd':
        packages = ['autoconf', 'automake', 'libtool', 'openssl', 'log4cplus', 'boost-libs']

        #execute('sudo portsnap --interactive fetch', timeout=240, check_times=check_times)
        #execute('sudo portsnap extract /usr/ports/devel/log4cplus', timeout=240, check_times=check_times)

        #execute('sudo make -C /usr/ports/devel/log4cplus install clean BATCH=yes', timeout=240, check_times=check_times)

        if 'docs' in features:
            packages.extend(['libxslt', 'elinks', 'docbook-xsl'])

        if 'radius' in features:
            packages.extend(['git'])

        if 'unittest' in features:
            _install_gtest_sources()

        execute('sudo pkg install -y %s' % ' '.join(packages), env=env, timeout=6 * 60, check_times=check_times)

    else:
        raise NotImplementedError

    if 'mysql' in features:
        _configure_mysql(system)

    if 'pgsql' in features:
        _configure_pgsql(system)

    if 'radius' in features:
        _install_freeradius_client()

    #execute('sudo rm -rf /usr/share/doc')


def build_local(features, tarball_path, check_times, jobs):
    env = os.environ.copy()
    env['LANGUAGE'] = env['LANG'] = env['LC_ALL'] = 'C'

    distro, revision = get_system_revision()

    execute('df -h')

    tarball_path = os.path.abspath(tarball_path)

    if 'native-pkg' in features:
        # native pkg build

        if distro in ['fedora', 'centos', 'rhel']:
            execute('rm -rf rpm-root')
            os.mkdir('rpm-root')
            os.mkdir('rpm-root/BUILD')
            os.mkdir('rpm-root/BUILDROOT')
            os.mkdir('rpm-root/RPMS')
            os.mkdir('rpm-root/SOURCES')
            os.mkdir('rpm-root/SPECS')
            os.mkdir('rpm-root/SRPMS')

            execute('rm -rf kea-src')
            os.mkdir('kea-src')
            execute('tar -zxf %s' % tarball_path, cwd='kea-src', check_times=check_times)
            src_path = glob.glob('kea-src/*')[0]
            rpm_dir = os.path.join(src_path, 'rpm')
            for f in os.listdir(rpm_dir):
                if f == 'kea.spec':
                    continue
                execute('cp %s rpm-root/SOURCES' % os.path.join(rpm_dir, f), check_times=check_times)
            execute('cp %s rpm-root/SPECS' % os.path.join(rpm_dir, 'kea.spec'), check_times=check_times)
            execute('cp %s rpm-root/SOURCES' % tarball_path, check_times=check_times)

            cmd = "rpmbuild -ba rpm-root/SPECS/kea.spec -D'_topdir /home/vagrant/rpm-root'"
            execute(cmd, env=env, timeout=60 * 40, check_times=check_times)

            if 'install' in features:
                execute('sudo rpm -i rpm-root/RPMS/x86_64/*rpm', check_times=check_times)

        elif distro in ['ubuntu', 'debian']:
            execute('rm -rf kea-src', check_times=check_times)
            os.mkdir('kea-src')
            execute('tar -zxf %s' % tarball_path, cwd='kea-src', check_times=check_times)
            src_path = glob.glob('kea-src/*')[0]

            execute('debuild -i -us -uc -b', env=env, cwd=src_path, timeout=60 * 40, check_times=check_times)

            if 'install' in features:
                execute('sudo dpkg -i kea-src/*deb', check_times=check_times)

        else:
            raise NotImplementedError

    else:
        # build straight from sources

        if tarball_path:
            execute('rm -rf kea-src')
            os.mkdir('kea-src')
            execute('tar -zxf %s' % tarball_path, cwd='kea-src', check_times=check_times)
            src_path = glob.glob('kea-src/*')[0]
        else:
            src_path = '.'

        execute('autoreconf -f -i', cwd=src_path, env=env)

        cmd = './configure'
        if 'mysql' in features:
            cmd += ' --with-mysql'
        if 'pgsql' in features:
            cmd += ' --with-pgsql'
        if 'cql' in features:
            cmd += ' --with-cql=/usr/bin/pkg-config'
        if 'unittest' in features:
            if distro in ['centos', 'fedora', 'rhel', 'freebsd']:
                cmd += ' --with-gtest-source=/usr/src/googletest-release-1.8.0/googletest/'
            elif distro == 'debian' and revision == '8':
                #cmd += ' --with-gtest-source=/usr/src/gtest' # it does not work
                cmd += ' --with-gtest-source=/usr/src/googletest-release-1.8.0/googletest/'
            elif distro == 'debian':
                cmd += ' --with-gtest-source=/usr/src/googletest/googletest'
            elif distro == 'ubuntu':
                if revision.startswith('16.'):
                    cmd += ' --with-gtest-source=/usr/src/googletest-release-1.8.0/googletest/'
                else:
                    cmd += ' --with-gtest-source=/usr/src/googletest/googletest'
            else:
                raise NotImplementedError
        if 'docs' in features and not (distro == 'rhel' and revision == '8'):
            cmd += ' --enable-generate-docs'
        if 'radius' in features:
            cmd += ' --with-freeradius=/usr/local'

        if distro == 'freebsd':
            cmd += ' --with-boost-include=/usr/local/include'  # TODO: this should be fixed in ./configure.ac
            cmd += ' --with-boost-lib-dir=/usr/local/lib'      # TODO: this should be fixed in ./configure.ac

        execute(cmd, cwd=src_path, env=env, check_times=check_times)

        if jobs == 0:
            cpus = multiprocessing.cpu_count() - 1
            if distro == 'centos':
                cpus = cpus // 2
            if cpus == 0:
                cpus = 1
        else:
            cpus = jobs
        cmd = 'make -j%s' % cpus
        execute(cmd, cwd=src_path, env=env, timeout=40 * 60, check_times=check_times)

        if 'unittest' in features:
            results_dir = os.path.abspath(os.path.join(src_path, 'tests_result'))
            execute('rm -rf %s' % results_dir)
            if not os.path.exists(results_dir):
                os.mkdir(results_dir)
            env['GTEST_OUTPUT'] = 'xml:%s/' % results_dir
            env['KEA_SOCKET_TEST_DIR'] = '/tmp/'
            execute('make check -k', cwd=src_path, env=env, timeout=60 * 60, raise_error=False, check_times=check_times)

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
            execute('sudo make install', cwd=src_path, env=env, check_times=check_times)

    execute('df -h')


def build_in_vagrant(provider, system, sys_revision, features, leave_system, tarball_path, dry_run, quiet, clean_start, check_times, jobs):
    log.info('')
    log.info(">>> Building %s, %s, %s" % (provider, system, sys_revision))
    log.info('')

    t0 = time.time()

    error = None
    total = 0
    passed = 0
    try:
        ve = VagrantEnv(provider, system, sys_revision, features, 'kea', dry_run, quiet, check_times)
        if clean_start:
            ve.destroy(force=True)
        ve.up()
        ve.prepare_deps()
        total, passed = ve.run_build_and_test(tarball_path, jobs)
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
        if not leave_system:
            ve.destroy(force=True)

    t1 = time.time()
    dt = int(t1 - t0)

    log.info('')
    log.info(">>> Building %s, %s, %s completed in %s:%s%s", provider, system, sys_revision, dt // 60, dt % 60, msg)
    log.info('')

    return dt, error, total, passed


def package_box(provider, system, sys_revision, features, dry_run, check_times):
    ve = VagrantEnv(provider, system, sys_revision, features, 'bare', dry_run, check_times=check_times)
    ve.destroy(force=True)
    ve.up()
    ve.prepare_deps()
    # TODO cleanup
    ve.package()


def prepare_system(provider, system, sys_revision, features, dry_run, check_times, clean_start):
    ve = VagrantEnv(provider, system, sys_revision, features, 'kea', dry_run, check_times=check_times)
    if clean_start:
        ve.destroy(force=True)
    ve.up()
    ve.prepare_deps()


def ssh(provider, system, sys_revision, features, dry_run):
    ve = VagrantEnv(provider, system, sys_revision, features, 'kea', dry_run)
    ve.up()
    ve.ssh()


def ensure_hammer_deps():
    distro, _ = get_system_revision()

    exitcode = execute('vagrant version', raise_error=False)
    if exitcode != 0:
        if distro in ['fedora', 'centos', 'rhel']:
            execute('wget --no-verbose -O /tmp/vagrant_2.2.2_x86_64.rpm https://releases.hashicorp.com/vagrant/2.2.2/vagrant_2.2.2_x86_64.rpm')
            execute('sudo rpm -i /tmp/vagrant_2.2.2_x86_64.rpm')
            os.unlink('/tmp/vagrant_2.2.2_x86_64.rpm')
        elif distro in ['debian', 'ubuntu']:
            execute('wget --no-verbose -O /tmp/vagrant_2.2.2_x86_64.deb https://releases.hashicorp.com/vagrant/2.2.2/vagrant_2.2.2_x86_64.deb')
            execute('sudo dpkg -i /tmp/vagrant_2.2.2_x86_64.deb')
            os.unlink('/tmp/vagrant_2.2.2_x86_64.deb')
        else:
            # TODO: check for packages here: https://www.vagrantup.com/downloads.html
            raise NotImplementedError

    exitcode = execute('vagrant plugin list | grep vagrant-lxc', raise_error=False)
    if exitcode != 0:
        execute('vagrant plugin install vagrant-lxc')


DEFAULT_FEATURES = ['install', 'unittest', 'docs']
ALL_FEATURES = ['install', 'unittest', 'docs', 'mysql', 'pgsql', 'cql', 'native-pkg', 'radius']

def parse_args():
    parser = argparse.ArgumentParser(description='Kea develepment environment management tool.')

    parser.add_argument('command', choices=['package-box', 'prepare-system', 'build', 'prepare-deps', 'list-systems', 'ssh', 'ensure-hammer-deps'],
                        help='Commands.')
    parser.add_argument('-p', '--provider', default='virtualbox', choices=['lxc', 'virtualbox', 'all', 'local'],
                        help="Backend build executor. If 'all' then build is executed several times on all providers. "
                        "If 'local' then build is executed on current system. Default is 'virtualbox'.")
    parser.add_argument('-s', '--system', default='all', choices=list(SYSTEMS.keys()) + ['all'],
                        help="Build is executed on selected system. If 'all' then build is executed several times on all systems. "
                        "If provider is 'local' then this option is ignored. Default is 'all'.")
    parser.add_argument('-r', '--revision', default='all',
                        help="Revision of selected system. If 'all' then build is executed several times "
                        "on all revisions of selected system. To list supported systems and their revisions invoke 'list-systems'. "
                        "Default is 'all'.")
    parser.add_argument('-w', '--with', nargs='+', default=set(), choices=ALL_FEATURES,
                        help="Enabled, comma-separated features. Default is '%s'." % ' '.join(DEFAULT_FEATURES))
    parser.add_argument('-x', '--without', nargs='+', default=set(), choices=ALL_FEATURES,
                        help="Disabled, comma-separated features. Default is ''.")
    parser.add_argument('-l', '--leave-system', action='store_true',
                        help='At the end of the command do not destroy vagrant system. Default behavior is destroing the system.')
    parser.add_argument('-t', '--from-tarball',
                        help='Instead of building sources in current folder use provided tarball package (e.g. tar.gz).')
    parser.add_argument('-v', '--verbose', action='store_true', help='Enable verbose mode.')
    parser.add_argument('-q', '--quiet', action='store_true', help='Enable quiet mode.')
    parser.add_argument('-n', '--dry-run', action='store_true', help='Print only what would be done.')
    parser.add_argument('-c', '--clean-start', action='store_true', help='If there is pre-existing system then it is destroyed first.')
    parser.add_argument('-i', '--check-times', action='store_true', help='Do not allow executing commands infinitelly.')
    parser.add_argument('-j', '--jobs', default=0, help='Number of processes used in compilation. Override make -j default value.')

    args = parser.parse_args()

    return args


def list_systems():
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


def _what_features(args):
    features = set(vars(args)['with'])
    features = features.union(DEFAULT_FEATURES)
    nofeatures = set(args.without)
    features = features.difference(nofeatures)

    return features


def _print_summary(results, features):
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
        print('| %10s | %10s | %8s | %6d:%02d | %s | %s |' % (provider, system, revision, dt // 60, dt % 60, status, ut_results))
    print("+------------+------------+----------+-----------+---------+--------------+")
    print("|                               Total: %6d:%02d |                        |" % (total_dt // 60, total_dt % 60))
    print("+=========================================================================+")


def main():
    args = parse_args()

    level = logging.INFO
    if args.verbose:
        level = logging.DEBUG

    format = '[HAMMER]  %(asctime)-15s  %(message)s'
    logging.basicConfig(format=format, level=level)

    features = _what_features(args)

    if args.command == 'list-systems':
        list_systems()

    elif args.command == "package-box":
        log.info('Enabled features: %s', ' '.join(features))
        package_box(args.provider, args.system, args.revision, features, args.dry_run, args.check_times)

    elif args.command == "prepare-system":
        log.info('Enabled features: %s', ' '.join(features))
        prepare_system(args.provider, args.system, args.revision, features, args.dry_run, args.check_times, args.clean_start)

    elif args.command == "build":
        log.info('Enabled features: %s', ' '.join(features))
        if args.provider == 'local':
            build_local(features, args.from_tarball, args.check_times, int(args.jobs))
            return

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
            duration, error, total, passed = build_in_vagrant(provider, system, revision, features, args.leave_system, args.from_tarball,
                                                              args.dry_run, args.quiet, args.clean_start, args.check_times, int(args.jobs))
            results[(provider, system, revision)] = (duration, error, total, passed)

            if error:
                fail = True
                if isinstance(error, KeyboardInterrupt):
                    break

        _print_summary(results, features)

        if fail:
            sys.exit(1)

    elif args.command == "prepare-deps":
        log.info('Enabled features: %s', ' '.join(features))
        prepare_deps_local(features, args.check_times)

    elif args.command == "ssh":
        ssh(args.provider, args.system, args.revision, features, args.dry_run)

    elif args.command == "ensure-hammer-deps":
        ensure_hammer_deps()


if __name__ == '__main__':
    # results = {
    #     ('virtualbox', 'centos', '7'): (920, False),
    #     ('lxc', 'fedora', '29'): (120, False),
    # }
    # _print_summary(results)

    main()
