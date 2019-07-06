FROM cpp_libs:latest

# RUN pip3 install matplotlib numpy
RUN apt-get install -y python3-matplotlib
RUN mkdir /app && ls /app
WORKDIR /app
COPY . /app

RUN cmake . && make

CMD ["./bin/generic"]
