set_target_properties(Genus PROPERTIES
        OUTPUT_NAME index
        SUFFIX ".html"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/html"
)

set(web_shell "${CMAKE_CURRENT_LIST_DIR}/web-shell.html")
set_property(TARGET Genus APPEND PROPERTY LINK_DEPENDS "${web_shell}")
target_link_options(Genus PRIVATE -sALLOW_MEMORY_GROWTH
        --shell-file "${web_shell}")

add_custom_target(run-web
        COMMAND Python3::Interpreter "${PROJECT_SOURCE_DIR}/scripts/preview-web.py"
                "$<TARGET_FILE_DIR:Genus>"
        DEPENDS Genus
        USES_TERMINAL
        VERBATIM
)
