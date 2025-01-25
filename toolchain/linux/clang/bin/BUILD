package(default_visibility = ["//visibility:public"])

# this distribution of clang is just a bunch of symlinks to the llvm binary
# but you need to keep the symlinks because llvm uses the name of the binary
# to decide what to do.

# To avoid using git lfs, we compress the llvm binary.
# Github has incredibly low bandwidth limits for lfs before you have to start paying for it,
# but there's no bandwith limits for normal checkout.
genrule(
    name = "extract_llvm",
    srcs = ["llvm.tar.gz"],
    outs = ["llvm"],
    cmd = "tar xf $(location llvm.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_clang",
    srcs = [":llvm"],
    outs = ["clang"],
    cmd = "ln -s llvm $(@D)/clang",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_clang++",
    srcs = [":llvm"],
    outs = ["clang++"],
    cmd = "ln -s llvm $(@D)/clang++",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_ld_lld",
    srcs = [":llvm"],
    outs = ["ld.lld"],
    cmd = "ln -s llvm $(@D)/ld.lld",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_ld64_lld",
    srcs = [":llvm"],
    outs = ["ld64.lld"],
    cmd = "ln -s llvm $(@D)/ld64.lld",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_lld",
    srcs = [":llvm"],
    outs = ["lld"],
    cmd = "ln -s llvm $(@D)/lld",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_lld-link",
    srcs = [":llvm"],
    outs = ["lld-link"],
    cmd = "ln -s llvm $(@D)/lld-link",
    tags = ["no-remote-cache"],
)

filegroup(
    name = "linker-files",
    srcs = [
        ":ld.lld",
        ":ld64.lld",
        ":lld",
        ":lld-link",
    ],
)

genrule(
    name = "link_llvm-ar",
    srcs = [":llvm"],
    outs = ["llvm-ar"],
    cmd = "ln -s llvm $(@D)/llvm-ar",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_llvm-objcopy",
    srcs = [":llvm"],
    outs = ["llvm-objcopy"],
    cmd = "ln -s llvm $(@D)/llvm-objcopy",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_llvm-objdump",
    srcs = [":llvm"],
    outs = ["llvm-objdump"],
    cmd = "ln -s llvm $(@D)/llvm-objdump",
    tags = ["no-remote-cache"],
)

genrule(
    name = "link_llvm-strip",
    srcs = [":llvm"],
    outs = ["llvm-strip"],
    cmd = "ln -s llvm $(@D)/llvm-strip",
    tags = ["no-remote-cache"],
)
