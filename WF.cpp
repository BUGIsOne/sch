#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<map>
#include<string>
#include<algorithm>
#include<cstring>
#include<io.h>
#include<iomanip>
#include<vector>
#define LINELENGTH 50

using namespace std;

typedef pair <char, size_t> PAIR;
typedef map <char, size_t> MAP1;
typedef map <string, size_t> MAP2;
typedef pair <string , size_t> PAIR2;

// sort alpha in appeared times
bool cmp(const PAIR &x, const PAIR &y)
{
	if(x.second != y.second)
		return x.second > y.second;
	return x.first < y.first;
}

bool cmp2(const PAIR2 &x, const PAIR2 &y)
{
	if(x.second != y.second)
		return x.second > y.second;
	return x.first < y.first;
}


// total alphas
int total_ch = 0;
// total words
int total_wd = 0;


//count alpha's num in map, copy the map to a vector
vector<PAIR> count_alpha(ifstream &input, string &s, MAP1 &map1)
{
	while(getline(input,s))
	{
		int len = s.length();
		transform(s.begin(),s.end(),s.begin(), ::tolower);
		for(int i=0; i<len; i++)
		{
			char ch = s[i];
			if(isalpha(ch))
			{
				++map1[ch];
				total_ch++;
			}
		}
	}
	vector<PAIR> map_vec(map1.begin(), map1.end());
	sort(map_vec.begin(), map_vec.end(), cmp);

	return map_vec;
}

// split words on a line
void split(string &s, MAP2 &map2)
{
	string word;
	if(s.length()>0)
	{
		int offset = s.find('.');
		if(offset != -1)
			word = s.substr(0, offset-1);
		else
			word = s;
	}
	if(word.length() > 0)
	{
		map2[word]++;
		total_wd++;
	}
}

// count time the word appears in an article
vector<PAIR2> count_word(ifstream &input, string &s, MAP2 &map2)
{
	while(getline(input,s, ' '))
	{
		// cout<<s<<endl;
		transform(s.begin(),s.end(),s.begin(), ::tolower);
		split(s, map2);
	}

	vector<PAIR2> map_vec2(map2.begin(), map2.end());
	sort(map_vec2.begin(), map_vec2.end(), cmp2);

	return map_vec2;
}

int main(int argc, char *argv[])
// int main()
{
  // open file according to argv[2]
  ifstream order(argv[1]);
  ifstream input(argv[2]);
  ofstream output("./output.txt");

	// get string of argv[1]
  string str_order = "";
  int argv1_len = strlen(argv[1]);
  for(int i=0; i<argv1_len; i++)
    str_order += (argv[1][i]);

	// read a line from file
  string s;

  MAP1 map1;
  MAP1::iterator it_map;
	vector<PAIR>::iterator it_vec;

	MAP2 map2;
	MAP2::iterator it_map2;
	vector<PAIR2>::iterator it_vec2;

  string str_line;
  //argv[1].length is right and input is not none
	if(str_order.length() == 2)
  {
		cout<<"Operating "<<str_order<<endl<<endl;
		// '''a test func to count every alpha in an article'''

  	// if(str_order == "-c")
  	// {
		// 	//use count_alpha to get a vector, which key is alpha, and value is times the alpha appears
	  // 	vector<PAIR> tmp_vec = count_alpha(input, s, map1);
	  //   for(it_vec=tmp_vec.begin(); it_vec != tmp_vec.end(); it_vec++)
	  //   {
		// 		float freq = (float)it_vec->second / total_ch;
		// 		freq *= 100;
	  // 		output<<it_vec->first<<" ";
		// 		output<<setiosflags(ios::fixed)<<setprecision(2);
		// 		output<<freq<<"%"<<endl;
		// 	}
		// }
	
		// '''a test func to count every alpha in every article in a directory'''

  	if(str_order == "-c")
  	{
			_finddata_t file;
			long lf;
			char dir_file[50]="";
			strcat(dir_file, argv[2]);
			strcat(dir_file, "\\*.txt");
			int k=1;
			long HANDLE;
			k = HANDLE = _findfirst(dir_file, &file);

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
				//use count_alpha to get a vector, which key is alpha, and value is times the alpha appears
				vector<PAIR> tmp_vec = count_alpha(fn, s, map1);

		    for(it_vec=tmp_vec.begin(); it_vec != tmp_vec.end(); it_vec++)
		    {
		    	float freq = (float)it_vec->second / total_ch;
					freq *= 100;
		  		output<<it_vec->first<<" ";
					output<<setiosflags(ios::fixed)<<setprecision(2);
					output<<freq<<"%"<<endl;
				}
				output<<endl<<endl;
				k = _findnext( HANDLE, &file );	
			}
			_findclose( HANDLE );

		}

		else if(str_order == "-f")
		{
			vector<PAIR2> tmp_vec2 = count_word(input, s, map2);

			for(it_vec2=tmp_vec2.begin(); it_vec2 != tmp_vec2.end(); it_vec2++)
	    {
				float freq = (float)it_vec2->second / total_wd;
				freq *= 100;
	  		output<<it_vec2->first<<" ";
				output<<setiosflags(ios::fixed)<<setprecision(2);
				output<<freq<<"%"<<endl;
			}
		}

		else if(str_order == "-d")
  	{
			_finddata_t file;
			long lf;
			char dir_file[100]="";
			strcat(dir_file, argv[2]);
			strcat(dir_file, "\\*.txt");
			int k=1;
			long HANDLE;
			k = HANDLE = _findfirst(dir_file, &file);
			
			cout<<dir_file<<endl<<endl;
			//read every txt in the dir
			while( k != -1 )
			{ 					
				map2.clear();
				total_wd =  0;
				
				output << file.name << endl;	
				char str_fn[100] ="";
				strcat(str_fn, argv[2]);
				strcat(str_fn, "\\");
				strcat(str_fn, file.name);
				ifstream fn(str_fn);
				
				vector<PAIR2> tmp_vec2 = count_word(fn, s, map2);
				
		    for(it_vec2=tmp_vec2.begin(); it_vec2 != tmp_vec2.end(); it_vec2++)
		    {
		    	float freq = (float)it_vec2->second / total_wd;
					freq *= 100;
		  		output<<it_vec2->first<<" ";
					output<<setiosflags(ios::fixed)<<setprecision(2);
					output<<freq<<"%"<<endl;
				}
				output<<endl<<endl;
				k = _findnext( HANDLE, &file );	
			}
			_findclose( HANDLE );

		}

 }
    
	input.close();
	output.close();

  return 0;
}
