#!/usr/bin/perl
use strict;
use warnings;

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
