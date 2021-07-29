# Base image
FROM ubuntu:20.04

# Install basic packages
# http://packages.ubuntu.com/de/trusty/build-essential
RUN apt-get update && apt-get -y install \
	build-essential

# Install additional tools
# http://packages.ubuntu.com/de/trusty/valgrind
# Comment out git if you don't want to manage the git repo
# from within the container
RUN apt-get install -y \
	git
#	valgrind \

# Install zsh and oh-my-zsh (comment out if you're fine with
# the regular shell)
RUN apt-get install -y \
	zsh \
	wget \
	&& sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Set working directory
WORKDIR /code

# Create volume
#VOLUME /code

# Copy contents of current working directory to /code
COPY . .

# Default command to run on starting the container: start shell
#CMD /bin/sh
CMD /bin/zsh
