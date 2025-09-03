#include <bits/stdc++.h>
#include <nlohmann/json.hpp> // JSON library (https://github.com/nlohmann/json)
using namespace std;
using json = nlohmann::json;

// Convert string in base `b` to decimal (big integer via __int128 / string math)
string baseToDecimal(const string &val, int base) {
    __int128 result = 0;
    for (char c : val) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else digit = 10 + (tolower(c) - 'a');
        result = result * base + digit;
    }
    // convert __int128 to string
    if (result == 0) return "0";
    string s;
    bool neg = false;
    while (result > 0) {
        int d = result % 10;
        s.push_back('0' + d);
        result /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

// Multiply polynomial (vector<long long>) with (x - root)
vector<__int128> multiplyPoly(const vector<__int128> &poly, __int128 root) {
    vector<__int128> res(poly.size() + 1);
    for (size_t i = 0; i < poly.size(); i++) {
        res[i] += poly[i];
        res[i + 1] -= poly[i] * root;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    string line;
    while (getline(cin, line)) input += line;

    json j = json::parse(input);
    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    // collect first k roots
    vector<__int128> roots;
    for (int i = 1; i <= n && (int)roots.size() < k; i++) {
        if (j.contains(to_string(i))) {
            int base = stoi((string)j[to_string(i)]["base"]);
            string value = j[to_string(i)]["value"];
            string decStr = baseToDecimal(value, base);
            __int128 root = 0;
            for (char c : decStr) root = root * 10 + (c - '0');
            roots.push_back(root);
        }
    }

    // Build polynomial
    vector<__int128> poly = {1}; // start with "1"
    for (__int128 r : roots) poly = multiplyPoly(poly, r);

    // print coefficients
    for (size_t i = 0; i < poly.size(); i++) {
        // convert __int128 to string
        __int128 x = poly[i];
        if (x == 0) {
            cout << "0";
        } else {
            bool neg = x < 0;
            if (neg) x = -x;
            string s;
            while (x > 0) {
                int d = x % 10;
                s.push_back('0' + d);
                x /= 10;
            }
            if (neg) cout << "-";
            reverse(s.begin(), s.end());
            cout << s;
        }
        if (i + 1 < poly.size()) cout << " ";
    }
    cout << "\n";

    return 0;
}
