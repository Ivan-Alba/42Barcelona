# Base image: Debian Bullseye
FROM debian:bullseye

# Install PHP and the mysqli extension needed for MariaDB
RUN apt-get update && apt-get install -y \
    php \
    php-mysqli \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Create the directory for Adminer
RUN mkdir -p /var/www/html

# Download the latest Adminer PHP file directly
RUN wget "https://github.com/vrana/adminer/releases/download/v4.17.1/adminer-4.17.1-mysql.php" -O /var/www/html/index.php

# Expose the internal port
EXPOSE 8080

# Start a simple PHP server to serve the single file
CMD ["php", "-S", "0.0.0.0:8080", "-t", "/var/www/html"]
