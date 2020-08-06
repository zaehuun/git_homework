
import cv2
import numpy as np


red_lower=np.array([170,100,100], np.uint8)
red_upper=np.array([180,255,255],np.uint8)
#defining the Range of green color
green_lower=np.array([50,100,10],np.uint8)
green_upper=np.array([80,255,255],np.uint8)
		
#defining the Range of yellow color
yellow_lower=np.array([0,100,100],np.uint8)
yellow_upper=np.array([20,255,255],np.uint8)

capture = cv2.VideoCapture(0)

while True:

    ret, img = capture.read()
    img = cv2.resize(img, (150,150))
    
    

    
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    #finding the range of red,green and yellow color in the image
    red=cv2.inRange(hsv, red_lower, red_upper)
    green=cv2.inRange(hsv,green_lower,green_upper)
    yellow=cv2.inRange(hsv,yellow_lower,yellow_upper)


    kernal = np.ones((5,5), "uint8")


    red = cv2.dilate(red, kernal)
    res = cv2.bitwise_and(img, img, mask = red)
		
    green = cv2.dilate(green, kernal)
    res1 = cv2.bitwise_and(img, img, mask = green)

    yellow = cv2.dilate(yellow, kernal)
    res2 = cv2.bitwise_and(img, img, mask= yellow)

    contours,hierarchy=cv2.findContours(red,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if(area>1000):
            print(area)
            x,y,w,h = cv2.boundingRect(contour)	
            img = cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),2)
            cv2.putText(img,"RED",(x,y),cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0,0,255)); print('red')
            #print "red"
    ################################################33
    contours,hierarchy=cv2.findContours(yellow,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if(area>1000):
            x,y,w,h = cv2.boundingRect(contour)	
            img = cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)
            cv2.putText(img,"Yellow",(x,y),cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0,255,0)); print('yellow')
		

    contours,hierarchy=cv2.findContours(green,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if(area>1000):
            x,y,w,h = cv2.boundingRect(contour)	
            img = cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
            cv2.putText(img,"Green",(x,y),cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255,0,0)); print('green')
    
    cv2.imshow("VideoFrame", img)

    if cv2.waitKey(33) > 0: break
