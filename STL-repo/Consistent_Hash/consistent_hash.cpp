#include<iostream>
#include<list>
#include<string>
#include<functional>
#include<set>
#include <unordered_map>
#include <chrono>
using namespace std;
using uint = unsigned int;

uint get_md5(string i) {
	size_t h = std::hash<string>{}(i);
	return static_cast<uint>(h & 0xFFFFFFFFu);
}

class physical_host;
class virtual_host {
private:
	string ip_vir;
	physical_host* ori_host;
	uint md5_;
public:
	virtual_host(string ip, physical_host* ptr) :
		ip_vir(ip), ori_host(ptr) {
		md5_ = get_md5(ip_vir);
	};
	bool operator<(const virtual_host& obj) const{
		return md5_ < obj.md5_;
	}
	uint fmd5_() const{
		return (uint)md5_;
	}
	physical_host* get_phyhost() const {
		return ori_host;
	}
};

class physical_host {
private:
	string ip_;
	list<virtual_host> vir_list;
	uint num_;
public:
	physical_host(string ip, int num) :
		ip_(ip) ,num_(num){
		if(num>=1)
		for (int i = 0; i < num; i++) {
			vir_list.push_back(
				virtual_host::virtual_host(
					ip + '#' + to_string(i),
					this
				)
			);
		}
	}
	list<virtual_host>& get_virlist() {
		return vir_list;
	}
	string get_ip() {
		return ip_;
	}
};

class consistent_hash {
private:
	set<virtual_host> hash_circle;
public:
	void add_server(physical_host&phy_ho) {
		auto list = phy_ho.get_virlist();
		for (virtual_host mem : list) {
			hash_circle.insert(mem);
		}
		cout << "add successed" << endl;
	}
	void del_server(physical_host& phy_ho) {
		auto list = phy_ho.get_virlist();
		for (virtual_host mem : list) {
			auto it = hash_circle.find(mem);
			if (it != hash_circle.end()) {
				hash_circle.erase(it);
			}
		}
		cout << "del successed" << endl;
	}
	string assign(string ip_import) {
		uint md5 = get_md5(ip_import);
		for (auto obj : hash_circle) {
			if (md5 < obj.fmd5_()) {
				return obj.get_phyhost()->get_ip();
			}
		}
		if (!hash_circle.empty())
			return (*(hash_circle.begin())).get_phyhost()->get_ip();
		else
			throw"erro";
	}
};

static string make_key(int idx) {
	return string("key_") + to_string(idx);
}

int main() {
	consistent_hash ch;

	physical_host p1("192.168.0.1", 3);
	physical_host p2("192.168.0.2", 5);
	physical_host p3("192.168.0.3", 8);

	ch.add_server(p1);
	ch.add_server(p2);
	ch.add_server(p3);

	cout << "\nSingle-key assignments (sample):" << endl;
	vector<string> sample_keys = { "user:alice", "user:bob", "order:12345", "session:xyz" };
	for (auto& k : sample_keys) {
		cout << "  " << k << " -> " << ch.assign(k) << '\n';
	}

	const int N = 10000;
	unordered_map<string, int> dist_before;
	dist_before.reserve(16);

	for (int i = 0; i < N; ++i) {
		string k = make_key(i);
		string host = ch.assign(k);
		dist_before[host]++;
	}

	cout << "\nDistribution across physical hosts (before removal):" << endl;
	for (auto& p : dist_before) {
		double pct = (100.0 * p.second) / N;
		cout << "  " << p.first << ": " << p.second << " (" << pct << "%)\n";
	}

	vector<string> assignments_before(N);
	for (int i = 0; i < N; ++i) assignments_before[i] = ch.assign(make_key(i));

	ch.del_server(p2);

	unordered_map<string, int> dist_after;
	dist_after.reserve(16);
	int moved = 0;
	for (int i = 0; i < N; ++i) {
		string k = make_key(i);
		string host = ch.assign(k);
		dist_after[host]++;
		if (host != assignments_before[i]) ++moved;
	}

	cout << "\nDistribution across physical hosts (after removal of " << p2.get_ip() << "):" << endl;
	for (auto& p : dist_after) {
		double pct = (100.0 * p.second) / N;
		cout << "  " << p.first << ": " << p.second << " (" << pct << "%)\n";
	}

	cout << "\nKeys moved due to removal: " << moved << " / " << N
		<< " (" << (100.0 * moved / N) << "%)\n";

	ch.add_server(p2);
	int returned = 0;
	for (int i = 0; i < N; ++i) {
		string host = ch.assign(make_key(i));
		if (host == assignments_before[i]) ++returned;
	}
	cout << "\nKeys that returned to original host after re-adding: " << returned << " / " << N
		<< " (" << (100.0 * returned / N) << "%)\n";

	cout << "\nEdge-case checks:" << endl;
	string longkey(1000, 'x');
	cout << "  long key -> " << ch.assign(longkey) << '\n';
	cout << "  special key '!@#$%^&*()' -> " << ch.assign("!@#$%^&*()") << '\n';

	cout << "\nTest complete." << endl;
	return 0;
}