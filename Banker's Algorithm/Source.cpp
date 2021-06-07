#include <math.h>
#include <string.h>
#include <map>
#include <iostream>
#include <string>
#include <ctype.h>
#include <vector>
#include <iomanip> 
#include <algorithm>


using namespace std;


int allocation[100][100];
int maximam[100][100];
int avail[100];
int request[100];
int safty_ans[100];
int n; // Number of processes
int number_of_process;
int need[100][100];

void check_safety(int alloc[][100], int max[][100], int* avail, int n, int m, int option)
{
	int i, j, k;
	bool safe = true;
	int finish[100];
	int ans[100];
	int index = 0;

	for (k = 0; k < n; k++) 
	{
		finish[k] = 0;
	}
	if (option == 0)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
				need[i][j] = max[i][j] - alloc[i][j];
		}
	}
	
	int y = 0;
	for (k = 0; k < 5; k++) 
	{
		for (i = 0; i < n; i++) 
		{
			if (finish[i] == 0) 
			{

				int flag = 0;
				for (j = 0; j < m; j++) 
				{
					if (need[i][j] > avail[j]) 
					{
						flag = 1;
						break;
					}
				}

				if (flag == 0)
				{
					ans[index++] = i;
					for (y = 0; y < m; y++)
						avail[y] += alloc[i][y];
					finish[i] = 1;
				}
			}
		}
	}

	for (i = 0; i < m; i++)
	{
		if (finish[i] != 1)
		{
			safe = false;
		}
	}

	if (safe == true)
	{
		cout << "=============================================" << endl;
		cout << "Need Matrix" << endl;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				cout << need[i][j] << " ";
			}
			cout << endl;
		}
		if (option == 0)
		{
			cout << "Following is the SAFE Sequence" << endl;
			for (i = 0; i < n - 1; i++)
			{
				safty_ans[i] = ans[i];
				cout << "P" << ans[i] << " -> ";
			}
			safty_ans[n - 1] = ans[n - 1];
			cout << "P" << ans[n - 1] << endl;
		}
		else
		{
			cout << "Yes , request can be granted with safe state" << endl;
			cout << "P" << ans[number_of_process] << "req" << " -> ";
			for (i = 0; i < n - 1; i++)
			{
				/*if (i == number_of_process)
				{
					continue;
				}*/
				cout << "P" << safty_ans[i] << " -> ";
			}
			cout << "P" << safty_ans[n - 1] << endl;
			
		}
	
	}
	else
	{
		if (option == 0)
		{
			cout << "NOT SAFE" << endl;
		}
		else
		{
			cout << "request will not be accept due to unsafe state " << endl;
		}
	}
		

}

void  immediate_request(int ProcessName,int* request,int alloc[][100], int max[][100], int* avail, int n, int m)
{
	int i, j, k;
	bool cant_be_granted = true;
	int finish[100];
	int ans[100];
	int index = 0;
	int need[100][100];
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			need[i][j] = max[i][j] - alloc[i][j];
	}

	/*for (j = 0; j < m; j++)
	{
		need[ProcessName][j] = need[ProcessName][j] + request[j];
	}

	for (j = 0; j < m; j++)
	{
		avail[j] += request[j];
	}*/

	for (j = 0; j < m; j++)
	{
		if (need[ProcessName][j] < request[j])
		{
			cout << "ERROR it can't be granted" << endl;
		}
		else
		{
			if (avail[j] < request[j])
			{
				cout << " request can't be granted " << endl;
			}
			else
			{
				/*Available = Available  – Requesti;
				Allocationi = Allocationi + Requesti;
				Needi = Needi – Requesti;*/
				avail[j] = avail[j] - request[j];
				alloc[ProcessName][j] += request[j];
				need[ProcessName][j] = need[ProcessName][j] - request[j];
			}
		}
	}


}


int main()
{
	while (1)
	{


		cout << "0 For check safty" << endl;
		cout << "1 for immediate request" << endl;
		

		int option;
		int i, j, k; // counters
		int m; // Number of resources

			cin >> option;

			if (option == 0)
			{

				cout << "Enter number of processes" << endl;
				cin >> n;
				cout << "Enter number of Resources" << endl;
				cin >> m;

				cout << "Enter Allocation Matrix" << endl;
				for (i = 0; i < n; i++)
				{
					for (j = 0; j < m; j++)
					{
						cin >> allocation[i][j];
					}
				}

				cout << "Enter Max Matrix" << endl;
				for (i = 0; i < n; i++)
				{
					for (j = 0; j < m; j++)
					{
						cin >> maximam[i][j];
					}
				}

				cout << "Enter Available Matrix" << endl;
				for (i = 0; i < m; i++)
				{
					cin >> avail[i];
				}

				check_safety(allocation, maximam, avail, n, m, option);
				
			}

			else if (option == 1)
			{

				cout << "Enter number of the requested process" << endl;
				cin >> number_of_process;
				cout << "Enter number of Resources" << endl;
				cin >> m;
				cout << "Enter Request Matrix" << endl;
				for (i = 0; i < m; i++)
				{
					cin >> request[i];
				}

				immediate_request(number_of_process, request, allocation, maximam, avail, n, m);
				check_safety(allocation, maximam, avail, n, m, option);
		}
	}

	return 0;
}