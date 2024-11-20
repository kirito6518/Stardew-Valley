/*2352031-古振*/
#include <iostream>
#include <string>
#include <sstream>
#include<algorithm>//max+列表以及各种重载
#include<vector>

using namespace std;

//Rectangle类
struct Rectangle {
    int x, y;
    Rectangle(int a = 0, int b = 0) : x(a), y(b) {}
    int Area() const {
        return x * y;
    }
    //输出
    void OutPut () {
        cout << x << "," << y;
    }
    //辅助函数，用于从字符串解析Rectangle
    void ParseRectangle(const string& str) {
        istringstream iss(str);//当做输入流
        char comma;
        iss >> x >> comma >> y;
    }
};
//特化版本用于string
bool CompareString(const string& a, const string& b) {
    return a.size() < b.size();
}
string max(const string& s1, const string& s2, const string& s3) {//系统库中没有带三个参的max，所以可以重载
    return max({ s1, s2, s3 }, CompareString);//系统库的max
}
//特化版本用于Rectangle
bool CompareRec(const Rectangle& a, const Rectangle& b) {
    return a.Area() < b.Area();
}
Rectangle max(const Rectangle& r1, const Rectangle& r2, const Rectangle& r3) {//系统库中没有带三个参的max，所以可以重载
    return max({ r1, r2, r3 }, CompareRec);//系统库的max
}
//特化版本用于Rectangle*
bool CompareRecPtr(Rectangle* a, Rectangle* b) {
    return a->Area() < b->Area();
}
Rectangle* max(Rectangle* r1, Rectangle* r2, Rectangle* r3) {//系统库中没有带三个参的max，所以可以重载
    return max({ r1, r2, r3 },CompareRecPtr);//系统库的max
}
//模板函数实现
template<typename T>
T max(T t1, T t2, T t3) {//系统库中没有带三个参的max，所以可以重载
    return max({ t1, t2, t3 });//系统库中有仅带列表的max，但无法处理string和结构体，此时才会调用特化
}
//测试
int main() {
    //实验数据
    vector<string> lines;
    cout << "请输入五组测试用例：" << endl;
    for (int i = 0; i < 5; i++) {
        string Input;
        getline(cin, Input);
        lines.push_back(Input);
    }
    cout << "结果：" << endl;
    for (const auto& line : lines) {
        istringstream iss(line);
        int find = 0;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '.') {//浮点数
                double d1, d2, d3;
                iss >> d1 >> d2 >> d3;
                cout << max(d1, d2, d3) << endl;
                find = 1;
                break;
            }
            else if (line[i] == ',') {//Rec，分为结构体和指针
                string s1, s2, s3;
                iss >> s1 >> s2 >> s3;
                Rectangle R1, R2, R3;
                R1.ParseRectangle(s1);
                R2.ParseRectangle(s2);
                R3.ParseRectangle(s3);
                Rectangle Result = max(R1, R2, R3);
                Result.OutPut();
                cout << endl;
                find = 1;
                break;
            }
            else if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] <= 'Z' && line[i] >= 'A')) {//字符或者字符串
                if (line[i + 1] == ' ') {//字符
                    char c1, c2, c3;
                    iss >> c1 >> c2 >> c3;
                    cout << max(c1, c2, c3) << endl;
                    find = 1;
                    break;
                }
                else {//字符串
                    string s1, s2, s3;
                    iss >> s1 >> s2 >> s3;
                    cout << max(s1, s2, s3) << endl;
                    find = 1;
                    break;
                }
            }
        }
        if (find == 0) {//整形
            int i1, i2, i3;
            iss >> i1 >> i2 >> i3;
            cout << max(i1, i2, i3) << endl;
        }
    }
    cout << "补充示例：传入结构体指针作为参数。" << endl;
    string line = "1,2 2,6 3,4";
    cout << "输入为：" << line << endl;
    string s1, s2, s3;
    istringstream iss(line);
    iss >> s1 >> s2 >> s3;
    Rectangle R1, R2, R3;
    R1.ParseRectangle(s1);
    R2.ParseRectangle(s2);
    R3.ParseRectangle(s3);
    if (line == "1,2 2,6 3,4") {//指针传参方式示例
        Rectangle* R1Ptr = &R1;
        Rectangle* R2Ptr = &R2;
        Rectangle* R3Ptr = &R3;
        Rectangle* Result = max(R1Ptr, R2Ptr, R3Ptr);
        Result->OutPut();
        cout << endl;
    }
    return 0;
}