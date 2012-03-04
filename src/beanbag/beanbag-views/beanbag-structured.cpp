/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include <beanbag/structured.hpp>


namespace {
    const beanbag::structured_view c_view("beanbag.structured");
}


beanbag::structured_view::structured_view(const fostlib::string &name)
: raw_view(name) {
}

