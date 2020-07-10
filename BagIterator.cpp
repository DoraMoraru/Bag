#include <exception>
#include <iostream>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c)
{
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	position = 0;
	frequency = bag.elements[0];
	index = 0;
}

void BagIterator::first() {
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	position = 0;
	frequency = bag.elements[0];
	index = 0;
}


void BagIterator::next() {
	/*
	BestCase= θ(1)
	AverageCase=WorstCase=θ(elements)
*/
	if (!valid()) {
		throw exception{ "" };
	}
	else {
		index++;
		frequency--;
		if (frequency <= 0) {
			position++;
			while (bag.elements[position] == 0 && position < bag.bagLength)
			{
				position++;
			}
			frequency = bag.elements[position];
		}
	}
}


bool BagIterator::valid() const {
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/

	return bag.bagSize > index&& index >= 0;
}

TElem BagIterator::getCurrent() const
{
	/*
	BestCase=AverageCase=WorstCase=θ(1)
	*/
	if (!valid()) {
		throw exception{ "" };
	}
	else
	{
		return bag.minElem + position;
	}
}