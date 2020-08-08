%%
mylego=legoev3;
mymotor1=motor(mylego,'A'); 

EXE_TIME=10;
period=0.05;
angle=180;
set_time=2; 

input=zeros(1,set_time/period); 
input=[input angle*ones(1,(EXE_TIME-set_time)/period)]; % 입력 신호 생성
p=0.7;i=0.2;d=0.1; % pid제어기의 값 설정


resetRotation(mymotor1); %모터 위치 초기화
%resetRotation(mymotor2);

start(mymotor1); 
%start(mymotor2);

t=timer('TimerFcn','stat=false;','StartDelay', EXE_TIME); 
start(t); %타이머 시작

%%
stat=true; 
lastR1=0;
sumerror=0;
prv_error=0;
r1=[];
idx=1;

while stat==true % 타이머 동작중인 동안 이 루프 실행
   tic() 
   
   r1=[r1 readRotation(mymotor1)]; % 현재 모터위치 확인
   error=input(idx)-r1(end); % 입력 에러값 확인
   sumerror=sumerror+error*period;
   drverror=(error-prv_error)/period;
   
   mymotor1.Speed=int8(error*p)+int8(sumerror*i)+int8(drverror*d);
   
   prv_error=error;
   idx=idx+1;
   ct=toc();
   pause(period-ct);
end
figure();plot(input,'r');hold on;plot(r1,'k');ylim([-20 300])
stop(mymotor1);
clear mylego;
clear mymotor1;