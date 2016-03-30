#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <bitset>
#include <fstream>
#include <time.h>
#include <queue>
#define MAXSIZE 87
#define WORKLEN 16
using namespace std;

bitset<32> b;
bitset<MAXSIZE> bitslides[32];
bitset<MAXSIZE> Potential;
bitset<MAXSIZE> Certain;

unsigned int string_to_unsigned_int(string str)
{
	unsigned int result(0);
	for (int i = str.size()-1;i >= 0;i--)
	{
		unsigned int temp(0),k = str.size() - i - 1;
		if (isdigit(str[i]))
		{
			temp = str[i] - '0';
			while (k--)
				temp *= 10;
			result += temp;
		}
		else
			break;
	}
	return result;
}

class Item
{
public:
  Item(unsigned int,string,string,string,unsigned int);
  void show();
	unsigned int get_value();
  //void change();
private:
  unsigned int id;
  string type;
  string statecode;
  string city;
  unsigned int value;
};

Item::Item(unsigned int id,string type,string statecode,string city,unsigned int value)
{
  this->id = id;
  this->type = type;
  this->statecode = statecode;
  this->city = city;
  this->value = value;
}

void Item::show()
{
  cout<< this->id<<"  "<<this->type<<"  "<<this->statecode<<"  "<<this->city<<"  "<<this->value<<endl;
}

unsigned int Item::get_value()
{
	return this->value;
}

class SampleBlock
{
public:
  SampleBlock(char);
  void add(Item good);
  void show();
	int get_size();
	Item get_Item(int);
private:
  int size;
  vector<Item> S;
  int QcsCode;
};


SampleBlock::SampleBlock(char code)
{
  this->size = 0;
  this->QcsCode = code;
  this->S.clear();
}
void SampleBlock::add(Item good)
{
  (this->size)++;
  this->S.push_back(good);
}

void SampleBlock::show() {
  cout<<"The size of the sample block is "<<this->size<<endl;
  cout<<"The sample code is "<<this->QcsCode<<endl;
  int i;
  for(i=0;i<this->size;++i)
    this->S[i].show();
}

int SampleBlock::get_size()
{
	return this->size;
}

Item SampleBlock::get_Item(int i)
{
	return this->S[i];
}

class Sample
{
public:
  Sample(string);
  void show();
  void GeneBit();
  void query();
  void select();
  void sum();
  void bit_sum();
  void mean();
  void bit_mean();
  void Max();
  void bit_max();
  void topK(int);
  void bit_topk(int);
private:
  string properity[5];
  vector<SampleBlock> Sample_Vector;
  int size;
  vector<unsigned int> selection;
};

Sample::Sample(string filename)
{
  //filename is the direction of file
  this->selection.clear();
  this->Sample_Vector.clear();
  ifstream sampleFile;
  sampleFile.open("test.csv");
  if(sampleFile.fail())
  {
    cout << "FILE dose not exist" <<endl;
    cout << "Exit program!"       <<endl;
  }

  char buf[100];
  int cnt =0;
  int code = 0;
  SampleBlock *pSb = new SampleBlock(0);
  Item *pItem;
  while(!sampleFile.eof())
  {
    cnt++;
    //cout<<cnt<<endl;
    sampleFile.getline(buf,100);

    if(cnt==2){
      this->size = atoi(buf);
    }
    else if(cnt==1)
    {
      const char * split = ",";
      char *p = strtok(buf,split);
      int pos = 0;
      while(p!=NULL){
        this->properity[pos++]=p;
        p = strtok(NULL,split);
      }
    }

    else
    {
      //cout<<buf<<endl;
      if(buf[0]=='#'){
      //  cout<<"Push sample block!"<<endl;
        this->Sample_Vector.push_back(*pSb);
        code++;
        pSb = new SampleBlock(code);
      //  (*pSb).show();
      //  this->Sample_Vector[0].show();

        if(buf[1]=='#')
          break;
      }
      else{
        //cout<<"Generate sample block!"<<endl;
        string strbuf[5];

        const char * split = ",";
        char *p = strtok(buf,split);
        int pos = 0;
        while(p!=NULL){
          strbuf[pos++] = p;
          p = strtok(NULL,split);
        }
        /*int i;
        for(i=0;i<5;i++){
          cout<<strbuf[i]<<"  ";
        }
        */
        //cout<<endl;
        unsigned int id_tmp = string_to_unsigned_int(strbuf[0]);
        unsigned int value_tmp = string_to_unsigned_int(strbuf[4]);
        pItem = new Item(id_tmp,strbuf[1],strbuf[2],strbuf[3],value_tmp);
        (*pSb).add(*pItem);
      }
    }

  }

  sampleFile.close();

  cout<<"Done!"<<endl;

}

