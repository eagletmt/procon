n;m;j;M=1e9+7;d[4501][4501];main(i){scanf("%d%d",&n,&m);for(;i<=n;i++)for(j=1;j<=m;j++)d[i][j]=(i*j?(i>=j?i==j:d[i][j-i])+d[i-1][j]:1)%M;printf("%d\n",d[n][m]);}