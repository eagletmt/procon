main(c){char k[26];for(gets(k);c=getchar(),~c;)putchar(c>96?k[c-97]:c>64?k[c-65]-32:c);}