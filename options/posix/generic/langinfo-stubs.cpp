
#include <langinfo.h>
#include <bits/ensure.h>
#include <mlibc/debug.hpp>
#include <mlibc/posix-locale.hpp>

namespace mlibc {

constinit const langinfo_locale posix_locale{
	.codeset = const_cast<char *>("UTF-8"),
	.d_t_fmt = const_cast<char *>("%a %b %e %H:%M:%S %Y"),
	.d_fmt = const_cast<char *>("%m/%d/%y"),
	.t_fmt = const_cast<char *>("%H:%M:%S"),
	.am_str = const_cast<char *>("AM"),
	.pm_str = const_cast<char *>("PM"),
	.t_fmt_ampm = const_cast<char *>("%I:%M:%S %p"),
	.era = const_cast<char *>(""),
	.era_d_t_fmt = const_cast<char *>(""),
	.era_d_fmt = const_cast<char *>(""),
	.era_t_fmt = const_cast<char *>(""),
	.days = {const_cast<char *>("Sunday"), const_cast<char *>("Monday"), const_cast<char *>("Tuesday"),
			 const_cast<char *>("Wednesday"), const_cast<char *>("Thursday"), const_cast<char *>("Friday"),
			 const_cast<char *>("Saturday")},
	.abdays = {const_cast<char *>("Sun"), const_cast<char *>("Mon"), const_cast<char *>("Tue"),
			   const_cast<char *>("Wed"), const_cast<char *>("Thu"), const_cast<char *>("Fri"),
			   const_cast<char *>("Sat")},
	.months = {const_cast<char *>("January"), const_cast<char *>("February"), const_cast<char *>("March"),
			   const_cast<char *>("April"), const_cast<char *>("May"), const_cast<char *>("June"),
			   const_cast<char *>("July"), const_cast<char *>("August"), const_cast<char *>("September"),
			   const_cast<char *>("October"), const_cast<char *>("November"), const_cast<char *>("December")},
	.abmonths = {const_cast<char *>("Jan"), const_cast<char *>("Feb"), const_cast<char *>("Mar"),
				 const_cast<char *>("Apr"), const_cast<char *>("May"), const_cast<char *>("Jun"),
				 const_cast<char *>("Jul"), const_cast<char *>("Aug"), const_cast<char *>("Sep"),
				 const_cast<char *>("Oct"), const_cast<char *>("Nov"), const_cast<char *>("Dec")},
	.alt_digits = const_cast<char *>(""),
	.radixchar = const_cast<char *>("."),
	.thousep = const_cast<char *>(""),
	.yesexpr = const_cast<char *>("^[yY]"),
	.noexpr = const_cast<char *>("^[nN]"),
	.crncystr = const_cast<char *>(""),
};

const langinfo_locale *global_locale;

int set_langinfo(int section, const char *locale){

}

void initLanginfo() {
	mlibc::global_locale = &mlibc::posix_locale;
}

} //namespace mlibc

char *nl_langinfo(nl_item item) {
	if(item >= ABDAY_1 && item <= ABDAY_7){
		return mlibc::global_locale->abdays[item - ABDAY_1];
	}
	else if(item >= DAY_1 && item <= DAY_7){
		return mlibc::global_locale->days[item - DAY_1];
	}
	else if(item >= ABMON_1 && item <= ABMON_12){
		return mlibc::global_locale->abmonths[item - ABMON_1];
	}
	else if(item >= MON_1 && item <= MON_12){
		return mlibc::global_locale->months[item - MON_1];
	}
	else {
		switch(item){
			case      AM_STR: return mlibc::global_locale->am_str;
			case      PM_STR: return mlibc::global_locale->pm_str;
			case     D_T_FMT: return mlibc::global_locale->d_t_fmt;
			case       D_FMT: return mlibc::global_locale->d_fmt;
			case       T_FMT: return mlibc::global_locale->t_fmt;
			case  T_FMT_AMPM: return mlibc::global_locale->t_fmt_ampm;
			case         ERA: return mlibc::global_locale->era;
			case   ERA_D_FMT: return mlibc::global_locale->era_d_fmt;
			case ERA_D_T_FMT: return mlibc::global_locale->era_d_t_fmt;
			case   ERA_T_FMT: return mlibc::global_locale->era_t_fmt;
			case     CODESET: return mlibc::global_locale->codeset;
			case    CRNCYSTR: return mlibc::global_locale->crncystr;
			case   RADIXCHAR: return mlibc::global_locale->radixchar;
			case     THOUSEP: return mlibc::global_locale->thousep;
			case     YESEXPR: return mlibc::global_locale->yesexpr;
			case      NOEXPR: return mlibc::global_locale->noexpr;
		}
	}

	return const_cast<char *>("");
}

/*char *nl_langinfo(nl_item item) {
	if(item == CODESET) {
		return const_cast<char *>("UTF-8");
	}else{
		mlibc::infoLogger() << "mlibc: nl_langinfo item "
				<< item << " is not implemented properly" << frg::endlog;
		return const_cast<char *>("");
	}
}*/

char *nl_langinfo_1(nl_item, locale_t) {
	__ensure(!"Not implemented");
	__builtin_unreachable();
}

