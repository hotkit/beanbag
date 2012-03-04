/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#pragma once
#ifndef BEANBAG_STRUCTURED_HPP
#define BEANBAG_STRUCTURED_HPP


#include <beanbag/raw.hpp>


namespace beanbag {


    class structured_view : public raw_view {
    public:
        structured_view(const fostlib::string &name);
    };


}


#endif // BEANBAG_STRUCTURED_HPP
