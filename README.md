# Trading Technologies Order Routing Client in C++
This is a C++ FIX client for order management. It can connect to a Trading Technologies
FIX gateway for order routing. Although it has only been testd with TT, with small modifications
it should work with the CQG gateway as well.

For more information about TT order routing please see:
https://library.tradingtechnologies.com/tt-fix/order-routing/fix-order-routing-overview.html

For more information about CQG order routing please see:
https://help.cqg.com/apihelp/index.html#!Documents/fixconnectorderrouting.htm

The QuickFix engine is used for the FIX protocol. https://en.wikipedia.org/wiki/QuickFIX

A driver program is included that allows for submission of commands for testing. These
include normal trading commands such as placing and cancelling orders.

Copyright 2022 Vincent Maciejewski, Quant Enterprises & M2 Tech
Contact:
v@m2te.ch
mayeski@gmail.com
https://www.linkedin.com/in/vmayeski/
http://m2te.ch/

A bit more information on the order manager is found on my blog:
http://maye.ski/
