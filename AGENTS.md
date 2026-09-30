# Agent notes

- This is a C++17 binary-clock exercise compiled with Emscripten to a static
  HTML/JavaScript/WebAssembly site. The clock uses 16 bits in row-major order:
  hours (indices 0–3, range 0–15), minutes (4–9, range 0–59), seconds (10–15,
  range 0–59). Do not claim it covers a full 24-hour day without changing the
  representation.
- `src/main.cpp` owns random time generation, bit extraction and answer checks.
  Its exported C functions (`clock_new_round`, `clock_bit`, `clock_check`) are
  called by JavaScript in `web/shell.html` via `Module.ccall`. Keep both sides
  of that interface in sync.
- `web/shell.html` is the Emscripten shell: keep `{{{ SCRIPT }}}` in place and
  define `Module` before it. `CMakeLists.txt` configures Emscripten to emit
  `index.html`, `index.js` and `index.wasm`.
- Run `make podman` to build locally. It uses `Containerfile` and
  `podman/build-wasm.sh` and writes to `build/podman/`. Serve that directory
  over HTTP to test the page, e.g. `python3 -m http.server 8000 --directory
  build/podman`. Build outputs under `build/` are ignored; do not commit them.
- `.github/workflows/pages.yml` builds on pushes to `main` (or manual runs)
  in the pinned Emscripten container and uploads only `build/pages/site/` to
  GitHub Pages. Keep its Emscripten version aligned with `Containerfile`, and
  keep generated filenames aligned with CMake and README.
- Native CMake builds compile a small informational executable, not the
  browser exercise. Prefer checking both the Podman build and the browser page
  after changes to C++/HTML or the Emscripten configuration.
