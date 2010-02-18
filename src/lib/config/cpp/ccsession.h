// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __CCSESSION_H
#define __CCSESSION_H 1

#include <string>

#include <config/data_def.h>
#include <cc/session.h>
#include <cc/data.h>

class ModuleCCSession {
public:
    /**
     * Initialize a config/command session
     * @param module_name: The name of this module. This is not a
     *                     reference because we expect static strings
     *                     to be passed here.
     * @param spec_file_name: The name of the file containing the
     *                        module specification.
     */
    ModuleCCSession(std::string spec_file_name,
                    isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config) = NULL,
                    isc::data::ElementPtr(*command_handler)(isc::data::ElementPtr command) = NULL
                    ) throw (isc::cc::SessionError);
    int getSocket();

    /**
     * Check if there is a command or config change on the command
     * session. If so, the appropriate handler is called if set.
     * If not set, a default answer is returned.
     * This is a non-blocking read; if there is nothing this function
     * will return 0.
     */
    int check_command();

    /**
     * The config handler function should expect an ElementPtr containing
     * the full configuration where non-default values have been set.
     * Later we might want to think about more granular control
     * (i.e. this does not scale to for instance lists containing
     * 100000 zones, where the whole list is passed every time a single
     * thing changes)
     */
    void set_config_handler(isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config)) { config_handler_ = config_handler; };

    /**
     * Set a command handler; the function that is passed takes an
     * ElementPtr, pointing to a list element, containing
     * [ module_name, command_name, arg1, arg2, ... ]
     * The returned ElementPtr should look like
     * { "result": [ return_value, result_value ] }
     * result value here is optional and depends on the command
     *
     * This protocol is very likely to change.
     */
    void set_command_handler(isc::data::ElementPtr(*command_handler)(isc::data::ElementPtr command)) { command_handler_ = command_handler; };
    
private:
    void read_module_specification(const std::string& filename);
    
    std::string module_name_;
    isc::cc::Session session_;
    isc::data::ModuleSpec module_specification_;
    isc::data::ElementPtr config_;

    isc::data::ElementPtr(*config_handler_)(isc::data::ElementPtr new_config);
    isc::data::ElementPtr(*command_handler_)(isc::data::ElementPtr command);
};

#endif // __CCSESSION_H

// Local Variables:
// mode: c++
// End:
