#include <bits/stdc++.h>
using namespace std;

int convertMode(char mode);
void display(std::vector<int> v);

int main(int argc, char **argv)
{
    char filename[100],line[20];
    string s;
    fstream f;
    char mode,r_id;
    int n,t_id;
    std::map< char , std::vector< std::pair<int,int> > > v;

    if(argc!=2)
        cout<<"Usage:"<<endl<<"./executable <input file>"<<endl;
    else
    {
        strcpy(filename, argv[1]);
        f.open(filename,ios::in);
        while(getline(f,s))
        {
            strcpy(line,s.c_str());
            sscanf(line,"%c %d %c",&mode,&t_id,&r_id);
            cout<<line<<endl;
        }
	}

	return 0;
}

int convertMode(char mode)
{
	if(mode=='R')
		return 0;
	else
		return 1;
}

void display(std::vector<int> v)
{
    cout<<"[ ";
    cout<<v[0];
    for(int i=1;i<v.size();i++)
    {
        cout<<",";
        cout<<" "<<v[i];
    }
    cout<<" ]";
    cout<<endl;
}
