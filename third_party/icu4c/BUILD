load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

filegroup(
    name = "all_files",
    srcs = glob([
        "**",
    ]),
)

configure_make(
    name = "icu",
    configure_command = "icu4c/source/configure",
    configure_options = ["--enable-static", "--disable-shared"],
    lib_source = ":all_files",
    out_static_libs = ["libicudata.a", "libicui18n.a", "libicuio.a", "libicutest.a", "libicutu.a", "libicuuc.a"],
    out_shared_libs = [], #"libicudata.so", "libicui18n.so", "libicuio.so", "libicutest.so", "libicutu.so", "libicuuc.so"
    visibility = ["//visibility:public"],
)