void Sample::show()
{
  cout<<"The sample size is "<<this->size<<" !"<<endl;
  int i;
  for(i=0;i<5;++i)
  {
    cout<<this->properity[i]<<"  ";
  }
  cout<<endl;

  int vol = this->Sample_Vector.size();
  for(i=0;i<vol;i++){
    this->Sample_Vector[i].show();
  }
}

void Sample::query()
{
  this->select();
	this->GeneBit();
	this->sum();
	this->bit_sum();
  this->mean();
  this->bit_mean();
  this->Max();
  this->bit_max();
  this->topK(50);
	this->bit_topk(50);
	this->selection.clear();
}

void Sample::select()
{
  int vol = this->Sample_Vector.size();
  int item_size;
  int i,j;
	unsigned int tmp;
  SampleBlock *pSb;

  for(i=1;i<vol;++i)
  {
    item_size = this->Sample_Vector[i].get_size();
    pSb = &(this->Sample_Vector[i]);
	//	cout<<item_size<<endl;
		for(j=0;j<item_size;++j){
			tmp = (*pSb).get_Item(j).get_value();
			this->selection.push_back(tmp);
		}
  }

	/*
	for(i=0;i<this->selection.size();++i)
		cout<<selection[i]<<endl;
		*/
}

void Sample::GeneBit()
{
	int i,j;
	for(i=0;i<32;++i)
		bitslides[i].reset();

	int len = this->selection.size();
	//cout<<"Here!"<<endl;
	for(i=0;i<len;++i){
		b = selection[i];
		for(j=31;j>=0;--j)
			bitslides[32-j-1][i] = b[j];
	}

	//cout<<endl<<endl;
	//for(i=0;i<32;++i)
		//cout<<bitslides[i]<<endl;

	//cout<<endl<<endl;
}

void Sample::sum()
{
	ofstream sumfile;
	string s("configure here!");

	unsigned long long sum=0;
	int i;
	int len = this->selection.size();
	clock_t start,end;
	double duration;

	start = clock();

	int m=1000000;

	while(m--)
		for(i=0;i<len;++i)
			sum+=this->selection[i];

	end = clock();

	duration = (end - start)*1.0/CLOCKS_PER_SEC/1000000;
	sumfile.open("sum.txt");
	sumfile<<"The result of sum is as below:"<<endl;
	sumfile<<"The sum of the sample is: "<<sum/1000000<<endl;
	sumfile<<"Using time totally: "<<duration<<"_ms"<<endl;
	sumfile<<"The configure is :"<<s<<endl;

	sumfile.close();
}

void Sample::bit_sum()
{
	int i;
	ofstream bsumfile;
	string s("configure here!");

	unsigned long long sum = 0;
	//unsigned int tmp;

	clock_t start,end;
	double duration;

	start = clock();
	for(i = 0 ;i < WORKLEN;++i){
		sum = (sum << 1) + bitslides[i].count();
	}

	sum = sum << (32 - WORKLEN);
	end = clock();
	duration = (end - start)*1000000.0/CLOCKS_PER_SEC/1000000;
	bsumfile.open("bit_sum.txt");
	bsumfile<<"The result of sum using bitslice is as below:"<<endl;
	bsumfile<<"The working bits is "<<WORKLEN <<endl;
	bsumfile<<"The sum of the sample is: "<<sum<<endl;
	bsumfile<<"Using time totally: "<<duration<<"_ms"<<endl;
	bsumfile<<"The configure is :"<<s<<endl;

	bsumfile.close();
}

