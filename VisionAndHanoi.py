#!/usr/bin/env python3

import math 
import numpy as np
import cv2
solution = []
status = []
store= []
def vision():
	#put vision code here
	
	
	block1 = 2
	block2 = 2
	block3 = 2
	block4 = 1
	block5 = 3

	blocks = [("1", block1), ("2", block2), ("3", block3), ("4", block4), ("5", block5)]
	peg1 = []
	peg2 = []
	peg3 = []
	for eachBlock in blocks:#format blockData to pegs
		if eachBlock[1] == 1:
			peg1.append(eachBlock[0])
		elif eachBlock[1] == 2:
			peg2.append(eachBlock[0])
		elif eachBlock[1] == 3:
			peg3.append(eachBlock[0])
		else:
			print("error with assigning blocks to pegs")
	print(peg1, peg2, peg3)
	return([peg1, peg2, peg3])

def display(index):
	print("Initial status:", store[index])
	for i in range(index,len(solution)):
		#string = "Move disk " + str(solution[i][0]) + " from " + str(solution[i][1]) + " to " + str(solution[i][2])
		string = "[" + str(solution[i][0]) + ", " + str(solution[i][1]) + ", " + str(solution[i][2]) + "]"
		print(string)
		#print(store[i+1])
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
