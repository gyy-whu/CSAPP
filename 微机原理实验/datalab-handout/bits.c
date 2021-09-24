/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 ת����������0��Ȼ��ȡ�� 
 */
int bitAnd(int x, int y) {
	return ~(~x|~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 ��ȡ��n���ֽڣ�ֻҪ�������Ƶ��������8n��������ȡ�������ɣ�&0xFF���� 
 */
int getByte(int x, int n) {
	return  0xFF&(x>>(n<<3)); 
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 ֱ�ӵ��������������ƣ�����ֻҪ���������ƣ�x>>n��,�ٰ�ǰ����ܱ��1��nλ����Ϊ0�Ϳ�����.
 ֻҪ���&һ�������ɣ��������ǰnλΪ0������ȫΪ1���Ӷ�ʹ�ð�ǰnλ��1���0�����ı�������
 �Ƚ�1����31λ��ȡ�����ɵõ�0x7FFFFFFF������������n-1λ���ɣ���ϧ������-�ţ��Ǿ�������nλ��
 ������һλ���������һλ��0����1���ɣ�������������ȼ����ɵ�((~(1<<31)>>n)<<1)+1��
 ��Ȼn-1Ҳ����n+~0����ʾ  
 */
int logicalShift(int x, int n) {
	return (x>>n)&(((~(1<<31)>>n)<<1)+1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4 
 ������Ŀ�������ƣ�����ֻ��ʹ��8λ�����������Ƚ�һ��32λ�����ֳ�8�����֣�ÿһ����4λ��
 ����λ���ƣ��ֱ����˸�������ÿһ����1�ĸ����͡� Ȼ��ǰ4�ֽ��Ƶ��������4�ֽ���ӣ�����
 ֱ����ӣ���Ϊ4λ���ֵλ15����1������Ϊ8�����ᱬ����Ȼ�������ӾͲ����ˣ��п��ܻᱬ����
 ����һ�������ǻ���Ҫ���ĸ�������ӡ� ������ͨ����õ� m1=0x1111,m2=0x11111111
 ǰ��˵������4λ���ֻ�ܱ�ʾ15�����ǻ�һ�ַ�������4�����ֱ��2�����֣���ÿ��������8λ��ʾ��
 ͨ��m3=0x0f0f��ʹ������ӡ� 
 ���ֻҪ������������Ӽ��ɽ�����������Ҫע�����������������Լ�һϵ�еļ��㣬ǰ�漸����
 �ֵ����Ѿ����ң�������ֻҪ���λ���������&0x3F���ɣ�32Ϊ0x2F������ȡ7λ1����0x3F�� 

 */
int bitCount(int x) {
	int m1=0x11+(0x11<<8);
	int m2=m1+(m1<<16);
	int m3=0xF+(0xF<<8);
	int all=(x&m2)+(x>>1&m2)+(x>>2&m2)+(x>>3&m2);//��ӱ��8�����֣�ÿһ����4λ 
	all=all+(all>>16);//��ɳ�4������ 
	all=(all&m3)+((all>>4)&m3);	//���2������ 
	return (all+(all>>8))&0x3F;//���������������Ӳ�ȡ���λ���� 
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 ���������֮��������0����0�ͷ���1���������0 
 ����ֻҪ�ҳ�0������֮�����ɣ�����֪����ֻ��0��0x10000000�Ĳ�������������ֻ��0�Ĳ������Լ���λ���
 ���λΪ0����������1��0x10000000Ҳ��1�����Դ�Ϊ�ж��������ɡ����������31��0��Ϊ0xFFFFFFFF,��������
 0x00000000���ټ�1���������ж����� 
 */
int bang(int x) {
	return (((~x+0x1)|x)>>31)+0x1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 ûɶ��˵��0x80000000��С 
 */
int tmin(void) {
	return 0x1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 �ж�x�ܷ���nλ�Ķ����Ʋ����ʾ����ҪҪ���ǵ���ʵ�Ƿ���λ�������Ǿ��Ȱ��������nλ���������ʾ��
 ����������32-nλ��������32-nλ�����������Ϳ��Ա�����nλ��������ȷ��nλʱ�����λ��Ӱ�졣����ԭ��
 ���бȽϣ��������ǾͿ��Ա�ʾ��������ǲ��ܱ�ʾ�� 
 */
int fitsBits(int x, int n) {
	int t=32+(~n+1) ;
	int y=(x<<t)>>t;
	
	return !(x^y);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 ��xΪ������ֱ������nλ���ɣ���xΪ��������Ҫһ��bias=2^n-1,���Ͻ����ģ�����׸����
 ����ص����Ҫ����һ������������ʱΪ0����ʱΪ2^n-1������ȡbias=x>>31&((1<<n)+~0) 
 ��ô��������ǣ�x+bias)>>n 
 */
int divpwr2(int x, int n) {
    return (x+(x>>31&((1<<n)+~0)))>>n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 �ܼ򵥣���λȡ���ټ�һ 
 */
int negate(int x) {
  return ~x+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 �ж��Ƿ����0������0������һλ�ض�Ϊ0����ȻҪ�ų����������0�����
 ������һ�㶼���������������������|�ж�Ϊ0��ȡ�� 
 */
int isPositive(int x) {
  return !((!x)|(x>>31));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 �������Ҫ�ж�xС�ڵ���y������1. �Ǿ���x-yС�ڵ���0��������y-x����0�ͷ���1�Ϳɡ�
 ��x��y�����xΪ��ʱ���Լ�x��yͬ����sxyΪ��ʱ��������������1 
 ������һ����Ҫע�⣬��y��x���ʱ������������ܻ���������Ե����жϷ��š�
 ��sxΪx�ķ���λ��syΪy�ķ���λ��syxΪy-x�ķ���λ��
 */
int isLessOrEqual(int x, int y) {
	int sx=(x>>31)&1;//x�ķ���λ��x��ʱ��sxΪ1 
	int sy=(y>>31)&1;//y�ķ���λ��y��ʱ��syΪ1
	int sxy=((y+~x+1)>>31)&1;//x-y�ķ���λ��x-yΪ��ʱ��x-yΪ1
	return ((sx^sy)&sx)|(!(sx^sy)&!sxy);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 �����Ƕ����Ʊ��룬���Է��ص�ֵ��ʵ����һ��32λ���е�һ��1��λ��-1,���Ϊ31 
 �����������ж����16λ����1����1�Ļ����ж��ұ�16λ����1�Ļ��Ͱ����Ƶ��ұߣ����ж��ұ�16λ��
 flag1�����ж����16��λ�ĸ����������1����flag1=16�������1����flag1=0�� 
 Ȼ�����ж����8λ������ͬ�ϡ� 
  
 */
int ilog2(int x) {
	int flag1,flag2,flag3,flag4,flag5; 
	flag1=(!(!(x>>16)))<<4; //���16λ������Ϊ1������Ϊ0����ͬ 
	x=x>>flag1;//flag1Ϊ1������16λ�Ƶ��ұ�16λ�������ƣ�����֮����1�ĵط�һ������16λ����ͬ 
	
	flag2=(!(!(x>>8)))<<3;//���8λ 
	x=x>>flag2;
	
	flag3=(!(!(x>>4)))<<2;//���4λ 
	x=x>>flag3;
	
	flag4=(!(!(x>>2)))<<1;//���2λ 
	x=x>>flag4;
	
	flag5=!(!(x>>1));//���һλ 
	
	return flag1+flag2+flag3+flag4+flag5;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 ��Ϊ�Ǹ������ĵ����ȱ�ʾ����ô-fҲ��ֻҪ����һλ�ķ��Ϳ����ˡ�
 ֮��ֻҪ�ٿ���һ��NaN���ɣ������NaN�Ļ�������ȫΪ1����β�벻Ϊ0 
 �Ȱѷ���λ���� ��Ȼ��������������||�� 
 (1<<23)-1ǡ���� 23��1 �� 
 	if((!(!(uf>>23)&0xff)&&(!(uf&((1<<23)-1))))
		fanuf=uf;	
	return fanuf;
�����������е㳬�� ������������ֱ�Ӿʹ��ں� 
*/
unsigned float_neg(unsigned uf) {
	unsigned  fanuf,nanm;
	fanuf=uf^0x80000000;//����λ ȡ�� 
	nanm=uf&0x7fffffff;//����λ����0�����಻�� 
	if(nanm>0x7f800000)//�ж��ǲ���NaN 
		fanuf=uf;	
	return fanuf;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 ����֪������������������ֻ�з���λ�����Ը�������ȡ-�󵱳���������
���ȣ�������ȷ������λs��
Ȼ��Ҫ�Ȱ�x�������λ����ȷ�������������ͱ���ȷ��С��frac���ֺ��油��0�ĸ�����
ͬʱҲ����ȷ������ 
 */
unsigned float_i2f(int x) {
	unsigned s=0;
	unsigned realx=x;
	unsigned cnt=0;
	unsigned t1,t2,jinwei;
	//0���뵥�����ۣ���Ϊ������ͨ��ѭ��ȷ����������ѭ�����ٴν��ж�0���жϣ�����ֱ���õ����浥���ж� 
	if(x==0)
		return 0;
	//С��0ʱ������λ��1������xȡ���������
	if(x<0) 
	{
		s=0x80000000;
		realx=-x;
	}
	t1=realx;
	while(1) 
	{
		t2=t1;
		t1=t1<<1;//ÿ������һλ 
		cnt+=1;//������1 
		//ֻ�е����λ��1��0x80000000�������ܳ�ѭ����ͨ���ƶ�������ȷ��x��λ��
		if(t2&0x80000000) 
			break; 
	}
	//���⻹Ҫ����������������⣬��Ϊint��4���ֽ���32λ����������ֻ��23λ���������ǲ�ȡ��ż������ 
	if ((t1 & 0x01ff)>0x0100)//��23λ֮���������0.5���ض���1 
        jinwei=1;
    else if ((t1 & 0x03ff)==0x0300)//��23λ֮�������0.5���ҵ�23λΪ1ʱ��Ҫ��һλ 
        jinwei=1;
    else//����ʱ�򲻽�λ 
        jinwei=0;
    //32-cnt����Ҫ�ƶ��Ĵ�����E����ôexp=E+bias=127+32-cnt��t1>>9����С������������frac 
	return s+((159-cnt)<<23)+(t1>>9)+jinwei;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
����ǹ�񻮵�������ôֻҪ�����Ľ���+1���ɡ�����Ƿǹ�񻯵�������ôֻҪ������β�����Ƽ��ɣ���ʹ�Ǻ�23λ
��Ϊ1Ҳû��ϵ����Ϊ����ǡ��ʹ�ý���+1����0-bias�����ʹ���������ֱ������û�����⣬�ǳ����
�����NaN���Ǿ�ֱ�ӷ��ؾ�ok�ˡ� 
 */
unsigned float_twice(unsigned uf) {
	if((uf&0x7f800000)==0) //�ǹ�񻰵���������ȫΪ0 
		uf=((uf&0x007fffff)<<1)+(uf&0x80000000);
	else if((uf&0x7f800000)!=0x7f800000) //��񻯵��������벻ȫΪ0�Ҳ���ȫ1�������������ƻ�Ҫ�ѷ���λ���� 
		uf=uf+0x800000;   
	return uf;
}
