FROM ubuntu:20.04
RUN apt-get update && apt-get install -y curl

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Pre-configure timezone before any package installation
RUN apt-get update && apt-get install -y tzdata \
    && ln -fs /usr/share/zoneinfo/Etc/UTC /etc/localtime \
    && dpkg-reconfigure -f noninteractive tzdata
# Install essential build tools and C++ related packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    g++ \
    git \
    make \
    build-essential \
    libboost-all-dev \
    libgtest-dev \
    libgmock-dev \
    libssl-dev \
    libsqlite3-dev \
    nlohmann-json3-dev\
    --no-install-recommends \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Copy the source code to the container
COPY . /app
WORKDIR /app
RUN chmod +x ./entrypoint.sh
EXPOSE 8080
# RUN mkdir -p build && cd build && cmake .. && make && cd ..

# Run the application
ENTRYPOINT ["./entrypoint.sh"]
CMD ["bash"]