# hue-api
A complete c++ api for hue products

This project is very much in development so this readme will be frequently updated
as features are added. The intention is to have a functional and easy to use c++ interface
for hue products, with some possible added functionality.  Below are some of the implemented features and the todo list:

## Features:

  - [X] JSON Configuration file which can populate and save off up settings.  Could be used
    for lighting settings as well

  - [X] Get and Post and Put methods implemented

  - [X] Auto-connect, hub IP retrieval and authentication (Testing in progress)

  - [X] Local name and descriptions for lights.

  - [ ] Add validation checks for value ranges (https://devblogs.microsoft.com/oldnewthing/20151013-00/?p=91371)

  - [ ] Re-factor simple names and give good descriptions

  - [ ] Modify String Utility to detect floating point.

  - [ ] Interface for command wrapper

  - [ ] ncurses debug console

  - [ ] web api

  - [ ] doxygen

## Prerequitites:

  - Curl development libraries
  - Boost Property Tree
  - Boost Optional
  - Boost JSON parser
  - CMake (v3.8+)

## Compilation and running:

  1. Download and cd into hue-api directory
  2. mkdir build
  3. cd build
  4. cmake ..
  5. make
  6. ./hue_server
  7. If you do not have a configuration file with a valid key you will need to press
     button on the HUE hub when prompted. Once this is complete the key should be saved
     in the configuration file which by default will be saved unless the build directory
     is removed.