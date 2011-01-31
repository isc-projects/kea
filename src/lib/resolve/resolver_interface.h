// Copyright (C) 2010  CZ NIC
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

#ifndef __RESOLVER_INTERFACE_H
#define __RESOLVER_INTERFACE_H

#include <dns/message.h>

/**
 * \file resolver_interface.h
 * \short Temporary interface to resolver.
 *
 * This file contains a dummy interface for the resolver, which does not yet
 * exist. When the resolver appears, this file should either wrap its
 * interface or, better, be removed completely.
 *
 * Currently left in while moving interfaces and classes around
 */

namespace isc {
namespace resolve {

/**
 * \short Abstract interface to the resolver.
 *
 * Abstract interface to the resolver. The NameserverAddressStore uses this
 * to ask for addresses. It is here because resolver does not yet exist.
 *
 * It is abstract to allow tests pass dummy resolvers.
 */
class ResolverInterface {
    public:
        /// \short An abstract callback when data from resolver are ready.
        class Callback {
            public:
                /// \short Some data arrived.
                virtual void success(isc::dns::MessagePtr response) = 0;
                
                /**
                 * \short No data available.
                 *
                 * \todo Pass some reason.
                 */
                virtual void failure() = 0;
                /// \short Virtual destructor, so descendants are cleaned up
                virtual ~ Callback() {};
        };
        typedef boost::shared_ptr<Callback> CallbackPtr;
        /**
         * \short Ask a question.
         *
         * Asks the resolver a question. Once the answer is ready
         * the callback is called.
         *
         * \param question What to ask. The resolver will decide who.
         * \param callback What should happen when the answer is ready.
         */
        virtual void resolve(const isc::dns::QuestionPtr& question,
            const CallbackPtr& callback) = 0;
        /// \short Virtual destructor, so descendants are properly cleaned up
        virtual ~ ResolverInterface() {}
};

} // namespace nsas
} // namespace isc

#endif //__RESOLVER_INTERFACE_H
