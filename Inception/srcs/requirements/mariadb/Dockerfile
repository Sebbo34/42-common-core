FROM debian:bullseye

RUN apt update
RUN apt upgrade -y
RUN apt install mariadb-server -y   
RUN apt-get install -y mariadb-client
COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf 
COPY ./tools/script.sh /
RUN chmod +x /script.sh
RUN mkdir -p /var/run/mysqld
RUN mkdir -p /var/lib/mysql
RUN chown mysql:mysql /var/run/mysqld/
RUN chmod -R 755 /var/run/mysqld/
RUN chown mysql:mysql /var/lib/mysql/
RUN chmod -R 755 /var/lib/mysql/
EXPOSE 3306
ENTRYPOINT [ "/script.sh" ]
