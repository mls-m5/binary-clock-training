FROM docker.io/emscripten/emsdk:3.1.74

WORKDIR /workspace

COPY podman/build-wasm.sh /usr/local/bin/build-wasm
RUN chmod +x /usr/local/bin/build-wasm

ENTRYPOINT ["/usr/local/bin/build-wasm"]
