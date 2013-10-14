// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/data.h>
#include <user.h>
#include <user_file.h>

#include <boost/foreach.hpp>

UserFile::UserFile(const std::string& fname) : fname_(fname) {
    if (fname_.empty()) {
        isc_throw(UserFileError, "file name cannot be blank");
    }
}

UserFile::~UserFile(){
};

void
UserFile::open() {
    if (isOpen()) {
        isc_throw (UserFileError, "file is already open");
    }

    ifs_.open(fname_.c_str(), std::ifstream::in);
    if (!ifs_.is_open()) {
        isc_throw(UserFileError, "cannot open file:" << fname_);
    }

    setOpenFlag(true);
}

UserPtr
UserFile::readNextUser() {
    if (!isOpen()) {
        isc_throw (UserFileError, "cannot read, file is not open");
    }

    if (ifs_.good()) {
        char buf[4096];

        // get the next line
        ifs_.getline(buf, sizeof(buf));

        // we got something, try to make a user out of it.
        if (ifs_.gcount() > 0) {
            return(makeUser(buf));
        }
    }

    // returns an empty user
    return (UserDataSource::readNextUser());
}

UserPtr
UserFile::makeUser(const std::string& user_string) {
    // This method leverages the existing JSON parsing provided by isc::data
    // library.  Should this prove to be a performance issue, it may be that
    // lighter weight solution would be appropriate.

    // Turn the string of JSON text into an Element set.
    isc::data::ElementPtr elements;
    try {
        elements = isc::data::Element::fromJSON(user_string);
    } catch (isc::data::JSONError& ex) {
        isc_throw(UserFileError,
                  "UserFile entry is malformed JSON: " << ex.what());
    }

    // Get a map of the Elements, keyed by element name.
    isc::data::ConstElementPtr element;
    PropertyMap properties;
    std::string id_type_str;
    std::string id_str;

    std::pair<std::string, isc::data::ConstElementPtr> element_pair;
    BOOST_FOREACH (element_pair, elements->mapValue()) {
        std::string label = element_pair.first;
        std::string value = "";
        element_pair.second->getValue(value);

        if (label == "type") {
            id_type_str = value;
        } else if (label == "id") {
            id_str = value;
        } else {
            if (properties.find(label) != properties.end()) {
                isc_throw (UserFileError,
                           "UserFile entry contains duplicate values: "
                           << user_string);
            }
            properties[label]=value;
        }
    }

    UserId::UserIdType id_type;
    try {
        id_type = UserId::lookupType(id_type_str);
    } catch (const std::exception& ex) {
        isc_throw (UserFileError, "UserFile entry has invalid type: "
                                  << user_string << " " << ex.what());
    }

    UserPtr user;
    try {
        user.reset(new User(id_type, id_str));
    } catch (const std::exception& ex) {
        isc_throw (UserFileError, "UserFile cannot create user form entry: "
                                  << user_string << " " << ex.what());
   }


    user->setProperties(properties);
    return (user);
}

void
UserFile::close() {
    if (ifs_.is_open()) {
        ifs_.close();
    }

    setOpenFlag(false);
}

