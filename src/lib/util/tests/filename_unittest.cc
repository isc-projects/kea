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

#include <string>

#include <gtest/gtest.h>

#include <util/filename.h>

using namespace isc;
using namespace isc::util;
using namespace std;

class FilenameTest : public ::testing::Test {
protected:
    FilenameTest()
    {
    }
};


// Check that the name can be changed

TEST_F(FilenameTest, SetName) {
    Filename fname("/a/b/c.d");
    EXPECT_EQ("/a/b/c.d", fname.fullName());

    fname.setName("test.txt");
    EXPECT_EQ("test.txt", fname.fullName());
}


// Check that the components are split correctly.  This is a check of the
// private member split() method.

TEST_F(FilenameTest, Components) {

    // Complete name
    Filename fname("/alpha/beta/gamma.delta");
    EXPECT_EQ("/alpha/beta/", fname.directory());
    EXPECT_EQ("gamma", fname.name());
    EXPECT_EQ(".delta", fname.extension());

    // Directory only
    fname.setName("/gamma/delta/");
    EXPECT_EQ("/gamma/delta/", fname.directory());
    EXPECT_EQ("", fname.name());
    EXPECT_EQ("", fname.extension());

    // Filename only
    fname.setName("epsilon");
    EXPECT_EQ("", fname.directory());
    EXPECT_EQ("epsilon", fname.name());
    EXPECT_EQ("", fname.extension());

    // Extension only
    fname.setName(".zeta");
    EXPECT_EQ("", fname.directory());
    EXPECT_EQ("", fname.name());
    EXPECT_EQ(".zeta", fname.extension());

    // Missing directory
    fname.setName("eta.theta");
    EXPECT_EQ("", fname.directory());
    EXPECT_EQ("eta", fname.name());
    EXPECT_EQ(".theta", fname.extension());

    // Missing filename
    fname.setName("/iota/.kappa");
    EXPECT_EQ("/iota/", fname.directory());
    EXPECT_EQ("", fname.name());
    EXPECT_EQ(".kappa", fname.extension());

    // Missing extension
    fname.setName("lambda/mu/nu");
    EXPECT_EQ("lambda/mu/", fname.directory());
    EXPECT_EQ("nu", fname.name());
    EXPECT_EQ("", fname.extension());

    // Check that the decomposition can occur in the presence of leading and
    // trailing spaces
    fname.setName("  lambda/mu/nu\t  ");
    EXPECT_EQ("lambda/mu/", fname.directory());
    EXPECT_EQ("nu", fname.name());
    EXPECT_EQ("", fname.extension());

    // Empty string
    fname.setName("");
    EXPECT_EQ("", fname.directory());
    EXPECT_EQ("", fname.name());
    EXPECT_EQ("", fname.extension());

    // ... and just spaces
    fname.setName("  ");
    EXPECT_EQ("", fname.directory());
    EXPECT_EQ("", fname.name());
    EXPECT_EQ("", fname.extension());

    // Check corner cases - where separators are present, but strings are
    // absent.
    fname.setName("/");
    EXPECT_EQ("/", fname.directory());
    EXPECT_EQ("", fname.name());
    EXPECT_EQ("", fname.extension());

    fname.setName(".");
    EXPECT_EQ("", fname.directory());
    EXPECT_EQ("", fname.name());
    EXPECT_EQ(".", fname.extension());

    fname.setName("/.");
    EXPECT_EQ("/", fname.directory());
    EXPECT_EQ("", fname.name());
    EXPECT_EQ(".", fname.extension());

    // Note that the space is a valid filename here; only leading and trailing
    // spaces should be trimmed.
    fname.setName("/ .");
    EXPECT_EQ("/", fname.directory());
    EXPECT_EQ(" ", fname.name());
    EXPECT_EQ(".", fname.extension());

    fname.setName(" / . ");
    EXPECT_EQ("/", fname.directory());
    EXPECT_EQ(" ", fname.name());
    EXPECT_EQ(".", fname.extension());
}

