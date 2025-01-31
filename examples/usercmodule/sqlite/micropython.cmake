# Create an INTERFACE library for our C module.
add_library(usermod_sqlite INTERFACE)

# Add our source files to the lib
target_sources(usermod_sqlite INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/usqlite_module.c
    ${CMAKE_CURRENT_LIST_DIR}/usqlite_connection.c
    ${CMAKE_CURRENT_LIST_DIR}/usqlite_cursor.c
    ${CMAKE_CURRENT_LIST_DIR}/usqlite_row.c
    ${CMAKE_CURRENT_LIST_DIR}/usqlite_file.c
    ${CMAKE_CURRENT_LIST_DIR}/usqlite_mem.c
    ${CMAKE_CURRENT_LIST_DIR}/usqlite_vfs.c
    ${CMAKE_CURRENT_LIST_DIR}/usqlite_utils.c
    ${CMAKE_CURRENT_LIST_DIR}/usqlite.c
	${CMAKE_CURRENT_LIST_DIR}/DataBaseInterface.c
	${CMAKE_CURRENT_LIST_DIR}/CircuitPythonDataBaseInterface.c
	${CMAKE_CURRENT_LIST_DIR}/databaseUtils.c
)

#if(IDF_TARGET MATCHES "^esp32^")
#    target_compile_options(usermod_sqlite INTERFACE
#        -mtext-section-literals
#    )
#endif()


# Add the current directory as an include directory.
target_include_directories(usermod_sqlite INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE usermod_sqlite)
