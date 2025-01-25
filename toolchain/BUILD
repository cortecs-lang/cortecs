load("@rules_cc//cc/toolchains:toolchain.bzl", "cc_toolchain")

# currently just pulling toolchain artifacts from:
# * https://chrome-infra-packages.appspot.com/p/fuchsia/third_party/clang
# * https://chrome-infra-packages.appspot.com/p/fuchsia/third_party/sysroot

cc_toolchain(
    name = "host_clang",
    args = [
        #"//toolchain/args:linux_sysroot",
        "//toolchain/args:no_canonical_prefixes",
        "//toolchain/args:isystem",
    ],
    enabled_features = ["@rules_cc//cc/toolchains/args:experimental_replace_legacy_action_config_features"],
    known_features = ["@rules_cc//cc/toolchains/args:experimental_replace_legacy_action_config_features"],
    tool_map = "//toolchain/linux/clang:all_tools",
)

toolchain(
    name = "host_cc_toolchain",
    toolchain = ":host_clang",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)
