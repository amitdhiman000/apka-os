#include <number.h>

#include <kconsol.h>


uint32_t ntobin(char* const out_buffer, uint32_t num);
uint32_t ntooct(char* const out_buffer, uint32_t num);
uint32_t ntodec(char* const out_buffer, uint32_t num);
uint32_t ntohex(char* const out_buffer, uint32_t num);

static char *reverse(char * const str, const size_t len)
{
	if (NULL != str && len > 1) {
        size_t left = 0;
        size_t right = len - 1;
		while (left < right) {
			char tmp = str[left];
			str[left] = str[right];
			str[right] = tmp;
            ++left;
			--right;
		}
	}
    return str;
}


/**
* Convert the number "num" into a string
*/
uint32_t ntos(char * const out_buffer, int32_t num, numbers_base_t base)
{
    uint32_t len = 0;
    uint32_t sign = 0;
    char *buffer = out_buffer;

    if (num < 0) {
        out_buffer[0] = '-';
        ++buffer;
        num = -num;
        sign = 1;
    }

    switch (base) {
        case BINARY:
        {
            len = ntobin(buffer, num);
            break;
        }
        case OCTAL:
        {
            len = ntooct(buffer, num);
            break;
        }
        case DECIMAL:
        {
            len = ntodec(buffer, num);
            break;
        }
        case HEXADECIMAL:
        {
            len = ntohex(buffer, num);
            break;
        }
        default:
        {
            break;
        }
    }

    len += sign;
    out_buffer[len] = '\0';

    return len;
}

/**
 * Convert from decimal to binary by saving in an integer array
 */
uint32_t ntobin(char* const out_buffer, uint32_t num)
{
    uint32_t i = 0;

    if (0 == num) {
		out_buffer[0] = '0';
		return 1;
	}

    do {
        out_buffer[i++] = (num & 0x1) + '0';
        num /= 2;
    } while (num > 0);

    reverse(out_buffer, i);
    return i;
}

/**
 * Convert a number into an octal string
 */
uint32_t ntooct(char * const out_buffer, uint32_t num)
{
    uint32_t i = 0;

    if (0 == num) {
		out_buffer[0] = '0';
		return 1;
	}

    while (num != 0) {
        out_buffer[i++] = num % 8 + '0'; 
        num = num / 8;
    }

    reverse(out_buffer, i);
    return i;
}

/**
 * Convert a number into an decimal string
 */
uint32_t ntodec(char * const out_buffer, uint32_t num)
{
    uint32_t i = 0;

    if (0 == num) {
		out_buffer[0] = '0';
		return 1;
	}

    while (num != 0) {
        out_buffer[i++] = num % 10 + '0';
        num = num / 10;
    }

	reverse(out_buffer, i);

    return i;
}


/**
 * Convert a number into an hexadecimal string
 */
uint32_t ntohex(char * const out_buffer, uint32_t num)
{    
    uint32_t i = 0;

    if (0 == num) {
		out_buffer[0] = '0';
		return 1;
	}

    while (num != 0)
    {
        // temporary variable to store remainder 
        int temp  = 0;
        temp = num % 16;           
        if (temp < 10)
        {
            out_buffer[i++] = temp + '0'; 
        }
        else
        {
            out_buffer[i++] = temp + 55; 
        }
        num = num / 16; 
    }

    reverse(out_buffer, i);

    return i;
}


#if 0
/**
 * Convert a number into an hexadecimal string
 */
void ntohex(char * const out_buffer, int32_t num)
{
  int a, ct, count;
  int four_bit[4];
  char str[5];
  char hex[255];
  int j = 0;
  char hexnum[17] = "0123456789abcdef";
  char *binnum[17];

  binnum[0] = "0000";
  binnum[1] = "0001";
  binnum[2] = "0010";
  binnum[3] = "0011";
  binnum[4] = "0100";
  binnum[5] = "0101";
  binnum[6] = "0110";
  binnum[7] = "0111";
  binnum[8] = "1000";
  binnum[9] = "1001";
  binnum[10] = "1010";
  binnum[11] = "1011";
  binnum[12] = "1100";
  binnum[13] = "1101";
  binnum[14] = "1110";
  binnum[15] = "1111";
  binnum[16] = '\0';


  decbin(num);
  binlen--;

 ciclo:
  for (a=0; a<4; a++)
    four_bit[a] = 0;

  /* ciclo per mettere i 4bit in single */
  for (ct=3; binlen>=0 && ct>=0; ct--, binlen--)
    four_bit[ct] = binvp[binlen];

  for (count=0; count<4; count++)
      str[count] = four_bit[count] + '0';
  str[4] = '\0';
  
  /* Fa il confronto
   * Te mi chiederai: ma la strcmp non ce l'abbiamo
   * beh io mi ricordo che nel vecchio dreamos c'era
   * al massimo la rifaccio, non è poi complicata ...
   */
  for (count=0; count<16; count++) {
    if (_kstrncmp (str, binnum[count], 4) == 0)
      hex[j++] = hexnum[count];
  }
    
  /* Se ancora non siamo arrivati alla fine
   * ripete tutto
   */  
  if (binlen>=0) { 
    goto ciclo;
  }
  
  /* Alla fine, hex contiene l'esadecimale, ma al contrario!
   * Indi rovesciamo tutto
   */
  int b;
  for (b=0, --j; j>=0; j--, b++)
    resulthex[b] = hex[j];
  resulthex [b] = '\0';
  // result contiene il risultato di tutte le fatiche :D
}
#endif