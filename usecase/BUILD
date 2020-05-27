load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "usecase",
    srcs = ["usecase.cc"],
    hdrs = ["usecase.h"],
    visibility = [
        "//gateway/controller:__pkg__",
        "//tests:__pkg__",
    ],
    deps = [
        "//:todo",
    ],
)