// Check that the expansion with a default works.

TEST_F(FilenameTest, ExpandWithDefault) {
    Filename fname("a.b");

    // These tests also check that the trimming of the default component is
    // done properly.
    EXPECT_EQ("/c/d/a.b", fname.expandWithDefault(" /c/d/  "));
    EXPECT_EQ("/c/d/a.b", fname.expandWithDefault("/c/d/e.f"));
    EXPECT_EQ("a.b", fname.expandWithDefault("e.f"));

    fname.setName("/a/b/c");
    EXPECT_EQ("/a/b/c.d", fname.expandWithDefault(".d"));
    EXPECT_EQ("/a/b/c.d", fname.expandWithDefault("x.d"));
    EXPECT_EQ("/a/b/c.d", fname.expandWithDefault("/s/t/u.d"));
    EXPECT_EQ("/a/b/c", fname.expandWithDefault("/s/t/u"));

    fname.setName(".h");
    EXPECT_EQ("/a/b/c.h", fname.expandWithDefault("/a/b/c.msg"));
}

// Check that we can use this as a default in expanding a filename

TEST_F(FilenameTest, UseAsDefault) {

    Filename fname("a.b");

    // These tests also check that the trimming of the default component is
    // done properly.
    EXPECT_EQ("/c/d/a.b", fname.useAsDefault(" /c/d/  "));
    EXPECT_EQ("/c/d/e.f", fname.useAsDefault("/c/d/e.f"));
    EXPECT_EQ("e.f", fname.useAsDefault("e.f"));

    fname.setName("/a/b/c");
    EXPECT_EQ("/a/b/c.d", fname.useAsDefault(".d"));
    EXPECT_EQ("/a/b/x.d", fname.useAsDefault("x.d"));
    EXPECT_EQ("/s/t/u.d", fname.useAsDefault("/s/t/u.d"));
    EXPECT_EQ("/s/t/u", fname.useAsDefault("/s/t/u"));
    EXPECT_EQ("/a/b/c", fname.useAsDefault(""));
}

TEST_F(FilenameTest, setDirectory) {
    Filename fname("a.b");
    EXPECT_EQ("", fname.directory());
    EXPECT_EQ("a.b", fname.fullName());
    EXPECT_EQ("a.b", fname.expandWithDefault(""));

    fname.setDirectory("/just/some/dir/");
    EXPECT_EQ("/just/some/dir/", fname.directory());
    EXPECT_EQ("/just/some/dir/a.b", fname.fullName());
    EXPECT_EQ("/just/some/dir/a.b", fname.expandWithDefault(""));

    fname.setDirectory("/just/some/dir");
    EXPECT_EQ("/just/some/dir/", fname.directory());
    EXPECT_EQ("/just/some/dir/a.b", fname.fullName());
    EXPECT_EQ("/just/some/dir/a.b", fname.expandWithDefault(""));

    fname.setDirectory("/");
    EXPECT_EQ("/", fname.directory());
    EXPECT_EQ("/a.b", fname.fullName());
    EXPECT_EQ("/a.b", fname.expandWithDefault(""));

    fname.setDirectory("");
    EXPECT_EQ("", fname.directory());
    EXPECT_EQ("a.b", fname.fullName());
    EXPECT_EQ("a.b", fname.expandWithDefault(""));

    fname = Filename("/first/a.b");
    EXPECT_EQ("/first/", fname.directory());
    EXPECT_EQ("/first/a.b", fname.fullName());
    EXPECT_EQ("/first/a.b", fname.expandWithDefault(""));

    fname.setDirectory("/just/some/dir");
    EXPECT_EQ("/just/some/dir/", fname.directory());
    EXPECT_EQ("/just/some/dir/a.b", fname.fullName());
    EXPECT_EQ("/just/some/dir/a.b", fname.expandWithDefault(""));
}
