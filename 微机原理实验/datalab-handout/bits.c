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
 转换成求两个0，然后取反 
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
 提取第n个字节，只要把它先移到最后（右移8n），再提取出来即可（&0xFF）。 
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
 直接的右移是算术右移，所以只要先算术右移（x>>n）,再把前面可能变成1的n位都改为0就可以了.
 只要最后&一个数即可，这个数的前n位为0，后面全为1，从而使得把前n位的1变成0而不改变后面的数
 先将1左移31位再取反即可得到0x7FFFFFFF，所以再右移n-1位即可，可惜不能用-号，那就先右移n位，
 再左移一位，并把最后一位的0补成1即可，考虑运算符优先级，可得((~(1<<31)>>n)<<1)+1。
 当然n-1也能用n+~0来表示  
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
 由于题目中有限制，我们只能使用8位的数，所以先将一个32位的数分成8个部分，每一部分4位，
 先逐位右移，分别计算八个部分中每一部分1的个数和。 然后将前4字节移到后面与后4字节相加（可以
 直接相加，因为4位最大值位15，而1最大个数为8，不会爆，当然如果再相加就不行了，有可能会爆），
 到这一步，我们还需要将四个部分相加。 首先运通过算得到 m1=0x1111,m2=0x11111111
 前面说过由于4位最大只能表示15，我们换一种方法来把4个部分变成2个部分，且每个部分用8位表示。
 通过m3=0x0f0f来使他们相加。 
 最后只要把两个部分相加即可解决。最后的最后还要注意由于是算术右移以及一系列的计算，前面几个部
 分的数已经错乱，而我们只要后八位，所以最后&0x3F即可（32为0x2F，所以取7位1，即0x3F） 

 */
