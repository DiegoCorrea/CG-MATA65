#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <limits>
using namespace std;
int main(){
std::vector<bool> a = { 0, 1, 1, 1, 1, 0, 1, 1, 1, 0 };
std::string s = "";
for (bool b : a)
{
    s += std::to_string(b);
}
int result = std::stoi(s);
return 0;
}