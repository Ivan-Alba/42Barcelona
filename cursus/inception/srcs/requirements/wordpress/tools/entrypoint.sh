#!/bin/bash

set -e

#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Path where WordPress lives
WP_PATH="/var/www/html"

# Database variables from .env and secrets
DB_HOST=${WORDPRESS_DB_HOST}
DB_NAME=${WORDPRESS_DB_NAME}
DB_USER=${WORDPRESS_DB_USER} # This is MYSQL_ADMIN
DB_PASSWORD=$(cat /run/secrets/db_password)
DB_USER_NAME=${MYSQL_USER}
DB_USER_PASSWORD=$(cat /run/secrets/db_user_password)

# Wait for MariaDB to be fully ready
echo "[INFO] Waiting for MariaDB at $DB_HOST..."
until mysql -h "$DB_HOST" -u "$DB_USER" -p"$DB_PASSWORD" "$DB_NAME" &> /dev/null; do
    echo "[INFO] MariaDB not ready, retrying in 2 seconds..."
    sleep 2
done
echo "[INFO] MariaDB is ready."

# Move to WordPress directory
cd $WP_PATH

# 1. CORE INSTALLATION (Only if wp-config doesn't exist)
if [ ! -f "wp-config.php" ]; then
    echo "[INFO] WordPress not found. Downloading and installing..."

    # Download WordPress core
    wp core download --allow-root

    # Create wp-config.php using secrets
    wp config create \
        --dbname="$DB_NAME" \
        --dbuser="$DB_USER" \
        --dbpass="$DB_PASSWORD" \
        --dbhost="$DB_HOST" \
        --allow-root

    # Run installation (Creates the Admin User)
    wp core install \
        --url="https://${DOMAIN_NAME}" \
        --title="Inception" \
        --admin_user="${DB_USER}" \
        --admin_password="${DB_PASSWORD}" \
        --admin_email="${DB_USER}@student.42.fr" \
        --skip-email \
        --allow-root

    echo "[INFO] WordPress core installed."
else
    echo "[INFO] WordPress core already present."
fi

# 2. USER MANAGEMENT (Outside the if, to ensure they always exist)
# Create second user if it doesn't exist
if ! wp user get "${DB_USER_NAME}" --allow-root > /dev/null 2>&1; then
    echo "[INFO] Creating second user: ${DB_USER_NAME}..."
    wp user create \
        "${DB_USER_NAME}" \
        "${DB_USER_NAME}@student.42.fr" \
        --user_pass="${DB_USER_PASSWORD}" \
        --role=author \
        --allow-root
    echo "[INFO] Second user created."
else
    echo "[INFO] Second user already exists."
fi

# Set proper ownership and permissions
chown -R www-data:www-data "$WP_PATH"

# Start PHP-FPM in foreground
echo "[INFO] Starting PHP-FPM..."
exec php-fpm7.4 -F
