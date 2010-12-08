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

#ifndef __MASTER_H
#define __MASTER_H 1

#include <functional>
#include <istream>

#include <exceptions/exceptions.h>

#include <dns/rrset.h>

namespace isc {
namespace dns {
class RRClass;

/// TBD documentation
class MasterError : public Exception {
public:
    MasterError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class MasterLoadCallback {
public:
    /// note: this constructor is intentionally not defined as "explicit"
    /// for the convenience of the caller of \c masterLoad().
    template <typename FUNC>
    MasterLoadCallback(FUNC func) :
        func_(new FUNC(func)),
        invoker_(invoke<FUNC>),
        deleter_(cleanup<FUNC>),
        copier_(copyFunctor<FUNC>)
    {}
    MasterLoadCallback(const MasterLoadCallback& source) :
        func_((*source.copier_)(source.func_)),
        invoker_(source.invoker_),
        deleter_(source.deleter_),
        copier_(source.copier_)
    {}
    ~MasterLoadCallback() { (*deleter_)(func_); }
    void operator()(RRsetPtr rrset) {
        (*invoker_)(func_, rrset);
    }
private:
    // For our purpose, we don't need this.  Simply hide it for now.
    MasterLoadCallback& operator=(const MasterLoadCallback& source);
    
    template <typename FUNC>
    static void invoke(void* func, RRsetPtr rrset) {
        FUNC* funcobj = static_cast<FUNC*>(func);
        return ((*funcobj)(rrset));
    }
    template <typename FUNC>
    static void cleanup(void* func) {
        delete static_cast<FUNC*>(func);
    }
    template <typename FUNC>
    static void* copyFunctor(void* func) {
        return (new FUNC(*static_cast<FUNC*>(func)));
    }
    void* func_;
    void (*invoker_)(void*, RRsetPtr);
    void (*deleter_)(void*);
    void* (*copier_)(void*);
};

/// If the RR class of a given RR is different from \c zone_class,
/// an exception of class \c MasterError will be thrown.
///
/// RRSIG consideration (later)?
// may eventually want to make it a class; for now, it's not clear whether
// we need that level of abstraction.
// may want to have load options; may want to support incremental load.
// may want to support "generous" mode.
void masterLoad(const char* const filename, const RRClass& zone_class,
                MasterLoadCallback callback);

void masterLoad(std::istream& input, const RRClass& zone_class,
                MasterLoadCallback callback);
}
}

#endif  // __MASTER_H

// Local Variables:
// mode: c++
// End:
