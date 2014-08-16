FROM kayess/fost-runtime
MAINTAINER Kirit Saelensminde

WORKDIR /srv
EXPOSE 80

ADD etc /etc/beanbag
ADD bin /usr/local/bin
ADD lib /usr/local/lib
ADD srv /srv/

RUN \
    ldconfig

CMD fost-webserver -p 80 -h 0 \
    -m /etc/beanbag/mime-types.json \
    -j /etc/beanbag/configuration.json
