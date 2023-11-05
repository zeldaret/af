FROM ubuntu:22.04 as build

# --- basic package installation ---
RUN apt-get update && \
    apt-get install -y \
        build-essential \
        git \
        clang \
        python3 \
        python3-pip \
        binutils-mips-linux-gnu \
        wget

# --- python package installation ---
COPY ./requirements.txt /temp/requirements.txt
COPY ./tools/splat/requirements.txt /temp/tools/splat/requirements.txt
RUN pip install -U -r /temp/requirements.txt
RUN rm -rf /temp

# --- set up work directory and env vars ---
RUN mkdir /af
WORKDIR /af
ENV PATH="/af/tools:${PATH}"

CMD echo 'Usage: docker run -it --rm -v ${PWD}:/af af make\n'\
         'See https://github.com/zeldaret/af/blob/master/README.md for more information'
