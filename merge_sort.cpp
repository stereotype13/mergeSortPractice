#include <iostream>
#include <limits>
#include <vector>

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
	
	//test mergeSort
	vector<int> unsorted = {7, 1, 5, 8, 9, 2, 5, 3, 7, 14, 56, 1, 8};
	vector<int> sorted(unsorted.size());
	mergeSort(unsorted, sorted);
	for (const auto& x : sorted) {
		cout << x << ", ";
	}
	cout << endl;

	int searchTerm = 7;
	cout << searchTerm << " was found at index " << binarySearch(searchTerm, sorted) << endl;
	return 0;
}