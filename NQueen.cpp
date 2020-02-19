/*@@人工智慧作業-2
  @@使用爬山演算法實作八皇后*/

#include <iostream>
#include <random>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

class NQueen {
protected:
	std::vector<std::vector<int>> map;

	int _size;

public:
	std::vector<int> X, Y;
	NQueen(int assign) {
		_size = assign;
	}


	//複製vector : main_vector  to  copy_vector
	void vector_cpy(std::vector<int>& main_vector, std::vector<int>& copy_vector) {
		copy_vector.clear();
		copy_vector.assign(main_vector.begin(), main_vector.end());
	}


	void rand() {
		clean();
		std::random_device rd; //利用硬體系統給的值來取值
		std::default_random_engine generator(rd()); //初始化，並利用rd()的值找出相對應的種子碼??
		std::uniform_int_distribution<int> distribution(0, _size - 1); //設定範圍與決定要產生什麼類型的亂數 ex:int float..
		for (int i = 0; i < _size; i++) {
			int randnumber = distribution(generator);
			X.push_back(i);
			Y.push_back(randnumber);
		}
	}


	void clean() {
		X.clear();
		Y.clear();
	}


	void set_map() {
		map.clear();
		//初始化棋盤
		for (int i = 0; i < _size; i++) {
			std::vector<int> tempv;
			for (int j = 0; j < _size; j++) {
				tempv.push_back(0);
			}
			map.push_back(tempv);
		}

		for (int i = 0; i < static_cast<int>(X.size()); i++) {
			map[X.at(i)][Y.at(i)] = 1;
		}
	}


	void print() {
		set_map();

		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (map[i][j] == 1)
					std::cout << "╳";
				else
					std::cout << "＿";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}


	int price(std::vector<int> x, std::vector<int> y, int p) {
		int count = 0;
		for (int i = 0; i < _size; i++) {
			for (int j = i + 1; j < _size; j++) {
				double _x = x[i] - x[j];
				double _y = y[i] - y[j];
				double m = _y / _x;
				if (_x == 0.0 || _y == 0.0 || m == 1.0 || m == -1.0) {
					count++;
					if (count >= p)
						return count;
					continue;
				}
			}
		}

		return count;
	}


	int price(std::vector<int> x, std::vector<int> y) {
		int count = 0;
		for (int i = 0; i < _size; i++) {
			for (int j = i + 1; j < _size; j++) {
				double _x = x[i] - x[j];
				double _y = y[i] - y[j];
				double m = _y / _x;
				if (_x == 0.0 || _y == 0.0 || m == 1.0 || m == -1.0) {
					count++;
					continue;
				}
			}
		}

		return count;
	}


	bool move(std::vector<int>& y, int row) {
		int p = price(X, y);
		for (int col = 0; col < _size; col++) {
			y.at(row) = col;//set

			int vp = price(X, y, p);
			if (vp < p)
				return true;
		}
		return false;
	}


	bool search() {
		for (int i = 0; i < _size; i++) {
			std::vector<int> y;
			vector_cpy(Y, y);
			if (move(y, i)) {
				vector_cpy(y, Y);
				std::cout << "End of Search.  price=" << price(X, Y) << std::endl;
				return true;
			}
		}
		return false;
	}


	void start() {
		int count = 0;
		while (true) {
			rand();
			while (true) {
				if (!search()) {
					if (price(X, Y) == 0) {
						print();
						std::cout << "restart:" << count << "\n";
						return;
					}
					else {
						break;
					}
				}
			}
			count++;
		}
	}
};


int main() {
	int n;
	while (true) {
		std::cin >> n;
		if (n <= 3)
			break;
		clock_t start_time, end_time;
		start_time = clock();
		NQueen queen(n);
		queen.start();
		end_time = clock();
		std::cout << "end. used:" << (end_time - start_time) / (double)(clock_t(1000)) << "s" << std::endl;
	}


	system("pause");
	return 0;
}
