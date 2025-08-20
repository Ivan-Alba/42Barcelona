-- Create WordPress admin user with password from secret
CREATE USER '${MYSQL_ADMIN}'@'%' IDENTIFIED BY FILE '/run/secrets/db_password';
-- Grant all privileges on the WordPress database
GRANT ALL PRIVILEGES ON `${MYSQL_DATABASE}`.* TO '${MYSQL_ADMIN}'@'%';
FLUSH PRIVILEGES;

-- Create a limited-permission WordPress user with password from secret
CREATE USER '${MYSQL_USER}'@'%' IDENTIFIED BY FILE '/run/secrets/db_user_password';
-- Grant only basic permissions on the WordPress database
GRANT SELECT, INSERT, UPDATE, DELETE ON `${MYSQL_DATABASE}`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;