int bitCount(int x) {
	int m1=0x11+(0x11<<8);
	int m2=m1+(m1<<16);
	int m3=0xF+(0xF<<8);
	int all=(x&m2)+(x>>1&m2)+(x>>2&m2)+(x>>3&m2);//相加变成8个部分，每一部分4位 
	all=all+(all>>16);//变成成4个部分 
	all=(all&m3)+((all>>4)&m3);	//变成2个部分 
	return (all+(all>>8))&0x3F;//最后两个部分再相加并取后八位即可 
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 此题的特殊之处就在于0，是0就返回1，否则就是0 
 所以只要找出0的特殊之处即可，我们知道，只有0和0x10000000的补码是它本身，而只有0的补码与自己按位或的
 最高位为0，其它都是1（0x10000000也是1）。以此为判断条件即可。将结果右移31，0则为0xFFFFFFFF,其它则是
 0x00000000，再加1即可满足判断条件 
 */
int bang(int x) {
	return (((~x+0x1)|x)>>31)+0x1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 没啥好说的0x80000000最小 
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
 判断x能否用n位的二进制补码表示，主要要考虑的其实是符号位，那我们就先把这个数用n位二进制码表示，
 所以先左移32-n位，再右移32-n位，这样操作就可以保留下n位，还可以确定n位时候符号位的影响。再与原数
 进行比较，如果相等那就可以表示，否则就是不能表示。 
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
 若x为正数，直接右移n位即可；若x为负数，需要一个bias=2^n-1,书上讲过的，不再赘述。
 因而重点就是要制造一个数，让他正时为0，负时为2^n-1。我们取bias=x>>31&((1<<n)+~0) 
 那么最后结果就是（x+bias)>>n 
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
 很简单，按位取反再加一 
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
 判断是否大于0，大于0的数第一位必定为0，当然要排除这个数就是0的情况
 这种题一般都是先让满足条件的情况用|判断为0再取反 
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
 这题就是要判断x小于等于y，返回1. 那就是x-y小于等于0，或者是y-x大于0就返回1就可。
 当x、y异号且x为负时，以及x、y同好且sxy为正时满足条件，返回1 
 但是有一点需要注意，当y跟x异号时，两者运算可能会溢出，所以得先判断符号。
 令sx为x的符号位，sy为y的符号位，syx为y-x的符号位。
 */
int isLessOrEqual(int x, int y) {
	int sx=(x>>31)&1;//x的符号位，x正时，sx为1 
	int sy=(y>>31)&1;//y的符号位，y正时，sy为1
	int sxy=((y+~x+1)>>31)&1;//x-y的符号位，x-y为正时，x-y为1
	return ((sx^sy)&sx)|(!(sx^sy)&!sxy);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 由于是二进制编码，所以返回的值其实就是一个32位数中第一个1的位置-1,最大为31 
 所以我们先判断左边16位有无1，无1的话就判断右边16位，有1的话就把它移到右边，仍判断右边16位。
 flag1就是判断左边16移位的个数，左边有1，则flag1=16，左边无1，则flag1=0； 
 然后再判断左边8位，过程同上。 
  
 */
int ilog2(int x) {
	int flag1,flag2,flag3,flag4,flag5; 
	flag1=(!(!(x>>16)))<<4; //左边16位，有则为1，无则为0，下同 
	x=x>>flag1;//flag1为1则把左边16位移到右边16位，否则不移，这样之后有1的地方一定在右16位，下同 
	
	flag2=(!(!(x>>8)))<<3;//左边8位 
	x=x>>flag2;
	
	flag3=(!(!(x>>4)))<<2;//左边4位 
	x=x>>flag3;
	
	flag4=(!(!(x>>2)))<<1;//左边2位 
	x=x>>flag4;
	
	flag5=!(!(x>>1));//最后一位 
	
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
 因为是浮点数的单精度表示，那么-f也就只要将第一位改反就可以了。
 之后只要再考虑一下NaN即可，如果是NaN的话，阶码全为1，且尾码不为0 
 先把符号位归零 ，然后两个条件，以||来 
 (1<<23)-1恰巧是 23个1 ， 
 	if((!(!(uf>>23)&0xff)&&(!(uf&((1<<23)-1))))
		fanuf=uf;	
	return fanuf;
不过符号数有点超了 ，换个方法，直接就大于号 
*/
unsigned float_neg(unsigned uf) {
	unsigned  fanuf,nanm;
	fanuf=uf^0x80000000;//符号位 取反 
	nanm=uf&0x7fffffff;//符号位都置0，其余不变 
	if(nanm>0x7f800000)//判断是不是NaN 
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
 我们知道负数和正数的区别只有符号位，所以负数可以取-后当成正数处理。
首先，我们先确定符号位s。
然后，要先把x的这个数位数给确定下来，这样就便于确定小数frac部分后面补的0的个数，
同时也可以确定阶码 
 */
unsigned float_i2f(int x) {
	unsigned s=0;
	unsigned realx=x;
	unsigned cnt=0;
	unsigned t1,t2,jinwei;
	//0必须单独讨论，因为他不好通过循环确定，与其在循环里再次进行对0的判断，不如直接拿到外面单独判断 
	if(x==0)
		return 0;
	//小于0时，符号位置1，并将x取负变成正数
	if(x<0) 
	{
		s=0x80000000;
		realx=-x;
	}
	t1=realx;
	while(1) 
	{
		t2=t1;
		t1=t1<<1;//每次左移一位 
		cnt+=1;//次数加1 
		//只有当最高位的1与0x80000000对齐后就能出循环，通过移动次数来确定x的位数
		if(t2&0x80000000) 
			break; 
	}
	//此外还要考虑四舍五入的问题，因为int是4个字节有32位，但单精度只有23位，并且我们采取向偶数舍入 
	if ((t1 & 0x01ff)>0x0100)//即23位之后的数大于0.5，必定进1 
        jinwei=1;
    else if ((t1 & 0x03ff)==0x0300)//即23位之后的数是0.5，且第23位为1时，要进一位 
        jinwei=1;
    else//其它时候不进位 
        jinwei=0;
    //32-cnt就是要移动的次数即E，那么exp=E+bias=127+32-cnt。t1>>9就是小数部分啦，即frac 
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
如果是规格划的数，那么只要将它的阶码+1即可。如果是非规格化的数，那么只要将它的尾数左移即可（即使是后23位
都为1也没关系，因为左移恰巧使得阶码+1，而0-bias的设计使得在这里的直接左移没有问题，非常巧妙）
如果是NaN，那就直接返回就ok了。 
 */
unsigned float_twice(unsigned uf) {
	if((uf&0x7f800000)==0) //非规格话的数，阶码全为0 
		uf=((uf&0x007fffff)<<1)+(uf&0x80000000);
	else if((uf&0x7f800000)!=0x7f800000) //规格化的数，阶码不全为0且不是全1，而且由于左移还要把符号位补上 
		uf=uf+0x800000;   
	return uf;
}
