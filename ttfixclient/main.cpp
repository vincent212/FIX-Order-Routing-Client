#include "config.h" // used to check if QuickFix was built with SSL

#include "quickfix/FileStore.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/SSLSocketInitiator.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/Log.h"

#include "TTFixClient.hpp"
#include "CallBackImp.hpp"
#include "Driver.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cout << "usage: " << argv[0]
         << " <settingsfile>" << std::endl;
    return 0;
  }
  std::string file = argv[1];
  FIX::Initiator *initiator = 0;
  FIX::SessionSettings settings(file);
  auto targetCompId = settings.get().getString("TARGETCOMPID");
  auto senderCompId = settings.get().getString("SENDERCOMPID");
  auto account = settings.get().getString("ACCOUNT");
  auto exchange = settings.get().getString("SECURITYEXCHANGE");
  auto password = settings.get().getString("PASSWORD");
  auto cb = new m2::ttfix::CallBackImp();
  m2::ttfix::TTFixClient application(
      cb,
      exchange,
      account,
      password,
      targetCompId,
      senderCompId);
  FIX::FileStoreFactory storeFactory(settings);
  FIX::ScreenLogFactory logFactory(settings);
#define USESSL
#ifdef USESSL
  static_assert(HAVE_SSL, "QF must be compiled with SSL enabled");
  initiator = new FIX::SSLSocketInitiator(application, storeFactory, settings, logFactory);
#else
  initiator = new FIX::SocketInitiator(application, storeFactory, settings, logFactory);
#endif
  initiator->start();
  // get_thread_id may be useful to add to Initiator.h
  // auto th = initiator->get_thread_id();
  // std::cout << "SSLSocketInitiator thread id: " << th << std::endl;
  m2::ttfix::Driver driv(&application);
  driv.run();
  initiator->stop();
  delete initiator;
  delete cb;
  return 0;
}