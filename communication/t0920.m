%%
Fs=1e3;Ts=1/Fs;
N=200;t=(0:N-1)*Ts;
x=randi([0 1],N,1);
figure(1)
stairs(t,x,'Linewidth',1);
ylim([0.2 1.2]);
xlabel('time $t$ (sec)','Interpreter','Latex');

%%
[r, lags]=xcorr(x,100,'unbiased'); %lags는 인덱스번호
figure(2),plot(lags*Ts,r,'Linewidth',1);grid on;
xlabel('delay $\tau$ (sec)', 'Interpreter','Latex');

%%
p=0.2; %1이 나올 확률이 0.2
y=rand(N,1)<p;
figure(3),stairs(t,y);ylim([0.2 1.2]);
grid on;set(gca,'Ytick',[0 1]);

%% 랜덤 워크
Fs=1e3;Ts=1/Fs;
N=200;t=(0:N-1)*Ts;
b=2*randi([0 1],N,1)-1;
x=cumsum(b);
figure(1);stairs(t,x,'Linewidth',1);grid on;
xlabel('time $t$ (sec)','Interpreter','Latex');

%% 위너 프로세스 /브라운 운동
Fs=1e3;Ts=1/Fs;
N=200;t=(0:N-1)*Ts;
b=2*rand(N,1)-1;
x=cumsum(b);
figure(1);plot(t,x,'Linewidth',1);grid on;
xlabel('time $t$ (sec)','Interpreter','Latex');


%% 브라운 운동 
N=1000;cnt=0;
N1=1000;
for i=1:1:N1
x=cumsum(randn(N,1));
y=cumsum(randn(N,1));

d(i,:)=sqrt(x.^2+y.^2);
end
%%
for i=1:N
   cnt=0;
   for j=1:N1
      if d(j,i)<=5
          cnt=cnt+1;
      end
   end
   p(i,1)=cnt/N1;
end

%% plot그리기
x=1:1:1000;
plot(x,p);
xlabel('실행 횟수');ylabel('확률');