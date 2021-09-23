#include<locale>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct MGC
{
	int line = 0;
	wstring b, m;
}find[10005];//创建结构体，记录敏感词 
int main()
{
	struct MGC find[10005];
	locale china("zh_CN.UTF-8");//设置地区，保证中文可读 
	string words,orgs,answer;
	cin>>words;
	cin>>orgs;
	cin>>answer;
	wifstream infile2;
	infile2.open(orgs);
	infile2.imbue(china);
	wstring a;
	unsigned int line=0,total=0;
	wofstream woutfile;//输出 
	woutfile.open(answer);
	woutfile.imbue(china);//输出中文
	while(getline(infile2,a))//用来读入一行待检测文件
	{
		line++;
		for(unsigned int i=0; i<a.size();i++){
			wifstream infile1;
			infile1.open(words);//输入敏感词 
			infile1.imbue(china);
			wstring b;
			while(getline(infile1,b))//读取敏感词
			{
				if((a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z'))//英文检测 
				{
					unsigned int k=0,len=0,count;
					while (k<b.size()&&i+len<a.size())
					{
						if(b[k]==a[i+len]||b[k]==a[i+len]+32||b[k]==a[i+len]-32)
							k++,len++,count=0;
						else
						{
							if(a[i+len]>=0&&a[i+len]<=126
								&&!((a[i+len]>='a'&&a[i+len]<='z')||(a[i+len]>='A'&&a[i+len]<='Z'))&& k!= 0) //检测为敏感词，记录 
								len++,count++;
							else break;
							if(count>20) break;
						}
					}
					if(k==b.size()){
						find[total].line = line;
						find[total].b = b;
						for(unsigned int k=i;k<i+len;k++)
						{//输出检测到的敏感词
							if(k==0)find[total].m=a[k];
							else find[total].m+=a[k];
						}
						total++;
					}
				}
				else{
					unsigned int k=0,len=0,count=0;
					while(k<b.size()&&i+len<a.size())
					{
						if(b[k]==a[i+len])
							k++,len++,count=0;
						else
						{
							if(a[i+len]>=0&&a[i+len]<=126
								&&!((a[i+len]>='a'&&a[i+len]<='z')||(a[i+len]>='A'&&a[i+len]<='Z'))&&k!=0)
								len++,count++;
							else break;
						}
						if(count>20) break;
					}
					if(k== b.size()){
						find[total].line=line;
						find[total].b=b;
						for(unsigned int k=i;k<i+len;k++)
						{//输出检测到的敏感词 
							if(k==0)find[total].m=a[k];
							else find[total].m+=a[k];
						}
						total++;
					}
				}
			}
		}
	}
	woutfile<<"Total:"<<total<<endl;
	for(unsigned int i=0;i<total;i++){
		woutfile<<"Line"<<find[i].line<<": <";
		woutfile<<find[i].b;
		woutfile<<"> ";//输出
		woutfile<<find[i].m;
		woutfile<<endl;
	}
	woutfile.close();
	return 0;
}
