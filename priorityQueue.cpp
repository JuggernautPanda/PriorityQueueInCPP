/*
 * priorityQueue.cpp
 * 
 * Copyright 2021 raja <raja@raja-Inspiron-N5110>
 * 
 * This queueogram is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This queueogram is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this queueogram; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "priorityQueue.h"
using namespace std;

// Step 1 : As per the requirement, we need a storage class with two fields - 
// Hence we can make use of the structures concept to create elements which act as Input
struct InPut {
	int priority;
	string value;
};

// Pointer to the last lastIndex
int lastIndex = -1;

// Store the element of a queue priority queue
InPut priorityQ[100];

class Priority_Q {
	
	public:
		Priority_Q() 
		{
        }
        
    // Function to insert a new element into priority queue
	void insertToQueue(int priority ,string value)
	{
		// Increase the lastIndex
		lastIndex++;

		// Insert the element into the queue
		priorityQ[lastIndex].value = value;
		priorityQ[lastIndex].priority = priority;
	}

	// Function to check the element with maxium priority
	int getmaxpriority(void)
	{
		int maxpriority = INT_MIN;
		int ind = -1;

		// Check for the element with maximum priority
		for (int i = 0; i <= lastIndex; i++) {

			// Handling edge case of threads with equal priorities : Based on Accept / Decline.
			// precedence is given to values of Accept.
			if (maxpriority == priorityQ[i].priority && ind > -1 && priorityQ[ind].value > priorityQ[i].value)
			{
				maxpriority = priorityQ[i].priority;
				ind = i;
			}
			else if (maxpriority < priorityQ[i].priority) 
			{
				maxpriority = priorityQ[i].priority;
				ind = i;
			}
		}

		// Return position of the element
		return ind;
	}

	// Function to remove the element with
	// the highest priority
	void deleteFromQueue(void)
	{
		// Find the position of the element
		// with highest priority
		int ind = getmaxpriority();

		// Shift the element one lastIndex before
		// from the position of the element
		// with highest queueiortity is found
		for (int i = ind; i < lastIndex; i++) {
			priorityQ[i] = priorityQ[i + 1];
		}

		// Decrease the lastIndex of the
		// priority queue by one
		lastIndex--;
	}

	void loadInPut(void)
	{
		//You can hard code a few input sets in your code.
		insertToQueue(2,"Accepted");
		//insertToQueue(2,"Denied");
		insertToQueue(4,"Denied");
		insertToQueue(4,"Accepted"); // creating an edge case of having the same priority
		insertToQueue(3,"Accepted");
	}

	void outFunc1(int ind)
	{
		cout << priorityQ[ind].priority;
		cout << ", Access is granted.\n";
		//cout << priorityQ[ind].value << endl;	
	}

	void outFunc2(int ind)
	{
		cout << priorityQ[ind].priority;
		cout << ", Access is denied.\n";
		//cout << priorityQ[ind].value << endl;
	}
};

int main(int argc, char **argv)
{
	// Instantiate an object p of class Priority_Q
	Priority_Q p; 
	// Step 2 : Load the hard coded values.
	p.loadInPut();
	
	// We shall use this to loop in the elements.
	int li = lastIndex; 
	
	/*
	 *  or use string input using getline()
		getline(cin,str); 
		For simplicity, use the hardcoded values.
	* 
	*/
	
	
	// Stores the top element at the moment
	int ind = p.getmaxpriority();
	
	while(li>=0) // Loop until you navigate through the entire queue
	{
		if((priorityQ[ind].value.compare("Accepted")) == 0)
		{
			p.outFunc1(ind);
		}
		else
		{
			p.outFunc2(ind);
		}
		p.deleteFromQueue();
		ind = p.getmaxpriority();
		li--;
	}
	return 0;
}

