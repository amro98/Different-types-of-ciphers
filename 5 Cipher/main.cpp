#include<iostream>
#include<conio.h>
#include<vector>
#include<map>
#include<string.h>
#include<stdlib.h>
using namespace std;
class CaesarCipher
{

public:
	string t;

	string Encreption(int key, string s)
	{
        string t;
		for (int i = 0; i < s.size(); i++)
		{
			t += (s[i] - 96+ key) % 26 + 96;

		}

		return t;
	}

	string decription(int key, string s)
	{
		string t;
		for (int i = 0; i < s.size(); i++)
		{
			t += (s[i] - 96- key + 26) % 26 + 96;
		}
		return t;
	}


};
class Affine_Cipher
{
    public:
    string Affine_Enc(string Msg)
    {
        string CTxt = "";
        int a = 3;
        int b = 6;
        for (int i = 0; i < Msg.length(); i++)
        {
            CTxt = CTxt + (char) ((((a * Msg[i]) + b) % 26) + 65);
        }
        return CTxt;
    }
    string Affine_Dec(string CTxt )
    {


        string Msg = "";
        int a = 3;
        int b = 6;
        int a_inv = 0;
        int flag = 0;
        for (int i = 0; i < 26; i++)
        {
            flag = (a * i) % 26;
            if (flag == 1)
            {
                a_inv = i;
            }
        }
        for (int i = 0; i < CTxt.length(); i++)
        {
            Msg = Msg + (char) (((a_inv * ((CTxt[i] - b)) % 26)) + 65);
        }
        return Msg;
    }
};
class Vigenere
{
public:
    string key;
    Vigenere(string key)
    {
        for (int i=0; i<key.size() ; i++)
        {
            if(key[i]>='A' && key[i]<='Z')
                this->key += key[i];
            else if(key[i]>='a'&&key[i]<='z')
                this->key +=key[i]+'A'-'a';
        }
    }
    string Encrypt(string text)
    {
        string out;
        for(int i=0 ,j=0; i<text.length();i++)
            {
                    char c = text[i];
                    if (c >= 'a' && c <= 'z')
                        c += 'A' - 'a';
                    else if (c < 'A' || c > 'Z')
                        continue;
                    out += (c + key[j] - 2 * 'A') % 26 + 'A';
                    j = (j + 1) % key.length();
            }
        return out;
    }
        string decryption(string t)
        {
		string output;
		for (int i = 0, j = 0; i < t.length(); ++i)
        {
			char c = t[i];
			if (c >= 'a' && c <= 'z')
				c += 'A' - 'a';
			else if (c < 'A' || c > 'Z')
				continue;
			output += (c - key[j] + 26) % 26 + 'A';
			j = (j + 1) % key.length();
		}
		return output;
        }


};
class Vernam_Cipher
{

public:

	string encreption(string key, string m)
	{
		int i, j;
		int mod = key.size();
		j = 0;
		for (i = key.size(); i<m.size(); i++) {
			key += key[j%mod];
			j++;
		}
		string ans = "";
		for (i = 0; i<m.size(); i++) {
			ans += (key[i] - 'A' + m[i] - 'A') % 26 + 'A';
		}

		return ans;
	}
	string decreption(string key, string m)
	{
		int i, j;
		int mod = key.size();
		j = 0;
		for (i = key.size(); i<m.size(); i++) {
			key += key[j%mod];
			j++;
		}
		string ans = "";
		for (i = 0; i<m.size(); i++) {
			ans += (m[i] - key[i] + 26) % 26 + 'A';
		}


		return ans;
	}};

