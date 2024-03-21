cmake_minimum_required(VERSION 3.5)

# Set the project name
project (demo1)

set(CLIENT
    client/client.c
)

set(SERVER
    server/server.c
)

# Add an executable
add_executable(server ${SERVER})
add_executable(client ${CLIENT})

