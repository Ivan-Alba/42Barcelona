# Developer Documentation - Inception

## Development Setup
1. **Prerequisites**: A Debian-based Linux environment.
2. **Configuration**: The `srcs/.env` file must define the variables used in `docker-compose.yml` (e.g., `${MYSQL_USER}`, `${FTP_USER}`).
3. **Secret Generation**: The `Makefile` uses `openssl rand -base64 16` to create unique passwords in the `secrets/` folder. These files are mapped in the `secrets:` section of the compose file.

## Architecture Details
- **Container Isolation**: All containers belong to `wp_network`.
- **Security**: 
    - Nginx is the only service with port 443 mapped.
    - WordPress connects to MariaDB using the `MYSQL_ADMIN` user and a secret-provided password.
    - The FTP container uses passive ports `21000-21010` for data transfer.
- **Persistence Strategy**:
    - `wordpress_db_data`: Maps to `/var/lib/mysql`.
    - `wordpress_site_data`: Shared between WordPress, Nginx (read-only), and FTP.
    - `portainer_data`: Persists Portainer configurations.

## Maintenance Commands
- **Rebuild from scratch**: `make re`.
- **Inspect Network**: `docker network inspect srcs_wp_network`.
- **View Container Logs**: `docker logs [container_name]`.
- **Debug Configuration**: Use `docker exec -it [container_name] sh` to inspect internal files like `/run/secrets/db_password`.

## Data Persistence & Storage
All project data persists even if containers are stopped. Data is stored in Docker-managed volumes. To completely wipe the database and files, use `make fclean`, which explicitly runs `docker volume rm`.
