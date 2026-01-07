#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

MYSQL_DIR=/var/lib/mysql

# Read secrets into variables
DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
DB_USER_PASSWORD=$(cat /run/secrets/db_user_password)
DB_PASSWORD=$(cat /run/secrets/db_password)

# Check if MariaDB is already initialized
if [ ! -f "$MYSQL_DIR/.initialized" ]; then
    echo "[INFO] MariaDB not initialized. Initializing now..."
    
    # Install database if directory is empty
    mysql_install_db --user=mysql --datadir="$MYSQL_DIR" > /dev/null

    # Start temporary server (no networking, only local socket)
    mysqld_safe --skip-networking --datadir="$MYSQL_DIR" &
    TEMP_PID=$!
    
    # Wait until server is ready to accept connections
    until mysqladmin ping --silent; do
        echo "[INFO] Waiting for MariaDB to start..."
        sleep 2
    done
    
    # 1. Secure the ROOT user immediately
    mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASSWORD}'; FLUSH PRIVILEGES;"
    
    # 2. Use the new root password for subsequent commands
    # Create database
    mysql -u root -p"${DB_ROOT_PASSWORD}" -e "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;"
    
    # Create the two mandatory users (SQL level)
    # One for administration, one for regular use
    mysql -u root -p"${DB_ROOT_PASSWORD}" -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_USER_PASSWORD}';"
    mysql -u root -p"${DB_ROOT_PASSWORD}" -e "CREATE USER IF NOT EXISTS '${MYSQL_ADMIN}'@'%' IDENTIFIED BY '${DB_PASSWORD}';"
    
    # Grant privileges to the admin user
    mysql -u root -p"${DB_ROOT_PASSWORD}" -e "GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_ADMIN}'@'%';"
    mysql -u root -p"${DB_ROOT_PASSWORD}" -e "FLUSH PRIVILEGES;"
    
    # Stop temporary server
    mysqladmin -u root -p"${DB_ROOT_PASSWORD}" shutdown
    wait $TEMP_PID
    
    # Mark as initialized
    touch "$MYSQL_DIR/.initialized"
    echo "[INFO] MariaDB initialized successfully."
else
    echo "[INFO] MariaDB already initialized. Skipping initialization."
fi

# Start MariaDB in foreground (real service)
exec mysqld --bind-address=0.0.0.0
