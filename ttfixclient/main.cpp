/*****************************************************************

THIS SOFTWARE IS OPEN SOURCE UNDER THE MIT LICENSE

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
  m2::ttfix::Driver driv(&application);
  driv.run();
  initiator->stop();
  delete initiator;
  delete cb;
  return 0;
}
