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

#ifndef ISC_SERVER_COMMON_KEYRING_H
#define ISC_SERVER_COMMON_KEYRING_H

#include <boost/shared_ptr.hpp>
#include <dns/tsigkey.h>
#include <config/ccsession.h>

/**
 * \file keyring.h
 * \brief TSIG keyring loaded from configuration.
 *
 * This file contains routines for loading a TSIG key ring from
 * the tsig_keys configuration section and keeping them up to date
 * on updates.
 *
 * You simply initialize/load the keyring with isc::server_common::initKeyring
 * and then just use the key ring referred to by isc::server_common::keyring. It
 * is automatically reloaded, when the configuration updates, so you no longer
 * needs to care about it.
 *
 * If you want to keep a key (or session) for longer time or your application
 * is multithreaded, you might want to have a copy of the shared pointer to
 * hold a reference. Otherwise an update might replace the keyring and delete
 * the keys in the old one.
 *
 * Also note that, while the interface doesn't prevent application from
 * modifying the keyring, it is not a good idea to do so. As mentioned above,
 * it might get reloaded at any time, which would replace the modified keyring.
 * The possibility to modify it is side effect of simpler implementation and
 * shorter code, not a goal.
 */

namespace isc {

namespace server_common {

/**
 * \brief The key ring itself
 *
 * This is where the key ring is stored. You can directly use it to your needs,
 * but you need to call initKeyring first, otherwise you'll find a NULL pointer
 * here only.
 */
extern boost::shared_ptr<dns::TSIGKeyRing> keyring;

/**
 * \brief Load the key ring for the first time
 *
 * This loads the key ring from configuration to keyring. It also registers for
 * config updates, so from now on, it'll be kept up to date.
 *
 * You can unload the key ring with deinitKeyring.
 *
 * If it is already loaded, this function does nothing. So, if more than one
 * part of an application needs to use the key ring, they all can just call
 * this independently to ensure the keyring is loaded.
 *
 * \param session The configuration session used to talk to the config manager.
 */
void
initKeyring(config::ModuleCCSession& session);

/**
 * \brief Unload the key ring
 *
 * This can be used to unload the key ring. It will reset the keyring to NULL
 * and stop receiving updates of the configuration.
 *
 * The need for this function should be quite rare, as it isn't required to be
 * called before application shutdown. And not calling it has only small
 * performance penalty -- the keyring will be kept in memory and updated when
 * the user changes configuration.
 *
 * This does nothing if the key ring is not loaded currently.
 *
 * \param session The configuration session used to talk to the config manager.
 *
 * \todo What do we do when the data that come are invalid? Should we ignore it,
 *     as walidity should have been checked already in the config manager, or
 *     throw? What about when we get an update and it's invalid?
 */
void
deinitKeyring(config::ModuleCCSession& session);

}
}

#endif
