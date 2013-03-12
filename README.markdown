# Beanbag — A lightweight JSON database — 0.0 #

Beanbag is a very lightweight ACID compliant transactional JSON database. The database itself is one or more JSON files and you interact with it through RESTful calls.

It's all very experimental so probably best used for fun rather than profit.


# Using Beanbag #

There is no release yet, so you'll need to checkout the develop branch and try from there. After checking out develop re-read this file.

## Running a Beanbag server ##

There isn't yet a simple Beanbag specific web server. The Beanbag views can be run by configuring them in the `fost-webserver` in the `fost-web` project.

After doing a debug (i.e. a default) build the examples can be run from the root of the checkout using (for the wiki example):

    bin/fost-webserver-d -p 8080 usr/share/beanbag/wiki/config-d.json

Or (for the raw JSON editor):

    bin/fost-webserver-d -p 8080 usr/share/beanbag/raw/config-d.json

The `-p` parameter controls the port the server will appear on.


# Server views #

The main purpose of the Beanbag server views is to allow different ways of mapping URL paths in the request to locations within the JSON structure at the server.

## beanbag.raw ##

This exposes the configured JSON data in it's entirety and unchanged. A request against the root of the view will return the entire structure, and requests against sub-paths will return the data at that location. If a path component is numeric then it will be interpreted as an array index in a JSON array.

For example, a path of:

    /path/into/1/structure/

Would appear as the equivalent JavaScript location:

    data['path']['into'][1]['structure']

If you were to do a `PUT` to a location like this then Beanbag will create objects and arrays as required to fulfil the location. If the data already present won't allow for the type of index access your path implies then an error will be returned.

Within the view configuration there needs to be a `html` key which contains either a `template` key or a `static` key. In either case the value is a file location that provides the HTML view. If it is `static` then it is always served as is. If it is `template` then the following substitutions are made:

1. `[[path]]` --- The representation of the file path the server sees as JSON data.
2. `[[data]]` --- The representation of the JSON data at the location specified by the path.
3. `[[etag]]` --- The ETag value for the data.

For examples see the raw and GTF demos.

### Media types ###

Both `application/json` and `text/html` are supported. To receive an `application/json` response then:

1. Use `application/json` in the Accept header before `text/html`. Currently, only response codes of 2xx will return JSON. Note that this means a 404 will always return `text/html`
2.  Add `__=` to the query string. This will force JSON to be produced, but it will be returned as `text/plain` to aid in debugging from a browser.

### Request methods ###

Currently `GET`, `PUT` and `DELETE` are supported. `PUT` is used for both creation of new locations inside the JSON and for updating of current values. Conditional `PUT`s (i.e. use of `If-Modified`) can be used to ensure that data has not already been changed. Clients should use the `ETag` header for this purpose. `DELETE` can also be used conditionally to ensure that recently updated information is not deleted.


## beanbag.structured ##

This exposes the JSON data in a more structured format designed to be more scalable. A JSON object is always returned for all locations and the data is placed into the `data` key. For atoms and arrays the actual data itself is replaced by a JSON object that describes where it can be found.


# Development #

This project uses git flow. Don't forget to do `git flow init -d` after you clone it.

The `./configure` script is used to pull changes and source for the other libraries that are needed. This can be run each time upstream changes are wanted, but it does not attempt to update the main repository view.

You can then build the software by running `./compile`.

A full example sequence is below:

    git clone git@github.com:KayEss/beanbag.git
    cd beanbag
    git flow init -d
    ./configure
    ./compile
    bin/fost-webserver-d -p 8080 usr/share/beanbag/wiki/config-d.json

Opening a browser to show http://localhost:8080/ should show this text.

