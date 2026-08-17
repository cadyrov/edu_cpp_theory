add_test([=[GameTest.GameName]=]  /Users/kot/Documents/repos/edu_cpp_theory/projects/1/labirinth/build/labirinth_tests [==[--gtest_filter=GameTest.GameName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GameTest.GameName]=]  PROPERTIES WORKING_DIRECTORY /Users/kot/Documents/repos/edu_cpp_theory/projects/1/labirinth/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  labirinth_tests_TESTS GameTest.GameName)
