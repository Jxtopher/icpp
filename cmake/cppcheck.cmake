## > cppcheck ##################################################################
set(CPPCHECK_TO_APPLY     "include/*.h"
                          "apps/*.cpp"  
                          "src/*.cpp" 
                          "src/*.h" 
                          "src/*.hpp" 
                          "test/unit/*.cpp" 
                          "test/unit/*.h" 
                          "test/unit/*.hpp") 

FIND_PROGRAM(CPPCHECK_EXECUTABLE cppcheck)

SET(PROJECT_TRDPARTY_DIR third-party)

add_custom_target(
        cppcheck
        COMMAND ${CPPCHECK_EXECUTABLE} --enable=all  --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}"/cppcheck-suppress" --error-exitcode=1 --quiet --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)" --language=c++  --std=c++20  -I ${CMAKE_CURRENT_SOURCE_DIR}/include/ -I ${CMAKE_CURRENT_BINARY_DIR}/generated/  ${CMAKE_CURRENT_SOURCE_DIR}/src/* ${CMAKE_CURRENT_SOURCE_DIR}/apps
)
## < cppcheck
