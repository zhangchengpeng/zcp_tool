#include "des.h"

//void AsciiToBcd(const char *str, unsigned char *hex, int count)
//{
//	int i;
//	for(i=0;i<count;i++)
//	{
//		hex[i] = ((str[i * 2] <= 0x39) ? str[i * 2] - 0x30 
//		    : str[i * 2] - 0x41 + 10);
//		hex[i] = hex[i] << 4;
//		hex[i] += ((str[i * 2 + 1] <= 0x39) ? str[i * 2 + 1] - 0x30
//		    : str[i * 2 + 1] - 0x41 + 10);
//	}
//}
//unsigned char ToHex(unsigned char c)
//{
//	unsigned char tmp1=c;
//	if(tmp1<=9 && tmp1>=0)
//		tmp1+='0';
//	else if(tmp1<=15 && tmp1>=10)
//		tmp1+='A'-10;
//	else
//		tmp1='0';
//	return tmp1;
//}
//unsigned char IsBmp1InBmp2(unsigned char * bmp1,unsigned char *bmp2,unsigned char len)
//{
//	unsigned char i,j,k,l;
//
//	for(i=0;i<len;i++)
//	{
//		if((*(bmp1+i))!=((*(bmp1+i))&(*(bmp2+i))))
//		{
//			j=(*(bmp1+i))^((*(bmp1+i))&(*(bmp2+i)));
//			k=0x80;
//			for(l=0;l<8;l++)
//			{
//				if((j&(k>>l))!=0)
//					return i*8+l+1;	
//				//BMP1有的位，在BMP2中无
//			}
//		}
//	}
//	return 0;
//	//BMP1中有的位，BMP2中全部有
//}
//void BcdToAscii(const char *hex, unsigned char *str, int count)
//{
//	int i;
//	unsigned char t;
//	for(i=0;i<count;i++)
//	{
//		t=(hex[i]&(0xf0));
//		t=t>>4;
//		str[2*i]=ToHex(t );
//		t=(hex[i]&(0x0f));
//		str[2*i+1]=ToHex(t);
//	}
//
//	unsigned char * tmp;
//	tmp=(unsigned char *)hex;
//
//	for(i=0;i<count;i++)
//	{
//		str[2*i]=((*(tmp+i))>>4);
//		str[2*i+1]=((*(tmp+i))&0x0f);
//	}
//}
CDes::CDes()
{
	byte _ip_table[]= 
	    {
		57, 49, 41, 33, 25, 17,  9, 1,
		    59, 51, 43, 35, 27, 19, 11, 3,
		    61, 53, 45, 37, 29, 21, 13, 5,
		    63, 55, 47, 39, 31, 23, 15, 7,
		    56, 48, 40, 32, 24, 16,  8, 0,
		    58, 50, 42, 34, 26, 18, 10, 2,
		    60, 52, 44, 36, 28, 20, 12, 4,
		    62, 54, 46, 38, 30, 22, 14, 6
	};
	memcpy(ip_table,_ip_table,sizeof(ip_table));

	byte _inv_ip_table[] = 
	    {
		39,  7, 47, 15, 55, 23, 63, 31,
		    38,  6, 46, 14, 54, 22, 62, 30,
		    37,  5, 45, 13, 53, 21, 61, 29,
		    36,  4, 44, 12, 52, 20, 60, 28,
		    35,  3, 43, 11, 51, 19, 59, 27,
		    34,  2, 42, 10, 50, 18, 58, 26,
		    33,  1, 41,  9, 49, 17, 57, 25,
		    32,  0, 40,  8, 48, 16, 56, 24
	};
	memcpy(inv_ip_table,_inv_ip_table,sizeof(inv_ip_table));

	byte _exp_table[] = 
	    {
		31,  0,  1,  2,  3,  4,
		    3,   4,  5,  6,  7,  8,
		    7,   8,  9, 10, 11, 12,
		    11, 12, 13, 14, 15, 16,
		    15, 16, 17, 18, 19, 20,
		    19, 20, 21, 22, 23, 24,
		    23, 24, 25, 26, 27, 28,
		    27, 28, 29, 30, 31,  0
	};
	memcpy(exp_table,_exp_table,sizeof(exp_table));

	byte _perm_table[] = 
	    {
		15,  6, 19, 20,
		    28, 11, 27, 16,
		    0, 14, 22, 25,
		    4, 17, 30,  9,
		    1,  7, 23, 13,
		    31, 26,  2,  8,
		    18, 12, 29,  5,
		    21, 10,  3, 24
	};
	memcpy(perm_table,_perm_table,sizeof(perm_table));


	byte _perm_choice1_C[] = 
	    {
		56, 48, 40, 32, 24, 16,  8,
		    0, 57, 49, 41, 33, 25, 17,
		    9,  1, 58, 50, 42, 34, 26,
		    18, 10,  2, 59, 51, 43, 35
	};
	memcpy(perm_choice1_C,_perm_choice1_C,sizeof(perm_choice1_C));

	byte _perm_choice1_D[] = 
	    {
		62, 54, 46, 38, 30, 22, 14,
		    6, 61, 53, 45, 37, 29, 21,
		    13,  5, 60, 52, 44, 36, 28,
		    20, 12,  4, 27, 19, 11,  3
	};
	memcpy(perm_choice1_D,_perm_choice1_D,sizeof(perm_choice1_D));

	byte _perm_choice2[] = 
	    {
		13, 16, 10, 23,  0,  4,
		    2, 27, 14,  5, 20,  9,
		    22, 18, 11,  3, 25,  7,
		    15,  6, 26, 19, 12,  1,
		    40, 51, 30, 36, 46, 54,
		    29, 39, 50, 44, 32, 47,
		    43, 48, 38, 55, 33, 52,
		    45, 41, 49, 35, 28, 31
	};
	memcpy(perm_choice2,_perm_choice2,sizeof(perm_choice2));

	byte _shifts_table[] =
	    {
		1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
	};
	memcpy(shifts_table,_shifts_table,sizeof(shifts_table));

	byte _sel_table[] = 
	    {
		/* s1 */
		14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		    0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
		    4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
		    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
		    /* s2 */
		15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
		    3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
		    0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
		    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
		    /* s3 */
		10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
		    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
		    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
		    1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
		    /* s4 */
		7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
		    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
		    10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
		    3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
		    /* s5 */
		2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
		    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
		    4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
		    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
		    /* s6 */
		12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
		    10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
		    9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
		    4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
		    /* s7 */
		4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
		    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
		    1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
		    6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
		    /* s8 */
		13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
		    1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
		    7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
		    2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
	};
	memcpy(sel_table,_sel_table,sizeof(sel_table));

	byte _bitmapx[] = 
	    {
		0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
		    0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
		    0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
		    0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
		    0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
		    0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
		    0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
		    0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
	};
	memcpy(bitmapx,_bitmapx,sizeof(bitmapx));


	//byte perm_keys[16][6];
	memset(perm_keys,0,sizeof(perm_keys));
	//byte key[8] /*= {0x012,0x34,0x45,0x67,0x89,0xab,0xcd,0xef}*/;
	memset(key,0,sizeof(key));
	//byte card_data[9] /*= {0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20,0}*/;
	memset(card_data,0,sizeof(card_data));
	//byte card_data1[9];
	memset(card_data1,0,sizeof(card_data1));
}

