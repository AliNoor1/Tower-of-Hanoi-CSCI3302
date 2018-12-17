#!/usr/bin/env python

import math 
import numpy as np
import cv2
import matplotlib.pyplot as plt
from matplotlib.colors import hsv_to_rgb
from matplotlib import cm
from matplotlib import colors
solution = []
status = []
store= []

def colorError(size, o1, o2, o3):
	if (o1 - o2 > abs(size/100)) or (o1 - o3 > abs(size/100)):
		print("WARNING! Color ambiguity. Results may vary.")

def visionHelper(image1, color1, color2):
	#create mask, gather coordinates of non-black pixels
	mask = cv2.inRange(image1, color1, color2)
	indices = np.where(mask!=[0])
	coordinates = zip(indices[0], indices[1])
	
	#define size
	height, width, channels = image1.shape
	halfheight = height/2
	halfwidth = width/2
	
	#declare counters
	oneCount = 0
	twoCount = 0
	threeCount = 0
	
	#count non-black pixels in each mask, depending on location
	for eachCoord in coordinates:
		if eachCoord[0] < halfheight:
			oneCount = oneCount+1
		elif eachCoord[1] <= halfwidth:
			twoCount = twoCount+1
		elif eachCoord[1] > halfwidth:
			threeCount = threeCount+1
		else:
			pass
	peg = max(oneCount, twoCount, threeCount)
	#are results too close to call?
	colorError((height*width), oneCount, twoCount, threeCount)
	if(peg==oneCount):
		return(1)
	elif(peg==twoCount):
		return(2)
	elif(peg==threeCount):
		return(3)
	else:
		return(4)

def vision():
	flags =[i for i in dir(cv2) if i.startswith('COLOR_')]

	#image processing

	#IMAGE FILENAME
	imageName = "testPic1.jpg"

	pic = cv2.imread(imageName)
	pic = cv2.cvtColor(pic, cv2.COLOR_BGR2RGB)
	hsv_pic = cv2.cvtColor(pic, cv2.COLOR_RGB2HSV)

	#~~~DEFINE COLOR RANGES - HSV/HSB~~~

	pink1 = (125,130,130)
	pink2 = (200,255,255)
	block1 = visionHelper(hsv_pic, pink1, pink2)

	blue1 = (100,50,50)
	blue2 = (120,255,255)
	block2 = visionHelper(hsv_pic, blue1, blue2)

	green1 = (60,40,40)
	green2 = (80,255,255)
	block3 = visionHelper(hsv_pic, green1, green2)

	red1 = (177,60,60)
	red2 = (250,255,200)
	block4 = visionHelper(hsv_pic, red1, red2)

	yellow1 = (20,60,60)
	yellow2 = (40,255,255)
	block5 = visionHelper(hsv_pic, yellow1, yellow2)
	
	#Associate blocks to pegs, in particular order
	blocks = [("1", block1), ("2", block2), ("3", block3), ("4", block4), ("5", block5)]
	peg1 = []
	peg2 = []
	peg3 = []
	for eachBlock in blocks:
		if eachBlock[1] == 1:
			peg1.append(eachBlock[0])
		elif eachBlock[1] == 2:
			peg2.append(eachBlock[0])
		elif eachBlock[1] == 3:
			peg3.append(eachBlock[0])
		else:
			print("error with assigning blocks to pegs")#'see' visionHelper function
	print(peg1, peg2, peg3)
	return([peg1, peg2, peg3])

def display(index):
	print("First Move:")
	output = ""
	for i in range(index,len(solution)):
		#string = "Move disk " + str(solution[i][0]) + " from " + str(solution[i][1]) + " to " + str(solution[i][2])
		#string = "[" + str(solution[i][0]) + ", " + str(solution[i][1]) + ", " + str(solution[i][2]) + "]"
		
		string = str(solution[i][0]) + " " + str(solution[i][1]) + " " + str(solution[i][2])
		print(string)
		output = output + string + "\n"
		#print(store[i+1])
	outfile = open("commands.txt", "w")
	outfile.write(output)
	outfile.close()
def updataStatus():
	global status
	global store
	index = 0
	store[index] = status
	index += 1 
	for i in range(len(solution)):
	  plate = solution[i][0] 
	  pre_state = solution[i][1] - 1
	  to_state = solution[i][2] - 1
	  if plate >= 0 and pre_state >= 0 and to_state >= 0:
	  	status[pre_state].remove(plate)
	  	status[to_state].append(plate)
	  	status[to_state].sort()	
	  	for m in range(3):
	  		for j in range(len(status[m])):
	  			store[index][m].append(status[m][j])
	  	index += 1	  	
def looking_For_Step(temp):
	temp[0].sort()
	temp[1].sort()
	temp[2].sort()
	check = -1
	for i in range(len(store)):
		if temp[0] in store[i] and temp[1] in store[i] and temp[2] in store[i] and check == -1:
			check = i 	
	return check	
def updataSolution(n,A,C):
    global solution
    solution.append((n, A, C))
def hannoi(n, A, B, C):
	if n == 0 :
		return
	else:
		hannoi(n-1, A,C,B)
		updataSolution(n,A,C)
		hannoi(n-1,B,A,C)
def main():
   global solution
   global status
   global store
   n = 5
   solution = []
   status = [[i+1 for i in range(n)],[],[]]
   store =  [ [ [], [], [] ] for i in range(n*n*n)]
   hannoi(n,1,2,3)  # TM: calculate the hannoi, the answer is in solution ( global matrix)
   updataStatus()   # TM: converte solution to status ( global step * 3 * n )
   index = looking_For_Step(vision()) # TM: looking for given status
   display(index)
if __name__ == '__main__':
	main()
