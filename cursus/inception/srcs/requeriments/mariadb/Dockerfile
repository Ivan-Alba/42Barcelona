# Dockerfile: MariaDB on Debian (bullseye)
FROM debian:bullseye-slim

# Set non-interactive mode for apt
ENV DEBIAN_FRONTEND=noninteractive

# Update repos and install MariaDB
RUN apt-get update && \
    apt-get install -y mariadb-server && \
    rm -rf /var/lib/apt/lists/*

# Copy initialization scripts
COPY conf /docker-entrypoint-initdb.d/

# Expose MariaDB port
EXPOSE 3306

# Use official MariaDB entrypoint
ENTRYPOINT ["docker-entrypoint.sh"]

# No CMD needed; entrypoint starts MariaDB daemon
