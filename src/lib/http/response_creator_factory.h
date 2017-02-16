// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_CREATOR_FACTORY_H
#define HTTP_RESPONSE_CREATOR_FACTORY_H

#include <http/response_creator.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace http {

/// @brief Specifies the interface for implementing custom factory classes
/// used to create instances of @ref HttpResponseCreator.
///
/// The @ref HttpResponseCreator defines an interface for the classes used
/// to generate HTTP responses. Such classes are defined outside of this
/// library and they are specific to the needs of the particular module.
/// In some cases it may be desired to create new instance of the
/// @ref HttpResponseCreator implementation for every request processed.
/// The @ref HttpResponseCreatorFactory is an interface to the "factory"
/// class which generates canned @ref HttpResponseCreator instances. The
/// pointer to the factory class is passed to the @ref HttpListener and
/// the listener propagates it down to other classes. These classes call
/// @ref HttpResponseCreatorFactory::create to retrieve an instance of the
/// appropriate @ref HttpResponseCreator, which is in turn used to generate
/// HTTP response.
///
/// Note that an implementation of the @ref HttpResponseCreatorFactory::create
/// may always return the same instance of the @ref HttpResponseCreator
/// if creating new instance for each request is not required or undesired.
class HttpResponseCreatorFactory {
public:

    /// @brief Virtual destructor.
    virtual ~HttpResponseCreatorFactory() { }

    /// @brief Returns an instance of the @ref HttpResponseCreator.
    ///
    /// The implementation may create new instance every time this method
    /// is called, or it may always return the same instance.
    ///
    /// @return Pointer to the instance of the @ref HttpResponseCreator to
    /// be used to generate HTTP response.
    virtual HttpResponseCreatorPtr create() const = 0;

};

/// @brief Pointer to the @ref HttpResponseCreatorFactory.
typedef boost::shared_ptr<HttpResponseCreatorFactory>
HttpResponseCreatorFactoryPtr;

} // end of namespace isc::http
} // end of namespace isc

#endif
