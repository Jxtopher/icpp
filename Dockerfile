FROM gcc:12.1.0

ARG DEBIAN_FRONTEND=noninteractive

# Package installation 
RUN apt-get update -y && \ 
    apt-get install -y --no-install-recommends git build-essential \
    cmake \
    pkg-config \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* \
    && useradd -ms /bin/bash user

COPY . /app
WORKDIR /app

RUN rm -rf build/*      \
    && mkdir -p build   \
    && cd build         \
    && cmake ..         \
    && make             \
    && make install

USER user
ENTRYPOINT ["icpp"]
