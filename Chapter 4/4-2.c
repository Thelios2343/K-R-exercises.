#include <ctype.h>
#include <stdio.h>

double atof(char s[]);


int main () {
    
    
    char nums [][20] = {
        "123.45",
        "123.45e-6",
        "1.2345E+3",
        "   -12.34e-2",
        "+0.001e4",
        "456e-3"
    };
    
    for (int i = 0; i < 6; i++) {
        printf("%2s -> %g\n", nums[i], atof(nums[i]));
    }

}


double atof(char s[])
{
    double val, power;
    int i, sign, exp_sign, exp;
    
    for (i = 0; isspace(s[i]); i++)
        ;
    
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    
    val = sign * val / power;
    
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        exp_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        
        
        for (exp = 0; isdigit(s[i]); i++)
            exp = 10 * exp + (s[i] - '0');
        
        
        if (exp_sign == 1) {
            while (exp-- > 0)
                val *= 10.0;
        } else {
            while (exp-- > 0)
                val /= 10.0;
        }
    }
    
    return val;
}
