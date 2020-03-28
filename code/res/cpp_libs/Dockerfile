FROM ubuntu:latest

# INSTALL PYTHON
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
  && apt-get install -y python3-pip python3-dev \
  && cd /usr/local/bin \
  && ln -s /usr/bin/python3 python \
  && pip3 install --upgrade pip
	&& pip3 install numpy

# INSTALL CPP
RUN apt-get install -y build-essential cmake


# INSTALL LIBRARIES
RUN apt-get install -y libopencv-dev python-opencv libfreetype6-dev libxrandr-dev libudev-dev libogg-dev libflac-dev libvorbis-dev libopenal-dev libboost-all-dev libgtkmm-3.0-dev libgtk-3-dev libsfml-dev

# INSTALL AUDIO ENV

ENV UNAME pacat

RUN apt-get update && apt-get install -y \
    espeak \
    vorbis-tools \
    sox \
    alsa-utils \
    libasound2 \
    libasound2-plugins \
    pulseaudio \
    pulseaudio-utils \
    --no-install-recommends \
    && rm -rf /var/lib/apt/lists/*


ENV HOME /home/pulseaudio
RUN useradd --create-home --home-dir $HOME pulseaudio \
	&& usermod -aG audio,pulse,pulse-access pulseaudio \
	&& chown -R pulseaudio:pulseaudio $HOME


# DEFAULTS TO GCC/G++8

RUN apt-get update \
    && apt-get install -y software-properties-common \
    && add-apt-repository ppa:ubuntu-toolchain-r/test -y \
    && apt-get install gcc-8 g++-8 -y \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 60 --slave /usr/bin/g++ g++ /usr/bin/g++-8 \
    && update-alternatives --config gcc
