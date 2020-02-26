#include<bits/stdc++.h>
using namespace std;
ofstream encoded_file("encode_data.txt");
ofstream decoded_file("decode_data.txt");
map<char,string> Code;
map<char,float> mp;
map<char,int> freq;
vector<string> files_data;

struct Node
{
    char data;
    float prob;
    Node* leftChild,*rightChild;
};

struct compare
{
    bool operator()(Node* leftChild,Node* rightChild)
    {
        return leftChild -> prob > rightChild -> prob;
    }
};

Node* create_node(char symbol,float prob)
{
    Node* newNode = new Node();
    newNode -> data = symbol;
    newNode -> prob = prob;
    newNode -> leftChild = newNode -> rightChild = NULL;
    return newNode;
}

void generate_code(Node* root,string codeWord)
{
    if(!root)
        return;
    if(root -> data != '$'){
        Code[root -> data] = codeWord;
        encoded_file << root -> data << " " << freq[root -> data] << " "<< codeWord << endl;
    }

    generate_code(root -> leftChild,codeWord + "0");
    generate_code(root -> rightChild,codeWord + "1");
}

void huffman_tree()
{
    priority_queue<Node*,vector<Node*>, compare> Q;
    map<char,float> :: iterator it;
    Node* left, *right;

    for(it = mp.begin(); it != mp.end(); it++)
    {
       Node* NewNode = create_node(it -> first,it -> second);
	   Q.push(NewNode);
    }

    while(Q.size() != 1)
    {
       left = Q.top();
       Q.pop();
       right = Q.top();
       Q.pop();

       Node* parent_node = create_node('$',left -> prob + right -> prob);
       parent_node -> leftChild = left;
       parent_node -> rightChild = right;
       Q.push(parent_node);
    }

   generate_code(Q.top(),"");
   encoded_file << '$' <<" " << 999999 <<" " << "END" << endl;
}

void encoding()
{
    string encodedLine = "";

    for(int i = 0; i < files_data.size(); i++)
    {
        for(int j = 0; j < files_data[i].size(); j++)
            encodedLine += Code[files_data[i][j]];

        encoded_file << encodedLine << endl;
        encodedLine = "";
    }
}

void decoding()
{
    ifstream readData("encode_data.txt");
    char symbol;
    string codeword,encode_string,decode_string;
    map<string,char> dict;
    int f;

    while(getline(readData,encode_string))
    {
        if(encode_string.find("END") != -1)
            break;
        symbol = encode_string[0];
        encode_string[0] = ' ';
        stringstream ss(encode_string);
        ss >> f, ss >> codeword;
        dict[codeword] = symbol;
    }

    while(readData >> encode_string)
    {
       codeword = "";

        for(int i = 0; i < encode_string.size(); i++)
        {
            codeword += encode_string[i];

            if(dict.find(codeword) != dict.end())
            {
                decode_string += dict[codeword];
                codeword = "";
            }
        }

         decoded_file << decode_string << endl;
        decode_string = "";
    }
}

void set_probability(int totalSize)
{
    map<char,float> :: iterator it;
    for(it = mp.begin(); it != mp.end(); it++)
        mp[it -> first] = (it -> second * 100.00) / (float)totalSize;
}
int main()
{
    ifstream input("in.txt");
    string sentence;
    int totalSize = 0;

    while(getline(input,sentence))
    {
        totalSize += sentence.size();
        files_data.push_back(sentence);

        for(int i = 0; i < sentence.size(); i++)
            mp[sentence[i]] += 1,freq[sentence[i]]++;
    }
    set_probability(totalSize);
    huffman_tree();
    encoding();
    decoding();
    return 0;
}
