/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <fost/test>
#include "databases.hpp"


FSL_TEST_SUITE(databases);


FSL_TEST_FUNCTION(can_inject_database) {
    fostlib::json config;
    fostlib::insert(config, "key", "value");
    beanbag::test_database("can_inject_database", config);

    fostlib::jsondb::local trans(*
        beanbag::database(fostlib::json("can_inject_database")));
    FSL_CHECK_EQ(config["key"], trans["key"]);
}

