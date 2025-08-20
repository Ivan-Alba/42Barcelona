# Use Debian (penultimate stable: bullseye-slim)
FROM debian:bullseye-slim

# Avoid interactive prompts during install
ENV DEBIAN_FRONTEND=noninteractive

# Install NGINX and OpenSSL (for HTTPS support)
RUN apt-get update && \
    apt-get install -y nginx openssl && \
    rm -rf /var/lib/apt/lists/*

# Create directories for config and SSL certificates
RUN mkdir -p /etc/nginx/conf.d /etc/nginx/certs

# Copy NGINX config files
COPY conf/ /etc/nginx/conf.d/

# Copy SSL certificates (server.crt and server.key)
COPY certs/ /etc/nginx/certs/

# Expose HTTPS port
EXPOSE 443

# Run NGINX in foreground (prevent daemonizing)
CMD ["nginx", "-g", "daemon off;"]
