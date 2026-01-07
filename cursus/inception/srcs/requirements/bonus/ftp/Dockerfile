# Base image: Debian Bullseye
FROM debian:bullseye

# Install vsftpd and clean up
RUN apt-get update && apt-get install -y vsftpd && rm -rf /var/lib/apt/lists/*

# Fix: vsftpd requirement for 500 OOPS error
# This directory must exist and not be writable by the ftp user
RUN mkdir -p /var/run/vsftpd/empty && \
    chmod 555 /var/run/vsftpd/empty

# Copy configuration
COPY conf/vsftpd.conf /etc/vsftpd.conf

# Expose ports (Control + Passive range)
EXPOSE 21 21000-21010

# Entrypoint logic:
# 1. Read password from secret
# 2. Create the user dynamicallly using $FTP_USER from environment
# 3. Set the home directory and permissions
# 4. Start vsftpd
CMD bash -c '\
    PASSWORD=$(cat /run/secrets/ftp_password) && \
    if ! id -u "$FTP_USER" >/dev/null 2>&1; then \
        useradd -m -s /bin/bash "$FTP_USER"; \
    fi && \
    echo "$FTP_USER:$PASSWORD" | chpasswd && \
    chown -R $FTP_USER:$FTP_USER /home/$FTP_USER && \
    echo "[INFO] vsftpd is starting for user: $FTP_USER" && \
    /usr/sbin/vsftpd /etc/vsftpd.conf \
'
