from miniscons import (
    Build,
    Flag,
    Routine,
    Script,
    Target,
    Tasks,
    conan,
    packages,
    flags,
)
from walkmate import tree

env = conan()

tests = Build(
    "tests",
    [*tree("src", r"\.cpp$"), *tree("test", r"\.cpp$")],
    flags("c++20"),
    packages(["gtest"]),
)

test = Target(
    "test",
    tests,
    ["--gtest_brief"],
)

includes = tests.packages["CPPPATH"]

cspell = Script(
    "cspell",
    ["npx", "cspell", ".", "--dot", "--gitignore"],
)

clang_tidy = Script(
    "clang-tidy",
    ["clang-tidy", tree("src", r"\.(cpp)$"), "--", [f"-I{i}" for i in includes]],
)

trufflehog = Script(
    "trufflehog",
    ["trufflehog3", "-c", ".trufflehog3.yaml"],
)

clang_format = Script(
    "clang-format",
    ["clang-format", "-i", tree(".", r"\.(cpp|hpp|tpp)$")],
)

prettier = Script(
    "prettier",
    ["npx", "prettier", ".", "--write"],
)

doxygen = Script(
    "doxygen",
    ["doxygen", "docs/doxygen/Doxyfile"],
)

breathe = Script(
    "breathe",
    [
        "breathe-apidoc",
        "./docs/doxygen/dist",
        "--output-dir",
        "docs/sphinx/dist",
        "--members",
    ],
)

sphinx = Script(
    "sphinx-build",
    ["sphinx-build", "docs/sphinx", "docs/dist"],
)

lint = Routine(
    "lint",
    [cspell, trufflehog],
)

fmt = Routine(
    "format",
    [clang_format, prettier],
)

docs = Routine(
    "docs",
    [doxygen, breathe, sphinx],
)

cli = Tasks(
    [tests],
    [test],
    [*lint.scripts, *fmt.scripts, *docs.scripts, clang_tidy],
    [lint, fmt, docs],
)

cli.register(env)
