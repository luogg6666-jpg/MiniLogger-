# MiniLogger

一个简单的 C++ 日志输出工具。

本项目实现了基础的日志输出功能，并通过生产者与消费者的思想实现多线程环境下的日志处理，用于学习和实践 C++ 中的多线程、线程同步以及日志系统设计。

## 项目特点

* 支持基础日志输出
* 支持控制台和文件输出
* 基于生产者-消费者模型进行设计
* 支持多线程环境下的日志操作
* 使用 CMake 构建项目
* 用于练习 C++ 多线程与工程化开发

## 项目结构

```text
MiniLogger/
├── CMakeLists.txt
├── CMakePresets.json
├── MiniLogger.h
├── MiniLogger.cpp
├── LogSink.h
├── ConsoleSink.h
├── FileSink.h
└── Main.cpp
```

## 主要技术

* C++
* CMake
* STL
* 多线程
* `std::thread`
* `std::mutex`
* 生产者-消费者模型

## 项目目的

本项目主要用于学习 C++ 日志系统的基本实现，以及多线程、线程同步、文件 I/O 和简单工程化开发。
