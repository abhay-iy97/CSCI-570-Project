#include<bits/stdc++.h>
#include<fstream>
#include<chrono>
using namespace std;
using namespace std::chrono;
int charValue(char c)
{
	if(c=='A') return 0;
	else if (c=='C') return 1;
	else if (c=='G') return 2;
	return 3;
}


pair<int, pair<string, string> > findOptimalCost(string s1, string s2, int delta, int alphas[4][4])
{
	int m = s1.length();
	int n = s2.length();
	// cout<<n<<" "<<m<<endl;
	vector< vector<pair<int, pair<int, int> > > > dp(m+1, vector<pair<int, pair<int, int> > >(n+1));
	for(int i=0;i<=m;i++)
	{
		vector<pair<int, pair<int, int> > > vec;
		vec.push_back(make_pair(0, make_pair(-1,-1)));
		for (int j= 0; j <=n; ++j)
		{
			dp.push_back(vec);
		}
	}

	for(int i=0;i<=m;i++)
	{
		dp[i][0].first = (i)*delta;
	}

	for(int i=0;i<=n;i++)
	{
		dp[0][i].first = (i)*delta;
	}
	
	// 	for(int i=0;i<=m;i++)
	// {
	// 	for(int j=0;j<=n;j++)
	// 	{
	// 		cout<<dp[i][j].first<<" ";
	// 	}
	// 	cout<<endl;
	// }



	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			 dp[i][j].first = dp[i-1][j-1].first + alphas[charValue(s1[i-1])][charValue(s2[j-1])];
			 dp[i][j].second = make_pair(i-1, j-1);

			 if(dp[i-1][j].first + delta < dp[i][j].first)
			 {
			 	dp[i][j].first = dp[i-1][j].first + delta;
			 	dp[i][j].second = make_pair(i-1, j);
			 }

			 if(dp[i][j-1].first + delta < dp[i][j].first)
			 {
			 	dp[i][j].first = dp[i][j-1].first + delta;
			 	dp[i][j].second = make_pair(i, j-1);
			 }
		}
	}


	// for(int i=0;i<=m;i++)
	// {
	// 	for(int j=0;j<=n;j++)
	// 	{
	// 		cout<<dp[i][j].first<<" ";
	// 	}
	// 	cout<<endl;
	// }

	int minCostForAlignment = dp[m][n].first;

	string xAlignment = "";
	string yAlignment = "";
	int i=m,j=n;
	while(i>0 && j > 0)
	{
		if(dp[i][j].second.first == i-1 && dp[i][j].second.second == j-1)
		{
			xAlignment = s1[i-1] + xAlignment;
			yAlignment = s2[j-1] + yAlignment;
			i--;
			j--;
		}
		else if(dp[i][j].second.first == i-1 )
		{
			xAlignment = s1[i-1] + xAlignment;
			yAlignment = "_" + yAlignment;
			i--;
		}
		else
		{
			xAlignment = "_" + xAlignment;
			yAlignment = s2[j-1] + yAlignment;
			j--;
		}
	}
	while(i>0)
	{
		xAlignment = s1[i-1] + xAlignment;
		yAlignment = "_" + yAlignment;
		i--;
	}

	while(j>0)
	{
		xAlignment = "_" + xAlignment;
		yAlignment = s2[j-1] + yAlignment;
		j--;
	}
	

	// cout<<xAlignment.substr(0,50)<<" "<<yAlignment.substr(0,50)<<endl;
	// cout<<xAlignment.substr(xAlignment.length()-50)<<" "<<yAlignment.substr(yAlignment.length()-50)<<endl;


	return make_pair(minCostForAlignment, make_pair(xAlignment, yAlignment));



}

void printVector(vector<int> vec)
{
	for(int i=0;i<vec.size();i++)
	{
		cout<<vec[i]<<" ";
	}
	cout<<endl;
	return;
}


vector<int> optimalCostValueOptimisedSpace(string s1, string s2, int delta, int alphas[4][4])
{
	int m = s1.length();
	int n = s2.length();

	if(n==0) 
	{
		vector<int> col1;
		col1.push_back(m*delta);
		return col1;
		// return delta * m;
	}

	if(m==0){
		vector<int> col1;
		for(int i=0;i<=n;i++)
			col1.push_back(i*delta);
		return col1;
	 	// return delta * n;
	}


	vector<int> col1(m+1);
	vector<int> col2(m+1);

	for(int i=0;i<=m;i++)
	{
		col1[i] = (i*delta);
	}
	// printVector(col1);
	vector<int> ans;
	ans.push_back(col1[m]);

	for(int i=1;i<=n;i++)
	{
		col2[0]=(i*delta);
		for(int j=1;j<=m;j++)
		{
			col2[j]= min(col2[j-1] + delta, min(col1[j-1] + alphas[charValue(s1[j-1])][charValue(s2[i-1])], col1[j] + delta));
		}
		// printVector(col1);
		// printVector(col2);
		ans.push_back(col2[m]);
		col1 = col2;
	}

	return ans;


	// return col2[col2.size()-1];

}

