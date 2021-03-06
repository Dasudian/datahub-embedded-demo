#include "Ucos_ii.h"
#include "DatahubTimer.h"

// 时间是否过期
char expired(Timer* timer)
{
	unsigned int now = OSTimeGet();
	int res = timer->end - now;
	//printf("时间是否过期，expired:end(%d) - now(%d) = %d\r\n", timer->end, now, res);
	return res <= 0;
}

// 将定时器从当前时间往后加timeout毫秒
void countdown_ms(Timer* timer, unsigned int timeout)
{
	unsigned int now;
	unsigned int count = (timeout * OS_TICKS_PER_SEC) / 1000;
	if (count == 0) {
		count = 1;
	}
	now = OSTimeGet();
	timer->end = now + count;
	//printf("定时器往后加:countdown_ms:now=%d, count=%d, end=%d\r\n", now, count, timer->end);
}

// 将定时器从当前时间往后加timeout秒
void countdown(Timer* timer, unsigned int timeout)
{
	unsigned int count = timeout * OS_TICKS_PER_SEC;
	timer->end = OSTimeGet() + count;
	//printf("countdown:timer->end = %d\r\n", timer->end);
}

// 返回还有多少ms超时
int left_ms(Timer* timer)
{
	unsigned int now = OSTimeGet();
	int res = timer->end - now;
	//printf("还有多少ms超时，left_ms:res = %d\r\n", res);
	return (res < 0) ? 0 : res * (1000 / OS_TICKS_PER_SEC);
}

void InitTimer(Timer* timer)
{
	timer->end = 0;
}
