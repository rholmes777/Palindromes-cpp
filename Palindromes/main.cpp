//
//  main.cpp
//  Palindromes
//
//  Created by Richard Holmes on 1/10/13.
//  Copyright (c) 2013 Richard Holmes. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const char* DICTIONARY_FILE_NAME = "/usr/share/dict/words";

vector<string> GetDictionaryWords(void)
{
    vector<string> ret;
    ifstream dictFile(DICTIONARY_FILE_NAME);
    string s;
    while (getline(dictFile, s)) {
        // store only the substring with word's characters, omitting the trailing newline of each word.
        ret.push_back(s.substr(0, s.size()));
    }
    return ret;
}

bool IsPalindrome(const string& aWord)
{
    vector<string>::size_type front = 0, back = aWord.size() - 1;
    
    while (front <= back)
    {
        if (aWord[front] != aWord[back])
        {
            return false;
        } else {
            if (front != back) {
                ++front;
                --back;
            } else {
                return true;
            }
        }
    }
    return true;
}

void TestPalindrome(const string& aWord, bool isPalindrome)
{
    if (IsPalindrome(aWord) == isPalindrome)
        cout << (isPalindrome ? "T: " : "F: ") << "Pass: " << aWord << " is " << (isPalindrome ? "" : "NOT ") << "a palindrome." << endl;
    else
        cout << (isPalindrome ? "T: " : "F: ") << "Fail: " << aWord << " is " << (isPalindrome ? "NOT " : "") << "a palindrome." << endl;
}

void SimpleTest()
{
    TestPalindrome("dad\n", false);
    TestPalindrome("A", true);
    TestPalindrome("AbbA", true);
    TestPalindrome("crap", false);
    TestPalindrome("ana", true);
    TestPalindrome("bada", false);
    TestPalindrome("cr", false);
    TestPalindrome("cc", true);
    TestPalindrome("dad", true);
    TestPalindrome("aa", true);
}

int main(int argc, const char * argv[])
{        
    // SimpleTest();

    vector<string> words = GetDictionaryWords();
    vector<string>::size_type longestSize = 0;
    string longestPalindrome;
    vector<string> longestPalindromes;
    
    for (auto aWord = words.begin(); aWord != words.end(); ++aWord)
    {
        if (IsPalindrome(*aWord))
        {
            if (aWord->size() > longestSize)
            {
                longestPalindromes.clear();
                longestSize = aWord->size();
                longestPalindromes.push_back(*aWord);
            } else if (aWord->size() == longestSize) {
                longestPalindromes.push_back(*aWord);
            }
        }
    }
    
    cout << "The longest palindrome size in our dictionary is " << longestSize << " characters: " << endl;
    for (auto aPalindrome = longestPalindromes.begin(); aPalindrome != longestPalindromes.end(); ++aPalindrome)
    {
        cout << *aPalindrome << endl;
    }
    
    return 0;
}

