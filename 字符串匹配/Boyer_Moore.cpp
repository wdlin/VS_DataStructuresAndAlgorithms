#include "MatchMethods.h"


/*
在用于查找子字符串的算法当中，BM（Boyer-Moore）算法是目前相当有效又容易理解的一种，一般情况下，比KMP算法快3-5倍。

BM算法在移动模式串的时候是从左到右，而进行比较的时候是从右到左的。

常规的匹配算法移动模式串的时候是从左到右，而进行比较的时候也是是从左到右的，基本框架是：
*/