void Sample::mean()
{
	ofstream sumfile;
	string s("configure here!");

	unsigned long long tmp=0;

	int i;
	int len = this->selection.size();
	clock_t start,end;
	double duration;

	start = clock();

	int m=1000000;

	while(m--){
		tmp = 0;
		for(i=0;i<len;++i)
			tmp+=this->selection[i];

		tmp = tmp * 1.0/len;
	}

	end = clock();

	duration = (end - start)*1.0/CLOCKS_PER_SEC/1000000;
	sumfile.open("mean.txt");
	sumfile<<"The result of mean is as below:"<<endl;
	sumfile<<"The mean of the sample is: "<<tmp<<endl;
	sumfile<<"Using time totally: "<<duration<<"_ms"<<endl;
	sumfile<<"The configure is :"<<s<<endl;

	sumfile.close();
}

void Sample::bit_mean()
{
	ofstream bsumfile;
	string s("configure here!");

	unsigned long long sum = 0;
	unsigned int tmp;
	int i,j;
	int len = this->selection.size();
	clock_t start,end;
	double duration;
	/*for(i=0;i<len;++i){
		tmp = selection[i];
		b = tmp;
		for(j=0;j<32;++j)
			bitslides[j][i] = b[i];
	}*/

	start = clock();
	for(i = 0 ;i < WORKLEN;++i){
		sum = (sum << 1) + bitslides[i].count();
	}

	sum = sum << 16;
	end = clock();
	duration = (end - start)*1000000.0/CLOCKS_PER_SEC/1000000;
	bsumfile.open("bit_mean.txt");
	bsumfile<<"The result of sum using bitslice is as below:"<<endl;
	bsumfile<<"The working bits is "<<WORKLEN <<endl;
	bsumfile<<"The sum of the sample is: "<<sum*1.0/len<<endl;
	bsumfile<<"Using time totally: "<<duration<<"_ms"<<endl;
	bsumfile<<"The configure is :"<<s<<endl;

	bsumfile.close();
}

void Sample::Max()
{
	ofstream sumfile;
	string s("configure here!");

	unsigned long long MAX=0;

	int i;
	int len = this->selection.size();
	clock_t start,end;
	double duration;

	start = clock();

	for(i=0;i<len;++i)
		if(selection[i]>MAX)
			MAX = selection[i];

	end = clock();

	duration = (end - start)*1000000.0/CLOCKS_PER_SEC/1000000;
	sumfile.open("MAX.txt");
	sumfile<<"The result of MAX is as below:"<<endl;
	sumfile<<"The MAX of the sample is: "<<MAX<<endl;
	sumfile<<"Using time totally: "<<duration<<"_ms"<<endl;
	sumfile<<"The configure is :"<<s<<endl;

	sumfile.close();
}

void Sample::bit_max()
{
	int i;
	ofstream maxfile;
	string s("configure here!");
	clock_t start,end;
	double duration;
	bitset<MAXSIZE> NextResult;
	int NumOnes;
	int pos;
	unsigned int MAX=0;

	start = clock();
	Potential.set();
	for(i = 0;i < WORKLEN;i++){
		NextResult = Potential & bitslides[i];
		//cout<<Potential<<endl;
		//cout<<NextResult<<endl;
		NumOnes = NextResult.count();
		if(NumOnes >= 1)
			Potential = NextResult;
		if(NumOnes == 1)
			break;
	}
	for(i=0;i<MAXSIZE;++i){
		if(Potential.test(i))
			break;
	}
	pos = i;
	//cout<< pos<<endl;
	b.reset();
	//cout<<b<<endl;
	for(i = 0;i < 32;++i)
		b[31-i] = bitslides[i][pos];

	//cout<<b<<endl;
	MAX = b.to_ulong();

	end = clock();
	duration = (end - start)*1000000/CLOCKS_PER_SEC/1000000;
	maxfile.open("BITMAX.txt");
	maxfile<<"The result of MAX using bitslice is as below:"<<endl;
	maxfile<<"The MAX of the sample is: "<<MAX<<endl;
	maxfile<<"Using time totally: "<<duration<<"_ms"<<endl;
	maxfile<<"The configure is :"<<s<<endl;

	maxfile.close();
}

