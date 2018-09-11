#include<bits/stdc++.h>
using namespace std;
#define CLR(a) memset(a,0,sizeof(a))
#define CCLR(a) memset(a,'0',sizeof(a))
using namespace std;
typedef long  l;
class BigInteger
{
public:
    string value;
    l size;
    BigInteger(){

    }
    BigInteger(string value){
        this->value=value;
        size=value.size();
    }
    BigInteger add( BigInteger b);
    BigInteger subtract( BigInteger b);
    BigInteger multipy( BigInteger b);
    BigInteger divide( BigInteger b);
    BigInteger remainder( BigInteger b);
    string gcd( BigInteger b);
    bool greater(BigInteger b);
};

bool BigInteger:: greater(BigInteger b){
string val1=value;
string val2=b.value;
val2.erase(0, min(val2.find_first_not_of('0'), val2.size()-1));
bool negative;
    if(val2.size()>val1.size()){
        negative=false;
        return negative;}
    else if(val2.size()<val1.size()){
        negative=true;
        return negative;}
    else{
        for(l i=0; i<val1.size(); i++){
            if (val1[i]<val2[i]){
                negative=false;
                return negative;
            }
            else if (val1[i] > val2[i]){
                negative=true;
                return negative;
            }
        }        
    }
    return false;
}

string BigInteger:: gcd(BigInteger b){
    BigInteger temp;
    // b.value.erase(0, min(b.value.find_first_not_of('0'), b.value.size()-1));
    // value.erase(0, min(value.find_first_not_of('0'), value.size()-1));
    while(b.value!="0"){
        temp=this->remainder(b);
        value=b.value;
        b.value=temp.value;
        b.value.erase(0, min(b.value.find_first_not_of('0'), b.value.size()-1));    
    }
    return value;
    //return new BigInteger(s);

}

BigInteger BigInteger:: divide(BigInteger b){
    BigInteger zero("0");
    string val1=(value);
    string val2=(b.value);
    val1.erase(0, min(val1.find_first_not_of('0'), val1.size()-1));
    val2.erase(0, min(val2.find_first_not_of('0'), val2.size()-1));
    if(val1.size()<val2.size()||!this->greater(b))
        return zero;
    BigInteger quotient("0");
    BigInteger one("1");
    BigInteger c("0");
    l i=0;
    
    while(i<val1.size()){
        c.value=c.value+val1.substr(i,1);
        BigInteger temp("0");
        c.value.erase(0, min(c.value.find_first_not_of('0'), c.value.size()-1));
        while(c.greater(b)||c.value==b.value){
            c=c.subtract(b);
            temp=temp.add(one);
        }
        if(temp.value!="0")
            quotient.value=quotient.value+temp.value;
        else if(temp.value=="0")
            quotient.value=quotient.value+"0";
        i++;
    }
    quotient.value.erase(0, min(quotient.value.find_first_not_of('0'), quotient.value.size()-1));
    return quotient;
}

BigInteger BigInteger:: remainder(BigInteger b){
    BigInteger zero("0");
    string val1=(value);
    string val2=(b.value);
    // val1.erase(0, min(val1.find_first_not_of('0'), val1.size()-1));
    // val2.erase(0, min(val2.find_first_not_of('0'), val2.size()-1));
    BigInteger c("0");
    l i=0;
    while(i<val1.size()){
        c.value=c.value+val1.substr(i,1);
        c.value.erase(0, min(c.value.find_first_not_of('0'), c.value.size()-1));
        while(c.greater(b)||c.value==b.value){
            c=c.subtract(b);
        }
        i++;
        // cout<<"c="<<c.value<<"i="<<i<<"\n";
    }
    c.value.erase(0, min(c.value.find_first_not_of('0'), c.value.size()-1));
    return c;
}

