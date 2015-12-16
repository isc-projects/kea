// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stats/context.h>
#include <map>

namespace isc {
namespace stats {

ObservationPtr StatContext::get(const std::string& name) const {
    std::map<std::string, ObservationPtr>::const_iterator obs = stats_.find(name);
    if (obs == stats_.end()) {
        return (ObservationPtr());
    } else {
        return (obs->second);
    }
}

void StatContext::add(const ObservationPtr& obs) {
    std::map<std::string, ObservationPtr>::iterator existing = stats_.find(obs->getName());
    if (existing == stats_.end()) {
        stats_.insert(make_pair(obs->getName() ,obs));
    } else {
        isc_throw(DuplicateStat, "Statistic named " << obs->getName()
                  << " already exists.");
    }

}

bool StatContext::del(const std::string& name) {
    std::map<std::string, ObservationPtr>::iterator obs = stats_.find(name);
    if (obs == stats_.end()) {
        return (false);
    } else {
        stats_.erase(obs);
        return (true);
    }
}

};
};
