#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

void display(const vector<int>& frames){
    cout<<"[";
    for(int i: frames) cout<<i<<" ";
    cout<<"]";
}

void fifo(vector<int> pages, int capacity){
    cout << "\n===== FIFO Page Replacement =====\n";
    vector<int> frames;
    int misses = 0;
    // while solving it comes different because we replace at same position as removed
    //in program that is added at last
    for(int i=0;i<pages.size();i++){
        int page = pages[i];
        cout << "Step " << i+1 << " | Page: " << page << " | ";

        if(find(frames.begin(),frames.end(),page) == frames.end()){ // page not found in the framee
            if(frames.size()<capacity){
                frames.push_back(page);
            }
            else{
                frames.erase(frames.begin());
                frames.push_back(page);
            }
            misses++;
            cout<<" Miss ";

        }else{ //element exists
            cout<<" Hit ";

        }
        display(frames);
        cout<<endl;
    }
    cout<<"\nTotal Misses: "<<misses<<"\n";
}


int main() {
    int n, capacity, choice;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter frame capacity: ";
    cin >> capacity;

    do {
        cout << "\n===== Page Replacement Menu =====\n";
        cout << "1. FIFO\n";
        cout << "2. LRU\n";
        cout << "3. Optimal\n";
        cout << "4. MRU\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: fifo(pages, capacity); break;
            // case 2: lru(pages, capacity); break;
            // case 3: optimal(pages, capacity); break;
            // case 4: mru(pages, capacity); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 5);

    return 0;
}