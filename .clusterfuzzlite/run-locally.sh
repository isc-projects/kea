#!/bin/sh

# Change to parent directory, so that the script can be called from anywhere.
parent_path=$(cd "$(dirname "${0}")" && pwd)
cd "${parent_path}" || exit 1

mkdir -p build/out
mkdir -p build/work

cd .. || exit 2

docker build -t kea-fuzzing -f .clusterfuzzlite/Dockerfile .

docker_run() {
  docker run \
    --interactive \
    --privileged \
    --platform linux/amd64 \
    --rm \
    --shm-size=2g \
    -e ARCHITECTURE=x86_64 \
    -e CIFUZZ=true \
    -e FUZZING_ARGS='-rss_limit_mb=8192' \
    -e FUZZING_ENGINE=libfuzzer \
    -e FUZZING_LANGUAGE=c++ \
    -e KEA_BUILD_DIR=/src \
    -e SANITIZER=address \
    -v "${parent_path}/build/out:/out" \
    -v "${parent_path}/build/work:/work" \
    kea-fuzzing \
    "${@}"
}

docker_run

docker_run compile
