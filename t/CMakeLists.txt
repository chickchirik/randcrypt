# CMake configuraton for the subproject is defined here

project(t)

add_executable(
	t
	${t_CPP}
)

# Link external libratires
# target_link_libraries(
# 	t
#	${DEP_LIBS}
#	${Boost_LIBRARIES}
# )

install(TARGETS t RUNTIME DESTINATION ${BIN_DIR})

# include_directories(
#	${INCLUDE_LIST}
# )
