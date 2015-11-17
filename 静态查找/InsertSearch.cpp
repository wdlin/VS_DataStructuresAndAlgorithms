
/*
��ֵ���ҷ�

��ʱ�临�Ӷ�����������Ҳ��o(n)�����Ƕ��ڱ��ϴ󣬶��ؼ��ֲַ��ֱȽϾ��ȵĲ��ұ���˵��
��ֵ�����㷨��ƽ�����ܱ��۰����Ҫ�õĶࡣ��֮������������ֲ��ǳ������ȣ�
��ô��ֵ����δ���Ǻܺ��ʵ�ѡ��
�㷨��ʹ���˳˳�������ô����������ȽϺã�ÿһ�ζ����ݵķ�����ͨ����ָ����ȣ����ö����൱����ġ����磬
�����ҵı�һ�����ڴ��̶����ڴ��У����ÿһ�αȽ϶�Ҫ���д��̷��ʡ�
*/

int insert_search(int* array, int size, int key)
{
	int pos, low, high;
	low = 0;
	high = size - 1;
	while (low <= high)
	{
		pos = ((key - array[low])*(high - low)) / (array[high] - array[low]) + low;
		if (array[pos] == key)
			return pos;
		if (array[pos] < key)
			low = pos + 1;
		else
			high = pos - 1;
	}
	return -1;
}