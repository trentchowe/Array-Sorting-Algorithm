#include <iostream>
#include <fstream>
#include <string>
using namespace std;



//define class
class SortableArray
{
	private:
			double *arrayStart = nullptr;
			unsigned int numElements;
	public:
			//constructor
			SortableArray();
			//second constructor
			SortableArray(unsigned int);
			//destructor
			~SortableArray();
			//return pointer to data array
			double* getPointer() const;
			//return number of elements
			unsigned int getElements() const;
			//fills data array with zeros
			void fillArrayZeros();
			//writes header info and array to text file
			void writeToFile(ofstream &outFile, bool);
			//merges two sub-arrays into a second array
			void mergeSubArrays(double *preMergeArray,double *postMergeArray, unsigned int, unsigned int, unsigned int);
			//splits two arrays
			void splitNoRecursive(double *preSplitArray, double *postSplitArray, unsigned int, unsigned int);
			//implements complete merge sort algorithm
			void completeMergeSortAlgorithm();
};

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

//prototype function outside of class
SortableArray readArray(ifstream &inFile);

int main()
{
	//define an instance of class
	SortableArray* arrayOne = new SortableArray;
	//open file
	//ofstream outFile("ece0301_merge_sort_results.txt");
	//arrayOne->writeToFile(outFile);
	//outFile.close();
	//open file to read from
	ifstream inFile("ece_0301_unsorted_array.txt");
	//define new object of class and set equal to function
	SortableArray arrayTwo = readArray(inFile);
	//reopen output file
	ofstream outFileTwo("ece0301_merge_sort_results.txt");
	//cal; file-writing function to write original array to output file
	bool header = false;
	arrayTwo.writeToFile(outFileTwo, header);
	//define second object from class with the same number of elements as the first object
	//unsigned int numElementsMain = arrayTwo.getElements();
	//SortableArray arrayThree(numElementsMain);
	//call complete merge sort algorithm
	arrayTwo.completeMergeSortAlgorithm();
	//use first array to call function to merge elements from first into second
	//unsigned int startSecondArray = 5;
	//unsigned int startFirstArray = 0;
	//unsigned int afterEndOfSecond = arrayTwo.getElements();
	//call split function
	//arrayTwo.splitNoRecursive(arrayTwo.getPointer(), arrayThree.getPointer(), startFirstArray, afterEndOfSecond);
	//call file writing function to write merged array to output file
	header = true;
	arrayTwo.writeToFile(outFileTwo, header);
	inFile.close();
	outFileTwo.close();
}

SortableArray readArray(ifstream& inFile)
{
	string one, two;
	//check if first line matches template
	getline(inFile, one);
	if(one.substr(0,9)!= "LENGTH = ")
	{
		cout<<"ERROR! Invalid input file header."<<endl;
		exit(EXIT_FAILURE);
	}
	//extract length number
	int sizeFirstLine = one.length();
	unsigned int length = stoi(one.substr(9,sizeFirstLine-9));
	SortableArray a(length);
	double *ptr = a.getPointer();
	for (int i = 0; i<length; i++)
	{
		string line;
		getline(inFile,line);
		double num = stod(line);
		*(ptr + i) = num;
	}
	return a;
}

