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

#include <string>
#include <stdexcept>

namespace m2::ttfix
{
  /**
   * @brief Order status values for tag 39
   * @see  https://library.tradingtechnologies.com/tt-fix/gateway/Msg_ExecutionReport_8.html
   *
   */
  enum class OrdStatus
  {
    NewOrder = 0,
    Partially_filled, // 1
    Filled,           // 2
    Done_for_day,     // 3
    Canceled,         // 4
    Replaced,         // 5
    Pending_Cancel,   // 6
    Rejected = 8,
    Pending_New = 10,    // A
    Expired = 12,        // C
    Pending_Replace = 15 // E
  };

  static OrdStatus convertOrdStatus(const std::string &s)
  {
    switch (s.c_str()[0])
    {
    case '0':
      return OrdStatus::NewOrder;
    case '1':
      return OrdStatus::Partially_filled;
    case '2':
      return OrdStatus::Filled;
    case '3':
      return OrdStatus::Done_for_day;
    case '4':
      return OrdStatus::Canceled;
    case '5':
      return OrdStatus::Replaced;
    case '6':
      return OrdStatus::Pending_Cancel;
    case '8':
      return OrdStatus::Rejected;
    case 'A':
      return OrdStatus::Pending_New;
    case 'C':
      return OrdStatus::Expired;
    case 'E':
      return OrdStatus::Pending_Replace;
    default:
      throw std::runtime_error("unknown OrdStatus: " + s);
    }
  }

  static std::string to_string(OrdStatus s)
  {
    switch (s)
    {
    case OrdStatus::NewOrder:
      return "OrdStatus::NewOrder";
    case OrdStatus::Partially_filled:
      return "OrdStatus::Partially_filled";
    case OrdStatus::Filled:
      return "OrdStatus::Filled";
    case OrdStatus::Done_for_day:
      return "OrdStatus::Done_for_day";
    case OrdStatus::Canceled:
      return "OrdStatus::Canceled";
    case OrdStatus::Replaced:
      return "OrdStatus::Replaced";
    case OrdStatus::Pending_Cancel:
      return "OrdStatus::Pending_Cancel";
    case OrdStatus::Rejected:
      return "OrdStatus::Rejected";
    case OrdStatus::Pending_New:
      return "OrdStatus::Pending_New";
    case OrdStatus::Expired:
      return "OrdStatus::Expired";
    case OrdStatus::Pending_Replace:
      return "OrdStatus::Pending_Replace";
    default:
      throw std::runtime_error("cannot convert OrdStatus to string");
    }
  }

}