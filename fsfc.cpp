#include<bits/stdc++.h>
using namespace std;

struct processes{
    int BT,WT,TAT,CT,AT,idx;
};
int n;
float ATAT=0, AWT=0;

bool cmpr(processes &a, processes &b){
    return a.AT<b.AT;
}

int main(){
    //input
    cout<<"Enter The Num Of Processes: "; cin>>n;
    vector<processes> p(n);
    cout<<"Enter The BT, AT Of Processes: ";
    for(int i=0; i<n; i++){
        cin>>p[i].BT;
        cin>>p[i].AT;
        p[i].idx=i+1;
    }
    cout<<"\n\n";
    
    sort(p.begin(),p.end(), cmpr);

    int minAT=p[0].AT;
    //chart
    for(int i=minAT; i<n; i++){
        cout<<"|";
        for(int j=0; j<p[i].BT; j++){
            if(j==p[i].BT/2){ cout<<"P"<<p[i].idx; continue;}
            cout<<"_";
        }
    }cout<<"|\n";
    int x=minAT;
    cout<<x;
    for(int i=minAT; i<n; i++){
        for(int j=0; j<p[i].BT; j++){
            x+=1;
            cout<<" ";
        }
        cout<<x;
        p[i].CT=x;
    }

    //calculations
    for(int i=minAT; i<n; i++){
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        ATAT+=p[i].TAT;
        AWT+=p[i].WT;
    }
    ATAT/=n;
    AWT/=n;

    cout<<"\n\nPROCESS\tTAT\tWT\n";
    for(int i=0; i<n; i++){
        cout<<"P"<<i+1<<"\t"<<p[i].TAT<<"\t"<<p[i].WT<<endl;
    }
    cout<<"\nATAT = "<<setprecision(4)<<ATAT<<"\nAWT = "<<setprecision(4)<<AWT<<endl;

}
