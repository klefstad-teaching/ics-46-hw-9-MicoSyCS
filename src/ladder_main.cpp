#include "ladder.h"
#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

int main()
{
/*    set<string> word_list;
    string file_name = "src/words.txt";
    load_words(word_list, file_name);
    string begin_word, end_word;
    cout << "enter start: ";
    cin >> begin_word;
    cout << "enter end: ";
    cin >> end_word;

    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);

    if (!ladder.empty()) {
        cout << "Found\n";
        print_word_ladder(ladder);
    }
    else cout << "No ladder\n";
*/

    verify_word_ladder();
    return 0;

}