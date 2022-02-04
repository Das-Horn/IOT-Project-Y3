with open("/etc/nginx/sites-available/reverse-proxy.conf", "w") as f:
    config = """
            server {

            access_log /var/log/nginx/reverse-access.log;
            error_log /var/log/nginx/reverse-error.log;

            location / {
            }
    }
    """
    f.writelines(config)
