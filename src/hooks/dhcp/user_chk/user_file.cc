// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/data.h>
#include <user.h>
#include <user_file.h>

#include <boost/foreach.hpp>
#include <errno.h>
#include <iostream>

namespace user_chk {

UserFile::UserFile(const std::string& fname) : fname_(fname), file_() {
    if (fname_.empty()) {
        isc_throw(UserFileError, "file name cannot be blank");
    }
}

UserFile::~UserFile(){
    close();
};

void
UserFile::open() {
    if (isOpen()) {
        isc_throw(UserFileError, "file is already open");
    }

    file_.open(fname_.c_str(), std::ifstream::in);
    int sav_error = errno;
    if (!file_.is_open()) {
        isc_throw(UserFileError, "cannot open file:" << fname_
                                 << " reason: " << strerror(sav_error));
    }
}

UserPtr
UserFile::readNextUser() {
    if (!isOpen()) {
        isc_throw (UserFileError, "cannot read, file is not open");
    }

    if (file_.good()) {
        char buf[USER_ENTRY_MAX_LEN];

        // Get the next line.
        file_.getline(buf, sizeof(buf));

        // We got something, try to make a user out of it.
        if (file_.gcount() > 0) {
            return(makeUser(buf));
        }
    }

    // Returns an empty user on EOF.
    return (UserPtr());
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

    // Iterate over the elements, saving of "type" and "id" to their
    // respective locals.  Anything else is assumed to be an option so
    // add it to the local property map.
    std::pair<std::string, isc::data::ConstElementPtr> element_pair;
    BOOST_FOREACH (element_pair, elements->mapValue()) {
        // Get the element's label.
        std::string label = element_pair.first;

        // Currently everything must be a string.
        if (element_pair.second->getType() != isc::data::Element::string) {
            isc_throw (UserFileError, "UserFile entry: " << user_string
                       << "has non-string value for : " << label);
        }

        std::string value = element_pair.second->stringValue();

        if (label == "type") {
            id_type_str = value;
        } else if (label == "id") {
            id_str = value;
        } else {
            // JSON parsing reduces any duplicates to the last value parsed,
            // so we will never see duplicates here.
            properties[label]=value;
        }
    }

    // First we attempt to translate the id type.
    UserId::UserIdType id_type;
    try {
        id_type = UserId::lookupType(id_type_str);
    } catch (const std::exception& ex) {
        isc_throw (UserFileError, "UserFile entry has invalid type: "
                                  << user_string << " " << ex.what());
    }

    // Id type is valid, so attempt to make the user based on that and
    // the value we have for "id".
    UserPtr user;
    try {
        user.reset(new User(id_type, id_str));
    } catch (const std::exception& ex) {
        isc_throw (UserFileError, "UserFile cannot create user form entry: "
                                  << user_string << " " << ex.what());
    }

    // We have a new User, so add in the properties and return it.
    user->setProperties(properties);
    return (user);
}

bool
UserFile::isOpen() const {
    return (file_.is_open());
}

void
UserFile::close() {
    try {
        if (file_.is_open()) {
            file_.close();
        }
    } catch (const std::exception& ex) {
        // Highly unlikely to occur but let's at least spit out an error.
        // Beyond that we swallow it for tidiness.
        std::cout << "UserFile unexpected error closing the file: "
                  << fname_ << " : " << ex.what() << std::endl;
    }
}

} // namespace user_chk
