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

#include <chrono>

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/fix44/NewOrderSingle.h"
#include "quickfix/fix44/ExecutionReport.h"
#include "quickfix/fix44/OrderCancelRequest.h"
#include "quickfix/fix44/OrderCancelReject.h"
#include "quickfix/fix44/Reject.h"
#include "quickfix/fix44/OrderCancelReplaceRequest.h"
#include "quickfix/fix44/MarketDataRequest.h"
#include "quickfix/fix44/News.h"
#include "quickfix/fix44/BusinessMessageReject.h"

#include "OrdStatus.hpp"
#include "ExecType.hpp"
#include "CallBackIF.hpp"

namespace m2::ttfix
{

  /**
   * @brief This class implements a FIX order manager for Trading Technologies
   * @see https://library.tradingtechnologies.com/tt-fix/order-routing/fix-order-routing-overview.html
   *
   */
  class TTFixClient : public FIX::Application,
                      public FIX::MessageCracker
  {
  public:
    TTFixClient(
        CallBackIF *_cb,
        const std::string _exchange,
        const std::string _account,
        const std::string _password,
        const std::string _targetCompId,
        const std::string _senderCompId) : cb(_cb),
                                           exchange(_exchange),
                                           account(_account),
                                           password(_password),
                                           targetCompId(_targetCompId),
                                           senderCompId(_senderCompId)
    {
    }

    ~TTFixClient()
    {
      delete newOrderSingle;
      delete orderCancelRequest;
      delete cancelReplaceRequest;
    }

    /**
     * @brief new order single
     * @see https://www.onixs.biz/fix-dictionary/4.4/msgType_D_68.html
     *
     * @param cficode
     * @param securityId
     * @param symbol
     * @param price
     * @param sz
     * @param bs 'B' or 'S'
     * @param orderType "MKT", "LIM", "STP", "STL"
     * @param timeInForce  "DAY", "IOC", "OPG", "GTC", "GTX"
     * @return int64_t client order id to be used for cancel and canc replace
     */
    [[nodiscard]] uint64_t sendNewOrderSingle(
        const char *cficode,
        const char *securityId,
        const char *symbol,
        double price,
        int qty,
        char bs,
        const char *orderType,
        const char *timeInForce);

    /**
     * @brief cancel order
     * @see https://www.onixs.biz/fix-dictionary/4.2/msgType_F_70.html
     * entire order will be cancelled
     *
     * @param origClOrdId as returned by sendNewOrderSingle
     * @return uint64_t client order id for this transaction
     */
    uint64_t sendCancelOrderRequest(
        uint64_t origClOrdId);

    /**
     * @brief cancel replace
     * @see https://www.onixs.biz/fix-dictionary/4.4/msgType_G_71.html
     *
     * If has_price is true, price must be set and it will be replaced.
     * If qty is zero it will not be changed.
     * Even though TT may allow for changing of order type and
     * time in force, this functionality is not exposed.
     *
     * @param origClOrdId as returned by sendNewOrderSingle
     * @param qty
     * @param price
     * @param has_price
     * @return uint64_t client order id
     */
    uint64_t sendCancelReplaceRequest(
        uint64_t origClOrdId,
        int qty,
        double price,
        bool has_price);

  private:
    CallBackIF *cb;
    FIX::SecurityExchange exchange;
    FIX::SenderCompID senderCompId;
    FIX::TargetCompID targetCompId;
    FIX::Account account;
    std::string password;
    bool noNews = true;
    bool isLoggedOn = false;
    FIX44::NewOrderSingle *newOrderSingle = 0;
    FIX44::OrderCancelRequest *orderCancelRequest = 0;
    FIX44::OrderCancelReplaceRequest *cancelReplaceRequest = 0;

    // Storing some order info for convenience of callers.
    // Ideally this map would not be here, however, it should
    // always be possible to cancel an order with just the
    // client order ID. Any additional fields needed by QF
    // constructor are looked up in ordInfo map.
    struct OrdInfo
    {
      FIX::Side side;
      double price;
      FIX::OrdType ordType;
      int qty_remaining;
      OrdInfo(
          FIX::Side _side,
          double _price,
          FIX::OrdType _ordType,
          int _qty_remaining) : side(_side),
                                price(_price),
                                ordType(_ordType),
                                qty_remaining(_qty_remaining)
      {
      }
    };
    std::map<int64_t, OrdInfo> ordInfo;

    /**
     * @brief create a uniqe order id as int and string representations
     *
     * @return std::tuple<int64_t, std::string>
     */
    std::tuple<int64_t, std::string> createCLOID()
    {
      uint64_t tse = std::chrono::system_clock::now().time_since_epoch().count();
      return std::make_tuple(tse, std::to_string(tse));
    }

    /**
     * @brief called when fix session is created
     *
     */
    void onCreate(const FIX::SessionID &) {}

    /**
     * @brief Logon ack
     *
     * @param sessionID
     */
    void onLogon(const FIX::SessionID &sessionID);

    /**
     * @brief Logout ack
     *
     * @param sessionID
     */
    void onLogout(const FIX::SessionID &sessionID);

    /**
     * @brief Admin messages to TT
     * must add password to Logon message here
     *
     * @param m
     */
    void toAdmin(FIX::Message &, const FIX::SessionID &);

    /**
     * @brief All messages to TT can be intercepted here
     *
     * @param message
     * @param sessionID
     */
    void toApp(FIX::Message &, const FIX::SessionID &);

    /**
     * @brief Admin messages from TT
     *
     * @param m
     */
    void fromAdmin(const FIX::Message &m, const FIX::SessionID &);

    /**
     * @brief all messages from TT can be intercepted here
     *
     * @param message
     * @param sessionID
     */
    void fromApp(const FIX::Message &message, const FIX::SessionID &sessionID);

    /**
     * @brief Provides Ack or Fill
     * @see https://library.tradingtechnologies.com/tt-fix/gateway/Msg_ExecutionReport_8.html
     *
     */
    void onMessage(const FIX44::ExecutionReport &, const FIX::SessionID &);

    /**
     * @brief Cancel Reject
     * @see https://library.tradingtechnologies.com/tt-fix/gateway/Msg_OrderCancelReject_9.html
     *
     */
    void onMessage(const FIX44::OrderCancelReject &, const FIX::SessionID &);

    /**
     * @brief End of recovery after restart
     * @see https://library.tradingtechnologies.com/tt-fix/general/Msg_News_B.html
     *
     */
    void onMessage(const FIX44::News &, const FIX::SessionID &);

    /**
     * @brief Session Level Reject
     * @see https://library.tradingtechnologies.com/tt-fix/general/Msg_SessionLevelReject_3.html
     *
     */
    void onMessage(const FIX44::Reject &, const FIX::SessionID &);

    /**
     * @brief Business Level Reject
     * @see https://library.tradingtechnologies.com/tt-fix/general/Msg_BusinessMessageReject_j.html
     *
     */
    void onMessage(const FIX44::BusinessMessageReject &, const FIX::SessionID &);
  };

}