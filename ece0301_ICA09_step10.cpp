#include "SortableArray.cpp"

int main()
{
			//define an instance of class
			//SortableArray* arrayOne = new SortableArray;
			//open file
			//ofstream outFile("ece0301_merge_sort_results.txt");
			//arrayOne->writeToFile(outFile);
			//outFile.close();
			//open file to read from
			//ifstream inFile("ece_0301_unsorted_array.txt");
			//define new object of class and set equal to function
			//SortableArray arrayTwo = readArray(inFile);
			//reopen output file
	//define object with 256 elements
	SortableArray randomArray(256);
	randomArray.fillArrayRandom();
	ofstream outFileTwo("ece0301_merge_sort_results.txt");
	//cal; file-writing function to write original array to output file
	bool header = false;
	randomArray.writeToFile(outFileTwo, header);
	//define second object from class with the same number of elements as the first object
	//unsigned int numElementsMain = arrayTwo.getElements();
	//SortableArray arrayThree(numElementsMain);
	//call complete merge sort algorithm
	randomArray.completeMergeSortAlgorithm();
	//use first array to call function to merge elements from first into second
	//unsigned int startSecondArray = 5;
	//unsigned int startFirstArray = 0;
	//unsigned int afterEndOfSecond = arrayTwo.getElements();
	//call split function
	//arrayTwo.splitNoRecursive(arrayTwo.getPointer(), arrayThree.getPointer(), startFirstArray, afterEndOfSecond);
	//call file writing function to write merged array to output file
	header = true;
	randomArray.writeToFile(outFileTwo, header);
	//inFile.close();
	outFileTwo.close();
}
