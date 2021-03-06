

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

ifstream in("input.txt");

enum class Functions
{
	invalid,
	abs,
	ceil,
	floor,
	trunc,
	round,
	exp,
	log,
	sqrt,
	cbrt,
	sin,
	cos,
	tan,
	asin,
	acos,
	atan,
	sinh,
	cosh,
	tanh,
	asinh,
	acosh,
	atanh,
	erf,
	erfc,
	tgamma
};

Functions resolveOption(string fnc)
{
	if (fnc == "abs")
		return Functions::abs;
	if (fnc == "sin")
		return Functions::sin;
	if (fnc == "cos")
		return Functions::cos;
	if (fnc == "tan")
		return Functions::tan;
	if (fnc == "sqrt")
		return Functions::sqrt;
	if (fnc == "log")
		return Functions::log;
	if (fnc == "exp")
		return Functions::exp;
	if (fnc == "ceil")
		return Functions::ceil;
	if (fnc == "floor")
		return Functions::floor;
	if (fnc == "trunc")
		return Functions::trunc;
	if (fnc == "round")
		return Functions::round;
	if (fnc == "cbrt")
		return Functions::cbrt;
	if (fnc == "asin")
		return Functions::asin;
	if (fnc == "acos")
		return Functions::acos;
	if (fnc == "atan")
		return Functions::atan;
	if (fnc == "sinh")
		return Functions::sinh;
	if (fnc == "cosh")
		return Functions::cosh;
	if (fnc == "tanh")
		return Functions::tanh;
	if (fnc == "asinh")
		return Functions::asinh;
	if (fnc == "acosh")
		return Functions::acosh;
	if (fnc == "atanh")
		return Functions::atanh;
	if (fnc == "erf")
		return Functions::erf;
	if (fnc == "erfc")
		return Functions::erfc;
	if (fnc == "tgamma")
		return Functions::tgamma;
	return Functions::invalid;
}

unsigned int findClosedPos(string str, unsigned int openPos)
{
	unsigned int count = 0;
	for (unsigned int i = openPos; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '(':
			{
				count++;
				break;
			}
		case ')':
			{
				count--;
				break;
			}

		default:
			break;
		}
		if (count == 0)
			return i;
	}
	return 0;
}

unsigned int findLeftBound(string str)
{
	unsigned int bound = str.find_last_not_of("-.0123456789x") + 1;
		if (bound < 0)
			bound = 0;
	return bound;
}

unsigned int findRightBound(string str)
{
	unsigned int bound = str.find_first_not_of("-.0123456789x") - 1;
	if (bound >= str.length())
		bound = str.length()-1;
	return bound;
}

