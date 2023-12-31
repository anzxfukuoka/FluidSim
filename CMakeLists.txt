
cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(FluidSimulation)

# Add all Source Files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add all Header Files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})


# Find the Required Packages (if Any -> OpenGL/Vulkan or Any)
find_package(OpenGL REQUIRED)

# Variable for the Libs to add to the Linkers
set(LIBS glfw opengl32 glad glm) #assimp

# Variables for Paths of External Libraries
set(GLFW_ROOT_DIR external/glfw)
set(GLAD_ROOT_DIR external/glad)
set(GLM_ROOT_DIR external/glm) # opengl math lib
#set(ASSIMP_ROOT_DIR external/assimp) # model importer lib

# Add the External Libraries / Files Directory
add_subdirectory(${GLFW_ROOT_DIR})
add_subdirectory(${GLAD_ROOT_DIR})
add_subdirectory(${GLM_ROOT_DIR})
#add_subdirectory(${ASSIMP_ROOT_DIR})

# Add the Include Directories for the Libraries / Files
#Used for adding #include into the cpp files

#		Include Files From Within the Workspace Folder

target_include_directories(${PROJECT_NAME} 
	PUBLIC ${GLFW_ROOT_DIR}/include
	PUBLIC ${GLAD_ROOT_DIR}/include/glad
	PUBLIC ${GLM_ROOT_DIR}/glm
#	PUBLIC ${ASSIMP_ROOT_DIR}/include/assimp
)

# Add a custom target for resource copying
add_custom_target(CopyResources
    COMMAND ${CMAKE_COMMAND} -E remove_directory
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    COMMENT "Copying resources directory"
)

# Make the main target dependent on the custom target
add_dependencies(${PROJECT_NAME} CopyResources)



#		Include Files from Outside the Workspace Folder -> Like Vulkan SDK

#target_include_directories(${PROJECT_NAME}
#	PRIVATE ${Vulkan_INCLUDE_DIRS}
#)

# Add the Link Directories for the Libraries / Files
#Used for creation of Static/Dynamic Libraries

#		Include Files From Within the Workspace Folder

target_link_directories(${PROJECT_NAME} 
	PRIVATE ${GLFW_ROOT_DIR}/src
	PRIVATE ${GLAD_ROOT_DIR}/src
	PRIVATE ${GLM_ROOT_DIR}/src
#	PRIVATE ${ASSIMP_ROOT_DIR}
	
)

# Add the Libs to the Linker for the Project

target_link_libraries(${PROJECT_NAME} ${LIBS})

# EXPLANATION FOR SOME STUFF

# GLOB_RECURSE -> Recursively go through all subdirectories
#		of the given path and get all the files matching the extension provided
# file() -> Store the Files matching the RegEx into a variable
# set() -> Alternative to file() if you want to set variables for a custom behaviour

# POST BUILD

# Resources dir copy
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    DEPENDS CopyResources
    COMMENT "Triggering post-build command"
)

# resources dir copy
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#	# update resources directory
#	COMMAND ${CMAKE_COMMAND} -E remove_directory
#    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${CMAKE_SOURCE_DIR}/resources
#    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
#)






