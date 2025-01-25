load("@bazel_skylib//rules/directory:directory.bzl", "directory")
load("@bazel_skylib//rules/directory:subdirectory.bzl", "subdirectory")
load("@rules_cc//cc/toolchains:tool.bzl", "cc_tool")
load("@rules_cc//cc/toolchains:tool_map.bzl", "cc_tool_map")

package(default_visibility = ["//visibility:public"])

# quickly writing down some things before I forget. I need to go back and better document all this
# I had to move libc++.a and libunwind.a from clang to sysroot
# toolchain/linux/clang/lib/clang/19/lib/x86_64-unknown-linux-gnu/BUILD is because llvm looks relative to
# itself for those files.
# taring up llvm is to get the file size down
cc_tool_map(
    name = "all_tools",
    tools = {
        "@rules_cc//cc/toolchains/actions:ar_actions": ":llvm-ar-tool",
        "@rules_cc//cc/toolchains/actions:assembly_actions": ":clang++-tool",
        "@rules_cc//cc/toolchains/actions:c_compile": ":clang-tool",
        "@rules_cc//cc/toolchains/actions:cpp_compile_actions": ":clang++-tool",
        "@rules_cc//cc/toolchains/actions:link_actions": ":lld-tool",
        "@rules_cc//cc/toolchains/actions:objcopy_embed_data": ":llvm-objcopy-tool",
        "@rules_cc//cc/toolchains/actions:strip": ":llvm-strip-tool",
    },
)

cc_tool(
    name = "clang-tool",
    src = "//toolchain/linux/clang/bin:clang",
    data = [
        ":builtin_headers",
        "//toolchain/linux/clang/bin:llvm",
    ],
)

cc_tool(
    name = "clang++-tool",
    src = "//toolchain/linux/clang/bin:clang++",
    data = [
        ":builtin_headers",
        "//toolchain/linux/clang/bin:llvm",
    ],
)

cc_tool(
    name = "lld-tool",
    src = "//toolchain/linux/clang/bin:clang++",
    data = [
        ":builtin_headers",
        "//toolchain/linux/clang/bin:linker-files",
        "//toolchain/linux/clang/bin:llvm",
        "//toolchain/linux/clang/lib/clang/19/lib/x86_64-unknown-linux-gnu:extract_lib",
    ],
)

cc_tool(
    name = "llvm-ar-tool",
    src = "//toolchain/linux/clang/bin:llvm-ar",
    data = ["//toolchain/linux/clang/bin:llvm"],
)

cc_tool(
    name = "llvm-objcopy-tool",
    src = "//toolchain/linux/clang/bin:llvm-objcopy",
    data = ["//toolchain/linux/clang/bin:llvm"],
)

cc_tool(
    name = "llvm-objdump-tool",
    src = "//toolchain/linux/clang/bin:llvm-objdump",
    data = ["//toolchain/linux/clang/bin:llvm"],
)

cc_tool(
    name = "llvm-strip-tool",
    src = "//toolchain/linux/clang/bin:llvm-strip",
    data = ["//toolchain/linux/clang/bin:llvm"],
)

# Directory-based rules in this toolchain only referece things in
# lib/ or include/ subdirectories.
directory(
    name = "toolchain_root",
    srcs = glob([
        "lib/**",
        "include/**",
    ]),
)

subdirectory(
    name = "include-c++-v1",
    parent = ":toolchain_root",
    path = "include/c++/v1",
)

subdirectory(
    name = "lib-clang-include",
    parent = ":toolchain_root",
    path = "lib/clang/19/include",
)

subdirectory(
    name = "include-x86_64-unknown-linux-gnu-c++-v1",
    parent = ":toolchain_root",
    path = "include/x86_64-unknown-linux-gnu/c++/v1",
)

filegroup(
    name = "builtin_headers",
    srcs = [
        ":include-c++-v1",
        ":include-x86_64-unknown-linux-gnu-c++-v1",
        ":lib-clang-include",
    ],
)
