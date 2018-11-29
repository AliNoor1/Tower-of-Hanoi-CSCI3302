//
//  main.cpp
//  Final Project
//
//  Created by Tianyi ma on 11/7/18.
//  Copyright © 2018 Tianyi ma. All rights reserved.
//


#include <iostream>
#include <cstdio>
using namespace std;
string solution[100][3];
int num = 0;
void display()
{
    for(int i = 0; i < 100; i++)
    {
        if(solution[i][0] != "" )
        {
            cout << "Move disk " << solution[i][0] << " from " << solution[i][1] << " to " << solution[i][2] << endl;
        }
    }
}

void hannoi (int n, char from, char buffer, char to)
{
    if (n == 0)
        return;
    hannoi (n - 1, from, to, buffer);
    solution[num][0] = to_string(n);
    solution[num][1] = from;
    solution[num][2] = to;
    num++;
    //cout << "Move disk " << n << " from " << from << " to " << to << endl;
    hannoi (n - 1, buffer, from, to);
}

int main()
{
    int n;
    cout<<"Please enter number of Hanoi"<<endl;
    cin >> n;
    hannoi (n, 'A', 'B', 'C');
    display();
    return 0;
}
