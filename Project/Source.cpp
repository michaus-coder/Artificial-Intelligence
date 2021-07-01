#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<conio.h>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

class Siswa {
	int number;
	string nama;
	int penghasilan, umur, tanggungan;
	int nilai, prestasi, keaktifan;
	int berat;
	int value;
public:
	Siswa() {
		nama = "";
		berat = 0;
		value = 0;
		penghasilan = 0;
		umur = 0;
		tanggungan = 0;
		nilai = 0;
		prestasi = 0;
		keaktifan = 0;
	}
	void setAll(int _number, string _nama, int _berat, int _value, int _penghasilan, int _umur, int _tanggungan, int _nilai, int _prestasi, int _keaktifan) {
		number = _number;
		nama = _nama;
		berat = _berat;
		value = _value;
		penghasilan = _penghasilan;
		umur = _umur;
		tanggungan = _tanggungan;
		nilai = _nilai;
		prestasi = _prestasi;
		keaktifan = _keaktifan;
	}
	void setNumber(int _number) {
		number = _number;
	}
	void setNama(string _nama) {
		nama = _nama;
	}
	void setBerat(int _berat) {
		berat = _berat;
	}
	void setValue(int _value) {
		value = _value;
	}
	void setPenghasilan(int _penghasilan) {
		penghasilan = _penghasilan;
	}
	void setUmur(int _umur) {
		umur = _umur;
	}
	void setTanggungan(int _tanggungan) {
		tanggungan = _tanggungan;
	}
	void setKeaktifan(int _keaktifan) {
		keaktifan = _keaktifan;
	}
	void setNilai(int _nilai) {
		nilai = _nilai;
	}
	string getNama() {
		return nama;
	}
	int getNumber() {
		return number;
	}
	int getBerat() {
		return berat;
	}
	int getValue() {
		return value;
	}
	int getPenghasilan() {
		return penghasilan;
	}
	int getUmur() {
		return umur;
	}
	int getTanggungan() {
		return tanggungan;
	}
	int getNilai() {
		return nilai;
	}
	int getPrestasi() {
		return prestasi;
	}
	int getKeaktifan() {
		return keaktifan;
	}
};

class listSiswa {
	Siswa* list;
	int count;
	int budget, min, max;
public:
	listSiswa() {
		count = 0;
		list = new Siswa[count];
		budget = 100000000;
		min = 2000000;
		max = 10000000;
	}
	void addSiswa(Siswa input) {
		Siswa* temp = new Siswa[count + 1];
		for (int i = 0; i < count; i++) {
			temp[i] = list[i];
		}
		temp[count] = input;
		delete[]list;
		list = temp;
		count++;
	}
	void editSiswa(int index, Siswa edit) {
		if (index > 0 && index < count)
		{
			list[index].setNama(edit.getNama());
			list[index].setBerat(edit.getBerat());
			list[index].setValue(edit.getValue());
		}
		else {
			cout << "Index out of range";
		}
	}
	void deleteSiswa(int index) {
		Siswa* temp = new Siswa[count - 1];
		int co = 0;
		for (int i = 0; i < count; i++) {
			if (i != index)
			{
				temp[co] = list[i];
				co++;
			}
		}
		delete[]list;
		list = temp;
		count--;
	}
	void showSiswa() {
		for (int i = 0; i < count; i++)
		{
			cout << "Index		: " << i << endl;
			cout << "Nama		: " << list[i].getNama() << endl;
			cout << "Beasiswa	: " << list[i].getBerat() << endl;
			cout << "Value		: " << list[i].getValue() << endl;
			cout << endl;
		}
	}

	Siswa getSiswaByIndex(int index) {
		return list[index];
	}

	int getCount() {
		return count;
	}

	int getWeightByIndex(int index) {
		return list[index].getBerat();
	}

	void setBudget(int _budget) {
		budget = _budget;
	}

	void setMin(int _min) {
		min = _min;
	}

	void setMax(int _max) {
		max = _max;
	}

	int getMin() {
		return min;
	}

	int getMax() {
		return max;
	}

	int getBudget() {
		return budget;
	}
};


