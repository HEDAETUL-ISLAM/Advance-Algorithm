#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct route {
    void *Destination;         
    unsigned int Cost;         
};
struct state {
    string Name;              
    list<route *> Routes;      
    unsigned int Heuristic;     
};

class GreedyBestFirstSearch {
private:
    struct node {
        state *State;
        unsigned int PathCost;
        node *Parent;
    };

    string print(node *Trace) {
        string Output = "";
        while (Trace != nullptr) {
            string t = Trace->State->Name + " " + to_string(Trace->PathCost) + "\n";
            Output = t + Output;
            Trace = Trace->Parent;
        }
        return Output;
    }

public:
    string run(state *Start, state *Goal) {
        stack<node *> Frontier;
        unordered_set<string> Explored;
        node *CurrentNode = new node;
        CurrentNode->State = Start;
        CurrentNode->PathCost = 0;
        CurrentNode->Parent = nullptr;
        Frontier.push(CurrentNode);
        Explored.insert(CurrentNode->State->Name);

        while (!Frontier.empty()) {
            CurrentNode = (node *)Frontier.top();
            Frontier.pop();

            //Goal test
            if(CurrentNode->State == Goal) {
                return print(CurrentNode);
            }

            for(list<route *>::reverse_iterator i = CurrentNode->State->Routes.rbegin(); i!=CurrentNode->State->Routes.rend(); i++) {
                unordered_set<string>::iterator Location = Explored.find(((state *)(*i)->Destination)->Name);

                if(Location == Explored.end()) {
                    node *Child = new node;
                    Child->State = (state *)(*i)->Destination;
                    Child->PathCost = CurrentNode->PathCost+1;
                    Child->Parent = CurrentNode;

                    Frontier.push(Child);

                    Explored.insert(Child->State->Name);
                }
            }
        }

        cout<<"Route not found"<<endl;
        return print(nullptr);
    }
};

int main() {
    string Algo, Start, Goal;
    int LTLNum, STLNum;
    unordered_map<string, state *> StateList;

    ifstream InputFile ("input.txt");
    if(InputFile.is_open()) {
        getline(InputFile,Start);
        getline(InputFile,Goal);

        string TempString;

        getline(InputFile,TempString);
        LTLNum = stoi(TempString);
        for(int i=0; i<LTLNum; i++) {
            getline(InputFile,TempString);

            string TempArray[3];
            stringstream SS(TempString);
            for(int j=0; j<3; j++)
                SS>>TempArray[j];

            state *TempStateA, *TempStateB;

            if(StateList.find(TempArray[0]) != StateList.end()) {
                TempStateA = StateList[TempArray[0]];
            }
            else {
                TempStateA = new state;
                StateList[TempArray[0]] = TempStateA;
                TempStateA->Name = TempArray[0];
            }
            if(StateList.find(TempArray[1]) != StateList.end()) {
                TempStateB = StateList[TempArray[1]];
            }
            else {
                TempStateB = new state;
                StateList[TempArray[1]] = TempStateB;
                TempStateB->Name = TempArray[1];
            }

            route *TempRoute = new route;
            TempRoute->Destination = TempStateB;
            TempRoute->Cost = (unsigned int)stoi(TempArray[2]);
            TempStateA->Routes.push_back(TempRoute);
        }

        getline(InputFile,TempString);
        STLNum = stoi(TempString);
        for(int i=0; i<STLNum; i++) {
            getline(InputFile,TempString);

            string TempArray[2];
            stringstream SS(TempString);
            for(int j=0; j<2; j++)
                SS>>TempArray[j];

            StateList[TempArray[0]]->Heuristic = (unsigned int)stoi(TempArray[1]);
        }

        InputFile.close();
    }
    else {
        cout<<"Input file not loaded"<<endl;
    }
    string Output = "";
    cout<<"Output of Greedy Best First Search"<<endl;
    GreedyBestFirstSearch GBFS;
    Output = GBFS.run(StateList[Start], StateList[Goal]);
    cout<<Output;
    return 0;
}
