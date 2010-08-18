// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __BENCHMARK_UTIL_H
#define __BENCHMARK_UTIL_H 1

/// \file
/// Utilities to help write benchmark cases.
///
/// The initial version of this library only contains utilities for very
/// specific benchmark cases, that is, building DNS query data.
/// It's not clear if we have more utilities including scenario-independent
/// ones in future, but we have them here for now.
/// If we find we only need utilities specific to individual benchmark
/// scenarios, we may move them to more specific places.
/// For example, the query generator may go to benchmarks for DNS server
/// implementations.

#include <istream>
#include <vector>

#include <exceptions/exceptions.h>

namespace isc {
namespace dns {
class RRClass;
}

namespace bench {
/// \brief An exception that is thrown if an error occurs within the benchmark
/// module.
class BenchMarkError : public Exception {
public:
    BenchMarkError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief A convenient shortcut type to represent a sequence of query %data
/// in wire format.
typedef std::vector<std::vector<unsigned char> > BenchQueries; 

/// \brief Load query %data from a file into a vector.
///
/// The format of the %data file is a sequence of tuples of query name and
/// query type.  Each line specifies a single tuple.  Empty lines and
/// lines beginning with a pound sign (#) are considered comments and will
/// be ignored.  Example:
/// \code
/// # This is a comment line, will be ignored.  same for the next line.
///
/// www.example.com AAAA
/// ftp.example.org NS
/// text.dot.example TXT \endcode
///
/// For those who are familiar with BIND 9's queryperf tool, this is the
/// same as the simplest form of the input file for queryperf.
///
/// For each tuple, this function builds a wire-format non recursive DNS
/// query message, and appends it to the given vector in a form of
/// a vector of <code>unsigned char</code>.
///
/// The resulting vector can be used, e.g., for benchmarking query processing
/// code without involving disk access or network I/O.
/// It would be handier than existing tool such as queryperf and can help
/// measure the "bare" (or the best possible) performance of the query
/// processing itself.
///
/// If this function fails to open the specified file to read the %data,
/// an exception of class \c BenchMarkError will be thrown.
/// If it fails to recognize an input line either as a comment or as
/// a tuple of strings, an exception of class \c BenchMarkError will be
/// thrown.
///
/// By default, this function does not require the strings be a valid
/// domain name or a valid textual representation of an RR type.
/// This is because the input %data may be built from a packet dump of
/// real query samples without validation, which may contain bogus values.
/// It would make more sense to just ignore the bogus %data than filter
/// the sample beforehand.
/// This behavior can be changed by setting the \c strict argument to
/// \c true, in which case if this function fails to parse the query name
/// or the type, it will throw an exception of class \c BenchMarkError.
///
/// If memory allocation fails during the processing, a corresponding standard
/// exception will be thrown.
///
/// This function only offers the basic exception guarantee.  That is, if
/// exception is thrown from this function, it is not guaranteed that
/// \c queries keeps the content before this function is called.
/// It is not so difficult to offer a stronger exception guarantee, but
/// since this function is used in a limited usage, mainly for testing
/// purposes, its benefit wouldn't outweigh the implementation complexity.
///
/// \param input_file A character string specifying the %data file name.
/// \param queries A vector wherein the query %data is to be stored.
/// \param qclass The RR class of the resulting queries.  The same RR class
/// is used for all queries.
/// \param strict If \c true, apply stricter validation on the query name and
/// query RR types; otherwise invalid inputs will be ignored.
void loadQueryData(const char* const input_file, BenchQueries& queries,
                   const isc::dns::RRClass& qclass, const bool strict = false);

/// \brief Load query %data from an input stream into a vector.
///
/// This version of function is same as
/// loadQueryData(const char*,  BenchQueries&, const isc::dns::RRClass&, const bool)
/// except it reads the input query sequence from a specified input stream.
///
/// This version will be used for a smaller scale test where query %data is
///  hardcoded in the benchmark source code.  For example, we could build
/// a sequence of wire-format queries via the following code:
/// \code
///    vector<QueryParam> queries;
///    stringstream qstream;
///    qstream << "www.example.com AAAA" << endl
///            << "ftp.example.org NS" << endl
///            << "text.dot.example TXT" << endl;
///    loadQueryData(qstream, queries, RRClass::IN()); \endcode
/// This will result in the same sequence of queries as the example using
/// a %data file shown in the other version of the function.
///
/// \param input An input stream object that is to emit the query sequence.
/// \param queries A vector wherein the query %data is to be stored.
/// \param qclass The RR class of the resulting queries.  The same RR class
/// is used for all queries.
/// \param strict If \c true, apply stricter validation on the query name and
/// query RR types; otherwise invalid inputs will be ignored.
void loadQueryData(std::istream& input, BenchQueries& queries,
                   const isc::dns::RRClass& qclass, const bool strict = false);
}
}
#endif  // __BENCHMARK_UTIL_H

// Local Variables: 
// mode: c++
// End: 
