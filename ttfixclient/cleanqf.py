#!/usr/bin/env python3

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
