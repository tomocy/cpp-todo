load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

new_git_repository(
    name = "bcrypt",
    build_file = "@//:BUILD",
    commit = "f80c71730374cb29c4fa606bbc04d1cc96654ba3",
    remote = "https://github.com/trusch/libbcrypt",
)

http_archive(
    name = "gtest",
    sha256 = "927827c183d01734cc5cfef85e0ff3f5a92ffe6188e0d18e909c5efebf28a0c7",
    strip_prefix = "googletest-release-1.8.1",
    url = "https://github.com/google/googletest/archive/release-1.8.1.zip",
)
