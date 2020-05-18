load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "controller",
    srcs = ["controller.cc"],
    hdrs = ["controller.h"],
    visibility = [
        "//gateway/presenter:__pkg__",
    ],
    deps = [
        "//:todo",
    ],
)

cc_library(
    name = "cli",
    srcs = ["cli.cc"],
    hdrs = ["cli.h"],
    visibility = [
        "//main/todo:__pkg__",
    ],
    deps = [
        ":controller",
    ],
)
