%% 기초 데이터 생성
th=0:0.01*pi:2*pi;
x=2*cos(th);y=2*sin(th);
th1=pi/4:0.1*pi:11/18*pi;
x1=[2*cos(11/18*pi) -1.2 -1.45 -1.3 -0.6 0 1 1.75...
    2.75 3.5 4.4 5.1 6.1 7.8 8 7.8 4.5 3.5 2.5 1.7 2*cos(pi/4) 2*cos(th1);...
    2*sin(11/18*pi) 3.3 5 6 7.5 8.1 8.5 8.55 8.4 8 ...
    7.5 6.85 6 4.3 4 3.7 3.8 3.7 3.3 2.2 2*sin(pi/4) 2*sin(th1)];
x2=[cos(2/3*pi) sin(2/3*pi);-sin(2/3*pi) cos(2/3*pi)]*x1;
x3=[cos(2/3*pi) sin(2/3*pi);-sin(2/3*pi) cos(2/3*pi)]*x2;
%% plot 그리기
s=tic;
for i=1:5
    tic;
for th2=2*pi:-0.1*pi:0.1*pi %cw 축소
   temp=[cos(th2) -sin(th2);sin(th2) cos(th2)];
   y1=(th2/(2*pi))*temp*x1;
   y2=(th2/(2*pi))*temp*x2;
   y3=(th2/(2*pi))*temp*x3;
   clf;
   fill(th2/(2*pi)*x,th2/(2*pi)*y,'b')
   hold on;grid on;axis([-15 15 -15 15])
   fill(y1(1,:),y1(2,:),[0.3 0.3 0.3])
   fill(y2(1,:),y2(2,:),[0.3 0.3 0.3])
   fill(y3(1,:),y3(2,:),[0.3 0.3 0.3])
   text(-5,13,'201401653 박철희','fontsize',15)
   pause(0.0001)
end
time1(i)=toc;
tic;
for th2=0.1*pi:0.1*pi:2*pi %ccw 확대
   temp=[cos(th2) -sin(th2);sin(th2) cos(th2)];
   y1=(th2/(2*pi))*temp*x1;
   y2=(th2/(2*pi))*temp*x2;
   y3=(th2/(2*pi))*temp*x3;
   clf;
   fill((th2/(2*pi))*x,(th2/(2*pi))*y,'b')
   hold on;grid on;axis([-15 15 -15 15])
   fill(y1(1,:),y1(2,:),[0.3 0.3 0.3])
   fill(y2(1,:),y2(2,:),[0.3 0.3 0.3])
   fill(y3(1,:),y3(2,:),[0.3 0.3 0.3])
   text(-5,13,'201401653 박철희','fontsize',15)
   pause(0.0001)
end
time2(i)=toc;
end
toc(s)