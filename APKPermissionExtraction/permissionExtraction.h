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
	void findAllManifest(); //�ҵ�Ŀ¼�����е�AndroidManifest.xml�ļ�
	void allPermission(); //�ҳ�����Ӧ�þ��е�Ȩ��,������permisison������
	void countPermission(); //��������Ȩ�޳��ֵĴ���
	void FeatureMatrix(); //������������
	void print(); //��ӡ���������permissionCount

	const fs::path p="C:/Users/hanze/Documents/Visual Studio 2015/Projects/APKPermissionExtraction/Debug/apk/";
	std::unordered_map<std::string, int> permission; //Ȩ�ޱ�ţ����ڹ���
	std::vector<std::string> manifest; //����manifest�ļ�Ŀ¼
	std::vector<std::vector<std::string>> app2permission; //ÿ��Ӧ�õ�Ȩ�޼���
	std::unordered_map<std::string, int> permissionCount; //ÿ��Ȩ�޳��ֵĸ���
	std::vector<std::vector<int>> matrix; //�������󣬱�ʾ�ڼ���app���еڼ���Ȩ�ޣ�Ŀ������һ��ϡ�������ʱʹ���ڽӾ���洢
};