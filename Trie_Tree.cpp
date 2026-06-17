#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<queue>
using namespace std;
class Trie_Tree{
    private:
    struct Trie_node{
        Trie_node(char ch_):
        ch(ch_),
        freq(0)
        {}
        char ch;
        int freq;
        map<char,Trie_node*>next;
    };
    Trie_node* head;
    public:
    Trie_Tree(){
        head=new Trie_node('\0');
    }
    ~Trie_Tree(){
        queue<Trie_node*>que;
        que.emplace(head);
        while(!que.empty()){
            Trie_node*cur=que.front();
            que.pop();
            for(map<char,Trie_node*>::iterator i=cur->next.begin();i!=cur->next.end();i++){
                que.emplace(i->second);
            }
            delete cur;
        }
    }
    void add(const string& word){
        Trie_node*cur=head;
        for(int i=0;i<word.size();i++){
            auto child=cur->next.find(word[i]);
            if(child==cur->next.end()){
                auto set_=new Trie_node(word[i]);
                cur->next.emplace(word[i],set_);
                cur=set_;
            }
            else{
                cur=child->second;
            }
        }
        cur->freq++;
    }
    int query(const string &word){
        Trie_node*cur=head;
        for(int i=0;i<word.size();i++){
            auto child=cur->next.find(word[i]);
            if(child==cur->next.end()){
                return 0;
            }
            else{
                cur=child->second;
            }
        }
        return cur->freq;
    }
    void Trie_show(){
        vector<string>word_list;
        string cur_word="\0";
        Trie_show(word_list,cur_word,head);
        for(auto& str:word_list){
            cout<<str<<' ';
        }
        cout<<endl;
    }
    vector<string> query_prefix(const string & pre){
        vector<string>result;
        string word=pre;
        Trie_node*cur=head;
        for(int i=0;i<pre.size();i++){
            auto child=cur->next.find(pre[i]);
            if(child==cur->next.end()){
                return result;
            }
            cur=child->second;
        }
        Trie_show(result,word,cur);
        return result;
    }
    void remove(const string& str){
        Trie_node* cur = head;
        Trie_node* del = head;
        int rem = 0;

        for(int i = 1; i <= str.size(); i++){
            auto child = cur->next.find(str[i-1]);
            if(child == cur->next.end()){
                return;
            }
            if(cur->next.size() > 1 || (cur->freq > 0 && i != str.size())){
                del = child->second;
                rem = i;
            }
            cur = child->second;
        }

        if(cur->freq == 0){
            return;
        }

        if(!cur->next.empty()){
            cur->freq = 0;
            return;
        }

        Trie_node* parent = head;
        char erase_ch;
        if(rem == 0){
            erase_ch = str[0];
            del = head->next[erase_ch];
            head->next.erase(erase_ch);
        } else {
            for(int j = 1; j <= rem - 1; j++){
                parent = parent->next.find(str[j-1])->second;
            }
            erase_ch = str[rem - 1];
            del = parent->next[erase_ch];
            parent->next.erase(erase_ch);
        }

        Trie_node* node = del;
        while(node != cur){
            auto next_ = node->next.begin()->second;
            delete node;
            node = next_;
        }
        delete cur;
    }
    private:
    void Trie_show(vector<string>&word_list,string word,Trie_node*node){
        for(auto child=node->next.begin();child!=node->next.end();child++){
            auto child_con=child->second;
            word.push_back(child_con->ch);
            if(child_con->freq!=0){
                word_list.push_back(word);
            }
            Trie_show(word_list,word,child_con);
            word.pop_back();
        }
    }
};
int main(){
    Trie_Tree trie;
    trie.add("ciallo");
    trie.add("aiallo");
    trie.add("aiaiio");
    trie.add("freqse");
    trie.add("chocolate");

    cout<<trie.query("ciallo")<<endl;
    trie.Trie_show();
    vector<string>res=trie.query_prefix("aia");
    for(auto valcabulary:res){
        cout<<valcabulary<<' ';
    }
    cout<<endl;

    trie.remove("freqse");
    cout<<trie.query("freqse")<<endl;
}