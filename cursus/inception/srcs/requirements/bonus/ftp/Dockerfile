FROM debian:bullseye

# Install vsftpd (FTP server) and clean up apt cache
RUN apt-get update && apt-get install -y vsftpd \
    && rm -rf /var/lib/apt/lists/*

# Create FTP user without a password initially
RUN useradd -m ftpuser

# Copy vsftpd configuration file into the container
COPY conf/vsftpd.conf /etc/vsftpd.conf

# Expose FTP port and passive ports range
EXPOSE 21 21000-21010

# Entrypoint: read password from Docker secret and start vsftpd
# The secret is mounted at /run/secrets/ftp_password at runtime
# passwd --stdin sets the ftpuser password
# Entrypoint: cambia la contraseña desde secret y lanza vsftpd
CMD bash -c '\
    PASSWORD=$(cat /run/secrets/ftp_password) && \
    echo "$FTP_USER:$PASSWORD" | chpasswd && \
    /usr/sbin/vsftpd /etc/vsftpd.conf \
'
