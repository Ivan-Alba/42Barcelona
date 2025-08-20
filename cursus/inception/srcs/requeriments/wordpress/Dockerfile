# Use official WordPress image with PHP-FPM based on Debian bullseye
FROM wordpress:php8.1-fpm-bullseye

# Set non-interactive for apt
ENV DEBIAN_FRONTEND=noninteractive

# Install extra packages if needed
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        git \          # Git for version control
        unzip \        # Unzip for plugins/themes
        mariadb-client \ # MySQL client for testing DB connections
    && rm -rf /var/lib/apt/lists/*  # Clean up cache

# Copy custom WordPress files
COPY conf/ /var/www/html/

# Set correct permissions
RUN chown -R www-data:www-data /var/www/html \  
    && chmod -R 755 /var/www/html              

# Expose PHP-FPM port
EXPOSE 9000  # Port for Nginx to connect PHP-FPM

# Entrypoint and CMD
# Already set in base image: ENTRYPOINT ["docker-entrypoint.sh"], CMD ["php-fpm"]
