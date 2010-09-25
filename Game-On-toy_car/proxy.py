import socket

s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s1.bind(("",9092))
s1.listen(1)
a,b = s1.accept()
print b
s2.connect(("192.168.122.163",9091))

while True:
    s2.send(a.recv(1))
