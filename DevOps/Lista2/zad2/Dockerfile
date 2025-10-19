FROM ubuntu:24.04
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    openssh-server \
    iproute2 \
    sudo \
    vim \
    curl \
    iputils-ping && \
    mkdir /var/run/sshd
RUN echo 'PermitRootLogin yes' >> etc/ssh/sshd_config