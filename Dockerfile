FROM gcc:latest

WORKDIR /home

COPY . /home/

RUN make

CMD ["./main.o"]