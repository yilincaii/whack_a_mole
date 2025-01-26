cmake_minimum_required(VERSION 3.17)
project(Simon)

set(CMAKE_CXX_STANDARD 14)

add_executable(Simon
	main.cpp
	AnimationSprite.cpp
	AnimationSprite.h
	Application.cpp
	Application.h
	)
target_link_libraries(Simon sfml-graphics sfml-audio)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)