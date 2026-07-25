# MessageConstructor

A small header-only library for creating timestamped messages for Arduino serial links and native C++ applications.

## Message format

```text
@#<timestamp>#&field1&field2#@
```

The timestamp is elapsed milliseconds since startup. Reserved characters inside fields are escaped with `\\`:

- `&` becomes `\\&`
- `#` becomes `\\#`
- `\\` becomes `\\\\`

Example:

```cpp
#include <MessageConstructor.h>

MessageConstructor constructor;
String message = constructor.constructMessage("temperature", 25.5, "A&B");
```

A deterministic timestamp can be supplied for tests or externally synchronized protocols:

```cpp
auto message = constructor.constructMessageAt(1000, "status", "ready");
// @#<1000>#&status&ready#@
```

## Arduino installation

Copy this repository into the Arduino libraries directory, install it through PlatformIO, or add it as a Git dependency. The public header is `MessageConstructor.h`.

The example sketch is available under `examples/BasicUsage`.

## Native C++ build and tests

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The native implementation requires C++11 or newer.

## Compatibility notes

- Arduino uses `millis()` as the elapsed timestamp source.
- Native C++ uses `std::chrono::steady_clock` elapsed time.
- `constructMessageAt()` avoids clock differences and is recommended for tests.
- Floating-point values use up to six significant digits in native builds.

## License

Released under CC0 1.0 Universal. See `LICENSE`.
