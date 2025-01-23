function(apply_preset_to target)
  # Separate arguments is necessary due to a string passed form the Preset json not usable directly
  # in the target_compile_options command
  separate_arguments(CXX_COMPILE_FLAGS UNIX_COMMAND ${CXX_COMPILE_FLAGS})
  target_compile_options(${target} PRIVATE ${CXX_COMPILE_FLAGS})

  # Use a different standard library
  if(CXX_STDLIB)
    separate_arguments(CXX_STDLIB UNIX_COMMAND ${CXX_STDLIB})
    target_compile_options(${target} PRIVATE ${CXX_STDLIB})
  endif()

  # Activate CLANG-TIDY
  if(CXX_CLANG_TIDY)
    set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY "${CXX_CLANG_TIDY}")
  endif()

  # Activate CPPCHECK
  if(CXX_CPPCHECK)
    set_target_properties(${target} PROPERTIES CXX_CPPCHECK "${CXX_CPPCHECK}")
  endif()

  # Activate INCLUDE WHAT YOU USE
  if(CXX_INCLUDE_WHAT_YOU_USE)
    set_target_properties(${target} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${CXX_INCLUDE_WHAT_YOU_USE})
  endif()

  # Add Sanitizer options (both compile and link)
  if(SANITIZER_FLAGS)
    separate_arguments(SANITIZER_FLAGS UNIX_COMMAND ${SANITIZER_FLAGS})
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS})
    target_link_options(${target} PRIVATE ${SANITIZER_FLAGS})
  endif()

endfunction()
