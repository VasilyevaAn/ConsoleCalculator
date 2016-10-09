#include <iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include <locale>

using namespace std;

bool is_operation (char c) {
	return c=='+' || c=='-' || c=='*' || c=='/' ;
}

bool is_unary_minus(char c){
    return c=='-';
}

int priority(char op) {
    switch (op) { 
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case ':':
            return 2;
        case '_':
            return 3;
    }
}

void process_op (vector<double> & num, char op) {
    if(op=='_'){
        double l = num.back();
        num.pop_back();
        num.push_back (-l);
    }
    else{
        double r = num.back();
        num.pop_back();
        double l = num.back();
        num.pop_back();
        switch (op) {
            case '+':  num.push_back (l + r);  break;
            case '-':  num.push_back (l - r);  break;
            case '*':  num.push_back (l * r);  break;
            case '/':  num.push_back (l / r);  break;
	}
	}
}

double calculate (string & s) {
	vector<double> num;
	vector<char> op;
	bool unary = true;
	for (size_t i=0; i<s.length(); ++i)
		if (!isspace (s[i]))
			if (s[i] == '('){
				op.push_back ('(');
				unary = true;
			}
			else if (s[i] == ')') {
				while (op.back() != '('){
					process_op (num, op.back());
                    op.pop_back();
				}
				op.pop_back();
				unary = false;
			}
			else if (is_operation (s[i])) {
			    if (unary&&is_unary_minus(s[i]))  s[i] = '_';
				while (!op.empty() && priority(op.back()) >= priority(s[i])){
					process_op (num, op.back());
                    op.pop_back();
				}
				op.push_back (s[i]);
				unary = true;
			}
			else {
				string operand;
				while (i < s.length() && !isspace (s[i])){
				    if(s[i]==',') s[i]='.';
					operand += s[i++];
				}
				--i;
				if (isdigit (operand[0]))
					num.push_back (atof (operand.c_str()));
				else
					cout<<"incorrectly input "<<operand;
					unary = false;
			}
	while (!op.empty()){
		process_op (num, op.back());
        op.pop_back();
	}
	return num.back();
}

int main()
{
    setlocale(LC_ALL,"Russian");
    string arithmetic="( 1 + 12,5 ) * 2";
    cout << calculate(arithmetic) << endl;

    arithmetic="( - 10 ) + 1 / 8 * 7";
    cout << calculate(arithmetic) << endl;

    arithmetic="sd + 1 / 8 * 7";
    cout << calculate(arithmetic) << endl;
    return 0;
}
