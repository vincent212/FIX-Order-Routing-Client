
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