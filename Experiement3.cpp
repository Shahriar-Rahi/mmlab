#include<bits/stdc++.h>
using namespace std ;


ifstream in("test.txt") ;

struct table{
    char ch ;
    float range,low,high ;


};


/*create_table1(struct table1[]){
    float low = 0.0 ,range ;
    char ch ;

   for(int i = 0 ; i < 7 ; i++){
    in>>ch >>range ;

    table1[i]->ch =ch ;
    table1[i]->range =range;
    table1[i]->low = low ;
    table1[i]->high= table1[0].low + table1[0].range  ;

    low = table1[i].high ;
   }



}
*/
float value(string input){

    float result = 0.0 ;


    char ch ;
    int j = 0 ;
    int rem  ;
    //cout<<input.size() ;
    for(int i = 1 ; i<=input.size() ; i++){
         ch = input[j] ;
         if(ch=='1')
            rem = 1 ;
         else rem = 0 ;

         result +=rem*pow(2,(i*-1)) ;
         j++ ;

    }
    cout<<result<<endl ;
    return result ;


}
void code_generate(float low , float high){
    char code[10] ;
     code[0] = '0' ;
    int k = 1 ;
    while(value(code)<low){
        code[k] = 1 ;
        if(value(code)> high)
            code[k] = 0 ;
        k = k + 1 ;
    }

    cout<<code<<endl ;

}



int main(){

   table table1[10],table2[10] ;



    float low = 0.0 ,range ;
    char ch ;


   for(int i = 0 ; i < 7 ; i++){
    in>>ch >>range ;

    table1[i].ch =ch ;
    table1[i].range =range;
    table1[i].low = low ;
    table1[i].high= table1[i].low + table1[i].range  ;

    low = table1[i].high ;

   }
   string symbol ;
  cout<<"Enter a symbol ::"  ;
  cin>>symbol ;


   float loww = 0.0 , high = 1.0 , rangee = 1.0  ;


   int len = symbol.size() ;

   for(int i = 0 ; i <len; i++){
        ch = symbol[i] ;
        float low_ , high_  ;

            for(int j = 0 ; j<7 ; j++){
               if(table1[j].ch == ch){
                   low_ = table1[j].low ;
                   high_ = table1[j].high ;
                   //cout<<low_<<" "<<high_<<endl;
                   break ;
               }
            }

       high = loww + rangee*high_ ;
       loww = loww + rangee*low_ ;
       rangee = high - loww ;


        table2[i].ch = ch ;
        table2[i].low = loww ;
        table2[i].high = high ;
        table2[i].range = rangee ;


   }

   for(int k =0 ; k< symbol.size() ; k++){
    cout<<table2[k].ch<<" "<<table2[k].low<<" "<<table2[k].high<<" "<<table2[k].range <<endl ;
   }

  loww = table2[len-1].low ;
  high = table2[len-2].high ;

  code_generate(loww,high) ;



   return 0 ;
}
