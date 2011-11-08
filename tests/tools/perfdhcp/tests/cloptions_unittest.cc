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

#include "../cloptions.h"

int checkOption(const char* optflag, const char* optval,
                confdata_t* confdata, int retExpected) {
    const char* argv[] = { "perfdhcp", NULL, NULL, NULL };
    int argc = 1;
    const char* server;
    int ret;

    argv[argc++] = optflag;
    if (optval != NULL) {
        argv[argc++] = optval;
    }
    argv[argc++] = "foo";   /* server */
    ret = procArgs(argc, argv, confdata, &server);
    EXPECT_EQ(ret, retExpected);
    return ret == retExpected;
}

void checkOptionInvalid(const char* optflag, const char* optval) {
    confdata_t confdata;

    checkOption(optflag, optval, &confdata, 2);
}

int checkOptionValid(const char* optflag, const char* optval,
                     confdata_t* confdata) {

    return checkOption(optflag, optval, confdata, 1);
}

void checkPosFloatOpt(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, "100.0", &confdata))
        EXPECT_EQ(100.0,
                  confdata.map[(unsigned)optflag[1]]->values[0]->value.floatval);
    checkOptionInvalid(optflag, "0");
    checkOptionInvalid(optflag, "-1");
    checkOptionInvalid(optflag, "0.0");
    checkOptionInvalid(optflag, "-1.0");
    checkOptionInvalid(optflag, "x");
}

void checkPosIntOpt(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, "100", &confdata))
        EXPECT_EQ(100,
                  confdata.map[(unsigned)optflag[1]]->values[0]->value.nnint);
    checkOptionInvalid(optflag, "0");
    checkOptionInvalid(optflag, "-1");
    checkOptionInvalid(optflag, "1.0");
    checkOptionInvalid(optflag, "x");
}

void checkFlag(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, NULL, &confdata))
        EXPECT_EQ(1,
                  confdata.map[(unsigned)optflag[1]]->values[0]->value.switchval);
}

void checkStrOpt(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, "bar", &confdata))
        EXPECT_EQ("bar",
                  confdata.map[(unsigned)optflag[1]]->values[0]->value.string);
}

void checkNEStrOpt(const char* optflag) {
    confdata_t confdata;

    if (checkOptionValid(optflag, "bar", &confdata))
        EXPECT_EQ("bar",
                  confdata.map[(unsigned)optflag[1]]->values[0]->value.string);
    checkOptionInvalid(optflag, "");
}

void checkFlagHandled(const char* optflag) {
    confdata_t confdata;

    checkOption(optflag, NULL, &confdata, 0);
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
