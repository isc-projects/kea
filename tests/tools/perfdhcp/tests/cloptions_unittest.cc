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

// Up to 4 arguments may be specified
// The final argument must be NULL.  This is not counted in the 4 arguments.
int checkOption(confdata_t* confdata, int retExpected, ...) {
    const char* argv[6] = { "perfdhcp" };
    int argc = 1;
    const char* server;
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
    ret = procArgs(argc, argv, confdata, &server);
    EXPECT_EQ(ret, retExpected);
    return(ret == retExpected);
}

void checkOptionInvalid(const char* optflag, const char* optval) {
    confdata_t confdata;

    checkOption(&confdata, 2, optflag, optval, NULL);
}

int checkOptionValid(const char* optflag, const char* optval,
                     confdata_t* confdata) {

    return(checkOption(confdata, 1, optflag, optval, NULL));
}

void checkPosFloatOpt(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, "100.0", &confdata)) {
        EXPECT_EQ(100.0,
                  confdata.map[(unsigned)optflag[1]]->values[0]->
                  value.floatval);
    }
    checkOptionInvalid(optflag, "0");
    checkOptionInvalid(optflag, "-1");
    checkOptionInvalid(optflag, "0.0");
    checkOptionInvalid(optflag, "-1.0");
    checkOptionInvalid(optflag, "x");
}

void checkPosIntOpt(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, "100", &confdata)) {
        EXPECT_EQ(100,
                  confdata.map[(unsigned)optflag[1]]->values[0]->value.nnint);
    }
    checkOptionInvalid(optflag, "0");
    checkOptionInvalid(optflag, "-1");
    checkOptionInvalid(optflag, "1.0");
    checkOptionInvalid(optflag, "x");
}

void checkFlag(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, NULL, &confdata)) {
        EXPECT_EQ(1,
                  confdata.map[(unsigned)optflag[1]]->values[0]->
                  value.switchval);
    }
}

void checkStrOpt(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, "bar", &confdata)) {
        EXPECT_EQ("bar",
                  confdata.map[(unsigned)optflag[1]]->values[0]->value.string);
    }
}

void checkNEStrOpt(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, "bar", &confdata)) {
        EXPECT_EQ("bar",
                  confdata.map[(unsigned)optflag[1]]->values[0]->value.string);
    }
    checkOptionInvalid(optflag, "");
}

void checkFlagHandled(const char* optflag) {
    confdata_t confdata;

    checkOption(&confdata, 0, optflag, NULL);
}

TEST(CommandOptionsTest, numreq) {
    checkPosIntOpt("-n");
}

TEST(CommandOptionsTest, rate) {
    checkPosIntOpt("-r");
}

TEST(CommandOptionsTest, droptime) {
    checkPosFloatOpt("-d");
}

TEST(CommandOptionsTest, period) {
    checkPosFloatOpt("-p");
}

TEST(CommandOptionsTest, v4) {
    checkFlag("-4");
}

TEST(CommandOptionsTest, v6) {
    checkFlag("-6");
}

TEST(CommandOptionsTest, initial) {
    checkFlag("-i");
}

TEST(CommandOptionsTest, help) {
    checkFlagHandled("-h");
}

TEST(CommandOptionsTest, version) {
    checkFlagHandled("-v");
}

TEST(CommandOptionsTest, localname) {
    checkNEStrOpt("-l");
}

TEST(CommandOptionsTest, diagnostics) {
    checkStrOpt("-x");
}

TEST(CommandOptionsTest, maxdrop) {
    checkNEStrOpt("-D");
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
    confdata_t confdata;

    if (checkOption(&confdata, 1, "-6i", "-leth0", "-r", "50", NULL)) {
        EXPECT_EQ("eth0",
                  confdata.map[(unsigned)'l']->values[0]->value.string);
        EXPECT_EQ(50, confdata.map[(unsigned)'r']->values[0]->value.nnint);
        EXPECT_EQ(1, confdata.map[(unsigned)'6']->values[0]-> value.switchval);
        EXPECT_EQ(1, confdata.map[(unsigned)'i']->values[0]-> value.switchval);
    }
}

TEST(CommandOptionsTest, ind) {
    confdata_t confdata;

    if (checkOption(&confdata, 1, "-i", "-n10", "-d", "5", NULL)) {
        EXPECT_EQ(1, confdata.map[(unsigned)'i']->values[0]-> value.switchval);
        EXPECT_EQ(10, confdata.map[(unsigned)'n']->values[0]->value.nnint);
        EXPECT_EQ(5, confdata.map[(unsigned)'d']->values[0]-> value.floatval);
    }
}

TEST(CommandOptionsTest, px) {
    confdata_t confdata;

    if (checkOption(&confdata, 1, "-p", "5.5", "-x", "fo", NULL)) {
        EXPECT_EQ("fo",
                  confdata.map[(unsigned)'x']->values[0]->value.string);
        EXPECT_EQ(5.5, confdata.map[(unsigned)'p']->values[0]->value.floatval);
    }
}
