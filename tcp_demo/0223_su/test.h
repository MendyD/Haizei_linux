/*************************************************************************
	> File Name: test.h
	> Author: 
	> Mail: 
	> Created Time: Sat 23 Feb 2019 16:18:26 CST
 ************************************************************************/
#ifdef _DEBUG
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif
