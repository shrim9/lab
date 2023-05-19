#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

int main(){
    vector<int> reference = {1,2,3,4,1,2,5,1,2,3,4,5};
    int frames = 4;
    int faults = 0;
    int hits = 0;
    queue<int> q;
    unordered_set<int> s;
    for(int i=0; i<reference.size(); ++i){
        int page = reference[i];
        if(q.size()<frames){ // frames not full
            if(s.find(page)==s.end()){ // page not found
                q.push(page);
                s.insert(page);
                faults++;
            }
            else{ // page found
                hits++;
            }
        }
        else{ // frames full
            if(s.find(page)==s.end()){ // page not found
                int first = q.front();
                q.pop();
                s.erase(first);
                q.push(page);
                s.insert(page);
                faults++;
            }
            else{ // page found
                hits++;
            }
        }
    }
    cout<<"Page Hits -> "<<hits<<endl;
    cout<<"Page Faults -> "<<faults<<endl;
    return 0;
}
//user input

/*#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

int main(){
    int num_pages;
    cout << "Enter the number of pages: ";
    cin >> num_pages;

    vector<int> reference(num_pages);
    cout << "Enter the page reference string: ";
    for (int i = 0; i < num_pages; i++) {
        cin >> reference[i];
    }

    int frames;
    cout << "Enter the number of frames: ";
    cin >> frames;

    int faults = 0;
    int hits = 0;
    queue<int> q;
    unordered_set<int> s;

    for(int i = 0; i < reference.size(); ++i){
        int page = reference[i];
        if(q.size() < frames){ // frames not full
            if(s.find(page) == s.end()){ // page not found
                q.push(page);
                s.insert(page);
                faults++;
            }
            else{ // page found
                hits++;
            }
        }
        else{ // frames full
            if(s.find(page) == s.end()){ // page not found
                int first = q.front();
                q.pop();
                s.erase(first);
                q.push(page);
                s.insert(page);
                faults++;
            }
            else{ // page found
                hits++;
            }
        }
    }

    cout << "Page Hits -> " << hits << endl;
    cout << "Page Faults -> " << faults << endl;

    return 0;
}
*/