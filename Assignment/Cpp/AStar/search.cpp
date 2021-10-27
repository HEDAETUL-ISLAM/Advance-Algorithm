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

class AStar {
private:
    struct node {
        state *State;                  
        unsigned int PathCost;         
        unsigned int AssumingPathCost;
        node *Parent;                 
        bool Closed;                   
    };

    string print(node *Trace) {
        string Output = "";
        while(Trace != nullptr) {
            string t = Trace->State->Name + " " + to_string(Trace->PathCost) + "\n";
            Output = t + Output;
            Trace = Trace->Parent;
        }
        return Output;
    }

public:
    string run(state *Start, state *Goal) {
        list<node *> Frontier;
        unordered_map<string, node *> Explored;
        node *CurrentNode = new node;
        CurrentNode->State = Start;
        CurrentNode->PathCost = 0;
        CurrentNode->AssumingPathCost = Start->Heuristic;
        CurrentNode->Parent = nullptr;
        CurrentNode->Closed = false;
        Frontier.push_back(CurrentNode);
        Explored[CurrentNode->State->Name] = CurrentNode;

        while (!Frontier.empty()) {
            CurrentNode = (node *)Frontier.front();
            Frontier.pop_front(); 
            if(CurrentNode->State == Goal) {
                return print(CurrentNode);
            }
            for(list<route *>::iterator i = CurrentNode->State->Routes.begin(); i!=CurrentNode->State->Routes.end(); i++) {
                unordered_map<string, node *>::iterator Location = Explored.find(((state *)(*i)->Destination)->Name);
                if(Location == Explored.end()) {
                    node *Child = new node;
                    Child->State = (state *)(*i)->Destination;
                    Child->PathCost = CurrentNode->PathCost + (*i)->Cost;
                    Child->AssumingPathCost = Child->PathCost + Child->State->Heuristic;
                    Child->Parent = CurrentNode;
                    Child->Closed = false;
                    Frontier.push_back(Child);
                    Explored[Child->State->Name] = Child;
                }
                else if(!(*Location).second->Closed) {
                    unsigned int ChildPathCost = CurrentNode->PathCost + (*i)->Cost;
                    if(ChildPathCost < (*Location).second->PathCost) {
                        (*Location).second->Parent = CurrentNode;
                        (*Location).second->PathCost = ChildPathCost;
                        (*Location).second->AssumingPathCost = ChildPathCost + (*Location).second->State->Heuristic;
                    }
                }
                else if((*Location).second->Closed) {
                    unsigned int ChildPathCost = CurrentNode->PathCost + (*i)->Cost;
                    if(ChildPathCost < (*Location).second->PathCost) {
                        (*Location).second->Parent = CurrentNode;
                        (*Location).second->PathCost = ChildPathCost;
                        (*Location).second->AssumingPathCost = ChildPathCost + (*Location).second->State->Heuristic;
                        (*Location).second->Closed = false;
                        Frontier.push_back((*Location).second);
                    }
                }
            }
            CurrentNode->Closed = true;
            Frontier.sort([](const node *i, const node *j) { return (i->AssumingPathCost < j->AssumingPathCost); });
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
    cout<<"Output of A* Search"<<endl;
    AStar ASS;
    Output = ASS.run(StateList[Start], StateList[Goal]);
    cout<<Output;


    return 0;
}