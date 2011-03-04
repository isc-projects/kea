#!/usr/bin/perl -w
#
# Copyright (C) 2004-2008, 2010  Internet Systems Consortium, Inc. ("ISC")
# Copyright (C) 2001  Internet Software Consortium.
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

# Framework for starting test servers.
# Based on the type of server specified, check for port availability, remove
# temporary files, start the server, and verify that the server is running.
# If a server is specified, start it. Otherwise, start all servers for test.

use strict;
use Cwd 'abs_path';
use Getopt::Long;

# Option handling
#   --noclean test [server [options]]
#
#   --noclean - Do not cleanup files in server directory
#   test - name of the test directory
#   server - name of the server directory
#   options - alternate options for the server

my $usage = "usage: $0 [--noclean] test-directory [server-directory [server-options]]";
my $noclean;
GetOptions('noclean' => \$noclean);
my $test = $ARGV[0];
my $server = $ARGV[1];
my $options = $ARGV[2];

if (!$test) {
	print "$usage\n";
}
if (!-d $test) {
	print "No test directory: \"$test\"\n";
}
if ($server && !-d "$test/$server") {
	print "No server directory: \"$test/$server\"\n";
}

# Global variables
my $topdir = abs_path("$test/..");
my $testdir = abs_path("$test");
my $RUN_BIND10 = $ENV{'RUN_BIND10'};
my $NAMED = $ENV{'NAMED'};
my $LWRESD = $ENV{'LWRESD'};
my $DIG = $ENV{'DIG'};
my $PERL = $ENV{'PERL'};

# Start the server(s)

if ($server) {
	if ($server =~ /^ns/) {
		&check_ports($server);
	}
	&start_server($server, $options);
	if ($server =~ /^ns/) {
		&verify_server($server);
	}
} else {
	# Determine which servers need to be started for this test.
	opendir DIR, $testdir;
	my @files = sort readdir DIR;
	closedir DIR;

	my @ns = grep /^nsx?[0-9]*$/, @files;
	my @lwresd = grep /^lwresd[0-9]*$/, @files;
	my @ans = grep /^ans[0-9]*$/, @files;

	# Start the servers we found.
	&check_ports();
	foreach my $s (@ns, @lwresd, @ans) {
		&start_server($s);
	}
	foreach my $s (@ns) {
		&verify_server($s);
	}
}

# Subroutines

sub check_ports {
	my $server = shift;
	my $options = "";

	if ($server && $server =~ /(\d+)$/) {
		$options = "-i $1";
	}

	my $tries = 0;
	while (1) {
		my $return = system("$PERL $topdir/testsock.pl -p 5300 $options");
		last if ($return == 0);
		if (++$tries > 4) {
			print "$0: could not bind to server addresses, still running?\n";
			print "I:server sockets not available\n";
			print "R:FAIL\n";
			system("$PERL $topdir/stop.pl $testdir"); # Is this the correct behavior?
			exit 1;
		}
		print "I:Couldn't bind to socket (yet)\n";
		sleep 2;
	}
}

sub start_server {
	my $server = shift;
	my $options = shift;

	my $cleanup_files;
	my $command;
	my $pid_file;

	if ($server =~ /^nsx/) {
		$cleanup_files = "{bind10.run}";
		$command = "B10_FROM_SOURCE_CONFIG_DATA_PATH=$testdir/$server/ ";
		$command .= "$RUN_BIND10 ";
		if ($options) {
			$command .= "$options";
		} else {
			$command .= "--msgq-socket-file=$testdir/$server/msgq_socket ";
			$command .= "--pid-file=$testdir/$server/bind10.pid ";
			$command .= "-v";
		}
		$command .= " >bind10.run 2>&1 &";
		$pid_file = "bind10.pid";
	} elsif ($server =~ /^ns/) {
		$cleanup_files = "{*.jnl,*.bk,*.st,named.run}";
		$command = "$NAMED ";
		if ($options) {
			$command .= "$options";
		} else {
			$command .= "-m record,size,mctx ";
			$command .= "-T clienttest ";
			$command .= "-T nosoa "
				if (-e "$testdir/$server/named.nosoa");
			$command .= "-T noaa "
				if (-e "$testdir/$server/named.noaa");
			$command .= "-c named.conf -d 99 -g";
		}
		$command .= " >named.run 2>&1 &";
		$pid_file = "named.pid";
	} elsif ($server =~ /^lwresd/) {
		$cleanup_files = "{lwresd.run}";
		$command = "$LWRESD ";
		if ($options) {
			$command .= "$options";
		} else {
			$command .= "-m record,size,mctx ";
			$command .= "-T clienttest ";
			$command .= "-C resolv.conf -d 99 -g ";
			$command .= "-i lwresd.pid -P 9210 -p 5300";
		}
		$command .= " >lwresd.run 2>&1 &";
		$pid_file = "lwresd.pid";
	} elsif ($server =~ /^ans/) {
		$cleanup_files = "{ans.run}";
		$command = "$PERL ./ans.pl ";
		if ($options) {
			$command .= "$options";
		} else {
			$command .= "";
		}
		$command .= " >ans.run 2>&1 &";
		$pid_file = "ans.pid";
	} else {
		print "I:Unknown server type $server\n";
		print "R:FAIL\n";
		system "$PERL $topdir/stop.pl $testdir";
		exit 1;
	}

	#               print "I:starting server $server\n";

	chdir "$testdir/$server";

	unless ($noclean) {
		unlink glob $cleanup_files;
	}

	system "$command";

	my $tries = 0;
	while (!-f $pid_file) {
		if (++$tries > 14) {
			print "I:Couldn't start server $server\n";
			print "R:FAIL\n";
			system "$PERL $topdir/stop.pl $testdir";
			exit 1;
		}
		sleep 1;
	}
}

sub verify_server {
	my $server = shift;
	my $n = $server;
	$n =~ s/^nsx?//;

	my $tries = 0;
	while (1) {
		my $return = system("$DIG +tcp +noadd +nosea +nostat +noquest +nocomm +nocmd -p 5300 version.bind. chaos txt \@10.53.0.$n > dig.out");
		last if ($return == 0);
		print `grep ";" dig.out`;
		if (++$tries >= 30) {
			print "I:no response from $server\n";
			print "R:FAIL\n";
			system("$PERL $topdir/stop.pl $testdir");
			exit 1;
		}
		sleep 2;
	}
	unlink "dig.out";
}

sub get_bind10_pid {
	my $runfile = shift;
	my $pidfile = shift;
	my $pid;

	return if (!-f $runfile);
	open(RUNFILE, $runfile) || return;
	while (<RUNFILE>) {
		if (/BIND 10 started \(PID ([\d]+)\)/) {
			$pid = $1;
			last;
		}
	}
	close(RUNFILE);
	if ($pid) {
		open(PIDFILE, ">$pidfile") || return;
		print PIDFILE "$pid\n";
		close(PIDFILE);
	}
}
