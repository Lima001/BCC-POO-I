#include <iostream>
#include <functional>

using namespace std;
 
std::function<int (int)> gerar(int x){

	auto func = [=](int valor){return valor * x;};
	return func;

}

int main(){

	std::function<int (int)> dobrar = gerar(2);
	cout << dobrar(5) << endl;
	
	return 0;
}