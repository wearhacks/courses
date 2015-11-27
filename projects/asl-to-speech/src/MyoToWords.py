__author__ = 'e_tak_000'

# The work is based over Niklas Rosenstein's myo-python

import myo as libmyo; libmyo.init()
import time
import os
import sys
import math

class Listener(libmyo.DeviceListener):

    def on_connect(self, myo, timestamp):
        print("Hello, Myo!")
        myo.vibrate('short')
        myo.vibrate('short')
        myo.vibrate('short')


    def on_disconnect(self, myo, timestamp):
        print("Goodbye, Myo!")


    def on_orientation_data(self, myo, timestamp, quat):
        print("Orientation:", quat.x, quat.y, quat.z, quat.w)


    def on_pose(self, myo, timestamp, pose):
        if pose == libmyo.Pose.fist:
            print("Don't show me 'ya fist!")
            return False  # Stops the Hub

#####################################################
#  Program Parameters

#Number of samples per second to take
samplingRate = 5

#total time of recording, in seconds
recordingTime = 2

#Minimum difference between readings to consider that there was a true change, and not just a glitch
minimumAcceptedDisplacement = 2;

#Maximum accepted number of invalid samples. An invalid sample is a sample whose difference with its next on is less thant minimumAcceptedDisplacement
# 2 here was chosen, assuming an array of 8 inputs. Maybe later I will convert it to a percentage of the size
maximumInvalidReadings = 3

#What differentiates between low and high differences
lowAmplitudeThreshold = 5

#Glitch amplitude
glitchAmplitude = 20

#Global variable to hold the recognized word
recognizedWord = ""


# A function that evaluates if the array is worthy to be taken into consideration or not.
# There should be a minimum number of irrelevant readings and no big variation in the data
def ComputeAxisValidity(Axis):
    invalidCount = 0
    axisIsValid = True
    highDifference = False
    averageDifference = []

    highestDiff = GetHighestDifference(Axis, 0, 0)

    for index in range(len(Axis) - 1):
        absoluteDifference = abs(Axis[index] - Axis[index + 1])
        averageDifference.append(absoluteDifference)
        if absoluteDifference < minimumAcceptedDisplacement:
            invalidCount += 1;

        if absoluteDifference > 3:
            highDifference = True

    average = reduce(lambda x, y: x + y, averageDifference) / len(averageDifference)

    if not highDifference:
        if highestDiff < 6:
            if invalidCount > maximumInvalidReadings or average <= minimumAcceptedDisplacement:
                axisIsValid = False

    return axisIsValid


############################################################################################
#Compute the general direction of the axis. Note that this function returns Axis length - 1
def ComputeAxisDirection(Axis):
    AxisDirection = []

    #Get the initial movement direction, even if glitched
    if ( Axis[0] < Axis[1] ) :
        AxisDirection.append('U')
    else:
        AxisDirection.append('D')

    for index in range(1, len(Axis) - 1) :
    #Smooth out glitches, differences of less than 3 are not considered to be changes in movement
        if (abs(Axis[index] - Axis[index + 1]) > minimumAcceptedDisplacement):
            if (Axis[index] < Axis[index + 1]) :
                AxisDirection.append('U')
            else:
                AxisDirection.append('D')
        else:
            #Else consider no change, and make the current direction equals the previous direction
            AxisDirection.append( AxisDirection[index-1] )

    return AxisDirection


#Compute Number of changes in direction. To simplify things, an array with more than 1 change in direction is invalid
def ComputeNumberOfDirectionChange(Axis):
    directionChange = 0

    for index in range(len(Axis) - 1):
        if (Axis[index] != Axis[index + 1])  :
            directionChange += 1

    return directionChange


#return the highest difference within the samples
def GetHighestDifference(AxisData, isDirectionChanged, AxisDirection):

    highestPoint = max(AxisData)
    lowestPoint = min(AxisData)

    highestDiff = abs(highestPoint - lowestPoint)

    return highestDiff


