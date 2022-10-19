/*****************************************************************

THIS SOFTWARE IS OPEN SOURCE UNDER THE MIT LICENSE
SUPPORT IS AVAILABE FROM THE AUTHORS

Copyright 2022 Vincent Maciejewsk, Quant Enterprises & M2 Tech
Contact:
v@m2te.ch
mayeski@gmail.com
https://www.linkedin.com/in/vmayeski/
http://m2te.ch/


Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

https://opensource.org/licenses/MIT

*****************************************************************/

#pragma once

#include "TTFixClient.hpp"
#include <set>
#include <stdexcept>

namespace m2::ttfix
{

  struct Driver
  {

    TTFixClient *client;

    Driver(TTFixClient *_client)
        : client(_client)
    {
    }

    char queryAction()
    {
      char value;
      std::cout << std::endl
                << "1) Enter Order" << std::endl
                << "2) Cancel Order" << std::endl
                << "3) Replace Order (price)" << std::endl
                << "4) Replace Order (size)" << std::endl
                << "5) Quit" << std::endl
                << "?: ";
      std::cin >> value;
      return value;
    }

    void run()
    {
      for (;;)
      {
#define DRIVERTRYCATCH
#ifdef DRIVERTRYCATCH
        try
        {
#endif
          switch (
              char action = queryAction();
              action)
          {
          case '1':
            queryEnterOrder();
            break;
          case '2':
            queryCancelOrder();
            break;
          case '3':
            queryReplaceOrder_price();
            break;
          case '4':
            queryReplaceOrder_size();
            break;
          case '5':
            return;
          default:
            std::cout << "invalid: " << action << std::endl;
          }
#ifdef DRIVERTRYCATCH
        }
        catch (std::runtime_error &e)
        {
          std::cout << "got runtime_error: " << e.what();
        }
#endif
      }
    }

    void queryEnterOrder()
    {
      std::cout << "NewOrderSingle ZNZ2\n";
      auto cficode = "FFDXSX";
      auto symbol = "ZN";
      auto securityId = "ZNZ2";
      std::cout << "order type (MKT, LIM, STP, STL): ";
      std::string ordertyp;
      std::cin >> ordertyp;
      std::string timeInForce = "DAY";
      double price = 0;
      if (ordertyp != "MKT")
      {
        std::cout << "price: ";
        std::cin >> price;
        std::cout << "time in force (DAY, IOC, OPG, GTC, GTX): ";
        std::cin >> timeInForce;
      }
      std::cout << "sz: ";
      int sz;
      std::cin >> sz;
      std::cout << "side (B,S): ";
      char side;
      std::cin >> side;
      auto clid = client->sendNewOrderSingle(
          cficode,
          securityId,
          symbol,
          price,
          sz,
          side,
          ordertyp.c_str(),
          timeInForce.c_str());
      std::cout << "NewOrderSingle clid= " << clid << std::endl;
    }

    void queryCancelOrder()
    {
      std::cout << "OrderCancelRequest\n";
      std::cout << "cloid: ";
      uint64_t cloid;
      std::cin >> cloid;
      client->sendCancelOrderRequest(
          cloid);
    }

    void queryReplaceOrder_price()
    {
      std::cout << "CancelReplaceRequest (change price)\n";
      uint64_t origClOrdId;
      std::cout << "cl ord id to cancel: ";
      std::cin >> origClOrdId;
      double price;
      std::cout << "price: ";
      std::cin >> price;
      client->sendCancelReplaceRequest(
          origClOrdId,
          0,
          price,
          true);
    }

    void queryReplaceOrder_size()
    {
      std::cout << "CancelReplaceRequest (change size)\n";
      uint64_t origClOrdId;
      std::cout << "cl ord id to cancel: ";
      std::cin >> origClOrdId;
      double price = 0;
      int sz;
      std::cout << "sz: ";
      std::cin >> sz;
      client->sendCancelReplaceRequest(
          origClOrdId,
          sz,
          price,
          false);
    }
  };

}