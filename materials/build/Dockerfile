FROM ubuntu

RUN apt-get update && apt-get install -y \
    git \
    git-lfs \
    curl \
    jq \
    bash \
    # build-base \
    # python3 \
    # valgrind \
    check \
    subunit \
    cppcheck \
    # alpine-sdk \
    # pcre \
    libncurses-dev \
    make \
    # clang-extra-tools \
    lcov

RUN mkdir /test 

COPY . /project
COPY materials/build/scripts /project/ci-scripts
COPY materials/build/scripts /project/tests
COPY materials/linters /project/tests/linters

WORKDIR "/project"

ENTRYPOINT ["/bin/bash","ci-scripts/test.sh"]
