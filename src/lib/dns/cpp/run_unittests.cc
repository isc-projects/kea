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

#include <iostream>
#include <stdexcept>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextTestProgressListener.h>

#include "name_unittest.h"

int
main(int argc, char* argv[])
{
    CppUnit::TestRunner runner;
    CppUnit::TestResult controller;

    // Add a listener that collects test result
    CppUnit::TestResultCollector result;
    controller.addListener( &result );        

    // Add a listener that print dots as test run.
    CppUnit::TextTestProgressListener progress;
    controller.addListener(&progress);

    runner.addTest(NameTest::suite());

    try {
        std::cout << "Running ";
        runner.run(controller, "");

        std::cerr << std::endl;

        // Print test in a compiler compatible format.
        CppUnit::CompilerOutputter outputter(&result, std::cerr);
        outputter.write();                      
    } catch (std::invalid_argument& e) {  // Test path not resolved
        std::cerr  <<  std::endl  
                   <<  "ERROR: "  <<  e.what()
                   << std::endl;
        return 0;
    }

    return (result.wasSuccessful() ? 0 : 1);
}
