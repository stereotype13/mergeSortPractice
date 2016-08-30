#include <iostream>
#include <limits>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;

#define INF numeric_limits<int>::max()


void merge(const vector<int>& right, const vector<int>& left, vector<int>& output) {
	int lengthOfRight = right.size();
	int lengthOfLeft = left.size();

	int rightIndex = 0, leftIndex = 0, outputIndex = 0;

	vector<int> tempRight = right, tempLeft = left;
	tempRight.push_back(INF);
	tempLeft.push_back(INF);

	while ( rightIndex < lengthOfRight || leftIndex < lengthOfLeft ) {
		if ( tempRight[rightIndex] <= tempLeft[leftIndex] ) {
			output[outputIndex] = tempRight[rightIndex];
			++rightIndex;
			++outputIndex;
		}
		else {
			output[outputIndex] = tempLeft[leftIndex];
			++leftIndex;
			++outputIndex;
		}
	}
}

void mergeSort( const vector<int>& input, vector<int>& output ) {
	int inputVectorSize = input.size();

	if (inputVectorSize == 1) {
		output = input;
		return;
	}

	if (inputVectorSize == 2) {
		merge(vector<int>{input[0]}, vector<int>{input[1]}, output);
		return;
	}

	vector<int> right, left;
	for ( int i = 0; i < inputVectorSize / 2; ++i ) {
		right.push_back( input[i] );
	}
	vector<int> outputRight( right.size() );

	for ( int i = inputVectorSize / 2; i < inputVectorSize; ++i ) {
		left.push_back( input[i] );
	}
	vector<int> outputLeft( left.size() );

	mergeSort(right, outputRight);
	mergeSort(left, outputLeft);

	merge(outputRight, outputLeft, output);
}

int binarySearch( int searchTerm, const vector<int>& vec ) {
	int left = 0, right = vec.size() - 1;
	
	while ( left < right ) {
		if ( vec[left] == searchTerm )
			return left;

		if (vec[right] == searchTerm)
			return right;

		int midPoint = (left + right) >> 1;
		if ( searchTerm == vec[midPoint] ) {
			return midPoint;
		}
		else if (searchTerm < vec[midPoint]) {
			right = --midPoint;
		}
		else {
			left = ++midPoint;
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	

	const int n = 10000;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, n);
	vector<int> unsorted;
	

	//fill unsorted with random integers
	for (int i = 0; i < n - 1; ++i) {
		unsorted.push_back( distribution(generator) );
	}

	vector<int> sorted( unsorted.size() );


	chrono::time_point<std::chrono::system_clock> start, end;
	cout << "Sorting..." << endl;

	start = chrono::system_clock::now();
	mergeSort( unsorted, sorted );
	end = chrono::system_clock::now();

	chrono::duration<double> elapsedTimeInSeconds = end - start;

	cout << "Elapsed time: " << elapsedTimeInSeconds.count() << "s\n";


	cout << "7862 was found at position " << binarySearch( 7862, sorted ) << "." << endl;
	
	
	return 0;
}