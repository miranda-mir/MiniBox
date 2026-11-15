/*
 * ksh88.c - port/amalgamation of the sh/ sources
 * from pdksh-ms_4.5 (PD KSH v4.5, patchlevel 5; 1992-05-12).
 *
 * Original source notices and licensing terms are retained with their code.
 */

/* NAME:
 *      stdh.h - standard headers
 *
 * SYNOPSIS:
 *      #include "stdh.h"
 *
 * DESCRIPTION:
 *      We use this header to encapsulate all the stddef et al 
 *      inclusion so that most of the source can ignore the 
 *      problems that their lack might cause.
 *
 * SEE ALSO:
 *      
 *
 * AMENDED:
 *      91/11/25  13:33:12  (sjg)
 *
 * RELEASED:
 *      91/11/25  13:33:17  v1.3
 *
 * SCCSID:
 *      @(#)stdh.h  1.3  91/11/25  13:33:12  (sjg)
 *
 */

// For S_IFMT

#include <minibox.hxx>

#define _BSD_SOURCE

#ifndef ARGS
# ifdef __STDC__
#   define ARGS(args) args
# else
#   define ARGS(args) ()
#   ifdef VOID
#     define void VOID
#   endif
#   define const
#   define volatile
# endif
#endif

#include <stdio.h>
/* if we have std headers then include them here
 * otherwise make allowances
 */
#ifndef NOSTDHDRS
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
#else
# ifdef HAVE_SYS_STDTYPES
#   include <sys/stdtypes.h>
# else
#   include <sys/types.h>
/* just in case they have sys/stdtypes and don't know it
 */
#   ifndef	__sys_stdtypes_h
#define _PID_T
#define _CLOCK_T
typedef int pid_t;
typedef long clock_t;
#   endif
# endif
# ifdef _SYSV
#   include <string.h>
# else
#   include <strings.h>
#   define strchr index
#   define strrchr rindex
# endif
/* just a useful subset of what stdlib.h would have
 */
extern char * getenv  ARGS((const char *));
extern void * malloc  ARGS((size_t));
extern int    free    ARGS((void *));
extern int    exit    ARGS((int));

/* these _should_ match ANSI */
extern char * strstr  ARGS((const char *, const char *));
extern void * memmove ARGS((void *, const void *, size_t));
extern void * memcpy  ARGS((void *, const void *, size_t));
#endif /* NOSTDHDRS */
  

#ifndef offsetof
#define	offsetof(type,id) ((size_t)&((type*)NULL)->id)
#endif


#include <setjmp.h>

/*
 * Configuration file for the PD ksh
 *
 * RCSid: $Id: config.h,v 1.3 1992/05/03 08:28:59 sjg Exp $
 */

#ifndef	_CONFIG_H
#define	_CONFIG_H

/*
 * Builtin edit modes
 */

#define	EMACS				/* EMACS-like mode */
#define	VI				/* vi-like mode */
#define	JOBS				/* job control */

#ifndef SIGINT
#include <signal.h>
#endif

/*
 * leave USE_SIGACT defined.
 * if you don't have sigaction(2) and the
 * implementation in sigact.c doesn't work for your system,
 * fix it.
 * 
 * Of course if your system has a real sigaction() 
 * implementation that is faulty! undef JOBS and add USE_SIGNAL
 * or whatever does work.  You may find it necessary to undef
 * USE_SIGACT, if so please report it.
 */
#define USE_SIGACT			/* POSIX signal handling */
/* 
 * These control how sigact.c implements sigaction()
 * If you don't define any of them it will try and work it out 
 * for itself.  The are listed in order of preference (usefulness).
 */
/* #define USE_SIGMASK			/* BSD4.2 ? signal handling */
/* #define USE_SIGSET			/* BSD4.1 ? signal handling */
/* #define USE_SIGNAL			/* plain old signal(2) */

#if defined(JOBS) && (!defined(SIGCONT) || (defined(_SYSV) && defined(USE_SIGNAL)))
#undef JOBS
#endif

/* #define	FASCIST			/* Fascist getopts */
#define	SHARPBANG			/* Hack to handle #! */
/* #define	SILLY			/* Game of life in EMACS mode */
/* #define	SWTCH			/* Handle SWTCH for shl(1) */

#endif	/* _CONFIG_H */

#define Extern
/*
 * Public Domain Bourne/Korn shell
 */

/* $Id: sh.h,v 1.3 1992/04/25 08:29:52 sjg Exp $ */

/* begin inlined config.h */
/*
 * Configuration file for the PD ksh
 *
 * RCSid: $Id: config.h,v 1.3 1992/05/03 08:28:59 sjg Exp $
 */

#ifndef	_CONFIG_H
#define	_CONFIG_H

/*
 * Builtin edit modes
 */

#define	EMACS				/* EMACS-like mode */
#define	VI				/* vi-like mode */
#define	JOBS				/* job control */

#ifndef SIGINT
#include <signal.h>
#endif

/*
 * leave USE_SIGACT defined.
 * if you don't have sigaction(2) and the
 * implementation in sigact.c doesn't work for your system,
 * fix it.
 * 
 * Of course if your system has a real sigaction() 
 * implementation that is faulty! undef JOBS and add USE_SIGNAL
 * or whatever does work.  You may find it necessary to undef
 * USE_SIGACT, if so please report it.
 */
#define USE_SIGACT			/* POSIX signal handling */
/* 
 * These control how sigact.c implements sigaction()
 * If you don't define any of them it will try and work it out 
 * for itself.  The are listed in order of preference (usefulness).
 */
/* #define USE_SIGMASK			/* BSD4.2 ? signal handling */
/* #define USE_SIGSET			/* BSD4.1 ? signal handling */
/* #define USE_SIGNAL			/* plain old signal(2) */

#if defined(JOBS) && (!defined(SIGCONT) || (defined(_SYSV) && defined(USE_SIGNAL)))
#undef JOBS
#endif

/* #define	FASCIST			/* Fascist getopts */
#define	SHARPBANG			/* Hack to handle #! */
/* #define	SILLY			/* Game of life in EMACS mode */
/* #define	SWTCH			/* Handle SWTCH for shl(1) */

#endif	/* _CONFIG_H */
/* end inlined config.h */

/* allow for non-Unix linkers. main.c has a "#define Extern " */
#ifndef Extern
# define Extern	extern
#endif

#ifndef SHELL
#define	SHELL	"/bin/sh"	/* shell to exec scripts */
#endif

/* some people object to this use of __STDC__ */
#ifdef __STDC__
#define	ARGS(args)	args	/* prototype declaration */
#else
#define	ARGS(args)	()	/* K&R declaration */
#ifdef VOID
#define	void	VOID
#endif
#define	const	
#define	volatile 
#endif

#ifdef _ULTRIX			/* Ultrix 2.x gets dup2 wrong */
int dup2 ARGS ((int, int));
/* assumes we don't want dup2 return value */
#define	dup2(ofd, nfd) \
		(void) ((dup2)(ofd, nfd), fcntl(nfd, F_SETFD, 0))
#endif

#if defined(EMACS) || defined(VI)
#define	EDIT
#endif

typedef int bool_t;
#define	FALSE	0
#define	TRUE	1

#define	sizeofN(type, n) (sizeof(type) * (n))
#define	BIT(i)	(1<<(i))	/* define bit in flag */

#define	NUFILE	10		/* Number of user-accessible files */
#define	FDBASE	10		/* First file usable by Shell */

/* you're not going to run setuid shell scripts, are you? */
#define	eaccess(path, mode)	access(path, mode)

#define	MAGIC	(char)0x80	/* prefix for ~*?[ during expand */
#define	NOT	'!'	/* might use ^ */

#define	LINE	256		/* input line size */
#define	PATH	256		/* pathname size */

Extern	int	kshpid;		/* $$, shell pid */
Extern	int	exstat;		/* exit status */
Extern	int	async;		/* $!, last &'d pid */
Extern	volatile int sigchld_caught;	/* count of dead children */


/*
 * Area-based allocation built on malloc/free
 */

typedef struct Area {
	struct Block *free;	/* free list */
} Area;

extern	Area	aperm;		/* permanent object space */
#define	APERM	&aperm
#define	ATEMP	&e.area

/*
 * parsing & execution environment
 */
Extern	struct	env {
	int	type;			/* enviroment type - see below */
	Area	area;			/* temporary allocation area */
	struct	block *loc;		/* local variables and functions */
	short  *savefd;			/* original redirected fd's */
	struct	env *oenv;		/* link to previous enviroment */
	jmp_buf	jbuf;			/* long jump back to env creator */
	int	interactive;		/* fd's 0,1,2 are tty */
	struct temp *temps;		/* temp files */
} e;

#define	E_NONE	0		/* dummy enviroment */
#define	E_PARSE	1		/* parsing command # */
#define	E_EXEC	2		/* executing command tree */
#define	E_LOOP	3		/* executing for/while # */
#define	E_TCOM	5		/* executing simple command */
#define	E_FUNC	6		/* executing function */
#define	E_ERRH	7		/* general error handler # */
/* # indicates env has valid jbuf */

/*
 * flags
 */
#define	FEXPORT	FLAG('a')	/* -a: allexport */
#define	FERREXIT FLAG('e')	/* -e: errexit (quit on error) */
#define	FBGNICE	29		/* bgnice */
#define	FEMACS 30		/* emacs command editing */
#define	FIGNEOF	27		/* ignoreeof (eof does not exit) */
#define	FHASHALL FLAG('h')	/* -h: trackall, hashall */
#define	FTALKING FLAG('i')	/* -i: interactive (talking type wireless) */
#define	FKEYWORD FLAG('k')	/* -k: keyword (name=value anywhere) */
#define	FMARKDIRS 28		/* markdirs */
#define	FMONITOR FLAG('m')	/* -m: monitor */
#define	FNOEXEC	FLAG('n')	/* -n: noexec */
#define	FNOGLOB	FLAG('f')	/* -f: noglob */
#define	FPRIVILEGED FLAG('p')	/* -p: privileged */
#define	FSTDIN	FLAG('s')	/* -s (invocation): parse stdin */
#define	FNOUNSET FLAG('u')	/* -u: nounset (unset vars is error) */
#define	FVERBOSE FLAG('v')	/* -v: verbose (echo input) */
#define	FVI 31			/* vi command editing */
#define	FXTRACE	FLAG('x')	/* -x: (execute) xtrace */

#define	FLAG(c)	(1 + c - 'a')	/* map char to flags index */
#define	FLAGS	32
Extern	char flag [FLAGS];
int	option ARGS((const char *name));
char   *getoptions ARGS((void));
void	printoptions ARGS((void));

extern	char	null [];	/* null value for variable */

/*
 * other functions
 */
char * substitute ARGS((char const *, int));
char   *search();
struct tbl *findcom();
char   *strsave ARGS((char *, Area *));
char   *ulton ARGS((unsigned long n, int base));
int	xstrcmp();
void	qsortp ARGS((void **base, size_t n, int (*compare)(void *, void *)));
long	evaluate ARGS((const char *expr));
void	resetopts();
void	histsave();
void	histlist();

void	j_init ARGS((void));
void	j_exit ARGS((void));
void	j_notify ARGS((void));
void	j_kill ARGS((int job, int sig));
#ifdef JOBS
void	j_change ARGS((void));
int	j_resume ARGS((int job, int bg));
#endif

/*
 * error handling
 */
void	leave();	/* abort shell (or fail in subshell) */

/*
 * library functions
 */
typedef	void (*handler_t)();	/* signal handler */

/* temp/here files. the file is removed when the struct is freed */
struct	temp {
	struct	temp * next;
	char   *name;
};
struct temp *maketemp ARGS((Area *ap));

/*
 * stdio and our IO routines
 */

#ifdef	BUFSIZ			/* <stdio.h> included? */
extern	FILE *	shf [NUFILE];	/* map shell fd to FILE */
#endif
void	fopenshf();
void	flushshf();

#undef	stdin
#undef	stdout

#define	stdin	shf[0]		/* standard input */
#define	stdout	shf[1]		/* standard output */
#define	shlout	shf[2]		/* shell output */

int	shellf ARGS((const char *fmt, ...)); /* fprintf(shlout, ); */
int	errorf ARGS((const char *fmt, ...)); /* fprintf(shlout, ); error(); */

/*
 * IO control
 */
extern	int ttyfd;		/* tty fd (original fd 0) */

int	savefd ARGS((int fd));	/* save user fd */
void	restfd ARGS((int fd, int ofd));
void	openpipe ARGS((int [2]));
void	closepipe ARGS((int [2]));

/*
 * trap handlers
 */
typedef struct trap {
	int	signal;		/* signal number */
	char   *name;		/* short name */
	char   *mess;		/* descriptive name */
	char   *trap;		/* trap command */
	int	volatile set;	/* trap pending */
	int	ourtrap;	/* not ignored (?) */
	int	sig_dfl;	/* originally SIG_DFL */
} Trap;

#ifndef	SIGKILL
#include <signal.h>
#endif	/* SIGKILL */
#ifdef	NSIG
#define	SIGNALS	NSIG
#else
#ifdef	_MINIX
#define	SIGNALS	(_NSIG+1)	/* _NSIG is # of signals used, excluding 0. */
#else
#define	SIGNALS	32
#endif	/* _MINIX */
#endif	/* NSIG */

#ifdef USE_SIGACT			/* always use it? */
#ifndef  SA_NOCLDSTOP
/* begin inlined sigact.h */
/* NAME:
 *      sigact.h - sigaction et al
 *
 * SYNOPSIS:
 *      #include <signal.h>
 *      #ifndef  SA_NOCLDSTOP
 *      # include "sigact.h"
 *      #endif
 *
 * DESCRIPTION:
 *      This header is the interface to a fake sigaction(2) implementation.  
 *      Do NOT include this header unless your system does not 
 *      have a real sigaction(2) implementation.
 */
/*
 * $Log: sigact.h,v $
 * Revision 1.2  1992/04/24  15:04:11  sjg
 * now compiles with cc
 *
 * Revision 1.1  1992/04/24  12:01:38  sjg
 * Initial revision
 *
 */

#ifndef _SIGACT_H
#define _SIGACT_H

#ifndef ARGS
# if defined(__STDC__)
#   define ARGS(p) p
# else
#   define ARGS(p) ()
# endif
#endif
#ifndef __STDC__
# define volatile			/* can change without warning */
# define const				/* read only */
#endif

#ifndef SIGKILL
# include <signal.h>
#endif
#ifndef SA_NOCLDSTOP
/* sa_flags */
#define	SA_NOCLDSTOP	0x0001		/* don't send SIGCHLD on child stop */
#define SA_RESTART	0x0002		/* re-start I/O */

/* sigprocmask flags */
#define	SIG_BLOCK	0x0001
#define	SIG_UNBLOCK	0x0002
#define	SIG_SETMASK	0x0004

#ifndef __sys_stdtypes_h
typedef int sigset_t;
#endif

struct sigaction
{
  void		(*sa_handler)();
  sigset_t	sa_mask;
  int		sa_flags;
};


int	sigaction	ARGS(( int sig, struct sigaction *act, struct sigaction *oact ));
int	sigaddset	ARGS(( sigset_t *mask, int sig ));
int	sigdelset	ARGS(( sigset_t *mask, int sig ));
int	sigemptyset	ARGS(( sigset_t *mask ));
int	sigfillset	ARGS(( sigset_t *mask ));
int	sigismember	ARGS(( sigset_t *mask, int sig ));
int	sigpending	ARGS(( sigset_t *set ));
int	sigprocmask	ARGS(( int how, sigset_t *set, sigset_t *oldset ));
int	sigsuspend	ARGS(( sigset_t *mask ));

#ifndef sigmask
#define sigmask(m)	(1<<((m)-1))	/* convert SIGnum to mask */
#endif
#if !defined(NSIG) && defined(_NSIG)
# define NSIG _NSIG
#endif
#endif /* ! SA_NOCLDSTOP */
#endif /* _SIGACT_H */
/*
 * Local Variables:
 * version-control:t
 * comment-column:40
 * End:
 */
/* end inlined sigact.h */
#endif
Extern struct sigaction Sigact, Sigact_dfl, Sigact_ign, Sigact_trap;
#endif

Extern	int volatile trap;	/* traps pending? */
extern	Trap	sigtraps[SIGNALS];
Trap    *gettrap ARGS((char *)); /* search for struct trap by number or name */
void	trapsig ARGS((int sig)); /* trap signal handler */

/*
 * fast character classes
 */
#define	C_ALPHA	0x01		/* a-z_A-Z */
#define	C_DIGIT	0x02		/* 0-9 */
#define	C_LEX1	0x04		/* \0 \t\n|&;<>() */
#define	C_VAR1	0x08		/* *@#!$-? */
#define	C_SUBOP	0x40		/* "=-+?#%" */
#define	C_IFS	0x80		/* $IFS */

extern	char ctypes [];
#if 0
void	initctypes ARGS((void));
void	setctypes ARGS((const char*, int type));
#endif
#define	ctype(c, t)	!!(ctypes[(unsigned char)(c)]&(t))
#define	letter(c)	ctype(c, C_ALPHA)
#define	digit(c)	ctype(c, C_DIGIT)
#define	letnum(c)	ctype(c, C_ALPHA|C_DIGIT)

/* begin inlined table.h */
/* $Id: table.h,v 1.2 1992/04/25 08:33:28 sjg Exp $ */

/*
 * generic hashed associative table for commands and variables.
 */

struct table {
	Area   *areap;		/* area to allocate entries */
	int	size, free;	/* hash size (always 2^^n), free entries */
	struct	tbl **tbls;	/* hashed table items */
};

struct tbl {			/* table item */
	int	flag;		/* flags */
	int	type;		/* command type or base, see below */
	union {
		char *s;	/* string */
		long i;		/* integer */
		int (*f) ARGS ((char**)); /* int function */
		struct op *t;	/* "function" tree */
	} val;			/* value */
	char	name[4];	/* name -- variable length */
};

/* flag bits */
#define	ALLOC	BIT(0)		/* val.s has been allocated */
#define	DEFINED	BIT(1)		/* is defined in block */
#define	ISSET	BIT(2)		/* has value, vp->val.[si] */
#define	SPECIAL	BIT(3)		/* PATH, IFS, SECONDS, etc */
#define	INTEGER	BIT(4)		/* val.i contains integer value */
#define	RDONLY	BIT(8)		/* read-only variable */
#define	EXPORT	BIT(9)		/* exported variable */
#define	LOCAL	BIT(10)		/* for local typeset() */
#define	TRACE	BIT(11)		/* trace (-t) */
#define	FUNCT	BIT(12)		/* function */
#define	EXPALIAS BIT(13)	/* expanding this alias */

/* command types */
#define	CNONE	0		/* undefined */
#define	CSHELL	1		/* built-in */
#define	CFUNC	2		/* function */
#define	CEXEC	4		/* executable command */
#define	CALIAS	5		/* alias */
#define	CKEYWD	6		/* keyword */

void tinit ARGS((struct table *, Area *)); /* initialize table */
unsigned int hash();		/* name hash function */
struct tbl *tsearch();		/* table lookup primative */
struct tbl *tenter();		/* table lookup/enter primative */
void tdelete();			/* mark tbl entry for deletion */
void twalk();			/* initialize walk of table */
struct tbl *tnext();		/* walk table returning table time */
struct tbl **tsort();		/* sort table entries by name */

/*
 * activation record for function blocks
 */
struct block {
	Area	area;		/* area to allocate things */
	int	argc;		/* current $# */
	char **	argv;		/* current $* */
	struct	table vars;	/* local variables */
	struct	table funs;	/* local functions */
#if 1
	char *	error;		/* error handler */
	char *	exit;		/* exit handler */
#else
	struct	trap error, exit;
#endif
	struct	block *next;	/* enclosing block */
};

Extern	struct block globals;	/* global variables and functions */
Extern	struct table commands;	/* hashed commands */
Extern	struct table builtins;	/* built-in commands */
Extern	struct table lexicals;	/* keywords and aliases */
Extern	struct table homedirs;	/* homedir() cache */

struct builtin {
	char   *name;
	int  (*func)();
};

/* these really are externs! Look in table.c for them */

extern const struct builtin shbuiltins [], kshbuiltins [];

/* var spec values */
#define	V_NONE	0
#define	V_PATH	1
#define	V_IFS	2
#define	V_SECONDS 3
#define	V_OPTIND 4
#define	V_MAIL	5
#define	V_MAILPATH 6
#define	V_RANDOM 7

Extern	Area   *lastarea;	/* area of last variable/function looked up */
Extern	char   *path;		/* PATH value */
Extern	char   *prompt;		/* PS1 or PS2 */

void	newblock();
void	popblock();
struct tbl *global(/* char *s */);
struct tbl *local(/* char *s */);
struct tbl *typeset(/* char *var; int set, clr */);
struct tbl *setvar(/* struct tbl *vdst, *vsrc */);
struct tbl *strint(/* struct tbl *vdst, *vsrc */);
long	intval(/* struct tbl *vp */);
void	setint(/* struct tbl *vp; long n */);
char   *strval(/* struct tbl *vp */);
void	setstr(/* struct tbl *vp; char *s */);
void	unset(/* struct tbl *vp */);
int	import(/* char *s */);
char  **makenv();
int	isassign(/* char *s */);

/* end inlined table.h */
/* begin inlined tree.h */
/*
 * command trees for compile/execute
 */

/* $Id: tree.h,v 1.2 1992/04/25 08:33:28 sjg Exp $ */

#define	NOBLOCK	((struct op *)NULL)
#define	NOWORD	((char *)NULL)
#define	NOWORDS	((char **)NULL)

/*
 * Description of a command or an operation on commands.
 */
struct op {
	int	type;			/* operation type, see below */
	char  **args;			/* arguments to a command */
	char  **vars;			/* variable assignments */
	struct ioword	**ioact;	/* IO actions (eg, < > >>) */
	struct op *left, *right; 	/* descendents */
	char   *str;		/* identifier for case and for (use vars[0]) */
};

/* Tree.type values */
#define	TEOF	0
#define	TCOM	1		/* command */
#define	TPAREN	2		/* (c-list) */
#define	TPIPE	3		/* a | b */
#define	TLIST	4		/* a [&;] b */
#define	TOR	5		/* || */
#define	TAND	6		/* && */
#define	TFOR	7
#define	TCASE	9
#define	TIF	10
#define	TWHILE	11
#define	TUNTIL	12
#define	TELIF	13
#define	TPAT	14		/* pattern in case */
#define	TBRACE	15		/* {c-list} */
#define	TASYNC	16		/* c & */
#define	TFUNCT	17		/* function name { command; } */
#define	TTIME	18		/* time pipeline */
#define	TEXEC	19		/* fork/exec eval'd TCOM */

/*
 * prefix codes for words in command tree
 */
#define	EOS	0		/* end of string */
#define	CHAR	1		/* unquoted character */
#define	QCHAR	2		/* quoted character */
#define	COMSUB	3		/* $() substitution (0 terminated) */
#define	OQUOTE	4		/* opening " or ' */
#define	CQUOTE	5		/* closing " or ' */
#define	OSUBST	6		/* opening ${ substitution */
#define	CSUBST	7		/* closing } of above */

/*
 * IO redirection
 */
struct ioword {
	int	unit;	/* unit affected */
	int	flag;	/* action (below) */
	char   *name;	/* file name */
};

/* ioword.flag - type of redirection */
#define	IOTYPE	0xF		/* type: bits 0:3 */
#define	IOREAD	0x1		/* < */
#define	IOWRITE	0x2		/* > */
#define	IORDWR	0x3		/* <>: todo */
#define	IOHERE	0x4		/* << (here file) */
#define	IOCAT	0x5		/* >> */
#define	IODUP	0x6		/* <&/>& */
#define	IOEVAL	BIT(4)		/* expand in << */
#define	IOSKIP	BIT(5)		/* <<-, skip ^\t* */
#define	IOCLOB	BIT(6)		/* >!, override -o noclob */

/* values for E_LOOP longjmp */
#define	LBREAK	1
#define	LCONTIN	2

/* execute/exchild flags */
#define	XEXEC	BIT(0)		/* execute without forking */
#define	XFORK	BIT(5)		/* fork before executing */
#define	XBGND	BIT(1)		/* command & */
#define	XPIPEI	BIT(2)		/* input is pipe */
#define	XPIPEO	BIT(3)		/* output is pipe */
#define	XPIPE	(XPIPEI|XPIPEO)	/* member of pipe */
#define	XXCOM	BIT(4)		/* dup2 xcomfd to 1 */

/*
 * flags to control expansion of words
 */
#define	DOBLANK	BIT(1)		/* perform blank interpretation */
#define	DOGLOB	BIT(2)		/* expand [?* */
#define	DOPAT	BIT(3)		/* quote *?[ */
#define	DOTILDE	BIT(5)		/* expand ~ */

#if 0
/* job.c: job control primatives */
int	execute ARGS((struct op *, int flags));	/* execute tree */
int	exchild ARGS((struct op *, int flags));	/* execute tree as child */
int	waitfor ARGS((int job)); 		/* wait for job completion */
int	waitlast ARGS((void));			/* wait for last job */

/* eval.c: word expansion */
char  **eval ARGS((char **wv, int flag)); 	/* expand words */
char   *evalstr ARGS((char *wp, int flags));	/* expand word */
char   *substitute ARGS((const char *s, int flags)); /* compile and expand string */

/* tree.c: command trees */
void	ptree ARGS((struct op *t, FILE *f));	/* print tree */
char   *wdscan ARGS((char *wp, int c));		/* scan word for prefix */
char   *wdcopy ARGS((char *wp, Area *));	/* copy word */
struct op *tcopy ARGS((struct op *t, Area *));	/* copy tree */
void	tfree ARGS((struct op *t, Area *));	/* free tree */
#endif
/* end inlined tree.h */
/* begin inlined lex.h */
/*
 * Source input, lexer and parser
 */

/* $Id: lex.h,v 1.2 1992/04/25 08:33:28 sjg Exp $ */

#define	IDENT	64

typedef struct source Source;
struct source {
	char   *str;		/* input pointer */
	int	type;		/* input type */
	union {
		char  **strv;	/* string [] */
		FILE   *file;	/* file */
		struct tbl *tblp; /* alias */
	} u;
	int	line;		/* line number */
	char   *file;		/* input file name */
	int	echo;		/* echo input to shlout */
	Source *next;		/* stacked source */
};

/* Source.type values */
#define	SEOF	0		/* input EOF */
#define	STTY	1		/* terminal input */
#define	SFILE	2		/* file input */
#define	SSTRING	4		/* string */
#define	SWSTR	3		/* string without \n */
#define	SWORDS	5		/* string[] */
#define	SWORDSEP 8		/* string[] seperator */
#define	SALIAS	6		/* alias expansion */
#define	SHIST	7		/* history expansion */

Source *pushs ARGS((int stype)); 	/* push Source */
struct op *compile ARGS((Source *s));	/* compile tree */

/*
 * states while lexing word
 */
#define	SBASE	0		/* outside any lexical constructs */
#define	SWORD	6		/* implicit quoting for substitute() */
#define	SDPAREN	7		/* inside (( )), implicit quoting */
#define	SSQUOTE	1		/* inside '' */
#define	SDQUOTE	2		/* inside "" */
#define	SBRACE	3		/* inside ${} */
#define	SPAREN	4		/* inside $() */
#define	SBQUOTE	5		/* inside `` */

Extern	int	multiline;	/* \n changed to ; */

typedef union {
	int	i;
	char   *cp;
	char  **wp;
	struct op *o;
	struct ioword *iop;
} YYSTYPE;

#define	LWORD	256
#define	LOGAND	257
#define	LOGOR	258
#define	BREAK	259
#define	IF	260
#define	THEN	261
#define	ELSE	262
#define	ELIF	263
#define	FI	264
#define	CASE	265
#define	ESAC	266
#define	FOR	267
#define	WHILE	268
#define	UNTIL	269
#define	DO	270
#define	DONE	271
#define	IN	272
#define	FUNCTION 273
#define	TIME	274
#define	REDIR	275
#define	MPAREN	276		/* () */
#define	MDPAREN	277		/* (( )) */
#define	YYERRCODE 300

/* flags to yylex */
#define	CONTIN	BIT(0)		/* skip new lines to complete command */
#define	ONEWORD	BIT(1)		/* single word for substitute() */
#define	ALIAS	BIT(2)		/* recognize alias */
#define	KEYWORD	BIT(3)		/* recognize keywords */
#define	LETEXPR	BIT(4)		/* get expression inside (( )) */

#define	SYNTAXERR	zzerr()
#define	HERES	10		/* max << in line */

Extern	char	line [LINE+1];	/* input line */
Extern	Source *source;		/* yyparse/yylex source */
Extern	YYSTYPE	yylval;		/* result from yylex */
Extern	int	yynerrs;
Extern	struct ioword *heres [HERES], **herep;
Extern	char	ident [IDENT+1];

extern	int	yylex ARGS((int flags));
extern	void	yyerror ARGS((const char *msg));

#define	HISTORY	100		/* size of saved history */

extern	char   *history [HISTORY];	/* saved commands */
extern	char  **histptr;	/* last history item */
extern	int	histpush;	/* number of pushed fc commands */

extern	char	**histget();
extern  char	**histpos();
extern	int	histnum();
extern	char	*findhist();
extern	int	histN();

#ifdef EDIT

extern	void	x_init ARGS ((void));	/* setup tty modes */
extern	void	x_init_emacs ARGS ((void));
extern	void	x_emacs_keys ();
extern	void	x_bind();

extern	int	x_read ARGS ((int fd, char *buf, size_t len));
extern	int	x_emacs ARGS ((char *buf, size_t len));
extern	int	x_vi ARGS ((char *buf, size_t len));

extern	bool_t	x_mode ARGS ((bool_t));	/* set/clear cbreak mode */
extern	int	x_getc();		/* get tty char */
extern	void	x_flush(), x_putc(), x_puts(); /* put tty char */

extern	int	x_cols;		/* tty columns */

#endif
/* end inlined lex.h */
/* begin inlined proto.h */
/*
 * prototypes for PD-KSH
 * originally generated using "cproto.c 3.5 92/04/11 19:28:01 cthuang "
 * $Id: proto.h,v 1.1 1992/04/25 08:29:02 sjg Exp $
 */
#ifndef ARGS
#if defined(__STDC__) || defined(__cplusplus)
#define ARGS(s) s
#else
#define ARGS(s) ()
#endif
#endif

/* alloc.c */
Area *	ainit		 ARGS((Area *ap));
void 	afreeall	 ARGS((Area *ap));
void *	alloc		 ARGS((size_t size, Area *ap));
void *	aresize		 ARGS((void *ptr, size_t size, Area *ap));
void 	afree		 ARGS((void *ptr, Area *ap));
/* c_ksh.c */
int 	c_hash		 ARGS((char **wp));
int 	c_cd		 ARGS((char **wp));
int 	c_print		 ARGS((char **wp));
int 	c_whence	 ARGS((char **wp));
int 	c_typeset	 ARGS((char **wp));
int 	c_alias		 ARGS((char **wp));
int 	c_unalias	 ARGS((char **wp));
int 	c_let		 ARGS((char **wp));
int 	c_jobs		 ARGS((char **wp));
int 	c_fgbg		 ARGS((char **wp));
int 	c_kill		 ARGS((char **wp));
int 	c_bind		 ARGS((char **wp));
/* c_sh.c */
int 	c_label		 ARGS((char **wp));
int 	c_shift		 ARGS((char **wp));
int 	c_umask		 ARGS((char **wp));
int 	c_dot		 ARGS((char **wp));
int 	c_wait		 ARGS((char **wp));
int 	c_read		 ARGS((char **wp));
int 	c_eval		 ARGS((char **wp));
int 	c_trap		 ARGS((char **wp));
void 	setsig		 ARGS((struct trap *p, void (*f)()));
int 	c_return	 ARGS((char **wp));
int 	c_brkcont	 ARGS((char **wp));
int 	c_exit		 ARGS((char **wp));
int 	c_set		 ARGS((char **wp));
int 	c_unset		 ARGS((char **wp));
int 	c_ulimit	 ARGS((char **wp));
int 	c_times		 ARGS((char **wp));
int 	timex		 ARGS((struct op *t, int f));
int 	c_exec		 ARGS((char **wp));
int 	c_builtin	 ARGS((char **wp));
/* c_test.c */
int 	c_test		 ARGS((char **wp));
int 	oexpr		 ARGS((int n));
int 	aexpr		 ARGS((int n));
int 	nexpr		 ARGS((int n));
int 	primary		 ARGS((int n));
int 	filstat		 ARGS((char *nm, int mode));
int 	t_lex		 ARGS((char *s));
int 	newerf		 ARGS((char *f1, char *f2));
int 	olderf		 ARGS((char *f1, char *f2));
int 	equalf		 ARGS((char *f1, char *f2));
/* do_ulimit.c */
int 	do_ulimit	 ARGS((char *a1, char *a2));
/* edit.c */
int 	x_read		 ARGS((int fd, char *buf, size_t len));
int 	x_getc		 ARGS((void));
void 	x_flush		 ARGS((void));
void 	x_adjust	 ARGS((void));
void 	x_putc		 ARGS((int c));
void 	x_puts		 ARGS((char *s));
void 	x_init		 ARGS((void));
bool_t 	x_mode		 ARGS((bool_t onoff));
int 	promptlen	 ARGS((char *cp));
int 	init_editmode	 ARGS((void));
/* emacs.c */
int 	x_emacs		 ARGS((char *buf, size_t len));
void 	x_redraw	 ARGS((int limit));
void 	x_bind		 ARGS((char *a1, char *a2, int macro));
void 	x_init_emacs	 ARGS((void));
void 	x_emacs_keys	 ARGS((int erase, int kill, int werase, int intr, int quit));
char *	x_lastcp	 ARGS((void));
/* eval.c */
char *	substitute	 ARGS((char const *cp, int f));
char **	eval		 ARGS((char **ap, int f));
char *	evalstr		 ARGS((char *cp, int f));
/* exec.c */
int 	execute		 ARGS((struct op *t, volatile int flags));
int 	shcomexec	 ARGS((char **wp));
int 	define		 ARGS((char *name, struct op *t));
int 	builtin		 ARGS((char *name, int (*func)()));
struct tbl *	findcom	 ARGS((char *name, int insert));
int 	flushcom	 ARGS((int all));
char *	search		 ARGS((char *name, char *path, int mode));
/* expr.c */
void 	evalerr		 ARGS((char *err));
long 	evaluate	 ARGS((const char *expr));
/* getopts.c */
void 	resetopts	 ARGS((void));
int 	c_getopts	 ARGS((char **wp));
/* history.c */
int 	c_fc	 	 ARGS((register char **wp));
void 	histbackup	 ARGS((void));
void 	histsave	 ARGS((char *cmd));
char **	histget	 	 ARGS((char *str));
char *	histrpl	 	 ARGS((char *s, char *pat, char *rep, int global));
void 	hist_init	 ARGS((Source *s));
void 	hist_finish	 ARGS((void));
char **	histpos	 	 ARGS((void));
int 	histN	 	 ARGS((void));
int 	histnum	 	 ARGS((int n));
char *	findhist	 ARGS((int start, int fwd, char *str));
/* io.c */
int 	errorf		 ARGS((const char *fmt, ...));
int 	shellf		 ARGS((const char *fmt, ...));
void 	fopenshf	 ARGS((int fd));
void 	flushshf	 ARGS((int fd));
int 	savefd		 ARGS((int fd));
void 	restfd		 ARGS((int fd, int ofd));
void 	openpipe	 ARGS((int *pv));
void 	closepipe	 ARGS((int *pv));
struct temp *	maketemp ARGS((Area *ap));
/* jobs.c */
void 	j_init		 ARGS((void));
void 	j_exit		 ARGS((void));
void 	j_change	 ARGS((void));
int 	exchild		 ARGS((struct op *t, int flags));
int 	waitlast	 ARGS((void));
int 	j_reapchld	 ARGS((void));
int 	j_reap		 ARGS((void));
int 	waitfor		 ARGS((int job));
void 	j_kill		 ARGS((int job, int sig));
int 	j_resume	 ARGS((int job, int bg));
void 	j_jobs		 ARGS((void));
void 	j_notify	 ARGS((void));
int 	j_lookup	 ARGS((char *cp));
int 	j_stopped	 ARGS((void));
/* lex.c */
int 	yylex		 ARGS((int cf));
int 	gethere		 ARGS((void));
void 	yyerror		 ARGS((const char *msg));
Source * pushs		 ARGS((int type));
int 	pprompt		 ARGS((char *cp));
/* mail.c */
void 	mcheck		 ARGS((void));
void 	mbset		 ARGS((char *p));
void 	mpset		 ARGS((char *mptoparse));
void 	mprint		 ARGS((void));
/* main.c */
int 	main		 ARGS((int argc, char **argv, char **envp));
int 	include		 ARGS((char *name));
#if 0
int 	command		 ARGS((char *comm));
#endif
int 	shell		 ARGS((Source *s));
void 	leave		 ARGS((int rv));
int 	error		 ARGS((void));
int 	unwind		 ARGS((void));
int 	newenv		 ARGS((int type));
int 	quitenv		 ARGS((void));
void 	aerror		 ARGS((Area *ap, const char *msg));
/* misc.c */
void 	setctypes	 ARGS((/* const */ char *s, int t));
void 	initctypes	 ARGS((void));
char *	ulton		 ARGS((unsigned long n, int base));
char *	strsave		 ARGS((char *s, Area *ap));
int 	option		 ARGS((const char *n));
char *	getoptions	 ARGS((void));
void 	printoptions	 ARGS((void));
int 	getn		 ARGS((char *as));
char *	strerror	 ARGS((int i));
int 	gmatch		 ARGS((char *s, char *p));
void 	qsortp		 ARGS((void **base, size_t n, int (*f)()));
int 	qsort1		 ARGS((void **base, void **lim, int (*f)()));
int 	xstrcmp		 ARGS((void *p1, void *p2));
void 	cleanpath	 ARGS((char *pwd, char *dir, char *clean));
/* syn.c */
int 	yyparse		 ARGS((void));
int 	keywords	 ARGS((void));
struct op * compile	 ARGS((Source *s));
/* table.c */
unsigned int 	hash	 ARGS((char *n));
void 	tinit		 ARGS((struct table *tp, Area *ap));
struct tbl *	tsearch	 ARGS((struct table *tp, char *n, unsigned int h));
struct tbl *	tenter	 ARGS((struct table *tp, char *n, unsigned int h));
void 	tdelete		 ARGS((struct tbl *p));
void 	twalk		 ARGS((struct table *tp));
struct tbl *	tnext	 ARGS((void));
struct tbl **	tsort	 ARGS((struct table *tp));
/* trace.c */
/* trap.c */
Trap *	gettrap		 ARGS((char *name));
void 	trapsig		 ARGS((int i));
int 	runtraps	 ARGS((void));
int 	runtrap		 ARGS((Trap *p));
int 	cleartraps	 ARGS((void));
int 	ignoresig	 ARGS((int i));
int 	restoresigs	 ARGS((void));
/* tree.c */
void 	ptree		 ARGS((struct op *t, FILE *f));
int 	pioact		 ARGS((FILE *f, struct ioword *iop));
int 	fptreef		 ARGS((FILE *f, char *fmt, ...));
int 	snptreef	 ARGS((char *s, int n, char *fmt, ...));
struct op *	tcopy	 ARGS((struct op *t, Area *ap));
char *	wdcopy		 ARGS((char *wp, Area *ap));
char *	wdscan		 ARGS((char *wp, int c));
void 	tfree		 ARGS((struct op *t, Area *ap));
/* var.c */
void 	newblock	 ARGS((void));
void 	popblock	 ARGS((void));
struct tbl *	global	 ARGS((char *n));
struct tbl *	local	 ARGS((char *n));
char *	strval		 ARGS((struct tbl *vp));
long 	intval		 ARGS((struct tbl *vp));
void 	setstr		 ARGS((struct tbl *vq, char *s));
struct tbl *	strint	 ARGS((struct tbl *vq, struct tbl *vp));
void 	setint		 ARGS((struct tbl *vq, long n));
int 	import		 ARGS((char *thing));
struct tbl *	typeset	 ARGS((char *var, int set, int clr));
void 	unset		 ARGS((struct tbl *vp));
int 	isassign	 ARGS((char *s));
char **	makenv		 ARGS((void));
/* version.c */
/* vi.c */
void 	vi_reset	 ARGS((char *buf, int len));
int 	vi_hook		 ARGS((int ch));
int 	save_cbuf	 ARGS((void));
int 	restore_cbuf	 ARGS((void));
int 	x_vi		 ARGS((char *buf, size_t len));
int 	getch		 ARGS((void));
char **	globstr		 ARGS((char *stuff));


/* end inlined proto.h */
  
/*
 * 91-07-06 <sjg@sun0>
 * use my simple debug tracing... 
 */
/* begin inlined trace.h */
/* NAME:
 *      trace.h - definitions for a simple trace facility
 *
 * SYNOPSIS:
 *      #include "trace.h"
 *
 * DESCRIPTION:
 *      Defines the macro _TRACE().
 *      Also declares Trace_log and Trace_level.
 *
 * SEE ALSO:
 *      
 *
 * AMENDED:
 *      91/11/22  22:53:58  (sjg)
 *
 * RELEASED:
 *      91/11/22  22:54:18  v1.2
 *
 * SCCSID:
 *      @(#)trace.h  1.2  91/11/22  22:53:58  (sjg)
 *
 *      @(#)Copyright (c) 1990 Simon J. Gerraty.
 */

/* some useful #defines */
#ifndef EXTERN
# define EXTERN extern
# define EXTERN_DEFINED
#endif

#ifndef TRUE
# define TRUE  1
# define FALSE 0
#endif
#ifndef ARGS
# if defined(__STDC__) || defined(PROTO)
#   define ARGS(p) p
# else
#   define ARGS(p) ()
# endif
#endif

/*
 * this garbage is sometimes needed when mixing
 * langauges or calling conventions under DOS.
 */
#ifndef _CDECL
# if defined(MSDOS) || defined(MSC)
#   ifndef NO_EXT_KEYS
#     define _CDECL  cdecl
#     define _NEAR   near
#   else
#     define _CDECL
#     define _NEAR
#   endif
# else /* not DrOS */
#   define _CDECL
#   define _NEAR
# endif /* DOS */
#endif /* _CDECL */

/* manifest constants */

/* struct / union */

/* macros */


#ifdef USE_TRACE
EXTERN char * _CDECL	Trace_log;
EXTERN int _CDECL 	Trace_level;

void _CDECL checkpoint	ARGS((char *fmt, ...));

/*
 * This macro takes a variabel number of args. 
 * examples:
 * 	_TRACE(5, ("The current Debug level is %d\n", Debug));
 * Note that if more than two args are provided, all but the 
 * first (which should be an integer indicating the Trace-level 
 * required for this message to be printed) must be enclosed in 
 * parenthesis. 
 */
# define _TRACE(lev, args) if (Trace_level >= lev) checkpoint args
#else 	/* don't USE_TRACE */
  /*
   * this macro evaluates to a harmless no entry
   * loop that most optimizers will remove all together.
   */
# define _TRACE(l, args) while (0)
#endif 	/* USE_TRACE */


/* This lot goes at the END */
/* be sure not to interfere with anyone else's idea about EXTERN */
#ifdef EXTERN_DEFINED
# undef EXTERN_DEFINED
# undef EXTERN
#endif
/*
 * Local Variables:
 * version-control:t
 * comment-column:40
 * End:
 */
/* end inlined trace.h */

#ifndef fileno
#define fileno(p)	((p)->_fileno)
#endif

#undef Extern
#define Extern extern

/*
 * Expanding strings
 */

#if 0				/* Usage */
	XString xs;
	char *xp;

	Xinit(xs, xp, 128);	/* allocate initial string */
	while ((c = generate()) {
		Xcheck(xs, xp);	/* expand string if neccessary */
		Xput(xs, xp, c); /* add character */
	}
	return Xclose(xs, xp);	/* resize string */
#endif

typedef struct XString {
	char   *end, *beg;	/* end, begin of string */
#if 1
	char   *oth, *old;	/* togo, adjust */
#endif
	size_t	len;		/* length */
} XString;

typedef char * XStringP;

/* initialize expandable string */
#define	Xinit(xs, xp, length) { \
			(xs).len = length; \
			(xs).beg = alloc((xs).len + 8, ATEMP); \
			(xs).end = (xs).beg + (xs).len; \
			xp = (xs).beg; \
		}

/* stuff char into string */
#define	Xput(xs, xp, c)	*xp++ = (c)

/* check for overflow, expand string */
#define	Xcheck(xs, xp) if (xp >= (xs).end) { \
			char *old_beg = (xs).beg; \
			(xs).len += (xs).len; /* double size */ \
			(xs).beg = aresize((xs).beg, (xs).len + 8, ATEMP); \
			(xs).end = (xs).beg + (xs).len; \
			xp = (xs).beg + (xp - old_beg); /* adjust pointer */ \
		}

/* free string */
#define	Xfree(xs, xp)	afree((void*) (xs).beg, ATEMP)

/* close, return string */
#define	Xclose(xs, xp)	(char*) aresize((void*)(xs).beg, \
					(size_t)(xp - (xs).beg), ATEMP)
/* begin of string */
#define	Xstring(xs, xp)	((xs).beg)

#define	Xsavepos(xs, xp) (xp - (xs).beg)
#define	Xrestpos(xs, xp, n) ((xs).beg + (n))

/*
 * expandable vector of generic pointers
 */

typedef struct XPtrV {
	void  **cur;		/* next avail pointer */
	void  **beg, **end;	/* begin, end of vector */
} XPtrV;

#define	XPinit(x, n) { \
			register void **vp; \
			vp = (void**) alloc(sizeofN(void*, n), ATEMP); \
			(x).cur = (x).beg = vp; \
			(x).end = vp + n; \
			}

#define	XPput(x, p) { \
			if ((x).cur >= (x).end) { \
				int n = XPsize(x); \
				(x).beg = (void**) aresize((void*) (x).beg, \
						   sizeofN(void*, n*2), ATEMP); \
				(x).cur = (x).beg + n; \
				(x).end = (x).cur + n; \
			} \
			*(x).cur++ = (p); \
			}

#define	XPptrv(x)	((x).beg)
#define	XPsize(x)	((x).cur - (x).beg)

#define	XPclose(x)	(void**) aresize((void*)(x).beg, \
					 sizeofN(void*, XPsize(x)), ATEMP)

#define	XPfree(x)	afree((void*) (x).beg, ATEMP)


#if 0
/*
 * area-based allocation built on malloc/free
 */

typedef struct Area {
	struct Block *free;	/* free list */
} Area;


#endif /* unused alloc.h */

#pragma push_macro("PATCHLEVEL")
#pragma push_macro("VERSION")
#pragma push_macro("RCSid")
#define RCSid RCSid_version
#line 1 "version.c"
/*
 * value of $KSH_VERSION
 */

#ifndef lint
static char *RCSid = "$Id: version.c,v 1.4 1992/05/12 09:30:37 sjg Exp $";
#endif

#include <setjmp.h>
/* begin inlined patchlevel.h from version.c */
/*
 * PD KSH
 * $Id: patchlevel.h,v 4.5 1992/05/12 09:30:34 sjg Exp $
 */
#define VERSION		4
#define PATCHLEVEL	5
/* end inlined patchlevel.h from version.c */

char ksh_version [] =
	"KSH_VERSION=@(#)PD KSH v4.5 92/05/12";

/***
$Log: version.c,v $
 * Revision 1.4  1992/05/12  09:30:37  sjg
 * see ChangeLog
 *
 * Revision 1.3  1992/05/03  08:29:20  sjg
 * Update for Patch05
 *
 * Revision 1.2  1992/04/25  08:33:28  sjg
 * Added RCS key.
 *
 * Revision 1.1  1992/04/18  05:51:48  sjg
 * Initial revision
 *
Version  4.0  91/11/09  sjg
distribution
Revision 3.3  89/03/27  15:52:29  egisin
distribution

Revision 3.2  88/12/14  20:10:41  egisin
many fixes

Revision 3.1  88/11/03  09:18:36  egisin
alpha distribution

Revision 1.3  88/10/20  17:34:03  egisin
added @(#) to ksh_version

Revision 1.2  88/09/27  19:01:58  egisin
fix version.c

Revision 1.1  88/09/27  18:59:06  egisin
Initial revision
***/

#pragma pop_macro("RCSid")
#pragma pop_macro("VERSION")
#pragma pop_macro("PATCHLEVEL")

#pragma push_macro("remove")
#pragma push_macro("RCSid")
#define RCSid RCSid_main
#line 1 "main.c"
/*
 * startup, main loop, enviroments and error handling
 */

#ifndef lint
static char *RCSid = "$Id: main.c,v 1.4 1992/04/29 06:25:47 sjg Exp $";
#endif
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <time.h>

#if !defined(HAVE_REMOVE) && !defined(remove)
#define remove(x)	unlink(x)
#endif

/*
 * global data
 */

Area	aperm;

static	void	reclaim ARGS((void));

/*
 * shell initialization
 */

static	char	initifs [] = "IFS= \t\n"; /* must be R/W */

static	const	char   initsubs [] = 
#ifdef sun				/* sun's don't have a real /bin */
  "${SHELL:=/bin/sh} ${PATH:=/usr/bin:/usr/ucb:.} ${HOME:=/} ${PS1:=$ } ${PS2:=> } ${MAILCHECK:=600}";
#else
  "${SHELL:=/bin/sh} ${PATH:=/bin:/usr/bin:.} ${HOME:=/} ${PS1:=$ } ${PS2:=> } ${MAILCHECK:=600}";
#endif

static	const	char *initcoms [] = {
	"cd", ".", NULL,		/* set up $PWD */
	"typeset", "-x", "SHELL", "PATH", "HOME", NULL,
	"typeset", "-r", "PWD", "OLDPWD", NULL,
	"typeset", "-i", "SECONDS=0", "OPTIND=1", NULL,
	"alias",
	  "integer=typeset -i", "pwd=print -r \"$PWD\"",
	  "history=fc -l", "r=fc -e -", "nohup=nohup ",
	  "login=exec login", "newgrp=exec newgrp",
	  "type=whence -v", "functions=typeset -f",
	  "echo=print", "true=:", "false=let", "[=\\[", NULL,
	NULL
};

#ifdef USE_TRACE
/*
 * use SIGUSR1 to bump up Trace_level
 * use SIGUSR2 to clear Trace_level
 */
void
set_TraceLev(sig)
  int sig;
{
  switch(sig)
  {
  case SIGUSR1:
    Trace_level++;
    break;
  case SIGUSR2:
    Trace_level = 0;
    break;
  }
#if defined(_SYSV) && !defined(USE_SIGACT)
  if (sig > 0)
    (void) signal(sig, set_TraceLev);
#endif
  return;
}
#endif

int ksh_main(argc, argv, envp)
	int argc;
	register char **argv;
	char **envp;
{
	register int i;
	register char *arg;
	int cflag = 0, qflag = 0, fflag = 0;
	int argi;
	char *name;
	register Source *s;
	register struct block *l = &globals;
	register char **wp0, **wp;
	extern char ksh_version [];
	extern time_t time();

#ifdef USE_SIGACT
	sigemptyset(&Sigact.sa_mask);
	sigemptyset(&Sigact_dfl.sa_mask);
	sigemptyset(&Sigact_ign.sa_mask);
	sigemptyset(&Sigact_trap.sa_mask);
	Sigact.sa_flags = 0;
	Sigact_dfl.sa_flags = 0;
	Sigact_ign.sa_flags = 0;
	Sigact_trap.sa_flags = 0;
	Sigact_dfl.sa_handler = SIG_DFL;
	Sigact_ign.sa_handler = SIG_IGN;
	Sigact_trap.sa_handler = trapsig;
#endif
	ainit(&aperm);		/* initialize permanent Area */

#ifndef F_SETFD
  init_clexec();
#endif
	/* set up base enviroment */
	e.type = E_NONE;
	ainit(&e.area);
	e.loc = l;
	e.savefd = NULL;
	e.oenv = NULL;

	initctypes();

	/* open file streams for fd's 0,1,2 */
	fopenshf(0);	fopenshf(1);	fopenshf(2);

	/* set up variable and command dictionaries */
	newblock();		/* set up global l->vars and l->funs */
	tinit(&commands, APERM);
	tinit(&builtins, APERM);
	tinit(&lexicals, APERM);
	tinit(&homedirs, APERM);

	/* import enviroment */
	if (envp != NULL)
		for (wp = envp; *wp != NULL; wp++)
			import(*wp);

	kshpid = getpid();
	typeset(initifs, 0, 0);	/* for security */
	typeset(ksh_version, 0, 0); /* RDONLY */

#ifdef USE_TRACE
#ifdef USE_SIGACT
	Sigact.sa_handler = set_TraceLev;
	sigaction(SIGUSR1, &Sigact, NULL);
	sigaction(SIGUSR2, &Sigact, NULL);
#else
	(void) signal(SIGUSR1, set_TraceLev);
	(void) signal(SIGUSR2, set_TraceLev);
#endif
	_TRACE(0, ("Traces enabled.")); /* allow _TRACE to setup */
#endif

	/* define shell keywords */
	keywords();

	/* define built-in commands */
	for (i = 0; shbuiltins[i].name != NULL; i++)
		builtin(shbuiltins[i].name, shbuiltins[i].func);
	for (i = 0; kshbuiltins[i].name != NULL; i++)
		builtin(kshbuiltins[i].name, kshbuiltins[i].func);

	/* assign default shell variable values */
	substitute(initsubs, 0);
	setint(typeset("PPID", INTEGER, 0), (long) getppid());
	typeset("PPID", RDONLY, 0);
	setint(typeset("RANDOM", INTEGER, 0), (long) time((time_t *)0));
	/* execute initialization statements */
	for (wp0 = (char**) initcoms; *wp0 != NULL; wp0 = wp+1) {
		/* copy because the alias initializers are readonly */
		for (wp = wp0; *wp != NULL; wp++)
			*wp = strsave(*wp, ATEMP);
		shcomexec(wp0);
	}
	afreeall(ATEMP);

	if (geteuid() == 0)
		setstr(global("PS1"), "# ");

	s = pushs(SFILE);
	s->u.file = stdin;
	cflag = 0;
	name = *argv;

	/* what a bloody mess */
	if ((argi = 1) < argc) {
		if (argv[argi][0] == '-' && argv[argi][1] != '\0') {
			for (arg = argv[argi++]+1; *arg; arg++) {
				switch (*arg) {
				  case 'c':
					cflag = 1;
					if (argi < argc) {
						s->type = SSTRING;
						s->str = argv[argi++];
					}
					break;
	
				  case 'q':
					qflag = 1;
					break;

				  default:
					if (*arg>='a' && *arg<='z')
						flag[FLAG(*arg)]++;
				}
			}
		}
		if (s->type == SFILE && argi < argc && !flag[FSTDIN]) {
			s->file = name = argv[argi++];
			if ((s->u.file = fopen(name, "r")) == NULL)
				errorf("%s: cannot open\n", name);
			fflag = 1;
			fileno(s->u.file) = savefd(fileno(s->u.file));
			setvbuf(s->u.file, (char *)NULL, _IOFBF, BUFSIZ);
		}
	}

	if (s->type == SFILE) {
		if (fileno(s->u.file) == 0)
			flag[FSTDIN] = 1;
		if (isatty(0) && isatty(1) && !cflag && !fflag)
			flag[FTALKING] = 1;
		if (flag[FTALKING] && flag[FSTDIN])
			s->type = STTY;
	}
	if (s->type == STTY) {
		ttyfd = fcntl(0, F_DUPFD, FDBASE);
#ifdef F_SETFD
		(void) fcntl(ttyfd, F_SETFD, 1);
#else
		(void) fd_clexec(ttyfd);
#endif
#ifdef EMACS
		x_init_emacs();
#endif
	}

	/* initialize job control */
	j_init();

	if (!qflag)
		ignoresig(SIGQUIT);

	l->argv = &argv[argi];
	l->argc = argc - argi;
	l->argv[0] = name;
	resetopts();

	if (name[0] == '-') {
		flag[FTALKING] = 1;
		(void) include("/etc/profile");
		(void) include(".profile");
	}

	/* include $ENV */
	arg = substitute(strval(global("ENV")), DOTILDE);
	if (*arg != '\0')
		(void) include(arg);

	if (flag[FTALKING])
	{
#ifdef USE_SIGACT
	  sigaction(SIGTERM, &Sigact_trap, NULL);
#else
	  signal(SIGTERM, trapsig);
#endif
	  ignoresig(SIGINT);
#if defined(EMACS) || defined(VI)
	  init_editmode();
#endif
	} else
	  flag[FHASHALL] = 1;

#ifdef JOBS			/* todo: could go before includes? */
	if (s->type == STTY) {
		flag[FMONITOR] = 1;
		j_change();
	}
#endif
	if (flag[FTALKING])
	{
	  hist_init(s);
	}
	argc = shell(s);
	leave(argc);
	return 0;
}

int
include(name)
	register char *name;
{
	register FILE *f;
	register Source *s;

	if (strcmp(name, "-") != 0) {
		f = fopen(name, "r");
		if (f == NULL)
			return 0;
		/* todo: the savefd doesn't get popped */
		fileno(f) = savefd(fileno(f)); /* questionable */
		setvbuf(f, (char *)NULL, _IOFBF, BUFSIZ);
	} else
		f = stdin;
	s = pushs(SFILE);
	s->u.file = f;
	s->file = name;
	/*return*/ shell(s);
	if (f != stdin)
		fclose(f);
	return 1;
}

int
command(comm)
	register char *comm;
{
	register Source *s;

	s = pushs(SSTRING);
	s->str = comm;
	return shell(s);
}

/*
 * run the commands from the input source, returning status.
 */
int
shell(s)
	Source *s;		/* input source */
{
	struct op *t;
	volatile int attempts = 13;
	volatile int wastty;
	volatile int reading = 0;
	extern void mcheck();

	newenv(E_PARSE);
	e.interactive = 1;
	exstat = 0;
	if (setjmp(e.jbuf)) {
		/*shellf("<unwind>");*/
		if (trap)	/* pending SIGINT */
			shellf("\n");
		if (reading && s->type == STTY && s->line)
			s->line--;
		sigtraps[SIGINT].set = 0;
	}

	while (1) {
		if (trap)
			runtraps();
		if (flag[FTALKING])
		{
#ifdef USE_SIGACT
		  sigaction(SIGINT, &Sigact_trap, NULL);
#else
		  signal(SIGINT, trapsig);
#endif
		}

		if (s->next == NULL)
			s->echo = flag[FVERBOSE];

		j_notify();

		if ((wastty = (s->type == STTY)) || s->type == SHIST) {
			prompt = substitute(strval(global("PS1")), 0);
			mcheck();
		}

		reading = 1;
		t = compile(s);
		reading = 0;
		j_reap();
		if (t != NULL && t->type == TEOF)
			if (wastty && flag[FIGNEOF] && --attempts > 0) {
				shellf("Use `exit'\n");
				s->type = STTY;
				continue;
			}
			else
				break;
		flushshf(2);	/* flush -v output */

		if (!flag[FNOEXEC] || s->type == STTY)
			execute(t, 0);

		reclaim();
	}
	/* Error: */
	quitenv();
	return exstat;
}

void
leave(rv)
	int rv;
{
	if (e.type == E_TCOM && e.oenv != NULL)	/* exec'd command */
		unwind();
	runtrap(&sigtraps[0]);
	if (flag[FTALKING])
	{
	  hist_finish();
	}
	j_exit();
	exit(rv);
	/* NOTREACHED */
}

error()
{
	if (flag[FERREXIT] || !flag[FTALKING])
		leave(1);
	unwind();
}

/* return to closest error handler or shell(), exit if none found */
unwind()
{
	while (1)
		switch (e.type) {
		  case E_NONE:
			leave(1);
			/* NOTREACHED */
		  case E_PARSE:
			longjmp(e.jbuf, 1);
			/* NOTREACHED */
		  case E_ERRH:
			longjmp(e.jbuf, 1);
			/* NOTREACHED */
		  default:
			quitenv();
			break;
		}
}

newenv(type)
{
	register struct env *ep;

	ep = (struct env *) alloc(sizeof(*ep), ATEMP);
	*ep = e;
	ainit(&e.area);
	e.type = type;
	e.oenv = ep;
	e.savefd = NULL;
	e.temps = NULL;
}

quitenv()
{
	register struct env *ep;
	register int fd;

	if ((ep = e.oenv) == NULL)
		exit(exstat);	/* exit child */
	if (e.loc != ep->loc)
		popblock();
	if (e.savefd != NULL)
		for (fd = 0; fd < NUFILE; fd++)
			restfd(fd, e.savefd[fd]);
	reclaim();
	e = *ep;
	afree(ep, ATEMP);
}

/* remove temp files and free ATEMP Area */
static void
reclaim()
{
	register struct temp *tp;

	for (tp = e.temps; tp != NULL; tp = tp->next)
		remove(tp->name);
	e.temps = NULL;
	afreeall(&e.area);
}

void
aerror(ap, msg)
	Area *ap;
	const char *msg;
{
	errorf("alloc internal error: %s\n", msg);
}

#pragma pop_macro("RCSid")
#pragma pop_macro("remove")

#pragma push_macro("UCHAR_MAX")
#pragma push_macro("swap2")
#pragma push_macro("swap3")
#pragma push_macro("RCSid")
#define RCSid RCSid_misc
#line 1 "misc.c"
/*
 * Miscellaneous functions
 */

#ifndef lint
static char *RCSid = "$Id: misc.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#ifndef NOSTDHDRS
# include <limits.h>
#else
# define UCHAR_MAX	0xFF
#endif

char ctypes [UCHAR_MAX+1];	/* type bits for unsigned char */

static char *   cclass      ARGS((char *p, int sub));

/*
 * Fast character classes
 */
void
setctypes(s, t)
	register /* const */ char *s;
	register int t;
{
	register int i;

	if ((t&C_IFS)) {
		for (i = 0; i < UCHAR_MAX+1; i++)
			ctypes[i] &=~ C_IFS;
		ctypes[0] |= C_IFS; /* include \0 in C_IFS */
	}
	ctypes[(unsigned char) *s++] |= t;	/* allow leading \0 in string */
	while (*s != 0)
		ctypes[(unsigned char) *s++] |= t;
}

void
initctypes()
{
	register int c;

	for (c = 'a'; c <= 'z'; c++)
		ctypes[c] |= C_ALPHA;
	for (c = 'A'; c <= 'Z'; c++)
		ctypes[c] |= C_ALPHA;
	ctypes['_'] |= C_ALPHA;
	setctypes("0123456789", C_DIGIT);
	setctypes("\0 \t\n|&;<>()", C_LEX1);
	setctypes("*@#!$-?", C_VAR1);
	setctypes("=-+?#%", C_SUBOP);
}

/* convert unsigned long to base N string */

char *
ulton(n, base)
	register unsigned long n;
	int base;
{
	register char *p;
	static char buf [20];

	p = &buf[sizeof(buf)];
	*--p = '\0';
	do {
		*--p = "0123456789ABCDEF"[n%base];
		n /= base;
	} while (n != 0);
	return p;
}

char *
strsave(s, ap)
	register char *s;
	Area *ap;
{
	return strcpy((char*) alloc((size_t)strlen(s)+1, ap), s);
}

static struct option {
	char *name;
	int flag;
} options[] = {
	{"allexport",	FEXPORT},
	{"bgnice",	FBGNICE},
#if defined(EDIT) && defined(EMACS)
	{"emacs",	FEMACS},
#endif
	{"errexit",	FERREXIT},
	{"hashall",	FHASHALL},
	{"ignoreeof",	FIGNEOF},
	{"interactive",	FTALKING},
	{"keyword",	FKEYWORD},
	{"markdirs",	FMARKDIRS},
	{"monitor",	FMONITOR},
	{"noexec",	FNOEXEC},
	{"noglob",	FNOGLOB},
	{"nounset",	FNOUNSET},
	{"privileged",	FPRIVILEGED},
	{"stdin",	FSTDIN},
	{"trackall",	FHASHALL},
	{"verbose",	FVERBOSE},
#if defined(EDIT) && defined(VI)
	{"vi",		FVI},
#endif
	{"xtrace",	FXTRACE},
	{NULL,		0}
};	

/*
 * translate -o option into F* constant
 */
int
option(n)
	const char *n;
{
	register struct option *op;

	for (op = options; op->name != NULL; op++)
		if (strcmp(op->name, n) == 0)
			return op->flag;
	return 0;
}

char *
getoptions()
{
	register int c;
	char m [26+1];
	register char *cp = m;

	for (c = 'a'; c <= 'z'; c++)
		if (flag[FLAG(c)])
			*cp++ = (char) c;
	*cp = 0;
	return strsave(m, ATEMP);
}

void
printoptions()
{
	register struct option *op;

	for (op = options; op->name != NULL; op++)
		if (flag[op->flag])
			shellf("%s ", op->name);
	shellf("\n");
}
	
/* atoi with error detection */

getn(as)
	char *as;
{
	register char *s;
	register int n;

	s = as;
	if (*s == '-')
		s++;
	for (n = 0; digit(*s); s++)
		n = (n*10) + (*s-'0');
	if (*s)
		errorf("%s: bad number\n", as);
	return (*as == '-') ? -n : n;
}

/*
 * stripped down strerror for kill and exec
 */
char *
strerror(i)
	int i;
{
	switch (i) {
	  case EINVAL:
		return "Invalid argument";
	  case EACCES:
		return "Permission denied";
	  case ESRCH:
		return "No such process";
	  case EPERM:
		return "Not owner";
	  case ENOENT:
		return "No such file or directory";
	  case ENOTDIR:
		return "Not a directory";
	  case ENOEXEC:
		return "Exec format error";
	  case ENOMEM:
		return "Not enough memory";
	  case E2BIG:
		return "Argument list too long";
	  default:
		return "Unknown system error";
	}
}

/*
 * int gmatch(string, pattern)
 * char *string, *pattern;
 *
 * Match a pattern as in sh(1).
 * pattern character are prefixed with MAGIC by expand.
 */

static	char	*cclass ARGS((char *, int c));

int
gmatch(s, p)
	register char *s, *p;
{
	register int sc, pc;

	if (s == NULL || p == NULL)
		return 0;
	while ((pc = *p++) != 0) {
		sc = *s++;
		if (pc ==  MAGIC)
			switch (*p++) {
			  case '[':
				if (sc == 0 || (p = cclass(p, sc)) == NULL)
					return (0);
				break;

			  case '?':
				if (sc == 0)
					return (0);
				break;

			  case '*':
				s--;
				do {
					if (*p == '\0' || gmatch(s, p))
						return (1);
				} while (*s++ != '\0');
				return (0);

			  default:
				if (sc != p[-1])
					return 0;
				break;
			}
		else
			if (sc != pc)
				return 0;
	}
	return (*s == 0);
}

static char *
cclass(p, sub)
	register char *p;
	register int sub;
{
	register int c, d, not, found = 0;

	if ((not = (*p == MAGIC && *++p == NOT)))
		p++;
	do {
		if (*p == MAGIC)
			p++;
		if (*p == '\0')
			return NULL;
		c = *p;
		if (p[1] == '-' && p[2] != ']') {
			d = p[2];
			p++;
		} else
			d = c;
		if (c == sub || (c <= sub && sub <= d))
			found = 1;
	} while (*++p != ']');

	return (found != not) ? p+1 : NULL;
}


/*
 * quick sort of array of generic pointers to objects.
 */

void
qsortp(base, n, f)
	void **base;		/* base address */
	size_t n;		/* elements */
	int (*f)();		/* compare function */
{
	qsort1(base, base + n, f);
}

#define	swap2(a, b)	{\
	register void *t; t = *(a); *(a) = *(b); *(b) = t;\
}
#define	swap3(a, b, c)	{\
	register void *t; t = *(a); *(a) = *(c); *(c) = *(b); *(b) = t;\
}

qsort1(base, lim, f)
	void **base, **lim;
	int (*f)();
{
	register void **i, **j;
	register void **lptr, **hptr;
	size_t n;
	int c;

  top:
	n = (lim - base) / 2;
	if (n == 0)
		return;
	hptr = lptr = base+n;
	i = base;
	j = lim - 1;

	for (;;) {
		if (i < lptr) {
			if ((c = (*f)(*i, *lptr)) == 0) {
				lptr --;
				swap2(i, lptr);
				continue;
			}
			if (c < 0) {
				i += 1;
				continue;
			}
		}

	  begin:
		if (j > hptr) {
			if ((c = (*f)(*hptr, *j)) == 0) {
				hptr ++;
				swap2(hptr, j);
				goto begin;
			}
			if (c > 0) {
				if (i == lptr) {
					hptr ++;
					swap3(i, hptr, j);
					i = lptr += 1;
					goto begin;
				}
				swap2(i, j);
				j -= 1;
				i += 1;
				continue;
			}
			j -= 1;
			goto begin;
		}

		if (i == lptr) {
			if (lptr-base >= lim-hptr) {
				qsort1(hptr+1, lim, f);
				lim = lptr;
			} else {
				qsort1(base, lptr, f);
				base = hptr+1;
			}
			goto top;
		}

		lptr -= 1;
		swap3(j, lptr, i);
		j = hptr -= 1;
	}
}

int
xstrcmp(p1, p2)
	void *p1, *p2;
{
	return (strcmp((char *)p1, (char *)p2));
}

void
cleanpath(pwd, dir, clean)
	char *pwd, *dir, *clean;
{
	register char  *s, *d, *p;
	char *slash = "/";
	register int inslash = 0;

	d = clean;
	if (*dir != '/') {
		s = pwd;
		while (*d++ = *s++)
			;
		if (d >= clean + 2 && *(d - 2) == '/')
			d--;
		else
			*(d - 1) = '/';
	}

	s = dir;
	while (*s) {
		if ((*d++ = *s++) == '/' && d > clean + 1) {
			if (*(p = d - 2) == '/') {
				--d;
			} else if (*p == '.') {
				if (*--p == '/') {
					d -= 2;
				} else if (*p == '.' && *--p == '/') {
					while (p > clean && *--p != '/')
						;
					d = p + 1;
				}
			}
		}
		if (!*s && !inslash && *(s - 1) != '/') {
			inslash = 1;
			s = slash;
		}
	}

	if (*(d - 1) == '/' && (d - 1) > clean)
		d--;
	*d = '\0';
}
#pragma pop_macro("RCSid")
#pragma pop_macro("swap3")
#pragma pop_macro("swap2")
#pragma pop_macro("UCHAR_MAX")

#pragma push_macro("RCSid")
#define RCSid RCSid_trap
#line 1 "trap.c"
/*
 * signal handling
 */

#ifndef lint
static char *RCSid = "$Id: trap.c,v 1.2 1992/04/24 12:01:38 sjg Exp $";
#endif

#include <errno.h>
#include <signal.h>
#include <setjmp.h>

Trap sigtraps [SIGNALS] = {
	{0,	"EXIT", "Signal 0"}, /* todo: belongs in e.loc->exit */
	{SIGHUP, "HUP", "Hangup"},
	{SIGINT, "INT", "Interrupt"},
	{SIGQUIT, "QUIT", "Quit"},
	{SIGILL, "ILL", "Illegal instruction"},
	{SIGTRAP, "TRAP", "Trace trap"},
#ifdef	SIGABRT
	{SIGIOT, "ABRT", "Abort"},
#else
	{SIGIOT, "IOT", "IOT instruction"},
#endif
	//{SIGEMT, "EMT", "EMT trap"},
    {SIGBUS, "BUS", "BUS trap"},
	{SIGFPE, "FPE", "Floating exception"},
	{SIGKILL, "KILL", "Killed"},
#ifdef _MINIX
	{SIGUSR1, "USR1", "User defined signal 1"},
	{SIGSEGV, "SEGV", "Memory fault"},
	{SIGUSR2, "USR2", "User defined signal 2"},
#else
	{SIGBUS, "BUS", "Bus error"},
	{SIGSEGV, "SEGV", "Memory fault"},
	{SIGSYS, "SYS", "Bad system call"},
#endif
	{SIGPIPE, "PIPE", "Broken pipe"},
	{SIGALRM, "ALRM", "Alarm clock"},
	{SIGTERM, "TERM", "Terminated"},
#ifdef _MINIX
	{SIGSTKFLT, "STKFLT", "Stack fault"},
#endif
#ifdef _SYSV
	{SIGUSR1, "USR1", "User defined signal 1"},
	{SIGUSR2, "USR2", "User defined signal 2"},
	{SIGCLD, "CLD", "Death of a child"},
	{SIGPWR, "PWR", "Power-fail restart"},
#ifdef JOBS			/* todo: need to be more portable */
	{SIGTSTP, "TSTP", "Stop"},
	{SIGTTIN, "TTIN", "Stop (tty input)"},
#ifdef SIGPOLL
	{SIGPOLL, "POLL", "Pollable event occured"},
#endif
	{SIGSTOP, "STOP", "Stop (signal)"},
	{SIGTTOU, "TTOU", "Stop (tty output)"},
	{SIGCONT, "CONT", "Continue"},
#endif
#else
#ifdef JOBS			/* todo: need to be more portable */
	{SIGURG, "URG", "Urgent condition"}, /* BSDism */
	{SIGSTOP, "STOP", "Stop (signal)"},
	{SIGTSTP, "TSTP", "Stop"},
	{SIGCONT, "CONT", "Continue"},
	{SIGCHLD, "CHLD", "Waiting children"},
	{SIGTTIN, "TTIN", "Stop (tty input)"},
	{SIGTTOU, "TTOU", "Stop (tty output)"},
#endif
#endif
};

Trap *
gettrap(name)
	char *name;
{
	int i;
	register Trap *p;

	if (digit(*name)) {
		i = getn(name);
		return (0 <= i && i < SIGNALS) ? &sigtraps[getn(name)] : NULL;
	}
#if 0
	if (strcmp("ERR", name) == 0)
		return &e.loc->err;
	if (strcmp("EXIT", name) == 0)
		return &e.loc->exit;
#endif
	for (p = sigtraps, i = SIGNALS; --i >= 0; p++)
		if (p->name != NULL && strcmp(p->name, name) == 0)
			return p;
	return NULL;
}

/*
 * trap signal handler
 */
void
trapsig(i)
	int i;
{
	trap = sigtraps[i].set = 1;
	if (i == SIGINT && e.type == E_PARSE)
		/* dangerous but necessary to deal with BSD silly signals */
		longjmp(e.jbuf, 1);
#ifdef USE_SIGACT
	sigaction(i, &Sigact_trap, NULL);
#else
	(void) signal(i, trapsig);
#endif
}

/*
 * run any pending traps
 */
runtraps()
{
	int i;
	register Trap *p;

	for (p = sigtraps, i = SIGNALS; --i >= 0; p++)
		if (p->set)
			runtrap(p);
	trap = 0;
}

runtrap(p)
	Trap *p;
{
	char *trapstr;

	p->set = 0;
	if ((trapstr = p->trap) == NULL)
		if (p->signal == SIGINT)
			unwind();	/* return to shell() */
		else
			return;
	if (p->signal == 0)	/* ??? */
		p->trap = 0;
	command(trapstr);
}
 
/* restore signals for children */
cleartraps()
{
	int i;
	register Trap *p;

	if ((p = sigtraps)->trap != NULL) {	/* Maybe put in exchild() */
		afree((void *)p->trap,APERM);	/* Necessary? */
		p->trap = NULL;
	}
	for (i = SIGNALS, p = sigtraps; --i >= 0; p++) {
		p->set = 0;
#ifdef USE_SIGACT
		if (p->ourtrap)
		{
		  sigaction(p->signal, &Sigact_ign, &Sigact);
		  if (Sigact.sa_handler != SIG_IGN)
		    sigaction(p->signal, &Sigact_dfl, NULL);
		}
#else
		if (p->ourtrap && signal(p->signal, SIG_IGN) != SIG_IGN)
			(void) signal(p->signal, SIG_DFL);
#endif
	}
}

ignoresig(i)
	int i;
{
#ifdef USE_SIGACT
  sigaction(i, &Sigact_ign, &Sigact);
  sigemptyset(&Sigact.sa_mask);
  Sigact.sa_flags = 0;

  if (Sigact.sa_handler != SIG_IGN)
    sigtraps[i].sig_dfl = 1;
#else
  if (signal(i, SIG_IGN) != SIG_IGN)
    sigtraps[i].sig_dfl = 1;
#endif
}

restoresigs()
{
	int i;
	register Trap *p;

	for (p = sigtraps, i = SIGNALS; --i >= 0; p++)
		if (p->sig_dfl) {
			p->sig_dfl = 0;
#ifdef USE_SIGACT
			sigaction(p->signal, &Sigact_dfl, NULL);
#else
			(void) signal(p->signal, SIG_DFL);
#endif
		}
}

#pragma pop_macro("RCSid")

#pragma push_macro("ICELLS")
#pragma push_macro("RCSid")
#define RCSid RCSid_alloc
#line 1 "alloc.c"
/*
 * area-based allocation built on malloc/free
 */

#ifndef lint
static char *RCSid = "$Id: alloc.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <setjmp.h>

#define	ICELLS	100		/* number of Cells in small Block */

typedef union Cell Cell;
typedef struct Block Block;

/*
 * The Cells in a Block are organized as a set of objects.
 * Each object (pointed to by dp) begins with a size in (dp-1)->size,
 * followed with "size" data Cells.  Free objects are
 * linked together via dp->next.
 */

union Cell {
	size_t	size;
	union Cell   *next;
	struct {int _;} junk;	/* alignment */
};

struct Block {
	struct Block  *next;		/* list of Blocks in Area */
	union Cell   *free;		/* object free list */
	union Cell   *last;		/* &b.cell[size] */
	union Cell	cell [1];	/* [size] Cells for allocation */
};

Block aempty = {&aempty, aempty.cell, aempty.cell};

/* create empty Area */
Area *
ainit(ap)
	register Area *ap;
{
	ap->free = &aempty;
	return ap;
}

/* free all object in Area */
void
afreeall(ap)
	register Area *ap;
{
	register Block *bp;
	register Block *tmp;

	bp = ap->free;
	if (bp != NULL && bp != &aempty) {
		do {
			tmp = bp->next;
			free((void*)bp);
			bp = tmp;
		} while (bp != ap->free);
		ap->free = &aempty;
	}
}

/* allocate object from Area */
void *
alloc(size, ap)
	size_t size;
	register Area *ap;
{
	int cells, split;
	register Block *bp;
	register Cell *dp, *fp, *fpp;

	if (size <= 0) {
		aerror(ap, "allocate bad size");
		return NULL;
	}
	cells = (unsigned)(size - 1) / sizeof(Cell) + 1;

	/* find Cell large enough */
	for (bp = ap->free; ; bp = bp->next) {
		for (fpp = NULL, fp = bp->free;
		     fp != bp->last; fpp = fp, fp = fpp->next)
			if ((fp-1)->size >= cells)
				goto Found;

		/* wrapped around Block list, create new Block */
		if (bp->next == ap->free) {
			bp = (Block*) malloc(offsetof(Block, cell[ICELLS + cells]));
			if (bp == NULL) {
				aerror(ap, "cannot allocate");
				return NULL;
			}
			if (ap->free == &aempty)
				bp->next = bp;
			else {
				bp->next = ap->free->next;
				ap->free->next = bp;
			}
			bp->last = bp->cell + ICELLS + cells;
			fp = bp->free = bp->cell + 1; /* initial free list */
			(fp-1)->size = ICELLS + cells - 1;
			fp->next = bp->last;
			fpp = NULL;
			break;
		}
	}
  Found:
	ap->free = bp;
	dp = fp;		/* allocated object */
	split = (dp-1)->size - cells;
	if (split < 0)
		aerror(ap, "allocated object too small");
	if (--split <= 0) {	/* allocate all */
		fp = fp->next;
	} else {		/* allocate head, free tail */
		(fp-1)->size = cells;
		fp += cells + 1;
		(fp-1)->size = split;
		fp->next = dp->next;
	}
	if (fpp == NULL)
		bp->free = fp;
	else
		fpp->next = fp;
	return (void*) dp;
}

/* change size of object -- like realloc */
void *
aresize(ptr, size, ap)
	register void *ptr;
	size_t size;
	Area *ap;
{
	int cells;
	register Cell *dp = (Cell*) ptr;

	if (size <= 0) {
		aerror(ap, "allocate bad size");
		return NULL;
	}
	cells = (unsigned)(size - 1) / sizeof(Cell) + 1;

	if (dp == NULL || (dp-1)->size < cells) { /* enlarge object */
		register Cell *np;
		register int i;
		void *optr = ptr;

		ptr = alloc(size, ap);
		np = (Cell*) ptr;
		if (dp != NULL)
			for (i = (dp-1)->size; i--; )
				*np++ = *dp++;
		afree(optr, ap);
	} else {		/* shrink object */
		int split;

		split = (dp-1)->size - cells;
		if (--split <= 0) /* cannot split */
			;
		else {		/* shrink head, free tail */
			(dp-1)->size = cells;
			dp += cells + 1;
			(dp-1)->size = split;
			afree((void*)dp, ap);
		}
	}
	return (void*) ptr;
}

void
afree(ptr, ap)
	void *ptr;
	register Area *ap;
{
	register Block *bp;
	register Cell *fp, *fpp;
	register Cell *dp = (Cell*)ptr;

	/* find Block containing Cell */
	for (bp = ap->free; ; bp = bp->next) {
		if (bp->cell <= dp && dp < bp->last)
			break;
		if (bp->next == ap->free) {
			aerror(ap, "freeing with invalid area");
			return;
		}
	}

	/* find position in free list */
	for (fpp = NULL, fp = bp->free; fp < dp; fpp = fp, fp = fpp->next)
		;

	if (fp == dp) {
		aerror(ap, "freeing free object");
		return;
	}

	/* join object with next */
	if (dp + (dp-1)->size == fp-1) { /* adjacent */
		(dp-1)->size += (fp-1)->size + 1;
		dp->next = fp->next;
	} else			/* non-adjacent */
		dp->next = fp;

	/* join previous with object */
	if (fpp == NULL)
		bp->free = dp;
	else if (fpp + (fpp-1)->size == dp-1) { /* adjacent */
		(fpp-1)->size += (dp-1)->size + 1;
		fpp->next = dp->next;
	} else			/* non-adjacent */
		fpp->next = dp;
}


#if TEST_ALLOC

Area a;

int ksh_main(int argc, char **argv) {
	int i;
	char *p [9];

	ainit(&a);
	for (i = 0; i < 9; i++) {
		p[i] = alloc(124, &a);
		printf("alloc: %x\n", p[i]);
	}
	for (i = 1; i < argc; i++)
		afree(p[atoi(argv[i])], &a);
	afreeall(&a);
	return 0;
}

void aerror(Area *ap, const char *msg) {
	abort();
}

#endif

#pragma pop_macro("RCSid")
#pragma pop_macro("ICELLS")

#pragma push_macro("RCSid")
#define RCSid RCSid_io
#line 1 "io.c"
/*
 * shell buffered IO and formatted output
 */

#ifndef lint
static char *RCSid = "$Id: io.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <setjmp.h>
#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#if 0
/* fputc with ^ escaping */
static void
fzotc(c, f)
	register int c;
	register FILE *f;
{
	if ((c&0x60) == 0) {		/* C0|C1 */
		putc((c&0x80) ? '$' : '^', f);
		putc((c&0x7F|0x40), f);
	} else if ((c&0x7F) == 0x7F) {	/* DEL */
		putc((c&0x80) ? '$' : '^', f);
		putc('?', f);
	} else
		putc(c, f);
}
#endif

/*
 * formatted output functions
 */

/* shellf(...); error() */
int
#ifdef __STDC__
errorf(const char *fmt, ...) {
#else
errorf(va_alist) va_dcl
{
	char *fmt;
#endif
	va_list va;

#ifdef __STDC__
	va_start(va, fmt);
#else
	va_start(va);
	fmt = va_arg(va, char *);
#endif
	vfprintf(shlout, fmt, va);
	va_end(va);
	/*fflush(shlout);*/
	error();
}

/* printf to shlout (stderr) */
int
#ifdef __STDC__
shellf(const char *fmt, ...) {
#else
shellf(va_alist) va_dcl
{
	char *fmt;
#endif
	va_list va;

#ifdef __STDC__
	va_start(va, fmt);
#else
	va_start(va);
	fmt = va_arg(va, char *);
#endif
	vfprintf(shlout, fmt, va);
	va_end(va);
	return 0;
}

/*
 * We have a stdio stream for any open shell file descriptors (0-9)
 */
FILE *	shf [NUFILE];		/* map shell fd to FILE * */

/* open stream for shell fd */
void
fopenshf(fd)
	int fd;
{
	if (shf[fd] != NULL)
		return;
	if (fd <= 2)
#ifdef _MINIX
		/* ? */;
#else
		_iob[fd]._flag = 0; /* re-use stdin, stdout, stderr */
#endif
	shf[fd] = fdopen(fd, "r+");
	if (shf[fd] == NULL)
		return;
	setvbuf(shf[fd], (char*)NULL, _IOFBF, (size_t)BUFSIZ);
}

/* flush stream assoc with fd */
/* this must invalidate input and output buffers */
void
flushshf(fd)
	int fd;
{
	if (shf[fd] != NULL) {
		fseek(shf[fd], 0L, 1); /* V7 derived */
		fflush(shf[fd]);	/* standard C */
	}
}

/*
 * move fd from user space (0<=fd<10) to shell space (fd>=10)
 */
int
savefd(fd)
	int fd;
{
	int nfd;

	if (fd < FDBASE) {
		flushshf(fd);
		nfd = fcntl(fd, F_DUPFD, FDBASE);
		if (nfd < 0)
			if (errno == EBADF)
				return -1;
			else
				errorf("too many files open in shell\n");
#ifdef F_SETFD
		(void) fcntl(nfd, F_SETFD, 1);
#else
		(void) fd_clexec(ttyfd);
#endif
		close(fd);
	} else
		nfd = fd;
	return nfd;
}

void
restfd(fd, ofd)
	int fd, ofd;
{
	if (ofd == 0)		/* not saved (e.savefd) */
		return;
	flushshf(fd);
	close(fd);
	if (ofd < 0)		/* original fd closed */
		return;
	(void) fcntl(ofd, F_DUPFD, fd);
	close(ofd);
}

void
openpipe(pv)
	register int *pv;
{
	if (pipe(pv) < 0)
		errorf("can't create pipe - try again\n");
	pv[0] = savefd(pv[0]);
	pv[1] = savefd(pv[1]);
}

void
closepipe(pv)
	register int *pv;
{
	close(pv[0]);
	close(pv[1]);
}

/*
 * temporary files
 */

struct temp *
maketemp(ap)
	Area *ap;
{
	register struct temp *tp;
	static unsigned int inc = 0;
	char path [PATH];

	sprintf(path, "/tmp/sh%05u%02u", (unsigned)getpid(), inc++);
#if defined(_SYSV) || defined(_BSD)
	close(creat(path, 0600));	/* to get appropriate permissions */
#endif
	tp = (struct temp *) alloc(sizeof(struct temp), ap);
	tp->next = NULL;
	tp->name = strsave(path, ap);
	return tp;
}
#pragma pop_macro("RCSid")

#pragma push_macro("ACCEPT")
#pragma push_macro("REJECT")
#pragma push_macro("command")
#pragma push_macro("token")
#pragma push_macro("tpeek")
#pragma push_macro("RCSid")
#define RCSid RCSid_syn
#define command syn_command
#line 1 "syn.c"
/*
 * shell parser (C version)
 */

#ifndef lint
static char *RCSid = "$Id: syn.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <setjmp.h>

static struct op *pipeline  ARGS((int cf));
static struct op *andor     ARGS((void));
static struct op *c_list    ARGS((void));
static struct ioword *synio ARGS((int cf));
static void     musthave    ARGS((int c, int cf));
static struct op *nested    ARGS((int type, int mark));
static struct op *command   ARGS((int cf));
static struct op *dogroup   ARGS((int onlydone));
static struct op *thenpart  ARGS((void));
static struct op *elsepart  ARGS((void));
static struct op *caselist  ARGS((void));
static struct op *casepart  ARGS((void));
static char **  wordlist    ARGS((void));
static struct op *block     ARGS((int type, struct op *t1, struct op *t2, char **wp));
static struct op *newtp     ARGS((int type));
static void     zzerr       ARGS((void));

static	struct	op	*outtree; /* yyparse output */

static	int	reject;		/* token(cf) gets symbol again */
static	int	symbol;		/* yylex value */

#define	REJECT	(reject = 1)
#define	ACCEPT	(reject = 0)
#define	token(cf) \
	((reject) ? (ACCEPT, symbol) : (symbol = yylex(cf)))
#define	tpeek(cf) \
	((reject) ? (symbol) : (REJECT, symbol = yylex(cf)))

int
yyparse()
{
	ACCEPT;
	yynerrs = 0;
	if ((tpeek(KEYWORD|ALIAS)) == 0) { /* EOF */
		outtree = newtp(TEOF);
		return 0;
	}
	outtree = c_list();
	musthave('\n', 0);
	return (yynerrs != 0);
}

static struct op *
pipeline(cf)
	int cf;
{
	register struct op *t, *p, *tl = NULL;
	register int c;

	t = command(cf);
	if (t != NULL) {
		while ((c = token(0)) == '|') {
			if ((p = command(CONTIN)) == NULL)
				SYNTAXERR;
			if (tl == NULL)
				t = tl = block(TPIPE, t, p, NOWORDS);
			else
				tl = tl->right = block(TPIPE, tl->right, p, NOWORDS);
			/*t = block(TPIPE, t, p, NOWORDS);*/
		}
		REJECT;
	}
	return (t);
}

static struct op *
andor()
{
	register struct op *t, *p;
	register int c;

	t = pipeline(0);
	if (t != NULL) {
		while ((c = token(0)) == LOGAND || c == LOGOR) {
			if ((p = pipeline(CONTIN)) == NULL)
				SYNTAXERR;
			t = block(c == LOGAND? TAND: TOR, t, p, NOWORDS);
		}
		REJECT;
	}
	return (t);
}

static struct op *
c_list()
{
	register struct op *t, *p, *tl = NULL;
	register int c;

	t = andor();
	if (t != NULL) {
		while ((c = token(0)) == ';' || c == '&' ||
		       ((multiline || source->type == SSTRING
		        || (source->type == SALIAS)) && c == '\n')) {
			if (c == '&') {
				if (tl)
					tl->right = block(TASYNC, tl->right, NOBLOCK, NOWORDS);
				else
					t = block(TASYNC, t, NOBLOCK, NOWORDS);
			}
			if ((p = andor()) == NULL)
				return (t);
			if (tl == NULL)
				t = tl = block(TLIST, t, p, NOWORDS);
			else
				tl = tl->right = block(TLIST, tl->right, p, NOWORDS);
		}
		REJECT;
	}
	return (t);
}

static struct ioword *
synio(cf)
	int cf;
{
	register struct ioword *iop;

	if (tpeek(cf) != REDIR)
		return NULL;
	ACCEPT;
	iop = yylval.iop;
	musthave(LWORD, 0);
	iop->name = yylval.cp;
	if ((iop->flag&IOTYPE) == IOHERE) {
		if (*ident != 0) /* unquoted */
			iop->flag |= IOEVAL;
		if (herep >= &heres[HERES])
			errorf("too many <<'s\n");
		*herep++ = iop;
	}
	return iop;
}

static void
musthave(c, cf)
	int c, cf;
{
	if ((token(cf)) != c)
		SYNTAXERR;
}

static struct op *
nested(type, mark)
	int type, mark;
{
	register struct op *t;

	multiline++;
	t = c_list();
	musthave(mark, KEYWORD);
	multiline--;
	return (block(type, t, NOBLOCK, NOWORDS));
}

static struct op *
command(cf)
	int cf;
{
	register struct op *t;
	register int c, iopn = 0;
	struct ioword *iop, **iops;
	XPtrV args, vars;

	iops = (struct ioword **) alloc(sizeofN(struct ioword *, NUFILE+1), ATEMP);
	XPinit(args, 16);
	XPinit(vars, 16);

	if (multiline)
		cf = CONTIN;
	cf |= KEYWORD|ALIAS;

	while ((iop = synio(cf)) != NULL) {
		if (iopn >= NUFILE)
			yyerror("too many redirections");
		iops[iopn++] = iop;
		cf &=~ CONTIN;
	}

	switch (c = token(cf)) {
	  case 0:
		yyerror("unexpected EOF");
		return NULL;

	  default:
		REJECT;
		if (iopn == 0)
			return NULL; /* empty line */
		t = newtp(TCOM);
		break;

	  case LWORD:
	  case MDPAREN:
		REJECT;
		t = newtp(TCOM);
		if (c == MDPAREN) {
			ACCEPT;
			XPput(args,"let");
			musthave(LWORD,LETEXPR);
			XPput(args,yylval.cp);
		}
		while (1)
			switch (tpeek(0)) {
			  case REDIR:
				if (iopn >= NUFILE)
					yyerror("too many redirections");
				iops[iopn++] = synio(0);
				break;

			  case LWORD:
				ACCEPT;
				if ((XPsize(args) == 0 || flag[FKEYWORD])
				    && strchr(ident+1, '='))
					{XPput(vars, yylval.cp);}
				else
					{XPput(args, yylval.cp);}
				break;

			  case MPAREN:
				ACCEPT;
				if (XPsize(args) != 1)
					SYNTAXERR;
				if (*ident == 0)
					yyerror("invalid function name\n");
				t = newtp(TFUNCT);
				t->str = strsave(ident, ATEMP);
				musthave('{', CONTIN|KEYWORD);
				t->left = nested(TBRACE, '}');
				return t;

			  default:
				goto Leave;
			}
	  Leave:
		break;

	  case '(':
		t = nested(TPAREN, ')');
		break;

	  case '{':
		t = nested(TBRACE, '}');
		break;

	  case FOR:
		t = newtp(TFOR);
		musthave(LWORD, 0);
		t->str = strsave(ident, ATEMP);
		multiline++;
		t->vars = wordlist();
		t->left = dogroup(0);
		multiline--;
		break;

	  case WHILE:
	  case UNTIL:
		multiline++;
		t = newtp((c == WHILE) ? TWHILE: TUNTIL);
		t->left = c_list();
		t->right = dogroup(1);
		multiline--;
		break;

	  case CASE:
		t = newtp(TCASE);
		musthave(LWORD, 0);
		t->str = yylval.cp;
		multiline++;
		musthave(IN, KEYWORD|CONTIN);
		t->left = caselist();
		musthave(ESAC, KEYWORD);
		multiline--;
		break;

	  case IF:
		multiline++;
		t = newtp(TIF);
		t->left = c_list();
		t->right = thenpart();
		musthave(FI, KEYWORD);
		multiline--;
		break;

	  case TIME:
		t = pipeline(CONTIN);
		t = block(TTIME, t, NOBLOCK, NOWORDS);
		break;

	  case FUNCTION:
		t = newtp(TFUNCT);
		musthave(LWORD, 0);
		t->str = strsave(ident, ATEMP);
		musthave('{', CONTIN|KEYWORD);
		t->left = nested(TBRACE, '}');
		break;

#if 0
	  case MDPAREN:
		t = newtp(TCOM);
		XPput(args, "let");
		musthave(LWORD, LETEXPR);
		XPput(args, yylval.cp);
		while (tpeek(0) == REDIR) {
			if (iopn >= NUFILE)
				yyerror("too many redirections");
			iops[iopn++] = synio(0);
		}
		break;
#endif
	}

	while ((iop = synio(0)) != NULL) {
		if (iopn >= NUFILE)
			yyerror("too many redirections");
		iops[iopn++] = iop;
	}

	if (iopn == 0) {
		afree((void*) iops, ATEMP);
		t->ioact = NULL;
	} else {
		iops[iopn++] = NULL;
		aresize((void*) iops, sizeofN(struct ioword *, iopn), ATEMP);
		t->ioact = iops;
	}

	if (t->type == TCOM) {
		XPput(args, NULL);
		t->args = (char **) XPclose(args);
		XPput(vars, NULL);
		t->vars = (char **) XPclose(vars);
	} else {
		XPfree(args);
		XPfree(vars);
	}

	return t;
}

static struct op *
dogroup(onlydone)
	int onlydone;
{
	register int c;
	register struct op *list;

	c = token(CONTIN|KEYWORD);
	if (c == DONE && onlydone)
		return NULL;
	if (c != DO)
		SYNTAXERR;
	list = c_list();
	musthave(DONE, KEYWORD);
	return list;
}

static struct op *
thenpart()
{
	register int c;
	register struct op *t;

	if ((c = token(0)) != THEN) {
		REJECT;
		return NULL;
	}
	t = newtp(0);
	t->left = c_list();
	if (t->left == NULL)
		SYNTAXERR;
	t->right = elsepart();
	return (t);
}

static struct op *
elsepart()
{
	register int c;
	register struct op *t;

	switch (c = token(0)) {
	  case ELSE:
		if ((t = c_list()) == NULL)
			SYNTAXERR;
		return (t);

	  case ELIF:
		t = newtp(TELIF);
		t->left = c_list();
		t->right = thenpart();
		return (t);

	  default:
		REJECT;
		return NULL;
	}
}

static struct op *
caselist()
{
	register struct op *t, *tl;

	t = tl = NULL;
	while ((tpeek(CONTIN|KEYWORD)) != ESAC) {
		struct op *tc = casepart();
		if (tl == NULL)
			t = tl = tc, tl->right = NULL;
		else
			tl->right = tc, tl = tc;
	}
	return (t);
}

static struct op *
casepart()
{
	register struct op *t;
	register int c, cf;
	XPtrV ptns;

	XPinit(ptns, 16);
	t = newtp(TPAT);
	cf = CONTIN|KEYWORD;
	c = token(cf);
	if (c != '(')
		REJECT;
	else
		cf = 0;
	do {
		musthave(LWORD, cf);
		XPput(ptns, yylval.cp);
		cf = 0;
	} while ((c = token(0)) == '|');
	REJECT;
	XPput(ptns, NULL);
	t->vars = (char **) XPclose(ptns);
	musthave(')', 0);

	t->left = c_list();
	if ((tpeek(CONTIN|KEYWORD)) != ESAC)
		musthave(BREAK, CONTIN|KEYWORD);
	return (t);
}

static char **
wordlist()
{
	register int c;
	XPtrV args;

	XPinit(args, 16);
	if ((c = token(CONTIN|KEYWORD)) != IN) {
		REJECT;
		return NULL;
	}
	while ((c = token(0)) == LWORD)
		XPput(args, yylval.cp);
	if (c != '\n' && c != ';')
		SYNTAXERR;
	if (XPsize(args) == 0) {
		XPfree(args);
		return NULL;
	} else {
		XPput(args, NULL);
		return (char **) XPclose(args);
	}
}

/*
 * supporting functions
 */

static struct op *
block(type, t1, t2, wp)
	struct op *t1, *t2;
	char **wp;
{
	register struct op *t;

	t = newtp(type);
	t->left = t1;
	t->right = t2;
	t->vars = wp;
	return (t);
}

const	struct res {
	char	*name;
	int	val;
} restab[] = {
	"for",		FOR,
	"case",		CASE,
	"esac",		ESAC,
	"while",	WHILE,
	"do",		DO,
	"done",		DONE,
	"if",		IF,
	"in",		IN,
	"then",		THEN,
	"else",		ELSE,
	"elif",		ELIF,
	"until",	UNTIL,
	"fi",		FI,
	"function",	FUNCTION,
	"time",		TIME,
	"{",		'{',
	"}",		'}',
	0
};

keywords()
{
	register struct res const *rp;
	register struct tbl *p;

	for (rp = restab; rp->name; rp++) {
		p = tenter(&lexicals, rp->name, hash(rp->name));
		p->flag |= DEFINED|ISSET;
		p->type = CKEYWD;
		p->val.i = rp->val;
	}
}

static struct op *
newtp(type)
	int type;
{
	register struct op *t;

	t = (struct op *) alloc(sizeof(*t), ATEMP);
	t->type = type;
	t->args = t->vars = NULL;
	t->ioact = NULL;
	t->left = t->right = NULL;
	t->str = NULL;
	return (t);
}

static void
zzerr()
{
	yyerror("syntax error");
}

struct op *
compile(s)
	Source *s;
{
	yynerrs = 0;
	multiline = 0;
	herep = heres;
	source = s;
	if (yyparse())
		unwind();
	if (s->type == STTY || s->type == SFILE || s->type == SHIST)
		s->str = null;	/* line is not preserved */
	return outtree;
}

#pragma pop_macro("RCSid")
#pragma pop_macro("tpeek")
#pragma pop_macro("token")
#pragma pop_macro("command")
#pragma pop_macro("REJECT")
#pragma pop_macro("ACCEPT")

#pragma push_macro("NULLSTR")
#pragma push_macro("getsc")
#pragma push_macro("ungetsc")
#pragma push_macro("RCSid")
#define RCSid RCSid_lex
#line 1 "lex.c"
/*
 * lexical analysis and source input
 */

#ifndef lint
static char *RCSid = "$Id: lex.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <setjmp.h>
#include <unistd.h>
#include <assert.h>

	int	ttyfd = -1;		/* tty fd for edit and jobs */
	char   *history[HISTORY];	/* saved commands */
	char  **histptr = history - 1;	/* last history item */
	int	histpush;		/* number of pushed fc commands */

/* we set s->str to NULLSTR instead of "", so that ungetsc() works */
static	char	nullstr [] = {0, 0};
#define	NULLSTR	(nullstr + 1)

static	int	expanding_alias;
static	int	alias;

static void     readhere    ARGS((struct ioword *iop));
static int      getsc_      ARGS((void));

/* optimized getsc_() */
#define	getsc()	((*source->str != 0) ? *source->str++ : getsc_())
#define	ungetsc() (source->str--)

/*
 * Lexical analyzer
 *
 * tokens are not regular expressions, they are LL(1).
 * for example, "${var:-${PWD}}", and "$(size $(whence ksh))".
 * hence the state stack.
 */

int
yylex(cf)
	int cf;
{
	register int c, state;
	char states [64], *statep = states;
	XString ws;		/* expandable output word */
	register char *wp;	/* output word pointer */
	register char *sp, *dp;
	int istate;
	int c2;
	static int rec_alias_cnt = 0;
	static struct tbl *rec_alias_table[20];


	if (expanding_alias) {
		expanding_alias = 0;
		while (rec_alias_cnt-- > 0)
			rec_alias_table[rec_alias_cnt]->flag &= ~EXPALIAS;
		rec_alias_cnt = 0;
	}
  Again:
	Xinit(ws, wp, 64);

	if (cf&ONEWORD)
		istate = SWORD;
	else if (cf&LETEXPR)
		istate = SDPAREN;
	else {			/* normal lexing */
		istate = SBASE;
		while ((c = getsc()) == ' ' || c == '\t')
			;
		if (c == '#')
			while ((c = getsc()) != 0 && c != '\n')
				;
		ungetsc();
	}
	if (alias) {			/* trailing ' ' in alias definition */
		alias = 0;
		cf |= ALIAS;
	}

	/* collect non-special or quoted characters to form word */
	for (*statep = state = istate;
	     !((c = getsc()) == 0 || (state == SBASE && ctype(c, C_LEX1))); ) {
		Xcheck(ws, wp);
		switch (state) {
		  case SBASE:
		  Sbase:
			switch (c) {
			  case '\\':
				c = getsc();
				if (c != '\n')
					*wp++ = QCHAR, *wp++ = c;
				else
					if (wp == Xstring(ws, wp))
						goto Again;
				break;
			  case '\'':
				*++statep = state = SSQUOTE;
				*wp++ = OQUOTE;
				break;
			  case '"':
				*++statep = state = SDQUOTE;
				*wp++ = OQUOTE;
				break;
			  default:
				goto Subst;
			}
			break;

		  Subst:
			switch (c) {
			  case '\\':
				c = getsc();
				switch (c) {
				  case '\n':
					break;
				  case '"': case '\\':
				  case '$': case '`':
					*wp++ = QCHAR, *wp++ = c;
					break;
				  default:
					Xcheck(ws, wp);
					*wp++ = CHAR, *wp++ = '\\';
					*wp++ = CHAR, *wp++ = c;
					break;
				}
				break;
			  case '$':
				c = getsc();
				if (c == '(') {
					*++statep = state = SPAREN;
					*wp++ = COMSUB;
				} else
				if (c == '{') {
					*++statep = state = SBRACE;
					*wp++ = OSUBST;
					c = getsc();
					do {
						Xcheck(ws, wp);
						*wp++ = c;
						c = getsc();
					} while (ctype(c, C_ALPHA|C_DIGIT));
					*wp++ = 0;
					/* todo: more compile-time checking */
					if (c == '}')
						ungetsc();
					else if (c == '#' || c == '%') {
						/* Korn pattern trimming */
						if (getsc() == c)
							c |= 0x80;
						else
							ungetsc();
						*wp++ = c;
					} else if (c == ':')
						*wp++ = 0x80|getsc();
					else
						*wp++ = c;
				} else if (ctype(c, C_ALPHA)) {
					*wp++ = OSUBST;
					do {
						Xcheck(ws, wp);
						*wp++ = c;
						c = getsc();
					} while (ctype(c, C_ALPHA|C_DIGIT));
					*wp++ = 0;
					*wp++ = CSUBST;
					ungetsc();
				} else if (ctype(c, C_DIGIT|C_VAR1)) {
					Xcheck(ws, wp);
					*wp++ = OSUBST;
					*wp++ = c;
					*wp++ = 0;
					*wp++ = CSUBST;
				} else {
					*wp++ = CHAR, *wp++ = '$';
					ungetsc();
				}
				break;
			  case '`':
				*++statep = state = SBQUOTE;
				*wp++ = COMSUB;
				break;
			  default:
				*wp++ = CHAR, *wp++ = c;
			}
			break;

		  case SSQUOTE:
			if (c == '\'') {
				state = *--statep;
				*wp++ = CQUOTE;
			} else
				*wp++ = QCHAR, *wp++ = c;
			break;

		  case SDQUOTE:
			if (c == '"') {
				state = *--statep;
				*wp++ = CQUOTE;
			} else
				goto Subst;
			break;

		  case SPAREN:
			if (c == '(')
				*++statep = state;
			else if (c == ')')
				state = *--statep;
			if (state == SPAREN)
				*wp++ = c;
			else
				*wp++ = 0; /* end of COMSUB */
			break;

		  case SBRACE:
			if (c == '}') {
				state = *--statep;
				*wp++ = CSUBST;
			} else
				goto Sbase;
			break;

		  case SBQUOTE:
			if (c == '`') {
				*wp++ = 0;
				state = *--statep;
			} else if (c == '\\') {
				switch (c = getsc()) {
				  case '\n':
					break;
				  case '\\':
				  case '$': case '`':
					*wp++ = c;
					break;
				  default:
					*wp++ = '\\';
					*wp++ = c;
					break;
				}
			} else
				*wp++ = c;
			break;

		  case SWORD:	/* ONEWORD */
			goto Subst;

		  case SDPAREN:	/* LETEXPR */
			if (c == ')') {
				if (getsc() == ')') {
					c = 0;
					goto Done;
				} else
					ungetsc();
			}
			goto Subst;
		}
	}
Done:
	Xcheck(ws, wp);
	if (state != istate)
		yyerror("no closing quote");

	if (c == '<' || c == '>') {
		char *cp = Xstring(ws, wp);
		if (wp > cp && cp[0] == CHAR && digit(cp[1])) {
			wp = cp; /* throw away word */
			c2/*unit*/ = cp[1] - '0';
		} else
			c2/*unit*/ = c == '>'; /* 0 for <, 1 for > */
	}

	if (wp == Xstring(ws, wp) && state == SBASE) {
		Xfree(ws, sp);	/* free word */
		/* no word, process LEX1 character */
		switch (c) {
		  default:
			return c;

		  case '|':
		  case '&':
		  case ';':
			if (getsc() == c)
				c = (c == ';') ? BREAK :
				    (c == '|') ? LOGOR :
				    (c == '&') ? LOGAND :
				    YYERRCODE;
			else
				ungetsc();
			return c;

		  case '>':
		  case '<': {
			register struct ioword *iop;

			iop = (struct ioword *) alloc(sizeof(*iop), ATEMP);
			iop->unit = c2/*unit*/;

			c2 = getsc();
			if (c2 == '>' || c2 == '<') {
				iop->flag = c != c2 ? IORDWR : c == '>' ? IOCAT : IOHERE;
				c2 = getsc();
			} else
				iop->flag = c == '>' ? IOWRITE : IOREAD;

			if (iop->flag == IOHERE)
				if (c2 == '-')
					iop->flag |= IOSKIP;
				else
					ungetsc();
			else
				if (c2 == '&')
					iop->flag = IODUP;
				else if (c2 == '!' && iop->flag == IOWRITE)
					iop->flag |= IOCLOB;
				else
					ungetsc();
			yylval.iop = iop;
			return REDIR;
		    }
		  case '\n':
			gethere();
			if (cf & CONTIN)
				goto Again;
			return c;

		  case '(':
			c2 = getsc();
			if (c2 == ')')
				c = MPAREN;
			else if (c2 == '(')
				c = MDPAREN;
			else
				ungetsc();
		  case ')':
			return c;
		}
	}

	*wp++ = EOS;		/* terminate word */
	yylval.cp = Xclose(ws, wp);
	if (state == SWORD || state == SDPAREN)	/* ONEWORD? */
		return LWORD;
	ungetsc();		/* unget terminator */

	/* copy word to unprefixed string ident */
	for (sp = yylval.cp, dp = ident; dp < ident+IDENT && (c = *sp++) == CHAR; )
		*dp++ = *sp++;
	/* Make sure the ident array stays '\0' padded */
	while (dp <= ident+IDENT)
		*dp++ = '\0';
#if 0
	if (*ident == '~' || (dp = strchr(ident, '=')) != NULL && dp[1] == '~')
		"Tilde expansion";
#endif
	if (c != EOS)
		*ident = 0;	/* word is not unquoted */

	if (*ident != 0 && (cf&(KEYWORD|ALIAS))) {
		register struct tbl *p;

		p = tsearch(&lexicals, ident, hash(ident));
		if (p != NULL && (p->flag&ISSET))
			if (p->type == CKEYWD && (cf&KEYWORD)) {
				afree(yylval.cp, ATEMP);
				return p->val.i;
			} else if (p->type == CALIAS && (cf&ALIAS) &&
				   !(p->flag&EXPALIAS)) {
				register Source *s;

				if (rec_alias_cnt == sizeof(rec_alias_table)/sizeof(rec_alias_table[0]))
					yyerror("excessive recusrsive aliasing");
				else
					rec_alias_table[rec_alias_cnt++] = p;
				p->flag |= EXPALIAS;
				/* check for recursive aliasing */
				for (s = source; s->type == SALIAS; s = s->next)
					if (s->u.tblp == p)
						return LWORD;
				afree(yylval.cp, ATEMP);

				/* push alias expansion */
				s = pushs(SALIAS);
				s->str = p->val.s;
				s->u.tblp = p;
				s->next = source;
				source = s;
				goto Again;
			} 
	}

	return LWORD;
}

static void readhere();

gethere()
{
	register struct ioword **p;

	for (p = heres; p < herep; p++)
		readhere(*p);
	herep = heres;
}

/*
 * read "<<word" text into temp file
 * todo: set up E_ERR to fclose(f) on unwind
 */

static void
readhere(iop)
	register struct ioword *iop;
{
	register FILE *f;
	struct temp *h;
	register int c;
	char *eof;
	register char *cp;
	char line [LINE+1];

	eof = evalstr(iop->name, 0);

	h = maketemp(ATEMP);
	h->next = e.temps; e.temps = h;
	iop->name = h->name;
	f = fopen(h->name, "w");
	if (f == NULL)
		errorf("Cannot create temporary file\n");
	setvbuf(f, (char *)NULL, _IOFBF, BUFSIZ);

	for (;;) {
		cp = line;
		while ((c = getsc()) != '\n') {
			if (c == 0)
				errorf("here document `%s' unclosed\n", eof);
			if (cp >= line+LINE)
				break;
			*cp++ = c;
		}
		ungetsc();
		*cp = 0;
		for (cp = line; iop->flag&IOSKIP && *cp == '\t'; cp++)
			;
		if (strcmp(eof, cp) == 0 || c == 0)
			break;
		while ((c = *cp++) != '\0')
			putc(c, f);
		while ((c = getsc()) != '\n') {
			if (c == 0)
				errorf("here document `%s' unclosed\n", eof);
			putc(c, f);
		}
		putc(c, f);
	}
	fclose(f);
}

void
yyerror(msg)
	const char *msg;
{
	yynerrs++;
	while (source->type == SALIAS) /* pop aliases */
		source = source->next;
	if (source->file != NULL)
		shellf("%s[%d]: ", source->file, source->line);
	source->str = NULLSTR;	/* zap pending input */
	errorf("%s\n", msg);
}

/*
 * input for yylex with alias expansion
 */

Source *
pushs(type)
	int type;
{
	register Source *s;

	s = (Source *) alloc(sizeof(Source), ATEMP);
	s->type = type;
	s->str = NULLSTR;
	s->line = 0;
	s->file = NULL;
	s->echo = 0;
	s->next = NULL;
	return s;
}

static int
getsc_()
{
	register Source *s = source;
	register int c;
	extern void	mprint();
	
	while ((c = *s->str++) == 0) {
		s->str = NULL;		/* return 0 for EOF by default */
		switch (s->type) {
		  case SEOF:
			s->str = NULLSTR;
			return 0;

		  case STTY:
			if (histpush < 0) {	/* commands pushed by dofc */
				s->type = SHIST;
				s->str = NULLSTR;
				continue;
			}
			s->line++;
			s->str = line;
			line[0] = '\0';
			mprint();
			pprompt(prompt);
			flushshf(1);	flushshf(2);
			/*
			 * This allows the arival of a SIGCHLD 
			 * to not disturb us until we are ready. 
			 * BSD and other systems that 
			 * automatically rety a read after an 
			 * interrupt don't need this but it 
			 * doesn't do any harm either.
			 */
		      retry:
#ifdef EDIT
#ifdef EMACS
			if (flag[FEMACS])
				c = x_read(ttyfd, line, LINE);
			else
#endif
#ifdef VI
			if (flag[FVI])
				c = x_read(ttyfd, line, LINE);
			else
#endif
#endif
				c = read(ttyfd, line, LINE);
			if (c < 0 && sigchld_caught)
			{
			  goto retry;
			}
			if (c < 0)	/* read error */
				c = 0;
			line[c] = '\0';
			prompt = strval(global("PS2"));
			if (c == 0) { /* EOF */
				s->str = NULL;
				s->line--;
			} else {
				c = 0;
				while(line[c] && ctype(line[c], C_IFS))
					c++;
				if (!line[c]) {
					s->str = &line[c - 1];
					s->line--;
				} else {
					s->str = &line[c];
					histsave(s->str);
				}
			}
			break;

		  case SHIST:
			if (histpush == 0) {
				s->type = STTY;
				s->str = NULLSTR;
				continue;
			}
			s->line++;
			s->str = histptr[++histpush];
#if 0
			pprompt("!< ");	/* todo: PS9 */
#endif
			shellf("%s\n", s->str);
			strcpy(line, s->str);
			s->str = strchr(line, 0);
			*s->str++ = '\n';
			*s->str = 0;
			s->str = line;
			break;

		  case SFILE:
			s->line++;
			s->str = fgets(line, LINE, s->u.file);
			if (s->str == NULL)
				if (s->u.file != stdin)
					fclose(s->u.file);
			break;

		  case SWSTR:
			break;

		  case SSTRING:
			s->str = "\n";
			s->type = SEOF;
			break;

		  case SWORDS:
			s->str = *s->u.strv++;
			s->type = SWORDSEP;
			break;

		  case SWORDSEP:
			if (*s->u.strv == NULL) {
				s->str = "\n";
				s->type = SEOF;
			} else {
				s->str = " ";
				s->type = SWORDS;
			}
			break;

		  case SALIAS:
			s->str = s->u.tblp->val.s;
			if (s->str[0] != 0) {
				c = strchr(s->str, 0)[-1];
				if (c == ' ' || c == '\t')
					alias = 1;	/* trailing ' ' */
			}
			source = s = s->next;
			expanding_alias = 1;
			continue;
		}
		if (s->str == NULL) {
			s->type = SEOF;
			s->str = NULLSTR;
			return 0;
		}
		if (s->echo)
			fputs(s->str, shlout);
	}
	return c;
}

pprompt(cp)
	register char *cp;
{
	while (*cp != 0)
		if (*cp != '!')
			putc(*cp++, shlout);
		else
			if (*++cp == '!')
				putc(*cp++, shlout);
			else
				shellf("%d", source->line);
	fflush(shlout);
}
#pragma pop_macro("RCSid")
#pragma pop_macro("ungetsc")
#pragma pop_macro("getsc")
#pragma pop_macro("NULLSTR")

#pragma push_macro("BEL")
#pragma push_macro("EXTERN")
#pragma push_macro("EXTERN_DEFINED")
#pragma push_macro("NTTYDISC")
#pragma push_macro("TIOCGETD")
#pragma push_macro("TIOCSETD")
#pragma push_macro("TIOCSETN")
#pragma push_macro("TIOCSPGRP")
#pragma push_macro("TIOCSTI")
#pragma push_macro("_D_")
#pragma push_macro("_I_")
#pragma push_macro("RCSid")
#define RCSid RCSid_edit
#line 1 "edit.c"
/*
 * Command line editing - common code
 *
 */

#if defined(EMACS) || defined(VI)

#ifndef lint
static char *RCSid = "$Id: edit.c,v 1.4 1992/05/12 09:30:31 sjg Exp $";
#endif

#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <setjmp.h>
#ifndef NOSTDHDRS
# include <string.h>
#endif
/* begin inlined tty.h from edit.c */
/*
	tty.h -- centralized definitions for a variety of terminal interfaces

	created by DPK, Oct. 1986

	last edit:	30-Jul-1987	D A Gwyn
*/

#if _BSD_SYSV			/* BRL UNIX System V emulation */
#include <termio.h>	/* includes <sys/_ioctl.h> */
#ifndef NTTYDISC
#define	TIOCGETD	_IOR( 't', 0, int )
#define	TIOCSETD	_IOW( 't', 1, int )
#define	NTTYDISC	2
#endif
#ifndef TIOCSTI
#define	TIOCSTI		_IOW( 't', 114, char )
#endif
#ifndef TIOCSPGRP
#define	TIOCSPGRP	_IOW( 't', 118, int )
#endif
#else	/* !_BSD_SYSV */
#if _BSD
#ifdef _MINIX
#include <sgtty.h>
#define TIOCSETN	TIOCSETP
#else
#include <sys/ioctl.h>
#endif
#else
#ifdef	mips
#include <termios.h>
#else
#include <termio.h>
#endif
#endif
#endif	/* _BSD_SYSV */
/* end inlined tty.h from edit.c */
#define EXTERN
/* begin inlined edit.h from edit.c */
/* NAME:
 *      edit.h - globals for edit modes
 *
 * DESCRIPTION:
 *      This header defines various global edit objects.
 *
 * SEE ALSO:
 *      
 *
 * RCSid:
 *      $Id: edit.h,v 1.2 1992/04/25 08:33:28 sjg Exp $
 *
 */

/* some useful #defines */
#ifdef EXTERN
# define _I_(i) = i
#else
# define _I_(i)
# define EXTERN extern
# define EXTERN_DEFINED
#endif

#define	BEL		0x07

/*
 * The following are used for my horizontal scrolling stuff
 */
EXTERN	char   *xbuf;		/* beg input buffer */
EXTERN	char   *xend;		/* end input buffer */
EXTERN char    *xcp;		/* current position */
EXTERN char    *xep;		/* current end */
EXTERN char    *xbp;		/* start of visible portion of input buffer */
EXTERN char    *xlp;		/* last char visible on screen */
EXTERN int	x_adj_ok;
/*
 * we use x_adj_done so that functions can tell 
 * whether x_adjust() has been called while they are active.
 */
EXTERN int	x_adj_done;

EXTERN int	x_cols;
EXTERN int	x_col;
EXTERN int	x_displen;
EXTERN int	x_arg;		/* general purpose arg */

EXTERN int	x_do_init;		/* set up tty modes */
EXTERN int	ed_erase, ed_kill, ed_werase, ed_intr, ed_quit;

#ifdef DEBUG
# define _D_(x) x
#else
# define _D_(x)
#endif

/****  edit.c  ****/
int             x_read      ARGS((int fd, char *buf, size_t len));
int             x_getc      ARGS((void));
void            x_flush     ARGS((void));
void            x_adjust    ARGS((void));
void            x_putc      ARGS((int c));
int             x_debug_info ARGS((void));
void            x_puts      ARGS((char *s));
void            x_init      ARGS((void));
bool_t          x_mode      ARGS((bool_t onoff));
bool_t          x_mode      ARGS((bool_t onoff));
int             promptlen   ARGS((char *cp));

/****  emacs.c  ****/
void            x_redraw    ARGS((int limit));
char*		x_lastcp    ARGS((void));
EXTERN int xlp_valid _I_(0);
  
/* This lot goes at the END */
/* be sure not to interfere with anyone else's idea about EXTERN */
#ifdef EXTERN_DEFINED
# undef EXTERN_DEFINED
# undef EXTERN
#endif
/*
 * Local Variables:
 * version-control:t
 * comment-column:40
 * End:
 */
/* end inlined edit.h from edit.c */
#undef EXTERN

#ifdef _CRAY2
extern unsigned	sleep();
#endif


static int	x_noecho = 0;

/*
 * read an edited command line
 */
int
x_read(fd, buf, len)
	int fd;			/* not used */
	char *buf;
	size_t len;
{
  static int setup_done = 0;
	int	i;

  if (setup_done != 42)
  {
    setup_done = 42;		/* these get done once only */
    x_do_init = 1;
    x_cols = 80;
    x_col = 0;
    ed_erase = -1, ed_kill = -1, ed_werase = -1, ed_intr = -1, ed_quit = -1;
    x_adj_ok = 1;
    x_adj_done = 0;
  }
	if (x_do_init)
		x_init();

	if (x_noecho)
		return(read(ttyfd, buf, len));

	(void)x_mode(TRUE);
#ifdef EMACS
	if (flag[FEMACS])
		i = x_emacs(buf, len);
	else
#endif
#ifdef VI
	if (flag[FVI])
		i = x_vi(buf, len);
	else
#endif
		i = -1;		/* internal error */
	(void) x_mode(FALSE);
	if (i > 4 && strstr(buf, "stty"))
		x_do_init = 1;
	if (i < 0 && errno == EINTR)
		trapsig(SIGINT);
	return i;
}

/* tty I/O */

int
x_getc()
{
  char c;

  /*
   * This allows the arival of a SIGCHLD to not disturb us until 
   * we are ready. 
   * BSD and other systems that automatically rety a read after 
   * an interrupt don't need this but it doesn't do any harm 
   * either. 
   */
 retry:
	if (read(ttyfd, &c, 1) != 1)
	{
	  if (sigchld_caught)		/* just a SIGCHLD ? */
	  {
	    goto retry;
	  }
	  return -1;
	}
	return c & 0x7F;
}

void
x_flush()
{
	fflush(stdout);
}


/* NAME:
 *      x_adjust - redraw the line adjusting starting point etc.
 *
 * DESCRIPTION:
 *      This function is called when we have exceeded the bounds 
 *      of the edit window.  It increments x_adj_done so that 
 *      functions like x_ins and x_delete know that we have been 
 *      called and can skip the x_bs() stuff which has already 
 *      been done by x_redraw.
 *
 * RETURN VALUE:
 *      None
 */

void
x_adjust()
{
  x_adj_done++;			/* flag the fact that we were called. */
#ifdef EMACS
  /*
   * we had a promblem if the prompt length > x_cols / 2
   */
  if ((xbp = xcp - (x_displen / 2)) < xbuf)
    xbp = xbuf;
  xlp_valid = FALSE;
  x_redraw(x_cols);
#endif
  x_flush();
}

void
x_putc(c)
	int c;
{
  if (c == '\r' || c == '\n')
    x_col = 0;
  if (x_col < x_cols)
  {
    putc(c, stdout);
    switch(c)
    {
    case BEL:
      break;
    case '\r':
    case '\n':
    break;
    case '\b':
      x_col--;
      break;
    default:
      x_col++;
      break;
    }
  }
  if (x_adj_ok && (x_col < 0 || x_col >= (x_cols - 2)))
  {
    x_adjust();
  }
}

#ifdef DEBUG
int
x_debug_info()
{
  x_flush();
  printf("\nksh debug:\n");
  printf("\tx_col == %d,\t\tx_cols == %d,\tx_displen == %d\n",
	 x_col, x_cols, x_displen);
  printf("\txcp == 0x%lx,\txep == 0x%lx\n", (long) xcp, (long) xep);
  printf("\txbp == 0x%lx,\txbuf == 0x%lx\n", (long) xbp, (long) xbuf);
  printf("\txlp == 0x%lx\n", (long) xlp);
  printf("\txlp == 0x%lx\n", (long) x_lastcp());
  printf("\n");
  x_redraw(-1);
  return 0;
}
#endif

void
x_puts(s)
	register char *s;
{
  register int	adj = x_adj_done;

  while (*s && adj == x_adj_done)
    x_putc(*s++);
}

#ifdef _BSD
static	struct sgttyb cb, cborig;
#ifdef TIOCGATC
static struct ttychars lchars, lcharsorig;
#else
static struct tchars tchars, tcharsorig;
#ifdef TIOCGLTC
static struct ltchars ltchars, ltcharsorig;
#endif
#endif
#else
static	struct termio cb, cborig;
#endif

/* initialize editing mode */
void
x_init()
{
	x_do_init = 0;
#ifdef _BSD
	(void)ioctl(ttyfd, TIOCGETP, &cborig);
	if ((cborig.sg_flags & ECHO) == 0)
		x_noecho = 1;
	cb = cborig;
	ed_erase = cb.sg_erase;
	ed_kill = cb.sg_kill;
	cb.sg_flags &= ~ECHO;
	cb.sg_flags |= CBREAK;
#ifdef TIOCGATC
	(void)ioctl(ttyfd, TIOCGATC, &lcharsorig);
	lchars = lcharsorig;
	ed_werase = lchars.tc_werasc;
	lchars.tc_suspc = -1;
	lchars.tc_dsuspc = -1;
	lchars.tc_lnextc = -1;
	lchars.tc_statc = -1;
	lchars.tc_intrc = -1;
	lchars.tc_quitc = -1;
	lchars.tc_rprntc = -1;
#else
	(void)ioctl(ttyfd, TIOCGETC, &tcharsorig);
#ifdef TIOCGLTC
	(void)ioctl(ttyfd, TIOCGLTC, &ltcharsorig);
#endif
	tchars = tcharsorig;
#ifdef TIOCGLTC
	ltchars = ltcharsorig;
	ed_werase = ltchars.t_werasc;
	ltchars = ltcharsorig;
	ltchars.t_suspc = -1;
	ltchars.t_dsuspc = -1;
	ltchars.t_lnextc = -1;
#endif
	tchars.t_intrc = -1;
	tchars.t_quitc = -1;
#ifdef TIOCGLTC
	ltchars.t_rprntc = -1;
#endif
#endif
#else /* !_BSD */
	(void)ioctl(ttyfd, TCGETA, &cborig);
	if ((cborig.c_lflag & ECHO) == 0)
		x_noecho = 1;
	cb = cborig;
	ed_erase = cb.c_cc[VERASE]; /* TODO */
	ed_kill = cb.c_cc[VKILL]; /* TODO */
	ed_intr = cb.c_cc[VINTR];
	ed_quit = cb.c_cc[VQUIT];
#ifdef _CRAY2		/* brain-damaged terminal handler */
	cb.c_lflag &= ~(ICANON|ECHO);
	/* rely on print routine to map '\n' to CR,LF */
#else
	cb.c_iflag &= ~(INLCR|ICRNL);
#ifdef _BSD_SYSV	/* need to force CBREAK instead of RAW (need CRMOD on output) */
	cb.c_lflag &= ~(ICANON|ECHO);
#else
#ifdef SWTCH	/* need CBREAK to handle swtch char */
	cb.c_lflag &= ~(ICANON|ECHO);
	cb.c_lflag |= ISIG;
	cb.c_cc[VINTR] = 0377;
	cb.c_cc[VQUIT] = 0377;
#else
	cb.c_lflag &= ~(ISIG|ICANON|ECHO);
#endif
#endif
	cb.c_cc[VTIME] = 0;
	cb.c_cc[VMIN] = 1;
#endif	/* _CRAY2 */
#endif
#ifdef EMACS
	x_emacs_keys(ed_erase, ed_kill, ed_werase, ed_intr, ed_quit);
#endif
}

static	bool_t	x_cur_mode = FALSE;

/* set/clear tty cbreak mode */

#ifdef _BSD
bool_t
x_mode(onoff)
	bool_t	onoff;
{
	bool_t	prev;

	if (x_cur_mode == onoff) return x_cur_mode;
	prev = x_cur_mode;
	x_cur_mode = onoff;
	if (onoff)  {
		(void)ioctl(ttyfd, TIOCSETN, &cb);
#ifdef TIOCGATC
		(void)ioctl(ttyfd, TIOCSATC, &lchars);
#else
		(void)ioctl(ttyfd, TIOCSETC, &tchars);
#ifdef TIOCGLTC
		(void)ioctl(ttyfd, TIOCSLTC, &ltchars);
#endif
#endif
	}
	else {
		(void)ioctl(ttyfd, TIOCSETN, &cborig);
#ifdef TIOCGATC
		(void)ioctl(ttyfd, TIOCSATC, &lcharsorig);
#else
		(void)ioctl(ttyfd, TIOCSETC, &tcharsorig);
#ifdef TIOCGLTC
		(void)ioctl(ttyfd, TIOCSLTC, &ltcharsorig);
#endif
#endif
	}
	return prev;
}

#else	/* !_BSD */

bool_t
x_mode(onoff)
bool_t	onoff;
{
	bool_t	prev;

	if (x_cur_mode == onoff) return x_cur_mode;
	prev = x_cur_mode;
	x_cur_mode = onoff;

	if (onoff)  {
#ifndef TCSETAW				/* e.g. Cray-2 */
		/* first wait for output to drain */
#ifdef TCSBRK
		(void)ioctl(ttyfd, TCSBRK, 1);
#else	/* the following kludge is minimally intrusive, but sometimes fails */
		(void)sleep((unsigned)1);	/* fake it */
#endif
#endif
#if defined(_BSD_SYSV) || !defined(TCSETAW)
/* _BSD_SYSV needs to force TIOCSETN instead of TIOCSETP (preserve type-ahead) */
		(void)ioctl(ttyfd, TCSETA, &cb);
#else
		(void)ioctl(ttyfd, TCSETAW, &cb);
#endif
	}
	else {
#ifndef TCSETAW				/* e.g. Cray-2 */
		/* first wait for output to drain */
#ifdef TCSBRK
		(void)ioctl(ttyfd, TCSBRK, 1);
#else
/* doesn't seem to be necessary when leaving xmode */
/*		(void)sleep((unsigned)1);	/* fake it */
#endif
#endif
#if defined(_BSD_SYSV) || !defined(TCSETAW)
/* _BSD_SYSV needs to force TIOCSETN instead of TIOCSETP (preserve type-ahead) */
		(void)ioctl(ttyfd, TCSETA, &cborig);
#else
		(void)ioctl(ttyfd, TCSETAW, &cborig);
#endif
	}
	return prev;
}
#endif	/* _BSD */


/* NAME:
 *      promptlen - calculate the length of PS1 etc.
 *
 * DESCRIPTION:
 *      This function is based on a fix from guy@demon.co.uk
 *      It fixes a bug in that if PS1 contains '!', the length 
 *      given by strlen() is probably wrong.
 *
 * RETURN VALUE:
 *      length
 */
 
int
promptlen(cp)
  register char  *cp;
{
  register int count = 0;

  while (*cp)
  {
    if ( *cp++ != '!' )
      count++;
    else
      if ( *cp == '!' )
      {
	cp++;
	count++;
      }
      else
      {
	register int i = source->line;

	do
	{
	  count ++;
	}
	while( ( i /= 10 ) > 0 );
      }
  }
  return count;
}


/*
 * this function check the environment
 * for FCEDIT,EDITOR or VISUAL
 * as a hint to what edit mode is desired.
 */
init_editmode()
{
  static char *ev[] = { "FCEDIT", "EDITOR", "VISUAL", NULL };
  register int i;
  register char *rcp, *rcp2;

  for (i = 0; ev[i]; i++)
  {
    if ((rcp = getenv(ev[i])) && *rcp)
      break;
  }
  if (ev[i] && rcp)
  {
    if (rcp2 = strrchr(rcp, '/'))
      rcp = ++rcp2;
#ifdef EMACS
    if (strstr(rcp, "emacs"))
    {
      flag[FVI] = 0;
      flag[FEMACS] = 1;
    }
#endif
#if defined(EMACS) && defined(VI)
    else
#endif
#ifdef VI
      if (strstr(rcp, "vi"))
      {
	flag[FVI] = 1;
	flag[FEMACS] = 0;
      }
#endif
  }
  return 0;
}
#endif
#pragma pop_macro("RCSid")
#pragma pop_macro("_I_")
#pragma pop_macro("_D_")
#pragma pop_macro("TIOCSTI")
#pragma pop_macro("TIOCSPGRP")
#pragma pop_macro("TIOCSETN")
#pragma pop_macro("TIOCSETD")
#pragma pop_macro("TIOCGETD")
#pragma pop_macro("NTTYDISC")
#pragma pop_macro("EXTERN_DEFINED")
#pragma pop_macro("EXTERN")
#pragma pop_macro("BEL")

#pragma push_macro("AEDIT")
#pragma push_macro("BEL")
#pragma push_macro("CMASK")
#pragma push_macro("CTRL")
#pragma push_macro("EXTERN")
#pragma push_macro("EXTERN_DEFINED")
#pragma push_macro("KEOL")
#pragma push_macro("KILLSIZE")
#pragma push_macro("KINTR")
#pragma push_macro("KNULL")
#pragma push_macro("KPREF")
#pragma push_macro("KSTD")
#pragma push_macro("PUSH_DELETE")
#pragma push_macro("S_ISDIR")
#pragma push_macro("S_ISREG")
#pragma push_macro("UNCTRL")
#pragma push_macro("XF_ALLOC")
#pragma push_macro("XF_NOBIND")
#pragma push_macro("X_TABSZ")
#pragma push_macro("_D_")
#pragma push_macro("_I_")
#pragma push_macro("iscfs")
#pragma push_macro("ismfs")
#pragma push_macro("xft_erase")
#pragma push_macro("xft_error")
#pragma push_macro("xft_ins_string")
#pragma push_macro("xft_insert")
#pragma push_macro("xft_intr")
#pragma push_macro("xft_kill")
#pragma push_macro("xft_quit")
#pragma push_macro("xft_werase")
#pragma push_macro("RCSid")
#define RCSid RCSid_emacs
#line 1 "emacs.c"
/*
 *  Emacs-like command line editing and history
 *
 *  created by Ron Natalie at BRL
 *  modified by Doug Kingston, Doug Gwyn, and Lou Salkind
 *  adapted to PD ksh by Eric Gisin
 */

#ifdef EMACS

#ifndef lint
static char *RCSid = "$Id: emacs.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <setjmp.h>
/* begin inlined edit.h from emacs.c */
/* NAME:
 *      edit.h - globals for edit modes
 *
 * DESCRIPTION:
 *      This header defines various global edit objects.
 *
 * SEE ALSO:
 *      
 *
 * RCSid:
 *      $Id: edit.h,v 1.2 1992/04/25 08:33:28 sjg Exp $
 *
 */

/* some useful #defines */
#ifdef EXTERN
# define _I_(i) = i
#else
# define _I_(i)
# define EXTERN extern
# define EXTERN_DEFINED
#endif

#define	BEL		0x07

/*
 * The following are used for my horizontal scrolling stuff
 */
EXTERN	char   *xbuf;		/* beg input buffer */
EXTERN	char   *xend;		/* end input buffer */
EXTERN char    *xcp;		/* current position */
EXTERN char    *xep;		/* current end */
EXTERN char    *xbp;		/* start of visible portion of input buffer */
EXTERN char    *xlp;		/* last char visible on screen */
EXTERN int	x_adj_ok;
/*
 * we use x_adj_done so that functions can tell 
 * whether x_adjust() has been called while they are active.
 */
EXTERN int	x_adj_done;

EXTERN int	x_cols;
EXTERN int	x_col;
EXTERN int	x_displen;
EXTERN int	x_arg;		/* general purpose arg */

EXTERN int	x_do_init;		/* set up tty modes */
EXTERN int	ed_erase, ed_kill, ed_werase, ed_intr, ed_quit;

#ifdef DEBUG
# define _D_(x) x
#else
# define _D_(x)
#endif

/****  edit.c  ****/
int             x_read      ARGS((int fd, char *buf, size_t len));
int             x_getc      ARGS((void));
void            x_flush     ARGS((void));
void            x_adjust    ARGS((void));
void            x_putc      ARGS((int c));
int             x_debug_info ARGS((void));
void            x_puts      ARGS((char *s));
void            x_init      ARGS((void));
bool_t          x_mode      ARGS((bool_t onoff));
bool_t          x_mode      ARGS((bool_t onoff));
int             promptlen   ARGS((char *cp));

/****  emacs.c  ****/
void            x_redraw    ARGS((int limit));
char*		x_lastcp    ARGS((void));
EXTERN int xlp_valid _I_(0);
  
/* This lot goes at the END */
/* be sure not to interfere with anyone else's idea about EXTERN */
#ifdef EXTERN_DEFINED
# undef EXTERN_DEFINED
# undef EXTERN
#endif
/*
 * Local Variables:
 * version-control:t
 * comment-column:40
 * End:
 */
/* end inlined edit.h from emacs.c */

#define PUSH_DELETE 1			/* push all deletes of >1 char */

static	Area	aedit;
#define	AEDIT	&aedit		/* area for kill ring and macro defns */

#undef CTRL			/* _BSD brain damage */
#define	CTRL(x)		((x) == '?' ? 0x7F : (x) & 0x1F)	/* ASCII */
#define	UNCTRL(x)	((x) == 0x7F ? '?' : (x) | 0x40)	/* ASCII */

#ifndef S_ISDIR
#define S_ISDIR(mode)	(((mode) & S_IFMT) == S_IFDIR)
#endif

#ifndef S_ISREG
#define S_ISREG(mode)	(((mode) & S_IFMT) == S_IFREG)
#endif

/* values returned by keyboard functions */
#define	KSTD	0
#define	KPREF	1		/* ^[, ^X */
#define	KEOL	2		/* ^M, ^J */
#define	KINTR	3		/* ^G, ^C */
#define	KNULL	4
	
struct	x_ftab  {
	int	(*xf_func)();
	char	*xf_name;
	char	xf_db_tab;
	char	xf_db_char;
	short	xf_flags;
};

#define	XF_ALLOC	2
#define	XF_NOBIND	4

#define	iscfs(c)	(c == ' ' || c == '\t')	/* Separator for completion */
#define	ismfs(c)	(!(isalnum(c)|| c == '$'))  /* Separator for motion */
#define	BEL		0x07
#define	CMASK		0x7F	/* 7-bit ASCII character mask */

#define X_TABSZ	128			/* size of keydef tables etc */

static	int	x_prefix1 = CTRL('['), x_prefix2 = CTRL('X');
static	char   **x_histp;	/* history position */
static	char   **x_nextcmdp;	/* for newline-and-next */
static	char	*xmp;		/* mark pointer */
static	int    (*x_last_command)();
static	struct	x_ftab const *(*x_tab)[X_TABSZ] = NULL; /* key definition */
static	char    *(*x_atab)[X_TABSZ] = NULL; /* macro definitions */
#define	KILLSIZE	20
static	char    *killstack[KILLSIZE];
static	int	killsp, killtp;
static	int	x_curprefix;
static	char    *macroptr;
static	int	x_maxlen;	/* to determine column width */

static int      x_insert    ARGS((int c));
static int      x_ins_string ARGS((int c));
static void     x_ins       ARGS((char *cp));
static int      x_del_back  ARGS((int c));
static int      x_del_char  ARGS((int c));
static void     x_delete    ARGS((int nc));
static int      x_del_bword ARGS((int c));
static int      x_mv_bword  ARGS((int c));
static int      x_mv_fword  ARGS((int c));
static int      x_del_fword ARGS((int c));
static int      x_bword     ARGS((void));
static int      x_fword     ARGS((void));
static void     x_goto      ARGS((char *cp));
static void     x_bs        ARGS((int c));
static int      x_size_str  ARGS((char *cp));
static int      x_size      ARGS((int c));
static void     x_zots      ARGS((char *str));
static void     x_zotc      ARGS((int c));
static int      x_mv_back   ARGS((int c));
static int      x_mv_forw   ARGS((int c));
static int      x_search_char ARGS((int c));
static int      x_newline   ARGS((int c));
static int      x_end_of_text ARGS((int c));
static int      x_beg_hist  ARGS((int c));
static int      x_end_hist  ARGS((int c));
static int      x_prev_com  ARGS((int c));
static int      x_next_com  ARGS((int c));
static void     x_load_hist ARGS((char **hp));
static int      x_nl_next_com ARGS((int c));
static int      x_eot_del   ARGS((int c));
static int      x_search_hist ARGS((int c));
static int      x_search    ARGS((char *pat, int offset));
static int      x_match     ARGS((char *str, char *pat));
static int      x_del_line  ARGS((int c));
static int      x_mv_end    ARGS((int c));
static int      x_mv_begin  ARGS((int c));
static int      x_draw_line ARGS((int c));
static int      x_transpose ARGS((int c));
static int      x_literal   ARGS((int c));
static int      x_meta1     ARGS((int c));
static int      x_meta2     ARGS((int c));
static int      x_kill      ARGS((int c));
static void     x_push      ARGS((int nchars));
static int      x_yank      ARGS((int c));
static int      x_meta_yank ARGS((int c));
static int      x_abort     ARGS((int c));
static int      x_error     ARGS((int c));
static int      x_stuffreset ARGS((int c));
static int      x_stuff     ARGS((int c));
static void     x_mapin     ARGS((char *cp));
static char *   x_mapout    ARGS((int c));
static void     x_print     ARGS((int prefix, int key));
static int      x_set_mark  ARGS((int c));
static int      x_kill_region ARGS((int c));
static int      x_xchg_point_mark ARGS((int c));
static int      x_copy_arg  ARGS((int c));
static int      x_noop      ARGS((int c));
#ifdef SILLY
static int      x_game_of_life ARGS((int c));
#endif
static void     add_stash   ARGS((char *dirnam, char *name));
static void     list_stash  ARGS((void));
static int      x_comp_comm ARGS((int c));
static int      x_list_comm ARGS((int c));
static int      x_complete  ARGS((int c));
static int      x_enumerate ARGS((int c));
static int      x_comp_file ARGS((int c));
static int      x_list_file ARGS((int c));
static void     compl_dec   ARGS((int type));
static void     compl_file  ARGS((int type));
static void     compl_command ARGS((int type));
static int      strmatch    ARGS((char *s1, char *s2));
static int      x_set_arg   ARGS((int c));
static int      x_prev_histword ARGS((void));
static int      x_fold_case ARGS((int c));

static	struct x_ftab const x_ftab[] = {
 	{x_insert,	"auto-insert",		0,	 0,	0 },
	{x_error,	"error",		0,	 0,	0 },
 	{x_ins_string,	"macro-string",		0,	 0,	XF_NOBIND|XF_ALLOC},
	{x_del_back,	"delete-char-backward",	0, CTRL('H'),	0 },
	{x_eot_del,	"eot-or-delete",	0, CTRL('D'),	0 },
	{x_del_bword,	"delete-word-backward",	1, CTRL('H'),	0 },
	{x_mv_bword,	"backward-word", 	1,	'b',	0 },
	{x_del_line,	"kill-line",		0, 	0,	0 },
	{x_abort,	"abort",		0,	0,	0 },
	{x_noop,	"no-op",		0,	0,	0 },
/* Do not move the above! */
	{x_mv_fword,	"forward-word",		1,	'f',	0 },
	{x_del_char,	"delete-char-forward",	0,	0,	0 },
	{x_del_fword,	"delete-word-forward", 	1,	'd',	0 },
	{x_mv_back,	"backward-char",	0, CTRL('B'),	0 },
	{x_mv_forw,	"forward-char",		0, CTRL('F'),	0 },
	{x_search_char,	"search-character",	0, CTRL(']'),	0 },
	{x_newline,	"newline",		0, CTRL('M'),	0 },
	{x_newline,	"newline",		0, CTRL('J'),	0 },
	{x_end_of_text,	"eot",			0, CTRL('_'),	0 },
	{x_abort,	"abort",		0, CTRL('G'),	0 },
	{x_prev_com,	"up-history",		0, CTRL('P'),	0},
	{x_next_com,	"down-history",		0, CTRL('N'),	0},
	{x_search_hist,	"search-history",	0, CTRL('R'),	0},
	{x_beg_hist,	"beginning-of-history",	1,	'<',	0},
	{x_end_hist,	"end-of-history",	1,	'>',	0},
	{x_mv_end,	"end-of-line",		0, CTRL('E'),	0 },
	{x_mv_begin,	"beginning-of-line",	0, CTRL('A'),	0 },
	{x_draw_line,	"redraw",		0, CTRL('L'),	0 },
	{x_meta1,	"prefix-1",		0, CTRL('['),	0 },
	{x_meta2,	"prefix-2",		0, CTRL('X'),	0 },
	{x_kill,	"kill-to-eol",		0, CTRL('K'),	0 },
	{x_yank,	"yank",			0, CTRL('Y'),	0 },
	{x_meta_yank,	"yank-pop", 		1,	'y',	0 },
	{x_literal,	"quote",		0, CTRL('^'),	0 },
	{x_stuffreset, 	"stuff-reset",		0,	 0,	0 },
#if defined(BRL) && defined(TIOCSTI)
	{x_stuff, 	"stuff",		0, CTRL('T'),	0 },
	{x_transpose,	"transpose-chars",	0,	 0,	0 },
#else
	{x_stuff, 	"stuff",		0,	 0,	0 },
	{x_transpose,	"transpose-chars",	0, CTRL('T'),	0 },
#endif
	{x_complete,	"complete",		1, CTRL('['),	0 },
	{x_enumerate,	"list",			1,	'?',	0 },
	{x_comp_file,	"complete-file",	1, CTRL('X'),	0 },
	{x_comp_comm,	"complete-command",	2, CTRL('['),	0 },
	{x_list_file,	"list-file",		0,	 0,	0 },
	{x_list_comm,	"list-command",		2,	'?',	0 },
	{x_nl_next_com,	"newline-and-next",	0, CTRL('O'),	0 },
	{x_set_mark,	"set-mark-command",	1,	' ',	0 },
	{x_kill_region,	"kill-region",		0, CTRL('W'),	0 },
	{x_xchg_point_mark, "exchange-point-and-mark", 2, CTRL('X'), 0 },
#if 0
	{x_copy_arg,	"copy-last-arg",	1,	'_',	0},
#endif
#ifdef SILLY
	{x_game_of_life, "play-game-of-life",	0,	0,	0 },
#endif 
#ifdef DEBUG
        {x_debug_info,	"debug-info",		1, CTRL('H'),	0 },
#endif
	{x_prev_histword, "prev-hist-word", 	1,	'.',	0 },
	{x_prev_histword, "prev-hist-word", 	1,	'_',	0 },
        {x_set_arg,	"",			1,	'0',	0 },
        {x_set_arg,	"",			1,	'1',	0 },
        {x_set_arg,	"",			1,	'2',	0 },
        {x_set_arg,	"",			1,	'3',	0 },
        {x_set_arg,	"",			1,	'4',	0 },
        {x_set_arg,	"",			1,	'5',	0 },
        {x_set_arg,	"",			1,	'6',	0 },
        {x_set_arg,	"",			1,	'7',	0 },
        {x_set_arg,	"",			1,	'8',	0 },
        {x_set_arg,	"",			1,	'9',	0 },
        {x_fold_case,	"upcase-word",		1,	'U',	0 },
        {x_fold_case,	"downcase-word",	1,	'L',	0 },
        {x_fold_case,	"capitalize-word",	1,	'C',	0 },
        {x_fold_case,	"upcase-word",		1,	'u',	0 },
        {x_fold_case,	"downcase-word",	1,	'l',	0 },
        {x_fold_case,	"capitalize-word",	1,	'c',	0 },
	{ 0 }
};

#define	xft_insert &x_ftab[0]
#define	xft_error &x_ftab[1]
#define	xft_ins_string &x_ftab[2]
#define	xft_erase &x_ftab[3]
#define	xft_kill &x_ftab[7]
#define	xft_werase &x_ftab[5]
#define xft_intr &x_ftab[8]
#define	xft_quit &x_ftab[9]

int
x_emacs(buf, len)
	char *buf;
	size_t len;
{
	char	c;
	int	i;
	int   (*func)();
	extern	x_insert();

	xbp = xbuf = buf; xend = buf + len;
	xlp = xcp = xep = buf;
	*xcp = 0;
	xlp_valid = TRUE;
	xmp = NULL;
	x_curprefix = 0;
	macroptr = null;
	x_histp = histptr + 1;

	if (x_nextcmdp != NULL) {
		x_load_hist(x_nextcmdp);
		x_nextcmdp = NULL;
	}

	/* <sjg@sun0> this may not be correct */
	if ((i = atoi(strval(global("COLUMNS")))) > 0)
	  x_cols = i;
	else
	  x_cols = 80;
	x_col = promptlen(prompt);
	x_adj_ok = 1;
	x_displen = x_cols - 2 - x_col;
	x_adj_done = 0;

	while (1)  {
		x_flush();
		if (*macroptr)  {
			c = *macroptr++;
			if (*macroptr == 0)
				macroptr = null;
		}
		else {
			if ((c = x_getc()) < 0)
				return i;
		}

		if (x_curprefix == -1)
			func = x_insert;
		else
			func = x_tab[x_curprefix][c&CMASK]->xf_func;
		if (func == NULL)
			func = x_error;
		i = c | (x_curprefix << 8);
		x_curprefix = 0;
		switch (i = (*func)(i))  {
		  case KSTD:
			x_last_command = func;
		  case KPREF:
		  case KNULL:
			break;
		  case KEOL:
			i = xep - xbuf;
			x_last_command = 0;
			return i;
		  case KINTR:	/* special case for interrupt */
			errno = EINTR;
			return -1;
		}
	}
}

static int
x_insert(c)  {
	char	str[2];

	/*
	 *  Should allow tab and control chars.
	 */
	if (c == 0)  {
		x_putc(BEL);
		return KSTD;
	}
	str[0] = c;
	str[1] = 0;
	x_ins(str);
	return KSTD;
}

static int
x_ins_string(c)
{
	if (*macroptr)   {
		x_putc(BEL);
		return KSTD;
	}
	macroptr = x_atab[c>>8][c & CMASK];
	return KSTD;
}

static void
x_ins(cp)
	char	*cp;
{
	int	count;
	register int	adj = x_adj_done;

	count = strlen(cp);
	if (xep+count >= xend) {
		x_putc(BEL);
		return;
	}

	if (xcp != xep)
		memmove(xcp+count, xcp, xep - xcp + 1);
	else
		xcp[count] = 0;
	memmove(xcp, cp, count);
	/*
	 * x_zots() may result in a call to x_adjust()
	 * we want xcp to reflect the new position.
	 */
	cp = xcp;
	xcp += count;
	xep += count;
	xlp_valid = FALSE;
	x_lastcp();
	x_adj_ok = (xcp >= xlp);
	x_zots(cp);
	if (adj == x_adj_done)	/* has x_adjust() been called? */
	{
	  /* no */
	  for (cp = xlp; cp > xcp; )
	    x_bs(*--cp);
	}

	x_adj_ok = 1;
	return;
}

static int
x_del_back(c)  {
	if (xcp == xbuf)  {
		x_putc(BEL);
		return KSTD;
	}
	x_goto(xcp - 1);
	x_delete(1);
	return KSTD;
}

static int
x_del_char(c)  {
	if (xcp == xep)  {
		x_putc(BEL);
		return KSTD;
	}
	x_delete(1);
	return KSTD;
}

static void
x_delete(nc)
  int nc;
{
	int	i,j;
	char	*cp;
	
	if (nc == 0)
		return;
	if (xmp != NULL) {
		if (xcp + nc > xmp)
			xmp = xcp;
		else if (xmp > xcp)
			xmp -= nc;
	}
#ifdef PUSH_DELETE
	/*
	 * This lets us yank a word we have deleted.
	 */
	if (nc > 1)
	  x_push(nc);
#endif
	xep -= nc;
	cp = xcp;
	j = 0;
	i = nc;
	while (i--)  {
		j += x_size(*cp++);
	}
	memmove(xcp, xcp+nc, xep - xcp + 1);	/* Copies the null */
	x_adj_ok = 0;			/* don't redraw */
	x_zots(xcp);
	/*
	 * if we are already filling the line,
	 * there is no need to ' ','\b'.
	 * But if we must, make sure we do the minimum.
	 */
	if ((i = x_cols - 2 - x_col) > 0)
	{
	  j = (j < i) ? j : i;
	  i = j;
	  while (i--)
	    x_putc(' ');
	  i = j;
	  while (i--)
	    x_putc('\b');
	}
	/*x_goto(xcp);*/
	x_adj_ok = 1;
	xlp_valid = FALSE;
	for (cp = x_lastcp(); cp > xcp; )
	  x_bs(*--cp);

	return;	
}

static int
x_del_bword(c)  {
	x_delete(x_bword());
	return KSTD;
}

static int
x_mv_bword(c)  {
	(void)x_bword();
	return KSTD;
}

static int
x_mv_fword(c)  {
	x_goto(xcp + x_fword());
	return KSTD;
}

static int
x_del_fword(c)  {
	x_delete(x_fword());
	return KSTD;
}

static int
x_bword()  {
	int	nc = 0;
	register char *cp = xcp;

	if (cp == xbuf)  {
		x_putc(BEL);
		return 0;
	}
	if (x_last_command != x_set_arg)
	  x_arg = 1;
	while (x_arg--)
	{
	  while (cp != xbuf && ismfs(cp[-1]))
	  {
	    cp--;
	    nc++;
	  }
	  while (cp != xbuf && !ismfs(cp[-1]))
	  {
	    cp--;
	    nc++;
	  }
	}
	x_goto(cp);
	return nc;
}

static int
x_fword()  {
	int	nc = 0;
	register char	*cp = xcp;

	if (cp == xep)  {
		x_putc(BEL);
		return 0;
	}
	if (x_last_command != x_set_arg)
	  x_arg = 1;
	while (x_arg--)
	{
	  while (cp != xep && !ismfs(*cp))
	  {
	    cp++;
	    nc++;
	  }
	  while (cp != xep && ismfs(*cp))
	  {
	    cp++;
	    nc++;
	  }
	}
	return nc;
}

static void
x_goto(cp)
	register char *cp;
{
  if (cp < xbp || cp >= (xbp + x_displen))
  {
    /* we are heading off screen */
    xcp = cp;
    x_adjust();
  }
  else
  {
    if (cp < xcp)		/* move back */
    {
      while (cp < xcp)
	x_bs(*--xcp);
    }
    else
    {
      if (cp > xcp) 		/* move forward */
      {
	while (cp > xcp)
	  x_zotc(*xcp++);
      }
    }
  }
}

static void
x_bs(c)  {
	register i;
	i = x_size(c);
	while (i--)
		x_putc('\b');
}

static int
x_size_str(cp)
	register char *cp;
{
	register size = 0;
	while (*cp)
		size += x_size(*cp++);
	return size;
}

static int
x_size(c)  {
	if (c=='\t')
		return 4;	/* Kludge, tabs are always four spaces. */
	if (c < ' ' || c == 0x7F) /* ASCII control char */
		return 2;
	return 1;
}

static void
x_zots(str)
	register char *str;
{
  register int	adj = x_adj_done;

  x_lastcp();
  while (*str && str < xlp && adj == x_adj_done)
    x_zotc(*str++);
}

static void
x_zotc(c)
	int c;
{
	if (c == '\t')  {
		/*  Kludge, tabs are always four spaces.  */
		x_puts("    ");
	} else if (c < ' ' || c == 0x7F)  { /* ASCII */
		x_putc('^');
		x_putc(UNCTRL(c));
	} else
		x_putc(c);
}

static int
x_mv_back(c)  {
	if (xcp == xbuf)  {
		x_putc(BEL);
		return KSTD;
	}
	x_goto(xcp-1);
	return KSTD;
}

static int
x_mv_forw(c)  {
	if (xcp == xep)  {
		x_putc(BEL);
		return KSTD;
	}
	x_goto(xcp+1);
	return KSTD;
}

static int
x_search_char(c)
	int c;
{
	char *cp;

	*xep = '\0';
	if ((c = x_getc()) < 0 ||
	    /* we search forward, I don't know what Korn does */
	    ((cp = (xcp == xep) ? NULL : strchr(xcp+1, c)) == NULL &&
	    (cp = strchr(xbuf, c)) == NULL)) {
		x_putc(BEL);
		return KSTD;
	}
	x_goto(cp);
	return KSTD;
}

static int
x_newline(c)  {
	x_putc('\n');
	x_flush();
	*xep++ = '\n';
	return KEOL;
}

static int
x_end_of_text(c)  {
#if 0
	x_store_hist();
#endif
	return KEOL;
}

static int x_beg_hist(c) {x_load_hist(history); return KSTD;}

static int x_end_hist(c) {x_load_hist(histptr); return KSTD;}

static int x_prev_com(c) {x_load_hist(x_histp-1); return KSTD;}

static int x_next_com(c) {x_load_hist(x_histp+1); return KSTD;}

static void
x_load_hist(hp)
	register char **hp;
{
	int	oldsize;

	if (hp < history || hp > histptr) {
		x_putc(BEL);
		return;
	}
	x_histp = hp;
	oldsize = x_size_str(xbuf);
	(void)strcpy(xbuf, *hp);
	xbp = xbuf;
	xep = xcp = xbuf + strlen(*hp);
	xlp_valid = FALSE;
	if (xep > x_lastcp())
	  x_goto(xep);
	else
	  x_redraw(oldsize);
}

static int
x_nl_next_com(c)
int	c;
{
	x_nextcmdp = x_histp + 1;
	return (x_newline(c));
}

static int
x_eot_del(c)
int	c;
{
	if (xep == xbuf)
		return (x_end_of_text(c));
	else
		return (x_del_char(c));
}

static int x_search(), x_match();

/* reverse incremental history search */
static int
x_search_hist(c)
	int c;
{
	int offset = -1;	/* offset of match in xbuf, else -1 */
	char pat [256+1];	/* pattern buffer */
	register char *p = pat;
	int (*func)();

	*p = 0;
	while (1) {
		if (offset < 0) {
			x_puts("\nI-search: ");
			x_zots(pat);
		}
		x_flush();
		if ((c = x_getc()) < 0)
			return KSTD;
		func = x_tab[0][c&CMASK]->xf_func;
		if (c == CTRL('['))
			break;
		else if (func == x_search_hist)
			offset = x_search(pat, offset);
		else if (func == x_del_back)
			continue;	/* todo */
		else if (func == x_insert) {
			/* add char to pattern */
			*p++ = c, *p = 0;
			if (offset >= 0) {
				/* already have partial match */
				offset = x_match(xbuf, pat);
				if (offset >= 0) {
					x_goto(xbuf + offset + (p - pat) - (*pat == '^'));
					continue;
				}
			}
			offset = x_search(pat, offset);
		} else { /* other command */
			static char push[2];
			push[0] = c;
			macroptr = push; /* push command */
			break;
		}
	}
	if (offset < 0)
		x_redraw(-1);
	return KSTD;
}

/* search backward from current line */
static int
x_search(pat, offset)
	char *pat;
	int offset;
{
	register char **hp;
	int i;

	for (hp = x_histp; --hp >= history; ) {
		i = x_match(*hp, pat);
		if (i >= 0) {
			if (offset < 0)
				x_putc('\n');
			x_load_hist(hp);
			x_goto(xbuf + i + strlen(pat) - (*pat == '^'));
			return i;
		}
	}
	x_putc(BEL);
	x_histp = histptr;
	return -1;
}

/* return position of first match of pattern in string, else -1 */
static int
x_match(str, pat)
	char *str, *pat;
{
	if (*pat == '^') {
		return (strncmp(str, pat+1, strlen(pat+1)) == 0) ? 0 : -1;
	} else {
		char *q = strstr(str, pat);
		return (q == NULL) ? -1 : q - str;
	}
}

static int
x_del_line(c)  {
	int	i, j;

	*xep = 0;
	i = xep- xbuf;
	j = x_size_str(xbuf);
	xcp = xbuf;
	x_push(i);
	xlp = xbp = xep = xbuf;
	xlp_valid = TRUE;
	*xcp = 0;
	xmp = NULL;
	x_redraw(j);
	return KSTD;
}

static int
x_mv_end(c)  {
	x_goto(xep);
	return KSTD;
}

static int
x_mv_begin(c)  {
	x_goto(xbuf);
	return KSTD;
}

static int
x_draw_line(c)
{
	x_redraw(-1);
	return KSTD;

}

void
x_redraw(limit)
  int limit;
{
	int	i, j;
	char	*cp;
	
	x_adj_ok = 0;
	if (limit == -1)
		x_putc('\n');
	else 
		x_putc('\r');
	x_flush();
	if (xbp == xbuf)
	{
	  pprompt(prompt);
	  x_col = promptlen(prompt);
	}
	x_displen = x_cols - 2 - x_col;
	xlp_valid = FALSE;
	cp = x_lastcp();
	x_zots(xbp);
	if (xbp != xbuf || xep > xlp)
	  limit = x_cols;
	if (limit >= 0)
	{
	  if (xep > xlp)
	    i = 0;			/* we fill the line */
	  else
	    i = limit - (xlp - xbp);

	  for (j = 0; j < i && x_col < (x_cols - 2); j++)
	    x_putc(' ');
	  i = ' ';
	  if (xep > xlp)		/* more off screen */
	  {
	    if (xbp > xbuf)
	      i = '*';
	    else
	      i = '>';
	  }
	  else
	    if (xbp > xbuf)
	      i = '<';
	  x_putc(i);
	  j++;
	  while (j--)
	    x_putc('\b');
	}
	for (cp = xlp; cp > xcp; )
	  x_bs(*--cp);
	x_adj_ok = 1;
	_D_(x_flush();)
	return;
}

static int
x_transpose(c)  {
	char	tmp;
	if (xcp == xbuf) {
		x_putc(BEL);
		return KSTD;
	} else if (xcp == xep) {
		if (xcp - xbuf == 1) {
			x_putc(BEL);
			return KSTD;
		}
		x_bs(xcp[-1]);
		x_bs(xcp[-2]);
		x_zotc(xcp[-1]);
		x_zotc(xcp[-2]);
		tmp = xcp[-1];
		xcp[-1] = xcp[-2];
		xcp[-2] = tmp;
	} else {
		x_bs(xcp[-1]);
		x_zotc(xcp[0]);
		x_zotc(xcp[-1]);
		tmp = xcp[-1];
		xcp[-1] = xcp[0];
		xcp[0] = tmp;
		x_bs(xcp[0]);
	}
	return KSTD;
}

static int
x_literal(c)  {
	x_curprefix = -1;
	return KSTD;
}

static int
x_meta1(c)  {
	x_curprefix = 1;
	return KPREF;
}

static int
x_meta2(c)  {
	x_curprefix = 2;
	return KPREF;
}

static int
x_kill(c)  {
	int	i;

	i = xep - xcp;
	xlp = xcp;
	xlp_valid = TRUE;
	x_push(i);
	x_delete(i);
	return KSTD;
}

static void
x_push(nchars)  {
	char	*cp;
	cp = alloc((size_t)(nchars+1), AEDIT);
	memmove(cp, xcp, nchars);
	cp[nchars] = 0;
	if (killstack[killsp])
		afree((void *)killstack[killsp], AEDIT);
	killstack[killsp] = cp;
	killsp = (killsp + 1) % KILLSIZE;
}

static int
x_yank(c)  {
	if (killsp == 0)
		killtp = KILLSIZE;
	else
		killtp = killsp;
	killtp --;
	if (killstack[killtp] == 0)  {
		x_puts("\nnothing to yank");
		x_redraw(-1);
		return KSTD;
	}
	xmp = xcp;
	x_ins(killstack[killtp]);
	return KSTD;
}

static int
x_meta_yank(c)  {
	int	len;
	if (x_last_command != x_yank && x_last_command != x_meta_yank)  {
		x_puts("\nyank something first");
		x_redraw(-1);
		return KSTD;
	}
	len = strlen(killstack[killtp]);
	x_goto(xcp - len);
	x_delete(len);
	do  {
		if (killtp == 0)
			killtp = KILLSIZE - 1;
		else
			killtp--;
	}  while (killstack[killtp] == 0);
	x_ins(killstack[killtp]);
	return KSTD;
}

static int
x_abort(c) {
	/* x_zotc(c); */
	xlp = xep = xcp = xbp = xbuf;
	xlp_valid = TRUE;
	*xcp = 0;
	return KINTR;
}

static int
x_error(c) {
	x_putc(BEL);
	return KSTD;
}

static int
x_stuffreset(c)
{
#ifdef TIOCSTI
	(void)x_stuff(c);
	return KINTR;
#else
	x_zotc(c);
	xlp = xcp = xep = xbp = xbuf;
	xlp_valid = TRUE;
	*xcp = 0;
	x_redraw(-1);
	return KSTD;
#endif
}

static int
x_stuff(c)
{
#if 0 || defined TIOCSTI
	char	ch = c;
	bool_t	savmode = x_mode(FALSE);

	(void)ioctl(ttyfd, TIOCSTI, &ch);
	(void)x_mode(savmode);
	x_redraw(-1);
#endif
	return KSTD;
}

static void
x_mapin(cp)
	char	*cp;
{
	char	*op;

	op = cp;
	while (*cp)  {
		/* XXX -- should handle \^ escape? */
		if (*cp == '^')  {
			cp++;
			if (*cp >= '?')	/* includes '?'; ASCII */
				*op++ = CTRL(*cp);
			else  {
				*op++ = '^';
				cp--;
			}
		} else
			*op++ = *cp;
		cp++;
	}
	*op = 0;
}

static char *
x_mapout(c)
	int c;
{
	static char buf[8];
	register char *p = buf;

	if (c < ' ' || c == 0x7F)  { /* ASCII */
		*p++ = '^';
		*p++ = (c == 0x7F) ? '?' : (c | 0x40);
	} else
		*p++ = c;
	*p = 0;
	return buf;
}

static void
x_print(prefix, key)
	int prefix, key;
{
	if (prefix == 1)
		shellf("%s", x_mapout(x_prefix1));
	if (prefix == 2)
		shellf("%s", x_mapout(x_prefix2));
	shellf("%s = ", x_mapout(key));
	if (x_tab[prefix][key]->xf_func != x_ins_string)
		shellf("%s\n", x_tab[prefix][key]->xf_name);
	else
		shellf("'%s'\n", x_atab[prefix][key]);
}

void
x_bind(a1, a2, macro)
	char *a1, *a2;
	int macro;		/* bind -m */
{
	struct x_ftab const *fp;
	int prefix, key;
	char *sp = NULL;

	if (x_tab == NULL)
		errorf("cannot bind, not a tty\n");

	if (a1 == NULL) {
		for (prefix = 0; prefix < 3; prefix++)
		    for (key = 0; key < 0x80; key++) {
			fp = x_tab[prefix][key];
			if (fp == NULL ||
			    fp->xf_func == x_insert || fp->xf_func == x_error)
				continue;
			x_print(prefix, key);
		    }
		return;
	}

	x_mapin(a1);
	prefix = key = 0;
	for (;; a1++) {
		key = *a1;
		if (x_tab[prefix][key]->xf_func == x_meta1)
			prefix = 1;
		else
		if (x_tab[prefix][key]->xf_func == x_meta2)
			prefix = 2;
		else
			break;
	}

	if (a2 == NULL) {
		x_print(prefix, key);
		return;
	}

	if (*a2 == 0)
		fp = xft_insert;
	else if (!macro) {
		for (fp = x_ftab; fp->xf_func; fp++)
			if (strcmp(fp->xf_name, a2) == 0)
				break;
		if (fp->xf_func == NULL || (fp->xf_flags & XF_NOBIND))
			errorf("%s: no such function\n", a2);
		if (fp->xf_func == x_meta1)
			x_prefix1 = key;
		if (fp->xf_func == x_meta2)
			x_prefix2 = key;
	} else {
		fp = xft_ins_string;
		x_mapin(a2);
		sp = strsave(a2, AEDIT);
	}

	if ((x_tab[prefix][key]->xf_flags & XF_ALLOC) && x_atab[prefix][key])
		afree((void *)x_atab[prefix][key], AEDIT);
	x_tab[prefix][key] = fp;
	x_atab[prefix][key] = sp;
}

void
x_init_emacs()
{
	register int i, j;
	struct x_ftab const *fp;

	ainit(AEDIT);

	x_tab = (struct x_ftab *(*)[X_TABSZ]) alloc(sizeofN(*x_tab, 3), AEDIT);
	for (j = 0; j < 128; j++)
		x_tab[0][j] = xft_insert;
	for (i = 1; i < 3; i++)
		for (j = 0; j < 128; j++)
			x_tab[i][j] = xft_error;
	for (fp = x_ftab; fp->xf_func; fp++)
		if (fp->xf_db_char || fp->xf_db_tab)
			x_tab[fp->xf_db_tab][fp->xf_db_char] = fp;

	x_atab = (char *(*)[X_TABSZ]) alloc(sizeofN(*x_atab, 3), AEDIT);
	for (i = 1; i < 3; i++)
		for (j = 0; j < 128; j++)
			x_atab[i][j] = NULL;
}

void
x_emacs_keys(erase, kill, werase, intr, quit)
	int erase, kill, werase, intr, quit;
{
	x_tab[0][erase] = xft_erase;
	x_tab[0][kill] = xft_kill;
	x_tab[0][werase] = xft_werase;
	x_tab[0][intr] = xft_intr;
	x_tab[0][quit] = xft_quit;
}

static int
x_set_mark(c) {
	xmp = xcp;
	return KSTD;
}

static int
x_kill_region(c) {
	int	rsize;
	char	*xr;

	if (xmp == NULL) {
		x_putc(BEL);
		return KSTD;
	}
	if (xmp > xcp) {
		rsize = xmp - xcp;
		xr = xcp;
	} else {
		rsize = xcp - xmp;
		xr = xmp;
	}
	x_goto(xr);
	x_push(rsize);
	x_delete(rsize);
	xmp = xr;
	return KSTD;
}

static int
x_xchg_point_mark(c) {
	char	*tmp;

	if (xmp == NULL) {
		x_putc(BEL);
		return KSTD;
	}
	tmp = xmp;
	xmp = xcp;
	x_goto( tmp );
	return KSTD;
}

#if 0
static int
x_copy_arg(c)	{
	char *last;
	if ((last = strval(local("_"))) && *last)
		x_ins(last);
	return KSTD;
}
#endif

static int
x_noop(c) {
	return KNULL;
}

#ifdef SILLY
static int
x_game_of_life(c)  {
	char	newbuf [256+1];
	register char *ip, *op;
	int	i, len;

	i = xep - xbuf;
	*xep = 0;
	len = x_size_str(xbuf);
	xcp = xbp = xbuf;
	memmove(newbuf+1, xbuf, i);
	newbuf[0] = 'A';
	newbuf[i] = 'A';
	for (ip = newbuf+1, op = xbuf; --i >= 0; ip++, op++)  {
		/*  Empty space  */
		if (*ip < '@' || *ip == '_' || *ip == 0x7F)  {
			/*  Two adults, make whoopee */
			if (ip[-1] < '_' && ip[1] < '_')  {
				/*  Make kid look like parents.  */
				*op = '`' + ((ip[-1] + ip[1])/2)%32;
				if (*op == 0x7F) /* Birth defect */
					*op = '`';
			}
			else
				*op = ' ';	/* nothing happens */
			continue;
		}
		/*  Child */
		if (*ip > '`')  {
			/*  All alone, dies  */
			if (ip[-1] == ' ' && ip[1] == ' ')
				*op = ' ';
			else	/*  Gets older */
				*op = *ip-'`'+'@';
			continue;
		}
		/*  Adult  */
		/*  Overcrowded, dies */
		if (ip[-1] >= '@' && ip[1] >= '@')  {
			*op = ' ';
			continue;
		}
		*op = *ip;
	}
	*op = 0;
	x_redraw(len);
	return KSTD;
}
#endif

/*
 *	File/command name completion routines
 */

/* type: 0 for list, 1 for completion */

static	XPtrV words;

static void
add_stash(dirnam, name)
	char *dirnam;	/* directory name, if file */
	char *name;
{
	char *cp;
	register int type = 0;	/* '*' if executable, '/' if directory, else 0 */
	register int len = strlen(name);

	/* determine file type */
	if (dirnam)  {
		struct stat statb;
		char *buf = alloc((size_t)(strlen(dirnam)+len+2), ATEMP);

		if (strcmp(dirnam, ".") == 0)
			*buf = '\0';
		else if (strcmp(dirnam, "/") == 0)
			(void)strcpy(buf, "/");
		else
			(void)strcat(strcpy(buf, dirnam), "/");
		(void)strcat(buf, name);
		if (stat(buf, &statb)==0)
			if (S_ISDIR(statb.st_mode))
				type = '/';
			else if (S_ISREG(statb.st_mode) && access(buf, 01)==0)
				type = '*';
		if (type)
			++len;
		afree((void *)buf, ATEMP);
	}

	if (len > x_maxlen)
		x_maxlen = len;

	/* stash name for later sorting */
	cp = alloc((size_t)(len+1), ATEMP);
	(void)strcpy(cp = alloc((size_t)(len+1), ATEMP), name);
	if (dirnam && type)  {	/* append file type indicator */
		cp[len-1] = type;
		cp[len] = '\0';
	}
	XPput(words, cp);
}

static void
list_stash()
{
	register char **array, **record;
	int items = 0, tabstop, loc, nrows, jump, offset;

	items = XPsize(words);
	array = (char**) XPptrv(words);
	if (items == 0)
		return;
	qsortp(XPptrv(words), (size_t)XPsize(words), xstrcmp);

	/* print names */
	x_maxlen = (x_maxlen/8 + 1) * 8;	/* column width */
	nrows = (items-1) / (x_cols/x_maxlen) + 1;
	for (offset = 0; offset < nrows; ++offset)  {
		tabstop = loc = 0;
		x_putc('\n');
		for (jump = 0; offset+jump < items; jump += nrows)  {
			if (jump)
				while (loc < tabstop)  {
					x_putc('\t');
					loc = (loc/8 + 1) * 8;
				}
			record = array + (offset + jump);
			x_puts(*record);
			loc += strlen(*record);
			tabstop += x_maxlen;	/* next tab stop */
			afree((void *)*record, ATEMP);
		}
	}

	afree((void*)array, ATEMP);
	x_redraw(-1);
}

static int
x_comp_comm(c)  {
	compl_command(1);
	return KSTD;
}
static int
x_list_comm(c)  {
	compl_command(0);
	return KSTD;
}
static int
x_complete(c)  {
	compl_dec(1);
	return KSTD;
}
static int
x_enumerate(c)  {
	compl_dec(0);
	return KSTD;
}
static int
x_comp_file(c)   {
	compl_file(1);
	return KSTD;
}
static int
x_list_file(c)  {
	compl_file(0);
	return KSTD;
}

static void
compl_dec(type)
{
	char	*cp;
	cp = xcp;

	while (cp != xbuf && !iscfs(*cp))
		cp--;
	if (cp == xbuf && strchr(cp, '/') == NULL)
		compl_command(type);
	else
		compl_file(type);
}

static void
compl_file(type)
{
	char	*str;
	register char *cp, *xp;
	char	*lastp;
	char	*dirnam;
	char	buf [256+1];
	char	bug [256+1];
	DIR    *dirp;
	struct dirent *dp;
	long	loc = -1;
	int	len;
	int	multi = 0;

	str = xcp;
	cp = buf;
	xp = str;
	while (xp != xbuf)  {
		--xp;
		if (iscfs(*xp))  {
			xp++;
			break;
		}
	}
	if (digit(*xp) && (xp[1] == '<' || xp[1] == '>'))
		xp++;
	while (*xp == '<' || *xp == '>')
		xp++;
	if (type)
		while (*xcp && !iscfs(*xcp))
			x_zotc(*xcp++);
	else {
		x_maxlen = 0;
		XPinit(words, 16);
	}
	while (*xp && !iscfs(*xp))
		*cp++ = *xp++;

	*cp = 0;
	strcpy(buf, cp = substitute(buf, DOTILDE));
	afree((void*)cp, ATEMP);
	lastp = strrchr(buf, '/');
	if (lastp)
		*lastp = 0;

	dirnam = (lastp == NULL) ? "." : (lastp == buf) ? "/" : buf;
	dirp = opendir(dirnam);
	if (dirp == NULL) {
		x_putc(BEL);
		return;
	}

	if (lastp == NULL)
		lastp = buf;
	else
		lastp++;
	len = strlen(lastp);

	while ((dp = readdir(dirp)) != NULL)  {
		cp = dp->d_name;
		if (cp[0] == '.' &&
		    (cp[1] == '\0' || (cp[1] == '.' && cp[2] == '\0')))
			continue; /* always ignore . and .. */
		if (strncmp(lastp, cp, len) == 0)
			if (type)  {
				if (loc == -1)  {
					(void)strcpy(bug, cp);
					loc = strlen(cp);
				} else {
					multi = 1;
					loc = strmatch(bug, cp);
					bug[loc] = 0;
				}
			} else
				add_stash(dirnam, cp);
	}
	(void)closedir(dirp);

	if (type) {
		if (loc <= 0)  {
			x_putc(BEL);
			return;
		}
		cp = bug + len;
		x_ins(cp);
		if (!multi)  {
			struct stat statb;
			if (lastp == buf)
				buf[0] = 0;
			else if (lastp == buf + 1)  {
				buf[1] = 0;
				buf[0] = '/';
			}  else
				(void)strcat(buf, "/");
			(void)strcat(buf, bug);
			if (stat(buf, &statb) == 0 && S_ISDIR(statb.st_mode))
				x_ins("/");
			else
				x_ins(" ");
		}
	} else
		list_stash();
}

static void
compl_command(type)
{
	register struct tbl *tp;
	char	*str;
	char	buf [256+1];
	char	bug [256+1];
	char	*xp;
	char	*cp;
	int  len;
	int  multi;
	int  loc;

	str = xcp;
	cp = buf;
	xp = str;
	while (xp != xbuf)  {
		--xp;
		if (iscfs(*xp))  {
			xp++;
			break;
		}
	}
	if (type)
		while (*xcp && !iscfs(*xcp))
			x_zotc(*xcp++);
	else {
		x_maxlen = 0;
		XPinit(words, 16);
	}
	while (*xp && !iscfs(*xp))
		*cp++ = *xp++;
	*cp = 0;

	len = strlen(buf);
	loc = -1;
	multi = 0;

	for (twalk(&commands); (tp = tnext()) != NULL; ) {
		int	klen;

		if (!(tp->flag&ISSET))
			continue;
		klen = strlen(tp->name);
		if (klen < len)
			continue;
		if (strncmp(buf, tp->name, len) ==0)
			if (type)  {
				if (loc == -1)  {
					(void)strcpy(bug, tp->name);
					loc = klen;
				} else {
					multi = 1;
					loc = strmatch(bug, tp->name);
					bug[loc] = 0;
				}
			} else
				add_stash((char *)0, tp->name);
	}

	if (type)  {
		if (loc <= 0)  {
			x_putc(BEL);
			return;
		}
		cp = bug + len;
		x_ins(cp);
		if (!multi)
			x_ins(" ");
	} else
		list_stash();
}

static int
strmatch(s1, s2)
	register char *s1, *s2;
{
	register char *p;

	for (p = s1; *p == *s2++ && *p != 0; p++)
		;
	return p - s1;
}



/* NAME:
 *      x_set_arg - set an arg value for next function
 *
 * DESCRIPTION:
 *      This is a simple implementation of M-[0-9].
 *
 * RETURN VALUE:
 *      KSTD
 */

static int
x_set_arg(c)
  int c;
{
  if ((x_arg = (c &= CMASK) - '0') < 0 || x_arg > 9)
  {
    x_arg = 1;
    x_putc(BEL);
  }
  return KSTD;
}


/* NAME:
 *      x_prev_histword - recover word from prev command
 *
 * DESCRIPTION:
 *      This function recovers the last word from the previous 
 *      command and inserts it into the current edit line.  If a 
 *      numeric arg is supplied then the n'th word from the 
 *      start of the previous command is used.  
 *      
 *      Bound to M-.
 *
 * RETURN VALUE:
 *      KSTD
 */

static int
x_prev_histword()
{
  register char *rcp;
  char *cp;
  char **hp;

  hp = x_histp-1;
  if (hp < history || hp > histptr)
  {
    x_putc(BEL);
    return;
  }
  cp = *hp;
  if (x_last_command != x_set_arg)
  {
    rcp = &cp[strlen(cp) - 1];
    /*
     * ignore white-space after the last word
     */
    while (rcp > cp && iscfs(*rcp))
      rcp--;
    while (rcp > cp && !iscfs(*rcp))
      rcp--;
    if (iscfs(*rcp))
      rcp++;
    x_ins(rcp);
  }
  else
  {
    int c;
    
    rcp = cp;
    /*
     * ignore white-space at start of line
     */
    while (*rcp && iscfs(*rcp))
      rcp++;
    while (x_arg-- > 1)
    {
      while (*rcp && !iscfs(*rcp))
	rcp++;
      while (*rcp && iscfs(*rcp))
	rcp++;
    }
    cp = rcp;
    while (*rcp && !iscfs(*rcp))
      rcp++;
    c = *rcp;
    *rcp = '\0';
    x_ins(cp);
    *rcp = c;
  }
  return KSTD;
}

/* NAME:
 *      x_fold_case - convert word to UPPER/lower case
 *
 * DESCRIPTION:
 *      This function is used to implement M-u,M-l and M-c
 *      to upper case, lower case or Capitalize words.
 *
 * RETURN VALUE:
 *      None
 */

static int
x_fold_case(c)
  int c;
{
  register char	*cp = xcp;
  
  if (cp == xep)
  {
    x_putc(BEL);
    return 0;
  }
  c &= 0137;				/* strip prefixes and case */
  if (x_last_command != x_set_arg)
    x_arg = 1;
  while (x_arg--)
  {
    /*
     * fisrt skip over any white-space
     */
    while (cp != xep && ismfs(*cp))
    {
      cp++;
    }
    /*
     * do the first char on its own since it may be
     * a different action than for the rest.
     */
    if (cp != xep)
    {
      if (c == 'L')			/* M-l */
      {
	if (isupper(*cp))
	  *cp = tolower(*cp);
      }
      else				/* M-u or M-c */
      {
	if (islower(*cp))
	  *cp = toupper(*cp);
      }
      cp++;
    }
    /*
     * now for the rest of the word
     */
    while (cp != xep && !ismfs(*cp))
    {
      if (c == 'U')			/* M-u */
      {
	if (islower(*cp))
	  *cp = toupper(*cp);
      }
      else				/* M-l or M-c */
      {
	if (isupper(*cp))
	  *cp = tolower(*cp);
      }
      cp++;
    }
  }
  x_goto(cp);
  return 0;
}

/* NAME:
 *      x_lastcp - last visible char
 *
 * SYNOPSIS:
 *      x_lastcp()
 *
 * DESCRIPTION:
 *      This function returns a pointer to that  char in the 
 *      edit buffer that will be the last displayed on the 
 *      screen.  The sequence:
 *      
 *      for (cp = x_lastcp(); cp > xcp; cp)
 *        x_bs(*--cp);
 *      
 *      Will position the cursor correctly on the screen.
 *
 * RETURN VALUE:
 *      cp or NULL
 */

char *
x_lastcp()
{
  register char *rcp;
  register int i;

  if (!xlp_valid)
  {
    for (i = 0, rcp = xbp; rcp < xep && i < x_displen; rcp++)
      i += x_size(*rcp);
    xlp = rcp;
  }
  xlp_valid = TRUE;
  return (xlp);
}

#endif /* EDIT */

#pragma pop_macro("RCSid")
#pragma pop_macro("xft_werase")
#pragma pop_macro("xft_quit")
#pragma pop_macro("xft_kill")
#pragma pop_macro("xft_intr")
#pragma pop_macro("xft_insert")
#pragma pop_macro("xft_ins_string")
#pragma pop_macro("xft_error")
#pragma pop_macro("xft_erase")
#pragma pop_macro("ismfs")
#pragma pop_macro("iscfs")
#pragma pop_macro("_I_")
#pragma pop_macro("_D_")
#pragma pop_macro("X_TABSZ")
#pragma pop_macro("XF_NOBIND")
#pragma pop_macro("XF_ALLOC")
#pragma pop_macro("UNCTRL")
#pragma pop_macro("S_ISREG")
#pragma pop_macro("S_ISDIR")
#pragma pop_macro("PUSH_DELETE")
#pragma pop_macro("KSTD")
#pragma pop_macro("KPREF")
#pragma pop_macro("KNULL")
#pragma pop_macro("KINTR")
#pragma pop_macro("KILLSIZE")
#pragma pop_macro("KEOL")
#pragma pop_macro("EXTERN_DEFINED")
#pragma pop_macro("EXTERN")
#pragma pop_macro("CTRL")
#pragma pop_macro("CMASK")
#pragma pop_macro("BEL")
#pragma pop_macro("AEDIT")

#pragma push_macro("BEL")
#pragma push_macro("B_")
#pragma push_macro("CMDLEN")
#pragma push_macro("C_")
#pragma push_macro("Ctrl")
#pragma push_macro("EXTERN")
#pragma push_macro("EXTERN_DEFINED")
#pragma push_macro("E_")
#pragma push_macro("INSERT")
#pragma push_macro("Isalnum")
#pragma push_macro("MAXVICMD")
#pragma push_macro("M_")
#pragma push_macro("O_")
#pragma push_macro("REPLACE")
#pragma push_macro("SRCHLEN")
#pragma push_macro("S_")
#pragma push_macro("U_")
#pragma push_macro("VARG1")
#pragma push_macro("VARG2")
#pragma push_macro("VCMD")
#pragma push_macro("VEXTCMD")
#pragma push_macro("VFAIL")
#pragma push_macro("VLIT")
#pragma push_macro("VNORMAL")
#pragma push_macro("VREDO")
#pragma push_macro("VREPLACE1CHAR")
#pragma push_macro("VSEARCH")
#pragma push_macro("VXCH")
#pragma push_macro("X_")
#pragma push_macro("_D_")
#pragma push_macro("_I_")
#pragma push_macro("bcopy")
#pragma push_macro("isbad")
#pragma push_macro("iscmd")
#pragma push_macro("isextend")
#pragma push_macro("islong")
#pragma push_macro("ismeta")
#pragma push_macro("ismove")
#pragma push_macro("issp")
#pragma push_macro("issrch")
#pragma push_macro("isundoable")
#pragma push_macro("RCSid")
#define RCSid RCSid_vi
#line 1 "vi.c"
/*
 *	vi command editing
 *	written by John Rochester (initially for nsh)
 *	bludgeoned to fit PD ksh by Larry Bouzane and Eric Gisin
 *	Further hacked (bugfixes and tweaks) by Mike Jetzer
 */

#ifdef VI

#ifndef lint
static char *RCSid = "$Id: vi.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <setjmp.h>
/* begin inlined edit.h from vi.c */
/* NAME:
 *      edit.h - globals for edit modes
 *
 * DESCRIPTION:
 *      This header defines various global edit objects.
 *
 * SEE ALSO:
 *      
 *
 * RCSid:
 *      $Id: edit.h,v 1.2 1992/04/25 08:33:28 sjg Exp $
 *
 */

/* some useful #defines */
#ifdef EXTERN
# define _I_(i) = i
#else
# define _I_(i)
# define EXTERN extern
# define EXTERN_DEFINED
#endif

#define	BEL		0x07

/*
 * The following are used for my horizontal scrolling stuff
 */
EXTERN	char   *xbuf;		/* beg input buffer */
EXTERN	char   *xend;		/* end input buffer */
EXTERN char    *xcp;		/* current position */
EXTERN char    *xep;		/* current end */
EXTERN char    *xbp;		/* start of visible portion of input buffer */
EXTERN char    *xlp;		/* last char visible on screen */
EXTERN int	x_adj_ok;
/*
 * we use x_adj_done so that functions can tell 
 * whether x_adjust() has been called while they are active.
 */
EXTERN int	x_adj_done;

EXTERN int	x_cols;
EXTERN int	x_col;
EXTERN int	x_displen;
EXTERN int	x_arg;		/* general purpose arg */

EXTERN int	x_do_init;		/* set up tty modes */
EXTERN int	ed_erase, ed_kill, ed_werase, ed_intr, ed_quit;

#ifdef DEBUG
# define _D_(x) x
#else
# define _D_(x)
#endif

/****  edit.c  ****/
int             x_read      ARGS((int fd, char *buf, size_t len));
int             x_getc      ARGS((void));
void            x_flush     ARGS((void));
void            x_adjust    ARGS((void));
void            x_putc      ARGS((int c));
int             x_debug_info ARGS((void));
void            x_puts      ARGS((char *s));
void            x_init      ARGS((void));
bool_t          x_mode      ARGS((bool_t onoff));
bool_t          x_mode      ARGS((bool_t onoff));
int             promptlen   ARGS((char *cp));

/****  emacs.c  ****/
void            x_redraw    ARGS((int limit));
char*		x_lastcp    ARGS((void));
EXTERN int xlp_valid _I_(0);
  
/* This lot goes at the END */
/* be sure not to interfere with anyone else's idea about EXTERN */
#ifdef EXTERN_DEFINED
# undef EXTERN_DEFINED
# undef EXTERN
#endif
/*
 * Local Variables:
 * version-control:t
 * comment-column:40
 * End:
 */
/* end inlined edit.h from vi.c */

#define CMDLEN		256
#define Ctrl(c)		(c&0x1f)
#define	bcopy(src, dst, len)	memmove(dst, src, len)
extern	int	histN();

static int      nextstate   ARGS((int ch));
static int      vi_insert   ARGS((int ch));
static int      vi_cmd      ARGS((int argcnt, char *cmd));
static int      domove      ARGS((int argcnt, char *cmd, int sub));
static int      redo_insert ARGS((int count));
static          yank_range  ARGS((int a, int b));
static int      bracktype   ARGS((int ch));
static          edit_reset  ARGS((char *buf, int len));
static int      putbuf      ARGS((char *buf, int len, int repl));
static          stripblanks ARGS((void));
static          del_range   ARGS((int a, int b));
static int      findch      ARGS((int ch, int cnt, int forw, int incl));
static int      forwword    ARGS((int argcnt));
static int      backword    ARGS((int argcnt));
static int      endword     ARGS((int argcnt));
static int      Forwword    ARGS((int argcnt));
static int      Backword    ARGS((int argcnt));
static int      Endword     ARGS((int argcnt));
static int      grabhist    ARGS((int save, int n));
static int      grabsearch  ARGS((int save, int start, int fwd, char *pat));
static          redraw_line ARGS((void));
static          refresh     ARGS((int leftside));
static int      outofwin    ARGS((void));
static          rewindow    ARGS((void));
static int      newcol      ARGS((int ch, int col));
static          display     ARGS((char *wb1, char *wb2, int leftside));
static          ed_mov_opt  ARGS((int col, char *wb));

#define C_	0x1
#define M_	0x2
#define E_	0x4
#define X_	0x8
#define U_	0x10
#define B_	0x20
#define O_	0x40
#define S_	0x80

#define isbad(c)	(classify[c]&B_)
#define iscmd(c)	(classify[c]&(M_|E_|C_|U_))
#define ismove(c)	(classify[c]&M_)
#define isextend(c)	(classify[c]&E_)
#define islong(c)	(classify[c]&X_)
#define ismeta(c)	(classify[c]&O_)
#define isundoable(c)	(!(classify[c]&U_))
#define issrch(c)	(classify[c]&S_)

char	classify[128] = {
	B_,	0,	0,	0,	0,	0,	O_,	0,
#if 1	/* Mike B. changes */
	C_|M_,	0,	O_,	0,	O_,	O_,	O_,	0,
#else
	C_,	0,	O_,	0,	O_,	O_,	O_,	0,
#endif
	O_,	0,	C_|U_,	0,	0,	0,	0,	0,
	0,	0,	O_,	0,	0,	0,	0,	0,
#if 1	/* Mike B. changes */
	C_|M_,	0,	0,	C_,	M_,	C_,	0,	0,
#else
	C_,	0,	0,	C_,	M_,	C_,	0,	0,
#endif
	0,	0,	C_,	C_,	M_,	C_,	0,	C_|S_,
	M_,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	M_,	0,	0,	0,	C_|S_,
	0,	C_,	M_,	C_,	C_,	M_,	M_|X_,	C_,
	0,	C_,	0,	0,	0,	0,	C_,	0,
	C_,	0,	C_,	C_,	M_|X_,	0,	0,	M_,
	C_,	C_,	0,	0,	0,	0,	M_,	C_,
	0,	C_,	M_,	E_,	E_,	M_,	M_|X_,	0,
	M_,	C_,	C_,	C_,	M_,	0,	C_,	0,
	C_,	0,	C_,	C_,	M_|X_,	C_|U_,	0,	M_,
	C_,	E_,	0,	0,	0,	0,	C_,	0
};

#define MAXVICMD	3
#define SRCHLEN		40

#define INSERT		1
#define REPLACE		2

#define VNORMAL		0
#define VARG1		1
#define VEXTCMD		2
#define VARG2		3
#define VXCH		4
#define VFAIL		5
#define VCMD		6
#define VREDO		7
#define VLIT		8
#define VSEARCH		9
#define VREPLACE1CHAR	10

struct edstate {
	int	winleft;
	char	*cbuf;
	int	cbufsize;
	int	linelen;
	int	cursor;
};

static char		undocbuf[CMDLEN];

static struct edstate	ebuf;
static struct edstate	undobuf = { 0, undocbuf, CMDLEN, 0, 0 };

static struct edstate	*es;			/* current editor state */
static struct edstate	*undo;

static char	ibuf[CMDLEN];		/* input buffer */
static int	inslen;			/* length of input buffer */
static int	srchlen;		/* length of current search pattern */
static char	ybuf[CMDLEN];		/* yank buffer */
static int	yanklen;		/* length of yank buffer */
static int	fsavecmd = ' ';		/* last find command */
static int	fsavech;		/* character to find */
static char	lastcmd[MAXVICMD];	/* last non-move command */
static int	lastac;			/* argcnt for lastcmd */
static int	lastsearch = ' ';	/* last search command */
static char	srchpat[SRCHLEN];	/* last search pattern */
static int	insert;			/* non-zero in insert mode */
static int	hnum;			/* position in history */
static int	hlast;			/* 1 past last position in history */
static int	modified;		/* buffer has been "modified" */
static int	state;

#if 0
vi_init()
{
	es = (struct edstate *) malloc((unsigned) sizeof(struct edstate));
	fsavecmd = ' ';
	lastsearch = ' ';
}

edit_init()
{
	wbuf[0] = malloc((unsigned) (x_cols - 3));
	wbuf[1] = malloc((unsigned) (x_cols - 3));
}
#endif

void
vi_reset(buf, len)
	char	*buf;
	int	len;
{
	state = VNORMAL;
	hnum = hlast = histnum(-1) + 1;
	insert = INSERT;
	yanklen = 0;
	inslen = 0;
	lastcmd[0] = 'a';
	lastac = 1;
	modified = 1;
	edit_reset(buf, len);
}

int
vi_hook(ch)
	int		ch;
{
	static char	curcmd[MAXVICMD];
	static char	locpat[SRCHLEN];
	static int	cmdlen;
	static int	argc1, argc2;

	if (state != VSEARCH && (ch == '\r' || ch == '\n')) {
		x_putc('\r');
		x_putc('\n');
		x_flush();
		return 1;
	}

	switch (state) {

	case VREPLACE1CHAR:
		curcmd[cmdlen++] = ch;
		state = VCMD;
		break;

	case VNORMAL:
		if (insert != 0) {
			if (ch == Ctrl('v')) {
				state = VLIT;
				ch = '^';
			}
			if (vi_insert(ch) != 0) {
				x_putc(Ctrl('g'));
				state = VNORMAL;
			} else {
				if (state == VLIT) {
					es->cursor--;
					refresh(0);
				} else
					refresh(insert != 0);
			}
		} else {
			cmdlen = 0;
			argc1 = 0;
			if (ch >= '1' && ch <= '9') {
				argc1 = ch - '0';
				state = VARG1;
			} else {
				curcmd[cmdlen++] = ch;
				state = nextstate(ch);
				if (state == VSEARCH) {
					save_cbuf();
					es->cursor = 0;
					es->linelen = 0;
					if (ch == '/') {
						if (putbuf("/", 1, 0) != 0) {
							return -1;
						}
					} else if (putbuf("?", 1, 0) != 0) 
							return -1;
					refresh(0);
				}
			}
		}
		break;

	case VLIT:
		if (isbad(ch)) {
			del_range(es->cursor, es->cursor + 1);
			x_putc(Ctrl('g'));
		} else
			es->cbuf[es->cursor++] = ch;
		refresh(1);
		state = VNORMAL;
		break;

	case VARG1:
		if (isdigit(ch))
			argc1 = argc1 * 10 + ch - '0';
		else {
			curcmd[cmdlen++] = ch;
			state = nextstate(ch);
		}
		break;

	case VEXTCMD:
		argc2 = 0;
		if (ch >= '1' && ch <= '9') {
			argc2 = ch - '0';
			state = VARG2;
			return 0;
		} else {
			curcmd[cmdlen++] = ch;
			if (ch == curcmd[0])
				state = VCMD;
			else if (ismove(ch))
				state = nextstate(ch);
			else
				state = VFAIL;
		}
		break;

	case VARG2:
		if (isdigit(ch))
			argc2 = argc2 * 10 + ch - '0';
		else {
			if (argc1 == 0)
				argc1 = argc2;
			else
				argc1 *= argc2;
			curcmd[cmdlen++] = ch;
			if (ch == curcmd[0])
				state = VCMD;
			else if (ismove(ch))
				state = nextstate(ch);
			else
				state = VFAIL;
		}
		break;

	case VXCH:
		if (ch == Ctrl('['))
			state = VNORMAL;
		else {
			curcmd[cmdlen++] = ch;
			state = VCMD;
		}
		break;

	case VSEARCH:
		switch (ch) {

		/* case Ctrl('['): */
		case '\r':
		case '\n':
			locpat[srchlen] = '\0';
			(void) strcpy(srchpat, locpat);
			/* redraw_line(); */
			state = VCMD;
			break;

		case 0x7f:
			if (srchlen == 0) {
				restore_cbuf();
				state = VNORMAL;
			} else {
				srchlen--;
				if (locpat[srchlen] < ' ' ||
						locpat[srchlen] == 0x7f) {
					es->linelen--;
				}
				es->linelen--;
				es->cursor = es->linelen;
				refresh(0);
				return 0;
			}
			refresh(0);
			break;

		case Ctrl('u'):
			srchlen = 0;
			es->linelen = 1;
			es->cursor = 1;
			refresh(0);
			return 0;

		default:
			if (srchlen == SRCHLEN - 1)
				x_putc(Ctrl('g'));
			else {
				locpat[srchlen++] = ch;
				if (ch < ' ' || ch == 0x7f) {
					es->cbuf[es->linelen++] = '^';
					es->cbuf[es->linelen++] = ch ^ '@';
				} else
					es->cbuf[es->linelen++] = ch;
				es->cursor = es->linelen;
				refresh(0);
			}
			return 0;
			break;
		}
		break;
	}
	switch (state) {

	case VCMD:
		state = VNORMAL;
		switch (vi_cmd(argc1, curcmd)) {
		case -1:
			x_putc(Ctrl('g'));
			break;
		case 0:
			if (insert != 0)
				inslen = 0;
			refresh(insert != 0);
			break;
		case 1:
			refresh(0);
			x_putc('\r');
			x_putc('\n');
			x_flush();
			return 1;
		}
		break;

	case VREDO:
		state = VNORMAL;
		if (argc1 != 0)
			lastac = argc1;
		switch (vi_cmd(lastac, lastcmd) != 0) {
		case -1:
			x_putc(Ctrl('g'));
			refresh(0);
			break;
		case 0:
			if (insert != 0) {
				if (lastcmd[0] == 's' || lastcmd[0] == 'c' ||
						lastcmd[0] == 'C') {
					if (redo_insert(1) != 0)
						x_putc(Ctrl('g'));
				} else {
					if (redo_insert(lastac) != 0)
						x_putc(Ctrl('g'));
				}
			}
			refresh(0);
			break;
		case 1:
			refresh(0);
			x_putc('\r');
			x_putc('\n');
			x_flush();
			return 1;
		}
		break;

	case VFAIL:
		state = VNORMAL;
		x_putc(Ctrl('g'));
		break;
	}
	return 0;
}

static int
nextstate(ch)
	int	ch;
{
	/*
	 * probably could have been done more elegantly than
	 * by creating a new state, but it works
	 */
	if (ch == 'r')
		return VREPLACE1CHAR;
	else if (isextend(ch))
		return VEXTCMD;
	else if (issrch(ch))
		return VSEARCH;
	else if (islong(ch))
		return VXCH;
	else if (ch == '.')
		return VREDO;
	else if (iscmd(ch))
		return VCMD;
	else
		return VFAIL;
}

static int
vi_insert(ch)
	int	ch;
{
	int	tcursor;

	switch (ch) {

	case '\0':
		return -1;

	case Ctrl('['):
		if (lastcmd[0] == 's' || lastcmd[0] == 'c' ||
				lastcmd[0] == 'C')
			return redo_insert(0);
		else
			return redo_insert(lastac - 1);

	case 0x7f:		/* delete */
		/* tmp fix */
		/* general fix is to get stty erase char and use that
		*/
	case Ctrl('H'):		/* delete */
		if (es->cursor != 0) {
			if (inslen > 0)
				inslen--;
			es->cursor--;
			if (insert != REPLACE) {
				bcopy(&es->cbuf[es->cursor+1],
						&es->cbuf[es->cursor],
						es->linelen - es->cursor);
				es->linelen--;
			}
		}
		break;

	case Ctrl('U'):
		if (es->cursor != 0) {
			inslen = 0;
			bcopy(&es->cbuf[es->cursor], es->cbuf,
						es->linelen - es->cursor);
			es->linelen -= es->cursor;
			es->cursor = 0;
		}
		break;

	case Ctrl('W'):
		if (es->cursor != 0) {
			tcursor = backword(1);
			bcopy(&es->cbuf[es->cursor], &es->cbuf[tcursor],
						es->linelen - es->cursor);
			es->linelen -= es->cursor - tcursor;
			if (inslen < es->cursor - tcursor)
				inslen = 0;
			else
				inslen -= es->cursor - tcursor;
			es->cursor = tcursor;
		}
		break;

	default:
		if (es->linelen == es->cbufsize - 1)
			return -1;
		ibuf[inslen++] = ch;
		if (insert == INSERT) {
			bcopy(&es->cbuf[es->cursor], &es->cbuf[es->cursor+1],
					es->linelen - es->cursor);
			es->linelen++;
		}
		es->cbuf[es->cursor++] = ch;
		if (insert == REPLACE && es->cursor > es->linelen)
			es->linelen++;
	}
	return 0;
}

static int
vi_cmd(argcnt, cmd)
	int		argcnt;
	char		*cmd;
{
	int		ncursor;
	int		cur, c1, c2, c3 = 0;
	struct edstate	*t;


	if (argcnt == 0) {
		if (*cmd == 'G')
			argcnt = hlast + 1;
		else if (*cmd != '_')
			argcnt = 1;
	}

	if (ismove(*cmd)) {
		if ((cur = domove(argcnt, cmd, 0)) >= 0) {
			if (cur == es->linelen && cur != 0)
				cur--;
			es->cursor = cur;
		} else
			return -1;
	} else {
		if (isundoable(*cmd)) {
			undo->winleft = es->winleft;
			bcopy(es->cbuf, undo->cbuf, es->linelen);
			undo->linelen = es->linelen;
			undo->cursor = es->cursor;
			lastac = argcnt;
			bcopy(cmd, lastcmd, MAXVICMD);
		}
		switch (*cmd) {

		case Ctrl('r'):
			redraw_line();
			break;

		case 'a':
			modified = 1;
			if (es->linelen != 0)
				es->cursor++;
			insert = INSERT;
			break;

		case 'A':
			modified = 1;
			del_range(0, 0);
			es->cursor = es->linelen;
			insert = INSERT;
			break;

		case 'c':
		case 'd':
		case 'y':
			if (*cmd == cmd[1]) {
				c1 = 0;
				c2 = es->linelen;
			} else if (!ismove(cmd[1]))
				return -1;
			else {
				if ((ncursor = domove(argcnt, &cmd[1], 1)) < 0)
					return -1;
				if (*cmd == 'c' &&
						(cmd[1]=='w' || cmd[1]=='W') &&
						!isspace(es->cbuf[es->cursor])) {
					while (isspace(es->cbuf[--ncursor]))
						;
					ncursor++;
				}
				if (ncursor > es->cursor) {
					c1 = es->cursor;
					c2 = ncursor;
				} else {
					c1 = ncursor;
					c2 = es->cursor;
				}
			}
			if (*cmd != 'c' && c1 != c2)
				yank_range(c1, c2);
			if (*cmd != 'y') {
				del_range(c1, c2);
				es->cursor = c1;
			}
			if (*cmd == 'c') {
				modified = 1;
				insert = INSERT;
			}
			break;

		case 'p':
			modified = 1;
			if (es->linelen != 0)
				es->cursor++;
			while (putbuf(ybuf, yanklen, 0) == 0 && --argcnt > 0)
				;
			if (es->cursor != 0)
				es->cursor--;
			if (argcnt != 0)
				return -1;
			break;

		case 'P':
			modified = 1;
			while (putbuf(ybuf, yanklen, 0) == 0 && --argcnt > 0)
				;
			if (es->cursor != 0)
				es->cursor--;
			if (argcnt != 0)
				return -1;
			break;

		case 'C':
			modified = 1;
			del_range(es->cursor, es->linelen);
			insert = INSERT;
			break;

		case 'D':
			yank_range(es->cursor, es->linelen);
			del_range(es->cursor, es->linelen);
			if (es->cursor != 0)
				es->cursor--;
			break;

		case 'G':
			if (grabhist(modified, argcnt - 1) < 0)
				return -1;
			else {
				modified = 0;
				hnum = argcnt - 1;
			}
			break;

		case 'i':
			modified = 1;
			insert = INSERT;
			break;

		case 'I':
			modified = 1;
			es->cursor = 0;
			insert = INSERT;
			break;

		case '+':
		case 'j':
			if (grabhist(modified, hnum + argcnt) < 0)
				return -1;
			else {
				modified = 0;
				hnum += argcnt;
			}
			break;

		case '-':
		case 'k':
			if (grabhist(modified, hnum - argcnt) < 0)
				return -1;
			else {
				modified = 0;
				hnum -= argcnt;
			}
			break;

		case 'r':
			if (es->linelen == 0)
				return -1;
			modified = 1;
			es->cbuf[es->cursor] = cmd[1];
			break;

		case 'R':
			modified = 1;
			insert = REPLACE;
			break;

		case 's':
			if (es->linelen == 0)
				return -1;
			modified = 1;
			if (es->cursor + argcnt > es->linelen)
				argcnt = es->linelen - es->cursor;
			del_range(es->cursor, es->cursor + argcnt);
			insert = INSERT;
			break;

		case 'x':
			if (es->linelen == 0)
				return -1;
			modified = 1;
			if (es->cursor + argcnt > es->linelen)
				argcnt = es->linelen - es->cursor;
			yank_range(es->cursor, es->cursor + argcnt);
			del_range(es->cursor, es->cursor + argcnt);
			break;

		case 'X':
			if (es->cursor > 0) {
				modified = 1;
				if (es->cursor < argcnt)
					argcnt = es->cursor;
				yank_range(es->cursor - argcnt, es->cursor);
				del_range(es->cursor - argcnt, es->cursor);
				es->cursor -= argcnt;
			} else
				return -1;
			break;

		case 'u':
			t = es;
			es = undo;
			undo = t;
			break;

		case '?':
			hnum = -1;
			/* ahhhhhh... */
		case '/':
			c3 = 1;
			srchlen = 0;
			lastsearch = *cmd;
			/* fall through */
		case 'n':
		case 'N':
			if (lastsearch == ' ')
				return -1;
			if (lastsearch == '?')
				c1 = 1; 
			else
				c1 = 0;
			if (*cmd == 'N')
				c1 = !c1;
			if ((c2 = grabsearch(modified, hnum,
							c1, srchpat)) < 0) {
				if (c3) {
					restore_cbuf();
					refresh(0);
				}
				return -1;
			} else {
				modified = 0;
				hnum = c2;
			}
			break;
		case '_': {
			int	space;
			char	*p, *sp;

			(void) histnum(-1);
			p = *histpos();
#define issp(c)		(isspace((c)) || (c) == '\n')
			if (argcnt) {
				while (*p && issp(*p))
					p++;
				while (*p && --argcnt) {
					while (*p && !issp(*p))
						p++;
					while (*p && issp(*p))
						p++;
				}
				if (!*p)
					return -1;
				sp = p;
			} else {
				sp = p;
				space = 0;
				while (*p) {
					if (issp(*p))
						space = 1;
					else if (space) {
						space = 0;
						sp = p;
					}
					p++;
				}
				p = sp;
			}
			modified = 1;
			if (es->linelen != 0)
				es->cursor++;
			while (*p && !issp(*p)) {
				argcnt++;
				p++;
			}
			if (putbuf(" ", 1, 0) != 0)
				argcnt = -1;
			else if (putbuf(sp, argcnt, 0) != 0)
				argcnt = -1;
			if (argcnt < 0) {
				if (es->cursor != 0)
					es->cursor--;
				return -1;
			}
			insert = INSERT;
			}
			break;

		case '~': {
			char	*p;

			if (es->linelen == 0)
				return -1;
			p = &es->cbuf[es->cursor];
			if (islower(*p)) {
				modified = 1;
				*p = toupper(*p);
			} else if (isupper(*p)) {
				modified = 1;
				*p = tolower(*p);
			}
			if (es->cursor < es->linelen - 1)
				es->cursor++;
			}
			break;

		case '#':
			es->cursor = 0;
			if (putbuf("#", 1, 0) != 0)
				return -1;
			return 1;

		case '*': {
			int	rval = 0;
			int	start, end;
			char	*toglob = undo->cbuf;
			char	**ap;
			char	**ap2;
			char	**globstr();

			if (isspace(es->cbuf[es->cursor]))
				return -1;
			start = es->cursor;
			while (start > -1 && !isspace(es->cbuf[start]))
				start--;
			start++;
			end = es->cursor;
			while (end < es->linelen && !isspace(es->cbuf[end]))
				end++;
			/* use undo buffer to build word up in */
			bcopy(&es->cbuf[start], toglob, end-start);
			if (*toglob != '~' && toglob[end-start-1] != '*') {
				toglob[end-start] = '*';
				toglob[end-start+1] = '\0';
			} else
				toglob[end-start] = '\0';
			ap = globstr(toglob);
			ap2 = ap;
			if (strcmp(ap[0], toglob) == 0 && ap[1] == (char *) 0)
				rval = -1;
			/* restore undo buffer that we used temporarily */
			bcopy(es->cbuf, toglob, es->linelen);
			if (rval < 0)
				return rval;
			del_range(start, end);
			es->cursor = start;
			while (1) {
				if (putbuf(*ap, strlen(*ap), 0) != 0) {
					rval = -1;
					break;
				}
				if (*++ap == (char *) 0)
					break;
				if (putbuf(" ", 1, 0) != 0) {
					rval = -1;
					break;
				}
			}
#if 0
			/*
			 * this is definitely wrong
			 */
			for (ap = ap2; *ap; ap++)
			    free(*ap);

			free(ap2);
#endif

			modified = 1;
			insert = INSERT;
			refresh(0);
			if (rval != 0)
				return rval;
			}
			break;
		}
		if (insert == 0 && es->cursor != 0 && es->cursor >= es->linelen)
			es->cursor--;
	}
	return 0;
}

static int
domove(argcnt, cmd, sub)
	int	argcnt;
	char	*cmd;
	int	sub;
{
	int	bcount, i = 0, t;	/* = 0 kludge for gcc -W */
	int	ncursor = 0;		/* = 0 kludge for gcc -W */

	switch (*cmd) {

	case 'b':
		if (!sub && es->cursor == 0)
			return -1;
		ncursor = backword(argcnt);
		break;

	case 'B':
		if (!sub && es->cursor == 0)
			return -1;
		ncursor = Backword(argcnt);
		break;

	case 'e':
		if (!sub && es->cursor + 1 >= es->linelen)
			return -1;
		ncursor = endword(argcnt);
		if (sub)
			ncursor++;
		break;

	case 'E':
		if (!sub && es->cursor + 1 >= es->linelen)
			return -1;
		ncursor = Endword(argcnt);
		if (sub)
			ncursor++;
		break;

	case 'f':
	case 'F':
	case 't':
	case 'T':
		fsavecmd = *cmd;
		fsavech = cmd[1];
		/* drop through */

	case ',':
	case ';':
		if (fsavecmd == ' ')
			return -1;
		i = fsavecmd == 'f' || fsavecmd == 'F';
		t = fsavecmd > 'a';
		if (*cmd == ',')
			t = !t;
		if ((ncursor = findch(fsavech, argcnt, t, i)) < 0)
			return -1;
		if (sub && t)
			ncursor++;
		break;

	case 'h':
		/* tmp fix */
	case Ctrl('H'):
		if (!sub && es->cursor == 0)
			return -1;
		ncursor = es->cursor - argcnt;
		if (ncursor < 0)
			ncursor = 0;
		break;

	case ' ':
	case 'l':
		if (!sub && es->cursor + 1 >= es->linelen)
			return -1;
		if (es->linelen != 0) {
			ncursor = es->cursor + argcnt;
			if (ncursor >= es->linelen)
				ncursor = es->linelen - 1;
		}
		break;

	case 'w':
		if (!sub && es->cursor + 1 >= es->linelen)
			return -1;
		ncursor = forwword(argcnt);
		break;

	case 'W':
		if (!sub && es->cursor + 1 >= es->linelen)
			return -1;
		ncursor = Forwword(argcnt);
		break;

	case '0':
		ncursor = 0;
		break;

	case '^':
		ncursor = 0;
		while (ncursor < es->linelen - 1 && isspace(es->cbuf[ncursor]))
			ncursor++;
		break;

	case '$':
		if (es->linelen != 0)
			ncursor = es->linelen;
		else
			ncursor = 0;
		break;

	case '%':
		ncursor = es->cursor;
		while (ncursor < es->linelen &&
				(i = bracktype(es->cbuf[ncursor])) == 0)
			ncursor++;
		if (ncursor == es->linelen)
			return -1;
		bcount = 1;
		do {
			if (i > 0) {
				if (++ncursor >= es->linelen)
					return -1;
			} else {
				if (--ncursor < 0)
					return -1;
			}
			t = bracktype(es->cbuf[ncursor]);
			if (t == i)
				bcount++;
			else if (t == -i)
				bcount--;
		} while (bcount != 0);
		if (sub)
			ncursor++;
		break;

	default:
		return -1;
	}
	return ncursor;
}

static int
redo_insert(count)
	int	count;
{
	while (count-- > 0)
		if (putbuf(ibuf, inslen, insert==REPLACE) != 0)
			return -1;
	if (es->cursor > 0)
		es->cursor--;
	insert = 0;
	return 0;
}

static
yank_range(a, b)
	int	a, b;
{
	yanklen = b - a;
	if (yanklen != 0)
		bcopy(&es->cbuf[a], ybuf, yanklen);
}

static int
bracktype(ch)
	int	ch;
{
	switch (ch) {

	case '(':
		return 1;

	case '[':
		return 2;

	case '{':
		return 3;

	case ')':
		return -1;

	case ']':
		return -2;

	case '}':
		return -3;

	default:
		return 0;
	}
}

/*
 *	Non user interface editor routines below here
 */

static int	cur_col;		/* current column on line */
static int	pwidth;			/* width of prompt */
static int	winwidth;		/* width of window */
/*static char	*wbuf[2];		/* window buffers */
static char	wbuf[2][80-3];	/* window buffers */ /* TODO */
static int	win;			/* window buffer in use */
static char	morec;			/* more character at right of window */
static int	lastref;		/* argument to last refresh() */
static char	holdbuf[CMDLEN];	/* place to hold last edit buffer */
static int	holdlen;		/* length of holdbuf */

save_cbuf()
{
	bcopy(es->cbuf, holdbuf, es->linelen);
	holdlen = es->linelen;
	holdbuf[holdlen] = '\0';
}

restore_cbuf()
{
	es->cursor = 0;
	es->linelen = holdlen;
	bcopy(holdbuf, es->cbuf, holdlen);
}

static
edit_reset(buf, len)
	char	*buf;
	int	len;
{
	es = &ebuf;
	es->cbuf = buf;
	es->cbufsize = len;
	undo = &undobuf;
	undo->cbufsize = len;

	es->linelen = undo->linelen = 0;
	es->cursor = undo->cursor = 0;
	es->winleft = undo->winleft = 0;

	cur_col = pwidth = promptlen(prompt);
	winwidth = x_cols - pwidth - 3;
	x_putc('\r');
	x_flush();
	pprompt(prompt);
	/* docap(CLR_EOL, 0); */
	win = 0;
	morec = ' ';
	lastref = 1;
}

static int
putbuf(buf, len, repl)
	char	*buf;
	int	len;
	int	repl;
{
	if (len == 0)
		return 0;
	if (repl) {
		if (es->cursor + len >= es->cbufsize - 1)
			return -1;
		if (es->cursor + len > es->linelen)
			es->linelen = es->cursor + len;
	} else {
		if (es->linelen + len >= es->cbufsize - 1)
			return -1;
		bcopy(&es->cbuf[es->cursor], &es->cbuf[es->cursor + len],
			es->linelen - es->cursor);
		es->linelen += len;
	}
	bcopy(buf, &es->cbuf[es->cursor], len);
	es->cursor += len;
	return 0;
}

static
stripblanks()
{
	int	ncursor;

	ncursor = 0;
	while (ncursor < es->linelen && isspace(es->cbuf[ncursor]))
		ncursor++;
	del_range(0, ncursor);
}

static
del_range(a, b)
	int	a, b;
{
	if (es->linelen != b)
		bcopy(&es->cbuf[b], &es->cbuf[a], es->linelen - b);
	es->linelen -= b - a;
}

static int
findch(ch, cnt, forw, incl)
	int	ch;
	int	forw;
	int	incl;
{
	int	ncursor;

	if (es->linelen == 0)
		return -1;
	ncursor = es->cursor;
	while (cnt--) {
		do {
			if (forw) {
				if (++ncursor == es->linelen)
					return -1;
			} else {
				if (--ncursor < 0)
					return -1;
			}
		} while (es->cbuf[ncursor] != ch);
	}
	if (!incl) {
		if (forw)
			ncursor--;
		else
			ncursor++;
	}
	return ncursor;
}

#define Isalnum(x) (isalnum(x) || (x == '_'))
static int
forwword(argcnt)
	int	argcnt;
{
	int	ncursor;

	ncursor = es->cursor;
	while (ncursor < es->linelen && argcnt--) {
		if (Isalnum(es->cbuf[ncursor]))
			while (Isalnum(es->cbuf[ncursor]) &&
					++ncursor < es->linelen)
				;
		else if (!isspace(es->cbuf[ncursor]))
			while (!Isalnum(es->cbuf[ncursor]) &&
					!isspace(es->cbuf[ncursor]) &&
					++ncursor < es->linelen)
				;
		while (isspace(es->cbuf[ncursor]) && ++ncursor < es->linelen)
			;
	}
	return ncursor;
}

static int
backword(argcnt)
	int	argcnt;
{
	int	ncursor;

	ncursor = es->cursor;
	while (ncursor > 0 && argcnt--) {
		while (--ncursor > 0 && isspace(es->cbuf[ncursor]))
			;
		if (ncursor > 0) {
			if (Isalnum(es->cbuf[ncursor]))
				while (--ncursor >= 0 &&
				   Isalnum(es->cbuf[ncursor]))
					;
			else
				while (--ncursor >= 0 &&
				   !Isalnum(es->cbuf[ncursor]) &&
				   !isspace(es->cbuf[ncursor]))
					;
			ncursor++;
		}
	}
	return ncursor;
}

static int
endword(argcnt)
	int	argcnt;
{
	int	ncursor;

	ncursor = es->cursor;
	while (ncursor < es->linelen && argcnt--) {
		while (++ncursor < es->linelen - 1 &&
				isspace(es->cbuf[ncursor]))
			;
		if (ncursor < es->linelen - 1) {
			if (Isalnum(es->cbuf[ncursor]))
				while (++ncursor < es->linelen &&
					  Isalnum(es->cbuf[ncursor]))
					;
			else
				while (++ncursor < es->linelen &&
				   !Isalnum(es->cbuf[ncursor]) &&
				   !isspace(es->cbuf[ncursor]))
					;
			ncursor--;
		}
	}
	return ncursor;
}

static int
Forwword(argcnt)
	int	argcnt;
{
	int	ncursor;

	ncursor = es->cursor;
	while (ncursor < es->linelen && argcnt--) {
		while (!isspace(es->cbuf[ncursor]) && ++ncursor < es->linelen)
			;
		while (isspace(es->cbuf[ncursor]) && ++ncursor < es->linelen)
			;
	}
	return ncursor;
}

static int
Backword(argcnt)
	int	argcnt;
{
	int	ncursor;

	ncursor = es->cursor;
	while (ncursor > 0 && argcnt--) {
		while (--ncursor >= 0 && isspace(es->cbuf[ncursor]))
			;
		while (ncursor >= 0 && !isspace(es->cbuf[ncursor]))
			ncursor--;
		ncursor++;
	}
	return ncursor;
}

static int
Endword(argcnt)
	int	argcnt;
{
	int	ncursor;

	ncursor = es->cursor;
	while (ncursor < es->linelen - 1 && argcnt--) {
		while (++ncursor < es->linelen - 1 &&
				isspace(es->cbuf[ncursor]))
			;
		if (ncursor < es->linelen - 1) {
			while (++ncursor < es->linelen &&
					!isspace(es->cbuf[ncursor]))
				;
			ncursor--;
		}
	}
	return ncursor;
}

static int
grabhist(save, n)
	int	save;
	int	n;
{
	char	*hptr;

	if (n < 0 || n > hlast)
		return -1;
	if (n == hlast) {
		restore_cbuf();
		return 0;
	}
	(void) histnum(n);
	if ((hptr = *histpos()) == NULL) {
		shellf("grabhist: bad history array\n");
		return -1;
	}
	if (save)
		save_cbuf();
	es->linelen = strlen(hptr);
	bcopy(hptr, es->cbuf, es->linelen);
	es->cursor = 0;
	return 0;
}

static int
grabsearch(save, start, fwd, pat)
	int	save, start, fwd;
	char	*pat;
{
	char	*hptr;

	if ((start == 0 && fwd == 0) || (start >= hlast - 1 && fwd == 1))
		return -1;
	if ((hptr = findhist(start, fwd, pat)) == NULL) {
		/* if (start != 0 && fwd && match(holdbuf, pat) >= 0) { */
		if (start != 0 && fwd && strcmp(holdbuf, pat) >= 0) {
			restore_cbuf();
			return 0;
		} else
			return -1;
	} else if (hptr == (char *)-1) {
		return -1;
	}
	if (save)
		save_cbuf();
	es->linelen = strlen(hptr);
	bcopy(hptr, es->cbuf, es->linelen);
	es->cursor = 0;
	return histN();
}

static
redraw_line()
{
	x_putc('\r');
	x_putc('\n');
	x_flush();
	pprompt(prompt);
	cur_col = 2;
	morec = ' ';
}

static
refresh(leftside)
	int		leftside;
{
	if (leftside < 0)
		leftside = lastref;
	else
		lastref = leftside;
	if (outofwin())
		rewindow();
	display(wbuf[1 - win], wbuf[win], leftside);
	win = 1 - win;
}

static int
outofwin()
{
	int	cur, col;

	if (es->cursor < es->winleft)
		return 1;
	col = 0;
	cur = es->winleft;
	while (cur < es->cursor)
		col = newcol(es->cbuf[cur++], col);
	if (col > winwidth)
		return 1;
	return 0;
}

static
rewindow()
{
	register int	tcur, tcol;
	int		holdcur1, holdcol1;
	int		holdcur2, holdcol2;

	holdcur1 = holdcur2 = tcur = 0;
	holdcol1 = holdcol2 = tcol = 0;
	while (tcur < es->cursor) {
		if (tcol - holdcol2 > winwidth / 2) {
			holdcur1 = holdcur2;
			holdcol1 = holdcol2;
			holdcur2 = tcur;
			holdcol2 = tcol;
		}
		tcol = newcol(es->cbuf[tcur++], tcol);
	}
	while (tcol - holdcol1 > winwidth / 2)
		holdcol1 = newcol(es->cbuf[holdcur1++], holdcol1);
	es->winleft = holdcur1;
}

static int
newcol(ch, col)
	int	ch, col;
{
	if (ch < ' ' || ch == 0x7f) {
		if (ch == '\t')
			return (col | 7) + 1;
		else
			return col + 2;
	} else
		return col + 1;
}

static
display(wb1, wb2, leftside)
	char	*wb1, *wb2;
	int	leftside;
{
	char	*twb1, *twb2, mc;
	int	cur, col, cnt;
	int	ncol = 0; /* set to 0 kludge for gcc -W */
	int	moreright;

	col = 0;
	cur = es->winleft;
	moreright = 0;
	twb1 = wb1;
	while (col < winwidth && cur < es->linelen) {
		if (cur == es->cursor && leftside)
			ncol = col + pwidth;
		if (es->cbuf[cur] < ' ' || es->cbuf[cur] == 0x7f) {
			if (es->cbuf[cur] == '\t') {
				do {
					*twb1++ = ' ';
				} while (++col < winwidth && (col & 7) != 0);
			} else {
				*twb1++ = '^';
				if (++col < winwidth) {
					*twb1++ = es->cbuf[cur] ^ '@';
					col++;
				}
			}
		} else {
			*twb1++ = es->cbuf[cur];
			col++;
		}
		if (cur == es->cursor && !leftside)
			ncol = col + pwidth - 1;
		cur++;
	}
	if (cur == es->cursor)
		ncol = col + pwidth;
	if (col < winwidth) {
		while (col < winwidth) {
			*twb1++ = ' ';
			col++;
		}
	} else
		moreright++;
	*twb1 = ' ';

	col = pwidth;
	cnt = winwidth;
	twb1 = wb1;
	twb2 = wb2;
	while (cnt--) {
		if (*twb1 != *twb2) {
			if (cur_col != col)
				ed_mov_opt(col, wb1);
			x_putc(*twb1);
			cur_col++;
		}
		twb1++;
		twb2++;
		col++;
	}
	if (es->winleft > 0 && moreright)
		mc = '+';
	else if (es->winleft > 0)
		mc = '<';
	else if (moreright)
		mc = '>';
	else
		mc = ' ';
	if (mc != morec) {
		ed_mov_opt(x_cols - 2, wb1);
		x_putc(mc);
		cur_col++;
		morec = mc;
	}
#if 0
	/*
	 * Hack to fix teh ^r redraw problem, but it redraws way too much.
	 * Probably unacceptable at low baudrates.  Someone please fix this
	 */
	else
	    {
	    ed_mov_opt(x_cols - 2, wb1);
	    }
#endif
	if (cur_col != ncol)
		ed_mov_opt(ncol, wb1);
}

static
ed_mov_opt(col, wb)
	int	col;
	char	*wb;
{
	if (col < cur_col) {
		if (col + 1 < cur_col - col) {
			x_putc('\r');
			x_flush();
			pprompt(prompt);
			cur_col = pwidth;
			while (cur_col++ < col)
				x_putc(*wb++);
		} else {
			while (cur_col-- > col)
				x_putc('\b');
		}
	} else {
		wb = &wb[cur_col - pwidth];
		while (cur_col++ < col)
			x_putc(*wb++);
	}
	cur_col = col;
}

int
x_vi(buf, len)
	char *buf;
	size_t len;
{
	int	c;

	vi_reset(buf, len > CMDLEN ? CMDLEN : len);
	x_flush();
	while ((c = getch()) != -1) {
		if (vi_hook(c))
			break;
		x_flush();
	}

	if (c == -1)
		return -1;

	if (es->cbuf != buf) {
		bcopy(es->cbuf, buf, es->linelen);
		buf[es->linelen] = '\n';
	} else
		es->cbuf[es->linelen] = '\n';

	es->linelen++;
	return es->linelen;
}

getch()
{
	char	buf;

	if (read(ttyfd, &buf, 1) != 1)
		return -1;
	if ((buf & 0x7f) == Ctrl('c')) {
		/*
		 * If you hit ctrl-c, the buffer was left in a
		 * strange state; the next command typed was
		 * mucked up.  Doing all of this is probably
		 * overkill, but it works most of the time.
		 */
		memset(es->cbuf, 0, CMDLEN);
		es->winleft = 0;
		es->cbufsize = 0;
		es->linelen = 0;
		es->cursor = 0;

		memset(undo->cbuf, 0, CMDLEN);
		undo->winleft = 0;
		undo->cbufsize = 0;
		undo->linelen = 0;
		undo->cursor = 0;
		x_mode(FALSE);
		trapsig(SIGINT);
	} else if ((buf & 0x7f) == Ctrl('d'))
		return -1;
	return buf & 0x7f;
}


char **globstr(stuff)
char *stuff;
    {
    char *vecp[2];

    vecp[0] = stuff;
    vecp[1] = NULL;
    return(eval(vecp, DOBLANK|DOGLOB|DOTILDE));
    }
#endif /* VI */
#pragma pop_macro("RCSid")
#pragma pop_macro("isundoable")
#pragma pop_macro("issrch")
#pragma pop_macro("issp")
#pragma pop_macro("ismove")
#pragma pop_macro("ismeta")
#pragma pop_macro("islong")
#pragma pop_macro("isextend")
#pragma pop_macro("iscmd")
#pragma pop_macro("isbad")
#pragma pop_macro("bcopy")
#pragma pop_macro("_I_")
#pragma pop_macro("_D_")
#pragma pop_macro("X_")
#pragma pop_macro("VXCH")
#pragma pop_macro("VSEARCH")
#pragma pop_macro("VREPLACE1CHAR")
#pragma pop_macro("VREDO")
#pragma pop_macro("VNORMAL")
#pragma pop_macro("VLIT")
#pragma pop_macro("VFAIL")
#pragma pop_macro("VEXTCMD")
#pragma pop_macro("VCMD")
#pragma pop_macro("VARG2")
#pragma pop_macro("VARG1")
#pragma pop_macro("U_")
#pragma pop_macro("S_")
#pragma pop_macro("SRCHLEN")
#pragma pop_macro("REPLACE")
#pragma pop_macro("O_")
#pragma pop_macro("M_")
#pragma pop_macro("MAXVICMD")
#pragma pop_macro("Isalnum")
#pragma pop_macro("INSERT")
#pragma pop_macro("E_")
#pragma pop_macro("EXTERN_DEFINED")
#pragma pop_macro("EXTERN")
#pragma pop_macro("Ctrl")
#pragma pop_macro("C_")
#pragma pop_macro("CMDLEN")
#pragma pop_macro("B_")
#pragma pop_macro("BEL")

#pragma push_macro("HISTFILE")
#pragma push_macro("RCSid")
#define RCSid RCSid_history
#line 1 "history.c"
/*
 * command history
 *
 * only implements in-memory history.
 */

#ifndef lint
static char *RCSid = "$Id: history.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <setjmp.h>

char   *histrpl();
char  **current;
int	curpos;

static FILE *hist_fh = NULL;
static FILE *hist_open ARGS((char *mode));
#ifndef HISTFILE
# define HISTFILE ".pdksh_hist"
#endif

  
c_fc(wp)
	register char **wp;
{
	register char *id;
	FILE *f;
	struct temp *tf;
	register char **hp;
	char **hbeg, **hend;
	char *p, *cmd = NULL;
	int lflag = 0, nflag = 0, sflag = 0, rflag = 0, gflag = 0;
	int done = 0;
	void histbackup();

	for (wp++; (id = *wp) != NULL && *id++ == '-' && !done; wp++)
		while (*id && !done) {
			switch (*id++) {
			  case 'l':
				lflag++;
				break;
			  case 'n':
				nflag++;
				break;
			  case 'r':
				rflag++;
				break;
			  case 'g':
				gflag++;
				break;
			  case 'e':
				if (++wp && (p = *wp)) {
					if (p[0] == '-' && !p[1]) {
						sflag++;
					} else {
						cmd = alloc((size_t)(strlen(p)+4),ATEMP);
						strcpy(cmd, p);
						strcat(cmd, " $_");
					}
				} else
					errorf("argument expected\n");
				id = "";
				break;
			  default:
				wp--;
				done++;
				break;
			}
		}

	if (sflag) {
		char *pat = NULL, *rep = NULL;

		hp = histptr - 1;
		while ((id = *wp++) != NULL) {
			/* todo: multiple substitutions */
			if ((p = strchr(id, '=')) != NULL) {
				pat = id;
				rep = p;
				*rep++ = '\0';
			} else
				hp = histget(id);
		}

		if (hp == NULL || hp < history)
			errorf("cannot find history\n");
		if (pat == NULL)
			strcpy(line, *hp);
		else
			histrpl(*hp, pat, rep, gflag);
		histbackup();
		histsave(line); 
		histpush--; 
		line[0] = '\0';
		return 0;
	}

	if (*wp != NULL) {
		hbeg = histget(*wp++); /* first */
		if (*wp != NULL)
			hend = histget(*wp++); /* last */
		else if (lflag)
			hend = histptr;
		else
			hend = hbeg;
	} else {
		if (lflag)
			hbeg = histptr - 16, hend = histptr;
		else
			hbeg = hend = histptr - 1;
		if (hbeg < history)
			hbeg = history;
	}
	if (hbeg == NULL || hend == NULL)
		errorf("can't find history\n");

	if (lflag)
		f = stdout;
	else {
		nflag++;
		tf = maketemp(ATEMP);
		tf->next = e.temps; e.temps = tf;
		f = fopen(tf->name, "w");
		if (f == NULL)
			errorf("cannot create temp file %s", tf->name);
		setvbuf(f, (char *)NULL, _IOFBF, BUFSIZ);
	}

	for (hp = (rflag ? hend : hbeg); rflag ? (hp >= hbeg) : (hp <= hend);
	      rflag ? hp-- : hp++) {
		if (!nflag)
			fprintf(f, "%3d: ", source->line - (int)(histptr-hp));
		fprintf(f, "%s\n", *hp);
	}

	if (lflag)
		return 0;
	else
		fclose(f);

	setstr(local("_"), tf->name);
	if (cmd) {
		command(cmd); /* edit temp file */
		afree(cmd, ATEMP);
	} else
		command("${FCEDIT:-/bin/ed} $_");

	f = fopen(tf->name, "r");
	if (f == NULL)
		errorf("cannot open temp file %s\n", tf->name);
	setvbuf(f, (char *)NULL, _IOFBF, BUFSIZ);
	/* we push the editted lines onto the history list */
	while (fgets(line, sizeof(line), f) != NULL) {
		histsave(line); 
		histpush--; 
	}
	line[0] = '\0';
	fclose(f);

	return 0;
}

/******************************/
/* Back up over last histsave */
/******************************/
void
histbackup()
{
	static int last_line = -1;

	if (histptr > history && last_line != source->line) { 
		source->line--;
		afree((void*)*histptr, APERM);
		histptr--;
		last_line = source->line;
	}
}

/*
 * save command in history
 */
void
histsave(cmd)
	char *cmd;
{
	register char **hp = histptr;
	char *cp;

	if (++hp >= history + HISTORY) { /* remove oldest command */
		afree((void*)*history, APERM);
		for (hp = history; hp < history + HISTORY - 1; hp++)
			hp[0] = hp[1];
	}
	*hp = strsave(cmd, APERM);
	if ((cp = strchr(*hp, '\n')) != NULL)
		*cp = '\0';
	histptr = hp;
}

/*
 * get pointer to history given pattern
 * pattern is a number or string
 */
char **
histget(str)
	char *str;
{
	register char **hp = NULL;

	if (*str == '-')
		hp = histptr + getn(str);
	else
	if (digit(*str))
		hp = histptr + (getn(str) - source->line);
	else 
	if (*str == '?') {	/* unanchored match */
		for (hp = histptr-1; hp >= history; hp--)
			if (strstr(*hp, str+1) != NULL)
				break;
	} else {		/* anchored match */
		for (hp = histptr; hp >= history; hp--)
			if (strncmp(*hp, str, strlen(str)) == 0)
				break;
	}

	return (history <= hp && hp <= histptr) ? hp : NULL;
}

char *
histrpl(s, pat, rep, global)
	char *s;
	char *pat, *rep;
	int global;
{
	char *s1, *p, *last = NULL;
	int len = strlen(pat);

	if (strlen(s) - strlen(pat) + strlen(rep) >= LINE)
		errorf("substitution too long\n");
	line[0] = '\0';
	p = line;
	while (s1 = strstr(s, pat)) {
		strncpy(p, s, s1 - s);		/* first part */
		strcpy(p + (s1 - s), rep);	/* replacement */
		s = s1 + len;
		last = s1;
		p = strchr(p, 0);
		if (!global)
			s = "";
	}
	if (last)
		strcpy(p, last + len);		/* last part */
	else
		errorf("substitution failed\n");
	return line;
}

/*
 * 92-04-25 <sjg@zen>
 * A simple history file implementation.
 * At present we only save the history when we exit.
 * This can cause problems when there are multiple shells are 
 * running under the same user-id.  The last shell to exit gets 
 * to save its history.
 */
void
hist_init(s)
  Source *s;
{
  static int once = 0;
  FILE *fh;
  
  if (once++)
    return;

  if (fh = hist_open("r"))
  {
    while (fgets(line, sizeof(line), fh) != NULL)
    {
      histsave(line); 
      s->line++;
    }
    line[0] = '\0';
    fclose(fh);
#if 0	/* this might be a good idea? */
    hist_fh = hist_open("a");
#endif
  }
  
}


/*
 * save our history.
 * We check that we do not have more than we are allowed.
 * If the history file is read-only we do nothing.
 * Handy for having all shells start with a useful history set.
 */

void
hist_finish()
{
  static int once = 0;
  FILE *fh;
  register int i, mx;
  register char **hp, *mode = "w";
  
  if (once++)
    return;
  if ((mx = atoi(strval(global("HISTSIZE")))) > HISTORY || mx <= 0)
    mx = HISTORY;
  /* check how many we have */
  i = histptr - history;
  if (i >= mx)
  {
    hp = &histptr[-mx];
  }
  else
  {
    hp = history;
  }
  if (fh = hist_open(mode))
  {
    for (i = 0; i < mx && hp[i]; i++)
      fprintf(fh, "%s\n", hp[i]);
    fclose(fh);
  }
}


/*
 * simply grab the nominated history file.
 */
static FILE *
hist_open(mode)
  char *mode;
{
  register char *rcp;
  FILE *fh;
  char name[128];
  
  if ((rcp = strval(global("HISTFILE"))) == NULL || *rcp == '\0')
  {
    (void) sprintf(name, "%s/%s", strval(global("HOME")), HISTFILE);
    rcp = name;
  }
  return fopen(rcp, mode);
}



/*
 * Return the current position.
 */
char **
histpos()
{
	return current;
}

int
histN()
{
	return curpos;
}

int
histnum(n)
{
	int	last = histptr - history;

	if (n < 0 || n >= last) {
		current = histptr;
		curpos = last;
		return last;
	}  else {
		current = &history[n];
		curpos = n;
		return n;
	}
}

/*
 * This will become unecessary if histget is modified to allow
 * searching from positions other than the end, and in either 
 * direction.
 */
char *
findhist(start, fwd, str)
	int	start;
	int	fwd;
	char 	*str;
{
	int	 pos = start;
	char	 *line, *last;

	/* XXX check that we are valid after this */
	if (fwd)
		pos++;
	else
		pos--;
	histnum(pos);
	line = *histpos();
	do {
		last = line;
		if (strstr(line, str) != 0) {
			/* keep position current */
			return (line);
		}
		if (fwd)
			pos++;
		else
			pos--;
		histnum(pos);
		line = *histpos();
	} while (line && *line && line != last && pos>0);

	histnum(start);
	if (pos <= 0)
		return (char*)-1; /* TODO */
	return NULL;
}
#pragma pop_macro("RCSid")
#pragma pop_macro("HISTFILE")

#pragma push_macro("FSTRING")
#pragma push_macro("RCSid")
#define RCSid RCSid_tree
#line 1 "tree.c"
/*
 * command tree climbing
 */

#ifndef lint
static char *RCSid = "$Id: tree.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <setjmp.h>

#ifdef __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

#define	FSTRING	(FILE*)NULL

static int      tputc       ARGS((int c, FILE *f));
static void     tputC       ARGS((int c, FILE *f));
static void     tputS       ARGS((char *wp, FILE *f));
static struct ioword **iocopy ARGS((struct ioword **iow, Area *ap));
static void     iofree      ARGS((struct ioword **iow, Area *ap));

/*
 * print a command tree
 */

void
ptree(t, f)
	register struct op *t;
	register FILE *f;
{
	register char **w;
	struct ioword **ioact;
	struct op *t1;

 Chain:
	if (t == NULL)
		return;
	switch (t->type) {
	  case TCOM:
		for (w = t->vars; *w != NULL; )
			fptreef(f, "%S ", *w++);
		for (w = t->args; *w != NULL; )
			fptreef(f, "%S ", *w++);
		break;
	  case TEXEC:
		t = t->left;
		goto Chain;
	  case TPAREN:
		fptreef(f, "(%T)", t->left);
		break;
	  case TPIPE:
		fptreef(f, "%T| ", t->left);
		t = t->right;
		goto Chain;
	  case TLIST:
		fptreef(f, "%T", t->left);
		fptreef(f, "%;");
		t = t->right;
		goto Chain;
	  case TOR:
	  case TAND:
		fptreef(f, "%T", t->left);
		fptreef(f, "%s %T", (t->type==TOR) ? "||" : "&&", t->right);
		break;
	  case TFOR:
		fptreef(f, "for %s ", t->str);
		if (t->vars != NULL) {
			fptreef(f, "in ");
			for (w = t->vars; *w; )
				fptreef(f, "%S ", *w++);
			fptreef(f, "%;");
		}
		fptreef(f, "do %T", t->left);
		fptreef(f, "%;done ");
		break;
	  case TCASE:
		fptreef(f, "case %S in%;", t->str);
		for (t1 = t->left; t1 != NULL; t1 = t1->right) {
			fptreef(f, "(");
			for (w = t1->vars; *w != NULL; w++) {
				fptreef(f, "%S", *w);
				fptreef(f, "%c", (w[1] != NULL) ? '|' : ')');
			}
			fptreef(f, " %T;;%;", t1->left);
		}
		fptreef(f, "esac ");
		break;
	  case TIF:
		fptreef(f, "if %T", t->left);
		fptreef(f, "%;");
		t = t->right;
		if (t->left != NULL) {
			fptreef(f, "then %T", t->left);
			fptreef(f, "%;");
		}
		if (t->right != NULL) {
			fptreef(f, "else %T", t->right);
			fptreef(f, "%;");
		}
		fptreef(f, "fi ");
		break;
	  case TWHILE:
	  case TUNTIL:
		fptreef(f, "%s %T",
			(t->type==TWHILE) ? "while" : "until",
			t->left);
		fptreef(f, "%;do %T", t->right);
		fptreef(f, "%;done ");
		break;
	  case TBRACE:
		fptreef(f, "{%;%T", t->left);
		fptreef(f, "%;} ");
		break;
	  case TASYNC:
		fptreef(f, "%T&", t->left);
		break;
	  case TFUNCT:
		fptreef(f, "function %s %T", t->str, t->left);
		break;
	  case TTIME:
		fptreef(f, "time %T", t->left);
		break;
	  default:
		fptreef(f, "<botch>");
		break;
	}
	if ((ioact = t->ioact) != NULL)
		while (*ioact != NULL)
			pioact(f, *ioact++);
}

pioact(f, iop)
	register FILE *f;
	register struct ioword *iop;
{
	register int flag = iop->flag;
	if (iop->unit > 1)
		fptreef(f, "%c", '0' + iop->unit );

	switch(flag&IOTYPE) {
	case IOREAD:
		fptreef(f, "< ");
		break;
	case IOHERE:
		if (flag&IOSKIP)
			fptreef(f, "<<- ");
		else
			fptreef(f, "<< ");
		if (!(flag&IOEVAL))
			fptreef(f, "'");
		break;
	case IOCAT:
		fptreef(f, ">> ");
		break;
	case IOWRITE:
		if (flag&IOCLOB)
			fptreef(f, ">! ");
		else
			fptreef(f, "> ");
		break;
	case IODUP:			/* Needs help */
		if (iop->unit == 0)
			fptreef(f, "<&");
		else
			fptreef(f, ">&");
		break;
	}

	if ((flag&IOTYPE) == IOHERE) {
		if (flag&IOEVAL)
			fptreef(f, "%s ", iop->name);
		else
			fptreef(f, "%s' ", iop->name);
	} else {
		fptreef(f, "%S ", iop->name);
	}
}


/*
 * variants of fputc, fputs for ptreef and snptreef
 */

static	char   *snpf_s;		/* snptreef string */
static	int	snpf_n;		/* snptreef length */

static int
tputc(c, f)
	int c;
	register FILE *f;
{
	if (f != NULL)
		putc(c, f);
	else
		if (--snpf_n >= 0)
			*snpf_s++ = c;
	return c;
}

static void
tputC(c, f)
	register int c;
	register FILE *f;
{
	if ((c&0x60) == 0) {		/* C0|C1 */
		tputc((c&0x80) ? '$' : '^', f);
		tputc(((c&0x7F)|0x40), f);
	} else if ((c&0x7F) == 0x7F) {	/* DEL */
		tputc((c&0x80) ? '$' : '^', f);
		tputc('?', f);
	} else
		tputc(c, f);
}

static void
tputS(wp, f)
	register char *wp;
	register FILE *f;
{
	register int c, quoted=0;

	while (1)
		switch ((c = *wp++)) {
		  case EOS:
			return;
		  case CHAR:
			tputC(*wp++, f);
			break;
		  case QCHAR:
			if (!quoted)
				tputc('\\', f);
			tputC(*wp++, f);
			break;
		  case OQUOTE:
		  	quoted = 1;
			tputc('"', f);
			break;
		  case CQUOTE:
			quoted = 0;
			tputc('"', f);
			break;
		  case OSUBST:
			tputc('$', f);
			tputc('{', f);
			while ((c = *wp++) != 0)
				tputc(c, f);
			if (*wp != CSUBST)
				tputC(*wp++, f);
			break;
		  case CSUBST:
			tputc('}', f);
			break;
		  case COMSUB:
			tputc('$', f);
			tputc('(', f);
			while (*wp != 0)
				tputC(*wp++, f);
			tputc(')', f);
			break;
		}
}

/*
 * this is the _only_ way to reliably handle
 * variable args with an ANSI compiler
 */
#ifdef __STDC__
/* VARARGS */ int
fptreef(FILE *f, char *fmt, ...)
{
#else
fptreef(va_alist) 
  va_dcl
{
  FILE *f;
  char *fmt;
#endif
  va_list	va;

#ifdef __STDC__
  va_start(va, fmt);
#else
  va_start(va);
  f = va_arg(va, FILE *);
  fmt = va_arg(va, char *);
#endif
  
  vfptreef(f, fmt, va);
  va_end(va);
  return 0;
}

/* VARARGS */ int
#ifdef __STDC__
snptreef(char *s, int n, char *fmt, ...)
{
#else
snptreef(va_alist)
  va_dcl
{
  char *s;
  int n;
  char *fmt;
#endif
  va_list va;

#ifdef __STDC__
  va_start(va, fmt);
#else
  va_start(va);
  s = va_arg(va, char *);
  n = va_arg(va, int);
  fmt = va_arg(va, char *);
#endif

  snpf_s = s;
  snpf_n = n;
  vfptreef(FSTRING, fmt, va);
  tputc('\0', FSTRING);
  va_end(va);
  return 0;
}


vfptreef(f, fmt, va)
	register FILE *f;
	register char *fmt;
	register va_list va;
{
	register int c;

	while ((c = *fmt++))
	    if (c == '%') {
		register long n;
		register char *p;
		int neg;

		switch ((c = *fmt++)) {
		  case 'c':
			tputc(va_arg(va, int), f);
			break;
		  case 's':
			p = va_arg(va, char *);
			while (*p)
				tputc(*p++, f);
			break;
		  case 'S':	/* word */
			p = va_arg(va, char *);
			tputS(p, f);
			break;
		  case 'd': case 'u': /* decimal */
			n = (c == 'd') ? va_arg(va, int) : va_arg(va, unsigned int);
			neg = c=='d' && n<0;
			p = ulton((neg) ? -n : n, 10);
			if (neg)
				*--p = '-';
			while (*p)
				tputc(*p++, f);
			break;
		  case 'T':	/* format tree */
			ptree(va_arg(va, struct op *), f);
			break;
		  case ';':	/* newline or ; */
			p = (f == FSTRING) ? "; " : "\n";
			while (*p)
				tputc(*p++, f);
			break;
		  default:
			tputc(c, f);
			break;
		}
	    } else
		tputc(c, f);
}

/*
 * copy tree (for function definition)
 */

static	struct ioword **iocopy();

struct op *
tcopy(t, ap)
	register struct op *t;
	Area *ap;
{
	register struct op *r;
	register char **tw, **rw;

	if (t == NULL)
		return NULL;

	r = (struct op *) alloc(sizeof(struct op), ap);

	r->type = t->type;

	/* this will copy function and for identifiers quite accidently */
	r->str = (t->str == NULL) ? NULL : wdcopy(t->str, ap);

	if (t->vars == NULL)
		r->vars = NULL;
	else {
		for (tw = t->vars; *tw++ != NULL; )
			;
		rw = r->vars = (char **)
			alloc((int)(tw - t->vars) * sizeof(*tw), ap);
		for (tw = t->vars; *tw != NULL; )
			*rw++ = wdcopy(*tw++, ap);
		*rw = NULL;
	}

	if (t->args == NULL)
		r->args = NULL;
	else {
		for (tw = t->args; *tw++ != NULL; )
			;
		rw = r->args = (char **)
			alloc((int)(tw - t->args) * sizeof(*tw), ap);
		for (tw = t->args; *tw != NULL; )
			*rw++ = wdcopy(*tw++, ap);
		*rw = NULL;
	}

	r->ioact = (t->ioact == NULL) ? NULL : iocopy(t->ioact, ap);

	r->left = tcopy(t->left, ap);
	r->right = tcopy(t->right, ap);

	return r;
}

char *
wdcopy(wp, ap)
	char *wp;
	Area *ap;
{
	size_t len = wdscan(wp, EOS) - wp;
	return memcpy(alloc(len, ap), wp, len);
}

/* return the position of prefix c in wp plus 1 */
char *
wdscan(wp, c)
	register char *wp;
	register int c;
{
	register int nest = 0;

	while (1)
		switch (*wp++) {
		  case EOS:
			return wp;
		  case CHAR:
		  case QCHAR:
			wp++;
			break;
		  case OQUOTE:
		  case CQUOTE:
			break;
		  case OSUBST:
			nest++;
			while (*wp++ != 0)
				;
			if (*wp != CSUBST)
				wp++;
			break;
		  case CSUBST:
			if (c == CSUBST && nest == 0)
				return wp;
			nest--;
			break;
		  case COMSUB:
			while (*wp++ != 0)
				;
			break;
		}
}

static	struct ioword **
iocopy(iow, ap)
	register struct ioword **iow;
	Area *ap;
{
	register struct ioword **ior;
	register int i;

	for (ior = iow; *ior++ != NULL; )
		;
	ior = (struct ioword **) alloc((int)(ior - iow) * sizeof(*ior), ap);

	for (i = 0; iow[i] != NULL; i++) {
		register struct ioword *p, *q;

		p = iow[i];
		q = (struct ioword *) alloc(sizeof(*p), ap);
		ior[i] = q;
		*q = *p;
		if (p->name != NULL)
			q->name = wdcopy(p->name, ap);
	}
	ior[i] = NULL;

	return ior;
}

/*
 * free tree (for function definition)
 */

static	void iofree();

void
tfree(t, ap)
	register struct op *t;
	Area *ap;
{
	register char **w;

	if (t == NULL)
		return;

	if (t->str != NULL)
		afree((void*)t->str, ap);

	if (t->vars != NULL) {
		for (w = t->vars; *w != NULL; w++)
			afree((void*)*w, ap);
		afree((void*)t->vars, ap);
	}

	if (t->args != NULL) {
		for (w = t->args; *w != NULL; w++)
			afree((void*)*w, ap);
		afree((void*)t->args, ap);
	}

	if (t->ioact != NULL)
		iofree(t->ioact, ap);

	tfree(t->left, ap);
	tfree(t->right, ap);

	afree((void*)t, ap);
}

static	void
iofree(iow, ap)
	struct ioword **iow;
	Area *ap;
{
	register struct ioword **iop;
	register struct ioword *p;

	for (iop = iow; (p = *iop++) != NULL; ) {
		if (p->name != NULL)
			afree((void*)p->name, ap);
		afree((void*)p, ap);
	}
}

#pragma pop_macro("RCSid")
#pragma pop_macro("FSTRING")

#pragma push_macro("MAXFD")
#pragma push_macro("RCSid")
#define RCSid RCSid_exec
#line 1 "exec.c"
/*
 * execute command tree
 */

#ifndef lint
static char *RCSid = "$Id: exec.c,v 1.3 1992/04/25 08:29:52 sjg Exp $";
#endif

#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static int      comexec     ARGS((struct op *t, char **vp, char **ap, int flags));
#ifdef	SHARPBANG
static void     scriptexec  ARGS((struct op *tp, char **ap));
#endif
static void     iosetup     ARGS((struct ioword *iop));
static int      herein      ARGS((char *hname, int sub));
static void     echo        ARGS((char **vp, char **ap));


/*
 * handle systems that don't have F_SETFD
 */
#ifndef F_SETFD
# ifndef MAXFD
#   define  MAXFD 64
# endif
/*
 * a bit field would be smaller, but this
 * will work
 */
static char clexec_tab[MAXFD+1];

/* this is so that main() can clear it */
void
init_clexec()
{
  (void) memset(clexec_tab, 0, sizeof(clexec_tab)-1);
}

int
fd_clexec(fd)
  int fd;
{
  if (fd < sizeof(clexec_tab))
  {
    clexec_tab[fd] = 1;
    return 0;
  }
  return -1;
}
#endif


/*
 * execute command tree
 */
int
execute(t, flags)
	register struct op *t;
	volatile int flags;	/* if XEXEC don't fork */
{
	int i;
	int volatile rv = 0;
	int pv[2];
	register char **ap;
	char *s, *cp;
	struct ioword **iowp;

	if (t == NULL)
		return 0;

	if ((flags&XFORK) && !(flags&XEXEC) && t->type != TPIPE)
		return exchild(t, flags); /* run in sub-process */

	newenv(E_EXEC);
	if (trap)
		runtraps();
 
	if (t->ioact != NULL || t->type == TPIPE) {
		e.savefd = (short*) alloc(sizeofN(short, NUFILE), ATEMP);
		for (i = 0; i < NUFILE; i++)
			e.savefd[i] = 0; /* not redirected */
		/* mark fd 0/1 in-use if pipeline */
		if (flags&XPIPEI)
			e.savefd[0] = -1;
		if (flags&XPIPEO)
			e.savefd[1] = -1;
	}

	/* do redirection, to be restored in quitenv() */
	if (t->ioact != NULL)
		for (iowp = t->ioact; *iowp != NULL; iowp++)
			iosetup(*iowp);

	switch(t->type) {
	  case TCOM:
		e.type = E_TCOM;
		rv = comexec(t, eval(t->vars, DOTILDE),
			     eval(t->args, DOBLANK|DOGLOB|DOTILDE), flags);
		break;

	  case TPAREN:
		exstat = rv = execute(t->left, flags|XFORK);
		break;

	  case TPIPE:
		flags |= XFORK;
		flags &= ~XEXEC;
		e.savefd[0] = savefd(0);
		e.savefd[1] = savefd(1);
		flags |= XPIPEO;
		(void) dup2(e.savefd[0], 0); /* stdin of first */
		while (t->type == TPIPE) {
			openpipe(pv);
			(void) dup2(pv[1], 1);	/* stdout of curr */
			exchild(t->left, flags);
			(void) dup2(pv[0], 0);	/* stdin of next */
			closepipe(pv);
			flags |= XPIPEI;
			t = t->right;
		}
		flags &= ~ XPIPEO;
		(void) dup2(e.savefd[1], 1); /* stdout of last */
		exchild(t, flags);
		(void) dup2(e.savefd[0], 0); /* close pipe in */
		if (!(flags&XBGND))
			exstat = rv = waitlast();
		break;

	  case TLIST:
		while (t->type == TLIST) {
			execute(t->left, 0);
			t = t->right;
		}
		rv = execute(t, 0);
		break;

	  case TASYNC:
		rv = execute(t->left, flags|XBGND|XFORK);
		break;

	  case TOR:
	  case TAND:
		rv = execute(t->left, 0);
		if (t->right != NULL && (rv == 0) == (t->type == TAND))
			rv = execute(t->right, 0);
		break;

	  case TFOR:
		e.type = E_LOOP;
		ap = (t->vars != NULL) ?
			eval(t->vars, DOBLANK|DOGLOB|DOTILDE) : e.loc->argv + 1;
		while ((i = setjmp(e.jbuf)))
			if (i == LBREAK)
				goto Break1;
		while (*ap != NULL) {
			setstr(global(t->str), *ap++);
			rv = execute(t->left, 0);
		}
	  Break1:
		break;

	  case TWHILE:
	  case TUNTIL:
		e.type = E_LOOP;
		while ((i = setjmp(e.jbuf)))
			if (i == LBREAK)
				goto Break2;
		while ((execute(t->left, 0) == 0) == (t->type == TWHILE))
			rv = execute(t->right, 0);
	  Break2:
		break;

	  case TIF:
	  case TELIF:
		if (t->right == NULL)
			break;	/* should be error */
		rv = execute(t->left, 0) == 0 ?
			execute(t->right->left, 0) :
			execute(t->right->right, 0);
		break;

	  case TCASE:
		cp = evalstr(t->str, 0);
		for (t = t->left; t != NULL && t->type == TPAT; t = t->right)
		    for (ap = t->vars; *ap; ap++)
			if ((s = evalstr(*ap, DOPAT)) && gmatch(cp, s))
				goto Found;
		break;
	  Found:
		rv = execute(t->left, 0);
		break;

	  case TBRACE:
		rv = execute(t->left, 0);
		break;

	  case TFUNCT:
		rv = define(t->str, t->left);
		break;

	  case TTIME:
		rv = timex(t, flags);
		break;

	  case TEXEC:		/* an eval'd TCOM */
		s = t->args[0];
		ap = makenv();
#ifndef F_SETFD
		for (i = 0; i < sizeof(clexec_tab); i++)
		  if (clexec_tab[i])
		  {
		    close(i);
		    clexec_tab[i] = 0;
		  }
#endif
		execve(t->str, t->args, ap);
		if (errno == ENOEXEC) {
			char *shell;
#ifdef	SHARPBANG
			scriptexec(t, ap);
#else
			shell = strval(global("EXECSHELL"));
			if (shell && *shell) {
				if ((shell = search(shell,path,1)) == NULL)
					shell = SHELL;
			} else {
				shell = SHELL;
			}
			*t->args-- = t->str;
			*t->args = shell;
			execve(t->args[0], t->args, ap);
			errorf("No shell\n");
#endif	/* SHARPBANG */
		}
		errorf("%s: %s\n", s, strerror(errno));
	}

	quitenv();		/* restores IO */
	if (e.interactive) {	/* flush stdout, shlout */
		fflush(shf[1]);
		fflush(shf[2]);
	}
	if ((flags&XEXEC))
		exit(rv);	/* exit child */
	return rv;
}

/*
 * execute simple command
 */

static int
comexec(t, vp, ap, flags)
	struct op *t;
	register char **ap, **vp;
	int flags;
{
	int i;
	int rv = 0;
	register char *cp;
	register char **lastp;
	register struct tbl *tp = NULL;
	register struct block *l;
	static struct op texec = {TEXEC};
	extern int c_exec(), c_builtin();

	if (flag[FXTRACE])
		echo(vp, ap);

	/* snag the last argument for $_ */
	if ((lastp = ap) && *lastp) {
		while (*++lastp)
			;
		setstr(typeset("_",LOCAL,0),*--lastp);
	}	

	/* create new variable/function block */
	l = (struct block*) alloc(sizeof(struct block), ATEMP);
	l->next = e.loc; e.loc = l;
	newblock();

 Doexec:
	if ((cp = *ap) == NULL)
		cp = ":";
	tp = findcom(cp, flag[FHASHALL]);

	switch (tp->type) {
	  case CSHELL:			/* shell built-in */
		while (tp->val.f == c_builtin) {
			if ((cp = *++ap) == NULL)
				break;
			tp = tsearch(&builtins, cp, hash(cp));
			if (tp == NULL)
				errorf("%s: not builtin\n", cp);
		}
		if (tp->val.f == c_exec) {
			if (*++ap == NULL) {
				e.savefd = NULL; /* don't restore redirection */
				break;
			}
			flags |= XEXEC;
			goto Doexec;
		}
		if ((tp->flag&TRACE))
			e.loc = l->next; /* no local block */
		i = (tp->flag&TRACE) ? 0 : LOCAL;
		while (*vp != NULL)
			(void) typeset(*vp++, i, 0);
		rv = (*tp->val.f)(ap);
		break;

	case CFUNC:			/* function call */
		if (!(tp->flag&ISSET))
			errorf("%s: undefined function\n", cp);
		l->argv = ap;
		for (i = 0; *ap++ != NULL; i++)
			;
		l->argc = i - 1;
		resetopts();
		while (*vp != NULL)
			(void) typeset(*vp++, LOCAL, 0);
		e.type = E_FUNC;
		if (setjmp(e.jbuf))
			rv = exstat; /* return # */
		else
			rv = execute(tp->val.t, 0);
		break;

	case CEXEC:		/* executable command */
		if (!(tp->flag&ISSET)) {
			/*
			 * mlj addition:
			 *
			 * If you specify a full path to a file
			 * (or type the name of a file in .) which
			 * doesn't have execute priv's, it used to
			 * just say "not found".  Kind of annoying,
			 * particularly if you just wrote a script
			 * but forgot to say chmod 755 script.
			 *
			 * This should probably be done in eaccess(),
			 * but it works here (at least I haven't noticed
			 * changing errno here breaking something
			 * else).
			 *
			 * So, we assume that if the file exists, it
			 * doesn't have execute privs; else, it really
			 * is not found.
			 */
			if (access(cp, 0) < 0)
			    shellf("%s: not found\n", cp);
			else
			    shellf("%s: cannot execute\n", cp);
			rv = 1;
			break;
		}

		/* set $_ to program's full path */
		setstr(typeset("_", LOCAL|EXPORT, 0), tp->val.s);
		while (*vp != NULL)
			(void) typeset(*vp++, LOCAL|EXPORT, 0);

		if ((flags&XEXEC)) {
			j_exit();
			if (flag[FMONITOR] || !(flags&XBGND))
			{
#ifdef USE_SIGACT
			  sigaction(SIGINT, &Sigact_dfl, NULL);
			  sigaction(SIGQUIT, &Sigact_dfl, NULL);
#else
			  signal(SIGINT, SIG_DFL);
			  signal(SIGQUIT, SIG_DFL);
#endif
			}
		}

		/* to fork we set up a TEXEC node and call execute */
		texec.left = t;	/* for tprint */
		texec.str = tp->val.s;
		texec.args = ap;
		rv = exchild(&texec, flags);
		break;
	}
	if (rv != 0 && flag[FERREXIT])
		leave(rv);
	return (exstat = rv);
}

#ifdef	SHARPBANG
static void
scriptexec(tp, ap)
	register struct op *tp;
	register char **ap;
{
	char line[LINE];
	register char *cp;
	register int fd, n;
	char *shell;

	shell = strval(global("EXECSHELL"));
	if (shell && *shell) {
		if ((shell = search(shell,path,1)) == NULL)
			shell = SHELL;
	} else {
		shell = SHELL;
	}

	*tp->args-- = tp->str;
	line[0] = '\0';
	if ((fd = open(tp->str,0)) >= 0) {
		if ((n = read(fd, line, LINE - 1)) > 0)
			line[n] = '\0';
		(void) close(fd);
	}
	if (line[0] == '#' && line[1] == '!') {
		cp = &line[2];
		while (*cp && (*cp == ' ' || *cp == '\t'))
			cp++;
		if (*cp && *cp != '\n') {
			*tp->args = cp;
			while (*cp && *cp != '\n' && *cp != ' ' && *cp != '\t')
				cp++;
			if (*cp && *cp != '\n') {
				*cp++ = '\0';
				while (*cp && (*cp == ' ' || *cp == '\t'))
					cp++;
				if (*cp && *cp != '\n') {
					tp->args--;
					tp->args[0] = tp->args[1];
					tp->args[1] = cp;
					while (*cp && *cp != '\n' &&
					       *cp != ' ' && *cp != '\t')
						cp++;
				}
			}
			*cp = '\0';
		} else
			*tp->args = shell;
	} else
		*tp->args = shell;

	(void) execve(tp->args[0], tp->args, ap);
	errorf( "No shell\n" );
}
#endif	/* SHARPBANG */

int
shcomexec(wp)
	register char **wp;
{
	register struct tbl *tp;

	tp = tsearch(&builtins, *wp, hash(*wp));
	if (tp == NULL)
		errorf("%s: shcomexec botch\n", *wp);
	return (*tp->val.f)(wp);
}

/*
 * define function
 */
int
define(name, t)
	char	*name;
	struct op *t;
{
	register struct block *l;
	register struct tbl *tp;

	for (l = e.loc; l != NULL; l = l->next) {
		lastarea = &l->area;
		tp = tsearch(&l->funs, name, hash(name));
		if (tp != NULL && (tp->flag&DEFINED))
			break;
		if (l->next == NULL) {
			tp = tenter(&l->funs, name, hash(name));
			tp->flag = DEFINED|FUNCT;
			tp->type = CFUNC;
		}
	}

	if ((tp->flag&ALLOC))
		tfree(tp->val.t, lastarea);
	tp->flag &= ~(ISSET|ALLOC);

	if (t == NULL) {		/* undefine */
		tdelete(tp);
		return 0;
	}

	tp->val.t = tcopy(t, lastarea);
	tp->flag |= (ISSET|ALLOC);

	return 0;
}

/*
 * add builtin
 */
builtin(name, func)
	char *name;
	int (*func)();
{
	register struct tbl *tp;
	int flag = DEFINED;

	if (*name == '=') {		/* sets keyword variables */
		name++;
		flag |= TRACE;	/* command does variable assignment */
	}

	tp = tenter(&builtins, name, hash(name));
	tp->flag |= flag;
	tp->type = CSHELL;
	tp->val.f = func;
}

/*
 * find command
 * either function, hashed command, or built-in (in that order)
 */
struct tbl *
findcom(name, insert)
	char	*name;
	int	insert;			/* insert if not found */
{
	register struct block *l = e.loc;
	unsigned int h = hash(name);
	register struct	tbl *tp = NULL;
	static struct tbl temp;

	if (strchr(name, '/') != NULL) {
		tp = &temp;
		tp->type = CEXEC;
		tp->flag = 0;	/* make ~ISSET */
		goto Search;
	}
	for (l = e.loc; l != NULL; l = l->next) {
		tp = tsearch(&l->funs, name, h);
		if (tp != NULL && (tp->flag&DEFINED))
			break;
	}
	if (tp == NULL) {
		tp = tsearch(&commands, name, h);
		if (tp != NULL && eaccess(tp->val.s,1) != 0) {
			if (tp->flag&ALLOC)
				afree(tp->val.s, commands.areap);
			tp->type = CEXEC;
			tp->flag = DEFINED;
		}
	}
	if (tp == NULL)
		tp = tsearch(&builtins, name, h);
	if (tp == NULL) {
		tp = tenter(&commands, name, h);
		tp->type = CEXEC;
		tp->flag = DEFINED;
	}
  Search:
	if (tp->type == CEXEC && !(tp->flag&ISSET)) {
		if (!insert) {
			tp = &temp;
			tp->type = CEXEC;
			tp->flag = 0;	/* make ~ISSET */
		}
		name = search(name, path, 1);
		if (name != NULL) {
			tp->val.s = strsave(name,
					    (tp == &temp) ? ATEMP : APERM);
			tp->flag |= ISSET|ALLOC;
		}
	}
	return tp;
}

/*
 * flush executable commands with relative paths
 */
flushcom(all)
	int all;		/* just relative or all */
{
	register struct tbl *tp;

	for (twalk(&commands); (tp = tnext()) != NULL; )
		if ((tp->flag&ISSET) && (all || tp->val.s[0] != '/')) {
			if ((tp->flag&ALLOC))
				afree(tp->val.s, commands.areap);
			tp->flag = DEFINED; /* make ~ISSET */
		}
}

/*
 * search for command with PATH
 */
char *
search(name, path, mode)
	char *name, *path;
	int mode;		/* 0: readable; 1: executable */
{
	register int i;
	register char *sp, *tp;
	struct stat buf;

	if (strchr(name, '/'))
		return (eaccess(name, mode) == 0) ? name : NULL;

	sp = path;
	while (sp != NULL) {
		tp = line;
		for (; *sp != '\0'; tp++)
			if ((*tp = *sp++) == ':') {
				--sp;
				break;
			}
		if (tp != line)
			*tp++ = '/';
		for (i = 0; (*tp++ = name[i++]) != '\0';)
			;
		i = eaccess(line, mode);
		if (i == 0 && (mode != 1 || (stat(line,&buf) == 0 &&
		    (buf.st_mode & S_IFMT) == S_IFREG)))
			return line;
		/* what should we do about EACCES? */
		if (*sp++ == '\0')
			sp = NULL;
	}
	return NULL;
}

/*
 * set up redirection, saving old fd's in e.savefd
 */
static void
iosetup(iop)
	register struct ioword *iop;
{
	register int u = -1;
	char *cp = iop->name;
	extern long lseek();

	if (iop->unit == 0 || iop->unit == 1 || iop->unit == 2)
		e.interactive = 0;
#if 0
	if (e.savefd[iop->unit] != 0)
		errorf("file descriptor %d already redirected\n", iop->unit);
#endif
	e.savefd[iop->unit] = savefd(iop->unit);

	if ((iop->flag&IOTYPE) != IOHERE)
		cp = evalstr(cp, DOTILDE);

	switch (iop->flag&IOTYPE) {
	  case IOREAD:
		u = open(cp, 0);
		break;

	  case IOCAT:
		if ((u = open(cp, 1)) >= 0) {
			(void) lseek(u, (long)0, 2);
			break;
		}
		/* FALLTHROUGH */
	  case IOWRITE:
		u = creat(cp, 0666);
		break;

	  case IORDWR:
		u = open(cp, 2);
		break;

	  case IOHERE:
		u = herein(cp, iop->flag&IOEVAL);
		/* cp may have wrong name */
		break;

	  case IODUP:
		if (*cp == '-')
			close(u = iop->unit);
		else
		if (digit(*cp))
			u = *cp - '0';
		else
			errorf("%s: illegal >& argument\n", cp);
		break;
	}
	if (u < 0)
		errorf("%s: cannot %s\n", cp,
		       (iop->flag&IOTYPE) == IOWRITE ? "create" : "open");
	if (u != iop->unit) {
		(void) dup2(u, iop->unit);
		if (iop->flag != IODUP)
			close(u);
	}

	fopenshf(iop->unit);
}

/*
 * open here document temp file.
 * if unquoted here, expand here temp file into second temp file.
 */
static int
herein(hname, sub)
	char *hname;
	int sub;
{
	int fd;
	FILE * volatile f = NULL;

	f = fopen(hname, "r");
	if (f == NULL)
		return -1;
	setvbuf(f, (char *)NULL, _IOFBF, BUFSIZ);

	if (sub) {
		char *cp;
		struct source *s;
		struct temp *h;

		newenv(E_ERRH);
		if (setjmp(e.jbuf)) {
			if (f != NULL)
				fclose(f);
			quitenv();
			return -1; /* todo: error()? */
		}

		/* set up yylex input from here file */
		s = pushs(SFILE);
		s->u.file = f;
		source = s;
		if (yylex(ONEWORD) != LWORD)
			errorf("exec:herein error\n");
		cp = evalstr(yylval.cp, 0);

		/* write expanded input to another temp file */
		h = maketemp(ATEMP);
		h->next = e.temps; e.temps = h;
		if (h == NULL)
			error();
		f = fopen(h->name, "w+");
		if (f == NULL)
			error();
		setvbuf(f, (char *)NULL, _IOFBF, BUFSIZ);
		fputs(cp, f);
		rewind(f);

		quitenv();
	}
	fd = dup(fileno(f));
	fclose(f);
	return fd;
}

static void
echo(vp, ap)
	register char **vp, **ap;
{
	shellf("+");
	while (*vp != NULL)
		shellf(" %s", *vp++);
	while (*ap != NULL)
		shellf(" %s", *ap++);
	shellf("\n");
}

#pragma pop_macro("RCSid")
#pragma pop_macro("MAXFD")

#pragma push_macro("JEXIT")
#pragma push_macro("JFREE")
#pragma push_macro("JRUN")
#pragma push_macro("JSIGNAL")
#pragma push_macro("JSTOP")
#pragma push_macro("SA_RESTART")
#pragma push_macro("SIGCHLD")
#pragma push_macro("WAIT_T")
#pragma push_macro("WEXITSTATUS")
#pragma push_macro("WIFCORED")
#pragma push_macro("WIFEXITED")
#pragma push_macro("WIFSIGNALED")
#pragma push_macro("WIFSTOPPED")
#pragma push_macro("WSTOPSIG")
#pragma push_macro("WTERMSIG")
#pragma push_macro("getpgid")
#pragma push_macro("killpg")
#pragma push_macro("setpgid")
#pragma push_macro("tcsetpgrp")
#pragma push_macro("waitpid")
#pragma push_macro("RCSid")
#define RCSid RCSid_jobs
#line 1 "jobs.c"
/*
 * Process and job control
 */
#ifndef lint
static char *RCSid = "$Id: jobs.c,v 1.4 1992/04/27 07:14:26 sjg Exp $";
#endif

/*
 * based on version by Ron Natalie, BRL
 * modified by Simon J. Gerraty <sjg@melb.bull.oz.au>
 *
 * TODO:
 *	change Proc table to Job table, with array of pids.
 *	make %+ be jobs, %- be jobs->next.
 *	do not JFREE members of pipeline.
 *	consider procs[] related critical sections.
 *	signal(SIGCHLD, j_sigchld) should be
 *	sigaction(SIGCHLD, sigchld, NULL),
 *	with sigchld.sa_flags = SA_RESTART.
 *	There is a simple work-around if there is no SA_RESTART.
 */

#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/times.h>
#include <sys/wait.h>
#ifdef JOBS
#ifdef _BSD
#include <sys/ioctl.h>
#else
#include <termios.h>
#endif
#endif

#ifdef _BSD
/*
 * These macros are for the benefit of SunOS 4.0.2 and 4.0.3
 * SunOS 4.1.1 already defines most of them.
 * Clearly these are aimed at SunOS, they may work for other
 * BSD systems but I can't promise.
 */
# ifndef WIFSTOPPED
#   define WIFSTOPPED(x)	((x).w_stopval == WSTOPPED)
# endif
# ifndef WIFSIGNALED
#   define WIFSIGNALED(x) ((x).w_stopval != WSTOPPED && (x).w_termsig != 0)
# endif
# ifndef WIFEXITED
#   define WIFEXITED(x)	((x).w_stopval != WSTOPPED && (x).w_termsig == 0)
# endif
# ifndef WSTOPSIG
#   define WSTOPSIG(x)	((x).w_stopsig)
# endif
# ifndef WTERMSIG
#   define WTERMSIG(x)	((x).w_termsig)
# endif
# ifndef WIFCORED
#   define WIFCORED(x)	((x).w_coredump)
# endif
# ifndef WEXITSTATUS
#   define WEXITSTATUS(x)	((x).w_retcode)
# endif
# ifndef HAVE_WAITPID
#   define	waitpid(pid, sp, opts)	wait3(sp, opts, (void*)NULL)
# endif
#else					/* not _BSD */
# ifndef WIFCORED
#   define	WIFCORED(x)	(!!((x)&0x80)) /* non-standard */
# endif
#endif

/* as of P1003.1 Draft 12.3:
 *	pid_t getpgrp(void);		// Get process group id
 *	pid_t setsid(void);		// Create session and Set process group id
 *	int setpgid(pid_t pid, pid_t pgid); // Set process group id for job control
 */


#ifdef JOBS
#ifdef _BSD			/* _BSD 4.* */
#define	setpgid(p, pg)	setpgrp(p, pg)
#define	getpgid(p)	getpgrp(p)
#define	tcsetpgrp(fd,p)	ioctl(fd, TIOCSPGRP, &(p))
#else				/* POSIX-compatible */
#define	getpgid(p)	getpgrp() /* 1003.1 stupidity */
#define	killpg(p, s)	kill(-(p), s)
#endif
#endif


#ifndef	SIGCHLD
#define	SIGCHLD	SIGCLD
#endif
#ifndef WAIT_T
#ifdef _BSD
#define WAIT_T union wait
#else
#define WAIT_T int
#endif
#endif
#ifndef SA_RESTART
#define SA_RESTART	0
#endif

typedef struct Proc Proc;
struct Proc {
	Proc   *next;		/* `procs' list link */
	int	job;		/* job number: %n */
	short	volatile state;	/* proc state */
	short	volatile notify; /* proc state has changed */
	Proc   *prev;		/* prev member of pipeline */
	pid_t	proc;		/* process id */
	pid_t	pgrp;		/* process group if flag[FMONITOR] */
	short	flags;		/* execute flags */
	WAIT_T	status;		/* wait status */
	clock_t	utime, stime;	/* user/system time when JDONE */
	char	com [48];	/* command */
};

/* proc states */
#define	JFREE	0		/* unused proc */
#define	JRUN	1		/* foreground */
#define JEXIT	2		/* exit termination */
#define	JSIGNAL	3		/* signal termination */
#define	JSTOP	4		/* stopped */

static	Proc *procs = NULL;	/* job/process table */

clock_t	j_utime, j_stime;	/* user and system time for last job a-waited */
#ifdef JOBS
# ifdef USE_SIGACT
sigset_t sm_default, sm_sigchld;	/* signal masks */
# else
static	int	sm_default, sm_sigchld;	/* signal masks */
# endif
static	int	our_pgrp;		/* shell's pgrp */
#endif
static	Proc   *j_lastj;		/* last proc created by exchild */
static	int	j_lastjob = 0;		/* last created job */
static	int	j_current = 0;		/* current job */
static	int	j_previous = 0;		/* previous job */

static int      j_waitj     ARGS((Proc *aj, int intr));
static void     j_print     ARGS((Proc *j));
static int      j_newjob    ARGS((void));
static Proc *   j_search    ARGS((int job));
static void	j_sigchld   ARGS((int sig));
  
/* initialize job control */
void
j_init()
{
#ifdef JOBS
# if defined(NTTYDISC) && defined(TIOCSETD)
	int ldisc = NTTYDISC;	/* BSD brain damage */

	if (ttyfd >= 0)
		ioctl(ttyfd, TIOCSETD, &ldisc);
# endif
	our_pgrp = getpgid(0);
	sigchld_caught = 0;
# ifdef USE_SIGACT
	sigemptyset(&sm_default);
	sigemptyset(&sm_sigchld);
	sigaddset(&sm_sigchld, SIGCHLD);
# else
	sm_default = 0;
	sm_sigchld = sigmask(SIGCHLD);
	_TRACE(5, ("j_init: sm_sigchld == 0x%x", sm_sigchld));
# endif
#endif 
#ifndef JOBS
# ifdef USE_SIGACT
	sigaction(SIGCHLD, &Sigact_dfl, NULL);
# else
#   ifdef _SYSV
	signal(SIGCHLD, SIG_DFL);	/* necessary ??? */
#   endif
# endif
#endif
}

/* job cleanup before shell exit */
void
j_exit()
{
	register Proc *j;
	int killed = 0;

#ifdef JOBS
	/* kill stopped jobs */
	for (j = procs; j != NULL; j = j->next)
		if (j->state == JSTOP) {
			killed ++;
			killpg(j->pgrp, SIGHUP);
			killpg(j->pgrp, SIGCONT);
		}
	if (killed)
		sleep(1);
#endif
	j_notify();

#ifdef JOBS
	if (flag[FMONITOR]) {
		flag[FMONITOR] = 0;
		j_change();
	}
#endif
}

#ifdef JOBS
/* turn job control on or off according to flag[FMONITOR] */
void
j_change()
{
#ifdef USE_SIGACT
	static struct sigaction old_tstp, old_ttin, old_ttou;
#else
	static handler_t old_tstp, old_ttin, old_ttou;
#endif
	if (flag[FMONITOR]) {
		if (ttyfd < 0) {
			flag[FMONITOR] = 0;
			shellf("job control requires tty\n");
			return;
		}
#ifdef USE_SIGACT
		Sigact.sa_handler = j_sigchld;
		sigemptyset(&Sigact.sa_mask);
		Sigact.sa_flags = SA_RESTART;
		sigaction(SIGCHLD, &Sigact, NULL);
		Sigact.sa_flags = 0;
		sigtraps[SIGCHLD].sig_dfl = 1; /* restore on fork */
		sigaction(SIGTSTP, &Sigact_ign, &old_tstp);
		sigtraps[SIGTSTP].sig_dfl = 1;
		sigaction(SIGTTIN, &Sigact_ign, &old_ttin);
		sigtraps[SIGTTIN].sig_dfl = 1;
		sigaction(SIGTTOU, &Sigact_ign, &old_ttou);
		sigtraps[SIGTTOU].sig_dfl = 1;
#else
		(void) signal(SIGCHLD, j_sigchld);
		sigtraps[SIGCHLD].sig_dfl = 1; /* restore on fork */
		old_tstp = signal(SIGTSTP, SIG_IGN);
		sigtraps[SIGTSTP].sig_dfl = 1;
		old_ttin = signal(SIGTTIN, SIG_IGN);
		sigtraps[SIGTTIN].sig_dfl = 1;
		old_ttou = signal(SIGTTOU, SIG_IGN);
		sigtraps[SIGTTOU].sig_dfl = 1;
#endif
#ifdef USE_SIGACT
		sigprocmask(SIG_SETMASK, &sm_default, NULL);
#else
		sigsetmask(sm_default);
#endif
		tcsetpgrp(ttyfd, our_pgrp);
	} else {
#ifdef USE_SIGACT
		sigaction(SIGCHLD, &Sigact_dfl, NULL);
		sigaction(SIGTSTP, &old_tstp, NULL);
		sigtraps[SIGTSTP].sig_dfl = 0;
		sigaction(SIGTTIN, &old_ttin, NULL);
		sigtraps[SIGTTIN].sig_dfl = 0;
		sigaction(SIGTTOU, &old_ttou, NULL);
		sigtraps[SIGTTOU].sig_dfl = 0;
#else
		(void) signal(SIGCHLD, SIG_DFL);
		(void) signal(SIGTSTP, old_tstp);
		sigtraps[SIGTSTP].sig_dfl = 0;
		(void) signal(SIGTTIN, old_ttin);
		sigtraps[SIGTTIN].sig_dfl = 0;
		(void) signal(SIGTTOU, old_ttou);
		sigtraps[SIGTTOU].sig_dfl = 0;
#endif
	}
}
#endif

/* execute tree in child subprocess */
int
exchild(t, flags)
	struct op *t;
	int flags;
{
	register int i;
	register Proc *j;
	int rv = 0;
	int forksleep;

	flags &= ~XFORK;
	if ((flags&XEXEC))
		return execute(t, flags);

	/* get free Proc entry */
	for (j = procs; j != NULL; j = j->next)
		if (j->state == JFREE)
			goto Found;
	j = (Proc*) alloc(sizeof(Proc), APERM);
	j->next = procs;
	j->state = JFREE;
	procs = j;
  Found:

	j->prev = ((flags&XPIPEI)) ? j_lastj : NULL;
	j->proc = j->pgrp = 0;
	j->flags = flags;
	j->job = (flags&XPIPEI) ? j_lastjob : j_newjob();
	snptreef(j->com, sizeof(j->com), "%T", t); /* save proc's command */
	j->com[sizeof(j->com)-1] = '\0';
	j->state = JRUN;

	/* stdio buffer must be flushed and invalidated */
	for (i = 0; i < NUFILE; i++)
		flushshf(i);

	/* create child process */
	forksleep = 0;
#ifdef JOBS
	/* don't allow SIGCHLD until we are ready */

#ifdef USE_SIGACT
	sigprocmask(SIG_SETMASK, &sm_sigchld, NULL);
# else
	sigsetmask(sm_sigchld);
# endif
#endif
	while ((i = fork()) < 0 && errno == EAGAIN && forksleep < 32) {
		if (forksleep) {
			sleep(forksleep);
			forksleep <<= 1;
		} else
			forksleep = 1;
	}
	if (i < 0) {
		j->state = JFREE;
		errorf("cannot fork - try again\n");
	}
	j->proc = (i != 0) ? i : getpid();

#ifdef JOBS
	/* job control set up */
	if (flag[FMONITOR] && !(flags&XXCOM))
	{
	  j->pgrp = !(flags&XPIPEI) ? j->proc : j_lastj->pgrp;
	  /* do in both parent and child to avoid fork race condition */
	  if (!(flags&XBGND))
	    tcsetpgrp(ttyfd, j->pgrp); /* could be trouble */
	  setpgid(j->proc, j->pgrp);
	}
#endif
	j_lastj = j;

	if (i == 0) {		/* child */
		e.oenv = NULL;
		if (flag[FTALKING])
			restoresigs();
		if ((flags&XBGND) && !flag[FMONITOR])
		{
#ifdef USE_SIGACT
		  sigaction(SIGINT, &Sigact_dfl, NULL);
		  sigaction(SIGQUIT, &Sigact_dfl, NULL);
		  if (flag[FTALKING])
		    sigaction(SIGTERM, &Sigact_dfl, NULL);
#else
		  signal(SIGINT, SIG_IGN);
		  signal(SIGQUIT, SIG_IGN);
		  if (flag[FTALKING])
		    signal(SIGTERM, SIG_DFL);
#endif
			if (!(flags&XPIPEI)) {
				i = open("/dev/null", 0);
				(void) dup2(i, 0);
				close(i);
			}
		}
		for (j = procs; j != NULL; j = j->next)
			j->state = JFREE;
		ttyfd = -1;
#ifdef JOBS
		/* is this needed in the child? */
# ifdef USE_SIGACT
		sigprocmask(SIG_SETMASK, &sm_default, NULL);
# else
		sigsetmask(sm_default);
# endif
#endif
		flag[FMONITOR] = flag[FTALKING] = 0;
		cleartraps();
		execute(t, flags|XEXEC); /* no return */
		/* NOTREACHED */
	}

	/* shell (parent) stuff */
	if ((flags&XBGND)) { /* async statement */
		async = j->proc;
		j_previous = j_current;
		j_current = j->job;
		if (flag[FTALKING])
			j_print(j);
	}
#ifdef JOBS
# ifdef USE_SIGACT
	sigprocmask(SIG_SETMASK, &sm_default, NULL);
# else
	sigsetmask(sm_default);
# endif
#endif
	if (!(flags&XBGND))
	{ 		/* sync statement */
		if (!(flags&XPIPE))
			rv = j_waitj(j, 0);
	}

	return rv;
}

/* wait for last job: pipeline or $() sub-process */
int
waitlast()
{
	return j_waitj(j_lastj, 0);
}

/* wait for job to complete or change state */
static int
j_waitj(aj, intr)
	Proc *aj;
	int intr;		/* interruptable */
{
	register Proc *j;
	int rv = 1;
	int ttysig = 0;

#ifdef JOBS
	if (flag[FMONITOR])
	{
# ifdef USE_SIGACT
	  sigprocmask(SIG_SETMASK, &sm_sigchld, NULL);
# else
	  _TRACE(5, ("j_waitj: sigsetmask(sm_sigchld==0x%x)", sm_sigchld));
	  sigsetmask(sm_sigchld);
# endif
	}
#endif
	/* wait for all members of pipeline */
	for (j = aj; j != NULL; j = j->prev) {
		/* wait for job to finish, stop, or ^C of built-in wait */
		while (j->state == JRUN) {
#ifdef JOBS
			if (flag[FMONITOR])
			{
			  /*
			   * 91-07-07 <sjg@sun0>
			   * we don't want to wait for a signal
			   * that has already arrived :-)
			   */
			  if (!sigchld_caught)
			  {
# ifdef USE_SIGACT
			    sigsuspend(&sm_default);
# else
			    _TRACE(4, ("j_waitj: sigpause(%d), sigchld_caught==%d", sm_default, sigchld_caught));
			    sigpause(sm_default);
			    _TRACE(4, ("j_waitj: sigpause() returned %d, sigchld_caught==%d", errno, sigchld_caught));
# endif /* USE_SIGACT */
			  }
			}
			else
#endif /* JOBS */
				j_sigchld(0);
			/*
			 * Children to reap
			 */
			if (sigchld_caught)
			  j_reapchld();
			_TRACE(4, ("j_waitj: j->proc==%d, j->com=='%s', j->state==0x%hx, j->status==0x%x, j->notify==%hd", j->proc, j->com, j->state, j->status, j->notify));
			
			if (sigtraps[SIGINT].set && intr)
				goto Break;
		}
		if (j->state == JEXIT) { /* exit termination */
			if (!(j->flags&XPIPEO))
				rv = WEXITSTATUS(j->status);
			j->notify = 0;
		} else
		if (j->state == JSIGNAL) { /* signalled to death */
			if (!(j->flags&XPIPEO))
				rv = 0x80 + WTERMSIG(j->status);
			if (WTERMSIG(j->status) == SIGINT ||
			    (WTERMSIG(j->status) == SIGPIPE &&
			     (j->flags&XPIPEO)))
				j->notify = 0;
			if (WTERMSIG(j->status) == SIGINT ||
			    WTERMSIG(j->status) == SIGQUIT)
				ttysig = 1;
		} else
#ifdef JOBS
		if (j->state == JSTOP)
			if (WSTOPSIG(j->status) == SIGTSTP)
				ttysig = 1;
#else
		;
#endif
	}

	/* compute total child time for time statement */
	for (j = aj; j != NULL; j = j->prev)
		j_utime += j->utime, j_stime += j->stime;

	/* find new current job */
#ifdef JOBS
	if (aj->state == JSTOP) {
		j_previous = j_current;
		j_current = aj->job;
	} else {
#else
	if (1) {
#endif
		int hijob = 0;

		/* todo: this needs to be done in j_notify */
		/* todo: figure out what to do with j_previous */
		j_current = 0;
		for (j = procs; j != NULL; j = j->next)
			if ((j->state == JRUN || j->state == JSTOP)
			    && j->job > hijob) {
				hijob = j->job;
				j_current = j->job;
			}
	}

  Break:
#ifdef JOBS
	if (flag[FMONITOR])
	{
	  /* reset shell job control state */
# ifdef USE_SIGACT
	  sigprocmask(SIG_SETMASK, &sm_default, NULL);
# else
	  sigsetmask(sm_default);
# endif
	  tcsetpgrp(ttyfd, our_pgrp);
	}
#endif
	if (ttysig)
		fputc('\n', shlout);
	j_notify();

	return rv;
}

/* SIGCHLD handler to reap children */
/*
 * 91-07-07 <sjg@sun0>
 * On the Sun SS2 this appears to get called
 * too quickly!
 * So just record the event and process later.
 */
static void
j_sigchld(sig)
	int sig;
{
	sigchld_caught++;	/* acknowledge it */
}

/*
 * 91-07-07 <sjg@sun0>
 * This now gets called when j_sigchld()
 * has recorded some signals...
 */
j_reapchld()
{
	struct tms t0, t1;
#if defined(JOBS)
# ifdef USE_SIGACT
	sigset_t	sm_old;

	sigprocmask(SIG_SETMASK, NULL, &sm_old);
# else
	int sm_old;

	sm_old = sigblock(0);	/* just get current mask */
	_TRACE(5, ("j_reapchld: sm_old==0x%x, sigchld_caught==%d", sm_old, sigchld_caught));
# endif
#endif
	(void) times(&t0);

	do {
		register Proc *j;
		int pid;
		WAIT_T status;
#ifdef JOBS
		if (flag[FMONITOR])
			pid = waitpid(-1, &status, (WNOHANG|WUNTRACED));
		else
#endif
			pid = wait(&status);
		if (pid < 0 && errno == ECHILD)
		{
		  /* no children - what are we doing here? */
		  _TRACE(5, ("j_reapchld: no children"));
		  sigchld_caught = 0;
		  break;
		}
		if (pid <= 0)	/* return if would block (0) ... */
			break;	/* ... or no children or interrupted (-1) */
		(void) times(&t1);

		_TRACE(5, ("j_reapchld: looking for pid==%d", pid));

		for (j = procs; j != NULL; j = j->next)
		{
		  _TRACE(6, ("j_reapchld: j->proc==%d, j->com=='%s', j->state==0x%hx, j->status==0x%x, j->notify==%hd", j->proc, j->com, j->state, j->status, j->notify));
		  if (j->state != JFREE && j->proc == pid)
		    goto Found;
		}
		_TRACE(5, ("j_reapchld: did not find pid==%d", pid));
		continue;
	  Found:
		_TRACE(5, ("j_reapchld: found pid==%d", pid));
		j->notify = 1;
		j->status = status;
#ifdef JOBS
		if (WIFSTOPPED(status))
			j->state = JSTOP;
		else
#endif
		if (WIFEXITED(status))
			j->state = JEXIT;
		else
		if (WIFSIGNALED(status))
			j->state = JSIGNAL;

		/* compute child's time */
		/* todo: what does a stopped job do? */
		j->utime = t1.tms_cutime - t0.tms_cutime;
		j->stime = t1.tms_cstime - t0.tms_cstime;
		t0 = t1;
#ifdef JOBS
# ifdef USE_SIGACT
		sigprocmask(SIG_BLOCK, &sm_sigchld, NULL);
# else
		sigblock(sm_sigchld);
# endif
#endif
		if (--sigchld_caught < 0) /* reduce the count */
		  sigchld_caught = 0;
#ifdef JOBS
# ifdef USE_SIGACT
		sigprocmask(SIG_SETMASK, &sm_old, NULL);
# else
		_TRACE(5, ("j_reapchld: j->proc==%d, j->com=='%s', j->state==0x%hx, j->status==0x%x, j->notify==%hd", j->proc, j->com, j->state, j->status, j->notify));
		sigsetmask(sm_old); /* restore old mask */
# endif
#endif
		
#ifdef JOBS
	} while (flag[FMONITOR]);
#else
	} while (0);		/* only once if wait()ing */
#endif
/*
 * this should be safe
 */
#if defined(_SYSV) && !defined(JOBS) && !defined(USE_SIGACT)
	signal(SIGCHLD, j_sigchld);
#if 0
	/* why was this here??? */
	signal(SIGCLD, SIG_DFL);
#endif
#endif
}

j_reap()
{
  if (sigchld_caught)
    j_reapchld();
/*
 * now done in j_reapchld()
 */
#if 0 && defined(_SYSV) && !defined(JOBS) && !defined(USE_SIGACT)
	signal(SIGCHLD, j_sigchld);
	signal(SIGCLD, SIG_DFL);
#endif
	return(0);
}

/* wait for child, interruptable */
int
waitfor(job)
	int job;
{
	register Proc *j;

	if (job == 0 && j_current == 0)
		errorf("no current job\n");
	j = j_search((job == 0) ? j_current : job);
	if (j == NULL)
		errorf("no such job: %d\n", job);
	if (flag[FTALKING])
		j_print(j);
	if (e.interactive) {	/* flush stdout, shlout */
		fflush(shf[1]);
		fflush(shf[2]);
	}
	return j_waitj(j, 1);
}

/* kill (built-in) a job */
void
j_kill(job, sig)
	int job;
	int sig;
{
	register Proc *j;

	j = j_search(job);
	if (j == NULL)
		errorf("cannot find job\n");
	if (j->pgrp == 0) {	/* !flag[FMONITOR] */
		if (kill(j->proc, sig) < 0) /* todo: all member of pipeline */
			errorf("kill: %s\n", strerror(errno));
#ifdef JOBS
	} else {
		if (sig == SIGTERM || sig == SIGHUP)
			(void) killpg(j->pgrp, SIGCONT);
		if (killpg(j->pgrp, sig) < 0)
			errorf("killpg: %s\n", strerror(errno));
#endif
	}
}

#ifdef JOBS

/* fg and bg built-ins */
int
j_resume(job, bg)
	int job;
	int bg;
{
	register Proc *j; 
	
	j = j_search((job == 0) ? j_current : job);
	if (j == NULL)
		errorf("cannot find job\n", job);
	if (j->pgrp == 0)
		errorf("job not job-controlled\n");

	j->state = JRUN;
	j_print(j);
	flushshf(2);

	if (!bg)
  		tcsetpgrp(ttyfd, j->pgrp); /* attach shell to job */
	if (killpg(j->pgrp, SIGCONT) < 0)
		errorf("cannot continue job %%%d\n", job);
	if (!bg)
		return j_waitj(j, 0);
	return 0;
}

#endif

/* list jobs for jobs built-in */
void
j_jobs()
{
	register Proc *j; 

	for (j = procs; j != NULL; j = j->next)
		if (j->state != JFREE)
			j_print(j);
}

/* list jobs for top-level notification */
void
j_notify()
{
	register Proc *j; 

	/*
	 * since reaping is no longer done in the signal handler
	 * we had better try here...
	 */
	if (sigchld_caught)
	  j_reapchld();
	
	for (j = procs; j != NULL; j = j->next) {
		if (j->state == JEXIT && !flag[FTALKING])
			j->notify = 0;
		if (j->state != JFREE && j->notify)
			j_print(j);
		if (j->state == JEXIT || j->state == JSIGNAL)
			j->state = JFREE;
		j->notify = 0;
	}
}

static void
j_print(j)
	register Proc *j;
{
	char buf [64], *s = buf;

	switch (j->state) {
	  case JRUN:
		s = "Running";
		break;

#ifdef JOBS
	  case JSTOP:
		strcpy(buf, "Stopped ");
		s = strchr(sigtraps[WSTOPSIG(j->status)].mess, '(');
		if (s != NULL)
			strcat(buf, s);
		s = buf;
		break;
#endif

	  case JEXIT: {
		int rv;
		rv = WEXITSTATUS(j->status);
		sprintf(buf, "Done (%d)", rv);
		if (rv == 0)
			*strchr(buf, '(') = 0;
		j->state = JFREE;
		} break;

	  case JSIGNAL: {
		int sig = WTERMSIG(j->status);
		char *n = sigtraps[sig].mess;
		if (n != NULL)
			sprintf(buf, "%s", n);
		else
			sprintf(buf, "Signal %d", sig);
		if (WIFCORED(j->status))
			strcat(buf, " - core dumped");
		j->state = JFREE;
		} break;

	  default:
		s = "Hideous job state";
		j->state = JFREE;
		break;
	}
	shellf("%%%-2d%c %5d %-20s %s%s\n", j->job,
	       (j_current==j->job) ? '+' : (j_previous==j->job) ? '-' : ' ',
	       j->proc, s, j->com, (j->flags&XPIPEO) ? "|" : "");
}

/* convert % sequence to job number */
int
j_lookup(cp)
	char *cp;
{
	register Proc *j;
	int len, job = 0;

	if (*cp == '%')		/* leading % is optional */
		cp++;
	switch (*cp) {
	  case '\0':
	  case '+':
		job = j_current;
		break;

	  case '-':
		job = j_previous;
		break;

	  case '0': case '1': case '2': case '3': case '4':
	  case '5': case '6': case '7': case '8': case '9': 
		job = atoi(cp);
		break;

	  case '?':		/* %?string */
		for (j = procs; j != NULL; j = j->next)
			if (j->state != JFREE && strstr(j->com, cp+1) != NULL)
				job = j->job;
		break;

	  default:		/* %string */
		len = strlen(cp);
		for (j = procs; j != NULL; j = j->next)
			if (j->state != JFREE && strncmp(cp, j->com, len) == 0)
				job = j->job;
		break;
	}
	if (job == 0)
		errorf("%s: no such job\n", cp);
	return job;
}

/* are any stopped jobs ? */
#ifdef JOBS
int
j_stopped()
{
	register Proc *j; 

	for (j = procs; j != NULL; j = j->next)
		if (j->state == JSTOP)
			return 1;
	return 0;
}
#endif

/* create new job number */
static int
j_newjob()
{
	register Proc *j; 
	register int max = 0;
	
	j_lastjob ++;
	for (j = procs; j != NULL; j = j->next)
		if (j->state != JFREE && j->job)
			if (j->job > max)
				max = j->job;
	if (j_lastjob > max)
		j_lastjob = max + 1;
	return j_lastjob;
}

/* search for job by job number */
static Proc *
j_search(job)
	int job;
{
	register Proc *j;

	for (j = procs; j != NULL; j = j->next)
		if (j->state != JFREE && job == j->job && !(j->flags&XPIPEO))
			return j;
	return NULL;
}

#pragma pop_macro("RCSid")
#pragma pop_macro("waitpid")
#pragma pop_macro("tcsetpgrp")
#pragma pop_macro("setpgid")
#pragma pop_macro("killpg")
#pragma pop_macro("getpgid")
#pragma pop_macro("WTERMSIG")
#pragma pop_macro("WSTOPSIG")
#pragma pop_macro("WIFSTOPPED")
#pragma pop_macro("WIFSIGNALED")
#pragma pop_macro("WIFEXITED")
#pragma pop_macro("WIFCORED")
#pragma pop_macro("WEXITSTATUS")
#pragma pop_macro("WAIT_T")
#pragma pop_macro("SIGCHLD")
#pragma pop_macro("SA_RESTART")
#pragma pop_macro("JSTOP")
#pragma pop_macro("JSIGNAL")
#pragma pop_macro("JRUN")
#pragma pop_macro("JFREE")
#pragma pop_macro("JEXIT")

#pragma push_macro("CLK_TCK")
#pragma push_macro("RCSid")
#define RCSid RCSid_c_sh
#line 1 "c_sh.c"
/*
 * built-in Bourne commands
 */

#ifndef lint
static char *RCSid = "$Id: c_sh.c,v 1.3 1992/04/25 08:29:52 sjg Exp $";
#endif

#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>		/* getcwd */
#include <sys/times.h>

static char *   clocktos    ARGS((clock_t t));

#ifndef CLK_TCK
#define CLK_TCK 60			/* 60HZ */
#endif

int
c_label(wp)
	char **wp;
{
	return 0;
}

int
c_shift(wp)
	register char **wp;
{
	register struct block *l = e.loc;
	register int n;

	n = wp[1] ? evaluate(wp[1]) : 1;
	if (l->argc < n) {
		errorf("nothing to shift\n");
		return (1);
	}
	l->argv[n] = l->argv[0];
	l->argv += n;
	l->argc -= n;
	return 0;
}

int
c_umask(wp)
	register char **wp;
{
	register int i;
	register char *cp;

	if ((cp = wp[1]) == NULL) {
		i = umask(0);
		umask(i);
		printf("%#3.3o\n", i);	/* should this be shell output? */
	} else {
		for (i = 0; *cp>='0' && *cp<='7'; cp++)
			i = i*8 + (*cp-'0');
		umask(i);
	}
	return 0;
}

int
c_dot(wp)
	char **wp;
{
	char *file, *cp;

	if ((cp = wp[1]) == NULL)
		return 0;
	file = search(cp, path, 0);
	if (file == NULL)
		errorf("%s: not found\n", cp);
	if (include(file))
		return exstat;
	return -1;
}

int
c_wait(wp)
	char **wp;
{
	register char *cp;

	wp++;
	cp = *wp;
	if (cp == NULL) cp = "%";
	/* todo: print status ? */
	return waitfor(j_lookup(cp));
}

int
c_read(wp)
	register char **wp;
{
	register int c = 0;
	FILE *f = stdin;
	int expand = 1;
	register char *cp;

	for (wp++; (cp = *wp) != NULL && *cp++ == '-'; wp++) {
		while (*cp) switch (*cp++) {
		  case 'e':
			expand = 1;
			break;
		  case 'r':
			expand = 0;
			break;
		  case 'u':
			if (!digit(*cp) || (f = shf[*cp++-'0']) == NULL)
				errorf("bad -u argument\n");
			break;
		}
	}

	if (*wp == NULL)
		errorf("missing name\n");
	if ((cp = strchr(*wp, '?')) != NULL) {
		*cp = 0;
		if (flag[FTALKING]) {
			shellf("%s ", cp+1);
			fflush(shlout);
		}
	}

	for (; *wp != NULL; wp++) {
		for (cp = line; cp <= line+LINE; ) {
			if (c == '\n')
				break;
			c = getc(f);
			if (c == EOF)
				return 1;
			if (expand && c == '\\') {
				c = getc(f);
				if (c == '\n')
					c = 0;
				else
					*cp++ = c;
				continue;
			}
			if (c == '\n' || (wp[1] && ctype(c, C_IFS)))
				break;
			*cp++ = c;
		}
		*cp = 0;
		setstr(global(*wp), line);
	}
	return 0;
}

int
c_eval(wp)
	register char **wp;
{
	register struct source *s;

	s = pushs(SWORDS);
	s->u.strv = wp+1;
	return shell(s);
}

void setsig ARGS((struct trap *p, handler_t f));

int
c_trap(wp)
	register char **wp;
{
	int i;
	char *s;
	register struct trap *p;

	wp++;
	if (*wp == NULL) {
		for (p = sigtraps, i = SIGNALS; --i >= 0; p++) {
			if (p->trap != NULL)
				shellf("%s: %s\n", p->name, p->trap);
		}
		return 0;
	}

	s = (gettrap(*wp) == NULL) ? *wp++ : NULL; /* get command */
	if (s != NULL && s[0] == '-' && s[1] == '\0')
		s = NULL;

	/* set/clear traps */
	while (*wp != NULL) {
		p = gettrap(*wp++);
		if (p == NULL)
			errorf("trap: bad signal %s\n", wp[-1]);
		if (p->trap != NULL)
			afree((void*)p->trap, APERM);
		p->trap = NULL;
		if (s != NULL) {
			if (strlen(s) != 0) {
				p->trap = strsave(s, APERM);
				setsig(p, trapsig);
			} else
				setsig(p, (handler_t)SIG_IGN);
		} else
			/* todo: restore to orginal value */
		    setsig(p,
		       (p->signal==SIGINT || p->signal==SIGQUIT) && flag[FTALKING]
			   ? (handler_t)SIG_IGN : (handler_t)SIG_DFL);
	}
	return 0;
}

void
setsig(p, f)
	register struct trap *p;
	void (*f)();
{
  if (p->signal == 0)
    return;
#ifdef USE_SIGACT
  sigaction(p->signal, &Sigact_ign, &Sigact);
  if (Sigact.sa_handler != SIG_IGN || p->ourtrap)
  {
    p->ourtrap = 1;
    Sigact.sa_handler = f;
    sigaction(p->signal, &Sigact, NULL);
    sigemptyset(&Sigact.sa_mask);
    Sigact.sa_flags = 0;
  }
#else
  if (signal(p->signal, SIG_IGN) != SIG_IGN || p->ourtrap)
  {
    p->ourtrap = 1;
    signal(p->signal, f);
  }
#endif
}

int
c_return(wp)
	char **wp;
{
	wp++;
	if (*wp != NULL)
		exstat = getn(*wp);
	quitenv();		/* pop E_TCOM */
	while (e.type == E_LOOP || e.type == E_EXEC)
		quitenv();
	if (e.type == E_FUNC)
		longjmp(e.jbuf, 1);
	leave(exstat);
}

int
c_brkcont(wp)
	register char **wp;
{
	int quit;

	quit = wp[1] == NULL ? 1 : getn(wp[1]);
	quitenv();		/* pop E_TCOM */
	while (e.type == E_LOOP || e.type == E_EXEC) {
		if (e.type == E_LOOP && --quit <= 0)
			longjmp(e.jbuf, (*wp[0] == 'b') ? LBREAK : LCONTIN);
		quitenv();
	}
	errorf("cannot %s\n", wp[0]);
}


/* 91-05-27 <sjg>
 * we are supposed to not exit first try
 * if there are stopped jobs.
 */
int
c_exit(wp)
	char **wp;
{
	register char *cp;
	static int extry = 0;
	
#ifdef JOBS
	if (extry++ == 0)
	{
	  if (flag[FMONITOR] && j_stopped()) /* todo: only once */
	  {
	    errorf("There are stopped jobs\n");
	    return 1;
	  }
	}
#endif
	e.oenv = NULL;
	if ((cp = wp[1]) != NULL)
		exstat = getn(cp);
	leave(exstat);
}

int
c_set(wp)
	register char **wp;
{
	struct block *l = e.loc;
	register char **owp = wp;
	register char *cp;
	int old_fmonitor = flag[FMONITOR];

	if ((cp = *++wp) == NULL) {
		static char * const args [] = {"set", "-", NULL};
		extern int c_typeset ARGS((char **args));
		return c_typeset(args);
	}
	
	for (; (cp = *wp) != NULL && (*cp == '-' || *cp == '+');) {
		int i, n = *cp++ == '-'; /* set or clear flag */
		wp++;
		if (*cp == '\0') {
			if (n)
				flag[FXTRACE] = flag[FVERBOSE] = 0;
			break;
		}
		if (*cp == '-')
			goto setargs;
		for (; *cp != '\0'; cp++)
			if (*cp == 'o') {
				if (*wp == NULL) {
					printoptions();
					return 0;
				}
				i = option(*wp++);
				if (i == 0)
					shellf("%s: unknown option\n", *--wp);
				flag[i] = n;
				if (i == FEMACS && n)
					flag[FVI] = 0;
				else if (i == FVI && n)
					flag[FEMACS] = 0;
			} else if (*cp>='a' && *cp<='z')
				flag[FLAG(*cp)] = n;
			else
				errorf("%c: bad flag\n", *cp);
		if (flag[FTALKING])
			flag[FERREXIT] = 0;
	}

#ifdef JOBS
	if (old_fmonitor != flag[FMONITOR])
		j_change();
#endif

	/* set $# and $* */
	if (*wp != NULL) {
	  setargs:
		owp = --wp;
		wp[0] = l->argv[0]; /* save $0 */
		while (*++wp != NULL)
			*wp = strsave(*wp, &l->area);
		l->argc = wp - owp - 1;
		l->argv = (char **) alloc(sizeofN(char *, l->argc+2), &l->area);
		for (wp = l->argv; (*wp++ = *owp++) != NULL; )
			;
		resetopts();
	}
	return 0;
}

int
c_unset(wp)
	register char **wp;
{
	register char *id;
	int flagf = 0;

	for (wp++; (id = *wp) != NULL && *id == '-'; wp++)
		if (*++id == 'f')
			flagf++;
	for (; (id = *wp) != NULL; wp++)
		if (!flagf) {	/* unset variable */
			unset(global(id));
		} else {	/* unset function */
			define(id, (struct op *)NULL);
		}
	return 0;
}

int
c_ulimit(wp)
	register char **wp;
{
	extern int do_ulimit();

	return do_ulimit(wp[1], wp[2]);
}

int
c_times(wp)
	char **wp;
{
	struct tms all;

	(void) times(&all);
	printf("Shell: ");
	printf("%8s user ", clocktos(all.tms_utime));
	printf("%8s system\n", clocktos(all.tms_stime));
	printf("Kids:  ");
	printf("%8s user ", clocktos(all.tms_cutime));
	printf("%8s system\n", clocktos(all.tms_cstime));

	return 0;
}

/*
 * time pipeline (really a statement, not a built-in comman)
 */
int
timex(t, f)
	struct op *t;
	int f;
{
	int rv;
	struct tms t0, t1;
	clock_t t0t, t1t;
	extern clock_t j_utime, j_stime; /* computed by j_wait */

	j_utime = j_stime = 0;
	t0t = times(&t0);
	rv = execute(t->left, f);
	t1t = times(&t1);

	shellf("%8s real ", clocktos(t1t - t0t));
	shellf("%8s user ",
	       clocktos(t1.tms_utime - t0.tms_utime + j_utime));
	shellf("%8s system ",
	       clocktos(t1.tms_stime - t0.tms_stime + j_stime));
	shellf("\n");

	return rv;
}

static char *
clocktos(t)
	clock_t t;
{
	static char temp[20];
	register int i;
	register char *cp = temp + sizeof(temp);

#if CLK_TCK != 100		/* convert to 1/100'ths */
	t = (t < 1000000000/CLK_TCK) ?
		(t * 100) / CLK_TCK : (t / CLK_TCK) * 100;
#endif

	*--cp = '\0';
	*--cp = 's';
	for (i = -2; i <= 0 || t > 0; i++) {
		if (i == 0)
			*--cp = '.';
		*--cp = '0' + (char)(t%10);
		t /= 10;
	}
	return cp;
}

/* dummy function, special case in comexec() */
int
c_exec(wp)
	char ** wp;
{
	return 0;
}

/* dummy function, special case in comexec() */
int
c_builtin(wp)
	char ** wp;
{
	return 0;
}

extern	int c_test();		/* in test.c */

const struct builtin shbuiltins [] = {
	{"=:", c_label},
	{"=.", c_dot},
	{"[", c_test},
	{"=builtin", c_builtin},
	{"=exec", c_exec},
	{"=shift", c_shift},
	{"=wait", c_wait},
	{"read", c_read},
	{"=eval", c_eval},
	{"=trap", c_trap},
	{"=break", c_brkcont},
	{"=continue", c_brkcont},
	{"=exit", c_exit},
	{"=return", c_return},
	{"=set", c_set},
	{"unset", c_unset},
	{"umask", c_umask},
	{"test", c_test},
	{"=times", c_times},
	{"ulimit", c_ulimit},
	{NULL, NULL}
};

#pragma pop_macro("RCSid")
#pragma pop_macro("CLK_TCK")

#pragma push_macro("RCSid")
#define RCSid RCSid_c_ksh
#line 1 "c_ksh.c"
/*
 * built-in Korn commands: c_*
 */

#ifndef lint
static char *RCSid = "$Id: c_ksh.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <setjmp.h>


int
c_hash(wp)
	register char **wp;
{
	register struct tbl *tp, **p;

	wp++;
	if (*wp == NULL) {
		for (p = tsort(&commands); (tp = *p++) != NULL; )
			if ((tp->flag&ISSET))
				printf("%s\n", tp->val.s);
		return 0;
	}

	if (strcmp(*wp, "-r") == 0)
		flushcom(1);
	while (*wp != NULL)
		findcom(*wp++, 1);
	return 0;
}

int
c_cd(wp)
	register char **wp;
{
	char path [PATH];
	char newd [PATH];
	register char *cp;
	register char *dir;
	register char *cdpath;
	register char *rep;
	register char *pwd = NULL, *oldpwd = NULL;
	register int done = 0;
	register int prt = 0;
	register struct tbl *v_pwd = NULL, *v_oldpwd = NULL;

	if ((dir = wp[1]) == NULL && (dir = strval(global("HOME"))) == NULL)
		errorf("no home directory");

	v_pwd = global("PWD");
	if ((pwd = strval(v_pwd)) == null) {
		setstr(v_pwd, getcwd(path, (size_t)PATH));
		pwd = strval(v_pwd);
	}

	if (wp[1] != NULL && (rep = wp[2]) != NULL) {
		/*
		 * Two arg version: cd pat rep
		 */
		if (strlen(pwd) - strlen(dir) + strlen(rep) >= PATH)
			errorf("substitution too long\n");
		cp = strstr(pwd, dir);
		if (cp == NULL)
			errorf("substitution failed\n");
		strncpy(path, pwd, cp - pwd);		/* first part */
		strcpy(path + (cp - pwd), rep);		/* replacement */
		strcat(path, cp + strlen(dir)); 	/* last part */
		dir = strsave(path, ATEMP);
		prt = 1;
	} else if (dir[0] == '-' && dir[1] == '\0') {
		/*
		 * Change to previous dir: cd -
		 */
		dir = strval(v_oldpwd = global("OLDPWD"));
		prt = 1;
	}
	if (dir[0] == '/' || (dir[0] == '.' && (dir[1] == '/' ||
	    (dir[1] == '.' && dir[2] == '/')))) {
		/*
		 * dir is an explicitly named path, so no CDPATH search
		 */
		cleanpath(pwd, dir, newd);
		if (chdir(newd) < 0)
			errorf("%s: bad directory\n", newd);
		else if (prt)
			shellf("%s\n", newd);
		flushcom(0);
	} else {
		/*
		 * search CDPATH for dir
		 */
		cdpath = strval(global("CDPATH"));
		while ( !done && cdpath != NULL ) {
			cp = path;
			while (*cdpath && *cdpath != ':')
				*cp++ = *cdpath++;
			if (*cdpath == '\0')
				cdpath = NULL;
			else
				cdpath++;
			if (prt = (cp > path)) {
				*cp++ = '/';
				(void) strcpy( cp, dir );
				cp = path;
			} else
				cp = dir;

			cleanpath(pwd, cp, newd);
			if (chdir(newd) == 0)
				done = 1;
		} while (!done && cdpath != NULL);
		if (!done)
			errorf("%s: bad directory\n", dir);
		if (prt)
			shellf("%s\n", newd);
		flushcom(0);
	}

	/*
	 * Keep track of OLDPWD and PWD
	 */
	oldpwd = pwd;
	pwd = newd;
	if (!v_oldpwd)
		v_oldpwd = global("OLDPWD");
	if (oldpwd && *oldpwd)
		setstr(v_oldpwd, oldpwd);
	else
		unset(v_oldpwd);
	if (*pwd)
		setstr(v_pwd, pwd);
	else
		unset(v_pwd);

	return 0;
}

int
c_print(wp)
	register char **wp;
{
	int nl = 1;
	int expand = 1;
	FILE *f = stdout;

	for (wp++; *wp != NULL && **wp == '-'; wp++) {
		register char *s = *wp + 1;
		if (*s == '\0') {
			wp++;
			break;
		}
		while (*s) switch (*s++) {
		  case 'n':
			nl = 0;
			break;
		  case 'e':
			expand = 1;
			break;
		  case 'r':
			expand = 0;
			break;
		  case 'u':
			if (!digit(*s) || (f = shf[*s++-'0']) == NULL)
				errorf("bad -u argument\n");
			break;
		}
	}

	while (*wp != NULL) {
		register char *s = *wp;
		register int c;
		while ((c = *s++) != '\0')
			if (expand && c == '\\') {
				switch ((c = *s++)) {
				case 'b': c = '\b'; break;
				case 'c': nl = 0; continue; /* AT&T brain damage */
				case 'f': c = '\f'; break;
				case 'n': c = '\n'; break;
				case 'r': c = '\r'; break;
				case 't': c = '\t'; break;
				case 'v': c = 0x0B; break;
				case '0': case '1': case '2': case '3':
				case '4': case '5': case '6': case '7':
					c = c - '0';
					if (*s >= '0' && *s <= '7')
						c = 8*c + *s++ - '0';
					if (*s >= '0' && *s <= '7')
						c = 8*c + *s++ - '0';
					break;
				case '\\': break;
				default:
					putc('\\', f);
				}
				putc(c, f);
			} else
				putc(c, f);
		if (*++wp != NULL)
			putc(' ', f);
	}
	if (nl)
		putc('\n', f);
	return 0;
}

/* todo: handle case where id is both lexical and command */
int
c_whence(wp)
	register char **wp;
{
	register struct tbl *tp;
	char *id;
	int vflag = 0;
	int ret = 0;

	for (wp++; (id = *wp) != NULL && *id == '-'; wp++)
		if (id[1] == 'v')
			vflag = 1;

	while ((id = *wp++) != NULL) {
		tp = tsearch(&lexicals, id, hash(id));
		if (tp == NULL)
			tp = findcom(id, 0);
		if (vflag)
			switch ((tp == NULL) ? CNONE : tp->type) {
			  case CNONE:
				printf("%s is unknown\n", id);
				ret = 1;
				break;
			  case CSHELL:
				printf("%s is a shell builtin\n", id);
				break;
			  case CFUNC:
				printf("%s is a function\n", id);
				fptreef(stdout, "function %s %T\n", id, tp->val.t);
				break;
			  case CEXEC:
				printf("%s is %s\n", id,
				       (tp->flag&ISSET) ? tp->val.s : "unknown");
				if (!(tp->flag&ISSET))
					ret = 1;
				break;
			  case CALIAS:
				printf("%s is the alias '%s'\n", id, tp->val.s);
				break;
			  case CKEYWD:
				printf("%s is a shell keyword\n", id);
				break;
			  default:
				printf("%s is *GOK*\n", id);
				break;
			}
		else
			switch ((tp == NULL) ? CNONE : tp->type) {
			  case CNONE:
				printf("\n");
				ret = 1;
				break;
			  case CSHELL:
				printf("builtin %s\n", id);
				break;
			  case CFUNC:
				printf("%s\n", id);
				break;
			  case CEXEC:
				printf("%s\n", (tp->flag&ISSET) ? tp->val.s : "");
				if (!(tp->flag&ISSET))
					ret = 1;
				break;
			  case CALIAS:
				printf("%s\n", tp->val.s);
				break;
			  case CKEYWD:
				printf("%s\n", id);
				break;
			  default:
				printf("*GOK*\n");
				break;
			}
	}
	return ret;
}

/* typeset, export, and readonly */
int
c_typeset(wp)
	register char **wp;
{
	register char *id;
	struct block *l = e.loc;
	register struct tbl *vp, **p;
	int fset = 0, fclr = 0;
	int thing = 0, func = 0, local = 0;

	switch (**wp) {
	  case 'e':		/* export */
		fset |= EXPORT;
		break;
	  case 'r':		/* readonly */
		fset |= RDONLY;
		break;
	  case 't':		/* typeset */
		local = 1;
		break;
	}

	for (wp++; (id = *wp) != NULL && (*id == '-' || *id == '+'); wp++) {
		int flag = 0;
		thing = *id;
		while (*++id != '\0') switch (*id) {
		  case 'f':
			flag |= FUNCT;
			func = 1;
			break;
		  case 'i':
			flag |= INTEGER;
			break;
		  case 'r':
			flag |= RDONLY;
			break;
		  case 'x':
			flag |= EXPORT;
			break;
		  case 't':
			flag |= TRACE;
			break;
		  default:
			errorf("unknown flag -%c\n", *id);
		}
		if (flag != 0) { /* + or - with options */
			if (thing == '-')
				fset |= flag;
			else
				fclr |= flag;
			thing = 0;
		}
	}

	/* list variables and attributes */
	if (*wp == NULL) {
		for (l = e.loc; l != NULL; l = l->next) {
		    for (p = tsort((func==0) ? &l->vars : &l->funs);
			 (vp = *p++) != NULL; )
			if ((vp->flag&ISSET))
			    if (thing == 0 && fclr == 0 && fset == 0) {
				printf("typeset ");
				if ((vp->flag&INTEGER))
					printf("-i ");
				if ((vp->flag&EXPORT))
					printf("-x ");
				if ((vp->flag&RDONLY))
					printf("-r ");
				if ((vp->flag&TRACE)) 
					printf("-t ");
				printf("%s\n", vp->name);
			    } else
			    if (thing == '+' ||
				(fclr && (vp->flag&fclr) == fclr)) {
				printf("%s\n", vp->name);
			    } else
			    if (thing == '-' ||
				(fset && (vp->flag&fset) == fset)) {
				if (fset&FUNCT)
				    printf("function %s\n", vp->name);
				else
				    printf("%s=%s\n", vp->name, strval(vp));
			    }
		}
		return (0);
	}

	if (local)
		fset |= LOCAL;
	for (; *wp != NULL; wp++)
#if 0
		if (func) {
		} else
#endif
		if (typeset(*wp, fset, fclr) == NULL)
			errorf("%s: not identifier\n", *wp);
	return 0;
}
	
int
c_alias(wp)
	register char **wp;
{
	register struct table *t = &lexicals;
	register struct tbl *ap, **p;
	int rv = 0;

	if (*++wp != NULL && strcmp(*wp, "-d") == 0) {
		t = &homedirs;
		wp++;
	}

	if (*wp == NULL)
		for (p = tsort(t); (ap = *p++) != NULL; )
			if (ap->type == CALIAS && (ap->flag&DEFINED))
				printf("%s='%s'\n", ap->name, ap->val.s);

	for (; *wp != NULL; wp++) {
		register char *id = *wp;
		register char *val = strchr(id, '=');

		if (val == NULL) {
			ap = tsearch(t, id, hash(id));
			if (ap != NULL && ap->type == CALIAS && (ap->flag&DEFINED))
				printf("%s='%s'\n", ap->name, ap->val.s);
			else
				rv = 1;
		} else {
			*val++ = '\0';
			ap = tenter(t, id, hash(id));
			if (ap->type == CKEYWD)
				errorf("cannot alias keyword\n");
			if ((ap->flag&ALLOC)) {
				afree((void*)ap->val.s, APERM);
				ap->flag &= ~(ALLOC|ISSET);
			}
			ap->type = CALIAS;
			ap->val.s = strsave(val, APERM);
			ap->flag |= DEFINED|ALLOC|ISSET;
		}
	}
	return rv;
}

int
c_unalias(wp)
	register char **wp;
{
	register struct table *t = &lexicals;
	register struct tbl *ap;

	if (*++wp != NULL && strcmp(*wp, "-d") == 0) {
		t = &homedirs;
		wp++;
	}

	for (; *wp != NULL; wp++) {
		ap = tsearch(t, *wp, hash(*wp));
		if (ap == NULL || ap->type != CALIAS)
			continue;
		if ((ap->flag&ALLOC))
			afree((void*)ap->val.s, APERM);
		ap->flag &= ~(DEFINED|ISSET|ALLOC);
	}
	return 0;
}

int
c_let(wp)
	char **wp;
{
	int rv = 1;

	for (wp++; *wp; wp++)
		rv = evaluate(*wp) == 0;
	return rv;
}

int
c_jobs(wp)
	char **wp;
{
	j_jobs();
	return 0;
}

#ifdef JOBS
int
c_fgbg(wp)
	register char **wp;
{
	int bg = strcmp(*wp, "bg") == 0;

	if (!flag[FMONITOR])
		errorf("Job control not enabled\n");
	wp++;
	j_resume(j_lookup((*wp == NULL) ? "%" : *wp), bg);
	return 0;
}
#endif

int
c_kill(wp)
	register char **wp;
{
	register char *cp;
	int sig = 15;		/* SIGTERM */
	int rv = 0;
	int n;
	int gotsig = FALSE;

	if (*++wp == NULL)
		errorf("Usage: kill [-l] [-signal] {pid|job} ...\n");
	if (strcmp(*wp, "-l") == 0) {
		register struct trap *p = sigtraps;
		for (sig = 0; sig < SIGNALS; sig++, p++)
			if (p->signal)
				printf("%2d %8s %s\n", p->signal, p->name, p->mess);
		return 0;
	}

	for (; (cp = *wp) != NULL; wp++)
		if (*cp == '-' && gotsig == FALSE && *(wp+1) != NULL) {
			struct trap *p;
			gotsig = FALSE;
			if (digit(*(cp+1))) {
				if ((n = atoi(cp+1)) < SIGNALS) {
					sig = n;
					gotsig = TRUE;
				} else if (kill(n, sig) < 0) {
					shellf("%s: %s\n", cp, strerror(errno));
					rv++;
				}
			} else {
				p = gettrap(cp+1);
				if (p == NULL)
					errorf("bad signal %s\n", cp+1);
				sig = p->signal;
				gotsig = TRUE;
			}
		} else {
			gotsig = FALSE;
			if (digit(*cp) || (*cp == '-' && digit(*(cp+1)))) {
				if (kill(atoi(cp), sig) < 0) {
					shellf("%s: %s\n", cp, strerror(errno));
					rv++;
				}
			} else
			if (*cp == '%')
				j_kill(j_lookup(cp), sig);
			else
				errorf("invalid argument\n");
		}
	return rv;
}

#ifdef EMACS
int
c_bind(wp)
	register char **wp;
{
	int macro = 0;
	register char *cp;

	for (wp++; (cp = *wp) != NULL && *cp == '-'; wp++)
		if (cp[1] == 'm')
			macro = 1;

	if (*wp == NULL)	/* list all */
		x_bind((char*)NULL, (char*)NULL, 0);

	for (; *wp != NULL; wp++) {
		cp = strchr(*wp, '=');
		if (cp != NULL)
			*cp++ = 0;
		x_bind(*wp, cp, macro);
	}

	return 0;
}
#endif

extern	c_fc();
extern	c_getopts();

const struct builtin kshbuiltins [] = {
	{"cd", c_cd},
	{"print", c_print},
	{"getopts", c_getopts},
	{"=typeset", c_typeset},
	{"=export", c_typeset},
	{"=readonly", c_typeset},
	{"whence", c_whence},
	{"=alias", c_alias},
	{"unalias", c_unalias},
	{"hash", c_hash},
	{"let", c_let},
	{"fc", c_fc},
	{"jobs", c_jobs},
	{"kill", c_kill},
#ifdef JOBS
	{"fg", c_fgbg},
	{"bg", c_fgbg},
#endif
#ifdef EMACS
	{"bind", c_bind},
#endif
	{NULL, NULL}
};

#pragma pop_macro("RCSid")

#pragma push_macro("BAND")
#pragma push_macro("BBINOP")
#pragma push_macro("BINOP")
#pragma push_macro("BOR")
#pragma push_macro("BUNOP")
#pragma push_macro("EOI")
#pragma push_macro("FILBDEV")
#pragma push_macro("FILCDEV")
#pragma push_macro("FILEQ")
#pragma push_macro("FILEX")
#pragma push_macro("FILFIFO")
#pragma push_macro("FILGID")
#pragma push_macro("FILGZ")
#pragma push_macro("FILID")
#pragma push_macro("FILNT")
#pragma push_macro("FILOT")
#pragma push_macro("FILRD")
#pragma push_macro("FILREG")
#pragma push_macro("FILSETG")
#pragma push_macro("FILSETU")
#pragma push_macro("FILSOCK")
#pragma push_macro("FILSTCK")
#pragma push_macro("FILSYM")
#pragma push_macro("FILTT")
#pragma push_macro("FILUID")
#pragma push_macro("FILWR")
#pragma push_macro("INTEQ")
#pragma push_macro("INTGE")
#pragma push_macro("INTGT")
#pragma push_macro("INTLE")
#pragma push_macro("INTLT")
#pragma push_macro("INTNE")
#pragma push_macro("LPAREN")
#pragma push_macro("OPERAND")
#pragma push_macro("OPTION")
#pragma push_macro("PAREN")
#pragma push_macro("RPAREN")
#pragma push_macro("STEQL")
#pragma push_macro("STNEQ")
#pragma push_macro("STNZE")
#pragma push_macro("STZER")
#pragma push_macro("UNOP")
#pragma push_macro("UNOT")
#pragma push_macro("RCSid")
#define RCSid RCSid_c_test
#line 1 "c_test.c"
/*
 * test(1); version 7-like  --  author Erik Baalbergen
 * modified by Eric Gisin to be used as built-in.
 * modified by Arnold Robbins to add SVR3 compatibility
 * (-x -c -b -p -u -g -k) plus Korn's -L -nt -ot -ef and new -S (socket).
 */

#ifndef lint
static char *RCSid = "$Id: c_test.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <sys/stat.h>

/* test(1) accepts the following grammar:
	oexpr	::= aexpr | aexpr "-o" oexpr ;
	aexpr	::= nexpr | nexpr "-a" aexpr ;
	nexpr	::= primary ! "!" primary
	primary	::= unary-operator operand
		| operand binary-operator operand
		| operand
		| "(" oexpr ")"
		;
	unary-operator ::= "-r"|"-w"|"-x"|"-f"|"-d"|"-c"|"-b"|"-p"|
		"-u"|"-g"|"-k"|"-s"|"-t"|"-z"|"-n"|"-o"|"-O"|"-G"|"-L"|"-S";

	binary-operator ::= "="|"!="|"-eq"|"-ne"|"-ge"|"-gt"|"-le"|"-lt"|
			"-nt"|"-ot"|"-ef";
	operand ::= <any legal UNIX file name>
*/

#define EOI	0
#define FILRD	1
#define FILWR	2
#define FILREG	3
#define FILID	4
#define FILGZ	5
#define FILTT	6
#define STZER	7
#define STNZE	8
#define STEQL	9
#define STNEQ	10
#define INTEQ	11
#define INTNE	12
#define INTGE	13
#define INTGT	14
#define INTLE	15
#define INTLT	16
#define UNOT	17
#define BAND	18
#define BOR	19
#define LPAREN	20
#define RPAREN	21
#define OPERAND	22
#define FILEX	23
#define FILCDEV	24
#define FILBDEV	25
#define FILFIFO	26
#define FILSETU	27
#define FILSETG	28
#define FILSTCK	29
#define FILSYM	30
#define FILNT	31
#define FILOT	32
#define FILEQ	33
#define FILSOCK	34
#define	FILUID	35
#define	FILGID	36
#define	OPTION	37

#define UNOP	1
#define BINOP	2
#define BUNOP	3
#define BBINOP	4
#define PAREN	5

struct t_op {
	char *op_text;
	short op_num, op_type;
} const ops [] = {
	{"-r",	FILRD,	UNOP},
	{"-w",	FILWR,	UNOP},
	{"-x",	FILEX,	UNOP},
	{"-f",	FILREG,	UNOP},
	{"-d",	FILID,	UNOP},
	{"-c",	FILCDEV,UNOP},
	{"-b",	FILBDEV,UNOP},
	{"-p",	FILFIFO,UNOP},
	{"-u",	FILSETU,UNOP},
	{"-g",	FILSETG,UNOP},
	{"-k",	FILSTCK,UNOP},
	{"-s",	FILGZ,	UNOP},
	{"-t",	FILTT,	UNOP},
	{"-z",	STZER,	UNOP},
	{"-n",	STNZE,	UNOP},
#if 0				/* conficts with binary -o */
	{"-o",	OPTION,	UNOP},
#endif
	{"-U",	FILUID,	UNOP},
	{"-G",	FILGID,	UNOP},
	{"-L",	FILSYM,	UNOP},
	{"-S",	FILSOCK,UNOP},
	{"=",	STEQL,	BINOP},
	{"!=",	STNEQ,	BINOP},
	{"-eq",	INTEQ,	BINOP},
	{"-ne",	INTNE,	BINOP},
	{"-ge",	INTGE,	BINOP},
	{"-gt",	INTGT,	BINOP},
	{"-le",	INTLE,	BINOP},
	{"-lt",	INTLT,	BINOP},
	{"-nt",	FILNT,	BINOP},
	{"-ot",	FILOT,	BINOP},
	{"-ef",	FILEQ,	BINOP},
	{"!",	UNOT,	BUNOP},
	{"-a",	BAND,	BBINOP},
	{"-o",	BOR,	BBINOP},
	{"(",	LPAREN,	PAREN},
	{")",	RPAREN,	PAREN},
	{0,	0,	0}
};

char **t_wp;
struct t_op const *t_wp_op;

static void syntax();

int
c_test(wp)
	char **wp;
{
	int	res;

	t_wp = wp+1;
	if (strcmp(wp[0], "[") == 0) {
		while (*wp != NULL)
			wp++;
		if (strcmp(*--wp, "]") != 0)
			errorf("[: missing ]\n");
		*wp = NULL;
	}
	res = *t_wp == NULL || !oexpr(t_lex(*t_wp));

	if (*t_wp != NULL && *++t_wp != NULL)
		syntax(*t_wp, "unknown operand");

	return res;
}

static void
syntax(op, msg)
	char	*op;
	char	*msg;
{
	if (op && *op)
		errorf("test: %s: %s\n", op, msg);
	else
		errorf("test: %s\n", msg);
}

oexpr(n)
{
	int res;

	res = aexpr(n);
	if (t_lex(*++t_wp) == BOR)
		return oexpr(t_lex(*++t_wp)) || res;
	t_wp--;
	return res;
}

aexpr(n)
{
	int res;

	res = nexpr(n);
	if (t_lex(*++t_wp) == BAND)
		return aexpr(t_lex(*++t_wp)) && res;
	t_wp--;
	return res;
}

nexpr(n)
	int n;			/* token */
{
	if (n == UNOT)
		return !nexpr(t_lex(*++t_wp));
	return primary(n);
}

primary(n)
	int n;			/* token */
{
	register char *opnd1, *opnd2;
	int res;

	if (n == EOI)
		syntax(NULL, "argument expected");
	if (n == LPAREN) {
		res = oexpr(t_lex(*++t_wp));
		if (t_lex(*++t_wp) != RPAREN)
			syntax(NULL, "closing paren expected");
		return res;
	}
	if (t_wp_op && t_wp_op->op_type == UNOP) {
		/* unary expression */
		if (*++t_wp == NULL && n != FILTT)
			syntax(t_wp_op->op_text, "argument expected");
		switch (n) {
		  case OPTION:
			return flag[option(*t_wp)];
		  case STZER:
			return strlen(*t_wp) == 0;
		  case STNZE:
			return strlen(*t_wp) != 0;
		  case FILTT:
			if (!digit(**t_wp))
				return filstat("0", n);
		  default:	/* all other FIL* */
			return filstat(*t_wp, n);
		}
	}
	opnd1 = *t_wp;
	(void) t_lex(*++t_wp);
	if (t_wp_op && t_wp_op->op_type == BINOP) {
		struct t_op const *op = t_wp_op;

		if ((opnd2 = *++t_wp) == (char *)0)
			syntax(op->op_text, "argument expected");
		
		switch (op->op_num) {
		case STEQL:
			return strcmp(opnd1, opnd2) == 0;
		case STNEQ:
			return strcmp(opnd1, opnd2) != 0;
		case INTEQ:
			return evaluate(opnd1) == evaluate(opnd2);
		case INTNE:
			return evaluate(opnd1) != evaluate(opnd2);
		case INTGE:
			return evaluate(opnd1) >= evaluate(opnd2);
		case INTGT:
			return evaluate(opnd1) > evaluate(opnd2);
		case INTLE:
			return evaluate(opnd1) <= evaluate(opnd2);
		case INTLT:
			return evaluate(opnd1) < evaluate(opnd2);
		case FILNT:
			return newerf (opnd1, opnd2);
		case FILOT:
			return olderf (opnd1, opnd2);
		case FILEQ:
			return equalf (opnd1, opnd2);
		}
	}
	t_wp--;
	return strlen(opnd1) > 0;
}

filstat(nm, mode)
	char *nm;
{
	struct stat s;
	
	switch (mode) {
	case FILRD:
		return eaccess(nm, 4) == 0;
	case FILWR:
		return eaccess(nm, 2) == 0;
	case FILEX:
		return eaccess(nm, 1) == 0;
	case FILREG:
		return stat(nm, &s) == 0 && (s.st_mode & S_IFMT) == S_IFREG;
	case FILID:
		return stat(nm, &s) == 0 && (s.st_mode & S_IFMT) == S_IFDIR;
	case FILCDEV:
		return stat(nm, &s) == 0 && (s.st_mode & S_IFMT) == S_IFCHR;
	case FILBDEV:
		return stat(nm, &s) == 0 && (s.st_mode & S_IFMT) == S_IFBLK;
	case FILFIFO:
#ifdef S_IFIFO
		return stat(nm, &s) == 0 && (s.st_mode & S_IFMT) == S_IFIFO;
#else
		return 0;
#endif
	case FILSETU:
		return stat(nm, &s) == 0 && (s.st_mode & S_ISUID) == S_ISUID;
	case FILSETG:
		return stat(nm, &s) == 0 && (s.st_mode & S_ISGID) == S_ISGID;
	case FILSTCK:
		return stat(nm, &s) == 0 && (s.st_mode & S_ISVTX) == S_ISVTX;
	case FILGZ:
		return stat(nm, &s) == 0 && s.st_size > 0L;
	case FILTT:
		return isatty(getn(nm));
	  case FILUID:
		return stat(nm, &s) == 0 && s.st_uid == geteuid();
	  case FILGID:
		return stat(nm, &s) == 0 && s.st_gid == getegid();
#ifdef S_IFLNK
	case FILSYM:
		return lstat(nm, &s) == 0 && (s.st_mode & S_IFMT) == S_IFLNK;
#endif
#ifdef S_IFSOCK
	case FILSOCK:
		return stat(nm, &s) == 0 && (s.st_mode & S_IFMT) == S_IFSOCK;
#endif
	  default:
		return 1;
	}
}

int
t_lex(s)
	register char *s;
{
	register struct t_op const *op = ops;

	if (s == 0) {
		t_wp_op = (struct t_op *)0;
		return EOI;
	}
	while (op->op_text) {
		if (strcmp(s, op->op_text) == 0) {
			t_wp_op = op;
			return op->op_num;
		}
		op++;
	}
	t_wp_op = (struct t_op *)0;
	return OPERAND;
}

newerf (f1, f2)
char *f1, *f2;
{
	struct stat b1, b2;

	return (stat (f1, &b1) == 0 &&
		stat (f2, &b2) == 0 &&
		b1.st_mtime > b2.st_mtime);
}

olderf (f1, f2)
char *f1, *f2;
{
	struct stat b1, b2;

	return (stat (f1, &b1) == 0 &&
		stat (f2, &b2) == 0 &&
		b1.st_mtime < b2.st_mtime);
}

equalf (f1, f2)
char *f1, *f2;
{
	struct stat b1, b2;

	return (stat (f1, &b1) == 0 &&
		stat (f2, &b2) == 0 &&
		b1.st_dev == b2.st_dev &&
		b1.st_ino == b2.st_ino);
}

#pragma pop_macro("RCSid")
#pragma pop_macro("UNOT")
#pragma pop_macro("UNOP")
#pragma pop_macro("STZER")
#pragma pop_macro("STNZE")
#pragma pop_macro("STNEQ")
#pragma pop_macro("STEQL")
#pragma pop_macro("RPAREN")
#pragma pop_macro("PAREN")
#pragma pop_macro("OPTION")
#pragma pop_macro("OPERAND")
#pragma pop_macro("LPAREN")
#pragma pop_macro("INTNE")
#pragma pop_macro("INTLT")
#pragma pop_macro("INTLE")
#pragma pop_macro("INTGT")
#pragma pop_macro("INTGE")
#pragma pop_macro("INTEQ")
#pragma pop_macro("FILWR")
#pragma pop_macro("FILUID")
#pragma pop_macro("FILTT")
#pragma pop_macro("FILSYM")
#pragma pop_macro("FILSTCK")
#pragma pop_macro("FILSOCK")
#pragma pop_macro("FILSETU")
#pragma pop_macro("FILSETG")
#pragma pop_macro("FILREG")
#pragma pop_macro("FILRD")
#pragma pop_macro("FILOT")
#pragma pop_macro("FILNT")
#pragma pop_macro("FILID")
#pragma pop_macro("FILGZ")
#pragma pop_macro("FILGID")
#pragma pop_macro("FILFIFO")
#pragma pop_macro("FILEX")
#pragma pop_macro("FILEQ")
#pragma pop_macro("FILCDEV")
#pragma pop_macro("FILBDEV")
#pragma pop_macro("EOI")
#pragma pop_macro("BUNOP")
#pragma pop_macro("BOR")
#pragma pop_macro("BINOP")
#pragma pop_macro("BBINOP")
#pragma pop_macro("BAND")

#pragma push_macro("ERR")
#pragma push_macro("GETOPTEOF")
#pragma push_macro("getopt")
#pragma push_macro("optarg")
#pragma push_macro("optind")
#pragma push_macro("RCSid")
#define RCSid RCSid_getopts
#define optind ksh_optind
#define optarg ksh_optarg
#define getopt ksh_getopt
#line 1 "getopts.c"
/*
 * Reimplementation of SysVr3 sh builtin command "getopts" for S5R2 shell.
 *
 * created by Arnold Robbins
 * modified by Doug Gwyn
 * modified for PD ksh by Eric Gisin
 */

#ifndef lint
static char *RCSid = "$Id: getopts.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <setjmp.h>

/*
 * The following is derived from getopt() source placed into the public
 * domain by AT&T (the only time they're known to have done that).
 *
 * It has been modified somewhat to fit into the context of the shell.
 *
 * -D"FASCIST" if you really want to strictly enforce ALL the
 * Command Syntax Standard rules (not recommended).
 */

#define GETOPTEOF	(-1)
#define ERR(S, C)	shellf("%s%c\n", (S), (C))

static	int	optind;
static char    *optarg;
static int	sp;

static int
getopt(argc, argv, opts)
	int argc;
	register char **argv, *opts;
{
	register int c;
	register char *cp;

	if (sp == 1)
		if (optind >= argc ||
		   argv[optind][0] != '-' || argv[optind][1] == '\0')
			return(GETOPTEOF);
		else if (strcmp(argv[optind], "--") == 0) {
			optind++;
			return(GETOPTEOF);
		}
	c = argv[optind][sp];
	if (c == ':' || (cp=strchr(opts, c)) == NULL) {
		ERR("illegal option -- ", c);
		if (argv[optind][++sp] == '\0') {
			optind++;
			sp = 1;
		}
		optarg = NULL;
		return('?');
	}
	if (*++cp == ':') {
#ifdef FASCIST
		if (sp != 1) {
			ERR("option must not be grouped -- ", c );
			optind++;
			sp = 1;
			optarg = NULL;
			return('?');
		} else
#endif
		if (argv[optind][sp+1] != '\0') {
#ifdef FASCIST
			ERR("option must be followed by whitespace -- ", c );
			optind++;
			sp = 1;
			optarg = NULL;
			return('?');
#else
			optarg = &argv[optind++][sp+1];
#endif
		} else if (++optind >= argc) {
			ERR("option requires an argument -- ", c);
			sp = 1;
			optarg = NULL;
			return('?');
		} else
			optarg = argv[optind++];
		sp = 1;
	} else {
		if (argv[optind][++sp] == '\0') {
			sp = 1;
			optind++;
		}
		optarg = NULL;
	}
	return(c);
}

/*
 * The following were created by Arnold Robbins.
 */

/* resetopts --- magic code for when OPTIND is reset to 1 */

void
resetopts ()
{
	optind = 1;
	sp = 1;
}

int
c_getopts(wp)
	char **wp;
{
	int ret;
	register int argc;
	char temp[2];
	char *optstr;			/* list of options */
	char *name;			/* variable to get flag val */
	char **argv;

	if ((optstr = *++wp) == NULL || (name = *++wp) == NULL)
		errorf("missing arguments\n");

	for (argc = 1; wp[argc] != NULL; argc++)
		;

	if (argc > 1)
		ret = getopt(argc, wp, optstr);
	else {
		if (**(e.loc->argv) == '\0') {
			/*
			 * When c_getopts gets called from comexec() it
			 * doesn't set up argc/argv in the local block.
			 * Maybe this should be done in newblock() but
			 * I'm not sure about the implications, and this
			 * is the only place I've been bitten so far...
			 * JRM
			 */
			argc = e.loc->next->argc;
			argv = e.loc->next->argv;
		} else {
			argc = e.loc->argc;
			argv = e.loc->argv;
		}
		ret = getopt(argc+1, argv, optstr);

	}

	/*
	 * set the OPTIND variable in any case, to handle "--" skipping
	 * unless it's 1, which would trigger a reset
	 */

	if (optind != 1)
		setint(global("OPTIND"), (long)optind);

	if (ret == GETOPTEOF)		/* end of args */
		return (1);

	/*
	 * else, got an arg, set the various shell variables
	 */

	if (optarg != NULL)
		setstr(global("OPTARG"), optarg);

	temp[0] = (char) ret;
	temp[1] = '\0';
	setstr(global(name), temp);

	return (0);
}
#pragma pop_macro("RCSid")
#pragma pop_macro("optind")
#pragma pop_macro("optarg")
#pragma pop_macro("getopt")
#pragma pop_macro("GETOPTEOF")
#pragma pop_macro("ERR")

#pragma push_macro("RLIMIT_FSIZE")
#pragma push_macro("RCSid")
#define RCSid RCSid_do_ulimit
#line 1 "do_ulimit.c"
/*
	ulimit -- handle "ulimit" builtin

	Eric Gisin, September 1988
	Adapted to PD KornShell. Removed AT&T code.

	last edit:	06-Jun-1987	D A Gwyn

	This started out as the BRL UNIX System V system call emulation
	for 4.nBSD, and was later extended by Doug Kingston to handle
	the extended 4.nBSD resource limits.  It now includes the code
	that was originally under case SYSULIMIT in source file "xec.c".
*/

#ifndef lint
static char *RCSid = "$Id: do_ulimit.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#if defined(_BSD) || defined(_BSD_SYSV)
#include <sys/time.h>
#include <sys/resource.h>
#else
#define	RLIMIT_FSIZE	2
#endif

extern	long ulimit();

int
do_ulimit(a1, a2)
	char	*a1, *a2;
{
	register int	c;
	long		i;
#if defined(_BSD) || defined(_BSD_SYSV)
	struct rlimit	limit;		/* data being gotten/set */
	int		softonly = 0;	/* set => soft limit, clear => hard limit */
	int		factor = 1024;	/* unit scaling (1K or 1) */
#endif
	int	command = RLIMIT_FSIZE;

	if (a1 && (*a1 == '-'))		/* DAG -- Gould added first test */
	{	c = *++a1;		/* DAG */
#if defined(_BSD) || defined(_BSD_SYSV)
		if (c >= 'A' && c <= 'Z')
		{
			++softonly;
			c += 'a' - 'A';	/* DAG -- map to lower-case */
		}
#endif
		switch(c)
		{
#if defined(_BSD) || defined(_BSD_SYSV)
			case 'c':
				command = RLIMIT_CORE;
				break;
			case 'd':
				command = RLIMIT_DATA;
				break;
			case 'm':
				command = RLIMIT_RSS;
				break;
			case 's':
				command = RLIMIT_STACK;
				break;
			case 't':
				factor = 1;
				command = RLIMIT_CPU;
				break;
#endif	/* _BSD || _BSD_SYSV */
			case 'f':
				command = RLIMIT_FSIZE;
#if _BSD_SYSV
				factor = 512;
#endif
				break;
			default:
#if _BSD
				errorf("Usage: %s [-cdmstf] [limit]\n", "ulimit");
#else
				errorf("Usage: %s [-f] [limit]\n", "ulimit");
#endif
		}
		a1 = a2;
	}
	if (a1)
	{
		i = 0;
		while ((c = *a1++) >= '0' && c <= '9')
		{
			i = (i * 10) + (long)(c - '0');
			if (i < 0)
				goto Error;
		}
		if (c || i < 0)
			goto Error;
	}
#if !(defined(_BSD) || defined(_BSD_SYSV))
	else
	{
		i = -1;
		command--;
	}

	if ((i = ulimit(command, i)) < 0L)
		goto Error;

	if (command != RLIMIT_FSIZE)
		shellf("%ld\n", i);
#else					/* DPK -- generalized for 4.nBSD: */
	if (getrlimit(command, &limit))
		goto Error;	/* errno is already set */

	if (a1)
	{
		limit.rlim_cur = i * factor;

		if (!softonly)
			limit.rlim_max = limit.rlim_cur;

		if (setrlimit(command, &limit))
			goto Error;
	}
	else
	{
		i = softonly ? limit.rlim_cur : limit.rlim_max;
#if _BSD			/* DAG -- System V always prints an integer */
		if (i == RLIM_INFINITY)
			shellf("unlimited\n");
		else
#endif
			shellf("%ld\n", i/factor);
	}
#endif	/* _BSD || _BSD_SYSV */
	return 0;

  Error:
	errorf("bad ulimit\n");
}

#pragma pop_macro("RCSid")
#pragma pop_macro("RLIMIT_FSIZE")

#pragma push_macro("RCSid")
#define RCSid RCSid_var
#line 1 "var.c"
#ifndef lint
static char *RCSid = "$Id: var.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <setjmp.h>
#include <time.h>

/*
 * Variables
 *
 * WARNING: unreadable code, needs a rewrite
 *
 * if (flag&INTEGER), val.i contains integer value, and type contains base.
 * otherwise, (val.s + type) contains string value.
 * if (flag&EXPORT), val.s contains "name=value" for E-Z exporting.
 */
char	null []	= "";
static	struct tbl vtemp;
static void     export      ARGS((struct tbl *vp, char *val));
static int      special     ARGS((char *name));
static void     getspec     ARGS((struct tbl *vp));
static void     setspec     ARGS((struct tbl *vp));

/*
 * create a new block for function calls and simple commands
 * assume caller has allocated and set up e.loc
 */
void
newblock()
{
	register struct block *l = e.loc;
	static char *empty[] = {""};

	ainit(&l->area);
	l->argc = 0;
	l->argv = empty;
	l->exit = l->error = NULL;
	tinit(&l->vars, &l->area);
	tinit(&l->funs, &l->area);
}

/*
 * pop a block handling special variables
 */
void
popblock()
{
	register struct block *l = e.loc;
	register struct tbl *vp, **vpp = l->vars.tbls;
	register int i;

	e.loc = l->next;	/* pop block */
	for (i = l->vars.size; --i >= 0; )
		if ((vp = *vpp++) != NULL && (vp->flag&SPECIAL))
			setspec(global(vp->name));
	afreeall(&l->area);
}

/*
 * Search for variable, if not found create globally.
 */
struct tbl *
global(n)
	register char *n;
{
	register struct block *l = e.loc;
	register struct tbl *vp;
	register int c;
	unsigned h = hash(n);

	c = n[0];
	if (digit(c)) {
		vp = &vtemp;
		lastarea = ATEMP;
		vp->flag = (DEFINED|RDONLY);
		vp->type = 0;
		*vp->name = c;	/* should strncpy */
		for (c = 0; digit(*n) && c < 1000; n++)
			c = c*10 + *n-'0';
		if (c <= l->argc)
			setstr(vp, l->argv[c]);
		return vp;
	} else
	if (!letter(c)) {
		vp = &vtemp;
		lastarea = ATEMP;
		vp->flag = (DEFINED|RDONLY);
		vp->type = 0;
		*vp->name = c;
		if (n[1] != '\0')
			return vp;
		vp->flag |= ISSET|INTEGER;
		switch (c) {
		  case '$':
			vp->val.i = kshpid;
			break;
		  case '!':
			vp->val.i = async;
			break;
		  case '?':
			vp->val.i = exstat;
			break;
		  case '#':
			vp->val.i = l->argc;
			break;
		  case '-':
			vp->flag &= ~ INTEGER;
			vp->val.s = getoptions();
			break;
		  default:
			vp->flag &= ~(ISSET|INTEGER);
		}
		return vp;
	}
	for (l = e.loc; l != NULL; l = l->next) {
		vp = tsearch(&l->vars, n, h);
		lastarea = &l->area;
		if (vp != NULL)
			return vp;
		if (l->next == NULL)
			break;
	}
	vp = tenter(&l->vars, n, h);
	vp->flag |= DEFINED;
	if (special(n))
		vp->flag |= SPECIAL;
	return vp;
}

/*
 * Search for local variable, if not found create locally.
 */
struct tbl *
local(n)
	register char *n;
{
	register struct block *l = e.loc;
	register struct tbl *vp;
	unsigned h = hash(n);

	if (!letter(*n)) {
		vp = &vtemp;
		lastarea = ATEMP;
		vp->flag = (DEFINED|RDONLY);
		vp->type = 0;
		return vp;
	}
	vp = tenter(&l->vars, n, h);
	lastarea = &l->area;
	vp->flag |= DEFINED;
	if (special(n))
		vp->flag |= SPECIAL;
	return vp;
}

/* get variable string value */
char *
strval(vp)
	register struct tbl *vp;
{
	register char *s;
	static char strbuf[40];

	if ((vp->flag&SPECIAL))
		getspec(vp);
	if (!(vp->flag&ISSET))
		return null;	/* special to dollar() */
	if (!(vp->flag&INTEGER))	/* string source */
		s = vp->val.s + vp->type;
	else {				/* integer source */
		register unsigned long n;
		register int base;

		s = strbuf + sizeof(strbuf);
		n = (vp->val.i < 0) ? -vp->val.i : vp->val.i;
		base = (vp->type == 0) ? 10 : vp->type;

		*--s = '\0';
		do {
			*--s = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[n%base];
			n /= base;
		} while (n != 0);
		/* todo: should we output base# ? */
		if (vp->val.i < 0)
			*--s = '-';
	}
	return s;
}

/* get variable integer value */
long
intval(vp)
	register struct tbl *vp;
{
	register struct tbl *vq;

	if ((vp->flag&SPECIAL))
		getspec(vp);
	if ((vp->flag&INTEGER))
		return vp->val.i;
	vq = &vtemp;
	vq->flag = (INTEGER);
	vq->type = 0;
	if (strint(vq, vp) == NULL)
		errorf("%s: bad number\n", vp->val.s);
	return vq->val.i;
}

/* set variable to string value */
void
setstr(vq, s)
	register struct tbl *vq;
	char *s;
{
	if (!(vq->flag&INTEGER)) { /* string dest */
		if ((vq->flag&ALLOC))
			afree((void*)vq->val.s, lastarea);
		vq->flag &= ~ (ISSET|ALLOC);
		vq->type = 0;
		if ((vq->flag&EXPORT))
			export(vq, s);
		else
			vq->val.s = strsave(s, lastarea);
		vq->flag |= ALLOC;
	} else {		/* integer dest */
		register struct tbl *vp = &vtemp;	
		vp->flag = (DEFINED|ISSET);
		vp->type = 0;
		vp->val.s = s;
		if (strint(vq, vp) == NULL)
			errorf("%s: bad number\n", s);
	}
	vq->flag |= ISSET;
	if ((vq->flag&SPECIAL))
		setspec(vq);
}
	
/* convert variable to integer variable */
struct tbl *
strint(vq, vp)
	register struct tbl *vq, *vp;
{
	register char *s = vp->val.s + vp->type;
	register int c;
	int base, neg = 0;
	
	vq->flag |= INTEGER;
	if (!(vp->flag&ISSET) || (s == NULL && !(vp->flag&INTEGER))) {
		vq->flag &= ~ ISSET;
		return NULL;
	}
	if ((vp->flag&INTEGER)) {
		vq->val.i = vp->val.i;
		return vq;
	}
	vq->val.i = 0;
	base = 10;
	for (c = *s++; c ; c = *s++)
		if (c == '-') {
			neg++;
		} else if (c == '#') {
			base = vq->type = vq->val.i;
			vq->val.i = 0;
		} else if (letnum(c)) {
			if ('0' <= c && c <= '9')
				c -= '0';
			else if ('a' <= c && c <= 'z') /* fuck EBCDIC */
				c -= 'a'-10;
			else if ('A' <= c && c <= 'Z')
				c -= 'A'-10;
			if (c < 0 || c >= base) {
				vq->flag &= ~ ISSET;
				return NULL;
			}
			vq->val.i = (vq->val.i*base) + c;
		} else
			break;
	if (neg)
		vq->val.i = -vq->val.i;
	if (vq->type < 2 || vq->type > 36)
		vq->type = 0;	/* default base (10) */
	return vq;
}

/* set variable to integer */
void
setint(vq, n)
	register struct tbl *vq;
	long n;
{
	if (!(vq->flag&INTEGER)) {
		register struct tbl *vp = &vtemp;
		vp->flag = (ISSET|INTEGER);
		vp->type = 0;
		vp->val.i = n;
		setstr(vq, strval(vp));	/* ? */
	} else
		vq->val.i = n;
	vq->flag |= ISSET;
	if ((vq->flag&SPECIAL))
		setspec(vq);
}

/* set variable from enviroment */
import(thing)
	char *thing;
{
	register struct tbl *vp;
	register char *val;

	val = strchr(thing, '=');
	if (val == NULL)
		return 0;
	*val = '\0';
	vp = local(thing);
	*val++ = '=';
	vp->flag |= DEFINED|ISSET|EXPORT;
	vp->val.s = thing;
	vp->type = val - thing;
	if ((vp->flag&SPECIAL))
		setspec(vp);
	return 1;
}

/*
 * make vp->val.s be "name=value" for quick exporting.
 */
static void
export(vp, val)
	register struct tbl *vp;
	char *val;
{
	register char *cp, *xp;
	char *op = (vp->flag&ALLOC) ? vp->val.s : NULL;

	xp = (char*)alloc(strlen(vp->name) + strlen(val) + 2, lastarea);
	vp->flag |= ALLOC;
	vp->val.s = xp;
	for (cp = vp->name; (*xp = *cp++) != '\0'; xp++)
		;
	*xp++ = '=';
	vp->type = xp - vp->val.s; /* offset to value */
	for (cp = val; (*xp++ = *cp++) != '\0'; )
		;
	if (op != NULL)
		afree((void*)op, lastarea);
}

/*
 * lookup variable (according to (set&LOCAL)),
 * set its attributes (INTEGER, RDONLY, EXPORT, TRACE),
 * and optionally set its value if an assignment.
 */
struct tbl *
typeset(var, set, clr)
	register char *var;
	int clr, set;
{
	register struct tbl *vp;
	register char *val;

	/* check for valid variable name, search for value */
	val = var;
	if (!letter(*val))
		return NULL;
	for (val++; *val != '\0'; val++)
		if (*val == '=')
			break;
		else if (letnum(*val))
			;
		else
			return NULL;
	if (*val == '=')
		*val = '\0';
	else
		val = NULL;
	vp = (set&LOCAL) ? local(var) : global(var);
	set &= ~ LOCAL;
	if (val != NULL)
		*val++ = '=';

	if (!(vp->flag&ISSET))
		vp->flag = (vp->flag & ~clr) | set;
	else
	    if (!(vp->flag&INTEGER) && (set&INTEGER)) {
		/* string to integer */
		vtemp.flag = (ISSET);
		vtemp.type = 0;
		vtemp.val.s = vp->val.s + vp->type;
		if ((vp->flag&ALLOC))
			afree((void*)vp->val.s, lastarea); /* dangerous, used later */
		vp->flag &= ~ ALLOC;
		vp->flag |= INTEGER;
		vp->type = 0;
		if (val == NULL && strint(vp, &vtemp) == NULL) {
			vp->flag &= ~ ISSET;
			errorf("%s: bad number\n", vtemp.val.s);
		}
	    } else
	    if ((clr&INTEGER) && (vp->flag&INTEGER)) {
		/* integer to string */
		vtemp.val.s = strval(vp);
		vp->flag &= ~ INTEGER;
		setstr(vp, vtemp.val.s);
	    }

	vp->flag = (vp->flag & ~clr) | set;

	if (val != NULL) {
		if ((vp->flag&RDONLY))
			errorf("cannot set readonly %s\n", var);
		if ((vp->flag&INTEGER))
			/* setstr should be able to handle this */
			(void)evaluate(var);
		else
			setstr(vp, val);
	}

	if ((vp->flag&EXPORT) && !(vp->flag&INTEGER) && vp->type == 0)
		export(vp, (vp->flag&ISSET) ? vp->val.s : null);

	return vp;
}

void
unset(vp)
	register struct tbl *vp;
{
	if ((vp->flag&ALLOC))
		afree((void*)vp->val.s, lastarea);
	vp->flag &= SPECIAL;	/* Should ``unspecial'' some vars */
}

int
isassign(s)
	register char *s;
{
	if (!letter(*s))
		return (0);
	for (s++; *s != '='; s++)
		if (*s == 0 || !letnum(*s))
			return (0);
	return (1);
}

/*
 * Make the exported environment from the exported names in the dictionary.
 */
char **
makenv()
{
	struct block *l = e.loc;
	XPtrV env;
	register struct tbl *vp, **vpp;
	register int i;

	XPinit(env, 64);
	for (l = e.loc; l != NULL; l = l->next)
		for (vpp = l->vars.tbls, i = l->vars.size; --i >= 0; )
			if ((vp = *vpp++) != NULL
			    && (vp->flag&(ISSET|EXPORT)) == (ISSET|EXPORT)) {
				register struct block *l2;
				register struct tbl *vp2;
				unsigned h = hash(vp->name);

				lastarea = &l->area;

				/* unexport any redefined instances */
				for (l2 = l->next; l2 != NULL; l2 = l2->next) {
					vp2 = tsearch(&l2->vars, vp->name, h);
					if (vp2 != NULL)
						vp2->flag &= ~ EXPORT;
				}
				if ((vp->flag&INTEGER)) {
					/* integer to string */
					char *val;
					val = strval(vp);
					vp->flag &= ~ INTEGER;
					setstr(vp, val);
				}
				XPput(env, vp->val.s);
			}
	XPput(env, NULL);
	return (char **) XPclose(env);
}

/*
 * handle special variables with side effects - PATH, SECONDS.
 */

static int
special(name)
	register char * name;
{
	if (strcmp("PATH", name) == 0)
		return V_PATH;
	if (strcmp("IFS", name) == 0)
		return V_IFS;
	if (strcmp("SECONDS", name) == 0)
		return V_SECONDS;
	if (strcmp("OPTIND", name) == 0)
		return V_OPTIND;
	if (strcmp("MAIL", name) == 0)
		return V_MAIL;
	if (strcmp("MAILPATH", name) == 0)
		return V_MAILPATH;
	if (strcmp("RANDOM", name) == 0)
		return V_RANDOM;
	return V_NONE;
}

extern	time_t time();
static	time_t	seconds;		/* time SECONDS last set */
#ifdef NOSTDHDRS
extern	int	rand();
extern	void	srand();
#endif

static void
getspec(vp)
	register struct tbl *vp;
{
	switch (special(vp->name)) {
	case V_SECONDS:
		vp->flag &= ~ SPECIAL;
		setint(vp, time((time_t *)0) - seconds);
		vp->flag |= SPECIAL;
		break;
	case V_RANDOM:
		vp->flag &= ~ SPECIAL;
		setint(vp, (rand() & 0x7fff));
		vp->flag |= SPECIAL;
		break;
	}
}

static void
setspec(vp)
	register struct tbl *vp;
{
	extern void	mbset(), mpset();

	switch (special(vp->name)) {
	  case V_PATH:
		path = strval(vp);
		flushcom(1);	/* clear tracked aliases */
		break;
	  case V_IFS:
		setctypes(strval(vp), C_IFS);
		break;
	  case V_SECONDS:
		seconds = time((time_t *)0);
		break;
	  case V_OPTIND:
		if (intval(vp) == 1)
			resetopts();
		break;
	  case V_MAIL:
		mbset(strval(vp));
		break;
	  case V_MAILPATH:
		mpset(strval(vp));
		break;
	  case V_RANDOM:
		vp->flag &= ~ SPECIAL;
		srand((unsigned int)intval(vp));
		vp->flag |= SPECIAL;
		break;
	}
}

#pragma pop_macro("RCSid")

#pragma push_macro("INIT_TBLS")
#pragma push_macro("RCSid")
#define RCSid RCSid_table
#line 1 "table.c"
#ifndef lint
static char *RCSid = "$Id: table.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

/*
 * dynamic hashed associative table for commands and variables
 */

#include <errno.h>
#include <setjmp.h>

#define	INIT_TBLS	8	/* initial table size (power of 2) */

static struct tstate {
	int left;
	struct tbl **next;
} tstate;

static void     texpand     ARGS((struct table *tp, int nsize));
static int      tnamecmp    ARGS((void *p1, void *p2));


unsigned int
hash(n)
	register char * n;
{
	register unsigned int h = 0;

	while (*n != '\0')
		h = 2*h + *n++;
	return h * 32821;	/* scatter bits */
}

#if 0
phash(s) char *s; {
	printf("%2d: %s\n", hash(s)%32, s);
}
#endif

void
tinit(tp, ap)
	register struct table *tp;
	register Area *ap;
{
	tp->areap = ap;
	tp->size = tp->free = 0;
	tp->tbls = NULL;
}

static void
texpand(tp, nsize)
	register struct table *tp;
	int nsize;
{
	register int i;
	register struct tbl *tblp, **p;
	register struct tbl **ntblp, **otblp = tp->tbls;
	int osize = tp->size;

	ntblp = (struct tbl**) alloc(sizeofN(struct tbl *, nsize), tp->areap);
	for (i = 0; i < nsize; i++)
		ntblp[i] = NULL;
	tp->size = nsize;
	tp->free = 8*nsize/10;	/* table can get 80% full */
	tp->tbls = ntblp;
	if (otblp == NULL)
		return;
	for (i = 0; i < osize; i++)
		if ((tblp = otblp[i]) != NULL)
			if ((tblp->flag&DEFINED)) {
				for (p = &ntblp[hash(tblp->name) &
						(tp->size-1)];
				     *p != NULL; p--)
					if (p == ntblp) /* wrap */
						p += tp->size;
				*p = tblp;
				tp->free--;
			} else {
				afree((void*)tblp, tp->areap);
			}
	afree((void*)otblp, tp->areap);
}

struct tbl *
tsearch(tp, n, h)
	register struct table *tp;	/* table */
	register char *n;		/* name to enter */
	unsigned int h;			/* hash(n) */
{
	register struct tbl **pp, *p;

	if (tp->size == 0)
		return NULL;

	/* search for name in hashed table */
	for (pp = &tp->tbls[h & (tp->size-1)]; (p = *pp) != NULL; pp--) {
		if (*p->name == *n && strcmp(p->name, n) == 0
		    && (p->flag&DEFINED))
			return p;
		if (pp == tp->tbls) /* wrap */
			pp += tp->size;
	}

	return NULL;
}

struct tbl *
tenter(tp, n, h)
	register struct table *tp;	/* table */
	register char *n;		/* name to enter */
	unsigned int h;			/* hash(n) */
{
	register struct tbl **pp, *p;
	register char *cp;

	if (tp->size == 0)
		texpand(tp, INIT_TBLS);
  Search:
	/* search for name in hashed table */
	for (pp = &tp->tbls[h & (tp->size-1)]; (p = *pp) != NULL; pp--) {
		if (*p->name == *n && strcmp(p->name, n) == 0)
			return p; 	/* found */
		if (pp == tp->tbls) /* wrap */
			pp += tp->size;
	}

	if (tp->free <= 0) {	/* too full */
		texpand(tp, 2*tp->size);
		goto Search;
	}

	/* create new tbl entry */
	for (cp = n; *cp != '\0'; cp++)
		;
	p = (struct tbl *) alloc(offsetof(struct tbl, name[(cp-n)+1]), tp->areap);
	p->flag = 0;
	p->type = 0;
	for (cp = p->name; *n != '\0';)
		*cp++ = *n++;
	*cp = '\0';

	/* enter in tp->tbls */
	tp->free--;
	*pp = p;
	return p;
}

void
tdelete(p)
	register struct tbl *p;
{
	p->flag = 0;
}

void
twalk(tp)
	register struct table *tp;
{
	tstate.left = tp->size;
	tstate.next = tp->tbls;
}

struct tbl *
tnext()
{
	while (--tstate.left >= 0) {
		struct tbl *p = *tstate.next++;
		if (p != NULL && (p->flag&DEFINED))
			return p;
	}
	return NULL;
}

static int
tnamecmp(p1, p2)
	void *p1, *p2;
{
	return strcmp(((struct tbl *)p1)->name, ((struct tbl *)p2)->name);
}

struct tbl **
tsort(tp)
	register struct table *tp;
{
	register int i;
	register struct tbl **p, **sp, **dp;

	p = (struct tbl **)alloc(sizeofN(struct tbl *, tp->size+1), ATEMP);
	sp = tp->tbls;		/* source */
	dp = p;			/* dest */
	for (i = 0; i < tp->size; i++)
		if ((*dp = *sp++) != NULL && ((*dp)->flag&DEFINED))
			dp++;
	i = dp - p;
	qsortp((void**)p, (size_t)i, tnamecmp);
	p[i] = NULL;
	return p;
}

#pragma pop_macro("RCSid")
#pragma pop_macro("INIT_TBLS")

#pragma push_macro("XARG")
#pragma push_macro("XARGSEP")
#pragma push_macro("XBASE")
#pragma push_macro("XCOM")
#pragma push_macro("XSUB")
#pragma push_macro("RCSid")
#define RCSid RCSid_eval
#line 1 "eval.c"
/*
 * Expansion - quoting, separation, substitution, globbing
 */

#ifndef lint
static char *RCSid = "$Id: eval.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <setjmp.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>

/*
 * string expansion
 *
 * first pass: quoting, IFS separation, ${} and $() substitution.
 * second pass: filename expansion (*?[]~).
 */

/* expansion generator state */
typedef struct Expand {
	/* int  type; */	/* see expand() */
	char   *str;		/* string */
	union {
		char  **strv;	/* string[] */
		FILE   *file;	/* file */
	} u;			/* source */
	short	split;		/* split "$@"*/
} Expand;

#define	XBASE	0		/* scanning original */
#define	XSUB	1		/* expanding ${} string */
#define	XARGSEP	2		/* ifs0 between "$@" */
#define	XARG	3		/* expanding $*, $@ */
#define	XCOM	4		/* expanding $() */

static void     expand      ARGS((char *cp, XPtrV *wp, int f));
static int      varsub      ARGS((Expand *xp, char *sp, int stype));
static int      comsub      ARGS((Expand *xp, char *cp));
static char *   trimsub     ARGS((char *str, char *pat, int how));
static void     glob        ARGS((char *cp, XPtrV *wp));
static void     globit      ARGS((char *ds, char *dp, char *sp, XPtrV *wp, int check));
static char *   debunk      ARGS((char *cp));
static char *   tilde       ARGS((char *acp));
static char *   homedir     ARGS((char *name));

int	ifs0 = ' ';		/* todo: first char of $IFS */

/* compile and expand word */
char *
substitute(cp, f)
	char const *cp;
	int f;
{
	struct source *s, *sold;

	sold = source;
	s = pushs(SWSTR);
	s->str = (char *) cp;
	source = s;
	if (yylex(ONEWORD) != LWORD)
		errorf("eval:substitute error\n");
	source = sold;
	return evalstr(yylval.cp, f);
}

/*
 * expand arg-list
 */
char **
eval(ap, f)
	register char **ap;
{
	XPtrV w;

	if (*ap == NULL)
		return ap;
	XPinit(w, 32);
	XPput(w, NULL);		/* space for shell name */
#ifdef	SHARPBANG
	XPput(w, NULL);		/* and space for one arg */
#endif
	while (*ap != NULL)
		expand(*ap++, &w, f);
	XPput(w, NULL);
#ifdef	SHARPBANG
	return (char **) XPclose(w) + 2;
#else
	return (char **) XPclose(w) + 1;
#endif
}

/*
 * expand string
 */
char *
evalstr(cp, f)
	register char *cp;
	int f;
{
	XPtrV w;

	XPinit(w, 1);
	expand(cp, &w, f);
	cp = (XPsize(w) == 0) ? "" : (char*) *XPptrv(w);
	XPfree(w);
	return cp;
}

/* for nested substitution: ${var:=$var2} */
typedef struct SubType {
	short	type;		/* [=+-?%#] action after expanded word */
	short	base;		/* begin position of expanded word */
	char   *name;		/* name for ${var=word} */
} SubType;

static void
expand(cp, wp, f)
	char *cp;		/* input word */
	register XPtrV *wp;	/* output words */
	int f;			/* DO* flags */
{
	register int c;
	register int type = XBASE; /* expansion type */
	register int quote = 0;	/* quoted */
	int quotestack[11];	/* Keep this bigger than the subtype stack */
	register int *qst = quotestack + 11;	/* This too, of course */
	XString ds;		/* destination string */
	register char *dp, *sp;	/* dest., source */
	int fdo, word, combase;	/* second pass flags; have word */
	Expand x;		/* expansion variables */
	SubType subtype [10];	/* substitution type stack */
	register SubType *st = subtype + 10;
	int newlines;		/* For trailing newlines in COMSUB */
	int trimming = 0;	/* flag if expanding ${var#pat} or ${var%pat} */

	if (cp == NULL)
		errorf("eval:expand(NULL)\n");
	if (flag[FNOGLOB])
		f &= ~ DOGLOB;

	Xinit(ds, dp, 128);	/* init dest. string */
	type = XBASE;
	sp = cp;
	fdo = 0;
	word = !(f&DOBLANK);

	while (1) {
		Xcheck(ds, dp);

		switch (type) {
		  case XBASE:	/* original prefixed string */
			c = *sp++;
			switch (c) {
			  case EOS:
				c = 0;
				break;
			  case CHAR:
				c = *sp++;
				break;
			  case QCHAR:
				quote |= 2; /* temporary quote */
				c = *sp++;
				break;
			  case OQUOTE:
				word = quote = 1;
				continue;
			  case CQUOTE:
				quote = 0;
				continue;
			  case COMSUB:
				type = comsub(&x, sp);
				sp = strchr(sp, 0) + 1;
				combase = Xsavepos(ds, dp);
				newlines = 0;
				continue;
			  case OSUBST: /* ${var{:}[=+-?]word} */
				cp = sp; 		/* variable */
				sp = strchr(sp, 0) + 1;	/* skip variable */
				c = (*sp == CSUBST) ? 0 : *sp++;
				if ((c&0x7F) == '#' || (c&0x7F) == '%') {
					if (flag[FNOUNSET] &&
					    strval(global(cp)) == null)
						errorf("%s: unset variable\n", cp);
					trimming++;
					type = XBASE;
					*--qst = quote;
					quote = 0;
				} else
					type = varsub(&x, cp, c);
				if (type == XBASE) {	/* expand? */
					if (st == subtype)
						errorf("ridiculous ${} nesting\n");
					--st;
					st->type = c;
					st->base = Xsavepos(ds, dp);
					st->name = cp;
				} else
					sp = wdscan(sp, CSUBST); /* skip word */
				continue;
			  case CSUBST: /* only get here if expanding word */
				*dp = 0;
				if (f&DOGLOB)
					f &= ~DOPAT;
				switch (st->type&0x7F) {
				  case '#':
				  case '%':
					*dp = 0;
					dp = Xrestpos(ds, dp, st->base);
					quote = *qst++;
					x.str = trimsub(strval(global(st->name)),
						dp, st->type);
					type = XSUB;
					trimming--;
					continue;
				  case '=':
#if 0
					if ((x.u.vp->flag&RDONLY))
						errorf("cannot set readonly %s\n", cp);
#endif
					setstr(global(st->name), Xrestpos(ds, dp, st->base));
					break;
				  case '?':
					if (dp == Xrestpos(ds, dp, st->base))
						errorf("missing value for %s\n", cp);
					else
						errorf("%s\n", Xrestpos(ds, dp, st->base));
				}
				st++;
				type = XBASE;
				continue;
			}
			break;

		  case XSUB:
			if ((c = *x.str++) == 0) {
				type = XBASE;
				continue;
			}
			break;

		  case XARGSEP:
			type = XARG;
			quote = 1;
		  case XARG:
			if ((c = *x.str++) == 0) {
				if ((x.str = *x.u.strv++) == NULL) {
					type = XBASE;
					continue;
				} else if (quote && x.split) {
					/* terminate word for "$@" */
					type = XARGSEP;
					quote = 0;
				}
				c = ifs0;
			}
			break;

		  case XCOM:
			if (newlines) {		/* Spit out saved nl's */
				c = '\n';
				--newlines;
			} else {
				while ((c = getc(x.u.file)) == '\n')
					newlines++;	/* Save newlines */
				if (newlines && c != EOF) {
					ungetc(c, x.u.file);
					c = '\n';
					--newlines;
				}
			}
			if (c == EOF) {
				cp = Xrestpos(ds, sp, combase);
				newlines = 0;
				fclose(x.u.file);
				if (x.split)
					waitlast();
				type = XBASE;
				continue;
			}
			break;
		}

		/* check for end of word or IFS separation */
		if (c == 0 || (!quote && (f&DOBLANK) && ctype(c, C_IFS))) {
			if (word) {
				*dp++ = 0;
				cp = Xclose(ds, dp);
				if (fdo&DOTILDE)
					cp = tilde(cp);
				if (fdo&DOGLOB)
					glob(cp, wp);
				else
					{XPput(*wp, cp);}
				fdo = word = 0;
				if (c != 0)
					Xinit(ds, dp, 128);
			} else
				; /* ignore IFS */
			if (c == 0)
				return;
		} else {
			/* mark any special second pass chars */
			if (!quote)
				switch (c) {
				  case '*':
				  case '?':
				  case '[':
					if (f&(DOPAT|DOGLOB) || trimming) {
						fdo |= (f&DOGLOB);
						*dp++ = MAGIC;
					}
					break;
				  case NOT:
					if ((f&(DOPAT|DOGLOB) || trimming) &&
					    dp[-1] == '[' && dp[-2] == MAGIC) {
						*dp++ = MAGIC;
					}
					break;
				  case '~':
					if (((f&DOTILDE) &&
					     dp == Xstring(ds, dp)) ||
					    (!(f&DOBLANK) && 
					    (dp[-1] == '=' || dp[-1] == ':'))) {
						fdo |= DOTILDE;
						*dp++ = MAGIC;
					}
					break;
				}
			else
				quote &= ~2; /* undo temporary */

			word = 1;
			*dp++ = c; /* save output char */
		}
	}
}

/*
 * Prepare to generate the string returned by ${} substitution.
 */
static int
varsub(xp, sp, stype)
	register Expand *xp;
	register char *sp;
	int stype;
{
	register int c;
	int type;

	/* ${#var}, string length or argc */
	if (sp[0] == '#' && (c = sp[1]) != 0) {
		c = (c == '*' || c == '@') ? e.loc->argc :
			strlen(strval(global(sp+1)));
		xp->str = strsave(ulton((unsigned long)c, 10), ATEMP);
		return XSUB;
	}

	c = sp[0];
	if (c == '*' || c == '@') {
		if (e.loc->argc == 0) {
			xp->str = null;
			type = XSUB;
		} else {
			xp->u.strv = e.loc->argv + 1;
			xp->str = *xp->u.strv++;
			xp->split = c == '@'; /* $@ */
			type = XARG;
		}
	} else {
		xp->str = strval(global(sp));
		type = XSUB;
	}

	c = stype&0x7F;
	/* test the compiler's code generator */
	if (c == '%' || c == '#' ||
	    (((stype&0x80) ? *xp->str=='\0' : xp->str==null) ? /* undef? */
	     c == '=' || c == '-' || c == '?' : c == '+'))
		type = XBASE;	/* expand word instead of variable value */
	if (type != XBASE && flag[FNOUNSET] && xp->str == null && c != '+')
		errorf("%s: unset variable\n", sp);
	return type;
}

/*
 * Run the command in $(...) and read its output.
 */
static int
comsub(xp, cp)
	register Expand *xp;
	char *cp;
{
	Source *s;
	register struct op *t;
	FILE *fi;

	s = pushs(SSTRING);
	s->str = cp;
	t = compile(s);

	if (t != NULL && t->type == TCOM && /* $(<file) */
	    *t->args == NULL && *t->vars == NULL && t->ioact != NULL) {
		register struct ioword *io = *t->ioact;

		if ((io->flag&IOTYPE) != IOREAD)
			errorf("funny $() command\n");
		fi = fopen(evalstr(io->name, DOTILDE), "r");
		if (fi != NULL)
			fileno(fi) = savefd(fileno(fi));
		xp->split = 0;	/* no waitlast() */
	} else {
		int ofd1, pv[2];
		openpipe(pv);
		fi = fdopen(pv[0], "r");
		ofd1 = savefd(1);
		dup2(pv[1], 1);
		close(pv[1]);
#if 0
		exchild(t, XXCOM|XPIPEO);
#else
		execute(t, XFORK|XXCOM|XPIPEO);
#endif
		dup2(ofd1, 1);
		close(ofd1);
		xp->split = 1;	/* waitlast() */
	}	

	if (fi == NULL)
		errorf("cannot open $() input\n");
	setvbuf(fi, (char *)NULL, _IOFBF, BUFSIZ);
	xp->u.file = fi;
	return XCOM;
}

/*
 * perform #pattern and %pattern substitution in ${}
 */

static char *
trimsub(str, pat, how)
	register char *str;
	char *pat;
	int how;
{
	register char *end = strchr(str, 0);
	register char *p, c, *match;

	switch (how&0xff) {	/* UCHAR_MAX maybe? */
	case '#':		/* shortest at begin */
		for (p = str; p <= end; p++) {
			c = *p; *p = '\0';
			if (gmatch(str, pat)) {
				*p = c;
				return p;
			}
			*p = c;
		}
		break;
	case '#'|0x80:		/* longest match at begin */
		for (p = end; p >= str; p--) {
			c = *p; *p = '\0';
			if (gmatch(str, pat)) {
				*p = c;
				return p;
			}
			*p = c;
		}
		break;
	case '%':		/* shortest match at end */
		for (p = end; p >= str; p--) {
			if (gmatch(p, pat)) {
				c = *p; *p = '\0';
				match = strsave( str, APERM );	/* APERM? */
				*p = c;
				return match;
			}
		}
		break;
	case '%'|0x80:	/* longest match at end */
		for (p = str; p <= end; p++) {
			if (gmatch(p, pat)) {
				c = *p; *p = '\0';
				match = strsave( str, ATEMP );	/* APERM? */
				*p = c;
				return match;
			}
		}
		break;
	}

	return str;		/* no match, return string */
}

/*
 * glob
 * Name derived from V6's /etc/glob, the program that expanded filenames.
 */

static	char   *debunk();

static void 
glob(cp, wp)
	char *cp;
	register XPtrV *wp;
{
	char path [PATH];
	register char *sp = cp;
	int oldsize;

	oldsize = XPsize(*wp);
	globit(path, path, sp, wp, 0);

	if (XPsize(*wp) == oldsize)
		{XPput(*wp, debunk(cp));}
	else
		qsortp(XPptrv(*wp) + oldsize, (size_t)(XPsize(*wp) - oldsize), xstrcmp);
}

static void
globit(ds, dp, sp, wp, check)
	char *ds;		/* dest path */
	char *dp;		/* dest end */
	char *sp;		/* source path */
	register XPtrV *wp;	/* output list */
	int check;		/* check dest existence */
{
	register char *np;	/* next source component */
	register char *tsp, *tdp;

	if (sp == NULL) {	/* end of source path */
		if (check && eaccess(ds, 0) < 0)
			return;
		XPput(*wp, strsave(ds, ATEMP));
		return;
	}

	if (dp > ds)
		*dp++ = '/';
	while (*sp == '/')
		*dp++ = *sp++;
	np = strchr(sp, '/');
	if (np != NULL)
		*np++ = 0;

	*dp = 0;
	if (strchr(sp, MAGIC) == NULL) { /* contains no pattern? */
		tdp = dp; tsp = sp;
		while ((*tdp++ = *tsp++) != 0)
			;
		--tdp;
		globit(ds, tdp, np, wp, check);
	} else {
		DIR *dirp;
		struct dirent *d;

		/* ToDo:
		 * should not attemp to open() special files: /dev/ttyd0/*
		 * opendir should do this check, but Doug Gwyn's does not.
		 */
		dirp = opendir((*ds == 0) ? "." : ds);
		if (dirp == NULL)
			goto Nodir;
		while ((d = readdir(dirp)) != NULL) {
			tsp = d->d_name;
			if (tsp[0] == '.' &&
			    (tsp[1] == 0 || (tsp[1] == '.' && tsp[2] == 0)))
				continue; /* always ignore . and .. */
			if ((*tsp == '.' && *sp != '.') || !gmatch(tsp, sp))
				continue;

			tdp = dp;
			while ((*tdp++ = *tsp++) != 0)
				;
			--tdp;
			globit(ds, tdp, np, wp, np != NULL);
		}
		closedir(dirp);
	  Nodir:;
	}

	if (np != NULL)
		*--np = '/';
}

/* remove MAGIC from string */
static char *
debunk(cp)
	char *cp;
{
	register char *dp, *sp;

	for (dp = sp = cp; *sp != 0; sp++)
		if (*sp != MAGIC)
			*dp++ = *sp;
	*dp = 0;
	return cp;
}

/*
 * tilde expansion
 *
 * based on a version by Arnold Robbins
 */

static char *homedir();

static char *
tilde(acp)
	char *acp;
{
	register int c;
	char path [PATH+1];
	register char *cp = acp, *wp = path, *dp;
	char userid [16+1];

  Again:
	while (1) {
		if ((c = *cp++) == 0) {
			*wp = 0;
			afree((void*)acp, ATEMP);
			return strsave(path, ATEMP);
		} else if (c == MAGIC && *cp == '~')
			break;
		else
			*wp++ = c;
	}

	dp = NULL;	/* no output substitution */
	if (cp[1] == 0 || cp[1] == '/' || cp[1] == ':') /* ~ or ~/ */
		dp = strval(global("HOME")), cp += 1;
	else if (cp[1] == '+' && (cp[2] == '/' || cp[2] == ':' || cp[2] == 0))
		dp = strval(global("PWD")), cp += 2;
	else if (cp[1] == '-' && (cp[2] == '/' || cp[2] == ':' || cp[2] == 0))
		dp = strval(global("OLDPWD")), cp += 2;
	else if (letter(cp[1])) {
		char *save = cp;
		for (dp = userid, cp++; letnum(*cp) && dp < userid+16; )
			*dp++ = *cp++;
		*dp = 0;
		dp = homedir(userid);
		if (dp == NULL)
			cp = save;
	}
	/* substitute */
	if (dp != NULL)
		while (*dp != 0)
			*wp++ = *dp++;
	goto Again;
}

/*
 * map userid to user's home directory.
 * todo: implement a cache with the "homedirs" table.
 * note that 4.3's getpw adds more than 6K to the shell,
 * and the YP version probably adds much more.
 * we might consider our own version of getpwnam() to keep the size down.
 */

static char *
homedir(name)
	char *name;
{
	register struct tbl *ap;
	register struct passwd *pw;
	extern struct passwd *getpwnam();

	ap = tsearch(&homedirs, name, hash(name));
	if ((ap != NULL && (ap->flag&ISSET)))
		return ap->val.s;
	pw = getpwnam(name);
	if (pw == NULL)
		return NULL;
	return pw->pw_dir;
}
#pragma pop_macro("RCSid")
#pragma pop_macro("XSUB")
#pragma pop_macro("XCOM")
#pragma pop_macro("XBASE")
#pragma pop_macro("XARGSEP")
#pragma pop_macro("XARG")

#pragma push_macro("LEQ")
#pragma push_macro("LGE")
#pragma push_macro("LIT")
#pragma push_macro("LLE")
#pragma push_macro("LNE")
#pragma push_macro("VAR")
#pragma push_macro("ef")
#pragma push_macro("RCSid")
#define RCSid RCSid_expr
#line 1 "expr.c"
/*
 * Korn expression evaluation
 */

#ifndef lint
static char *RCSid = "$Id: expr.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <errno.h>
#include <setjmp.h>

#define	ef	else if		/* fashion statement */

#define	VAR	0x01
#define	LIT	0x02
#define	LEQ	0x03
#define	LNE	0x04
#define	LLE	0x05
#define	LGE	0x06

static const char *expression;	/* expression being evaluated */
static const char *tokp;	/* lexical position */
static int tok;			/* token from token() */
static struct tbl *val;		/* value from token() */

static struct tbl *asn      ARGS((void));
static struct tbl *e6       ARGS((void));
static struct tbl *e5       ARGS((void));
static struct tbl *e3       ARGS((void));
static struct tbl *e2       ARGS((void));
static struct tbl *e0       ARGS((void));
static void     token       ARGS((void));
static struct tbl *tempvar  ARGS((void));
static struct tbl *intvar   ARGS((struct tbl *vp));

/*
 * parse and evalute expression
 */
void
evalerr(err)
	char *err;
{
	errorf("%s: %s\n", expression, err);
}

long
evaluate(expr)
	const char *expr;
{
	struct tbl *v;

	expression = tokp = expr;
	token();
	v = intvar(asn());
	if (!(tok == 0))
		evalerr("bad expression");
	return v->val.i;
}

static struct tbl *
asn()
{
	register struct tbl *vl, *vr;

	vr = vl = e6();
	if ((tok == '=')) {
		Area * olastarea = lastarea;
		token();
		if ((vl->flag&RDONLY)) /* assign to rvalue */
			evalerr("bad assignment");
		vr = intvar(asn());
		lastarea = olastarea;
		setint(vl, vr->val.i);
		if ((vl->flag&INTEGER) && vl->type == 0) /* default base? */
			vl->type = vr->type;
	}
	return vr;
}

static struct tbl *
e6()
{
	register struct tbl *vl, *vr;

	vl = e5();
	while ((tok == LEQ) || (tok == LNE)) {
		int op = tok;
		token();
		vl = intvar(vl);
		vr = intvar(e5());
		vl->val.i = vl->val.i == vr->val.i;
		if (op == LNE)
			vl->val.i = ! vl->val.i;
	}
	return vl;
}

static struct tbl *
e5()
{
	register struct tbl *vl, *vr;

	vl = e3();
	while ((tok == LLE) || (tok == '<') || (tok == '>') || (tok == LGE)) {
		int op = tok;
		token();
		vl = intvar(vl);
		vr = intvar(e3());
		if (op == LLE)
			vl->val.i = vl->val.i <= vr->val.i;
		ef (op == '<')
			vl->val.i = vl->val.i < vr->val.i;
		ef (op == LGE)
			vl->val.i = vl->val.i >= vr->val.i;
		ef (op == '>')
			vl->val.i = vl->val.i > vr->val.i;
	}
	return vl;
}

static struct tbl *
e3()
{
	register struct tbl *vl, *vr;

	vl = e2();
	while ((tok == '+') || (tok == '-')) {
		int op = tok;
		token();
		vl = intvar(vl);
		vr = intvar(e2());
		if (op == '+')
			vl->val.i += vr->val.i;
		ef (op == '-')
			vl->val.i -= vr->val.i;
	}
	return vl;
}

static struct tbl *
e2()
{
	register struct tbl *vl, *vr;

	vl = e0();
	while ((tok == '*') || (tok == '/') || (tok == '%')) {
		int op = tok;
		token();
		vl = intvar(vl);
		vr = intvar(e0());
		if (op != '*' && vr->val.i == 0)
			evalerr("zero divisor");
		if (op == '*')
			vl->val.i *= vr->val.i;
		ef (op == '/')
			vl->val.i /= vr->val.i;
		ef (op == '%')
			vl->val.i %= vr->val.i;
	}
	return vl;
}

static struct tbl *
e0()
{
	register struct tbl *v;

	if ((tok == '!') || (tok == '-')) {
		int op = tok;
		token();
		v = intvar(e0());
		if (op == '!')
			v->val.i = !v->val.i;
		ef (op == '-')
			v->val.i = -v->val.i;
	} else
	if ((tok == '(')) {
		token();
		v = asn();
		if (!(tok == ')'))
			evalerr("missing )");
		token();
	} else
	if ((tok == VAR) || (tok == LIT)) {
		v = val;
		token();
	} else
		evalerr("bad expression");
	return v;
}

static void
token()
{
	register char *cp = (char *) tokp;
	register int c, c2;

	/* skip white space */
	do c = *cp++;	while (c != '\0' && (c == ' ' || c == '\t'));
	tokp = cp-1;

	if (letter(c)) {
		for (; letnum(c); c = *cp++)
			;
		c = *--cp;
		*cp = 0;
		val = global(tokp);
		*cp = c;
		tok = VAR;
	} else
	if (digit(c)) {
		for (; letnum(c) || c == '#'; c = *cp++)
			;
		c = *--cp;
		*cp = 0;
		val = tempvar();
		setstr(val, tokp);
		val->flag |= RDONLY;
		*cp = c;
		tok = LIT;
	} else {
		c2 = *cp++;
		if (c == '=' && c2 == '=')
			c = LEQ;
		ef (c == '!' && c2 == '=')
			c = LNE;
		ef (c == '<' && c2 == '=')
				c = LLE;
		ef (c == '>' && c2 == '=')
				c = LGE;
		else
			cp--;
		tok = c;
	}
	tokp = cp;
}

static struct tbl *
tempvar()
{
	register struct tbl *vp;

	vp = (struct tbl*) alloc(sizeof(struct tbl), ATEMP);
	lastarea = ATEMP;
	vp->flag = ISSET|INTEGER;
	vp->type = 0;
	vp->name[0] = '\0';
	return vp;
}

/* cast (string) variable to temporary integer variable */
static struct tbl *
intvar(vp)
	register struct tbl *vp;
{
	register struct tbl *vq;

	vq = tempvar();
	vq->type = 10;
	if (strint(vq, vp) == NULL) {
		if ((vp->flag&ISSET) && vp->val.s && *(vp->val.s)) {
			evalerr("bad number");
		} else {
			vq->flag |= (ISSET|INTEGER);
			vq->type = 10;
			vq->val.i = 0;
		}
	}
	return vq;
}

#pragma pop_macro("RCSid")
#pragma pop_macro("ef")
#pragma pop_macro("VAR")
#pragma pop_macro("LNE")
#pragma pop_macro("LLE")
#pragma pop_macro("LIT")
#pragma pop_macro("LGE")
#pragma pop_macro("LEQ")

#pragma push_macro("MBMESSAGE")
#pragma push_macro("RCSid")
#define RCSid RCSid_mail
#line 1 "mail.c"
/*
 * Mailbox checking code by Robert J. Gibson, adapted for PD ksh by
 * John R. MacMillan
 */
#ifndef lint
static char *RCSid = "$Id: mail.c,v 1.2 1992/04/25 08:33:28 sjg Exp $";
#endif

#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <sys/stat.h>

#define MBMESSAGE	"you have mail in $_"

typedef struct mbox {
	struct mbox    *mb_next;	/* next mbox in list */
	char	       *mb_path;	/* path to mail file */
	char	       *mb_msg;		/* to announce arrival of new mail */
	unsigned int	mb_size;	/* size of mail file (bytes) */
} mbox_t;

struct mailmsg {
	char		*msg;		/* Text of message */
	struct mailmsg	*next;		/* Next message */
};

/*
 * $MAILPATH is a linked list of mboxes.  $MAIL is a treated as a
 * special case of $MAILPATH, where the list has only one node.  The
 * same list is used for both since they are exclusive.
 */

static mbox_t  *mplist = NULL;
static mbox_t  mbox = { NULL, NULL, NULL, 0 };
static long	mlastchkd = 0;	/* when mail was last checked */
static struct mailmsg *mmsgs = NULL;	/* Messages to be printed */
#if 0
static void	munset();		/* free mlist and mval */
static mbox_t  *mballoc();		/* allocate a new mbox */
static void	maddmsg();
#endif
static void     munset      ARGS((mbox_t *mlist));
static mbox_t * mballoc     ARGS((char *p, char *m));
static void     maddmsg     ARGS((mbox_t *mbp));

void
mcheck()
{
	register mbox_t	*mbp;
	long		 now;
	struct tbl	*vp, mailcheck;
	struct stat	 stbuf;

	vp = global("MAILCHECK");
	if (!(vp->flag & ISSET) || strint(&mailcheck, vp) == NULL)
		return;

	if (mlastchkd == 0)
		mlastchkd = time((long *)0);

	if ((now=time((long *)0)) - mlastchkd >= mailcheck.val.i) {
		mlastchkd = now;
		
		vp = global("MAILPATH");
		if (vp && (vp->flag & ISSET))
			mbp = mplist;
		else if ((vp = global("MAIL")) && (vp->flag & ISSET))
			mbp = &mbox;
		else
			mbp = NULL;

		while (mbp) {
			if (stat(mbp->mb_path, &stbuf) == 0 &&
			    (stbuf.st_mode & S_IFMT) == S_IFREG) {
				if (mbp->mb_size < stbuf.st_size)
					maddmsg( mbp );
				mbp->mb_size = stbuf.st_size;
			} else {
				/*
				 * Some mail readers remove the mail
				 * file if all mail is read.  If file
				 * does not exist, assume this is the
				 * case and set size to zero.
				 */
				mbp->mb_size = 0;
			}
			mbp = mbp->mb_next;
		}
	}
}

void
mbset(p)
	register char	*p;
{
	struct stat	stbuf;

	if (mbox.mb_msg)
		afree((void *)mbox.mb_msg, APERM);
	mbox.mb_path = p;
	mbox.mb_msg = NULL;
	if (stat(p,&stbuf) == 0 && (stbuf.st_mode & S_IFMT) == S_IFREG)
		mbox.mb_size = stbuf.st_size;
	else
		mbox.mb_size = 0;
}

void
mpset(mptoparse)
	register char	*mptoparse;
{
	register mbox_t	*mbp;
	register char	*mpath, *mmsg, *mval;

	munset( mplist );
	mplist = NULL;
	mval = strsave(mptoparse, APERM);
	while (mval) {
		mpath = mval;
		if ((mval = strchr(mval, ':')) != NULL) {
			*mval ='\0', mval++;
		}
		if ((mmsg = strchr(mpath, '?')) != NULL) {
			*mmsg = '\0', mmsg++;
		}
		mbp = mballoc(mpath, mmsg);
		mbp->mb_next = mplist;
		mplist = mbp;
	}
}

static void
munset(mlist)
register mbox_t	*mlist;
{
	register mbox_t	*mbp;

	while (mlist != NULL) {
		mbp = mlist;
		mlist = mbp->mb_next;
		if (!mlist)
			afree((void *)mbp->mb_path, APERM);
		afree((void *)mbp, APERM);
	}
}

static mbox_t *
mballoc(p, m)
	char	*p;
	char	*m;
{
	struct stat	stbuf;
	register mbox_t	*mbp;

	mbp = (mbox_t *)alloc(sizeof(mbox_t), APERM);
	mbp->mb_next = NULL;
	mbp->mb_path = p;
	mbp->mb_msg = m;
	if (stat(mbp->mb_path, &stbuf) == 0 &&
	   (stbuf.st_mode & S_IFMT) == S_IFREG) {
		mbp->mb_size = stbuf.st_size;
	} else {
		mbp->mb_size = 0;
	}
	return(mbp);
}

void
mprint()
{
	struct mailmsg *mm;

	while ((mm = mmsgs) != NULL) {
		shellf( "%s\n", mm->msg );
		fflush(shlout);
		afree((void *)mm->msg, APERM);
		mmsgs = mm->next;
		afree((void *)mm, APERM);
	}
}

static void
maddmsg( mbp )
mbox_t	*mbp;
{
	struct mailmsg	*message;
	struct tbl	*vp;

	message = (struct mailmsg *)alloc(sizeof(struct mailmsg), APERM);
	setstr((vp = typeset("_", LOCAL, 0)), mbp->mb_path);

	if (mbp->mb_msg)
		message->msg = strsave(substitute(mbp->mb_msg,0),APERM);
	else
		message->msg = strsave(substitute(MBMESSAGE,0),APERM);

	unset(vp);
	message->next = mmsgs;
	mmsgs = message;
}
#pragma pop_macro("RCSid")
#pragma pop_macro("MBMESSAGE")

#pragma push_macro("ARGS")
#pragma push_macro("NSIG")
#pragma push_macro("SA_NOCLDSTOP")
#pragma push_macro("SA_RESTART")
#pragma push_macro("SIG_BLOCK")
#pragma push_macro("SIG_SETMASK")
#pragma push_macro("SIG_UNBLOCK")
#pragma push_macro("USE_SIGMASK")
#pragma push_macro("USE_SIGNAL")
#pragma push_macro("USE_SIGSET")
#pragma push_macro("_SIGACT_H")
#pragma push_macro("const")
#pragma push_macro("sigmask")
#pragma push_macro("volatile")
#pragma push_macro("RCSid")
#define RCSid RCSid_sigact
#line 1 "sigact.c"
/* NAME:
 *      sigact.c - fake sigaction(2)
 *
 * SYNOPSIS:
 *      #include <signal.h>
 *      #ifndef  SA_NOCLDSTOP
 *      # include "sigact.h"
 *      #endif
 * 
 *      int sigaction(int sig, struct sigaction *act, 
 *                      struct sigaction *oact);
 *      int sigaddset(sigset_t *mask, int sig);
 *      int sigdelset(sigset_t *mask, int sig);
 *      int sigemptyset(sigset_t *mask);
 *      int sigfillset(sigset_t *mask);
 *      int sigismember(sigset_t *mask, int sig);
 *      int sigpending(sigset_t *set);
 *      int sigprocmask(int how, sigset_t *set, sigset_t *oldset);
 *      int sigsuspend(sigset_t *mask);
 *
 * DESCRIPTION:
 *      This is a fake sigaction implementation.  It uses 
 *      sigset(2) if available, otherwise it just uses 
 *      signal(2).  If it thinks sigaction(2) really exists it 
 *      compiles to almost nothing.
 *      
 *      The need for all this is the problems caused by mixing 
 *      signal handling routines in the one process.  This 
 *      module allows for a consistent POSIX compliant interface 
 *      to whatever is available.
 *
 * RETURN VALUE:
 *      0==success, -1==failure
 *
 * FILES:
 *      None.
 *
 * SEE ALSO:
 *      
 *
 * BUGS:
 *      Since we fake most of this, don't expect fancy usage to 
 *      work.
 *      
 * COPYRIGHT:
 *      @(#)Copyright (c) 1992 Simon J. Gerraty
 *
 *      This is free software.  It comes with NO WARRANTY.
 *      Permission to use, modify and distribute this source code 
 *      is granted subject to the following conditions.
 *      1/ that that the above copyright notice and this notice 
 *      are preserved in all copies and that due credit be given 
 *      to the author.  
 *      2/ that any changes to this code are clearly commented 
 *      as such so that the author does get blamed for bugs 
 *      other than his own.
 *      
 *      Please send copies of changes and bug-fixes to:
 *      sjg@zen.void.oz.au
 *
 */
#ifndef lint
static char  *RCSid = "$Id: sigact.c,v 1.5 1992/05/03 08:29:10 sjg Exp $";
#endif
/*
 * $Log: sigact.c,v $
 * Revision 1.5  1992/05/03  08:29:10  sjg
 * Update for Patch05
 *
 * Revision 1.4  1992/04/29  06:29:13  sjg
 * avoid use of #pragma
 *
 * Revision 1.3  1992/04/26  11:24:43  sjg
 * USE_SIGSET corrected in sigsuspend().
 *
 * Revision 1.2  1992/04/24  15:04:11  sjg
 * now compiles with cc
 *
 * Revision 1.1  1992/04/24  12:03:58  sjg
 * Initial revision
 *
 */

#include <signal.h>

/*
 * some systems have a faulty sigaction() implementation!
 * Allow us to bypass it.
 */
#if !defined(SA_NOCLDSTOP) || defined(USE_SIGNAL) || defined(USE_SIGSET) || defined(USE_SIGMASK)

/*
 * if we haven't been told,
 * try and guess what we should implement with.
 */
#if !defined(USE_SIGSET) && !defined(USE_SIGMASK) && !defined(USE_SIGNAL)
# if defined(sigmask) || defined(BSD) || defined(_BSD) && !defined(BSD41)
#   define USE_SIGMASK
# else
#   ifndef NO_SIGSET
#     define USE_SIGSET
#   else
#     define USE_SIGNAL
#   endif
# endif
#endif
/*
 * if we still don't know, we're in trouble
 */
#if !defined(USE_SIGSET) && !defined(USE_SIGMASK) && !defined(USE_SIGNAL)
error must know what to implement with
#endif

/* begin inlined sigact.h from sigact.c */
/* NAME:
 *      sigact.h - sigaction et al
 *
 * SYNOPSIS:
 *      #include <signal.h>
 *      #ifndef  SA_NOCLDSTOP
 *      # include "sigact.h"
 *      #endif
 *
 * DESCRIPTION:
 *      This header is the interface to a fake sigaction(2) implementation.  
 *      Do NOT include this header unless your system does not 
 *      have a real sigaction(2) implementation.
 */
/*
 * $Log: sigact.h,v $
 * Revision 1.2  1992/04/24  15:04:11  sjg
 * now compiles with cc
 *
 * Revision 1.1  1992/04/24  12:01:38  sjg
 * Initial revision
 *
 */

#ifndef _SIGACT_H
#define _SIGACT_H

#ifndef ARGS
# if defined(__STDC__)
#   define ARGS(p) p
# else
#   define ARGS(p) ()
# endif
#endif
#ifndef __STDC__
# define volatile			/* can change without warning */
# define const				/* read only */
#endif

#ifndef SIGKILL
# include <signal.h>
#endif
#ifndef SA_NOCLDSTOP
/* sa_flags */
#define	SA_NOCLDSTOP	0x0001		/* don't send SIGCHLD on child stop */
#define SA_RESTART	0x0002		/* re-start I/O */

/* sigprocmask flags */
#define	SIG_BLOCK	0x0001
#define	SIG_UNBLOCK	0x0002
#define	SIG_SETMASK	0x0004

#ifndef __sys_stdtypes_h
typedef int sigset_t;
#endif

struct sigaction
{
  void		(*sa_handler)();
  sigset_t	sa_mask;
  int		sa_flags;
};


int	sigaction	ARGS(( int sig, struct sigaction *act, struct sigaction *oact ));
int	sigaddset	ARGS(( sigset_t *mask, int sig ));
int	sigdelset	ARGS(( sigset_t *mask, int sig ));
int	sigemptyset	ARGS(( sigset_t *mask ));
int	sigfillset	ARGS(( sigset_t *mask ));
int	sigismember	ARGS(( sigset_t *mask, int sig ));
int	sigpending	ARGS(( sigset_t *set ));
int	sigprocmask	ARGS(( int how, sigset_t *set, sigset_t *oldset ));
int	sigsuspend	ARGS(( sigset_t *mask ));

#ifndef sigmask
#define sigmask(m)	(1<<((m)-1))	/* convert SIGnum to mask */
#endif
#if !defined(NSIG) && defined(_NSIG)
# define NSIG _NSIG
#endif
#endif /* ! SA_NOCLDSTOP */
#endif /* _SIGACT_H */
/*
 * Local Variables:
 * version-control:t
 * comment-column:40
 * End:
 */
/* end inlined sigact.h from sigact.c */



int
sigaction(sig, act, oact)
  int sig;
  struct sigaction *act, *oact;
{
  void (*oldh)();

  if (act)
  {
#ifdef USE_SIGSET
    oldh = sigset(sig, act->sa_handler);
#else
    oldh = signal(sig, act->sa_handler);
#endif
  }
  else
  {
    if (oact)
    {      
#ifdef USE_SIGSET
      oldh = sigset(sig, SIG_IGN);
#else
      oldh = signal(sig, SIG_IGN);
#endif
      if (oldh != SIG_IGN)
      {
#ifdef USE_SIGSET
	(void) sigset(sig, oldh);
#else
	(void) signal(sig, oldh);
#endif
      }
    }
  }
  if (oact)
  {
    oact->sa_handler = oldh;
  }
  return 0;				/* hey we're faking it */
}

int
sigaddset(mask, sig)
  sigset_t *mask;
  int sig;
{
  *mask |= sigmask(sig);
  return 0;
}


int
sigdelset(mask, sig)
  sigset_t *mask;
  int sig;
{
  *mask &= ~(sigmask(sig));
  return 0;
}


int
sigemptyset(mask)
  sigset_t *mask;
{
  *mask = 0;
  return 0;
}


int
sigfillset(mask)
  sigset_t *mask;
{
  *mask = ~0;
  return 0;
}


int
sigismember(mask, sig)
  sigset_t *mask;
  int sig;
{
  return ((*mask) & sigmask(sig));
}


int
sigpending(set)
  sigset_t *set;
{
  return 0;
}


int
sigprocmask(how, set, oldset)
  int how;
  sigset_t *set, *oldset;
{
#ifdef USE_SIGSET
  register int i;
#endif
  sigset_t sm;

#ifdef USE_SIGMASK
  sm = sigblock(0);
#else
  sm = 0;
#endif
  
  if (oldset)
    *oldset = sm;	/* dangerous ? */
  if (set)
  {
    switch (how)
    {
    case SIG_BLOCK:
      sm |= *set;
      break;
    case SIG_UNBLOCK:
      sm &= ~(*set);
      break;
    case SIG_SETMASK:
      sm = *set;
      break;
    }
#ifdef USE_SIGMASK
    (void) sigsetmask(sm);
#else
# ifdef USE_SIGSET
    for (i = 1; i < NSIG; i++)
    {
      if (how == SIG_UNBLOCK)
      {
	if (*set & sigmask(i))
	  sigrelse(i);
      }
      else
	if (sm & sigmask(i))
	{
	  sighold(i);
	}
    }
# endif
#endif
  }
  return 0;
}


int
sigsuspend(mask)
  sigset_t *mask;
{
#ifdef USE_SIGSET
  int sig = SIGCHLD;			/* our default */
  
  /*
   * add as many tests as you think sensible, but
   * SIGALRM, and SIGCHLD are probably the most
   * common.
   */
  if (*mask & sigmask(SIGALRM))
    sig = SIGALRM;
  else
    if (*mask & sigmask(SIGPIPE))
      sig = SIGPIPE;
  sigpause(sig);
#else
# ifdef USE_SIGMASK
  sigpause(mask);
# else
  pause();
# endif
#endif
  return 0;
}

#endif /* ! SA_NOCLDSTOP */


/* This lot (for GNU-Emacs) goes at the end of the file. */
/* 
 * Local Variables:
 * version-control:t
 * comment-column:40
 * End:
 */
#pragma pop_macro("RCSid")
#pragma pop_macro("volatile")
#pragma pop_macro("sigmask")
#pragma pop_macro("const")
#pragma pop_macro("_SIGACT_H")
#pragma pop_macro("USE_SIGSET")
#pragma pop_macro("USE_SIGNAL")
#pragma pop_macro("USE_SIGMASK")
#pragma pop_macro("SIG_UNBLOCK")
#pragma pop_macro("SIG_SETMASK")
#pragma pop_macro("SIG_BLOCK")
#pragma pop_macro("SA_RESTART")
#pragma pop_macro("SA_NOCLDSTOP")
#pragma pop_macro("NSIG")
#pragma pop_macro("ARGS")

#pragma push_macro("ARGS")
#pragma push_macro("BOOLEAN")
#pragma push_macro("ENTRY")
#pragma push_macro("EXTERN")
#pragma push_macro("EXTERN_DEFINED")
#pragma push_macro("FALSE")
#pragma push_macro("LOCAL")
#pragma push_macro("TRUE")
#pragma push_macro("_CDECL")
#pragma push_macro("_NEAR")
#pragma push_macro("_TRACE")
#pragma push_macro("RCSid")
#define RCSid RCSid_trace
#line 1 "trace.c"
/* NAME:
 *      trace.c - a simple trace facility
 *
 * SYNOPSIS:
 *      TRACE(level, (fmt [, ...]));
 *
 * DESCRIPTION:
 *      This module provides a simple trace facility via
 *      a call to checkpoint() which opens a log file and writes 
 *      an entry and closes the log (so that process crashes 
 *      won't destroy the log :-).  checkpoint() takes options 
 *      like printf().  If Trace_log is not initialized then
 *      stderr is used.
 *      
 *      The header file trace.h defines a macro TRACE() which 
 *      is useful in that it allows checkpoint to be called 
 *      based on the value of Trace_level, and the calls can be 
 *      eliminated by undefining USE_TRACE.
 *
 * RETURN VALUE:
 *      None.
 *
 * FILES:
 *      None.
 *
 * SEE ALSO:
 *      
 *
 * BUGS:
 *      
 *
 * AMENDED:
 *      91/11/22  22:53:56  (sjg)
 *
 * RELEASED:
 *      91/11/22  22:54:17  v1.2
 *
 *      @(#)Copyright (c) 1990 Simon J. Gerraty.
 */
#ifdef USE_TRACE

#ifndef lint
static char  sccs_id[] = "@(#)trace.c     1.2  91/11/22  22:53:56  (sjg)";
#endif

/* include files */
#include <stdio.h>
#ifdef __STDC__
# include <stdlib.h>
#endif

#define EXTERN
/* begin inlined trace.h from trace.c */
/* NAME:
 *      trace.h - definitions for a simple trace facility
 *
 * SYNOPSIS:
 *      #include "trace.h"
 *
 * DESCRIPTION:
 *      Defines the macro _TRACE().
 *      Also declares Trace_log and Trace_level.
 *
 * SEE ALSO:
 *      
 *
 * AMENDED:
 *      91/11/22  22:53:58  (sjg)
 *
 * RELEASED:
 *      91/11/22  22:54:18  v1.2
 *
 * SCCSID:
 *      @(#)trace.h  1.2  91/11/22  22:53:58  (sjg)
 *
 *      @(#)Copyright (c) 1990 Simon J. Gerraty.
 */

/* some useful #defines */
#ifndef EXTERN
# define EXTERN extern
# define EXTERN_DEFINED
#endif

#ifndef TRUE
# define TRUE  1
# define FALSE 0
#endif
#ifndef ARGS
# if defined(__STDC__) || defined(PROTO)
#   define ARGS(p) p
# else
#   define ARGS(p) ()
# endif
#endif

/*
 * this garbage is sometimes needed when mixing
 * langauges or calling conventions under DOS.
 */
#ifndef _CDECL
# if defined(MSDOS) || defined(MSC)
#   ifndef NO_EXT_KEYS
#     define _CDECL  cdecl
#     define _NEAR   near
#   else
#     define _CDECL
#     define _NEAR
#   endif
# else /* not DrOS */
#   define _CDECL
#   define _NEAR
# endif /* DOS */
#endif /* _CDECL */

/* manifest constants */

/* struct / union */

/* macros */


#ifdef USE_TRACE
EXTERN char * _CDECL	Trace_log;
EXTERN int _CDECL 	Trace_level;

void _CDECL checkpoint	ARGS((char *fmt, ...));

/*
 * This macro takes a variabel number of args. 
 * examples:
 * 	_TRACE(5, ("The current Debug level is %d\n", Debug));
 * Note that if more than two args are provided, all but the 
 * first (which should be an integer indicating the Trace-level 
 * required for this message to be printed) must be enclosed in 
 * parenthesis. 
 */
# define _TRACE(lev, args) if (Trace_level >= lev) checkpoint args
#else 	/* don't USE_TRACE */
  /*
   * this macro evaluates to a harmless no entry
   * loop that most optimizers will remove all together.
   */
# define _TRACE(l, args) while (0)
#endif 	/* USE_TRACE */


/* This lot goes at the END */
/* be sure not to interfere with anyone else's idea about EXTERN */
#ifdef EXTERN_DEFINED
# undef EXTERN_DEFINED
# undef EXTERN
#endif
/*
 * Local Variables:
 * version-control:t
 * comment-column:40
 * End:
 */
/* end inlined trace.h from trace.c */
#undef EXTERN

/* some useful #defines */
#ifndef ENTRY
# define ENTRY
# define LOCAL static
# define BOOLEAN int
#endif
#ifndef TRUE
# define TRUE  1
# define FALSE 0
#endif
#ifndef ARGS
# if defined(__STDC__) || defined(PROTO)
#   define ARGS(p) p
# else
#   define ARGS(p) ()
# endif
#endif


/* NAME:
 *      checkpoint - write a logfile entry
 *
 * SYNOPSIS:
 *      checkpoint(fmt, ...)
 *
 * DESCRIPTION:
 *      This function takes a variable number or args  
 *      like the printf(3S) family of functions.
 *
 * RETURN VALUE:
 *      None
 */
extern char * _CDECL strdup	ARGS((char *s));
  
#ifdef __STDC__
# include <stdarg.h>

ENTRY void _CDECL
checkpoint(fmt)
	char *fmt;
{
  int c;
  va_list arg_ptr;
  FILE *fp;
  register char *rcp;
  char  *mode;
  static  setup;
  
  va_start(arg_ptr, fmt);
#else  /* __STDC__ */
# include <varargs.h>
  
ENTRY void _CDECL
checkpoint(va_alist)
  va_dcl
{
  extern char *getenv	ARGS((char *var));
  char *fmt;
  int c;
  va_list arg_ptr;
  FILE *fp;
  register char *rcp;
  char  *mode;
  static  setup;
  
  va_start(arg_ptr);
  fmt = va_arg(arg_ptr, char *);
#endif /* __STDC__ */
  
  /* 42 is a "magic" number */
  if (setup == 42)
    mode = "a";
  else
  {
    if (Trace_level == 0 && (rcp = getenv("TRACE_LEVEL")))
      Trace_level = atoi(rcp);
    if (Trace_log == NULL || *Trace_log == '\0')
    {
      if (rcp = getenv("TRACE_LOG"))
	Trace_log = strdup(rcp);
      else
	Trace_log = NULL;
    }
    setup = 42;
    mode= "w";
  }
  if (Trace_log)
    fp = fopen(Trace_log, mode);
  else
    fp = stderr;
  if (fp != (FILE *)NULL)
  {
    vfprintf(fp, fmt, arg_ptr);
    fputc('\n', fp);
    if (fp == stderr)
      fflush(fp);
    else
      fclose(fp);
  }
}

#endif /* USE_TRACE */

/* This lot (for GNU-Emacs) goes at the end of the file. */
/* 
 * Local Variables:
 * version-control:t
 * comment-column:40
 * End:
 */
#pragma pop_macro("RCSid")
#pragma pop_macro("_TRACE")
#pragma pop_macro("_NEAR")
#pragma pop_macro("_CDECL")
#pragma pop_macro("TRUE")
#pragma pop_macro("LOCAL")
#pragma pop_macro("FALSE")
#pragma pop_macro("EXTERN_DEFINED")
#pragma pop_macro("EXTERN")
#pragma pop_macro("ENTRY")
#pragma pop_macro("BOOLEAN")
#pragma pop_macro("ARGS")
