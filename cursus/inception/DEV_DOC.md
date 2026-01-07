# Developer Documentation

## Architecture Details
- **Container Isolation**: All containers belong to `wp_network`.
- **Nginx Proxy**: Acts as a Reverse Proxy for Adminer, Portainer, and the Static Site, centralizing all traffic through Port 443 with TLS v1.3.
- **Service Communication**:
    - **WordPress <-> MariaDB**: via Port 3306.
    - **WordPress <-> Redis**: via Port 6379 (Object Cache).
    - **Nginx <-> WordPress**: via Port 9000 (FastCGI/PHP-FPM).

## Maintenance Commands
- **Check Status**: `make ps`.
- **Follow Logs**: `make logs` (Press Ctrl+C to exit, handled via `|| true` in Makefile).
- **Manual Debug**: `docker exec -it [container_name] bash`.

## Data Persistence
All data is stored in `/home/igarcia2/data/`.
- `mariadb/`: Database binary files.
- `wordpress/`: PHP files and uploads.
- `portainer/`: Portainer database and configs.
