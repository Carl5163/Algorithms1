#include <iostream>
#include <fstream>

using namespace std;

void readFile(char*, int, float*);
int getN(char*);
void bruteForce(int, int, float*);

int main(int argc, char* argv[]) {

  int n;
  int k;
  float* sequence;

  // Check to see if the appropriate number of arguments were passed.
  if(argc != 4) {
    cout << "\033[31mERROR:\033[0m Please execute this function using the form:\nprogram1 <inputfilename> <k> <-b|-d>\n";
    return 1;
  }

  // Check to see if the file exists and if so return the number of elements.
  n = getN(argv[1]);
  if(n == -1) {
    cout << "\033[31mERROR:\033[0m The file \033[33m" << argv[1] << "\033[0m not found." << endl;
    return 1;
  }

  // Read the file into an array.
  sequence = new float[n];
  readFile(argv[1], n, sequence);

  // Parse the subsequence length.
  k = atoi(argv[2]);

  // Print initial output.
  cout << argv[1] << endl;
  cout << "n = " << n << ", k = " << k << endl;

  // Finally perform the appropriate algorithm.
  if(argv[3][1] == 'b' || argv[3][1] == 'B') {
    bruteForce(n, k, sequence);
  } else if(argv[3][1] == 'd' || argv[3][1] == 'd') {

  }



  return 0;
}

void bruteForce(int n, int k, float* sequence) {

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

  cout << "Big average: " << bigAvg << " at [" << bigL << "~" << bigR << "]\n";

}

int getN(char* fname) {

  int n = -1;
  ifstream in;
  in.open(fname);
  if(in) {
    float temp;
    while(!in.eof()) {
        n++;
        in >> temp;
    }
  }
  in.close();
  return n;

}

void readFile(char* fname, int n, float* sequence) {

  ifstream in;
  in.open(fname);
  for(int i = 0; i < n; i++) {
    in >> sequence[i];
  }
  in.close();
}
