FROM python:3.12

WORKDIR /backend

RUN apt-get update && apt-get install -y netcat-openbsd && rm -rf /var/lib/apt/lists/*

COPY requirements.txt .

RUN pip install --no-cache-dir -r requirements.txt

COPY . /backend

RUN chmod +x /backend/initialize_db_and_start_server.sh

EXPOSE 8000

ENTRYPOINT ["/backend/initialize_db_and_start_server.sh"]
