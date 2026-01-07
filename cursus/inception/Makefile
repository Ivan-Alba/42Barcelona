# Makefile for Docker Compose project

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

# Default target
all: setup_dirs check_docker certs secrets build up
	@echo "[INFO] All done. Access your site at https://$(DOMAIN)"

# Rebuild
re: fclean all

# Create local directories
setup_dirs:
	@echo "[INFO] Creating local data directories in $(DATA_PATH)..."
	@mkdir -p $(DATA_PATH)/mariadb
	@mkdir -p $(DATA_PATH)/wordpress
	@mkdir -p $(DATA_PATH)/portainer

# Stop and remove containers
clean:
	@echo "[INFO] Stopping and removing containers and networks..."
	@$(DOCKER_COMPOSE) down >/dev/null 2>&1
	@docker system prune -af
	@echo "[INFO] Clean finished."

# Full clean
fclean: clean
	@echo "[INFO] Performing full clean..."
	@$(DOCKER_COMPOSE) down -v >/dev/null 2>&1
	@rm -rf $(CERTS_DIR)
	@rm -rf $(SECRETS_DIR)
	@echo "[INFO] Removing local data directories..."
	@sudo rm -rf $(DATA_PATH)
	@echo "[INFO] Full clean finished."

# Build images
build:
	@echo "[INFO] Building Docker images..."
	@$(DOCKER_COMPOSE) build

# Run
up:
	@echo "[INFO] Launching containers..."
	@$(DOCKER_COMPOSE) up -d 

# SSL Certs
certs:
	@if [ -f $(CERTS_DIR)/server.key ] && [ -f $(CERTS_DIR)/server.crt ]; then \
		echo "[INFO] Certificates already exist. Skipping..."; \
	else \
		mkdir -p $(CERTS_DIR); \
		openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
			-keyout $(CERTS_DIR)/server.key \
			-out $(CERTS_DIR)/server.crt \
			-subj "/C=FR/ST=Paris/L=Paris/O=42/OU=42/CN=$(DOMAIN)" >/dev/null 2>&1; \
		echo "[INFO] Certificates generated for $(DOMAIN)."; \
	fi

# Secrets
secrets:
	@mkdir -p $(SECRETS_DIR)
	@if [ ! -f $(SECRETS_DIR)/db_root_password.txt ]; then \
		echo -n "$$(openssl rand -base64 16)" > $(SECRETS_DIR)/db_root_password.txt; \
		echo "[INFO] Generated db_root_password"; \
	fi
	@if [ ! -f $(SECRETS_DIR)/db_password.txt ]; then \
		echo -n "$$(openssl rand -base64 16)" > $(SECRETS_DIR)/db_password.txt; \
		echo "[INFO] Generated db_password"; \
	fi
	@if [ ! -f $(SECRETS_DIR)/db_user_password.txt ]; then \
		echo -n "$$(openssl rand -base64 16)" > $(SECRETS_DIR)/db_user_password.txt; \
		echo "[INFO] Generated db_user_password"; \
	fi
	@if [ ! -f $(SECRETS_DIR)/ftp_password.txt ]; then \
		echo -n "$$(openssl rand -base64 16)" > $(SECRETS_DIR)/ftp_password.txt; \
		echo "[INFO] Generated ftp_password"; \
	fi

# Docker install
check_docker:
	@command -v docker >/dev/null 2>&1 || { \
		echo "[INFO] Docker not found. Installing..."; \
		sudo apt update && sudo apt install -y docker.io; \
	}
	@command -v docker-compose >/dev/null 2>&1 || { \
		echo "[INFO] docker-compose not found. Installing..."; \
		sudo apt update && sudo apt install -y docker-compose; \
	}

.PHONY: all re clean fclean build up certs secrets setup_dirs
