#include <cstring>
#include "MatchMethods.h"

/*
最简单的匹配方法，匹配失败就在主串回溯后移动一位，继续匹配。
O(m*n)
*/

int simple_match(const char*text, const char * find)
{
	/*int text_len = strlen(text);
	int find_len = strlen(find);
	if (text_len < find_len)
		return -1;*/
	int i = 0, j = 0;

	while (text[i] != '\0'&& find[j] != '\0')
	{
		if (text[i] == find[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (find[j] == '\0')
		return i - j;
	else
		return -1;
}