/*************************************************************************
	> File Name: test.h
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  2/23 16:32:23 2019
 ************************************************************************/


#define _DEBUG_ 1
 
#if _DEBUG_
#define PR(...) printf(__VA_ARGS__)
#else
#define PR(...)
#endif

