load("@rules_cc//cc/toolchains:args.bzl", "cc_args")
load("@rules_cc//cc/toolchains/args:sysroot.bzl", "cc_sysroot")

cc_sysroot(
    name = "linux_sysroot",
    data = [
        "//toolchain/linux/sysroot:root",
        "//toolchain/linux/sysroot:usr-include",
        "//toolchain/linux/sysroot:usr-include-x86_64-linux-gnu",
    ],
    sysroot = "//toolchain/linux/sysroot:root",
    visibility = ["//visibility:public"],
)

cc_args(
    name = "no_canonical_prefixes",
    actions = [
        "@rules_cc//cc/toolchains/actions:c_compile",
        "@rules_cc//cc/toolchains/actions:cpp_compile_actions",
    ],
    args = ["-no-canonical-prefixes"],
    visibility = ["//visibility:public"],
)

cc_args(
    name = "isystem",
    actions = [
        "@rules_cc//cc/toolchains/actions:c_compile",
        "@rules_cc//cc/toolchains/actions:cpp_compile_actions",
    ],
    args = [
        "-isystem",
        "toolchain/linux/clang/include/c++/v1",
        "-isystem",
        "toolchain/linux/clang/include/x86_64-unknown-linux-gnu/c++/v1",
        "-isystem",
        "toolchain/linux/clang/include",
        "-isystem",
        "toolchain/linux/clang/lib/clang/19/include",
    ],
    visibility = ["//visibility:public"],
)
