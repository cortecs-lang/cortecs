package(default_visibility = ["//visibility:public"])

# To avoid using git lfs, we compress the clang binaries.
# Github has incredibly low bandwidth limits for lfs before you have to start paying for it,
# but there's no bandwith limits for normal checkout.
genrule(
    name = "extract_clang_exe",
    srcs = ["clang.exe.tar.gz"],
    outs = ["clang.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location clang.exe.tar.gz); echo $(@D); tar.exe xvf $(location clang.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

genrule(
    name = "extract_clang++_exe",
    srcs = ["clang++.exe.tar.gz"],
    outs = ["clang++.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location clang++.exe.tar.gz); echo $(@D); tar.exe xvf $(location clang++.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

filegroup(
    name = "linker-files",
    srcs = [
        ":ld.lld.exe",
        ":ld64.lld.exe",
        ":lld.exe",
        ":lld-link.exe",
    ],
)

genrule(
    name = "extract_ld_lld_exe",
    srcs = ["ld.lld.exe.tar.gz"],
    outs = ["ld.lld.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location ld.lld.exe.tar.gz); echo $(@D); tar.exe xvf $(location ld.lld.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

genrule(
    name = "extract_ld64_lld_exe",
    srcs = ["ld64.lld.exe.tar.gz"],
    outs = ["ld64.lld.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location ld64.lld.exe.tar.gz); echo $(@D); tar.exe xvf $(location ld64.lld.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

genrule(
    name = "extract_lld-link_exe",
    srcs = ["lld-link.exe.tar.gz"],
    outs = ["lld-link.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location lld-link.exe.tar.gz); echo $(@D); tar.exe xvf $(location lld-link.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

genrule(
    name = "extract_lld_exe",
    srcs = ["lld.exe.tar.gz"],
    outs = ["lld.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location lld.exe.tar.gz); echo $(@D); tar.exe xvf $(location lld.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

genrule(
    name = "extract_llvm-ar_exe",
    srcs = ["llvm-ar.exe.tar.gz"],
    outs = ["llvm-ar.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location llvm-ar.exe.tar.gz); echo $(@D); tar.exe xvf $(location llvm-ar.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

genrule(
    name = "extract_llvm-objcopy_exe",
    srcs = ["llvm-objcopy.exe.tar.gz"],
    outs = ["llvm-objcopy.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location llvm-objcopy.exe.tar.gz); echo $(@D); tar.exe xvf $(location llvm-objcopy.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

genrule(
    name = "extract_llvm-objdump_exe",
    srcs = ["llvm-objdump.exe.tar.gz"],
    outs = ["llvm-objdump.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location llvm-objdump.exe.tar.gz); echo $(@D); tar.exe xvf $(location llvm-objdump.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)

genrule(
    name = "extract_llvm-strip_exe",
    srcs = ["llvm-strip.exe.tar.gz"],
    outs = ["llvm-strip.exe"],
    cmd_ps = "echo helloworld; tar.exe --help; echo helloworld; echo $(location llvm-strip.exe.tar.gz); echo $(@D); tar.exe xvf $(location llvm-strip.exe.tar.gz) -C $(@D)",
    tags = ["no-remote-cache"],
)
