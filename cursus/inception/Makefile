# Makefile for Docker Compose project

# Load .env so Make can use variables (Compose auto-loads srcs/.env)
ENV_FILE = srcs/.env
-include $(ENV_FILE)
export DOMAIN

# Paths and commands
COMPOSE_FILE   = srcs/docker-compose.yml
DOCKER_COMPOSE = docker-compose -f $(COMPOSE_FILE)
CERTS_DIR      = srcs/requirements/nginx/certs
SECRETS_DIR    = secrets
DOMAIN         = $(DOMAIN_NAME)

# Default target: build and run
all: check_docker certs secrets build up

# Rebuild everything from scratch
re: fclean all

# Stop containers and remove networks
clean:
	$(DOCKER_COMPOSE) down
	docker system prune -af --volumes

# Clean everything: containers, images, volumes and certs
fclean: clean
	docker volume rm srcs_wordpress_db_data srcs_wordpress_site_data
	rm -rf $(CERTS_DIR)
	rm -rf $(SECRETS_DIR)

# Build images
build:
	$(DOCKER_COMPOSE) build

# Run in detached mode
up:
	$(DOCKER_COMPOSE) up -d 

# Generate self-signed SSL certificates
certs:
	@if [ -f $(CERTS_DIR)/server.key ] && [ -f $(CERTS_DIR)/server.crt ]; then \
		echo "[INFO] Certificates already exist. Skipping..."; \
	else \
		mkdir -p $(CERTS_DIR); \
		openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
			-keyout $(CERTS_DIR)/server.key \
			-out $(CERTS_DIR)/server.crt \
			-subj "/C=FR/ST=Paris/L=Paris/O=42/OU=42/CN=$(DOMAIN)"; \
		echo "[INFO] Certificates generated."; \
	fi

# Generate secrets random passwords
secrets:
	mkdir -p $(SECRETS_DIR)
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

# Check docker installation
check_docker:
	@command -v docker >/dev/null 2>&1 || { \
		echo "Docker not found. Installing..."; \
		sudo apt update; \
		sudo apt install -y apt-transport-https ca-certificates curl software-properties-common; \
		curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg; \
		echo "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $$(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null; \
		sudo apt update; \
		sudo apt install -y docker-ce docker-ce-cli containerd.io; \
	}
	@command -v docker-compose >/dev/null 2>&1 || { \
		echo "docker-compose not found. Installing..."; \
		sudo apt update; \
		sudo apt install -y docker-compose; \
	}

.PHONY: all re clean fclean build up certs secrets