void Sample::topK(int k)
{
	ofstream topfile;
	string s("configure here!");

	int i;
	int len = this->selection.size();
	//cout<< this->selection.size()<<endl;
	clock_t start,end;
	double duration;
  priority_queue<unsigned int> q;
	vector<unsigned int> result;
	while(!q.empty())
		q.pop();
	result.clear();

	start = clock();

	for(i=0;i<len;++i)
		q.push(selection[i]);


	//##q.size() == 87  It is right!!
	for(i=0;i<k;++i){
		result.push_back(q.top());
		q.pop();
	}

	end = clock();

	while(!q.empty()){
		q.pop();
	}
	//cout<<"point!!!!"<<endl;
	duration = (end - start)*1000000.0/CLOCKS_PER_SEC/1000000;

	topfile.open("topK.txt");
	topfile<<"The result of top "<<k<<"is as below:"<<endl;

	for(i=0;i<k;i++){
		topfile<<result[i]<<" ";
		if(i%10==9)
			topfile<<endl;
	}

	result.clear();
	topfile<<"Using time totally: "<<duration<<"_ms"<<endl;
	topfile<<"The configure is :"<<s<<endl;

	topfile.close();
}

void Sample::bit_topk(int k)
{
	int NumTopFound;
	int NumOnes;
	int i,j;
	int pos;
	int ApprRes;
	string s("configure here!");
	clock_t start,end;
	double duration;
	bitset<MAXSIZE> NextResult;
	vector<int> TopRes;
	vector<unsigned int> TopVec;
	TopRes.clear();

	start = clock();

	Potential.set();
	Certain.reset();
	NumTopFound = 0;
	for(i = 0;i < WORKLEN;++i)
	{
		NextResult = Potential & bitslides[i];
		NumOnes = NextResult.count();
		if(NumOnes <= k - NumTopFound){
			Certain = Certain | NextResult;
			Potential = Potential & (~NextResult);
			NumTopFound += NumOnes;
		}
		else{
			Potential = NextResult;
		}

		if(NumTopFound == k)
			break;
	}

	for(i=0;i<MAXSIZE;++i)
		if(Certain.test(i))
			TopRes.push_back(i);

	ApprRes = k - NumTopFound;
	i=0;
	while(ApprRes--)
		if(Potential.test(i))
			TopRes.push_back(i++);


	TopVec.clear();
	//cout<< TopRes.size() <<"  "<<k<<endl;
	/*for(i= 0;i<k;i++){
		cout<<TopRes[i]<<endl;
	}
	*/
	for(i=0;i<k;++i){
		pos = TopRes[i];
		cout<< i <<" "<<pos<<endl;
		for(j = 0;j < 32;++j)
			b[31-j] = bitslides[j][pos];
		TopVec.push_back(b.to_ulong());
	}
	end = clock();

	duration = (end - start)*1000000.0/CLOCKS_PER_SEC/1000000;
	ofstream BitTopFile;
	BitTopFile.open("BitTop.txt");
	BitTopFile <<"The result of top "<<k<<"using bitset is as below:"<<endl;

	for(i=0;i<k;i++){
		BitTopFile<<TopVec[i]<<" ";
		if(i%10==9)
			BitTopFile<<endl;
	}

	TopVec.clear();
	BitTopFile<<"Using time totally: "<<duration<<"_ms"<<endl;
	BitTopFile<<"The configure is :"<<s<<endl;
	BitTopFile.close();
}

int main()
{
  string s = "test.csv";
  Sample sam(s);
  //sam.show();
	sam.query();

  return 0;
}
