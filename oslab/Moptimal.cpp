#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

int main(){
    vector<int> reference = {1,2,3,4,1,2,5,1,2,3,4,5};
    int frames = 3;
    int faults = 0;
    int hits = 0;
    
    unordered_set<int> s;
    for(int i=0; i<reference.size(); ++i){
        int page = reference[i];
        if(s.size()<frames){ // frames not full
            if(s.find(page)==s.end()){ // page not found
                s.insert(page);
                faults++;
            }
            else{ // page found
                hits++;
            }
        }
        else{ // frames full
            if(s.find(page)==s.end()){ // page not found
                unordered_set<int> lru_pages;
                int temp;
                for(int j=i+1; j<reference.size(); ++j){
                    int lru = reference[j];
                    if(s.find(lru) != s.end()){
                        lru_pages.insert(lru);
                    }
                    if(lru_pages.size() == frames){
                        temp = lru; 
                        break;
                    }
                }
                s.erase(temp);
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

//User input
/*#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    cout << "Enter the number of pages in the reference sequence: ";
    int n;
    cin >> n;

    cout << "Enter the reference sequence: ";
    vector<int> reference(n);
    for (int i = 0; i < n; ++i) {
        cin >> reference[i];
    }

    cout << "Enter the number of frames: ";
    int frames;
    cin >> frames;

    int faults = 0;
    int hits = 0;

    unordered_set<int> s;
    for (int i = 0; i < reference.size(); ++i) {
        int page = reference[i];
        if (s.size() < frames) {  // frames not full
            if (s.find(page) == s.end()) {  // page not found
                s.insert(page);
                faults++;
            } else {  // page found
                hits++;
            }
        } else {  // frames full
            if (s.find(page) == s.end()) {  // page not found
                unordered_set<int> lru_pages;
                int temp;
                for (int j = i + 1; j < reference.size(); ++j) {
                    int lru = reference[j];
                    if (s.find(lru) != s.end()) {
                        lru_pages.insert(lru);
                    }
                    if (lru_pages.size() == frames) {
                        temp = lru;
                        break;
                    }
                }
                s.erase(temp);
                s.insert(page);
                faults++;
            } else {  // page found
                hits++;
            }
        }
    }

    cout << "Page Hits -> " << hits << endl;
    cout << "Page Faults -> " << faults << endl;
    return 0;
}
*/