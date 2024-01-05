# Start from the common base image
FROM boostbase as beastgres

# Install PostgreSQL development headers
RUN apt-get update && apt-get install -y libpq-dev

# Copy the C++ source code
COPY . /usr/src/beastgres

# Set the working directory
WORKDIR /usr/src/beastgres

# Build the application
RUN cmake . && make

# Command to run the application
CMD ["./beastgres"]

