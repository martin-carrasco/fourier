FROM cpp_libs:latest

RUN pip3 install matplotlib numpy
RUN mkdir /app && ls /app
WORKDIR /app
COPY . /app

RUN cmake . && make

CMD ["./bin/opencv"]