string calcFunc(string expr, float param)
{
	unsigned int Pos = 0;
	while (expr.find('-', Pos) != string::npos) // turns a-b into a+-b
	{
		Pos = expr.find('-', Pos);
		if (Pos > 0)
			if (isdigit(expr[Pos - 1]) || expr[Pos - 1] == 'x' || expr[Pos - 1] ==')')
			{
				expr.insert(Pos, 1, '+');
			}
		Pos += 2;
	}
	while (expr.find('(') != string::npos) //handles parentheses
	{
		unsigned int openPos = expr.find('(');
		unsigned int closedPos = findClosedPos(expr, openPos);
		string replacement = calcFunc(expr.substr(openPos + 1, closedPos - openPos - 1),param);
		expr.replace(openPos, closedPos - openPos + 1, replacement);
	}
	while (expr.find_first_not_of("().^*/+-0123456789x") != string::npos) //Evaluates Functions
	{
		unsigned int start = expr.find_first_not_of("().^*/+-0123456789x");
		unsigned int end = expr.find_first_of("().^*/+-0123456789x",start);
		while (end < expr.length() - 2 && expr[end] == 'x' && string("().^*/+-0123456789x").find(expr[end + 1] == string::npos))
			end = expr.find_first_of("().^*/+-0123456789x", end);
		string function = expr.substr(start, end - start);
		unsigned int bound = findRightBound(expr.substr(end, expr.length() - end));
		string argument = expr.substr(end, bound + 1);
		string replacement = "";
		switch (resolveOption(function))
		{
		case Functions::abs:
		{
			replacement = to_string(abs(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::sin:
		{
			replacement = to_string(sin(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::cos:
		{
			replacement = to_string(cos(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::tan:
		{
			replacement = to_string(tan(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::sqrt:
		{
			replacement = to_string(sqrt(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::log:
		{
			replacement = to_string(log(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::exp:
		{
			replacement = to_string(exp(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::ceil:
		{
			replacement = to_string(ceil(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::floor:
		{
			replacement = to_string(floor(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::trunc:
		{
			replacement = to_string(trunc(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::round:
		{
			replacement = to_string(round(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::cbrt:
		{
			replacement = to_string(cbrt(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::asin:
		{
			replacement = to_string(asin(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::acos:
		{
			replacement = to_string(acos(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::atan:
		{
			replacement = to_string(atan(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::sinh:
		{
			replacement = to_string(sinh(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::cosh:
		{
			replacement = to_string(cosh(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::tanh:
		{
			replacement = to_string(tanh(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::asinh:
		{
			replacement = to_string(asinh(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::acosh:
		{
			replacement = to_string(acosh(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::atanh:
		{
			replacement = to_string(atanh(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::erf:
		{
			replacement = to_string(erf(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::erfc:
		{
			replacement = to_string(erfc(stof(calcFunc(argument, param))));
			break;
		}
		case Functions::tgamma:
		{
			replacement = to_string(tgamma(stof(calcFunc(argument, param))));
			break;
		}
		default:
			break;
		}
			 
		expr.replace(start, bound - start + 1, replacement);

	}
	while (expr.find('^') != string::npos) //handles power-raising
	{
		unsigned int opPos = expr.find('^');
		unsigned int lPos = findLeftBound(expr.substr(0, opPos));
		string left = expr.substr(lPos, opPos - lPos);
		unsigned int rPos = opPos + findRightBound(expr.substr(opPos + 1, expr.length() - opPos - 1)) + 1;
		string right = expr.substr(opPos + 1, rPos - opPos);
		string replacement = to_string(pow(stof(calcFunc(left, param)), stof(calcFunc(right, param))));
		expr.replace(lPos, rPos - lPos + 1, replacement);

	}
	while (expr.find_first_of("*/") != string::npos) //handles multiplication and division
	{
		unsigned int opPos = expr.find_first_of("*/");
		unsigned int lPos = findLeftBound(expr.substr(0, opPos));
		string left = expr.substr(lPos, opPos - lPos);
		unsigned int rPos = opPos + findRightBound(expr.substr(opPos + 1, expr.length() - opPos - 1)) + 1;
		string right = expr.substr(opPos + 1, rPos - opPos);
		switch (expr[opPos])
		{
		case '*':
		{
			string replacement = to_string(stof(calcFunc(left, param)) * stof(calcFunc(right, param)));
			expr.replace(lPos, rPos - lPos + 1, replacement);
			break;
		}
		case '/':
		{
			string replacement = to_string(stof(calcFunc(left, param)) / stof(calcFunc(right, param)));
			expr.replace(lPos, rPos - lPos + 1, replacement);
			break;
		}
		default:
			break;
		}
	}
	while (expr.find('+') != string::npos) //handles addition (and by extension subtraction)
	{
		unsigned int opPos = expr.find('+');
		unsigned int lPos = findLeftBound(expr.substr(0, opPos));
		string left = expr.substr(lPos, opPos - lPos);
		unsigned int rPos = opPos + findRightBound(expr.substr(opPos + 1, expr.length() - opPos - 1)) + 1;
		string right = expr.substr(opPos + 1, rPos - opPos);
		string replacement = to_string(stof(calcFunc(left, param)) + stof(calcFunc(right, param)));
		expr.replace(lPos, rPos - lPos + 1, replacement);
		
	}
	if (expr == "x") //handles the parameter
	{
		string replacement = to_string(param);
		expr = replacement;
	}
	return expr;
}

int main()
{
	string expr;
	float x;
	in >> expr >>x;
	cout << calcFunc(expr, x);

}


