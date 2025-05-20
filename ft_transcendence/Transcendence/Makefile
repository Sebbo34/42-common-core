NAME = ft_transcendence

BRIGHT_RED = \033[0;91m
GREEN = \033[0;32m
FULL_GREEN = \033[7;32m
RESET = \033[0m

all: ${NAME}

${NAME}:
	@echo "\n${BRIGHT_RED}Creating ${NAME}...${RESET}\n"
	@mkdir -p ./data/postgres_db
	@docker compose -f docker-compose.yml -p ${NAME} up -d --build
	@echo "\n${FULL_GREEN}${NAME} created!${RESET}\n"

down:
	@docker exec -it transcendence_web bash -c "rm -rf /backend/app/migrations"
	@docker exec -it transcendence_web bash -c "rm -rf /backend/app/__pycache__"
	@docker exec -it transcendence_web bash -c "rm -rf /backend/pong_project/__pycache__"
	@docker compose -f docker-compose.yml -p ${NAME} down
	@echo "\n${GREEN}Stopped and removed containers, networks, and " \
		"volumes established by the compose up command${RESET}\n"

clean: down
	@CONT=$(docker ps -qa); \
	if [ -n "$$CONT" ]; then \
		docker stop $$CONT || true; \
		docker rm $$CONT || true; \
	fi
	@IMAGES=$(docker images -qa); \
	if [ -n "$$IMAGES" ]; then \
		docker rmi -f $$IMAGES || true; \
	fi
	@VOLUMES=$(docker volume ls -q); \
	if [ -n "$$VOLUMES" ]; then \
		docker volume rm $$VOLUMES || true; \
	fi
	@NETWORKS=$(docker network ls -q); \
	if [ -n "$$NETWORKS" ]; then \
		docker network rm $$NETWORKS 2>/dev/null || true; \
	fi

	@docker system prune -af --volumes
	@docker run --rm -v $(PWD)/data:/data debian rm -rf data/*
	@rm -rf data
	@echo "\n${GREEN}Docker cleaned${RESET}\n"

re: clean all

.PHONY: all re down clean
