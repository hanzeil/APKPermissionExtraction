#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_iterators.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
namespace fs = std::experimental::filesystem;
class PermissionExtraction {
public:
	void start() {
		findAllManifest();
		allPermission();
		countPermission();
		FeatureMatrix();
		print();
	}
private:
	void findAllManifest(); //找到目录中所有的AndroidManifest.xml文件
	void allPermission(); //找出所有应用具有的权限,保存在permisison变量中
	void countPermission(); //计算所有权限出现的次数
	void FeatureMatrix(); //构建特征矩阵
	void print(); //打印特征矩阵和permissionCount

	const fs::path p="C:/Users/hanze/Documents/Visual Studio 2015/Projects/APKPermissionExtraction/Debug/apk/";
	std::unordered_map<std::string, int> permission; //权限编号，便于管理
	std::vector<std::string> manifest; //所有manifest文件目录
	std::vector<std::vector<std::string>> app2permission; //每个应用的权限集合
	std::unordered_map<std::string, int> permissionCount; //每个权限出现的个数
	std::vector<std::vector<int>> matrix; //特征矩阵，表示第几个app具有第几个权限，目测这是一个稀疏矩阵，暂时使用邻接矩阵存储
};