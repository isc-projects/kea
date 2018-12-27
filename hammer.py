#!/usr/bin/env python3
# PYTHON_ARGCOMPLETE_OK  TODO
from __future__ import print_function
import os
import sys
import glob
import argparse
import time
import platform
import subprocess
import logging
import multiprocessing

# TODO:
# - add docker provider
# - add CCACHE support


SYSTEMS = {
    'fedora': ['27', '28', '29'],
    'centos': ['7'],
    'rhel': ['7', '8'],
    'ubuntu': ['18.04'],
    'debian': ['8', '9'],
    #'freebsd': ['11.0', '11.1', '11.2', '12.0'],
    'freebsd': ['11.2'],
}

IMAGE_TEMPLATES = {
    'fedora-27-lxc':           {'bare': 'lxc-fedora-27',               'kea': 'lxc-fedora-27'},
    'fedora-27-virtualbox':    {'bare': 'generic/fedora27',            'kea': 'generic/fedora27'},
    'fedora-28-lxc':           {'bare': 'lxc-fedora-28',               'kea': 'lxc-fedora-28'},
    'fedora-28-virtualbox':    {'bare': 'generic/fedora28',            'kea': 'generic/fedora28'},
    'fedora-29-lxc':           {'bare': 'lxc-fedora-29',               'kea': 'lxc-fedora-29'},
    'fedora-29-virtualbox':    {'bare': 'generic/fedora29',            'kea': 'generic/fedora29'},
    'centos-7-lxc':            {'bare': 'lxc-centos-7',                'kea': 'lxc-centos-7'},
    'centos-7-virtualbox':     {'bare': 'generic/centos7',             'kea': 'generic/centos7'},
#    'rhel-7-virtualbox':       {'bare': 'generic/rhel7',               'kea': 'generic/rhel7'},   # TODO: subsciption needed
    'rhel-8-virtualbox':       {'bare': 'generic/rhel8',               'kea': 'generic/rhel8'},
    'ubuntu-18.04-lxc':        {'bare': 'zeitonline/bionic64-lxc',     'kea': 'zeitonline/bionic64-lxc'},
    'ubuntu-18.04-virtualbox': {'bare': 'ubuntu/bionic64',             'kea': 'ubuntu/bionic64'},
    'debian-8-lxc':            {'bare': 'debian/jessie64',             'kea': 'debian/jessie64'},
    'debian-8-virtualbox':     {'bare': 'debian/jessie64',             'kea': 'debian/jessie64'},
    'debian-9-lxc':            {'bare': 'debian/stretch64',            'kea': 'debian/stretch64'},
    'debian-9-virtualbox':     {'bare': 'debian/stretch64',            'kea': 'debian/stretch64'},
    'debian-9-lxc':            {'bare': 'debian/stretch64',            'kea': 'debian/stretch64'},
    #'freebsd-11.0-virtualbox': {'bare': 'freebsd/FreeBSD-11.0-STABLE', 'kea': 'freebsd/FreeBSD-11.0-STABLE'},  # reboots in the boot loop
    #'freebsd-11.1-virtualbox': {'bare': 'freebsd/FreeBSD-11.1-STABLE', 'kea': 'freebsd/FreeBSD-11.1-STABLE'},  # TODO: not tested
    #'freebsd-11.2-virtualbox': {'bare': 'freebsd/FreeBSD-11.2-STABLE', 'kea': 'freebsd/FreeBSD-11.2-STABLE'},  # TODO: not tested
    'freebsd-11.2-virtualbox': {'bare': 'generic/freebsd11', 'kea': 'generic/freebsd11'},
    #'freebsd-12.0-virtualbox': {'bare': 'freebsd/FreeBSD-12.0-STABLE', 'kea': 'freebsd/FreeBSD-12.0-STABLE'},  # TODO: not tested
}

