#include<bits/stdc++.h>
using namespace std;
#define CLR(a) memset(a,0,sizeof(a))
#define CCLR(a) memset(a,'0',sizeof(a))
using namespace std;
typedef long long l;
l heapSize=0L;
vector <string> tempFileNames;
vector<ifstream*> tempFiles;
struct HeapN
{	int value;
	ifstream* fName;
};

HeapN *heapData=new HeapN[1000000];

void printHeap(){
	for (int i = 0; i < heapSize; ++i){
		cout<<heapData[i].value<<"\n";
	}		
}

l leftC(l p){
    return 2*p+1;
}
l parent(l c){
    return (c-1)/2;
}
l rightC(l p){
    return 2*p+2;   
}
void minHeapify(l n,l i,l k){
    l left=leftC(i);
    l right=rightC(i);
    l min=i;
    if(left<n&&heapData[left].value<heapData[i].value)
        min=left;
    if(right<n&&heapData[min].value>heapData[right].value)
        min=right;
    if(min!=i){
        swap(heapData[i],heapData[min]);
        minHeapify(n,min,k);
    }
}

void buildHeap(l k){
	l temp=(heapSize/2)-1;
	while(temp>=0){
		minHeapify(heapSize,temp,k);
		temp--;
	}
}


void openTemp(){
	 for (size_t i=0; i < tempFileNames.size(); ++i) {
        ifstream *file;
        file = new ifstream(tempFileNames[i].c_str(),ios::in);
        if (file->good() == true) 
            tempFiles.push_back(file);
    }
}
void closeTemp(){

	for (size_t i=0; i < tempFiles.size(); ++i) {
        tempFiles[i]->close();
        delete tempFiles[i];
    }
    for (size_t i=0; i < tempFileNames.size(); ++i) {
        remove(tempFileNames[i].c_str()); 
	}
}

//Change the same input file to have sorted chunks of k
void sortedChunks(char *iFile,char *ouFile, l k){
	l num;
	l a[k],i=0,index=0,tmpCount=1;//index contains the total size
	ifstream myfile(iFile,ios_base::in);
	ofstream ofile(iFile,ios_base::in);
	ofstream outfile(ouFile,ios_base::out);
	while(myfile >> num){
		if(i==k){
			sort(a,a+k);
			

			//create temp files
			stringstream tempFileSS;
			tempFileSS <<"./abcd"<<tmpCount++<<".txt";
		 	string tempFileName = tempFileSS.str();
			ofstream *output;
		 	output = new ofstream(tempFileName.c_str(), ios::out);

			for (l j = 0; j < k; ++j){
				*output << a[j] << endl;
			}
			i=0;
			output->close();
			delete output;
			tempFileNames.push_back(tempFileName);
		}
		a[i]=num;
		i++;
		index++;
	}
	// cout<<index<<"\n";
	//last chunk
	sort(a,a+i);//last chunk may b of k or <k (info from i)

	//create temp files
	stringstream tempFileSS;
	tempFileSS <<"./abcd"<<tmpCount++<<".txt";
 	string tempFileName = tempFileSS.str();
	ofstream *output;
 	output = new ofstream(tempFileName.c_str(), ios::out);

	for (l j = 0; j < i; ++j){
		*output << a[j] << endl;//writing to output temp file
	}

	output->close();
	delete output;
	tempFileNames.push_back(tempFileName);
	
	//////////////// mergee
	
	openTemp();//load ifstreams of temp files
	
	//create array of headnodes from first values in each temp files
	for (l x = 0; x < tempFiles.size(); ++x) {
        *tempFiles[x] >>num;
        heapData[heapSize].value=num;
		heapData[heapSize].fName=tempFiles[x];
		heapSize++;
	}

	//Min heapify property enoforced
	buildHeap(k);

	long long t=0;
	while (t<index) {
		// printHeap();
		// cout<<"\n";
		l num2;
		l top = heapData[0].value;
		ifstream* ifs=heapData[0].fName;
		outfile <<top<< endl;
		*(ifs)>>num2;
		if (*(ifs)){
			heapData[0].value=num2;
			heapData[0].fName=ifs;
			minHeapify(heapSize,0,k);
		}
		else{
			heapData[0].value=heapData[heapSize-1].value;
			heapData[0].fName=heapData[heapSize-1].fName;
			minHeapify(heapSize,0,k);
			heapSize--;
		}
		t++;
	}

	//close and delete temp files
	closeTemp();

}

int main(int len,char **args){
	l k=1000000;
	heapSize=0;
	sortedChunks(args[1],args[2],k);

}

