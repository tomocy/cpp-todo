load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "todo",
    srcs = ["todo.cc"],
    hdrs = ["todo.h"],
    visibility = [
        "//gateway/controller:__pkg__",
        "//gateway/presenter:__pkg__",
        "//infra:__pkg__",
        "//main/todo:__pkg__",
        "//usecase:__pkg__",
    ],
)
