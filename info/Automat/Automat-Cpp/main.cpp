#include <iostream>
#include <string.h>

using namespace std;

int state;

void transfer(char chars) {
  switch (state) {
    case 0:
      switch (chars){
        case 'A':
          state++;               
          cout << "State: " << state << endl << "Char:  " << chars << endl;
          break;
        case 'B':
          state=state;
          cout << "State: " << state << endl << "Char:  " << chars << endl;
          break;
        case 'C':
          state=state;
          cout << "State: " << state << endl << "Char:  " << chars << endl;
          break;
        case 'D':
          state=state;
          cout << "State: " << state << endl << "Char:  " << chars << endl;
          break;
        case 'E':
          state=state;
          cout << "State: " << state << endl << "Char:  " << chars << endl;
          break;
      }
    break;

    case 1:
      switch (chars) {
        case 'A':
          state=state;
          cout << "State: " << state << endl << "Char:  " << chars << endl;
          break;
        case 'C':
          state++;
          cout << "State: " << state << endl << "Char:  " << chars << endl;
          break;
      }
    break;

    case 2:
      switch (chars) {
        case 'A':
          state++;      
          cout << "State: " << state << endl << "Char:  " << chars << endl;
          break;
        case 'B':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'C':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'D':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'E':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
      }
    break;

    case 3:
      switch (chars) {
        case 'A':
          state=1;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'B':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'C':
          state=2;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'D':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'E':
          state=4;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
      }
    break;

    case 4:
      switch (chars) {
        case 'A':
          state=5;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'B':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'C':
          state=2;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'D':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'E':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
      }
    break;

    case 5:
      switch (chars) {
        case 'A':
          state=1;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'B':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'C':
          state=2;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'D':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
        case 'E':
          state=0;
          cout << "State: " << state << endl << "Char:  " << chars << endl;  
          break;
      }
    break;
  }
}
void test(string string) {
  state=0;
  for(int i=0; i < string.size(); i++) {
    transfer(string[i]);
  }
  if(state==5){cout<<"String is \033[1;32mpossible\033[0;00m. State: " << state << endl;}
  else {cout<<"String is \033[1;31mnot possible\033[0;00m. State: " << state << endl;}
;}


int main(int argc, const char* argv[]) {
  string input = argv[1];
  cout << "Input string: " << input << endl;
  test(input);

  return 0;
}
