#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "bdc.h"

// to_string function
string vec_to_string(vector<int> v){
    string outcome="{";
    for(int i:v){
        outcome+=to_string(i);
        outcome+=",";
    }
    if(v.size()>=1){  
        outcome.pop_back();
    }
    outcome+="}";
    return outcome;
}

vector<int> biggest_divisible_conglomerate(vector<int> input){
    // in case exception
    if (input.empty()) return {};
    if (input.size() == 1) return input;

    //make sure the smallest element always is the first one 
    sort(input.begin(), input.end());
    
    //make table there
    int n=input.size();
    vector<vector<int>> answers(n);

    //fill table with single element
    for(int i = 0;i<n;i++){
        answers[i] = {input[i]};
        //for test:
        //cout<<"initial answers:"<<vec_to_string(answers[i])<<endl;
    }

    
    //fill table by diviable elements
    for(int i = 0;i < n;i++){
        int cur_element = input[i];
        for(int j = i+1; j < n;j++){
            
            //analysis:
            //algorithm：if a%b=0, b%c=0, then a%c should be = 0 too. We make dynamic table base on that.
            //it allow us to divide those big problem to smaller problems. Like in our table, we can use the bottom of table to top of table
            //So, we can build the table from bottom to top and eventually complete it
            
            if (input[j]%cur_element==0 && answers[i].size() >= answers[j].size()){
                answers[j] = {input[j]};
                // add all elements from the answers at i spot into the answers at j spot
                for(long long unsigned int k = 0; k < answers[i].size();k++){   
                    answers[j].push_back(answers[i][k]);
                    //for test:
                    //cout<<"pushed elements:"<<vec_to_string(answers[j])<<endl;
                }
            }
        }
    
    }

    //for test table
    // cout<<"input:"<<vec_to_string(input)<<endl;
    // for(long long unsigned int i = 0; i < answers.size();i++){   
    //     cout<<"table:"<<vec_to_string(answers[i])<<endl;
    // }

    //find largest one subset
    int max_len_idx=0;
    long long unsigned int max_len = 0;
    for(long long unsigned int i = 0; i < answers.size();i++){   
        if(answers[i].size()>max_len){
            max_len=answers[i].size();
            max_len_idx=i;
        }
    }

    return answers[max_len_idx];
}