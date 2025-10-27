#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define MAX_SIZE 100

// Stack structure definitions
struct charStack {
    int top;
    char data[MAX_SIZE];
};

struct numStack {
    int top;
    double data[MAX_SIZE];
};

// Stack functions
void InitCharStack(charStack *s) {
    s->top = -1;
}

void InitNumStack(numStack *s) {
    s->top = -1;
}

bool IsCharStackEmpty(charStack *s) {
    return (s->top == -1);
}

bool IsNumStackEmpty(numStack *s) {
    return (s->top == -1);
}

bool PushCharStack(charStack *s, char x) {
    if (s->top == MAX_SIZE - 1) return false;
    s->top++;
    s->data[s->top] = x;
    return true;
}

bool PushNumStack(numStack *s, double x) {
    if (s->top == MAX_SIZE - 1) return false;
    s->top++;
    s->data[s->top] = x;
    return true;
}

bool PopCharStack(charStack *s, char &x) {
    if (s->top == -1) return false;
    x = s->data[s->top];
    s->top--;
    return true;
}

bool PopNumStack(numStack *s, double &x) {
    if (s->top == -1) return false;
    x = s->data[s->top];
    s->top--;
    return true;
}

char GetCharStackTop(charStack *s) {
    if (s->top == -1) return '\0';
    return s->data[s->top];
}

double GetNumStackTop(numStack *s) {
    if (s->top == -1) return 0;
    return s->data[s->top];
}

// Utility function to check operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;  // Exponentiation has higher precedence
    return 0;  // Invalid operator
}

// Function to perform arithmetic operations
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                cout << "Error: Division by zero!" << endl;
                exit(1);
            }
            return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Function to evaluate the expression
double evaluate(string expression) {
    charStack operators;
    numStack values;

    InitCharStack(&operators);
    InitNumStack(&values);

    for (int i = 0; i < expression.length(); i++) {
        char current = expression[i];

        // Skip whitespace
        if (current == ' ') continue;

        // If the character is a number, parse the whole number
        if (isdigit(current)) {
            double val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            PushNumStack(&values, val);
            i--;  // Adjust for the increment in the loop
        }
        // If the character is an opening parenthesis, push it to the stack
        else if (current == '(') {
            PushCharStack(&operators, current);
        }
        // If the character is a closing parenthesis, resolve the stack
        else if (current == ')') {
            while (!IsCharStackEmpty(&operators) && GetCharStackTop(&operators) != '(') {
                char op = GetCharStackTop(&operators);
                PopCharStack(&operators, op);

                double val2 = GetNumStackTop(&values);
                PopNumStack(&values, val2);

                double val1 = GetNumStackTop(&values);
                PopNumStack(&values, val1);

                double result = applyOperation(val1, val2, op);
                PushNumStack(&values, result);
            }
            PopCharStack(&operators, current); // Pop the '('
        }
        // If the character is an operator
        else if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') {
            while (!IsCharStackEmpty(&operators) && precedence(GetCharStackTop(&operators)) >= precedence(current)) {
                char op = GetCharStackTop(&operators);
                PopCharStack(&operators, op);

                double val2 = GetNumStackTop(&values);
                PopNumStack(&values, val2);

                double val1 = GetNumStackTop(&values);
                PopNumStack(&values, val1);

                double result = applyOperation(val1, val2, op);
                PushNumStack(&values, result);
            }
            PushCharStack(&operators, current);
        }
    }

    // Process the remaining operators in the stack
    while (!IsCharStackEmpty(&operators)) {
        char op = GetCharStackTop(&operators);
        PopCharStack(&operators, op);

        double val2 = GetNumStackTop(&values);
        PopNumStack(&values, val2);

        double val1 = GetNumStackTop(&values);
        PopNumStack(&values, val1);

        double result = applyOperation(val1, val2, op);
        PushNumStack(&values, result);
    }

    return GetNumStackTop(&values);
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);

    double result = evaluate(expression);
    cout << "Result: " << result << endl;
    return 0;
}
