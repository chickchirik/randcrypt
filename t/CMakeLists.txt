# CMake configuraton for the subproject is defined here

project(t)

add_executable(
	t
	${t_CPP}
	${src_CPP}
)

install(TARGETS t RUNTIME DESTINATION ${BIN_DIR})
