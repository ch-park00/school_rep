%% 
a=load('rpdata.mat');
t=0:1/44100:2;
y1=a.y(441:881);
y1=[y1;zeros(440,1)];
y2=a.y(882:1322);
y2=[zeros(440,1);y2];
plot(y1,'color','r')
hold on;
plot(y2,'color','b')
legend('y1','y2');
%%
t=linspace(0,(2/5)*pi,1000);
v1=18*sqrt(2)*sin(5*t);
v2=8*sqrt(2)*cos(60*t+(pi/4));
v=v1+v2;
plot(v1);
hold on;
plot(v2);
plot(v);
m1=mean(v1);
m2=mean(v2);
m=mean(v);
r1=rms(v1);
r2=rms(v2);
r=rms(v);
%% 연습문제4-1
Fs=100;
Ts=1/Fs;
h=[ones(100,1);zeros(300,1)];
x=[ones(200,1);zeros(100,1)];
y=conv(x,h)*Ts;
plot(h,'r');
hold on;
plot(x,'g');
plot(y,'b');
legend('h','x','y');

%% 연습문제4-2
Fs=100;Ts=1/Fs;
h=[ones(100,1);zeros(300,1)];
x=[zeros(100,1);ones(100,1);linspace(1,0,100)'];
y=conv(x,h)/Fs;
plot(h,'r');
hold on;
plot(x,'g');
plot(y,'b');
legend('h','x','y');