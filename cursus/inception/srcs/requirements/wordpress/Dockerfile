# WordPress on Debian Bullseye
FROM debian:bullseye-slim

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install PHP-FPM and required extensions, plus tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    php7.4-fpm \
    php7.4-mysql \
    php7.4-mbstring \
    php7.4-xml \
    php7.4-curl \
    php7.4-gd \
    mariadb-client \
    unzip \
    git \
    curl \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Create target directory
RUN mkdir -p /var/www/html
RUN mkdir -p /run/php && chown www-data:www-data /run/php



# Copy custom WordPress config if any
COPY conf/wp-config.php /usr/local/etc/wp-config.php

# Copy entrypoint.sh
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

# Configurar PHP-FPM para escuchar por TCP
RUN sed -i 's|^listen = .*|listen = 0.0.0.0:9000|' /etc/php/7.4/fpm/pool.d/www.conf

# Expose PHP-FPM port
EXPOSE 9000

# Use entrypoint
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
