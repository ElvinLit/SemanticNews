# C++ Test Suite

This directory contains unit tests for the NewsAggregator project using Qt Test framework.

## Running Tests

### Build the tests:
```bash
cd build
cmake ..
make 
./test_relevance_engine
```

### Run a specific test:
```bash
./test_relevance_engine
```

### Run all tests with ctest:
```bash
ctest
# or with verbose output:
ctest -V
```

## Test Structure

- `test_relevance_engine.cpp` - Tests for RelevanceEngine component

## Adding New Tests

1. Create a new test file: `test_<component>.cpp`
2. Add to `CMakeLists.txt`:
```cmake
add_executable(test_<component>
    src/tests/test_<component>.cpp
    src/<component_path>/<Component>.cpp
)
target_link_libraries(test_<component> Qt6::Core Qt6::Test)
add_test(NAME <Component>Test COMMAND test_<component>)
```

## Test Naming Convention

- Test class: `Test<ComponentName>`
- Test methods: `test<MethodName>_<scenario>()`
- Example: `testComputeMatches_aboveThreshold()`

