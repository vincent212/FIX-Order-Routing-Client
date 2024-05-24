# FIX Order Routing Client in C++
This is a C++ FIX client for order management. It has been tested with Trading Technologies
FIX gateway for order routing. With small modifications
it should work with the CQG gateway as well.

For more information about TT order routing please see:
https://library.tradingtechnologies.com/tt-fix/order-routing/fix-order-routing-overview.html

Exchange connectivity available via TT
https://www.tradingtechnologies.com/markets/markets-served/

For more information about CQG order routing please see:
https://help.cqg.com/apihelp/index.html#!Documents/fixconnectorderrouting.htm

Exchange connectivity available via CQG
https://www.cqg.com/partners/exchanges/tradable-exchanges

The QuickFix engine is used for the FIX protocol. https://en.wikipedia.org/wiki/QuickFIX

A driver program is included that allows for submission of commands for testing. These
include normal trading commands such as placing and cancelling orders.

Copyright 2022 Vincent Maciejewski, Quant Enterprises & M2 Tech
Contact:
v@m2te.ch
mayeski@gmail.com
https://www.linkedin.com/in/vmayeski/
http://m2te.ch/

Latency for NewOrderSigle send is under 7 micro seconds. Will go down to 3.5us if you compile QuickFix with C++17.
