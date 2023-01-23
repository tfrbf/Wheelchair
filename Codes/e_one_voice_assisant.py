import win32api
import speech_recognition as sr
import pyttsx3
import datetime
import webbrowser
import os
import time
import subprocess


engine=pyttsx3.init('sapi5')

voices=engine.getProperty('voices')

engine.setProperty('rate', 112) #set speaking speed rate
engine.setProperty('voice','voices[0].id')

def  speak(text):
    engine.say(text)
    engine.runAndWait()

def   wishMe():
    hour=datetime.datetime.now().hour
    if  hour>=0 and hour<12:
        speak("Hello,Good Morning")
        print("Hello,Good Morning")
    elif  hour>=12 and hour<18:
        speak("Hello,Good Afternoon")
        print("Hello,Good Afternoon")
    else:
        speak("Hello,Good Evening")
        print("Hello,Good Evening")



def  takeCommand():
    r=sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening...")
        audio=r.listen(source)

    try:
        statement=r.recognize_google(audio,language='en-in')
        print(f"you siad :{statement}\n")
        #speak("Welcome to e-one")
        speak(audio)

    except Exception as e:
        speak("Pardon me, please say that again")
        
        return "None"
    return statement

print("Loading e-One...")
speak("Loading e-One")
#wishMe()

if __name__=='__main__':
    while True:
        speak("Tell me how can I help you now?")
        statement = takeCommand()
        #if statement==0:
        #    continue

        if 'hi' in statement:
            speak("hi Mr.Farshbaf tell your password")
            print("hi Mr.Farshbaf tell your password")
            statement = takeCommand()

            if '1379' in statement:
                speak("All systems are ready for you sir, e-one is under your control")
                print("All systems are ready for you sir, e-one is under your control")
                statement = takeCommand()
                break

        
        
        
        #if statement==0:
           # continue

        if "good bye" in statement or "ok bye" in statement or "stop" in statement:
            speak('your personal assistant e-one is shutting down,Good bye')
            print('your personal assistant e-one is shutting down,Good bye')
            break