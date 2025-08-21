#!/bin/bash

set -e

MYSQL_DIR=/var/lib/mysql
DB_USER_PASSWORD=$(cat /run/secrets/db_user_password)
DB_PASSWORD=$(cat /run/secrets/db_password)

# Check if MariaDB is already initialized
if [ ! -f "$MYSQL_DIR/.initialized" ]; then
    echo "[INFO] MariaDB not initialized. Initializing now..."
    
	# Start temporary server (no networking, only local socket)
    mysqld_safe --skip-networking --datadir="$MYSQL_DIR" &
    TEMP_PID=$!
    
	# Wait until server is ready to accept connections
    until mysqladmin ping --silent; do
        echo "[INFO] Waiting for MariaDB to start..."
        sleep 2
    done
    
	# Create database
    mysql -u root -e "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;"
    
	# Create users
    mysql -u root -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_USER_PASSWORD}';"
    mysql -u root -e "CREATE USER IF NOT EXISTS '${MYSQL_ADMIN}'@'%' IDENTIFIED BY '${DB_PASSWORD}';"
    
	# Grant privileges
    mysql -u root -e "GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_ADMIN}'@'%';"
    mysql -u root -e "FLUSH PRIVILEGES;"
    
	# Stop temporary server
    mysqladmin -u root shutdown
    wait $TEMP_PID
    
	# Mark as initialized
    touch "$MYSQL_DIR/.initialized"
    echo "[INFO] MariaDB initialized successfully."
else
    echo "[INFO] MariaDB already initialized. Skipping initialization."
fi

# Start MariaDB in foreground (real service)
exec mysqld --bind-address=0.0.0.0
