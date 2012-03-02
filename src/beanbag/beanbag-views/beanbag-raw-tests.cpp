/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <fost/test>
#include "databases.hpp"
#include <beanbag/beanbag>


FSL_TEST_SUITE(beanbag_raw);


FSL_TEST_FUNCTION(get_has_etag) {
    fostlib::json config;
    beanbag::test_database("get_has_etag", config);
    const beanbag::raw_view view("beanbag.test.get_has_etag");
}

