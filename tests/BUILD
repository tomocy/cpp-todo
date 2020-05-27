load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "tests",
    srcs = ["usecase_test.cc"],
    deps = [
        "//infra:memory",
        "//usecase",
        "@gtest//:gtest_main",
    ],
)
