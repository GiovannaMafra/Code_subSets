#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

//set class that stores integers according to the requested interface
class Set {
    set<int> data;
public:
    void add(int e) { data.insert(e); }
    void remove(int e) { data.erase(e); }
    int size() const { return data.size(); }
    
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }

    // Required for the set of sets to compare and store Set objects
    bool operator<(const Set& other) const {
        return this->data < other.data;
    }
};

//class with a set of sets according to the requested interface
class SetOfSets {
    set<Set> data;
public:
    void add(Set s) { data.insert(s); }
    int size() const { return data.size(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};

/**
 * The generate() function uses backtracking to explore all combinations.
 */
void generate(int i, vector<int>& nums, Set currentOption, SetOfSets& allSubsets) {
    if (i == nums.size()) {
        allSubsets.add(currentOption);
        return;
    }
    //include the currentOption element
    currentOption.add(nums[i]); 
    generate(i + 1, nums, currentOption, allSubsets);

    //dont include the currentOption element
    currentOption.remove(nums[i]); 
    generate(i + 1, nums, currentOption, allSubsets);
}

/**
 * The getSubSets() function calls generate and returns all subsets of A.
 */
SetOfSets getSubSets(vector<int> A) {
    SetOfSets allSubsets;
    Set emptySet;
    generate(0, A, emptySet, allSubsets);
    return allSubsets;
}

/**
 * The main function will:
 * - Obtain the input and filter only the numeric characters.
 * - Call getSubSets to generate combinations using the Set structure.
 * - Use a vector to sort the sets
 * - Print the result
 */
int main() {
    string input;
    cin >> input;

    vector<int> nums;
    for (char num : input) {
        if(isdigit(num)) {
            nums.push_back(num - '0');
        }
    }

    SetOfSets result = getSubSets(nums);

    vector<Set> ans;
    for (auto s : result) { 
        ans.push_back(s);
    }

    //sort by the set size 
    sort(ans.begin(), ans.end(), [](const Set& a, const Set& b) {
        if (a.size() != b.size()) {
            return a.size() > b.size(); 
        }
        return a < b;
    });

    cout << "[";
    for (int i = 0; i < ans.size(); i++) {
        cout << "[";
        auto it = ans[i].begin();
        while (it != ans[i].end()) {
            cout << *it;
            if (next(it) != ans[i].end()) cout << ",";
            it++;
        }
        cout << "]";
        if (i < ans.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}