CDes::~CDes()
{

}

void CDes::do_ip(byte *input, byte *output, byte *table)
{
	byte i,j;

	for (i=0; i<8; i++)
		output[i] = 0;	/* clear output array area */

	for (i=0; i<64; i++)
	{
		j = table[i];
		if (input[j>>3] & bitmapx[j])
			output[i>>3] |= bitmapx[i]; /* set bit if needed */
	}
}

void CDes::function_rk(byte *input, byte *output, byte *key)
{

	byte temp[6];
	byte hold[4];
	register byte i;
	byte row, column;
	byte bits;

	for (i=0; i<6; i++) temp[i] = 0;                   /* clear temp array area */
	output[0] = output[1] = output[2] = output[3] = 0; /* clear output words */

	/* expand 32 bit input */
	for (i=0; i<48; i++){
		row = exp_table[i];
		if (input[row>>3] & bitmapx[row])
			temp[i>>3] |= bitmapx[i]; /* set bit if needed */
	}

	/* XOR expanded data with permuted key */
	for (i=0; i<6; i++) temp[i] ^= key[i];


	/* calc 'select functions' */
	hold[0] = hold[1] = hold[2] = hold[3] = 0;
	for (i=0; i<8; i++){
		row = 0;
		switch (i){
		case 0:
			if (temp[0] & 0x80) row = 2;
			if (temp[0] & 0x04) row++;
			column = (byte)((temp[0] & 0x78)>>3);
			break;

		case 1:
			if (temp[0] & 0x02) row = 2;
			if (temp[1] & 0x10) row++;
			column = (byte)((temp[1] & 0xe0) >> 5);
			if (temp[0] & 0x01) column += 8;
			break;

		case 2:
			if (temp[1] & 0x08) row = 2;
			if (temp[2] & 0x40) row++;
			column = (byte)((temp[1] & 0x07) << 1);
			if (temp[2] & 0x80) column++;
			break;

		case 3:
			if (temp[2] & 0x20) row = 2;
			if (temp[2] & 0x01) row++;
			column = (byte)((temp[2] & 0x1e) >> 1);
			break;

		case 4:
			if (temp[3] & 0x80) row = 2;
			if (temp[3] & 0x04) row++;
			column = (byte)((temp[3] & 0x78)>>3);
			break;

		case 5:
			if (temp[3] & 0x02) row = 2;
			if (temp[4] & 0x10) row++;
			column = (byte)((temp[4] & 0xe0) >> 5);
			if (temp[3] & 0x01) column += 8;
			break;

		case 6:
			if (temp[4] & 0x08) row = 2;
			if (temp[5] & 0x40) row++;
			column = (byte)((temp[4] & 0x07) << 1);
			if (temp[5] & 0x80) column++;
			break;

		case 7:
			if (temp[5] & 0x20) row = 2;
			if (temp[5] & 0x01) row++;
			column = (byte)((temp[5] & 0x1e) >> 1);
		}

		bits = sel_table[column + (i<<6) + (row<<4)]; /* s*64 + row*16 + column */

		if ((i & 0x01) == 0) bits <<= 4;
		hold[i >> 1] |= bits;
	}

	/* run permutation function on 32 bit output */
	for (i=0; i<32; i++){
		row = perm_table[i];
		if (hold[row>>3] & bitmapx[row])
			output[i>>3] |= bitmapx[i]; /* set bit if needed */
	}

}

