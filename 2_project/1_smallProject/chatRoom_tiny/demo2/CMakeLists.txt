cmake_minimum_required(VERSION 3.5)

# Set the project name
project (demo2)

set(CLIENT
    client/src/client.c
    client/src/myFunction.c
    client/src/myUI.c
)

set(SERVER
    server/src/server.c
    server/src/mySocket.c
    server/src/mySQL.c
    server/src/myUI.c
)

# Add an executable
link_libraries(sqlite3)

add_executable(server ${SERVER})
add_executable(client ${CLIENT})

target_include_directories(client 
    PRIVATE
        ${PROJECT_SOURCE_DIR}/client/include
)

target_include_directories(server 
    PRIVATE
        ${PROJECT_SOURCE_DIR}/server/include
)


