#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include <stdlib.h>

void err(string ans_c, string out_c, int line) {
    cout << "at line #" << line;
    cout << ":\nans says \"" << ans_c << "\"\noutput says \"" << out_c << "\"" << endl;

}

bool equals(string ans_file, string out_file, int sample) {
    cout << "comparing sample #" << sample << "..." << endl;
    ifstream ans(ans_file), out(out_file);
    string ans_c, out_c;
    int line_number = 1;
    int a1,a2;
    string last_ans_c = "oogabooga";
    while (1) {
        a1=0,a2=0;
        if(getline(ans,ans_c)) a1 = 1;
        if(getline(out,out_c)) a2 = 1;
        if (ans_c == "dec 0") {
            a1 = 0;
            if(getline(ans, ans_c)) a1 = 1;
        }
        //if (out_c.substr(0,10) == "switch_end") {
        //    a1 = 0;
        //    if(getline(ans, ans_c)) a1 = 1;
        //}
        if(a1+a2!=2) break;
        if(out_c=="dpl") {
            if(ans_c != "dpl") {
                if(ans_c != last_ans_c) {
                    cout << "our code says dpl but their code does something weird? line #" << line_number << endl;
                    return 0;
                }
            }
        } else if (ans_c != out_c) {
            size_t i = out_c.find(ans_c);
            bool fixed = i!=string::npos;
            i += out_c.size();
            while(++i < out_c.size() && fixed) if(out_c[i]!='0') fixed = false;

            if(!fixed) {
                err(ans_c,out_c,line_number);
                return 0;
            }
        }
        ++line_number;
        last_ans_c = ans_c;
    }
    if (a1!=a2) {
        cout << "not both files are done!" << endl;
        err(ans_c,out_c,line_number);
        return 0;
    }
    cout << "done comparing sample #" << sample << "." << endl;
    return 1;
}

int main() {
    for (int i = 1; i <= 12; ++i) {
        string in_file = "../hw2tests/sample" + to_string(i) + ".c";
        string ans_file = "../hw2tests/Pcode" + to_string(i) + ".txt";
        string out_file = "output" + to_string(i) + ".txt";
        system(("compiler.exe -Pcode " + in_file + " > " + out_file).c_str());
        bool good = equals(ans_file,out_file,i);
        system(("del " + out_file).c_str());
        if(!good) return 0;
    }
    return 0;
}