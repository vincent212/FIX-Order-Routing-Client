# Trading Technologies Order Routing Client in C++
This is a C++ FIX client for order management. It can connect to a Trading Technologies
FIX gateway that will then communicate with an exchange such as the CME. For more
information about TT order routing please see:
https://library.tradingtechnologies.com/tt-fix/order-routing/fix-order-routing-overview.html

A driver program is included that allows submission of commands for testing. These
include normal trading commands such as placing and cancelling orders.

After the client starts please wait for the "Logon" and "News" messages.

Copyright 2022 Vincent Maciejewski, Quant Enterprises & M2 Tech
Contact:
v@m2te.ch
mayeski@gmail.com
https://www.linkedin.com/in/vmayeski/
http://m2te.ch/

A bit more information on the order manager is found on my blog:
http://maye.ski/

# Instructions

Building QuickFix

First install openssl from https://www.openssl.org/
to /usr/local

Download quickfix-1.15.1 from GitHub.

If you want to disable file system I/O in QF please
read README in qf_hack.

Then build QuickFix:

        ./bootstrap
        ./configure --with-openssl=/usr/local
        make -j8
        make check
        sudo make install

Building TT FIX Client


Make sure that your include path contains the QuickFix configuration
file config.h. It will normally be found in: quickfix-1.15.1/
In main.cpp it is used to assert if QuickFix build with SSL support.

Once you have installed QuickFix run the Python script cleanqf.py
to convert C++14 header to C++17. Edit the installation directory
if you ahave not installed in /usr/local/

Code was built using GCC 8.5.0

Assuming you have installed QuickFix in /usr/local you can use this command to build:

g++ -Ipath_to_config_h -std=c++17 TTFixClient.cpp main.cpp -o test -lquickfix
