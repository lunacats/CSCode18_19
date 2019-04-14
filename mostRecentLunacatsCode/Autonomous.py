from RobotCommunication import *
import PixyFollowSig
from time import sleep
import json
import threading


# The height that the picture should be at the target position
posHeight = 60
posWidth  = 30

# The allowed variation for the height
heightVary = 20
widthVary = 5;
    

taskInput = ""

lidarDistance = 0;
objectDetected = False;


def terminTask():
    global taskInput
    while taskInput != "S":
        taskInput = raw_input("Input")
    PixyFollowSig.terminate()


def faceTarget(angle,target):
    if angle - 50 > target:
        right(15)
        return False
    elif angle + 50 < target:
        left(15)
        return False
    return True

def goForward(angle):
    global lidarDistance
    global objectDetected

    print "Going Forward:" + str(angle)
    if faceTarget(angle,0):
        newDataStr = forward(15)
        print "GOT: '"+newDataStr+"'"
        newData = json.loads(newDataStr)
        lidarDistance = newData["L"]
        print "Distance:" + str(lidarDistance)
        if lidarDistance < 3.0:
            objectDetected = True


def goBack(angle):
    print "Going Back:" + str(angle)
    if faceTarget(angle, 0):
        back(15)

def goLeft(angle):
    print "Going Left"
    if faceTarget(angle, -250):
        forward(15)
def goRight(angle):
    print "Going Right"
    if faceTarget(angle, 250):
        forward(15)

def holdPos():
    stop()
    print "Holding Position"


atGoodHeight = False

def processHeight(data,i,angle):
    global atGoodHeight
    height = data["H" + str(i)]
    #print "getting Height:" + str(height)

    if height > posHeight + heightVary:
        goBack(angle)
        atGoodHeight = False
    elif height < posHeight - heightVary:
        goForward(angle)
        atGoodHeight = False
    else:
        atGoodHeight = True

def processWidth(data,i,angle):
    width = data["W" + str(i)]
    #print "getting Width:" + str(width)

    if width > posWidth + widthVary:
        goLeft(angle)
    elif width < posWidth - widthVary:
        goRight(angle)
    else:
        holdPos()





if __name__ == '__main__':



    while taskInput != "S":
        PixyFollowSig.track()

        dataString = PixyFollowSig.getSig()
        data = json.loads(dataString)

        if objectDetected:
            print "Object Detected!!!!!"
            back(15)
            sleep(0.5)
            left(15)
            sleep(2)
            forward(15)
            sleep(1.5)
            objectDetected = False
            print "Object evaded!"
        if data["C"] == 0:
            stop()
        else:
            for i in range(0,data["C"]):
                if data["S"+str(i)] == 1:
                    processHeight(data,i,data["A"])
                if data["S" + str(i)] == 1 and atGoodHeight:
                    processWidth(data, i,data["A"])



