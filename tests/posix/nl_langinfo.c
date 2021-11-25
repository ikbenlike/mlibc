#include <string.h>
#include <assert.h>
#include <langinfo.h>

int main(void){
	char *a = NULL;

	a = nl_langinfo(CODESET);
	assert(a && !strcmp("UTF-8", a));

	a = nl_langinfo(D_T_FMT);
	assert(a && !strcmp("%a %b %e %H:%M:%S %Y", a));

	a = nl_langinfo(D_FMT);
	assert(a && !strcmp("%m/%d/%y", a));

	a = nl_langinfo(T_FMT);
	assert(a && !strcmp("%H:%M:%S", a));

	a = nl_langinfo(AM_STR);
	assert(a && !strcmp("AM", a));

	a = nl_langinfo(PM_STR);
	assert(a && !strcmp("PM", a));

	a = nl_langinfo(T_FMT_AMPM);
	assert(a && !strcmp("%I:%M:%S %p", a));

	a = nl_langinfo(ERA);
	assert(a && !strcmp("", a));

	a = nl_langinfo(ERA_D_T_FMT);
	assert(a && !strcmp("", a));

	a = nl_langinfo(ERA_D_FMT);
	assert(a && !strcmp("", a));

	a = nl_langinfo(ERA_T_FMT);
	assert(a && !strcmp("", a));

	a = nl_langinfo(DAY_1);
	assert(a && !strcmp("Sunday", a));

	a = nl_langinfo(DAY_2);
	assert(a && !strcmp("Monday", a));

	a = nl_langinfo(DAY_3);
	assert(a && !strcmp("Tuesday", a));

	a = nl_langinfo(DAY_4);
	assert(a && !strcmp("Wednesday", a));

	a = nl_langinfo(DAY_5);
	assert(a && !strcmp("Thursday", a));

	a = nl_langinfo(DAY_6);
	assert(a && !strcmp("Friday", a));

	a = nl_langinfo(DAY_7);
	assert(a && !strcmp("Saturday", a));

	a = nl_langinfo(ABDAY_1);
	assert(a && !strcmp("Sun", a));

	a = nl_langinfo(ABDAY_2);
	assert(a && !strcmp("Mon", a));

	a = nl_langinfo(ABDAY_3);
	assert(a && !strcmp("Tue", a));

	a = nl_langinfo(ABDAY_4);
	assert(a && !strcmp("Wed", a));

	a = nl_langinfo(ABDAY_5);
	assert(a && !strcmp("Thu", a));

	a = nl_langinfo(ABDAY_6);
	assert(a && !strcmp("Fri", a));

	a = nl_langinfo(ABDAY_7);
	assert(a && !strcmp("Sat", a));

	a = nl_langinfo(MON_1);
	assert(a && !strcmp("January", a));
	
	a = nl_langinfo(MON_2);
	assert(a && !strcmp("February", a));
	
	a = nl_langinfo(MON_3);
	assert(a && !strcmp("March", a));
	
	a = nl_langinfo(MON_4);
	assert(a && !strcmp("April", a));
	
	a = nl_langinfo(MON_5);
	assert(a && !strcmp("May", a));
	
	a = nl_langinfo(MON_6);
	assert(a && !strcmp("June", a));
	
	a = nl_langinfo(MON_7);
	assert(a && !strcmp("July", a));
	
	a = nl_langinfo(MON_8);
	assert(a && !strcmp("August", a));
	
	a = nl_langinfo(MON_9);
	assert(a && !strcmp("September", a));
	
	a = nl_langinfo(MON_10);
	assert(a && !strcmp("October", a));
	
	a = nl_langinfo(MON_11);
	assert(a && !strcmp("November", a));
	
	a = nl_langinfo(MON_12);
	assert(a && !strcmp("December", a));

	a = nl_langinfo(ABMON_1);
	assert(a && !strcmp("Jan", a));
	
	a = nl_langinfo(ABMON_2);
	assert(a && !strcmp("Feb", a));
	
	a = nl_langinfo(ABMON_3);
	assert(a && !strcmp("Mar", a));
	
	a = nl_langinfo(ABMON_4);
	assert(a && !strcmp("Apr", a));
	
	a = nl_langinfo(ABMON_5);
	assert(a && !strcmp("May", a));
	
	a = nl_langinfo(ABMON_6);
	assert(a && !strcmp("Jun", a));
	
	a = nl_langinfo(ABMON_7);
	assert(a && !strcmp("Jul", a));
	
	a = nl_langinfo(ABMON_8);
	assert(a && !strcmp("Aug", a));
	
	a = nl_langinfo(ABMON_9);
	assert(a && !strcmp("Sep", a));
	
	a = nl_langinfo(ABMON_10);
	assert(a && !strcmp("Oct", a));
	
	a = nl_langinfo(ABMON_11);
	assert(a && !strcmp("Nov", a));
	
	a = nl_langinfo(ABMON_12);
	assert(a && !strcmp("Dec", a));

	a = nl_langinfo(ALT_DIGITS);
	assert(a && !strcmp("", a));

	a = nl_langinfo(RADIXCHAR);
	assert(a && !strcmp(".", a));

	a = nl_langinfo(THOUSEP);
	assert(a && !strcmp("", a));

	a = nl_langinfo(YESEXPR);
	assert(a && !strcmp("^[yY]", a));

	a = nl_langinfo(NOEXPR);
	assert(a && !strcmp("^[nN]", a));

	a = nl_langinfo(CRNCYSTR);
	assert(a && !strcmp("", a));
}
