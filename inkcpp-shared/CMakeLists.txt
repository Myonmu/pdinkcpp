add_library(inkcpp_shared INTERFACE)
target_include_directories(inkcpp_shared
	INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
	$<INSTALL_INTERFACE:inkcpp>
)
FILE(GLOB PUBLIC_HEADERS "public/*")
set_target_properties(inkcpp_shared PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

target_link_libraries(inkcpp_shared INTERFACE pdcpp)