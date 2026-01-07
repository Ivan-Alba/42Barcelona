# Makefile for Docker Compose project (Inception)

# Load .env so Make can use variables
ENV_FILE = srcs/.env
-include $(ENV_FILE)
export DOMAIN

# Paths and commands
COMPOSE_FILE   = srcs/docker-compose.yml
DOCKER_COMPOSE = docker-compose -f $(COMPOSE_FILE)
CERTS_DIR      = srcs/requirements/nginx/certs
SECRETS_DIR    = secrets
DOMAIN         = $(DOMAIN_NAME)
DATA_PATH      = /home/igarcia2/data

# --- MAIN TARGETS ---

# Default target: Simplified to trigger the full setup and launch
all: up
	@echo "[INFO] All done. Access your site at https://$(DOMAIN)"

# Rebuild: Full cleanup followed by a fresh start
re: fclean all

# --- DOCKER OPERATIONS ---

# Build images: Ensures data directories exist before building
build: setup_dirs
	@echo "[INFO] Building Docker images..."
	@$(DOCKER_COMPOSE) build

# Up: The core rule. Chains all dependencies to ensure a perfect launch.
# If anything is missing (certs, secrets, docker), it handles it before 'up -d'.
up: setup_dirs check_docker certs secrets build
	@echo "[INFO] Launching containers in background..."
	@$(DOCKER_COMPOSE) up -d 

# Down: Stops and removes containers/networks but PRESERVES volumes (Persistence)
down:
	@echo "[INFO] Stopping and removing containers/networks (preserving volumes)..."
	@$(DOCKER_COMPOSE) down

# PS: Shows status. Depends on secrets to avoid "undefined secret file" warnings.
ps: secrets
	@$(DOCKER_COMPOSE) ps

# Logs: Follow real-time output from all containers
logs:
	@$(DOCKER_COMPOSE) logs -f

# --- CLEANUP ---

# Clean: Stops containers and prunes unused Docker data (keeps volumes and secrets)
clean: down
	@echo "[INFO] Cleaning Docker system (pruning)..."
	@docker system prune -af
	@echo "[INFO] Clean finished."

# Fclean: Nuclear option. Removes containers, volumes, secrets, certs, and local data.
fclean: clean
	@echo "[INFO] Performing full clean (removing volumes and local data)..."
	@$(DOCKER_COMPOSE) down -v >/dev/null 2>&1
	@rm -rf $(CERTS_DIR)
	@rm -rf $(SECRETS_DIR)
	@echo "[INFO] Removing local data directories with sudo..."
	@sudo rm -rf $(DATA_PATH)
	@echo "[INFO] Full clean finished."

# --- PREREQUISITES (DEPENDENCIES) ---

# Create physical directories on the host for volume mapping
setup_dirs:
	@echo "[INFO] Ensuring local data directories exist..."
	@mkdir -p $(DATA_PATH)/mariadb
	@mkdir -p $(DATA_PATH)/wordpress
	@mkdir -p $(DATA_PATH)/portainer

# Generate self-signed SSL certificates for Nginx
certs:
	@if [ -f $(CERTS_DIR)/server.key ] && [ -f $(CERTS_DIR)/server.crt ]; then \
		echo "[INFO] Certificates already exist. Skipping..."; \
	else \
		mkdir -p $(CERTS_DIR); \
		openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
			-keyout $(CERTS_DIR)/server.key \
			-out $(CERTS_DIR)/server.crt \
			-subj "/C=ES/ST=Barcelona/L=Barcelona/O=42/OU=42/CN=$(DOMAIN)" >/dev/null 2>&1; \
		echo "[INFO] Certificates generated for $(DOMAIN)."; \
	fi

# Generate random passwords for secure storage (Secrets)
secrets:
	@mkdir -p $(SECRETS_DIR)
	@if [ ! -f $(SECRETS_DIR)/db_root_password.txt ]; then \
		echo -n "$$(openssl rand -base64 16)" > $(SECRETS_DIR)/db_root_password.txt; \
	fi
	@if [ ! -f $(SECRETS_DIR)/db_password.txt ]; then \
		echo -n "$$(openssl rand -base64 16)" > $(SECRETS_DIR)/db_password.txt; \
	fi
	@if [ ! -f $(SECRETS_DIR)/db_user_password.txt ]; then \
		echo -n "$$(openssl rand -base64 16)" > $(SECRETS_DIR)/db_user_password.txt; \
	fi
	@if [ ! -f $(SECRETS_DIR)/ftp_password.txt ]; then \
		echo -n "$$(openssl rand -base64 16)" > $(SECRETS_DIR)/ftp_password.txt; \
	fi
	@echo "[INFO] Secrets are ready."

# Automatically install Docker and Docker-compose if not found on the system
check_docker:
	@command -v docker >/dev/null 2>&1 || { \
		echo "[INFO] Docker not found. Installing..."; \
		sudo apt update && sudo apt install -y docker.io; \
	}
	@command -v docker-compose >/dev/null 2>&1 || { \
		echo "[INFO] docker-compose not found. Installing..."; \
		sudo apt update && sudo apt install -y docker-compose; \
	}

.PHONY: all re clean fclean build up down certs secrets setup_dirs logs ps
