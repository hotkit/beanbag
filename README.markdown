# Beanbag — A lightweight JSON database — 0.0 #

Beanbag is a very lightweight ACID compliant transactional JSON database. The database itself is one or more JSON files and you interact with it through RESTful calls.

It's all very experimental so probably best used for fun rather than profit.

# Using Beanbag #

There is no release yet, so you'll need to checkout the develop branch and try from there. After checking out develop re-read this file.

## Running a Beanbag server ##


# Server views #

## beanbag.raw ##

This exposes the configured JSON data in it's entirety and unchanged. A request against the root of the view will return the entire structure, and requests against sub-paths will return the data at that location.

### Media types ###

Both `application/json` and `text/html` are supported. To receive an `application/json` response then:

1. `application/json` is in the Accept header before `text/html` and the response code is 2xx. Note that this means a 404 will always return `text/html`.
2. A query string of `?__=` is present.

### Request methods ###

Currently both `GET` and `PUT` are supported. `PUT` is used for both creation of new locations inside the JSON and for updating of current values. Conditional `PUT`s (i.e. use of `If-Modified`) can be used to ensure that data has not already been changed. Clients should use the `ETag` header for this purpose.


# Development #

This project uses git flow. Don't forget to do `git flow init -d` after you clone it.
