FROM alpine:3.19

# Install only what we need
RUN apk add --no-cache build-base

WORKDIR /app

COPY main.c .
COPY input.txt .

RUN gcc main.c -o grammar && strip grammar

CMD ["./grammar"]