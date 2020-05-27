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
    deps = [
        "@bcrypt",
    ],
)

cc_library(
    name = "bcrypt",
    srcs = glob(["src/**"]),
    hdrs = glob(["include/bcrypt/**"]),
    includes = [
        "include",
        "include/bcrypt",
    ],
    visibility = [
        "@//:__pkg__",
    ],
)

cc_library(
    name = "json",
    hdrs = ["single_include/nlohmann/json.hpp"],
    visibility = [
        "@//infra:__pkg__",
    ],
)
