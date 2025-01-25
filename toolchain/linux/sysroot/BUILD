load("@bazel_skylib//rules/directory:directory.bzl", "directory")
load("@bazel_skylib//rules/directory:subdirectory.bzl", "subdirectory")

package(default_visibility = ["//visibility:public"])

directory(
    name = "root",
    srcs = glob(["**/*"]),
)

subdirectory(
    name = "usr-include-x86_64-linux-gnu",
    parent = ":root",
    path = "usr/include/x86_64-linux-gnu",
)

subdirectory(
    name = "usr-include",
    parent = ":root",
    path = "usr/include",
)
