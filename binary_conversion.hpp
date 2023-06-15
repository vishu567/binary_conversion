string binaryConversion(int temp1, int n) {
        string temp = "";
        for (int i = 0; i < n; i++, temp1 /= 2) {
            temp += (temp1 % 2) + '0';
        }
        reverse(temp.begin(), temp.end());
        return temp;
    }
