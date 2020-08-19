// https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/

class Solution {
public:
    class TrieNode {
        public:
            TrieNode* children[27];
            bool isEnd;
            TrieNode() : isEnd(0) {
                memset(children, NULL, sizeof children);
            }
    };
    class Trie {
        public:
            Trie() : root_(new TrieNode()) {
            }
            void AddFolders(vector<string>& folder) {
                for (string& s : folder)
                    AddFolder(s);
            }
            vector <string> getCompressed(vector <string>& folder) {
                vector <string> compressed;
                for (const string s : folder)
                    if (!IsPartOfAnother(s))
                        compressed.push_back(s);
                return compressed;
            }
        private:
            TrieNode* root_;
            void AddFolder(const string& folder) {
                TrieNode* cur = root_;
                for (char c : folder) {
                    int ind = (c == '/' ? 26 : c - 'a');
                    if (!cur->children[ind])
                        cur->children[ind] = new TrieNode();
                    cur = cur->children[ind];
                }
                cur->isEnd = 1;
            }
            bool IsPartOfAnother(const string& folder) {
                TrieNode* cur = root_;
                for (int i = 0; i < folder.size() - 1; ++i) {
                    if (cur->isEnd && folder[i] == '/') return true;
                    int ind = (folder[i] == '/' ? 26 : folder[i] - 'a');
                    cur = cur->children[ind];
                }
                return false;
            }
    };
    vector<string> removeSubfolders(vector<string>& folder) {
        Trie trie = Trie();
        trie.AddFolders(folder);
        return trie.getCompressed(folder);
    }
};