void CDes::rotate(byte *ptr, byte times)
{
	byte bit,ntimes;

	ntimes = (byte)(8 - times);
	bit = (byte)((ptr[0] >> (ntimes-4)) & 0xf0); /* save LS Bit of lower word before shifting */
	ptr[0] <<= times;
	ptr[0] |= (ptr[1] >> ntimes);
	ptr[1] <<= times;
	ptr[1] |= (ptr[2] >> ntimes);
	ptr[2] <<= times;
	ptr[2] |= (ptr[3] >> ntimes);
	ptr[3] &= 0xf0;
	ptr[3] <<= times;
	ptr[3] |= bit;
}

void CDes::gen_keys()
{

	byte data,i, k;
	byte c_block[4], d_block[4];

	/* generate 28 bit blocks using 'Permuted Choice 1' */
	/* generate 'C' block */
	/* Ian you can use memset function here but I do not have the book here, so ...*/
	c_block[0] = c_block[1] = c_block[2] = c_block[3] = 0;
	for (i=0; i<28; i++) {
		k = perm_choice1_C[i];
		if (key[k>>3] & bitmapx[k])
			c_block[i>>3] |= bitmapx[i]; /* set bit if needed */
	}
	// printf("\nc_block:");
	// for (i=0;i<4;i++) printf("%02x",c_block[i]);
	/* generate 'D' block */
	d_block[0] = d_block[1] = d_block[2] = d_block[3] = 0;
	for (i=0; i<28; i++) {
		k = perm_choice1_D[i];
		if (key[k>>3] & bitmapx[k])
			d_block[i>>3] |= bitmapx[i]; /* set bit if needed */
	}
	// printf("\nd_block:");
	// for (i=0;i<4;i++) printf("%02x",d_block[i]);

	/* perform 'shifts' and generate 'Permuted Keys' */
	for (k=0; k<16; k++) {

		/* 'left shift' (rotate!) C block */
		rotate(c_block, shifts_table[k]);

		/* 'left shift' (rotate!) D block */
		rotate(d_block, shifts_table[k]);

		perm_keys[k][0] = perm_keys[k][1] =
		    perm_keys[k][2] = perm_keys[k][3] =
		    perm_keys[k][4] = perm_keys[k][5] = 0;

		/* run 'Permuted Choice 2' to generate 48 bit 'Permuted Key' */
		for (i=0; i<48; i++) {
			data = perm_choice2[i];
			if (data < 28) {	/* selected bit is in 'C' block */
				if (c_block[data>>3] & bitmapx[data])
					perm_keys[k][i>>3] |= bitmapx[i]; /* set bit if needed */
			} else {	/* selected bit is in 'D' block */
				data -= 28;
				if (d_block[data>>3] & bitmapx[data])
					perm_keys[k][i>>3] |= bitmapx[i]; /* set bit if needed */
			}
		}
	}

}

