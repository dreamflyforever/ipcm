IPCM (Inter-Process Communication by mqtt protocol)
==========

[中文页](README_zh.md)  
[![Build Status](https://secure.travis-ci.org/php/php-src.png?branch=master)](https://travis-ci.org/dreamflyforever/ipcm)

The project build indepent module process communicated by new method, one process subscribes to topics, the other  
publishes the message through the same topics, and it supports function one to many, and  many to one, it's very
convenience to integration.

## feature (rk3399 soc platform)
bandwidth: 51MB/s, if use unix socket, it may fast more  
suport binary and text message  
suport process number : 256   
suport topics number : 256  
suport funciton : one to many, many to one (process)  
ram: 129kB  
cpu: 11%  

## example
check the `client/example.c`  
Receive message by callback function, it friendly for the developer.

## compile & run
'scons' : libipcm.so, ipcm_client & ipcm_server  
export LD_LIBRARY_PATH=LD_LIBRARY_PATH:.

## license
MIT by Jim

<img src="https://github.com/dreamflyforever/ipcm/blob/master/logo.jpeg" width="100px">
