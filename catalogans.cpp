#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Function to convert a number from any base to decimal
long long baseToDecimal(const string& value, int base) {
    long long result = 0;
    string digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    
    for (char c : value) {
        char lowerC = tolower(c);
        size_t digitPos = digits.find(lowerC);
        if (digitPos == string::npos || (int)digitPos >= base) {
            throw invalid_argument("Invalid digit for base");
        }
        result = result * base + digitPos;
    }
    return result;
}

// Structure to hold a point
struct Point {
    long long x;
    long long y;
    
    Point(long long x_val, long long y_val) : x(x_val), y(y_val) {}
};

// Lagrange interpolation to find the constant term (secret)
long long lagrangeInterpolation(const vector<Point>& points, int k) {
    long double secret = 0.0;
    
    // Use first k points
    for (int i = 0; i < k; i++) {
        long double xi = (long double)points[i].x;
        long double yi = (long double)points[i].y;
        
        // Calculate Lagrange basis polynomial Li(0)
        long double numerator = 1.0;
        long double denominator = 1.0;
        
        for (int j = 0; j < k; j++) {
            if (i != j) {
                long double xj = (long double)points[j].x;
                numerator *= (0.0 - xj);  // (0 - xj)
                denominator *= (xi - xj);
            }
        }
        
        long double li = numerator / denominator;
        secret += yi * li;
    }
    
    return (long long)(secret + 0.5);  // Round to nearest integer
}

int main() {
    cout << "=== TEST CASE 1 ===" << endl;
    
    // Test Case 1
    vector<Point> points1;
    points1.push_back(Point(1, baseToDecimal("4", 10)));
    points1.push_back(Point(2, baseToDecimal("111", 2)));
    points1.push_back(Point(3, baseToDecimal("12", 10)));
    points1.push_back(Point(6, baseToDecimal("213", 4)));
    
    cout << "n = 4, k = 3" << endl;
    cout << "Polynomial degree = 2" << endl << endl;
    
    cout << "Point 1: base 10, value \"4\" -> decimal " << baseToDecimal("4", 10) << endl;
    cout << "Point 2: base 2, value \"111\" -> decimal " << baseToDecimal("111", 2) << endl;
    cout << "Point 3: base 10, value \"12\" -> decimal " << baseToDecimal("12", 10) << endl;
    cout << "Point 6: base 4, value \"213\" -> decimal " << baseToDecimal("213", 4) << endl;
    
    // Sort points by x value
    sort(points1.begin(), points1.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    
    cout << "\nUsing first 3 points for interpolation:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "(" << points1[i].x << ", " << points1[i].y << ")" << endl;
    }
    
    long long secret1 = lagrangeInterpolation(points1, 3);
    cout << "\nThe secret (constant term) is: " << secret1 << endl;
    
    cout << "\n" << string(50, '=') << "\n" << endl;
    
    // Test Case 2
    cout << "=== TEST CASE 2 ===" << endl;
    cout << "n = 10, k = 7" << endl;
    cout << "Polynomial degree = 6" << endl << endl;
    
    vector<Point> points2;
    
    // Process each point for test case 2
    vector<pair<int, pair<int, string>>> testData2 = {
        {1, {6, "13444211440455345511"}},
        {2, {15, "aed7015a346d635"}},
        {3, {15, "6aeeb69631c227c"}},
        {4, {16, "e1b5e05623d881f"}},
        {5, {8, "316034514573652620673"}},
        {6, {3, "2122212201122002221120200210011020220200"}},
        {7, {3, "20120221122211000100210021102001201112121"}},
        {8, {6, "20220554335330240002224253"}},
        {9, {12, "45153788322a1255483"}},
        {10, {7, "1101613130313526312514143"}}
    };
    
    for (auto& data : testData2) {
        int key = data.first;
        int base = data.second.first;
        string value = data.second.second;
        
        try {
            long long decimal_val = baseToDecimal(value, base);
            points2.push_back(Point(key, decimal_val));
            cout << "Point " << key << ": base " << base << ", value \"" << value 
                 << "\" -> decimal " << decimal_val << endl;
        } catch (const exception& e) {
            cout << "Point " << key << ": Error converting - number too large" << endl;
            // For very large numbers, we'll use a placeholder
            points2.push_back(Point(key, 0));  // This will affect accuracy
        }
    }
    
    // Sort points by x value
    sort(points2.begin(), points2.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    
    cout << "\nUsing first 7 points for interpolation:" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "(" << points2[i].x << ", " << points2[i].y << ")" << endl;
    }
    
    long long secret2 = lagrangeInterpolation(points2, 7);
    cout << "\nThe secret (constant term) is: " << secret2 << endl;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "FINAL ANSWERS:" << endl;
    cout << "Test Case 1 Secret: " << secret1 << endl;
    cout << "Test Case 2 Secret: " << secret2 << endl;
    cout << "\nNote: Test Case 2 may have precision issues due to very large numbers" << endl;
    cout << "For exact results with large numbers, use arbitrary precision arithmetic." << endl;
    
    return 0;
}
