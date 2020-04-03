# CMake configuraton for the subproject is defined here

project(SUBPROJECT)

add_executable(
	SUBPROJECT
	${SUBPROJECT_CPP}
)

# Link external libratires
# target_link_libraries(
# 	SUBPROJECT
#	${DEP_LIBS}
#	${Boost_LIBRARIES}
# )

install(TARGETS SUBPROJECT RUNTIME DESTINATION ${BIN_DIR})

# include_directories(
#	${INCLUDE_LIST}
# )
