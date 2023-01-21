import Speech_recognitation as sr
from Pyfirmata import Arduino, SERVO , util
from time import sleep

r = sr.Recognizer()
mic = sr.Microphone(device_index=1)

with mic as source:
    r.adjust_for_ambient_noise(source)

    while True:
        audio = r.listen(source)

        try:
            if r.recognize_google(audio)=='on':
                print("on")
            else:
                print("nothing")

        except:
            print("no audio")