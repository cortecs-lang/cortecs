cc_library(
    name = "json",
    srcs = glob(["*.c"]),
    hdrs = glob(["public-headers/cortecs/*.h"]),
    features = ["treat_warnings_as_errors"],
    includes = ["public-headers/"],
    visibility = ["//visibility:public"],
    deps = [
        "//source/cortecs/gc",
        "//source/cortecs/string",
        "//source/cortecs/types",
    ],
)
