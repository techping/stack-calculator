#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define FORMULA_MAX_LEN 50/* the maximum length of formula to be supported */
#define PARENTHESES_MAX_NUM 10/* the maximum number of parentheses to be supported */

/* return operator's priority */
char operator_priority_hash(char operator)
{
	if (operator == '(')
		return -1;
	else if (operator == '+' || operator == '-')
		return 1;
	else if (operator == '*' || operator == '/')
		return 2;
	else if (operator == '^')
		return 3;
	else/* operator is not supported */
		return 0;
}

/* calculate the operand and the oprator in stack */
void calculate(stack operand_stack, stack operator_stack)
{
	int tmp = top(operand_stack);
	pop(operand_stack);
	switch (top(operator_stack)) {
		case '+': {
			tmp += top(operand_stack);
			break;
		}
		case '-': {
			tmp = top(operand_stack) - tmp;
			break;
		}
		case '*': {
			tmp *= top(operand_stack);
			break;
		}
		case '/': {
			tmp = top(operand_stack) / tmp;
			break;
		}
		case '^': {
			tmp = pow(top(operand_stack), tmp);
			break;
		}
		default: {
			break;
		}
	}
	pop(operand_stack);
	push(tmp, operand_stack);
	pop(operator_stack);
}

/* notice!!!: only support for calculation of single figures */
int main()
{
	char *formula_str = malloc(sizeof(char) * FORMULA_MAX_LEN);
	int sum = 0;/* store final result */
	stack operand_stack[PARENTHESES_MAX_NUM], operator_stack;
	for (int i = 0; i < PARENTHESES_MAX_NUM; i++)
		operand_stack[i] = create_stack();
	int i = 0;/* the index of operand stack */
	operator_stack = create_stack();
	scanf("%s", formula_str);
	printf("formula is: %s\n", formula_str);
	while (1) {
		if (!*formula_str) {/* formula is empty, then calculate the rest in stack */
			while (top(operator_stack))
				calculate(operand_stack[i], operator_stack);
			break;
		} else if (*formula_str >= '0' && *formula_str <= '9')/* handle operand */
			push(*formula_str - '0', operand_stack[i]);
		else {/* handle operator */
			if (*formula_str == '(') {/* handle '(' */
				i++;/* use next operand stack */
				push(*formula_str, operator_stack);
			} else if (*formula_str == ')') {/* handle ')' */
				while (top(operator_stack) && top(operator_stack) != '(')
					calculate(operand_stack[i], operator_stack);
				push(top(operand_stack[i]), operand_stack[i - 1]);
				pop(operand_stack[i--]);
				pop(operator_stack);/*remove '('*/
			} else {/* handle '+' '-' '*' '/' '^' */
				while (operator_priority_hash(*formula_str)/* the operator is supported */
					   && operator_priority_hash(*formula_str) <=/* the operator has a lower priority */
					   operator_priority_hash(top(operator_stack)))
					calculate(operand_stack[i], operator_stack);
				push(*formula_str, operator_stack);
			}
		}
		formula_str++;
	}
	sum = top(operand_stack[i]);
	pop(operand_stack[i]);
	printf("result is: %d\n", sum);
	return 0;
}
