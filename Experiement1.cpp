#include<bits/stdc++.h>
using namespace std;


string int2string(int n)
{
    string result = "";

    while(n)
    {
        result += (n % 10) + '0';
        n = n / 10;
    }

    reverse(result.begin(),result.end());
    return result;
}

string RLE_encoding(string mess)
{
    string encrypt_mess = "";
    map<char,int> mp;
    map<char,int> :: iterator it;
    int freq;
    char symbol;

    for(int i = 0; i < mess.size(); i++)
    {
        if(mp.size() == 0 || mp.find(mess[i]) != mp.end()) mp[mess[i]]++;
        if(mp.size() != 0 && mp.find(mess[i]) == mp.end())
        {
            it = mp.begin();
            freq = it -> second;
            symbol = it -> first;
            encrypt_mess += to_string(freq) + "!" + symbol;
            mp.clear();
            mp[mess[i]]++;
        }
    }

     it = mp.begin();
     freq = it -> second;
     symbol = it -> first;
     encrypt_mess += to_string(freq) + "!" + symbol;
     return encrypt_mess;
}

string RLE_decoding(string mess)
{
    char symbol;
    string decrypt_mess = "",freq = "";
    bool isFound = false;

    for(int i = 0; i < mess.size(); i++)
    {
        if(mess[i] == '!') isFound = true;
        if(!isFound)
          freq += mess[i];
        else
        {
            int cnt = atoi(freq.c_str());
            freq = "";
            isFound = false;
            symbol = mess[i+1];
            ++i;
            for(int j = 1; j <= cnt; j++) decrypt_mess += symbol;
        }
    }

    return decrypt_mess;
}
int main()
{
    ifstream readData("RLEinput.txt");
    ofstream encoded_file("RLEencode.txt");
    ofstream decoded_file("RLEdecode.txt");

   string message,encoded_mess,decoded_mess;
   getline(readData,message);
   encoded_mess = RLE_encoding(message);
   if(encoded_mess.size() < message.size())
   decoded_mess = RLE_decoding(encoded_mess);
   else encoded_mess = decoded_mess = message;

   encoded_file << "encrypted message is : " << encoded_mess << endl;
   decoded_file << "decrypted message is : " << decoded_mess << endl;
   return 0;
}
