# Agent notes

- At the end of every task, before testing or committing, run `clang-format -i`
  on all tracked C++ source and header files (`.cpp`, `.cc`, `.cxx`, `.h`,
  `.hpp`) using the repository's `.clang-format`. Check formatting with
  `clang-format --dry-run --Werror` on those files; do not format generated or
  fetched dependency files under `build/`.

- This is a C++17 binary-clock exercise compiled with Emscripten to a static
  HTML/JavaScript/WebAssembly site. The clock uses 16 bits in row-major order:
  hours (indices 0–3, range 0–15), minutes (4–9, range 0–59), seconds (10–15,
  range 0–59). Do not claim it covers a full 24-hour day without changing the
  representation.
- `src/clock.hpp` and `src/clock.cpp` own the clock state, bit positions/weights,
  answer evaluation and per-field correctness; `test/clock_test.cpp` uses doctest
  with a fixed random seed in a native CMake build (`ctest --test-dir <build>`).
  `test/CMakeLists.txt` fetches a pinned doctest 2.5.3 GitHub ZIP with a SHA256
  hash only for native builds; keep WebAssembly builds free of test dependencies.
  `src/main.cpp` exports this logic and English/Swedish text and feedback through
  `clock_*` C functions. JavaScript in `web/shell.html` calls these via
  `Module.ccall` and only handles DOM rendering, form validity, language choice
  and storage. Keep the interface and the English fallback HTML in sync with
  C++ translations. Language changes must preserve the current round/answers.
- `web/shell.html` is the Emscripten shell: keep `{{{ SCRIPT }}}` in place and
  define `Module` before it. `CMakeLists.txt` configures Emscripten to emit
  `index.html`, `index.js` and `index.wasm`. It tracks changes to the shell
  through `LINK_DEPENDS`, so editing the page triggers a relink.
- Run `make podman` to build locally. It uses `Containerfile` and
  `podman/build-wasm.sh` and writes to `build/podman/`. Serve that directory
  over HTTP to test the page, e.g. `python3 -m http.server 8000 --directory
  build/podman`. Build outputs under `build/` are ignored; do not commit them.
- `.github/workflows/native-tests.yml` builds and runs the native doctest
  suite in Release mode on pushes and PRs to `main` (or manual runs).
  `.github/workflows/pages.yml` separately builds on pushes to `main` (or
  manual runs) in the pinned Emscripten container and uploads only
  `build/pages/site/` to GitHub Pages; deployment is not gated on native tests. Keep its Emscripten version aligned with `Containerfile`, and
  keep generated filenames aligned with CMake and README.
- Native CMake builds compile an interactive terminal exercise. `src/terminal.cpp`
  handles the 4×4 circle-only bit display (`●`/`○`, no labels in the grid) and
  line input via injected streams; `src/main.cpp`
  runs it with `std::cin` and `std::cout`. `test/terminal_test.cpp` covers input,
  hints, success/new rounds and EOF. Run `./build/native/binary-training` and
  `ctest --test-dir build/native --output-on-failure` after building. Prefer
  checking both the native and Podman builds after C++ changes, and the browser
  page after changes to HTML or the Emscripten configuration.
