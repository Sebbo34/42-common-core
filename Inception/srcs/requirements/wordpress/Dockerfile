FROM debian:bullseye

RUN apt update
RUN apt upgrade -y
RUN apt-get -y install wget
RUN apt-get install -y php7.3\
	php-fpm\
	php-mysql\
	mariadb-client \
	curl	
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar

RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp
COPY ./conf/www.conf /etc/php/7.4/fpm/pool.d/
COPY ./conf/auto-config.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/auto-config.sh
EXPOSE 9000
ENTRYPOINT ["/usr/local/bin/auto-config.sh"]