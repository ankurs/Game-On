import serial
import socket

s = serial.Serial("com4",4800)
sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.bind(("",9090))
sock.listen(10)
a,b = sock.accept()
print b
s.write("\x00")

up = 0
down = 0
right = 0
left = 0

while True:
    data = a.recv(1)
    if data > 0:
        print data
        if data == "\x01" and left == 0:
            print "Turn Left"
            val = ""
            if up == 1:
                val = "\x06"
            elif down == 1:
                val = "\x0a"
            else:
                val = "\x02"
            s.write(val)
            left = 1
            right = 0
        if data == "\x02" and right == 0:
            print "Turn Right"
            val = ""
            if up == 1:
                val = "\x05"
            elif down == 1:
                val = "\x09"
            else:
                val = "\x01"
            s.write(val)
            right = 1
            left = 0        
        if data == "\x03":
            print "Straignt"
            left = 0
            right = 0
            val = ""
            if up == 1:
                val = "\x04"
            elif down == 1:
                val = "\x08"
            else:
                val = "\x00"
            s.write(val)        
        if data == "\x04" and down == 0:
            print "Back"
            val = ""
            if left == 1:
                val = "\x09"
            elif right == 1:
                val = "\x0a"
            else:
                val = "\x08"              
            s.write(val)
            down = 1
            up = 0
        if data == "\x05" and up == 0:
            print "Forword"
            val = ""
            if left == 1:
                val = "\x05"
            elif right == 1:
                val = "\x06"
            else:
                val = "\x04"                
            s.write(val)
            down = 0
            up = 1           
        if data == "\x06":
            print "Center"
            val = ""
            if left == 1:
                val = "\x01"
            elif right == 1:
                val = "\x02"
            else:
                val = "\x00"
            s.write(val)
            down = 0
            up = 0
