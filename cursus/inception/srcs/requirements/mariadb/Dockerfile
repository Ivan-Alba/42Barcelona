# Dockerfile: MariaDB on Debian (bullseye-slim)
FROM debian:bullseye-slim

ENV DEBIAN_FRONTEND=noninteractive

# Install MariaDB
RUN apt-get update && \
    apt-get install -y mariadb-server && \
    rm -rf /var/lib/apt/lists/*

# Create directory for socket
RUN mkdir -p /run/mysqld && chown -R mysql:mysql /run/mysqld

# Copy entrypoint script
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

# Expose MariaDB port
EXPOSE 3306

# Use custom entrypoint
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
