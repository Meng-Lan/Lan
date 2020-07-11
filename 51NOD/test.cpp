#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits.h>
#include<utility>
using namespace std;

/** 请完成下面这个函数，实现题目要求的功能 **/
 /** 当然，你也可以不按照这个模板来作答，完全按照自己的想法来 ^-^  **/
int minCost(vector<vector<int>>& costs)
{
	pair<int,long long> d[2];
    for(int i=0;i<costs.size();++i){
        if(!i){
            d[0]=make_pair(0,costs[i][0]);
            d[1]=make_pair(1,INT32_MAX);
            for(int j=1;j<costs[i].size();++j) if(costs[i][j]<=d[0].second){
                d[1]=d[0];
                d[0]=make_pair(j,costs[i][j]);
            }
        }
        else{
            pair<int,int> t[2];
            if(d[0].first!=0) t[0]=make_pair(0,d[0].second+costs[i][0]);
            else t[0]=make_pair(0,d[1].second+costs[i][0]);
            for(int j=1;j<costs[i].size();++j) {
                long long c=j!=d[0].first?d[0].second+costs[i][j]:d[1].second+costs[i][j];
                if(c<=t[0].second){
                    t[1]=t[0];
                    t[0]=make_pair(j,c);
                }
            }
            d[0]=t[0];d[1]=t[1];
        }
    }
    return d[0].second;

}

int main()
{
	int N,K;
	int cost;
	vector<vector<int> > costs;
	string s;
	istringstream is;

	getline(cin, s);
	is.str(s);
	is>>N>>K;
	for(int i =0 ; i < N; i++)
	{
		vector<int> t;
		getline(cin, s);
		is.clear();
		is.str(s);
		for(int j = 0; j < K; j++) {
			is >> cost;
			t.push_back(cost);
		}
		costs.push_back(t);
	}
	cout<<minCost(costs)<<endl;
	return 0;
}