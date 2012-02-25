/*
    Copyright 2012 Felspar Co Ltd. http://support.felspar.com/
    Distributed under the Boost Software License, Version 1.0.
    See accompanying file LICENSE_1_0.txt or copy at
        http://www.boost.org/LICENSE_1_0.txt
*/


#include "databases.hpp"
#include <fost/unicode>


namespace {
    typedef std::map< fostlib::string, boost::shared_ptr<fostlib::jsondb> > databases_t;
    boost::mutex g_mutex;
    databases_t g_databases;
}


boost::shared_ptr< fostlib::jsondb > beanbag::database(
        const fostlib::json &which_json) {
    fostlib::string which(fostlib::coerce<fostlib::string>(which_json));

    boost::mutex::scoped_lock lock(g_mutex);
    databases_t::const_iterator loc(g_databases.find(which));

    if ( loc == g_databases.end() ) {
        boost::shared_ptr< fostlib::jsondb > db(
            new fostlib::jsondb(which) );
        g_databases[which] = db;
        return db;
    } else
        return loc->second;
}
