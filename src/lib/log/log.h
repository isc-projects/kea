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

#ifndef __LOG_H
#define __LOG_H

namespace isc {
namespace log {

class RootLogger : public Logger
{
public:

    /// \brief Return Root Logger
    ///
    /// Returns the root logger for the system.  Only one root logger is
    /// defined and the name corresponds to the 
    static Log* getRootLogger() {
        static Log root_logger();

        return &root_logger;
    }

    /// \brief Set Logger Name
    ///
    /// Sets the name of the root logger.  This is dynamic, and 

private:
    static std::string  root_name_;
};

}
}



#endif // __LOG_H
