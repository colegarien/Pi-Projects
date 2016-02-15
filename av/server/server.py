import os, socket, sys, threading

maps_dir = "/home/pi/av/maps"

class AsciiServer:
  def __init__(self, host="localhost", port=1080):
    self.host = host
    self.port = port
    self.backlog = 5
    self.insize = 1024
    self.server = None
    self.threads = []
  
  def initialize(self):
    try:
      self.server = socket.socket()
      self.server.bind((self.host,self.port))
      print 'Host:', self.host
      print 'port:', self.port
      self.server.listen(self.backlog)
    except socket.error, (value, message):
      if self.server:
        self.server.close()
      print 'Could not open socket: '+message
      sys.exit(1)

  def run(self):
    self.initialize()
    running = 1
    while running:
      try:
        service_thread = AsciiClientHandler(self.server.accept())
        service_thread.start()
        self.threads.append(service_thread)
      except (KeyboardInterrupt, SystemExit):
        self.server.close()
        for service_thread in self.threads:
          service_thread.join()
        running = 0

class AsciiClientHandler(threading.Thread):
  def __init__(self, (client, address)):
    threading.Thread.__init__(self)
    self.client = client
    self.address = address
    self.insize = 1024
    print 'Got connection from', self.address

  def run(self):
    running = 1
    while running:
      print 'waiting on command...'
      command = self.client.recv(self.insize).strip()
      print 'recv command >'+command+'<'
      if command == "MAP":
        mapname = os.path.join(maps_dir,self.client.recv(self.insize).strip())
        try:
          with open(mapname,'rb') as f:
            byte_s = f.read()
            self.client.send(byte_s)
          print 'map '+ mapname + ' served'
        except IOError:
          self.client.send('')
          print mapname + ' not found'
      elif command == "DONE" or command == "":
        print 'client has finished'
        self.client.close()
        running = 0

s = AsciiServer(host='localhost', port=1080)
s.run()
