/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: Xinran Ma]
 * This file is the starter project for the word ladder problem on Assignment #1.
 */

#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <vector>
#include <iostream>
#include <map>


using namespace std;

queue<vector<string>> words_queue;
int signed found_target = 0;
int signed deepth = 0;
queue<vector<string>> result_queue;
map<string, int> map_dic;

//declare function
void search_ladder_words(string orginal_word, string target_word, Lexicon & lexicon);
void one_hop_check(vector<string> check_this_time, string target_word, Lexicon & lexicon);

int main() {
	// [TODO: fill in the code]

	string orginal_word, target_word;

	std::cout << "Enter start word (RETURN to quit): ";
	std::cin >> orginal_word;
	std::cout << "Enter destination word: ";
	std::cin >> target_word;

	//check error cases
	if(orginal_word.length() != target_word.length()){
	std::cout << "No ladder found." << endl;
	return EXIT_FAILURE;
}

	Lexicon lexicon("EnglishWords.dat");
	if(!lexicon.containsWord(orginal_word) || !lexicon.containsWord(target_word)){
	std::cout << "No ladder found." << endl;
	return EXIT_FAILURE;
} 

	if(orginal_word == target_word){
		std::cout << "No ladder found." << endl;
		return EXIT_FAILURE;
	}
	//begin to search 
	search_ladder_words(orginal_word, target_word, lexicon);

	//output results
	if(found_target == 1){
		vector<string> output_vector;
		cout << "Found ladder: ";
		while(!result_queue.empty()){
			output_vector = result_queue.front();
			result_queue.pop();
			int signed k = output_vector.size();
			for(int signed i = 1; i <= k; i++){
				if(i != k){
					cout << output_vector[i-1] << " ";	
				}else{
					cout << output_vector[i-1] << endl;
				}
			}
		}
	}


	return EXIT_SUCCESS;
}

void search_ladder_words(string orginal_word, string target_word, Lexicon & lexicon){

	words_queue.push({orginal_word});
	map_dic[orginal_word] = 1;

	while(!words_queue.empty()){
		vector<string> check_this_time = words_queue.front();
		words_queue.pop();
		int signed vector_length = check_this_time.size();
		if(found_target == 1 && vector_length >= deepth)
			break;	
		else{
			one_hop_check(check_this_time, target_word, lexicon);
		}
		//
	}
}

//use lexicon to check and add all one hop words into both queue and check list
void one_hop_check(vector<string> check_this_time, string target_word, Lexicon & lexicon) {

	deepth = check_this_time.size() + 1;
	string current_word = check_this_time.back();
	char temp_l;
	string temp_word;
	int signed current_word_length = current_word.length();
	
	vector<string> temp_vector = check_this_time;
	int check_this_time_size = check_this_time.size();

	for(int signed i=0; i < current_word_length; ++i){
		for(temp_l = 'a'; temp_l <= 'z'; temp_l++){
			temp_word = current_word;
			temp_word[i] = temp_l;
			if (map_dic.count(temp_word) > 0 && (int) (map_dic.find(temp_word)->second) <= (int) check_this_time_size) {
				continue;
			}
			else {
				if (lexicon.containsWord(temp_word)) {
					if (temp_word == target_word) {
						found_target = 1;
						//insert this stuff into result_queue;
						temp_vector.push_back(temp_word);
						result_queue.push(temp_vector);
						temp_vector.pop_back();
					}
					else {
						temp_vector.push_back(temp_word);
						words_queue.push(temp_vector);
						temp_vector.pop_back();
						map_dic[temp_word] = deepth;
					}
				}
			}
		}
	}
}
