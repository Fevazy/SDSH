add_executable(test_smoke smoke.c)
target_link_libraries(test_smoke PRIVATE sdsh)
add_test(
    NAME smoke_test
    COMMAND test_smoke
)
