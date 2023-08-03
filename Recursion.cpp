#include <iostream>
#include<vector>
using namespace std;

int reverseDigit(int num,int & power)
{
	
	if (num < 10)
		return num;
	else
	{
		int result;
		result = num % 10;
		result = result * (pow(10, power - 1));
		power--;
		result += reverseDigit(num / 10,power);
		return result;
	}
}
void evenOdd(int *arr, int size)
{
	if (!size)
		return;
	else
	{
		if (arr[size - 1] % 2 == 0)
		{
			for (int i = 1; i < size; i++)
			{
				if (arr[size - 1 - i] % 2 != 0)
				{
					int temp = arr[size - 1];
					arr[size - 1] = arr[size - 1 - i];
					arr[size - i - 1] = temp;
					break;
				}
			}
		}
		evenOdd(arr, size-1);
	}
}
void result(int* arr)
{
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;
	arr[5] = 6;
	arr[6] = 7;
	arr[7] = 8;
}
bool checkSum(int *arr,int size)
{
	if(size<=1)
		return false;
	else
	{
		if (!checkSum(arr, size - 1))
		{
			for (int i = size - 2; i >= 1; i--)
				for (int j = i - 1; j >= 0; j--)
					if (arr[size - 1] == arr[i] + arr[j])
						return true;
			return false;
		}
		return true;
	}
}
int countPath(int x, int y)
{
	if (x == 0 && y == 0)
		return 1;
	else if (x < 0 || y < 0)
		return 0;
	else
	{
		int xpath=0,ypath=0;
		xpath = countPath(x - 1, y);
		ypath = countPath(x, y - 1);
		return xpath + ypath;
	}
}
void merge(int* arr, int high, int low, int mid)
{
	int size = (high - low)+1;
	int* temp = new int[size];
	int k = 0;
	int i = low;
	int j = mid + 1;
	while(i<=mid&&j<=high)
	{	
		if (arr[i] > arr[j])
		{
			temp[k] = arr[j];
			j++;
		}
		else
		{
			temp[k] = arr[i];
			i++;
		}
		k++;
	}
	if (i > mid)
	{
		while (j <= high)
		{
			temp[k] = arr[j];
			k++;
			j++;
		}
	}
	else if (j > high)
	{
		while (i <= mid)
		{
			temp[k] = arr[i];
			k++;
			i++;
		}
	}
	i = low;
	k = 0;
	while (k < size)
	{
		arr[i] = temp[k];
		i++;
		k++;
	}

}
void mergeSort(int *arr,int high,int low)
{
	if (low >= high)
		return;
	else
	{
		int mid = (high + low) / 2;
		mergeSort(arr, high, mid+1);
		mergeSort(arr, mid, low);
		merge(arr, high, low, mid);
		return;
	}
}
int factorial(int n)
{
	if (n == 0)
		return 1;
	else
		return factorial(n - 1) * n;
}
int combination(int n, int r)
{
	return factorial(n) / (factorial(r) * factorial(n - r));
}
vector<int> subset;
void makesubset(int a[], int size, int index,int k,int **matrix,int &r) 
{
	if (index == size) 
	{
		// print the subset
		if (subset.size() == k)
		{
			for (int i = 0; i < subset.size(); i++) {
				matrix[r][i] = subset[i];
			}
			r++;
		}
	}
	else 
	{
		subset.push_back(a[index]);
		makesubset(a, size, index + 1,k,matrix,r);
		subset.pop_back();
		makesubset(a, size, index + 1,k,matrix,r);
	}
}
int**subSets(int arr[], int size, int k)
{
	int l=0;
	int row = combination(size, k);
	int** matrix = new int* [row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[k];
	}
	makesubset(arr, size,0, k,matrix, l);
	return matrix;
}
//bool spaceAvailale(int chess[][8], int row, int col)
//{
//	int i, j;
//	for (i = 0; i < col; i++)
//		if (chess[row][i])
//			return false;
//	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
//		if (chess[i][j])
//			return false;
//	for (i = row, j = col; j >= 0 && i < 8; i++, j--)
//		if (chess[i][j])
//			return false;
//	return true;
//}
void eightQueen(int *arr,int chess[][8], int size, int i)
{
		result(arr);
}
void makechess(int arr[][8], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			arr[i][j] = 0;
		}
	}
}
int* placeQueen()
{
	int* arr = new int[8];
	int chess[8][8];
	makechess(chess, 8);
	eightQueen(arr,chess, 8, 0);
	return arr;
}
int main()
{
	int option=-1;		//Option variable to select which problem to run
	int size;			//Size of Array to be used in many programs
	int* arr;			//arr to be used in many programs
	int k;				//Variable For Subset i.e size of subsets to be returned
	int high, low;		//Variables For Merge Sort
	int num, power;		//Variables For Reverse Digit, number and Power
	int x, y;			//Variables For Count PAth x and Y coordinates
	while (option)
	{
		cout << "Which Program Do you want to run:\n1)Reverse Digit\n2)Even Odd\n3)Check Sum\n4)Count Paths\n5)Merge Sort\n6)Subsets\n0 to Exit\n";
		cin >> option;
		system("cls");
		switch (option)
		{
		case 0:
			break;
		case 1:
			cout << "--------------Reverse Digits---------------\n";
			cout << "Enter Positive Number: ";
			cin >> num;
			cout << "Enter Number of Digits: ";
			cin >> power;
			(power < 0) ?power = -power : false;//Converts Power to Positive
			num=reverseDigit(num, power);
			cout << "Reversed Num: " << num<<endl;
			break;
		case 2:
			cout << "-----------------Even Odd------------------\n";
			cout << "-Program Separates Even & Odd int in Array-\n";
			cout << "Enter Size of Array: ";
			cin >> size;
			(size < 0) ? size = -size : false;//Converts Size to Positive
			arr = new int[size];
			cout << "Enter Data in Array: \n";
			for (int i = 0; i < size; i++)
			{
				cin >> arr[i];
			}
			evenOdd(arr, size);
			cout << "Array after even odd swap: ";
			for (int i = 0; i < size; i++)
			{
				cout << arr[i];
				(i != size - 1) ? cout << ", " : cout << endl;
			}
			delete[]arr;
			break;
		case 3:
			cout << "--------------Check Sum---------------\n";
			cout << "-Checks if any two element in array that make a thrid element of array-\n";
			cout << "Enter Size of Array: \n";
			cin >> size;
			(size < 0) ? size = -size : false;//Converts Size to Positive
			arr = new int[size];
			cout << "Enter Data in Array: ";
			for (int i = 0; i < size; i++)
			{
				cin >> arr[i];
			}
			if (checkSum(arr, size))
				cout << "\nExists\n" << endl;
			else
				cout << "\nDoesnt Exists\n" << endl;
			delete[]arr;
			break;
		case 4:
			cout << "--------Count Path From (0,0) in graph---------\n";
			cout << "Enter X coordinate: ";
			cin >> x;
			cout << "Enter Y coordinate: ";
			cin >> y;
			cout<<countPath(x, y)<<" Paths Found\n";
			break;
		case 5:
			cout << "--------------Merge Sort---------------\n";
			cout << "Enter Size: ";
			cin >> size;
			(size < 0) ? size = -size : false;//Converts Size to Positive
			arr = new int[size];
			cout << "Enter Data in Array: ";
			for (int i = 0; i < size; i++)
			{
				cin >> arr[i];
			}
			high = size - 1;
			low = 0;
			mergeSort(arr, high, low);
			cout << "Array after Merge Sort: ";
			for (int i = 0; i < size; i++)
			{
				cout << arr[i];
				(i != size - 1) ? cout << ", " : cout << endl;
			}
			delete []arr;
			break;
		case 6:
			cout << "--------------Find Subsets---------------\n";
			int** result;
			cout << "Enter Size of Array: ";
			cin >> size;
			(size < 0) ? size = -size : false;//Converts Size to Positive
			arr = new int[size];
			cout << "Enter Data in Array: ";
			for (int i = 0; i < size; i++)
			{
				cin >> arr[i];
			}
			cout << "Enter k(size of Subset): ";
			cin >> k;
			result=subSets(arr, size,k);
			cout << "Subsets\n";
			for (int i = 0; i < combination(size, k); i++)
			{
				for (int j = 0; j < k; j++)
				{
					cout << result[i][j];
					(j != k - 1) ? cout << ", " : cout << endl;
				}
			}
			break;
		default:
			cout << "Invalid Input\n";
		}
		cout << "Do you wish to Run another program?\n 0 for No\n 1 for yes\n";
		cin >> option;
	}
}