%%
num1=10;den1=[1,2,10];
num2=5;den2=[1,5];
[num,den]=series(num1,den1,num2,den2);
printsys(num,den)
[num,den]=parallel(num1,den1,num2,den2);
printsys(num,den)
[num,den]=feedback(num1,den1,num2,den2);
printsys(num,den)

%%
kp=300;
hp=kp;
plant=tf([0 0 1],[1 10 20]);
sys_cl=feedback(hp*plant,1);
t=0:0.01:2;
step(sys_cl,t);

%%
kp=300;kd=10;
plant=tf([0 0 1],[1 10 20]);
Hpd=tf([kd kp],1);
%sys_cl=tf([0 kd kp],[1 10+kd 20+kp]);
sys_cl=feedback(Hpd*plant,1);
t=0:0.01:2;
step(sys_cl,t);

%%
kp=30;ki=70;
plant=tf([0 0 1],[1 10 20]);
hpi=tf([kp ki],[1 0]);
sys_cl=feedback(hpi*plant,1);
% settling time을 확인하기 힘들어 5초까지 확인
t=0:0.01:5; 
step(sys_cl,t);

%%
kp=350;ki=300;kd=50;
plant=tf([0 0 1],[1 10 20]);
hpid=tf([kd kp ki],[1 0]);
sys_cl=feedback(hpid*plant,1);
t=0:0.01:5;
step(sys_cl,t)
