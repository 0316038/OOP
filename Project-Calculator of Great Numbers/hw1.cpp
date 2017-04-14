#include<iostream>
#include<fstream>
#include<string.h>
#include <cmath>

using namespace std;



class Great{

private:
    int num[100];
    bool sign=true;    /*** sign=true 為正數，false 為負數 ***/
    int length=0;

public:
    Great(){
        for(int i=0; i<100; i++){
            num[i]=0;
        }
        //memset(num, 0, 100);/***歸零***/
    };

    Great(string a){
                                            /*** 倒過來存***/
        if(a.length()==1 && a[0]=='0'){       /** 如果輸入的字串是 "0",length = 0 **/
            length=0;
        }

        else{

            for(int i=a.length()-1;i>=0;i--){
                if(a[i]=='-'){sign=false;}
                int x=a[i]-'0';
                if(x>=0&&x<10)
                    num[length++]=x;
            }
        }
        for(int i=length; i<100; i++){
            num[i]=0;
        }
        /*if(sign){
            length=a.length();
        }else if(!sign){
            length=a.length()-1;
        }*/
        /*for(int i=0;i<length;i++){
            if(num[i]==0){
                length--;
            }
        }*/
    }

    Great (int a){
        if(a<0){
            sign=false;
            a=abs(a);
            int i;
            for(i=0;a!=0;i++){
               num[i]=a%10;
               a=a/10;
            }
            length=i;
        }
        else if(a>0){
            sign=true;
            int i;
            for(i=0;a!=0;i++){
               num[i]=a%10;
               a=a/10;
            }
            //cout<<num[i-1]<<endl;
            length=i;
        }
    }

    int compare(Great a, Great b){
        if(a.length>b.length) return 1;
        else if(a.length<b.length) return -1;
        else if(a.length==b.length){
            int i;
            for(i=a.length-1;i>=0;i--){
                if(a.num[i]>b.num[i]){
                    return 1;
                    break;
                }
                else if(a.num[i]<b.num[i]){
                    return -1;
                    break;
                }
                else continue;
            }
            if(i==-1) return 0;
        }

    }


    int get_num(int index){
        return num[index];
    }

    int get_len(){
        return length;
    }

    int get_sign(){
        return sign;
    }

    Great operator +(Great a);
    Great operator -(Great a);
    Great operator *(Great a);
    Great operator /(Great a);


};
ostream& operator << (ostream& out,Great p)
{
    if(p.get_sign()==false) out << "-" ;
    for(int i=p.get_len()-1;i>=0;i--){
        out << p.get_num(i);
    }
    return out;
}
Great Great :: operator +(Great a)
{
    Great result;
    ///正+正 ///
    if(sign && a.sign){
        int carry=0;
        int len=max(length,a.length);
        for(int i=0;i<len;i++){
            result.num[i]=num[i]+a.num[i]+carry;
            //cout<<i<<num[i]<<a.num[i]<<"==="<<endl;
            carry=0;
            if(result.num[i]>=10){
               result.num[i]%=10;
               carry=1;
            }
        }
    if(carry==0){
        result.length=max(length,a.length);
    }
    else if(carry==1){
        result.num[max(length,a.length)]=1;
        result.length=max(length,a.length)+1;
    }
    return result;
    }
    /// 正+負 ///
    else if(sign && !a.sign){
        Great b=a;
        b.sign=true;
        result=*this-b;
    }
    /// 負+正 ///
    else if(!sign && a.sign){
        Great b=*this;
        b.sign=true;
        result=a-b;
    }
    /// 負+負 ///
    else if(!sign && !a.sign){
        Great b=*this;
        Great c=a;
        b.sign=true;
        c.sign=true;
        result=b+c;
        result.sign=false;
    }
    return result;
}

Great Great :: operator *(Great a)
{
    //cout<<"//////////////////////////"<<endl;
    Great result;

    //int carry=0;
    int k=0;
    for(int i=0;i<length;i++){
            k=i;
            //cout<<i<<endl;
        for(int j=0;j<a.length;j++){
            //cout<<"hi"<<endl;
            //Great temp;
            result.num[k]+=num[i]*a.num[j];
            k++;

        }
    }
    //cout<<"hi"<<endl;
    int sarah=0;
    while(sarah<k){
        if(result.num[sarah]>=10){
            result.num[sarah+1]+=(result.num[sarah]/10);
            result.num[sarah]%=10;
        }
        sarah++;
    }
    if(result.num[k]>0) {result.length=k+1;}
    else {result.length=k;}
    if(!sign && a.sign) result.sign=false;
    if( sign && !a.sign) result.sign=false;
    //cout<<"//////////////////////////"<<endl;
    return result;


}