class individual {
	int count;
	Siswa* item;
	int totalberat;
	int totalvalue;
public:
	individual() {
		count = 0;
		item = new Siswa[count];
		totalberat = 0;
		totalvalue = 0;
	}
	void setItemPerIndexChild(int _count, individual a) {
		item = new Siswa[_count];
		for (int i = 0; i < _count; i++)
		{
			item[i] = a.getItem(i);
		}
		count = _count;
	}
	int getCountIndividual() {
		return count;
	}
	int getNumberItemByIndex(int index) {
		return item[index].getNumber();
	}
	Siswa getItem(int index) {
		return item[index];
	}
	void addGen(Siswa input) {
		Siswa* tmp = new Siswa[count + 1];
		for (int i = 0; i < count; i++) {
			tmp[i] = item[i];
		}
		tmp[count] = input;
		delete[]item;
		item = tmp;
		count++;
	}
	void InitIndividual(listSiswa a, int budget) {
		int tmpweight = 0;
		int tmpcount = 0;
		int arr[100];
		bool check;
		int random;
		int tmp = a.getCount();
		int check_count = 0;
		listSiswa copy;
		for (int i = 0; i < a.getCount(); i++) {
			copy.addSiswa(a.getSiswaByIndex(i));
		}
		while (tmpweight < budget && tmp > tmpcount) {
			random = rand() % copy.getCount();
			check_count++;
			if ((tmpweight + copy.getWeightByIndex(random)) >= budget && check_count < copy.getCount()) {
				continue;
			}
			else if ((tmpweight + copy.getWeightByIndex(random)) >= budget && check_count >= copy.getCount()) {
				break;
			}
			addGen(copy.getSiswaByIndex(random));
			tmpweight = tmpweight + copy.getWeightByIndex(random);
			copy.deleteSiswa(random);
			tmpcount++;
			

		}
		
		count = tmpcount;
		totalberat = tmpweight;
		totalvalue = getFitnessIndividual();
	}
	int getFitnessIndividual() {
		for (int i = 0; i < count; i++)
		{
			totalvalue = totalvalue + item[i].getValue();
		}
		return totalvalue;
	}
	int getWeightTotal() {
		for (int i = 0; i < count; i++)
		{
			totalberat = totalberat + item[i].getBerat();
		}
		return totalberat;
	}
	int getValue() {
		return totalvalue;
	}
	int getTotalBerat() {
		return totalberat;
	}
	void change_item(int index, Siswa change) {
		item[index] = change;
	}
	bool checkisi(int a) {
		for (int i = 0; i < count; i++)
		{
			if (a == item[i].getNumber()) {
				return true;
			}
		}
		return false;
	}
	void display() {
		for (int i = 0; i < count; i++)
		{
			cout << "[" << item[i].getNumber() << "]";
		}
	}
	void showList() {
		for (int i = 0; i < count; i++)
		{
			cout << "====================================================================" << endl;
			cout << "Index               : " << item[i].getNumber() << endl;
			cout << "Name                : " << item[i].getNama() << endl;
			cout << "Monthly Income      : " << item[i].getPenghasilan() << endl;
			cout << "Parent Age (Father) : " << item[i].getUmur() << endl;
			cout << "Monthly Outcome     : " << item[i].getTanggungan() << endl;
			cout << "Average Score       : " << item[i].getNilai() << endl;
			cout << "Achievement         : " << item[i].getPrestasi() << endl;
			cout << "Contribution        : " << item[i].getKeaktifan() << endl;
			int beasiswa = item[i].getBerat(); 
			cout << "Beasiswa            : " << beasiswa << endl;
			cout << "====================================================================" << endl;
			cout << endl;
		}
	}
};

class population {
	int count;
	individual* data;
	int totalvaluepopulation;
public:
	population() {
		count = 0;
		data = new individual[count];
		totalvaluepopulation = 0;
	}
	int getCountPopulation() {
		return count;
	}
	int getTotalValuePopulation() {
		for (int i = 0; i < count; i++)
		{
			totalvaluepopulation = totalvaluepopulation + data[i].getValue();
		}
		return totalvaluepopulation;
	}
	void setPopulation(individual a[], int _count) {
		count = _count;
		data = new individual[count];
		for (int i = 0; i < count; i++)
		{
			data[i] = a[i];
		}
	}
	int getValueByIndex(int index) {
		return data[index].getValue();
	}
	individual getDataByIndex(int index) {
		return data[index];
	}
	void display() {
		for (int i = 0; i < count; i++)
		{
			cout << "Individual " << i + 1 << " : ";
			data[i].display();
			cout << endl;
			cout << "Total Fitness : " << data[i].getValue() << endl;
			cout << "Total Berat : " << data[i].getTotalBerat() << endl;
			cout << endl;
		}
	}
	void add_population(individual a) {
		individual* tmp;
		tmp = new individual[count + 1];
		for (int i = 0; i < count; i++)
		{
			tmp[i] = data[i];
		}
		tmp[count] = a;
		delete[]data;
		data = tmp;
		count++;
	}
	void setDataByIndex(int index, individual a) {
		data[index] = a;
	}
};

