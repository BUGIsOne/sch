#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<map>
#include<string>
#include<algorithm>
#include<cstring>

using namespace std;

int main(int argc, char  *argv[])
// int main()
{
  // 打开文件
  ifstream order(argv[1]);
  ifstream input(argv[2]);

  string str_order = "";
  int argv1_len = strlen(argv[1]);
  for(int i=0; i<argv1_len; i++)
    str_order += (argv[1][i]);

  // ifstream input("./test.txt");

  string s;
  int total_ch = 0;
  map <char, size_t> map1;
  map <char, size_t>::iterator it_map;

  // if(output && input)
  if(input)
  {
    while(getline(input,s))
    {
      int len = s.length();
      transform(s.begin(),s.end(),s.begin(), ::tolower);
      for(int i=0; i<len; i++)
      {
        char ch = s[i];
        if(isalpha(ch))
          ++map1[ch];
      }
    }
  }


  
  if(str_order.length() == 2 && str_order=="-c")
    for(it_map=map1.begin(); it_map != map1.end(); it_map++)
      cout<<it_map->first<<" "<<it_map->second<<endl;
  
  // cout<<str_order;
  // getchar();
  return 0;
}