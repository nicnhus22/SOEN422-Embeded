import cv2
import urllib 
import numpy as np

stream=urllib.urlopen('http://192.168.7.2:8080/?action=stream.mjpg')
bytes=''
best_cnt = []
while True:
    bytes+=stream.read(1024)
    a = bytes.find('\xff\xd8')
    b = bytes.find('\xff\xd9')

    #Defining the red color range and calculating if these values lie in the range
    red_lower = np.array([20,100, 100], np.uint8)
    red_upper = np.array([30, 255, 255], np.uint8)

  
    if a!=-1 and b!=-1:
        jpg = bytes[a:b+2]
        bytes= bytes[b+2:]
        i = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8),cv2.CV_LOAD_IMAGE_COLOR)

        red_binary = cv2.inRange(i, red_lower, red_upper)
        # Dilates the red space, making it larger
        dilation = np.ones((15, 15), "uint8")
        red_binary = cv2.dilate(red_binary, dilation)

        contours, _ = cv2.findContours(red_binary, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
        
        # finding contour with maximum area and store it as best_cnt
        max_area = 0

        for cnt in contours:
            area = cv2.contourArea(cnt)
            if area > max_area:
                max_area = area
                best_cnt = cnt        

        # finding centroids of best_cnt and draw a circle there
        if not best_cnt == []:    
            M = cv2.moments(best_cnt)
            cx,cy = int(M['m10']/M['m00']), int(M['m01']/M['m00'])
            print cx
                   
        ''' 
        if not contours == []:
            print "Yellow surface detected!---------------------------------------------------"
        else:
            print "No yellow surface  detected."
        '''

        #print i
        if cv2.waitKey(1) ==27:
            exit(0)  
