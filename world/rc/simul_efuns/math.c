#define F_INFINITESIMAL (0.00005) // 默认浮点精度为5位
#undef FLOAT_PRECISION

// 函数：转换为非负数
int to_uint( int iNumber ) { return iNumber > 0 ? iNumber : 0; }

// 函数：转换为自然数
int to_nint( int iNumber ) { return iNumber > 0 ? iNumber : 1; }

// 函数：转换为绝对值
int abs( int iNumber ) { return iNumber < 0 ? - iNumber : iNumber; }
float fabs(float x) { return x<0 ? -x : x; }

/***************************************************************************
*	将总数量随机分配成N个组，结果放进一个数组中。
*	例如：整组开材料包，叠加总数量按五行随机分配为5组

*	数组中每个元素的值取得过程：
*	1.每个元素初始为随机生成的一个0-期望值（平均数）之间的数
*	2.每个元素加上剩下的 总数量/分组 （平均数）
*	3.余数随机加给数组中的元素
****************************************************************************/
int* rand_group_to_array( int amount, int iGroupNum )
{
	int iAverage;
	int iLeftDiv, iLeftMod;
	int *arrRet;
	int i;

	if( amount<=0 || iGroupNum <=0 )
	{
		return [];
	}

	arrRet = allocate( iGroupNum );
	iAverage = amount / iGroupNum;

	//1.先为每个分量随机分配一个值
	for( i=0; i<iGroupNum; i++ )
	{
		int iRandom = random(iAverage + 1);
		arrRet[i] = iRandom;
		amount -= iRandom;
	}
	iLeftDiv = amount / iGroupNum;		//商(平均数)
	iLeftMod = amount % iGroupNum;		//余数

	//2.每个元素加上剩下的 总数量/分组
	for( i=0; i<iGroupNum; i++ )
	{
		arrRet[i] += iLeftDiv;
	}

	//3.余数随机加给数组中的元素
	for( i=0; i<iLeftMod; i++ )
	{
		arrRet[random(iGroupNum)] += 1;
	}

	return arrRet;
}

int sum(int *nArray)
{
    return foldl(nArray, 0, add);
}

int max( int n1, int n2)
{
	return n1 >= n2? n1 : n2;
}

int min( int n1, int n2)
{
	return n1 >= n2? n2 : n1;
}

int round( float x )
{
	return to_int(x + 0.5);
}

#ifdef FLOAT_PRECISION
int ceil_to_int( float x, float infinitesmall )
{
	if (!infinitesmall) infinitesmall = F_INFINITESIMAL;

	if (x == 0) return 0;
	if (x > 0)
	{
		int iX = to_int(x);
		if (iX + infinitesmall >= x)
		{
			// 此时认为x精度不够，直接取整的值有效
			return iX;
		}
		else
		{
			return iX + 1;
		}
	}
	else
	{
		int iX = to_int(x);
		if (iX - 1 + infinitesmall >= x)
		{
			return iX - 1;
		}
		else
		{
			return iX;
		}
	}
}
#endif
