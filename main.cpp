#include <iostream> 
#include <string>
#include <vector>
#include <sstream>


template<typename T>
std::string toHash(T unhashed[], int n) {
  std::vector<unsigned int> hashvec;
  double A=0.61803398875; // обратное отношение золотого сечения
  for(int i = 0; i < n; ++i) {
    hashvec.push_back((unsigned int)(unhashed[i]*n*n*n));
  }
  for(int i = 0; i < hashvec.size(); ++i) {
    hashvec[i] = n*fmod((hashvec[i]*A), 1); // хеширование умножением
    hashvec[i] <<= 2;
  }
  unsigned long int h[8];
  h[0]=0xc1059ed8UL;	h[1]=0x367cd507UL;
	h[2]=0x3070dd17UL;	h[3]=0xf70e5939UL;
	h[4]=0xffc00b31UL;	h[5]=0x68581511UL;
	h[6]=0x64f98fa7UL;	h[7]=0xbefa4fa4UL;
  while(!hashvec.empty()) {
    for(int i = 0; !hashvec.empty(); ++i) {
      h[i] += hashvec.back();
      hashvec.pop_back();
      i%=8;
    }
  }
  std::string hash;
  std::stringstream ss;
  for(int i = 0; i < 8; ++i) {
    ss << std::hex << h[i];
  }
  hash = ss.str();
  return hash;
}
template<>
std::string toHash(double unhashed[], int n) { //для double нужна отдельная функция, чтобы не потерять хотя бы 5 значений после запятой
  std::vector<unsigned int> hashvec;
  double A=0.61803398875; // обратное отношение золотого сечения
  for(int i = 0; i < n; ++i) {
    hashvec.push_back((unsigned int)(unhashed[i]*100000*n*n*n));
  }
  for(int i = 0; i < hashvec.size(); ++i) {
    hashvec[i] = n*fmod((hashvec[i]*A), 1); // хеширование умножением
    hashvec[i] <<= 2;
  }
  unsigned long int h[8];
  h[0]=0xc1059ed8UL;	h[1]=0x367cd507UL;
	h[2]=0x3070dd17UL;	h[3]=0xf70e5939UL;
	h[4]=0xffc00b31UL;	h[5]=0x68581511UL;
	h[6]=0x64f98fa7UL;	h[7]=0xbefa4fa4UL;
  while(!hashvec.empty()) {
    for(int i = 0; !hashvec.empty(); ++i) {
      h[i] *= hashvec.back();
      hashvec.pop_back();
      i%=8;
    }
  }
  std::string hash;
  std::stringstream ss;
  for(int i = 0; i < 8; ++i) {
    ss << std::hex << h[i];
  }
  hash = ss.str();
  return hash;
}


int main() {
  int intarray[] = {28143, 62643, 53935, 63922, 88071, 13317, 26393, 17752};
  double doublearray[] = {632.49543, 823.91432, 188.75238, 265.50126, 719.93643, 880.59621, 548.43605, 802.39721};
  std::cout << toHash("Hello World", 11) << std::endl; // запускаю по 2 раза, чтобы убедиться в "нерандомности" хеш суммы
  std::cout << toHash("Hello World", 11) << std::endl;
  std::cout << toHash(intarray, 8) << std::endl;
  std::cout << toHash(intarray, 8) << std::endl;
  std::cout << toHash(doublearray, 8) << std::endl;
  std::cout << toHash(doublearray, 8) << std::endl;
}
