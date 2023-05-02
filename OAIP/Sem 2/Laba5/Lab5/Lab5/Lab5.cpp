#include <iostream>
#include <stdio.h>
#include<stdlib.h>

using namespace std;

struct Stack {
    char info;

    Stack* next;
};

void Push(Stack** top, char _info)
{
    Stack* b = new Stack;
    b->info = _info;
    b->next = (*top);
    (*top) = b;
}

void Pop(Stack** top)
{
    Stack* temp;
    temp = *top;
    *top = (*top)->next;
    delete temp;
}


struct StackDouble {
    double info;

    StackDouble* next;
};

void PushDouble(StackDouble** top, double _info)
{
    StackDouble* b = new StackDouble;
    b->info = _info;
    b->next = (*top);
    (*top) = b;
}

void PopDouble(StackDouble** top)
{
    StackDouble* temp;
    temp = *top;
    *top = (*top)->next;
    delete temp;
}



int Priority(char _info) {
    switch (_info) {
    case '*': case '/':     return 3;
    case '-': case '+':     return 2;
    case '(':               return 1;
    }
    return 0;
}

bool isValidExpression(char* expression) {
    // Проверка на отсутствие оператора в начале выражения
    if (expression[0] == '+' || expression[0] == '-' || expression[0] == '*' || expression[0] == '/') {
        cout << "\nOperator cannot be at the beginning of an expression\n";
        return false;
    }

    // Проверка на пустой ввод
    if (expression[0] == '\0') {
        cout << "\nInput is empty\n";
        return false;
    }

    int i = 0;
    int bracket = 0;

    while (expression[i] != '\0') {
        //Проверка на ввод корректных значений
        if ((expression[i] < 'a' || expression[i] > 'z') &&
            expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' && expression[i] != '(' && expression[i] != ')') {
            return false;
        }

        //Проверка на отсутствие двух операндов подряд
        if ((expression[i] >= 'a' && expression[i] <= 'z') && (expression[i + 1] >= 'a' && expression[i + 1] <= 'z')) {
            cout << "\nOperand cannot be specified twice in a row\n";
            return false;
        }

        //Проверка на отсутствие двух операторов подряд
        if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') &&
            (expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' || expression[i + 1] == '/')) {
            cout << "\nOperator cannot be specified twice in a row\n";
            return false;
        }

        //Проверка на предшествие открывающей скобки оператора
        if ((expression[i] >= 'a' && expression[i] <= 'z') && (expression[i + 1] == '(')){
            cout << "\nAn operand cannot precede a parenthesis\n";
            return false;
        }

        //Проверка на отсутствие оператора после открывающейся скобки
        if (expression[i] == '(' && (expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' || expression[i + 1] == '/')) {
            cout << "\nAn operator cannot follow a parenthesis\n";
            return false;
        }

        
        if (i > 0) {
            //Проверка на наличие оператора после закрывающей скобки
            if ((expression[i] >= 'a' && expression[i] <= 'z') && (expression[i - 1] == ')')) {
                cout << "\nAn operand cannot follow a parenthesis\n";
                return false;
            }

            //Проверка на отсутствие оператора перед закрывающейся скобкой
            if (expression[i] == ')' && (expression[i - 1] == '+' || expression[i - 1] == '-' || expression[i - 1] == '*' || expression[i - 1] == '/')) {
                cout << "\nAn operator cannot precede a parenthesis\n";
                return false;
            }

            //Проверка на отсутствие открывающей и закрывающей скобки подряд 
            if (expression[i] == '(' && (expression[i + 1] == ')' || expression[i - 1] == ')')) {
                cout << "\nUnable to open/close and immediately close/open bracket\n";
                return false;
            }

        }

        if (expression[i] == '(') bracket++;
        if (expression[i] == ')') bracket--;

        //Проверка на выражения вида (a+b))+((c+d)
        if (bracket < 0) {
            cout << "\nUnexpected closing parenthesis\n";
            return false;
        } 
        i++;
    }

    //Проверка на несовпадение открывающих и закрывающих скобок
    if (bracket != 0) {
        cout << "\nExpression is missing an opening or closing parenthesis\n";
        return false;
    }
    // Проверка на отсутствие оператора в конце выражения
    if (expression[i - 1] == '+' || expression[i - 1] == '-' || expression[i - 1] == '*' || expression[i - 1] == '/') {
        cout << "\nOperator cannot be at the end of an expression\n";
        return false;
    }

    return true;
}

double numericRezult(double _values[26] , char rpn[101]) {
    double finalRezult = 0;
    StackDouble* operands = NULL;
    double number;

    for (int i = 0; i < strlen(rpn); i++) {
        if (rpn[i] >= 'a' && rpn[i] <= 'z') {
            number = _values[rpn[i] - 'a'];
            PushDouble(&operands, number);
        }
        else {
            double op1 = operands->info;
            PopDouble(&operands);
            double op2 = operands->info;
            PopDouble(&operands);

            switch (rpn[i]) {
            case '+': PushDouble(&operands, op2 + op1); break;
            case '-': PushDouble(&operands, op2 - op1); break;
            case '*': PushDouble(&operands, op2 * op1); break;
            case '/': PushDouble(&operands, op2 / op1); break;
            }
            
        }
    }
    finalRezult = round (operands->info * 1000) / 1000; //Округление до 3х знаков после запятой
    PopDouble(&operands);

    return finalRezult;
}

int main()
{
    cout << "Enter math expression (up to 100 characters) : ";
    char formula[101];
    gets_s(formula);
    if (isValidExpression(formula)) {
        char rpn[101];
        int pos = 0;
        Stack* operators = NULL;


        for (int i = 0; i < strlen(formula); i++) {
            if (formula[i] >= 'a' && formula[i] <= 'z') {
                rpn[pos] = formula[i];
                pos++;
            }
            else if (formula[i] == '(') {
                Push(&operators, formula[i]);
            }
            else if (formula[i] == ')') {
                while (operators->info != '(') {
                     rpn[pos] = operators->info;
                     pos++;
                     Pop(&operators);
                }
                if (operators->info == '(') {
                    Pop(&operators);
                }
            }
            else if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/') {
                if (operators == NULL || Priority(formula[i]) > Priority(operators->info)) {
                    Push(&operators, formula[i]);
                }
                else {
                    while (operators != NULL && Priority(formula[i]) <= Priority(operators->info)) {
                        rpn[pos] = operators->info;
                        pos++;
                        Pop(&operators);
                    }
                    Push(&operators, formula[i]);
                }
            }
        }

        while (operators != NULL) {
            rpn[pos] = operators->info;
            pos++;
            Pop(&operators);
        }
        rpn[pos] = '\0';

        int lenght = strlen(rpn);

        cout << "\nRezult RPN:\n";
        for (pos = 0; pos < lenght; pos++) {
            cout << rpn[pos] << " ";
        }
        
        cout << endl << endl;

        double values[26] = { 0 }; //память под каждую строчную букву
        bool flags[26] = { false };
        
        for (pos = 0; pos < lenght; pos ++) {
            if (rpn[pos] >= 'a' && rpn[pos] <= 'z') {
                if (!flags[rpn[pos] - 'a']) { //Проверка, вводилось ли значение для этой переменной раньше
                    cout << "Enter values for variable [" << rpn[pos] << "]: ";
                    cin >> values[rpn[pos] - 'a']; //записываем значение для каждой буквы под индексом a-0, c-2, d-3 ... z-25
                    flags[rpn[pos] - 'a'] = true;
                }
            }
        }

        cout <<"\nNumeric rezult of your expression: " << numericRezult(values, rpn);

        cout << endl;
    }
    else {
        cout << "Invalid expression";
    }
    return 0;
}
