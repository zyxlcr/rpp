
namespace rf
{
	mac max(a,b) r_cond(a>b,a,b)
	mac min(a,b) r_cond(a>b,b,a)
	mac abs(a) r_cond(a<0,neg a,a)
		
	text(int r,int c,rstr s)
	{
		pos=r*80+c
		for i=0;i<s.count;i++
		{
			text(pos,s[i])
			pos++
		}
	}
	
	text(int pos,char ch)
	{
		text(pos,ch,0xa.tochar)
	}
	
	text(int pos,char ch,char col)
	{
		pos*=2
		pos+=0xb8000
		mov esi,pos
		mov1 [esi],ch
		pos++
		ch=col
		mov esi,pos
		mov1 [esi],ch
	}
	
	//未自动卷屏
	print(char* p)
	{
		text(0,0,p)
	}

	print_l(char* p,int len)
	{
		print(rstr(p,len).cstr)
	}
	
	//%d
	sprintf(char* dst,char* format,int n)
	{
		a=n.abs
		rstr s
		for
			s+=(a%10+`0).tochar
			a/=10
			if(a==0)
				break
		s.reverse
		if n<0
			s='-'+s
		strcpy(dst,s.cstr)
	}
	
	//%u
	sprintf(char* dst,char* format,uint n)
	{
		a=n
		rstr s
		for
			s+=(a%10+`0).tochar
			a/=10
			if(a==0)
				break
		s.reverse
		strcpy(dst,s.cstr)
	}
	
	//%I64d
	sprintf(char* dst,char* format,int8 n)
	{
		a=n.abs
		rstr s
		for
			s+=(a%10+`0).tochar
			a/=10
			if(a==0)
				break
		s.reverse
		if n<0
			s='-'+s
		strcpy(dst,s.cstr)
	}
	
	//todo
	//sprintf8(char* dst,char* format,double n)
	
	sscanf_int(char* src,char* format,void* n)
	{
		is_neg=*src==`-
		rstr s=src
		if is_neg
			s=s.sub 1
		s.reverse
		sum=0
		pro=1
		for i=0;i<s.count;i++
			sum+=pro*(s[i].toint-`0)
			pro*=10
		if is_neg
			sum=-sum
		*n.topint=sum
	}
	
	sscanf(char* src,char* format,void* n)
	{
		if(strcmp(format,"%d")==0)
			sscanf_int(src,format,n)
		else
			error("todo: unknow format")
	}
	
	init_heap()
	{
		memset(16777216p,0,(16*1024))
	}
	
	char* malloc(int size)
	{
		count=r_ceil_div(size+4,4096);
		char* start=16777216p
		for(p=start;p<start+(16*1024);p++)
		{
			ifn(*p==0&&p+count<=16793600p)
				continue
			for(q=p;q<p+count;q++)
				if(*q!=0)
					break
			ifn(q>=p+count)
				continue
			memset(p,1,count)
			k=4096*(p-start)+16793600
			*k.to<int*> =size
			k+=4
			return k.to<char*>
		}
		return null
	}
	
	mfree(char* p)
	{
		int size=*(p.to<int*>-1)
		pos=p.toint-4
		count=r_ceil_div(size+4,4096);
		pos=(pos-16793600)/4096+16777216
		memset(pos.to<char*>,0,count);
	}
	
	memcpy(char* dst,char* src,int size)
	{
		for i=0;i<size;i++ 
		{
			*dst=*src
			dst++
			src++
		}
	}

	memset(char* begin,int val,int size)
	{
		for i=0;i<size;i++ 
		{
			*begin=val.tochar
			begin++
		}
	}
	
	int strcmp(char* a,char* b)
	{
		for(!(*a).empty&&!(*b).empty)
		{
			if *a!=*b 
				return *a<*b
		}
		return *a<*b
	}

	int strlen(char* p)
	{
		sum=0
		for(;!(*p).empty;p++)
			sum++
		return sum
	}

	strcpy(char* dst,char* src)
	{
		for *src!=0
		{
			*dst=*src
			dst++
			src++
		}
		*dst=0
	}

	bool is_number(char ch)
	{
		int t=ch.toint
		return t>=`0&&t<=`9
	}
	
	exit(int a)
	{
		rn hlt
	}
	
	error(char* p="")
	{
		print p
		print "\nerror\n"
		rf.init_heap//这里调用是为了让init_heap参与编译
		exit(0)
	}
	
	print(rstr& s)
	{
		print_l s.begin,s.count
	}

	print(uint a)
	{
		print rstr(a).cstr
	}

	print(int a)
	{
		print rstr(a).cstr
	}
	
	print(int8 a)
	{
		print rstr(a).cstr
	}
	
	print(double a)
	{
		print rstr(a).cstr
	}

	printl(rstr& s)
	{
		print_l s.begin,s.count
		print "\n"
	}

	printl(char* p="")
	{
		print p
		print "\n"
	}

	printl(int a)
	{
		print a
		printl
	}

	printl(uint a)
	{
		print a
		printl
	}
	
	printl(int8 a)
	{
		print a
		printl
	}
	
	printl(double a)
	{
		print a
		printl
	}

	enum
	{
		c_call_js,
		c_cp_txt,
		c_find_meta,
		c_find_func,
		c_find_dll,
		c_stdcall_func,
		c_cdecl_func,
		c_get_vclass,

		c_thr_create,
		c_thr_wait,

		c_mu_init,
		c_mu_del,
		c_mu_enter,
		c_mu_leave,

		c_execmd,
		c_srand,
		c_rand,
		c_gettick,
		c_sleep,

		c_puts,
		c_puts_l,
		c_getch,
		c_getstdin,
		c_getstdout,
		c_get_argc,
		c_get_argv,

		c_sprintf,
		c_sprintf8,
		c_sscanf,

		c_malloc,
		c_mfree,
		c_memset,
		c_memcpy,
		
		c_strcpy,
		c_strcmp,
		c_strlen,
		
		c_fopen_w,
		c_fopen,
		c_fclose,
		c_fread,
		c_fwrite,
		c_fseek,
		c_fseek8,
		c_ftell,
		c_ftell8,

		c_s_socket,
		c_s_connect,
		c_s_close,
		c_s_send,
		c_s_recv,
		c_s_bind,
		c_s_listen,
		c_s_accept,
		
		c_gbk_to_utf8,
		c_gbk_to_utf16,
		c_utf8_to_gbk,
		c_utf8_to_utf16,
		c_utf16_to_gbk,
		c_utf16_to_utf8,
		
		c_CloseHandle,
		c_MessageBoxA,
		c_itof8,
	};
}