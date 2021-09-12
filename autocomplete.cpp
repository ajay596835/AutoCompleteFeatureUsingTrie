#include <bits/stdc++.h>

using namespace std;

struct trienode {
  bool is_word;
  trienode * child[26];

};

trienode * get_new_node() {
  trienode * temp = new trienode;
  temp -> is_word = false;

  for (int i = 0; i < 26; i++) {
    temp -> child[i] = NULL;
  }

  return temp;
}

void insert(trienode * root, string key) {
  trienode * temp = root;

  for (int i = 0; i < (int) key.length(); i++) {
    int ind = int(key[i]) - 'a';
    if (temp -> child[ind] == NULL) {
      temp -> child[ind] = get_new_node();
    }
    temp = temp -> child[ind];
  }

  temp -> is_word = true;
}

void find_all_words(trienode * root, string key, vector < string > & all_words) {
  if (root == NULL) return;
  trienode * temp = root;

  for (int i = 0; i < (int) key.size(); i++) {
    int ind = int(key[i]) - 'a';
    if (temp -> child[ind] == NULL) return;

    temp = temp -> child[ind];
  }

  queue < pair < trienode * , string > > q;
  q.push(make_pair(temp, key));
  string this_word;
  while (!q.empty()) {
    temp = q.front().first;
    this_word = q.front().second;
    if (temp -> is_word) all_words.push_back(this_word);
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (temp -> child[i] != NULL) {
        q.push(make_pair(temp -> child[i], this_word + char(i + int('a'))));
      }
    }
  }

}

void auto_complete(trienode * root, string key) {
  if (key.size() == 0) return;

  vector < string > all_words;

  find_all_words(root, key, all_words);

  if (all_words.size() == 0) {
    cout << "There are no suggestions." << '\n';
    return;
  }

  cout << "There are " << all_words.size() << " suggestions for this prefix " << key << '\n';
  for (int i = 0; i < (int) all_words.size(); i++) {
    cout << all_words[i] << ' ';
  }

  return;
}

int main() {
  int n;
  cin >> n;
  vector < string > dict;
  string key;
  for (int i = 0; i < n; i++) {
    cin >> key;
    dict.push_back(key);
  }

  trienode * root = get_new_node();

  for (int i = 0; i < dict.size(); i++) {
    insert(root, dict[i]);
  }

  cout << "Enter key to autocomplete :" << '\n';
  cin >> key;
  auto_complete(root, key);
  return 0;
}