# Where the main processing is, this is where the wrds are recognized
def AnalyzeDirection(pInput, rInput, yInput, t, numberOfSamples):

    pBiDrectional = False
    yBiDrectional = False

    isPitchValid = ComputeAxisValidity(pInput)
    isYawValid = ComputeAxisValidity(yInput)

    if isPitchValid and isYawValid:
        #Potentially a hello
        pDir = ComputeAxisDirection(pInput)
        yDir = ComputeAxisDirection(yInput)

        pDirChange = ComputeNumberOfDirectionChange(pDir)
        yDirChange = ComputeNumberOfDirectionChange(yDir)

        if pDirChange == 1:
            pBiDrectional = True

        if yDirChange == 1:
            yBiDrectional = True

        if not pBiDrectional and not yBiDrectional:
            return

        pExtreme = GetHighestDifference(pInput, pDirChange, pDir)

        # Now we ended up with 2 bidirectional pitch and yaw, see if they fit
        # First, yaw is low-high-low and pitch is high-low-high. if that doesn't apply, break
        if ((pDir[0] == 'U') and (yDir[0] == 'U')):
            #print("Yaw must have a Low-High-Low profile and Pitch the opposite, unrecognized word")
            return
        # Now that all is set, if x has a high amplitude then it's a hello, else it's a please
        if( pExtreme > lowAmplitudeThreshold):
            print("Recognized word: Hello!")
            recognizedWord = "Hello"
            textToSpeech(recognizedWord)

    elif isPitchValid and not isYawValid:
        #Potentilly a thanks or welcome
        pDir = ComputeAxisDirection(pInput)
        pDirChange = ComputeNumberOfDirectionChange(pDir)

        #In pitch-only words, all recognized words are unidirectional.
        if pDirChange > 0:
            return

        #Now, we don't care much here about the amplitude, all we care about is the direction
        #A High-Low is You're welcome, and Low-High is Thanks
        if(pDir[0] == 'D'):
            print("Recognized word: You're Welcome!")
            recognizedWord = "You're Welcome!"
            textToSpeech(recognizedWord)
        else:
            print("Recognized word: Thanks!")
            recognizedWord = "Thanks"
            textToSpeech(recognizedWord)
    else:
        #Check for roll, if valid then there could be a "How?"
        isRollValid = ComputeAxisValidity(rInput)
        if not isRollValid:
            #The three axis were stationary.. drink some coffeeeeeee!@#$"
            return
        #Check if it's a "How?"
        rDir = ComputeAxisDirection(rInput)
        rDirChange = ComputeNumberOfDirectionChange(rDir)

        #No multi-directio roll movements are supported
        if rDirChange > 0:
            return

        #Where is Low-High roll. High-Low roll is unrecognized
        if(rDir[0] == 'U'):
            print("Recognized word: Where?")
            recognizedWord = "Where?"
            textToSpeech(recognizedWord)
        else:
            #Unrecognized word
            print("Invalid: Unrecognized word")
            return

def computePitch(x, y, z, w):
    pitch = math.asin(max(-1.0, min(1.0, (2.0 * ( (w * y) - (z * x) ) )) ) )
    return pitch


def computeRoll(x, y, z, w):
    roll = math.atan2( 2.0 * (( w * x) + (y * z)) , 1.0 - (2.0 * ( (x*x) + (y*y) )) )
    return roll


def computeYaw(x, y, z, w):
    yaw = math.atan2( (2.0 * ( (w * z) + (x * y) ) ), (1.0 - ( 2.0 * ( (y * y) + (z * z) ) ) ) )
    return yaw

def textToSpeech(text):
    os.system('py -3 tts.py creds.json ' + "\"" + text + "\"" + ' output.pcm')

def getMyoInput():
    feed = libmyo.device_listener.Feed()
    try:
        hub = libmyo.Hub()
    except MemoryError:
        print("Myo: Hub could not be created. Make sure Myo Connect is running.")
        return
    hub.run(1000, feed)

    myo = feed.wait_for_single_device(timeout=10.0)  # seconds
    print("Myo: Trying to connect...")
    if not myo:
        print("Myo: No Myo connected after 10 seconds.")
        sys.exit()

    print("Myo: Connected!!")

    pitch = 0
    roll = 0
    yaw  = 0

    # These 3 lists will hold the readings of the accelerometers.
    # Their input will be then analyzed to infer the direction of the motion.
    pitchInput = []
    rollInput = []
    yawInput = []

    if hub.running and myo.connected:

        myo.vibrate('short')
        time.sleep(1)

        #Register the input for recordTiming seconds
        for threeSecond in range( int(recordingTime * samplingRate)):
            #Take samplingRate reading per second
            time.sleep( 1.0 / samplingRate)

            #Read the accelerometer
            quat = myo.orientation

            pitch = computePitch(quat.x, quat.y, quat.z, quat.w)
            roll = computeRoll(quat.x, quat.y, quat.z, quat.w)
            yaw = computeYaw(quat.x, quat.y, quat.z, quat.w)

            pitch_n = int((pitch + math.pi/2.0) / math.pi * 40)
            roll_n =  int((roll + math.pi )/( math.pi * 2.0) * 120)
            yaw_n = int((yaw + math.pi)/(math.pi * 2.0) * 40)

            #Add it to the input list
            pitchInput.append(pitch_n)
            rollInput.append(roll_n)
            yawInput.append(yaw_n)

        AnalyzeDirection(pitchInput, rollInput, yawInput, recordingTime, samplingRate)

    hub.shutdown()

if __name__ == '__main__':
    getMyoInput()