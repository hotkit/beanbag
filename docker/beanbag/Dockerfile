FROM kayess/fost-runtime:latest
MAINTAINER Kirit Saelensminde

WORKDIR /srv
EXPOSE 2222

ADD etc /etc/beanbag
ADD bin /usr/local/bin
ADD lib /usr/local/lib
ADD srv /srv/

RUN \
    ldconfig

CMD ["fost-webserver", "-j", "/etc/beanbag/configuration.json"]
