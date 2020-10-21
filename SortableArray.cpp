#include "SortableArray.h"

SortableArray::SortableArray()
{
	numElements = 10;
	arrayStart = new double[numElements];
	//initialize all array elements to 0
	fillArrayZeros();
}

SortableArray::SortableArray(unsigned int num)
{
	numElements = num;
	arrayStart = new double[numElements];
	fillArrayZeros();
}

SortableArray::~SortableArray()
{
	delete arrayStart;
}

double* SortableArray::getPointer() const
{
	return(arrayStart);
}

unsigned int SortableArray::getElements() const
{
	return(numElements);
}

void SortableArray::fillArrayZeros()
{
	for (int i=0; i<numElements; i++)
		{
			*(arrayStart + i) = 0;
		}
}

void SortableArray::writeToFile(ofstream& outFile, bool header)
{
	if(header==false)
	{
	outFile << "ECE 0301 - Sorting Arrays"<< endl << "Unsorted Array:" << endl;
	}
	else
	{
		outFile<<"Sorted Array:"<<endl;
	}
	for (int i=0; i<numElements; i++)
		{
			outFile << *(arrayStart + i) << endl;
		}
}

void SortableArray::mergeSubArrays(double* preMergeArray, double* postMergeArray, unsigned int startOfSecondArray, unsigned int startOfFirstArray, unsigned int afterEndOfSecond)
{
	//initialize all pointers
	double* blackPtr = (preMergeArray+startOfFirstArray), *grayPtr = (preMergeArray+startOfSecondArray), *redPtr = (preMergeArray + startOfSecondArray), *bluePtr = (preMergeArray+afterEndOfSecond), *greenPtr = (postMergeArray+startOfFirstArray);
	//do this until one of the arrays are done
	while(blackPtr < redPtr && grayPtr < bluePtr)
		{
			//check which element is larger in premerge array and put it in the postmerge array
			if(*blackPtr < *grayPtr)
			{
				*greenPtr = *blackPtr;
				blackPtr++;
			}
			else
			{
				*greenPtr = *grayPtr;
				grayPtr++;
			}
			//go to next element in postmerge array
			greenPtr++;
		}
	//finish copying the remaining elements of whichever array has leftovers
	while(blackPtr < redPtr)
	{
		*greenPtr = *blackPtr;
		blackPtr++;
		greenPtr++;
	}
	while(grayPtr < bluePtr)
	{
		*greenPtr = *grayPtr;
		grayPtr++;
		greenPtr++;
	}
	
}

void SortableArray::splitNoRecursive(double* preSplitArray, double* postSplitArray, unsigned int startOfFirstArray, unsigned int afterEndOfSecondArray)
{
	//if second parameter is one more than first, return to calling function
	if(afterEndOfSecondArray == (startOfFirstArray+1))
	{
		return;
	}
	//calculate midpoint index
	unsigned int midpointIndex = (startOfFirstArray + afterEndOfSecondArray) / 2;
	//recursively call split function on first half of array
	splitNoRecursive(postSplitArray, preSplitArray, startOfFirstArray, midpointIndex);
	//recursively call split function on second half of array
	splitNoRecursive(postSplitArray, preSplitArray, midpointIndex, afterEndOfSecondArray);
	//call merge function
	mergeSubArrays(preSplitArray, postSplitArray, midpointIndex, startOfFirstArray, afterEndOfSecondArray);
}

void SortableArray::completeMergeSortAlgorithm()
{
	//define pointer to double, assign it to data array pointer
	double* dataArrayPtr = getPointer();
	//define new object with same number of elements as calling object
	SortableArray workingArray(numElements);
	//define pointer to working array
	double* workingArrayPtr = workingArray.getPointer();
	//copy data from the calling object to the working array
	for (int i = 0; i<numElements; i++)
		{
			*(workingArrayPtr + i) = *(dataArrayPtr+i);
		}
	//call split function
	splitNoRecursive(workingArrayPtr, dataArrayPtr, 0, numElements);
}

void SortableArray::fillArrayRandom()
{
	double* dataArray = getPointer();
	for (int i=0; i<numElements; i++)
		{
			double randNumHolder = static_cast<double>(rand()) / RAND_MAX;
			double randElement = 2*randNumHolder -1;
			*(dataArray + i) = randElement;
		}
}
