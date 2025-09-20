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
    int replaceIndex = 0;  // points to the frame to replace next

for(int i = 0; i < pages.size(); i++){
    int page = pages[i];
    cout << "Step " << i+1 << " | Page: " << page << " | ";

    if(find(frames.begin(), frames.end(), page) == frames.end()){ // page not in frames
        if(frames.size() < capacity){
            frames.push_back(page);
        } else {
            frames[replaceIndex] = page;  // replace in-place
            replaceIndex = (replaceIndex + 1) % capacity;  // move circularly
        }
        misses++;
        cout << "Miss ";
    } else {
        cout << "Hit ";
    }
    display(frames);
    cout << endl;
}
    cout<<"\nTotal Misses: "<<misses<<"\n";
}

void lru(vector<int> pages, int capacity) {
    cout << "\n===== LRU Page Replacement =====\n";
    vector<int> frames;
    unordered_map<int, int> lastUsed;
    int misses = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        cout << "Step " << i+1 << " | Page: " << page << " | ";

        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            if (frames.size() < capacity) {
                frames.push_back(page);
            } else {
                // find least recently used
                int lruPage = frames[0], minIndex = lastUsed[lruPage];
                for (int f : frames) {
                    if (lastUsed[f] < minIndex) {
                        minIndex = lastUsed[f];
                        lruPage = f;
                    }
                }
                replace(frames.begin(), frames.end(), lruPage, page);
            }
            misses++;
            cout << "Miss ";
        } else {
            cout << "Hit  ";
        }
        lastUsed[page] = i;                                                                         
        display(frames);
        cout << endl;
    }
    cout << "Total Misses (LRU): " << misses << "\n";
}

// Optimal Algorithm
void optimal(vector<int> pages, int capacity) {
    cout << "\n===== Optimal Page Replacement =====\n";
    vector<int> frames;
    int misses = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        cout << "Step " << i+1 << " | Page: " << page << " | ";

        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            if (frames.size() < capacity) {
                frames.push_back(page);
            } else {
                // predict future use
                //pages = {1,2,3,1,4,5}
                // frames = [1,2,3]
                // farthest = 3+1 =4 i=3 when 1 comes
                // victim = 1
                int farthest = i+1, victim = frames[0];

                for (int f : frames) {
                    //cout<<"\nFinding between index "<<i+1<<" to end ";
                    auto it = find(pages.begin()+i+1, pages.end(), f);
                    if (it == pages.end()) { // if page not found
                        victim = f;  //replace it with victim = frames[0]
                        break;
                    } else if (it - pages.begin() > farthest) { //if element presnt in further array
                        // farthest = 
                        farthest = it - pages.begin();
                        victim = f;
                    }
                }
                replace(frames.begin(), frames.end(), victim, page);
            }
            misses++;
            cout << "Miss ";
        } else {
            cout << "Hit  ";
        }
        display(frames);
        cout << endl;
    }
    cout << "Total Misses (Optimal): " << misses << "\n";
}

// MRU Algorithm
void mru(vector<int> pages, int capacity) {
    cout << "\n===== MRU Page Replacement =====\n";
    vector<int> frames;
    unordered_map<int, int> lastUsed; // to store last usage index of pages in frames
    int misses = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        cout << "Step " << i+1 << " | Page: " << page << " | ";

        // If page is not in frames (miss)
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            if (frames.size() < capacity) {
                frames.push_back(page);
            } else {
                // find most recently used page (max lastUsed index)
                int mruPage = frames[0], maxIndex = lastUsed[mruPage];
                for (int f : frames) {
                    if (lastUsed[f] > maxIndex) {
                        maxIndex = lastUsed[f];
                        mruPage = f;
                    }
                }
                replace(frames.begin(), frames.end(), mruPage, page);
            }
            misses++;
            cout << "Miss ";
        } else {
            cout << "Hit  ";
        }
        lastUsed[page] = i; // update last used index
        display(frames);
        cout << endl;
    }
    cout << "Total Misses (MRU): " << misses << "\n";
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
            case 2: lru(pages, capacity); break;
            case 3: optimal(pages, capacity); break;
            case 4: mru(pages, capacity); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 5);

    return 0;
}
