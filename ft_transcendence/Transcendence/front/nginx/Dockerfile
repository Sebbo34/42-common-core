FROM nginx:1.27

RUN apt-get update && apt-get install -y openssl gettext && rm -rf /var/lib/apt/lists/*

COPY default.conf.template /etc/nginx/conf.d/default.conf.template

RUN mkdir -p /etc/nginx/ssl && \
	openssl req -x509 -nodes -days 365 \
	  -newkey rsa:2048 \
	  -subj "/CN=${LOCAL_IP}" \
	  -keyout /etc/nginx/ssl/transcendence.key \
	  -out /etc/nginx/ssl/transcendence.crt

CMD envsubst '$LOCAL_IP $WEB_SERVICE_URL' < /etc/nginx/conf.d/default.conf.template > /etc/nginx/conf.d/default.conf && \
	exec nginx -g 'daemon off;'
