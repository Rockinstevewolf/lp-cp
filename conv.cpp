#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct person{
	string id;
	string name;
	string sex;
};
person destr_p(person data){
	data.id.clear(), data.name.clear(), data.sex.clear();
	return data;
}

struct fam{
	person dad;
	person mom;
	vector<person> child;
};
fam destr_f(fam data){
	data.dad = destr_p(data.dad);
	data.mom = destr_p(data.mom);
	data.child.clear();
	return data;
}


string kill_slash(string s){
	int n = s.length();
	string out = "";
	string get_char;
	for(int i = 0; i < n-1; i++){
		get_char = s.substr(i,1);
		if(get_char != "/"){
			out = out + get_char;
		}
	}
	//cout << out << endl;
	return out;
}

string translit(string s){
	int n = s.length();
	string out = "";
	string get_char;
	for(int i = 0; i < n; i++){
		get_char = s.substr(i,2);
        	 if(get_char == "а")	out = out + "a";
        else if(get_char == "б")	out = out + "b";
        else if(get_char == "в")	out = out + "v";
        else if(get_char == "г")	out = out + "g";
        else if(get_char == "д")	out = out + "d";
        else if(get_char == "е")	out = out + "e";
        else if(get_char == "ё")	out = out + "ye";
        else if(get_char == "ж")	out = out + "zh";
        else if(get_char == "з")	out = out + "z";
        else if(get_char == "и")	out = out + "i";
        else if(get_char == "й")	out = out + "y";
        else if(get_char == "к")	out = out + "k";
        else if(get_char == "л")	out = out + "l";
        else if(get_char == "м")	out = out + "m";
        else if(get_char == "н")	out = out + "n";
        else if(get_char == "о")	out = out + "o";
        else if(get_char == "п")	out = out + "p";
        else if(get_char == "р")	out = out + "r";
        else if(get_char == "с")	out = out + "s";
        else if(get_char == "т")	out = out + "t";
        else if(get_char == "у")	out = out + "u";
        else if(get_char == "ф")	out = out + "f";
        else if(get_char == "х")	out = out + "ch";
        else if(get_char == "ц")	out = out + "z";
        else if(get_char == "ч")	out = out + "ch";
        else if(get_char == "ш")	out = out + "sh";
        else if(get_char == "щ")	out = out + "ch";
        //else if(get_char == "ъ")	out = out + "''";
        else if(get_char == "ы")	out = out + "y";
        //else if(get_char == "ь")	out = out + "''";
        else if(get_char == "э")	out = out + "e";
        else if(get_char == "ю")	out = out + "yu";
        else if(get_char == "я")	out = out + "ya";
        else if(get_char == "А")	out = out + "A";
        else if(get_char == "Б")	out = out + "B";
        else if(get_char == "В")	out = out + "V";
        else if(get_char == "Г")	out = out + "G";
        else if(get_char == "Д")	out = out + "D";
        else if(get_char == "Е")	out = out + "E";
        else if(get_char == "Ё")	out = out + "Ye";
        else if(get_char == "Ж")	out = out + "Zh";
        else if(get_char == "З")	out = out + "Z";
        else if(get_char == "И")	out = out + "I";
        else if(get_char == "Й")	out = out + "Y";
        else if(get_char == "К")	out = out + "K";
        else if(get_char == "Л")	out = out + "L";
        else if(get_char == "М")	out = out + "M";
        else if(get_char == "Н")	out = out + "N";
        else if(get_char == "О")	out = out + "O";
        else if(get_char == "П")	out = out + "P";
        else if(get_char == "Р")	out = out + "R";
        else if(get_char == "С")	out = out + "S";
        else if(get_char == "Т")	out = out + "T";
        else if(get_char == "У")	out = out + "U";
        else if(get_char == "Ф")	out = out + "F";
        else if(get_char == "Х")	out = out + "Ch";
        else if(get_char == "Ц")	out = out + "Z";
        else if(get_char == "Ч")	out = out + "Ch";
        else if(get_char == "Ш")	out = out + "Sh";
        else if(get_char == "Щ")	out = out + "Ch";
        //else if(get_char == "Ъ")	out = out + "''";
        else if(get_char == "Ы")	out = out + "Y";
        //else if(get_char == "Ь")	out = out + "''";
        else if(get_char == "Э")	out = out + "E";
        else if(get_char == "Ю")	out = out + "Yu";
        else if(get_char == "Я")	out = out + "Ya";
        else if(get_char == " ")	out = out + " ";
    }
    return out;
}

