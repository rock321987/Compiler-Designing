#include <cstdio>
#include <iostream>
#include <set>
#include <set>
#include <string>
#include <map>
#include <utility>

using namespace std;

map < char, set < string > > break_by_pipe(set < string > prod_rules)
{
    map < char , set < string > > break_rules;

    for (set < string > :: iterator it = prod_rules.begin();it != prod_rules.end();it++) {
        string x = "";
        set < string > tmp;
        for (int i = 2;i < (*it).length();i++) {
            if ((*it).at(i) == '|') {
                tmp.insert(x);
                x.clear();
                continue;
            }
            x.push_back((*it).at(i));
        }
        tmp.insert(x);
        break_rules[(*it).at(0)] = tmp;
    }

    return break_rules;
}

map < char , set < char > > first(map < char , set < string > > break_rules)
{
    map < char , set < char > > res;

    while (1) {
        int flag = 0;

        for (map < char, set < string > > :: iterator it = break_rules.begin();it != break_rules.end();it++) {
            int sz = res[it->first].size();
            
            for (set < string > :: iterator it1 = ((*it).second).begin();it1 != ((*it).second).end();it1++) {
                int i = 0;
                pos:char x1 = (*it1).at(i);
                
                if (isupper(x1)) {
                    if (res[x1].size()) {
                        for (set < char > :: iterator it2 = res[x1].begin();it2 != res[x1].end();it2++) {
                            if (*it2 == '~') {
                                i++;
                                if (i < (*it1).size()) {
                                    goto pos;
                                } else {
                                    res[it->first].insert('~');
                                }
                            } else {
                                res[it->first].insert(*it2);
                            }
                        }
                    }
                } else {
                    res[it->first].insert(x1);
                }
            }

            if (sz != res[it->first].size()) {
                flag = 1;
            }
        }

        if (flag == 0) {
            break;
        }
    }

    return res;
}

map < char , set < char > > follow(map < char , set < string > > break_rules , map < char , set < char > > first_set, char ins)
{
    map < char , set < char > > follow_set;
    map < char , set < string > > :: iterator it = break_rules.begin();
    map < char , set < char > > second_iteration;

    for (map < char , set < string > > :: iterator it = break_rules.begin();it != break_rules.end();it++) {
        char x = it->first;
        set < char > re;
        set < char > si;
        for (map < char , set < string > > :: iterator it1 = break_rules.begin();it1 != break_rules.end();it1++) {
            char y = it1->first;
            for (set < string > :: iterator it2 = it1->second.begin();it2 != it1->second.end();it2++) {
                //int pos = (*it2).find(x);
                int len = (*it2).length();
                int pos[1005];
                int j = 0, k = 0;

                while (j < len) {
                    if ((*it2).at(j) == x) {
                        pos[k] = j;
                        k++;
                    }
                    j++;
                }
                
                for (int j = 0;j < k;j++) {
                    if (pos[j] >= 0) {
                        if (pos[j] == len - 1) {
                            //FOLLOW y
                            for (set < char > :: iterator op = follow_set[y].begin();op != follow_set[y].end();op++) {
                                re.insert(*op);
                            }
                            si.insert(y);
                        } else {
                            jmp:pos[j]++;
                            char z = (*it2).at(pos[j]);
                            if (!(z >= 'A' && z <= 'Z')) {
                                re.insert(z);
                            } else {
                                for (set < char > :: iterator it3 = first_set[z].begin();it3 != first_set[z].end();it3++) {
                                    if (*it3 == '~') {
                                        if (pos[j] == len - 1) {
                                            //FOLLOW y
                                            for (set < char > :: iterator op = follow_set[y].begin();op != follow_set[y].end();op++) {
                                                re.insert(*op);
                                            }
                                            si.insert(y);
                                        } else {
                                            goto jmp;
                                        }
                                    } else if (!((*it3) >= 'A' && (*it3) <= 'Z')) {
                                        re.insert(*it3);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (x == ins) {
                re.insert('$');
            }

            follow_set[x] = re;
            second_iteration[x] = si;
        }
    }
    
    for (map < char, set < char > > :: iterator it = second_iteration.begin();it != second_iteration.end();it++) {
        for (set < char > :: iterator it1 = (it->second).begin();it1 != (it->second).end();it1++) {
            for (set < char > :: iterator it2 = follow_set[*it1].begin();it2 != follow_set[*it1].end();it2++) {
                follow_set[it->first].insert(*it2);
            }
        }
    }

    return follow_set;
}

int main() {
    //while(1) {
    int n;
    printf("enter number of production rules\n");
    scanf("%d", &n);
    set < string > prod_rules;
    char ins;

    for (int i = 0;i < n;i++) {
        string x;
        cin >> x;
        prod_rules.insert(x);
        if (i == 0) {
            ins = x.at(0);
        }
    }

    map < char , set < string > > break_rules = break_by_pipe(prod_rules);
    map < char , set < char > > first_set = first(break_rules);

    printf("\n\n---------------------FIRST---------------------\n\n");

    for (map < char, set < char > > :: iterator it = first_set.begin();it != first_set.end();it++) {
        cout << it->first << " = ";
        for (set < char > :: iterator it1 = (it->second).begin();it1 != (it->second).end();it1++) {
            cout << *it1 << " ";
        }
        cout << endl;
    }

    map < char , set < char > > follow_set = follow(break_rules, first_set, ins);
    
    printf("\n\n---------------------FOLLOW---------------------\n\n");

    for (map < char, set < char > > :: iterator it = follow_set.begin();it != follow_set.end();it++) {
        cout << it->first << " = ";
        for (set < char > :: iterator it1 = (it->second).begin();it1 != (it->second).end();it1++) {
            cout << *it1 << " ";
        }
        cout << endl;
    }
    //}

    return 0;
}
