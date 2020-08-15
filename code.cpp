#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include<chrono>
#include<thread>

using namespace std::chrono;
using namespace std::this_thread;

int convert_to_integer(std::string s){
    int ans=0,L_count=0,V_count=0;
    int a[s.length()];
    for(int i=0;i<s.length();i++){
        if(s[i]=='I')
            a[i]=1;
        else if(s[i]=='V')
            a[i]=5;
        else if(s[i]=='X')
            a[i]=10;
        else if(s[i]=='L')
            a[i]=50;
        else if(s[i]=='C')
            a[i]=100;
        else if(s[i]=='D')
            a[i]=500;
        else if(s[i]=='M')
            a[i]=1000;
        else{
            std::cout<<"INVALID ROMAN NUMBER"<<std::endl;
            exit(0);
        }    
    }
    if(s.length()<2){
        ans=a[0];
        return ans;
    }
    for(int i=0;i<s.length();i++){
        if(a[i]>a[i-1])
            ans+=a[i]-(2*a[i-1]);
        else
            ans+=a[i];
    }
    return ans;
}

std::string ones(int n){                                                        //ONES
    std::string temp="";
    if(n<4){
        while(n!=0){
            temp+='I';
            n--;
        }
    }
    else if(n==4)
        temp="IV";
    else if(n==9)
        temp="IX";
    else{
        temp='V';
        if(n>5){
            while(n>5){
                temp+='I';
                n--;
            }
        }
    }
    return temp;
}

std::string tens(int n){                                                        //TENS
    std::string temp="";
    if(n==10)
        temp='X';
    else{
        while(n>9){
            temp+='X';
            n-=10;
        }
        temp+=ones(n);
    }
    return temp;
}

std::string fifty(int n){                                                       //FIFTY
    std::string temp="";
    if(n>39 && n<50){
        temp="XL";
        if(n==40)
            return temp;
        else{
            temp+=ones(n-40);
        }
    }
    else if(n>49){
        temp='L';
        if(n>50){
            temp+=tens(n-50);
        }
    }
    return temp;
}

std::string hundreds(int n){                                                         //HUNDREDS
    std::string temp="";
    if(n>89 && n<100){
        temp="XC";
        if(n==90)
            return temp;
        else{
            temp+=ones(n-90);
        }
    }
    else if(n>99){
        temp='C';
        if(n>100){
            if((n-100)>89)
                temp+=hundreds(n-100);
            else if((n-100)>39 && (n-100)<90)
                temp+=fifty(n-100);
            else if((n-100)>9 && (n-100)<40)
                temp+=tens(n-100);
            else
                temp+=ones(n-100);
        }
    }
    return temp;
}

std::string thousands(int n){                                                 //THOUSANDS 
    std::string temp="";
    if(n>399 && n<500){
        temp="CD";
        if(n==400)
            return temp;
        else{
            if((n-400)>89)
                temp+=hundreds(n-400);
            else if((n-400)>39 && (n-400)<90)
                temp+=fifty(n-400);
            else if((n-400)>9 && (n-400)<40)
                temp+=tens(n-400);
            else
                temp+=ones(n-400);
        }
    }
    else if(n>499 && n<900){
        temp='D';
        if(n==500)
            return temp;
        else if(n>500){
            if((n-500)>89)
                temp+=hundreds(n-500);
            else if((n-500)>39 && (n-500)<90)
                temp+=fifty(n-500);
            else if((n-500)>9 && (n-500)<40)
                temp+=tens(n-500);
            else
                temp+=ones(n-500);
        }                                                        
    }
    else if(n>899){
        if(n<1000){
            temp="CM";
            if(n==900)
                return temp;
            else{
                if((n-900)>89)
                    temp+=hundreds(n-900);
                else if((n-900)>39 && (n-900)<90)
                    temp+=fifty(n-900);
                else if((n-900)>9 && (n-900)<40)
                    temp+=tens(n-900);
                else
                    temp+=ones(n-900);
            }
        }
        else if(n>=1000){
            temp='M';
            if(n==1000)
                return temp;
            else{
                if((n-1000)>399 && (n-1000)<4000)
                    temp+=thousands(n-1000);
                else if((n-1000)>89 && (n-1000)<400)
                    temp+=hundreds(n-1000);
                else if((n-1000)>39 && (n-1000)<90)
                    temp+=fifty(n-1000);
                else if((n-1000)>9 && (n-1000)<40)
                    temp+=tens(n-1000);
                else
                    temp+=ones(n-1000);
            }
        }
    }
    return temp;
}

std::string convert_to_roman(int a){
    std::string ans="";
    if(a<10){
        ans=ones(a);
        a--;
    }
    else if(a>9 && a<40){
        ans=tens(a);
        a--;
    }
    else if(a>39 && a<90){
        ans+=fifty(a);
        a--;
    }
    else if(a>89 && a<400){
        ans+=hundreds(a);
        a--;
    }
    else if(a>399 && a<4000){
        ans+=thousands(a);
    }
    else
      	ans+="Out of Bounds";
    return ans;   
}

int main(){
	std::cout<<"Expected Ouput should be less than 4000 in value"<<std::endl;
    int a;
    std::string N1,N2;
    char op;
    std::cout<<"Enter the first Roman Operand: ";std::cin>>N1;
    int x=convert_to_integer(N1);
    std::cout<<"Enter the operator:[ +, - , / , * ]: ";
    std::cin>>op;
    std::cout<<"Enter the second Roman Operand: ";
    std::cin>>N2;
    int y=convert_to_integer(N2);
    if(op=='+')
        a=x+y;
    else if(op=='-')
        a=x-y;
    else if(op=='/')
        a=x/y;
    else if(op=='*')
        a=x*y;
    else { return 0;}
    if(a>=4000){
        std::cout<<std::endl<<"Out of Bounds";
        return 0;
    }
    std::string ans=convert_to_roman(a);
    std::cout<<std::endl<<"Result :  ";
    std::cout<<x<<" ";sleep_for(milliseconds(700));
    std::cout<<op<<" ";sleep_for(milliseconds(700));
    std::cout<<y<<" ";sleep_for(milliseconds(700));
    std::cout<<"="<<" ";sleep_for(milliseconds(700));
    std::cout<<ans<<"("<<a<<")"<<std::endl;
    return 0;
}