Great Great :: operator -(Great a)
{
    //cout<<"///////////////"<<endl;
    Great result;

    if(sign && a.sign ){
        int k=Great::compare(*this,a);
        /// 被減數>0、減數>0 且 被減數-減數>0 ///
        if(k==1){
            int borrow=0;
        int len=max(length,a.length);
        for(int i=0;i<len;i++){
            //if(num[i]>=a.num[i]){
                //cout<<i<<num[i]<<a.num[i]<<result.num[i]<<endl;
               result.num[i]=num[i]-a.num[i]-borrow;
               borrow=0;
               if(result.num[i]<0){
                  result.num[i]+=10;
                  borrow=1;
               }
            //}
        }
        for(int i=len-1;i>=0;i--){
            if(result.num[i]>0){
                result.length=i+1;
                break;
            }
        }
        //cout<<result.length<<endl;
        }
        /// 被減數>0、減數>0 且 被減數-減數<0 ///
        else if(k==-1){
            int borrow=0;
        int len=max(length,a.length);
        for(int i=0;i<len;i++){
            if(a.num[i]>=num[i]){
               result.num[i]+=a.num[i]-num[i]-borrow;
               borrow=0;
               if(result.num[i]<0){
                  result.num[i]+=10;
                  borrow=1;
               }
            }
        }
        for(int i=len;i>=0;i--){
            if(result.num[i]>0){
                result.length=i+1;
                break;
            }
        }
        //cout<<result.length<<endl;
        result.sign=false;
        }
    }



    else if(sign && ! a.sign){
        Great b=a;
        b.sign=true;
        result=*this+b;
    }

    else if(!sign && a.sign){
        Great b=*this;
        b.sign=true;
        result=b+a;
        result.sign=false;
    }

    else if(!sign && !a.sign){
        Great b=*this;
        Great c=a;
        b.sign=true;
        c.sign=true;
        result=c-b;
    }
    return result;

}

Great Great :: operator /(Great a)
{
    Great x;
    Great sol;
    int y=length-a.length;
        for(int i=length-a.length;i>=0;i--){
            int j=i;
            for(int k=0;k<a.length+1;k++){
                x.num[k]=num[j++];
            }
            for(j--; j>=0; j--){
                if(x.num[j]>0){
                    x.length=j+1;
                    break;
                }
            }
            for(int t=1; ;t++){
                //cout<<t<<endl;
                Great c=Great(t);
                //cout<<"...."<<c;
                Great d=c*a;
                //cout<<"!!"<<d<<x<<endl;
                int k=Great::compare(d,x);
                if(k==1){
                    sol.num[i]=t-1;
                    int temp=1;
                    for(int y=0;y<i;y++){
                        temp*=10;
                    }
                    Great stone(temp);
                    Great stone1(t-1);
                    //cout<<stone1<<endl;
                    *this=*this-stone*a*stone1;
                    //cout<<*this<<endl;
                    break;
                    //cout<<"break"<<endl;
                }else if(k==0){
                    sol.num[i]=t;
                    int temp=1;
                    for(int y=0;y<i;y++){
                        temp*=10;
                    }
                    //cout<<"!!!!"<<temp<<endl;
                    Great stone(temp);
                    Great stone1(t);
                    *this=*this-stone*a*stone1;
                    //cout<<sol<<"MMM"<<endl;
                    break;
                    //cout<<*this<<endl;
                }
            }
        }
    sol.length= sol.num[y]==0? y: y+1;

    if(!sign && a.sign) sol.sign=false;
    if( sign && !a.sign) sol.sign=false;

    return sol;

}






int main()
{
    ifstream intput("test.txt");
	string a,c;
	char b;
	while(intput>>a>>b>>c){
        Great X=Great(a);
        Great Y=Great(c);
        //cout<<a<<endl;
        if(b=='+'){
            Great result=X+Y;
            cout << result << endl;
        }
        if(b=='-'){
            Great result=X-Y ;
            //cout<<"!!"<<Y<<endl;
            cout << result << endl;
        }
        if(b=='*'){
            Great result=X*Y ;
            cout << result << endl;
        }
        if(b=='/'){
            Great result=X/Y ;
            cout << result << endl;
        }
	}

}


