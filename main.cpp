#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <utility>
using namespace std;
#define ull unsigned long long
#define ll long long


//Big factorial
#define BMax 10000
int res[BMax];
int res_size;

void multiply(int num){
    int carry=0,temp;
    for(int i=0;i<res_size;i++){
        temp=res[i]*num+carry;
        res[i]=temp%10;
        carry=temp/10;
    }
    while(carry){
        res[res_size++]=carry%10;
        carry/=10;
    }
}

void bigFact(int num){
    memset(res,0,sizeof res);
    res[0]=1;
    res_size=1;
    for(int i=2;i<=num;i++)
        multiply(i);
}
void printBigFact(){
    for(int i=res_size-1;i>=0;i--) cout<<res[i];cout<<"\n";
}





//Number of factorial digits
ull noOfFactDigits(int num){
    long double cnt=1;
    for(int i=1;i<=num;i++) cnt+=log10(i);
    return (ull)cnt;

}





//given p, find x such that p^x divides n!
int factPrimePower(int prime,int n){
    int ret=0;
    for(int i=prime;i<=n;i*=prime) ret+=n/i;
    return ret;
}






//Factorial Factorization
/*
1) sieve
2) Factorial Factorization
    1) for every prime in sieve
    2) call factorial prime power
*/
#define maxSiz 1000
int is_prime[maxSiz+5];
vector <int> primes;
void sieve(int siz=maxSiz){
    primes.clear();
    memset(is_prime,true,sizeof is_prime);
    is_prime[0]=is_prime[1]=false;
    for(int i=4;i<=siz;i+=2) is_prime[i]=false;
    for(int i=3;i*i<=siz;i+=2) if(is_prime[i]) for(int j=i*2;j<=siz;j+=i) is_prime[j]=false;
    for(int i=0;i<=siz;i++)if(is_prime[i]) primes.push_back(i);
}

vector <pair<int,int> >fact_factorization;
int arr_fact[1000];
void factFactorization(int num){
    memset(arr_fact,-1,sizeof arr_fact);
    fact_factorization.clear();
    int temp;
    for(int i=0;i<primes.size() && primes[i]<=num;i++){
        temp=factPrimePower(primes[i],num);
        if(temp) arr_fact[primes[i]]=fact_factorization.size(),fact_factorization.push_back(make_pair(primes[i],temp));
    }

}
void prinP4(){

    cout<<" "<<fact_factorization[0].first<<"^"<<fact_factorization[0].second;
    for(int i=1;i<fact_factorization.size();i++) cout<<" * "<<fact_factorization[i].first<<"^"<<fact_factorization[i].second;
    cout<<endl;
}









//max X such that m6x divides n!
vector <pair<int,int> >num_factorization;
int arr[1000];
void factorize(int m){
    memset(arr,-1,sizeof arr);
    num_factorization.clear();
    int cnt=0;
    for(int i=0;i<primes.size() && primes[i]*primes[i]<=m;i++){
        if(m%primes[i]==0){
            cnt=0;
            while(m%primes[i]==0){
                cnt++;
                m/=primes[i];
            }
            arr[primes[i]]=num_factorization.size();
            num_factorization.push_back(make_pair(primes[i],cnt));

        }
    }
    if(m>1) num_factorization.push_back(make_pair(m,1));

}
void prinP5(){

    cout<<" "<<num_factorization[0].first<<"^"<<num_factorization[0].second;
    for(int i=1;i<num_factorization.size();i++) cout<<" * "<<num_factorization[i].first<<"^"<<num_factorization[i].second;
    cout<<endl;
}
int P5(int m,int n){
    factorize(m);
    factFactorization(n);
    prinP5();
    prinP4();
    int maxP=10000;
    for(int i=0;i<num_factorization.size();i++){
        int numPrime=num_factorization[i].first;
        if(arr_fact[numPrime]==-1) return -1;
        int idx=arr_fact[numPrime];
        maxP=min(maxP,fact_factorization[idx].second/num_factorization[i].second);
    }
    return maxP;

}






//gcd(m,n!)
int gcd(int m,int n){
    factorize(m);
    prinP5();
    factFactorization(n);
    prinP4();
    int ret=1;
    for(int i=0;i<num_factorization.size();i++){
        int numPrime=num_factorization[i].first;
        if(arr_fact[numPrime]==-1) continue;
        int idx=arr_fact[numPrime];
        cout<<pow(num_factorization[i].first,min(fact_factorization[idx].second,num_factorization[i].second))<<endl;
        ret*=pow(num_factorization[i].first,min(fact_factorization[idx].second,num_factorization[i].second));
    }

    return ret;

}



int main()
{
    sieve();
    int x=gcd(169*2,26);
    cout<<x<<endl;
    return 0;
}
