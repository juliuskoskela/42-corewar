#!/bin/bash

if ! command -v docker &> /dev/null
then
    echo "docker not found: install to run this script"
    exit
fi

image_name="ubuntu-container"

# Build a Docker image
docker-compose build $image_name

# Start a container instance
# option --rm removes the container once it has been exited
docker-compose run --rm $image_name
