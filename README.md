# Facerecognition
Simple application designed to immplement face detection as well recognitiion using open cv and c++. 

Detection happens using the camera. Faces detected can then be stored and later used to recognize the same user.

Important note about keys and what they do:
    * ESC:  This exits recognizer
    * ENTER:     This attempts to identify a new face  and add it to the databasee
    

##  Usage
Use premake to build
````
git clone ...
cd facerecognition
````
for xcode project workspace, run:
```
premake/premake5 xcode4
````
or for visual studio:
```
premake/premake5 vs2019
````
Note! Dialogue window has not been implemented in windows yet.
See how to use [premake](https://github.com/premake/premake-core/wiki/Using-Premake) if you are curious about it.
