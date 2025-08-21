#!/bin/bash
set -e

# Path where WordPress lives
WP_PATH="/var/www/html"

# Database variables (.env)
DB_HOST=${WORDPRESS_DB_HOST}
DB_NAME=${WORDPRESS_DB_NAME}
DB_USER=${WORDPRESS_DB_USER}

if [ -f /run/secrets/db_password ]; then
    DB_PASSWORD=$(cat /run/secrets/db_password)
fi

echo "[INFO] Waiting for MariaDB to be ready..."
until mysql -h "$DB_HOST" -P 3306 -u "$DB_USER" -p"$DB_PASSWORD" "$DB_NAME" &> /dev/null; do
    echo "[INFO] MariaDB not ready, retrying in 2 seconds..."
	sleep 2
done
echo "[INFO] MariaDB is ready."

# Path inside container where wp-config.php from build is stored
WP_CONFIG_SOURCE="/usr/local/etc/wp-config.php"

# Check if WordPress is installed by looking for index.php
if [ ! -f "$WP_PATH/index.php" ]; then
    echo "[INFO] WordPress not found in $WP_PATH. Installing..."

    # Download and extract WordPress
    curl -o /tmp/wordpress.tar.gz https://wordpress.org/latest.tar.gz
    tar -xzf /tmp/wordpress.tar.gz -C $WP_PATH --strip-components=1
    rm /tmp/wordpress.tar.gz

    # Copy wp-config.php only if it does not exist
    if [ ! -f "$WP_PATH/wp-config.php" ] && [ -f "$WP_CONFIG_SOURCE" ]; then
        cp "$WP_CONFIG_SOURCE" "$WP_PATH/wp-config.php"
        echo "[INFO] Copied wp-config.php into place."
    fi

    # Set proper ownership and permissions
    chown -R www-data:www-data "$WP_PATH"
    find "$WP_PATH" -type d -exec chmod 755 {} \;
    find "$WP_PATH" -type f -exec chmod 644 {} \;

    echo "[INFO] WordPress installed successfully."
else
    echo "[INFO] WordPress already present in $WP_PATH. Skipping install."
fi

# Start PHP-FPM in the foreground
exec php-fpm7.4 -F