individual randomselection(population a) {
	individual tmp;
	int total = a.getTotalValuePopulation();
	int random = rand() % total;
	int random_array[6];
	for (int i = 0; i < a.getCountPopulation(); i++)
	{
		if (i == 0) {
			random_array[i] = a.getValueByIndex(i);
		}
		else {
			random_array[i] = random_array[i - 1] + a.getValueByIndex(i);
		}
	}
	for (int i = 0; i < a.getCountPopulation(); i++)
	{
		if (random <= random_array[i]) {
			tmp = a.getDataByIndex(i);
			break;
		}
	}
	return tmp;
}

bool checkParent(individual x, individual y) {
	int tmpx, tmpy;
	tmpx = x.getCountIndividual();
	tmpy = y.getCountIndividual();
	if (tmpx == tmpy) {
		int count = 0;
		for (int i = 0; i < tmpx; i++)
		{
			if (x.getNumberItemByIndex(i) == y.getNumberItemByIndex(i)) {
				count++;
			}
		}
		if (count == tmpx) {
			return true;
		}
	}
	else {
		return false;
	}
}

individual reproduce(individual x, individual y, int random) {
	individual child;
	child.setItemPerIndexChild(x.getCountIndividual(), x);
	for (int i = 0; i < random; i++)
	{
		for (int j = 0; j < child.getCountIndividual(); j++)
		{
			if (child.getNumberItemByIndex(j) == y.getNumberItemByIndex(i)) {
				Siswa temp = child.getItem(i);
				child.change_item(i, child.getItem(j));
				child.change_item(j, temp);
			}
		}
		child.change_item(i, y.getItem(i));
	}
	return child;
}

void mutate(individual& child, listSiswa n) {
	int rand_point = rand() % child.getCountIndividual();
	bool check = true;
	while (check)
	{
		int rand_item = rand() % child.getCountIndividual();
		if (!child.checkisi(rand_item))
		{
			check = false;
			child.change_item(rand_point, n.getSiswaByIndex(rand_item));
		}
	}
}

void bubble_sort(population item) {

	for (int i = 1; i < item.getCountPopulation(); i++) {
		for (int j = item.getCountPopulation() - 1; j >= i; j--) {
			if (item.getValueByIndex(j) > item.getValueByIndex(j - 1)) {
				individual temp;
				temp = item.getDataByIndex(j - 1);
				item.setDataByIndex(j - 1, item.getDataByIndex(j));
				item.setDataByIndex(j, temp);
			}
		}
	}
	cout << endl;
}

float countWeight(int penghasilan, int tanggungan, int umur, int min, int max) {
	float tempweight = penghasilan - tanggungan;
	float weight = 0;
	if (tempweight >= 7500000) {
		weight = min;
	}
	else if (tempweight >= 5000000 && tempweight < 7500000) {
		weight = 0.25 * max;
	}
	else if (tempweight >= 3000000 && tempweight < 5000000) {
		weight = 0.50 * max;
	}
	else if (tempweight >= 2000000 && tempweight < 3000000) {
		weight = 0.75 * max;
	}
	else if (tempweight >= 1000000 && tempweight < 2000000) {
		weight = 0.90 * max;
	}
	else if (tempweight < 1000000) {
		weight = max;
	}

	if (umur >= 65) {
		weight = weight + ((umur / 100) * min);
	}
	
	return weight;
}

float countValue(int nilai, int prestasi, int keaktifan) {
	float value;
	value = nilai + (prestasi * 10) + (keaktifan * 5);
	return value;
}



