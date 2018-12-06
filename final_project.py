import math 
import numpy as np
solution = []
status = []
store= []
def display():
	for i in range(len(solution)):
		string = "Move disk " + str(solution[i][0]) + " from " + str(solution[i][1]) + " to " + str(solution[i][2])
		print(string)
		print(store[i])
def updataStatus():
	global status
	global store
	index = 0
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
def updataSolution(n,A,C):
    global solution
    solution.append((n, A, C))
def hannoi(n, A, B, C):
	global solution
	global numSolution 
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
   n = 2            # TM: number of obstacal we need.
   solution = []
   status = [[i+1 for i in range(n)],[],[]]
   store =  [ [ [], [], [] ] for i in range(n*n)]
   hannoi(n,1,2,3)  # TM: calculate the hannoi, the answer is in solution ( global matrix)
   updataStatus()   # TM: converte solution to status ( global step * 3 * n )
   display()
   
if __name__ == '__main__':
	main()