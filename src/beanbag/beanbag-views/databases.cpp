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
    fostlib::nullable<fostlib::string> which_name(which.get<fostlib::string>());
    fostlib::string name;
    if ( which_name.isnull() )
        name = fostlib::coerce<fostlib::string>(which["name"]);
    else
        name = which_name.value();

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


void beanbag::test_database(const fostlib::string &name, const fostlib::json &blob) {
    boost::mutex::scoped_lock lock(g_mutex);
    boost::shared_ptr< fostlib::jsondb > db(new fostlib::jsondb);
    fostlib::jsondb::local transaction(*db);
    transaction.insert(fostlib::jcursor(), blob);
    transaction.commit();
    g_databases[name] = db;
}

