//note: weight = frequency for leaves
#include <fstream>
#include "simon_func.h"
using namespace std;

struct Node{
	int weight, asciiValue, frequency; //if it is not leaf, asciiValue = -1
	Node* leftkid, *rightkid;
	Node(int asciiValue = -1, Node* leftkid = NULL, Node* rightkid = NULL) : 
		weight{0}, asciiValue{asciiValue}, frequency{0}, leftkid{leftkid}, rightkid{rightkid}{}
	void update(int freq = 0){
		//update weight by adding children's weight if it's not leaf
		if(asciiValue == -1) weight = leftkid->weight + rightkid->weight;
		
		//update weight by frequency
		else weight = freq;
	}
};

bool cmpt(const Node* first, const Node* other){
	return first->weight < other->weight;
}

deque<Node*> asciiNodes;
deque<Node*> asciiTrie;
vector<Node*> deleteTmpList; //all tmp heap pointer are stored here for delete
Node* asciiTrieRoot;
vector<string> asciiCode; //asciiCode[i] stores the ith code for that ascii char

void buildTrie(deque<Node*> asciiTrie){
	while(asciiTrie.size() > 1) {
		stable_sort(asciiTrie.begin(), asciiTrie.end(),cmpt);
		Node* tmp = new Node(-1, asciiTrie[0], asciiTrie[1]);
		deleteTmpList.push_back(tmp);
		tmp->update();
		asciiTrie.pop_front();
		asciiTrie.pop_front();
		asciiTrie.push_back(tmp);
	}
	
}

//get ascii code for vector asciiCode
void getAsciiCode(Node* asciiTrieNode, string curCode){
	if(asciiTrieNode == NULL) return;
	if(asciiTrieNode->asciiValue != -1) asciiCode[asciiTrieNode->asciiValue] = curCode;
	getAsciiCode(asciiTrieNode->leftkid, curCode + "0");
	getAsciiCode(asciiTrieNode->rightkid, curCode + "1");
}


int main(int argc, char* argv[]){
	int charCount = 0;
	int charNeed = 128;
	int tmpchar;
	
	//initialize ascii Nodes, and construct first asciiTrie
	forEach(asciiIndex,0,128) asciiNodes.push_back(new Node(asciiIndex));
	forVec(val, asciiNodes) asciiTrie.push_back(val);
	buildTrie(asciiTrie);
	asciiTrieRoot = deleteTmpList[deleteTmpList.size() - 1];
	forEach(i,0,128) asciiCode.push_back("");
	getAsciiCode(asciiTrieRoot,"");
	
	try{
		while(true){
			//get chars
			forEach(i,0,charNeed){
				charCount++;
				tmpchar = getchar();
				if(tmpchar == -1) throw "DONE";
				cout<<asciiCode[tmpchar];
				asciiNodes[tmpchar]->update(++asciiNodes[tmpchar]->frequency); //update weight and frequency
			}
			
			asciiTrie.clear();
			forVec(val, asciiNodes) asciiTrie.push_back(val);
			buildTrie(asciiTrie);
			asciiTrieRoot = deleteTmpList[deleteTmpList.size() - 1];
			forEach(i,0,128) asciiCode[i] = "";
			getAsciiCode(asciiTrieRoot,"");
			if(charCount > charNeed) charNeed *= 2;
		}
	} catch(char const* err){
		
	}
	
	//delete everything we used
	forVec(val,deleteTmpList) delete val;
	forVec(val, asciiNodes) delete val;
	return 0;
}

