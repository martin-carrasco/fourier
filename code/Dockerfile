FROM cpp_libs:latest

RUN apt-get -y install pulseaudio pulseaudio-utils

RUN mkdir /app && ls /app
WORKDIR /app
COPY . /app

# RUN ./configure
RUN cmake . && make

WORKDIR /app

CMD ["./bin/image"]
