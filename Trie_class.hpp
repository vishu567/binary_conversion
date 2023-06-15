
#ifndef _TRIE_HPP
#define _TRIE_HPP
class Node{
	public:
	Node* add[56];
	int key;
	
	Node(){ //constructor
		key=-1;
		for(int i=0;i<56;i++)
		      add[i]=NULL;
	}
	
	Node* getNode(){ //returns a ptr to a new node
		Node *temp;
		temp = new Node;
		return temp;
	}
};

class Trie{
	private:
		Node *start;
	public:
		Trie(){ //default constructor for class Trie
		    Node temp;
			start=temp.getNode();
		}
		
		void insert(std::string s,int k){
			
			Node *ptr=start; //Setting the root as the first letter of the word 
			Node temp;
			for(int i=0;i<s.length();i++){
				int next=Trie::getNext(s[i]);
				if(ptr->add[next]==NULL)
					ptr->add[next]=temp.getNode(); //if next index doesn't exist we'll create a new Node
				ptr = ptr->add[next];
			}
			
			ptr->key=k;
		}
		
        int search(std::string s){
	        Node *ptr=start;
	        for(int i=0;i<s.length();i++){
	        	 int next=Trie::getNext(s[i]);
		         if(ptr->add[next]==NULL){
			         return -1;
	 	         }
		         ptr=ptr->add[next];
	        }
	        return ptr->key;
        }
        
        int getNext(char c){
        	if(c>='a'&&c<='z')return c-'a';
        	if(c>='A'&&c<='Z')return c-'A'+26;
        	if(c==' ')return 52;
        	if(c=='-')return 53;
        	if(c==',')return 54;
        	if(c=='.')return 55;
		}
};

#endif


