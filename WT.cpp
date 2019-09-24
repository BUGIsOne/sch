#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<map>
#include<string>
#include<algorithm>
#include<cstring>
#include<io.h>

using namespace std;

int main(int argc, char *argv[])
// int main()
{
  // 打开文件
  ifstream order(argv[1]);
  ifstream input(argv[2]);
  ofstream output("./output.txt");

  string str_order = "";
  int argv1_len = strlen(argv[1]);
  for(int i=0; i<argv1_len; i++)
    str_order += (argv[1][i]);

  

  string s;
  int total_ch = 0;
  map <char, size_t> map1;
  map <char, size_t>::iterator it_map;

  string str_line;
  //argv[1].length is right and input is not none
	if(str_order.length() == 2)
  {
		cout<<str_order<<endl<<endl;
  	if(str_order == "-c")
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
	  		
	    for(it_map=map1.begin(); it_map != map1.end(); it_map++)
	    {
	  		output<<it_map->first<<" "<<it_map->second<<endl;	
			}
		}
	
  	else if(str_order == "-d")
  	{
			_finddata_t file;
			long lf;
			char dir_file[50]="";
			strcat(dir_file, argv[2]);
			strcat(dir_file, "\\*.txt");
			int k=1;
			long HANDLE;
			k = HANDLE = _findfirst(dir_file, &file);
			// k = HANDLE = _findfirst(dir_file, &file);
			cout<<dir_file<<endl<<endl;
			//read every txt in the dir
			while( k != -1 )
			{ 					
				output << file.name << endl;	
				char str_fn[50] ="";
				strcat(str_fn, argv[2]);
				strcat(str_fn, "\\");
				strcat(str_fn, file.name);
				ifstream fn(str_fn);
				while(getline(fn,s))
		    {
		    	//cout<<"succ"<<endl;
		      int len = s.length();
		      transform(s.begin(),s.end(),s.begin(), ::tolower);
		      for(int i=0; i<len; i++)
		      {
		        char ch = s[i];
		        if(isalpha(ch))
		          ++map1[ch];
		      }
		    }
		  				
		    for(it_map=map1.begin(); it_map != map1.end(); it_map++)
		    {
		    	//cout<<it_map->first<<" "<<it_map->second<<endl;
		  		output<<it_map->first<<" "<<it_map->second<<endl;	
				}
				output<<endl<<endl;
				k = _findnext( HANDLE, &file );	
			}
			_findclose( HANDLE );

		}
 }
    
	input.close();
	output.close();
  // cout<<str_order;
  // getchar();
  return 0;
}
