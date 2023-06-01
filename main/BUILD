

cc_library(
	name =  "graph",
	hdrs = ["graph.hpp"],
)

cc_binary(
	name = "test",
	srcs = ["test.cpp,tests.cpp"],
    deps = [":graph"]
)

cc_binary(
    name = "tests",
    srcs = ["tests.cpp"],
    deps = [":graph","@com_google_googletest//:gtest_main"]
)