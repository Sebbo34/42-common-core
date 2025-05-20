#!/bin/bash

echo "Waiting for the database to connect..."
for i in $(seq 1 $TIMEOUT); do
	nc -z $POSTGRES_HOST $POSTGRES_PORT &&
		echo "✅ Database connection successful" &&
		break
	sleep 1
done

if [ $i -eq $TIMEOUT ]; then
	echo "PostgreSQL remains unresponsive after $TIMEOUT seconds"
	echo "❌ Database connection failed"
	exit 1
fi

echo "Running migrations..."

python manage.py makemigrations app
echo "✅ Migration files created"

python manage.py migrate
echo "✅ Migration files applied to the database"

echo "Launching Django server..."

python manage.py runserver 0.0.0.0:8000
