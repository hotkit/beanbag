/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once
#include <fost/jsondb>


namespace beanbag {


    /// Return a reference to the requested database
    boost::shared_ptr< fostlib::jsondb > database(const fostlib::json &which);

    /// Insert a specified JSON blog into the databases with the specified name. Useful for testing.
    void test_database(const fostlib::string &name, const fostlib::json &blob);


}

