#pragma once

class field {
public:
	field();

    field(int size);

	field(std::string filename);

    void print();

    void rotate(int x, int y, int n);

    std::vector<std::vector<int>> rotate_test(int x, int y, int n);

    bool is_complete();

	int setting(int size);
    int setting(std::string filename);

    int size();

    std::vector<int>& operator[](size_t row) {
        if (row >= entity.size()) {
            throw std::out_of_range("Row index out of range");
        }
        return entity[row];
    }

    const std::vector<int>& operator[](size_t row) const {
        if (row >= entity.size()) {
            throw std::out_of_range("Row index out of range");
        }
        return entity[row];
    }
private:
    std::vector<std::vector<int>> entity;
};
