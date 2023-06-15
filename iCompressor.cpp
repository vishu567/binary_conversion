#include<bits/stdc++.h>

#include "Trie_class.hpp"

#include <sys/stat.h>

using namespace std;
struct stat results;
int initial_size = 0;


class LevelTwo {
    public: string lvl1 = "";
    string decompressed = "";
    int char_count = 0;
    unsigned char * tempans,
    * realans;char * char_ans,
    * out_ans;
    int power[10] = {1,2,4,8,16,32,64,128,256,512};

    void readToString(char name[]) {
        lvl1 = "";
        int charLen;
        char * inpStr;
        if (stat(name, & results) == 0) char_count = charLen = results.st_size;
        ifstream myFile1(name, ios::in | ios::binary);
        inpStr = new char[charLen];
        myFile1.read(inpStr, charLen);
        for (int i = 0; i < charLen; i++) lvl1 += inpStr[i];
        myFile1.close();
    }

    void writeToFile(char name[], char * ptr, int size) {
        ofstream myFile(name, ios::out | ios::binary);
        myFile.write(ptr, size);
        myFile.close();
    }

    void string_flush(string & ptr, int & ind, int flag = 0) {
        int size = ptr.size();
        string temp1 = "";
        for (int i = 0; size - i >= 8 + flag; i += 8) {
            int temp = 0;
            for (int j = i, k = 0, t; k < 8; ++k, ++j) {
                t = power[7 - k];
                temp += t * (ptr[j] - '0');
            }
            char_count++;
            tempans[ind++] = temp;
        }
        for (int i = 0, j = size - 1; i < size % 8; i++) temp1 += ptr[j--];
        reverse(temp1.begin(), temp1.end());
        ptr = temp1;
        return;
    }

    int valid(char a) {
        if ((a >= 'a' && a <= 'z')) return (int) a - 'a' + 1;
        if (a == ' ') return 27;
        if (a == ',') return 28;
        if (a == '.') return 29;
        if (a == '-') return 30;
        return -1;
    }

    char revmap(int n) {
        if (n > 0 && n <= 26) return 'a' + n - 1;
        if (n == 27) return ' ';
        if (n == 28) return ',';
        if (n == 29) return '.';
        return '-';
    }

    string binaryConversion(int temp1, int n) {
        



    }

    string getchars(int n) {
        string retval = "";
        if (n % 30 == 0) {
            retval += revmap((n / 30) - 1);
            retval += revmap(30);
            return retval;
        }
        retval += revmap(n / 30);
        retval += revmap(n % 30);
        return retval;
    }

    void compress(string lvl1) {
        string ans = "";
        int temp1, temp2, ind = 0;
        int size = lvl1.size();
        for (int i = 0, j = 0; i < size; ++i, ++j) {
            if (lvl1[i + 1] == size) {
                ans += '0';
                ans += binaryConversion((int)(unsigned char) lvl1[i], 8);
            } else if ((valid(lvl1[i]) != -1) && valid(lvl1[i + 1]) != -1) {
                ans += '1';
                temp1 = valid(lvl1[i]) * 30;
                temp2 = valid(lvl1[i + 1]);
                temp1 += temp2;
                ans += binaryConversion(temp1, 10);
                i++;
            } else {
                ans += '0';
                ans += binaryConversion((int)(unsigned char) lvl1[i], 8);
            }
            //if(i!=0&&j>10000){string_flush(ans,ind,4);j=0;}
        }

        size = ans.size() % 8;
        if (size != 0) {
            for (int j = 0; j < 8 - size; ++j)
                ans += '0';
        }
        string_flush(ans, ind);
        tempans[ind++] = '\0';
    }

    void decompressor(string & ans, int flag = 3) {
        int size = ans.size(), end_ind = 0;
        for (int i = 0; size - i >= 9 + flag; i++) {
            int temp = 0;
            if (ans[i] == '1') {
                for (int j = i + 1, k = 0, t; k < 10; ++k, ++j) {
                    t = power[9 - k];
                    temp += t * (ans[j] - '0');
                }
                decompressed += getchars(temp);
                i += 10;
            } else {
                for (int j = i + 1, k = 0, t; k < 8; ++k, ++j) {
                    t = power[7 - k];
                    temp += t * (ans[j] - '0');
                }
                decompressed += (unsigned char) temp;
                i += 8;
            }
            end_ind = i + 1;
        }
        string tmp_str = "";
        for (int i = end_ind; i < size; i++) tmp_str += ans[i];
        ans = tmp_str;
    }

    void decomp_reader(unsigned char * ptr) {
        string ans = "";
        for (int i = 0, j = 0; i < char_count; ++i, j++) {
            ans += binaryConversion( * (ptr + i), 8);
            if (j > 500000) {
                decompressor(ans);
                j = 0;
            }
        }
        decompressor(ans, 0);
    }
    void levelTwoMainD(char * fileName) {
        char_count = 0;
        readToString(fileName);
        realans = new unsigned char[char_count];
        for (int i = 0; i < char_count; i++) realans[i] = lvl1[i];
        decomp_reader(realans);
        out_ans = new char[decompressed.size()];
        for (int i = 0; i < decompressed.size(); i++) out_ans[i] = decompressed[i];
        cout << endl;
        ofstream myFile("doutput1.bin", ios::out | ios::binary);
        myFile.write(out_ans, decompressed.size());
        myFile.close();
    }

    void levelTwoMainC(char * fileName) {
        readToString("coutput1.bin");
        tempans = new unsigned char[2 * lvl1.size()];
        char_count = 0;
        compress(lvl1);
        int size = lvl1.size();
        char_ans = new char[char_count];
        realans = new unsigned char[char_count];
        for (int i = 0; i < char_count; i++) char_ans[i] = tempans[i];
        for (int j = strlen(fileName) - 1, k = 0; k <= 3; j--, k++) fileName[j] = '\0';
        strcat(fileName, "_compressed.bin");
        writeToFile(fileName, char_ans, char_count);
        cout << "\n\tFile Compressed Succesfully\n\tFile Name: " << fileName << endl;
        cout << "\tText compressed by: " << 100 - ((double) char_count * 100 / initial_size) << "%\n";
    }

};
int main() {
    system("CLS");
    string t1;
    ifstream t("Logo.txt");
    stringstream buffer;
    buffer << t.rdbuf();
    cout << buffer.str() << endl;
    t.close();
    LevelOneCompressor f;
    LevelOneDecompressor fd;
    LevelTwo d;
    LevelTwo d1;
    int ch;
}