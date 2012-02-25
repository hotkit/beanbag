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
        const fostlib::json &which) {
    fostlib::string name(fostlib::coerce<fostlib::string>(which["name"]));

    boost::mutex::scoped_lock lock(g_mutex);
    databases_t::const_iterator loc(g_databases.find(name));

    if ( loc == g_databases.end() ) {
        fostlib::json tplate(fostlib::json::parse(fostlib::utf::load_file(
            fostlib::coerce<boost::filesystem::wpath>(which["template"]))));
        boost::shared_ptr< fostlib::jsondb > db(
            new fostlib::jsondb(
                fostlib::coerce<fostlib::string>(which["filepath"]),
                tplate) );
        g_databases[name] = db;
        return db;
    } else
        return loc->second;
}
