# User Documentation - Inception Stack

## Services Overview
- **Web Server (Nginx)**: The secure entry point for all web traffic via HTTPS (Port 443).
- **WordPress**: The main CMS platform powered by PHP-FPM.
- **MariaDB**: The relational database used by WordPress to store content.
- **Redis Cache**: A high-performance object cache to speed up WordPress database queries.
- **Adminer**: A lightweight, web-based tool for database management.
- **FTP Server**: A secure server providing direct file access to the WordPress volume (Port 21).
- **Static Site**: A simple secondary web page served via Nginx for portfolio or info purposes.
- **Portainer**: A visual dashboard to monitor and manage all Docker containers.

## Operational Guide
- **Starting the project**: Execute `make` in the root directory. This will handle certificates, secrets, and detached startup.
- **Checking Status**: Run `make ps` to verify that all 8 services are "Up".
- **Stopping the project**: Execute `make down` to stop containers without losing data.

## Accessing the Infrastructure
Since Nginx acts as a **Reverse Proxy**, all web services are centralized under the main domain on Port 443:

- **Main WordPress Site**: [https://igarcia2.42.fr](https://igarcia2.42.fr)
- **WordPress Admin**: [https://igarcia2.42.fr/wp-admin](https://igarcia2.42.fr/wp-admin)
- **Adminer (DB)**: [https://igarcia2.42.fr/adminer](https://igarcia2.42.fr/adminer)
- **Portainer (Docker UI)**: [https://igarcia2.42.fr/portainer](https://igarcia2.42.fr/portainer)
- **Static Portfolio**: [https://igarcia2.42.fr/myPage/](https://igarcia2.42.fr/myPage/)



## Bonus Features
### Redis Object Cache
Redis is pre-configured to work with WordPress. You can verify the connection status by running:
`docker exec -it wordpress wp redis status --allow-root`

### FTP Server
To access files via FTP (e.g., using FileZilla or the `ftp` command):
- **Host**: `igarcia2.42.fr` (or `localhost` if testing locally)
- **Port**: 21
- **User**: The value defined as `FTP_USER` in your `.env` file.
- **Data Ports**: The server uses passive ports `21000-21010`.

## Credential Management
Passwords are automatically generated for security. If you need to log in to the database or FTP, check the following local files:
- `secrets/db_root_password.txt`
- `secrets/db_password.txt`
- `secrets/ftp_password.txt`
