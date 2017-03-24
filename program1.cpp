#include <iostream>
#include <fstream>

using namespace std;

int readFile(char*, float*);
float* bruteForce(int, int, float*);
float sum(int, int, float*);
float* divAndConquer(int, int, int, float*);

int main(int argc, char* argv[]) {

  int n;
  int k;
  float* sequence;

  // Check to see if the appropriate number of arguments were passed.
  if(argc != 4) {
    cout << "\033[31mERROR:\033[0m Please execute this function using the form:\nprogram1 <inputfilename> <k> <-b|-d>\n";
    return 1;
  }


  // Read the file into an array.
  sequence = new float[n];
  n = readFile(argv[1], sequence);
  if(n == -1) {
    cout << "\033[31mERROR:\033[0m The file \033[33m" << argv[1] << "\033[0m not found." << endl;
    return 1;
  }

  // Parse the subsequence length.
  k = atoi(argv[2]);

  // Print initial output.
  cout << argv[1] << endl;
  cout << "n = " << n << ", k = " << k << endl;


  // Finally perform the appropriate algorithm.

  float* ret;
  if(argv[3][1] == 'b' || argv[3][1] == 'B') {
    ret = bruteForce(n, k, sequence);
  } else if(argv[3][1] == 'd' || argv[3][1] == 'D') {
    //ret = divAndConquer(0, n, k, sequence);
  }



  cout << "Big average: " << ret[0] << " at [" << ret[1] << "~" << ret[2] << "]\n";


  return 0;
}

float* divAndConquer(int l, int r, int k, float* sequence) {
  if(r-l == k-1) {
    //return sum(l, r, sequence);
  }
  if(r-l < k-1) {
    //return 0;
  }
//  float* left =


}

float sum(int l, int r, float* sequence) {
  float sum = 0;
  for(int i = l; i < r; i++) {
    sum += sequence[i];
  }
  return sum;
}

float* bruteForce(int n, int k, float* sequence) {

  int bigL = 0;
  int bigR = k-1;
  float bigAvg = 0;

  for(int i = 0; i < n - k + 1; i++) {
    float avg = 0;
    for(int j = i; j < i + k; j++) {
      avg += sequence[j];
    }
    avg = avg/k;
    if(avg >= bigAvg) {
      bigL = i;
      bigR = i+k-1;
      bigAvg = avg;
    }
  }

  float ret[3];
  ret[0] = bigAvg;
  ret[1] = bigL;
  ret[2] = bigR;
  return ret;

}

int readFile(char* fname, float* sequence) {

  int n = -1;
    ifstream in;
    in.open(fname);
    if(in) {
      in >> n;
      for(int i = 0; i < n; i++) {
        in >> sequence[i];
      }
    }
  in.close();
  return n;
}
