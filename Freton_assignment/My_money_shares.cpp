#include <bits/stdc++.h>
using namespace std;

// Recursive function to solve the problem
void recursive_solve(vector<int>& weight, int ram_value, int shyam_value, int rahim_value, vector<int>& ram_apples, vector<int>& shyam_apples, vector<int>& rahim_apples) {
    if (weight.empty()) return;

    int w = weight[0];
    weight.erase(weight.begin());

    if (ram_value >= w) {
        ram_apples.push_back(w);
        recursive_solve(weight, ram_value - w, shyam_value, rahim_value, ram_apples, shyam_apples, rahim_apples);
    } else if (shyam_value >= w) {
        shyam_apples.push_back(w);
        recursive_solve(weight, ram_value, shyam_value - w, rahim_value, ram_apples, shyam_apples, rahim_apples);
    } else {
        rahim_apples.push_back(w);
        recursive_solve(weight, ram_value, shyam_value, rahim_value - w, ram_apples, shyam_apples, rahim_apples);
    }
}

int main() {
    int ram, shyam, rahim;
    cout << "Enter the price paid by Ram: ";
    cin >> ram;
    cout << "Enter the price paid by Shyam: ";
    cin >> shyam;
    cout << "Enter the price paid by Rahim: ";
    cin >> rahim;

    vector<int> weight;
    int input;
    cout << "Enter apple weights in grams (-1 to stop): ";
    while (cin >> input && input != -1) {
        weight.push_back(input);
    }

    int total_weight = accumulate(weight.begin(), weight.end(), 0);
    sort(weight.rbegin(), weight.rend()); // Sort weights in descending order

    int ram_value = (total_weight * ram) / (ram + shyam + rahim);
    int shyam_value = (total_weight * shyam) / (ram + shyam + rahim);
    int rahim_value = total_weight - ram_value - shyam_value; // The remaining weight goes to Rahim

    vector<int> ram_apples, shyam_apples, rahim_apples;

    recursive_solve(weight, ram_value, shyam_value, rahim_value, ram_apples, shyam_apples, rahim_apples);

    cout << "Distribution Result:" << endl;
    cout << "Ram: ";
    for (int w : ram_apples) cout << w << " ";
    cout << endl;

    cout << "Shyam: ";
    for (int w : shyam_apples) cout << w << " ";
    cout << endl;

    cout << "Rahim: ";
    for (int w : rahim_apples) cout << w << " ";
    cout << endl;

    return 0;
}