// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef SIGNAL_SET_H
#define SIGNAL_SET_H

#include <exceptions/exceptions.h>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <set>
#include <signal.h>

namespace isc {
namespace util {
namespace io {

class SignalSetError : public Exception {
public:
    SignalSetError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

class SignalSet;

typedef boost::shared_ptr<SignalSet> SignalSetPtr;

typedef boost::function<void(int signum)> SignalHandler;

class SignalSet : public boost::noncopyable {
private:
    typedef std::set<int> Pool;

public:

    SignalSet(const int sig0);

    SignalSet(const int sig0, const int sig1);

    SignalSet(const int sig0, const int sig1, const int sig2);

    /// @throw SignalSetError if signal being added duplicates an existing
    /// signal.
    void add(const int sig);

    void clear();

    int getNext() const;

    void handleNext(SignalHandler signal_handler);

    void remove(const int sig);

private:

    void block() const {
        maskSignals(SIG_BLOCK);
    }

    Pool::iterator erase(const int signal);

    void maskSignals(const int mask) const;

    void popNext() const;

    void unblock() const {
        maskSignals(SIG_UNBLOCK);
    }

    Pool registered_signals_;
};

}
}
}

#endif // SIGNAL_SET_H

