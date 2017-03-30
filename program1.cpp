#include <sys/time.h>
#include <iostream>
#include <fstream>

using namespace std;

float* readFile(char*, int&);
int bruteForce(int, int, float*);
int bruteForceCenter(int l, int r, int k, int n, float* sequence);
float average(int, int, int, float*);
int divAndConquer(int, int, int, int n, float*);

int main(int argc, char* argv[]) {


  struct timeval start, end;
  long mtime, seconds, useconds;

  int n;
  int k;
  float* sequence;

  // Check to see if the appropriate number of arguments were passed.
  if(argc != 4) {
    cout << "\033[31mERROR:\033[0m Please execute this function using the form:\nprogram1 <inputfilename> <k> <-b|-d>\n";
    return 1;
  }


  // Read the file into an array.
  sequence = readFile(argv[1], n);
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

  int ret;
  gettimeofday(&start, NULL);
  mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
  if(argv[3][1] == 'b' || argv[3][1] == 'B') {
    ret = bruteForce(n, k, sequence);
    cout << "Brute Force\n";
  } else if(argv[3][1] == 'd' || argv[3][1] == 'D') {
    ret = divAndConquer(0, n, k, n, sequence);
    cout << "Divide and Conquer\n";
  }

  gettimeofday(&end, NULL);

  seconds  = end.tv_sec  - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;

  mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

  cout << "Largest average: " << average(ret, ret+k, k, sequence) << " at [" << ret << "~" << ret+k-1 << "]\n";
  cout << "Algorithm took \033[32m~" << mtime << "ms\033[0m.\n";


  return 0;
}

// IN: l -> left index, r -> right index, k -> subarray length,
// n -> length of whole sequence, and sequence -> the sequence itself.
// OUT: Start index of the largest sub sequence of length k contained in these bounds.
int divAndConquer(int l, int r, int k, int n, float* sequence) {

  // Base cases. There are a different number of base cases depending on k.
  // If the subarray length is equal to k, just average the whole array and return.
  // If the subarray length is less than k, return 0 because there is no sequence worth averaging.
  if(r-l == k-1) {
    return l;
  }
  if(r-l < k-1) {
    return -1;
  }

  // Otherwise, recurse on left, right, and do a brute force check for the possible
  // sequences in the at the divide line.

  int leftI = divAndConquer(l, l+(r-l)/2, k, n, sequence);
  int rightI = divAndConquer(l+(r-l)/2+1, r, k, n, sequence);
  int centerI = bruteForceCenter(l+(r-l)/2-(k-2), l+(r-l)/2+(k-1), k, n, sequence);

  // This last part just picks the index that gives the larges sequence and returns it.
  int ret = leftI;

  if(average(ret, ret+k, k, sequence) < average(rightI, rightI+k, k, sequence)) {
    //cout << "Changing ret from " << ret << " to " << rightI << endl;
    ret = rightI;
  }
  if(average(ret, ret+k, k, sequence) < average(centerI, centerI+k, k, sequence)) {
    //cout << "Changing ret from " << ret << " to " << centerI << endl;
    ret = centerI;
  }
  return ret;

}

float average(int l, int r, int k, float* sequence) {

  if(l < 0 || r < 0) {
    return 0;
  }
  float sum = 0;
  for(int i = l; i < r; i++) {
    sum += sequence[i];
  }

  return sum/k;

}

int bruteForceCenter(int l, int r, int k, int n, float* sequence) {

  int bigL = max(l, 0);
  int bigR = min(l+k-1, n);

  float bigAvg = 0;

  for(int i = l; i < r - k + 1; i++) {
    float avg = 0;
    avg = average(i, i+k, k, sequence);
    if(avg >= bigAvg) {
      bigL = i;
      bigR = i+k-1;
      bigAvg = avg;
    }
  }

  return bigL;


}

int bruteForce(int n, int k, float* sequence) {

  int bigL = 0;
  int bigR = k-1;
  float bigAvg = 0;

  for(int i = 0; i < n - k + 1; i++) {
    float avg = 0;
    avg = average(i, i+k, k, sequence);
    if(avg >= bigAvg) {
      bigL = i;
      bigR = i+k-1;
      bigAvg = avg;
    }
  }

  return bigL;

}

float* readFile(char* fname, int &n) {
  float* sequence;
  n = -1;
  ifstream in;
  in.open(fname);
  if(in) {
    in >> n;
    sequence = new float[n];
    for(int i = 0; i < n; i++) {
      in >> sequence[i];
    }
  }
  in.close();
  return sequence;
}