pair<string, string> findOptimalCostOptimizedSpace(string s1, string s2, int delta, int alphas[4][4])
{
	int len1 = s1.length();
	int len2 = s2.length();

	// cout<<s1.length()<<" and lens2 : "<<s2.length()<<" valueS2: "<<s2<<endl;

	if(len1 == 0 && len2 == 0)
	{
		return make_pair("", "");
	}
	if(len1 == 0)
	{
		string p1 = "";
		for(int i=0;i<len2;i++)
		{
			p1 += "_";
		}
		return make_pair(p1, s2);
	}

	if(len2 == 0)
	{
		// cout<<"here<<"<<endl;
		string p2 = "";
		for(int i=0;i<len1;i++)
		{
			p2 += "_";
		}
		return make_pair(s1, p2);
	}
	if(len1 == 1 && len2 == 1)
	{
		if(s1[0] == s2[0]) return make_pair(s1,s2);
		else
		{
			if(2*delta > alphas[charValue(s1[0])][charValue(s2[0])])
			{
				return make_pair(s1,s2);
			}
			else return make_pair("_"+s1, s2+"_");
		}
	}
	if(len1 == 1 || len2 == 1)
	{
		pair<int, pair<string, string> > ans = findOptimalCost(s1, s2, delta, alphas);
		return ans.second;
	}
	
	int m1 = len1 / 2;

	string leftS1 = s1.substr(0,m1);
	string rightS1 = s1.substr(m1);


	// cout<<leftS1<<", "<<rightS1<<endl;

	vector<int> s2DividedForLeftS1;
	vector<int> s2DividedForRightS1;
	


	/*
	for(int i=0;i<=s2.length();i++)
	{
		string temp = s2.substr(0,i);
		// cout<<"calling from here 1"<<endl;
		int val = optimalCostValueOptimisedSpace(leftS1, temp, delta, alphas);
		s2DividedForLeftS1.push_back(val);
	}
	*/

	s2DividedForLeftS1 = optimalCostValueOptimisedSpace(leftS1, s2, delta, alphas);


	string s2Reversed = s2;
	string rightS1Reversed = rightS1;
	reverse(s2Reversed.begin(), s2Reversed.end());
	reverse(rightS1Reversed.begin(), rightS1Reversed.end());


	/*
	for(int i=0;i<=s2Reversed.length();i++)
	{
		string temp = s2Reversed.substr(0,i);
		int val = optimalCostValueOptimisedSpace(rightS1Reversed, temp, delta, alphas);
		s2DividedForRightS1.push_back(val);
	}
	*/
	s2DividedForRightS1 = optimalCostValueOptimisedSpace(rightS1Reversed, s2Reversed , delta, alphas);




	// cout<<s2DividedForLeftS1.size()<<" "<<s2DividedForRightS1.size()<<endl;

	reverse(s2DividedForRightS1.begin(), s2DividedForRightS1.end());
	int mini = INT_MAX, ind = -1;
	for(int i=0;i<s2DividedForLeftS1.size();i++)
	{
		if(mini >= s2DividedForLeftS1[i] + s2DividedForRightS1[i])
		{
			mini = s2DividedForLeftS1[i] + s2DividedForRightS1[i];
			// cout<<"minimum cost value : "<<mini<<" for "<<i<<endl;
			ind = i;
		}
	}
	// cout<<"divide at "<<ind<<endl;
	string s2Left = s2.substr(0, ind);
	string s2Right = s2.substr(ind);

	// cout<<"giving : "<<s2Left<<", "<<s2Right<<" with cost: "<<mini<<endl;

	pair<string, string> leftAns = findOptimalCostOptimizedSpace(leftS1, s2Left, delta, alphas);
	// cout<<"leftSorted"<<endl;
	// cout<<rightS1<<", "<<s2Right<<endl;
	pair<string, string> rightAns = findOptimalCostOptimizedSpace(rightS1, s2Right, delta, alphas);

	pair<string, string> finalAns;
	finalAns.first = leftAns.first + rightAns.first;
	finalAns.second = leftAns.second + rightAns.second;

	return finalAns;


}





