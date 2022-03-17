cmake_minimum_required(VERSION 3.0.0)
project(myProject VERSION 0.1.0)

#set(CMAKE_BUILD_TYPE Debug)

# include(CTest)
# enable_testing()

# find_package(MPI REQUIRED) 
# if (MPI_FOUND) 
#     include_directories(SYSTEM ${MPI_INCLUDE_PATH}) 
# else (MPI_FOUND) 
#     message(SEND_ERROR "This application cannot compile without MPI") 
# endif (MPI_FOUND) 

file(GLOB srcfile2 "./LeetCode/*.cpp")
add_executable(LeetCode ${srcfile2})

# file(GLOB srcfile "./DesignMode/*.cpp")
# add_executable(DesignMode ${srcfile})

# file(GLOB srcfile3 "./TestSolution/*.cpp")
# add_executable(TestSolution ${srcfile3})

# add_executable(DealFile "./DealFile.cpp")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
