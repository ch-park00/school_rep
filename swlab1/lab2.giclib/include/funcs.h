// funcs.h라는 코드가 include 되어 있지 않다면 endif까지 코드를 수행하고
// 이미 include되어 있다면 수행하지 않는다.
// 여러 번 include 하는 문제를 방지한다.
#ifndef FUNCS_H
#define FUNCS_H

void foo();
void goo();

#endif