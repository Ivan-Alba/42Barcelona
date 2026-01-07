# Inception - igarcia2

*This project has been created as part of the 42 curriculum by igarcia2.*

## Description
Inception is a system administration project that involves orchestrating a complex infrastructure using **Docker Compose**. The project focuses on building custom Docker images based on **Debian Bullseye** to run a secure WordPress stack. The infrastructure is isolated within a dedicated virtual network, featuring Nginx as the sole TLS entry point (Port 443).

## Instructions
1. **Host Setup**: Map your local IP to the domain in `/etc/hosts`:
   `127.0.0.1 igarcia2.42.fr`
2. **Environment**: Create a `srcs/.env` file with configuration variables like `DOMAIN_NAME`, `MYSQL_USER`, `MYSQL_DATABASE`, and `FTP_USER`.
3. **Execution**:
   - `make`: Automates directory setup, Docker check, SSL generation, random secret creation, and starts the stack in detached mode.
   - `make down`: Stops and removes containers/networks while **preserving** volumes.
   - `make fclean`: Deep clean including the removal of all volumes, secrets, and certificates.

## Project Design & Choices
### Secrets vs Environment Variables
Passwords are handled via **Docker Secrets**. They are stored in `.txt` files in a non-indexed `secrets/` folder and mounted at `/run/secrets/` inside containers. This prevents sensitive data from being exposed in environment dumps (`env` command).

### Docker Network vs Host Network
We use a custom bridge network (`wp_network`). Only Nginx exposes port 443. All other services communicate internally using Docker's internal DNS (e.g., WordPress connects to `mariadb:3306`).