void CDes::cipher(byte *input, byte *output, byte mode)
{

	byte i;
	byte last[8], temp[4];

	/* perform 'Initial Permutation' */
	do_ip(input, last, ip_table);
	// printf("\nip:");
	// for (i=0;i<8;i++) printf("%02x",last[i]);

	/* Generate 'Preoutput' */
	for (i=0; i<16; i++) {

		if (mode) function_rk(&last[4], temp, perm_keys[15-i]);
		else function_rk(&last[4], temp, perm_keys[i]);

		/* XOR result with lower bits of last iteration */
		temp[0] ^= last[0];
		temp[1] ^= last[1];
		temp[2] ^= last[2];
		temp[3] ^= last[3];

		/* copy high 32 bits of previous iteration to low bits */
		last[0] = last[4];
		last[1] = last[5];
		last[2] = last[6];
		last[3] = last[7];

		/* copy result of XOR to high bits */
		last[4] = temp[0];
		last[5] = temp[1];
		last[6] = temp[2];
		last[7] = temp[3];
	}

	i       = last[4];
	last[4] = last[0];
	last[0] = i;
	i       = last[5];
	last[5] = last[1];
	last[1] = i;
	i       = last[6];
	last[6] = last[2];
	last[2] = i;
	i       = last[7];
	last[7] = last[3];
	last[3] = i;

	/* perform 'Inverse Initial Permutation' */
	do_ip(last, output, inv_ip_table);

}

void CDes::DeCode(byte *dg,byte *out,const byte *key_ptr)
{
	byte des_buf[8];
	memcpy(key,key_ptr,8);
	gen_keys();
	cipher(dg,des_buf,1);
	memcpy(out,des_buf,8);
}

void CDes::EnCode(byte *dg,byte *out,const byte *key_ptr)
{
	byte des_buf[8];
	memcpy(key,key_ptr,8);
	gen_keys();
	cipher(dg,des_buf,0);
	memcpy(out,des_buf,8);
}
