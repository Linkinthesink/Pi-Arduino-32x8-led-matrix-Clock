import gpiozero
from gpiozero import LED
from time import sleep
from datetime import datetime
import time

pin8 = LED(21)
pin7 = LED(20)
pin6 = LED(16)

correcthr = 0
i = 0
j = 0


correcthr = 0
min = 0

while True:
    pin6.off()
    pin7.off()
    pin8.off()
    myobj = datetime.now()
    
    if (myobj.hour > 12):
        correcthr = myobj.hour - 12
    else:
        correcthr = myobj.hour
        
    min = myobj.minute
    



    

    
    #read Signal
    pin6.on()
    sleep(0.003)
    
    # Hr send
    while (i < correcthr):
        pin7.on()
        sleep(0.0002)
        #print(0)
        pin7.off()
        sleep(0.0002)
        #print(1)
        i += 1
    i = 0
    
    #End read signal
    pin6.off()
    sleep(0.003)
    #Second read signal
    pin6.on()
    sleep(0.003)
    
    # Min Send

    while (i < min):
        pin8.on()
        sleep(0.0002)
        #print(0)
        pin8.off()
        sleep(0.0002)
        #print(1)
        i += 1
        
    i = 0
    

    #end read signal
    pin6.off()
    sleep (0.003)
    
    
    
    
    
    
