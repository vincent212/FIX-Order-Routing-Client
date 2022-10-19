#!/usr/bin/env python3

# THIS SOFTWARE IS OPEN SOURCE UNDER THE MIT LICENSE
# SUPPORT IS AVAILABE FROM THE AUTHORS

# Copyright 2022 Vincent Maciejewsk, Quant Enterprises & M2 Tech
# Contact:
# v@m2te.ch
# mayeski@gmail.com
# https://www.linkedin.com/in/vmayeski/
# http://m2te.ch/


# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:

# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

# https://opensource.org/licenses/MIT

import os
import fnmatch

def listFiles(dirP,pattern):
    ret = []
    if dirP[len(dirP)-1] != '/':
        dirP = dirP + '/'
    l = os.listdir(dirP)
    l = fnmatch.filter(l,pattern)
    for f in l:
        if os.path.isfile(dirP+f):
            ret.append(dirP+f)
    ret.sort()
    return ret

files=listFiles("/usr/local/include/quickfix","*.h")

for fn in files:
  print("updating: %s" % (fn))
  os.rename(fn,fn+".orig")
  lines=open(fn+".orig",'r').readlines()
  f=open(fn,'w')
  cnt=0
  for line in lines:
      rline=line.replace("throw(","/*throw(")
      rline=rline.replace("throw (","/*throw(")
      posthrow=rline.find("throw(")
      if posthrow<0:
        f.write(line)
        #print(line.rstrip())
        continue
      posthrowbrace=rline.find(")",posthrow)
      rline2=rline[:posthrowbrace+1] + "*/" + rline[posthrowbrace+1:]
      f.write(rline2)
      cnt+=1
      #print (rline2.rstrip())
  f.close()
  print("replaced %d lines" % (cnt))
