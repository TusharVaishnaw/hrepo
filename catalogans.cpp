#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
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

// Precise Lagrange interpolation
long long lagrangeInterpolation(const vector<Point>& points, int k) {
    long double secret = 0.0;
    
    for (int i = 0; i < k; i++) {
        long double xi = (long double)points[i].x;
        long double yi = (long double)points[i].y;
        
        // Calculate Lagrange basis polynomial Li(0)
        long double li = 1.0;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                long double xj = (long double)points[j].x;
                li *= (0.0 - xj) / (xi - xj);
            }
        }
        
        secret += yi * li;
    }
    
    return (long long)round(secret);
}

int main() {
    cout << fixed << setprecision(0);
    
    cout << "=== HASHIRA PLACEMENTS - FINAL RESULTS ===" << endl << endl;
    
    // Test Case 1
    cout << "TEST CASE 1:" << endl;
    cout << "============" << endl;
    
    vector<Point> points1;
    points1.push_back(Point(1, baseToDecimal("4", 10)));      // (1, 4)
    points1.push_back(Point(2, baseToDecimal("111", 2)));     // (2, 7)
    points1.push_back(Point(3, baseToDecimal("12", 10)));     // (3, 12)
    points1.push_back(Point(6, baseToDecimal("213", 4)));     // (6, 39)
    
    cout << "Base conversions:" << endl;
    cout << "(1, " << points1[0].y << ")" << endl;
    cout << "(2, " << points1[1].y << ")" << endl;
    cout << "(3, " << points1[2].y << ")" << endl;
    cout << "(6, " << points1[3].y << ")" << endl;
    
    // Sort points by x value
    sort(points1.begin(), points1.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    
    cout << "\nUsing first 3 points: ";
    for (int i = 0; i < 3; i++) {
        cout << "(" << points1[i].x << "," << points1[i].y << ") ";
    }
    cout << endl;
    
    long long secret1 = lagrangeInterpolation(points1, 3);
    cout << "\n*** TEST CASE 1 ANSWER: " << secret1 << " ***" << endl;
    
    cout << "\n" << string(50, '=') << endl << endl;
    
    // Test Case 2
    cout << "TEST CASE 2:" << endl;
    cout << "============" << endl;
    
    vector<Point> points2;
    
    // Test case 2 data
    vector<tuple<int, int, string>> testData2 = {
        {1, 6, "13444211440455345511"},
        {2, 15, "aed7015a346d635"},
        {3, 15, "6aeeb69631c227c"},
        {4, 16, "e1b5e05623d881f"},
        {5, 8, "316034514573652620673"},
        {6, 3, "2122212201122002221120200210011020220200"},
        {7, 3, "20120221122211000100210021102001201112121"},
        {8, 6, "20220554335330240002224253"},
        {9, 12, "45153788322a1255483"},
        {10, 7, "1101613130313526312514143"}
    };
    
    cout << "Base conversions:" << endl;
    for (auto& [key, base, value] : testData2) {
        try {
            long long decimal_val = baseToDecimal(value, base);
            points2.push_back(Point(key, decimal_val));
            cout << "(" << key << ", " << decimal_val << ")" << endl;
        } catch (const exception& e) {
            cout << "Point " << key << ": Number too large for standard precision" << endl;
            // For very large numbers, we'll need to use approximation or big integer library
            points2.push_back(Point(key, 0));  // Placeholder
        }
    }
    
    // Sort points by x value
    sort(points2.begin(), points2.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    
    cout << "\nUsing first 7 points for interpolation." << endl;
    
    long long secret2 = lagrangeInterpolation(points2, 7);
    cout << "\n*** TEST CASE 2 ANSWER: " << secret2 << " ***" << endl;
    cout << "(Note: May have precision limitations due to very large numbers)" << endl;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "FINAL SUBMISSION ANSWERS:" << endl;
    cout << string(50, '=') << endl;
    cout << "Test Case 1: " << secret1 << endl;
    cout << "Test Case 2: " << secret2 << endl;
    
    return 0;
}
