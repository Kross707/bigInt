#pragma once
#include<string>
#include<sstream>

class bigInt
{
	std::string __number;
	long long int __size;
	bool __negative;

	std::string __custom__adder(std::string a, std::string b)
	{
		long long n1 = a.size();
		long long n2 = b.size();
		int carry = 0;

		std::string result = "";
		long long int i, j;
		for (i = n1 - 1, j = n2 - 1; i >= 0; i--, j--)
		{
			int temp = (a[i] - '0') + carry;
			if (j >= 0)
				temp += (b[j] - '0');

			carry = 0;
			if (temp > 9)
			{
				carry = 1;
				temp %= 10;
			}
			result += (temp + '0');
		}

		if (carry)
			result += carry + '0';
		return std::string(result.rbegin(), result.rend());
	}
	std::string __custom__subtracter(std::string a, std::string b)
	{
		long long n1 = a.size();
		long long n2 = b.size();
		int borrow = 0;

		std::string result = "";
		long long int i, j;
		for (i = n1 - 1, j = n2 - 1; i >= 0; i--, j--)
		{

			int temp = (a[i] - '0') - borrow;
			if (j >= 0)
				temp -= (b[j] - '0');

			borrow = 0;
			if (temp < 0)
			{
				borrow = 1;
				temp = 10 + temp;
			}
			result += (temp + '0');
		}

		return std::string(result.rbegin(), result.rend());
	}
	std::string __custom__multiply__by10(std::string a, int degree)
	{
		std::string result;
		while (degree--)
			result += '0';
		return a + result;
	}
	bigInt __custom__multiplication(std::string a, std::string b)
	{
		long long n1 = a.size();
		long long n2 = b.size();

		bigInt tempResult, finalResult;

		long long int i, j;
		for (j = n2 - 1; j >= 0; j--)
		{
			std::string result = "";
			int carry = 0;
			for (i = n1 - 1; i >= 0; i--)
			{
				int temp = (a[i] - '0') * (b[j] - '0') + carry;
				carry = 0;
				if (temp > 9)
				{
					carry = temp / 10;
					temp %= 10;
				}
				result += (temp + '0');
			}
			if (carry)
				result += (carry + '0');
			tempResult = bigInt(__custom__multiply__by10(std::string(result.rbegin(), result.rend()), n2 - 1 - j));
			finalResult = finalResult + tempResult;
		}
		return finalResult;
	}
	std::string __custom__single__division(std::string a, std::string b)
	{
		bigInt divisor(b), dividend(a);
		int count = -1;
		while (count < 10)
		{
			std::string hi;
			hi += ('0' + ++count);
			if (divisor > dividend - divisor * bigInt(hi))
				break;
		}
		std::string result;
		result += count + '0';
		return result;
	}
	/*
	std::string __custom__single__digit__modulo(std::string a, std::string b)
	{
		int dividend = std::stoll(a);
		int divisor = std::stoll(b);
		
		dividend% divisor;
	}
	*/
public:
	bigInt()
	{
		this->__number = "0";
		this->__size = 1;
		__negative = false;
	}
	bigInt(const char ch[])
	{
		int flag = 0;
		if (ch[0] == '-')
			__negative = true;
		else __negative = false;
		for (int i = 0; ch[i] != '\0'; i++)
		{
			if (ch[i] != '0' && ch[i] != '-')
				flag = 1;
			if (flag == 1)
				this->__number += ch[i];
		}
		if (flag == 0)
			this->__number += '0';
		this->__size = this->__number.size();
	}
	bigInt(std::string str)
	{
		int flag = 0;
		if (str[0] == '-')
			__negative = true;
		else __negative = false;
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (str[i] != '0' && str[i] != '-')
				flag = 1;
			if (flag == 1)
				this->__number += str[i];
		}
		if (flag == 0)
			this->__number += '0';
		this->__size = this->__number.size();
	}
	
	bool operator >(bigInt b)
	{
		if (this->size() == b.size())
		{
			for (long long int i = 0; i < this->size(); i++)
			{
				int temp = this->returnNumberAsString()[i] - b.returnNumberAsString()[i];
				if (temp > 0)
					return true;
				else if (temp < 0)
					return false;
			}
			return false;
		}
		else
		{
			if (this->size() - b.size() > 0)
				return true;
			else return false;
		}
	}
	bool operator <(bigInt b)
	{
		if (this->size() == b.size())
		{
			for (long long int i = 0; i < this->size(); i++)
			{
				int temp = this->returnNumberAsString()[i] - b.returnNumberAsString()[i];
				if (temp < 0)
					return true;
				else if (temp > 0)
					return false;
			}
			return false;
		}
		else
		{
			if (this->size() - b.size() < 0)
				return true;
			else return false;
		}
	}
	bool operator ==(bigInt b)
	{
		if (this->returnNumberAsString() == b.returnNumberAsString())
			return true;
		else return false;
	}

	bool isNegative()
	{
		return __negative;
	}

	void invertSign()
	{
		__negative = !__negative;
	}

	bigInt inverse()
	{
		bigInt inverted = *this;
		inverted.invertSign();
		return inverted;
	}

	bigInt operator +(bigInt b)
	{
		if ((this->isNegative() && b.isNegative()) || (!this->isNegative() && !b.isNegative()))
		{
			if (this->size() > b.size())
				return bigInt(__custom__adder(this->returnNumberAsString(), b.returnNumberAsString()));
			else
				return bigInt(__custom__adder(b.returnNumberAsString(), this->returnNumberAsString()));
		}
		else
		{
			if (this->isNegative())
				return b - this->inverse();
			else return *this - b.inverse();
		}
	}
	bigInt operator -(bigInt b)
	{
		if ((this->isNegative() && b.isNegative()))
		{
			if (*this > b)
				return bigInt(__custom__subtracter(this->returnNumberAsString(), b.returnNumberAsString())).inverse();
			else
				return bigInt(__custom__subtracter(b.returnNumberAsString(), this->returnNumberAsString()));
		}
		else if ((!this->isNegative() && !b.isNegative()))
		{
			if (*this > b)
				return bigInt(__custom__subtracter(this->returnNumberAsString(), b.returnNumberAsString()));
			else
				return bigInt(__custom__subtracter(b.returnNumberAsString(), this->returnNumberAsString())).inverse();
		}
		else
		{
			if (this->isNegative())
				return this->inverse() + b;
			else return *this + b.inverse();
		}
	}
	bigInt operator *(bigInt b)
	{
		if ((this->isNegative() && b.isNegative()) || (!this->isNegative() && !b.isNegative()))
			return bigInt(__custom__multiplication(this->returnNumberAsString(), b.returnNumberAsString()));
		else return bigInt(__custom__multiplication(this->returnNumberAsString(), b.returnNumberAsString())).inverse();
	}
	bigInt operator /(bigInt b)
	{
		if (b > * this)
		{
			return bigInt();
		}
		else
		{
			int flag = 0;
			if (b.isNegative())
			{
				b.invertSign();
				flag = 1;
			}

			bigInt result, remainder, temp2;
			std::string temp = "";
			for (long long i = 0; ;)
			{
				while (b > bigInt(temp) && i < this->size())
				{
					result = bigInt(result.returnNumberAsString() + '0');
					temp += this->returnNumberAsString()[i];
					i++;
				}
				temp2 = __custom__single__division(temp, b.returnNumberAsString());
				result = bigInt(result.returnNumberAsString() + temp2.returnNumberAsString());
				remainder = bigInt(temp) - temp2 * b;

				if (i >= this->size())
					break;

				temp = remainder.returnNumberAsString() + this->returnNumberAsString()[i++];
			}
			if ((this->isNegative() && flag == 1) || (!this->isNegative() && flag == 0) )
				return result;
			else return result.inverse();
		}
	}

	std::string returnNumberAsString()
	{
		return __number;
	}
	long long size()
	{
		return __size;
	}
};

std::ostream& operator<<(std::ostream& oo, bigInt obj)
{
	if (obj.isNegative())
		oo << "-";
	oo << obj.returnNumberAsString();
	return oo;
}