class Playfair_Cipher
{
public:

void SelectPlayfair_CipherTyepDecryption() {

    int i, j, k, n;
    cout << "Enter the encrypted message\n" << endl;
    string s;
    cin >> s;
    cout << "Enter the key\n" << endl;
    string key;
    cin >> key;
    vector<vector<char> > a(5, vector<char>(5, ' '));
    n = 5;
    map<char, int> mp;
    k = 0;
    int pi, pj;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            while (mp[key[k]] > 0 && k < key.size()) {
                k++;
            }
            if (k < key.size()) {
                a[i][j] = key[k];
                mp[key[k]]++;
                pi = i;
                pj = j;
            }
            if (k == key.size())
                break;
        }
        if (k == key.size())
            break;
    }
    k = 0;
    for (; i < n; i++) {
        for (; j < n; j++) {
            while (mp[char(k + 'a')] > 0 && k < 26) {
                k++;
            }
            if (char(k + 'a') == 'j') {
                j--;
                k++;
                continue;
            }
            if (k < 26) {
                a[i][j] = char(k + 'a');
                mp[char(k + 'a')]++;
            }
        }
        j = 0;
    }
    string ans;
    map<char, pair<int, int> > mp2;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            mp2[a[i][j]] = make_pair(i, j);
        }
    }
    for (i = 0; i < s.size() - 1; i += 2) {
        int y1 = mp2[s[i]].first;
        int x1 = mp2[s[i]].second;
        int y2 = mp2[s[i + 1]].first;
        int x2 = mp2[s[i + 1]].second;
        if (y1 == y2) {
            ans += a[y1][(x1 - 1) % 5];
            ans += a[y1][(x2 - 1) % 5];
        }
        else if (x1 == x2) {
            ans += a[(y1 - 1) % 5][x1];
            ans += a[(y2 - 1) % 5][x2];
        }
        else {
            ans += a[y1][x2];
            ans += a[y2][x1];
        }
    }
    if (ans[ans.size() - 1] == 'x')
        ans[ans.size() - 1] = '\0';
    for (i = 1; i < ans.size(); i++) {
        if (ans[i] == 'x')
            ans[i] = ans[i - 1];
    }

    cout << ans << '\n' << endl;

}
void SelectPlayfair_CipherTyepEncryption() {

    int i, j, k, n;
    cout << "Enter the message" << endl;
    string s, origin;
   cin>> origin;
    cout << "Enter the key" << endl;
    string key;
    cin >> key;
    for (i = 0; i < origin.size(); i++) {
        if (origin[i] != ' ')
            s += origin[i];
    }
    vector<vector<char> > a(5, vector<char>(5, ' '));
    n = 5;
    map<char, int> mp;
    k = 0;
    int pi, pj;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            while (mp[key[k]] > 0 && k < key.size()) {
                k++;
            }
            if (k < key.size()) {
                a[i][j] = key[k];
                mp[key[k]]++;
                pi = i;
                pj = j;
            }
            if (k == key.size())
                break;
        }
        if (k == key.size())
            break;
    }
    k = 0;
    for (; i < n; i++) {
        for (; j < n; j++) {
            while (mp[char(k + 'a')] > 0 && k < 26) {
                k++;
            }
            if (char(k + 'a') == 'j') {
                j--;
                k++;
                continue;
            }
            if (k < 26) {
                a[i][j] = char(k + 'a');
                mp[char(k + 'a')]++;
            }
        }
        j = 0;
    }
    string ans;
    if (s.size() % 2 == 1)
        s += "x";
    for (i = 0; i < s.size() - 1; i++) {
        if (s[i] == s[i + 1])
            s[i + 1] = 'x';
    }
    map<char, pair<int, int> > mp2;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            mp2[a[i][j]] = make_pair(i, j);
        }
    }

    for (i = 0; i < s.size() - 1; i += 2) {
        int y1 = mp2[s[i]].first;
        int x1 = mp2[s[i]].second;
        int y2 = mp2[s[i + 1]].first;
        int x2 = mp2[s[i + 1]].second;
        if (y1 == y2) {
            ans += a[y1][(x1 + 1) % 5];
            ans += a[y1][(x2 + 1) % 5];
        }
        else if (x1 == x2) {
            ans += a[(y1 + 1) % 5][x1];
            ans += a[(y2 + 1) % 5][x2];
        }
        else {
            ans += a[y1][x2];
            ans += a[y2][x1];
        }
    }
    cout << ans << '\n' << endl;

}

};

