
#include<iostream>
using namespace std;

string reflexVaumeAction(string location, string status){
    if(location == "A" && status == "C"){
        return "Right";
    }
    else if(location == "a" && status == "c"){
        return "Right";
    }
    else if(location == "A" && status == "D"){
        return "Suck";
    }
    else if(location == "a" && status == "d"){
        return "Suck";
    }
    else if(location == "B" && status == "C"){
        return "Left";
    }
    else if(location == "b" && status == "c"){
        return "Left";
    }
    else if(location == "B" && status == "D"){
        return "Suck";
    }
    else if(location == "b" && status == "d"){
        return "Suck";
    }
    else{
        return "Wring input.....";
    }
}

int main(){
    string location,status;
    cout<<"enter location A/B: ";
    getline(cin,location);

    cout<<"enter status C for clean or D for dirty: ";
    getline(cin,status);
    cout<<reflexVaumeAction(location,status)<<endl;
}