individual genetic_algorithm(listSiswa input) {
	individual data[6];
	for (int i = 0; i < 6; i++)
	{
		data[i].InitIndividual(input, input.getBudget());
	}
	population datapopulasi;
	datapopulasi.setPopulation(data, 6);
	datapopulasi.display();

	population newpopulation;
	individual x, y;
	
	for (int i = 0; i < 50; i++)
	{
		for (int i = 0; i < datapopulasi.getCountPopulation(); i++)
		{
			x = randomselection(datapopulasi);
			y = randomselection(datapopulasi);
			while (checkParent(x, y) == true) {
				y = randomselection(datapopulasi);
			}
			cout << endl;
			cout << "X : ";
			x.display();
			cout << endl;
			cout << "Y : ";
			y.display();

			individual child1;
			individual child2;
			int tmp;
			if (x.getCountIndividual() > y.getCountIndividual()) {
				tmp = y.getCountIndividual();
			}
			else {
				tmp = x.getCountIndividual();
			}
			int randomchild = rand() % tmp - 1;
			if (randomchild <= 0) {
				randomchild = 1;
			}
			cout << endl;
			cout << "Random Number : " << randomchild;
			child1 = reproduce(x, y, randomchild);
			child2 = reproduce(y, x, randomchild);
			cout << endl;
			cout << "Child 1 : ";
			child1.display();
			cout << endl;
			cout << "Child 2 : ";
			child2.display();
			cout << endl;
			if ((rand() % 100) < 5)
			{
				mutate(child1, input);
				cout << endl << "Child 1 After Mutate" << endl;
				child1.display();
				cout << endl;
			}
			if ((rand() % 100) < 5)
			{
				mutate(child2, input);
				cout << endl << "Child 2 After Mutate" << endl;
				child2.display();
				cout << endl;
			}
			newpopulation.add_population(child1);
			newpopulation.add_population(child2);
		}
		for (int i = 0; i < datapopulasi.getCountPopulation(); i++)
		{
			newpopulation.add_population(datapopulasi.getDataByIndex(i));
		}
		bubble_sort(newpopulation);
		population datapopulasi;
		for (int i = 0; i < 5; i++)
		{
			datapopulasi.add_population(newpopulation.getDataByIndex(i));
		}
	}
	bubble_sort(datapopulasi);
	individual a = datapopulasi.getDataByIndex(0);
	
	return a;
}

