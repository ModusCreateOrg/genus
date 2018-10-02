FROM ubuntu:18.04
COPY scripts /opt/genus/scripts
RUN /bin/bash /opt/genus/scripts/docker-install-debian-prerequisites.sh
COPY creative-engine /opt/creative-engine
COPY CMakeLists.txt \
    creative-engine \
    images \
    resources \
    scripts \
    sdkconfig.linux \
    sdkconfig.osx \
    src \
    /opt/genus/
RUN /bin/bash /opt/genus/scripts/build.sh docker-build
