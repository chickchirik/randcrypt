# CMake configuraton for the subproject is defined here

project(t)

add_executable(
	t
	${t_CPP}
	${src_CPP}
)

target_link_libraries(t ${CONAN_LIBS})

install(TARGETS t RUNTIME DESTINATION ${BIN_DIR})
