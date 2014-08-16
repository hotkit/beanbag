FROM kayess/fost-runtime
MAINTAINER Kirit Saelensminde

WORKDIR /srv
EXPOSE 80

ADD bin /usr/local/bin
ADD lib /usr/local/lib

RUN \
    ldconfig
