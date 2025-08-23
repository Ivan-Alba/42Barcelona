# Use lightweight Debian
FROM debian:bullseye-slim

# Install NGINX
RUN apt-get update && apt-get install -y nginx \
    && rm -rf /var/lib/apt/lists/*

# Copy static site
RUN rm -f /etc/nginx/sites-enabled/default
COPY conf/static.conf /etc/nginx/sites-available/static.conf
RUN ln -s /etc/nginx/sites-available/static.conf /etc/nginx/sites-enabled/

# Expose HTTP port
EXPOSE 80

# Run NGINX in foreground
CMD ["nginx", "-g", "daemon off;"]
