load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "gtest",
    sha256 = "53de8c75150430c217550ec6bb413029300120407f2de02ea8e20e89675f5e94",
    strip_prefix = "googletest-912db742531bf82efb01194bc08140416e3b3467",
    urls = [
        "https://github.com/google/googletest/archive/912db742531bf82efb01194bc08140416e3b3467.tar.gz",
    ],
)

http_archive(
    name = "benchmark",
    sha256 = "aeec52381284ec3752505a220d36096954c869da4573c2e1df3642d2f0a4aac6",
    strip_prefix = "benchmark-1.7.1",
    url = "https://github.com/google/benchmark/archive/refs/tags/v1.7.1.zip",
)

# Boost
# Famous C++ library that has given rise to many new additions to the C++ Standard Library
# Makes @boost available for use: For example, add `@boost//:algorithm` to your deps.
# For more, see https://github.com/nelhage/rules_boost and https://www.boost.org
http_archive(
    name = "com_github_nelhage_rules_boost",
    strip_prefix = "rules_boost-d5d2549b6cfe8946d133831f99746b1e9f595abf",

    # Replace the commit hash in both places (below) with the latest, rather than using the stale one here.
    # Even better, set up Renovate and let it do the work for you (see "Suggestion: Updates" in the README).
    url = "https://github.com/nelhage/rules_boost/archive/d5d2549b6cfe8946d133831f99746b1e9f595abf.tar.gz",
    # When you first run this tool, it'll recommend a sha256 hash to put here with a message like: "DEBUG: Rule 'com_github_nelhage_rules_boost' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = ..."
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")

boost_deps()
