# requirements/bonus/portainer/Dockerfile

FROM portainer/portainer-ce:latest

# Creamos el directorio para los datos de Portainer
VOLUME /data

# No exponemos puertos porque el acceso será mediante Nginx
# (nginx -> proxy_pass a http://portainer:9000)

# Definir el comando de arranque de Portainer
CMD ["-H", "unix:///var/run/docker.sock"]
