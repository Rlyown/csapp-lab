FROM ubuntu:16.04

ENV LANG=en_US.UTF-8
ENV TZ=Asia/Shanghai

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone \
	&& apt-get update -y \
	&& apt-get -y install gcc \
	gcc-multilib \
	g++ \
	gdb \
    cgdb \
    nasm \
	automake \
	autoconf \
	libtool \
	make \
	cmake \
	ssh \
	ntp \
	vim \
	wget \
	curl \
	telnet \
	sudo \
	git \
	subversion \
	doxygen \
	lighttpd \
	net-tools \
	inetutils-ping \
	python \
	golang \
	libbz2-dev \
	libdb++-dev \
	libssl-dev \
	libdb-dev \
	libssl-dev \
	openssl \
	libreadline-dev \
	libcurl4-openssl-dev \
	libncurses-dev \
	autotools-dev \
	build-essential \
	libicu-dev \
	python-dev \
	libgmp3-dev \
	libmpfr-dev \
	libmpc-dev \
    grub2 \
    libgcc-5-dev \
    xorriso \
    texinfo \
    libcloog-isl-dev \
    bison

# change sshd listen port
# RUN echo "Port 36000" /etc/ssh/sshd_config
RUN mkdir /var/run/sshd \
	&& sed -i 's/Port[ ]*22/Port 36000/' /etc/ssh/sshd_config \
	&& echo "PasswordAuthentication yes" >> /etc/ssh/sshd_config

# add user
RUN mkdir /home/bingo \
	&& useradd -s /bin/bash bingo \
	&& echo "bingo:123456" | chpasswd \
	&& chown -R bingo:bingo /home/bingo \
	&& echo "bingo  ALL=(ALL)       NOPASSWD:ALL" >> /etc/sudoers

# Container should expose ports.
EXPOSE 36000
CMD ["/usr/sbin/sshd", "-D"]
