FROM registry.gitlab.isc.org/isc-projects/kea:fuzz-latest

# Copy repo and link build.sh so that it runs from a location relative to the Kea repo.
WORKDIR "${SRC}"
COPY . "${SRC}/kea"
RUN ln -s "${SRC}/kea/.clusterfuzzlite/build.sh" "${SRC}/build.sh"
