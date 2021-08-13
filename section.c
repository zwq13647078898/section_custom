#include <unistd.h>
#include <stdio.h>

struct mydyh_desc {
	unsigned int	nr;
	const char		*name;
	unsigned long	price;

	void			(*fun)(unsigned long, const char *);
};

extern struct mydyh_desc __dyh_info_begin[], __dyh_info_end[];

#define for_each_dyh_desc(p)			\
	for (p = __dyh_info_begin; p < __dyh_info_end; p++)

#define SECTION_START(_type,_name)			\
static const struct mydyh_desc __mydyh_desc_##_type	\
	__attribute__((used, __section__(".dyh.info.init"))) = {	\
		.nr		= MY_DYH_##_type,		\
		.name	= _name,
		
#define SECTION_END						\
};

#define MY_DYH_PHONE	0
#define MY_DYH_CAR		1

void huawei_phone(unsigned long price, const char *name)
{
	printf("hello.\n");
	printf("name=%s, price=%ld\n", name, price);
	
	return;
}

void byd_phone(unsigned long price, const char *name)
{
	printf("world.\n");
	printf("name=%s, price=%ld\n", name, price);
	
	return;
}

SECTION_START(PHONE, "huawei")
	.price = 100,
	.fun = huawei_phone,
SECTION_END

SECTION_START(CAR, "byd")
	.price = 200,
	.fun = byd_phone,
SECTION_END

int main()
{
	struct mydyh_desc *p;
	
	for_each_dyh_desc(p) {
		p->fun(p->price, p->name);
	}
	
	return 0;
}