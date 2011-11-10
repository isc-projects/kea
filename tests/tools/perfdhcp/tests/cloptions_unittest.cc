// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <stdint.h>
#include <gtest/gtest.h>
#include <exceptions/exceptions.h>
#include <stdarg.h>

#include "../cloptions.h"
#include "../perfdhcp.h"
#include "../dkdebug.h"

// Up to 4 arguments may be specified
// The final argument must be NULL.  This is not counted in the 4 arguments.
int checkOption(int retExpected, ...) {
    const char* argv[6] = { "perfdhcp" };
    int argc = 1;
    int ret;
    const char* p;
    va_list ap;

    va_start(ap, retExpected);
    p = va_arg(ap, const char *);
    while (p != NULL && argc < 5) {
        argv[argc++] = p;
        p = va_arg(ap, const char *);
    }
    va_end(ap);
    argv[argc++] = "foo";   /* server */
    ret = procArgs(argc, argv);
    EXPECT_EQ(ret, retExpected);
    return(ret == retExpected);
}

void checkOptionInvalid(const char* optflag, const char* optval) {
    checkOption(2, optflag, optval, NULL);
}

int checkOptionValid(const char* optflag, const char* optval) {

    return(checkOption(1, optflag, optval, NULL));
}

void checkPosFloatOpt(const char* optflag, double (*retfunc)(void)) {
    if (checkOptionValid(optflag, "100.0")) {
        EXPECT_EQ(100.0, (*retfunc)());
    }
    checkOptionInvalid(optflag, "0");
    checkOptionInvalid(optflag, "-1");
    checkOptionInvalid(optflag, "0.0");
    checkOptionInvalid(optflag, "-1.0");
    checkOptionInvalid(optflag, "x");
}

void checkPosIntOpt(const char* optflag, unsigned (*retfunc)(void)) {
    if (checkOptionValid(optflag, "100")) {
        EXPECT_EQ(100, (*retfunc)());
    }
    checkOptionInvalid(optflag, "0");
    checkOptionInvalid(optflag, "-1");
    checkOptionInvalid(optflag, "1.0");
    checkOptionInvalid(optflag, "x");
}

void checkFlag(const char* optflag, int (*retfunc)(void)) {
    if (checkOptionValid(optflag, NULL)) {
        EXPECT_EQ(1, (*retfunc)());
    }
}

void checkStrOpt(const char* optflag, const char *(*retfunc)(void)) {
    if (checkOptionValid(optflag, "bar")) {
        EXPECT_EQ("bar", (*retfunc)());
    }
}

void checkNEStrOpt(const char* optflag, const char *(*retfunc)(void)) {
    if (checkOptionValid(optflag, "bar")) {
        EXPECT_EQ("bar", (*retfunc)());
    }
    checkOptionInvalid(optflag, "");
}

void checkFlagHandled(const char* optflag) {
    checkOption(0, optflag, NULL);
}

// Command line option tests

TEST(CommandOptionsTest, numreq) {
    checkPosIntOpt("-n", getnumRequest);
}

TEST(CommandOptionsTest, rate) {
    checkPosIntOpt("-r", getrate);
}

TEST(CommandOptionsTest, droptime) {
    checkPosFloatOpt("-d", getdropTime);
}

TEST(CommandOptionsTest, period) {
    checkPosFloatOpt("-p", gettestPeriod);
}

TEST(CommandOptionsTest, help) {
    checkFlagHandled("-h");
}

TEST(CommandOptionsTest, version) {
    checkFlagHandled("-v");
}

TEST(CommandOptionsTest, v4) {
    if (checkOptionValid("-4", NULL)) {
        EXPECT_EQ(0, getv6());
    }
}

TEST(CommandOptionsTest, v6) {
    checkFlag("-6", getv6);
}

TEST(CommandOptionsTest, initial) {
    checkFlag("-i", getinitialOnly);
}

TEST(CommandOptionsTest, localname) {
    checkNEStrOpt("-l", getlocalName);
}

TEST(CommandOptionsTest, diagnostics) {
    if (checkOptionValid("-x", "sm")) {
        EXPECT_EQ(1, dk_set(DK_SOCK));
        EXPECT_EQ(1, dk_set(DK_MSG));
        EXPECT_EQ(0, dk_set(DK_PACKET));
    }
    checkOptionInvalid("-x", "z");
}

TEST(CommandOptionsTest, maxdrop) {
    checkNEStrOpt("-D", getmaxDrop);
}

/*
 * NOTE: GNU getopt() as of 2011-11-07 is subject to a bug that causes it to
 * break if called with an invalid option followed by another call with optind
 * re-initialiation.  The code in this module currently doesn't exercise the
 * bug, but it is highly sensitive to run-time conditions (stack layout etc.)
 */
TEST(CommandOptionsTest, nosuchopt) {
    checkOptionInvalid("-W", "");
}

TEST(CommandOptionsTest, v4v6) {
    checkOptionInvalid("-4", "-6");
}

TEST(CommandOptionsTest, ilr6) {
    if (checkOption(1, "-6i", "-leth0", "-r", "50", NULL)) {
        EXPECT_EQ("eth0", getlocalName());
        EXPECT_EQ(50, getrate());
        EXPECT_EQ(1, getv6());
        EXPECT_EQ(1, getinitialOnly());
    }
}

TEST(CommandOptionsTest, ind) {
    if (checkOption(1, "-i", "-n10", "-d", "5", NULL)) {
        EXPECT_EQ(1, getinitialOnly());
        EXPECT_EQ(10, getnumRequest());
        EXPECT_EQ(5, getdropTime());
    }
}

TEST(CommandOptionsTest, px) {
    if (checkOption(1, "-p", "5.5", "-x", "a", NULL)) {
        EXPECT_EQ(5.5, gettestPeriod());
        EXPECT_EQ(1, dk_set(DK_SOCK));
        EXPECT_EQ(1, dk_set(DK_MSG));
        EXPECT_EQ(1, dk_set(DK_PACKET));
    }
}
