# WordPress on Debian Bullseye
FROM debian:bullseye-slim

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install PHP-FPM and required extensions, plus tools
# Added php7.4-phar and php7.4-mysqli which are often needed by WP-CLI
RUN apt-get update && apt-get install -y --no-install-recommends \
    php7.4-fpm \
    php7.4-mysql \
    php7.4-mbstring \
    php7.4-xml \
    php7.4-curl \
    php7.4-gd \
    php7.4-phar \
    mariadb-client \
    unzip \
    curl \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Install WP-CLI (The tool that automates WordPress installation)
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# Create target directories and set permissions
RUN mkdir -p /var/www/html
RUN mkdir -p /run/php && chown www-data:www-data /run/php

# [Important] Configure PHP-FPM to listen on port 9000 instead of a socket
# This allows Nginx to communicate with WordPress over the Docker network
RUN sed -i 's|^listen = .*|listen = 0.0.0.0:9000|' /etc/php/7.4/fpm/pool.d/www.conf

# Copy entrypoint.sh (Make sure the path matches your project structure)
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

# Set working directory to the web root
WORKDIR /var/www/html

# Expose PHP-FPM port
EXPOSE 9000

# Use entrypoint
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
