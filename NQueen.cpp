/*@@�H�u���z�@�~-2
  @@�ϥΪ��s�t��k��@�K�ӦZ*/

#include <iostream>
#include <random>
#include <vector>

class NQueen {
protected:
	std::vector<std::vector<int>> map;
	
	int _size;

public:
	std::vector<int> X, Y;
	NQueen(int assign) {
		_size = assign;
	}


	//�ƻsvector : main_vector  to  copy_vector
	void vector_cpy(std::vector<int> &main_vector, std::vector<int> &copy_vector) {
		copy_vector.clear();
		copy_vector.assign(main_vector.begin(), main_vector.end());
	}


	void rand() {
		clean();
		std::random_device rd; //�Q�εw��t�ε����ȨӨ���
		std::default_random_engine generator(rd()); //��l�ơA�çQ��rd()���ȧ�X�۹������ؤl�X??
		std::uniform_int_distribution<int> distribution(0, _size - 1); //�]�w�d��P�M�w�n���ͤ����������ü� ex:int float..
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
		//��l�ƴѽL
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
					std::cout << "��";
				else
					std::cout << "��";
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


	int price(std::vector<int> x,std::vector<int> y) {
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


	bool move(std::vector<int> &y,int row) {
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
				std::cout << "End of Search.  price=" << price(X,Y) << std::endl;
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
	std::cin >> n;
	while (true) {
		NQueen queen(n);
		queen.start();
		std::cin >> n;
		if (n <= 3)
			break;
	}
	

	system("pause");
	return 0;
}