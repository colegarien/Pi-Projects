import random
import struct

mapw = 10
maph = 10

class Map:
  def __init__(self, tx, ty):
    self.x = tx
    self.y = ty
    self.w = 80
    self.h = 24
    self.data = []
    for y in xrange(0, self.h):
      for x in xrange(0, self.w):
        self.data.append([])
        if (self.x == 0 and x==0) or (self.y == 0 and y == 0) or (self.x == mapw-1 and x == self.w -1) or (self.y == maph-1 and y==self.h-1):
          self.data[x].append(1)
        else:
          self.data[x].append( random.randint(0, 9) )
  def show(self):
    for y in xrange(0, test.h):
      out = ''
      for x in xrange(0, test.w):
        out += str(test.data[x][y])
      print out
  def save(self):
    f = open(str(self.x)+str(self.y),'wb')
    f.write(struct.pack("B",self.x))
    f.write(struct.pack("B",self.y))
    f.write(struct.pack("B",self.w))
    f.write(struct.pack("B",self.h))
    for y in xrange(0, test.h):
      for x in xrange(0, test.w):
        f.write(struct.pack("B",test.data[x][y]))
    f.close()

for x in xrange(0, mapw):
  for y in xrange(0, maph):
    test = Map(x,y)
    test.save()
