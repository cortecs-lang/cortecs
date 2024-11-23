#!/bin/bash

bazel clean
rm compile_commands.json

# verify file formatting
find source/ -iname '*.h' -o -iname '*.c' -exec clang-format --dry-run --Werror {} \;

# build compile_commands.json
CC=clang bazel build //...
CC=clang bazel run @hedron_compile_commands//:refresh_all

# run linter
find source/ -type f -iname '*.c' ! -iname '*.template.c' -exec clang-tidy --config-file ./source/.clang-tidy -p ./ {} \;

# run code coverate
CC=gcc bazel coverage --instrumentation_filter //source/... --noinstrument_test_targets --combined_report=lcov //source/...
genhtml --branch-coverage --output genhtml "$(bazel info output_path)/_coverage/_coverage_report.dat"