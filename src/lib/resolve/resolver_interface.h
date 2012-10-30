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

#ifndef RESOLVER_INTERFACE_H
#define RESOLVER_INTERFACE_H

#include <dns/message.h>

///
/// \file resolver_interface.h
/// \short Interface to resolver.
///
/// This file contains an interface for the resolver. By subclassing
/// this abstract interface, other parts of the system can ask the
/// resolver to do some resolving too.
///
/// This is done by creating a subclass of ResolverInterface::Callback,
/// which defines what to do with the result, and then calling resolve()
/// on the ResolverInterface implementation.
///
/// One default Callback subclass is provided right now, in
/// resolver_callback.[h|cc], which calls resumse() on a given DNSServer
///

namespace isc {
namespace resolve {

///
/// \short Abstract interface to the resolver.
///
/// Abstract interface to the resolver. The NameserverAddressStore uses this
/// to ask for addresses. It is here because resolver does not yet exist.
///
/// It is abstract to allow tests pass dummy resolvers.
///
class ResolverInterface {
    public:
        /// \short An abstract callback for when the resolver is done.
        ///
        /// You can pass an instance of a subclass of this (as a
        /// CallbackPtr) to RecursiveQuery::sendQuery(), and when it
        /// is done, it will either call success() if there is an
        /// answer MessagePtr, or failure(), if the resolver was not
        /// able to find anything.
        ///
        /// Note that a result Message does not necessarily contain
        /// the actual answer (it could be a noerror/nodata response).
        class Callback {
            public:
                /// \short Some data arrived.
                virtual void success(const isc::dns::MessagePtr response) = 0;
                
                ///
                ///\short No data available.
                ///
                ///\todo Provide error reason (result of the
                ///      classification call, for instance? We'd also
                ///      need some way to say 'everything times out')
                ///
                virtual void failure() = 0;

                /// \short Virtual destructor, so descendants are cleaned up
                virtual ~Callback() {};
        };

        typedef boost::shared_ptr<Callback> CallbackPtr;

        ///
        ///\short Ask a question.
        ///
        /// Asks the resolver a question. Once the answer is ready
        /// the callback is called.
        ///
        /// \param question What to ask. The resolver will decide who.
        /// \param callback What should happen when the answer is ready.
        ///
        virtual void resolve(const isc::dns::QuestionPtr& question,
            const CallbackPtr& callback) = 0;

        /// \short Virtual destructor, so descendants are properly cleaned up
        virtual ~ ResolverInterface() {}
};

} // namespace nsas
} // namespace isc

#endif //RESOLVER_INTERFACE_H
