#include <iostream>
#include <fstream>
#include "json.hpp"
#include "field.h"

using json = nlohmann::json;

field::field() {};

field::field(int size) {
	entity = std::vector<std::vector<int>>(size, std::vector<int>(size, -1));
}

field::field(std::string filename) {
	if (setting(filename) == -1) {
		exit(EXIT_FAILURE);
	}
}

void field::print() {
    int size = int(entity.size());

    std::cout << "-------output-------" << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << entity[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

void field::rotate(int x, int y, int n) {
    std::vector<std::vector<int>> tmp_entity = entity;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            entity[y + n - i - 1][x + j] = tmp_entity[y + j][x + i];
        }
    }
}

std::vector<std::vector<int>> field::rotate_test(int x, int y, int n) {
    std::vector<std::vector<int>> tmp_entity = entity;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tmp_entity[y + n - i - 1][x + j] = entity[y + j][x + i];
        }
    }
    return tmp_entity;
}

bool field::is_complete() {
    int size = int(entity.size());
    std::vector<int> list = { 1, -1 }; // リストでペア管理したほうが実行時間早いかも

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            bool no_pair = true;
            for (auto v : list) {
                if (i + v >= 0 && i + v < size) {
                    if (entity[i][j] == entity[i + v][j]) {
                        no_pair = false;
                        break;
                    }
                }
                if (j + v >= 0 && j + v < size) {
                    if (entity[i][j] == entity[i][j + v]) {
                        no_pair = false;
                        break;
                    }
                }
            }
            if (no_pair == true) return false;
        }
    }
    return true;
}

int field::setting(int size) {
	entity = std::vector<std::vector<int>>(size, std::vector<int>(size, -1));
	return 0;
}

int field::setting(std::string filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "指定のファイルが見つかりませんでした" << std::endl;
		return -1;
	}
	else if (std::string{ filename.end() - 5, filename.end() } != ".json") {
		std::cout << "指定のファイルはJSONファイルではありません" << std::endl;
		return -1;
	}

	nlohmann::json data;
	file >> data;

	int size = data["problem"]["field"]["size"];
	for (int i = 0; i < size; i++) {
		std::vector<int> tmp;
		for (int j = 0; j < size; j++) {
			tmp.push_back(data["problem"]["field"]["entities"][i][j]);
		}
		entity.push_back(tmp);
	}
	return 0;
}

int field::size() {
    return int(entity.size());
}
