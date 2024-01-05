# Base stage for downloading and installing Boost
FROM ubuntu:22.04 as boostbase

# Install necessary dependencies for building Boost
RUN apt-get update && apt-get install -y cmake g++ make wget

# Download and extract Boost
RUN wget https://archives.boost.io/release/1.84.0/source/boost_1_84_0.tar.gz && \
    tar -xzvf boost_1_84_0.tar.gz -C /tmp

# Build and install Boost
WORKDIR /tmp/boost_1_84_0
RUN ./bootstrap.sh --prefix=/usr/local/boost && \
    ./b2 install

# Remove unnecessary files
RUN rm -rf /tmp/boost_1_84_0 && rm /boost_1_84_0.tar.gz

