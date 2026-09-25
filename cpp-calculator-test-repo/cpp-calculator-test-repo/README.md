# C++ Calculator Test Repo

A deliberately small C++ repository for testing Jenkins/static code analysis.

## Build

### Windows
```bat
build.bat
```

### Linux/macOS
```bash
./build.sh
```

The executable is created in `build/`.

## Run

```text
calculator 10 + 5
calculator 10 - 5
calculator 10 * 5
calculator 10 / 5
```

The code is intentionally simple so it can be used as a test project for
Jenkins, compiler warnings, and static-analysis tools such as clang-tidy.
