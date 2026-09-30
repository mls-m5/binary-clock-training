.PHONY: podman

podman:
	podman build -f Containerfile -t binary-training-wasm .
	podman run --rm --userns=keep-id -v "$(CURDIR):/workspace:Z" binary-training-wasm
