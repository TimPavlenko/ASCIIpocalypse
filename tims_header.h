// tims_header.h
// ������������ ���� �� ������ ������� ��� �������� ��� ������� �������

#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <typeinfo>
#include <stdarg.h>
#include <codecvt> // codecvt_utf8
#include <locale>  // wstring_convert

/*namespace th {
    void print(std::string str, char end = '\n');
    std::vector <std::string> split(std::string str, char separator);
    std::string cut(std::string str, std::string to_cut);
}*/

// ############## classes ##############
class Vector2i {
public:
	int x, y;
	Vector2i(){ x=0; y=0; }
	Vector2i(int nx, int ny){ x=nx; y=ny; }
};

class Vector3i {
public:
	int x, y, z;
	Vector3i(){ x=0; y=0; z=0; }
	Vector3i(int nx, int ny, int nz){ x=nx; y=ny; z=nz; }
};



// ############## funcs ##############

int rfr(int n1, int n2){ // rand_from_range
	return (n1 + rand() % n2);
}

void print(auto str, char end='\n') {
    /*
    switch typeid(str).name() {
    case ("string" or "char"):
        std::cout << str << endl;
        break;
    }
    */
	std::cout << str << end;
}

std::vector <std::string> split(std::string str, char separator) {
    std::vector <std::string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}


std::vector <std::wstring> wsplit(std::wstring str, wchar_t separator) {
    std::vector <std::wstring> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            std::wstring temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

std::string cut(std::string str, std::string to_cut) {
    while (str.find(to_cut) != std::string::npos) {
        if (!to_cut.empty()) {
            std::string::const_iterator sub = std::find_end(str.begin(), str.end(), to_cut.begin(), to_cut.end());
            if (sub != str.end()) {
                str.erase(sub, sub + to_cut.size());
            }
        }
    }
    return str;
}

std::string read_file(std::string path) {
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

int div_up(int x, int y){
    return (x + y - 1) / y;
}

void print_int(int n, ...){
  va_list argptr;
  va_start(argptr, n);
  int x;
  for (int i = 0; i < n; i++)
  {
    x = va_arg(argptr, int);
    printf("%d ", x);
  }
  va_end(argptr);
}

/*std::string cat(std::string *s, ...){ // попытка определить универсальную операцию строковой конкатинации
	std::string **p = &s;         //--берем адрес-адреса
	std::string res = "";
    while (*p!=0){
		res+=(**p);
		p++;
    }
    return res;
}*/ // костыли:

std::string cat(auto s1, auto s2){
	return std::string{s1}+std::string{s2};
}
std::string cat(auto s1, auto s2, auto s3){
	return std::string{s1}+std::string{s2}+std::string{s3};
}
std::wstring wcat(std::wstring s1, std::wstring s2){
	std::wstring rez = s1;
	rez+=s2;
	return rez;
}
std::wstring wcat(std::wstring s1, std::wstring s2, std::wstring s3){
	std::wstring rez = s1;
	rez+=s2;
	rez+=s3;
	return rez;
}

bool to_bool(std::string const& s) {
     return (s != "0" and s != "true");
}

std::string rem(int n, std::string s, std::string addstr=" "){ // remaining
	std::string srez = "";

	for(int i=0; i<n; i++){
		if(i+1 < s.size()){
			srez += s[i];
		}else{
		    srez += addstr;
		}
	}

	return srez;
}

std::wstring wrem(int n, std::wstring s, std::wstring addstr=L" "){ // remaining
	std::wstring srez = L"";

	for(int i=0; i<n; i++){
		if(i+1 < s.size()){
			srez += s[i];
		}else{
		    srez += addstr;
		}
	}

	return srez;
}

std::string rem_center(int n, std::string s, std::string addstr=" "){
	std::string srez = "";
	bool flag = true;

	for(int i=0; i<n; i++){
		if(i+1 < s.size()){
			srez += s[i];
		}else{
			if(flag){
				srez = addstr + srez;
			}else{
				srez += addstr;
			}
			flag = !flag;
		}
	}
	return srez;
}

Vector2i square_center(int size_x, int size_y){
	Vector2i res;
	res.x = div_up(size_x, 2);
	res.y = div_up(size_y, 2);
	return res;
}
