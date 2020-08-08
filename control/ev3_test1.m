%%
mylego=legoev3;
mymotor1= motor(mylego, 'A');
mymotor2= motor(mylego, 'B'); % 모터 두개의 출력 포트는 각각 A,B에 연결

EXE_TIME = 10; % 실행 시간
period=0.1; % 샘플링 주기
speed=40; % 모터 속도
p=0.1,i=0,d=0; % 제어기 값

mymotor1.Speed =speed;
mymotor2.Speed =speed; % 각 모터의 스피드 설정

resetRotation(mymotor1);
resetRotation(mymotor2); % 모터 위치 초기화

start(mymotor1);
start(mymotor2); % 모터 회전 시작 


t=timer('TimerFcn','stat=false;','StartDelay', EXE_TIME);
start(t); % 타이머 시작

%%
stat =true;
lastR1=0;
lastR2=0;
speed1=[];
speed2=[];

sumerror=0;
prv_error=0;
while stat==true % 타이머 동작하는 동안 해당 루프 반복
   tic();
   r1=readRotation(mymotor1); %현재 모터 위치 읽기
   r2=readRotation(mymotor2);
   
   speed1=[speed1 (r1-lastR1)/period]; % 현재 모터 속도 계산
   speed2=[speed2 (r2-lastR2)/period];
   
   diff=speed1(end)-speed2(end); % 두 모터간의 속도차이 계산
   sumerror=sumerror+diff*period;
   drverror=(diff-prv_error)/period;
   mymotor1.Speed=mymotor1.Speed-int8(diff*p)+int8(sumerror*i)+int8(drverror*d); % 속도차이만큼 속도 제어
   
   lastR1=r1;
   lastR2=r2;
   dt=toc();
   pause(period-dt);
end

stop(mymotor1);
stop(mymotor2);
plot(speed1,'k');hold on;plot(speed2,'r');
clear mylego
clear mymotor1 
clear mymotor2

