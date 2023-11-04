#include <stdio.h>
#include <changepoint.h>

int main(){
    struct paramerters par;
    struct values val;
    InitParameters(&par);
    InitValues(&val);
    int a = IsChagePoint(470,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(484,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(484,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(474,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(484,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(493,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(773,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(870,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(773,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(4400,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(773,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(870,&par,&val);
    printf("%d\n",a);
    a = IsChagePoint(773,&par,&val);
    printf("%d\n",a);
    return 0;
}
/*
x = [
    487,
484,
474,
484,
493,
773,
870,
773,
4400,
773,
870,
773,
]
*/