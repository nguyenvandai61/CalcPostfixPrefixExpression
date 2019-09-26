#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

#define MAX 200
struct Stack
{
	float DATA[MAX];
	int TOP;
};
void init(Stack *S)
{
	S->TOP = -1;
}
int isEmpty(Stack *S)
{
	if (S->TOP == -1)
		return 1;
	return 0;
}
void Push(struct Stack* S, float item)
{
	if (S->TOP == (MAX - 1))
	{
		printf("\nStack is full");
	}
	else
	{
		++S->TOP;
		S->DATA[S->TOP] = item;
	}
}
int top(Stack *S)
{
	return (S->DATA[S->TOP]);
}

float Pop(struct Stack* S)
{
	float ret = -1;
	if (S->TOP == -1)
		printf("\nStack is empty");
	else
	{
		ret = S->DATA[S->TOP];
		--S->TOP;
	}
	return ret;
}
int Precedence(char x)
{
	if (x == '(')
		return 0;
	if (x == '+' || x == '-')
		return 1 ;
	if (x == '*' || x == '/' || x == '%')
		return 2;

	return 3;
}


void InfixtoPostfix(char infix[], char postfix[])
{
	Stack S;
	char x, token;
	int i=0, j=0;    
	init(&S);
	
	// Duyet tat ca cac ky tu trong infix
	while(infix[i] != '\0')
	{
		token = infix[i]; // Luu ky tu
		if (isalnum(token)) { // Truong hop la so hoac chu
			postfix[j++] = token;
			if (!isdigit(infix[i+1]) && isdigit(infix[i])) {
				postfix[j++] = ' ';
			}
		}
		else
			// Truong hop dau ngoac
			if (token == '(')
				Push(&S, '(');
			else
				if (token == ')' && !isEmpty(&S)) {
					while ((x = Pop(&S)) != '(') { 
			 			postfix[j++] = x;
					 }
				}
				else // Truong hop phep tinh
				{
					while (!isEmpty(&S) && Precedence(token) < Precedence(top(&S)))
					{
						x = Pop(&S);
						postfix[j++] = x;
					}
					Push(&S, token);
				}
		i++;
	}

	while (!isEmpty(&S))
	{
		x = Pop(&S);
		postfix[j++] = x;
	}

	postfix[j] = '\0';
}
float Evaluate(char *Postfix)
{
	struct Stack S;
	char *p;
	float op1, op2, result;
	S.TOP = -1; 
	p = &Postfix[0];
	
	while (*p != '\0')
	{
		// Xet truong hop dau " "
		while (*p == ' ' || *p == '\t')
		{
			p++;
		}
		
		if (isalnum(*p)) {
			// Xet truong hop so
			if (isdigit(*p))
			{
				int num = 0;
				while(isdigit(*p)) {
					num*= 10;
					num+= *p - 48;
					p++;
				}
				p--;		
				cout << num << endl;
				Push(&S, num);
			}
			// Xet la chu
			else
			{
				Push(&S, *p);
			}
		}
		// xet la toan tu
		else
		{
			op1 = Pop(&S);
			op2 = Pop(&S);
			
			switch (*p)
			{
			case '+':
				result = op2 + op1;
				break;
			case '-':
				result = op2 - op1;
				break;
			case '/':
				result = op2 / op1;
				break;
			case '*':
				result = op2 * op1;
				break;
			default:
				printf("\nInvalid Operator");
				return 0;
			}
			Push(&S, result);
		}
		p++;
	}
	result = Pop(&S);
	return result;
}

float Evaluate2(char *Prefix)
{
	struct Stack S;
	char *p;
	float op1, op2, result;
	int prefixLength = strlen(Prefix);
	S.TOP = -1; 
	p = &Prefix[prefixLength-1];
	
	while (p >= &Prefix[0])
	{
		// Xet truong hop dau " "
		while (*p == ' ' || *p == '\t')
		{
			p--;
		}
		
		if (isalnum(*p)) {
			// Xet truong hop so
			if (isdigit(*p))
			{
				int num = *p - 48;
//				while(isdigit(*p)) {
//					num*= 10;
//					num+= *p - 48;
//					p--;
//				}
//				p++;		
				cout << num << endl;
				Push(&S, num);
			}
			// Xet la chu
			else
			{
				Push(&S, *p);
			}
		}
		// xet la toan tu
		else
		{
			op1 = Pop(&S);
			op2 = Pop(&S);
			
			switch (*p)
			{
			case '+':
				result = op1 + op2;
				break;
			case '-':
				result = op1 - op2;
				break;
			case '/':
				result = op1 / op2;
				break;
			case '*':
				result = op1 * op2;
				break;
			default:
				printf("\nInvalid Operator");
				return 0;
			}
			Push(&S, result);
		}
		p--;
	}
	result = Pop(&S);
	return result;
}




void InfixtoPrefix(char Infix[], char Prefix[]) {
	int infixLength = strlen(Infix);
	// Dao chuoi
	char temp;
	
	for(int i = 0; i <infixLength/2; i++) {
		temp = Infix[i];
		Infix[i] = Infix[infixLength-1-i];
		Infix[infixLength-1-i] = temp;
	}
	
	// Doi ngoac
	for(int i = 0; i < infixLength; i++)
		if (Infix[i] == '(')
			Infix[i] = ')'; 
		else if (Infix[i] == ')')
				Infix[i] = '(';
	cout << "infix reverse: " << Infix << endl;
	// Chuyen sang hau to
	InfixtoPostfix(Infix, Prefix);
	printf("%s\n", Prefix);
	
	// Dao nguoc lai
	int prefixLength = strlen(Prefix);
	for(int i = 0; i <prefixLength/2; i++) {
		temp = Prefix[i];
		Prefix[i] = Prefix[prefixLength-1-i];
		Prefix[prefixLength-1-i] = temp;
	}
}




int main()
{
	char A[MAX], B[MAX], C[MAX], D[MAX];
	printf("Infix : ");
	const char* word = "2+6*9-7+5"; //x
//	const char* word = "4+5*3-2";
//	const char* word = "2-3*5+4"; // x
//	const char* word = "(2+3)*(5+4)";
//	const char* word = "5*7-4*2*3";
//	const char* word = "(4+3)*2-5";
//	const char* word = "5+3*2-4+5";

	printf("%s\n", word);
	// Chuyen const char ve char array
    strncpy(A,word, MAX);
    
    
	InfixtoPrefix(A, B);
	printf("Chuoi Prefix: %s\n", B);
	printf("Equals is %f\n", Evaluate2(&B[0]));
	
	strncpy(C,word, MAX);
	InfixtoPostfix(C, D);
	printf("Postfix: %s\n", D);
	printf("Equals is %f\n", Evaluate(&D[0]));
	
	return 0;
}
