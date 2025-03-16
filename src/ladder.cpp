#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg)
{
    cerr << word1 << word2 << msg;
}

bool edit_distance_within(const std::string & str1, const std::string & str2, int d)
{
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1-len2) > d) return false;
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
    for (int i = 0; i <= len1; ++i) dp[i][0] = i;
    for (int j = 0; j <= len2; ++j) dp[0][j] = j;
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (str1[i - 1] == str2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else {
                dp[i][j] = min({dp[i - 1][j - 1],  
                                dp[i - 1][j],      
                                dp[i][j - 1]}) + 1;}
        }
    }
    return dp[len1][len2] <= d;
}

bool is_adjacent(const string& word1, const string & word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string> & word_list)
{
    queue<vector<string>> paths;
    vector<string> ladder_begin = {begin_word};
    paths.push(ladder_begin);
    set<string> v;
    vector<string> e;
    v.insert(begin_word);
    while(!paths.empty())
    {
        int level_size = paths.size();
        set<string> level_visited;
        for(int i = 0; i < level_size; i++) {
            vector<string> ladder = paths.front();
            paths.pop();
            string last = ladder.back();
            for(const string & word : word_list) {
                if (is_adjacent(last, word) && v.find(word) == v.end()) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                paths.push(new_ladder);
                v.insert(word);
                }
            }
        }
        v.insert(level_visited.begin(), level_visited.end());
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream in(file_name);
    if (!in) 
    {
        error(file_name, "not opened", " "); return; 
    }

    string word;
    while (in >> word)
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.empty()) {error("ladder is empty", " ", " "); return;}
    for (size_t i = 0; i < ladder.size(); ++i)
        cout << ladder[i] << " ";
    cout << endl;
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}