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
    src = ":bin/clang",
    data = [
        ":bin/llvm",
        ":builtin_headers",
    ],
)

cc_tool(
    name = "clang++-tool",
    src = ":bin/clang++",
    data = [
        ":bin/llvm",
        ":builtin_headers",
    ],
)

cc_tool(
    name = "lld-tool",
    src = ":bin/clang++",
    data = [
        ":bin/llvm",
        ":builtin_headers",
        ":linker-files",
        "//toolchain/linux/clang/lib/clang/19/lib/x86_64-unknown-linux-gnu:extract_lib",
    ],
)

cc_tool(
    name = "llvm-ar-tool",
    src = ":bin/llvm-ar",
    data = [":bin/llvm"],
)

cc_tool(
    name = "llvm-objcopy-tool",
    src = ":bin/llvm-objcopy",
    data = [":bin/llvm"],
)

cc_tool(
    name = "llvm-objdump-tool",
    src = ":bin/llvm-objdump",
    data = [":bin/llvm"],
)

cc_tool(
    name = "llvm-strip-tool",
    src = ":bin/llvm-strip",
    data = [":bin/llvm"],
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

genrule(
    name = "link_clang",
    srcs = [
        ":bin/llvm",
        ":builtin_headers",
    ],
    outs = ["bin/clang"],
    cmd = "ln -s llvm $(@D)/clang",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_clang++",
    srcs = [
        ":bin/llvm",
        ":builtin_headers",
    ],
    outs = ["bin/clang++"],
    cmd = "ln -s llvm $(@D)/clang++",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_ld_lld",
    srcs = [":bin/llvm"],
    outs = ["bin/ld.lld"],
    cmd = "ln -s llvm $(@D)/ld.lld",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_ld64_lld",
    srcs = [":bin/llvm"],
    outs = ["bin/ld64.lld"],
    cmd = "ln -s llvm $(@D)/ld64.lld",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_lld",
    srcs = [":bin/llvm"],
    outs = ["bin/lld"],
    cmd = "ln -s llvm $(@D)/lld",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_lld-link",
    srcs = [":bin/llvm"],
    outs = ["bin/lld-link"],
    cmd = "ln -s llvm $(@D)/lld-link",
    tags = ["no-remote-cache"],
)

filegroup(
    name = "linker-files",
    srcs = [
        ":bin/ld.lld",
        ":bin/ld64.lld",
        ":bin/lld",
        ":bin/lld-link",
    ],
)

genrule(
    name = "link_llvm-ar",
    srcs = [":bin/llvm"],
    outs = ["bin/llvm-ar"],
    cmd = "ln -s llvm $(@D)/llvm-ar",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_llvm-objcopy",
    srcs = [":bin/llvm"],
    outs = ["bin/llvm-objcopy"],
    cmd = "ln -s llvm $(@D)/llvm-objcopy",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_llvm-objdump",
    srcs = [":bin/llvm"],
    outs = ["bin/llvm-objdump"],
    cmd = "ln -s llvm $(@D)/llvm-objdump",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_llvm-strip",
    srcs = [":bin/llvm"],
    outs = ["bin/llvm-strip"],
    cmd = "ln -s llvm $(@D)/llvm-strip",
    tags = ["no-remote-cache"],
)

# this distribution of clang is just a bunch of symlinks to the llvm binary
# but you need to keep the symlinks because llvm uses the name of the binary
# to decide what to do.

# To avoid using git lfs, we tar up the llvm binary.
# Github has incredibly low bandwidth limits for lfs before you have to start paying for it,
# but there's no bandwith limits for normal checkout.
genrule(
    name = "extract_llvm",
    srcs = ["bin/llvm.tar.gz"],
    outs = ["bin/llvm"],
    cmd = "tar xf $(location bin/llvm.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)
