#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;



//define class
class SortableArray
{
	private:
			double *arrayStart = nullptr;
			unsigned int numElements;
			//merges two sub-arrays into a second array
			void mergeSubArrays(double *preMergeArray,double *postMergeArray, unsigned int, unsigned int, unsigned int);
			//splits two arrays
			void splitNoRecursive(double *preSplitArray, double *postSplitArray, unsigned int, unsigned int);
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
			//implements complete merge sort algorithm
			void completeMergeSortAlgorithm();
			//fills data array with pseudorandom numbers
			void fillArrayRandom();
};
