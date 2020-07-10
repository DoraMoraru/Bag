#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <math.h>
using namespace std;


Bag::Bag() {
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	capacity = 3;
	bagLength = 0;
	bagSize = 0;
	elements = new TElem[capacity];
	for (int i = 0; i < capacity; ++i)
		elements[i] = 0;
}


void Bag::add(TElem elem) {
	/*
	Best Case = θ(1) :For just one element that will be added
	Average Case: θ(elements)
	Worst Case: θ(elements^2): When the element < minElement

	*/
	if (bagLength == capacity)
	{
		capacity = capacity + 5;
		TElem* newElements = new TElem[this->capacity];

		for (int index = 0; index < this->bagLength; ++index)
		{
			newElements[index] = this->elements[index];
		}
		delete[] this->elements;

		elements = newElements;
	} // Complexity : θ(length)

	if (bagSize == 0) {
		minElem = elem;
		maxElem = elem;

		elements[0] = 1;

		bagLength++;
		bagSize++;
	}// Complexity : θ(1)

	else if (elem > maxElem)
	{
		int minDifference = elem - minElem;
		int maxDifference = elem - maxElem;
		maxElem = elem;

		if (maxElem - minElem + 1 >= capacity)
		{
			capacity = minDifference + 5;
			TElem* newElements = new TElem[capacity];

			for (int index = 0; index < this->bagLength; ++index)
			{
				newElements[index] = elements[index];
			}

			delete[] this->elements;

			elements = newElements;
			for (int index = bagLength; index < capacity; ++index)
			{
				elements[index] = 0;
			}
		}//Complexity : θ(capacity)
		elements[minDifference] = 1;
		bagLength += maxDifference;
		bagSize++;
	}// Complexity : θ(capacity)

	else if (elem < minElem)
	{
		int difference = minElem - elem;
		minElem = elem;

		if (maxElem - minElem + 1 >= capacity)
		{
			capacity = maxElem - minElem + 5;
			TElem* newElements = new TElem[capacity];

			for (int index = 0; index < bagLength; ++index)
			{
				newElements[index] = elements[index];
			}

			delete[] this->elements;

			elements = newElements;
			for (int index = bagLength; index < capacity; ++index)
			{
				elements[index] = 0;
			}
		}//Complexity: θ(length ^ 2)
		for (int index = 0; index < difference; ++index)
		{
			bagLength++;
			for (int index2 = bagLength; index2 > 0; index2--)
			{
				elements[index2] = elements[index2 - 1];
			}
		}
		for (int index = 1; index < difference; ++index)
		{
			elements[index] = 0;
		}
		elements[0] = 1;
		bagSize++;
	}
	// Complexity : θ(length^2 + difference ^ 2)
	else
	{
		int difference;
		difference = elem - minElem;
		bagSize++;
		elements[difference]++;
	}// Complexity : θ(1)
}


bool Bag::remove(TElem elem) {

	/*
	Best Case = θ(1) : Element not found
	Average Case: θ(Elements)
	Worst Case: θ(Elements)
	*/

	if (search(elem) == false)
		return false;

	this->elements[elem - minElem]--;
	this->bagSize--;

	if (elem == minElem && this->elements[elem - minElem] == 0)
	{
		/*
		Best Case = θ(1) : its stops at the next element
		Average Case: θ(length)
		Worst Case: θ(length^2)
		*/
		while (elements[0] == 0 && this->bagLength > 0)
		{
			for (int i = 0; i < this->bagLength; ++i)
			{
				this->elements[i] = this->elements[i + 1];
			}
			this->bagLength--;
			minElem++;
		}
	}
	else if (elem == maxElem && this->elements[elem - maxElem] == 0)
	{
		/*
		Best Case = θ(1) : its stops at the next element
		Average Case: θ(length)
		Worst Case: θ(length)
		*/
		while (elements[this->bagLength - 1] == 0 && this->bagLength > 0)
		{
			this->bagLength--;
			maxElem--;
		}
	}

	return true;
}


bool Bag::search(TElem elem) const {
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	if (elem < minElem || elem > maxElem)
		return false;
	int difference = elem - minElem;
	return this->elements[difference] != 0;
}

int Bag::nrOccurrences(TElem elem) const {
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	if (search(elem) == false)
		return 0;
	return this->elements[elem - minElem];
}


int Bag::size() const {
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	if (isEmpty() == true)
		return 0;
	return this->bagSize;
}

int Bag::uniqueCount()
{
	int counts = 0;

	if (isEmpty() == true)
		counts = 0;

	for (int index = 0; index < bagLength; ++index)
	{
		if (elements[index] == 1)
		{
			counts++;
		}
	}
	return counts;
}



bool Bag::isEmpty() const {
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	return bagSize == 0;
}

BagIterator Bag::iterator() const {
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	return BagIterator(*this);
}


Bag::~Bag() {
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	delete[] this->elements;
}

