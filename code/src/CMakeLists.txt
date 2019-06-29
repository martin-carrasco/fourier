FILE (GLOB_RECURSE algorithms algorithms/*.cpp )
FILE (GLOB_RECURSE applications applications/*.cpp )
FILE (GLOB_RECURSE utility utility/*.cpp )

SET (project_SRCS ${algorithms} ${applications} ${utility})

SET (project_MOC_HEADERS app.h)
# SET (project_LIBS  ${SFMLall_LIBRARIES} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${PYGTK_LIBRARIES} ${GTKMM_LIBRARIES})
SET (project_LIBS  ${SFMLall_LIBRARIES})

SET (bin_audio audio)
SET (bin_image image)
SET (CMAKE_CXX_FLAGS "-g -std=c++17 -Wall -Wfloat-conversion")

ADD_EXECUTABLE(${bin_audio} main_audio.cpp  ${project_SRCS} ${project_MOC_SRCS_GENERATED})
ADD_EXECUTABLE(${bin_image} main_image.cpp  ${project_SRCS} ${project_MOC_SRCS_GENERATED})

TARGET_LINK_LIBRARIES(${bin_audio} ${project_LIBS})
TARGET_LINK_LIBRARIES(${bin_image} ${project_LIBS})

MESSAGE(${bin_audio})
MESSAGE(${bin_image})

SET_TARGET_PROPERTIES(${bin_audio} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${bin_audio} CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(${bin_image} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${bin_image} CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${bin_audio} DESTINATION bin)
INSTALL(TARGETS ${bin_image} DESTINATION bin)
