load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = ["//src/lib:TrojanMap",
            "//src/lib:NCursesLib", "@ncurses//:main",
	     	"@opencv//:opencv"],
)