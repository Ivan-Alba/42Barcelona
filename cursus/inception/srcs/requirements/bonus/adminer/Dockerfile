# Dockerfile: Adminer container

# Base image: lightweight PHP + Apache on Debian Bullseye
FROM php:8.1-apache-bullseye

# Install required PHP extensions (mysqli for MariaDB/MySQL)
RUN docker-php-ext-install mysqli pdo pdo_mysql

# Copy Adminer PHP file into web root
# Adminer is a single PHP file, acting as a database client
COPY adminer.php /var/www/html/

# Expose HTTP port
EXPOSE 8080

# Ensure Apache runs in foreground
CMD ["apache2-foreground"]
