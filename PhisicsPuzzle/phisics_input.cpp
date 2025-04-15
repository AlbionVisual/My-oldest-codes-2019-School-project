//Include files
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <queue>

//Set namespace
using namespace std;

//Naming funcs
void readFormulsFile(string src);

//Structures
struct saveValues
{
	double value;
	string measure;
	string designation;
};

struct formulasValue
{
	string designation;
	bool isInDirectRatio;
};

struct formuls
{
	string designation;
	int numOfDesignations;
	bool isSum;
	map<int, formulasValue> formulasValues;
};

//Declaring main vars
map<int, formuls> requiredFormuls;
int formulsCount = 0;

//Main function (there -----)
int main()
{
	readFormulsFile("formuls");
	struct forMainChain
	{
		int formulasIndex;
		int letterIndex = -1;
	};
	//-----Setting chain for formuls-----
	map<int, forMainChain> chain;
	int chainCount = 0;

	//-----input from file-----
	fstream inputfile("input.avp");

	//-----Getting num of formuls-----
	int n;
	cout << "How much input values: ";
	inputfile >> n;
	cout << n << endl;
	//cin >> n;
	inputfile.ignore();

	//-----Getting all formuls to string-----
	cout << "Type all input values like: <designation> = <value> <measure>:\n";
	map<int, string> input;
	for (int i = 0; i < n; i++)
	{
		getline(inputfile, input[i]);
		cout << input[i] << endl;
	}

	//-----Parting all formuls to structure-----
	map<int, saveValues> values;
	for (int i = 0; i < n; i++)
	{
		//-----Deleting all spaces-----
		while (input[i].find_first_of(' ') != string::npos)
			input[i].erase(input[i].find_first_of(' '), 1);

		//-----Finding = and get designstion to structure-----
		int tempNum = 0;
		for (int k = 0; k < input[i].length(); k++)
			if (input[i][k] == '=')
			{
				values[i].designation = input[i].substr(0, k);
				tempNum = k + 1;
			}
		//-----Getting value to structure-----
		int tempNum2;
		for (int k = tempNum; k < input[i].length(); k++)
		{
			if (!((input[i][k] <= '9' and input[i][k] >= '0') or input[i][k] == ' ' or input[i][k] == ',' or input[i][k] == '.'))
			{
				string tempStr = input[i].substr(tempNum, k - tempNum);
				values[i].value = stod(tempStr);
				tempNum2 = k;
				k = input[i].size();
			}
		}
		//-----Getting measure to structure-----
		values[i].measure = input[i].substr(tempNum2, input[i].size() - tempNum2);
	}

	//-----Get input formuls-----
	cout << "Write num of multiplying input formuls: ";
	int numOfInputFormuls = 0;
	inputfile >> numOfInputFormuls;
	cout << numOfInputFormuls << endl;
	for (int i = formulsCount; i < numOfInputFormuls + formulsCount; i++)
	{
		inputfile >> requiredFormuls[i].designation >> requiredFormuls[i].numOfDesignations;
		requiredFormuls[i].isSum = false;
		cout << requiredFormuls[i].designation << " " << requiredFormuls[i].numOfDesignations << " ";
		for (int k = 0; k < requiredFormuls[i].numOfDesignations; k++)
		{
			inputfile >> requiredFormuls[i].formulasValues[k].designation >> requiredFormuls[i].formulasValues[k].isInDirectRatio;
			cout << requiredFormuls[i].formulasValues[k].designation << " " << requiredFormuls[i].formulasValues[k].isInDirectRatio << " ";
		}
		cout << endl;
	}

	cout << "Write num of summary input formuls: ";
	numOfInputFormuls = 0;
	inputfile >> numOfInputFormuls;
	cout << numOfInputFormuls << endl;
	for (int i = formulsCount; i < numOfInputFormuls + formulsCount; i++)
	{
		inputfile >> requiredFormuls[i].designation >> requiredFormuls[i].numOfDesignations;
		requiredFormuls[i].isSum = true;
		cout << requiredFormuls[i].designation << " " << requiredFormuls[i].numOfDesignations << " ";
		for (int k = 0; k < requiredFormuls[i].numOfDesignations; k++)
		{
			inputfile >> requiredFormuls[i].formulasValues[k].designation >> requiredFormuls[i].formulasValues[k].isInDirectRatio;
			cout << requiredFormuls[i].formulasValues[k].designation << " " << requiredFormuls[i].formulasValues[k].isInDirectRatio << " ";
		}
		cout << endl;
	}

	//-----Get value user have to find------
	cout << "Type designation you would find: ";
	queue<string> undeclaredVars;
	undeclaredVars.push("EMPTY");
	inputfile >> undeclaredVars.back();
	cout << undeclaredVars.back() << endl;

	//-----Starting main cycle-----

	while (!undeclaredVars.empty())
	{
		//----Get formula test for reality-----
		struct tempStructfordependchain
		{
			int index;
			int quality;
		};
		map<int, tempStructfordependchain> tempChain;
		int index = 0;
		//-----Getting best quality formula-----
		for (int i = 0; i < requiredFormuls.size(); i++)
			if (requiredFormuls[i].designation == undeclaredVars.front())
			{
				//cout << "front " << undeclaredVars.front() << endl;
				tempChain[index].index = i;
				//cout << "index "<< i << endl;
				tempChain[index].quality = requiredFormuls[i].numOfDesignations;
				//cout << "Quality " << tempChain[index].quality << endl;

				for (int k = 0; k < requiredFormuls[i].numOfDesignations; k++)
				{
					int tempNum = 0;
					for (int n = 0; n < values.size(); n++)
					{
						if ((values[n].designation == requiredFormuls[i].formulasValues[k].designation))
						{
							tempNum++;
						}
					}
					tempChain[index].quality -= tempNum;
				}
				//cout << "Quality " << tempChain[index].quality << endl;

				index++;
			}
			else
			{
				for (int k = 0; k < requiredFormuls[i].numOfDesignations; k++)
					if (undeclaredVars.front() == requiredFormuls[i].formulasValues[k].designation)
					{
						int tempNum = 0;
						for (int n = 0; n < values.size(); n++)
						{
							if ((values[n].designation == requiredFormuls[i].formulasValues[k].designation && n != k))
							{
								tempNum++;
							}
							else if (n == k)
								if (requiredFormuls[i].designation == values[n].designation)
									tempNum++;
						}
						tempChain[index].quality -= tempNum;
					}
				index++;
			}

		int formulasIndex;
		for (int i = 0; i < tempChain.size(); i++)
		{
			int max = requiredFormuls[tempChain[i].index].numOfDesignations;
			//cout << "max pre " << max << endl;

			if (max > tempChain[i].quality)
			{
				max = tempChain[i].quality;
				formulasIndex = tempChain[i].index;
				//cout << "FormulInd " << formulasIndex << endl;
			}
			//cout << "Max after " << max << endl;
		}
		//{cout << formulasIndex<<endl;
		int letterIndex = -1;
		for (int i = 0; i < requiredFormuls[formulasIndex].numOfDesignations; i++)
		{
			if (requiredFormuls[formulasIndex].formulasValues[i].designation == values[formulasIndex].designation)
			{
				letterIndex = i;
			}
		}

		//-----Searching for underclared vars-----
		chain[chainCount].formulasIndex = formulasIndex;
		chain[chainCount].letterIndex = letterIndex;
		// cout << "Chain " << chain[chainCount] << endl;
		chainCount++;
		undeclaredVars.pop();
		for (int j = 0; j < requiredFormuls[formulasIndex].numOfDesignations; j++)
		{
			if (letterIndex == -1 or letterIndex != j)
			{
				for (int n = 0; n < values.size(); n++)
				{
					if (requiredFormuls[formulasIndex].formulasValues[j].designation == values[n].designation)
					{
						n = values.size() + 1;
					}
					if (n == values.size() - 1)
					{
						//cout << "Undeclar " <<requiredFormuls[formulasIndex].formulasValues[j].designation<<endl;
						undeclaredVars.push(requiredFormuls[formulasIndex].formulasValues[j].designation);
					}
				}
			}
			else
			{
				for (int n = 0; n < values.size(); n++)
				{
					if (requiredFormuls[formulasIndex].designation == values[n].designation)
					{
						n = values.size() + 1;
					}
					if (n == values.size() - 1)
					{
						//cout << "Undeclar " <<requiredFormuls[formulasIndex].formulasValues[j].designation<<endl;
						undeclaredVars.push(requiredFormuls[formulasIndex].designation);
					}
				}
			}
		}
		//system("pause");
	}

	//-----Loading chain-----
	for (int i = 1; i < chainCount + 1; i++)
	{
		//cout << i << "   " << chain[i] << endl;
		if (chain[chainCount - i].letterIndex == -1)
			cout << requiredFormuls[chain[chainCount - i].formulasIndex].designation << " = ";
		else
			cout << requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[chain[chainCount - i].letterIndex].designation << " = ";
		if (requiredFormuls[chain[chainCount - i].formulasIndex].isSum)
		{
			for (int k = 0; k < requiredFormuls[chain[chainCount - i].formulasIndex].numOfDesignations; k++)
			{
				if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio and chain[chainCount - i].letterIndex == -1)
					cout << " + " << requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation;
				else if (chain[chainCount - i].letterIndex == -1)
					cout << " -" << requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation;
				else if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio and chain[chainCount - i].letterIndex != -1 and chain[chainCount - i].letterIndex != k)
					cout << " -" << requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation;
				else if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio and chain[chainCount - i].letterIndex != -1 and chain[chainCount - i].letterIndex == k)
					cout << " -" << requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[0].designation;
				else if (!requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio and chain[chainCount - i].letterIndex != -1 and chain[chainCount - i].letterIndex != k)
					cout << " +" << requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[0].designation;
			}
			values[n + chainCount - i].designation = requiredFormuls[chain[chainCount - i].formulasIndex].designation;
			double sum = 0;
			for (int k = 0; k < requiredFormuls[chain[chainCount - i].formulasIndex].numOfDesignations; k++)
			{
				int tempi = 0;
				for (int n = 0; n < values.size(); n++)
				{
					if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation == values[n].designation and chain[chainCount - i].letterIndex == -1)
					{
						if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio)
							sum += values[n].value;
						else
							sum -= values[n].value;
					}
					else if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation == values[n].designation)
					{
						if (requiredFormuls[chain[chainCount - i].formulasIndex].designation == values[n].designation)
							tempi = n;
						if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio and chain[chainCount - i].letterIndex != k)
							sum -= values[n].value;
						else if (chain[chainCount - i].letterIndex != k)
							sum += values[n].value;
						else if (chain[chainCount - i].letterIndex == k)
							sum -= values[tempi].value;
					}
				}
			}
			values[n + chainCount - i].value = sum;
			values[n + chainCount - i].measure = "mpss";

			cout << " = " << sum;
			cout << endl;
		}
		else
		{
			for (int k = 0; k < requiredFormuls[chain[chainCount - i].letterIndex].numOfDesignations; k++)
			{
				//cout << "chain " << chain[i] << endl;
				if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio)
					cout << requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation;
				else
					cout << "(1/" << requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation << ")";
			}
			values[n + chainCount - i].designation = requiredFormuls[chain[chainCount - i].formulasIndex].designation;
			double sum = 1;
			for (int k = 0; k < requiredFormuls[chain[chainCount - i].formulasIndex].numOfDesignations; k++)
			{
				int tempi = 0;
				for (int n = 0; n < values.size(); n++)
				{
					if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation == values[n].designation and chain[chainCount - i].letterIndex == -1)
					{
						if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio)
							sum *= values[n].value;
						else
							sum /= values[n].value;
					}
					else if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation == values[n].designation)
					{
						if (requiredFormuls[chain[chainCount - i].formulasIndex].designation == values[n].designation)
							tempi = n;
						if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio and chain[chainCount - i].letterIndex != k)
							sum /= values[n].value;
						else if (chain[chainCount - i].letterIndex != k)
							sum *= values[n].value;
						else if (chain[chainCount - i].letterIndex == k)
							sum /= values[tempi].value;
					}
				}
			}
			/*
			for (int k = 0; k < requiredFormuls[chain[chainCount - i].formulasIndex].numOfDesignations; k++)
			{
				for (int n = 0; n < values.size(); n++)
				{
					if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].designation == values[n].designation)
					{
						if (requiredFormuls[chain[chainCount - i].formulasIndex].formulasValues[k].isInDirectRatio)
							sum *= values[n].value;
						else
							sum /= values[n].value;
					}
				}
			}
			//*/
			values[n + chainCount - i].value = sum;
			values[n + chainCount - i].measure = "mpss";

			cout << " = " << sum;
			cout << endl;
		}
	}

	return 0;
}

