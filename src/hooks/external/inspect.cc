// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>

namespace isc {

typedef int* IntPtr;
typedef int*** IntPtr3;

struct Four {
    IntPtr3 a, b, c, d;

    Four() : a(0), b(0), c(0), d() { }
};

typedef Four* FourPtr;

typedef boost::shared_ptr<Four> FourSharedPtr;

struct Encap {
    FourSharedPtr object;
};

} // end of namespace isc

using namespace std;
using namespace isc;

int main() {
    cout << "sizeof(IntPtr ::= int*) is " << sizeof(IntPtr) * 8 << " octets\n";
    cout << "sizeof(IntPtr3 ::= int***) is " << sizeof(IntPtr3) * 8 << " octets\n";
    if (sizeof(IntPtr) != sizeof(IntPtr3)) {
        cout << "unusual size difference between IntPtr and IntPtr3?\n";
    }
    if (sizeof(Four) != 4 * sizeof(IntPtr3)) {
        cout << "sizeof(Four) is " << sizeof(Four) * 8
             << " octets and don't match expected " << sizeof(IntPtr3) * 32
             << " octet?\n";
    }
    Four one;
    Four zero;
    memset(&zero, 0, sizeof(Four));
    if (memcmp(&zero, &one, sizeof(Four)) != 0) {
        cout << "Four instance is not initialized to 0 as expected?\n";
    }
    cout << "sizeof(FourPtr ::= Four*) is " << sizeof(FourPtr) * 8 << " octets\n";
    cout << "sizeof(FourSharedPtr ::= shared_ptr<Four> is " << sizeof(FourSharedPtr) * 8 << " octets\n";
    cout << "sizeof(Encap) is " << sizeof(Encap) * 8 << " octets\n";
    if (sizeof(FourSharedPtr) != sizeof(Encap)) {
        cout << "unusual size difference between Encap and FourSharedPtr\n";
    }
    size_t size = sizeof(Encap);
    if (sizeof(Four) < sizeof(Encap)) {
        cout << "shared pointers are very big?\n";
        size = sizeof(Four);
    }
    Encap encap;
    if (memcmp(&encap, &zero, size) != 0) {
        cerr << "shared pointers are not initialized to 0???\n";
        return (-1);
    }
    cout << "shared pointers are initialized to 0 as expected\n";
    return (0);
}