pair<string, string> preprocessStrings(string s1, string s2, vector<int>& indexesS1, vector<int>& indexesS2)
{

	for(int i=0;i<indexesS1.size();i++)
	{
		string s1_l="", s1_r="";

		s1_l += s1.substr(0,indexesS1[i]+1);
		s1_r +=  s1.substr(indexesS1[i]+1);

		string updatedS1 = "";

		updatedS1 += (s1_l + s1 + s1_r); 

		s1 = updatedS1;
	}

	for(int i=0;i<indexesS2.size();i++)
	{
		string s2_l = s2.substr(0,indexesS2[i]+1);
		string s2_r = s2.substr(indexesS2[i]+1);
		string updatedS2 = "";
		updatedS2 += (s2_l + s2 + s2_r);
		s2 = updatedS2;
	}

	return make_pair(s1,s2);

}


void writeOutput(vector<int> iMinCostAdv, pair<string, string> iMinCostDnCnDP, duration<long long,std::micro> iDuration)
{
	ofstream outputFile;
	outputFile.open ("output.txt");
	outputFile << iMinCostDnCnDP.first << endl;					//Line1
	outputFile << iMinCostDnCnDP.second << endl;				//Line2
	outputFile << iMinCostAdv[iMinCostAdv.size()-1]<<endl;		//Line3 - Cost
	outputFile << iDuration.count() / double(1000000) << endl;	//Line4 - Time consumed
	outputFile << "1234" << endl;								//Line5 - Space consumed - Dummy value (To do - Find actual cost)
	outputFile.close();
	
}
int main(int argc, char* argv[])
{


	auto start = high_resolution_clock::now();

 	string fileName = "";
	if(argc == 2)
    {
		fileName = argv[1];	//Input File Name
	}
	if(!fileName.empty())
	{
		ifstream file(fileName);
		string line;
		string s1="", s2 ="";
		vector<int> indexesS1;
		vector<int> indexesS2;
		bool flag = false;
		int num = -1;
		int count = 0;
		while(getline(file, line))
		{
			if(count == 0 && !flag)
			{
				s1 += line;
			}
			else if(line[0] >= 58 && !flag)
			{
				// cout<<"here : "<<line<<endl;
				s2 += line;
				flag = true;
			}
			else
			{
				if(!flag){
					if(line=="") continue;
					int val = stoi(line);
					indexesS1.push_back(val);
				}
				else{
					if(num==-1)
						num = 0;
					if(line=="") continue;
					indexesS2.push_back(stoi(line));
					num++;
				}
			}
			count++;
			// if()
		}

		// cout<<s1.size() <<" "<<s2.size()<<endl;

		if(s1.size()>1)
		s1 = s1.substr(0, s1.size()-1);

		if(s2.size()>1)
		s2 = s2.substr(0, s2.size()-1);

		// cout<<s1<<", "<<s2<<endl;

		/*
		cout<<s1<<" "<<s2<<endl;
		for(int i=0;i<indexesS1.size();i++)
		{
			cout<<indexesS1[i]<<" ";
		}
		cout<<endl;
		for(int i=0;i<indexesS2.size();i++)
		{
			cout<<indexesS2[i]<<" ";
		}

		// cout<<endl;

		*/





		pair<string, string> alginmentStrings = preprocessStrings(s1, s2, indexesS1, indexesS2);

		string sequence1 = alginmentStrings.first;
		string sequence2 = alginmentStrings.second;

		cout<<sequence1.size()<<" "<<sequence2.size()<<endl;

		int delta = 30;

		int alphas[4][4] = { 	 
			{0,110,48,94},
			{110, 0, 118, 48}, 
			{48,118,0,110}, 
			{94,48,110,0} 
		};

		// pair<int, pair<string, string> > minCostBasic = findOptimalCost(sequence1, sequence2, delta, alphas);
		// cout<<minCostBasic.first<<endl;

		// cout<<minCostBasic.second.first<<endl;
		// cout<<minCostBasic.second.second<<endl;
		// cout<<endl;

		pair<string, string> minCostDnCnDP = findOptimalCostOptimizedSpace(sequence1, sequence2, delta, alphas);
		vector<int> minCostAdv = optimalCostValueOptimisedSpace(sequence1, sequence2,delta,alphas);
		cout<<minCostAdv[minCostAdv.size()-1]<<endl;

		cout<<minCostDnCnDP.first<<endl;
		cout<<minCostDnCnDP.second<<endl;


		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<microseconds>(stop - start);
		cout << duration.count() / double(1000000) << endl;
		writeOutput(minCostAdv, minCostDnCnDP, duration);
		file.close();
	}
}