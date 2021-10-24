# hue-api
A complete c++ api for hue products

This project is very much in development so this readme will be frequently updated
as features are added. The intention is to have a functional and easy to use c++ interface
for hue products, with some possible added functionality.  Below are some of the implemented features and the todo list:

Features:

  - JSON Configuration file which can populate and save off up settings.  Could be used
    for lighting settings as well

  - Get and Post methods implemented

  - Auto-connect, hub IP retrieval and authentication (Testing in progress) 

TO DO:

  - Create Light class which will hold all of the structures for the light and implement
    all of the high level functionality.  It should dependancy inject the Command class 
    and implement a virtual interface to Command where appropriate, such as the connect 
    method.  The goal would be that the end user will not need to make calls within
    the Command and Config methods.

