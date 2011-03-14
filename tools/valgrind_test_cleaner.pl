#!/usr/bin/perl
use strict;
use warnings;

# This script can be used on a valgrind output of the tests (from
# tests_in_valgrind.sh) to remove some uninteresting error reports.
# Since we care about the tested application not leaking/crashing, not
# the tests itself, memory leaks that are caused only by the tests
# (eg. unreleased test data), we don't want to have logs full of them.
#
# This script does some heuristics to eliminate some of such error
# reports. Currently, the memory lost reports whose stack contains
# no call from the real application are suppressed.
#
# Of course, the rest still can contain many uninteresting entries.

# Yes, it's perl even when we use python. I wrote it for myself when
# I needed to clean the outputs and after it proved useful to me, I
# thought it might be for others too, so I just included it. It's not
# that we would be switching to perl. If it should grow in future to
# include more heuristics and do something more fancy, we should probably
# rewrite it in python instead.

my ($block, $blockOK);

sub endBlock(_) {
	return unless $block;
	if ($blockOK) {
		print @$block;
	}
	undef $block;
	undef $blockOK;
}

sub startBlock(_) {
	$block = [@_];
}

sub addToBlock(_) {
	my ($line) = @_;
	push @$block, $line;
	return unless $line =~ /^==\d+==\s+(at|by) 0x[0-9A-F]+: (.*) \(.+:\d+\)$/;
	$_ = $2;
	return $blockOK = 1 if /^isc::/;
	return $blockOK = 1 if /^asiolink:/;
	return if /^main \(/;
	return if /^testing::/;
	return if /^\(anonymous namespace\)::/;
	$blockOK = 1;
}

while(<>) {
	if (/^==\d+==\s*$/) {
		print;
		endBlock;
	} elsif (/^==\d+==\s+\d+bytes.*lost in loss record/) {
		startBlock;
	} elsif ($block) {
		addToBlock;
	} else {
		print;
	}
}
endBlock;
