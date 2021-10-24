# json-config-template
A generic template for a JSON based configuration file with example of usage.

Very simple config file template and demo.
read and write calls are overloaded with string
parameters, otherwise the default location defined
in the header is used.  A timestamp is set when writing
the file.  It does not seem to be saving off the full
64 bits of information.  I'll have to look into this later
but this still should be good down to seconds, which is fine
for most config file timestamps.

compile with -lboost_system
