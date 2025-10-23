Always use context7 when I need code generation, setup or configuration steps, or
library/API documentation. This means you should automatically use the Context7 MCP
tools to resolve library id and get library docs without me having to explicitly ask.

---

Repository overview:
- `CMakeLists.txt` is the top-level entry point. It enforces C++17, disables some Eigen warnings, and pulls Eigen 5.0.0 via `ExternalProject_Add` (no local patches required). It enables CTest integration and adds `test`, `benchmark`, and `examples` subdirectories (all excluded from default builds unless requested).
- Precision is compile-time selectable through `include/UKF/Config.h` by defining exactly one of `UKF_SINGLE_PRECISION` or `UKF_DOUBLE_PRECISION`. Many targets define `-DEIGEN_NO_MALLOC` to guarantee deterministic stack-only allocations.
- The library is header-only. All public classes live in `include/UKF`:
  * `Types.h` gathers Eigen typedefs and the `real_t` alias.
  * `Integrator.h` provides Euler, Heun, and RK4 integrators.
  * `StateVector.h` composes keyed fields into contiguous Eigen vectors, handles quaternion-specific covariance treatment, and generates sigma points.
  * `MeasurementVector.h` mirrors the state utilities for fixed or dynamic measurement sets, including quaternion/rotation handling and innovation math.
  * `Core.h` implements both standard and square-root UKF variants, including sigma point propagation, innovation, and Kalman gain computation.
  * `Integrator.h`, `MeasurementVector.h`, and `Core.h` rely heavily on templates to avoid runtime allocations and to tailor field dimensions at compile time.

Build targets:
- `test/` declares its own `CMakeLists.txt` which downloads GoogleTest 1.7.0 via `ExternalProject_Add`, builds a `unittest` binary, and hooks it into CTest (`check` target). Tests cover state vectors, fixed/dynamic measurements, the core filter, and square-root formulations. Helper assertions reside in `test/comparisons.h`.
- `benchmark/` uses Google Benchmark v1.3.0 (again via external project) to compare performance of state, measurement, and core operations. `BenchmarkMain.cpp` provides the benchmark entry point.
- `examples/` auto-discovers subdirectories and builds shared libraries:
  * `ahrs/` implements a square-root UKF for an attitude and angular-rate estimator coupled with a parameter estimation filter. It builds `libahrs` and exposes a C API through `ahrs.h`. The accompanying Python package (`examples/ahrs/python/ukf`) loads `libahrs.dylib` via `ctypes` for scripting.
  * `sfwa_ukf/` reproduces the UKF used in the 2014 UAV Challenge. It models a large state vector with wind, biases, and dynamics helpers, exposing an API in `cukf.h` and a similar Python loader.

Additional notes:
- `README.md` gives a high-level introduction, explains how to specialize state/measurement/core classes, and cites reference papers for the algorithms used.
- `LICENSE` is MIT-style, credited to Thiemar Pty Ltd (2016).
- The project assumes Eigen is not already installed; the external project downloads and configures it in the build tree and exposes the include path via `eigen_dir`.
- There is no `src/` directory; all functional code is in headers or example sources, so consumers typically include the headers and link against Eigen only.
- Because Eigen is pulled during configure, offline builds require pruning or mirroring the download, or predefining `eigen_dir` in a parent project to skip the download step.
