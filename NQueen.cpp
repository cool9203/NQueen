/*@@�H�u���z�@�~-2
  @@�ϥΪ��s�t��k��@�K�ӦZ*/

#include <iostream>
#include <random>
#include <vector>

class NQueen {
protected:
	std::vector<std::vector<int>> map;

public:
	NQueen(int assign) {
		//��l�ƴѽL
		for (int i = 0; i < assign; i++) {
			std::vector<int> tempv;
			for (int j = 0; j < assign; j++) {
				tempv.push_back(0);
			}
			map.push_back(tempv);
		}
	}


	//�ƻsvector : main_vector  to  copy_vector
	void vector_cpy(std::vector<std::vector<int>> &main_vector, std::vector<std::vector<int>> &copy_vector) {
		copy_vector.clear();
		copy_vector.assign(main_vector.begin(), main_vector.end());
	}


	//�M��map
	void clean() {
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			for (int j = 0; j < static_cast<int>(map.size()); j++) {
				map.at(i).at(j) = 0;
			}
		}
	}


	//�H����map�@�ӽL��(�T�w�C����u��1�ӬӦZ)
	void rand() {
		clean();
		std::random_device rd; //�Q�εw��t�ε����ȨӨ���
		std::default_random_engine generator(rd()); //��l�ơA�çQ��rd()���ȧ�X�۹������ؤl�X??
		std::uniform_int_distribution<int> distribution(0, map.size() - 1); //�]�w�d��P�M�w�n���ͤ����������ü� ex:int float..
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			int randnumber = distribution(generator);
			if (map.at(i).at(randnumber)!=1)
				map.at(i).at(randnumber) = 1;
		}
	}


	//���
	void print() {
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			for (int j = 0; j < static_cast<int>(map.size()); j++) {
				std::cout << map.at(j).at(i) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}


	//��ܮy��(0 ~ N-1)
	void print_coordinate() {
		std::vector<int> x, y;
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			for (int j = 0; j < static_cast<int>(map.size()); j++) {
				if (map[i][j] == 1) {
					x.push_back(i);
					y.push_back(j);
				}
				if (map.size() == x.size())
					break;
			}
			if (map.size() == x.size())
				break;
		}
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			std::cout << "(" << x.at(i) << "," << y.at(i) << ")\n";
		}
	}


	//�Q�αײv�ӭp��
	int price_slope(std::vector<std::vector<int>> v) {
		std::vector<int> x, y;
		for (int i = 0; i < static_cast<int>(v.size()); i++) {
			for (int j = 0; j < static_cast<int>(v.size()); j++) {
				if (v[i][j] == 1) {
					x.push_back(i);
					y.push_back(j);
				}
				if (v.size() == x.size())
					break;
			}
			if (v.size() == x.size())
				break;
		}
		return slope(v, x, y);
		
	}


	//�ײv�p�� - �p�Gxy=0�A�Y����榳��L�l    �p�G(y/x)==1.0 or -1.0 �Y�צ榳��L�l
	int slope(std::vector<std::vector<int>> v, std::vector<int> _x, std::vector<int> _y) {
		int count = 0;
		for (int i = 0; i < static_cast<int>(v.size()); i++) {
			for (int j = i + 1; j < static_cast<int>(v.size()); j++) {
				double x = _x[i] - _x[j];
				double y = _y[i] - _y[j];
				double m = y / x;
				if (x == 0.0 || y == 0.0 || m == 1.0 || m == -1.0) {
					count++;
					continue;
				}
			}
		}
		return count;
	}


	//�Q�θӤl�O�_���P��L�l�Ĭ��ӭp��(�ӦZ���k�G���I���B���B�צ�)
	int price_conflict(std::vector<std::vector<int>> v) {
		int count = 0;
		for (int i = 0; i < static_cast<int>(v.size()); i++) {
			for (int j = 0; j < static_cast<int>(v.size()); j++) {
				if (v.at(i).at(j) == 1) {
					count += conflict(v, i, j);
					//std::cout << count << " ";
				}
			}
		}
		//std::cout << std::endl;
		return count;
	}


	int conflict(std::vector<std::vector<int>> v, int row,int col) {
		int count = 0;
		int utdl_row = row, dtul_row = row;
		int utdl_col = col, dtul_col = col;
		bool utd_b = false, dtu_b = false;
		//�p����I���ƾ�ƪ��Ĭ��
		for (int i = 0; i < static_cast<int>(v.size()); i++) {
			if (v[row][i] == 1 && i != col)
				count++;

			if (v[i][col] == 1 && i != row)
				count++;

			//����U������|�Ϊ����ܼ�
			if (utdl_row != 0 && utdl_col != 0) {
				utdl_row--;
				utdl_col--;
			}
			if (dtul_row != 0 && dtul_col != v.size() - 1) {
				dtul_row--;
				dtul_col++;
			}
		}
		//�p����I���䪺�Ĭ��
		
		while (true) {
			if (utd_b && dtu_b)
				break;

			if (utdl_row != v.size() && utdl_col != v.size()) {
				if (v[utdl_row][utdl_col] == 1 && utdl_row != row && utdl_col != col)
					count++;
				utdl_row++;
				utdl_col++;
			}
			else {
				utd_b = true;
			}

			if (dtul_row != v.size() && dtul_col != -1) {
				if (v[dtul_row][dtul_col] == 1 && dtul_row != row && dtul_col != col)
					count++;
				dtul_row++;
				dtul_col--;
			}
			else {
				dtu_b = true;
			}
		}
		return count;
	}


	//�i�}����ù�ڰ���A�ݬO�_����֪�price   if price��� return true
	bool move(std::vector<std::vector<int>> &v, int _row, int func) {
		int price;
		if (func == 1)
			price = price_slope(v);
		else
			price = price_conflict(v);
		for (int col = 0; col < static_cast<int>(v.size()); col++) {
			for (int i = 0; i < static_cast<int>(v.size()); i++) { //���M�Ũ���
				v[_row][i] = 0;
			}

			v[_row][col] = 1; //set
			int vp;
			if (func == 1)
				vp = price_slope(v);
			else
				vp = price_conflict(v);

			if (vp < price) //�p�G������ than
				return true;
		}
		return false;
	}


	//�i�}�Ҧ��A���U�@�B�����price��   if price��� return true
	bool search(int func) {
		for (int i = 0; i < static_cast<int>(map.size()); i++) {
			std::vector<std::vector<int>> v;
			vector_cpy(map, v);
			if (move(v, i, func)) { //if ������ than
				vector_cpy(v, map);
				if (func==1)
					std::cout << "End of Search.  price_slope=" << price_slope(map) << std::endl;
				else
					std::cout << "End of Search.  price_conflict=" << price_conflict(map) << std::endl;
				return true;
			}
		}
		return false;
	}


	//���H�����@�L�� -> ��price��_��0(�Y�z�Q���A) -> if price==0 return and print   else loop
	void start_slope() {
		while (true) {
			rand();
			while (true) {
				if (!search(1)) {
					if (price_slope(map) == 0) {
						print();
						std::cout << "\n" << "price_conflict:" << price_conflict(map) << std::endl;
						return;
					}
					else {
						break;
					}
				}
			}
			std::cout << "\n";
		}
	}


	void start_conflict() {
		while (true) {
			rand();
			while (true) {
				if (!search(0)) {
					if (price_conflict(map) == 0) {
						print();
						std::cout << "\n" << "price_slope:" << price_slope(map) << std::endl;
						return;
					}
					else {
						break;
					}
				}
			}
			std::cout << "\n";
		}
	}
};


/*
int main() {
	NQueen queen(8);
	//queen.start_slope();
	queen.start_conflict();
	queen.print_coordinate();
	
	system("pause");
	return 0;
}
*/