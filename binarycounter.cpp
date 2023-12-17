#include <bits/stdc++.h>
using namespace std;

// Function to display elements of a vector in reverse order
void display(vector<int> v)
{
    for (int i = v.size() - 1; i >= 0; i--)
    {
        cout << v[i] << " ";
    }
}

// Function to increment a binary vector and return the total cost (number of flips)
int increment(vector<int> &binary)
{
    int i = 0;
    int no_of_flips = 0;

    // Flip all the trailing 1s to 0
    while (i < binary.size() && binary[i] == 1)
    {
        binary[i] = 0;
        no_of_flips++;
        i++;
    }

    // If there are more bits left, flip the first 0 to 1
    if (i < binary.size())
    {
        binary[i] = 1;
        no_of_flips++;
    }

    return no_of_flips;
}

// Function to convert a decimal number to binary representation
vector<int> convert(int n)
{
    vector<int> binary(n, 0);
    int rem = 0;
    int i = 0;

    // Convert decimal to binary
    while (n > 0)
    {
        rem = n % 2;
        binary[i] = rem;
        i++;
        n /= 2;
    }

    return binary;
}

// Function to perform binary counting and display the results
void binary_counter(int n, int k)
{
    vector<int> binary = convert(n);
    cout << "Original Number : ";
    display(binary);
    cout << endl;

    int count = 0;
    // Increment the binary representation k times
    while (count < k)
    {
        int tc = increment(binary);
        display(binary);
        cout << "Total Cost : " << tc;
        cout << endl;
        count++;
    }
}

int main()
{
    // User input for starting number
    cout << "Enter starting number : ";
    int n;
    cin >> n;

    // User input for the number of times to increment
    cout << "Enter number of times to increment : ";
    int a;
    cin >> a;

    // Perform binary counting and display the results
    binary_counter(n, a);

    return 0;
}

// Enter starting number : 10
// Enter number of times to increment : 3
// Original Number : 0 0 0 0 0 0 1 0 1 0
// 0 0 0 0 0 0 1 0 1 1 Total Cost : 1
// 0 0 0 0 0 0 1 1 0 0 Total Cost : 3
// 0 0 0 0 0 0 1 1 0 1 Total Cost : 1