//Functions
void readFormulsFile(string src)
{
	ifstream file(src + ".avp");
	int count;
	file >> count;
	//cout << count << endl;
	for (int i = 0; i < count; i++)
	{
		formulsCount++;
		file >> requiredFormuls[i].designation >> requiredFormuls[i].numOfDesignations;
		requiredFormuls[i].isSum = false;
		//cout << requiredFormuls[i].designation << " " << requiredFormuls[i].numOfDesignations << endl;
		for (int k = 0; k < requiredFormuls[i].numOfDesignations; k++)
		{
			file >> requiredFormuls[i].formulasValues[k].designation >> requiredFormuls[i].formulasValues[k].isInDirectRatio;
			//cout << requiredFormuls[i].formulasValues[k].designation << requiredFormuls[i].formulasValues[k].isInDirectRatio << endl;
		}
	}

	file >> count;
	count += formulsCount;
	//cout << count << endl;
	for (int i = formulsCount; i < count; i++)
	{
		formulsCount++;
		file >> requiredFormuls[i].designation >> requiredFormuls[i].numOfDesignations;
		requiredFormuls[i].isSum = true;
		//cout << requiredFormuls[i].designation << " " << requiredFormuls[i].numOfDesignations << endl;
		for (int k = 0; k < requiredFormuls[i].numOfDesignations; k++)
		{
			file >> requiredFormuls[i].formulasValues[k].designation >> requiredFormuls[i].formulasValues[k].isInDirectRatio;
			//cout << requiredFormuls[i].formulasValues[k].designation << requiredFormuls[i].formulasValues[k].isInDirectRatio << endl;
		}
	}
}