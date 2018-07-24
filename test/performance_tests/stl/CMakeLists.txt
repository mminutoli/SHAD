set(tests
#  iterator_perf
#  for_perf
#  algorithm_perf
  numeric_perf
)

foreach(t ${tests})
  set(CMAKE_CXX_STANDARD 17)
  add_executable(${t} ${t}.cc)
  if (CLANG_TIDY_EXE)
    set_target_properties(
      ${t} PROPERTIES
      CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
  endif()
  target_link_libraries(${t} ${SHAD_RUNTIME_LIB} runtime shadperf_main ${benchmark_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endforeach(t)
