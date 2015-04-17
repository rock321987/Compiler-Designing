#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

void cyk(vector < string > pr, int n)
{
	string match;
	printf("Enter string to be matched\n");
	cin >> match;
	vector < vector < set < string > > > res;

	for (int i = 0; i < match.length(); i++) {
		if (i == 0) {
			vector < set < string > > column;
			for (int j = 0; j < match.length(); j++) {
				set < string > element;
				for (vector < string > :: iterator it = pr.begin();it != pr.end();it++) {
					string tmp = "";
					if ((*it).length() == 3 && (*it).at(2) == match.at(j)) {
						tmp = (*it).at(0);
						element.insert(tmp);
					}
				}
				if (element.empty()) {
					element.insert("$");
				}
				column.push_back(element);
			}
			res.push_back(column);
		} else {
			vector < set < string > > column;
			for (int j = 0;j < match.length() - i;j++) {
				set < string > element;				
				for (int x1 = i; x1 > 0; x1--) {
					int x2 = i + 1 - x1;

					string tmp1 = "", tmp2 = "";

					for (set < string > :: iterator it = res.at(x1 - 1).at(j).begin();it != res.at(x1 - 1).at(j).end();it++) {
						tmp1.append(*it);
					}

					for (set < string > :: iterator it = res.at(x2 - 1).at(x1 + j).begin();it != res.at(x2 - 1).at(x1 + j).end();it++) {
						tmp2.append(*it);
					}

					for (int p = 0; p < tmp1.length(); p++) {
						for (int q = 0;q < tmp2.length();q++) {
							if (tmp1 == "$" || tmp2 == "$") {

							} else {
								string tmp = "";
								//cout << tmp1.at(p) << " " << tmp2.at(q);
								tmp.push_back(tmp1.at(p));
								tmp.push_back(tmp2.at(q));
								for (vector < string > :: iterator it = pr.begin();it != pr.end();it++) {
									string xx = (*it).substr(2, (*it).length() - 1);
									if (xx == tmp) {
										string yy = "";
										yy = (*it).at(0);
										element.insert(yy);
									}
								}
							}
						}
					}
				}

				if (element.empty()) {
					element.insert("$");
				}

				column.push_back(element);
			}
			res.push_back(column);
		}
	}

	for (vector < vector < set < string > > > :: iterator it = res.begin();it != res.end();it++) {
		for (vector < set < string > > :: iterator it1 = (*it).begin();it1 != (*it).end();it1++) {
			for (set < string > :: iterator it2 = (*it1).begin();it2 != (*it1).end();it2++) {
				cout << *it2;
			}
			cout << " ";
		}
		cout << "\n";
	}
}

int main()
{
	int n;
	string str;
	vector < string > pr;

	printf("Enter number of production rules\n");
	scanf("%d", &n);

	for (int i = 0;i < n;i++) {
		cin >> str;
		pr.push_back(str);
	}

	cyk(pr, n);

	return 0;
}
