#include "zoneset.h"

// see findClosest()
static bool
stripLabel(isc::dns::Name& n) {
    std::string str = n.toText(false);
    size_t pos = str.find('.');
    if (pos + 1 < str.size()) {
        n = isc::dns::Name(str.substr(pos+1));
        return true;
    } else {
        return false;
    }
}

bool
ZoneSet::findClosest(const isc::dns::Name& n, isc::dns::Name& closest) {

    // name compare doesnt work in this branch, so we convert and
    // strip labels
    isc::dns::Name cur = n;
    if (contains(n)) {
        closest = n;
        return true;
    }

    bool labels_left = stripLabel(cur);
    while(labels_left) {
        if (contains(cur)) {
            closest = cur;
            return true;
        } else {
            labels_left = stripLabel(cur);
        }
    }
    return false;
}
