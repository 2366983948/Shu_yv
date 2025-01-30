#include <iostream>

using namespace std;

/**
 * 计算两个整数的最大公约数（GCD）。
 * 
 * @param x 整数x。
 * @param y 整数y。
 * @return 返回x和y的最大公约数。
 */
int gcd(int x,int y){
    // 通过不断交换x和y的值，并将x对y取模，直到y为0，同时更新x为当前最大公约数
    while( y^=x^=y^=x%=y );
    return x;
}
 /**
 * 计算两个整数的最小公倍数（LCM）
 * @param x 整数x
 * @param y 整数y
 * @return 返回x和y的最小公倍数
 */
int lcm(int x, int y){
    // 通过x和y的最大公约数（gcd）计算它们的最小公倍数
    return x*y/gcd(x,y);
}

int main()
{   
    cout << "gcd(12,18) = " << gcd(12,18) << endl;
    cout << "lcm(12,18) = " << lcm(12,18) << endl;
    cout << "Hello world!" << endl;
    return 0;
}