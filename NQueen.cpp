/*@@人工智慧作業-2
  @@使用爬山演算法實作八皇后*/

#include <iostream>
#include <random>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

class NQueen {
protected:
	std::vector<std::vector<int>> map;

	int _size;
	std::default_random_engine generator; //偽亂數產生器
	std::random_device rd; //利用硬體系統給的值來得到一個隨機數
	std::uniform_int_distribution<int> distribution;

public:
	std::vector<int> X, Y;
	NQueen(int assign) {
		_size = assign;
		generator.seed(rd()); //設定偽亂數產生器的seed
		//設定亂數分布範圍
		std::uniform_int_distribution<int>::param_type param(0, this->_size - 1);
		distribution.param(param);
	}


	//複製vector : main_vector  to  copy_vector
	void vector_cpy(std::vector<int>& main_vector, std::vector<int>& copy_vector) {
		copy_vector.clear();
		copy_vector.assign(main_vector.begin(), main_vector.end());
	}


	void rand() {
		clean();
		for (int i = 0; i < _size; i++) {
			int randnumber = this->distribution(this->generator);
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
		LARGE_INTEGER start_time, end_time, frequency_time;
		QueryPerformanceFrequency(&frequency_time);
		QueryPerformanceCounter(&start_time);

		NQueen queen(n);
		queen.start();

		QueryPerformanceCounter(&end_time);
		printf("used:%lf s\n\n", (end_time.QuadPart - start_time.QuadPart) / (double)(frequency_time.QuadPart));
	}


	system("pause");
	return 0;
}