LXC_VAGRANTFILE_TPL = """# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.provider "lxc"

  config.vm.hostname = "{system}-{revision}-kea-srv-lxc"

  config.vm.box = "{image_tpl}"
end
"""

VBOX_VAGRANTFILE_TPL = """# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.hostname = "{system}-{revision}-kea-srv"

  config.vm.box = "{image_tpl}"

  config.vm.provider "virtualbox" do |v|
    v.name = "hmr-{system}-{revision}-kea-srv"
    v.memory = 8192

    nproc = Etc.nprocessors
    if nproc > 8
      nproc -= 2
    elsif nproc > 1
      nproc -= 1
    end
    v.cpus = nproc
  end
end
"""


log = logging.getLogger()


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


def execute(cmd, timeout=60, cwd=None, env=None, raise_error=True):
    log.info('>>>>> Executing %s in %s', cmd, cwd if cwd else os.getcwd())
    p = subprocess.Popen(cmd, cwd=cwd, env=env, shell=True)
    ver = platform.python_version()
    if ver.startswith('2'):
        exitcode = p.wait()
    else:
        exitcode = p.wait(timeout)
    if exitcode != 0 and raise_error:
        raise Exception('some issue')
    return exitcode


class VagrantEnv(object):
    def __init__(self, provider, system, sys_revision, features, leave_system, image_template_variant):
        self.system = system
        self.sys_revision = sys_revision
        self.leave_system = leave_system
        self.features = features

        if provider == "virtualbox":
            vagrantfile_tpl = VBOX_VAGRANTFILE_TPL
        elif provider == "lxc":
            vagrantfile_tpl = LXC_VAGRANTFILE_TPL

        image_tpl = IMAGE_TEMPLATES["%s-%s-%s" % (system, sys_revision, provider)][image_template_variant]
        self.repo_dir = os.getcwd()

        vagrantfile = vagrantfile_tpl.format(system=system,
                                             revision=sys_revision,
                                             image_tpl=image_tpl,
                                             repo_dir=self.repo_dir)

        sys_dir = "%s-%s" % (system, sys_revision)
        if provider == "virtualbox":
            vagrant_dir = os.path.join(self.repo_dir, 'hammer', sys_dir, 'vbox')
        elif provider == "lxc":
            vagrant_dir = os.path.join(self.repo_dir, 'hammer', sys_dir, 'lxc')

        if not os.path.exists(vagrant_dir):
            os.makedirs(vagrant_dir)

        vagrantfile_path = os.path.join(vagrant_dir, "Vagrantfile")

        if os.path.exists(vagrantfile_path):
            # TODO: destroy any existing VM
            pass

        with open(vagrantfile_path, "w") as f:
            f.write(vagrantfile)

        self.vagrant_dir = vagrant_dir

    def up(self):
        try:
            execute("vagrant up --no-provision", cwd=self.vagrant_dir, timeout=5 * 60)  # timeout: 3 minutes
            #raise Exception('Preparing vagrant system failed.')
        except:
            if not self.leave_system:
                self.destroy()
            raise

    def package(self):
        execute("vagrant package", cwd=self.vagrant_dir, timeout=3 * 60)  # timeout: 3 minutes
        if exitcode != 0:
            raise Exception('Packaging vagrant system to box failed.')

    def run_build_and_test(self, tarball_path):
        if not tarball_path:
            name_ver = 'kea-1.5.0'
            execute('tar --transform "flags=r;s|^|%s/|" --exclude hammer --exclude "*~" --exclude .git -zcf /tmp/%s.tar.gz .' % (name_ver, name_ver))
            tarball_path = '/tmp/%s.tar.gz' % name_ver
        execute('vagrant upload %s %s.tar.gz' % (tarball_path, name_ver), cwd=self.vagrant_dir)
        self.execute("rm -rf kea-src")

        t0 = time.time()
        try:
            bld_cmd = "%s hammer.py build -p local -t %s.tar.gz" % (self.python, name_ver)
            if self.features_arg:
                bld_cmd += ' ' + self.features_arg
            if self.nofeatures_arg:
                bld_cmd += ' ' + self.nofeatures_arg
            self.execute(bld_cmd, timeout=40 * 60)  # timeout: 40 minutes

            if 'native-pkg' in self.features:
                execute('vagrant ssh-config > %s/ssh.cfg' % self.vagrant_dir, cwd=self.vagrant_dir)
                execute('scp -F %s/ssh.cfg -r default:/home/vagrant/rpm-root/RPMS/x86_64/ .' % self.vagrant_dir)
        finally:
            if not self.leave_system:
                self.destroy(force=True)
        t1 = time.time()
        dt = int(t1 - t0)
        log.info("")
        log.info(">>>>>> Build time %s:%s", dt // 60, dt % 60)
        log.info("")

    def destroy(self, force=False):
        cmd = 'vagrant destroy'
        if force:
            cmd += ' --force'
        execute(cmd, cwd=self.vagrant_dir, timeout=3 * 60)  # timeout: 3 minutes

    def ssh(self):
        execute('vagrant ssh', cwd=self.vagrant_dir, timeout=None)

    def execute(self, cmd, timeout=None, raise_error=True):
        return execute("vagrant ssh -c '%s'" % cmd, cwd=self.vagrant_dir, timeout=timeout, raise_error=raise_error)

    def prepare_deps(self, features):
        if features:
            self.features_arg = '--with ' + ' '.join(features)
        else:
            self.features_arg = ''

        nofeatures = set(DEFAULT_FEATURES) - features
        if nofeatures:
            self.nofeatures_arg = '--without ' + ' '.join(nofeatures)
        else:
            self.nofeatures_arg = ''

        if self.system == 'centos' and self.sys_revision == '7' or self.system == 'debian' and self.sys_revision == '8':
            self.python = 'python'
        elif self.system == 'freebsd':
            self.python = 'python3.6'
        else:
            self.python = 'python3'

        if self.system == 'rhel' and self.sys_revision == '8':
            exitcode = self.execute("sudo subscription-manager repos --list-enabled | grep rhel-8-for-x86_64-baseos-beta-rpms", raise_error=False)
            if exitcode != 0:
                self.execute("sudo subscription-manager register --user godfryd2 --password 'donotchange'")
                self.execute("sudo subscription-manager refresh")
                self.execute("sudo subscription-manager attach --pool 8a85f99a67cdc3e70167e45c85f47429")
                self.execute("sudo subscription-manager repos --enable rhel-8-for-x86_64-baseos-beta-rpms")
                self.execute("sudo dnf install -y python36")

        hmr_py_path = os.path.join(self.repo_dir, 'hammer.py')
        execute('vagrant upload %s' % hmr_py_path, cwd=self.vagrant_dir)

        cmd = "sudo {python} hammer.py prepare-deps {features} {nofeatures}"
        cmd = cmd.format(features=self.features_arg,
                         nofeatures=self.nofeatures_arg,
                         python=self.python)
        self.execute(cmd)


def _install_gtest_sources():
    if not os.path.exists('/usr/src/googletest-release-1.8.0/googletest'):
        execute('wget --no-verbose -O /tmp/gtest.tar.gz https://github.com/google/googletest/archive/release-1.8.0.tar.gz')
        execute('tar -C /usr/src -zxf /tmp/gtest.tar.gz')
        os.unlink('/tmp/gtest.tar.gz')


def prepare_deps(features):
    system, revision = get_system_revision()
    log.info('Preparing deps for %s %s', system, revision)

    if system == 'fedora':
        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel', 'log4cplus-devel', 'boost-devel',
                    'community-mysql-devel', 'postgresql-devel']

        if 'native-pkg' in features:
            packages.remove('community-mysql-devel')
            packages.extend(['rpm-build', 'mariadb-connector-c-devel'])

        cmd = 'dnf -y install %s' % ' '.join(packages)
        execute(cmd, timeout=120)

        if 'unittest' in features:
            _install_gtest_sources()

    elif system == 'centos':
        install_cmd = 'yum -y --setopt=skip_missing_names_on_install=False install %s'

        execute(install_cmd % 'epel-release')

        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel', 'log4cplus-devel', 'boost-devel',
                    'mariadb-devel', 'postgresql-devel']

        if 'docs' in features:
            packages.extend(['libxslt', 'elinks'])

        execute(install_cmd % ' '.join(packages))

        if 'unittest' in features:
            _install_gtest_sources()

    if system == 'rhel':
        packages = ['make', 'autoconf', 'automake', 'libtool', 'gcc-c++', 'openssl-devel', 'boost-devel',
                    'mariadb-devel', 'postgresql-devel']
        packages.extend(['rpm-build'])

        if 'docs' in features:
            packages.extend(['libxslt'])

        install_cmd = 'dnf -y install %s'
        execute(install_cmd % ' '.join(packages))

        # prepare lib4cplus as epel repos are not available for rhel 8 yet
        if revision == '8' and not os.path.exists('/usr/include/log4cplus/logger.h'):
            execute('mkdir srpms')
            execute('wget --no-verbose -O srpms/log4cplus-1.1.3-0.4.rc3.el7.src.rpm https://rpmfind.net/linux/epel/7/SRPMS/Packages/l/log4cplus-1.1.3-0.4.rc3.el7.src.rpm')
            execute('sudo rpm -i rpmbuild/RPMS/x86_64/log4cplus-1.1.3-0.4.rc3.el8.x86_64.rpm')
            execute('sudo rpm -i rpmbuild/RPMS/x86_64/log4cplus-devel-1.1.3-0.4.rc3.el8.x86_64.rpm')

        if 'unittest' in features:
            _install_gtest_sources()

    elif system == 'ubuntu':
        execute('apt update')

        packages = ['gcc', 'g++', 'make', 'autoconf', 'automake', 'libtool', 'libssl-dev', 'liblog4cplus-dev', 'libboost-system-dev']

        if 'unittest' in features:
            packages.append('googletest')

        if 'docs' in features:
            packages.extend(['dblatex', 'xsltproc', 'elinks'])

        if 'native-pkg' in features:
            packages.extend(['build-essential', 'fakeroot', 'devscripts'])
            packages.extend(['bison', 'debhelper', 'default-libmysqlclient-dev', 'libmysqlclient-dev', 'docbook', 'docbook-xsl', 'flex', 'libboost-dev',
                             'libpq-dev', 'postgresql-server-dev-all', 'python3-dev'])

        execute('apt install --no-install-recommends -y %s' % ' '.join(packages), timeout=240)

    elif system == 'debian':
        execute('apt update')

        packages = ['gcc', 'g++', 'make', 'autoconf', 'automake', 'libtool', 'libssl-dev', 'liblog4cplus-dev', 'libboost-system-dev']

        if 'docs' in features:
            packages.extend(['dblatex', 'xsltproc', 'elinks'])

        if 'unittest' in features:
            if revision == '8':
                packages.append('libgtest-dev')
            else:
                packages.append('googletest')

        execute('apt install --no-install-recommends -y %s' % ' '.join(packages), timeout=240)

    elif system == 'freebsd':
        packages = ['autoconf', 'automake', 'libtool', 'openssl', 'log4cplus', 'boost-libs']
        execute('pkg install -y %s' % ' '.join(packages), timeout=240)

        #execute('portsnap --interactive fetch', timeout=240)
        #execute('portsnap extract /usr/ports/devel/log4cplus', timeout=240)

        #execute('make -C /usr/ports/devel/log4cplus install clean BATCH=yes', timeout=240)

        if 'unittest' in features:
            _install_gtest_sources()

    else:
        raise NotImplementedError