BigInteger BigInteger:: multipy(BigInteger b){
    l rSize=size>b.size?size:b.size;
    string val1=(value);
    val1.erase(0, min(val1.find_first_not_of('0'), val1.size()-1));
    string val2=(b.value);
    val2.erase(0, min(val2.find_first_not_of('0'), val2.size()-1));
    if(val1.size()<val2.size())
        swap(val1,val2);
    reverse(val1.begin(),val1.end());
    reverse(val2.begin(),val2.end());
    char result[rSize*2];
    CCLR(result);
    l carry=0,k=0,temp;
    for(l i=0;i<val2.size();i++){
        k=i;
        for(l j=0;j<val1.size();j++,k++){
            temp=(result[k]-48)+carry+(val1[j]-48)*(val2[i]-48);
            result[k]=temp%10+48;
            if(temp>=10){
                carry=temp/10;
            }
            else{
                carry=0;
            }

        }    
        if(carry){
            result[k++]=carry+48;
            carry=0;
        }
    }
    result[k]='\0';
    string result1(result);
    //result1.erase(0, min(result1.find_first_not_of('0'), result1.size()-1));
    reverse(result1.begin(),result1.end());
    return BigInteger(result1);
}


BigInteger BigInteger:: add(BigInteger b){
    l rSize=size>b.size?size:b.size;
    string val1=(value);
    val1.erase(0, min(val1.find_first_not_of('0'), val1.size()-1));
    string val2=(b.value);
    val2.erase(0, min(val2.find_first_not_of('0'), val2.size()-1));
    reverse(val1.begin(),val1.end());
    reverse(val2.begin(),val2.end());
    char result[rSize+2];
    CCLR(result);
    l i=0,carry=0;
    while((i<val1.size())&&(i<val2.size())){        
        result[i]=(carry+val1[i]+val2[i]-96)%10+48;
        if((carry+val1[i]+val2[i]-96)>=10)
            carry=1;
        else
            carry=0;
        i++;
    }
    while(i<val1.size()){
        result[i]=(carry+val1[i]-48)%10+48;
        if((carry+val1[i]-48)>=10)
            carry=1;
        else
            carry=0;
        i++;
    }
    while(i<val2.size()){
        result[i]=(carry+val2[i]-48)%10+48;
        if((carry+val2[i]-48)>=10)
            carry=1;
        else
            carry=0;
        i++;
    }
    if(carry)
        result[i++]=carry+48;
    result[i]='\0';
    i=0;
    string result1(result);
    reverse(result1.begin(),result1.end());
    return BigInteger(result1);
}
BigInteger BigInteger:: subtract(BigInteger b){
    string val1=value;
    string val2=b.value;
    val1.erase(0, min(val1.find_first_not_of('0'), val1.size()-1));
    val2.erase(0, min(val2.find_first_not_of('0'), val2.size()-1));
    bool negative=(val2.size()>val1.size()?true:false);
    if(val2.size()>val1.size())
        negative=true;
    else if(val2.size()<val1.size())
        negative=false;
    else{
        for(l i=0; i<val1.size(); i++){
            if (val1[i]<val2[i]){
                negative=true;break;
            }
            else if (val1[i] > val2[i]){
                negative=false;break;
            }
        }
            
    }
    l rSize=(negative?val2.size():val1.size());
    if(negative)
        swap(val1,val2);
    reverse(val1.begin(),val1.end());
    reverse(val2.begin(),val2.end());
    char result[rSize+2];
    CCLR(result);
    l i=0,carry=0;
    while((i<val1.size())&&(i<val2.size())){        
        if((carry+val1[i]-48)<(val2[i]-48)){
            result[i]=(carry+val1[i]-48)+10-(val2[i]-48)+48;
            carry=-1;
        }
        else{
            result[i]=(carry+val1[i]-48)-(val2[i]-48)+48;
            carry=0;
        }
        i++;
    }
    while(i<val1.size()){
        if(val1[i]=='0'&&carry==-1){
            result[i]=(carry+10)+48;
            carry=-1;
        }
        else{
            result[i]=(carry+val1[i]-48)+48;
            carry=0;
        }
        i++;
    }
    if(carry||negative)
        result[i++]='-';
    result[i]='\0';
    i=0;
    string result1(result);
    reverse(result1.begin(),result1.end());
    if(result1[0]!='-')
        result1.erase(0, min(result1.find_first_not_of('0'), result1.size()-1));
    else{
        result1=result1.substr(1,result1.size()-1);
        result1.erase(0, min(result1.find_first_not_of('0'), result1.size()-1));
        result1='-'+result1;
    }
    //cout<<result1;
    return BigInteger(result1);
}
int main() {
    //freopen("output.txt","w",stdout);
    l t,op;
    cin>>t;
    string val1,val2;
    BigInteger a();
    BigInteger b();
    BigInteger c;
    while(t--){
        cin>>val1;
        cin>>val2;
        cin>>op;
        BigInteger a(val1);
        BigInteger b(val2);
        switch(op){
            case 1: 
                if(a.value[0]=='-'&&b.value[0]=='-'){
                    a.value=a.value.substr(1,a.value.size());
                    b.value=b.value.substr(1,b.value.size());
                    c=a.add(b);
                    if(c.value!="0")
                        c.value="-"+c.value;
                }
                else if(a.value[0]=='-'){
                    a.value=a.value.substr(1,a.value.size());
                    c=b.subtract(a);
                }
                else if(b.value[0]=='-'){
                    b.value=b.value.substr(1,b.value.size());
                    c=a.subtract(b);
                }
                else
                    c=a.add(b);

                break;
            case 2: 
                if(a.value[0]=='-'&&b.value[0]=='-'){
                        a.value=a.value.substr(1,a.value.size());
                        b.value=b.value.substr(1,b.value.size());
                        c=b.subtract(a);
                    }
                    else if(a.value[0]=='-'){
                        a.value=a.value.substr(1,a.value.size());
                        c=a.add(b);
                        c.value="-"+c.value;
                    }
                    else if(b.value[0]=='-'){
                        b.value=b.value.substr(1,b.value.size());
                        c=a.add(b);
                    }
                    else
                        c=a.subtract(b);

                break;
            case 3: 
                    if(a.value[0]=='-'&&b.value[0]=='-'){
                        a.value=a.value.substr(1,a.value.size());
                        b.value=b.value.substr(1,b.value.size());
                        c=a.multipy(b);
                    }
                    else if(a.value[0]=='-'){
                        a.value=a.value.substr(1,a.value.size());
                        c=a.multipy(b);
                        if(c.value!="0")
                            c.value="-"+c.value;
                    }
                    else if(b.value[0]=='-'){
                        b.value=b.value.substr(1,b.value.size());
                        c=a.multipy(b);
                        if(c.value!="0")
                            c.value="-"+c.value;
                    }
                    else
                        c=a.multipy(b);
                break;
            case 4: 
                    if(a.value[0]=='-'&&b.value[0]=='-'){
                        a.value=a.value.substr(1,a.value.size());
                        b.value=b.value.substr(1,b.value.size());
                        c=a.divide(b);
                    }
                    else if(a.value[0]=='-'){
                        a.value=a.value.substr(1,a.value.size());
                        c=a.divide(b);
                        if(c.value!="0")
                            c.value="-"+c.value;
                    }
                    else if(b.value[0]=='-'){
                        b.value=b.value.substr(1,b.value.size());
                        c=a.multipy(b);
                        if(c.value!="0")
                            c.value="-"+c.value;
                    }
                        c=a.divide(b);
                break;
            case 5: 
                    if(a.value[0]=='-'&&b.value[0]=='-'){
                        a.value=a.value.substr(1,a.value.size());
                        b.value=b.value.substr(1,b.value.size());
                    }
                    else if(a.value[0]=='-'){
                        a.value=a.value.substr(1,a.value.size());
                    }
                    else if(b.value[0]=='-'){
                        b.value=b.value.substr(1,b.value.size());
                    }                    
                    else
                        c.value=a.gcd(b);//a.greater(b)?a.gcd(b):b.gcd(c);
                break;
        }
        cout<<c.value<<"\n";
    }
    return 0;
}
