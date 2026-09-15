cmake_minimum_required(VERSION 3.10)

project(MiniLogger)

add_executable(MiniLogger
    MiniLogger.cpp
    Main.cpp
    MiniLogger.h
    LogSink.h
    ConsoleSink.h
    FileSink.h
)

set_property(TARGET MiniLogger PROPERTY CXX_STANDARD 20)