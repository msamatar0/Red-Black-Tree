#include "rbtree.h"

int main(){
	kvpair nodes[26]{
		kvpair(18, "Laguna Niguel"),
		kvpair(41, "Mission Viejo"),
		kvpair(22, "San Clemente"),
		kvpair(44, "Irvine"),
		kvpair(58, "Lake Forest"),
		kvpair(32, "San Diego"),
		kvpair(49, "Anaheim"),
		kvpair(31, "Los Angeles"),
		kvpair(17, "Orange"),
		kvpair(72, "Palm Springs"),
		kvpair(41, "Riverside"),
		kvpair(19, "Brea"),
		kvpair(60, "Santa Ana"),
		kvpair(35, "Tustin"),
		kvpair(103, "Oceanside"),
		kvpair(103, "Oceanside"),
		kvpair(18, "Del Mar"),
		kvpair(22, "Aliso Viejo"),
		kvpair(49, "Laguna Beach"),
		kvpair(42, "Vista"),
		kvpair(49, "San Diego"),
		kvpair(99, "San Juan"),
		kvpair(29, "Dana Point"),
		kvpair(88, "El Segundo"),
		kvpair(41, "San Clemente"),
		kvpair(62, "Laguna Hills")
	};
	cout << "Nodes[\n";
	for(kvpair i : nodes)
		cout << "  " << i << endl;
	cout << "]\n";
	redBlackTree<int, string> dict;
	int i = 0;
	for(; i < 4; ++i)
		dict.add(nodes[i]);
	//dict.remove(41);
	for(; i < 7; ++i)
		dict.add(nodes[i]);
	//dict.remove(58);
	for(; i < 11; ++i)
		dict.add(nodes[i]);
	//dict.remove(73);
	for(; i < 19; ++i)
		dict.add(nodes[i]);
	//dict.remove(41);
	for(; i < 26; ++i)
		dict.add(nodes[i]);
	cout << dict << endl;
}