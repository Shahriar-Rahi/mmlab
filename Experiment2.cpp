#include<bits/stdc++.h>
using namespace std;
map<string,int> dictionary;
ifstream input("inLZW.txt");

vector<string> input_data;
map<string,int> :: iterator it;

void encoding()
{
   ofstream encoded_data("encoded_dataLZW.txt");
   map<string,int> dict;
   int index;
   vector<int> decode_seq;
   string entry,stringLine;

    for(int line_no = 0; line_no < input_data.size(); line_no++)
    {
        dict.clear();
        decode_seq.clear();
        entry = "";

        stringLine = input_data[line_no];
        for(it = dictionary.begin(); it != dictionary.end(); it++)
        {
            dict[it -> first] = it -> second;
            index = it -> second;
        }

        for(int i = 0; i < stringLine.size(); i++)
        {
            if(dict.find(entry + stringLine[i]) != dict.end())
                entry =  entry + stringLine[i];
            else
            {
                dict[entry + stringLine[i]] = ++index;
                decode_seq.push_back(dict[entry]);
                entry = stringLine[i];
            }
        }

        decode_seq.push_back(dict[entry]);
        for(int i = 0; i < decode_seq.size(); i++)
            encoded_data << " " << decode_seq[i];
        encoded_data << endl;
    }
}

void decoding()
{
    int code,index;
    ifstream readData("encoded_dataLZW.txt");
    ofstream writeData("decoded_dataLZW.txt");
    string entry,s,stringLine;
    map<int,string> codeWordDict;

    while(getline(readData,stringLine))
    {
        entry = s = "";
        codeWordDict.clear();
        stringstream ss(stringLine);
        for(it = dictionary.begin(); it != dictionary.end(); it++)
            codeWordDict[it -> second] = it -> first,index = it -> second;

        while(ss >> code)
        {
            if(codeWordDict.find(code) == codeWordDict.end())
                entry = s + s[0];
            else
                entry = codeWordDict[code];
            writeData << entry;
            if(s != "")
                codeWordDict[++index] = s + entry[0];
            s = entry;
        }

        writeData << endl;
    }
}
int main()
{
    string stringLine;

    while(getline(input,stringLine))
    {
       input_data.push_back(stringLine);
       for(int i = 0; i < stringLine.size(); i++)
       {
           string s = "";
           s += stringLine[i];
           dictionary[s] = (int)stringLine[i];
       }
    }

    encoding();
    decoding();
    return 0;
}
