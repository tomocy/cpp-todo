load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "rand",
    srcs = ["rand.cc"],
    hdrs = ["rand.h"],
)

cc_library(
    name = "memory",
    srcs = ["memory.cc"],
    hdrs = ["memory.h"],
    visibility = [
        "//main/todo:__pkg__",
        "//tests:__pkg__",
    ],
    deps = [
        ":rand",
        "//:todo",
        "//gateway/controller:cli",
    ],
)

cc_library(
    name = "file",
    srcs = ["file.cc"],
    hdrs = ["file.h"],
    visibility = [
        "//main/todo:__pkg__",
    ],
    deps = [
        ":rand",
        "//:todo",
        "//gateway/controller:cli",
        "@json",
    ],
)
