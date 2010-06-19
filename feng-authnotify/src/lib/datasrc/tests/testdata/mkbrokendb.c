/*
 * Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/* $Id$ */

/*
 * This file is provided for reference purpose only.  A broken DB file, named
 * "brokendb.sqlite3" in this directory was created using this program.
 */

#include <stdio.h>

#include <sqlite3.h>

static const char* create_statement =
	"CREATE TABLE schema_version (version INTEGER NOT NULL)";

int
main() {
	sqlite3* db = NULL;
	if (sqlite3_open("brokendb.sqlite3", &db) != 0) {
		sqlite3_close(db);
		fprintf(stderr, "failed to open sqlite3 DB");
		return (-1);
	}

	if (sqlite3_exec(db, create_statement, NULL, NULL, NULL) != SQLITE_OK) {
		fprintf(stderr, "failed to execute SQL statement: %s\n",
			create_statement);
		return (-1);
	}

	sqlite3_close(db);
	return (0);
}
