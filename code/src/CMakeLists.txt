FILE (GLOB_RECURSE algorithms algorithms/*.cpp )
FILE (GLOB_RECURSE applications applications/*.cpp )
FILE (GLOB_RECURSE utility utility/*.cpp )
FILE (GLOB_RECURSE main_files main/*.cpp )

SET (project_SRCS ${algorithms} ${applications} ${utility})

SET (project_MOC_HEADERS app.h)

# SET (project_LIBS  ${SFMLall_LIBRARIES} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${PYGTK_LIBRARIES} ${GTKMM_LIBRARIES} ${OpenCV_LIBRARIES})

SET (project_LIBS  ${SFMLall_LIBRARIES} ${PYTHON_LIBRARIES} ${OpenCV_LIBRARIES} -lstdc++fs)
# SET (project_LIBS  ${SFMLall_LIBRARIES}  ${OpenCV_LIBRARIES})

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wfloat-conversion")

MESSAGE("ALL MAIN FILES: ${main_files}")

foreach(main ${main_files})
    STRING( REPLACE ".cpp" "" path_no_extension ${main} )
    GET_FILENAME_COMPONENT(basename ${path_no_extension} NAME)
    ADD_EXECUTABLE(${basename} ${main} ${project_SRCS} ${project_MOC_SRCS_GENERATED})
    TARGET_LINK_LIBRARIES(${basename} ${project_LIBS})
    SET_TARGET_PROPERTIES(${basename} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${basename} CLEAN_DIRECT_OUTPUT 1)
    INSTALL(TARGETS ${basename} DESTINATION bin)
endforeach()
