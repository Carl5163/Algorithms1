#include <iostream>
#include <fstream>

using namespace std;

float* readFile(char*, int);
int getN(char*);
int* bruteForce(int, int, float*);

int main(int argc, char* argv[]) {

  int n;
  int k;
  float* sequence;

  if(argc != 4) {
    cout << "ERROR: Please execute this function using the form:\nprogram1 <inputfilename> <k> <-b|-d>\n";
    return 1;
  }

  n = getN(argv[1]);
  sequence = readFile(argv[1], n);
  k = atoi(argv[2]);

  cout << argv[1] << endl;
  cout << "n = " << n << ", k = " << k << endl;

  if(argv[3][1] == 'b' || argv[3][1] == 'B') {
    bruteForce(n, k, sequence);
  }



  return 0;
}

int* bruteForce(int n, int k, float* sequence) {

  int bigL = 0;
  int bigR = k;
  float bigAvg = 0;

  for(int i = 0; i < n - k; i++) {
    float avg = 0;
    for(int j = i; j < i + k; j++) {
      avg += sequence[j];
      cout << sequence[j] << endl;
    }
    avg = avg/k;
    if(avg > bigAvg) {
      bigL = i+1;
      bigR = i+k;
      bigAvg = avg;
    }
  }

  cout << "Big average: " << bigAvg << " at [" << bigL << "~" << bigR << "]\n";

}

int getN(char* fname) {

  int n = -1;
  ifstream in;
  in.open(fname);
  float temp;
  while(!in.eof()) {
      n++;
      in >> temp;
  }
  in.close();
  return n;

}

float* readFile(char* fname, int n) {

  ifstream in;
  in.open(fname);
  float* sequence = new float[n];

  in.close();

  return sequence;

}
