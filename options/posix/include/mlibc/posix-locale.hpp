#ifndef MBLIC_POSIX_LOCALE
#define MBLIC_POSIX_LOCALE

namespace mlibc {



struct langinfo_locale {
	char *codeset; //LC_CTYPE

	char *d_t_fmt; //LC_TIME
	char *d_fmt;
	char *t_fmt;
	char *am_str;
	char *pm_str;
	char *t_fmt_ampm;
	char *era;
	char *era_d_t_fmt;
	char *era_d_fmt;
	char *era_t_fmt;
	char *days[7];
	char *abdays[7];
	char *months[12];
	char *abmonths[12];
	char *alt_digits;

	char *radixchar; //LC_NUMERIC
	char *thousep;

	char *yesexpr; //LC_MESSAGES
	char *noexpr;

	char *crncystr; //LC_MONETARY
};

void initLanginfo();

int set_langinfo(int section, const char *locale);

}

#endif
