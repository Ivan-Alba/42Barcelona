*This project has been created as part of the 42 curriculum by igarcia2.*

## Description
Inception is a system administration project that involves orchestrating a complex infrastructure using **Docker Compose**. The project focuses on building custom Docker images (Debian/Alpine) to run a secure WordPress stack. The infrastructure is isolated within a dedicated virtual network, featuring Nginx as the sole TLS entry point, MariaDB for data persistence, and several bonus services including Redis, FTP, a static site, Adminer, and Portainer.

## Instructions
1. **Host Setup**: Map your local IP to the domain in `/etc/hosts`:
   `127.0.0.1 igarcia2.42.fr`
2. **Environment**: Create a `srcs/.env` file. Do not include passwords; only configuration variables like `DOMAIN_NAME`, `MYSQL_USER`, `MYSQL_DATABASE`, and `FTP_USER`.
3. **Execution**:
   - `make`: Automates Docker check, SSL certificate generation, random secret creation, and starts the stack.
   - `make clean`: Stops containers and performs a system prune.
   - `make fclean`: Deep clean including the removal of all volumes, secrets, and certificates.

## Project Design & Choices
### Virtual Machines vs Docker
Virtual Machines virtualize the hardware layer, requiring a full Guest OS. Docker virtualizes the Operating System layer, allowing containers to share the host's kernel. This makes Docker significantly more efficient in terms of RAM and startup speed.

### Secrets vs Environment Variables
Passwords in this project are handled via **Docker Secrets** rather than `.env` variables. Secrets are stored in `.txt` files (ignored by Git) and mounted as temporary files in `/run/secrets/` inside containers. This prevents sensitive data from being exposed in process logs or environment dumps.

### Docker Network vs Host Network
We use a custom bridge network (`wp_network`). Unlike `host` networking, which shares the host's IP stack, a bridge network provides isolation. Only Nginx exposes port 443 to the host; all other inter-service communication happens internally via Docker's DNS.

### Docker Volumes vs Bind Mounts
The project uses **Named Volumes** (`wordpress_site_data`, `wordpress_db_data`, etc.) for database and site persistence. Unlike bind mounts, which link to a specific host path, named volumes are fully managed by Docker, providing better performance and decoupling from the host's file structure.

## Resources
- [Docker & Docker Compose Official Docs](https://docs.docker.com/)
- [Nginx TLS/SSL Configuration](https://nginx.org/en/docs/http/configuring_https_servers.html)
- **AI Usage**: AI was utilized to automate the `Makefile` logic for SSL/Secret generation and to structure the technical comparisons in this documentation.
