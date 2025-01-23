include(FetchContent)

function(loadextlib_git _libraryName _gitRepo _gitTag)
  string(TOLOWER ${_libraryName} libName)
  
  set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/ext_libs/${libName})
  set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
  set(FETCHCONTENT_QUIET ON)

  FetchContent_Declare(
      ${libName}
      GIT_REPOSITORY ${_gitRepo}
      GIT_TAG ${_gitTag}
  )
  
  FetchContent_MakeAvailable(${libName})
endfunction()


function(load_gtest)
  set(libName "googletest")
  
  loadextlib_git(${libName} 
                "https://github.com/google/googletest.git" 
                "release-1.12.1")
endFunction()