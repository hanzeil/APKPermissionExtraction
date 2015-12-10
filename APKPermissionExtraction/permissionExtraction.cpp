#include "permissionExtraction.h"
void PermissionExtraction::findAllManifest() {
	using namespace std;
	for (auto item : fs::directory_iterator(p)) {
		for (auto item2 : fs::directory_iterator(item)) {
			string xmlPath = item2.path().string() + "/AndroidManifest.xml";
			if (fs::exists(xmlPath)) {
				manifest.push_back(xmlPath);
			}
		}
	}
}
void PermissionExtraction::allPermission() {
	using namespace rapidxml;
	app2permission.resize(manifest.size());
	for (size_t t = 0; t < manifest.size(); t++) {
		file<> fxml(manifest[t].c_str());
		xml_document<> doc;
		doc.parse<0>(fxml.data());
		xml_node<>* root = doc.first_node();
		xml_node<>* next = root->first_node();
		while (next) {
			//找到uses-permission节点
			if (strcmp(next->name(), "uses-permission") == 0) {
				xml_attribute<> *attr = next->first_attribute();
				while (attr) {
					//找到android:name属性的值
					if (strcmp(attr->name(), "android:name") == 0) {
						//记录在permission里
						app2permission[t].push_back(std::string(attr->value()));
					}
					attr = attr->next_attribute();
				}
			}
			next = next->next_sibling(); //下一个节点
		}
	}
}
void PermissionExtraction::countPermission() {
	for (auto app : app2permission) {
		for (auto itemOfPermission : app) {
			static int number = 0;
			permissionCount[itemOfPermission]++; //每个权限出现的个数
			if (permission.find(itemOfPermission) == permission.end()) {
				permission[itemOfPermission] = number++; //给每个权限从0开始编号
			}
		}
	}
}
void PermissionExtraction::FeatureMatrix() {
	matrix.resize(manifest.size());
	for (size_t i = 0; i < matrix.size(); i++) {
		fill_n(back_inserter(matrix[i]),permission.size(),0); //每一行插入n个0，n为出现过权限的个个数
		for (auto itemOfPermission : app2permission[i]) {
			int j = permission[itemOfPermission];
			std::cout << j << std::endl;
			matrix[i][j] = 1;
		}
	}
}
void PermissionExtraction::print() {
	std::ofstream f1("permissionCount.txt");
	std::ofstream f2("matrix.txt");
	for (auto item : permissionCount) {
		f1 << item.first << " " << item.second << std::endl;
	}
	f1.close();
	for (auto line : matrix) {
		for (auto col : line) {
			f2 << col << " ";
		}
		f2 << std::endl;
	}
	f2.close();
}