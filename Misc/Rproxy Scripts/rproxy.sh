apt-get update
apt install nginx
apt install python3
systemctl stop apache2
systemctl disable apache2
curl -s https://install.zerotier.com | sudo bash
zerotier-cli join (ID HERE)
python3 nginx-setup.py
unlink /etc/nginx/sites-enabled/default
ln -s /etc/nginx/sites-available/reverse-proxy.conf /etc/nginx/sites-enabled/reverse-proxy.conf
systemctl enable ngin
systemctl start nginx