void main() {
	srand(time(NULL));
	ifstream inFile;
	Siswa data;
	listSiswa arr;
	individual result;
	int choice;
	int counterdata = 1;
	do {
		system("CLS");
		cout << "Menu : " << endl;
		cout << "1. Input Data" << endl;
		cout << "2. Edit Data" << endl;
		cout << "3. Delete Data" << endl;
		cout << "4. Show Data" << endl;
		cout << "5. Process Data" << endl;
		cout << "6. Show Result" << endl;
		cout << "7. Input Data by Excel Format File" << endl;
		cout << "8. Set Budget, Minimum & Maximum" << endl;
		cout << "0. Exit" << endl;
		cout << "Input Choice : ";
		cin >> choice;	cin.ignore();
		if (choice == 1) {
			string nama;
			int penghasilan, umur, tanggungan;
			int nilai, prestasi, keaktifan;
			int cosemster, avgscore, temp, temp_score = 0;
			cout << "Input Data : " << endl;
			cout << "Name : "; getline(cin, nama);
			cout << "Monthly Income : "; cin >> penghasilan;
			cout << "Parent Age (Father) : "; cin >> umur;
			cout << "Monthly Outcome : "; cin >> tanggungan;

			cout << "What Semester Are you ? "; cin >> cosemster;
			for (int i = 0; i < cosemster; i++) {
				cout << "Semester " << i << "'s Average Score : "; cin >> temp;
				temp_score += temp;
			}
			avgscore = temp_score / cosemster;
			nilai = avgscore;
			cout << "Achievement : "; cin >> prestasi;
			cout << "Contribution : "; cin >> keaktifan;
			int berat = countWeight(penghasilan, tanggungan, umur, arr.getMin(), arr.getMax());
			int value = countValue(nilai, prestasi, keaktifan);
			data.setAll(counterdata, nama, berat, value, penghasilan, umur, tanggungan, nilai, prestasi, keaktifan);
			arr.addSiswa(data);
			counterdata++;
			cout << "Siswa Added" << endl;
			system("pause");
		}
		else if (choice == 2) {
			int index;
			string nama;
			int penghasilan, umur, tanggungan;
			int nilai, prestasi, keaktifan;
			int cosemster, avgscore, temp, temp_score = 0;
			cout << "List Siswa" << endl;
			arr.showSiswa();
			cout << "Index : " << endl;
			cin >> index;
			cin.ignore();
			cout << "Input Data : " << endl;
			cout << "Name : "; getline(cin, nama);
			cout << "Monthly Income : "; cin >> penghasilan;
			cout << "Parent Age (Father) : "; cin >> umur;
			cout << "Monthly Outcome : "; cin >> tanggungan;
			cout << "What Semester Are you ? "; cin >> cosemster;
			for (int i = 0; i < cosemster; i++) {
				int tempco = i + 1;
				cout << "Semester " << tempco << "'s Average Score : "; cin >> temp;
				temp_score += temp;
			}
			avgscore = temp_score / cosemster;
			nilai = avgscore;
			cout << "Achievement : "; cin >> prestasi;
			cout << "Contribution : "; cin >> keaktifan;
			int berat = countWeight(penghasilan, tanggungan, umur, arr.getMin(), arr.getMax());
			int value = countValue(nilai, prestasi, keaktifan);
			Siswa tempSiswa;
			tempSiswa.setAll(counterdata, nama, berat, value, penghasilan, umur, tanggungan, nilai, prestasi, keaktifan);
			arr.editSiswa(index, tempSiswa);
			cout << "Siswa Edited" << endl;
			system("pause");
		}
		else if (choice == 3) {
			int index;
			cout << "Input Index yang ingin di hapus: ";
			cin >> index;
			arr.deleteSiswa(index);
			cout << "Siswa Deleted" << endl;
			system("pause");
		}
		else if (choice == 4) {
			cout << "List Siswa" << endl;
			arr.showSiswa();
			system("pause");

		}
		else if (choice == 5) {
			result = genetic_algorithm(arr);
			system("pause");

		}
		else if (choice == 6) {
			cout << "Scholarship Achiever List" << endl;
			result.showList();

			cout << "Total Weight : " << result.getTotalBerat() << endl;
			cout << "Total Value : " << result.getValue() << endl;
			system("pause");

		}
		else if (choice == 7) {
			fstream fin;
			fin.open("dummy_data.csv", ios::in);
			int rollnum, roll2, count = 0;
			vector<string> row;
			string line, word, temp;
			while (fin >> line) {

				row.clear();
				stringstream s(line);
				while (getline(s, word, ',')) {
					row.push_back(word);
				}
				
				int counter = stoi(row[0]);
				string nama = row[1];
				int penghasilan = stoi(row[2]);
				int umur = stoi(row[3]);
				int tanggungan = stoi(row[4]);
				int nilai = stoi(row[5]);
				int prestasi = stoi(row[6]);
				int keaktifan = stoi(row[7]);
				cout << "Counter: " << counter << "\n";
				cout << "Nama: " << nama << "\n";
				cout << "Penghasilan: " << penghasilan << "\n";
				cout << "Umur: " << umur << "\n";
				cout << "Tanggungan: " << tanggungan << "\n";
				cout << "Nilai: " << nilai << "\n";
				cout << "Prestasi: " << prestasi << "\n";
				cout << "Keaktifan: " << keaktifan << "\n";
				int berat = countWeight(penghasilan, tanggungan, umur, arr.getMin(), arr.getMax());
				int value = countValue(nilai, prestasi, keaktifan);
				data.setAll(stoi(row[0]), nama, berat, value, penghasilan, umur,tanggungan, nilai, prestasi, keaktifan);
				arr.addSiswa(data);
			}
			system("pause");
		}
		else if (choice == 8) {
			int _budget, _min, _max;
			cout << "Budget : ";
			cin >> _budget;
			cout << "Min    : ";
			cin >> _min;
			cout << "Max    : ";
			cin >> _max;
			arr.setBudget(_budget);
			arr.setMin(_min);
			arr.setMax(_max);
			system("pause");

		}
	} while (choice != 0);
}