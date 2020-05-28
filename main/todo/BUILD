load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "todo",
    srcs = ["main.cc"],
    deps = [
        "//:todo",
        "//gateway/controller:cli",
        "//gateway/presenter:text",
        "//infra:file",
    ],
)