string parent_generator(person parent, person child){
	string buff, comma="','", tok="').", par="parent('";
	buff = par + parent.name + comma + child.name + tok;
	return buff;
}
string sex_generator(person human){
	string buff, comma="','", tok="').", sex="sex('";
	if(human.sex[0] == 'M'){
		string male = "m";
		buff = sex + human.name + comma + male + tok;
	}
	else if(human.sex[0] == 'F'){
		string fem = "f";
		buff = sex + human.name + comma + fem + tok;
	}
	return buff;
}

int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, "Russian");
	int k = 0;
	bool done = false;
	person p_buff,zero;
	fam f_buff;
	vector<person> list;
	string NAME="1 NAME", SEX = "1 SEX", HUSB = "1 HUSB", WIFE = "1 WIFE", CHILD = "1 CHIL", RIN_MH = "1 RIN MH:F";
	string line, check, file_out;
	ifstream file;
	string filename;
	if(argc == 1){
		filename = "heritage.ged";
		file.open(filename);
	}
	else{
		filename = argv[1];
		file.open(filename);
	}
	if(file.is_open()){
		cout << filename << "....is...........working...\n";
	}
	else{
		cout << "Error, no file provided!\n";
		file.close();
		return 0;
	}
	int n=0;
	ofstream fout;
	fout.open("list.pl");
	while(!file.eof()){
		getline(file,line);
//получаем список всех людей
		if((line[0] == '0') && (line[12] == 'I')){
			p_buff = destr_p(p_buff);
			p_buff.id = line.substr(3,7);
			//cout << buff.id.size() << endl;
		}
		else if(line.substr(0,6) == NAME){
			p_buff.name = line.substr(7);
			p_buff.name = kill_slash(p_buff.name.substr(0,p_buff.name.size()-1));
			if(line[8] == '/'){
				p_buff.name = "Unknown";
			}
		}
		else if(line.substr(0,5) == SEX){
			p_buff.sex = line.substr(6,1);
			list.push_back(p_buff);
		}
//обрабатываем семьи
		else if((line[0] == '0') && (line[12] == 'F')){
			f_buff = destr_f(f_buff);
		}
		else if(line.substr(0,6) == HUSB){
			for(n=0; n<list.size();n++){
				if(line.substr(8,7) == list.at(n).id){
					f_buff.dad = list.at(n);
					//cout << f_buff.dad.sex << "    " << f_buff.dad.id << ":   " << f_buff.dad.name << endl;
				}
			}
		}
		else if(line.substr(0,6) == WIFE){
			for(n=0; n<list.size();n++){
				if(line.substr(8,7) == list.at(n).id){
					f_buff.mom = list.at(n);
					//cout << f_buff.mom.sex << "   " << f_buff.mom.id << ":  " << f_buff.mom.name << endl;
				}
			}
		}
		else if(line.substr(0,6) == CHILD){
			for(n=0; n<list.size();n++){
				if(line.substr(8,7) == list.at(n).id){
					f_buff.child.push_back(list.at(n));
					k++;
					//cout << f_buff.child.at(i).sex << "   " << f_buff.child.at(i).id << ":  " << f_buff.child.at(i).name << endl;
				}
			}
		}
		else if(line.substr(0,10) == RIN_MH){
			if(f_buff.dad.id != destr_p(zero).id){
				for(n=0; n<f_buff.child.size(); n++){
					file_out = parent_generator(f_buff.dad,f_buff.child.at(n));
					fout << file_out << endl;
				}
				done = true;
			}
			if(f_buff.mom.id != destr_p(zero).id){
				for(n=0; n<f_buff.child.size(); n++){
					file_out = parent_generator(f_buff.mom,f_buff.child.at(n));
					fout << file_out << endl;
				}
				done = true;
			}
		}
	}
	for(person hum : list){
		file_out = sex_generator(hum);
		fout << file_out << endl;
	}


	fout.close();
	file.close();
	if(done) cout << "Everything is DONE!\nCheck your new data in 'list.pl'\n";
	else cout << "Couldn't convert your file\nPlease give the true '*.ged' file\n";
	/*cout << translit(list.at(15).name) << endl;
	cout << list.at(13).name << endl;
	k = list.at(13).name.length();
	for(n=0;n<k;n++)
		cout << ".";
	cout << endl << k << endl;*/
	return 0;
}
