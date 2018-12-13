#include <iostream>
#include <cstdio>
using namespace std;
string solution[100][3];
string status[100][3];
string store[100][3];
int index = 0;

int display(index)
{
	for i = index; i < solution.len()in range(index,len(solution)):
		string = "Move disk " + str(solution[i][0]) + " from " + str(solution[i][1]) + " to " + str(solution[i][2])
		printf(string);
		printf(store[i]);
		return 0;
}

int arrayLen(myArray)
{
	size_t size = sizeof(myArray) / sizeof(myArray[0]);
	return int(size);
}

int updateStatus()
{
	solSize = arrayLen(solution);
	for(i = 0; i < solSize; i++;)
	{
	string plate = solution[i][0];
	  pre_state = solution[i][1] - 1;
	  to_state = solution[i][2] - 1;
	  if plate >= 0 and pre_state >= 0 and to_state >= 0{
	  	status[pre_state].remove(plate);
	  	status[to_state].append(plate);
	  	status[to_state].sort();
	  	for m in range(3):
	  		for j in range(len(status[m])):
	  			store[index][m].append(status[m][j]);
	  	index = index + 1;
	  	return 0;
	}

}
	
void looking_For_Step(temp){
	temp[0].sort()
	temp[1].sort()
	temp[2].sort()
	for i in range(len(store)):
		if temp[0] in store[i] and temp[1] in store[i] and temp[2] in store[i]:
			index = i
	if index >= 0:
		print(i-1)
		return i-1
}
void updataSolution(n,A,C){
    global solution
    solution.append((n, A, C))
}
void hannoi(n, A, B, C){
	global solution
	global numSolution 
	if n == 0 :
		return
	else:
		hannoi(n-1, A,C,B)
		updataSolution(n,A,C)
		hannoi(n-1,B,A,C)
}
int main(solution, status, store)
{
   n = 5
   solution = []
   status = [[i+1 for i in range(n)],[],[]]
   store =  [ [ [], [], [] ] for i in range(n*n)]
   hannoi(n,1,2,3)  // TM: calculate the hannoi, the answer is in solution ( global matrix)
   updataStatus()   // TM: converte solution to status ( global step * 3 * n )
   index = looking_For_Step([[],[1],[2]]) // TM: looking for given status
   display(index)
}
 
main(solution, status, store);