def build_local(features, tarball_path):
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
            execute('tar -zxf %s' % tarball_path, cwd='kea-src')
            src_path = glob.glob('kea-src/*')[0]
            rpm_dir = os.path.join(src_path, 'rpm')
            for f in os.listdir(rpm_dir):
                if f == 'kea.spec':
                    continue
                execute('cp %s rpm-root/SOURCES' % os.path.join(rpm_dir, f))
            execute('cp %s rpm-root/SPECS' % os.path.join(rpm_dir, 'kea.spec'))
            execute('cp %s rpm-root/SOURCES' % tarball_path)

            cmd = "rpmbuild -ba rpm-root/SPECS/kea.spec -D'_topdir /home/vagrant/rpm-root'"
            execute(cmd, env=env, timeout=60 * 40)

            if 'install' in features:
                execute('sudo rpm -i rpm-root/RPMS/x86_64/*rpm')

        elif distro in ['ubuntu', 'debian']:
            execute('rm -rf kea-src')
            os.mkdir('kea-src')
            execute('tar -zxf %s' % tarball_path, cwd='kea-src')
            src_path = glob.glob('kea-src/*')[0]

            execute('debuild -i -us -uc -b', env=env, cwd=src_path, timeout=60 * 40)

            if 'install' in features:
                execute('sudo dpkg -i kea-src/*deb')

        else:
            raise NotImplementedError

    else:
        # build straight from sources

        if tarball_path:
            execute('rm -rf kea-src')
            os.mkdir('kea-src')
            execute('tar -zxf %s' % tarball_path, cwd='kea-src')
            src_path = glob.glob('kea-src/*')[0]
        else:
            src_path = '.'

        execute('autoreconf -f -i', cwd=src_path, env=env)

        cmd = './configure'
        if 'mysql' in features:
            cmd += ' --with-mysql'
        if 'pgsql' in features:
            cmd += ' --with-pgsql'
        if 'unittest' in features:
            if distro in ['centos', 'fedora', 'freebsd']:
                cmd += ' --with-gtest-source=/usr/src/googletest-release-1.8.0/googletest/'
            elif distro == 'debian' and revision == '8':
                cmd += ' --with-gtest-source=/usr/src/gtest'
            elif distro in ['debian', 'ubuntu']:
                cmd += ' --with-gtest-source=/usr/src/googletest/googletest'
            else:
                raise NotImplementedError
        if 'docs' in features:
            cmd += ' --enable-generate-docs'

        if distro == 'freebsd':
            cmd += ' --with-boost-include=/usr/local/include'  # TODO: this should be fixed in ./configure.ac
            cmd += ' --with-boost-lib-dir=/usr/local/lib'      # TODO: this should be fixed in ./configure.ac

        execute(cmd, cwd=src_path, env=env)

        cpus = multiprocessing.cpu_count() - 1
        if distro == 'centos':
            cpus = cpus // 2
        if cpus == 0:
            cpus = 1
        cmd = 'make -j%s' % cpus
        execute(cmd, cwd=src_path, env=env, timeout=60 * 40)  # TODO 6,      timeout: 40mins

        if 'unittest' in features:
            execute('make check', cwd=src_path, env=env, timeout=60 * 60, raise_error=False)

        if 'install' in features:
            execute('sudo make install', cwd=src_path, env=env)

    execute('df -h')


