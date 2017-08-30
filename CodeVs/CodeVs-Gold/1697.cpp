#include <iostream>
#include <cstring>
#include <limits.h>
using namespace std;
#define MAX(x,y) x>y?x:y
#define MIN(x,y) x<y?x:y
struct Data
{
	char num[500];
	int bits;
};
Data largePlus(const Data num1, const Data num2);
Data largeMul(const Data num1, const int num2, int offset = 0);
Data largeMultiple(const Data num1, const Data num2);
int main()
{
	int n; cin >> n;
	Data *data = new Data[n];
	data[0].bits = 1;
	data[0].num[0] = '0';
	data[1].bits = 1;
	data[1].num[0] = '1';
	Data temp; int num;
	for (int i = 2; i < n; i++)
	{
		data[i] = largePlus(data[i - 1], data[i - 2]);
		num = i;
		temp.bits = 0;
		while (num != 0)
		{
			temp.num[temp.bits++] = '0' + num % 10;
			num /= 10;
		}
		data[i] = largeMultiple(data[i], temp);
	}
	for (int i = data[n - 1].bits - 1; i >= 0; i--)
		cout << data[n - 1].num[i];
	cout << endl;
	delete[] data;
	return 0;
}
Data largePlus(const Data num1, const Data num2)
{
	int bitsMAX = MAX(num1.bits, num2.bits);
	int bitsMIN = MIN(num1.bits, num2.bits);
	int carry = 0;
	Data result;
	for (int i = 0; i < bitsMIN; i++)
	{
		result.num[i] = num1.num[i] + num2.num[i] + carry - '0';
		if (result.num[i] > '9')
		{
			result.num[i] -= 10;
			carry = 1;
		}
		else carry = 0;
	}
	for (int i = bitsMIN; i < bitsMAX; i++)
	{
		if (num1.bits < num2.bits) result.num[i] = num2.num[i] + carry;
		else result.num[i] = num1.num[i] + carry;
		if (result.num[i] > '9')
		{
			result.num[i] -= 10;
			carry = 1;
		}
		else carry = 0;
	}
	if (carry == 1)
	{
		result.num[bitsMAX] = '1';
		result.bits = bitsMAX + 1;
	}
	else result.bits = bitsMAX;
	return result;
}
Data largeMul(const Data num1, const int num2, int offset)
{
	Data result;
	if (num2 == 0)
	{
		result.num[0] = '0'; result.bits = 1;
		return result;
	}
	int bits = num1.bits;
	int carry = 0;
	int temp;
	memset(result.num, '0', sizeof(char)*offset);
	for (int i = 0; i < bits; i++)
	{
		temp = (num1.num[i] - '0')*num2 + carry;
		result.num[i + offset] = (temp % 10) + '0';
		carry = temp / 10;
	}
	if (carry != 0)
	{
		result.num[bits + offset] = carry + '0';
		result.bits = bits + offset + 1;
	}
	else result.bits = bits + offset;
	return result;
}
Data largeMultiple(const Data num1, const Data num2)
{
	int bits = num2.bits;
	Data result;
	result.num[0] = '0'; result.bits = 1;
	Data temp;
	for (int i = 0; i < bits; i++)
	{
		temp = largeMul(num1, num2.num[i] - '0', i);
		result = largePlus(result, temp);
	}
	return result;
}