#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;
vector<short int> **nfa, finalStates, dfaFinalStates;
vector<vector<short int> > dfaId, isVisitedVec;
vector<short int> Move(vector<short int> &state, char symbol)
{
    vector<short int> next;
    vector<short int>::iterator i, j;
    for(i=state.begin(); i!=state.end(); ++i)
    {
        for(j=nfa[*i][symbol-'a'].begin(); j!=nfa[*i][symbol-'a'].end(); ++j)
        {
            next.push_back(*j);
        }
    }
    sort(next.begin(), next.end());
    next.erase(unique(next.begin(),next.end()),next.end());
    return next;
}
short int name(vector<short int> state)
{
    if(find(dfaId.begin(), dfaId.end(), state)==dfaId.end())
        dfaId.push_back(state);
    return distance(dfaId.begin(),find(dfaId.begin(), dfaId.end(), state));
}
bool isVisited(vector<short int> state)
{
    return find(isVisitedVec.begin(), isVisitedVec.end(), state)!=isVisitedVec.end();
}
bool isFinalState(short int state)
{
    return find(finalStates.begin(), finalStates.end(), state)!=finalStates.end();
}
int main(int argc, char ** argv)
{
    //ifstream in(argv[1]);
    ifstream in("data.in");
    short int stateCount, finalStateCount, symbolCount, st, ends, i, t1, t2;
    char c;
    map<short int, vector<pair<char, short int> > > dfa;
    in>>stateCount>>finalStateCount>>symbolCount;
    nfa=new vector<short int>*[stateCount];
    for(i=0; i<stateCount; ++i)
        nfa[i]=new vector<short int>[symbolCount];
    finalStates.resize(finalStateCount);
    for(i=0; i<finalStateCount; ++i)
    {
        in>>finalStates[i];
    }
    while(in>>st>>c>>ends)
    {
        if(islower(c))
            nfa[st][c-'a'].push_back(ends);
    }
    vector<vector<short int> > unvis;
    vector<short int> zero;
    zero.push_back(0);
    unvis.push_back(zero);
    while(!unvis.empty())
    {
        vector<short int> temp=unvis.back();
        unvis.pop_back();
        isVisitedVec.push_back(temp);
        for(char s='a'; s<'a'+symbolCount; ++s)
        {
            vector<short int> currentState=Move(temp, s);
            vector<short int>::iterator j;
            if(!currentState.empty())
            {
                if(!isVisited(currentState))
                    unvis.push_back(currentState);
                t1=name(temp);
                t2=name(currentState);
                dfa[t1].push_back(make_pair(s, t2));
            }
        }
    }
    for(vector<vector<short int> >::iterator it=dfaId.begin(); it!=dfaId.end(); ++it)
    {
        for(vector<short int>::iterator it2=(*it).begin(); it2!=(*it).end(); ++it2)
        {
            if(isFinalState(*it2))
            {
                dfaFinalStates.push_back(name(*it));
                break;
            }
        }
    }
    cout<<dfaId.size()<<' '<<dfaFinalStates.size()<<' '<<symbolCount<<endl;
    for(vector<short int>::iterator it3=dfaFinalStates.begin(); it3!=dfaFinalStates.end(); ++it3)
        cout<<*it3<<' ';
    cout<<endl;
    for(map<short int, vector<pair<char, short int> > >::iterator it4=dfa.begin(); it4!=dfa.end(); ++it4)
    {
        for(vector<pair<char, short int> >::iterator it5=it4->second.begin(); it5!=it4->second.end(); ++it5)
            cout<<it4->first<<' '<<(*it5).first<<' '<<(*it5).second<<endl;
    }
    return 0;
}