def build_in_vagrant(provider, system, sys_revision, features, leave_system, tarball_path):
    log.info('')
    log.info(">>> Building %s, %s, %s" % (provider, system, sys_revision))
    log.info('')

    t0 = time.time()

    error = False
    try:
        ve = VagrantEnv(provider, system, sys_revision, features, leave_system, 'kea')
        ve.up()
        ve.prepare_deps(features)
        ve.run_build_and_test(tarball_path)
    except:
        log.exception('building failed')
        error = True

    t1 = time.time()
    dt = int(t1 - t0)

    log.info('')
    log.info(">>> Building %s, %s, %s completed in %s:%s", provider, system, sys_revision, dt // 60, dt % 60)
    log.info('')

    return dt, error


def package_box(provider, system, sys_revision, features):
    ve = VagrantEnv(provider, system, sys_revision, features, False, 'bare')
    ve.up()
    ve.prepare_deps(features)
    ve.package()


def prepare_system(provider, system, sys_revision, features):
    ve = VagrantEnv(provider, system, sys_revision, features, False, 'kea')
    ve.up()
    ve.prepare_deps(features)
    # TODO remove kea-src


def ssh(provider, system, sys_revision, features):
    ve = VagrantEnv(provider, system, sys_revision, features, False, 'kea')
    ve.up()
    ve.prepare_deps(features)
    ve.ssh()


DEFAULT_FEATURES = ['install', 'unittest', 'docs']
ALL_FEATURES = ['install', 'unittest', 'docs', 'mysql', 'pgsql', 'native-pkg']

def parse_args():
    parser = argparse.ArgumentParser(description='Kea develepment environment management tool.')

    parser.add_argument('command', choices=['package-box', 'prepare-system', 'build', 'prepare-deps', 'list-systems', 'ssh'],
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
                        help='At the end of command do not destroy vagrant system. Default behavior is destroing the system.')
    parser.add_argument('-t', '--from-tarball',
                        help='Instead of building sources in current folder use provided tarball package (e.g. tar.gz).')
    parser.add_argument('-v', '--verbose', action='store_true', help='Enable verbose mode.')

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


def _print_summary(results):
    print("")
    print("+===== Hammer Summary ====================================+")
    print("|   provider |     system | revision |  duration | status |")
    print("+------------+------------+----------+-----------+--------+")
    total_dt = 0
    for key, result in results.items():
        provider, system, revision = key
        dt, error = result
        total_dt += dt
        status = ' \033[1;31merror\033[0;0m' if error else '    \033[0;32mok\033[0;0m'
        print('| %10s | %10s | %8s | %6d:%02d | %s |' % (provider, system, revision, dt // 60, dt % 60, status))
    print("+------------+------------+----------+-----------+--------+")
    print("|                               Total: %6d:%02d |        |" % (total_dt // 60, total_dt % 60))
    print("+=========================================================+")


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
        package_box(args.provider, args.system, args.revision, features)

    elif args.command == "prepare-system":
        log.info('Enabled features: %s', ' '.join(features))
        prepare_system(args.provider, args.system, args.revision, features)

    elif args.command == "build":
        log.info('Enabled features: %s', ' '.join(features))
        if args.provider == 'local':
            build_local(features, args.from_tarball)
            return

        if args.provider == 'all':
            providers = ['lxc', 'virtualbox']
        else:
            providers = [args.provider]

        if args.system == 'all':
            systems = SYSTEMS.keys()
        else:
            systems = [args.system]

        results = {}
        fail = False
        for provider in providers:
            for system in systems:
                if args.revision == 'all':
                    revisions = SYSTEMS[system]
                else:
                    revisions = [args.revision]

                for revision in revisions:
                    duration, error = build_in_vagrant(provider, system, revision, features, args.leave_system, args.from_tarball)
                    results[(provider, system, revision)] = (duration, error)
                    if error:
                        fail = True

        _print_summary(results)

        if fail:
            sys.exit(1)

    elif args.command == "prepare-deps":
        log.info('Enabled features: %s', ' '.join(features))
        prepare_deps(features)

    elif args.command == "ssh":
        ssh(args.provider, args.system, args.revision, features)


if __name__ == '__main__':
    # results = {
    #     ('virtualbox', 'centos', '7'): (920, False),
    #     ('lxc', 'fedora', '29'): (120, False),
    # }
    # _print_summary(results)

    main()
