# Base image
FROM ubuntu:20.04

# Install basic packages
RUN apt-get update && apt-get -y install \
	build-essential

# Install additional tools
RUN apt-get update && apt-get -y install \
	git \
	vim

ARG user="ubuntu-user"

# Create a new user to run as (by default, container is run as root)
RUN groupadd -r ${user} && adduser --ingroup ${user} ${user}

# Install zsh and oh-my-zsh (comment out if you're fine with the regular shell)
#RUN apt-get install -y \
#	zsh \
#	wget \
#	&& sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Set working directory
WORKDIR /code

# Next, you can either
# 1) share the current working directory by binding it to the container as a volume
#    => changes made on the host and on the guest side are propagated to the other, or
# 2) make a copy of all contents of current working directory to the container
#    => changes made on the container side do not affect files on the host

# 1) Create volume
#VOLUME /code

# 2) Copy contents of current working directory to /code
COPY . .
RUN chown -R ${user}:${user} .

USER ${user}

# Default command to run on starting the container: start shell
CMD /bin/bash
#CMD /bin/zsh
