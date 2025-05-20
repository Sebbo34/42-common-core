all: 
	mkdir -p /home/sbo/data/mariadb
	mkdir -p /home/sbo/data/wordpress
	docker compose -f ./srcs/docker-compose.yml build
	docker compose -f ./srcs/docker-compose.yml up -d

logs:
	docker logs wordpress
	docker logs mariadb
	docker logs nginx

clean:
	@docker compose -f ./scrs/docker-compose.yml down

fclean: clean
	@sudo rm -rf /home/sbo/data/mariadb/*
	@sudo rm -rf /home/sbo/data/wordpress/*
	@docker system prune -af

re: fclean all

.Phony: all logs clean fclean