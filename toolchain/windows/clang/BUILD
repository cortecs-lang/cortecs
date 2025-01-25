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
    src = "//toolchain/windows/clang/bin:clang.exe",
    data = [
        ":builtin_headers",
    ],
)

cc_tool(
    name = "clang++-tool",
    src = "//toolchain/windows/clang/bin:clang++.exe",
    data = [
        ":builtin_headers",
    ],
)

cc_tool(
    name = "lld-tool",
    src = "//toolchain/windows/clang/bin:clang++.exe",
    data = [
        ":builtin_headers",
        "//toolchain/windows/clang/bin:linker-files",
        "//toolchain/windows/clang/lib/clang/19/lib/x86_64-pc-windows-msvc:extract_lib",
    ],
)

cc_tool(
    name = "llvm-ar-tool",
    src = "//toolchain/windows/clang/bin:llvm-ar.exe",
)

cc_tool(
    name = "llvm-objcopy-tool",
    src = "//toolchain/windows/clang/bin:llvm-objcopy.exe",
)

cc_tool(
    name = "llvm-objdump-tool",
    src = "//toolchain/windows/clang/bin:llvm-objdump.exe",
)

cc_tool(
    name = "llvm-strip-tool",
    src = "//toolchain/windows/clang/bin:llvm-strip.exe",
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
    name = "include-x86_64-pc-windows-msvc-c++-v1",
    parent = ":toolchain_root",
    path = "include/x86_64-pc-windows-msvc/c++/v1",
)

filegroup(
    name = "builtin_headers",
    srcs = [
        ":include-c++-v1",
        ":include-x86_64-pc-windows-msvc-c++-v1",
        ":lib-clang-include",
    ],
)
