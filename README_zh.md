IPCM (Inter-Process Communication by mqtt protocol)
==========
[![Build Status](https://secure.travis-ci.org/php/php-src.png?branch=master)](https://travis-ci.org/dreamflyforever/ipcm)

IPCM 是一种高效并发的处理各个进程之间或是进程内部信息发送接受的一套软件框架，用户可以很方便的使用API进行代码集成测试，快速用于工程。

## 工作原理
把信息流看作总线，所有的数据都共享在总线上，数据会包含主题，只有subscribe订阅该主题的进程才可以收到信息，同理，发送数据也是具备主题身份才可以发送数据。这样就可以实现数据的分发，一对一，一对多，多对一都是可以的。

## 特性
带宽：51MB/s（跟硬件平台相关）  
支持二进制和文本格式的数据流  
支持256个接收者和发送者，主题  
内存占用129KB  
cpu占用 11% （rk3399，4核1.3GB，2核1.8GB）

## 例子
查看`client/example.c`, 接受数据采用回调的方式，方便用户使用。

## 编译
代码采用construct构建，直接`scons`，如未安装scons，请'apt install scons' 进行安装

## license
MIT by Jim

<img src="https://github.com/dreamflyforever/ipcm/blob/master/logo.jpeg" width="100px">