void Display_All_Encryption()
{
    int Key,Choice,x;
    string M,Msg,St_key,k;
    CaesarCipher obj1;
    Affine_Cipher obj2;
    Vernam_Cipher obj4;
    Playfair_Cipher obj5;


                cout<<"Press 1 For Ceaser Cipher Encryption\n";
                cout<<"Press 2 For Affine Cipher Encryption\n";
                cout<<"Press 3 For Vigenere Cipher Encryption\n";
                cout<<"Press 4 For Vernam Cipher Encryption\n";
                cout<<"Press 5 For Playfair Cipher Encryption\n";
                cout<<"------Press 0 to Exit------\n";
                cin>>Choice;
                if(Choice==1)
                {
                    cout << "Enter The Key" << endl;
                    cin >> Key;
                    cout << "Enter The Msg" << endl;
                    cin >> Msg;
                    cout << "the Encreption is: " << obj1.Encreption(Key,Msg) << endl;
                }
                else
                    if(Choice==2)
                {

                    cout << "Enter The Msg" << endl;
                    cin >> Msg;
                    cout << "the Encreption is " << obj2.Affine_Enc(Msg) << endl;

                }
                else
                    if(Choice==3)
                {cout << "enter the msg" << endl;
                    string ori;
                    cin >> ori;
                    cout<<"Enter The Key"<<endl;
                    cin>>k;
                    Vigenere obj3(k);
                    cout << "the incription is " << obj3.Encrypt(ori)<<endl;
                }
                else
                if(Choice==4)
                {
                    cout << "Enter The String Key" << endl;
                    cin >> St_key;
                    cout << "Enter The Msg" << endl;
                    cin>>Msg;
                    cout << "the Encreption is \t" << obj4.encreption(St_key,Msg) << endl;
                }
                else
                    if(Choice==5)
                {
                    obj5.SelectPlayfair_CipherTyepEncryption();
                }
                else
                {
                    exit(0);
                }


}
void Display_All_Decryption()
{
    CaesarCipher obj1;
    Affine_Cipher obj2;
    Vernam_Cipher obj4;
    Playfair_Cipher obj5;
    int Key,Choice,x;
    string M,Msg,St_key;

                    cout<<"Press 1 For Ceaser Cipher Decryption\n";
                    cout<<"Press 2 For Affine Cipher Decryption\n";
                    cout<<"Press 3 For Vernam Cipher Decryption\n";
                    cout<<"Press 4 For Playfair Cipher Decryption\n";
                    cout<<"Press 5 For Viggner Cipher Decryption\n";
                    cout<<"------Press 0 to Exit------\n";
                    cin>>Choice;
                if(Choice==1)
                {
                    cout << "Enter The Key" << endl;
                    cin >> Key;
                    cout << "Enter The Msg" << endl;
                    cin >> Msg;
                    cout << "the Decrption is \t" << obj1.decription(Key,Msg) << endl;

                }
                else
                    if(Choice==2)
                {

                    cout << "Enter The Msg" << endl;
                    cin >> Msg;
                    cout << "the Decrption is " << obj2.Affine_Dec(Msg) << endl;

                }
                else
                    if(Choice==3)
                    {
                        cout << "Enter The String Key" << endl;
                        cin >> St_key;
                        cout << "Enter The Msg" << endl;
                        cin>>Msg;
                        cout << "the Decrption is \t" << obj4.decreption(St_key,Msg) << endl;
                    }
                else
                    if(Choice==4)
                {
                    obj5.SelectPlayfair_CipherTyepEncryption();
                }
                else if(Choice==5)
                {
                    cout << "enter the msg" << endl;
                    string ori,k;
                    cin >> ori;
                    cout<<"Enter The Key"<<endl;
                    cin>>k;
                    Vigenere obj3(k);
                    cout << "the Decrption is " << obj3.decryption(ori)<<endl;
                }
                else
                {
                    exit(0);
                }


}


int main()
{
    int x;
    for(int j = 0; j<100 ; j++)
    {

        cout<<"---(1)Encrypt Or (2)Decrypt---\n"<<endl;
        cin>>x;
        if(x==1)
        {
            Display_All_Encryption();
        }
        else if(x==2)
        {
            Display_All_Decryption();
        }

        else
            {return 0;}
    }


    return 0;

}
