/*****************************************************************

THIS SOFTWARE IS OPEN SOURCE UNDER THE MIT LICENSE
SUPPORT IS AVAILABE FROM THE AUTHORS

Copyright 2022 Vincent Maciejewski, Quant Enterprises & M2 Tech
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

#include <iostream>

#include "OrdStatus.hpp"
#include "ExecType.hpp"
#include "CallBackIF.hpp"

namespace m2::ttfix
{
  /**
   * @brief call back implementation
   *
   */
  struct CallBackImp : public CallBackIF
  {

    virtual void onLogon() noexcept override
    {
      std::cout << "logged on\n";
    }

    virtual void onLogout() noexcept override
    {
      std::cout << "logged out\n";
    }

    virtual void onNews(const std::string&text) noexcept override
    {
      std::cout << "news: " << text << std::endl;;
    }

    virtual void onExecutionReport(
        OrdStatus s,
        ExecType x,
        uint64_t clOrdId,
        const std::string &TTOrdId,
        uint64_t cmeOrdId,
        uint qty,
        uint cumQty,
        uint leavesQty,
        bool has_px,
        double px,
        const std::string &tranactionTime,
        const std::string &TTreceiveTime,
        const std::string &sendingTime,
        const std::string &text
        ) noexcept override
    {
      std::cout << "ExecutionReport:"
                << " s=" << to_string(s)
                << " x=" << to_string(x)
                << " clOrdId=" << clOrdId
                << " TTOrdId=" << TTOrdId
                << " cmeOrdId=" << cmeOrdId
                << " qty=" << qty
                << " cumQty=" << cumQty
                << " leavesQty=" << leavesQty
                << " has_px=" << has_px
                << " px=" << px
                << " tranactionTime=" << tranactionTime
                << " TTreceiveTime=" << TTreceiveTime
                << " sendingTime=" << sendingTime
                << " text=" << text
                << std::endl;
    }

    virtual void onOrderCancelReject(
        OrdStatus s,
        uint64_t clOrdId,
        uint64_t origClOrdId,
        const std::string &TTOrdId,
        uint64_t cmeOrdId,
        int cxlRejResponseTo,
        int cxlRejReason,
        const std::string &complianceText,
        const std::string &tranactionTime,
        const std::string &TTreceiveTime,
        const std::string &text
        ) noexcept override
    {
      std::cout << "OrderCancelReject:"
                << " s=" << to_string(s)
                << " clOrdId=" << clOrdId
                << " origClOrdId=" << origClOrdId
                << " TTOrdId=" << TTOrdId
                << " cmeOrdId=" << cmeOrdId
                << " cxlRejResponseTo=" << cxlRejResponseTo
                << " cxlRejReason=" << cxlRejReason
                << " complianceText=" << complianceText
                << " tranactionTime=" << tranactionTime
                << " TTreceiveTime=" << TTreceiveTime
                << " text=" << text
                << std::endl;
    }
  };
}